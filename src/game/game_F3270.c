#include "types.h"

/*
 * Reviewed source unit: src/game/game_F3270.c
 * Boundary evidence: docs/evidence/game_raw_paired_owner_streams.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C5DC0
 * - func_150C5E0C
 * - func_150C5EFC
 * - func_150C5F40
 * - func_150C5F94
 * - func_150C60D8
 * - func_150C6410
 * - func_150C6438
 * - func_150C6460
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5DC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5E0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5EFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5F40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5F94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C60D8.s")
s32 func_150C63EC(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (*(u8 *)((u8 *)arg0 + 0x5C) == 0) {
        var_v1 = 0;
    }
    *(u8 *)((u8 *)arg0 + 0x5C) = 0U;
    return var_v1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C6410.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C6438.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C6460.s")
