#include "types.h"

/*
 * Reviewed source unit: src/game/game_10D7B0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E0300
 * - func_150E0348
 * - func_150E03F8
 * - func_150E05F8
 * - func_150E06D8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E0300.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E0348.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E03F8.s")
extern f32 D_800A0FD0;
extern f32 D_800A0FD4;
extern void *D_800DBFF0;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E05F8 CURRENT (970) */
void func_150E05F8(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_v0;

    temp_fv1 = *(f32 *)((u8 *)D_800DBFF0 + 0x300) - (f32) *(s16 *)((u8 *)arg0 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)D_800DBFF0 + 0x2F8) - (f32) *(s16 *)((u8 *)arg0 + 0x10);
    temp_fa1 = *(f32 *)((u8 *)D_800DBFF0 + 0x2FC) - (f32) *(s16 *)((u8 *)arg0 + 0x12);
    temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + ((temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1)));
    if (temp_fv0 <= D_800A0FD0) {
        var_v0 = 0xFF;
    } else if (D_800A0FD4 <= temp_fv0) {
        var_v0 = 0;
    } else {
        var_v0 = (s32) (255.0f - ((temp_fv0 - D_800A0FD0) * (1.0f / (D_800A0FD4 - D_800A0FD0)) * 255.0f));
    }
    *(s8 *)((u8 *)arg0 + 0x8A) = (s8) var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E05F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E05F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E06D8.s")
