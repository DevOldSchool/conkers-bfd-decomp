#include "types.h"

/*
 * Reviewed source unit: src/game/game_43760.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150162B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *arg0, s32 arg1);

extern s32 D_80086000;
extern s8 D_800CC26E;
extern u8 D_800CC298[];
extern s8 D_800CC2A2;
extern s8 D_800CC2B0;
extern u8 D_800CC2D0[];
extern s8 D_800D18D0;
extern s32 D_800D2138;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150162B0 CURRENT (920) */
void func_150162B0(void) {
    func_100226F0(D_800CC2D0, 0x4F4C);
    D_80086000 = 0;

    if (D_800D2138 == 2) {
        D_800CC26E = 2;
    } else if (D_800D2138 == 3) {
        D_800CC26E = 3;
    } else if (D_800D2138 == 4) {
        D_800CC26E = 4;
    } else {
        D_800CC26E = 0;
    }

    D_800CC2B0 = 0;
    func_100226F0(D_800CC298, 0x18);
    D_800CC2A2 = 1;
    D_800D18D0 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150162B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_43760/func_150162B0.s")
