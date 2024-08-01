#pragma once

#include "model.h"

#include <vector>

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
            if (_HasReachedTarget)
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

        ErrorCode HasReachedTargets(const std::vector<Target>& targets, bool& hasReachedTarget)
        {
            if (_HasReachedTarget)
            {
                hasReachedTarget = true;
                return Success;
            }
            else
            {
                hasReachedTarget = false;
            }

            for (const Target& target : targets)
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

                if (targetCount < target.count)
                {
                    hasReachedTarget = false;
                    return Success;
                }
                continue;
            }

            hasReachedTarget = true;
            return Success;
        }

        int GetTime()
        {
            return _Time;
        }

        int GetCurrentSupplyCap() const
        {
        }

        int WillExceedSupplyCap(ObjectID unit) const
        {
        }

        bool CanAfford(ObjectID object) const
        {
        }

        int Buy(ObjectID object)
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
        bool _HasReachedTarget;
    };
}
