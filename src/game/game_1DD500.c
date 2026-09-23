#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DD500.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B0050
 * - func_151B01B8
 * - func_151B03B8
 * - func_151B09BC
 * - func_151B0B88
 * - func_151B118C
 * - func_151B14AC
 * - func_151B1828
 * - func_151B1918
 * - func_151B19A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_800AA28C;
extern f32 D_800AA290;
extern f32 D_800AA294;
extern f32 D_800AA298;
extern f32 D_800AA29C;
f32 func_150ADA68(void);
u32 func_150ADA20(void);
void func_15143794(s16, s16, f32, void *);
void func_151DA6F8(f32 *, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B0050 CURRENT (2192) */
s32 func_151B0050(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s16 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, u8 arg14) {
    f32 position[3];
    f32 velocity[3];
    volatile f32 random_float0;
    u32 random_int0;
    u32 random_int1;
    f32 random_float1;
    u32 random_int2;

    position[0] = arg2;
    position[1] = arg3;
    position[2] = arg4;
    func_15143794(arg9, arg8, (func_150ADA68() * D_800AA28C) + D_800AA290, velocity);
    random_float0 = func_150ADA68();
    random_int0 = func_150ADA20();
    random_int1 = func_150ADA20();
    random_float1 = func_150ADA68();
    random_int2 = func_150ADA20();
    func_151DA6F8(position, velocity, (random_float0 * 0.0f) + D_800AA294, (s16) ((random_int0 % 20U) + 0x1F), (random_int1 % 101U) + 0x9B, (random_float1 * D_800AA298) + D_800AA29C, (random_int2 & 1) + 3, 1, 1.0f, 1.0f, 0, 0, 0, 0x10, 0xF, 0, arg14, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B0050 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B0050.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B01B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B03B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B09BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B0B88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B118C.s")
s32 func_151B1478(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B14AC.s")
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B1828 CURRENT (917) */
s32 func_151B1828(u8 *arg0) {
    f32 sp24;
    void *sp1C;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 temp_a0;
    u8 *temp_v1;

    temp_a0 = *(u8 *)((u8 *)arg0 + 0x120) + (*(s8 *)((u8 *)arg0 + 0x122) * D_800BE9E4);
    *(u8 *)((u8 *)arg0 + 0x120) = temp_a0;
    *(u8 *)((u8 *)arg0 + 0x121) = (u8) (*(u8 *)((u8 *)arg0 + 0x121) + (*(s8 *)((u8 *)arg0 + 0x123) * D_800BE9E4));
    sp24 = func_151423D8((temp_a0 - 0x40) & 0xFF);
    temp_v1 = (void *)(arg0 + 0x110);
    sp1C = temp_v1;
    temp_fv0 = func_151423D8((*(u8 *)((u8 *)temp_v1 + 0x11) - 0x40) & 0xFF);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv1 + (((*(f32 *)((u8 *)temp_v1 + 0x14) + (*(f32 *)((u8 *)temp_v1 + 0x1C) * sp24)) - temp_fv1) * 0.5f));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 + (((*(f32 *)((u8 *)temp_v1 + 0x18) + (*(f32 *)((u8 *)temp_v1 + 0x20) * temp_fv0)) - temp_fa0) * 0.5f));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B1828 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1828.s")
void func_1516972C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B1918 CURRENT (520) */
void func_151B1918(s32 arg0) {
    s32 var_s3;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s2;

    var_s2 = (u8 *)(arg0 + 0x28);
    *(s32 *)((u8 *)arg0 + 0x30) = 0;
    var_s0 = var_s2 + 0xC;
    var_s3 = 0;
    *(f32 *)((u8 *)arg0 + 0xB8) = 0.0f;
    do {
        var_s1 = var_s0;
        if (*(s32 *)(var_s2 + 0xC) != 0) {
            func_1516972C(*(s32 *)var_s0);
        }
        *(s32 *)(var_s1 + 4) = 0;
        *(s32 *)(var_s1 + 8) = 0;
        var_s3 += 0xC;
        var_s2 += 0xC;
        var_s0 += 0xC;
    } while (var_s3 != 0x84);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B1918 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1918.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B19A4 CURRENT (10) */
void func_151B19A4(void *arg0, void *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x28);
    if ((arg2 == 0) || (arg2 == 0x13)) {
        if ((temp_v1 == *(s32 *)arg1) ||
            (*(u8 *)((u8 *)arg0 + 0x2C) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C((s32)arg0);
        }
    } else {
        temp_v0 = (u8 *)arg0 + 0x28;
        if (arg2 == 0x2D) {
            temp_a0 = *(s32 *)temp_v0;
            temp_v1 = *(s32 *)arg1;
            if (temp_v1 == temp_a0) {
                *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
                *(s32 *)temp_v0 = temp_v1;
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B19A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B19A4.s")
void func_151B1918(s32 arg0);
void func_1514933C(s32 arg0);
void func_15149368(s32 arg0);

void func_151B1A58(s32 arg0) {
    func_151B1918(arg0);
    func_1514933C(arg0);
}
void func_151B1A84(s32 arg0) {
    func_151B1918(arg0);
    func_15149368(arg0);
}
