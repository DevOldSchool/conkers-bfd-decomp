#include "types.h"

/*
 * Reviewed source unit: src/game/game_2D4B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_final.md
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15000000 CURRENT (60) */
void func_15000000(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_10023790((D_80041E58 + var_s0 * 0x18), (D_80041EA0 + var_s0 * 0x20), 8);
        func_10008570(var_s0 & 0xFF, (D_80041E58 + var_s0 * 0x18));
        var_s0 += 1;
    } while (var_s0 != 3);
    func_100085A4(0, 6, 1);
    func_1000E934();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15000000 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2D4B0/func_15000000.s")
