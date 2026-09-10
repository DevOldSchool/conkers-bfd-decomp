#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D4AC0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A7610
 * - func_151A77C0
 * - func_151A787C
 * - func_151A7908
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4AC0/func_151A7610.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A77C0 CURRENT (240) */
void func_151A77C0(u8 *arg0) {
    s16 temp_v1;
    s32 temp_lo;
    s8 temp_lo_2;
    u8 *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    temp_v0 = (void *)(arg0 + 0x50);
    if (temp_v1 < *(s16 *)((u8 *)arg0 + 0x54)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (temp_v1 * *(s16 *)((u8 *)arg0 + 0x56));
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 8)) {
        temp_lo = *(s16 *)((u8 *)temp_v0 + 0xA) * D_800BE9E4;
        *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + temp_lo);
        *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) + temp_lo);
    }
    if (*(s16 *)((u8 *)arg0 + 0x38) < *(s16 *)((u8 *)arg0 + 0x50)) {
        *(s8 *)((u8 *)arg0 + 0x2F) = 0x15;
        *(u16 *)((u8 *)arg0 + 0x44) = (u16) (*(u16 *)((u8 *)arg0 + 0x44) | 0x201);
        temp_lo_2 = *(s16 *)((u8 *)arg0 + 0x38) * *(s16 *)((u8 *)temp_v0 + 2);
        *(s32 *)((u8 *)arg0 + 0x14) = 0xC000F;
        *(s8 *)((u8 *)arg0 + 0x42) = temp_lo_2;
        *(s8 *)((u8 *)arg0 + 0x41) = temp_lo_2;
        *(s8 *)((u8 *)arg0 + 0x40) = temp_lo_2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A77C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4AC0/func_151A77C0.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A787C CURRENT (155) */
void func_151A787C(u8 *arg0) {
    s16 temp_v1;
    s32 temp_lo;
    s8 temp_lo_2;
    u8 *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    temp_v0 = (void *)(arg0 + 0x50);
    if (temp_v1 < *(s16 *)((u8 *)arg0 + 0x54)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (temp_v1 * *(s16 *)((u8 *)arg0 + 0x56));
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 8)) {
        temp_lo = *(s16 *)((u8 *)temp_v0 + 0xA) * D_800BE9E4;
        *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + temp_lo);
        *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) + temp_lo);
    }
    temp_lo_2 = *(s16 *)((u8 *)arg0 + 0x38) * *(s16 *)((u8 *)temp_v0 + 2);
    *(s8 *)((u8 *)arg0 + 0x42) = temp_lo_2;
    *(s8 *)((u8 *)arg0 + 0x41) = temp_lo_2;
    *(s8 *)((u8 *)arg0 + 0x40) = temp_lo_2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A787C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4AC0/func_151A787C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4AC0/func_151A7908.s")
