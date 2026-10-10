#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FE9E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D1530
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1509BE40(s32, ...);
extern f32 D_800A08D0, D_800A08D4;
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D1530 CURRENT (2195) */
void func_150D1530(void *arg0) {
    u8 *actor;
    f32 savedFraction;
    register f32 fraction;
    register f32 clamped;
    register f32 amount;
    f32 vertical;
    f32 first, second;
    s32 result;
    s32 flags;

    actor = arg0;
    if (*(s32 *)(actor + 0x2C) != 0x40) {
        if (*(s32 *)(actor + 0x5F0) & 0x80) {
            clamped = 0.0f;
            amount = *(f32 *)(*(u8 **)(actor + 0x3D0) + 0x3C);
            if (amount < 0.0f) {
            } else if (amount > 170.0f) {
                clamped = 170.0f;
            } else {
                clamped = amount;
            }
            fraction = clamped * D_800A08D0;
            savedFraction = fraction;
            if (func_15123934(actor, 8, 0, *(s32 *)(actor + 0x134), 3)) {
                flags = *(s32 *)(actor + 0x84) | 0x01300080;
                *(s32 *)(actor + 0x84) = flags;
                *(s32 *)(actor + 0x84) = flags & ~6;
                *(s16 *)(actor + 0x1B4) = 1;
                *(s16 *)(actor + 0x1E0) = 2;
            }
            fraction = savedFraction;
            vertical = 34.0f * fraction + 75.0f;
            *(f32 *)(actor + 0x374) = -194.0f * fraction + 280.0f;
            *(f32 *)(actor + 0x348) = vertical;
            *(f32 *)(actor + 0x34C) = vertical;
            if (D_800BE9F0 == 0x32) {
                savedFraction = fraction;
                result = func_1509BE40(4, actor[0x23D] | 0x2000, 0xAC, 0x4027, 0x4035, 0x4036, 0x4037);
            } else {
                savedFraction = fraction;
                result = func_1509BE40(5, actor[0x23D] | 0x2000, 0xAC, 0x400A, 0x400B, 0x400C, 0x400D, 0x400E);
            }
            if (result) {
                *(s32 *)(actor + 0x84) |= 0x10000000;
            } else {
                if ((*(u8 **)(actor + 0x3D0))[0x81]) {
                    *(f32 *)(actor + 0x190) = -30.0f;
                } else {
                    *(f32 *)(actor + 0x190) = 123.0f;
                }
                *(s32 *)(actor + 0x84) &= 0xEFFFFFFF;
            }
            fraction = savedFraction;
            amount = D_800A08D4 * fraction + 10.0f;
            *(f32 *)(actor + 0x1A8) = amount;
            *(f32 *)(actor + 0x1A4) = amount;
            if (actor[0x23C]) {
                first = *(f32 *)(actor + 0x1A4);
                second = *(f32 *)(actor + 0x1A8);
                *(f32 *)(actor + 0x1A4) = first;
                *(f32 *)(actor + 0x1A8) = second;
            }
        } else if (func_151239CC(actor, 3)) {
            *(f32 *)(actor + 0x1A8) = 0.0f;
            *(f32 *)(actor + 0x1A4) = 0.0f;
            *(f32 *)(actor + 0x190) = 0.0f;
        }
        if (D_800BE9F0 == 0x32) {
            if (func_1509BE40(1, 0x4039, 6, 0x9000)) {
                *(s32 *)(actor + 0x84) |= 0x1000;
                return;
            }
            *(s32 *)(actor + 0x84) &= ~0x1000;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D1530 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FE9E0/func_150D1530.s")
