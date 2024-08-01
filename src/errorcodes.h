#pragma once

namespace SGBuilds
{
    using ErrorCode = int;
    constexpr ErrorCode Success = 0;
    constexpr ErrorCode InvalidObjectList = -1;
    constexpr ErrorCode EmptyObjectList = -2;
    constexpr ErrorCode MultipleFactionsInList = -3;
    constexpr ErrorCode NotYetImplemented = -99;
}

#define CHECK_ERROR(error) if ((error) != Success) { return error; }
