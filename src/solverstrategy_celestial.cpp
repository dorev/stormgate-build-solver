#include "solverstrategy.h"

namespace SGBuilds
{
    ErrorCode CelestialStrategy::Update(const std::vector<BuildTarget>& buildTargets, NodePtr& node) const
    {
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToIncreaseSupply(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToTech(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToExpand(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToProduceUnit(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToProduceProducer(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToProduceWorker(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToProduceUpgrade(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        return NotYetImplemented;
    }
}
