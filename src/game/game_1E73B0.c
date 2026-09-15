#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E73B0.c
 * Boundary evidence: docs/evidence/game_raw_complete_code_selected_segments.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B9F00
 * - func_151BA084
 * - func_151BA468
 * - func_151BA518
 * - func_151BB0E0
 * - func_151BB61C
 * - func_151BBA9C
 * - func_151BBEE4
 * - func_151BBFBC
 * - func_151BC104
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15160CDC(
    s32 arg0,
    s32 arg1,
    void *arg2,
    void *arg3,
    f32 arg4,
    s32 arg5,
    s32 arg6,
    s32 arg7,
    s32 arg8,
    s32 arg9,
    s32 arg10,
    s32 arg11,
    s32 arg12,
    s32 arg13,
    s32 arg14,
    s32 arg15
);
extern u8 D_800AA760;
extern u8 D_800AA76C;
extern f32 D_800AA82C;

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151B9F00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA084.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA518.s")
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
extern void func_151BB0E0(void);

void func_151BB044(void *arg0) {
    func_1000FA64(0x4A7,
                  (s32) (s16) (s32) *(f32 *)((u8 *)arg0 + 0x14),
                  (s32) (s16) (s32) *(f32 *)((u8 *)arg0 + 0x18),
                  (s32) (s16) (s32) *(f32 *)((u8 *)arg0 + 0x1C),
                  0x2000, 0x320, 0xC8, (void *)&func_151BB0E0,
                  (s32) arg0, 0, 8, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BB0E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BB61C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BBA9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BBEE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BBFBC.s")
void func_151BC074(s32 arg0) {
    if (arg0 != 0) {
        func_15160CDC(arg0, 1, &D_800AA760, &D_800AA76C, D_800AA82C, 2, 0x12C, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 0, 0xFF, 1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BC104.s")
