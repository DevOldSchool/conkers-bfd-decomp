#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E5FF0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B8B40
 * - func_151B8BE0
 * - func_151B8C54
 * - func_151B8CFC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15047D60(f32);                             /* extern */
f32 func_15144B68(f32, void *);                     /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B8B40 CURRENT (110) */
s32 func_151B8B40(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((func_15047D60(*(f32 *)((u8 *)arg0 + 0x44)) * *(f32 *)((u8 *)arg0 + 0x5C)) + *(f32 *)((u8 *)arg0 + 0x48));
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x44) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x44), arg0);
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) + (*(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B8B40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E5FF0/func_151B8B40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E5FF0/func_151B8BE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E5FF0/func_151B8C54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E5FF0/func_151B8CFC.s")
