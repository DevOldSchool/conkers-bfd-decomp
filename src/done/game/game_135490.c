#include "types.h"

/*
 * Reviewed source unit: src/game/game_135490.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 */

s32 func_150859AC(s32, s32);
s32 func_1509BE40(s32, s32, s32, s32);
void func_15123070(void *);
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);

void func_15107FE0(void *arg0) {
    u8 *state;

    state = arg0;
    if (func_150859AC(*(u8 *)(*(u8 **)(state + 0x3D0) + 0x127), 1) == 9) {
        func_151239CC(arg0, 2);
        if (func_15123934(arg0, 8, 0, *(s32 *)(state + 0x134), 3) != 0) {
            *(s16 *)(state + 0x73C) = 0;
            *(s32 *)(state + 0x84) |= 0x1300000;
            *(s32 *)(state + 0x84) = *(s32 *)(state + 0x84) & ~4;
            func_15123070(arg0);
        }
        *(f32 *)(state + 0x348) = 150.0f;
        *(f32 *)(state + 0x34C) = 150.0f;
        *(f32 *)(state + 0x374) = 340.0f;
        *(f32 *)(state + 0x190) = -6.0f;
        *(s32 *)(state + 0x5F0) |= 0x800;
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
