#include "types.h"

/*
 * Reviewed source unit: src/game/game_14F580.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15122170
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15048F90(void *, void *, void *);
f32 func_15048FC8(f32 *);
void *func_15122980(void *);
extern f32 D_800A3460;

void func_151220D0(void *arg0) {
    f32 vector[3];
    f32 temp_fv0;

    if (!((*(u16 **)((u8 *)arg0 + 0x36C))[0] & 4)) {
        func_15048F90((u8 *)arg0 + 0x2F8, (u8 *)arg0 + 0x2BC, vector);
        vector[0] += *(f32 *)((u8 *)arg0 + 0x2C8) - *(f32 *)((u8 *)arg0 + 0x2BC);
        vector[2] += *(f32 *)((u8 *)arg0 + 0x2D0) - *(f32 *)((u8 *)arg0 + 0x2C4);
        temp_fv0 = func_15048FC8(&vector[0]);
        *(f32 *)((u8 *)arg0 + 0x37C) = temp_fv0;
        *(f32 *)((u8 *)arg0 + 0x39C) = temp_fv0 * D_800A3460;
    }
    func_15122980(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_14F580/func_15122170.s")
