#include "types.h"

/*
 * Reviewed source unit: src/game/game_AC030.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507EB80
 * - func_1507EBB8
 * - func_1507EC38
 * - func_1507EE58
 * - func_1507EEB8
 * - func_1507EEF4
 * - func_1507EFD0
 * - func_1507F454
 * - func_1507F4C0
 * - func_1507F54C
 * - func_1507F640
 * - func_1507FC2C
 * - func_1507FEA0
 * - func_1507FF94
 * - func_1507FFD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EB80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EBB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EC38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EE58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EEB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EEF4.s")
void func_1507EFA0(s32 arg0, s32 arg1) {
    s32 var_v0;
    u8 *var_v1;

    var_v0 = 4;
    var_v1 = arg1 + 4;
loop_1:
    var_v0 -= 1;
    if (arg0 == *var_v1) {
        *var_v1 = 0;
        return;
    }
    var_v1 -= 1;
    if (var_v0 < 0) {
        return;
    }
    goto loop_1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EFD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507F454.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507F4C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507F54C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507F640.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FC2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FEA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FF94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FFD8.s")
