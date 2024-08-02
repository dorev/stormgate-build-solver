#pragma once

#include "model.h"

#include <map>
#include <memory>

// Therium regeneration =~ 3.125/s
// Sustainable harvest -> 5 workers

#define CHECK_OBJECT(object) if (object.id == 0) { return NoData; }
#define GET_OBJECT(variableName, objectId) const Object& variableName = Database::Get(objectId); CHECK_OBJECT(variableName)

namespace SGBuilds
{
    class Database
    {
    private:
        static inline const auto& GetData()
        {
            static Database instance;
            return instance._Data;
        }

    public:
        template <class T = Object>
        static const T& Get(ObjectID id)
        {
            const auto itr = GetData().find(id);
            if (itr == GetData().end())
            {
                static const Object sentinel;
                return sentinel;
            }

            return *static_cast<const T*>(itr->second.get());
        }

        Database();

    private:
        const std::map<ObjectID, std::shared_ptr<Object>> _Data;
    };
}
