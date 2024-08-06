#pragma once

#include "errorcodes.h"

#include <vector>
#include <algorithm>
#include <memory>

namespace SGBuilds
{
    using ObjectID = unsigned;
    using SpellID = unsigned;

    namespace ID
    {
        constexpr unsigned FactionMask                  = 0xFF000000;
        constexpr ObjectID Vanguard                     = 0x01000000;
        constexpr ObjectID Infernal                     = 0x02000000;
        constexpr ObjectID Celestial                    = 0x04000000;

        constexpr unsigned ObjectTypeMask               = 0x00FF0000;
        constexpr ObjectID Building                     = 0x00010000;
        constexpr ObjectID Unit                         = 0x00020000;
        constexpr ObjectID Upgrade                      = 0x00040000;
        constexpr ObjectID Spell                        = 0x00080000;

        constexpr unsigned MaxObjectIDShift             = 16;
        constexpr unsigned ObjectIDMask                 = 0x0000FFFF;
        constexpr ObjectID NoTransformation             = 0;
        constexpr ObjectID NoRequirements               = 0;
        constexpr ObjectID NoObject                     = 0;

        // Vanguard

        constexpr ObjectID CommandPost                  = Vanguard | Building | 0x0001;
        constexpr ObjectID CentralCommand               = Vanguard | Building | 0x0002;
        constexpr ObjectID HighCommand                  = Vanguard | Building | 0x0004;
        constexpr ObjectID Barracks                     = Vanguard | Building | 0x0008;
        constexpr ObjectID Habitat                      = Vanguard | Building | 0x0010;
        constexpr ObjectID SolarHabitat                 = Vanguard | Building | 0x0020;
        constexpr ObjectID Rampart                      = Vanguard | Building | 0x0040;
        constexpr ObjectID MechBay                      = Vanguard | Building | 0x0080;
        constexpr ObjectID BiokineticsLab               = Vanguard | Building | 0x0100;
        constexpr ObjectID SentryPost                   = Vanguard | Building | 0x0200;
        constexpr ObjectID HangarBay                    = Vanguard | Building | 0x0400;
        constexpr ObjectID MachineLab                   = Vanguard | Building | 0x0800;
        constexpr ObjectID Scrapyard                    = Vanguard | Building | 0x1000;

        constexpr ObjectID Bob                          = Vanguard | Unit | 0x0001;
        constexpr ObjectID Lancer                       = Vanguard | Unit | 0x0002;
        constexpr ObjectID Scout                        = Vanguard | Unit | 0x0004;
        constexpr ObjectID Exo                          = Vanguard | Unit | 0x0008;
        constexpr ObjectID MedTech                      = Vanguard | Unit | 0x0010;
        constexpr ObjectID Graven                       = Vanguard | Unit | 0x0020;
        constexpr ObjectID Hedgehog                     = Vanguard | Unit | 0x0040;
        constexpr ObjectID Vulcan                       = Vanguard | Unit | 0x0080;
        constexpr ObjectID Atlas                        = Vanguard | Unit | 0x0100;
        constexpr ObjectID Hornet                       = Vanguard | Unit | 0x0200;
        constexpr ObjectID Evac                         = Vanguard | Unit | 0x0400;
        constexpr ObjectID Sentinel                     = Vanguard | Unit | 0x0800;
        constexpr ObjectID Helicarrier                  = Vanguard | Unit | 0x1000;

        constexpr ObjectID KineticRedirection           = Vanguard | Upgrade | 0x0001;
        constexpr ObjectID VoriliumClaws                = Vanguard | Upgrade | 0x0002;
        constexpr ObjectID QuickdrawHustle              = Vanguard | Upgrade | 0x0004;
        constexpr ObjectID MedtechAdeptTraining         = Vanguard | Upgrade | 0x0008;
        constexpr ObjectID MassInfiltrate               = Vanguard | Upgrade | 0x0010;
        constexpr ObjectID OrbitalEnergyOptimizer       = Vanguard | Upgrade | 0x0020;
        constexpr ObjectID OverchargeAmplifier          = Vanguard | Upgrade | 0x0040;
        constexpr ObjectID TransonicRockets             = Vanguard | Upgrade | 0x0080;
        constexpr ObjectID ImpactThrusters              = Vanguard | Upgrade | 0x0100;
        constexpr ObjectID PlasmaArcInfusion            = Vanguard | Upgrade | 0x0200;
        constexpr ObjectID ReleaseSkymine               = Vanguard | Upgrade | 0x0400;
        constexpr ObjectID SkysprintRetrofit            = Vanguard | Upgrade | 0x0800;
        constexpr ObjectID SentinelAdeptAugmentation    = Vanguard | Upgrade | 0x1000;
        constexpr ObjectID CovertBombers                = Vanguard | Upgrade | 0x2000;

