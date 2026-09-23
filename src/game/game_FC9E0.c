#include "types.h"

/*
 * Reviewed source unit: src/game/game_FC9E0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CF530
 * - func_150CF5E8
 * - func_150CF680
 * - func_150CF800
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_151CF898(void *arg0, f32 arg1, f32 arg2, void *arg3);
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF530 CURRENT (100) */
void func_150CF530(s32 arg0, void *arg3) {
    func_151CF898(&D_800CC2D0, *(f32 *)((u8 *)&D_800CC2D0 + 0x18) + 300.0f, -10000.0f, arg3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF530 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF530.s")
extern s32 D_80088890;
extern s32 D_80088894;
extern s32 D_80088898;
extern s32 D_800BE9E4;

void func_150CF578(s32 arg0) {
    s32 count;
    s32 temp_v1;

    count = D_800BE9E4;
    D_80088890 += count * 0x1A;
    temp_v1 = count * 0x1C;
    D_80088894 -= temp_v1;
    D_80088898 -= temp_v1;
}
extern s32 D_8008889C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF5E8 CURRENT (575) */
void *func_150CF5E8(u8 *arg0) {
    u8 *temp_a0;

    *(s32 *)((u8 *)arg0 + 0) = (s32) (((((s32) D_80088890 >> 7) & 0xFFF) << 0xC) | 0xF2000000 | (((s32) D_80088894 >> 7) & 0xFFF));
    *(s32 *)((u8 *)arg0 + 4) = 0x47E47E;
    temp_a0 = (void *)(arg0 + 8);
    *(s32 *)((u8 *)arg0 + 8) = (s32) (((((s32) D_80088898 >> 7) & 0xFFF) << 0xC) | 0xF2000000 | (((s32) D_8008889C >> 7) & 0xFFF));
    *(s32 *)((u8 *)temp_a0 + 4) = 0x0147E47E;
    return temp_a0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF5E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF5E8.s")
void *func_10022EC0(void *, const void *, u32);
void *func_1515548C(f32 *, s32, s32, s32, s32, s32, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF680 CURRENT (2297) */
void func_150CF680(s16 arg0, u8 arg1, s32 arg2) {
    struct {
        u8 sp30;
        u8 gap31[3];
        f32 sp34, sp38, sp3C, sp40, sp44, sp48, sp4C;
        u8 sp50;
        u8 gap51;
        s16 sp52, sp54, sp56, sp58;
        u8 sp5A, sp5B, sp5C, sp5D, sp5E, sp5F, sp60, sp61, sp62, sp63;
        s32 sp64, sp68, sp6C, sp70, sp74, sp78, sp7C;
        u8 sp80, sp81;
        u8 gap82[2];
        s8 sp84;
        u8 gap85[3];
        f32 sp88, sp8C, sp90, sp94;
    } locals;
    u8 *result;

    locals.sp54 = 0x31;
    locals.sp5A = 8;
    locals.sp50 = 0xC1;
    locals.sp56 = 1;
    locals.sp61 = 0xFF;
    locals.sp52 = arg0;
    locals.sp58 = 0xFF;
    locals.sp5B = 0xFF;
    locals.sp63 = 0xFF;
    locals.sp68 = 0x200004;
    locals.sp5C = 0xFF;
    locals.sp5D = 0xFF;
    locals.sp5E = 0xFF;
    locals.sp5F = 0xFF;
    locals.sp60 = 0xFF;
    locals.sp62 = 0xFF;
    locals.sp30 = 0;
    locals.sp34 = 0.0f;
    locals.sp40 = -300.0f;
    locals.sp38 = -300.0f;
    locals.sp3C = 0.0f;
    locals.sp4C = 7.5f;
    locals.sp48 = 7.5f;
    locals.sp64 = 0;
    locals.sp6C = 0x9F0601;
    locals.sp80 = 0;
    locals.sp81 = 0xA;
    locals.sp70 = 0x17;
    locals.sp74 = 0x44;
    locals.sp78 = 0x80;
    locals.sp7C = 0x20;
    locals.sp8C = 1.0f;
    locals.sp88 = 1.0f;
    locals.sp94 = 0.0f;
    locals.sp90 = 0.0f;
    locals.sp44 = 72.0f;
    locals.sp84 = D_80082FA0;
    result = func_1515548C(&locals.sp40, 0xC, 0, 0, 0x10, arg1, arg2);
    if (result != 0) {
        func_10022EC0(result + 0x70, &locals.sp30, 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF680 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF680.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF800.s")
void func_150CFBEC(u8 *arg0, f32 *arg1, u8 arg2) {
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x70);
    if (arg2 == 0x52) {
        *temp_v0 = (u8)(*temp_v0 | 1);
        *(f32 *)((u8 *)temp_v0 + 4) = 0.0f;
        *(f32 *)((u8 *)temp_v0 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x10);
        *(f32 *)((u8 *)temp_v0 + 0xC) = (f32) (*arg1 - *(f32 *)((u8 *)arg0 + 0x10));
    }
}
void func_150CFC38(f32 arg0) {
    f32 sp1C;

    sp1C = arg0;
    func_1515572C(&sp1C, 0x52);
}
