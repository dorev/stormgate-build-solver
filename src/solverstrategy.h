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
        virtual ErrorCode Update(const std::vector<Objective>& objectives, NodePtr& node) const = 0;

        virtual ErrorCode GetObjectivesToIncreaseSupply(const GameState&, const std::vector<Objective>&, std::vector<ObjectID>&) const { return NotYetImplemented; }
        virtual ErrorCode GetObjectivesToTech(const GameState&, const std::vector<Objective>&, std::vector<ObjectID>&) const { return NotYetImplemented; }
        virtual ErrorCode GetObjectivesToExpand(const GameState&, const std::vector<Objective>&, std::vector<ObjectID>&) const { return NotYetImplemented; }
        virtual ErrorCode GetObjectivesToProduceUnit(const GameState&, const std::vector<Objective>&, std::vector<ObjectID>&) const { return NotYetImplemented; }
        virtual ErrorCode GetObjectivesToProduceProducer(const GameState&, const std::vector<Objective>&, std::vector<ObjectID>&) const { return NotYetImplemented; }
        virtual ErrorCode GetObjectivesToProduceWorker(const GameState&, const std::vector<Objective>&, std::vector<ObjectID>&) const { return NotYetImplemented; }
        virtual ErrorCode GetObjectivesToProduceUpgrade(const GameState&, const std::vector<Objective>&, std::vector<ObjectID>&) const { return NotYetImplemented; }

        ErrorCode GetObjectivesForDecision(const DecisionID& decision, const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
        {
            switch (decision)
            {
            default:
                return InvalidDecision;

            case Decision::IncreaseSupply: return GetObjectivesToIncreaseSupply(state, objective, objects);
            case Decision::Tech: return GetObjectivesToTech(state, objective, objects);
            case Decision::Expand: return GetObjectivesToExpand(state, objective, objects);
            case Decision::ProduceUnit: return GetObjectivesToProduceUnit(state, objective, objects);
            case Decision::ProduceProducer: return GetObjectivesToProduceProducer(state, objective, objects);
            case Decision::ProduceWorker: return GetObjectivesToProduceWorker(state, objective, objects);
            case Decision::ProduceUpgrade: return GetObjectivesToProduceUpgrade(state, objective, objects);
            }
        }
    };

    class VanguardStrategy : public SolverStrategy
    {
    public:
        ErrorCode Update(const std::vector<Objective>& objectives, NodePtr& node) const override;
        ErrorCode GetObjectivesToIncreaseSupply(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
        ErrorCode GetObjectivesToTech(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
        ErrorCode GetObjectivesToExpand(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
        ErrorCode GetObjectivesToProduceUnit(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
        ErrorCode GetObjectivesToProduceProducer(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
        ErrorCode GetObjectivesToProduceWorker(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
        ErrorCode GetObjectivesToProduceUpgrade(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    };

    // class InfernalStrategy : public SolverStrategy
    // {
    // public:
    //     ErrorCode Update(const std::vector<Objective>& objectives, NodePtr& node) const override;
    //     ErrorCode GetObjectivesToIncreaseSupply(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToTech(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToExpand(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToProduceUnit(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToProduceProducer(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToProduceWorker(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToProduceUpgrade(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    // };

    // class CelestialStrategy : public SolverStrategy
    // {
    // public:
    //     ErrorCode Update(const std::vector<Objective>& objectives, NodePtr& node) const override;
    //     ErrorCode GetObjectivesToIncreaseSupply(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToTech(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToExpand(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToProduceUnit(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToProduceProducer(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToProduceWorker(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    //     ErrorCode GetObjectivesToProduceUpgrade(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const override;
    // };
}
