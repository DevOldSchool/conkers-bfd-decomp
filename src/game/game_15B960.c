#include "types.h"

/*
 * Reviewed source unit: src/game/game_15B960.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512E4B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15047D60(f32);
f32 func_15047C00(f32);
extern f32 D_800A3730;
extern u8 D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512E4B0 CURRENT (219) */
void func_1512E4B0(void *arg0) {
    f32 sp18;
    f32 temp_fa0;
    f32 temp_ft2;
    register s32 var_a1;
    u8 *temp_v0;
    u8 *state;

    state = arg0;
    var_a1 = 0;
    if (state[0x23D] == 3) {
        var_a1 = 1;
    }
    temp_v0 = (var_a1 * 0x32C) + D_800CC2D0;
    *(f32 *)(state + 0x2BC) = *(f32 *)(temp_v0 + 0x14);
    *(f32 *)(state + 0x2C0) = *(f32 *)(temp_v0 + 0x18) + 150.0f;
    *(f32 *)(state + 0x2C4) = *(f32 *)(temp_v0 + 0x1C);
    temp_fa0 = ((f32)(s16)(s32)((*(f32 *)(temp_v0 + 0x40) * 10.0f) +
                    (f32)(s16)(-*(s16 *)(temp_v0 + 0x2E4))) * D_800A3730) / 1800.0f;
    sp18 = temp_fa0;
    temp_ft2 = func_15047D60(temp_fa0) * 60.0f;
    *(f32 *)(state + 0x2FC) = *(f32 *)(state + 0x2C0);
    *(f32 *)(state + 0x2F8) = *(f32 *)(state + 0x2BC) - temp_ft2;
    *(f32 *)(state + 0x300) = *(f32 *)(state + 0x2C4) - (func_15047C00(temp_fa0) * 60.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512E4B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15B960/func_1512E4B0.s")
