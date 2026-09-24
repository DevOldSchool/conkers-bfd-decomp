#include "types.h"

/*
 * Reviewed source unit: src/game/game_10EF60.c
 * Boundary evidence: docs/evidence/game_raw_path_owner_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E1AB0
 * - func_150E1D14
 * - func_150E28DC
 * - func_150E2FC0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E1AB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E1D14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E28DC.s")
s32 func_150E2DA4(s32 arg0, s32 arg1) {
    return arg0;
}
void func_150E1AB0(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32,
                   f32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                   s32, s32, f32, f32, f32, f32, f32, f32);

void func_150E2DB4(s32 arg0, u8 arg1, s16 arg2, s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                   f32 arg9, s16 arg10, s16 arg11, u16 arg12, u8 arg13) {
    func_150E1AB0(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                  40.0f, 400.0f, (s32)arg12, 0x27, 1, (s32)arg10,
                  (s32)arg11, arg0, (s32)arg1, (s32)arg2, arg3, 0,
                  (s32)arg13, arg4, arg5, arg6, arg7, arg8, arg9);
}

void func_150E2EA4(s32 arg0, u8 arg1, s16 arg2, s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                   f32 arg9, s16 arg10, s16 arg11, u16 arg12,
                   f32 arg13, f32 arg14, u8 arg15, f32 arg16) {
    func_150E1AB0(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, arg16, 0.0f,
                  arg13, arg14, (s32)arg12, 0x27, 1, (s32)arg10,
                  (s32)arg11, arg0, (s32)arg1, (s32)arg2, arg3, 0,
                  (s32)arg15, arg4, arg5, arg6, arg7, arg8, arg9);
}
void func_150E2F90(s32 arg0, s32 arg1, s16 arg2) {
    func_150E2DA4(arg0, (s32) arg2);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E2FC0 CURRENT (10) */
void func_150E2FC0(void *arg0, void *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    if (arg2 == 0x2D) {
        temp_v0 = *(s32 *)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)arg0 + 0xDC);
        if (temp_v0 == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0xDC) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0xDA) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0xDC) = temp_v0;
            *(u8 *)((u8 *)arg0 + 0xDA) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E2FC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E2FC0.s")
