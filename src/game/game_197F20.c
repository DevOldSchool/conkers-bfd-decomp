#include "types.h"

/*
 * Reviewed source unit: src/game/game_197F20.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1516AA70
 * - func_1516B6BC
 * - func_1516C878
 * - func_1516C934
 * - func_1516CC58
 * - func_1516D0CC
 * - func_1516D2E0
 * - func_1516D328
 * - func_1516D378
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516AA70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516B6BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516C878.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516C934.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516CC58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516D0CC.s")
void func_1516D2D8(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516D2E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516D328.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197F20/func_1516D378.s")
void *func_1516D3C4(void *arg0) {
    s32 *temp_v1;

    if ((arg0 != 0) && (*(u8 *)((u8 *)arg0 + 0) == 0x51)) {
        temp_v1 = *(s32 **)((u8 *)arg0 + 0x10);
        *temp_v1 |= 0x500;
        return arg0;
    }
    return 0;
}
