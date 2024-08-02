#include "gamestate.h"
#include "database.h"

namespace SGBuilds
{
    Intention GameState::GetIntention() const
    {
        return _Intention;
    }
    
    void GameState::SetIntention(const Intention& intention)
    {
        _Intention = intention;
    }

    ErrorCode GameState::Reset(const ObjectID& faction)
    {
        return NotYetImplemented;
    }

    ErrorCode GameState::Update(const std::vector<Target>& targets)
    {
        if (!_HasReachedTargets)
        {
            ErrorCode result = UpdateResources();
            CHECK_ERROR(result);

            result = UpdatePendingObjects();
            CHECK_ERROR(result);
        }

        return Success;
    }

    ErrorCode GameState::HasReachedTarget(const Target& target, bool& hasReachedTarget)
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
                if (object == target)
                {
                    targetCount++;
                }
            }
            break;

        case ID::Upgrade:
            for (const Object& object : _Upgrades)
            {
                if (object == target)
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

    ErrorCode GameState::HasReachedTargets(const std::vector<Target>& targets, bool& hasReachedTargets)
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

    int GameState::GetTime()
    {
        return _Time;
    }

    const std::vector<Building>& GameState::GetBuildings() const
    {
        return _Buildings;
    }

    ErrorCode GameState::IsAllowedByTech(ObjectID objectId, bool& allowed) const
    {
        GET_OBJECT(object, objectId);
        return IsAllowedByTech(object, allowed);
    }

    ErrorCode GameState::IsAllowedByTech(const Object& object, bool& allowed) const
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

    ErrorCode GameState::CanAfford(ObjectID id, bool& canAfford)
    {
        GET_OBJECT(object, id);
        return CanAfford(object, canAfford);
    }

    ErrorCode GameState::CanAfford(const Object& object, bool& canAfford)
    {
        canAfford = object.cost.luminite < _Luminite && object.cost.therium < _Therium;
        return Success;
    }

    ErrorCode GameState::CanProduce(ObjectID objectId, bool& canProduce)
    {
        GET_OBJECT(object, objectId);

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
                if (building == producerBuildingId && building.IsIdle())
                {
                    canProduce = true;
                    break;
                }
            }
        }

        return Success;
    }

    ErrorCode GameState::CanAffordAndProduce(ObjectID objectId, bool& canAffordAndProduce)
    {
        GET_OBJECT(object, objectId);

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

    ErrorCode GameState::Buy(ObjectID id)
    {
        GET_OBJECT(object, id);

        if (object.cost.luminite >= _Luminite || object.cost.therium >= _Therium)
        {
            return NotEnoughResources;
        }

        _Luminite -= object.cost.luminite;
        _Therium -= object.cost.therium;

        _PendingObjects.emplace_back(object);

        return Success;
    }

    int GameState::GetCurrentSupplyCap() const
    {
        return -1;
    }

    int GameState::WillExceedSupplyCap(ObjectID unit) const
    {
        return -1;
    }

    int GameState::LuminiteIsSaturated() const
    {
        return -1;
    }

    ErrorCode GameState::UpdateResources()
    {
        return NotYetImplemented;
    }

    ErrorCode GameState::UpdatePendingObjects()
    {
        // Tick time progress
        // Clear reached targets
        // TODO: consider production buff? (ex: SolarHabitat +25% buff)
        // Check if a target the target is completed
        return NotYetImplemented;
    }
}
