#include "types.h"
#include "game_vec.h"

/*
 * Reviewed source unit: src/game/game_1BBFC0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518EF54
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1BBFC0Vertex {
    s16 x, y, z, flag;
    u8 other[8];
} Game1BBFC0Vertex;

typedef struct Game1BBFC0Beam {
    u8 unknown0[0x2C];
    f32 width;
    f32 progress;
    Vec3f start;
    Vec3f end;
    u8 unknown4C[0x74];
    u8 vertexTemplate[0x40];
    u8 *buffers[1];
} Game1BBFC0Beam;

typedef struct Game1BBFC0Camera {
    u8 unknown0[0x2F8];
    Vec3f position;
    u8 unknown304[0x69C];
} Game1BBFC0Camera;

void *func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern Game1BBFC0Camera *D_800DBFF0;

void *func_1518EB10(Game1BBFC0Beam *arg0, s16 arg1) {
    Game1BBFC0Vertex *vertices;
    void *result;
    f32 progress;
    Vec3f tip;
    f32 dx, dy, dz;
    f32 vx, vy, vz;
    f32 nx, ny, nz;
    f32 lengthSquared;
    u8 fresh;
    Vec3f *eye;
    f32 scale;

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
    progress = arg0->progress;
    dx = arg0->end.x - arg0->start.x;
    dy = arg0->end.y - arg0->start.y;
    dz = arg0->end.z - arg0->start.z;
    tip.x = arg0->start.x + dx * progress;
    tip.y = arg0->start.y + dy * progress;
    tip.z = arg0->start.z + dz * progress;
    eye = &D_800DBFF0[arg1].position;
    dx = tip.x - arg0->start.x;
    dy = tip.y - arg0->start.y;
    dz = tip.z - arg0->start.z;
    vx = arg0->start.x - eye->x;
    vy = arg0->start.y - eye->y;
    vz = arg0->start.z - eye->z;
    nx = dy * vz - vy * dz;
    ny = dz * vx - vz * dx;
    nz = dx * vy - vx * dy;
    lengthSquared = nx * nx + ny * ny + nz * nz;
    if (lengthSquared == 0.0f) {
        nx = 0.0f;
        ny = 0.0f;
        nz = 0.0f;
    } else {
        scale = arg0->width / sqrtf(lengthSquared);
        nx *= scale;
        ny *= scale;
        nz *= scale;
    }
    vertices->x = arg0->start.x + nx;
    vertices->y = arg0->start.y + ny;
    vertices->z = arg0->start.z + nz;
    vertices->flag = 0;
    vertices++;
    vertices->x = arg0->start.x - nx;
    vertices->y = arg0->start.y - ny;
    vertices->z = arg0->start.z - nz;
    vertices->flag = 0;
    vertices++;
    dx = -dx;
    dy = -dy;
    dz = -dz;
    vx = tip.x - eye->x;
    vy = tip.y - eye->y;
    vz = tip.z - eye->z;
    nx = dy * vz - vy * dz;
    ny = dz * vx - vz * dx;
    nz = dx * vy - vx * dy;
    lengthSquared = nx * nx + ny * ny + nz * nz;
    if (lengthSquared == 0.0f) {
        nx = 0.0f;
        ny = 0.0f;
        nz = 0.0f;
    } else {
        scale = arg0->width / sqrtf(lengthSquared);
        nx *= scale;
        ny *= scale;
        nz *= scale;
    }
    vertices->x = tip.x + nx;
    vertices->y = tip.y + ny;
    vertices->z = tip.z + nz;
    vertices->flag = 0;
    vertices++;
    vertices->x = tip.x - nx;
    vertices->y = tip.y - ny;
    vertices->z = tip.z - nz;
    vertices->flag = 0;
    return result;
}
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518EF54 CURRENT (20) */
s32 func_1518EF54(u8 *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 *temp_v1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x150);
    temp_v1 = (void *)(arg0 + 0x110);
    *(f32 *)((u8 *)arg0 + 0x140) = (f32) (*(f32 *)((u8 *)arg0 + 0x140) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x144) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14C) * D_800BE9A4) + *(f32 *)((u8 *)arg0 + 0x144));
    *(f32 *)((u8 *)arg0 + 0x148) = (f32) (*(f32 *)((u8 *)arg0 + 0x148) * temp_fv0);
    temp_fv1 = D_800BE9A4;
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x140) * temp_fv1;
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x144) * temp_fv1;
    temp_ft4 = *(f32 *)((u8 *)arg0 + 0x148) * temp_fv1;
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + temp_fa1);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + temp_ft4);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + temp_fa1);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) + temp_ft4);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x38);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x3C);
    *(f32 *)(arg0 + 0x40) = (*(f32 *)(arg0 + 0x40) - *(f32 *)(arg0 + 0x34)) * *(f32 *)(arg0 + 0x15C) + *(f32 *)(arg0 + 0x34);
    *(f32 *)(arg0 + 0x44) = temp_fv0 + *(f32 *)(temp_v1 + 0x4C) * (*(f32 *)(arg0 + 0x44) - temp_fv0);
    *(f32 *)(arg0 + 0x48) = temp_fv1 + *(f32 *)(temp_v1 + 0x4C) * (*(f32 *)(arg0 + 0x48) - temp_fv1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518EF54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BBFC0/func_1518EF54.s")
extern f32 D_800BE9A4;

s32 func_1518F058(void *arg0) {
    u8 *base = arg0;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;

    temp_fv0 = *(f32 *)(base + 0x150);
    *(f32 *)(base + 0x140) = (f32) (*(f32 *)(base + 0x140) * temp_fv0);
    *(f32 *)(base + 0x144) = (f32) ((*(f32 *)(base + 0x14C) * D_800BE9A4) + *(f32 *)(base + 0x144));
    *(f32 *)(base + 0x148) = (f32) (*(f32 *)(base + 0x148) * temp_fv0);
    temp_fa0 = *(f32 *)(base + 0x140) * D_800BE9A4;
    temp_fa1 = *(f32 *)(base + 0x144) * D_800BE9A4;
    temp_ft4 = *(f32 *)(base + 0x148) * D_800BE9A4;
    *(f32 *)(base + 0x34) = (f32) (*(f32 *)(base + 0x34) + temp_fa0);
    *(f32 *)(base + 0x38) = (f32) (*(f32 *)(base + 0x38) + temp_fa1);
    *(f32 *)(base + 0x3C) = (f32) (*(f32 *)(base + 0x3C) + temp_ft4);
    *(f32 *)(base + 0x40) = (f32) (*(f32 *)(base + 0x40) + temp_fa0);
    *(f32 *)(base + 0x44) = (f32) (*(f32 *)(base + 0x44) + temp_fa1);
    *(f32 *)(base + 0x48) = (f32) (*(f32 *)(base + 0x48) + temp_ft4);
    return 1;
}
s32 func_1518F108(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x154);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    if (*(s16 *)((u8 *)arg0 + 0x1C) < *(s16 *)((u8 *)arg0 + 0x158)) {
        *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (*(s16 *)((u8 *)arg0 + 0x15A) * *(s16 *)((u8 *)arg0 + 0x1C));
    }
    return 1;
}
s32 func_1518F15C(void *arg0) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 - *(f32 *)((u8 *)arg0 + 0x154) * *(f32 *)((u8 *)arg0 + 0x30));
    if (*(s16 *)(0x1C + (u8 *)arg0) < *(s16 *)((u8 *)arg0 + (short) 0x158)) {
        *(s8 *)(0x5C + (u8 *)arg0) = (s8) (*(s16 *)((u8 *)arg0 + 0x15A) * *(s16 *)(0x1C + (u8 *)arg0));
    }
    return 1;
}
