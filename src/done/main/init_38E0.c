#include "types.h"
#include "globals.h"

/*
 * Reviewed source unit: src/main/init_38E0.c
 * Boundary evidence: docs/evidence/boundaries/main/main_boundary_beta_comparison.md
 */

void func_800038E0(void) {
    D_80038070 = (volatile u16 *)0xBC000C02;
    D_80038074 = 0x4040;
    *(volatile s16 *)0xBC000C02 = 0x4040;
}
s32 func_8000390C(void) {
    return 0;
}
