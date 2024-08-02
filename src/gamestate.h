#pragma once

#include "model.h"

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

        ErrorCode Update(const std::vector<Target>& targets)
        {
            if (_HasReachedTargets)
            {
                return Success;
            }

            ErrorCode result = Success;

            result = UpdateResources();
            CHECK_ERROR(result);

            result = UpdatePendingObjects();
            CHECK_ERROR(result);

            return result;
        }

        ErrorCode HasReachedTarget(const Target& target, bool& hasReachedTarget)
        {
            int targetCount = 0;
            ObjectID objectType = target.id & ID::ObjectTypeMask;

            // TODO: there is probably a way to make this prettier...
            switch (objectType)
            {
            case ID::Building:
                for (const Object& object : _Buildings)
                {
                    if (object.id == target.id)
                    {
                        targetCount++;
                    }
                }
                break;

            case ID::Unit:
                for (const Object& object : _Units)
                {
                    if (object.id == target.id)
                    {
                        targetCount++;
                    }
                }
                break;

            case ID::Upgrade:
                for (const Object& object : _Upgrades)
                {
                    if (object.id == target.id)
                    {
                        targetCount++;
                    }
                }
                break;

            default:
                return InvalidObjectType;
            }

            hasReachedTarget = targetCount < target.count;

            return Success;
        }

        ErrorCode HasReachedTargets(const std::vector<Target>& targets, bool& hasReachedTargets)
        {
            if (_HasReachedTargets)
            {
                hasReachedTargets = true;
                return Success;
            }

            for (const Target& target : targets)
            {
                ErrorCode result = HasReachedTarget(target, hasReachedTargets);
                CHECK_ERROR(result);

                if (!hasReachedTargets)
                {
                    return Success;
                }
            }

            _HasReachedTargets = true;
            return Success;
        }

        int GetTime()
        {
            return _Time;
        }

        const std::vector<Building>& GetBuildings() const
        {
            return _Buildings;
        }

        const Target& GetCurrentTarget() const
        {
            return _CurrentTarget;
        }

        ErrorCode SetCurrentTarget(const Target& target)
        {
            if (_CurrentTarget.id != 0)
            {
                return StateAlreadyHasATarget;
            }

            _CurrentTarget = target;
        }

        ErrorCode IsAllowedByTech(ObjectID objectId, bool& allowed) const
        {
            GetObject(object, objectId);
            return IsAllowedByTech(object, allowed);
        }

        ErrorCode IsAllowedByTech(const Object& object, bool& allowed) const
        {
            std::vector<ObjectID> requiredBuildings;
            ErrorCode result = object.ExpandRequirements(requiredBuildings);
            CHECK_ERROR(result);

            for (const ObjectID id : requiredBuildings)
            {
                if (!ContainsID(_Buildings, id))
                {
                    allowed = false;
                    return Success;
                }
            }

            allowed = true;
            return Success;
        }

        ErrorCode CanAfford(ObjectID id, bool& canAfford)
        {
            GetObject(object, id);
            return CanAfford(object, canAfford);
        }

        ErrorCode CanAfford(const Object& object, bool& canAfford)
        {
            canAfford = object.cost.luminite < _Luminite && object.cost.therium < _Therium;
            return Success;
        }

        ErrorCode CanProduce(ObjectID objectId, bool& canProduce)
        {
            GetObject(object, objectId);

            ErrorCode result = CanAfford(object, canProduce);
            CHECK_ERROR(result);

            if (!canProduce)
            {
                return Success;
            }

            result = IsAllowedByTech(object, canProduce);
            CHECK_ERROR(result);

            // Find if we have a producer building available
            if (objectId & ID::Unit)
            {
                ObjectID producerBuildingId = static_cast<const Unit&>(object).producer;
                int producerBuildingCount = 0;
                for (const Building& building : _Buildings)
                {
                    if (building.id == producerBuildingId && building.status == Status::Idle)
                    {
                        canProduce = true;
                        break;
                    }
                }
            }

            return Success;
        }

        ErrorCode CanAffordAndProduce(ObjectID objectId, bool& canAffordAndProduce)
        {
            GetObject(object, objectId);

            canAffordAndProduce = object.cost.luminite < _Luminite && object.cost.therium < _Therium;

            std::vector<ObjectID> requiredBuildings;
            ErrorCode result = object.ExpandRequirements(requiredBuildings);
            CHECK_ERROR(result);

            for (const ObjectID id : requiredBuildings)
            {
                if (!ContainsID(_Buildings, id))
                {
                    canAffordAndProduce = false;
                    return Success;
                }
            }

            canAffordAndProduce = true;
            return Success;
        }

        ErrorCode Buy(ObjectID id)
        {
            GetObject(object, id);

            if (object.cost.luminite >= _Luminite || object.cost.therium >= _Therium)
            {
                return NotEnoughResources;
            }

            _Luminite -= object.cost.luminite;
            _Therium -= object.cost.therium;

            _PendingObjects.emplace_back(object);

            return Success;
        }

        int GetCurrentSupplyCap() const
        {
        }

        int WillExceedSupplyCap(ObjectID unit) const
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
            // Tick time progress
            // Clear reached targets
            // TODO: consider production buff? (ex: SolarHabitat +25% buff)
            return NotYetImplemented;
        }

    private:
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
        Target _CurrentTarget;
        bool _HasReachedTargets;
    };
}
