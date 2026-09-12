#include "types.h"

/*
 * Reviewed source unit: src/game/game_12B250.c
 * Boundary evidence: docs/evidence/game_raw_slot_motion_attachment_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FDDA0
 * - func_150FDF38
 * - func_150FE0B8
 * - func_150FE288
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_12B250/func_150FDDA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B250/func_150FDF38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B250/func_150FE0B8.s")
extern void func_151D3E04(s32 arg0, s32 arg1, s32 *arg2, u8 arg3, f32 arg4);
extern u8 D_80088B80;
extern s32 D_800A1F70;

void func_150FE248(s32 arg0, s32 arg1, s32 arg2) {
    func_151D3E04(arg0, arg2, &D_800A1F70, D_80088B80, 0.0f);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B250/func_150FE288.s")
