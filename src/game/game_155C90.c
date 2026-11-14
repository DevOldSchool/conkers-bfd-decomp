#include "types.h"

/*
 * Reviewed source unit: src/game/game_155C90.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 */

typedef struct Game155C90Actor { u8 pad00[0x3C]; f32 speed; } Game155C90Actor;
typedef struct Game155C90Target { u8 pad00[0x120]; u8 active; } Game155C90Target;
typedef struct Game155C90Camera {
    u8 pad00[0x2C];
    s32 flags;
    u8 pad30[0x104];
    s32 setting;
    u8 pad138[0x104];
    u8 instant;
    u8 pad23D[0x153];
    f32 angle;
    u8 pad394[0x14];
    f32 valueA;
    u8 pad3AC[0x24];
    Game155C90Actor *actor;
    Game155C90Target *target;
    u8 pad3D8[0x210];
    f32 valueB;
    u8 pad5EC[0x70];
    f32 velocityA, velocityB;
    u8 pad664[0x64];
    s32 state;
    u8 pad6CC[0x30];
    s32 mode;
    u8 pad700[0x3C];
    s16 state73C;
    u8 pad73E[0x76];
    f32 delta;
} Game155C90Camera;

void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)
extern f32 D_800894F0[][5];
extern s32 D_800D2DB4;

void func_151287E0(Game155C90Camera *arg0, f32 *arg1, f32 *arg2) {
    f32 angle;
    s32 savedSetting;
    f32 scaleA;
    f32 scaleB;
    f32 speedScaleA;
    f32 speedScaleB;
    f32 bias;
    f32 value;
    f32 angle2;
    f32 speed;

    savedSetting = arg0->setting;
    if (arg0->flags & 0x40) {
        arg0->setting = 0;
    }
    if (D_800D2DB4 != 0 || (arg0->state73C != 0 && arg0->state73C != 3) || arg0->target->active != 0) {
        func_150495B0(&arg0->valueB, 0.0f, &arg0->velocityB, 6.0f, 9.0f, arg0->delta);
        func_150495B0(&arg0->valueA, 0.0f, &arg0->velocityA, 1.5f, 2.5f, arg0->delta);
        return;
    }
    scaleA = D_800894F0[arg0->setting][0];
    scaleB = D_800894F0[arg0->setting][1];
    speedScaleA = D_800894F0[arg0->setting][2];
    speedScaleB = D_800894F0[arg0->setting][3];
    bias = D_800894F0[arg0->setting][4];
    if (arg0->instant != 0 || scaleA == speedScaleA) {
        speed = 0.0f;
    } else {
        speed = arg0->actor->speed;
    }
    if (speed > 30.0f) {
        speed = 30.0f;
    }
    angle = arg0->angle;
    if (arg0->state != 0 && (arg0->mode == 10 || arg0->mode == 14)) {
        angle = fabsf(arg0->angle);
    }
    while (angle > 180.0f) {
        angle = 360.0f - angle;
    }
    if (angle < 90.0f) {
        angle = -180.0f + angle;
    }
    angle -= 90.0f * (angle < 0.0f ? -1.0f : 1.0f);
    value = (angle * 0.011111111f * scaleA - angle * speed * 0.00037037037f * speedScaleA) + bias;
    if (arg0->flags & 0x100) {
        value = 0.0f;
    }
    if (arg2 != 0) {
        *arg2 = value;
    } else if (arg0->instant != 0) {
        arg0->valueA = value;
        arg0->velocityA = 0.0f;
    } else {
        func_150495B0(&arg0->valueA, value, &arg0->velocityA, 1.5f, 2.5f, arg0->delta);
    }
    angle2 = arg0->angle;
    while (angle2 > 180.0f) {
        angle2 -= 360.0f;
    }
    if (angle2 > 90.0f) {
        angle2 = 180.0f - angle2;
    } else if (angle2 < -90.0f) {
        angle2 = -180.0f - angle2;
    }
    if (arg1 != 0) {
        *arg1 = -(angle2 * 0.011111111f * scaleB) - angle2 * speed * 0.00037037037f * speedScaleB;
    } else if (arg0->instant != 0) {
        arg0->valueB = -(angle2 * 0.011111111f * scaleB) - angle2 * speed * 0.00037037037f * speedScaleB;
        arg0->velocityB = 0.0f;
    } else if (arg0->flags & 0x100) {
        func_150495B0(&arg0->valueB, -(angle2 * 0.011111111f * scaleB) - angle2 * speed * 0.00037037037f * speedScaleB, &arg0->velocityB, 6.0f, 9.0f, arg0->delta);
    } else {
        func_150495B0(&arg0->valueB, -(angle2 * 0.011111111f * scaleB) - angle2 * speed * 0.00037037037f * speedScaleB, &arg0->velocityB, 1.5f, 2.5f, arg0->delta);
    }
    arg0->setting = savedSetting;
}
