#include "types.h"

/*
 * Reviewed source unit: src/game/game_11C2B0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EEE00
 * - func_150EEF40
 * - func_150EEF80
 * - func_150EF38C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EEE00.s")
extern void func_151403A8(void *arg0, s32 arg1, void *arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EEF40 CURRENT (440) */
void func_150EEF40(void *arg0, s32 arg1) {
    struct {
        void *field0;
        u8 field4;
        u8 field5;
    } sp18;

    sp18.field0 = arg0;
    sp18.field5 = arg1 & 0xFF;
    sp18.field4 = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151403A8(&sp18, 0x43, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EEF40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EEF40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EEF80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EF38C.s")
s32 func_150EF784(void *arg0, s32 arg1, s32 arg2) {
    if (*(u8 *)((u8 *)arg0 + 4) == 0x28) {
        return 1;
    }
    return 0;
}
