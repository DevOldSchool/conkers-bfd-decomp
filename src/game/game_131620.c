#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_131620.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151041E4
 * - func_1510448C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game131620Effect {
    u8 pad0[0x10];
    s32 field_10;
    s32 field_14;
    s16 field_18;
    s8 field_1A;
    s8 field_1B;
    s8 field_1C;
    u8 pad1D[3];
} Game131620Effect;

Game131620Effect *func_15167A68(s32, s32, s32, s32, u8, u8);

void func_15104170(s32 arg0, s32 arg1, s32 arg2) {
    Game131620Effect *effect;

    effect = func_15167A68(0x64, 0, sizeof(*effect), 0, 0xFF, 1);
    if (effect != 0) {
        effect->field_18 = 0xF;
        effect->field_1A = 0;
        effect->field_1B = 0;
        effect->field_10 = arg1;
        effect->field_14 = arg2;
        effect->field_1C = arg0;
    }
}
typedef struct Game131620Frame {
    u8 pad0[8];
    f32 value;
} Game131620Frame;
typedef struct Game131620Camera {
    u8 pad0[0x674];
    f32 field674;
} Game131620Camera;
typedef struct Game131620Actor {
    u8 pad0[0x13F];
    u8 index13F;
    u8 pad140[0x190];
    Game131620Frame *frame2D0;
    u8 pad2D4[0x44];
    Game131620Camera *camera318;
} Game131620Actor;

void func_100176C4(void);
s32 func_10010F30(s32, s32, s32, s32, s32);
void func_1000E2F4(s32);
void func_151D66F0(s32, s32);
void func_151254F4(void *, s32);
extern s32 D_800BE9E4, D_800BEA08;
extern s8 D_800BEA0C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151041E4 CURRENT (2306) */
void func_151041E4(Game131620Effect *arg0) {
    Game131620Actor *source;
    Game131620Actor *owner;
    Game131620Actor *laterOwner;
    Game131620Frame *animation;
    register s32 amount;
    s32 step;
    s32 trigger;
    register s32 mode;
    register s32 timer;
    f32 frame;
    s32 tick;

    switch ((u8)arg0->field_1A) {
    case 0:
        animation = ((Game131620Actor *)arg0->field_10)->frame2D0;
        mode = (u8)arg0->field_1C;
        trigger = 0;
        frame = animation->value;
        if (mode == 0) {
            if (frame >= 19.0f) {
                goto trigger_effect;
            }
        } else if (mode == 1) {
            tick = D_800BE9E4;
            timer = (u16)arg0->field_18;
            if (tick < timer) {
                arg0->field_18 = timer - tick;
            } else {
trigger_effect:
                trigger = 1;
            }
        }
        mode = 1;
        if (trigger != 0) {
            source = (void *)arg0->field_14;
            owner = (void *)arg0->field_10;
            arg0->field_1A = mode;
            D_800BEA0C = mode;
            func_100176C4();
            func_10010F30(0x5B2, 0x7FFF, 0, 0, 0);
            func_10010F30(0x5B2, 0x7FFF, 127, -100, 0);
            func_10010F30(0x5B2, 0x7FFF, 0, 0, 0);
            func_10010F30(0x5B2, 0x7FFF, 127, -100, 0);
            func_151D66F0(210, 2);
            func_151254F4(owner->camera318, source->index13F);
            owner->camera318->field674 = 0.0f;
        }
        break;
    case 1:
        amount = (u8)arg0->field_1B;
        step = D_800BEA08 * 10;
        amount += step;
        if (amount >= 255) {
            *(u8 *)&arg0->field_1B = 255;
            arg0->field_1A = 2;
            arg0->field_18 = 180;
        } else {
            arg0->field_1B = amount;
        }
        break;
    case 2:
        tick = D_800BEA08;
        timer = (u16)arg0->field_18;
        if (tick < timer) {
            arg0->field_18 = timer - tick;
        } else {
            D_800BEA0C = 0;
            laterOwner = (void *)arg0->field_10;
            func_1000E2F4(0);
            func_151254F4(laterOwner->camera318, laterOwner->index13F);
            laterOwner->camera318->field674 = 0.0f;
            arg0->field_1A = 3;
        }
        break;
    case 3:
        amount = (u8)arg0->field_1B;
        step = D_800BEA08 * 10;
        amount -= step;
        if (amount <= 0) {
            func_1516972C((u8 *)arg0);
            func_151D66F0(0, 0);
        } else {
            func_151D66F0((amount * 210) >> 8, 2);
            arg0->field_1B = amount;
        }
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151041E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_151041E4.s")

typedef struct Game131620ScaleState {
    u8 pad0[0x1B];
    u8 scale;
} Game131620ScaleState;

s32 func_1517F08C(s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510448C CURRENT (30) */
s32 func_1510448C(s32 arg0, Game131620ScaleState * volatile arg1, s16 arg2) {
    s32 temp_v0;
    Game131620ScaleState *state;

    state = arg1;
    if ((arg2 != 0) || ((temp_v0 = state->scale) == 0)) {
        return arg0;
    }
    return func_1517F08C(arg0, (temp_v0 * 0x3F) >> 8, 0, 0, 0, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510448C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_1510448C.s")
extern void *D_800CC5EC;

u8 func_151044F4(void) {
    if (D_800CC5EC != 0) {
        return *(u8 *)((u8 *)D_800CC5EC + 0x7D);
    }
    return 0U;
}
