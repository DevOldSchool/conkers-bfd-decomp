#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B81D0.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518AD20
 * - func_1518B1D8
 * - func_1518B2A8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B81D0/func_1518AD20.s")
s32 func_1518B1AC(void *arg0) {
    if (*(f32 *)((u8 *)arg0 + 0x3C) < *(f32 *)((u8 *)arg0 + 0x170)) {
        return 0;
    }
    return 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518B1D8 CURRENT (790) */
s32 func_1518B1D8(void *arg0) {
    f32 temp_fv0;
    s32 temp_t6;
    s32 var_a1;
    s32 var_v1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x3C) - *(f32 *)((u8 *)arg0 + 0x170);
    if (temp_fv0 < 0.0f) {
        return 0;
    }
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x64) * 4;
    {
        s32 var_v0 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v0 = 0xFF;
    }
    var_v1 = (s32) temp_fv0 >> 1;
    var_a1 = var_v0;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < var_v0) {
        var_a1 = var_v1;
    }
    if (var_a1 < 0) {
        return 0;
    }
    *(s8 *)((u8 *)arg0 + 0x70) = (s8) var_a1;
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518B1D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B81D0/func_1518B1D8.s")
extern void func_1518B2A8(void *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

void func_1518B264(void *arg0, f32 arg1, f32 arg2, s32 arg3, u8 arg4) {
    func_1518B2A8(arg0, arg1, arg2, arg3, 4, 0xFF, (s32) arg4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B81D0/func_1518B2A8.s")
