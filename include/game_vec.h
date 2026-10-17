#ifndef CONKER_GAME_VEC_H
#define CONKER_GAME_VEC_H

#include "types.h"

/* Three-float vector shared by the game overlay.
 * Promoted from 115 identical source-local copies (f32 x, y, z at 0x0, 0x4,
 * 0x8; size 0xC) under docs/decompilation-workflow.md, Shared type
 * definitions. Matched bodies keep using the same field names.
 */
typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

#endif
