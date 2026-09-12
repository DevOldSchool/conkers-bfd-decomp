#include "types.h"

/*
 * Reviewed source unit: src/game/game_197F20.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1516AA70
 * - func_1516B6BC
 * - func_1516C878
 * - func_1516C934
 * - func_1516CC58
 * - func_1516D0CC
 * - func_1516D2E0
 * - func_1516D328
 * - func_1516D378
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516AA70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516B6BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516C878.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516C934.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516CC58.s")
f32 func_15047C00(f32);                             /* extern */
extern u16 D_80090562;
extern u16 D_80090582;
extern f32 D_800A6DE4;
extern f32 D_800A6DE8;
extern void *D_800BE628;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516D0CC CURRENT (5643) */
void func_1516D0CC(void *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft2;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv0_4;
    f32 var_ft0;
    f32 var_ft2;

    var_ft2 = (f32) D_80090562;
    if ((s32) D_80090562 < 0) {
        var_ft2 += 4294967296.0f;
    }
    var_ft0 = (f32) D_80090582;
    if ((s32) D_80090582 < 0) {
        var_ft0 += 4294967296.0f;
    }
    sp1C = (*(f32 *)((u8 *)arg0 + 0x38) / var_ft2) * var_ft0 * 0.25f * *(f32 *)((u8 *)arg0 + 0x28);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x38) * 0.5f;
    temp_ft5 = *(f32 *)((u8 *)arg0 + 0x3C);
    temp_fa1 = *arg2;
    temp_ft2 = func_15047C00(*(f32 *)((u8 *)arg0 + 0x58) + D_800A6DE4) * temp_fv1;
    sp28 = temp_fa1;
    sp2C = temp_fa1 - temp_ft5;
    temp_fa0 = ((temp_ft2 * D_800A6DE8 * *(f32 *)((u8 *)arg0 + 0x28)) + *arg1) - sp1C;
    sp24 = temp_fa0 - temp_fv1;
    sp20 = temp_fv1 + temp_fa0;
    if (arg0 != 0) {
        temp_fv0 = *(f32 *)((u8 *)D_800BE628 + 0x24);
        if (sp2C < temp_fv0) {
            *arg2 = temp_fv0 + temp_ft5;
        } else {
            temp_fv0_2 = *(f32 *)((u8 *)D_800BE628 + 0x28);
            if (temp_fv0_2 < sp28) {
                *arg2 = temp_fv0_2;
            }
        }
        temp_fv0_3 = *(f32 *)((u8 *)D_800BE628 + 0x2C);
        if (sp24 < temp_fv0_3) {
            *arg1 -= sp24 - temp_fv0_3;
        } else {
            temp_fv0_4 = *(f32 *)((u8 *)D_800BE628 + 0x30);
            if (temp_fv0_4 < sp20) {
                *arg1 += temp_fv0_4 - sp20;
            }
        }
        *arg1 = (f32) (s32) *arg1;
        *arg2 = (f32) (s32) *arg2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516D0CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516D0CC.s")
void func_1516D2D8(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516D2E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516D328.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516D378 CURRENT (15) */
void *func_1516D378(void *arg0) {
    s32 *temp_v1;
    s32 *temp_v1_2;

    if ((arg0 != 0) && (*(u8 *)((u8 *)arg0 + 0) == 0x51)) {
        temp_v1 = *(s32 **)((u8 *)arg0 + 0x10);
        *temp_v1 |= 0x100;
        temp_v1_2 = *(s32 **)((u8 *)arg0 + 0x10);
        *temp_v1_2 &= ~0x400;
        return arg0;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516D378 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516D378.s")
void *func_1516D3C4(void *arg0) {
    s32 *temp_v1;

    if ((arg0 != 0) && (*(u8 *)((u8 *)arg0 + 0) == 0x51)) {
        temp_v1 = *(s32 **)((u8 *)arg0 + 0x10);
        *temp_v1 |= 0x500;
        return arg0;
    }
    return 0;
}
