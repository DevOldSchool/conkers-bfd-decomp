#include "types.h"

/*
 * Reviewed source unit: src/game/game_11FB50.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_model_owner_mode_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F2994
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);
s32 func_1509BE40(s32, ...);
void func_15124B18(u8 *);
void func_15128774(void *, void *);
void func_150F2994(s32, s32);

void func_150F26A0(u8 *actor) {
    u8 *state;
    s32 mode;

    state = *(u8 **)(actor + 0x3D0);
    if (state[0x102] != 0 && state[0x104] == 0) {
        func_150F2994((s32)actor, 1);
        if (*(s32 *)(actor + 0x2C) != 0x100 && *(s32 *)(actor + 0x6C8) == 0) {
            if (func_15123934(actor, 0x80, 0, 0, 3) != 0) {
                *(u32 *)(actor + 0x84) |= 0x300400;
                *(u32 *)(actor + 0x84) &= ~6U;
                *(s16 *)(actor + 0x1B4) = 1;
                *(s16 *)(actor + 0x1E0) = 3;
                func_15124B18(actor);
            }
            *(f32 *)(actor + 0x348) = 29.0f;
            *(f32 *)(actor + 0x34C) = 29.0f;
            *(f32 *)(actor + 0x374) = 200.0f;
            *(f32 *)(actor + 0x190) = -19.0f;
            if (actor[0x3E8] == 0) {
                if (0.5f * *(f32 *)(actor + 0x374) <
                    *(f32 *)(actor + 0x370) - *(f32 *)(actor + 0x374)) {
                    func_15128774(actor, *(u8 **)(actor + 0x3D0));
                }
            }
        }
    } else {
        state[7] = 0xFF;
        if (actor[0x23E] == 0x3B) {
            func_150F2994((s32)actor, 1);
            if (*(s32 *)(actor + 0x2C) != 0x100 && *(s32 *)(actor + 0x6C8) == 0) {
                if (func_15123934(actor, 8, 0, 0, 3) != 0) {
                    *(u32 *)(actor + 0x84) |= 0x300000;
                    *(u32 *)(actor + 0x84) &= ~4U;
                    *(s16 *)(actor + 0x1B4) = 1;
                    *(s16 *)(actor + 0x1E0) = 3;
                }
                *(s32 *)(actor + 0x134) = 0;
                *(f32 *)(actor + 0x348) = 125.0f;
                *(f32 *)(actor + 0x34C) = 125.0f;
                *(f32 *)(actor + 0x374) = 220.0f;
                *(f32 *)(actor + 0x190) = 30.0f;
            }
        } else {
            mode = *(s32 *)(actor + 0x2C);
            if ((mode == 8 || mode == 0x80) && *(s32 *)(actor + 0x6C8) == 0) {
                func_151239CC(actor, 3);
            }
            if (*(s16 *)(actor + 0x1B4) == 1) {
                *(s16 *)(actor + 0x1B4) = 2;
                func_15124B18(actor);
            }
            func_150F2994((s32)actor, 0);
        }
    }
    if (func_1509BE40(1, 0x405A, 6, 0x9000) != 0) {
        *(u32 *)(actor + 0x84) |= 0x80000000;
    } else {
        *(u32 *)(actor + 0x84) &= 0x7FFFFFFF;
    }
    if (func_1509BE40(1, 0x405E, 6, 0x9000) != 0) {
        *(u32 *)(actor + 0x84) |= 0x10000;
    } else {
        *(u32 *)(actor + 0x84) &= 0xFFFEFFFF;
    }
    if (func_1509BE40(1, 0x405F, 6, 0x2000) != 0) {
        *(u32 *)(actor + 0x84) |= 0x10;
        return;
    }
    *(u32 *)(actor + 0x84) &= ~0x10U;
}
void func_1509BFB0(s32, s32, s32);
extern void *D_800D2E4C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F2994 CURRENT (300) */
void func_150F2994(s32 arg0, s32 arg1) {
    register s32 index;
    register s32 limit;
    register s32 saved_arg1;

    saved_arg1 = arg1;
    index = 0;
    limit = 0xE;
    do {
        func_1509BFB0(0, index + 0x4016, saved_arg1);
        index += 1;
    } while (index != limit);
    func_1509BFB0(0, 0x405D, saved_arg1);
    func_1509BFB0(0, 0x405F, saved_arg1);
    if (*(u8 *)((u8 *)D_800D2E4C + 0x15) & 8) {
        func_1509BFB0(0, 0x4063, saved_arg1);
        func_1509BFB0(0, 0x4064, saved_arg1);
        func_1509BFB0(0, 0x4065, saved_arg1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F2994 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11FB50/func_150F2994.s")
