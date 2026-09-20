#include "types.h"

/*
 * Reviewed source unit: src/game/game_FC410.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CEF60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150A3444(s32, s16, s16, s16);
f32 func_150AD780(f32);
f32 func_150AD78C(f32);
void func_151749A0(s32, s32);
void *func_151149AC(s32);
extern f32 D_800A0830;
extern f32 D_800A0834;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CEF60 CURRENT (1810) */
void func_150CEF60(s32 arg0) {
    struct {
        f32 trig;
        u8 pad20[0x18];
        f32 angle;
    } local;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)func_151149AC(4) + 8) * D_800A0830;
    local.angle = temp_fa0;
    local.trig = func_150AD78C(temp_fa0);
    temp_fv0 = func_150AD780(temp_fa0);
    temp_fv1 = 76.0f - -1.0f;
    temp_fa0_2 = 241.0f - 44.0f;
    func_150A3444(2,
                  (s16)(s32)(((temp_fv1 * temp_fv0) - (temp_fa0_2 * local.trig)) + -1.0f),
                  (s16)(s32)((temp_fv1 * local.trig) + (temp_fa0_2 * temp_fv0) + 44.0f),
                  (s16)(s32)D_800A0834);
    func_151749A0(5, 3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CEF60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC410/func_150CEF60.s")
