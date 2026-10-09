#include "types.h"

/*
 * Reviewed source unit: src/game/game_439B0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_compact_multi_function_units.md
 */

void func_100226F0(void *, s32);
extern s8 D_800D1940;
extern s8 D_800D1941;
extern s32 D_800D1944;
extern s32 D_800D1948;
extern s32 D_800D194C;
extern s32 D_800D1950;
extern u8 D_800D1958[];
extern f32 D_800D1988;
extern f32 D_800D198C;
extern f32 D_800D1990;
extern s8 D_800D1994;
extern s8 D_800D1995;
extern s32 D_800D1998;

void func_15016500(void) {
    D_800D1940 = 0;
    D_800D1941 = 0;
    D_800D1944 = 0;
    D_800D1948 = 0;
    D_800D194C = 0;
    D_800D1950 = 0;
    func_100226F0(D_800D1958, 0x30);
    D_800D1988 = 0.0f;
    D_800D198C = 0.0f;
    D_800D1990 = 0.0f;
    D_800D1994 = 0;
    D_800D1995 = 0;
    D_800D1998 = 0;
}

void func_100226F0(void *arg0, s32 arg1);
s32 func_1502B020(s32 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4);

extern u8 D_800BE580[8];
extern u8 D_800BEAAB;

void func_15016588(void) {
    extern u8 D_800BE580[];
    s32 i;
    s32 byte;
    s32 bit;
    s32 out;

    func_100226F0(D_800BE580, 8);
    byte = -1;
    for (i = 0; i != 0x43; i++) {
        if ((i & 7) == 0) {
            bit = 1;
            byte++;
        } else {
            bit <<= 1;
        }
        func_1502B020(&out, 3, 0x1A, D_800BEAAB, i);
        if (out != 0) {
            D_800BE580[byte] |= bit;
        }
    }
}
