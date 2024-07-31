#pragma once

#include "common.h"

#include <vector>

namespace SGBuilds
{
    class GameState
    {
    public:
        GameState(ObjectID factionId)
        {
        }

        void Update(int timeIncrement = 1)
        {
            // update buildings
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
        int time;
        float luminite;
        float therium;
        std::vector<Unit> units;
        std::vector<Unit> workers;
        std::vector<Building> buildings;
        std::vector<Upgrade> upgrades;
        std::vector<Object> pendingCompletion;
        int workersOnLuminite;
        int workersOnTherium;
        int workersBuilding;
    };

    // I will probably need something for faction behaviours for building
}
