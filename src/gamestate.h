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

        ObjectID GetCurrentTarget() const
        {
            return _CurrentTarget;
        }

        ErrorCode SetCurrentTarget(ObjectID objectId)
        {
            if (_CurrentTarget != 0)
            {
                return StateAlreadyHasATarget;
            }

            _CurrentTarget = objectId;
        }

        ErrorCode CanProduce(ObjectID objectId, bool& canProduce) const
        {
            GetObject(object, objectId);
            std::vector<ObjectID> requiredBuildings;

            ErrorCode result = object.ExpandRequirements(requiredBuildings);
            CHECK_ERROR(result);

            for (const ObjectID id : requiredBuildings)
            {
                if (ContainsID(requiredBuildings, id))
                {
                    canProduce = false;
                    return Success;
                }
            }

            canProduce = true;
            return Success;
        }

        ErrorCode Buy(ObjectID objectId)
        {
            GetObject(object, objectId);

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
        ObjectID _CurrentTarget;
        bool _HasReachedTargets;
    };
}
