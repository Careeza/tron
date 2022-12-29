#pragma once

#define EGMatchmakingMode_FILL_ROOM       ((nByte)0) ///<Fills up rooms (oldest first) to get players together as fast as possible. Default. Makes most sense with MaxPlayers > 0 and games that can only start with more players.
#define EGMatchmakingMode_SERIAL_MATCHING ((nByte)1) ///<Distributes players across available rooms sequentially but takes filter into account. Without filter, rooms get players evenly distributed.
#define EGMatchmakingMode_RANDOM_MATCHING ((nByte)2) ///<Joins a (fully) random room. Expected properties must match but aside from this, any available room might be selected.