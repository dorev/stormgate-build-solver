#include "faction.h"

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
}
