#include "types.h"

/*
 * Reviewed source unit: src/game/effects/colourframebuffer.c
 * Boundary evidence: docs/evidence/effects_colourframebuffer.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515FDA0
 * - func_1515FF74
 * - func_1515FFEC
 * - func_151600D8
 * - func_15160274
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_1515FDA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_1515FF74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_1515FFEC.s")
extern void (*D_8008B0E4[])(void *, s32, u8);

void func_15160090(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008B0E4[*(u8 *)((u8 *)arg0 + 0x14)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_151600D8.s")
void func_15169260(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_800A6670;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15160274 CURRENT (650) */
void func_15160274(s32 arg0, u8 arg1) {
    s32 sp1C;

    sp1C = D_800A6670;
    func_15169260(&sp1C, 1, arg0, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15160274 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_15160274.s")
