#pragma once

#define EGEventCache_DO_NOT_CACHE                            ((nByte) 0) // Default value (not sent).
#define EGEventCache_MERGE_CACHE                             ((nByte) 1) // Obsolete - Merges this event's keys with those already cached.
#define EGEventCache_REPLACE_CACHE                           ((nByte) 2) // Obsolete - Replaces the event cache for this eventCode with this event's content.
#define EGEventCache_REMOVE_CACHE                            ((nByte) 3) // Obsolete - Removes this event (by eventCode) from the cache.
#define EGEventCache_ADD_TO_ROOM_CACHE                       ((nByte) 4) // Adds this event to the room's cache
#define EGEventCache_ADD_TO_ROOM_CACHE_GLOBAL                ((nByte) 5) // Adds this event to the cache for actor 0 (becoming a "globally owned" event in the cache).
#define EGEventCache_REMOVE_FROM_ROOM_CACHE                  ((nByte) 6) // Removes fitting events from the room's cache.
#define EGEventCache_REMOVE_FROM_ROOM_CACHE_FOR_ACTORS_LEFT  ((nByte) 7) // Removes events of players who already left the room (cleaning up).
#define EGEventCache_SLICE_INC_INDEX                         ((nByte)10) // Increments the slice index.
#define EGEventCache_SLICE_SET_INDEX                         ((nByte)11) // Sets the slice index to the specified value.
#define EGEventCache_SLICE_PURGE_INDEX                       ((nByte)12) // Deletes or purges the specified slice index.
#define EGEventCache_SLICE_PURGE_UP_TO_INDEX                 ((nByte)13) // Purges all cache slices up to the specified index (inclusive).