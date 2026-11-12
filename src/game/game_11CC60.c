#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_11CC60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EFA4C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150EF7B0(void *arg0) {
    void **var_s1;
    void **base;
    s32 var_s0;

    var_s0 = 0;
    base = (void **)((u8 *)arg0 + 0x110);
    var_s1 = base;
    do {
        if (var_s1[7] != 0) {
            func_1516972C(var_s1[7]);
        }
        var_s0 += 4;
        var_s1 = (void **)((u8 *)var_s1 + 4);
    } while (var_s0 != 8);
    if (base[9] != 0) {
        func_1516972C(base[9]);
    }
    if (base[10] != 0) {
        func_1516972C(base[10]);
    }
    if (base[11] != 0) {
        func_1516972C(base[11]);
    }
    func_1513CA6C(arg0);
}
void func_150EF860(void *arg0) {
    void **var_s1;
    void **base;
    s32 var_s0;

    var_s0 = 0;
    base = (void **)((u8 *)arg0 + 0x110);
    var_s1 = base;
    do {
        if (var_s1[7] != 0) {
            func_1516979C(var_s1[7]);
        }
        var_s0 += 4;
        var_s1 = (void **)((u8 *)var_s1 + 4);
    } while (var_s0 != 8);
    if (base[9] != 0) {
        func_1516979C(base[9]);
    }
    if (base[10] != 0) {
        func_1516979C(base[10]);
    }
    if (base[11] != 0) {
        func_1516979C(base[11]);
    }
    func_1513CAA0(arg0);
}
void func_150EF910(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *p = arg0 + 0x110;

    if (arg2 == 0) {
        s32 a;
        s32 b;
        s32 c;
        s32 d;

        a = *(s32 *)p;
        b = *(s32 *)arg1;
        c = p[4];
        d = arg1[4];
        if ((a == b) || (d == c)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)p) {
            *(s32 *)p = *(s32 *)(arg1 + 4);
            p[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)p) {
            *(s32 *)p = *(s32 *)arg1;
            p[4] = arg1[8];
        }
        if (*(s32 *)arg1 == *(s32 *)(p + 8)) {
            *(s32 *)(p + 8) = *(s32 *)(arg1 + 4);
            p[0xC] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)(p + 8)) {
            s32 id = *(s32 *)arg1;

            *(s32 *)(p + 8) = id;
            p[0xC] = arg1[8];
        }
    } else if (arg2 == 0x43) {
        if (((*(s32 *)arg1 == *(s32 *)p) || (arg1[4] == p[4])) && (arg1[5] == p[0xD])) {
            func_1516972C(arg0);
        }
    }
}
void func_15143134(f32 *, f32 *, s32);
extern f32 D_800A1620[][3];
extern u8 D_800A1638[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EFA4C CURRENT (1190) */
s32 func_150EFA4C(u8 *arg0) {
    typedef struct { s32 words[3]; } Copy12;
    u8 *parent;
    u8 temp_v0;
    u8 *temp_t0;
    u8 *temp_t1;
    u8 *temp_v1;

    parent = *(u8 **)(arg0 + 0x60);
    temp_v1 = *(u8 **)(parent + 8);
    temp_t0 = temp_v1 + 0x110;
    if (temp_v1[0x128] & 1) {
        temp_t1 = *(u8 **)temp_t0;
        if (*(s32 *)(temp_t1 + 0x1D4) != 0) {
            temp_v0 = temp_t0[0xD];
            *(Copy12 *)(arg0 + 0x30) = *(Copy12 *)(temp_v1 + 0x34);
            *(Copy12 *)(arg0 + 0x3C) = *(Copy12 *)(temp_v1 + 0x40);
            *(f32 *)(arg0 + 0x54) = *(f32 *)(temp_t0 + 0x3C);
            *(f32 *)(arg0 + 0x58) = *(f32 *)(temp_t0 + 0x40);
            func_15143134(D_800A1620[temp_v0], (f32 *)(arg0 + 0x48),
                          (D_800A1638[temp_v0] << 6) +
                              *(s32 *)(temp_t1 + 0x1D4));
            *(f32 *)(arg0 + 0x48) -= *(f32 *)(arg0 + 0x30);
            *(f32 *)(arg0 + 0x4C) -= *(f32 *)(arg0 + 0x34);
            arg0[0x1C] |= 2;
            *(f32 *)(arg0 + 0x50) -= *(f32 *)(arg0 + 0x38);
            return 1;
        } else {
            arg0[0x1C] &= ~2;
            return 1;
        }
    } else {
        arg0[0x1C] &= ~2;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EFA4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11CC60/func_150EFA4C.s")
