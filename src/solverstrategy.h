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
        virtual ErrorCode Update(const std::vector<Target>& targets, NodePtr& node) = 0;
    };

    using SolverStrategyPtr = std::shared_ptr<SolverStrategy>;

    class VanguardStrategy : public SolverStrategy
    {
    public:
        ErrorCode Update(const std::vector<Target>& targets, NodePtr& node) override
        {
            if (!node->children.empty())
            {
                return MustNotUpdateNodeWithChildren;
            }

            GameState& state = node->state;

            // List requirements left
            // Filter out inaccessible objects (because of lacking prereqs)
            // Start a branch for each possible choice
            // Consider the possibility of constructing multiple production buildings

            return NotYetImplemented;
        }
    };
}
