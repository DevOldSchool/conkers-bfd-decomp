#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1136E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E6230
 * - func_150E63A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1136E0MotionState {
    u8 flags;
    u8 pad1[3];
    f32 target[3];
    u8 pad10[0x18];
    f32 previousSign;
    s8 callback;
} Game1136E0MotionState;

typedef struct Game1136E0MotionActor {
    u8 pad0[0x34];
    f32 position[3];
    f32 velocity[3];
    u8 pad4C[4];
    f32 factor;
    u8 pad54[0xBC];
    Game1136E0MotionState state;
} Game1136E0MotionActor;

f32 func_15144A74(void *, void *);
extern s32 (*D_80088A10[])(void *);
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E6230 CURRENT (2478) */
s8 func_150E6230(Game1136E0MotionActor *arg0) {
    f32 delta[3];
    f32 sign;
    s8 result;
    Game1136E0MotionState *state;

    result = 1;
    state = &arg0->state;
    if (state->flags & 1) {
        delta[0] = state->target[0] - arg0->position[0];
        delta[1] = state->target[1] - arg0->position[1];
        delta[2] = state->target[2] - arg0->position[2];
        if (func_15144A74(delta, state->target) < 0.0f) {
            sign = -1.0f;
        } else {
            sign = 1.0f;
        }
        if (sign != state->previousSign) {
            result = 0;
            if (state->callback != -1) {
                result = (s8)D_80088A10[state->callback](arg0);
            }
        }
    }
    arg0->position[0] += arg0->velocity[0] * arg0->factor * D_800BE9A4;
    arg0->position[1] += arg0->velocity[1] * arg0->factor * D_800BE9A4;
    arg0->position[2] += arg0->velocity[2] * arg0->factor * D_800BE9A4;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E6230 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1136E0/func_150E6230.s")
typedef struct Game1136E0StripVertex {
    s16 x, y, z, flag;
    u8 pad8[7];
    u8 alpha;
} Game1136E0StripVertex;

typedef struct Game1136E0Strip {
    u8 pad0[0x2C];
    f32 width;
    f32 length;
    Vec3f position;
    Vec3f direction;
    u8 pad4C[0x10];
    u8 alpha;
    u8 pad5D[0x63];
    u8 vertexTemplate[0x40];
    u8 *buffers[1];
} Game1136E0Strip;

typedef struct Game1136E0Camera {
    u8 pad0[0x2F8];
    Vec3f position;
    u8 pad304[0x69C];
} Game1136E0Camera;

void *func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern Game1136E0Camera *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E63A0 CURRENT (9860) */
void *func_150E63A0(Game1136E0Strip *arg0, s16 arg1) {
    Vec3f start;
    Vec3f end;
    f32 dx, dy, dz;
    f32 mx, my, mz;
    f32 nx, ny, nz;
    f32 ox, oy, oz;
    f32 lengthSquared;
    f32 scale;
    Vec3f *eye;
    Game1136E0StripVertex *vertices;
    void *result;
    u8 fresh;

    func_151D5D60(arg0->buffers, arg1, 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != NULL) {
        if (fresh != 0) {
            func_10022EC0(arg0->buffers[arg1], arg0->vertexTemplate, 0x40);
            func_10022EC0(arg0->buffers[arg1] + 0x40, arg0->vertexTemplate, 0x40);
        }
    } else {
        return NULL;
    }
    eye = &D_800DBFF0[arg1].position;
    start = arg0->position;
    end.x = arg0->position.x - arg0->direction.x * arg0->length;
    end.y = arg0->position.y - arg0->direction.y * arg0->length;
    end.z = arg0->position.z - arg0->direction.z * arg0->length;
    dx = end.x - start.x;
    mx = dx * 0.5f + start.x - eye->x;
    dy = end.y - start.y;
    my = dy * 0.5f + start.y - eye->y;
    dz = end.z - start.z;
    mz = dz * 0.5f + start.z - eye->z;
    nx = dy * mz - my * dz;
    ny = dz * mx - mz * dx;
    nz = dx * my - mx * dy;
    lengthSquared = nx * nx + ny * ny + nz * nz;
    if (lengthSquared == 0.0f) {
        oz = 0.0f;
        ox = 0.0f;
        oy = 0.0f;
    } else {
        scale = arg0->width / sqrtf(lengthSquared);
        ox = nx * scale;
        oy = ny * scale;
        oz = nz * scale;
    }
    vertices->x = start.x - ox;
    vertices->y = start.y - oy;
    vertices->z = start.z - oz;
    vertices->alpha = arg0->alpha;
    vertices->flag = 0;
    vertices++;
    vertices->x = end.x - ox;
    vertices->y = end.y - oy;
    vertices->z = end.z - oz;
    vertices->alpha = 0;
    vertices->flag = 0;
    vertices++;
    vertices->x = end.x + ox;
    vertices->y = end.y + oy;
    vertices->z = end.z + oz;
    vertices->alpha = 0;
    vertices->flag = 0;
    vertices++;
    vertices->x = start.x + ox;
    vertices->y = start.y + oy;
    vertices->z = start.z + oz;
    vertices->alpha = arg0->alpha;
    vertices->flag = 0;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E63A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1136E0/func_150E63A0.s")
s32 func_150E679C(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 8) {
        temp_v1 = temp_v0 << 5;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    return 1;
}
void *func_1513C73C(s32, u8, u8, s32, f32, f32, f32, f32, f32, u8, u8, s32, u8, s32);

typedef struct Game1136E0Descriptor {
    s32 field_0;
    s16 field_4;
    s8 field_6;
    u8 pad7;
    s32 field_8;
    s32 field_C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 field_14;
    u8 field_15;
    u8 pad16[2];
    s32 field_18;
    u8 pad1C[0x14];
} Game1136E0Descriptor;

s32 func_150E67D0(u8 *arg0) {
    Game1136E0Descriptor descriptor;
    u8 *temp_v1;

    descriptor.field_6 = 0x3A;
    descriptor.field_0 = 1;
    descriptor.field_4 = 0x64;
    descriptor.field_8 = 0;
    descriptor.field_C = 0;
    descriptor.field_10 = 0xFF;
    descriptor.field_11 = 0xFF;
    descriptor.field_12 = 0;
    descriptor.field_13 = 0;
    descriptor.field_14 = 0;
    descriptor.field_15 = 0xFF;
    descriptor.field_18 = 0x130001;
    temp_v1 = arg0 + 0x110;
    func_1513C73C((s32 *)&descriptor, 0, 0, temp_v1 + 0x14,
                  *(f32 *)(temp_v1 + 4), *(f32 *)(temp_v1 + 8),
                  *(f32 *)(temp_v1 + 0xC), 50.0f, 50.0f,
                  func_150ADA20() & 0xFF, 0, 0, arg0[0xC], arg0[1]);
    return 0;
}
