#include "types.h"

/*
 * Reviewed source unit: src/game/game_D5650.c
 * Boundary evidence: docs/evidence/game_raw_handwritten_entry_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A81A0
 * - func_150A81D0
 * - func_150A94DC
 * - func_150A9984
 * - func_150A9B0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s64 **D_80088544;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A81A0 CURRENT (3370) */
void func_150A81A0(s64 *arg0, s64 *arg1) {
    s64 *temp_a3;
    s64 *var_a0;
    s64 *var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_a3 = (void *)(var_a1 + 0x40);
    do {
        *var_a0 = *var_a1;
        var_a0 += 8;
        var_a1 += 8;
    } while (var_a1 != temp_a3);
    *D_80088544 = var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A81A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A81A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A81D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A94DC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A9984 CURRENT (11665) */
void func_150A9984(void *arg0, s32 arg1) {
    u8 *p = arg0;
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;
    s32 fifth;
    s32 sixth;
    s32 seventh;
    s32 eighth;
    s32 ninth;
    s32 tenth;
    s32 eleventh;
    s32 last;
    f32 saved24;
    f32 saved34;

    do {
        arg1--;
        first = (s32)(*(f32 *)(p + 0) * 65536.0f);
        second = (s32)(*(f32 *)(p + 4) * 65536.0f);
        saved24 = *(f32 *)(p + 0x24);
        *(s16 *)(p + 0) = (u32)first >> 16;
        third = (s32)(*(f32 *)(p + 8) * 65536.0f);
        *(s16 *)(p + 2) = (u32)second >> 16;
        saved34 = *(f32 *)(p + 0x34);
        *(s32 *)(p + 4) = third & 0xFFFF0000;
        fourth = (s32)(*(f32 *)(p + 0x10) * 65536.0f);
        *(s16 *)(p + 0x20) = first;
        *(s16 *)(p + 0x22) = second;
        *(s32 *)(p + 0x24) = third << 16;
        fifth = (s32)(*(f32 *)(p + 0x14) * 65536.0f);
        *(s16 *)(p + 0x28) = fourth;
        *(s16 *)(p + 8) = (u32)fourth >> 16;
        *(s16 *)(p + 0x2A) = fifth;
        sixth = (s32)(*(f32 *)(p + 0x18) * 65536.0f);
        *(s16 *)(p + 0xA) = (u32)fifth >> 16;
        *(s32 *)(p + 0x2C) = sixth << 16;
        *(s32 *)(p + 0xC) = sixth & 0xFFFF0000;
        seventh = (s32)(*(f32 *)(p + 0x20) * 65536.0f);
        *(s16 *)(p + 0x30) = seventh;
        eighth = (s32)(saved24 * 65536.0f);
        *(s16 *)(p + 0x10) = (u32)seventh >> 16;
        *(s16 *)(p + 0x32) = eighth;
        ninth = (s32)(*(f32 *)(p + 0x28) * 65536.0f);
        *(s16 *)(p + 0x12) = (u32)eighth >> 16;
        *(s32 *)(p + 0x34) = ninth << 16;
        *(s32 *)(p + 0x14) = ninth & 0xFFFF0000;
        tenth = (s32)(*(f32 *)(p + 0x30) * 65536.0f);
        eleventh = (s32)(saved34 * 65536.0f);
        *(s16 *)(p + 0x38) = tenth;
        *(s16 *)(p + 0x18) = (u32)tenth >> 16;
        *(s16 *)(p + 0x3A) = eleventh;
        *(s16 *)(p + 0x1A) = (u32)eleventh >> 16;
        last = (s32)(*(f32 *)(p + 0x38) * 65536.0f);
        p += 0x40;
        *(s32 *)(p - 4) = last << 16;
        *(s32 *)(p - 0x24) = (last & 0xFFFF0000) + 1;
    } while (arg1 != 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A9984 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A9984.s")
f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern f32 D_8009F6D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A9B0C CURRENT (9318) */
void func_150A9B0C(f32 *arg0, f32 arg1, f32 arg2, f32 arg3,
                   f32 arg4, f32 arg5, f32 arg6) {
    f32 sin_x;
    f32 cos_x;
    f32 neg_cos_x;
    f32 sin_y;
    f32 cos_y;
    f32 neg_cos_y;
    f32 sin_z;
    f32 cos_z;
    f32 neg_cos_z;
    f32 temp_1;
    f32 temp_2;
    f32 temp_3;
    f32 temp_4;

    arg1 *= D_8009F6D0;
    sin_x = func_150AD780(arg1);
    cos_x = func_150AD78C(arg1);
    neg_cos_x = -cos_x;
    arg2 *= D_8009F6D0;
    sin_y = func_150AD780(arg2);
    cos_y = func_150AD78C(arg2);
    neg_cos_y = -cos_y;
    arg3 *= D_8009F6D0;
    sin_z = func_150AD780(arg3);
    cos_z = func_150AD78C(arg3);
    neg_cos_z = -cos_z;

    temp_1 = sin_x * sin_z;
    temp_2 = neg_cos_x * sin_z;
    temp_3 = sin_x * neg_cos_z;
    temp_4 = neg_cos_x * neg_cos_z;
    arg0[0] = (cos_z * sin_y) * arg4;
    arg0[1] = cos_z * arg4;
    arg0[2] = (cos_z * neg_cos_y) * arg4;
    arg0[4] = ((temp_3 * sin_y) + (cos_x * cos_y)) * arg5;
    arg0[5] = temp_1 * arg5;
    arg0[6] = ((temp_3 * neg_cos_y) + (cos_x * sin_y)) * arg5;
    arg0[8] = ((temp_4 * sin_y) + (sin_x * cos_y)) * arg6;
    arg0[9] = temp_2 * arg6;
    arg0[10] = ((temp_4 * neg_cos_y) + (sin_x * sin_y)) * arg6;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A9B0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A9B0C.s")
