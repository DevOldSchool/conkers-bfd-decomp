#include "types.h"

/*
 * Reviewed source unit: src/game/game_DDF10.c
 * Boundary evidence: docs/evidence/game_raw_audio_owner_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B0A60
 * - func_150B0C34
 * - func_150B0C58
 * - func_150B0D20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_150ADA68();                                /* extern */
extern f32 D_8009F870;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B0A60 CURRENT (2115) */
void func_150B0A60(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, s16 *arg5) {
    f32 temp_fv1;
    f32 temp_fa0;
    f32 var_fv0;

    *arg5 = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x40) * D_8009F870) - 128.0f);
    temp_fv1 = func_150ADA68() * 248.0f;
    {
        f32 sp1C = temp_fv1;
    temp_fa0 = func_150ADA68() + -0.5f;
    if (temp_fv1 < 122.0f) {
        *(f32 *)((u8 *)arg4 + 4) = 0.0f;
        *(f32 *)((u8 *)arg4 + 0) = (f32) ((*(f32 *)((u8 *)arg3 + 0) * temp_fa0 * 122.0f) + (*(f32 *)((u8 *)arg2 + 0) * -31.5f));
        *(f32 *)((u8 *)arg4 + 8) = (f32) ((*(f32 *)((u8 *)arg3 + 4) * temp_fa0 * 122.0f) + (*(f32 *)((u8 *)arg2 + 4) * -31.5f));
    } else {
        var_fv0 = 61.0f;
        if ((temp_fv1 - 122.0f) < 63.0f) {
            var_fv0 = -61.0f;
            *arg5 += 0x40;
        } else {
            *arg5 -= 0x40;
        }
        *(f32 *)((u8 *)arg4 + 4) = 0.0f;
        *(f32 *)((u8 *)arg4 + 0) = (f32) ((*(f32 *)((u8 *)arg3 + 0) * var_fv0) + (*(f32 *)((u8 *)arg2 + 0) * 63.0f * temp_fa0));
        *(f32 *)((u8 *)arg4 + 8) = (f32) ((*(f32 *)((u8 *)arg3 + 4) * var_fv0) + (*(f32 *)((u8 *)arg2 + 4) * 63.0f * temp_fa0));
    }
    *(f32 *)((u8 *)arg4 + 0) = (f32) (*(f32 *)((u8 *)arg4 + 0) + *(f32 *)((u8 *)arg0 + 0x14));
    *(f32 *)((u8 *)arg4 + 4) = (f32) (*(f32 *)((u8 *)arg4 + 4) + *(f32 *)((u8 *)arg1 + 0x118));
    *(f32 *)((u8 *)arg4 + 8) = (f32) (*(f32 *)((u8 *)arg4 + 8) + *(f32 *)((u8 *)arg0 + 0x1C));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B0A60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DDF10/func_150B0A60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DDF10/func_150B0C34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DDF10/func_150B0C58.s")
void func_150B0CE0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DDF10/func_150B0D20.s")
