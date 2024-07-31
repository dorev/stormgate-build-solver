#pragma once

#include "common.h"

#include <map>
#include <memory>

// Therium regeneration =~ 3.125/s
// Sustainable harvest -> 5 workers
 
namespace SGBuilds
{
    class Database
    {
    private:
        const std::map<ObjectID, std::shared_ptr<Object>> _Data;

        static const auto& GetInstance()
        {
            static Database instance;
            return instance._Data;
        }

    public:
        template <class T>
        static const T& Get(ObjectID id)
        {
            return *static_pointer_cast<T>(GetInstance().at(id));
        }

        Database()
            : _Data
            {
                {
                    ID::Bob,
                    std::make_shared<Unit>
                    (
                        ID::Bob,
                        Cost{20, 50, 0},
                        ID::CommandPost,
                        1,
                        ID::CommandPost | ID::CentralCommand | ID::HighCommand,
                        0.9f,
                        0.625f
                    )
                },
                {
                    ID::Exo,
                    std::make_shared<Unit>
                    (
                        ID::Exo,
                        Cost{28, 100, 25},
                        ID::BiokineticsLab,
                        2,
                        ID::Barracks
                    )
                },
                {
                    ID::MedTech,
                    std::make_shared<Unit>
                    (
                        ID::MedTech,
                        Cost{30, 100, 50},
                        ID::CentralCommand,
                        3,
                        ID::Barracks
                    )
                },
                {
                    ID::QuickdrawHustle,
                    std::make_shared<Upgrade>
                    (
                        ID::QuickdrawHustle,
                        Cost{60, 100, 100},
                        ID::BiokineticsLab
                    )
                },
                {
                    ID::CommandPost,
                    std::make_shared<Building>
                    (
                        ID::CommandPost,
                        Cost{90, 400, 0},
                        0,
                        ID::CentralCommand,
                        10
                    )
                },
                {
                    ID::CentralCommand,
                    std::make_shared<Building>
                    (
                        ID::CentralCommand,
                        Cost{40, 200, 100},
                        ID::CommandPost | ID::Barracks,
                        ID::HighCommand,
                        10
                    )
                },
                {
                    ID::Barracks,
                    std::make_shared<Building>
                    (
                        ID::Barracks,
                        Cost{40, 150, 0},
                        ID::CommandPost
                    )
                },
                {
                    ID::Habitat,
                    std::make_shared<Building>
                    (
                        ID::CentralCommand,
                        Cost{20, 200, 0},
                        0,
                        ID::HighCommand,
                        10
                    )
                }
            }
        {
        }
    };
}
