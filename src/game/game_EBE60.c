#include "types.h"

/*
 * Reviewed source unit: src/game/game_EBE60.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BE9B0
 * - func_150BEACC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15142314(s32, s32, void *);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BE9B0 CURRENT (610) */
s32 func_150BE9B0(f32 *arg0, void *arg1, void *arg2, u8 arg3) {
    f32 position[3];
    s32 var_a1;

    switch (arg3) {
    case 4:
        var_a1 = 0x17;
        break;
    case 5:
        var_a1 = 0x14;
        break;
    case 6:
        var_a1 = 0xC;
        break;
    case 7:
        var_a1 = 0x10;
        break;
    default:
        var_a1 = 0x10;
        break;
    }
    func_15142314(*(s32 *)((u8 *)arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 10.0f;
    position[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 50.0f, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BE9B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EBE60/func_150BE9B0.s")
s32 func_150BEAA8(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg0 == 1)) {
        return 0x11;
    }
    return -1;
}
s32 func_150BE9B0(f32 *, void *, void *, u8);
void func_15141F78(s32, void *, f32, s32, f32 *, s32);
void func_15142180(u8, f32 *, s32, f32, f32);
extern f32 D_800A00C0;
extern f32 D_800A00C4;
extern f32 D_800A00C8;
extern f32 D_800A00CC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BEACC CURRENT (1088) */
void func_150BEACC(void *arg0, u8 arg1, s32 arg2) {
    s32 saved_arg1;
    s32 work[9];
    f32 position[3];

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        saved_arg1 = arg1;
        if (func_150BE9B0(position, arg0, work, arg1) != 0) {
            func_15141F78(0xB, work,
                          (f32)arg2 * D_800A00C0 * D_800A00C4,
                          (u32)(*(f32 *)((u8 *)arg0 + 0x40) * D_800A00C8) & 0xFF,
                          position, saved_arg1);
            if (arg2 >= 0x4C) {
                func_15142180(2, position, work[6], 3.232f, D_800A00CC);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BEACC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EBE60/func_150BEACC.s")
