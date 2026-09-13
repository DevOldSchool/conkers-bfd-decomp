#include "types.h"

/*
 * Reviewed source unit: src/game/game_118400.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EAF50
 * - func_150EB090
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game118400Record Game118400Record;

s32 func_151420F8(Game118400Record *);
extern s32 D_800BE9F0;

#pragma GLOBAL_ASM("asm/nonmatchings/game_118400/func_150EAF50.s")

s32 func_150EB030(s32 arg0, Game118400Record *arg1) {
    if (arg0 == 1) {
        if (D_800BE9F0 == 4) {
            if (func_151420F8(arg1) != 0) {
                return 6;
            }
            return 3;
        }
        return -1;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_118400/func_150EB090.s")
