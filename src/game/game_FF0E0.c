#include "types.h"

/*
 * Reviewed source unit: src/game/game_FF0E0.c
 * Boundary evidence: docs/evidence/game_raw_child_chain_render_lists.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D1C30
 * - func_150D1F6C
 * - func_150D2054
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1516972C(void *arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_FF0E0/func_150D1C30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF0E0/func_150D1F6C.s")
void func_150D2054(s32 arg0);
void func_1514933C(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D2054 CURRENT (435) */
void func_150D2054(void *arg0) {
    s32 temp_t8;
    s32 var_s0;
    void *temp_a0;
    u8 *var_s1;

    var_s0 = 0;
    var_s1 = (u8 *)arg0 + 0x28;
    do {
        temp_a0 = *(void **)(var_s1 + (var_s0 * 4) + 0x24);
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        temp_t8 = (var_s0 + 1) & 0xFF;
        var_s0 = temp_t8;
    } while (temp_t8 < 6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D2054 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF0E0/func_150D2054.s")

void func_150D20B0(s32 arg0) {
    func_150D2054(arg0);
    func_15149368(arg0);
}

void func_150D20DC(s32 arg0) {
    func_150D2054(arg0);
    func_1514933C(arg0);
}
