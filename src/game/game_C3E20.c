#include "types.h"

/*
 * Reviewed source unit: src/game/game_C3E20.c
 * Boundary evidence: docs/evidence/game_raw_record_command_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15096970
 * - func_150969A0
 * - func_15096A68
 * - func_15096D78
 * - func_1509759C
 * - func_15097798
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_15096970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_150969A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_15096A68.s")
s32 func_15096A68(s32);                             /* extern */
extern u8 D_800C35EA;
extern u8 D_800D2DC0;

void func_15096D08(void) {
    s32 var_s0;
    u8 *var_s1;

    var_s0 = 0;
    if (D_800C35EA != 1) {
        var_s1 = &D_800D2DC0;
loop_2:
        if (*var_s1 != 0) {
            if (func_15096A68(var_s0) == 0) {
                goto block_6;
            }
            return;
        }
block_6:
        var_s0 += 1;
        var_s1 += 0x24;
        if (var_s0 == 3) {

        } else {
            goto loop_2;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_15096D78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_1509759C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_15097798.s")
