#include "types.h"

/*
 * Reviewed source unit: src/game/game_1CBE20.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1519E970
 * - func_1519EA04
 * - func_1519EA78
 * - func_1519EB8C
 * - func_1519ED24
 * - func_1519ED84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519E970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519EA04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519EA78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519EB8C.s")
extern f32 D_800A8CD8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519ED24 CURRENT (505) */
s32 func_1519ED24(void *arg0) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x170);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x18) * D_800A8CD8);
    *(f32 *)((u8 *)arg0 + 0x1C) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x1C) * D_800A8CD8);
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) *(f32 *)((u8 *)temp_v1 + 0xC);
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) *(f32 *)((u8 *)temp_v1 + 0x10);
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) *(f32 *)((u8 *)temp_v1 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) *(f32 *)((u8 *)temp_v1 + 0);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) *(f32 *)((u8 *)temp_v1 + 4);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) *(f32 *)((u8 *)temp_v1 + 8);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519ED24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519ED24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519ED84.s")
s32 func_1519EF04(void *arg0) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x110);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x18) * 10.0f);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x1C) * 10.0f);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) *(f32 *)((u8 *)temp_v1 + 0xC);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) *(f32 *)((u8 *)temp_v1 + 0x10);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) *(f32 *)((u8 *)temp_v1 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) *(f32 *)((u8 *)temp_v1 + 0);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) *(f32 *)((u8 *)temp_v1 + 4);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) *(f32 *)((u8 *)temp_v1 + 8);
    return 1;
}
