#include "solverstrategy.h"

namespace SGBuilds
{
    ErrorCode InfernalStrategy::Update(const std::vector<Objective>& objective, NodePtr& node) const
    {
        (void) objective;
        (void) node;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetObjectivesToIncreaseSupply(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetObjectivesToTech(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetObjectivesToExpand(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetObjectivesToProduceUnit(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetObjectivesToProduceProducer(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetObjectivesToProduceWorker(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }

    ErrorCode InfernalStrategy::GetObjectivesToProduceUpgrade(const GameState& state, const std::vector<Objective>& objective, std::vector<ObjectID>& objects) const
    {
        (void) state;
        (void) objective;
        (void) objects;
        return NotYetImplemented;
    }
}
