#include "types.h"

/*
 * Reviewed source unit: src/game/game_DC6B0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AF200
 * - func_150AF2E0
 * - func_150AF328
 * - func_150AF6E4
 * - func_150AF738
 * - func_150AF7C4
 * - func_150AFBF4
 * - func_150AFC68
 * - func_150AFDB0
 * - func_150AFE64
 * - func_150B003C
 * - func_150B0094
 * - func_150B0348
 * - func_150B060C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF200.s")
extern void func_151CF898(void *arg0, f32 arg1, f32 arg2, void *arg3);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AF2E0 CURRENT (10) */
void func_150AF2E0(void *arg0, void *arg1) {
    s16 temp_v0;

    temp_v0 = *(s16 *)((u8 *)arg1 + 2);
    func_151CF898(arg0, (f32)(temp_v0 + *(s16 *)((u8 *)arg1 + 8)), (f32)temp_v0, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AF2E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF2E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF328.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF6E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF738.s")
void func_150B1DB0(s32 arg0, s32 arg1, s32 arg2);

void func_150AF790(s32 arg0, s32 arg1) {
    func_150B1DB0(arg1, arg1 + 0x1ECC0, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF7C4.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AFBF4 CURRENT (469) */
s32 func_150AFBF4(u8 *arg0) {
    void *sp18;
    f32 temp_fv0;
    u8 *temp_v1;

    *(f32 *)((u8 *)arg0 + 0x78) = (f32) (*(f32 *)((u8 *)arg0 + 0x78) + (*(f32 *)((u8 *)arg0 + 0x7C) * D_800BE9A4));
    temp_fv0 = func_15144B68(*(f32 *)((u8 *)arg0 + 0x78));
    temp_v1 = (void *)(arg0 + 0x70);
    *(f32 *)((u8 *)temp_v1 + 8) = temp_fv0;
    sp18 = temp_v1;
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) ((func_15047D60(temp_fv0) * *(f32 *)((u8 *)temp_v1 + 4)) + *(f32 *)((u8 *)arg0 + 0x70));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AFBF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AFBF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AFC68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AFDB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AFE64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150B003C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150B0094.s")
void func_1516972C(void *arg0, void *arg1);
void func_150B02C0(void *arg0);
void func_15132570(s32 arg0);
void func_1513259C(s32 arg0);

void func_150B02C0(void *arg0) {
    volatile void **field_170 = (volatile void **)((u8 *)arg0 + 0x170);

    if (*field_170 != 0) {
        func_1516972C(*field_170, arg0);
    }
}

void func_150B02F0(s32 arg0) {
    func_150B02C0(arg0);
    func_15132570(arg0);
}
void func_150B031C(s32 arg0) {
    func_150B02C0(arg0);
    func_1513259C(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150B0348.s")
/* Call context: func_151149AC: unique active project prototype */
s32 func_151149AC(u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B060C CURRENT (309) */
s32 func_150B060C(s32 arg0, void *arg1) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = func_151149AC(arg0 & 0xFF);
    *(s32 *)((u8 *)arg1 + 8) = temp_v0;
    if (temp_v0 == 0) {
        return 0;
    }
    temp_v1 = *(s32 *)((u8 *)arg1 + 8);
    *(f32 *)((u8 *)arg1 + 0) = -150.0f;
    *(f32 *)((u8 *)arg1 + 4) = 4.5f;
    *(f32 *)((u8 *)arg1 + 0xC) = (f32) *(s16 *)((u8 *)temp_v1 + 0x10);
    *(f32 *)((u8 *)arg1 + 0x10) = (f32) *(s16 *)((u8 *)temp_v1 + 0x12);
    *(f32 *)((u8 *)arg1 + 0x14) = (f32) *(s16 *)((u8 *)temp_v1 + 0x14);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B060C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150B060C.s")
