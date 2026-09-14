#include "types.h"

/*
 * Reviewed source unit: src/game/game_D5500.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A8050
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern f32 D_8009F6C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A8050 CURRENT (9504) */
void func_150A8050(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs2_2;
    f32 temp_fs3;
    f32 temp_fs3_2;
    f32 temp_fs3_3;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_fs5_2;
    f32 temp_fs5_3;
    f32 temp_ft5;

    temp_fs5 = D_8009F6C0;
    temp_fs2 = arg1 * temp_fs5;
    temp_fs0 = func_150AD780(temp_fs2);
    temp_fs1 = func_150AD78C(temp_fs2);
    temp_fs3 = arg2 * temp_fs5;
    temp_fs2_2 = func_150AD780(temp_fs3);
    temp_fs3_2 = func_150AD78C(temp_fs3);
    temp_fs5_2 = arg3 * temp_fs5;
    temp_fs4 = func_150AD780(temp_fs5_2);
    temp_fs5_3 = func_150AD78C(temp_fs5_2);
    *(f32 *)((u8 *)arg0 + 0) = temp_fs2_2 * temp_fs4;
    *(f32 *)((u8 *)arg0 + 8) = -temp_fs3_2;
    temp_ft5 = temp_fs1 * temp_fs3_2;
    *(s32 *)((u8 *)arg0 + 0xC) = 0;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0;
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(f32 *)((u8 *)arg0 + 4) = temp_fs2_2 * temp_fs5_3;
    *(f32 *)((u8 *)arg0 + 0x10) = (temp_ft5 * temp_fs4) - (temp_fs0 * temp_fs5_3);
    *(f32 *)((u8 *)arg0 + 0x14) = (temp_ft5 * temp_fs5_3) + (temp_fs0 * temp_fs4);
    temp_fs3_3 = temp_fs0 * temp_fs3_2;
    *(s32 *)((u8 *)arg0 + 0x30) = 0;
    *(s32 *)((u8 *)arg0 + 0x34) = 0;
    *(s32 *)((u8 *)arg0 + 0x38) = 0;
    *(f32 *)((u8 *)arg0 + 0x18) = temp_fs1 * temp_fs2_2;
    *(f32 *)((u8 *)arg0 + 0x20) = (temp_fs3_3 * temp_fs4) + (temp_fs1 * temp_fs5_3);
    *(f32 *)((u8 *)arg0 + 0x24) = (temp_fs3_3 * temp_fs5_3) - (temp_fs1 * temp_fs4);
    *(f32 *)((u8 *)arg0 + 0x28) = temp_fs0 * temp_fs2_2;
    *(f32 *)((u8 *)arg0 + 0x3C) = 1.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A8050 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5500/func_150A8050.s")
