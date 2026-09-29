#include "types.h"

/*
 * Reviewed source unit: src/game/game_105D90.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D8A34
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);

s32 func_150D88E0(f32 *arg0, void *arg1, u8 arg2) {
    struct {
        f32 sp30;
        f32 sp34;
        f32 sp38;
        s32 sp3C;
    } local;

    switch (arg2) {
    case 3:
        local.sp3C = 0x12;
        local.sp38 = -7.0f;
        local.sp30 = 30.0f;
        break;
    case 4:
        local.sp3C = 0x15;
        local.sp38 = -4.0f;
        local.sp30 = 35.0f;
        break;
    case 5:
        local.sp3C = 0xF;
        local.sp38 = 5.0f;
        local.sp30 = 20.0f;
        break;
    case 6:
        local.sp3C = 0x18;
        local.sp38 = 5.0f;
        local.sp30 = 31.0f;
        break;
    }
    local.sp34 = 0.0f;
    func_150A7960((u8 *)*(void **)((u8 *)arg1 + 0x1D4) + (local.sp3C << 6),
                   local.sp38, 0.0f, local.sp30, &local.sp38, &local.sp34, &local.sp30);
    arg0[0] = local.sp38;
    arg0[1] = local.sp34;
    arg0[2] = local.sp30;
    return 1;
}
s32 func_150D8A20(s32 arg0, s32 arg1) {
    return 8;
}
void func_151875E0(f32, f32, f32, s32, s32, s32, f32, f32);
void func_15165F80(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A0B30;
extern f32 D_800A0B34;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D8A34 CURRENT (531) */
void func_150D8A34(void *arg0, u8 arg1, s32 arg2) {
    f32 position[3];

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        func_150D88E0(position, arg0, arg1);
        func_151875E0(position[0], position[1], position[2],
                      0x1E, 0xF, 7, D_800A0B30, D_800A0B34);
        func_15165F80(-1, (s32)position[0],
                      (s32)(*(f32 *)((u8 *)arg0 + 0x180) + 4.0f),
                      (s32)position[2], 4, 0x32, 0, 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D8A34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105D90/func_150D8A34.s")
