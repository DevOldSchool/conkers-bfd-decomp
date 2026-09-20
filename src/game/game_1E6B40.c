#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E6B40.c
 * Boundary evidence: docs/evidence/game_raw_scene_setup_emission_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B9690
 * - func_151B9964
 * - func_151B9CB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6B40/func_151B9690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6B40/func_151B9964.s")
void *func_15167A68(s32, s32, s32, s32, s32, s32);

void func_151B9BF0(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4,
    s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 arg10, s16 arg11,
    s16 arg12, s32 arg13, u8 arg14, s32 arg15) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(7, arg15, 0x2C, 0, (s32)arg14, 1);
    if (temp_v0 != 0) {
        *(s8 *)(temp_v0 + 0x14) = (s8)arg0;
        *(s8 *)(temp_v0 + 0x15) = (s8)arg1;
        *(s16 *)(temp_v0 + 0x16) = arg2;
        *(s16 *)(temp_v0 + 0x18) = arg3;
        *(s16 *)(temp_v0 + 0x1A) = arg4;
        *(s16 *)(temp_v0 + 0x1C) = arg5;
        *(s16 *)(temp_v0 + 0x1E) = arg6;
        *(s16 *)(temp_v0 + 0x20) = arg7;
        *(s16 *)(temp_v0 + 0x22) = arg8;
        *(s16 *)(temp_v0 + 0x24) = arg9;
        *(s16 *)(temp_v0 + 0x26) = arg10;
        *(s16 *)(temp_v0 + 0x28) = arg11;
        *(s16 *)(temp_v0 + 0x2A) = arg12;
        *(s32 *)(temp_v0 + 0x10) = arg13;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6B40/func_151B9CB0.s")
