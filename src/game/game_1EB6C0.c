#include "types.h"

/*
 * Reviewed source unit: src/game/game_1EB6C0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BE210
 * - func_151BE4B8
 * - func_151BE558
 * - func_151BE644
 * - func_151BE6CC
 * - func_151BE7C8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150ADA20();                                /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800AA89C;
extern f32 D_800AA8A0;
extern f32 D_800AA8A4;
extern f32 D_800AA8A8;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BE210 CURRENT (2235) */
s32 func_151BE210(u8 *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    u8 *temp_s0;
    u8 *temp_s0_2;

    *(f32 *)((u8 *)arg0 + 0x134) = (f32) (*(f32 *)((u8 *)arg0 + 0x134) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x134) < 0.0f) {
        temp_s0 = (void *)(arg0 + 0x110);
        *(f32 *)((u8 *)temp_s0 + 0x24) = (f32) (func_150ADA68() * 4.0f);
        *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_s0 + 0x10)) + *(f32 *)((u8 *)temp_s0 + 8));
    }
    temp_s0_2 = (void *)(arg0 + 0x110);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 + ((*(f32 *)((u8 *)temp_s0_2 + 0x18) - temp_fv0) * D_800AA89C));
    *(f32 *)((u8 *)temp_s0_2 + 0x28) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 0x28) - D_800BE9A4);
    if (*(f32 *)((u8 *)temp_s0_2 + 0x28) < 0.0f) {
        *(f32 *)((u8 *)temp_s0_2 + 0x28) = (f32) (func_150ADA68() * 9.0f);
        if (func_150ADA20() & 1) {
            *(f32 *)((u8 *)temp_s0_2 + 0x1C) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_s0_2 + 0x14)) + *(f32 *)((u8 *)temp_s0_2 + 0xC));
        } else {
            *(f32 *)((u8 *)temp_s0_2 + 0x1C) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_s0_2 + 0x20)) + *(f32 *)((u8 *)temp_s0_2 + 0xC));
        }
    }
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0_2 + ((*(f32 *)((u8 *)temp_s0_2 + 0x1C) - temp_fv0_2) * D_800AA8A0));
    *(f32 *)((u8 *)temp_s0_2 + 0x38) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 0x38) - D_800BE9A4);
    if (*(f32 *)((u8 *)temp_s0_2 + 0x38) < 0.0f) {
        *(f32 *)((u8 *)temp_s0_2 + 0x38) = (f32) (func_150ADA68() * 10.0f);
        *(f32 *)((u8 *)temp_s0_2 + 0x34) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_s0_2 + 0x30)) + *(f32 *)((u8 *)temp_s0_2 + 0x2C));
    }
    temp_fv0_3 = *(f32 *)((u8 *)temp_s0_2 + 0x3C);
    *(f32 *)((u8 *)temp_s0_2 + 0x3C) = (f32) (temp_fv0_3 + ((*(f32 *)((u8 *)temp_s0_2 + 0x34) - temp_fv0_3) * D_800AA8A8));
    *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (u32) *(f32 *)((u8 *)temp_s0_2 + 0x3C);
    temp_fv1 = *(f32 *)((u8 *)temp_s0_2 + 0x40);
    temp_fa0 = *(f32 *)((u8 *)temp_s0_2 + 0x44);
    *(f32 *)((u8 *)temp_s0_2 + 0x40) = (f32) (temp_fv1 + ((*(f32 *)((u8 *)temp_s0_2 + 0x48) - temp_fv1) * D_800AA8A4));
    *(f32 *)((u8 *)temp_s0_2 + 0x44) = (f32) (temp_fa0 + ((*(f32 *)((u8 *)temp_s0_2 + 0x4C) - temp_fa0) * D_800AA8A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BE210 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE210.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE4B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE558.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_151BE604(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BE644 CURRENT (30) */
void func_151BE644(void *arg0) {
    void *temp_v0;
    s32 temp_v1;
    s32 temp_t7;

    temp_v0 = (u8 *)arg0 + 0x110;
    if (*(s32 *)((u8 *)arg0 + 0x160) != 0) {
        temp_v1 = *(s32 *)((u8 *)temp_v0 + 0x50);
        temp_v1 += 0x28;
        temp_t7 = *(u8 *)((u8 *)temp_v0 + 5);
        *(s32 *)((u8 *)temp_v1 + (temp_t7 << 2) + 8) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BE644 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE644.s")
void func_151BE644(void *arg0);
void func_1513CA6C(void *arg0);
void func_1513CAA0(void *arg0);

void func_151BE674(void *arg0) {
    func_151BE644(arg0);
    func_1513CA6C(arg0);
}
void func_151BE6A0(void *arg0) {
    func_151BE644(arg0);
    func_1513CAA0(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE6CC.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_151BE788(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x180, arg0 + 0x184, arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BE7C8 CURRENT (30) */
void func_151BE7C8(void *arg0) {
    void *temp_v0;
    s32 temp_v1;
    s32 temp_t7;
    s32 temp_t8;

    temp_v0 = (u8 *)arg0 + 0x170;
    if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
        temp_v1 = *(s32 *)((u8 *)temp_v0 + 8);
        temp_t7 = *(u8 *)((u8 *)temp_v0 + 0xC);
        temp_t8 = temp_t7 << 2;
        temp_v1 += 0x28;
        *(s32 *)((u8 *)temp_v1 + temp_t8 + 0x10) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BE7C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE7C8.s")
void func_151BE7C8(void *arg0);
void func_151411A4(void *arg0);
void func_151411C4(void *arg0);

void func_151BE7F8(void *arg0) {
    func_151BE7C8(arg0);
    func_151411A4(arg0);
}
void func_151BE824(void *arg0) {
    func_151BE7C8(arg0);
    func_151411C4(arg0);
}
