#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_11A680.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_state_resource_helpers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150ED298
 * - func_150ED578
 * - func_150ED638
 * - func_150ED748
 * - func_150EEC84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_15144BC8: unique active project prototype */
f32 func_15144BC8(f32);

f32 func_150ED1D0(f32 arg0, f32 arg1) {
    f32 temp_fv0;
    f32 var_fv1;

    arg0 = func_15144BC8(arg0);
    temp_fv0 = func_15144BC8(func_15144BC8(arg1) - arg0);
    var_fv1 = temp_fv0;
    if (temp_fv0 > 180.0f) {
        var_fv1 = -360.0f + temp_fv0;
    }
    return var_fv1;
}
typedef struct {
    u8 pad_0[0x14];
    f32 field_14;
    u8 pad_18[4];
    f32 field_1C;
    u8 pad_20[0x20];
    f32 field_40;
} Game11A680Position;

s32 func_1505A630(f32, f32, s32);

void func_150ED234(Game11A680Position *arg0, Game11A680Position *arg1) {
    func_150ED1D0((f32)(func_1505A630(arg1->field_14 - arg0->field_14,
                                     arg0->field_1C - arg1->field_1C, 0) + 0x4000) * 0.005493164f,
                  arg0->field_40);
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_15047C00(f32);
f32 func_15047D60(f32);
f32 func_15048408(f32);
f32 func_150484A0(f32, f32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_151EFEB8(void *, s32);
extern f32 D_800A1590, D_800A1594, D_800A1598, D_800A159C;
extern f32 D_800A15A0, D_800A15A4, D_800A15A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150ED298 CURRENT (6825) */
f32 func_150ED298(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 discriminant;
    f32 x;
    f32 y;
    f32 z;
    f32 speedY;
    f32 speedX;
    f32 height;
    f32 distance;
    f32 result;
    f32 matrix[16];
    f32 angle;
    register f32 root, negativeSpeed;
    register f32 time, firstTime, secondTime;
    s32 transform;

    transform = *(s32 *)((u8 *)arg0 + 0x1D4);
    if (transform != 0) {
        func_151EFEB8(matrix, transform + 0xC0);
        func_150A7960(matrix, 0.0f, 0.0f, 1.0f, &x, &y, &z);
        x -= matrix[12];
        z -= matrix[14];
        y -= matrix[13];
        arg1 = func_150484A0(y, sqrtf(x * x + z * z)) * D_800A1590;
        if (arg1 > 180.0f) {
            arg1 -= 360.0f;
        }
        y = matrix[13];
        x = matrix[12];
        z = matrix[14];
    } else {
        x = *(f32 *)((u8 *)arg0 + 0x14);
        y = *(f32 *)((u8 *)arg0 + 0x18);
        z = *(f32 *)((u8 *)arg0 + 0x1C);
    }
    x = arg2 - x;
    height = arg3 - y;
    z = arg4 - z;
    distance = sqrtf(x * x + z * z) - arg5;
    if (distance < 100.0f) {
        distance = 100.0f;
    }
    result = D_800A1594;
    angle = arg1 * D_800A1598;
    speedX = func_15047C00(angle) * D_800A159C;
    speedY = func_15047D60(angle) * D_800A15A0;
    discriminant = speedY * speedY + 2.0f * (height * -2.5f);
    if (discriminant > 0.0f) {
        root = sqrtf(discriminant);
        negativeSpeed = -speedY;
        firstTime = (negativeSpeed - root) / -2.5f;
        time = firstTime;
        if (firstTime > 0.0f) {
            secondTime = (negativeSpeed + root) / -2.5f;
            if (secondTime > 0.0f && firstTime < secondTime) {
                time = secondTime;
            }
        }
        if (time > 0.0f) {
            result = distance - time * speedX;
        }
    } else {
        result = (func_15048408(sqrtf(-2.0f * height * -2.5f) * D_800A15A4) * D_800A15A8 - arg1) * 1000.0f;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150ED298 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED298.s")
extern u8 D_800BE616;
extern u32 *D_800BE728;
extern u8 *D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150ED578 CURRENT (220) */
void func_150ED578(void *arg0) {
    u8 var_v0;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v1;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x31C);
    if ((temp_v0 != 0) && (*(u8 *)(temp_v0 + 0x84) == 0)) {
        if (D_800BE616 != 0) {
            var_v0 = *(u8 *)((u8 *)arg0 + 0x127);
        } else {
            var_v0 = *(u8 *)((u8 *)arg0 + 0x124);
        }
        if ((*(u16 *)D_800BE728[var_v0] & 0x10) != 0) {
            temp_v1 = D_800CC2D0 + (var_v0 * 0x32C);
            if (*(u8 *)(*(u8 **)(temp_v1 + 0x31C) + 0x197) != 0) {
                temp_v0_2 = *(u8 **)(temp_v1 + 0x318);
                if (temp_v0_2 != 0) {
                    *(u8 *)((u8 *)arg0 + 0x2FC) |= (u8)(1 << *(u8 *)(temp_v0_2 + 0x23D));
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150ED578 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED578.s")
void func_15062FC0(void *, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150ED638 CURRENT (570) */
void func_150ED638(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;

    if (arg1 < -0x2D) {
        arg1 = -0x2D;
    } else {
        var_v0 = arg1;
        if (arg1 >= 0x2E) {
            var_v0 = 0x2D;
        }
        arg1 = var_v0;
    }
    if (arg2 < -0x2D) {
        arg2 = -0x2D;
    } else {
        var_v0_2 = arg2;
        if (arg2 >= 0x2E) {
            var_v0_2 = 0x2D;
        }
        arg2 = var_v0_2;
    }
    if (*(u8 *)((u8 *)arg0 + 4) == 0x28) {
        var_s0 = 0x7C;
    } else {
        temp_v0 = arg1;
        arg1 = arg2;
        var_s0 = 0x1C;
        arg2 = temp_v0;
    }
    func_15062FC0(arg0, 0, 0, 0x800, 0x800, var_s0, arg2 * -7, 0);
    func_15062FC0(arg0, 1, var_s0, 0x800, 0x800, var_s0,
                  arg1 * -7, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150ED638 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED638.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED748.s")
void func_151254F4(void *, s32);
void func_1517F488(s32, s32, s32, s32, s32, s32);
extern u8 D_800BE748[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EEC84 CURRENT (741) */
void func_150EEC84(u8 *arg0) {
    s32 var_a1;
    u8 *temp_s0;
    s32 temp_v0;

    temp_v0 = *(s32 *)(arg0 + 0x318);
    arg0[5] = 3;
    *(s16 *)(arg0 + 0xE4) = 0;
    arg0[0x125] = 0xFF;
    arg0[0x328] = 0;
    if (temp_v0 != 0) {
        var_a1 = 0;
        temp_s0 = (u8 *)temp_v0;
        if (*(u8 *)((u32)temp_v0 + 0x23DU) == 3) {
            var_a1 = 1;
        }
        func_151254F4(temp_s0, var_a1);
        (*(u8 **)(arg0 + 0x31C))[0x78] = 0x29;
        *(u16 *)(D_800BE748 + (var_a1 * 6)) &= 0xFFEF;
        arg0 = (u8 *)((u32)&D_800CC2D0 + (u32)var_a1 * 0x32CU);
        arg0[0x2FC] |= (u8)(1U << (temp_s0[0x23D] & 31));
        if (arg0[0x10A] != 0) {
            func_1517F488(0xFF, 0, 0, 0xB4, 0x14, (s32)temp_s0[0x23D]);
            arg0[0x10A] = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EEC84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150EEC84.s")
void func_151045E0(s32, s32, s32);

void func_150EEDA8(void *arg0) {
    if (*(u8 *)((u8 *)arg0 + 5) != 3) {
        func_151045E0((s32)arg0, 0xF, 0x437A0000);
        *(u8 *)((u8 *)arg0 + 5) = 3;
        *(s16 *)((u8 *)arg0 + 0xE4) = 0;
        *(u8 *)((u8 *)arg0 + 0x125) = 0xFF;
    }
    func_15052590(arg0);
}
