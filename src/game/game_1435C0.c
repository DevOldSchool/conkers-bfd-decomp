#include "types.h"

/*
 * Reviewed source unit: src/game/game_1435C0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15116110
 * - func_1511617C
 * - func_151162D4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1435C0/func_15116110.s")
f32 func_1510F648(f32, f32, f32);                   /* extern */
extern f32 D_800A2FA8;
extern f32 D_800A2FAC;
extern u16 D_800CC354;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511617C CURRENT (1575) */
void func_1511617C(void *arg0) {
    s16 sp1E;
    f32 temp_fv0;
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x12);
    sp1E = temp_v0;
    temp_fv0 = func_1510F648((f32) *(s16 *)((u8 *)arg0 + 0x10), (f32) temp_v0, (f32) *(s16 *)((u8 *)arg0 + 0x14));
    *(f32 *)((u8 *)arg0 + 0x7C) = temp_fv0;
    if (fabsf(temp_fv0 - (f32) *(s16 *)((u8 *)arg0 + 0x12)) > 200.0f) {
        *(s32 *)((u8 *)arg0 + 0x3C) = 0;
    }
    if (!(*(u8 *)((u8 *)arg0 + 0x4F) & 4)) {
        temp_v0_2 = *(s32 *)((u8 *)arg0 + 0x3C);
        *(s32 *)((u8 *)arg0 + 0x3C) = (s32) ((f32) temp_v0_2 + ((f32) -temp_v0_2 * D_800A2FA8));
    } else {
        var_v1 = -0x14;
        if (D_800CC354 == 0x4B) {
            var_v1 = -0x28;
        }
        temp_v0_3 = *(s32 *)((u8 *)arg0 + 0x3C);
        *(s32 *)((u8 *)arg0 + 0x3C) = (s32) ((f32) temp_v0_3 + ((f32) (var_v1 - temp_v0_3) * D_800A2FAC));
    }
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x7C) + (f32) *(s32 *)((u8 *)arg0 + 0x3C));
    *(s16 *)((u8 *)arg0 + 0x5C) = (s16) (*(s16 *)((u8 *)arg0 + 0x12) - sp1E);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511617C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1435C0/func_1511617C.s")
f32 func_15047C00(f32);                             /* extern */
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151162D4 CURRENT (2253) */
void func_151162D4(void *arg0) {
    f32 sp24;
    s32 sp20;
    s16 sp1E;
    f32 temp_fv1;

    sp1E = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x12) + *(f32 *)((u8 *)arg0 + 0x18));
    {
        s32 temp_t9 = *(s32 *)((u8 *)arg0 + 0x3C);
    sp20 = (temp_t9 >> 0x10) & 0xFFFF;
    sp24 = (f32) (s16) temp_t9;
    temp_fv1 = func_15047C00((f32) *(s32 *)((u8 *)arg0 + 0x7C) * 0.005493164f) * sp24;
    *(f32 *)((u8 *)arg0 + 0x18) = temp_fv1;
    *(s32 *)((u8 *)arg0 + 0x7C) = (s32) (*(s32 *)((u8 *)arg0 + 0x7C) + (sp20 * D_800BE9E4));
    *(s16 *)((u8 *)arg0 + 0x5C) = (s16) (s32) (((f32) *(s16 *)((u8 *)arg0 + 0x12) + temp_fv1) - (f32) sp1E);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151162D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1435C0/func_151162D4.s")
