#include "solverstrategy.h"

namespace SGBuilds
{
    ErrorCode VanguardStrategy::Update(const std::vector<Target>& targets, NodePtr& node)
    {
        ErrorCode result;

        if (!node->children.empty())
        {
            return MustNotUpdateNodeWithChildren;
        }

        GameState& state = node->state;

        // Progress on current target
        const ObjectID& target = state.GetTargetObject();
        bool nodeTargetReached = false;

        if (target)
        {
            bool canAfford, canProduce;
            result = state.CanAffordAndProduce(target, canAfford, canProduce);
            CHECK_ERROR(result);

            if (!canProduce)
            {
                return InvalidDecision;
            }

            if (canAfford)
            {
                result = state.Buy(target);
                nodeTargetReached = true;
                CHECK_ERROR(result);
            }
        }

        // When target is reached, prepare next generation of nodes
        if (nodeTargetReached)
        {
            std::vector<ObjectID> nextGenerationTargets;

            // For all possible decisions, validate all possible targets considering tech
            for (int decision = 0; decision < Decision::MaxDecision; ++decision)
            {
                GetTargetsForDecision(decision, state, nextGenerationTargets);
                // CATCH UP HERE!!
            }

        }




        // Check if current intention is done
        // If it is



        // Validate the intention of the current node
        // See if we can take a macro, tech, or producing decision and branch form the tree if possible
        // Don't forget to consider the idea of increasing supply! ... or should increasing supply be part of macroing?

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

        // NOTE
        // This above appears to be quite faction-agnostic

        // From this point we should either follow these objectives or macro


        // Create macro node if possible
        bool canAfford, canProduce;
        result = state.CanAffordAndProduce(ID::Bob, canAfford, canProduce);
        CHECK_ERROR(result);

        // How to avoid creating macro nodes at each update? We have to check if we already went down that path




        // Is this node already pursuing a target?
        // Can it afford this target?


        // Start a branch for each possible choice


        // Consider the possibility of constructing multiple production buildings
        // Let's do something super naive first!

        return NotYetImplemented;
    }


    ErrorCode VanguardStrategy::GetTargetsForDecision(const DecisionID& decision, GameState& state, std::vector<ObjectID>& targetObjects)
    {
        return NotYetImplemented;
    }
}
