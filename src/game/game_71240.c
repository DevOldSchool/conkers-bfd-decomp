#include "types.h"

/*
 * Reviewed source unit: src/game/game_71240.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15043D90
 * - func_15043E68
 * - func_15043F6C
 * - func_15043FF0
 * - func_150440A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_71240/func_15043D90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71240/func_15043E68.s")
void func_15043EC8(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    *(f32 *)((u8 *)arg0 + 0x30) = arg4;
    *(f32 *)((u8 *)arg0 + 0x34) = arg5;
    *(f32 *)((u8 *)arg0 + 0x38) = arg6;
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) * arg2);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) * arg2);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) * arg2);
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) * arg3);
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) * arg3);
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) * arg3);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_71240/func_15043F6C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15043FF0 CURRENT (710) */
void func_15043FF0(void *arg0, void *arg1) {
    *(f32 *)((u8 *)arg0 + 0) = (f32) *(s16 *)((u8 *)arg1 + 0x18);
    *(f32 *)((u8 *)arg0 + 4) = (f32) *(s16 *)((u8 *)arg1 + 0x1A);
    *(f32 *)((u8 *)arg0 + 8) = (f32) *(s16 *)((u8 *)arg1 + 0x1C);
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + ((f32) *(s16 *)((u8 *)arg1 + 0x38) * 0.000015258789f));
    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + ((f32) *(s16 *)((u8 *)arg1 + 0x3A) * 0.000015258789f));
    *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + ((f32) *(s16 *)((u8 *)arg1 + 0x3C) * 0.000015258789f));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15043FF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71240/func_15043FF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71240/func_150440A0.s")
