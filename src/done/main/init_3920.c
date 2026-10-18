#include "types.h"

/*
 * Reviewed source unit: src/main/init_3920.c
 * Boundary evidence: docs/evidence/boundaries/main/main_system_wrapper_boundaries.md
 *
 * Original object compiled without -g3: the raw 0x3920 body fills the
 * `jr $ra` delay slot (`lui; jr; sb; nop`), which IDO 5.3 -O2 -g3 never does
 * for a single-statement leaf (`lui; sb; jr; nop`); the pinned flags minus
 * -g3 assemble to the raw bytes exactly. Maintainer-approved 2026-10-18.
 */
/* CONKER_COMPILE_WITHOUT: -g3 */

extern u8 D_80038080;

void func_80003920(void) {
    D_80038080 = 0;
}
