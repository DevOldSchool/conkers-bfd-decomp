#include "types.h"

/*
 * Reviewed source unit: src/game/game_117D90.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EA904
 * - func_150EA944
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150EA8E0(s32 arg0) {
    func_150E5AE0();
}
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EA904 CURRENT (60) */
void func_150EA904(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = D_800DBEF4 + (arg1 * 0xA0);
    if (*(u8 *)((u8 *)temp_v0 + 0x72) == 0xE0) {
        *(u8 *)((u8 *)temp_v0 + 0x73) = (u8) (*(u8 *)((u8 *)temp_v0 + 0x73) | 3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EA904 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_117D90/func_150EA904.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_117D90/func_150EA944.s")
