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

u8 func_151D8E20(void);
void func_151DBCBC(s32, f32, u8, s32, f32 *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AC550 CURRENT (308) */
s32 func_151AC550(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4,
                  s32 arg5) {
    void *object;
    f32 values[3];
    u8 *records;

    object = *(void **)(arg0 + 0x98);
    records = *(u8 **)(arg0 + 0x94);
    values[1] = arg4;
    values[0] = *(f32 *)(records + (*(s8 *)(arg0 + 0x2D) * 0x14));
    values[2] = *(f32 *)(records + (*(s8 *)(arg0 + 0x2D) * 0x14) + 8);
    func_151DBCBC(func_151D8E20() & 0xFF,
                  *(f32 *)object * 7.0f,
                  *(u8 *)((u8 *)object + 0x1B), arg5, values,
                  arg0[0xC], arg0[1]);
    *(s8 *)((u8 *)object + 0x20) = 4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AC550 */
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
