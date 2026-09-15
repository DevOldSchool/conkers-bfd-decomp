#include "types.h"

/*
 * Reviewed source unit: src/game/game_200930.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D3480
 * - func_151D3D50
 * - func_151D3E04
 * - func_151D3E6C
 * - func_151D3F14
 * - func_151D3FF4
 * - func_151D40D4
 * - func_151D42E8
 * - func_151D4408
 * - func_151D469C
 * - func_151D4794
 * - func_151D4C38
 * - func_151D4D04
 * - func_151D4DAC
 * - func_151D5174
 * - func_151D5334
 * - func_151D5404
 * - func_151D5514
 * - func_151D5648
 * - func_151D5714
 * - func_151D57F8
 * - func_151D5A18
 * - func_151D5B6C
 * - func_151D5D60
 * - func_151D5E30
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game200930ResourceSlots {
    s32 entries[4];
} Game200930ResourceSlots;

void func_100043B4(s32, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3480.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3D50 CURRENT (739) */
s32 func_151D3D50(u8 *arg0) {
    void *sp18;
    f32 temp_fv0;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x170);
    if (*(s16 *)((u8 *)arg0 + 0x170) > 0) {
        *(f32 *)((u8 *)temp_v0 + 4) = (f32) (*(f32 *)((u8 *)temp_v0 + 4) + (*(f32 *)((u8 *)temp_v0 + 8) * D_800BE9A4));
        sp18 = temp_v0;
        temp_fv0 = func_15144B68(*(f32 *)((u8 *)temp_v0 + 4));
        *(f32 *)((u8 *)temp_v0 + 4) = temp_fv0;
        *(f32 *)((u8 *)arg0 + 0x24) = (f32) ((func_15047D60(temp_fv0) * *(f32 *)((u8 *)temp_v0 + 0xC)) + *(f32 *)((u8 *)arg0 + 0x54));
        *(s16 *)((u8 *)arg0 + 0x170) = (s16) (*(s16 *)((u8 *)arg0 + 0x170) - D_800BE9E4);
    } else {
        *(s32 *)((u8 *)arg0 + 0x20) = (s32) *(s32 *)((u8 *)arg0 + 0x50);
        *(f32 *)((u8 *)arg0 + 0x24) = (f32) *(f32 *)((u8 *)arg0 + 0x54);
        *(s32 *)((u8 *)arg0 + 0x28) = (s32) *(s32 *)((u8 *)arg0 + 0x58);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3D50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3D50.s")
/* Call context: func_15143134: unique active project prototype */
void func_15143134(f32 *, f32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3E04 CURRENT (373) */
void func_151D3E04(void *arg0, f32 *arg1, f32 *arg2, s32 arg3, f32 arg4) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x1D4);
    if (temp_v0 != 0) {
        func_15143134(arg2, arg1, temp_v0 + ((arg3 & 0xFF) << 6));
        return;
    }
    *(f32 *)((u8 *)arg1 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + arg4);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3E04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3E04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3E6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3F14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3FF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D40D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D42E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4408.s")
void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_151D4668(void *arg0) {
    struct {
        void *sp18;
        volatile u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32 *)&sp, 0x3C, (s32)arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D469C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4794.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4C38.s")
void func_15131828(s32, s32, s32, s32);
void func_15131958(void *, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D4D04 CURRENT (10) */
s32 func_151D4D04(s32 arg0, s32 arg1) {
    s32 sp20;
    s32 temp_a2;

    temp_a2 = arg0 + 0xA8;
    sp20 = temp_a2;
    func_15131828(arg0, arg0 + 0xAC, temp_a2, arg0 + 0xAA);
    func_15131958((void *)(arg0 + 0x58), *(f32 *)(temp_a2 + 0xC));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D4D04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4D04.s")
/* Call context: func_151D469C: unique active project prototype */
void func_151D469C(u8 *, s32, s32, s32, s32);

void func_151D4D58(u8 *arg0) {
    func_151D469C(arg0, 0, 0x50, 0xFF, 1);
    func_151D469C(arg0, 1, 0x50, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4DAC.s")
void func_151D5148(void *arg0) {
    void *temp_v0;
    s16 temp_v1;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    temp_v1 = *(s16 *)((u8 *)temp_v0 + 0x24);
    if (temp_v1 > 0) {
        *(s16 *)((u8 *)temp_v0 + 0x24) = (s16) (temp_v1 - 1);
        temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    }
    *(s16 *)((u8 *)temp_v0 + 0x1AA) = (s16) (*(s16 *)((u8 *)temp_v0 + 0x1AA) + 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5174.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5334.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5404.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5514.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5648.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5714.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D57F8.s")
/* Call context: func_15145740: unique active project prototype */
/* Call context: func_15145EA4: unique active project prototype */
void func_15145740(void *, void *, void *, void *, f32);
void func_15145EA4(s32 *, s32 *, s32, s32);
extern f32 D_800AB240;
extern f32 D_800AB244;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5A18 CURRENT (4979) */
void func_151D5A18(void *arg0, s32 arg1, void *arg2, void *arg3, void *arg4, s32 arg5, u8 arg6) {
    s32 sp44;
    s32 sp40;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    f32 var_ft4;
    f32 var_ft5;

    func_15145740(arg0, arg2, arg3, arg4, D_800AB240);
    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        sp40 = arg1;
        sp44 = arg5;
        func_15145EA4(&sp44, &sp40, *(s32 *)((u8 *)arg0 + 0x1D4) + (arg6 << 6), 1);
        return;
    }
    temp_fa1 = *(f32 *)((u8 *)arg2 + 0);
    if ((D_800AB244 < fabsf(temp_fa1)) || (D_800AB244 < fabsf(*(f32 *)((u8 *)arg2 + 8)))) {
        temp_fv1 = *(f32 *)((u8 *)arg2 + 8);
        temp_fa0 = 1.0f / sqrtf((temp_fa1 * temp_fa1) + (temp_fv1 * temp_fv1));
        var_ft4 = temp_fv1 * temp_fa0;
        var_ft5 = -temp_fa1 * temp_fa0;
    } else {
        var_ft4 = 1.0f;
        var_ft5 = 0.0f;
    }
    *(f32 *)((u8 *)arg1 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + (34.0f * var_ft5));
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + 49.0f);
    *(f32 *)((u8 *)arg1 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C) + (34.0f * var_ft4));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5A18 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5A18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5B6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5D60.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5E30 CURRENT (405) */
void func_151D5E30(Game200930ResourceSlots *arg0) {
    register s32 resource;
    s32 index;

    index = 0;
    do {
        resource = arg0->entries[index];
        if (resource != 0) {
            func_100043B4(resource, 3);
        }
        index = (index + 1) & 0xFF;
    } while (index < 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5E30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5E30.s")
