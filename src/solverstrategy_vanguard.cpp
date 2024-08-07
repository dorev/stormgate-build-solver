#include "solverstrategy.h"

namespace SGBuilds
{
    // NOTE: We'll see later, but this Update method looks quite faction agnostic!

    ErrorCode VanguardStrategy::Update(const std::vector<Objective>& objective, NodePtr& node) const
    {
        ErrorCode result;

        if (!node->children.empty())
        {
            return MustNotUpdateNodeWithChildren;
        }

        GameState& state = node->state;

        // Progress on current objective
        const ObjectID& objectId = state.GetObjectiveObject();
        bool nodeObjectiveReached = false;

        if (objectId != ID::NoObject)
        {
            bool canAfford, techAllows, canProduce;
            result = state.CheckProductionCapability(objectId, techAllows, canAfford, canProduce);
            CHECK_ERROR(result);

            if (!techAllows)
            {
                return InvalidDecision;
            }

            if (canAfford && canProduce)
            {
                result = state.Buy(objectId);
                CHECK_ERROR(result);

                nodeObjectiveReached = true;
            }
        }

        // When objective is reached, prepare next generation of nodes
        if (nodeObjectiveReached)
        {
            // For all possible decisions, evaluate all possible objectives
            std::vector<ObjectID> nextNodeObjectives;
            for (int decision = 0; decision < Decision::MaxDecision; ++decision)
            {
                // NOTE: This is likely the only call that has faction-specific logic
                GetObjectivesForDecision(decision, state, objective, nextNodeObjectives);
            }

            // Add a child node for each possible objective
            Graph& graph = node->graph;
            for (const ObjectID& objectiveObject : nextNodeObjectives)
            {
                NodePtr newChildNode = graph.AddNode(state);
                newChildNode->state.SetObjectiveObject(objectiveObject);
                graph.AddEdge(node, newChildNode);
            }
        }

        return Success;
    }

    ErrorCode VanguardStrategy::GetObjectivesToIncreaseSupply(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        // Build Habitat
        // Upgrade Habitat to SolarHabitat
        // Upgrade Habitat to Rampart
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToTech(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToExpand(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToProduceUnit(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        // Check what units we need for the build
        // Check if tech allows unit
        // Check if supply allows unit
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToProduceProducer(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        // Check what units we need for the build
        // Check what producer buildings we need for this
        // Check if tech allows unit
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToProduceWorker(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        // A worker for luminite
        // A worker for therium
        // Set their status appropriately in the pending object
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToProduceUpgrade(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        for (const Objective& buildObjective : objective)
        {
            ObjectID id = buildObjective.id;
            if (IsUpgrade(id) && !ContainsID(state.GetUpgrades(), id))
            {
                bool techAllows;
                ErrorCode result = state.TechAllows(id, techAllows);
                CHECK_ERROR(result);

                if (techAllows)
                {
                    objects.push_back(id);
                }
            }
        }

        return Success;
    }
}
