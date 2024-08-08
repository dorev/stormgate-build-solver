#include "faction.h"
#include "solverstrategy.h"
#include "database.h"

namespace SGBuilds
{
    ErrorCode Vanguard::ResetGameState(GameState& state) const
    {
        ObjectPtr object = nullptr;
        ErrorCode result = state.Give(ID::CommandPost, object);
        CHECK_ERROR(result);

        for (int i = 0; i < 10; ++i)
        {
            result = state.Give(ID::Bob, object);
            CHECK_ERROR(result);

            object->task = Task::CollectingLuminite;
        }

        result = state.Give(ID::Scout, object);
        CHECK_ERROR(result);

        state._Luminite = 100; // TODO: Validate this
        state._Therium = 0;
        state._Time = 0;
        state._ObjectiveObject = nullptr;
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
        for (const BuildingPtr& building : state.GetBuildings())
        {
            supply += building->supply;
        }
        return supply;
    }

    bool Vanguard::LuminiteSaturated(const GameState& state) const
    {
        int baseCount = 0;
        for (const BuildingPtr& building : state.GetBuildings())
        {
            if (building->id == ID::CommandPost || building->id == ID::CentralCommand || building->id == ID::HighCommand)
            {
                baseCount++;
            }
        }

        int workersCollectingLuminite = 0;
        for (const UnitPtr& unit : state.GetUnits())
        {
            if (unit->id == ID::Bob && unit->task == Task::CollectingLuminite)
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

    bool Vanguard::HasBuilderAvailable(const GameState& state) const
    {
        for (const UnitPtr& unit : state.GetUnits())
        {
            if (unit->id == ID::Bob && unit->task != Task::CompletingBuilding)
            {
                return true;
            }
        }

        return false;
    }

    ErrorCode Vanguard::StartProduction(GameState& state, ObjectPtr& object) const
    {
        object = nullptr;

        switch (GetObjectType(object->id))
        {
        case ID::Building:
            for (UnitPtr& unit : state._Units)
            {
                if (unit->id == ID::Bob && unit->task != Task::CompletingBuilding)
                {
                    state._PendingObjects.emplace_back(object);
                    unit->task = Task::CompletingBuilding;
                    unit->target = object->GetUID();
                    return Success;
                }
            }
            return NoBuilderAvailable;

        // CATCH UP HERE
        case ID::Unit:
        case ID::Upgrade:
        default:
            break;
        }

        return NotYetImplemented;
    }

    ErrorCode Vanguard::FinishProduction(GameState& state, ObjectPtr pendingObject) const
    {
        for (UnitPtr& unit : state._Units)
        {
            if (unit->id == ID::Bob && unit->task == Task::CompletingBuilding && unit->target == pendingObject->GetUID())
            {
                unit->task = LuminiteSaturated(state) ? Task::CollectingTherium : Task::CollectingLuminite;
                unit->target = ID::NoObject;
            }
        }

        return Success;
    }
}
