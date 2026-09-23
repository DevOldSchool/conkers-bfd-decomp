#include "types.h"

/*
 * Reviewed source unit: src/game/game_1218A0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F43F0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1509BE40(s32, s32, s32, s32);
void func_1509BFB0(s32, s32, s32);
s32 func_15123934(void *, s32, s32, s32, s32);
void func_151239CC(void *, s32);
void func_15124B18(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F43F0 CURRENT (120) */
void func_150F43F0(u8 *arg0) {
    s32 flags;

    if (arg0[0x23E] == 0x3B) {
        func_1509BFB0(0, 0x405C, 1);
        if (*(s32 *)(arg0 + 0x2C) != 0x100 && *(s32 *)(arg0 + 0x6C8) == 0) {
            if (func_15123934(arg0, 8, 0, 0, 0) != 0) {
                flags = *(s32 *)(arg0 + 0x84) | 0x300000;
                *(volatile s32 *)(arg0 + 0x84) = flags;
                *(s32 *)(arg0 + 0x84) = flags & ~4;
                *(s16 *)(arg0 + 0x1B4) = 1;
                *(s16 *)(arg0 + 0x1E0) = 3;
                func_15124B18(arg0);
            }
            *(s32 *)(arg0 + 0x134) = 0;
            *(f32 *)(arg0 + 0x348) = 125.0f;
            *(f32 *)(arg0 + 0x34C) = 125.0f;
            *(f32 *)(arg0 + 0x374) = 220.0f;
            *(f32 *)(arg0 + 0x190) = 30.0f;
        } else {
            *(f32 *)(arg0 + 0x190) = 0.0f;
        }
    } else if (*(s32 *)(arg0 + 0x2C) == 8 && *(s32 *)(arg0 + 0x6C8) == 0) {
        func_151239CC(arg0, 0);
        func_1509BFB0(0, 0x405C, 0);
    }
    if (func_1509BE40(1, 0x4054, 6, 0x9000) != 0 &&
        func_1509BE40(1, 0x405E, 6, 0x9000) == 0) {
        *(s32 *)(arg0 + 0x84) |= 0x80000000;
        return;
    }
    *(s32 *)(arg0 + 0x84) &= 0x7FFFFFFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F43F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1218A0/func_150F43F0.s")
