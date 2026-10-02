#include "types.h"

/*
 * Reviewed source unit: src/game/game_3F4D0.c
 * Boundary evidence: docs/evidence/game_small_units_3D6F0_3FC30.md
 */

typedef struct Game3F4D0Descriptor {
    s8 field_0;
    u8 pad1[3];
    s32 field_4;
    f32 field_8;
    f32 field_C;
    f32 field_10[5];
    s8 field_24;
    s8 field_25;
    s8 field_26;
} Game3F4D0Descriptor;

void func_151A8B20(Game3F4D0Descriptor *, s32, s32, s32, s32);
extern f32 D_80096530;
extern f32 D_80096534;

void func_15012020(s32 arg0, s32 arg1) {
    Game3F4D0Descriptor descriptor;

    descriptor.field_0 = 7;
    descriptor.field_4 = arg0;
    descriptor.field_10[0] = 0.0f;
    descriptor.field_10[1] = 0.0f;
    descriptor.field_10[2] = 0.0f;
    descriptor.field_10[3] = 0.0f;
    descriptor.field_10[4] = 0.0f;
    descriptor.field_24 = 0;
    descriptor.field_25 = -1;
    descriptor.field_26 = 3;
    descriptor.field_8 = D_80096530;
    descriptor.field_C = D_80096534;
    func_151A8B20(&descriptor, -1, 0, 0xFF, 0);
}
