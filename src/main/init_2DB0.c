#include "types.h"

/*
 * Reviewed source unit: src/main/init_2DB0.c
 * Boundary evidence: docs/evidence/main_system_wrapper_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80002DB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_80023390(void);
u32 func_800233C0(void *);
extern u8 D_8002AB40;
extern volatile u32 D_A4500000;
extern volatile u32 D_A4500004;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80002DB0 CURRENT (845) */
s32 func_80002DB0(void *arg0, u32 arg1) {
    u8 *buffer;

    buffer = arg0;
    if (D_8002AB40 != 0) {
        buffer = (u8 *)arg0 - 0x2000;
    }
    if ((((u32)arg0 + arg1) & 0x3FFF) == 0x2000) {
        D_8002AB40 = 1;
    } else {
        D_8002AB40 = 0;
    }
    if (func_80023390() != 0) {
        return -1;
    }
    D_A4500000 = func_800233C0(buffer);
    D_A4500004 = arg1;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80002DB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_2DB0/func_80002DB0.s")
