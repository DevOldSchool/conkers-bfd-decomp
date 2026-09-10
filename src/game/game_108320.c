#include "types.h"

/*
 * Reviewed source unit: src/game/game_108320.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DAE70
 * - func_150DB114
 * - func_150DB2D8
 * - func_150DB518
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DAE70.s")
extern f32 D_800A0BE4;
extern f32 D_800A0BE8;
extern f32 D_800A0BEC;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DB114 CURRENT (2465) */
s32 func_150DB114(u8 *arg0) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fa1;
    s16 temp_v1;
    u8 *var_v0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x134);
    var_v0 = (void *)(arg0 + 0x110);
    *(f32 *)((u8 *)arg0 + 0x110) = (f32) (*(f32 *)((u8 *)arg0 + 0x110) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x114) = (f32) (*(f32 *)((u8 *)arg0 + 0x114) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x118) = (f32) (*(f32 *)((u8 *)arg0 + 0x118) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + (*(f32 *)((u8 *)arg0 + 0x110) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg0 + 0x114) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + (*(f32 *)((u8 *)arg0 + 0x118) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x124) = (f32) (*(f32 *)((u8 *)arg0 + 0x124) + (*(f32 *)((u8 *)arg0 + 0x12C) * D_800BE9A4));
    if (D_800A0BE4 < *(f32 *)((u8 *)arg0 + 0x124)) {
        var_v0 = (void *)(arg0 + 0x110);
        *(f32 *)((u8 *)var_v0 + 0x14) = (f32) D_800A0BE4;
        *(f32 *)((u8 *)var_v0 + 0x1C) = (f32) -*(f32 *)((u8 *)var_v0 + 0x1C);
        var_fa1 = D_800A0BE8;
    } else {
        var_fa1 = D_800A0BEC;
        if (*(f32 *)((u8 *)var_v0 + 0x14) < var_fa1) {
            *(f32 *)((u8 *)var_v0 + 0x14) = var_fa1;
            *(f32 *)((u8 *)var_v0 + 0x1C) = (f32) -*(f32 *)((u8 *)var_v0 + 0x1C);
        }
    }
    temp_fv0_2 = *(f32 *)((u8 *)var_v0 + 0x20);
    *(f32 *)((u8 *)var_v0 + 0x18) = (f32) (*(f32 *)((u8 *)var_v0 + 0x18) + (temp_fv0_2 * D_800BE9A4));
    temp_fv1 = *(f32 *)((u8 *)var_v0 + 0x18);
    if (D_800A0BE4 < temp_fv1) {
        *(f32 *)((u8 *)var_v0 + 0x18) = (f32) D_800A0BE4;
        *(f32 *)((u8 *)var_v0 + 0x20) = (f32) -temp_fv0_2;
    } else if (temp_fv1 < var_fa1) {
        *(f32 *)((u8 *)var_v0 + 0x18) = var_fa1;
        *(f32 *)((u8 *)var_v0 + 0x20) = (f32) -temp_fv0_2;
    }
    *(f32 *)((u8 *)var_v0 + 0xC) = (f32) (*(f32 *)((u8 *)var_v0 + 0xC) + (*(f32 *)((u8 *)var_v0 + 0x10) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)var_v0 + 0xC) * *(f32 *)((u8 *)var_v0 + 0x14));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)var_v0 + 0xC) * *(f32 *)((u8 *)var_v0 + 0x18));
    temp_v1 = *(u8 *)((u8 *)arg0 + 0x5C) - *(u8 *)((u8 *)var_v0 + 0x28);
    if (temp_v1 < 0) {
        *(u8 *)((u8 *)arg0 + 0x5C) = 0U;
        return 0;
    }
    *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DB114 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DB114.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DB2D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_108320/func_150DB518.s")
