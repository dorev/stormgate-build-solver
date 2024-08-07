#include "solver.h"
#include "database.h"
#include "faction.h"

namespace SGBuilds
{
    ErrorCode Solver::Solve(Objective* objectives, unsigned objectivesSize)
    {
        std::vector<Objective> objectiveList = std::vector<Objective>(objectives, objectives + objectivesSize);

        ErrorCode result = ValidateObjectiveList(objectiveList);
        CHECK_ERROR(result);

        result = PrepareObjectives(objectiveList);
        CHECK_ERROR(result);

        result = InitSolver();
        CHECK_ERROR(result);

        result = ProcessGraph();
        CHECK_ERROR(result);

        result = PrepareBuildOrder();
        CHECK_ERROR(result);

        return Success;
    }

    ErrorCode Solver::GetBuildOrderSize(unsigned& buildOrderSize)
    {
        (void) buildOrderSize;
        return NotYetImplemented;
    }

    ErrorCode Solver::ReadAndClearBuildOrder(BuildOrderStep*& buildOrderSteps)
    {
        (void) buildOrderSteps;
        return NotYetImplemented;
    }

    ErrorCode Solver::ValidateObjectiveList(std::vector<Objective> objectiveList)
    {
        if (objectiveList.empty())
        {
            return EmptyObjectiveList;
        }

        // Validate faction
        ObjectID factionId = GetObjectFaction(objectiveList[0]);
        if (factionId != ID::Vanguard && factionId != ID::Infernal && factionId != ID::Celestial)
        {
            return InvalidFaction;
        }

        _Faction = factionId;

        // Validate that all objects belong to the same faction
        for (const Objective& objective : objectiveList)
        {
            if (GetObjectFaction(objective) != factionId)
            {
                return MultipleFactionsInList;
            }
        }

        return Success;
    }

    ErrorCode Solver::PrepareObjectives(std::vector<Objective>& objectiveList)
    {
        _Objectives = objectiveList;

        // Add objectives for missing required objects (ex. missing production buildings for objective units)
        // Production building identified that way will have a count of 0, to indicate an arbitrary count
        for (const Objective& objective : _Objectives)
        {
            GET_PROTOTYPE(object, objective.id);

            std::vector<ObjectID> objectiveRequirements;
            ErrorCode result = object.ExpandRequirements(objectiveRequirements);
            CHECK_ERROR(result);

            // If a requirement is not met in _Objectives, add it in
            for (const ObjectID& id : objectiveRequirements)
            {
                if (!ContainsID(_Objectives, id))
                {
                    GET_PROTOTYPE(requiredBuilding, id);
                    bool arbitraryCount = static_cast<const Building&>(requiredBuilding).producer;
                    _Objectives.push_back({ id, arbitraryCount ? 0 : 1 });
                }
            }
        }

        return Success;
    }

    ErrorCode Solver::InitSolver()
    {
        // Init graph
        GameState rootState;
        rootState.Reset(Faction::Get(_Faction));
        _Graph.AddNode(rootState);

        return Success;
    }

    ErrorCode Solver::ProcessGraph()
    {
        ErrorCode result = Success;

        while (1)
        {
            _Graph.GetLeafNodes(_LeafNodes);
            if (_LeafNodes.size() == 1 && _Solution != nullptr)
            {
                break;
            }

            // Update all leaves and check if they reach the build order objective
            for (NodePtr node : _LeafNodes)
            {
                result = node->state.Update();
                CHECK_ERROR(result);

                result = Faction::Strategy(_Faction).Update(_Objectives, node);
                CHECK_ERROR(result);

                bool buildCompleted = false;
                result = node->state.HasCompletedBuild(_Objectives, buildCompleted);
                CHECK_ERROR(result);

                if (buildCompleted)
                {
                    // Compare with the current solution
                    // The best branch should reach the build order objective in the smallest time possible.
                    // A solved branch with a longer time than the current best solution should be pruned.
                    if (_Solution == nullptr || node->state.GetTime() < _Solution->state.GetTime())
                    {
                        _Solution = node;
                    }
                    else
                    {
                        // Move up the branch to remove previous nodes that didn't reach the objectives
                        while (node->parent->children.size() == 1)
                        {
                            node = node->parent;
                        }
                        _Graph.RemoveNode(node);
                    }
                }
            }
        }

        return Success;
    }

    ErrorCode Solver::PrepareBuildOrder()
    {
        // Aggregate and synthesize best solution into a readable build order
        return NotYetImplemented;
    }
}