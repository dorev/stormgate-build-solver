#pragma once

namespace SGBuilds
{
    using ErrorCode = int;
    constexpr ErrorCode Success = 0;
    constexpr ErrorCode InvalidObjectType = -1;
    constexpr ErrorCode EmptyObjectList = -2;
    constexpr ErrorCode MultipleFactionsInList = -3;
    constexpr ErrorCode InvalidFaction = -4;
    constexpr ErrorCode MustNotUpdateNodeWithChildren = -5;
    constexpr ErrorCode StateAlreadyHasATarget = -6;
    constexpr ErrorCode NoData = -7;
    constexpr ErrorCode NotEnoughResources = -8;
    constexpr ErrorCode NotYetImplemented = -99;
}

#define CHECK_ERROR(error) if ((error) != Success) { return error; }
