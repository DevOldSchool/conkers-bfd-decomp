#include "types.h"

/*
 * Reviewed source unit: src/game/game_E8C10.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BB760
 * - func_150BBB5C
 * - func_150BC488
 * - func_150BCBBC
 * - func_150BCFB8
 * - func_150BD070
 * - func_150BD740
 * - func_150BD954
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BB760.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BBB5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BC488.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BCBBC.s")
extern f32 D_8009FEF8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BCFB8 CURRENT (2300) */
s32 func_150BCFB8(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x48);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10) * D_8009FEF8) + arg4);
    if (temp_fv0 > -2.0f) {
        *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) & ~0x6F);
        *(f32 *)((u8 *)arg0 + 0x48) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
        return 1;
    }
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (-temp_fv0 * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * temp_fv1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BCFB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BCFB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BD070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BD740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BD954.s")
s32 func_150BDB3C(void *arg0) {
    s32 temp_t6;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    if (temp_t6 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
        *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) temp_t6;
    }
    return 1;
}
