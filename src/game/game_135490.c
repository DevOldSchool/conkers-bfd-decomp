#include "types.h"

/*
 * Reviewed source unit: src/game/game_135490.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15107FE0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150859AC(s32, s32);
s32 func_1509BE40(s32, s32, s32, s32);
void func_15123070(void *);
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15107FE0 CURRENT (315) */
void func_15107FE0(void *arg0) {
    u8 *state;
    s32 temp_t9;

    state = arg0;
    if (func_150859AC(*(u8 *)(*(u8 **)(state + 0x3D0) + 0x127), 1) == 9) {
        func_151239CC(arg0, 2);
        if (func_15123934(arg0, 8, 0, *(s32 *)(state + 0x134), 3) != 0) {
            *(s16 *)(state + 0x73C) = 0;
            temp_t9 = *(s32 *)(state + 0x84) | 0x1300000;
            *(volatile s32 *)(state + 0x84) = temp_t9;
            *(volatile s32 *)(state + 0x84) = temp_t9 & ~4;
            func_15123070(arg0);
        }
        *(s32 *)(state + 0x5F0) |= 0x800;
        *(f32 *)(state + 0x348) = 150.0f;
        *(f32 *)(state + 0x34C) = 150.0f;
        *(f32 *)(state + 0x374) = 340.0f;
        *(f32 *)(state + 0x190) = -6.0f;
    } else {
        *(s32 *)(state + 0x5F0) &= ~0x800;
    }
    if ((func_1509BE40(1, 0x401A, 6, 0x9000) != 0) ||
        (func_1509BE40(1, 0x401B, 6, 0x9000) != 0)) {
        *(s32 *)(state + 0x84) |= 0x10000;
    } else {
        *(s32 *)(state + 0x84) &= 0xFFFEFFFF;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15107FE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135490/func_15107FE0.s")
