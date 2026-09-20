#include "types.h"

/*
 * Reviewed source unit: src/game/game_DF930.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B2570
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150B2480(s32 arg0, s32 arg1) {
    return 0xA;
}
u32 func_150ADA20(void);
void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
void func_151D5404(f32 *, s32, s32, s32, s32, s32, s32, s32);
void func_151D3FF4(s32, u8, s32);

void func_150B2494(void *arg0, s32 arg1, s32 arg2) {
    f32 position[3];

    position[0] = *(f32 *)((u8 *)arg0 + 0x14);
    position[1] = *(f32 *)((u8 *)arg0 + 0x180);
    position[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    func_1514C678(position[0], position[1], *(s32 *)&position[2], 135.0f,
                  0, 0xFF, (func_150ADA20() % 15U) + 0x1B,
                  7, 0, 0.0f, 0, 0xFF);
    func_151D5404(position, 0x44BBC000, 0x453B8000, 0x39AEC33E,
                  0xC, 0xF, 0xFF, 0);
    func_151D3FF4((s32)position, 0xFF, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DF930/func_150B2570.s")
