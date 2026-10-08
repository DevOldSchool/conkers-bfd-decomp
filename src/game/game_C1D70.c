#include "types.h"

/*
 * Reviewed source unit: src/game/game_C1D70.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150948C0
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
void func_1509499C(u8 *arg0, u8 *arg1) {
    s16 temp_a2;
    s16 temp_v1;
    s32 var_a3;
    u8 *var_v0;

    var_v0 = *(u8 **)(arg0 + 4);
    temp_v1 = arg0[1];
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
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15047C00(f32);                             /* extern */
extern f32 D_8009DEA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15094AB8 CURRENT (9301) */
void func_15094AB8(u8 *arg0, u8 *arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    struct Output {
        s16 prefix[4];
        s16 x;
        s16 y;
        s16 suffix[2];
    };
    struct Input {
        s16 x;
        s16 y;
    };
    struct Output *output = (struct Output *)arg0;
    struct Input *input = (struct Input *)arg1;
    f32 angle;
    f32 sine;
    f32 cosine;
    f32 centerX;
    f32 centerY;
    s32 i;

    angle = arg3 * D_8009DEA0;
    sine = func_15047D60(angle);
    cosine = func_15047C00(angle);
    for (i = 0; i < arg2; i++) {
        centerX = (f32)((arg4 / 2) << 5);
        centerY = (f32)((arg5 / 2) << 5);
        output[i].x = (s32)
            ((((f32)input[i].x - centerX) * cosine -
              ((f32)input[i].y - centerY) * sine) + centerX);
        output[i].y = (s32)
            ((((f32)input[i].y - centerY) * cosine +
              ((f32)input[i].x - centerX) * sine) + centerY);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15094AB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C1D70/func_15094AB8.s")
void func_15094E98(void) {

}
