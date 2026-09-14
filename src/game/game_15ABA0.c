#include "types.h"

/*
 * Reviewed source unit: src/game/game_15ABA0.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512D748
 * - func_1512D980
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800DC2C0[];

void func_1512D6F0(void *arg0) {
    void *temp_v0;

    temp_v0 = D_800DC2C0 + (*(u8 *)((u8 *)arg0 + 0x23D) * 0x68);
    *(s32 *)((u8 *)temp_v0 + 0x50) = 5;
    *(f32 *)((u8 *)temp_v0 + 0x54) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x58) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x5C) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x60) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x2C) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x28) = -1.0f;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15ABA0/func_1512D748.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15ABA0/func_1512D980.s")
