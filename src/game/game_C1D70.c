#include "types.h"

/*
 * Reviewed source unit: src/game/game_C1D70.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150948C0
 * - func_1509499C
 * - func_15094AB8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1509499C(u8 *, u8 *);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
extern void *D_800D2C20;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150948C0 CURRENT (893) */
void func_150948C0(u8 *arg0, s32 arg1) {
    void *items[16];
    s32 index;
    u8 *item;
    void *current;
    f32 *output;

    func_1509499C(arg0, (u8 *)items);
    index = 0;
    item = (u8 *)(s32)items;
    do {
        current = *(void **)item;
        if (current != 0) {
            output = (f32 *)(arg1 + index * 0xC);
            func_150A7960(D_800D2C20,
                          (f32)*(s16 *)current,
                          (f32)*(s16 *)((u8 *)current + 2),
                          (f32)*(s16 *)((u8 *)current + 4),
                          output, output + 1, output + 2);
        }
        index++;
        item += 4;
    } while (index != 0x10);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150948C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C1D70/func_150948C0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509499C CURRENT (130) */
void func_1509499C(u8 *arg0, u8 *arg1) {
    s16 temp_a2;
    s16 temp_v1;
    s32 var_a3;
    u8 *var_v0;

    temp_v1 = arg0[1];
    var_v0 = *(u8 **)(arg0 + 4);
    temp_a2 = temp_v1 & 0xF;
    temp_v1 = (temp_v1 >> 4) + 1;
    for (var_a3 = 0; var_a3 < temp_a2; var_a3++) {
        ((s32 *)arg1)[var_a3] = 0;
    }
    for (var_a3 = temp_a2; var_a3 < temp_v1; var_a3++) {
        ((u8 **)arg1)[var_a3] = var_v0;
        var_v0 += 0x10;
    }
    for (; var_a3 < 0x10; var_a3++) {
        ((s32 *)arg1)[var_a3] = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509499C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C1D70/func_1509499C.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15047C00(f32);                             /* extern */
extern f32 D_8009DEA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15094AB8 CURRENT (19612) */
void func_15094AB8(u8 *arg0, u8 *arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    f32 sp34;
    f32 sp24;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_ft4;
    f32 var_ft5;
    void *temp_a0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *var_v0;
    u8 *var_v1;

    temp_fa0 = arg3 * D_8009DEA0;
    sp24 = temp_fa0;
    sp34 = func_15047D60(temp_fa0);
    temp_fv0 = func_15047C00(temp_fa0);
    {
        s32 var_a1 = 0;
    if ((arg2 > 0) && (!(arg2 & 1) || (temp_fv1 = (f32) ((arg4 / 2) << 5), var_a1 = 1, temp_fa0_2 = (f32) ((arg5 / 2) << 5), *(s16 *)((u8 *)arg0 + 8) = (s16) (s32) (((((f32) *(s16 *)((u8 *)arg1 + 0) - temp_fv1) * temp_fv0) - (((f32) *(s16 *)((u8 *)arg1 + 2) - temp_fa0_2) * sp34)) + temp_fv1), *(s16 *)((u8 *)arg0 + 0xA) = (s16) (s32) ((((f32) *(s16 *)((u8 *)arg1 + 2) - temp_fa0_2) * temp_fv0) + (((f32) *(s16 *)((u8 *)arg1 + 0) - temp_fv1) * sp34) + temp_fa0_2), (arg2 != 1)))) {
        temp_fv1_2 = (f32) ((arg4 / 2) << 5);
        var_v1 = (void *)(arg0 + (var_a1 * 0x10));
        temp_v0 = (void *)(arg1 + (var_a1 * 4));
        temp_fa0_3 = (f32) ((arg5 / 2) << 5);
        temp_a0 = (void *)((arg2 * 4) + arg1);
        var_v0 = (void *)(temp_v0 + 8);
        var_ft5 = ((f32) *(s16 *)((u8 *)temp_v0 + 0) - temp_fv1_2) * temp_fv0;
        var_ft4 = ((f32) *(s16 *)((u8 *)temp_v0 + 2) - temp_fa0_3) * sp34;
        if (var_v0 != temp_a0) {
            do {
                var_v0 += 8;
                var_v1 += 0x20;
                *(s16 *)((u8 *)var_v1 + -0x18) = (s16) (s32) ((var_ft5 - var_ft4) + temp_fv1_2);
                *(s16 *)((u8 *)var_v1 + -0x16) = (s16) (s32) ((((f32) *(s16 *)((u8 *)var_v0 + -0xE) - temp_fa0_3) * temp_fv0) + (((f32) *(s16 *)((u8 *)var_v0 + -0x10) - temp_fv1_2) * sp34) + temp_fa0_3);
                *(s16 *)((u8 *)var_v1 + -8) = (s16) (s32) (((((f32) *(s16 *)((u8 *)var_v0 + -0xC) - temp_fv1_2) * temp_fv0) - (((f32) *(s16 *)((u8 *)var_v0 + -0xA) - temp_fa0_3) * sp34)) + temp_fv1_2);
                *(s16 *)((u8 *)var_v1 + -6) = (s16) (s32) ((((f32) *(s16 *)((u8 *)var_v0 + -0xA) - temp_fa0_3) * temp_fv0) + (((f32) *(s16 *)((u8 *)var_v0 + -0xC) - temp_fv1_2) * sp34) + temp_fa0_3);
                var_ft5 = ((f32) *(s16 *)((u8 *)var_v0 + -8) - temp_fv1_2) * temp_fv0;
                var_ft4 = ((f32) *(s16 *)((u8 *)var_v0 + -6) - temp_fa0_3) * sp34;
            } while (var_v0 != temp_a0);
        }
        temp_v1 = (void *)(var_v1 + 0x20);
        *(s16 *)((u8 *)temp_v1 + -0x18) = (s16) (s32) ((var_ft5 - var_ft4) + temp_fv1_2);
        *(s16 *)((u8 *)temp_v1 + -0x16) = (s16) (s32) ((((f32) *(s16 *)((u8 *)var_v0 + -6) - temp_fa0_3) * temp_fv0) + (((f32) *(s16 *)((u8 *)var_v0 + -8) - temp_fv1_2) * sp34) + temp_fa0_3);
        *(s16 *)((u8 *)temp_v1 + -8) = (s16) (s32) (((((f32) *(s16 *)((u8 *)var_v0 + -4) - temp_fv1_2) * temp_fv0) - (((f32) *(s16 *)((u8 *)var_v0 + -2) - temp_fa0_3) * sp34)) + temp_fv1_2);
        *(s16 *)((u8 *)temp_v1 + -6) = (s16) (s32) ((((f32) *(s16 *)((u8 *)var_v0 + -2) - temp_fa0_3) * temp_fv0) + (((f32) *(s16 *)((u8 *)var_v0 + -4) - temp_fv1_2) * sp34) + temp_fa0_3);
    }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15094AB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C1D70/func_15094AB8.s")
void func_15094E98(void) {

}
