#include "types.h"

/*
 * Reviewed source unit: src/game/game_C8950.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509B4A0
 * - func_1509B570
 * - func_1509B5AC
 * - func_1509B704
 * - func_1509B764
 * - func_1509B810
 * - func_1509B8FC
 * - func_1509B950
 * - func_1509BA04
 * - func_1509BBA0
 * - func_1509BE40
 * - func_1509BFB0
 * - func_1509C120
 * - func_1509C228
 * - func_1509C3A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B4A0.s")
void *func_1509B704(s16, s16);                      /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509B570 CURRENT (454) */
void *func_1509B570(s16 arg0) {
    u8 *temp_v0;

    temp_v0 = func_1509B704(arg0, arg0);
    if (temp_v0 != 0) {
        return temp_v0 + *(u16 *)((u8 *)temp_v0 + 0xA);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509B570 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B570.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B5AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B704.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B764.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B810.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B8FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B950.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BA04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BBA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BE40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BFB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509C120.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509C228.s")
extern s32 D_800BE9F0;
extern u8 D_800D2E44;

s32 func_1509C2A4(void) {
    if ((D_800BE9F0 == 3) || (D_800BE9F0 == 5) || (D_800BE9F0 == 9) || (D_800BE9F0 == 0xD) || (D_800BE9F0 == 0xF) || (D_800BE9F0 == 0x11) || (D_800BE9F0 == 0x15) || (D_800BE9F0 == 0x16) || (D_800BE9F0 == 0x18) || (D_800BE9F0 == 0x1A) || (D_800BE9F0 == 0x1D) || (D_800BE9F0 == 0x1F) || (D_800BE9F0 == 0x20) || (D_800BE9F0 == 0x21) || (D_800BE9F0 == 0x22) || (D_800BE9F0 == 0x24) || (D_800BE9F0 == 0x25) || (D_800BE9F0 == 0x2A) || (D_800BE9F0 == 0x2B) || (D_800BE9F0 == 0x2D) || (D_800BE9F0 == 0x30) || (D_800BE9F0 == 0x33) || (D_800BE9F0 == 0x34) || (D_800BE9F0 == 0x38) || (D_800BE9F0 == 0x3E) || (D_800BE9F0 == 0x3F) || (D_800D2E44 != 0)) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509C3A0.s")
extern void *D_800D2E4C;

s32 func_1509C414(s32 arg0) {
    return ((*(u8 *)((u8 *)D_800D2E4C + 3) & 1) << 0xA) + arg0 + 0x1400;
}
