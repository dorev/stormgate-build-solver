#pragma once

#include "model.h"
#include "errorcodes.h"
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
        ErrorCode Update(const std::vector<Target>& targets, NodePtr& node) override;

        ErrorCode GetTargetsForDecision(const DecisionID& decision, GameState& state, std::vector<ObjectID>& targetObjects);
    };
}
