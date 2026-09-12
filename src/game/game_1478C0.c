#include "types.h"

/*
 * Reviewed source unit: src/game/game_1478C0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511A410
 * - func_1511A494
 * - func_1511A738
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511A410 CURRENT (1925) */
s32 func_1511A410(s8 *arg0, s32 *arg1) {
    s32 sp10;
    s32 var_v0;
    s32 var_v1;
    s8 var_a1;
    s32 spC;

    spC = 0;
    sp10 = 0;
    var_v0 = 0;
    var_v1 = 0;
    if (*arg0 != -0x21) {
        var_a1 = *((0 * 8) + arg0);
loop_2:
        if (var_a1 == -3) {
            (&spC)[var_v0] = var_v1;
            var_v0 += 1;
        }
        var_v1 += 1;
        var_a1 = *((var_v1 * 8) + arg0);
        if ((var_a1 != -0x21) && (var_v0 < 2)) {
            goto loop_2;
        }
    }
    *arg1 = sp10;
    return spC;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511A410 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1478C0/func_1511A410.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1478C0/func_1511A494.s")
void func_15116110(void);
void func_1511A494(void *, void *, void *);

void func_1511A6FC(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x3C) != 0) {
        func_15116110();
    }
    func_1511A494(arg0, (u8 *)arg0 + 0x80, (u8 *)arg0 + 0x84);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1478C0/func_1511A738.s")
