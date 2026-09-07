#include "types.h"

/*
 * Reviewed source unit: src/game/game_DAE50.c
 * Boundary evidence: docs/evidence/game_final_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AD9A0
 * - func_150ADA20
 * - func_150ADA68
 * - func_150ADACC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s64 D_800885B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AD9A0 CURRENT (3270) */
s32 func_150AD9A0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;

    temp_v0 = arg0 >> 0x1F;
    var_a0 = (arg0 ^ temp_v0) - temp_v0;
    temp_v0_2 = arg1 >> 0x1F;
    var_a1 = (arg1 ^ temp_v0_2) - temp_v0_2;
    temp_v0_3 = arg2 >> 0x1F;
    var_a2 = (arg2 ^ temp_v0_3) - temp_v0_3;
    if (var_a0 < var_a1) {
        temp_a1 = var_a1 ^ var_a0;
        var_a0 ^= temp_a1;
        var_a1 = var_a0 ^ temp_a1;
    }
    temp_v0_4 = var_a2 ^ var_a0;
    if (var_a0 < var_a2) {
        var_a0 ^= temp_v0_4;
        var_a2 = temp_v0_4 ^ var_a0;
    }
    if (var_a1 < var_a2) {
        temp_a2 = var_a2 ^ var_a1;
        var_a1 ^= temp_a2;
        var_a2 = temp_a2 ^ var_a1;
    }
    return ((u32) (var_a1 * 0xB) >> 5) + (((u32) var_a2 >> 2) + var_a0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AD9A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAE50/func_150AD9A0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150ADA20 CURRENT (8515) */
s64 func_150ADA20(void) {
    s64 temp_a0;
    u64 temp_a2;

    temp_a2 = (((u64) (D_800885B0 << 0x3F) >> 0x1F) | ((u64) (D_800885B0 << 0x1F) >> 0x20)) ^ ((u64) (D_800885B0 << 0x2C) >> 0x20);
    temp_a0 = ((temp_a2 >> 0x14) & 0xFFF) ^ temp_a2;
    D_800885B0 = temp_a0;
    return (s64) (temp_a0 << 0x20) >> 0x20;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150ADA20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAE50/func_150ADA20.s")
extern f32 D_8009F740;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150ADA68 CURRENT (8885) */
f32 func_150ADA68(void) {
    s64 temp_a0;
    u64 temp_a2;

    temp_a2 = (((u64) (D_800885B0 << 0x3F) >> 0x1F) | ((u64) (D_800885B0 << 0x1F) >> 0x20)) ^ ((u64) (D_800885B0 << 0x2C) >> 0x20);
    temp_a0 = ((temp_a2 >> 0x14) & 0xFFF) ^ temp_a2;
    D_800885B0 = temp_a0;
    return (f32) (((s64) (temp_a0 << 0x20) >> 0x20) & 0xFFFF) * D_8009F740;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150ADA68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAE50/func_150ADA68.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150ADACC */
void func_150ADACC(s32 arg0) {
    D_800885B0 = arg0 + 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150ADACC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAE50/func_150ADACC.s")
