#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1EB6C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups_continued.md
 */

f32 func_150ADA68();                                /* extern */
extern f32 D_800BE9A4;

typedef struct Game1EB6C0State {
    void *field_0;
    u8 pad_4[4];
    f32 field_8;
    f32 field_C;
    f32 field_10;
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    f32 field_2C;
    f32 field_30;
    f32 field_34;
    f32 field_38;
    f32 field_3C;
    f32 field_40;
    f32 field_44;
    f32 field_48;
    f32 field_4C;
    u8 pad_50[4];
    f32 field_54;
    u8 field_58;
} Game1EB6C0State;

s32 func_151BE210(u8 *arg0) {
    Game1EB6C0State *s = (Game1EB6C0State *)(arg0 + 0x110);
    f32 scale;

    s->field_24 -= D_800BE9A4;
    if (s->field_24 < 0.0f) {
        s->field_24 = func_150ADA68() * 4.0f;
        s->field_18 = func_150ADA68() * s->field_10 + s->field_8;
    }
    *(f32 *)(arg0 + 0x2C) += (s->field_18 - *(f32 *)(arg0 + 0x2C)) * 0.35f;
    s->field_28 -= D_800BE9A4;
    if (s->field_28 < 0.0f) {
        s->field_28 = func_150ADA68() * 9.0f;
        if (func_150ADA20() & 1) {
            s->field_1C = func_150ADA68() * s->field_14 + s->field_C;
        } else {
            s->field_1C = func_150ADA68() * s->field_20 + s->field_C;
        }
    }
    *(f32 *)(arg0 + 0x30) += (s->field_1C - *(f32 *)(arg0 + 0x30)) * 0.4f;
    s->field_38 -= D_800BE9A4;
    if (s->field_38 < 0.0f) {
        s->field_38 = func_150ADA68() * 10.0f;
        s->field_34 = func_150ADA68() * s->field_30 + s->field_2C;
    }
    scale = 0.65000004f;
    s->field_3C += (s->field_34 - s->field_3C) * 0.4f;
    arg0[0x5C] = s->field_3C;
    s->field_40 += (s->field_48 - s->field_40) * scale;
    s->field_44 += (s->field_4C - s->field_44) * scale;
    return 1;
}

void *func_1513FAB4(void *arg0, s32 arg1, f32 *arg2, s16 arg3);

void *func_151BE4B8(void *arg0, s16 arg1) {
    Game1EB6C0State *state;
    void *linked;
    f32 values[2];

    linked = *(void **)((u8 *)arg0 + 0x110);
    if ((*(u8 *)((u8 *)arg0 + 0x114) != *(u8 *)((u8 *)linked + 0x3B)) ||
        (state = (Game1EB6C0State *)((u8 *)arg0 + 0x110), *(s32 *)linked == 0)) {
        func_1516972C(arg0);
        return 0;
    }
    if (!(state->field_58 & 1)) {
        return 0;
    }
    values[0] = state->field_40 * state->field_54;
    values[1] = state->field_44 * state->field_54;
    return func_1513FAB4(arg0, 0, values, arg1);
}
void func_151BE558(void *arg0, void *arg1, u8 arg2) {
    s32 temp_t6;
    u8 *temp_v0;

    temp_t6 = arg2;
    temp_v0 = (u8 *)arg0 + 0xB0;
    if (temp_t6 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0) {
            u8 *dst = temp_v0;

            *(s32 *)dst = *(s32 *)arg1;
            *(u8 *)(dst + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if (temp_t6 == 0) {
        s32 temp_v1 = *(s32 *)arg1;

        if ((temp_v1 == *(s32 *)temp_v0) ||
            (temp_v0[4] == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C((u8 *)arg0);
        }
    }
}

extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_151BE604(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}
void func_151BE644(void *arg0) {
    void *temp_v0;
    s32 temp_v1;

    temp_v0 = (u8 *)arg0 + 0x110;
    if (*(s32 *)((u8 *)arg0 + 0x160) != 0) {
        temp_v1 = *(s32 *)((u8 *)temp_v0 + 0x50);
        temp_v1 += 0x28;
        *(s32 *)((u8 *)temp_v1 + (*(u8 *)((u8 *)temp_v0 + 5) << 2) + 8) = 0;
    }
}
void func_151BE644(void *arg0);

void func_151BE674(void *arg0) {
    func_151BE644(arg0);
    func_1513CA6C(arg0);
}
void func_151BE6A0(void *arg0) {
    func_151BE644(arg0);
    func_1513CAA0(arg0);
}
typedef struct Game1EB6C0Choices {
    s32 values[4];
} Game1EB6C0Choices;

extern Game1EB6C0Choices D_800AA7A8;
extern f32 D_800AA8AC;
extern s32 D_800BE9E4;

s32 func_151BE6CC(void *arg0) {
    typedef struct { u8 pad0[0x48]; f32 value; } State;
    f32 current;
    Game1EB6C0Choices choices;
    State *state;

    choices = D_800AA7A8;
    state = (State *)((u8 *)arg0 + 0x110);
    *(s16 *)((u8 *)arg0 + 0x170) -= D_800BE9E4;
    if (*(s16 *)((u8 *)arg0 + 0x170) < 0) {
        *(s8 *)((u8 *)arg0 + 0x18) = (s8)choices.values[func_150ADA20() & 3];
        *(s16 *)((u8 *)arg0 + 0x170) = (s16)((func_150ADA20() & 7) + 3);
    }
    current = state->value;
    state->value += (*(f32 *)((u8 *)arg0 + 0x174) - current) * D_800AA8AC;
    return 1;
}
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_151BE788(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x180, arg0 + 0x184, arg0);
}
void func_151BE7C8(void *arg0) {
    void *temp_v0;
    s32 temp_v1;

    temp_v0 = (u8 *)arg0 + 0x170;
    if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
        temp_v1 = *(s32 *)((u8 *)temp_v0 + 8);
        temp_v1 += 0x28;
        *(s32 *)((u8 *)temp_v1 + (*(u8 *)((u8 *)temp_v0 + 0xC) << 2) + 0x10) = 0;
    }
}
void func_151BE7C8(void *arg0);

void func_151BE7F8(void *arg0) {
    func_151BE7C8(arg0);
    func_151411A4(arg0);
}
void func_151BE824(void *arg0) {
    func_151BE7C8(arg0);
    func_151411C4(arg0);
}
