#include "types.h"

/*
 * Reviewed source unit: src/main/init_38E0.c
 * Boundary evidence: docs/evidence/main_boundary_beta_comparison.md
 *
 * TODO: Implement these source-unit functions:
 * - func_800038E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern volatile u16 *D_80038070;
extern u16 D_80038074;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800038E0 CURRENT (410) */
void func_800038E0(void) {
    D_80038070 = (volatile u16 *)0xBC000C02;
    D_80038074 = 0x4040;
    *(volatile u16 *)0xBC000C02 = 0x4040;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800038E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_38E0/func_800038E0.s")
s32 func_8000390C(void) {
    return 0;
}
