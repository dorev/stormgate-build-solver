#include "solverstrategy.h"

namespace SGBuilds
{
    ErrorCode CelestialStrategy::Update(const std::vector<BuildTarget>& buildTargets, NodePtr& node) const
    {
        (void) buildTargets;
        (void) node;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToIncreaseSupply(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToTech(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToExpand(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToProduceUnit(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToProduceProducer(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToProduceWorker(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetTargetsToProduceUpgrade(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }
}
