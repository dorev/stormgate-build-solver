#include "solverstrategy.h"

namespace SGBuilds
{
    ErrorCode CelestialStrategy::Update(const std::vector<Objective>& objective, NodePtr& node) const
    {
        (void) objective;
        (void) node;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetObjectivesToIncreaseSupply(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetObjectivesToTech(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetObjectivesToExpand(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetObjectivesToProduceUnit(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetObjectivesToProduceProducer(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetObjectivesToProduceWorker(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode CelestialStrategy::GetObjectivesToProduceUpgrade(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }
}
