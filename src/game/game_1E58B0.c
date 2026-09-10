#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E58B0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B8400
 * - func_151B85AC
 * - func_151B863C
 * - func_151B8668
 * - func_151B86F4
 * - func_151B8908
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B8400.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B85AC CURRENT (105) */
s32 func_151B85AC(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x110);
    if (temp_v0 != 0) {
        *(s32 *)((u8 *)arg0 + 0x34) = (s32) *(s32 *)((u8 *)temp_v0 + 0x38);
        *(s32 *)((u8 *)arg0 + 0x38) = (s32) *(s32 *)((u8 *)temp_v0 + 0x3C);
        *(s32 *)((u8 *)arg0 + 0x3C) = (s32) *(s32 *)((u8 *)temp_v0 + 0x40);
        *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    } else {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 1);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B85AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B85AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B863C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B8668.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B86F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B8908.s")
