#include "types.h"

/*
 * Reviewed source unit: src/game/game_157840.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512A390
 * - func_1512ABF8
 * - func_1512AD54
 * - func_1512B1B8
 * - func_1512B53C
 * - func_1512B630
 * - func_1512B730
 * - func_1512BB10
 * - func_1512C068
 * - func_1512C150
 * - func_1512C20C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512A390.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512ABF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512AD54.s")
void func_1512AD54(void);
extern u8 D_800BEAC0;
extern u8 D_800C3671;

void func_1512B100(void *arg0) {
    u8 *base;
    s32 state;
    s32 flags;

    base = (u8 *)arg0;
    state = *(s32 *)(base + 0x2C);
    if ((state & ~0x100) && (D_800BEAC0 == 0) && (D_800C3671 == 0)) {
        if (state != 0x40) {
            flags = *(s32 *)(base + 0x84);
            if ((flags & 8) && !(flags & 0x200) && (*(u8 *)(base + 0x23C) == 0)) {
                flags = *(s32 *)(base + 0x5F0);
                if (!(flags & 0x80) && !(flags & 0x40)) {
                    func_1512AD54();
                    return;
                }
            }
        }
        *(s16 *)(base + 0x5F8) = 1;
        *(s16 *)(base + 0x5FC) = 2;
        *(s16 *)(base + 0x5FE) = 0x3C;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B1B8.s")
extern s32 D_800BE628;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512B53C CURRENT (4675) */
s32 func_1512B53C(void *arg0) {
    s32 var_v0;
    s32 var_v1;
    u8 *table;
    u8 *entry;

    table = (u8 *)D_800BE628;
    if (*(s16 *)((u8 *)arg0 + 0x5FC) != 0) {
        *(s16 *)((u8 *)arg0 + 0x5F8) = 1;
        var_v0 = 0;
        var_v1 = 0;
        entry = table + (*(u8 *)((u8 *)arg0 + 0x23D) * 0x180);
        if (*(f32 *)(entry + 4) > 0.0f) {
            do {
                var_v0 += 1;
                *(s16 *)((u8 *)*(s32 *)((u8 *)arg0 + 0x8BC) + var_v1) = (s16)0xFFFC;
                var_v1 += 2;
            } while ((f32)var_v0 < *(f32 *)(entry + 4));
        }
        *(f32 *)((u8 *)arg0 + 0x60C) = 0.0f;
        *(s16 *)((u8 *)arg0 + 0x5FC) -= 1;
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512B53C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B53C.s")
void func_1512B5FC(void *arg0, s32 arg1, s32 arg2) {
    *(u8 *)((u8 *)arg0 + 2) = (u8) *(u8 *)((u8 *)arg0 + 1);
    if (*(s32 *)((u8 *)arg0 + 4) < arg1) {
        *(u8 *)((u8 *)arg0 + 1) = 0U;
    } else {
        *(u8 *)((u8 *)arg0 + 1) = 1U;
    }
    *(s32 *)((u8 *)arg0 + 8) = arg2;
    *(s32 *)((u8 *)arg0 + 4) = arg1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B730.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512BB10.s")
void func_15123A54(f32, f32);
void func_1512C150(void *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512C068 CURRENT (20) */
void func_1512C068(u8 *arg0) {
    f32 temp_fa0;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft3;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa1;
    s32 temp_v0;

    if (*(f32 *)(arg0 + 0x390) < 180.0f) {
        var_fa1 = 2.0f;
    } else {
        var_fa1 = -2.0f;
    }
    temp_v0 = *(s32 *)(arg0 + 0x2C);
    if ((temp_v0 != 0x80) && (temp_v0 != 0x40)) {
        temp_fv1 = *(f32 *)(arg0 + 0x2F8) - *(f32 *)(arg0 + 0x2BC);
        temp_fa0 = *(f32 *)(arg0 + 0x300) - *(f32 *)(arg0 + 0x2C4);
        temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
        *(f32 *)(arg0 + 0x370) = temp_fv0;
        if (temp_fv0 < 42.0f) {
            temp_ft4 = 45.0f;
            temp_ft3 = *(f32 *)(arg0 + 0x37C);
            temp_ft1 = 0.0f;
            temp_ft5 = temp_ft4 * var_fa1;
            *(f32 *)(arg0 + 0x5CC) = temp_ft1;
            temp_ft0 = temp_ft3 - temp_ft5;
            *(f32 *)(arg0 + 0x384) = temp_ft0;
            func_15123A54(temp_fa0, var_fa1);
            *(s32 *)(arg0 + 0x240) |= 2;
        }
    }
    func_1512C150(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512C068 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512C068.s")
f32 func_15048A70(f32, f32);                        /* extern */
extern f32 D_800A3694;
extern f32 D_800A3698;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512C150 CURRENT (150) */
void func_1512C150(void *arg0) {
    f32 temp_fv0;

    *(f32 *)((u8 *)arg0 + 0x5CC) = (f32) (*(f32 *)((u8 *)arg0 + 0x5CC) + D_800A3694);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x5CC);
    if (temp_fv0 > 1.0f) {
        *(f32 *)((u8 *)arg0 + 0x5CC) = 1.0f;
    } else {
        *(f32 *)((u8 *)arg0 + 0x5CC) = temp_fv0;
    }
    if (*(f32 *)((u8 *)arg0 + 0x5CC) == 1.0f) {
        *(s32 *)((u8 *)arg0 + 0x240) = (s32) (*(s32 *)((u8 *)arg0 + 0x240) & ~2);
        *(f32 *)((u8 *)arg0 + 0x384) = (f32) D_800A3698;
        return;
    }
    *(f32 *)((u8 *)arg0 + 0x384) = (f32) (*(f32 *)((u8 *)arg0 + 0x384) + (func_15048A70(*(f32 *)((u8 *)arg0 + 0x384), *(f32 *)((u8 *)arg0 + 0x37C)) * *(f32 *)((u8 *)arg0 + 0x5CC)));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512C150 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512C150.s")
void func_1512C200(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512C20C.s")
s32 func_1512C47C(s32 arg0) {
    return 1;
}
