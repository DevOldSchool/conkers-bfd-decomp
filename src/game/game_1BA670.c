#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BA670.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518D1C0
 * - func_1518D6E0
 * - func_1518E308
 * - func_1518E37C
 * - func_1518E3C4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1BA670/func_1518D1C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BA670/func_1518D6E0.s")
s32 func_1518E298(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x1C);
    if ((temp_v1 != 0) && (*(s32 *)((u8 *)temp_v1 + 0) != 0)) {
        *(s16 *)((u8 *)arg0 + 2) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x14);
        *(s16 *)((u8 *)arg0 + 4) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x18);
        *(s16 *)((u8 *)arg0 + 6) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x1C);
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BA670/func_1518E308.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BA670/func_1518E37C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BA670/func_1518E3C4.s")
