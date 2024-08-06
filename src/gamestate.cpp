#include "gamestate.h"
#include "database.h"

namespace SGBuilds
{
    GameState::GameState()
        : _Faction(Faction::Get(ID::Vanguard))
    {
    }

    const ObjectID& GameState::GetTargetObject() const
    {
        return _TargetObject;
    }

    void GameState::SetTargetObject(const ObjectID& targetObject)
    {
        _TargetObject = targetObject;
    }

    ErrorCode GameState::Reset(const Faction& faction)
    {
        *const_cast<Faction*>(&_Faction) = faction;
        _Faction.ResetGameState(*this);
        return Success;
    }

    ErrorCode GameState::Update()
    {
        if (!_BuildCompleted)
        {
            _Time += TimeIncrementPerUpdate;

            ErrorCode result = UpdateResources();
            CHECK_ERROR(result);

            result = UpdatePendingObjects();
            CHECK_ERROR(result);
        }

        return Success;
    }

    ErrorCode GameState::HasReachedTarget(const BuildTarget& target, bool& hasReachedTarget)
    {
        int targetCount = 0;
        ObjectID objectType = GetObjectType(target);

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

        if (target.count == 0)
        {
            hasReachedTarget = targetCount > 0;
        }
        else
        {
            hasReachedTarget = targetCount >= target.count;
        }

        return Success;
    }

    ErrorCode GameState::HasCompletedBuild(const std::vector<BuildTarget>& buildTargets, bool& hasReachedTargets)
    {
        if (!_BuildCompleted)
        {
            for (const BuildTarget& target : buildTargets)
            {
                ErrorCode result = HasReachedTarget(target, hasReachedTargets);
                CHECK_ERROR(result);

                if (!hasReachedTargets)
                {
                    return Success;
                }
            }
        }

        _BuildCompleted = true;

        return Success;
    }

    ErrorCode GameState::ListNextAccessibleTargets(const std::vector<BuildTarget>& buildTargets, std::vector<ObjectID>& accessibleTargets)
    {
        ErrorCode result;

        // List targets yet to be completed
        std::vector<ObjectID> remainingTargets;
        for (const BuildTarget& target : buildTargets)
        {
            bool hasReachedTarget;
            result = HasReachedTarget(target, hasReachedTarget);
            CHECK_ERROR(result);

            if (!hasReachedTarget)
            {
                remainingTargets.push_back(target);
            }
        }

        // Filter out inaccessible objects (because of lacking prereqs)
        for (const ObjectID& targetObject : remainingTargets)
        {
            bool techAllows;
            result = TechAllows(targetObject, techAllows);
            CHECK_ERROR(result);

            if (techAllows)
            {
                accessibleTargets.push_back(targetObject);
            }
        }

        return Success;
    }

    float GameState::GetTime()
    {
        return _Time;
    }

    const std::vector<Building>& GameState::GetBuildings() const
    {
        return _Buildings;
    }

    const std::vector<Unit>& GameState::GetUnits() const
    {
        return _Units;
    }

    const std::vector<Upgrade>& GameState::GetUpgrades() const
    {
        return _Upgrades;
    }

    ErrorCode GameState::TechAllows(ObjectID objectId, bool& allowed) const
    {
        GET_PROTOTYPE(object, objectId);
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
        GET_PROTOTYPE(object, id);
        return CanAfford(object, canAfford);
    }

    ErrorCode GameState::CanAfford(const Object& object, bool& canAfford)
    {
        canAfford = object.cost.luminite < _Luminite && object.cost.therium < _Therium;
        return Success;
    }

    ErrorCode GameState::CanProduce(ObjectID objectId, bool& techAllows, bool& canProduce)
    {
        GET_PROTOTYPE(object, objectId);
        return CanProduce(object, techAllows, canProduce);
    }

    ErrorCode GameState::CanProduce(const Object& object, bool& techAllows, bool& canProduce)
    {
        ErrorCode result = IsAllowedByTech(object, techAllows);
        CHECK_ERROR(result);

        if (!techAllows)
        {
            canProduce = false;
            return Success;
        }

        // Find if we have a producer building available
        if (IsUnit(object) || IsUpgrade(object))
        {
            ObjectID producerBuildingId = static_cast<const Unit&>(object).producer;
            for (const Building& building : _Buildings)
            {
                if (building == producerBuildingId && building.IsIdle())
                {
                    canProduce = true;
                    break;
                }
            }
        }
        else if (IsBuilding(object))
        {
            canProduce = _Faction.HasBuilderAvailable(*this);
        }

        return Success;
    }

    ErrorCode GameState::CheckProductionCapability(ObjectID objectId, bool& techAllows, bool& canAfford, bool& canProduce)
    {
        GET_PROTOTYPE(object, objectId);

        ErrorCode result = CanAfford(object, canAfford);
        CHECK_ERROR(result);

        result = CanProduce(object, techAllows, canProduce);
        CHECK_ERROR(result);

        return Success;
    }

    ErrorCode GameState::Buy(ObjectID id)
    {
        GET_PROTOTYPE(object, id);

        if (object.cost.luminite >= _Luminite || object.cost.therium >= _Therium)
        {
            return NotEnoughResources;
        }

        _Luminite -= object.cost.luminite;
        _Therium -= object.cost.therium;

        if (IsBuilding(id))
        {
            _Faction.StartBuildingProduction(*this);
        }

        _PendingObjects.emplace_back(std::make_shared<Object>(object));

        return Success;
    }

    int GameState::GetCurrentPopulationCap() const
    {
        return _Faction.GetPopulationCap(*this);
    }

    int GameState::LuminiteIsSaturated() const
    {
        return _Faction.LuminiteSaturated(*this);
    }

    ErrorCode GameState::UpdateResources()
    {
        for (const Unit& unit : _Units)
        {
            switch (unit.task)
            {
            case Task::CollectingLuminite:
                _Luminite += unit.luminitePerSecond;
                break;
            case Task::CollectingTherium:
                _Therium += unit.theriumPerSecond;
                break;
            default:
                break;
            }
        }

        return Success;
    }

    ErrorCode GameState::UpdatePendingObjects()
    {
        for (auto itr = _PendingObjects.rbegin(); itr != _PendingObjects.rend(); ++itr)
        {
            ObjectPtr object = *itr;

            float productionBuffFactor = 1.0f;
            if (object->buff.id == ID::SolarHabitatBuff)
            {
                productionBuffFactor += 0.25;
            }

            // NOTE: What's the production buff if more workers come to help build?

            object->completion += (TimeIncrementPerUpdate / object->cost.time) * productionBuffFactor;

            if (object->completion >= 1.0f)
            {
                // CATCH UP HERE
                // Add to the relevant GameState vector
                switch (GetObjectType(*object))
                {
                case ID::Building:
                    //_Buildings.emplace_back();
                case ID::Unit:
                case ID::Upgrade:
                    break;
                }

                // Remove pending object from this vector
            }
        }

        return NotYetImplemented;
    }
}
