#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D9A00.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AC550
 * - func_151AC61C
 * - func_151AC810
 * - func_151ACA20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9A00/func_151AC550.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9A00/func_151AC61C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9A00/func_151AC810.s")
extern f32 D_800BE9A4;

s32 func_151AC9EC(void *arg0) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
    return 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ACA20 CURRENT (510) */
s32 func_151ACA20(void *arg0) {
    s16 temp_v1;
    s16 var_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    var_v0 = 0xFF;
    if (temp_v1 < 0x10) {
        var_v0 = temp_v1 * 0x10;
    }
    if (var_v0 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
        *(u8 *)((u8 *)arg0 + 0x5C) = (u8) var_v0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ACA20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9A00/func_151ACA20.s")
