#include "types.h"

/*
 * Reviewed source unit: src/game/game_39750.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500C2F0
 * - func_1500C8D0
 * - func_1500CE4C
 * - func_1500D3AC
 * - func_1500D8C8
 * - func_1500DE88
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800DC460;
extern s32 D_800DC464;
extern s16 D_800DC468;
extern u8 D_800DC46A[];
extern u8 D_800DC63A[];
extern s32 D_800DC63C;

void func_1500C2A0(void) {
    s32 i;

    for (i = 0; i < 233; i++) {
        (&D_800DC468)[i] = 0;
    }
    D_800DC460 = 0;
    D_800DC464 = 0;
    D_800DC63C = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_39750/func_1500C2F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_39750/func_1500C8D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_39750/func_1500CE4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_39750/func_1500D3AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_39750/func_1500D8C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_39750/func_1500DE88.s")
