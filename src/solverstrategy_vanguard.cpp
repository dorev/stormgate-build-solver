#include "solverstrategy.h"

namespace SGBuilds
{
    // NOTE: We'll see later, but this Update method looks quite faction agnostic!

    ErrorCode VanguardStrategy::Update(const std::vector<BuildTarget>& buildTargets, NodePtr& node) const
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
            bool canAfford, techAllows, canProduce;
            result = state.CheckProductionCapability(target, techAllows, canAfford, canProduce);
            CHECK_ERROR(result);

            if (!techAllows)
            {
                return InvalidDecision;
            }

            if (canAfford && canProduce)
            {
                result = state.Buy(target);
                CHECK_ERROR(result);

                nodeTargetReached = true;
            }
        }

        // When target is reached, prepare next generation of nodes
        if (nodeTargetReached)
        {
            // For all possible decisions, evaluate all possible targets
            std::vector<ObjectID> nextNodeTargets;
            for (int decision = 0; decision < Decision::MaxDecision; ++decision)
            {
                // NOTE: This is likely the only call that has faction-specific logic
                GetTargetsForDecision(decision, state, buildTargets, nextNodeTargets);
            }

            // Add a child node for each possible target
            Graph& graph = node->graph;
            for (const ObjectID& targetObject : nextNodeTargets)
            {
                NodePtr newChildNode = graph.AddNode(state);
                newChildNode->state.SetTargetObject(targetObject);
                graph.AddEdge(node, newChildNode);
            }
        }

        return Success;
    }

    ErrorCode VanguardStrategy::GetTargetsToIncreaseSupply(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        // Build Habitat
        // Upgrade Habitat to SolarHabitat
        // Upgrade Habitat to Rampart
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetTargetsToTech(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetTargetsToExpand(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetTargetsToProduceUnit(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        // Check what units we need for the build
        // Check if tech allows unit
        // Check if supply allows unit
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetTargetsToProduceProducer(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        // Check what units we need for the build
        // Check what producer buildings we need for this
        // Check if tech allows unit
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetTargetsToProduceWorker(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        // A worker for luminite
        // A worker for therium
        // Set their status appropriately in the pending object
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetTargetsToProduceUpgrade(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        for (const BuildTarget& buildTarget : buildTargets)
        {
            ObjectID id = buildTarget.id;
            if (IsUpgrade(id) && !ContainsID(state.GetUpgrades(), id))
            {
                bool techAllows;
                ErrorCode result = state.TechAllows(id, techAllows);
                CHECK_ERROR(result);

                if (techAllows)
                {
                    targetObjects.push_back(id);
                }
            }
        }

        return Success;
    }
}
