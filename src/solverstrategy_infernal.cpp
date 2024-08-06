#include "solverstrategy.h"

namespace SGBuilds
{
    ErrorCode InfernalStrategy::Update(const std::vector<BuildTarget>& buildTargets, NodePtr& node) const
    {
        (void) buildTargets;
        (void) node;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetTargetsToIncreaseSupply(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetTargetsToTech(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetTargetsToExpand(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetTargetsToProduceUnit(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetTargetsToProduceProducer(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetTargetsToProduceWorker(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetTargetsToProduceUpgrade(const GameState& state, const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& targetObjects) const
    {
        (void) state;
        (void) buildTargets;
        (void) targetObjects;
        return NotYetImplemented;
    }
}
