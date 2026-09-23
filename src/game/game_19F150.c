#include "types.h"

/*
 * Reviewed source unit: src/game/game_19F150.c
 * Boundary evidence: docs/evidence/game_raw_animated_emission_controllers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15171CA0
 * - func_15171D4C
 * - func_151720C4
 * - func_151725FC
 * - func_15172B20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game19F150Object {
    u8 pad0[0x16];
    s16 field_16;
    u8 pad18[0x0E];
    s16 field_26;
    u8 pad28[0x0E];
    s16 field_36;
    u8 pad38[0x0E];
    s16 field_46;
    u8 pad48[8];
    s16 field_50;
    s16 field_52;
    s16 field_54;
    u16 field_56;
    u8 field_58;
    s8 field_59;
} Game19F150Object;

extern Game19F150Object *func_15167A68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15171CA0 CURRENT (595) */
Game19F150Object *func_15171CA0(s16 arg0, u16 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    Game19F150Object *var_v1;

    var_v1 = func_15167A68(arg5 == 0 ? 0xF : 0x43, arg7, 0x60, 1, arg6, 1);
    if (var_v1 == 0) {
        return 0;
    }
    var_v1->field_52 = 0;
    var_v1->field_50 = arg0;
    var_v1->field_54 = arg4;
    var_v1->field_56 = arg1;
    var_v1->field_58 = arg2;
    var_v1->field_16 = 0;
    var_v1->field_26 = 0;
    var_v1->field_36 = 0;
    var_v1->field_46 = 0;
    var_v1->field_59 = arg3;
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15171CA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_15171CA0.s")
typedef struct Game171D4CGeometry {
    u8 pad00[0x10];
    s16 values[0x1E];
} Game171D4CGeometry;

void func_1516972C(Game19F150Object *);
Game19F150Object *func_15171CA0(s16, u16, u8, s32, s32, s32, u8, s32);
s32 func_15172B20(s32, f32, f32, f32, f32, s32, s32, u8);
extern u8 *D_8008CA4C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15171D4C CURRENT (3135) */
void func_15171D4C(f32 arg0, f32 arg1, f32 arg2, s16 arg3,
                    u16 arg4, u8 arg5, f32 arg6, s32 arg7,
                    s32 arg8, s32 arg9, s32 arg10, s32 arg11,
                    u8 arg12, s32 arg13) {
    Game19F150Object *object;
    Game19F150Object *saved;
    Game171D4CGeometry *geometry;
    f32 radius;
    s16 y;
    s16 left;
    s16 right;
    s16 bottom;
    s16 top;
    s16 uv;
    u8 *descriptor;

    object = func_15171CA0(arg3, arg4, arg5, arg9, arg10, arg11,
                            arg12, arg13);
    if (object != 0) {
        if (!(arg9 & 2)) {
            saved = object;
            if (func_15172B20((s32)((u8 *)object + 0x10), arg0, arg1,
                              arg2, arg6, arg7, arg8,
                              *(u16 *)(D_8008CA4C[object->field_58] + 6)) == 0) {
                func_1516972C(saved);
            }
        } else {
            geometry = (Game171D4CGeometry *)object;
            radius = (f32)arg8;
            y = (s16)(s32)arg1;
            geometry->values[(0x42 - 0x10) / 2] = y;
            geometry->values[(0x32 - 0x10) / 2] = y;
            geometry->values[(0x22 - 0x10) / 2] = y;
            geometry->values[(0x12 - 0x10) / 2] = y;
            left = (s16)(s32)(arg0 - radius);
            geometry->values[(0x40 - 0x10) / 2] = left;
            geometry->values[(0x10 - 0x10) / 2] = left;
            right = (s16)(s32)(radius + arg0);
            bottom = (s16)(s32)(arg2 - radius);
            top = (s16)(s32)(radius + arg2);
            geometry->values[(0x48 - 0x10) / 2] = 0x2000;
            geometry->values[(0x30 - 0x10) / 2] = right;
            geometry->values[(0x20 - 0x10) / 2] = right;
            geometry->values[(0x18 - 0x10) / 2] =
                geometry->values[(0x48 - 0x10) / 2];
            geometry->values[(0x24 - 0x10) / 2] = bottom;
            geometry->values[(0x14 - 0x10) / 2] = bottom;
            geometry->values[(0x44 - 0x10) / 2] = top;
            geometry->values[(0x34 - 0x10) / 2] = top;
            descriptor = D_8008CA4C[arg5];
            geometry->values[(0x2A - 0x10) / 2] = 0x2000;
            uv = (*(u16 *)(descriptor + 6) + 0x100) << 5;
            geometry->values[(0x38 - 0x10) / 2] = uv;
            geometry->values[(0x28 - 0x10) / 2] = uv;
            geometry->values[(0x1A - 0x10) / 2] =
                geometry->values[(0x2A - 0x10) / 2];
            uv = (*(u16 *)(descriptor + 8) + 0x100) << 5;
            geometry->values[(0x4A - 0x10) / 2] = uv;
            geometry->values[(0x3A - 0x10) / 2] = uv;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15171D4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_15171D4C.s")
void func_1516972C(Game19F150Object *);
Game19F150Object *func_15171CA0(s16, u16, u8, s32, s32, s32, u8, s32);
s32 func_151725FC(s32, s32, f32, f32, f32, f32, s32, s32);
f32 func_15047C00(f32);
f32 func_15047D60(f32);
void func_1510E82C(s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32);
extern u8 *D_8008CA4C[];
extern f32 D_800A7154;
extern f32 D_800A7158;

void func_15171F04(f32 arg0, f32 arg1, f32 arg2, s32 arg3,
                   s16 arg4, u16 arg5, u8 arg6, s32 arg7, s32 arg8,
                   s32 arg9, s32 arg10, u8 arg11, s32 arg12) {
    Game19F150Object *object;

    object = func_15171CA0(arg4, arg5, arg6, arg8, arg9, arg10,
                           (u8)arg11, arg12);
    if (object != 0) {
        if (func_151725FC((s32)((u8 *)object + 0x10), arg3, arg0, arg1,
                          arg2, 0.0f, arg7,
                          *(u16 *)((u8 *)D_8008CA4C[object->field_58] + 6)) == 0) {
            func_1516972C(object);
        }
    }
}
extern s32 D_800BE9E4;

void func_15171FC0(Game19F150Object *arg0) {
    s16 temp_v0;
    s32 temp_v0_2;

    temp_v0 = arg0->field_50;
    if (temp_v0 < -1) {
        arg0->field_50 = temp_v0 + 1;
        if (arg0->field_50 == -1) {
            func_1516972C(arg0);
        }
    } else {
        if (temp_v0 == 0) {
            arg0->field_50 = -3;
            return;
        }
        if (temp_v0 != -1) {
            if (!((u8) arg0->field_59 & 4)) {
                if (D_800BE9E4 < temp_v0) {
                    arg0->field_50 = temp_v0 - D_800BE9E4;
                } else {
                    arg0->field_50 = 0;
                }
            }
            arg0->field_52 += arg0->field_54;
            temp_v0_2 = D_8008CA4C[arg0->field_58][4];
            if (((s16) arg0->field_52 / 256) >= (s32) temp_v0_2) {
                if ((u8) arg0->field_59 & 4) {
                    arg0->field_50 = -3;
                    return;
                }
                arg0->field_52 = (temp_v0_2 << 8) - 0x100;
            }
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_151720C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_151725FC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15172B20 CURRENT (2037) */
s32 func_15172B20(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, u8 arg7) {
    f32 sp50;
    s32 sp48;
    f32 sp44;
    s32 sp40;
    f32 angle;
    f32 x;
    f32 z;
    f32 scale;

    angle = (arg4 - 90.0f) * D_800A7154;
    sp50 = func_15047C00(angle);
    scale = (f32)arg5;
    x = arg1 + (scale * func_15047D60(angle));
    z = arg3 + (scale * sp50);
    arg1 = x;
    arg3 = z;
    func_1510E82C((s32)&sp40, 0, (s32)&sp44, 0, (s32)&sp48, 0,
                  x, arg2, z, arg2, 0, 0);
    if (sp40 == 0) {
        return 0;
    }
    if (sp44 == D_800A7158) {
        return 0;
    }
    return func_151725FC(arg0, sp40, arg1, sp44, arg3, arg4, arg6, arg7);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15172B20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_15172B20.s")
