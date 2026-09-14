#include "types.h"

/*
 * Reviewed source unit: src/game/game_12B050.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FDBA0
 * - func_150FDC2C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_1513EDE4(s16);                           /* extern */
void func_150FDC2C(s32 arg0);
void func_1513CA6C(s32 arg0);
void func_1513CAA0(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FDBA0 CURRENT (470) */
void *func_150FDBA0(void *arg0, s16 arg1) {
    void *temp_v0;

    temp_v0 = func_1513EDE4(arg1);
    if (temp_v0 != 0) {
        *(s16 *)((u8 *)temp_v0 + 8) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x124);
        *(s16 *)((u8 *)temp_v0 + 0x18) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x128);
        *(s16 *)((u8 *)temp_v0 + 0x28) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x128);
        *(s16 *)((u8 *)temp_v0 + 0x38) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x124);
    }
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FDBA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B050/func_150FDBA0.s")
void func_1516972C(s32, s32);
void func_100111C8(u16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FDC2C CURRENT (931) */
void func_150FDC2C(s32 arg0) {
    void *sp18;
    s32 temp_a0;
    u16 temp_a0_2;
    u16 temp_a0_3;
    void *var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x134) != 0) {
        func_1516972C(*(s32 *)((u8 *)arg0 + 0x134), arg0);
    }
    var_v0 = (void *)(arg0 + 0x110);
    temp_a0 = *(s32 *)((u8 *)var_v0 + 0x28);
    if (temp_a0 != 0) {
        sp18 = var_v0;
        func_1516972C(temp_a0, arg0);
    }
    temp_a0_2 = *(u16 *)((u8 *)var_v0 + 0x54);
    if (temp_a0_2 != 0) {
        sp18 = var_v0;
        func_100111C8(temp_a0_2);
    }
    temp_a0_3 = *(u16 *)((u8 *)var_v0 + 0x56);
    if (temp_a0_3 != 0) {
        func_100111C8(temp_a0_3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FDC2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B050/func_150FDC2C.s")
void func_150FDCAC(s32 arg0) {
    func_150FDC2C(arg0);
    func_1513CA6C(arg0);
}
void func_150FDCD8(s32 arg0) {
    func_150FDC2C(arg0);
    func_1513CAA0(arg0);
}
