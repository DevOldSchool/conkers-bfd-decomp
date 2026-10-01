#include "types.h"

/*
 * Reviewed source unit: src/main/init_11FA0.c
 * Boundary evidence: docs/evidence/main_allocator_transfer_controller_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80011FB0
 * - func_80011FEC
 * - func_80012020
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_80042770;

void func_80011FA0(s32 arg0) {
    D_80042770 = arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_11FA0/func_80011FB0.s")
extern s32 D_80042778;

void func_80011FDC(s32 arg0) {
    D_80042778 = arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_11FA0/func_80011FEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_11FA0/func_80012020.s")
