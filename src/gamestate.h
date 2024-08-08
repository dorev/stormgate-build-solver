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
        const ObjectID& GetObjectiveObject() const;
        void SetObjectiveObject(const ObjectID& objectiveId);
        ErrorCode Reset(const Faction& faction);
        ErrorCode Update();
        ErrorCode HasReachedObjective(const Objective& objective, bool& hasReachedObjective);
        ErrorCode HasCompletedBuild(const std::vector<Objective>& objective, bool& buildCompleted);
        ErrorCode ListNextAccessibleObjectives(const std::vector<Objective>& objectives, std::vector<ObjectID>& accessibleObjectives);
        float GetTime();
        const std::vector<BuildingPtr>& GetBuildings() const;
        const std::vector<UnitPtr>& GetUnits() const;
        const std::vector<UpgradePtr>& GetUpgrades() const;
        ErrorCode TechAllows(ObjectID objectId, bool& allowed) const;
        ErrorCode IsAllowedByTech(const Object& object, bool& allowed) const;
        ErrorCode CanAfford(ObjectID objectId, bool& canAfford);
        ErrorCode CanAfford(const Object& object, bool& canAfford);
        ErrorCode CanProduce(ObjectID objectId, bool& techAllows, bool& canProduce);
        ErrorCode CanProduce(const Object& object, bool& techAllows, bool& canProduce);
        ErrorCode CheckProductionCapability(ObjectID objectId, bool& techAllows, bool& canAfford, bool& canProduce);
        ErrorCode Buy(const ObjectID& objectId, ObjectPtr& object);
        ErrorCode Give(const ObjectID& objectId, ObjectPtr& object);

    private:
        ErrorCode UpdateResources();
        ErrorCode UpdatePendingObjects();

    private:
        ObjectID _ObjectiveId;
        const Faction& _Faction;
        float _Time;
        float _Luminite;
        float _Therium;
        std::vector<UnitPtr> _Units;
        std::vector<BuildingPtr> _Buildings;
        std::vector<UpgradePtr> _Upgrades;
        std::vector<ObjectPtr> _PendingObjects;
        bool _BuildCompleted;
    };
}
