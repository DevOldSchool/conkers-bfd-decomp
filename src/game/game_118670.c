#include "types.h"

/*
 * Reviewed source unit: src/game/game_118670.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EB1C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameEB1C0Actor {
    u8 pad0[0x2C];
    s32 mode;
    u8 pad30[0x54];
    u32 flags;
    u8 pad88[0xAC];
    s32 target;
    u8 pad138[0x58];
    f32 angle;
    u8 pad194[0xA9];
    u8 event;
    u8 pad23E[0x10A];
    f32 range1;
    f32 range2;
    u8 pad350[0x24];
    f32 scale;
    u8 pad378[0x58];
    u8 *selection;
    u8 pad3D4[0x21C];
    u32 state_flags;
    u8 pad5F4[0x80];
    f32 speed;
    u8 pad678[0x50];
    s32 pending;
} GameEB1C0Actor;

/* Raw helpers walk arg0 additional words after the three fixed arguments. */
s32 func_1509BE40(s32, s32, s32, ...);
s32 func_1509BFB0(s32, s32, s32, ...);
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);
void func_151254F4(void *, s32);
extern s32 D_80088A90;
extern f32 D_800A1480;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EB1C0 CURRENT (195) */
void func_150EB1C0(GameEB1C0Actor *arg0) {
    volatile s32 enabled;
    s32 other;
    u32 flags;
    f32 range;
    f32 scale;
    f32 angle;

    enabled = func_1509BE40(0, func_1509BE40(0, 0x2006, 0xB7) | 0x2000, 0xBC);
    other = func_1509BE40(0, 0x2000, 0xBB);
    if (enabled != 0 && other != 0) {
        func_1509BFB0(0, 0x405D, 1);
        func_1509BFB0(0, 0x405E, 1);
        func_1509BFB0(0, 0x405F, 1);
        func_1509BFB0(0, 0x4060, 1);
        func_1509BFB0(0, 0x4061, 1);
        if (arg0->mode != 0x100 && arg0->pending == 0) {
            if (func_15123934(arg0, 8, 0, 0, 3)) {
                flags = arg0->flags | 0x01100004;
                *(volatile u32 *)&arg0->flags = flags;
                arg0->flags = flags & ~2;
                arg0->speed = 0.0f;
                func_151254F4(arg0, arg0->selection[0x65] - 1);
                arg0->state_flags |= 0x10;
            }
            range = 320.0f;
            scale = D_800A1480;
            angle = 180.0f;
            arg0->target = 0;
            arg0->range1 = range;
            arg0->range2 = range;
            arg0->scale = scale;
            arg0->angle = angle;
            D_80088A90 = 1;
            func_1509BFB0(0, 0x405C, 0);
        }
    } else {
        if (func_151239CC(arg0, 3)) {
            arg0->angle = 0.0f;
            func_151254F4(arg0, arg0->event);
            arg0->state_flags &= ~0x10;
            arg0->speed = 0.0f;
            D_80088A90 = 0;
        }
        func_1509BFB0(0, 0x405C, 1);
        func_1509BFB0(0, 0x405D, 0);
        func_1509BFB0(0, 0x405E, 0);
        func_1509BFB0(0, 0x405F, 0);
        func_1509BFB0(0, 0x4060, 0);
        func_1509BFB0(0, 0x4061, 0);
        if (func_1509BE40(1, 0x4040, 6, 0x9000)) {
            arg0->flags |= 0x80;
            return;
        }
        arg0->flags &= ~0x80;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EB1C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_118670/func_150EB1C0.s")
