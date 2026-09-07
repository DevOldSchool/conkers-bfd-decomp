#include "types.h"

/*
 * Reviewed source unit: src/game/game_1897A0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515C2F0
 * - func_1515C388
 * - func_1515C534
 * - func_1515C6F4
 * - func_1515CF9C
 * - func_1515D088
 * - func_1515D130
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C2F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C388.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C534.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C6F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515CF9C.s")
s32 func_1515D030(void *arg0, s32 arg1) {
    s32 var_v1;
    s8 temp_v0;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x2C);
    var_v1 = 1;
    if (temp_v0 >= 3) {
        *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (temp_v0 - 1);
        *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(s8 *)((u8 *)arg0 + 0x2E) - 1);
        if (*(s8 *)((u8 *)arg0 + 0x2E) < 0) {
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(u8 *)((u8 *)arg0 + 0x25) - 1);
        }
    } else {
        var_v1 = 0;
    }
    return var_v1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515D088.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515D130.s")
