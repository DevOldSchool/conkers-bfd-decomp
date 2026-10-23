#ifndef CONKER_GAME_PATH_H
#define CONKER_GAME_PATH_H

#include "types.h"

/* 8-byte spatial records: an origin/bounds prefix and indexed points.
 * The final two bytes are opaque metadata, not padding. */
typedef struct GameSpatialPoint {
    s16 x, y, z;
    u8 unknown6[2];
} GameSpatialPoint;

extern GameSpatialPoint **D_800D2104;

#endif