        constexpr SpellID SolarHabitatBuff              = Vanguard | Spell | 0x0001; // TODO: find the real name for this
    }

    inline bool IsBuilding(const ObjectID& id) { return (id & ID::ObjectTypeMask) == ID::Building; }
    inline bool IsUnit(const ObjectID& id) { return (id & ID::ObjectTypeMask) == ID::Unit; }
    inline bool IsUpgrade(const ObjectID& id) { return (id & ID::ObjectTypeMask) == ID::Upgrade; }
    inline ObjectID GetObjectType(const ObjectID& id) { return id & ID::ObjectTypeMask; }
    inline ObjectID GetObjectFaction(const ObjectID& id) { return id & ID::FactionMask; }

    using TaskID = unsigned;
    namespace Task
    {
        constexpr TaskID Idle                         = 0;
        constexpr TaskID CompletingBuilding           = 1;
        constexpr TaskID CompletingUnit               = 2;
        constexpr TaskID CompletingUpgrade            = 3;
        constexpr TaskID CompletingTransformation     = 4;
        constexpr TaskID CollectingLuminite           = 5;
        constexpr TaskID CollectingTherium            = 6;
    }

    using DecisionID = unsigned;
    namespace Decision
    {
        constexpr DecisionID IncreaseSupply             = 0;
        constexpr DecisionID Tech                       = 1;
        constexpr DecisionID Expand                     = 2;
        constexpr DecisionID ProduceUnit                = 3;
        constexpr DecisionID ProduceProducer            = 4;
        constexpr DecisionID ProduceWorker              = 5;
        constexpr DecisionID ProduceUpgrade             = 6;
        constexpr DecisionID MaxDecision                = 7;
    }

    struct Cost
    {
        int time = -1;
        float luminite = -1.0f;
        float therium = -1.0f;
    };

    struct Buff
    {
        SpellID id = 0;
        float startTime = -1.0f;
        // TODO : find a way to identify the buff caster (shared_ptr<>?)
    };

    class Object
    {
    public:
        ObjectID id = 0;
        Cost cost { 0, 0 , 0};
        ObjectID requirements = 0;
        SpellID spells = 0;
        TaskID task = Task::Idle;
        Buff buff = { 0, 0 };
        float completion = 1.0f;

        operator ObjectID() const { return id; }
        bool IsIdle() const { return task == Task::Idle; }

        Object(ObjectID id = 0, Cost cost = { 0, 0 }, ObjectID requirements = 0, SpellID spells = 0);
        Object(const Object& other);
        Object& operator=(const Object& other);
        virtual ~Object();

        ErrorCode ExpandRequirements(std::vector<ObjectID>& requiredBuildings) const;

        private:
            unsigned _UID;
    };

    using ObjectPtr = std::shared_ptr<Object>;

    class Building : public Object
    {
    public:
        ObjectID transformable;
        int supply;
        bool producer;

        Building(ObjectID id, Cost cost, ObjectID requirements, ObjectID transformation = 0, int supply = 0, int producer = false, SpellID spells = 0);
        Building(const Object& object = Object());
    };

    class Unit : public Object
    {
    public:
        int supply;
        ObjectID producer;
        float luminitePerSecond;
        float theriumPerSecond;

        Unit(ObjectID id, Cost cost, ObjectID requirements, int supply, ObjectID producer, float luminitePerSecond = 0.0f, float theriumPerSecond = 0.0f);
        Unit(const Object& object = Object());
    };

    class Upgrade : public Object
    {
    public:
        ObjectID producer;

        Upgrade(ObjectID id, Cost cost, ObjectID requirements, ObjectID producer);
        Upgrade(const Object& object = Object());
    };

    struct BuildTarget
    {
        ObjectID id = 0;
        int count = 1;

        operator ObjectID() const { return id; }
        bool IsValid() const { return id > 0; }
    };

    template <class T>
    inline bool ContainsID(const T& container, ObjectID id)
    {
        auto itr = std::find_if(container.begin(), container.end(), [id](const Object& object) { return object.id == id; });
        return itr != container.end();
    }

    template <>
    inline bool ContainsID(const std::vector<BuildTarget>& container, ObjectID id)
    {
        auto itr = std::find_if(container.begin(), container.end(), [id](const BuildTarget& target) { return target.id == id; });
        return itr != container.end();
    }

    inline bool operator==(const Object& object, const BuildTarget& target)
    {
        return object.id == target.id;
    }
    
    inline bool operator==(const BuildTarget& target, const Object& object)
    {
        return object == target;
    }

    inline bool operator!=(const Object& object, const BuildTarget& target)
    {
        return !(object == target);
    }

    inline bool operator!=(const BuildTarget& target, const Object& object)
    {
        return object != target;
    }
}
