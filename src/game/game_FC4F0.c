#include "types.h"

/*
 * Reviewed source unit: src/game/game_FC4F0.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 */

extern f32 func_150484A0(f32 arg0, f32 arg1);
extern f32 D_800A0838;

f32 func_150CF040(s32 arg0, s32 arg1) {
    arg0 += 1;
    arg1 -= 0x2C;
    return func_150484A0((f32) arg0, (f32) arg1) * D_800A0838;
}
