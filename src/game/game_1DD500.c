#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DD500.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B0050
 * - func_151B01B8
 * - func_151B03B8
 * - func_151B09BC
 * - func_151B0B88
 * - func_151B118C
 * - func_151B14AC
 * - func_151B1828
 * - func_151B1918
 * - func_151B19A4
 * - func_151B1A58
 * - func_151B1A84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B0050.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B01B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B03B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B09BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B0B88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B118C.s")
s32 func_151B1478(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B14AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1828.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B19A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1A58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1A84.s")
