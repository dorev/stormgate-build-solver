#pragma once

#include "model.h"
#include "database.h"

namespace SGBuilds
{
    Object::Object(ObjectID id, Cost cost, ObjectID requirements, SpellID spells)
        : id(id)
        , cost(cost)
        , requirements(requirements)
        , spells(spells)
        , task(Task::Idle)
        , buff()
        , completion(0.0f)
    {
    }

    Object::Object(const Object& other)
        : id(other.id)
        , cost(other.cost)
        , requirements(other.requirements)
        , spells(other.spells)
        , task(other.task)
        , buff(other.buff)
        , completion(other.completion)
    {
    }

    Object::Object(const ObjectID& objectId)
    {
        const Object& prototype = Database::Get(objectId);
        if (prototype.id == ID::NoObject)
        {
            // TODO: big problem! assert
            return;
        }

        id = prototype.id;
        cost = prototype.cost;
        requirements = prototype.requirements;
        spells = prototype.spells;
        task = Task::Idle;
        buff = Buff();
        completion = 0.0f;
    }

    Object& Object::operator=(const Object& other)
    {
        if (this != &other)
        {
            id = other.id;
            cost = other.cost;
            requirements = other.requirements;
            spells = other.spells;
            task = other.task;
            buff = other.buff;
            completion = other.completion;
        }

        return *this;
    }

    Object::~Object()
    {
    }

    ErrorCode Object::ExpandRequirements(std::vector<ObjectID>& requiredBuildings) const
    {
        if (requirements == 0)
        {
            return {};
        }

        if (requirements & ID::Upgrade || requirements & ID::Unit)
        {
            return InvalidRequirements;
        }

        for (int i = 0; i < ID::MaxObjectIDShift; ++i)
        {
            if (i & requirements)
            {
                ObjectID buildingId = requirements & ~(ID::ObjectIDMask);
                buildingId |= (1 << i);
                requiredBuildings.push_back(buildingId);
            }
        }

        return Success;
    }

    // Building

    Building::Building(ObjectID id, Cost cost, ObjectID requirements, ObjectID transformation, int supply, int producer, SpellID spells)
        : Object(id, cost, requirements, spells)
        , transformable(transformation)
        , supply(supply)
        , producer(producer)
    {
    }

    Building::Building(const ObjectID& objectId)
    {
        if (objectId == ID::NoObject || !IsBuilding(objectId))
        {
            // TODO: big problem! assert
            return;
        }

        const Building& prototype = static_cast<const Building&>(Database::Get(objectId));

        id = prototype.id;
        cost = prototype.cost;
        requirements = prototype.requirements;
        spells = prototype.spells;
        task = Task::Idle;
        buff = Buff();
        completion = 0.0f;
        transformable = prototype.transformable;
        supply = prototype.supply;
        producer = prototype.producer;
    }

    // Unit

    Unit::Unit(ObjectID id, Cost cost, ObjectID requirements, int supply, ObjectID producer, float luminitePerSecond, float theriumPerSecond)
        : Object(id, cost, requirements)
        , supply(supply)
        , producer(producer)
        , luminitePerSecond(luminitePerSecond)
        , theriumPerSecond(theriumPerSecond)
    {
    }

    Unit::Unit(const ObjectID& objectId)
    {
        if (objectId == ID::NoObject || !IsUnit(objectId))
        {
            // TODO: big problem! assert
            return;
        }

        const Unit& prototype = static_cast<const Unit&>(Database::Get(objectId));

        id = prototype.id;
        cost = prototype.cost;
        requirements = prototype.requirements;
        spells = prototype.spells;
        task = Task::Idle;
        buff = Buff();
        completion = 0.0f;
        supply = prototype.supply;
        producer = prototype.producer;
        luminitePerSecond = prototype.luminitePerSecond;
        theriumPerSecond = prototype.theriumPerSecond;
    }

    // Upgrade

    Upgrade::Upgrade(ObjectID id, Cost cost, ObjectID requirements, ObjectID producer)
        : Object(id, cost, requirements)
        , producer(producer)
    {
    }

    Upgrade::Upgrade(const ObjectID& objectId)
    {
        if (objectId == ID::NoObject || !IsUpgrade(objectId))
        {
            // TODO: big problem! assert
            return;
        }

        const Upgrade& prototype = static_cast<const Upgrade&>(Database::Get(objectId));

        id = prototype.id;
        cost = prototype.cost;
        requirements = prototype.requirements;
        spells = prototype.spells;
        task = Task::Idle;
        buff = Buff();
        completion = 0.0f;
        producer = prototype.producer;
    }

}
