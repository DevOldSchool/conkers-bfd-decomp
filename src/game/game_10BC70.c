#include "types.h"

/*
 * Reviewed source unit: src/game/game_10BC70.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DE7C0
 * - func_150DEB58
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_10BC70/func_150DE7C0.s")
extern f32 D_800BE9A4;

s32 func_150DEACC(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) ((*(f32 *)((u8 *)arg0 + 0x110) * D_800BE9A4) + *(f32 *)((u8 *)arg0 + 0x34));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) ((*(f32 *)((u8 *)arg0 + 0x114) * D_800BE9A4) + *(f32 *)((u8 *)arg0 + 0x38));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((*(f32 *)((u8 *)arg0 + 0x118) * D_800BE9A4) + *(f32 *)((u8 *)arg0 + 0x3C));
    *(f32 *)((u8 *)arg0 + 0x11C) = (f32) (*(f32 *)((u8 *)arg0 + 0x11C) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x11C) < 0.0f) {
        return 0;
    }
    return 1;
}
s32 func_15140410(s32, s32, s32, s16);
extern s32 D_80082FA0;
extern s32 D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DEB58 CURRENT (120) */
s32 func_150DEB58(s32 arg0, s16 arg1) {
    if (*(f32 *)((u8 *)(D_800DBFF0 + (D_80082FA0 * 0x9A0)) + 0x388) < 5.0f) {
        return 0;
    }
    return func_15140410(arg0, arg0 + 0x120, arg0 + 0x12C, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DEB58 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10BC70/func_150DEB58.s")
