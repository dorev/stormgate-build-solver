#include "faction.h"
#include "solverstrategy.h"
#include "database.h"

namespace SGBuilds
{
    /*
    ErrorCode Infernal::ResetGameState(GameState& state) const
    {
        state._Buildings.clear();
        state._Units.clear();
        state._Upgrades.clear();
        state._PendingObjects.clear();

        return NotYetImplemented;
    }

    const SolverStrategy& Infernal::GetSolverStrategy() const
    {
        static const InfernalStrategy strategy;
        return strategy;
    }

    int Infernal::GetPopulationCap(const GameState& state) const
    {
        int supply = 0;
        for (const Building& building : state.GetBuildings())
        {
            supply += building.supply;
        }
        return supply;
    }

    bool Infernal::LuminiteSaturated(const GameState& state) const
    {
        int baseCount = 0;
        for (const Building& building : state.GetBuildings())
        {
            if (building == ID::CommandPost || building == ID::CentralCommand || building == ID::HighCommand)
            {
                baseCount++;
            }
        }

        int workersCollectingLuminite = 0;
        for (const Unit& unit : state.GetUnits())
        {
            if (unit == ID::Bob && unit.status == Task::CollectingLuminite)
            {
                workersCollectingLuminite++;
            }
        }

        if (workersCollectingLuminite <= 0)
        {
            return false;
        }

        return workersCollectingLuminite >= (baseCount * 12);
    }
    */
}
