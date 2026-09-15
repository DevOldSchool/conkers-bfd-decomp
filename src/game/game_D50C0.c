#include "types.h"

/*
 * Reviewed source unit: src/game/game_D50C0.c
 * Boundary evidence: docs/evidence/game_raw_handwritten_entry_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A7C10
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A7C10 CURRENT (6645) */
void func_150A7C10(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 temp_fv0;
    s32 temp_fv0_2;
    s32 temp_fv0_3;

    *(s64 *)((u8 *)arg0 + 0) = 0;
    *(s64 *)((u8 *)arg0 + 8) = 0;
    temp_fv0 = (s32)(arg1 * 65536.0f);
    *(s64 *)((u8 *)arg0 + 0x10) = 0;
    *(s64 *)((u8 *)arg0 + 0x18) = 0;
    *(s64 *)((u8 *)arg0 + 0x20) = 0;
    *(s64 *)((u8 *)arg0 + 0x28) = 0;
    temp_fv0_2 = (s32)(arg2 * 65536.0f);
    *(s64 *)((u8 *)arg0 + 0x30) = 0;
    *(s64 *)((u8 *)arg0 + 0x38) = 0;
    *(s16 *)((u8 *)arg0 + 0) = 1;
    *(s16 *)((u8 *)arg0 + 0xA) = 1;
    temp_fv0_3 = (s32)(arg3 * 65536.0f);
    *(s16 *)((u8 *)arg0 + 0x14) = 1;
    *(s16 *)((u8 *)arg0 + 0x1E) = 1;
    *(s16 *)((u8 *)arg0 + 0) = (s16)((u32)temp_fv0 >> 0x10);
    *(s16 *)((u8 *)arg0 + 0xA) = (s16)((u32)temp_fv0_2 >> 0x10);
    *(s16 *)((u8 *)arg0 + 0x14) = (s16)((u32)temp_fv0_3 >> 0x10);
    *(s16 *)((u8 *)arg0 + 0x20) = (s16)temp_fv0;
    *(s16 *)((u8 *)arg0 + 0x2A) = (s16)temp_fv0_2;
    *(s16 *)((u8 *)arg0 + 0x34) = (s16)temp_fv0_3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A7C10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D50C0/func_150A7C10.s")
