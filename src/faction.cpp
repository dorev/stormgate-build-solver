#include "faction.h"
#include "gamestate.h"
#include "solverstrategy.h"

namespace SGBuilds
{
    Faction::~Faction()
    {
    }

    const Faction& Faction::Get(const ObjectID& id)
    {
        static const Vanguard vanguardFaction;
        static const Infernal infernalFaction;
        static const Celestial celestialFaction;

        switch (id & ID::FactionMask)
        {
        default:
            // Add log/error/assert

        case ID::Vanguard:
            return vanguardFaction;

        case ID::Infernal:
            return infernalFaction;

        case ID::Celestial:
            return celestialFaction;
        }
    }

    const SolverStrategy& Faction::Strategy(const ObjectID& id)
    {
        return Faction::Get(id).GetSolverStrategy();
    }

    // Dummy implementations for virtual methods
    // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

    ErrorCode Faction::ResetGameState(GameState& state) const
    {
        (void) state;
        return NotYetImplemented;
    }

    const SolverStrategy& Faction::GetSolverStrategy() const
    {
        static const VanguardStrategy strategy;
        return strategy;
    }

    int Faction::GetPopulationCap(const GameState& state) const
    {
        (void) state;
        return -1;
    }

    bool Faction::LuminiteSaturated(const GameState& state) const
    {
        (void) state;
        return false;
    }

    bool Faction::HasBuilderAvailable(const GameState& state) const
    {
        (void) state;
        return false;
    }

    ErrorCode Faction::StartProduction(GameState& state, const ObjectID& buildingId, ObjectPtr& object) const
    {
        (void) state;
        (void) buildingId;
        (void) object;
        return NotYetImplemented;
    }

    ErrorCode Faction::FinishProduction(GameState& state, ObjectPtr pendingObject) const
    {
        (void) state;
        return NotYetImplemented;
    }
}
