#include "gamestate.h"
#include "database.h"

namespace SGBuilds
{
    GameState::GameState()
        : _Faction(Faction::Get(ID::Vanguard))
    {
    }

    const ObjectID& GameState::GetObjectiveObject() const
    {
        return _ObjectiveId;
    }

    void GameState::SetObjectiveObject(const ObjectID& objectiveObject)
    {
        _ObjectiveId = objectiveObject;
    }

    ErrorCode GameState::Reset(const Faction& faction)
    {
        _Buildings.clear();
        _Units.clear();
        _Upgrades.clear();
        _PendingObjects.clear();

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

    ErrorCode GameState::HasReachedObjective(const Objective& objective, bool& hasReachedObjective)
    {
        int objectiveCount = 0;
        ObjectID objectType = GetObjectType(objective);

        // TODO: there is probably a way to make this prettier...
        switch (objectType)
        {
        case ID::Building:
            for (const ObjectPtr& object : _Buildings)
            {
                if (object->id == objective.id)
                {
                    objectiveCount++;
                }
            }
            break;

        case ID::Unit:
            for (const ObjectPtr& object : _Units)
            {
                if (object->id == objective)
                {
                    objectiveCount++;
                }
            }
            break;

        case ID::Upgrade:
            for (const ObjectPtr& object : _Upgrades)
            {
                if (object->id == objective)
                {
                    objectiveCount++;
                }
            }
            break;

        default:
            return InvalidObjectType;
        }

        if (objective.count == 0)
        {
            hasReachedObjective = objectiveCount > 0;
        }
        else
        {
            hasReachedObjective = objectiveCount >= objective.count;
        }

        return Success;
    }

    ErrorCode GameState::HasCompletedBuild(const std::vector<Objective>& objectives, bool& hasReachedObjectives)
    {
        if (!_BuildCompleted)
        {
            for (const Objective& objective : objectives)
            {
                ErrorCode result = HasReachedObjective(objective, hasReachedObjectives);
                CHECK_ERROR(result);

                if (!hasReachedObjectives)
                {
                    return Success;
                }
            }
        }

        _BuildCompleted = true;

        return Success;
    }

    ErrorCode GameState::ListNextAccessibleObjectives(const std::vector<Objective>& objectives, std::vector<ObjectID>& accessibleObjectives)
    {
        ErrorCode result;

        // List objectives yet to be completed
        std::vector<ObjectID> remainingObjectives;
        for (const Objective& objective : objectives)
        {
            bool hasReachedObjective;
            result = HasReachedObjective(objective, hasReachedObjective);
            CHECK_ERROR(result);

            if (!hasReachedObjective)
            {
                remainingObjectives.push_back(objective);
            }
        }

        // Filter out inaccessible objects (because of lacking prereqs)
        for (const ObjectID& objectiveObject : remainingObjectives)
        {
            bool techAllows;
            result = TechAllows(objectiveObject, techAllows);
            CHECK_ERROR(result);

            if (techAllows)
            {
                accessibleObjectives.push_back(objectiveObject);
            }
        }

        return Success;
    }

    float GameState::GetTime()
    {
        return _Time;
    }

    const std::vector<BuildingPtr>& GameState::GetBuildings() const
    {
        return _Buildings;
    }

    const std::vector<UnitPtr>& GameState::GetUnits() const
    {
        return _Units;
    }

    const std::vector<UpgradePtr>& GameState::GetUpgrades() const
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

    ErrorCode GameState::CanAfford(ObjectID objectId, bool& canAfford)
    {
        GET_PROTOTYPE(object, objectId);
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
            for (const BuildingPtr& building : _Buildings)
            {
                if (building->id == producerBuildingId && building->IsIdle())
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

    ErrorCode GameState::Buy(const ObjectID& objectId, ObjectPtr& object)
    {
        object = nullptr;

        GET_PROTOTYPE(objectPrototype, objectId);

        if (objectPrototype.cost.luminite >= _Luminite || objectPrototype.cost.therium >= _Therium)
        {
            return NotEnoughResources;
        }

        _Luminite -= objectPrototype.cost.luminite;
        _Therium -= objectPrototype.cost.therium;

        ErrorCode result = _Faction.StartProduction(*this, objectId, object);
        CHECK_ERROR(result);

        _PendingObjects.emplace_back(object);

        return Success;
    }

    ErrorCode GameState::Give(const ObjectID& objectId, ObjectPtr& object)
    {
        object = nullptr;

        GET_PROTOTYPE(objectPrototype, objectId);

        switch (GetObjectType(objectId))
        {
        case ID::Building:
            object = _Buildings.emplace_back(std::make_shared<Building>(objectId));
            break;

        case ID::Unit:
            object = _Units.emplace_back(std::make_shared<Unit>(objectId));
            break;

        case ID::Upgrade:
            object = _Upgrades.emplace_back(std::make_shared<Upgrade>(objectId));
            break;

        default:
            return InvalidObjectType;
        }

        return Success;
    }

    ErrorCode GameState::UpdateResources()
    {
        for (const UnitPtr& unit : _Units)
        {
            switch (unit->task)
            {
            case Task::CollectingLuminite:
                _Luminite += unit->luminitePerSecond;
                break;
            case Task::CollectingTherium:
                _Therium += unit->theriumPerSecond;
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

            if (IsUnit(object->id))
            {
                if (object->buff.id == ID::SolarHabitatBuff)
                {
                    productionBuffFactor += 0.25;
                }
            }

            if (IsBuilding(object->id))
            {
                int buildersOnBuilding = 0;
                for (const UnitPtr& unit : _Units)
                {
                    if (unit->id == ID::Bob && unit->task == Task::CompletingBuilding && unit->target == object->GetUID())
                    {
                        buildersOnBuilding++;
                    }
                }

                if (--buildersOnBuilding >= 1)
                {
                    // TODO: confirm Bob speed buff, I have no idea how much it is honestly
                    productionBuffFactor += 0.25;
                }
            }

            object->completion += (TimeIncrementPerUpdate / object->cost.time) * productionBuffFactor;

            if (object->completion >= 1.0f)
            {
                ErrorCode result = _Faction.FinishProduction(*this, object);
                CHECK_ERROR(result);

                switch (GetObjectType(object->id))
                {
                case ID::Building:
                    _Buildings.emplace_back(std::static_pointer_cast<Building>(object));
                    break;

                case ID::Unit:
                    _Units.emplace_back(std::static_pointer_cast<Unit>(object));
                    break;

                case ID::Upgrade:
                    _Upgrades.emplace_back(std::static_pointer_cast<Upgrade>(object));
                    break;

                default:
                    return InvalidObjectType;
                }

                // Remove pending object from this vector
                // Converting reverse iterator to regular iterator
                _PendingObjects.erase(--itr.base());
            }
        }

        return NotYetImplemented;
    }
}
