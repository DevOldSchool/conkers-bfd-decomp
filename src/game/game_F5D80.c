#include "types.h"

/*
 * Reviewed source unit: src/game/game_F5D80.c
 * Boundary evidence: docs/evidence/game_raw_radial_composite_effect.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C88D0
 * - func_150C8A68
 * - func_150C8DB8
 * - func_150C99B4
 * - func_150C9BDC
 * - func_150C9DC4
 * - func_150CA07C
 * - func_150CA150
 * - func_150CA930
 * - func_150CAA04
 * - func_150CAC28
 * - func_150CADD0
 * - func_150CB008
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C88D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C8A68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C8DB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C99B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C9BDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C9DC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CA07C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CA150.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CA930.s")
s32 func_150CA9D0(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x28)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) temp_v1;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CAA04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CAC28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CADD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CB008.s")
