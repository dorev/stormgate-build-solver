#pragma once

#include "common.h"

namespace SGBuilds
{
    constexpr Worker Bob
    {
        ID::Bob,
        {20, 50, 0},
        ID::CommandPost,
        1,
        ID::CommandPost | ID::CentralCommand | ID::HighCommand,
        1.0f,
        1.0f
    };

    constexpr Unit Exo
    {
        ID::Exo,
        {28, 100, 25},
        ID::BiokineticsLab,
        2,
        ID::Barracks
    };

    constexpr Unit MedTech
    {
        ID::MedTech,
        {30, 100, 50},
        ID::CentralCommand,
        3,
        ID::Barracks
    };

    constexpr Upgrade QuickdrawHustle
    {
        ID::QuickdrawHustle,
        {60, 100, 100},
        ID::BiokineticsLab
    };

    constexpr Building CommandPost
    {
        ID::CommandPost,
        {90, 400, 0},
        0,
        ID::CentralCommand
    };

    constexpr Building CentralCommand
    {
        ID::CentralCommand,
        {40, 200, 100},
        ID::CommandPost | ID::Barracks,
        ID::HighCommand
    };

    constexpr Building Barracks
    {
        ID::Barracks,
        {40, 150, 0},
        ID::CommandPost,
        0
    };

    constexpr SupplyBuilding Habitat
    {
        ID::CentralCommand,
        {20, 200, 0},
        0,
        ID::HighCommand,
        10
    };
}
