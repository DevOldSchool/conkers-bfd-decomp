#include "types.h"

/*
 * Reviewed source unit: src/game/game_143870.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151163C0
 * - func_1511650C
 * - func_15116888
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_143870/func_151163C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_143870/func_1511650C.s")
f32 func_15048A40(s32);                             /* extern */
s32 func_150490A8(f32 *, s32);                      /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15116888 CURRENT (2279) */
s32 func_15116888(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    f32 sp1C;
    f32 sp24;

    sp1C = (f32) ((s32) *(f32 *)((u8 *)arg3 + 0x14) - arg0);
    sp24 = (f32) ((s32) *(f32 *)((u8 *)arg3 + 0x1C) - arg1);
    return (s32) (*(f32 *)((u8 *)arg3 + 0x3C) * func_15048A40(((0x40 - ((s32) *(u16 *)((u8 *)arg3 + 0x76) >> 8)) - func_150490A8(&sp1C, arg0)) & 0xFF));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15116888 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_143870/func_15116888.s")
void func_15116924(s32 arg0) {

}
