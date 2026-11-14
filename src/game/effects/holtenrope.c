#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/effects/holtenrope.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_beta_camera_rope_bee.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B32C8
 * - func_151B3FDC
 * - func_151B4A14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct HoltenRopePoint {
    f32 x;
    f32 y;
    f32 z;
    Vec3f velocity;
} HoltenRopePoint;

typedef struct HoltenRopeEffect {
    u8 pad0[0x10];
    u8 flags;
    u8 pad11;
    s16 timer;
    u8 primaryState[0xC];
    u8 secondaryState[0xC];
    s8 primaryCallback;
    s8 secondaryCallback;
    u8 pad2E[6];
    s8 updateCallback;
    u8 pad35[3];
    f32 radius;
    f32 gain;
    f32 stiffness;
    u8 pad44[4];
    HoltenRopePoint points[10];
    f32 doubledRadiusSquared;
    s32 scaledRadius;
    u8 resetState[1];
} HoltenRopeEffect;

typedef s32 (*HoltenRopeStateCallback)(HoltenRopeEffect *, void *, s32);
typedef s32 (*HoltenRopeUpdateCallback)(HoltenRopeEffect *);

void func_100226F0(void *, s32);
void *func_10022EC0(void *, const void *, u32);
extern f32 D_800AA390;
extern s32 D_800BE9E4;
extern HoltenRopeStateCallback D_8008FAF0[];
extern HoltenRopeUpdateCallback D_8008FAF8[];

HoltenRopeEffect *func_151B30B0(void *arg0, f32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    HoltenRopeEffect *result;
    f32 radius;

    result = func_15167A68(0x33, arg4, arg2 + 0x150, 1, arg3, 1);
    if (result == 0) {
        return 0;
    }
    func_10022EC0(&result->flags, arg0, 0x38);
    radius = result->radius;
    result->flags |= 0xE;
    result->doubledRadiusSquared = 2.0f * ((radius * radius) / D_800AA390);
    result->scaledRadius = (s32)(radius * arg1 * 4096.0f);
    func_100226F0(result->resetState, 0x10);
    return result;
}

