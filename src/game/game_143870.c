#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_143870.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511650C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15047C00(f32);
extern f32 D_800A2FB0;
extern f32 D_800A2FB4;
extern s32 D_800BE9E4;

void func_151163C0(u8 *actor) {
    f32 heightScale;
    s32 heightRate;
    s32 swayRate;
    f32 swayScale;
    s16 previousHeight;
    f32 previousSway;
    f32 result;

    heightRate = (*(s32 *)(actor + 0x3C) >> 16) & 0xFF;
    heightScale = (f32)(*(s32 *)(actor + 0x3C) & 0xFF);
    swayRate = (*(s32 *)(actor + 0x3C) >> 24) & 0xFF;
    swayScale = (f32)(u32)((*(s32 *)(actor + 0x3C) >> 8) & 0xFF) * 1.40625f;
    previousHeight = *(s16 *)(actor + 0x12);
    previousSway = *(f32 *)actor;
    *(f32 *)(actor + 0x18) = func_15047C00((f32)*(s32 *)(actor + 0x7C) * D_800A2FB0) * heightScale;
    result = func_15047C00((f32)*(s32 *)(actor + 0x80) * D_800A2FB4) * swayScale;
    *(f32 *)actor = result;
    *(s32 *)(actor + 0x7C) += heightRate * D_800BE9E4;
    *(s32 *)(actor + 0x80) += swayRate * D_800BE9E4;
    *(s16 *)(actor + 0x5C) = *(s16 *)(actor + 0x12) - previousHeight;
    *(f32 *)(actor + 0x60) = result - previousSway;
}
void func_1000F91C(u16, s32, s16, s32, s32, s32, s32, s32, s32, s32);
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15116888(s32, s32, s32, void *);
void func_100111C8(u16);
void func_1511515C(void *);
extern f64 D_800A2FB8;
extern f32 D_800A2FC0, D_800A2FC4, D_800A2FC8, D_800A2FCC, D_800A2FD0;
extern u8 D_800CC2D0[];
f32 fabsf(f32);
#pragma intrinsic(fabsf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511650C CURRENT (1005) */
void func_1511650C(void *arg0, s32 arg1, s32 arg2, f32 arg3) {
    register s32 value;
    register s32 timer;
    register s32 push;
    s32 adjustment;
    register f32 velocity;
    register f32 amount;
    register u16 sound;

    if (!(*(u8 *)((u8 *)arg0 + 0x4F) & 4)) {
        push = 0;
    } else {
        push = func_15116888(*(s16 *)((u8 *)arg0 + 0x10),
                             *(s16 *)((u8 *)arg0 + 0x14),
                             (s32)((u8 *)arg0 + 0x7C), D_800CC2D0) >> 3;
    }
    if ((arg1 & 1) && (push < 0)) {
        push = 0;
    }
    value = *(s16 *)((u8 *)arg0 + 0x3C) + push;
    if (push != 0) {
        *(s32 *)((u8 *)arg0 + 0x80) = 0;
    }
    timer = *(s32 *)((u8 *)arg0 + 0x80);
    adjustment = (s32) ((f64) value * D_800A2FB8);
    if (timer <= 0) {
        value += adjustment;
        if (value > 0) {
            value -= 1;
            if (value <= 0) {
                if (push == 0) {
                    if (timer == 0) {
                        *(s32 *)((u8 *)arg0 + 0x80) = 0x14;
                    } else {
                        *(s32 *)((u8 *)arg0 + 0x80) = 0;
                        value = 0;
                    }
                } else {
                    value = 0;
                }
            }
        } else if (value < 0) {
            value += 1;
            if (value >= 0) {
                if (push == 0) {
                    if (timer == 0) {
                        *(s32 *)((u8 *)arg0 + 0x80) = 0x14;
                    } else {
                        *(s32 *)((u8 *)arg0 + 0x80) = 0;
                        value = 0;
                    }
                } else {
                    value = 0;
                }
            }
        }
    } else if (timer > 0) {
        if (value > 0) {
            value += 1;
            if ((*(s32 *)((u8 *)arg0 + 0x80) = timer - D_800BE9E4) <= 0) {
                *(s32 *)((u8 *)arg0 + 0x80) = -1;
            }
        } else {
            value -= 1;
            if ((*(s32 *)((u8 *)arg0 + 0x80) = timer - D_800BE9E4) <= 0) {
                *(s32 *)((u8 *)arg0 + 0x80) = -1;
            }
        }
    }
    *(s32 *)((u8 *)arg0 + 0x3C) =
        (*(s32 *)((u8 *)arg0 + 0x3C) & 0xFFFF) | ((u32)value << 0x10);
    func_1511515C(arg0);
    if (arg2 != 0) {
        velocity = *(f32 *)((u8 *)arg0 + 0x64);
        amount = fabsf(velocity) * D_800A2FC0;
        if (amount > 1.0f) {
            amount = 1.0f;
        }
        value = (u32) ((D_800A2FC4 * amount) + D_800A2FC8);
        sound = *(u16 *)((u8 *)arg0 + 0x74);
        amount = (amount * arg3) - 500.0f;
        if (sound == 0) {
            if (D_800A2FCC < velocity) {
                *(u16 *)((u8 *)arg0 + 0x74) = func_10010F88(
                    arg2, (u16)value, (s32)(s16)(s32)amount, 0, -1,
                    *(s16 *)((u8 *)arg0 + 0x10), *(s16 *)((u8 *)arg0 + 0x12),
                    *(s16 *)((u8 *)arg0 + 0x14), 0x3E8, 0x1770);
            }
        } else {
            adjustment = value & 0xFFFF;
            if (D_800A2FD0 < velocity) {
                func_1000F91C(sound, adjustment, (s16)(s32)amount, 0, -1,
                              *(s16 *)((u8 *)arg0 + 0x10),
                              *(s16 *)((u8 *)arg0 + 0x12),
                              *(s16 *)((u8 *)arg0 + 0x14), 0xC8, 0x7D0);
                return;
            }
            func_100111C8(sound);
            *(u16 *)((u8 *)arg0 + 0x74) = 0U;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511650C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_143870/func_1511650C.s")

s32 func_15116888(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 x;
    s32 z;
    s32 bearing;
    s32 angle;
    s32 tmp1;
    f32 result;
    f32 displacement[3];
    f32 cosine;

    x = (s32)*(f32 *)((u8 *)arg3 + 0x14);
    z = (s32)*(f32 *)((u8 *)arg3 + 0x1C);
    tmp1 = z;
    displacement[0] = (f32)(x - arg0);
    displacement[2] = tmp1 - arg1;
    bearing = func_150490A8(displacement);
    angle = *(u16 *)((u8 *)arg3 + 0x76);
    angle = 0x40 - (angle >> 8);
    angle -= bearing;
    cosine = func_15048A40(angle);
    result = *(f32 *)((u8 *)arg3 + 0x3C) * cosine;
    return (s32)result;
}
void func_15116924(s32 arg0) {

}
