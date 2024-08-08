#include "solverstrategy.h"

namespace SGBuilds
{
    // NOTE: We'll see later, but this Update method looks quite faction agnostic!

    ErrorCode VanguardStrategy::Update(const std::vector<Objective>& objectives, NodePtr& node) const
    {
        ErrorCode result;

        if (!node->children.empty())
        {
            return MustNotUpdateNodeWithChildren;
        }

        GameState& state = node->state;

        // Progress on current objective
        ObjectPtr& object = state.GetObjectiveObject();
        bool nodeObjectiveReached = false;

        if (object != nullptr)
        {
            bool canAfford, techAllows, canProduce;
            result = state.CheckProductionCapability(object->id, techAllows, canAfford, canProduce);
            CHECK_ERROR(result);

            if (!techAllows)
            {
                return InvalidDecision;
            }

            if (canAfford && canProduce)
            {
                result = state.Buy(object);
                CHECK_ERROR(result);

                nodeObjectiveReached = true;
            }
        }

        // When objective is reached, prepare next generation of nodes
        if (nodeObjectiveReached)
        {
            // For all possible decisions, evaluate all possible objectives
            std::vector<ObjectPtr> nextNodeObjectives;
            for (int decision = 0; decision < Decision::MaxDecision; ++decision)
            {
                // NOTE: This is likely the only call that has faction-specific logic
                GetObjectivesForDecision(decision, state, objectives, nextNodeObjectives);
            }

            // Add a child node for each possible objective
            Graph& graph = node->graph;
            for (const ObjectPtr& objectiveObject : nextNodeObjectives)
            {
                NodePtr newChildNode = graph.AddNode(state);
                newChildNode->state.SetObjectiveObject(objectiveObject);
                graph.AddEdge(node, newChildNode);
            }
        }

        return Success;
    }

    ErrorCode VanguardStrategy::GetObjectivesToIncreaseSupply(const GameState& state, const std::vector<Objective>& objectives, std::vector<ObjectPtr>& objects) const
    {
        // Build Habitat
        // Upgrade Habitat to SolarHabitat
        // Upgrade Habitat to Rampart
        (void) state;
        (void) objectives;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToTech(const GameState& state, const std::vector<Objective>& objectives, std::vector<ObjectPtr>& objects) const
    {
        (void) state;
        (void) objectives;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToExpand(const GameState& state, const std::vector<Objective>& objectives, std::vector<ObjectPtr>& objects) const
    {
        (void) state;
        (void) objectives;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToProduceUnit(const GameState& state, const std::vector<Objective>& objectives, std::vector<ObjectPtr>& objects) const
    {
        // Check what units we need for the build
        // Check if tech allows unit
        // Check if supply allows unit
        (void) state;
        (void) objectives;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToProduceProducer(const GameState& state, const std::vector<Objective>& objectives, std::vector<ObjectPtr>& objects) const
    {
        // Check what units we need for the build
        // Check what producer buildings we need for this
        // Check if tech allows unit
        (void) state;
        (void) objectives;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode VanguardStrategy::GetObjectivesToProduceWorker(const GameState& state, const std::vector<Objective>& objectives, std::vector<ObjectPtr>& objects) const
    {
        (void) state;
        (void) objectives;

        UnitPtr luminiteBob = std::make_shared<Unit>(ID::Bob);
        luminiteBob->task = Task::CollectingLuminite;
        objects.emplace_back(luminiteBob);

        UnitPtr theriumBob = std::make_shared<Unit>(ID::Bob);
        theriumBob->task = Task::CollectingTherium;
        objects.emplace_back(theriumBob);

        return Success;
    }

    ErrorCode VanguardStrategy::GetObjectivesToProduceUpgrade(const GameState& state, const std::vector<Objective>& objectives, std::vector<ObjectPtr>& objects) const
    {
        for (const Objective& buildObjective : objectives)
        {
            ObjectID upgradeId = buildObjective.id;
            if (IsUpgrade(upgradeId) && !ContainsID(state.GetUpgrades(), upgradeId))
            {
                bool techAllows;
                ErrorCode result = state.TechAllows(upgradeId, techAllows);
                CHECK_ERROR(result);

                if (techAllows)
                {
                    objects.emplace_back(std::make_shared<Upgrade>(upgradeId));
                }
            }
        }

        return Success;
    }
}
