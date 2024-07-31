#pragma once

#include "common.h"
#include "database.h"
#include "gamestate.h"

namespace SGBuilds
{
    using ErrorCode = int;
    constexpr ErrorCode Success = 0;
    constexpr ErrorCode InvalidObjectList = 0;
    constexpr ErrorCode NotYetImplemented = -99;

    #define CHECK_ERROR(error) if ((error) != Success) { return error; }

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

            ErrorCode result = ValidateObjectList(_Faction);
            CHECK_ERROR(result);

            result = SummarizeRequirements();
            CHECK_ERROR(result);

            result = InitGameGraph();
            CHECK_ERROR(result);




            return Success;
        }

        unsigned GetBuildOrderSize()
        {
            return 0;
        }

        ErrorCode ReadAndClearBuildOrder(BuildOrderStep*& buildOrderSteps)
        {
            return NotYetImplemented;
        }

    private:
        ErrorCode ValidateObjectList(ObjectID& faction);
        ErrorCode SummarizeRequirements();
        ErrorCode InitGameGraph();


    private:
        ObjectID _Faction;
        std::vector<ObjectID> _TargetObjectList;
        std::vector<ObjectID> _Requirements;
    };
}
