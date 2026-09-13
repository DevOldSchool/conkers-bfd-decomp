#include "types.h"

/*
 * Reviewed source unit: src/game/game_447B0.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15017300
 * - func_150174C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800D2138[];

#pragma GLOBAL_ASM("asm/nonmatchings/game_447B0/func_15017300.s")
void func_1501748C(s32 arg0) {

}
void func_15017498(void) {
    func_100226F0(D_800D2138, 0x20C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_447B0/func_150174C0.s")
void *func_1502B5C8(u32 *, s32, ...);
void func_150174C0(u8);
extern u32 D_80087380;
extern void *D_800D23C0;
extern u8 D_800DBF00;

void func_15017578(s32 arg0) {
    u32 sp24;

    sp24 = 0;
    D_800D23C0 = func_1502B5C8(&sp24, 3, 0xC, arg0, 4);
    D_80087380 = sp24 / 24U;
    func_150174C0(D_800DBF00);
}
