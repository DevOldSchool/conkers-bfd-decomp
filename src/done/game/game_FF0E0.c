#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FF0E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_child_chain_render_lists.md
 */

extern s32 D_800A5480;

typedef struct {
    u8 pad_0[0x18];
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    u8 pad_24[0x18];
    f32 field_3C;
    void *field_40;
    u8 field_44;
} GameFF0E0State;

typedef struct {
    f32 position[3];
    f32 rotation[3];
    f32 velocity[3];
    void *children[6];
    f32 intensity;
} GameFF0E0Motion;

void func_150A8050(void *, f32, f32, f32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
extern f32 D_800A08F0[][3];
extern f32 D_800BE9A4;

void func_150D1C30(u8 *arg0) {
    GameFF0E0Motion *state;
    u8 *child;
    f32 matrix[4][4];
    s32 index;

    state = (GameFF0E0Motion *)(arg0 + 0x28);
    if (arg0[0x6C] & 1) {
        state->rotation[0] += state->velocity[0] * D_800BE9A4;
        state->rotation[1] += state->velocity[1] * D_800BE9A4;
        state->rotation[2] += state->velocity[2] * D_800BE9A4;
        func_150A8050(matrix, state->rotation[0], state->rotation[1], state->rotation[2]);
        for (index = 0; index != 6; index++) {
            child = state->children[index];
            if (child != NULL) {
                f32 targetZ, targetY, targetX;
                f32 pointZ, pointY, pointX;
                f32 fraction;

                func_150A7960(matrix, D_800A08F0[index][0], D_800A08F0[index][1],
                              D_800A08F0[index][2], &targetX, &targetY, &targetZ);
                if (func_150AC9C0(state->position[0], state->position[1], state->position[2],
                                  targetX, targetY, targetZ, NULL, NULL,
                                  &pointX, &pointY, &pointZ, &fraction, NULL, NULL, 0.0f)) {
                    (*(u8 **)(child + 0x14))[9] = 0;
                    *(s16 *)(*(u8 **)(child + 0x14) + 0xE) = (s32)pointX;
                    *(s16 *)(*(u8 **)(child + 0x14) + 0x10) = (s32)pointY;
                    *(s16 *)(*(u8 **)(child + 0x14) + 0x12) = (s32)pointZ;
                    (*(u8 **)(child + 0x14))[0x2F] = (u32)(state->intensity * fraction);
                } else {
                    (*(u8 **)(child + 0x14))[9] = 1;
                }
            }
        }
    } else {
        for (index = 0; index < 6; index++) {
            u8 *disabledChild = state->children[index];
            if (disabledChild != NULL) {
                (*(u8 **)(disabledChild + 0x14))[9] = 1;
            }
        }
    }
}

typedef struct {
    Vec3f position;
    f32 scale;
} GameFF0E0Placement;

void func_150D1F6C(u8 *arg0, u8 *arg1, u8 arg2) {
    GameFF0E0State *state = (GameFF0E0State *)(arg0 + 0x28);

    if (arg2 == 0x32) {
        GameFF0E0Placement *placement = (GameFF0E0Placement *)arg1;

        *(Vec3f *)&state->field_18 = placement->position;
        state->field_3C = placement->scale;
    } else if ((arg2 == 0x30) || (arg2 == 0x31)) {
        if (arg1 == state->field_40) {
            if (arg2 == 0x30) {
                state->field_44 |= 1;
            } else {
                u8 *flags = &state->field_44;

                *flags &= 0xFFFE;
            }
        }
    } else if (arg2 == 0x4E) {
        *(Vec3f *)(arg0 + 0x40) = *(Vec3f *)&D_800A5480;
    } else if (arg2 == 0x4F) {
        func_1516972C(arg0);
    }
}
void func_150D2054(u8 *arg0);

void func_150D2054(u8 *arg0) {
    u8 var_s0;
    void *temp_a0;
    u8 *var_s1;

    var_s0 = 0;
    var_s1 = (u8 *)arg0 + 0x28;
    do {
        temp_a0 = ((void **)(var_s1 + 0x24))[var_s0];
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        var_s0++;
    } while (var_s0 < 6);
}

void func_150D20B0(void *arg0) {
    func_150D2054(arg0);
    func_15149368(arg0);
}

void func_150D20DC(void *arg0) {
    func_150D2054(arg0);
    func_1514933C(arg0);
}
