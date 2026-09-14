#include "types.h"

/*
 * Reviewed source unit: src/game/game_2D4B0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15000000
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1000E934(void);
void func_10023790(void *, void *, s32);
void func_10008570(s32, u8 *);
void func_100085A4(s32, s32, s32);
extern u8 D_80041E58[];
extern u8 D_80041EA0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15000000 CURRENT (75) */
void func_15000000(void) {
    u8 *var_s1;
    u8 *var_s2;
    s32 var_s0;

    var_s2 = D_80041EA0;
    var_s1 = D_80041E58;
    var_s0 = 0;
    do {
        func_10023790(var_s1, var_s2, 8);
        func_10008570(var_s0 & 0xFF, var_s1);
        var_s0 += 1;
        var_s1 += 0x18;
        var_s2 += 0x20;
    } while (var_s0 != 3);
    func_100085A4(0, 6, 1);
    func_1000E934();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15000000 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2D4B0/func_15000000.s")
