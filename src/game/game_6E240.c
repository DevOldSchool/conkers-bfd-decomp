#include "types.h"

/*
 * Reviewed source unit: src/game/game_6E240.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15040D9C
 * - func_15040FCC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15040D90(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E240/func_15040D9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E240/func_15040FCC.s")
void func_1504129C(void) {
    s32 value = 0;

loop:
    value += 4;
    if (value != 0x18000000) {
        goto loop;
    }
}
