#include "types.h"
#include "game_vec.h"

/*
 * Reviewed source unit: src/game/game_AE1D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15080D20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameAE1D0Actor {
    u8 pad0[4];
    u8 model;
    u8 pad5[0xF];
    f32 x, y, z;
    u8 pad20[0x20];
    f32 yaw;
    u8 pad44[0x58];
    s32 unk_9C;
    u8 unk_A0[0x18];
    f32 pitch;
    u8 padBC[0x69];
    u8 suppressEffect;
    u8 pad126[0x26];
    f32 scale;
    f32 heightScale;
    u8 pad154[0x80];
    s32 transform;
} GameAE1D0Actor;

typedef struct GameAE1D0Bounds {
    u8 pad0[0xE];
    u16 radius;
    s16 height;
} GameAE1D0Bounds;

typedef struct GameAE1D0Sphere {
    u8 joint;
    u8 unk_01;
    u16 radius;
    s16 x, y, z;
} GameAE1D0Sphere;

f32 func_15047C00(f32);
f32 func_15047D60(f32);
void func_15143134(f32 *, f32 *, s32);
void func_1505D1C4(f32, f32, f32, s32, s32, u16, s32, s32);
extern GameAE1D0Sphere *D_80086C60[];
extern u8 D_8009CBCC[];
extern f32 D_8009CBD8;
extern f32 D_8009CBDC;
extern GameAE1D0Bounds *D_800D1C90[];
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15080D20 CURRENT (2025) */
s32 func_15080D20(s32 arg0, void *arg1, s32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 angle;
    f32 sine;
    f32 cosine;
    f32 radius;
    f32 sourceScale;
    f32 savedX;
    f32 position[3];
    GameAE1D0Actor *source;
    GameAE1D0Actor *target;
    GameAE1D0Bounds *bounds;
    s32 index;
    f32 local[3];
    f32 world[3];
    s32 count;
    s32 transform;
    GameAE1D0Sphere *sphere;
    u32 modelIndex;
    f32 convertedRadius;

    source = (GameAE1D0Actor *)arg0;
    target = arg1;
    sourceScale = source->scale;
    arg3 *= sourceScale;
    arg4 *= sourceScale;
    angle = source->pitch * D_8009CBD8;
    sine = func_15047D60(angle);
    cosine = func_15047C00(angle);
    position[0] = 0.0f;
    position[1] = -arg3 * sine;
    position[2] = arg3 * cosine;
    angle = source->yaw * D_8009CBDC;
    sine = func_15047D60(angle);
    cosine = func_15047C00(angle);
    savedX = position[0];
    position[0] = position[2] * sine + savedX * cosine;
    position[2] = position[2] * cosine + -savedX * sine;
    position[0] += source->x;
    position[1] += source->y;
    position[2] += source->z;
    index = 0;
    modelIndex = target->model;
    bounds = D_800D1C90[modelIndex];
    convertedRadius = (f32)(u32)bounds->radius;
    angle = convertedRadius * target->scale;
    dx = position[0] - target->x;
    dy = position[1] - (target->y + (f32)bounds->height * target->heightScale);
    dz = position[2] - target->z;
    if (angle * angle < dx * dx + dy * dy + dz * dz) {
        return 0;
    }
    count = D_8009CBCC[arg2];
    sphere = D_80086C60[arg2];
    transform = target->transform;
    if (count > 0) {
        arg2 = (s32)sphere;
        do {
            local[0] = ((GameAE1D0Sphere *)arg2)->x;
            local[1] = ((GameAE1D0Sphere *)arg2)->y;
            local[2] = ((GameAE1D0Sphere *)arg2)->z;
            func_15143134(local, world, transform + (((GameAE1D0Sphere *)arg2)->joint << 6));
            dx = position[0] - world[0];
            dy = position[1] - world[1];
            dz = position[2] - world[2];
            index++;
            convertedRadius = (f32)(u32)((GameAE1D0Sphere *)arg2)->radius;
            radius = convertedRadius * target->scale + arg4;
            if (!(radius * radius < dx * dx + dy * dy + dz * dz)) {
                if (target->suppressEffect == 0) {
                    func_1505D1C4(target->x, target->y, target->z, arg5,
                        (arg0 - (s32)&D_800CC2D0) / 0x32C, 0, 0, 0);
                }
                return ((GameAE1D0Sphere *)arg2)->joint + 1;
            }
            arg2 += sizeof(GameAE1D0Sphere);
        } while (index != count);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15080D20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_15080D20.s")
typedef struct GameAE1D0ModelEntry {
    u16 model;
    u8 sphereSet;
    u8 unk_03;
} GameAE1D0ModelEntry;

extern GameAE1D0ModelEntry D_8009BD30[];

s32 func_1508108C(void *arg0) {
    s32 index;

    for (index = 0; index < 0x17; index++) {
        if (*(u8 *)((u8 *)arg0 + 4) == D_8009BD30[index].model) {
            return index;
        }
    }
    return -1;
}
s32 func_151452C4(void *, void *, Vec3f *, f32, Vec3f *, Vec3f *, f32 *, f32 *);

s32 func_1508114C(GameAE1D0Actor *arg0, void *arg1, void *arg2, Vec3f *arg3, Vec3f *arg4,
                  Vec3f *arg5, f32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9,
                  s16 *arg10) {
    s32 index;
    GameAE1D0Sphere *spheres;
    s32 count;
    s32 i;
    s32 best;
    f32 t;
    f32 t2;
    s32 priority;
    Vec3f pos;
    Vec3f bestPos;
    Vec3f hit;
    Vec3f normal;
    f32 local[3];
    Vec3f bestHit;
    Vec3f bestNormal;
    f32 radius;
    f32 (*transform)[4][4];

    if (arg0->transform == 0) {
        return -1;
    }
    index = func_1508108C(arg0);
    if (index == -1) {
        return -1;
    }
    spheres = D_80086C60[D_8009BD30[index].sphereSet];
    count = D_8009CBCC[D_8009BD30[index].sphereSet];
    *arg6 = -1.0f;
    pos.x = arg0->x;
    pos.y = D_800D1C90[arg0->model]->height * arg0->heightScale + arg0->y;
    pos.z = arg0->z;
    radius = D_800D1C90[arg0->model]->radius * arg0->heightScale;
    if (func_151452C4(arg1, arg2, &pos, radius, &hit, &normal, &t, &t2) == 0) {
        return 0;
    }
    priority = -1;
    for (i = 0; i < count; i++) {
        if (arg0->unk_9C & (1 << spheres[i].joint)) {
            continue;
        }
        transform = (f32 (*)[4][4])arg0->transform;
        local[0] = spheres[i].x;
        local[1] = spheres[i].y;
        local[2] = spheres[i].z;
        func_15143134(local, &pos.x, (s32)transform[spheres[i].joint]);
        if (func_151452C4(arg1, arg2, &pos, spheres[i].radius * arg0->scale, &hit, &normal, &t, &t2) == 0) {
            continue;
        }
        if (*arg6 == -1.0f || (t < *arg6 && spheres[i].unk_01 >= priority)) {
            *arg6 = t;
            bestHit = hit;
            bestNormal = normal;
            bestPos = pos;
            best = i;
            priority = spheres[i].unk_01;
        }
    }
    if (*arg6 == -1.0f) {
        return 0;
    }
    *arg6 = t;
    *arg7 = best;
    *arg9 = spheres[best].unk_01;
    *arg8 = spheres[best].joint;
    arg10[0] = spheres[best].x;
    arg10[1] = spheres[best].y;
    arg10[2] = spheres[best].z;
    *arg3 = bestHit;
    *arg4 = bestNormal;
    if (arg5 != NULL) {
        *arg5 = bestPos;
    }
    return 1;
}
s32 func_15080D20(s32, void *, s32, f32, f32, s32);
s32 func_1508108C(void *);
extern u8 D_800CC2D0;

s32 func_15081574(s32 arg0, f32 arg1, f32 arg2, void **arg3, s32 arg4, s32 arg5) {
    u8 *var_s0;
    s32 i;
    s32 temp_v0;
    s32 temp_v0_2;

    *arg3 = 0;
    for (i = 0; i < 25; i++) {
        var_s0 = &D_800CC2D0 + i * 0x32C;
        if ((*(s32 *)(var_s0 + 0) == 0) || (*(s32 *)(var_s0 + 0x1D4) == 0) || (arg5 != var_s0[4])) continue;
        temp_v0_2 = func_1508108C(var_s0);
        if (temp_v0_2 != -1) {
            temp_v0 = func_15080D20(arg0, var_s0, D_8009BD30[temp_v0_2].sphereSet, arg1, arg2, arg4);
            if (temp_v0 != 0) {
                *arg3 = var_s0;
                return temp_v0;
            }
        }
    }
    return 0;
}
