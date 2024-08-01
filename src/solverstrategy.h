#pragma once

#include "model.h"
#include "errorcodes.h"
#include "database.h"
#include "gamestate.h"
#include "graph.h"

#include <vector>

namespace SGBuilds
{

    class SolverStrategy
    {
    public:
        virtual ErrorCode PlanNextStep(const std::vector<Target>& targets, NodePtr& node) = 0;
        // Check what requirements can be met next
        // Check if we can afford/produce a worker instead 
        // Create as many branches as we have options

    };

    using SolverStrategyPtr = std::shared_ptr<SolverStrategy>;

    class VanguardStrategy : public SolverStrategy
    {
    public:
        ErrorCode PlanNextStep(const std::vector<Target>& targets, NodePtr& node) override
        {
            return NotYetImplemented;
        }
    };
}
