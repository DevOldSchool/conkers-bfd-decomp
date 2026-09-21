#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B7870.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518A3C0
 * - func_1518A5F4
 * - func_1518A914
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7870/func_1518A3C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7870/func_1518A5F4.s")
void func_150A7790(void *, s32);
void func_150A8050(f32 *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518A914 CURRENT (425) */
s32 func_1518A914(s32 arg0, void *arg1) {
    struct {
        f32 matrix[16];
        f32 pad;
    } work;
    volatile f32 *temp_v0;

    func_150A8050(work.matrix, *(s32 *)((u8 *)arg1 + 0x100),
                  *(s32 *)((u8 *)arg1 + 0x104),
                  *(s32 *)((u8 *)arg1 + 0x108));
    temp_v0 = (volatile f32 *)((u8 *)arg1 + 0x100);
    work.matrix[12] = *(f32 *)((u8 *)arg1 + 0x48);
    work.matrix[13] = *(f32 *)((u8 *)arg1 + 0x4C);
    work.matrix[14] = *(f32 *)((u8 *)arg1 + 0x50);
    work.matrix[0] *= temp_v0[3];
    work.matrix[1] *= temp_v0[3];
    work.matrix[2] *= temp_v0[3];
    work.matrix[4] *= temp_v0[3];
    work.matrix[5] *= temp_v0[3];
    work.matrix[6] *= temp_v0[3];
    work.matrix[8] *= temp_v0[3];
    work.matrix[9] *= temp_v0[3];
    work.matrix[10] *= temp_v0[3];
    func_150A7790(work.matrix, arg0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518A914 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7870/func_1518A914.s")
