#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D8DE0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_model_owner_mode_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AB9C8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u8 func_151D8E20(void);
void *func_10022EC0(void *, const void *, u32);
extern f32 D_800A9014;

typedef struct {
    void *field_0;
    u8 field_4;
    u8 pad_5[3];
    s32 field_8;
    f32 field_C;
    f32 field_10;
    f32 field_14;
    u8 field_18;
} Game1D8DE0Packet;

void func_151AB930(void *arg0) {
    u8 *temp_v0;
    Game1D8DE0Packet packet;

    packet.field_0 = arg0;
    packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_8 = *(u16 *)((u8 *)arg0 + 0x84);
    packet.field_C = 0.0f;
    packet.field_10 = D_800A9014;
    packet.field_14 = 3.0f;
    packet.field_18 = func_151D8E20();
    temp_v0 = func_151491F4(0x3C, -1, 0xE, 1, 9, 0x1C, 0xFF, 0);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, (void *)&packet.field_0, 0x1C);
    }
}
void func_1504715C(void *, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32,
                   f32, f32, s32, void *, s32, s32, s32, s32);
extern f32 D_800A9018, D_800A901C, D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB9C8 CURRENT (4390) */
void func_151AB9C8(u8 *arg0) {
    u8 *parent;
    volatile u8 savedInvalid;
    u8 invalid;
    u32 surface[9];
    f32 position[3];
    f32 velocity[3];
    f32 horizontal;
    f32 horizontalSpeed;
    f32 sinePitch;
    f32 cosinePitch;
    f32 sineYaw;
    f32 cosineYaw;
    f32 speed;
    u32 firstRandom;
    u32 secondRandom;
    Game1D8DE0Packet *state;

    invalid = 0;
    state = (Game1D8DE0Packet *)(arg0 + 0x28);
    if (**(s32 **)(arg0 + 0x28) == 0) {
        invalid = 1;
    } else {
        parent = state->field_0;
        if (state->field_4 != parent[0x3B]) {
            invalid = 1;
        } else if (state->field_8 != *(u16 *)(parent + 0x84)) {
            invalid = 1;
        }
    }
    savedInvalid = invalid;
    if (invalid == 0) {
        savedInvalid = invalid;
        state = (Game1D8DE0Packet *)(arg0 + 0x28);
        state->field_C += (state->field_10 + func_150ADA68() * state->field_14) * D_800BE9A4;
        if (state->field_C > 1.0f) {
            func_1504715C(surface, state->field_0);
            do {
                firstRandom = (s16)(func_150ADA20() & 0xFF);
                secondRandom = (s16)((func_150ADA20() % 46U) - 0x3F);
                sinePitch = func_151423D8((u8)secondRandom);
                cosinePitch = func_151423D8((u8)(secondRandom - 0x40));
                sineYaw = func_151423D8((u8)firstRandom);
                cosineYaw = func_151423D8((u8)(firstRandom - 0x40));
                speed = func_150ADA68();
                horizontal = 30.0f * sinePitch;
                position[0] = *(f32 *)((u8 *)state->field_0 + 0x14) + horizontal * cosineYaw;
                position[1] = *(f32 *)((u8 *)state->field_0 + 0x18) - 75.0f * cosinePitch;
                position[2] = *(f32 *)((u8 *)state->field_0 + 0x1C) + horizontal * sineYaw;
                speed = (speed * D_800A9018 + 500.0f) * D_800A901C;
                horizontalSpeed = speed * sinePitch;
                velocity[0] = horizontalSpeed * cosineYaw;
                velocity[1] = -speed * cosinePitch;
                velocity[2] = horizontalSpeed * sineYaw;
                sinePitch = func_150ADA68();
                firstRandom = func_150ADA20();
                secondRandom = func_150ADA20();
                func_151D9014(position, velocity, state->field_18,
                    sinePitch * 0.5f + -1.0f, firstRandom % 26U + 0x20,
                    secondRandom % 101U + 0x64, func_150ADA68() * 34.0f + 52.0f,
                    1, 1.0f, 1.0f, 1, surface, 1, 0, arg0[0xC], arg0[1]);
                state->field_C -= 1.0f;
            } while (state->field_C > 1.0f);
        }
    }
    if (savedInvalid != 0) {
        *(s16 *)(arg0 + 0xE) = -1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB9C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D8DE0/func_151AB9C8.s")

void func_151ABD54(void *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;

    temp_v0 = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
        if ((*(s32 *)temp_v0 == *(s32 *)arg1) || (temp_v0[4] == arg1[4])) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)(arg1 + 4);
            temp_v0[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)arg1;
            temp_v0[4] = arg1[8];
        }
    }
}
