#pragma once

#include "common.h"

namespace SGBuilds
{
    struct PlayerAssets
    {
        int luminite;
        int theurium;
        std::vector<Building> buildings;
        std::vector<SupplyBuilding> supplyBuilding;
        std::vector<Unit> units;
        std::vector<Worker> workers;
        std::vector<Upgrade> upgrades;
    };

    class GameState
    {
    public:
        int GetCurrentSupplyCap() const
        {

        }

        int CanAfford(ObjectID object)
        {

        }

    private:
        PlayerAssets assets;
    };
}
