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
            ErrorCode result;

            if (!node->children.empty())
            {
                return MustNotUpdateNodeWithChildren;
            }

            GameState& state = node->state;

            // List targets yet to be completed
            std::vector<Target> remainingTargets;
            for (const Target& target : targets)
            {
                bool hasReachedTarget;
                result = state.HasReachedTarget(target, hasReachedTarget);
                CHECK_ERROR(result);

                if (!hasReachedTarget)
                {
                    remainingTargets.push_back(target);
                }
            }

            // Filter out inaccessible objects (because of lacking prereqs)
            std::vector<Target> accessibleTargets;
            for (const Target& target : remainingTargets)
            {
                bool canProduce;
                result = state.IsAllowedByTech(target.id, canProduce);

                if (canProduce)
                {
                    accessibleTargets.push_back(target);
                }
            }

            // This above appears to be quite faction-agnostic

            // From this point we should either follow these objectives or macro

            // Create macro node if possible
            bool canAfford;
            result = state.CanAffordAndProduce(ID::Bob, canAfford);
            CHECK_ERROR(result);

            bool canProduce;
            result = state.IsAllowedByTech(ID::Bob, canProduce);
            CHECK_ERROR(result);



            // How to avoid creating macro nodes at each update? We have to check if we already went down that path




            // Is this node already pursuing a target?
            // Can it afford this target?


            // Start a branch for each possible choice


            // Consider the possibility of constructing multiple production buildings
            // Let's do something super naive first!

            return NotYetImplemented;
        }
    };
}
