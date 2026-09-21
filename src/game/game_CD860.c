#include "types.h"

/*
 * Reviewed source unit: src/game/game_CD860.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A04D8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150A3444(s32, s16, s16, s16);
void func_151C970C(s32, void *);
void func_150A2864(s32, s32);
void func_150A2940(s32, s32, s32);
void func_150A3398(s32, u16, s32, s32, s32, s32);
extern s32 D_800D3098;

s32 func_150A03B0(s32 arg0, u32 arg1, void *arg2) {
    s32 temp_v0;
    s32 var_a0;
    s32 var_v0;

    switch (arg1) {
    case 0:
        func_150A2864(arg0, 0);
        return 1;
    case 1:
        func_150A2864(arg0, 1);
        return 1;
    case 2:
        func_150A2940(arg0, *(s32 *)((u8 *)arg2 + 8), *(s32 *)((u8 *)arg2 + 0xC));
        return 1;
    case 3:
        func_150A3444(arg0, *(s16 *)((u8 *)arg2 + 0xA),
                        *(s16 *)((u8 *)arg2 + 0xE),
                        *(s16 *)((u8 *)arg2 + 0x12));
        goto block_14;
    case 4:
        func_150A3398(arg0, *(u16 *)((u8 *)arg2 + 0xA),
                        *(s32 *)((u8 *)arg2 + 0xC),
                        *(s32 *)((u8 *)arg2 + 0x10),
                        *(s32 *)((u8 *)arg2 + 0x14),
                        *(s32 *)((u8 *)arg2 + 0x18));
        goto block_14;
    case 5:
        temp_v0 = *(s32 *)((u8 *)arg2 + 8);
        if (temp_v0 == 0x3E7) {
            var_a0 = 2;
        } else {
            if (temp_v0 != 0) {
                var_v0 = 0;
            } else {
                var_v0 = 1;
            }
            var_a0 = var_v0;
        }
        func_151C970C(var_a0, (void *)(D_800D3098 + (arg0 * 0x34)));
    default:
block_14:
        return 0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD860/func_150A04D8.s")
