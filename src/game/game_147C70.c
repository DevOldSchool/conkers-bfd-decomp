#include "types.h"

/*
 * Reviewed source unit: src/game/game_147C70.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511A838
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[4];
    f32 *values;
    u8 pad8[8];
    f32 field_10;
    f32 field_14;
    f32 field_18;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
} Game147C70Output;

typedef struct {
    u8 pad0[0x16];
    u16 value_count;
    u8 pad18[0x68];
    Game147C70Output *output;
} Game147C70State;

void func_1511A7C0(Game147C70State *arg0) {
    s32 offset;
    s32 index;
    Game147C70Output *output;

    output = arg0->output;
    output->field_1E = 1;
    output->field_10 = 0.0f;
    output->field_1C = 0;
    output->field_1D = 7;
    output->field_14 = 260.0f;
    output->field_18 = 100.0f;
    index = 0;
    offset = 0;
    if ((s32)arg0->value_count > 0) {
        do {
            index += 1;
            *(f32 *)((u8 *)output->values + offset) = 0.0f;
            offset += sizeof(f32);
        } while (index < (s32)arg0->value_count);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_147C70/func_1511A838.s")
