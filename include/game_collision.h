#ifndef CONKER_GAME_COLLISION_H
#define CONKER_GAME_COLLISION_H

#include "types.h"

/* Collision hit record shared by the game overlay (size 0x24).
 * Promoted from six identical source-local copies (game_71820.c,
 * game_105A40.c, game_117FC0.c and game_1FC830.c as Game71820Hit,
 * game_A28B0.c as GameA28B0Transform, game_E7DE0.c as GameE7DE0Hit) under
 * docs/decompilation-workflow.md, Shared type definitions. Matched bodies
 * keep using the same field names.
 */
typedef struct Game71820Hit {
    f32 height;
    s16 points[9];
    s32 object;
    u8 flags;
    u8 active;
    u8 pad1E[2];
    s32 field20;
} Game71820Hit;

#endif
