#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FF0E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_child_chain_render_lists.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D1C30
 * - func_150D1F6C
 * - func_150D2054
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D1C30 CURRENT (1598) */
void func_150D1C30(u8 *arg0) {
    GameFF0E0Motion *state;
    u8 *disabledChild;
    f32 matrix[4][4];
    u8 *child;
    f32 targetZ, targetY, targetX;
    f32 pointZ, pointY, pointX;
    f32 fraction;
    s32 index;

    state = (GameFF0E0Motion *)(arg0 + 0x28);
    if (arg0[0x6C] & 1) {
        state->rotation[0] += state->velocity[0] * D_800BE9A4;
        state->rotation[1] += state->velocity[1] * D_800BE9A4;
        state->rotation[2] += state->velocity[2] * D_800BE9A4;
        func_150A8050(matrix, state->rotation[0], state->rotation[1], state->rotation[2]);
        index = 0;
        do {
            child = state->children[index];
            if (child != NULL) {
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
            index++;
        } while (index != 6);
    } else {
        for (index = 0; index < 6; index++) {
            disabledChild = state->children[index];
            if (disabledChild != NULL) (*(u8 **)(disabledChild + 0x14))[9] = 1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D1C30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF0E0/func_150D1C30.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D1F6C CURRENT (1915) */
void func_150D1F6C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_t6;
    GameFF0E0State *temp_v0;

    temp_t6 = arg2;
    if (temp_t6 == 0x32) {
        temp_v0 = (GameFF0E0State *)(arg0 + 0x28);
        temp_v0->field_18 = *(s32 *)arg1;
        temp_v0->field_1C = *(s32 *)(arg1 + 4);
        temp_v0->field_20 = *(s32 *)(arg1 + 8);
        temp_v0->field_3C = *(f32 *)(arg1 + 0xC);
        return;
    }
    if ((temp_t6 == 0x30) || (temp_t6 == 0x31)) {
        temp_v0 = (GameFF0E0State *)(arg0 + 0x28);
        if (arg1 == temp_v0->field_40) {
            if (temp_t6 == 0x30) {
                temp_v0->field_44 |= 1;
                return;
            }
            temp_v0->field_44 &= 0xFFFE;
        }
    } else {
        if (temp_t6 == 0x4E) {
            *(s32 *)(arg0 + 0x40) = *(&D_800A5480 + 0);
            *(s32 *)(arg0 + 0x44) = *(&D_800A5480 + 1);
            *(s32 *)(arg0 + 0x48) = *(&D_800A5480 + 2);
            return;
        }
        if (temp_t6 == 0x4F) {
            func_1516972C(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D1F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF0E0/func_150D1F6C.s")
void func_150D2054(u8 *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D2054 CURRENT (25) */
void func_150D2054(u8 *arg0) {
    s32 temp_t8;
    s32 var_s0;
    void *temp_a0;
    u8 *var_s1;

    var_s0 = 0;
    var_s1 = (u8 *)arg0 + 0x28;
    do {
        temp_a0 = *(void **)(var_s1 + (var_s0 * 4) + 0x24);
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        var_s0++;
        temp_t8 = var_s0 & 0xFF;
        var_s0 = temp_t8;
    } while (temp_t8 < 6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D2054 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF0E0/func_150D2054.s")

void func_150D20B0(void *arg0) {
    func_150D2054(arg0);
    func_15149368(arg0);
}

void func_150D20DC(void *arg0) {
    func_150D2054(arg0);
    func_1514933C(arg0);
}
