#include "database.h"

namespace SGBuilds
{
    Database::Database()
        : _Data
        {
            {
                ID::Bob,
                std::make_shared<Unit>
                (
                    ID::Bob,
                    Cost{ 20, 50, 0 },
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
                    Cost{ 28, 100, 25 },
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
                    Cost{ 30, 100, 50 },
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
                    Cost{ 60, 100, 100 },
                    ID::BiokineticsLab,
                    ID::BiokineticsLab
                )
            },
            {
                ID::CommandPost,
                std::make_shared<Building>
                (
                    ID::CommandPost,
                    Cost{ 90, 400, 0 },
                    ID::NoRequirements,
                    ID::CentralCommand,
                    99,
                    true
                )
            },
            {
                ID::CentralCommand,
                std::make_shared<Building>
                (
                    ID::CentralCommand,
                    Cost{ 40, 200, 100 },
                    ID::CommandPost | ID::Barracks,
                    ID::HighCommand,
                    99,
                    true
                )
            },
            {
                ID::Barracks,
                std::make_shared<Building>
                (
                    ID::Barracks,
                    Cost{ 40, 150, 0 },
                    ID::CommandPost,
                    ID::NoTransformation,
                    0,
                    true
                )
            },
            {
                ID::Habitat,
                std::make_shared<Building>
                (
                    ID::CentralCommand,
                    Cost{ 20, 200, 0 },
                    ID::NoRequirements,
                    ID::SolarHabitat | ID::Rampart,
                    10,
                    false
                )
            },
            {
                ID::SolarHabitat,
                std::make_shared<Building>
                (
                    ID::CentralCommand,
                    Cost{ 1, 100, 0 }, // TODO: confirm this value, luminite cost has been guessed here
                    ID::CentralCommand,
                    ID::NoTransformation,
                    15,
                    false,
                    ID::SolarHabitatBuff
                )
            }
        }
    {
    }
}
