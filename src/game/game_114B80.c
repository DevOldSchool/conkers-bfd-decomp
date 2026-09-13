#include "types.h"

/*
 * Reviewed source unit: src/game/game_114B80.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E76D0
 * - func_150E7994
 * - func_150E7C9C
 * - func_150E7FEC
 * - func_150E81A8
 * - func_150E83AC
 * - func_150E8470
 * - func_150E8854
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E76D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E7994.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E7C9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E7FEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E81A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E83AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E8470.s")
void func_15131828(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_150E8824(s32 arg0, s32 arg1) {
    func_15131828(arg0, arg0 + 0xAC, arg0 + 0xA8, arg0 + 0xAA);
    return 1;
}

void func_10022EC0(void *, void *, s32);
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E8854 CURRENT (9) */
void func_150E8854(void) {
    f32 value;
    u8 *object;

    value = 10.0f;
    object = func_15149130(0x12C, -1, 0x35, -1, 0, 0, 4, 0xFF, 1);
    if (object != 0) {
        func_10022EC0(object + 0x28, &value, 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E8854 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E8854.s")
