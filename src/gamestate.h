#pragma once

#include "model.h"
#include "faction.h"

namespace SGBuilds
{
    using DecisionID = DecisionID;

    class GameState
    {
    private:
        static constexpr float TimeIncrementPerUpdate = 1.0f;
        friend class Vanguard;
        friend class Infernal;
        friend class Celestial;

    public:
        GameState();
        const ObjectID& GetTargetObject() const;
        void SetTargetObject(const ObjectID& targetObject);
        ErrorCode Reset(const Faction& faction);
        ErrorCode Update();
        ErrorCode HasReachedTarget(const BuildTarget& target, bool& hasReachedTarget);
        ErrorCode HasCompletedBuild(const std::vector<BuildTarget>& buildTargets, bool& buildCompleted);
        ErrorCode ListNextAccessibleTargets(const std::vector<BuildTarget>& targets, std::vector<ObjectID>& accessibleTargets);
        float GetTime();
        const std::vector<Building>& GetBuildings() const;
        const std::vector<Unit>& GetUnits() const;
        const std::vector<Upgrade>& GetUpgrades() const;
        ErrorCode TechAllows(ObjectID objectId, bool& allowed) const;
        ErrorCode IsAllowedByTech(const Object& object, bool& allowed) const;
        ErrorCode CanAfford(ObjectID id, bool& canAfford);
        ErrorCode CanAfford(const Object& object, bool& canAfford);
        ErrorCode CanProduce(ObjectID objectId, bool& techAllows, bool& canProduce);
        ErrorCode CanProduce(const Object& object, bool& techAllows, bool& canProduce);
        ErrorCode CheckProductionCapability(ObjectID objectId, bool& techAllows, bool& canAfford, bool& canProduce);
        ErrorCode Buy(ObjectID id);
        int GetCurrentPopulationCap() const;
        int LuminiteIsSaturated() const;

    private:
        ErrorCode UpdateResources();
        ErrorCode UpdatePendingObjects();

    private:
        ObjectID _TargetObject;
        const Faction& _Faction;
        float _Time;
        float _Luminite;
        float _Therium;
        std::vector<Unit> _Units;
        std::vector<Building> _Buildings;
        std::vector<Upgrade> _Upgrades;
        std::vector<Object> _PendingObjects;
        bool _BuildCompleted;
    };
}
