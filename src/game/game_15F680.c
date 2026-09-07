#include "types.h"

/*
 * Reviewed source unit: src/game/game_15F680.c
 * Boundary evidence: docs/evidence/game_raw_clipping_resource_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151321D0
 * - func_151323AC
 * - func_151323F8
 * - func_15132444
 * - func_1513259C
 * - func_151325C8
 * - func_1513264C
 * - func_15132A4C
 * - func_15132A88
 * - func_15132B80
 * - func_15132DDC
 * - func_151332DC
 * - func_15133510
 * - func_15133588
 * - func_151336A8
 * - func_15133760
 * - func_151337C0
 * - func_15133894
 * - func_151339D4
 * - func_15133A50
 * - func_15133A94
 * - func_15133B98
 * - func_15133C58
 * - func_15133D20
 * - func_15133DE8
 * - func_15133E3C
 * - func_15133E84
 * - func_15133EB8
 * - func_15133EEC
 * - func_15133FD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151321D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151323AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151323F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132444.s")
void func_15132570(s32 arg0) {
    func_15132444(arg0);
    func_15169804(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_1513259C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151325C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_1513264C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132A4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132A88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132B80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132DDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151332DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133510.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133588.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151336A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133760.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151337C0 CURRENT (325) */
s32 func_151337C0(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x5C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x48);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + ((temp_fv1 * D_800BE9A4) + (D_800BE9A4 * temp_fa0 * D_800BE9A4 * 0.5f)));
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (temp_fv1 + (temp_fa0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) + (*(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151337C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151337C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133894.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151339D4 CURRENT (275) */
s32 func_151339D4(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) + arg4);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) * -temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * temp_fv0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151339D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151339D4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15133A50 CURRENT (460) */
s32 func_15133A50(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x48) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x50) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x54) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) + arg4);
    *(f32 *)((u8 *)arg0 + 0x58) = 0.0f;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15133A50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133A94.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15133B98 CURRENT (3897) */
s32 func_15133B98(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_ft1;
    f32 temp_ft5;

    temp_ft5 = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) * -temp_ft5);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) + arg4);
    temp_ft1 = fabsf(*(f32 *)((u8 *)arg0 + 0x48));
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) * temp_ft5);
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) * temp_ft5);
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) * temp_ft5);
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) * temp_ft5);
    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * temp_ft5);
    if (temp_ft1 < 4.0f) {
        *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) & ~0x69);
        *(f32 *)((u8 *)arg0 + 0x48) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x50) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x54) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x58) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x5C) = 0.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15133B98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133B98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133C58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133D20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133DE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133E3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133E84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133EB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133EEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133FD8.s")
