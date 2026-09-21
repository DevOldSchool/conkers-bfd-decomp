#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E67C0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B9408
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150A7790(void *, s32);
void func_150A8050(f32 *, f32, f32, s32);

s32 func_151B9310(s32 arg0, void *arg1) {
    struct {
        f32 pad[2];
        f32 matrix[16];
    } work;

    func_150A8050(work.matrix, 0.0f, 0.0f,
                  *(s32 *)((u8 *)arg1 + 0x170));
    work.matrix[12] = *(f32 *)((u8 *)arg1 + 0x38);
    work.matrix[13] = *(f32 *)((u8 *)arg1 + 0x3C);
    work.matrix[14] = *(f32 *)((u8 *)arg1 + 0x40);
    work.matrix[0] *= *(f32 *)((u8 *)arg1 + 0x18);
    work.matrix[1] *= *(f32 *)((u8 *)arg1 + 0x18);
    work.matrix[2] *= *(f32 *)((u8 *)arg1 + 0x18);
    work.matrix[4] *= *(f32 *)((u8 *)arg1 + 0x1C);
    work.matrix[5] *= *(f32 *)((u8 *)arg1 + 0x1C);
    work.matrix[6] *= *(f32 *)((u8 *)arg1 + 0x1C);
    work.matrix[8] *= *(f32 *)((u8 *)arg1 + 0x18);
    work.matrix[9] *= *(f32 *)((u8 *)arg1 + 0x18);
    work.matrix[10] *= *(f32 *)((u8 *)arg1 + 0x18);
    func_150A7790(work.matrix, arg0);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E67C0/func_151B9408.s")
