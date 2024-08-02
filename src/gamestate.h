#pragma once

#include "model.h"

namespace SGBuilds
{
    using Intention = DecisionID;

    class GameState
    {
    private:
        static constexpr float TimeIncrementPerUpdate = 1.0f;

    public:
        Intention GetIntention() const;
        void SetIntention(const Intention& intention);
        ErrorCode Reset(const ObjectID& faction);
        ErrorCode Update(const std::vector<Target>& targets);
        ErrorCode HasReachedTarget(const Target& target, bool& hasReachedTarget);
        ErrorCode HasReachedTargets(const std::vector<Target>& targets, bool& hasReachedTargets);
        int GetTime();
        const std::vector<Building>& GetBuildings() const;
        ErrorCode IsAllowedByTech(ObjectID objectId, bool& allowed) const;
        ErrorCode IsAllowedByTech(const Object& object, bool& allowed) const;
        ErrorCode CanAfford(ObjectID id, bool& canAfford);
        ErrorCode CanAfford(const Object& object, bool& canAfford);
        ErrorCode CanProduce(ObjectID objectId, bool& canProduce);
        ErrorCode CanAffordAndProduce(ObjectID objectId, bool& canAffordAndProduce);
        ErrorCode Buy(ObjectID id);
        int GetCurrentSupplyCap() const;
        int WillExceedSupplyCap(ObjectID unit) const;
        int LuminiteIsSaturated() const;

    private:
        ErrorCode UpdateResources();
        ErrorCode UpdatePendingObjects();

    private:
        Intention _Intention;
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
        bool _HasReachedTargets;
    };
}
