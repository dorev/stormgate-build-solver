#include "faction.h"
#include "solverstrategy.h"
#include "database.h"

namespace SGBuilds
{
    ErrorCode Vanguard::ResetGameState(GameState& state) const
    {
        state._Buildings.clear();
        state._Units.clear();
        state._Upgrades.clear();
        state._PendingObjects.clear();

        GET_PROTOTYPE(commandPost, ID::CommandPost);
        state._Buildings.push_back(static_cast<const Building&>(commandPost));

        GET_PROTOTYPE(protoBob, ID::Bob);
        Unit bob = static_cast<const Unit&>(protoBob);
        bob.task = Task::CollectingLuminite;
        for (int i = 0; i < 10; ++i)
        {
            state._Units.push_back(static_cast<const Unit&>(bob));
        }

        GET_PROTOTYPE(scout, ID::Scout);
        state._Units.push_back(static_cast<const Unit&>(scout));

        state._Luminite = 100; // TODO: Validate this
        state._Therium = 0;
        state._Time = 0;
        state._ObjectiveObject = Objective();
        state._BuildCompleted = false;

        return Success;
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

    bool Vanguard::LuminiteSaturated(const GameState& state) const
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
            if (unit == ID::Bob && unit.task == Task::CollectingLuminite)
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

    ErrorCode Vanguard::StartBuildingProduction(GameState& state) const
    {
        if (!HasBuilderAvailable(state))
        {
            return NotEnoughResources;
        }

        for (Unit& unit : state._Units)
        {
            if (unit == ID::Bob && unit.task != Task::CompletingBuilding)
            {
                unit.task = Task::CompletingBuilding;
                break;
            }
        }

        return Success;
    }

    ErrorCode Vanguard::FinishBuildingProduction(GameState& state) const
    {
        for (Unit& unit : state._Units)
        {
            if (unit == ID::Bob && unit.task == Task::CompletingBuilding)
            {
                unit.task = LuminiteSaturated(state) ? Task::CollectingTherium : Task::CollectingLuminite;
                return Success;
            }
        }

        return NotEnoughResources;
    }

    bool Vanguard::HasBuilderAvailable(const GameState& state) const
    {
        for (const Unit& unit : state.GetUnits())
        {
            if (unit.id == ID::Bob && unit.task != Task::CompletingBuilding)
            {
                return true;
            }
        }

        return false;
    }
}
