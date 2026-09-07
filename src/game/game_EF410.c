#include "types.h"

/*
 * Reviewed source unit: src/game/game_EF410.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C1F60
 * - func_150C2290
 * - func_150C2424
 * - func_150C251C
 * - func_150C2558
 * - func_150C2700
 * - func_150C2804
 * - func_150C2898
 * - func_150C29F0
 * - func_150C2C00
 * - func_150C2FCC
 * - func_150C308C
 * - func_150C3160
 * - func_150C3230
 * - func_150C3574
 * - func_150C3994
 * - func_150C3D5C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C1F60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2290.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2424.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C251C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2558.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2700.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2804.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2898.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C29F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2C00.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C2FCC CURRENT (465) */
s32 func_150C2FCC(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x150);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x50);
    temp_ft5 = *(f32 *)((u8 *)arg0 + 0x4C);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + ((temp_fa1 * D_800BE9A4) + (0.5f * temp_ft5 * D_800BE9A4 * D_800BE9A4)));
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (temp_fa1 + (temp_ft5 * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x2C) < 10.0f) || (*(f32 *)((u8 *)arg0 + 0x30) < 10.0f)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C2FCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2FCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C308C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3160.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3230.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3574.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3994.s")
s32 func_150C3D48(s32 arg0) {
    return arg0 + 0xEDCBA988;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3D5C.s")
