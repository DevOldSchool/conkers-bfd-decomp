#include "types.h"

/*
 * Reviewed source unit: src/game/game_43330.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15015E80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_10003C40(s32, s32, s32, s32);
extern void *D_800B0DF0;
extern s32 D_800BE9C8[2];
extern s32 D_800BEBA4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15015E80 CURRENT (2885) */
void func_15015E80(void) {
    u16 value;
    s32 next;

    value = *(u16 *)((u8 *)D_800B0DF0 + 0x1C);
    if (value == 0) {
        value = 0x1F40;
        *(u16 *)((u8 *)D_800B0DF0 + 0x1C) = value;
    }
    value = (u16)(value + 0x190);
    *(u16 *)((u8 *)D_800B0DF0 + 0x1C) = value;
    D_800BE9C8[0] = func_10003C40(value * 8, 0xFF, 2, 0);
    next = func_10003C40(value * 8, 0xFF, 2, 0);
    D_800BE9C8[1] = next;
    D_800BEBA4 = ((next - D_800BE9C8[0]) >> 3) - 0x190;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15015E80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_43330/func_15015E80.s")
