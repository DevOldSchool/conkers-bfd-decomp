#include "types.h"

/*
 * Reviewed source unit: src/game/game_3F560.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150120B0
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_3F560/func_150120B0.s")

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
