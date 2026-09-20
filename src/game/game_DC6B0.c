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
 * - func_150AF7C4
 * - func_150AFBF4
 * - func_150AFDB0
 * - func_150AFE64
 * - func_150B0094
 * - func_150B0348
 * - func_150B060C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_151149AC(s32);
void func_1505D024(s32, s32, s32, s32);
extern u8 D_800CC2D0;
extern u8 D_800CC3D4;
extern s32 D_800DBEF4;
extern s32 D_800DBF94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AF200 CURRENT (40) */
void func_150AF200(s32 arg0, s32 arg1) {
    s32 delta;
    s32 index;

    if (D_800CC3D4 == 0) {
        delta = func_151149AC(arg0 & 0xFF) - D_800DBEF4;
        index = delta / 160;
        if (*(s32 *)(D_800DBF94 + (index * 4)) & 1) {
            func_1505D024((s32)&D_800CC2D0, 0x3F, 0x6E00, -1);
            return;
        }
        delta = func_151149AC((u8)arg1) - D_800DBEF4;
        index = delta / 160;
        if (*(s32 *)(D_800DBF94 + (index * 4)) & 1) {
            func_1505D024((s32)&D_800CC2D0, 0x3F, 0xEE00, -1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AF200 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF200.s")
extern void func_151CF898(void *arg0, f32 arg1, f32 arg2, void *arg3);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AF2E0 CURRENT (20) */
void func_150AF2E0(void *arg0, void *arg1) {
    s32 temp_v0;
    s32 temp_t7;

    temp_v0 = *(s16 *)((u8 *)arg1 + 2);
    temp_t7 = temp_v0 + *(s16 *)((u8 *)arg1 + 8);
    func_151CF898(arg0, (f32)temp_t7, (f32)temp_v0, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AF2E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF2E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF328.s")
/* Call context: func_15131828: unique active project prototype */
/* Call context: func_15131958: unique active project prototype */
void func_15131828(s32, s32, s32, s32);
void func_15131958(void *, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AF6E4 CURRENT (10) */
s32 func_150AF6E4(s32 arg0, s32 arg1) {
    s32 sp20;
    s32 temp_a2;

    temp_a2 = arg0 + 0xA8;
    sp20 = temp_a2;
    func_15131828(arg0, arg0 + 0xAC, temp_a2, arg0 + 0xAA);
    func_15131958((void *)(arg0 + 0x58), *(f32 *)((u8 *)temp_a2 + 0xC));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AF6E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF6E4.s")
void func_1515FF74(s8 *, s32, u8, void *);

void func_150AF738(s16 arg0, u8 arg1, void *arg2) {
    struct {
        s8 sp18;
        s8 sp19;
        s8 sp1A;
        u8 pad1B;
        s16 sp1C;
        s8 sp1E;
    } locals;

    locals.sp18 = 1;
    locals.sp19 = -1;
    locals.sp1A = 2;
    locals.sp1E = 0;
    locals.sp1C = arg0;
    func_1515FF74(&locals.sp18, 0, arg1, arg2);
}
void func_150B1DB0(s32 arg0, s32 arg1, s32 arg2);

void func_150AF790(s32 arg0, s32 arg1) {
    func_150B1DB0(arg1, arg1 + 0x1ECC0, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF7C4.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AFBF4 CURRENT (220) */
s32 func_150AFBF4(u8 *arg0) {
    volatile struct {
        u8 *ptr;
        u8 pad[4];
    } saved;
    register f32 temp_fv0;
    volatile f32 *temp_v1;

    *(f32 *)((u8 *)arg0 + 0x78) += *(f32 *)((u8 *)arg0 + 0x7C) * D_800BE9A4;
    temp_fv0 = func_15144B68(*(f32 *)((u8 *)arg0 + 0x78));
    temp_v1 = (volatile f32 *)((s32)arg0 + 0x70);
    temp_v1[2] = temp_fv0;
    saved.ptr = (u8 *)temp_v1;
    temp_fv0 = func_15047D60(temp_fv0);
    temp_v1 = (volatile f32 *)saved.ptr;
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) (temp_v1[0] + (temp_v1[1] * temp_fv0));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AFBF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AFBF4.s")
void func_1516D99C(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_150AFC68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516D99C(1, 0, 0, 0xD, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 1, 0, 0, 0, 0, 0xAA, 0xAA, 0xAA, 0xAA, arg2, arg3, 0, arg0, 0xF0, 0x50, 0x50, 1, 4, 0, 1, 0, 0, 0, arg1, 0, (u8) (s32) arg4, arg5);
}
void func_1516972C(void *);
extern u8 D_800C3E78;
extern void *D_800DCE94;
extern s8 D_800DD190;
extern s32 D_800DD198;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AFDB0 CURRENT (3002) */
void func_150AFDB0(void) {
    s32 temp_t7;
    void **var_v0;
    void *var_a0;
    u8 *var_s0;

    var_a0 = D_800DCE94;
    temp_t7 = D_800DD190 + 1;
    D_800DD190 = temp_t7;
    if (var_a0 != 0) {
        var_v0 = (void **)((u8 *)&D_800DD198 + ((s8)temp_t7 * 4));
        var_s0 = &D_800C3E78;
        do {
            *var_v0 = *(void **)((u8 *)var_a0 + 8);
            if (*var_s0 == *(u8 *)((u8 *)var_a0 + 0x3F)) {
                func_1516972C(var_a0);
                var_v0 = (void **)((u8 *)&D_800DD198 + (D_800DD190 * 4));
            }
            var_a0 = *var_v0;
        } while (var_a0 != 0);
    }
    D_800DD190 -= 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AFDB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AFDB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AFE64.s")
void func_15179008(s32);
void func_150AF200(s32, s32);
extern s32 D_800BE9F0;

void func_150B003C(s32 arg0) {
    if (D_800BE9F0 == 6) {
        func_15179008(0);
        func_150AF200(0xE2, 0xE1);
        return;
    }
    func_150AF200(0xDF, 0xDE);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150B0094.s")
void func_1516972C(void *arg0);
void func_150B02C0(void *arg0);
void func_15132570(s32 arg0);
void func_1513259C(s32 arg0);

void func_150B02C0(void *arg0) {
    volatile void **field_170 = (volatile void **)((u8 *)arg0 + 0x170);

    if (*field_170 != 0) {
        func_1516972C((void *)*field_170);
    }
}

void func_150B02F0(s32 arg0) {
    func_150B02C0((void *)arg0);
    func_15132570(arg0);
}
void func_150B031C(s32 arg0) {
    func_150B02C0((void *)arg0);
    func_1513259C(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150B0348.s")
/* Call context: func_151149AC: unique active project prototype */
s32 func_151149AC(s32);

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
