#include "types.h"

/*
 * Reviewed source unit: src/game/game_191C30.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15164780
 * - func_1516489C
 * - func_15164F0C
 * - func_15165628
 * - func_151658DC
 * - func_15165BB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
extern s32 D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15164780 CURRENT (88) */
void *func_15164780(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    void *sp24;
    void *temp_v0;
    void *temp_v1;

    temp_v1 = *(void **)(D_800DBFF0 + (arg0[6] * 0x9A0) + 0x3D0);
    if (temp_v1 != 0) {
        temp_v0 = *(void **)((u8 *)temp_v1 + 0x31C);
        if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x198) != 0)) {
            return 0;
        }
    }
    temp_v0 = func_15167A68(0x39, arg3, arg1 + 0x68, 1, arg2, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    sp24 = temp_v0;
    func_10022EC0((u8 *)temp_v0 + 0x10, arg0, 0x38);
    *(s8 *)((u8 *)sp24 + 0x60) = 1;
    *(s8 *)((u8 *)sp24 + 0x61) = 1;
    *(s8 *)((u8 *)sp24 + 0x62) = 1;
    *(s8 *)((u8 *)sp24 + 0x63) = 1;
    *(s8 *)((u8 *)sp24 + 0x64) = 1;
    *(s8 *)((u8 *)sp24 + 0x65) = 1;
    *(f32 *)((u8 *)sp24 + 0x48) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x4C) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x50) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x54) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x58) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x5C) = 0.0f;
    return sp24;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15164780 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15164780.s")
void func_15164888(u8 *arg0) {
    arg0[0x10] |= 2;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_1516489C.s")
void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800DCDE0;

void func_15164EE4(void) {
    func_100226F0(&D_800DCDE0, 0x60);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15164F0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15165628.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151658DC CURRENT (8265) */
s32 func_151658DC(u8 *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v1 = 1;
    temp_v0 = (void *)(arg0 + 0x68);
    *(f32 *)((u8 *)arg0 + 0x104) = (f32) (*(f32 *)((u8 *)arg0 + 0x104) + D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x104) < *(f32 *)((u8 *)arg0 + 0xF8)) {
        temp_v0_2 = (void *)(arg0 + 0x68);
        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x68) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x1C) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 4) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 8) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0xC) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x10) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x14) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x18) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x1C) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x20) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x24) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x28) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x2C) * *(f32 *)((u8 *)temp_v0_2 + 0x9C));
    } else {
        temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0x9C);
        temp_fa0 = *(f32 *)((u8 *)temp_v0 + 0x90) + *(f32 *)((u8 *)temp_v0 + 0x94);
        if (temp_fv1 < temp_fa0) {
            *(f32 *)((u8 *)arg0 + 0x18) = (f32) *(f32 *)((u8 *)temp_v0 + 0x60);
            *(f32 *)((u8 *)arg0 + 0x1C) = (f32) *(f32 *)((u8 *)temp_v0 + 0x64);
            *(f32 *)((u8 *)arg0 + 0x20) = (f32) *(f32 *)((u8 *)temp_v0 + 0x68);
            *(f32 *)((u8 *)arg0 + 0x24) = (f32) *(f32 *)((u8 *)temp_v0 + 0x6C);
            *(f32 *)((u8 *)arg0 + 0x28) = (f32) *(f32 *)((u8 *)temp_v0 + 0x70);
            *(f32 *)((u8 *)arg0 + 0x2C) = (f32) *(f32 *)((u8 *)temp_v0 + 0x74);
            *(f32 *)((u8 *)arg0 + 0x30) = (f32) *(f32 *)((u8 *)temp_v0 + 0x78);
            *(f32 *)((u8 *)arg0 + 0x34) = (f32) *(f32 *)((u8 *)temp_v0 + 0x7C);
            *(f32 *)((u8 *)arg0 + 0x38) = (f32) *(f32 *)((u8 *)temp_v0 + 0x80);
            *(f32 *)((u8 *)arg0 + 0x3C) = (f32) *(f32 *)((u8 *)temp_v0 + 0x84);
            *(f32 *)((u8 *)arg0 + 0x40) = (f32) *(f32 *)((u8 *)temp_v0 + 0x88);
            *(f32 *)((u8 *)arg0 + 0x44) = (f32) *(f32 *)((u8 *)temp_v0 + 0x8C);
        } else if (temp_fv1 < (temp_fa0 + *(f32 *)((u8 *)temp_v0 + 0x98))) {
            temp_fv0 = temp_fv1 - temp_fa0;
            *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x60) - (*(f32 *)((u8 *)temp_v0 + 0x3C) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x1C) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x64) - (*(f32 *)((u8 *)temp_v0 + 0x40) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x68) - (*(f32 *)((u8 *)temp_v0 + 0x44) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x6C) - (*(f32 *)((u8 *)temp_v0 + 0x30) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x70) - (*(f32 *)((u8 *)temp_v0 + 0x34) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x74) - (*(f32 *)((u8 *)temp_v0 + 0x38) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x78) - (*(f32 *)((u8 *)temp_v0 + 0x54) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x7C) - (*(f32 *)((u8 *)temp_v0 + 0x58) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x80) - (*(f32 *)((u8 *)temp_v0 + 0x5C) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x84) - (*(f32 *)((u8 *)temp_v0 + 0x48) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x88) - (*(f32 *)((u8 *)temp_v0 + 0x4C) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x8C) - (*(f32 *)((u8 *)temp_v0 + 0x50) * temp_fv0));
        } else {
            var_v1 = 0;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151658DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_151658DC.s")
f32 func_15165BB0(void *, void *, f32, f32, f32);

void func_15165B80(u8 *arg0) {
    func_15165BB0(arg0, arg0 + 0x108, *(f32 *)((u8 *)arg0 + 0x114), *(f32 *)((u8 *)arg0 + 0x118), *(f32 *)((u8 *)arg0 + 0x11C));
}
f32 func_15143E64(f32 *, void *);                   /* extern */
void *func_15144B34(u8, void *);                    /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15165BB0 CURRENT (1233) */
f32 func_15165BB0(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sp28;
    f32 sp20;
    f32 sp24;
    f32 temp_fv0;
    f32 var_fv1;
    void *temp_v0;

    temp_v0 = func_15144B34(*(u8 *)((u8 *)arg0 + 0x16), arg0);
    sp20 = *(f32 *)((u8 *)arg1 + 0) - *(f32 *)((u8 *)temp_v0 + 0);
    sp24 = *(f32 *)((u8 *)arg1 + 4) - *(f32 *)((u8 *)temp_v0 + 4);
    sp28 = *(f32 *)((u8 *)arg1 + 8) - *(f32 *)((u8 *)temp_v0 + 8);
    temp_fv0 = func_15143E64(&sp20, arg1);
    if (temp_fv0 < arg2) {
        var_fv1 = 1.0f;
    } else if ((arg2 + arg3) < temp_fv0) {
        var_fv1 = 0.0f;
    } else {
        var_fv1 = 1.0f - ((temp_fv0 - arg2) * arg4);
    }
    return var_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15165BB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15165BB0.s")
