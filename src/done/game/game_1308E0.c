#include "types.h"

/*
 * Reviewed source unit: src/game/game_1308E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 */

typedef struct {
    u8 pad00[0xAD];
    u8 state;
} Game1308E0State;

typedef struct {
    u8 pad00[0x84];
    u32 flags;
    u8 pad88[0x1B5];
    u8 event;
    u8 pad23E[0x192];
    Game1308E0State *state;
} Game1308E0Actor;

extern s32 D_800BE9F0;
s32 func_1509BE40(s32, s32, s32, s32);

void func_15103430(Game1308E0Actor *arg0) {
    s32 event;

    event = arg0->event | 0x9000;
    if (arg0->state->state == 1) {
        arg0->flags |= 0x01000000;
    } else {
        arg0->flags &= 0xFEFFFFFF;
    }
    if (D_800BE9F0 == 0x34) {
        if (func_1509BE40(1, 0x406D, 6, event)) arg0->flags |= 0x200;
        else arg0->flags &= ~0x200;
        return;
    }
    if (D_800BE9F0 == 0x30) {
        if (func_1509BE40(1, 0x403C, 6, event) || func_1509BE40(1, 0x403D, 6, event))
            arg0->flags |= 0x200;
        else arg0->flags &= ~0x200;
        return;
    }
    if (D_800BE9F0 == 0x2D) {
        if (func_1509BE40(1, 0x4053, 6, event) || func_1509BE40(1, 0x4054, 6, event) ||
            func_1509BE40(1, 0x4056, 6, event) || func_1509BE40(1, 0x4057, 6, event))
            arg0->flags |= 0x20000000;
        else arg0->flags &= 0xDFFFFFFF;
        if (func_1509BE40(1, 0x4058, 6, 0x9000) || func_1509BE40(1, 0x4059, 6, 0x9000))
            arg0->flags |= 0x80000000;
        else arg0->flags &= 0x7FFFFFFF;
        return;
    }
    if (D_800BE9F0 == 0x34) {
        if (func_1509BE40(1, 0x406E, 6, event)) arg0->flags |= 0x20000000;
        else arg0->flags &= 0xDFFFFFFF;
    }
}
