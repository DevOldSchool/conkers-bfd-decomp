#include "types.h"

/*
 * Reviewed source unit: src/game/game_11CC60.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EF7B0
 * - func_150EF860
 * - func_150EF910
 * - func_150EFA4C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_1516972C(void *arg0);
extern void func_1513CA6C(void *arg0);
extern void func_1516979C(void *arg0);
extern void func_1513CAA0(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EF7B0 CURRENT (717) */
void func_150EF7B0(void *arg0) {
    void **var_s1;
    s32 var_s0;

    var_s0 = 0;
    var_s1 = (void **)((u8 *)arg0 + 0x110);
    do {
        if (var_s1[7] != 0) {
            func_1516972C(var_s1[7]);
        }
        var_s0 += 4;
        var_s1 = (void **)((u8 *)var_s1 + 4);
    } while (var_s0 != 8);
    if (var_s1[1] != 0) {
        func_1516972C(var_s1[1]);
    }
    if (var_s1[2] != 0) {
        func_1516972C(var_s1[2]);
    }
    if (var_s1[3] != 0) {
        func_1516972C(var_s1[3]);
    }
    func_1513CA6C(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EF7B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11CC60/func_150EF7B0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EF860 CURRENT (717) */
void func_150EF860(void *arg0) {
    void **var_s1;
    s32 var_s0;

    var_s0 = 0;
    var_s1 = (void **)((u8 *)arg0 + 0x110);
    do {
        if (var_s1[7] != 0) {
            func_1516979C(var_s1[7]);
        }
        var_s0 += 4;
        var_s1 = (void **)((u8 *)var_s1 + 4);
    } while (var_s0 != 8);
    if (var_s1[1] != 0) {
        func_1516979C(var_s1[1]);
    }
    if (var_s1[2] != 0) {
        func_1516979C(var_s1[2]);
    }
    if (var_s1[3] != 0) {
        func_1516979C(var_s1[3]);
    }
    func_1513CAA0(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EF860 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11CC60/func_150EF860.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EF910 CURRENT (2970) */
void func_150EF910(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_a3;

    temp_t6 = arg2;
    temp_a3 = arg0;
    if (temp_t6 == 0) {
        arg0 += 0x110;
        temp_v0 = arg0;
        if ((*(s32 *)temp_v0 == *(s32 *)arg1) ||
            (arg1[4] == temp_v0[4])) {
            func_1516972C(temp_a3);
        }
    } else if (temp_t6 == 0x2D) {
        arg0 += 0x110;
        temp_v0 = arg0;
        temp_a2 = *(s32 *)temp_v0;
        temp_v1 = *(s32 *)arg1;
        if (temp_v1 == temp_a2) {
            *(s32 *)temp_v0 = *(s32 *)(arg1 + 4);
            temp_v0[4] = arg1[9];
        } else if ((s32)arg1[4] == temp_a2) {
            *(s32 *)temp_v0 = temp_v1;
            temp_v0[4] = arg1[8];
        }
        temp_a2_2 = *(s32 *)(temp_v0 + 8);
        if (*(s32 *)arg1 == temp_a2_2) {
            *(s32 *)(temp_v0 + 8) = *(s32 *)(arg1 + 4);
            temp_v0[0xC] = arg1[9];
            return;
        }
        if ((s32)arg1[4] == temp_a2_2) {
            *(s32 *)(temp_v0 + 8) = *(s32 *)arg1;
            temp_v0[0xC] = arg1[8];
        }
    } else {
        arg0 += 0x110;
        temp_v0_2 = arg0;
        if ((temp_t6 == 0x43) &&
            ((*(s32 *)arg1 == *(s32 *)temp_v0_2) ||
             (arg1[4] == temp_v0_2[4])) &&
            (arg1[5] == temp_v0_2[0xD])) {
            func_1516972C(temp_a3);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EF910 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11CC60/func_150EF910.s")
void func_15143134(f32 *, f32 *, s32);
extern f32 D_800A1620[][3];
extern u8 D_800A1638[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EFA4C CURRENT (1875) */
s32 func_150EFA4C(u8 *arg0) {
    u8 temp_v0;
    u8 *temp_t0;
    u8 *temp_t1;
    u8 *temp_v1;

    temp_v1 = *(u8 **)(*(u8 **)(arg0 + 0x60) + 8);
    temp_t0 = temp_v1 + 0x110;
    if (temp_v1[0x128] & 1) {
        temp_t1 = *(u8 **)temp_t0;
        if (*(s32 *)(temp_t1 + 0x1D4) != 0) {
            temp_v0 = temp_t0[0xD];
            *(s32 *)(arg0 + 0x30) = *(s32 *)(temp_v1 + 0x34);
            *(s32 *)(arg0 + 0x34) = *(s32 *)(temp_v1 + 0x38);
            *(s32 *)(arg0 + 0x38) = *(s32 *)(temp_v1 + 0x3C);
            *(s32 *)(arg0 + 0x3C) = *(s32 *)(temp_v1 + 0x40);
            *(s32 *)(arg0 + 0x40) = *(s32 *)(temp_v1 + 0x44);
            *(s32 *)(arg0 + 0x44) = *(s32 *)(temp_v1 + 0x48);
            *(f32 *)(arg0 + 0x54) = *(f32 *)(temp_t0 + 0x3C);
            *(f32 *)(arg0 + 0x58) = *(f32 *)(temp_t0 + 0x40);
            func_15143134(D_800A1620[temp_v0], (f32 *)(arg0 + 0x48),
                          (D_800A1638[temp_v0] << 6) +
                              *(s32 *)(temp_t1 + 0x1D4));
            *(f32 *)(arg0 + 0x48) -= *(f32 *)(arg0 + 0x30);
            *(f32 *)(arg0 + 0x4C) -= *(f32 *)(arg0 + 0x34);
            arg0[0x1C] |= 2;
            *(f32 *)(arg0 + 0x50) -= *(f32 *)(arg0 + 0x38);
        } else {
            arg0[0x1C] &= 0xFD;
        }
    } else {
        arg0[0x1C] &= 0xFD;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EFA4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11CC60/func_150EFA4C.s")
