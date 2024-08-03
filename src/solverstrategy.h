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
        virtual ErrorCode Update(const std::vector<BuildTarget>& targets, NodePtr& node) const = 0;

        virtual ErrorCode GetTargetsToIncreaseSupply(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const = 0;
        virtual ErrorCode GetTargetsToTech(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const = 0;
        virtual ErrorCode GetTargetsToExpand(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const = 0;
        virtual ErrorCode GetTargetsToProduceUnit(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const = 0;
        virtual ErrorCode GetTargetsToProduceProducer(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const = 0;
        virtual ErrorCode GetTargetsToProduceWorker(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const = 0;
        virtual ErrorCode GetTargetsToProduceUpgrade(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const = 0;

        ErrorCode GetTargetsForDecision(const DecisionID& decision, const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
        {
            switch (decision)
            {
            default:
                return InvalidDecision;

            case Decision::IncreaseSupply: return GetTargetsToIncreaseSupply(state, buildTargets, targetObjects);
            case Decision::Tech: return GetTargetsToTech(state, buildTargets, targetObjects);
            case Decision::Expand: return GetTargetsToExpand(state, buildTargets, targetObjects);
            case Decision::ProduceUnit: return GetTargetsToProduceUnit(state, buildTargets, targetObjects);
            case Decision::ProduceProducer: return GetTargetsToProduceProducer(state, buildTargets, targetObjects);
            case Decision::ProduceWorker: return GetTargetsToProduceWorker(state, buildTargets, targetObjects);
            case Decision::ProduceUpgrade: return GetTargetsToProduceUpgrade(state, buildTargets, targetObjects);
            }
        }
    };

    class VanguardStrategy : public SolverStrategy
    {
    public:
        ErrorCode Update(const std::vector<BuildTarget>& targets, NodePtr& node) const override;
        ErrorCode GetTargetsToIncreaseSupply(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToTech(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToExpand(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceUnit(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceProducer(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceWorker(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceUpgrade(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
    };

    class InfernalStrategy : public SolverStrategy
    {
    public:
        ErrorCode Update(const std::vector<BuildTarget>& targets, NodePtr& node) const override;
        ErrorCode GetTargetsToIncreaseSupply(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToTech(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToExpand(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceUnit(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceProducer(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceWorker(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceUpgrade(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
    };

    class CelestialStrategy : public SolverStrategy
    {
    public:
        ErrorCode Update(const std::vector<BuildTarget>& targets, NodePtr& node) const override;
        ErrorCode GetTargetsToIncreaseSupply(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToTech(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToExpand(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceUnit(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceProducer(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceWorker(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
        ErrorCode GetTargetsToProduceUpgrade(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const override;
    };
}
