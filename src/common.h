#pragma once

#include <string>
#include <vector>

namespace SGBuilds
{
    using ObjectID = uint32_t;

    namespace ID
    {
        constexpr ObjectID Vanguard                      = 0x01000000;
        constexpr ObjectID Infernal                      = 0x02000000;
        constexpr ObjectID Celestial                     = 0x04000000;

        constexpr ObjectID Building                      = 0x00010000;
        constexpr ObjectID Unit                          = 0x00020000;
        constexpr ObjectID Upgrade                       = 0x00040000;
        constexpr ObjectID Spell                         = 0x00080000;

        constexpr ObjectID CommandPost                   = Vanguard | Building | 0x0001;
        constexpr ObjectID CentralCommand                = Vanguard | Building | 0x0002;
        constexpr ObjectID HighCommand                   = Vanguard | Building | 0x0004;
        constexpr ObjectID Barracks                      = Vanguard | Building | 0x0008;
        constexpr ObjectID Habitat                       = Vanguard | Building | 0x0010;
        constexpr ObjectID SolarHabitat                  = Vanguard | Building | 0x0020;
        constexpr ObjectID Rampart                       = Vanguard | Building | 0x0040;
        constexpr ObjectID MechBay                       = Vanguard | Building | 0x0080;
        constexpr ObjectID BiokineticsLab                = Vanguard | Building | 0x0100;
        constexpr ObjectID SentryPost                    = Vanguard | Building | 0x0200;
        constexpr ObjectID HangarBay                     = Vanguard | Building | 0x0400;
        constexpr ObjectID MachineLab                    = Vanguard | Building | 0x0800;
        constexpr ObjectID Scrapyard                     = Vanguard | Building | 0x1000;

        constexpr ObjectID Bob                           = Vanguard | Unit | 0x0001;
        constexpr ObjectID Lancer                        = Vanguard | Unit | 0x0002;
        constexpr ObjectID Scout                         = Vanguard | Unit | 0x0004;
        constexpr ObjectID Exo                           = Vanguard | Unit | 0x0008;
        constexpr ObjectID MedTech                       = Vanguard | Unit | 0x0010;
        constexpr ObjectID Graven                        = Vanguard | Unit | 0x0020;
        constexpr ObjectID Hedgehog                      = Vanguard | Unit | 0x0040;
        constexpr ObjectID Vulcan                        = Vanguard | Unit | 0x0080;
        constexpr ObjectID Atlas                         = Vanguard | Unit | 0x0100;
        constexpr ObjectID Hornet                        = Vanguard | Unit | 0x0200;
        constexpr ObjectID Evac                          = Vanguard | Unit | 0x0400;
        constexpr ObjectID Sentinel                      = Vanguard | Unit | 0x0800;
        constexpr ObjectID Helicarrier                   = Vanguard | Unit | 0x1000;

        constexpr ObjectID KineticRedirection            = Vanguard | Upgrade | 0x0001;
        constexpr ObjectID VoriliumClaws                 = Vanguard | Upgrade | 0x0002;
        constexpr ObjectID QuickdrawHustle               = Vanguard | Upgrade | 0x0004;
        constexpr ObjectID MedtechAdeptTraining          = Vanguard | Upgrade | 0x0008;
        constexpr ObjectID MassInfiltrate                = Vanguard | Upgrade | 0x0010;
        constexpr ObjectID OrbitalEnergyOptimizer        = Vanguard | Upgrade | 0x0020;
        constexpr ObjectID OverchargeAmplifier           = Vanguard | Upgrade | 0x0040;
        constexpr ObjectID TransonicRockets              = Vanguard | Upgrade | 0x0080;
        constexpr ObjectID ImpactThrusters               = Vanguard | Upgrade | 0x0100;
        constexpr ObjectID PlasmaArcInfusion             = Vanguard | Upgrade | 0x0200;
        constexpr ObjectID ReleaseSkymine                = Vanguard | Upgrade | 0x0400;
        constexpr ObjectID SkysprintRetrofit             = Vanguard | Upgrade | 0x0800;
        constexpr ObjectID SentinelAdeptAugmentation     = Vanguard | Upgrade | 0x1000;
        constexpr ObjectID CovertBombers                 = Vanguard | Upgrade | 0x2000;
    }

    struct Cost
    {
        int time;
        int luminite;
        int theurium;
    };

    struct Buildable
    {
        const ObjectID id;
        const Cost cost;
        const ObjectID requirements;

        operator ObjectID() const { return id; }
    };

    struct Building : Buildable
    {
        const ObjectID upgradable;
    };

    struct SupplyBuilding : Building
    {
        const int supply;
    };

    struct Unit : Buildable
    {
        const int supply;
        const ObjectID producer;
    };

    struct Worker : Unit
    {
        const float luminitePerSecond;
        const float theuriumPerSecond;
    };

    struct Upgrade : Buildable
    {
    };

    struct BuildOrderStep
    {
        const int supply;
        const ObjectID purchase;
    };

}
