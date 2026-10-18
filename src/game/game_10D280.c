#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_10D280.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DFDD0
 * - func_150DFEFC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[0x13];
    s8 state;
    u8 pad14[0x10];
    s8 **commands;
} Game10D280Object;

typedef struct {
    u8 pad0[0x2D8];
    f32 timer;
    f32 scale;
    u8 pad2E0[0xC];
    s32 active;
} Game10D280State;

extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DFDD0 CURRENT (1395) */
s32 func_150DFDD0(Game10D280Object *arg0, Game10D280State *arg1) {
    f32 timer;
    f32 intensity;
    s32 index;
    s32 tile;
    volatile s8 *commands;
    u32 *command;

    if (arg1->active != 0) {
        arg0->state = 2;
        arg1->timer = arg1->timer - D_800BE9A4;
        timer = arg1->timer;
        if (timer < 0.0f) {
            arg1->active = 0;
            return 1;
        }
        intensity = 1.0f - (arg1->scale * timer);
    } else {
        intensity = 0.0f;
        arg0->state = 0;
    }

    commands = *arg0->commands;
    if (commands != 0) {
        index = 0;
        if (*commands != -0xE) {
            do {
                index++;
            } while (*(commands + (index * 8)) != -0xE);
        }
        command = (u32 *) ((s8 *) commands + (index * 8));
        tile = 2 - ((s32) ((*command >> 12) & 0xFFF) / 3);
        if (tile < 0) {
            do {
                tile += 0x40;
            } while (tile < 0);
        }
        *command = (((s32) ((500.0f * intensity) + 2.0f) & 0xFFF) << 12) |
                   0xF2000000 | (tile & 0xFFF);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DFDD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D280/func_150DFDD0.s")
typedef struct Game10D280Parent {
    s32 active;
    u8 pad4[0x10];
    f32 position[3];
    u8 pad20[0x1B];
    u8 generation;
} Game10D280Parent;
typedef struct Game10D280EffectState {
    Game10D280Parent *parent;
    u8 generation, pad5;
    s16 lightTimer, particleTimer, ringTimer;
} Game10D280EffectState;
typedef struct Game10D280Effect {
    u8 pad0, kind;
    u8 pad2[0xA];
    u8 flags, padD;
    s16 life;
    u8 pad10[0x18];
    Game10D280EffectState state;
} Game10D280Effect;
typedef struct Game10D280Light {
    u8 type;
    s8 mode;
    s16 duration;
    u8 flags;
} Game10D280Light;

f32 func_150ADA68(void);
void func_15107700(void *, s16, s16, s16, s32, f32, f32, s32, s32, u8 *, s32, s32);
void func_15107B78(void *, s16, s16, u8, s32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DFEFC CURRENT (110) */
void func_150DFEFC(Game10D280Effect *arg0) {
    Game10D280EffectState *state;
    Game10D280Parent *parent;
    Game10D280Light light;
    s32 position[3];
    s8 count;
    u8 color[4];
    u32 pitch, yaw;

    parent = arg0->state.parent;
    state = &arg0->state;
    if (parent->active == 0 || parent->generation != state->generation) {
        arg0->life = -1;
        return;
    }
    state->lightTimer -= D_800BE9E4;
    if (state->lightTimer < 0) {
        position[0] = parent->position[0];
        position[1] = parent->position[1];
        position[2] = parent->position[2];
        light.type = 3;
        light.mode = -1;
        light.duration = func_150ADA20() % 11U + 5;
        light.flags = 0;
        func_151602C0(&light.type, position, func_150ADA20() % 121U + 50,
                       255, 255, 255, 255, 0, 0, arg0->flags, arg0->kind);
        state->lightTimer = func_150ADA20() % 81U + 69;
    }
    state->particleTimer -= D_800BE9E4;
    if (state->particleTimer < 0) {
        count = func_150ADA20() % 3U + 2;
        do {
            color[0] = 0xAE;
            color[1] = 0xD2;
            color[2] = 0xFF;
            color[3] = func_150ADA20() % 61U + 150;
            yaw = func_150ADA20();
            pitch = func_150ADA20();
            func_15107700(parent, (s16)(yaw & 255), (s16)(pitch % 129U - 63),
                           (s16)(func_150ADA20() % 21U + 10), 4, 40.0f,
                           func_150ADA68() * 20.0f + 25.0f, 0, 2, color,
                           arg0->flags, arg0->kind);
            count--;
        } while (count > 0);
        state->particleTimer = func_150ADA20() % 141U + 25;
    }
    state->ringTimer -= D_800BE9E4;
    if (state->ringTimer < 0) {
        pitch = func_150ADA20();
        func_15107B78(parent, (s16)(pitch & 255),
                       (s16)((func_150ADA20() & 127) - 64), arg0->flags, arg0->kind);
        state->ringTimer = func_150ADA20() % 26U + 15;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DFEFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D280/func_150DFEFC.s")

void func_150E02C0(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
