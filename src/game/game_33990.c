#include "types.h"

/*
 * Reviewed source unit: src/game/game_33990.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150064E0
 * - func_15006590
 * - func_15006BEC
 * - func_1500707C
 * - func_15007168
 * - func_1500727C
 * - func_15007360
 * - func_15007440
 * - func_15007558
 * - func_15007718
 * - func_15007750
 * - func_15007778
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_150064E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15006590.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15006BEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_1500707C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007168.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_1500727C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007440.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007558.s")
void func_15007644(void) {

}
extern s8 D_80082BB4;
extern s8 D_800BE3EC;

void func_1500764C(void) {
    D_80082BB4 = 6;
    D_800BE3EC = 0;
}
void func_15007668(void) {
    D_80082BB4 = 7;
    D_800BE3EC = 0;
}
void func_15007684(void) {
    D_80082BB4 = 4;
    D_800BE3EC = 0;
}
void func_150076A0(void) {
    D_80082BB4 = 5;
    D_800BE3EC = 0;
}
void func_150064E0(void);
extern u8 D_800BE616;

void func_150076BC(s32 arg0) {
    if (arg0 < 0) {
        func_150064E0();
    }
    if ((arg0 >= 0) && (arg0 < 4) && (D_800BE616 == 0)) {
        D_80082BB4 = 1;
        D_800BE3EC = arg0;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15007718 CURRENT (330) */
void func_15007718(s8 arg0) {
    if ((arg0 >= 0) && (arg0 < 3) && (D_800BE616 == 0)) {
        D_80082BB4 = 2;
        D_800BE3EC = arg0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15007718 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007718.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15007750 CURRENT (310) */
void func_15007750(s8 arg0) {
    if ((arg0 >= 0) && (arg0 < 3)) {
        D_80082BB4 = 3;
        D_800BE3EC = arg0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15007750 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007750.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007778.s")
