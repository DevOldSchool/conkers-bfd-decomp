#include "types.h"

/*
 * Reviewed source unit: src/game/game_3BA70.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500E5C0
 * - func_1500E738
 * - func_1500E8C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_3BA70/func_1500E5C0.s")
void func_1500E70C(s32 arg0) {
    if (arg0 == 0x2B) {
        func_15011C70();
    }
}
extern s32 D_80082FA0;
extern s8 D_8008FD8C;
extern s8 D_800DCA20;
extern f32 D_800DCA24;
extern s8 D_800DCA28;
extern f32 D_800DCA2C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500E738 CURRENT (1795) */
void func_1500E738(void) {
    switch (D_80082FA0) {                           /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        D_800DCA20 = 0;
        D_800DCA24 = 1.0f;
        break;
    case 1:                                         /* switch 1 */
        D_800DCA20 = 1;
        D_800DCA24 = 0.5f;
        break;
    case 2:                                         /* switch 1 */
    case 3:                                         /* switch 1 */
        D_800DCA20 = 2;
        D_800DCA24 = 0.25f;
        break;
    }
    switch (D_8008FD8C) {                           /* switch 2 */
    case 2:                                         /* switch 2 */
        D_800DCA28 = 1;
        D_800DCA2C = 0.5f;
        return;
    case 3:                                         /* switch 2 */
    case 4:                                         /* switch 2 */
        D_800DCA28 = 2;
        D_800DCA2C = 0.25f;
        return;
    case 5:                                         /* switch 2 */
    case 6:                                         /* switch 2 */
    case 7:                                         /* switch 2 */
    case 8:                                         /* switch 2 */
        D_800DCA28 = 3;
        D_800DCA2C = 0.125f;
        return;
    case 9:                                         /* switch 2 */
    case 10:                                        /* switch 2 */
    case 11:                                        /* switch 2 */
    case 12:                                        /* switch 2 */
    case 13:                                        /* switch 2 */
    case 14:                                        /* switch 2 */
    case 15:                                        /* switch 2 */
    case 16:                                        /* switch 2 */
        D_800DCA28 = 4;
        D_800DCA2C = 0.0625f;
        return;
    default:                                        /* switch 2 */
        D_800DCA28 = 0;
        D_800DCA2C = 1.0f;
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500E738 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3BA70/func_1500E738.s")
/* Call context: func_15008E00: unique active project prototype */
/* Call context: func_15008E10: unique active project prototype */
void func_15008E00(void);
void func_15008E10(s32);

void func_1500E890(void) {
    func_15008E00();
    func_15008E10(0);
    func_15008E10(1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_3BA70/func_1500E8C0.s")
/* Call context: func_15195AA8: unique active project prototype */
void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80090320;
extern s32 D_800B0E00;
extern s32 D_800B0E04;

void func_1500EAA0(void) {
    func_15195AA8(D_800B0E00, D_80090320, 0, -1, 0, 0, 0, -8);
    func_15195AA8(D_800B0E04, D_80090320, 0, -1, 0, 1, 0, -8);
}
