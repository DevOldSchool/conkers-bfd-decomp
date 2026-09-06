#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DCA70.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AF5C0
 * - func_151AF6D4
 * - func_151AFC08
 * - func_151AFC88
 * - func_151AFEA4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AF5C0.s")
s32 func_151AF6C0(s32 arg0, s32 arg1) {
    return 0xC;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AF6D4.s")
s32 func_151AFBD4(void *arg0) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AFC08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AFC88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AFEA4.s")
