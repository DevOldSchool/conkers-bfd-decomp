#include "types.h"

/*
 * Reviewed source unit: src/game/game_3F560.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501214C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game3F560Actor {
    u8 pad0[0x3B];
    u8 field_3B;
} Game3F560Actor;

typedef struct Game3F560Descriptor {
    Game3F560Actor *actor;
    u8 field_4;
    u8 pad5;
    s16 field_6;
    u8 field_8;
    u8 field_9;
    u8 field_A;
} Game3F560Descriptor;

void func_15190770(Game3F560Descriptor *, s32, u8, s32);
extern s32 D_800BE9F0;

void func_10022EC0(s32, f32 *, s32);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_80096540;

void func_150120B0(s32 arg0) {
    s32 temp_v0;
    f32 values[8];

    values[0] = 50.0f;
    values[1] = 50.0f;
    values[2] = 50.0f;
    values[3] = 50.0f;
    values[4] = 50.0f;
    values[5] = 50.0f;
    values[6] = 0.0f;
    values[7] = D_80096540;
    temp_v0 = func_15149130(0x12C, -1, 0x1E, -1, 0, 0x41, 0x20, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, values, 0x20);
    }
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501214C CURRENT (400) */
void func_1501214C(Game3F560Actor *arg0) {
    Game3F560Descriptor descriptor;

    if (D_800BE9F0 != 0x18) {
        descriptor.actor = arg0;
        descriptor.field_4 = arg0->field_3B;
        descriptor.field_6 = 0x12C;
        descriptor.field_8 = 0;
        descriptor.field_9 = 0;
        descriptor.field_A = 2;
        func_15190770(&descriptor, 0, 0xFF, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501214C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3F560/func_1501214C.s")
