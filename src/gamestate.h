#pragma once

#include "model.h"

namespace SGBuilds
{
    using DecisionID = DecisionID;

    class GameState
    {
    private:
        static constexpr float TimeIncrementPerUpdate = 1.0f;

    public:
        DecisionID GetDecision() const;
        void SetDecision(const DecisionID& intention);
        const ObjectID& GetTargetObject() const;
        void SetTargetObject(const ObjectID& targetObject);
        ErrorCode Reset(const ObjectID& faction);
        ErrorCode Update(const std::vector<Target>& targets);
        ErrorCode HasReachedTarget(const Target& target, bool& hasReachedTarget);
        ErrorCode HasCompletedBuild(const std::vector<Target>& targets, bool& buildCompleted);
        int GetTime();
        const std::vector<Building>& GetBuildings() const;
        ErrorCode IsAllowedByTech(ObjectID objectId, bool& allowed) const;
        ErrorCode IsAllowedByTech(const Object& object, bool& allowed) const;
        ErrorCode CanAfford(ObjectID id, bool& canAfford);
        ErrorCode CanAfford(const Object& object, bool& canAfford);
        ErrorCode CanProduce(ObjectID objectId, bool& canProduce);
        ErrorCode CanAffordAndProduce(ObjectID objectId, bool& canAfford, bool& canProduce);
        ErrorCode Buy(ObjectID id);
        int GetCurrentSupplyCap() const;
        int WillExceedSupplyCap(ObjectID unit) const;
        int LuminiteIsSaturated() const;

    private:
        ErrorCode UpdateResources();
        ErrorCode UpdatePendingObjects();

    private:
        DecisionID _Decision;
        ObjectID _TargetObject;
        int _Time;
        float _Luminite;
        float _Therium;
        std::vector<Unit> _Units;
        std::vector<Building> _Buildings;
        std::vector<Upgrade> _Upgrades;
        std::vector<Object> _PendingObjects;
        int _WorkersOnLuminite;
        int _WorkersOnTherium;
        int _WorkersBuilding;
        bool _BuildCompleted;
    };
}
