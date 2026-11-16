#include "types.h"
#include <PR/gbi.h>

/*
 * Reviewed source unit: src/game/game_C1D70.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_reconciled_empty_stub_splits.md
 */

void func_1509499C(u8 *, u8 *);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
extern void *D_800D2C20;

void func_150948C0(u8 *arg0, s32 arg1) {
    s16 *items[16];
    s32 index;
    f32 *output;

    func_1509499C(arg0, (u8 *)items);
    for (index = 0; index < 16; index++) {
        if (items[index] != 0) {
            output = (f32 *)(arg1 + index * 0xC);
            func_150A7960(D_800D2C20, items[index][0], items[index][1], items[index][2],
                          output, output + 1, output + 2);
        }
    }
}
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

void func_15094AB8(Vtx *arg0, s16 (*arg1)[2], s32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    s32 halfWidth;
    s32 halfHeight;
    f32 sine;
    f32 cosine;
    f32 centerX;
    f32 centerY;
    f32 angle;
    s32 i;

    angle = arg3 * D_8009DEA0;
    sine = func_15047D60(angle);
    cosine = func_15047C00(angle);
    halfWidth = arg4 / 2;
    halfHeight = arg5 / 2;
    centerX = halfWidth << 5;
    centerY = halfHeight << 5;
    for (i = 0; i < arg2; i++) {
        arg0[i].v.tc[0] = ((arg1[i][0] - centerX) * cosine - (arg1[i][1] - centerY) * sine) + centerX;
        arg0[i].v.tc[1] = ((arg1[i][0] - centerX) * sine + (arg1[i][1] - centerY) * cosine) + centerY;
    }
}
void func_15094E98(void) {

}
