#pragma once

#include "model.h"
#include "errorcodes.h"
#include "database.h"
#include "gamestate.h"
#include "buildordergraph.h"

#include <vector>
#include <unordered_set>

namespace SGBuilds
{
    struct BuildOrderStep
    {
        const int supply;
        const int time;
        const ObjectID buy;
    };

    class Solver
    {
    public:
        ErrorCode Solve(ObjectID* objects, unsigned objectsSize)
        {
            _TargetObjectList = std::vector<ObjectID>(objects, objects + objectsSize);

            ErrorCode result = ValidateObjectList();
            CHECK_ERROR(result);

            result = SummarizeRequirements();
            CHECK_ERROR(result);

            result = InitGraph();
            CHECK_ERROR(result);

            result = ProcessGraph();
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
        ErrorCode ValidateObjectList()
        {
            if (_TargetObjectList.empty())
            {
                return EmptyObjectList;
            }

            // Confirm that all objects belong to the same faction
            ObjectID faction = _TargetObjectList[0] & ID::FactionMask;
            for (ObjectID id : _TargetObjectList)
            {
                if ((id & ID::FactionMask) != faction)
                {
                    return MultipleFactionsInList;
                }
            }

            return Success;
        }

        ErrorCode SummarizeRequirements()
        {
            std::unordered_set<ObjectID> uniqueObjectIds;
            for (ObjectID id : uniqueObjectIds)
            {
                uniqueObjectIds.insert(id);
            }

            for (ObjectID id : uniqueObjectIds)
            {
                _Requirements |= Database::Get(id).requirements;
            }

            return Success;
        }

        ErrorCode InitGraph()
        {
            GameState rootState;
            rootState.Reset(_Faction);
            _Graph.AddNode(rootState);

            return Success;
        }

        ErrorCode ProcessGraph()
        {
            // Check what requirements are met
            // Check what requirements can be met next
            // Check if we can afford/produce a worker instead
            return NotYetImplemented;
        }

    private:
        ObjectID _Faction;
        std::vector<ObjectID> _TargetObjectList;
        ObjectID _Requirements;
        BuildOrderGraph _Graph;
    };
}
