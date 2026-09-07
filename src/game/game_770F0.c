#include "types.h"

/*
 * Reviewed source unit: src/game/game_770F0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15049C40
 * - func_15049CB8
 * - func_15049EDC
 * - func_1504A140
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15049C40 CURRENT (190) */
void func_15049C40(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)arg1 + 0);
    temp_fa1 = *(f32 *)((u8 *)arg1 + 4);
    temp_ft4 = *(f32 *)((u8 *)arg1 + 8);
    temp_fv1 = *(f32 *)((u8 *)arg1 + 0xC);
    if (((temp_fv1 * *(f32 *)((u8 *)arg0 + 0xC)) + ((*(f32 *)((u8 *)arg0 + 0) * temp_fa0) + (*(f32 *)((u8 *)arg0 + 4) * temp_fa1) + (*(f32 *)((u8 *)arg0 + 8) * temp_ft4))) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0) = (f32) -temp_fa0;
        *(f32 *)((u8 *)arg1 + 4) = (f32) -temp_fa1;
        *(f32 *)((u8 *)arg1 + 8) = (f32) -temp_ft4;
        *(f32 *)((u8 *)arg1 + 0xC) = (f32) -temp_fv1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15049C40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_15049C40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_15049CB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_15049EDC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504A140 CURRENT (4804) */
void func_1504A140(void *arg0, void *arg1) {
    f32 sp44;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_ft3;

    temp_fs0 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 4);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0xC);
    temp_ft1 = 2.0f / ((temp_fa0 * temp_fa0) + ((temp_fs0 * temp_fs0) + (temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1)));
    temp_ft5 = temp_fv0 * temp_ft1;
    sp44 = temp_ft1;
    temp_ft4 = temp_fv1 * temp_ft1;
    temp_fa1 = temp_fa0 * temp_ft1;
    sp34 = temp_fs0 * temp_ft5;
    sp30 = temp_fs0 * temp_ft4;
    sp2C = temp_fs0 * temp_fa1;
    temp_ft3 = temp_fv0 * temp_fa1;
    sp28 = temp_fv0 * temp_ft5;
    sp24 = temp_fv0 * temp_ft4;
    sp20 = temp_ft3;
    temp_ft0 = temp_fa0 * temp_fa1;
    sp1C = temp_fv1 * temp_ft4;
    sp18 = temp_fv1 * temp_fa1;
    sp14 = temp_ft0;
    *(f32 *)((u8 *)arg1 + 0) = (f32) (1.0f - (sp1C + sp14));
    *(f32 *)((u8 *)arg1 + 4) = (f32) (sp24 + sp2C);
    *(f32 *)((u8 *)arg1 + 8) = (f32) (temp_ft3 - sp30);
    *(f32 *)((u8 *)arg1 + 0x10) = (f32) (sp24 - sp2C);
    *(f32 *)((u8 *)arg1 + 0x18) = (f32) (sp18 + sp34);
    *(f32 *)((u8 *)arg1 + 0x14) = (f32) (1.0f - (sp28 + temp_ft0));
    *(f32 *)((u8 *)arg1 + 0x24) = (f32) (sp18 - sp34);
    *(f32 *)((u8 *)arg1 + 0x20) = (f32) (sp20 + sp30);
    *(f32 *)((u8 *)arg1 + 0xC) = 0.0f;
    *(f32 *)((u8 *)arg1 + 0x1C) = 0.0f;
    *(f32 *)((u8 *)arg1 + 0x2C) = 0.0f;
    *(f32 *)((u8 *)arg1 + 0x3C) = 1.0f;
    *(f32 *)((u8 *)arg1 + 0x28) = (f32) (1.0f - (sp28 + sp1C));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504A140 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_1504A140.s")
