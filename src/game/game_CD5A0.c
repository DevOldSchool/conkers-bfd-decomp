#include "types.h"

/*
 * Reviewed source unit: src/game/game_CD5A0.c
 * Boundary evidence: docs/evidence/game_raw_record_transform_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A00F0
 * - func_150A019C
 * - func_150A0264
 * - func_150A02D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A00F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A019C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A0264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A02D0.s")
extern s32 D_800D3014[];

s32 func_150A0374(s32 arg0, s32 arg1, volatile s32 arg2) {
    if (arg1 == 3) {
        return *(s32 *)((u8 *)D_800D3014 + (arg0 * 0xC));
    }
    return 0;
}
