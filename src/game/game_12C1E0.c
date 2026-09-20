#include "types.h"

/*
 * Reviewed source unit: src/game/game_12C1E0.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FED30
 * - func_150FF084
 * - func_150FF2D4
 * - func_150FF474
 * - func_150FF6E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FED30.s")
extern s32 func_1503195C(void *arg0, s32 arg1, s32 arg2);
void func_1514654C(void *, s32, s32, void **, void **, s32);
extern u8 D_800A2050;

void func_150FEFD0(void *arg0, s16 arg1, void *arg2) {
    u8 *sp34;
    void *sp30;
    s32 result;

    if (arg1 == -1) {
        *(f32 *)((u8 *)arg2 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg2 + 4) = *(f32 *)((u8 *)arg0 + 0x18);
        *(f32 *)((u8 *)arg2 + 8) = *(f32 *)((u8 *)arg0 + 0x1C);
        return;
    }
    result = func_1503195C(arg0, arg1, 0);
    if (result == 0) {
        *(f32 *)((u8 *)arg2 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg2 + 4) = *(f32 *)((u8 *)arg0 + 0x18);
        *(f32 *)((u8 *)arg2 + 8) = *(f32 *)((u8 *)arg0 + 0x1C);
        return;
    }
    sp34 = &D_800A2050;
    sp30 = arg2;
    func_1514654C(arg0, result, 0, (void **)&sp34, &sp30, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF084.s")

void func_150FF288(void *arg0) {
    func_1503195C(arg0, 0x82, 0);
}
void func_15145740(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4);
extern f32 D_800A211C;

void func_150FF2AC(void *arg0, void *arg1, void *arg2, void *arg3) {
    func_15145740(arg0, arg1, arg2, arg3, D_800A211C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF2D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF474.s")
s32 func_150FF6B4(void *arg0, s32 arg1, s32 arg2) {
    if (*(u8 *)((u8 *)arg0 + 4) == 0x98) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF6E0.s")
