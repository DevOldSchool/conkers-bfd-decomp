#include "types.h"

/*
 * Reviewed source unit: src/game/game_1CE2F0.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_beta_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A0E40
 * - func_151A0F28
 * - func_151A1010
 * - func_151A11E4
 * - func_151A175C
 * - func_151A18DC
 * - func_151A1998
 * - func_151A1E34
 * - func_151A1EE8
 * - func_151A1FB4
 * - func_151A24A8
 * - func_151A25E0
 * - func_151A26EC
 * - func_151A2960
 * - func_151A2A14
 * - func_151A2AD4
 * - func_151A2BD0
 * - func_151A2C24
 * - func_151A2F0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A0E40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A0F28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A1010.s")
void func_151A11CC(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A11E4.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A175C CURRENT (1900) */
void func_151A175C(u8 *arg0) {
    s16 temp_lo;
    s16 temp_lo_2;
    s16 temp_v1;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    u8 *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    if (*(s16 *)((u8 *)arg0 + 0x54) < temp_v1) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) ((*(s16 *)((u8 *)(arg0 + 0x50) + 2) - temp_v1) * *(s16 *)((u8 *)arg0 + 0x50));
    }
    temp_v0 = (void *)(arg0 + 0x50);
    if (*(s16 *)((u8 *)temp_v0 + 0xA) < temp_v1) {
        temp_lo = (*(s16 *)((u8 *)temp_v0 + 8) - temp_v1) * *(s16 *)((u8 *)temp_v0 + 6);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo;
    }
    if (*(s16 *)((u8 *)temp_v0 + 0xC) < temp_v1) {
        temp_t7 = ((*(s16 *)((u8 *)arg0 + 0x20) << 8) | *(u8 *)((u8 *)arg0 + 0x2C)) + (((*(s16 *)((u8 *)temp_v0 + 0xE) << 8) | *(s16 *)((u8 *)temp_v0 + 0x14)) * D_800BE9E4);
        *(s16 *)((u8 *)arg0 + 0x20) = (s16) (temp_t7 >> 8);
        *(u8 *)((u8 *)arg0 + 0x2C) = (u8) temp_t7;
        temp_t6 = ((*(s16 *)((u8 *)arg0 + 0x22) << 8) | *(u8 *)((u8 *)arg0 + 0x2E)) + (((*(s16 *)((u8 *)temp_v0 + 0x10) << 8) | *(s16 *)((u8 *)temp_v0 + 0x16)) * D_800BE9E4);
        *(s16 *)((u8 *)arg0 + 0x22) = (s16) (temp_t6 >> 8);
        *(u8 *)((u8 *)arg0 + 0x2E) = (u8) temp_t6;
        temp_t5 = ((*(s16 *)((u8 *)arg0 + 0x24) << 8) | *(u8 *)((u8 *)arg0 + 0x2D)) + (((*(s16 *)((u8 *)temp_v0 + 0x12) << 8) | *(s16 *)((u8 *)temp_v0 + 0x18)) * D_800BE9E4);
        *(s16 *)((u8 *)arg0 + 0x24) = (s16) (temp_t5 >> 8);
        *(u8 *)((u8 *)arg0 + 0x2D) = (u8) temp_t5;
    }
    if (*(s16 *)((u8 *)arg0 + 0x38) < *(s16 *)((u8 *)temp_v0 + 0x1A)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (*(s16 *)((u8 *)arg0 + 0x38) * *(s16 *)((u8 *)temp_v0 + 0x1C));
    }
    if (*(s16 *)((u8 *)arg0 + 0x38) < *(s16 *)((u8 *)temp_v0 + 0x1E)) {
        temp_lo_2 = *(s16 *)((u8 *)arg0 + 0x38) * *(s16 *)((u8 *)temp_v0 + 0x20);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo_2;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo_2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A175C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A175C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A18DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A1998.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A1E34 CURRENT (815) */
void func_151A1E34(u8 *arg0) {
    s16 temp_lo;
    s16 temp_lo_2;
    s16 temp_v1;
    u8 *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    if (*(s16 *)((u8 *)arg0 + 0x54) < temp_v1) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) ((*(s16 *)((u8 *)(arg0 + 0x50) + 2) - temp_v1) * *(s16 *)((u8 *)arg0 + 0x50));
    }
    temp_v0 = (void *)(arg0 + 0x50);
    if (*(s16 *)((u8 *)temp_v0 + 0xA) < temp_v1) {
        temp_lo = (*(s16 *)((u8 *)temp_v0 + 8) - temp_v1) * *(s16 *)((u8 *)temp_v0 + 6);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo;
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0xC)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (temp_v1 * *(s16 *)((u8 *)temp_v0 + 0xE));
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x10)) {
        temp_lo_2 = temp_v1 * *(s16 *)((u8 *)temp_v0 + 0x12);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo_2;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo_2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A1E34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A1E34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A1EE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A1FB4.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A24A8 CURRENT (1050) */
void func_151A24A8(u8 *arg0) {
    s16 temp_lo;
    s16 temp_v1;
    s32 temp_lo_2;
    s8 temp_lo_3;
    u8 *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    if (*(s16 *)((u8 *)arg0 + 0x54) < temp_v1) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) ((*(s16 *)((u8 *)(arg0 + 0x50) + 2) - temp_v1) * *(s16 *)((u8 *)arg0 + 0x50));
    }
    temp_v0 = (void *)(arg0 + 0x50);
    if (*(s16 *)((u8 *)temp_v0 + 0xA) < temp_v1) {
        temp_lo = (*(s16 *)((u8 *)temp_v0 + 8) - temp_v1) * *(s16 *)((u8 *)temp_v0 + 6);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo;
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x10)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (temp_v1 * *(s16 *)((u8 *)temp_v0 + 0x12));
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x14)) {
        temp_lo_2 = *(s16 *)((u8 *)temp_v0 + 0x16) * D_800BE9E4;
        *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + temp_lo_2);
        *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) + temp_lo_2);
    }
    if (*(s16 *)((u8 *)arg0 + 0x38) < *(s16 *)((u8 *)temp_v0 + 0xC)) {
        *(s8 *)((u8 *)arg0 + 0x2F) = 0x13;
        *(u16 *)((u8 *)arg0 + 0x44) = (u16) (*(u16 *)((u8 *)arg0 + 0x44) | 0x101);
        temp_lo_3 = *(s16 *)((u8 *)arg0 + 0x38) * *(s16 *)((u8 *)temp_v0 + 0xE);
        *(s32 *)((u8 *)arg0 + 0x14) = 0x520003;
        *(s8 *)((u8 *)arg0 + 0x42) = temp_lo_3;
        *(s8 *)((u8 *)arg0 + 0x41) = temp_lo_3;
        *(s8 *)((u8 *)arg0 + 0x40) = temp_lo_3;
    }
    if (*(s16 *)((u8 *)arg0 + 0x38) < *(s16 *)((u8 *)temp_v0 + 0x18)) {
        *(s16 *)((u8 *)arg0 + 0x32) = (s16) *(s16 *)((u8 *)temp_v0 + 0x1A);
        *(s16 *)((u8 *)temp_v0 + 0x18) = -0x270F;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A24A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A24A8.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A25E0 CURRENT (975) */
void func_151A25E0(u8 *arg0) {
    s16 temp_lo;
    s16 temp_v1;
    s32 temp_lo_2;
    s8 temp_lo_3;
    u8 *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    if (*(s16 *)((u8 *)arg0 + 0x54) < temp_v1) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) ((*(s16 *)((u8 *)(arg0 + 0x50) + 2) - temp_v1) * *(s16 *)((u8 *)arg0 + 0x50));
    }
    temp_v0 = (void *)(arg0 + 0x50);
    if (*(s16 *)((u8 *)temp_v0 + 0xA) < temp_v1) {
        temp_lo = (*(s16 *)((u8 *)temp_v0 + 8) - temp_v1) * *(s16 *)((u8 *)temp_v0 + 6);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo;
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x10)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (temp_v1 * *(s16 *)((u8 *)temp_v0 + 0x12));
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x14)) {
        temp_lo_2 = *(s16 *)((u8 *)temp_v0 + 0x16) * D_800BE9E4;
        *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + temp_lo_2);
        *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) + temp_lo_2);
    }
    if (*(s16 *)((u8 *)arg0 + 0x38) < *(s16 *)((u8 *)temp_v0 + 0x18)) {
        *(s16 *)((u8 *)arg0 + 0x32) = (s16) *(s16 *)((u8 *)temp_v0 + 0x1A);
        *(s16 *)((u8 *)temp_v0 + 0x18) = -0x270F;
    }
    temp_lo_3 = *(s16 *)((u8 *)arg0 + 0x38) * *(s16 *)((u8 *)temp_v0 + 0xE);
    *(s8 *)((u8 *)arg0 + 0x42) = temp_lo_3;
    *(s8 *)((u8 *)arg0 + 0x41) = temp_lo_3;
    *(s8 *)((u8 *)arg0 + 0x40) = temp_lo_3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A25E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A25E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A26EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A2960.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A2A14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A2AD4.s")
void func_151A2B84(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, void *arg5) {
    f32 temp_fv0;

    temp_fv0 = 1.0f - arg4;
    *(f32 *)((u8 *)arg5 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * temp_fv0);
    *(f32 *)((u8 *)arg5 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * temp_fv0);
    *(f32 *)((u8 *)arg5 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * temp_fv0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A2BD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A2C24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A2F0C.s")
