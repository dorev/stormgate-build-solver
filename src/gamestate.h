#pragma once

#include "model.h"

#include <vector>

namespace SGBuilds
{
    class GameState
    {
    private:
        static constexpr float TimeIncrementPerUpdate = 1.0f;

    public:
        ErrorCode Reset(ObjectID faction)
        {
            return NotYetImplemented;
        }

        ErrorCode Update()
        {
            ErrorCode result = Success;

            result = UpdateResources();
            CHECK_ERROR(result);

            result = UpdatePendingObjects();
            CHECK_ERROR(result);

            return result;
        }

        int GetCurrentSupplyCap() const
        {
        }

        int WillExceedSupplyCap(ObjectID unit) const
        {
        }

        bool CanAfford(ObjectID object) const
        {
        }

        int Buy(ObjectID object)
        {
        }

        int LuminiteIsSaturated() const
        {
        }

    private:
        ErrorCode UpdateResources()
        {
            return NotYetImplemented;
        }

        ErrorCode UpdatePendingObjects()
        {
            return NotYetImplemented;
        }

    private:
        int time;
        float luminite;
        float therium;
        std::vector<Unit> units;
        std::vector<Unit> workers;
        std::vector<Building> buildings;
        std::vector<Upgrade> upgrades;
        std::vector<Object> pendingObjects;
        int workersOnLuminite;
        int workersOnTherium;
        int workersBuilding;
    };
}
