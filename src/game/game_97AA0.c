#include "types.h"

/*
 * Reviewed source unit: src/game/game_97AA0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1506A5F0
 * - func_1506A79C
 * - func_1506A864
 * - func_1506A968
 * - func_1506AA48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A5F0.s")
void func_150E0348(s32 arg0, s32 arg1, s32 arg2);

void func_1506A6FC(s32 arg0, u8 arg1) {
    func_150E0348(arg0, 0xFF, 1);
}
void func_151BB61C(void *, void *, void *, s32, s32);
extern u8 D_800D1560;
extern u8 D_800D1570;

void func_1506A724(void *arg0, s32 arg1) {
    func_151BB61C(arg0, &D_800D1560, &D_800D1570, 0xFF, 1);
}
void func_151BBA9C(void *, void *, void *, s32, s32);

void func_1506A760(void *arg0, s32 arg1) {
    func_151BBA9C(arg0, &D_800D1560, &D_800D1570, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A79C.s")
void func_151BC104(s32 arg0, s32 arg1, s32 arg2);

void func_1506A83C(s32 arg0, u8 arg1) {
    func_151BC104(arg0, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A864.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A968.s")
extern void func_151B6320(s32 arg0, s32 arg1, s32 arg2);
extern void func_151B7144(s32 arg0, s32 arg1, s32 arg2);

void func_1506AA08(s32 arg0, s32 arg1) {
    func_151B7144(arg0, 0xFF, 1);
    func_151B6320(arg0, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506AA48.s")
