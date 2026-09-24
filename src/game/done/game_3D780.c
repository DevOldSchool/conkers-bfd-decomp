#include "types.h"

/*
 * Reviewed source unit: src/game/game_3D780.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 */

void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
void *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800902E8;
extern s32 D_800902EC;
extern s32 D_800B0E00;
extern s32 D_800B0E04;

void func_150102D0(void) {
    func_15195AA8(D_800B0E00, D_800902E8, 0, -1, 0, 0, 0, -6);
    func_15195AA8(D_800B0E04, D_800902E8, 0, -1, 0, 1, 0, -6);
    func_15195AA8(D_800B0E00, D_800902EC, 0, -1, 0, 0, 0, -3);
    func_15195AA8(D_800B0E04, D_800902EC, 0, -1, 0, 1, 0, -3);
    func_15149130(0x12C, -1, 0x3B, -1, 0, 0, 0, 0xFF, 1);
}
/* Call context: func_15177410: unique active project prototype */
void func_15177410(s32, s32, s32, s32, s32, f32, s32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_150103E0(void) {
    func_15177410(0, 0xFF, -0xD95, -0x3C3, 0x2AC, 0.0f, 0x3A98, 15.0f, -0x6A, 0x1E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F);
    func_15177410(4, 0xFE, 0x964, -0x3E0, 0x30B, 0.0f, 0x7D0, 15.0f, -0x6A, 0x1E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F);
}
