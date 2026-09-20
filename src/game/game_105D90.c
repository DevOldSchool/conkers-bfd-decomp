#include "types.h"

/*
 * Reviewed source unit: src/game/game_105D90.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D88E0
 * - func_150D8A34
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_105D90/func_150D88E0.s")
s32 func_150D8A20(s32 arg0, s32 arg1) {
    return 8;
}
void func_150D88E0(f32 *, void *, u8, void *);
void func_151875E0(f32, f32, f32, s32, s32, s32, f32, f32);
void func_15165F80(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A0B30;
extern f32 D_800A0B34;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D8A34 CURRENT (1206) */
void func_150D8A34(void *arg0, u8 arg1, s32 arg2) {
    f32 position[3];
    s32 actor;

    actor = (s32)arg0;
    if (*(s32 *)(actor + 0x1D4) != 0) {
        func_150D88E0(position, (void *)actor, arg1, (void *)actor);
        func_151875E0(position[0], position[1], position[2],
                      0x1E, 0xF, 7, D_800A0B30, D_800A0B34);
        func_15165F80(-1, (s32)position[0],
                      (s32)(*(f32 *)(actor + 0x180) + 4.0f),
                      (s32)position[2], 4, 0x32, 0, 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D8A34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105D90/func_150D8A34.s")
