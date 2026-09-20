#include "types.h"

/*
 * Reviewed source unit: src/game/game_10D7B0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E0348
 * - func_150E03F8
 * - func_150E05F8
 * - func_150E06D8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_1515F170(s32 arg0, s32 arg1);
extern void func_1513BAE8(void);
extern u8 D_80088980;

void func_150E0300(void) {
    if (D_80088980 == 0) {
        func_1515F170(6, 0);
        func_1513BAE8();
        D_80088980 = 1;
    }
}
extern u32 func_1513418C(void *arg0, s32 arg1, u8 arg2, s32 arg3);
extern f32 D_800A0FB4;
extern f32 D_800A0FB8;
extern s32 D_800A5480[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E0348 CURRENT (3363) */
void func_150E0348(void *arg0, u8 arg1, s32 arg2) {
    s8 sp45;
    s8 sp44;
    s8 sp43;
    s8 sp42;
    s16 sp40;
    f32 sp3C;
    f32 sp38;
    s32 sp2C[3];
    s8 sp28;
    void *sp24;
    u8 sp20;
    s32 sp1C;
    s32 sp18;

    sp18 = 0;
    sp1C = 0;
    sp28 = 0;
    sp24 = arg0;
    sp20 = *(u8 *)((u8 *)arg0 + 0x3B);
    sp2C[0] = D_800A5480[0];
    sp2C[1] = D_800A5480[1];
    sp2C[2] = D_800A5480[2];
    sp40 = 0x12C;
    sp42 = 0x1B;
    sp43 = 0xB;
    sp44 = -1;
    sp45 = 0;
    sp38 = D_800A0FB4;
    sp3C = D_800A0FB8;
    func_1513418C(&sp18, 0, arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E0348 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E0348.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E03F8.s")
extern f32 D_800A0FD0;
extern f32 D_800A0FD4;
extern void *D_800DBFF0;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E05F8 CURRENT (970) */
void func_150E05F8(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_v0;

    temp_fv1 = *(f32 *)((u8 *)D_800DBFF0 + 0x300) - (f32) *(s16 *)((u8 *)arg0 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)D_800DBFF0 + 0x2F8) - (f32) *(s16 *)((u8 *)arg0 + 0x10);
    temp_fa1 = *(f32 *)((u8 *)D_800DBFF0 + 0x2FC) - (f32) *(s16 *)((u8 *)arg0 + 0x12);
    temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + ((temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1)));
    if (temp_fv0 <= D_800A0FD0) {
        var_v0 = 0xFF;
    } else if (D_800A0FD4 <= temp_fv0) {
        var_v0 = 0;
    } else {
        var_v0 = (s32) (255.0f - ((temp_fv0 - D_800A0FD0) * (1.0f / (D_800A0FD4 - D_800A0FD0)) * 255.0f));
    }
    *(s8 *)((u8 *)arg0 + 0x8A) = (s8) var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E05F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E05F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E06D8.s")
