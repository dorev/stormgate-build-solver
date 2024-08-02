#pragma once

#include "model.h"
#include "errorcodes.h"
#include "database.h"
#include "gamestate.h"
#include "graph.h"
#include "solverstrategy.h"

#include <vector>
#include <unordered_set>

namespace SGBuilds
{
    struct BuildOrderStep
    {
        const unsigned supply;
        const unsigned time;
        const ObjectID buy;
    };

    class Solver
    {
    public:
        ErrorCode Solve(ObjectID* objects, unsigned objectsSize)
        {
            std::vector<ObjectID> objectList = std::vector<ObjectID>(objects, objects + objectsSize);

            ErrorCode result = ValidateObjectList(objectList);
            CHECK_ERROR(result);

            result = PrepareTargets(objectList);
            CHECK_ERROR(result);

            result = InitSolver();
            CHECK_ERROR(result);

            result = ProcessGraph();
            CHECK_ERROR(result);

            result = PrepareBuildOrder();
            CHECK_ERROR(result);

            return Success;
        }

        ErrorCode GetBuildOrderSize(unsigned& buildOrderSize)
        {
            return NotYetImplemented;
        }

        ErrorCode ReadAndClearBuildOrder(BuildOrderStep*& buildOrderSteps)
        {
            return NotYetImplemented;
        }

    private:
        ErrorCode ValidateObjectList(std::vector<ObjectID> objectList)
        {
            if (objectList.empty())
            {
                return EmptyObjectList;
            }

            // Validate faction
            ObjectID faction = objectList[0] & ID::FactionMask;
            if (faction == 0)
            {
                return InvalidFaction;
            }
            _Faction = faction;

            // Validate that all objects belong to the same faction
            for (ObjectID id : objectList)
            {
                if ((id & ID::FactionMask) != faction)
                {
                    return MultipleFactionsInList;
                }
            }

            return Success;
        }

        ErrorCode PrepareTargets(std::vector<ObjectID> objectList)
        {
            for (ObjectID id : objectList)
            {
                // Find if a target already exists for that ID
                int objectTargetIndex = -1;
                for (int i = 0; i < _Targets.size(); ++i)
                {
                    if (_Targets[i].id == id)
                    {
                        objectTargetIndex = i;
                        break;
                    }
                }

                // Update or create the target
                if (objectTargetIndex >= 0)
                {
                    (*const_cast<int*>(&_Targets[objectTargetIndex].count))++;
                }
                else
                {
                    _Targets.push_back({id, 1});
                }
            }

            // Add targets for missing required objects (ex. missing production buildings for target units)
            // Production building identified that way will have a count of 0, to indicate an arbitrary count
            for (const Target& target : _Targets)
            {
                GetObject(object, target.id);

                std::vector<ObjectID> targetRequirements;
                ErrorCode result = object.ExpandRequirements(targetRequirements);
                CHECK_ERROR(result);

                // If a requirement is not met in _Targets, add it in
                for (const ObjectID& id : targetRequirements)
                {
                    if (!ContainsID(_Targets, id))
                    {
                        GetObject(requiredBuilding, id);
                        bool arbitraryCount = static_cast<const Building&>(requiredBuilding).producer;
                        _Targets.push_back({ id, arbitraryCount ? 0 : 1 });
                    }
                }
            }

            return Success;
        }

        ErrorCode InitSolver()
        {
            // Init graph
            GameState rootState;
            rootState.Reset(_Faction);
            _Graph.AddNode(rootState);

            // Select solver strategy based on faction
            switch (_Faction)
            {
            case ID::Vanguard:
                _SolverStrategy = std::make_shared<VanguardStrategy>();
                break;

            default:
                return NotYetImplemented;
            }

            return Success;
        }

        ErrorCode ProcessGraph()
        {
            ErrorCode result = Success;

            while (1)
            {
                _Graph.GetLeafNodes(_LeafNodes);
                if (_LeafNodes.size() == 1 && _Solution != nullptr)
                {
                    break;
                }

                // Update all leaves and check if they reach the build order target
                for (NodePtr node : _LeafNodes)
                {
                    result = node->state.Update(_Targets);
                    CHECK_ERROR(result);

                    bool hasReachedTargets = false;
                    result = node->state.HasReachedTargets(_Targets, hasReachedTargets);
                    CHECK_ERROR(result);

                    if (hasReachedTargets)
                    {
                        // Compare with the current solution
                        // The best branch should reach the build order target in the smallest time possible.
                        // A solved branch with a longer time than the current best solution should be pruned.
                        if (_Solution == nullptr || node->state.GetTime() < _Solution->state.GetTime())
                        {
                            _Solution = node;
                        }
                        else
                        {
                            // Move up the branch to remove previous nodes that didn't reach the targets
                            while (node->parent->children.size() == 1)
                            {
                                node = node->parent;
                            }
                            _Graph.RemoveNode(node);
                        }
                    }
                    else
                    {
                        result = _SolverStrategy->Update(_Targets, node);
                        CHECK_ERROR(result);
                    }
                }
            }

            return Success;
        }

        ErrorCode PrepareBuildOrder()
        {
            return NotYetImplemented;
        }

    private:
        ObjectID _Faction;
        std::vector<Target> _Targets;
        SolverStrategyPtr _SolverStrategy;

        Graph _Graph;
        std::vector<NodePtr> _LeafNodes;
        NodePtr _Solution;
    };
}
