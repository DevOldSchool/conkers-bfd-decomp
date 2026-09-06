#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A89B0.c
 * Boundary evidence: docs/evidence/game_raw_sorted_record_object_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517B500
 * - func_1517B6E8
 * - func_1517B7F8
 * - func_1517B89C
 * - func_1517BBAC
 * - func_1517CFC4
 * - func_1517D074
 * - func_1517D578
 * - func_1517D5FC
 * - func_1517D690
 * - func_1517D7B0
 * - func_1517DE5C
 * - func_1517E05C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B500.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B6E8.s")
s32 func_1517B7A8(void *arg0, void *arg1, s32 *arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = *arg2;
    if (temp_v0 >= 0x300) {
        if (temp_v0 >= 0x501) {
            *arg2 = temp_v0 - 0x200;
        } else {
            *arg2 = 0x300;
        }
    }
    *(s16 *)((u8 *)arg1 + 0) = (s16) *(s16 *)((u8 *)arg0 + 0);
    *(s16 *)((u8 *)arg1 + 2) = (s16) *(s16 *)((u8 *)arg0 + 2);
    *(s16 *)((u8 *)arg1 + 4) = (s16) *(s16 *)((u8 *)arg0 + 4);
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B7F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B89C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517BBAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517CFC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D074.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D578.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D5FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D7B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517DE5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517E05C.s")
