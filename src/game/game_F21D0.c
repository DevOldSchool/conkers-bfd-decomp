#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_F21D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C4D20
 * - func_150C4E9C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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
extern f32 D_800A03F0;
extern f32 D_800A03F4;
extern f32 D_800A03F8;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C4D20 CURRENT (1731) */
void func_150C4D20(GameF21D0Mover *arg0) {
    struct {
        s32 timer;
        f32 velocity;
    } state;
    f32 angle;
    f32 elapsed;

    angle = arg0->angle;
    state.velocity = arg0->velocity;
    if (angle > 180.0f) {
        angle -= 360.0f;
    }
    state.timer = (s32)((u32)arg0->timer + (u32)D_800BE9E4);
    elapsed = (f32)state.timer;
    state.velocity -= angle * D_800A03F0;
    if (elapsed >= 256.0f) {
        state.timer = (s32)(elapsed - 256.0f);
        func_10010F88(0xF, 0x55F0U, 0, 0, 0, arg0->field10, arg0->field12, arg0->field14, 0x1F4, 0x3E8);
    }
    arg0->timer = state.timer;
    state.velocity += func_15048A40(state.timer & 0xFF) * D_800A03F4;
    if ((arg0->flags & 4) == 4) {
        state.velocity += D_800A03F4;
    }
    state.velocity *= D_800A03F8;
    arg0->velocity = state.velocity;
    arg0->angle = arg0->angle + state.velocity;
    angle = arg0->angle;
    if (angle < 0.0f) {
        arg0->angle = angle + 360.0f;
        return;
    }
    if (angle >= 360.0f) {
        arg0->angle = angle - 360.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C4D20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F21D0/func_150C4D20.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C4E9C CURRENT (300) */
void func_150C4E9C(u8 *arg0) {
    u8 *resource;
    s32 limit;
    GameF21D0ScrollState *initialState;
    s32 adjustment;
    GameF21D0ScrollState *state;
    s32 mode;
    s32 initialPhase;
    s32 index;
    s32 offset;
    u8 *vertex;
    s32 result;

    mode = arg0[0x73] & 3;
    initialState = *(GameF21D0ScrollState **)(arg0 + 0x7C);
    if (initialState == NULL) {
        state = func_10003C40(0x10, 1, 0, 0);
        *(GameF21D0ScrollState **)(arg0 + 0x7C) = state;
        func_1511A410(*(s8 **)(arg0 + 0x1C), (s32 *)state);
        state->initialPhase = *(s16 *)(*(u8 **)(arg0 + 0x28) + 0xA);
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
        if (state->speed > 100.0f) {
            state->speed = state->speed - 25.0f * (f32)D_800BE9E4;
        } else {
            state->speed = 100.0f;
            mode = *(s16 *)(((u8 **)(arg0 + 0x20))[D_800BE9C0] + 0xA) % 1024;
            while (mode < 0) {
                mode += 1024;
            }
            initialPhase = state->initialPhase % 1024;
            while (initialPhase < 0) {
                initialPhase += 1024;
            }
            if (mode >= initialPhase && (f32)mode - state->speed <= (f32)initialPhase) {
                state->speed = (f32)(mode - initialPhase);
                arg0[0x73] &= 0xFFFC;
                arg0[0x73] |= 3;
            }
        }
    }
    if (state->speed != 0.0f) {
        offset = 0;
        index = 0;
        if (*(u16 *)(arg0 + 0x16) > 0) {
            do {
                index++;
                vertex = ((u8 **)(arg0 + 0x20))[D_800BE9C0] + offset;
                offset += 0x10;
                *(s16 *)(vertex + 0xA) = (s32)((f32)*(s16 *)(vertex + 0xA) - state->speed);
            } while (index < *(u16 *)(arg0 + 0x16));
        }
    }
    if (*(s16 *)(((u8 **)(arg0 + 0x20))[D_800BE9C0] + 0xA) < -0x2800) {
        offset = 0;
        index = 0;
        if (*(u16 *)(arg0 + 0x16) > 0) {
            do {
                index++;
                vertex = ((u8 **)(arg0 + 0x20))[D_800BE9C0] + offset;
                offset += 0x10;
                *(s16 *)(vertex + 0xA) += 0x2800;
            } while (index < *(u16 *)(arg0 + 0x16));
        }
    }
    adjustment = 0;
    result = func_1510D0EC((s32)resource, &limit, 3, 0);
    if (state->enabled != 0) {
        adjustment = limit + result - 0x200;
    }
    func_1510D874((s32)arg0, result, adjustment, 4, 5);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C4E9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F21D0/func_150C4E9C.s")

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
