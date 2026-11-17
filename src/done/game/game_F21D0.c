#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_F21D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 */

typedef struct GameF21D0Mover {
    f32 angle;
    u8 pad04[0xC];
    s16 field10;
    s16 field12;
    s16 field14;
    u8 pad16[0x39];
    u8 flags;
    u8 pad50[0x10];
    f32 velocity;
    u8 pad64[0x18];
    s32 timer;
} GameF21D0Mover;

s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800BE9E4;

void func_150C4D20(GameF21D0Mover *arg0) {
    f32 velocity;
    f32 angle;
    f32 wave;
    s32 timer;

    angle = arg0->angle;
    velocity = arg0->velocity;
    if (angle > 180.0f) {
        angle -= 360.0f;
    }
    timer = arg0->timer;
    timer += D_800BE9E4;
    velocity -= angle * 0.009f;
    if (timer >= 256.0f) {
        timer -= 256.0f;
        func_10010F88(0xF, 0x55F0U, 0, 0, 0, arg0->field10, arg0->field12, arg0->field14, 0x1F4, 0x3E8);
    }
    arg0->timer = timer;
    wave = func_15048A40(timer);
    velocity += wave * 0.1f;
    if ((arg0->flags & 4) == 4) {
        velocity += 0.1f;
    }
    velocity *= 0.8f;
    arg0->velocity = velocity;
    arg0->angle = arg0->angle + velocity;
    angle = arg0->angle;
    if (angle < 0.0f) {
        arg0->angle = angle + 360.0f;
        return;
    }
    if (angle >= 360.0f) {
        arg0->angle = angle - 360.0f;
    }
}
typedef struct GameF21D0ScrollState {
    s32 enabled;
    s16 initialPhase;
    u8 pad6[2];
    f32 speed;
    f32 remainder;
} GameF21D0ScrollState;

void *func_10003C40(s32, s32, s32, s32);
s32 func_1511A410(s8 *, s32 *);
s32 func_1510D0EC(s32, s32 *, s32, s32);
void func_1510D874(s32, s32, s32, s32, s32);
extern u8 D_1C0[], D_2C1[];
extern u8 D_800BE9C0;

typedef struct GameF21D0Vertex {
    s16 ob[3];
    u16 flag;
    s16 tc[2];
    u8 cn[4];
} GameF21D0Vertex;

void func_150C4E9C(u8 *arg0) {
    u8 *resource;
    s32 limit;
    GameF21D0ScrollState *initialState;
    s32 adjustment;
    GameF21D0ScrollState *state;
    s32 mode;
    s32 index;
    s32 result;

    mode = arg0[0x73] & 3;
    initialState = *(GameF21D0ScrollState **)(arg0 + 0x7C);
    if (initialState == NULL) {
        state = func_10003C40(0x10, 1, 0, 0);
        *(GameF21D0ScrollState **)(arg0 + 0x7C) = state;
        func_1511A410(*(s8 **)(arg0 + 0x1C), (s32 *)state);
        state->initialPhase = (*(GameF21D0Vertex **)(arg0 + 0x28))->tc[1];
        state->speed = 0;
        state->remainder = 0;
    } else {
        state = initialState;
    }
    if (mode == 0 || mode == 2) {
        resource = D_2C1;
    } else {
        resource = D_1C0;
    }
    if (mode == 0 || mode == 3) {
        state->speed = 0;
        state->remainder = 0;
    } else if (mode == 2) {
        if (state->speed < 300.0f) {
            state->speed = state->speed + 25.0f * (f32)D_800BE9E4;
        } else {
            state->speed = 300.0f;
        }
    } else if (mode == 1) {
        s32 phase;
        s32 initialPhase;

        if (state->speed > 100.0f) {
            state->speed = state->speed - 25.0f * (f32)D_800BE9E4;
        } else {
            state->speed = 100.0f;
            phase = ((GameF21D0Vertex *)((u8 **)(arg0 + 0x20))[D_800BE9C0])->tc[1] % 1024;
            while (phase < 0) {
                phase += 1024;
            }
            initialPhase = state->initialPhase % 1024;
            while (initialPhase < 0) {
                initialPhase += 1024;
            }
            if (phase >= initialPhase && (f32)phase - state->speed <= (f32)initialPhase) {
                state->speed = (f32)(phase - initialPhase);
                arg0[0x73] &= 0xFFFC;
                arg0[0x73] |= 3;
            }
        }
    }
    if (state->speed != 0.0f) {
        for (index = 0; index < *(u16 *)(arg0 + 0x16); index++) {
            ((GameF21D0Vertex *)((u8 **)(arg0 + 0x20))[D_800BE9C0])[index].tc[1] = (f32)((GameF21D0Vertex *)((u8 **)(arg0 + 0x20))[D_800BE9C0])[index].tc[1] - state->speed;
        }
    }
    if (((GameF21D0Vertex *)((u8 **)(arg0 + 0x20))[D_800BE9C0])->tc[1] < -0x2800) {
        for (index = 0; index < *(u16 *)(arg0 + 0x16); index++) {
            ((GameF21D0Vertex *)((u8 **)(arg0 + 0x20))[D_800BE9C0])[index].tc[1] += 0x2800;
        }
    }
    adjustment = 0;
    result = func_1510D0EC((s32)resource, &limit, 3, 0);
    if (state->enabled != 0) {
        adjustment = limit + result - 0x200;
    }
    func_1510D874((s32)arg0, result, adjustment, 4, 5);
}

extern void *D_800D98D0;
extern void *D_800D98E0;

void func_150C522C(void) {
    void **var_s0;
    void **var_s1;
    void *temp_a0;

    var_s1 = (var_s0 = &D_800D98D0, &D_800D98E0);
    do {
        temp_a0 = *var_s0;
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        var_s0++;
        var_s0[-1] = 0;
    } while (var_s0 != var_s1);
}
