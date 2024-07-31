#pragma once

#include "common.h"
#include "database.h"
#include "gamestate.h"

namespace SGBuilds
{
    using ErrorCode = int;
    constexpr ErrorCode Success = 0;
    constexpr ErrorCode NotYetImplemented = -1;

    class Solver
    {
    public:
        ErrorCode Solve(ObjectID* objects, unsigned objectsSize)
        {
            return NotYetImplemented;
        }

        unsigned GetBuildOrderSize()
        {
            return 0;
        }

        ErrorCode ReadAndClearBuildOrder(BuildOrderStep*& buildOrderSteps)
        {
            return NotYetImplemented;
        }
    };
}
