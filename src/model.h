#pragma once

#include "errorcodes.h"

#include <vector>
#include <algorithm>

namespace SGBuilds
{
    using ObjectID = unsigned;

    namespace ID
    {
        constexpr unsigned FactionMask                   = 0xFF000000;
        constexpr ObjectID Vanguard                      = 0x01000000;
        constexpr ObjectID Infernal                      = 0x02000000;
        constexpr ObjectID Celestial                     = 0x04000000;

        constexpr unsigned ObjectTypeMask                = 0x00FF0000;
        constexpr ObjectID Building                      = 0x00010000;
        constexpr ObjectID Unit                          = 0x00020000;
        constexpr ObjectID Upgrade                       = 0x00040000;
        constexpr ObjectID Spell                         = 0x00080000;

        constexpr unsigned MaxObjectIDShift              = 16;
        constexpr unsigned ObjectIDMask                  = 0x0000FFFF;
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
        const int time;
        const float luminite;
        const float therium;
    };

    struct Object
    {
        const ObjectID id;
        const Cost cost;
        const ObjectID requirements;
        float completion;

        operator ObjectID() const { return id; }

        Object(ObjectID id = 0, Cost cost = {0, 0}, ObjectID requirements = 0)
            : id(id)
            , cost(cost)
            , requirements(requirements)
        {
        }

        virtual ~Object()
        {
        }

        ErrorCode ExpandRequirements(std::vector<ObjectID>& requiredBuildings) const
        {
            if (requirements == 0)
            {
                return {};
            }

            if (requirements & ID::Upgrade || requirements & ID::Unit)
            {
                return InvalidRequirements;
            }

            for (int i = 0; i < ID::MaxObjectIDShift; ++i)
            {
                if (i & requirements)
                {
                    ObjectID id = requirements & ~(ID::ObjectIDMask);
                    id |= (1 << i);
                    requiredBuildings.push_back(id);
                }
            }

            return Success;
        }
    };

    struct Building : Object
    {
        const ObjectID upgradable;
        const int supply;
        const bool producer;

        Building(ObjectID id, Cost cost, ObjectID requirements, ObjectID upgradable = 0, int supply = 0, int producer = false)
            : Object(id, cost, requirements)
            , upgradable(upgradable)
            , supply(supply)
            , producer(producer)
        {
        }
    };

    struct Unit : Object
    {
        const int supply;
        const ObjectID producer;
        const float luminitePerSecond;
        const float theriumPerSecond;

        Unit(ObjectID id, Cost cost, ObjectID requirements, int supply, ObjectID producer, float luminitePerSecond = 0.0f, float theriumPerSecond = 0.0f)
            : Object(id, cost, requirements)
            , supply(supply)
            , producer(producer)
            , luminitePerSecond(luminitePerSecond)
            , theriumPerSecond(theriumPerSecond)
        {
        }
    };

    struct Upgrade : Object
    {
        Upgrade(ObjectID id, Cost cost, ObjectID requirements)
            : Object(id, cost, requirements)
        {
        }
    };

    struct Target
    {
        ObjectID id = 0;
        int count = 1;
    };

    template <class T>
    bool ContainsID(const T& container, ObjectID id)
    {
        auto itr = std::find_if(container.begin(), container.end(), [id](const Object& object) { return object.id == id; });
        return itr != container.end();
    }

    template <>
    bool ContainsID(const std::vector<Target>& container, ObjectID id)
    {
        auto itr = std::find_if(container.begin(), container.end(), [id](const Target& target) { return target.id == id; });
        return itr != container.end();
    }
}