void func_151B3184(HoltenRopeEffect *arg0) {
    s32 callback;
    u8 finished = 0;

    if (arg0->flags & 1) {
        arg0->timer -= D_800BE9E4;
        if (arg0->timer < 0) {
            finished = 1;
        }
    }
    if (finished == 0) {
        callback = arg0->primaryCallback;
        if (callback != -1) {
            if (D_8008FAF0[callback](arg0, arg0->primaryState, 1) == 0) {
                finished = 1;
            }
        }
        callback = arg0->secondaryCallback;
        if (callback != -1) {
            if (D_8008FAF0[callback](arg0, arg0->secondaryState, 0) == 0) {
                finished = 1;
            }
        }
        if ((arg0->flags & 4) || (arg0->flags & 8)) {
            arg0->flags |= 2;
        } else {
            callback = arg0->updateCallback;
            if (callback != -1) {
                if (D_8008FAF8[callback](arg0) == 0) {
                    finished = 1;
                }
            }
        }
    }
    if (finished != 0) {
        func_1516972C(arg0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B32C8.s")
extern void (*D_8008FB68[])(void *, s32, u8);

void func_151B3A34(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008FB68[*(u8 *)((u8 *)arg0 + 0x44)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}

s32 func_151B3A7C(u8 *arg0) {
    HoltenRopeEffect *effect = (HoltenRopeEffect *)arg0;
    Vec3f delta;
    Vec3f pos;
    Vec3f *start = (Vec3f *)effect->primaryState;
    Vec3f *end = (Vec3f *)effect->secondaryState;
    s32 i;

    delta.x = end->x - start->x;
    delta.y = end->y - start->y;
    delta.z = end->z - start->z;
    pos = *start;
    for (i = 0; i < 10; i++) {
        HoltenRopePoint *point = &effect->points[i];

        *(Vec3f *)point = pos;
        point->velocity.x = 0.0f;
        point->velocity.y = 0.0f;
        point->velocity.z = 0.0f;
        pos.x += delta.x * 0.11111111f;
        pos.y += delta.y * 0.11111111f;
        pos.z += delta.z * 0.11111111f;
    }
    effect->flags &= ~2;
    return 1;
}
/* Call context: func_15047D60: unique active project prototype */
/* Call context: func_150484A0: unique active project prototype */
f32 func_15047D60(f32);
f32 func_150484A0(f32, f32);
f32 func_15047C00(f32);                             /* extern */
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 fabsf(f32);
#pragma intrinsic(fabsf)

s32 func_151B3CF0(HoltenRopeEffect *arg0) {
    Vec3f delta;
    Vec3f mid;
    Vec3f a;
    Vec3f b;
    f32 inv;
    f32 nx;
    f32 nz;
    f32 px;
    f32 py;
    f32 heading;
    f32 angle;
    f32 r;
    s32 i;

    delta.x = ((Vec3f *)arg0->secondaryState)->x - ((Vec3f *)arg0->primaryState)->x;
    delta.y = ((Vec3f *)arg0->secondaryState)->y - ((Vec3f *)arg0->primaryState)->y;
    delta.z = ((Vec3f *)arg0->secondaryState)->z - ((Vec3f *)arg0->primaryState)->z;
    if ((0.0001f < fabsf(delta.x)) || (0.0001f < fabsf(delta.z))) {
        mid.x = ((Vec3f *)arg0->primaryState)->x + (delta.x * 0.5f);
        mid.y = ((Vec3f *)arg0->primaryState)->y + (delta.y * 0.5f);
        mid.z = ((Vec3f *)arg0->primaryState)->z + (delta.z * 0.5f);
        a.x = ((Vec3f *)arg0->primaryState)->x - mid.x;
        a.y = ((Vec3f *)arg0->primaryState)->y - mid.y;
        a.z = ((Vec3f *)arg0->primaryState)->z - mid.z;
        b.x = ((Vec3f *)arg0->secondaryState)->x - mid.x;
        b.y = ((Vec3f *)arg0->secondaryState)->y - mid.y;
        b.z = ((Vec3f *)arg0->secondaryState)->z - mid.z;
        inv = 1.0f / sqrtf((delta.x * delta.x) + (delta.z * delta.z));
        nx = delta.z * inv;
        nz = delta.x * inv;
        px = ((b.z * nx) + (b.x * nz)) - ((a.z * nx) + (a.x * nz));
        py = b.y - a.y;
        heading = func_150484A0(py, px);
        r = sqrtf((px * px) + (py * py)) * 0.5f;
        angle = heading - 3.1415927f;
        for (i = 0; i < 10; i++, angle += 0.34906587f) {
            HoltenRopePoint *point = &arg0->points[i];
            f32 s = func_15047D60(angle);
            f32 c = func_15047C00(angle);

            point->x = (r * c * nz) + mid.x;
            point->y = (r * s) + mid.y;
            point->z = (r * c * nx) + mid.z;
        }
    }
    return 1;
}
extern f32 D_800AA3AC;

s32 func_151B3F28(void *arg0, f32 *arg1, u8 arg2) {
    s32 result;

    result = 1;
    if (arg2 != 0) {
        u8 *base;

        base = (u8 *)arg0 + 0x150;
        if (*(s32 *)*(u8 **)base != 0 && base[4] == (*(u8 **)base)[0x3B]) {
            arg1[0] = *(f32 *)(*(u8 **)base + 0x14);
            arg1[1] = *(f32 *)(*(u8 **)base + 0x18);
            arg1[2] = *(f32 *)(*(u8 **)base + 0x1C);
            *(u8 *)((u8 *)arg0 + 0x10) &= ~4;
        } else {
            result = 0;
            *(u8 *)((u8 *)arg0 + 0x10) |= 0xC;
        }
    } else {
        arg1[0] = 0.0f;
        arg1[1] = D_800AA3AC;
        arg1[2] = 0.0f;
        *(u8 *)((u8 *)arg0 + 0x10) &= ~8;
    }
    return result;
}
/* Call context: func_15047D60: unique active project prototype */
s32 func_151B3A7C(u8 *);
extern f32 D_800AA3B0;
extern f32 D_800AA3B4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B3FDC CURRENT (8437) */
s32 func_151B3FDC(u8 *arg0) {
    volatile f32 sp110;
    volatile f32 sp108;
    volatile f32 sp104;
    volatile f32 sp100;
    volatile f32 spFC;
    volatile f32 spF8;
    volatile f32 spF4;
    volatile f32 spF0;
    volatile f32 spEC;
    volatile f32 spE8;
    volatile f32 spD0;
    volatile f32 spAC;
    volatile f32 spA4;
    volatile f32 sp98;
    volatile f32 sp6C;
    volatile f32 sp68;
    volatile f32 sp64;
    volatile f32 sp5C;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs1_2;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs3_2;
    f32 temp_fs4;
    f32 temp_fs4_2;
    f32 temp_fs5;
    f32 temp_fs5_2;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 temp_ft4;
    f32 temp_ft4_2;
    f32 temp_ft4_3;
    f32 temp_ft5;
    f32 temp_ft5_2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 var_fs0;
    s32 var_s1;
    u8 *var_s2;
    u8 *node;
    f32 threshold;

    threshold = D_800AA3B0;
    temp_fs4 = *(f32 *)((u8 *)arg0 + 0x20);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14);
    temp_fs5 = *(f32 *)((u8 *)arg0 + 0x24);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x18);
    temp_fs0 = temp_fs4 - temp_fv1;
    temp_fv0 = fabsf(temp_fs0);
    sp110 = temp_fs5 - temp_fa0;
    temp_ft4 = *(f32 *)((u8 *)arg0 + 0x28);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x1C);
    sp5C = temp_ft4;
    temp_fs3 = temp_ft4 - temp_fa1;
    if ((threshold < temp_fv0) || (threshold < fabsf(temp_fs3))) {
        temp_ft4_2 = temp_fv1 + (temp_fs0 * 0.5f);
        sp100 = temp_ft4_2;
        temp_ft5 = temp_fa0 + (sp110 * 0.5f);
        spF4 = temp_fv1 - temp_ft4_2;
        temp_fs1 = temp_fa1 + (temp_fs3 * 0.5f);
        sp104 = temp_ft5;
        sp108 = temp_fs1;
        spE8 = temp_fs4 - temp_ft4_2;
        spEC = temp_fs5 - temp_ft5;
        spF8 = temp_fa0 - temp_ft5;
        spFC = temp_fa1 - temp_fs1;
        temp_ft3 = sp5C - temp_fs1;
        temp_fv0_2 = sqrtf((temp_fs0 * temp_fs0) + (temp_fs3 * temp_fs3));
        spF0 = temp_ft3;
        temp_fv1_2 = 1.0f / temp_fv0_2;
        temp_fs4_2 = temp_fs3 * temp_fv1_2;
        temp_fs5_2 = temp_fs0 * temp_fv1_2;
        temp_ft4_3 = ((temp_ft3 * temp_fs4_2) + (spE8 * temp_fs5_2)) - ((spFC * temp_fs4_2) + (spF4 * temp_fs5_2));
        temp_ft5_2 = spEC - spF8;
        spD0 = temp_ft4_3;
        temp_ft0 = (temp_ft4_3 * temp_ft4_3) + (temp_ft5_2 * temp_ft5_2);
        temp_fv0_3 = sqrtf(temp_ft0);
        sp64 = temp_ft0;
        spA4 = temp_ft0;
        temp_fv1_3 = 1.0f / temp_fv0_3;
        spAC = temp_fv0_3 * 0.5f;
        temp_ft3_2 = *(f32 *)((u8 *)arg0 + 0x138);
        sp68 = temp_ft3_2;
        temp_fs1_2 = spD0 * temp_fv1_3;
        temp_fs2 = temp_ft5_2 * temp_fv1_3;
        temp_ft1 = temp_ft0 * 0.25f;
        sp6C = temp_ft1;
        if (sp68 < sp6C) {
            return func_151B3A7C(arg0);
        }
        var_fs0 = 0.0f;
        var_s1 = 0;
        var_s2 = (void *)(arg0 + 0x48);
        sp98 = sqrtf(sp68 - sp6C);
        do {
            node = var_s2;
            temp_fs3_2 = func_15047D60(var_fs0);
            var_s1 += 0x18;
            temp_fv1_4 = spAC * func_15047C00(var_fs0);
            var_s2 += 0x18;
            temp_fa0_2 = sp98 * temp_fs3_2;
            temp_fa1_2 = (temp_fv1_4 * temp_fs1_2) - (temp_fa0_2 * temp_fs2);
            *(f32 *)((u8 *)node + 0) = (f32) ((temp_fa1_2 * temp_fs5_2) + sp100);
            *(f32 *)((u8 *)node + 4) = (f32) (((temp_fv1_4 * temp_fs2) - (temp_fa0_2 * temp_fs1_2)) + sp104);
            *(f32 *)((u8 *)node + 8) = (f32) ((temp_fa1_2 * temp_fs4_2) + sp108);
            var_fs0 += D_800AA3B4;
        } while (var_s1 != 0xF0);
        goto block_6;
    }
block_6:
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B3FDC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3FDC.s")
extern f32 D_800BE9A4;
extern s32 D_800DBFF4;
extern Vec3f D_800A5480;

s32 func_151B42A4(HoltenRopeEffect *arg0) {
    u8 result;

    result = 1;
    {
        Vec3f delta;

        delta.x = ((Vec3f *)arg0->secondaryState)->x - ((Vec3f *)arg0->primaryState)->x;
        delta.y = ((Vec3f *)arg0->secondaryState)->y - ((Vec3f *)arg0->primaryState)->y;
        delta.z = ((Vec3f *)arg0->secondaryState)->z - ((Vec3f *)arg0->primaryState)->z;
        if ((0.0001f < fabsf(delta.x)) || (0.0001f < fabsf(delta.z))) {
            Vec3f mid;
            Vec3f a;
            Vec3f b;
            f32 halfX;
            f32 halfY;
            f32 halfZ;
            f32 distance;
            f32 inv;
            f32 farSide;
            f32 nearSide;
            f32 nx;
            f32 nz;
            f32 px;
            f32 ux;
            f32 uy;
            f32 py;
            f32 lengthSquared;
            f32 r;
            f32 length;
            f32 invLength;
            f32 halfSquared;

            halfX = delta.x * 0.5f;
            halfY = delta.y * 0.5f;
            halfZ = delta.z * 0.5f;
            mid.x = ((Vec3f *)arg0->primaryState)->x + halfX;
            mid.y = ((Vec3f *)arg0->primaryState)->y + halfY;
            mid.z = ((Vec3f *)arg0->primaryState)->z + halfZ;
            a.x = ((Vec3f *)arg0->primaryState)->x - mid.x;
            a.y = ((Vec3f *)arg0->primaryState)->y - mid.y;
            a.z = ((Vec3f *)arg0->primaryState)->z - mid.z;
            b.x = ((Vec3f *)arg0->secondaryState)->x - mid.x;
            b.y = ((Vec3f *)arg0->secondaryState)->y - mid.y;
            b.z = ((Vec3f *)arg0->secondaryState)->z - mid.z;
            distance = sqrtf((delta.x * delta.x) + (delta.z * delta.z));
            inv = 1.0f / distance;
            nx = delta.z * inv;
            nz = delta.x * inv;
            farSide = (b.z * nx) + (b.x * nz);
            nearSide = (a.z * nx) + (a.x * nz);
            px = farSide - nearSide;
            py = b.y - a.y;
            lengthSquared = (px * px) + (py * py);
            length = sqrtf(lengthSquared);
            invLength = 1.0f / length;
            r = length * 0.5f;
            ux = px * invLength;
            uy = py * invLength;
            halfSquared = lengthSquared * 0.25f;
            if (arg0->doubledRadiusSquared < halfSquared) {
                result = func_151B3A7C((u8 *)arg0);
            } else {
                f32 angle;
                f32 h;
                f32 dampAngle;
                s32 i;
                HoltenRopePoint *point;
                f32 s;
                f32 c;
                f32 damp;
                f32 v;
                f32 t;
                f32 w;
                Vec3f prev;
                Vec3f pos;
                f32 lift;
                f32 offsetX;
                f32 offsetZ;

                h = sqrtf(arg0->doubledRadiusSquared - halfSquared);
                for (i = 0, angle = 0.0f, dampAngle = 0.0f; i < 10; i++) {
                    point = &arg0->points[i];
                    prev = *(Vec3f *)point;
                    s = func_15047D60(angle);
                    c = func_15047C00(angle);
                    damp = func_15047D60(dampAngle);
                    v = r * c;
                    t = h * s;
                    w = (v * ux) - (t * uy);
                    offsetX = w * nz;
                    lift = (v * uy) - (t * ux);
                    offsetZ = w * nx;
                    pos.x = offsetX + mid.x;
                    pos.y = lift + mid.y;
                    pos.z = offsetZ + mid.z;
                    if (arg0->flags & 2) {
                        *(Vec3f *)point = pos;
                        point->velocity.x = 0.0f;
                        point->velocity.y = 0.0f;
                        point->velocity.z = 0.0f;
                    } else if (D_800DBFF4 != 0) {
                        *(Vec3f *)point = pos;
                        point->velocity = D_800A5480;
                    } else {
                        f32 diffX;
                        f32 diffY;
                        f32 diffZ;
                        f32 dx;
                        f32 dy;
                        f32 dz;
                        f32 ax;
                        f32 ay;
                        f32 az;

                        diffX = prev.x - pos.x;
                        dx = diffX * damp;
                        dx *= arg0->stiffness;
                        diffY = prev.y - pos.y;
                        dy = diffY * damp;
                        dy *= arg0->stiffness;
                        diffZ = prev.z - pos.z;
                        dz = diffZ * damp;
                        dz *= arg0->stiffness;
                        point->x = pos.x + dx;
                        point->y = pos.y + dy;
                        point->z = pos.z + dz;
                        ax = arg0->gain * dx;
                        ay = arg0->gain * dy;
                        az = arg0->gain * dz;
                        point->x += (point->velocity.x * D_800BE9A4) + (0.5f * ax * D_800BE9A4 * D_800BE9A4);
                        point->y += (point->velocity.y * D_800BE9A4) + (0.5f * ay * D_800BE9A4 * D_800BE9A4);
                        point->z += (point->velocity.z * D_800BE9A4) + (0.5f * az * D_800BE9A4 * D_800BE9A4);
                        point->velocity.x += ax * D_800BE9A4;
                        point->velocity.y += ay * D_800BE9A4;
                        point->velocity.z += az * D_800BE9A4;
                    }
                    angle += 0.34906587f;
                    dampAngle += 0.34906587f;
                }
            }
        }
    }
    arg0->flags &= ~2;
    return result;
}
typedef struct {
    s32 active;
    u8 pad4[0x37];
    u8 index;
    u8 pad3C[0x198];
    s32 transform;
} HoltenRopeResource;

typedef struct {
    HoltenRopeResource *primary;
    u8 primaryIndex;
    u8 primaryOffset;
    u8 pad6[2];
    f32 primaryVector[3];
    HoltenRopeResource *secondary;
    u8 secondaryIndex;
    u8 secondaryOffset;
    u8 pad1A[2];
    f32 secondaryVector[3];
} HoltenRopePair;

void func_15143134(f32 *, f32 *, s32);

s32 func_151B47D8(HoltenRopeEffect *arg0, HoltenRopePair *arg1, f32 *arg2, u8 arg3) {
    f32 *input;
    HoltenRopeResource *primary;
    HoltenRopeResource *secondary;

    primary = arg1->primary;
    secondary = arg1->secondary;
    if (primary->transform == 0 || secondary->transform == 0) {
        arg0->flags |= 0xC;
        return 1;
    }
    if (primary->active == 0 || primary->index != arg1->primaryIndex ||
        secondary->active == 0 || secondary->index != arg1->secondaryIndex) {
        return 0;
    }
    arg0->flags &= ~(arg3 ? 4 : 8);
    if (arg3 != 0) {
        input = arg1->primaryVector;
    } else {
        input = arg1->secondaryVector;
    }
    func_15143134(input, arg2,
                  arg3 ? primary->transform + (arg1->primaryOffset << 6)
                       : secondary->transform + (arg1->secondaryOffset << 6));
    return 1;
}

s32 func_151B48DC(HoltenRopeEffect *arg0) {
    f32 start;
    f32 end;
    f32 step;
    f32 x;
    s32 i;

    start = *(f32 *)arg0->primaryState;
    end = *(f32 *)arg0->secondaryState;
    step = -(start - end) * 0.1f;
    x = start;
    for (i = 0; i < 10; i++, x += step) {
        HoltenRopePoint *point = &arg0->points[i];

        point->x = x;
        point->y = 0.0f;
        point->z = 0.0f;
    }
    arg0->flags &= ~2;
    return 1;
}
s32 func_151B498C(s32 arg0, u32 *arg1, u32 *arg2, u32 *arg3, u32 *arg4, u32 *arg5, u32 *arg6, u32 *arg7, u32 *arg8, u32 *arg9, u32 *arg10, u32 *arg11, s8 *arg12, s8 *arg13) {
    *arg1 = 0x220005;
    *arg2 = 0x40600;
    *arg3 = 0xFF;
    *arg4 = 0xFF;
    *arg5 = 0xFF;
    *arg6 = 0xFF;
    *arg7 = 0xFF;
    *arg8 = 0xFF;
    *arg9 = 0xFF;
    *arg10 = 0xFF;
    *arg11 = 0;
    *arg12 = 5;
    *arg13 = 0x2B;
    return 1;
}
void func_1502EC34(u8 *, s32 *, s32 *, s32 *, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B4A14 */
u8 func_151B4A14(void *arg0, u32 *arg1, u32 *arg2, u32 *arg3,
                 u32 *arg4, u32 *arg5, u32 *arg6, u32 *arg7,
                 u32 *arg8, u32 *arg9, u32 *arg10, u32 *arg11,
                 s8 *arg12, s8 *arg13) {
    u8 result;
    HoltenRopeEffect *effect = (HoltenRopeEffect *)arg0;
    u8 *base;
    u8 *data;
    s32 value0;
    s32 value1;
    s32 value2;
    s32 value3;

    base = (u8 *)effect + 0x150;
    data = *(u8 **)base;
    result = 1;
    func_1502EC34(data, &value0, &value1, &value2, &value3);
    if (data[0xA4] & 1) {
        *arg1 = 0x200005;
        *arg2 = 0x60600;
        *arg3 = value0;
        *arg4 = value1;
        *arg5 = value2;
        *arg6 = 0xFF;
        *arg7 = *arg8 = *arg9 = value3;
        *arg10 = 0xFF;
        *arg11 = 0x100000;
        *arg12 = 5;
        *arg13 = 0x2F;
    } else {
        result = func_151B498C((s32)effect, arg1, arg2, arg3, arg4,
                              arg5, arg6, arg7, arg8, arg9, arg10,
                              arg11, arg12, arg13);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B4A14 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B4A14.s")

s32 func_151B4B78(HoltenRopeEffect *arg0) {
    f32 x;
    s32 i;

    x = -1000.0f;
    for (i = 0; i < 10; i++, x += 222.22223f) {
        HoltenRopePoint *point = &arg0->points[i];

        point->x = x;
        point->y = 0.0f;
        point->z = 0.0f;
    }
    arg0->flags &= ~2;
    return 1;
}
typedef struct {
    u8 pad_0[0x44];
    u8 field_44;
} HoltenRopeState;

void func_151D5E30(void *, void *);
extern void (*D_8008FB70[])(void *);

void func_151B4C1C(u8 *arg0) {
    void (*temp_v0)(void *);

    func_151D5E30(arg0 + 0x140, arg0);
    temp_v0 = D_8008FB70[((HoltenRopeState *)arg0)->field_44];
    if (temp_v0 != 0) {
        temp_v0(arg0);
    }
}
void func_151B4C1C(u8 *arg0);

void func_151B4C6C(void *arg0) {
    func_151B4C1C(arg0);
    func_15169824(arg0);
}
void func_151B4C98(void *arg0) {
    func_151B4C1C(arg0);
    func_15169824(arg0);
}
