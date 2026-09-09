#include "types.h"

/*
 * Reviewed source unit: src/game/game_15D730.c
 * Boundary evidence: docs/evidence/game_raw_text_view_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15130280
 * - func_15130374
 * - func_151303BC
 * - func_151303EC
 * - func_15130A9C
 * - func_1513137C
 * - func_15131514
 * - func_1513164C
 * - func_1513177C
 * - func_151317C8
 * - func_15131828
 * - func_151319C4
 * - func_15131AFC
 * - func_15131B3C
 * - func_15131B7C
 * - func_15131C2C
 * - func_15131C84
 * - func_15131D4C
 * - func_15131D9C
 * - func_15131DEC
 * - func_15131EE4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15130280.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15130374.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_151303BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_151303EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15130A9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_1513137C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131514.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_1513164C.s")
void func_151318E8(void *, f32);

s32 func_151316AC(u8 *arg0, s32 arg1) {
    func_151318E8(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    return 1;
}
void func_15131918(void *, f32);

s32 func_151316DC(u8 *arg0, s32 arg1) {
    func_15131918(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    return 1;
}
void func_15131958(void *, f32);

s32 func_1513170C(u8 *arg0, s32 arg1) {
    func_15131958(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    return 1;
}
void func_1513173C(void) {
    func_15169804();
}
void func_1513175C(void) {
    func_15169824();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_1513177C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_151317C8.s")
s32 func_15131814(s32 arg0, s32 arg1) {
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131828.s")
extern s32 D_800BE9E4;

void func_151318E8(void *arg0, f32 arg1) {
    s32 var_v0;

    var_v0 = D_800BE9E4;
    if (var_v0 > 0) {
        do {
            var_v0 -= 1;
            *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
        } while (var_v0 > 0);
    }
}
void func_15131918(void *arg0, f32 arg1) {
    s32 var_v0;

    var_v0 = D_800BE9E4;
    if (var_v0 > 0) {
        do {
            var_v0 -= 1;
            *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
            *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
        } while (var_v0 > 0);
    }
}
void func_15131958(void *arg0, f32 arg1) {
    s32 var_v0;

    var_v0 = D_800BE9E4;
    if (var_v0 > 0) {
        do {
            var_v0 -= 1;
            *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
            *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
            *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
        } while (var_v0 > 0);
    }
}
void func_151319C4(void *arg0, s32 arg1, void *arg2);

void func_151319A4(void *arg0, s32 arg1) {
    func_151319C4(arg0, arg1, (u8 *)arg0 + 0xA8);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_151319C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131AFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131B3C.s")
extern f32 D_800A3848;
extern f32 D_800A384C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15131B7C CURRENT (2126) */
s32 func_15131B7C(void *arg0, s32 arg1, void *arg2, void *arg3) {
    f32 temp_fv0;

    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg2 + 4) + (*(f32 *)((u8 *)arg0 + 0x3C) * D_800A3848));
    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg3 + 4));
    *(f32 *)((u8 *)arg0 + 0x5C) = (f32) (*(f32 *)((u8 *)arg0 + 0x5C) * -*(f32 *)((u8 *)arg3 + 4));
    temp_fv0 = fabsf(*(f32 *)((u8 *)arg0 + 0x5C));
    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg3 + 4));
    if (temp_fv0 < D_800A384C) {
        *(f32 *)((u8 *)arg0 + 0x58) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x5C) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x60) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x64) = 0.0f;
        *(u8 *)((u8 *)arg3 + 0) = (u8) (*(u8 *)((u8 *)arg3 + 0) & 0xFFFE);
        *(s32 *)((u8 *)arg0 + 0x68) = (s32) (*(s32 *)((u8 *)arg0 + 0x68) & ~6);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15131B7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131B7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131C2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131C84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131D4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131D9C.s")
extern f32 D_800BE9A4;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15131DEC CURRENT (10) */
s32 func_15131DEC(void *arg0, s32 arg1) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0xA8);
    temp_fa0 = sqrtf(temp_fv1) * *(f32 *)((u8 *)arg0 + 0xB0);
    *(f32 *)((u8 *)arg0 + 0x3C) = temp_fa0;
    *(f32 *)((u8 *)arg0 + 0x38) = temp_fa0;
    *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) (*(f32 *)((u8 *)arg0 + 0xB4) - (*(f32 *)((u8 *)arg0 + 0xB8) * temp_fv1 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0xA8) = (f32) (temp_fv1 + D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0xAC) < *(f32 *)((u8 *)arg0 + 0xA8)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15131DEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131DEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131EE4.s")
