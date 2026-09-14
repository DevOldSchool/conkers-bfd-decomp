#include "types.h"

/*
 * Reviewed source unit: src/game/game_10CD70.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DF920
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game10CD70Indices {
    u8 values[3];
} Game10CD70Indices;

typedef struct Game10CD70Record {
    u8 pad0[0x14];
    u8 active;
    u8 pad15[0x1F];
} Game10CD70Record;

extern Game10CD70Indices D_80088984;
extern Game10CD70Record *D_800D3098;

s32 func_150DF8C0(s32 arg0) {
    Game10CD70Indices indices = D_80088984;

    if (D_800D3098[indices.values[arg0]].active != 0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_10CD70/func_150DF920.s")
