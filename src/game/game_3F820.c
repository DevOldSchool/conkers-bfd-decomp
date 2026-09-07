#include "types.h"

/*
 * Reviewed source unit: src/game/game_3F820.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15012370
 * - func_150124A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1518AADC(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_80088750;

void func_151EF954(void *, f32, f32, f32, f32, f32, f32, f32);
extern s32 D_80082FA0;
extern u8 *D_800BE628;
extern u8 D_800DCC10[];
extern f32 D_80096560;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15012370 CURRENT (705) */
void func_15012370(void) {
    f32 temp_fs2;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_t0;
    s32 var_s0;
    u8 *temp_v0;

    var_s0 = 0;
    if (D_80082FA0 >= 0) {
        temp_fs2 = D_80096560;
        do {
            temp_v0 = D_800BE628 + (var_s0 * 0x180);
            temp_fv0 = *(f32 *)(temp_v0 + 4) * 0.5f;
            temp_fv1 = *(f32 *)(temp_v0 + 8) * 0.5f;
            func_151EF954(D_800DCC10 + (var_s0 << 6), -temp_fv0, temp_fv0,
                          -temp_fv1, temp_fv1, 1.0f, temp_fs2, 1.0f);
            temp_t0 = (var_s0 + 1) & 0xFF;
            var_s0 = temp_t0;
        } while (D_80082FA0 >= temp_t0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15012370 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3F820/func_15012370.s")
void func_15012470(void) {
    D_80088750 = func_1518AADC(4, 0x12C, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_3F820/func_150124A0.s")
