#pragma once

namespace SGBuilds
{
    using ErrorCode = int;
    constexpr ErrorCode Success = 0;
    constexpr ErrorCode InvalidObjectType = -1;
    constexpr ErrorCode EmptyObjectiveList = -2;
    constexpr ErrorCode MultipleFactionsInList = -3;
    constexpr ErrorCode InvalidFaction = -4;
    constexpr ErrorCode MustNotUpdateNodeWithChildren = -5;
    constexpr ErrorCode StateAlreadyHasAObjective = -6;
    constexpr ErrorCode NoData = -7;
    constexpr ErrorCode NotEnoughResources = -8;
    constexpr ErrorCode InvalidRequirements = -9;
    constexpr ErrorCode InvalidDecision = -10;
    constexpr ErrorCode NoBuilderAvailable = -11;
    constexpr ErrorCode NotYetImplemented = -9999;
}

#define CHECK_ERROR(error) if ((error) != Success) { return error; }
