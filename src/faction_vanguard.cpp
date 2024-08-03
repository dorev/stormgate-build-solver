#include "faction.h"
#include "solverstrategy.h"

namespace SGBuilds
{
    void Vanguard::ResetGameState(GameState& state) const
    {
        // NotYetImplemented
    }

    const SolverStrategy& Vanguard::GetSolverStrategy() const
    {
        static const VanguardStrategy strategy;
        return strategy;
    }

    int Vanguard::GetPopulationCap(const GameState& state) const
    {
        int supply = 0;

        for (const Building& building : state.GetBuildings())
        {
            supply += building.supply;
        }

        return supply;
    }

    int Vanguard::LuminiteSaturated(const GameState& state) const
    {
    }
}
