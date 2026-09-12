#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E2490.c
 * Boundary evidence: docs/evidence/game_raw_secondary_stream_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B4FE0
 * - func_151B50F4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E2490/func_151B4FE0.s")
typedef struct {
    u8 pad_0[0xC];
    u8 field_C;
} Game1E2490Data;

void func_151B50F4(f32 *, s32, s32, s32, s32);

void func_151B50A4(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, Game1E2490Data *arg6) {
    f32 sp24[3];

    sp24[0] = arg0;
    sp24[1] = arg1;
    sp24[2] = arg2;
    func_151B50F4(sp24, arg3, arg4, arg5, arg6->field_C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E2490/func_151B50F4.s")
