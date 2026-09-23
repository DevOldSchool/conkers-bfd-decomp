#include "types.h"

/*
 * Reviewed source unit: src/game/game_2DDF0.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15000940
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800A2CD0[];
extern u8 D_800A2CE8[];
extern u8 D_800A2CEC[];
extern u8 D_800A2D04[];
extern u8 *D_800B0DF0;
extern u8 D_800D9E70[];
extern u8 D_800D9E88[];
extern u8 D_800D9E98[];
extern u8 D_800D9EA8[];
extern u8 D_800D9EB4[];
extern u8 D_800D9EB7[];
extern u8 D_800D9EB8[];
extern u8 D_800D9EC4[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15000940 CURRENT (7667) */
void func_15000940(s32 arg0) {
    u8 *source = D_800A2CD0 + ((D_800B0DF0[0x29] << 2) - D_800B0DF0[0x29]);
    u8 *var_v0 = D_800D9EB8;
    u8 *var_a2 = D_800D9EA8;
    u8 *var_a1 = D_800D9E98;
    u8 *var_a0 = D_800D9E88;
    u8 *var_v1 = D_800D9E70;
    u8 *var_s2;
    u8 *var_t3;
    u8 *var_t4;
    u8 *var_t5;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s3;
    u8 *var_s4;
    u8 *var_s5;
    u8 *base0;
    u8 *base1;
    u8 *base2;
    u8 b0, b1, b2;

    base0 = D_800A2CE8 + ((source[0] << 2) - source[0]);
    base1 = D_800A2CEC + ((source[1] << 2) - source[1]);
    base2 = D_800A2D04 + ((source[2] << 2) - source[2]);
    do {
        var_s2 = D_800D9EB4;
        var_t3 = var_v1;
        var_t4 = var_a0;
        var_t5 = base0;
        var_s0 = var_a1;
        var_s1 = base1;
        var_s3 = base2;
        var_s4 = var_a2;
        var_s5 = var_v0;
        do {
            b2 = *var_s3;
            b0 = *var_t5;
            b1 = *var_s1;
            var_s2++;
            var_t3 += 2;
            var_t4++;
            var_t5++;
            var_s0++;
            var_s1++;
            var_s3++;
            var_s4++;
            var_s5++;
            *(s16 *)(var_t3 - 2) = 0;
            var_s5[-1] = 0;
            var_s2[-1] = b2;
            var_s4[-1] = b2;
            var_t4[-1] = b0;
            var_s0[-1] = b1;
        } while (var_s2 != D_800D9EB7);
        var_v0 += 3;
        var_v1 += 6;
        var_a0 += 3;
        var_a1 += 3;
        var_a2 += 3;
    } while (var_v0 != D_800D9EC4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15000940 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DDF0/func_15000940.s")
