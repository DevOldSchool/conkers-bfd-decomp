#include "types.h"

/*
 * Reviewed source unit: src/game/game_439B0.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15016588
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15016588 CURRENT (328) */
void func_15016588(void) {
    s32 var_s0;
    s32 var_s1;
    s32 mask;
    struct { s32 result; volatile s32 mask; } query;

    func_100226F0(D_800BE580, 8);
    var_s1 = -1;
    var_s0 = 0;
    mask = query.mask;

    do {
        if (!(var_s0 & 7)) {
            mask = 1;
            var_s1++;
        } else {
            mask *= 2;
        }

        func_1502B020(&query.result, 3, 0x1A, D_800BEAAB, var_s0);
        var_s0++;
        if (query.result != 0) {
            D_800BE580[var_s1] |= mask;
        }
    } while (var_s0 != 0x43);
    query.mask = mask;

}
#endif /* CONKER_DEFERRED_CANDIDATE func_15016588 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_439B0/func_15016588.s")
