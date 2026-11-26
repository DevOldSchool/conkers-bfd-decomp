#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_130240.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 */

void func_15145EA4(s32 *, s32 *, s32, s32);
void *func_1503195C(void *, s32, s32);
s32 func_1514654C(void *, s32, s32, void **, void **, s32);

s32 func_15102D90(void *arg0) {
    u8 *owner;
    u8 *link;
    void *sources[2];
    void *targets[2];
    s16 index;

    link = (u8 *)arg0 + 0x110;
    owner = *(u8 **)link;
    link[0x14] &= 0xFFFE;
    if ((link[4] != owner[0x3B]) || (*(s32 *)owner == 0)) {
        return 0;
    }
    if ((*(s32 *)(owner + 0x1D4) == 0) || ((owner[0x74] & 0xF) == 0xF)) {
        return 1;
    }
    sources[0] = (u8 *)arg0 + 0x34;
    sources[1] = (u8 *)arg0 + 0x40;
    targets[0] = link + 0x18;
    targets[1] = link + 0x24;
    index = *(s16 *)(link + 0xC);
    if (index != -1) {
        void *node = func_1503195C(owner, index, 0);

        if (node == 0) {
            return 0;
        }
        if (func_1514654C(owner, (s32)node, *(s32 *)(link + 0x10),
                          sources, targets, 2) == 0) {
            return 0;
        }
    } else {
        func_15145EA4((s32 *)sources, (s32 *)targets,
                      *(s32 *)(link + 8) + *(s32 *)(owner + 0x1D4), 2);
    }
    link[0x14] |= 1;
    return 1;
}

typedef struct Game130240Vertex {
    s16 x, y, z, flags;
    u8 attributes[8];
} Game130240Vertex;

typedef struct Game130240Ribbon {
    u8 unk_0[0x14];
    u8 flags;
    u8 unk_15[3];
    Vec3f start, end;
} Game130240Ribbon;

typedef struct Game130240Trail {
    u8 unk_0[0x2C];
    f32 halfWidth;
    f32 fraction;
    u8 unk_34[0xC0 - 0x34];
    Game130240Vertex vertexTemplate[4];
    Game130240Vertex *vertices[4];
    Game130240Ribbon ribbon;
} Game130240Trail;

void *func_10022EC0(void *, const void *, u32);
s32 func_15144B34(s32);
void func_15145548(void *, void *, void *, void *, f32 *);
void func_151D5D60(void *, s16, s32, void **, u8 *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

void *func_15102EB8(Game130240Trail *trail, s16 arg1) {
    Vec3f *camera;
    Vec3f endpoint;
    Vec3f delta;
    f32 scale;
    Vec3f point;
    f32 nx, ny, nz;
    f32 dx, dy, dz;
    Game130240Vertex *vertices;
    void *result;
    f32 parameter;
    f32 lengthSquared;
    u8 fresh;
    Game130240Ribbon *ribbon;

    camera = (Vec3f *)func_15144B34(arg1);
    if (!(trail->ribbon.flags & 1)) {
        return NULL;
    }
    func_151D5D60(trail->vertices, arg1, 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != NULL) {
        if (fresh != 0) {
            func_10022EC0(trail->vertices[arg1], trail->vertexTemplate, 0x40);
            func_10022EC0(trail->vertices[arg1] + 4, trail->vertexTemplate, 0x40);
        }
        ribbon = &trail->ribbon;
    } else {
        return NULL;
    }
    endpoint.x = ribbon->start.x + (ribbon->end.x - ribbon->start.x) * trail->fraction;
    endpoint.y = ribbon->start.y + (ribbon->end.y - ribbon->start.y) * trail->fraction;
    endpoint.z = ribbon->start.z + (ribbon->end.z - ribbon->start.z) * trail->fraction;
    delta.x = endpoint.x - ribbon->start.x;
    delta.y = endpoint.y - ribbon->start.y;
    delta.z = endpoint.z - ribbon->start.z;
    func_15145548(&ribbon->start, &delta, camera, &point, &parameter);
    dx = point.x - camera->x;
    dy = point.y - camera->y;
    dz = point.z - camera->z;
    nx = delta.y * dz - dy * delta.z;
    ny = delta.z * dx - dz * delta.x;
    nz = delta.x * dy - dx * delta.y;
    lengthSquared = nx * nx + ny * ny + nz * nz;
    if (lengthSquared == 0.0f) {
        nz = ny = nx = 0.0f;
    } else {
        scale = trail->halfWidth / sqrtf(lengthSquared);
        nx *= scale;
        ny *= scale;
        nz *= scale;
    }
    vertices->x = (s32)(ribbon->start.x + nx);
    vertices->y = (s32)(ribbon->start.y + ny);
    vertices->z = (s32)(ribbon->start.z + nz);
    vertices->flags = 0;
    vertices++;
    vertices->x = (s32)(endpoint.x + nx);
    vertices->y = (s32)(endpoint.y + ny);
    vertices->z = (s32)(endpoint.z + nz);
    vertices->flags = 0;
    vertices++;
    vertices->x = (s32)(endpoint.x - nx);
    vertices->y = (s32)(endpoint.y - ny);
    vertices->z = (s32)(endpoint.z - nz);
    vertices->flags = 0;
    vertices++;
    vertices->x = (s32)(ribbon->start.x - nx);
    vertices->y = (s32)(ribbon->start.y - ny);
    vertices->z = (s32)(ribbon->start.z - nz);
    vertices->flags = 0;
    return result;
}


typedef struct Game130240Descriptor {
    s32 flags;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s32 fieldC;
    s32 field10;
    u8 color14[4];
    u8 color18[4];
    u8 alpha;
    u8 kind;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    Vec3f position;
    Vec3f velocity;
    Vec3f acceleration;
    f32 field54;
    s32 field58;
    s32 field5C;
    u8 field60;
    u8 field61;
    s8 field62;
    s8 field63;
    s8 field64;
    s8 field65;
    u8 field66;
    u8 pad67[9];
} Game130240Descriptor;

void *func_15130374(s32, u8, s32, u8, s32);
extern s32 D_80088BD0[];

void func_15103254(s32 arg0, s32 arg1, f32 arg2, Vec3f *arg3,
                   s32 arg4, s32 arg5, s32 arg6) {
    s32 index;
    Game130240Descriptor descriptor;
    s32 second;
    s32 first;

    index = func_150ADA20() & 3;
    descriptor.kind = D_80088BD0[index];
    descriptor.field8 = 0x2203;
    descriptor.flags = 0x200005;
    descriptor.field4 = 0x20000;
    descriptor.fieldA = (s16)arg0 + 1;
    descriptor.fieldC = 0;
    descriptor.field10 = 0;
    descriptor.color14[0] = 0xFF;
    descriptor.color14[1] = 0xFF;
    descriptor.color14[2] = 0xFF;
    descriptor.color14[3] = 0xFF;
    descriptor.color18[0] = 0xFF;
    descriptor.color18[1] = 0xFF;
    descriptor.color18[2] = 0xFF;
    descriptor.color18[3] = ((u8 *)&arg1)[3];
    descriptor.alpha = 0xFF;
    descriptor.field2C = arg2;
    descriptor.field28 = arg2;
    descriptor.position = *arg3;
    descriptor.field1E = 3;
    descriptor.field20 = 0x55;
    descriptor.field22 = 1;
    descriptor.velocity.x = 0.0f;
    descriptor.velocity.y = 0.0f;
    descriptor.velocity.z = 0.0f;
    descriptor.acceleration.x = 0.0f;
    descriptor.acceleration.y = 0.0f;
    descriptor.acceleration.z = 0.0f;
    descriptor.field54 = 0.0f;
    descriptor.field24 = 1.0f;
    first = (func_150ADA20() & 1) ? 0x40 : 0;
    if (func_150ADA20() & 1) {
        second = 0x80;
    } else {
        second = 0;
    }
    descriptor.field58 = second | 1 | first | 0x8000 | 0x4000 | 0x200 | 0x40000 | 0x800000;
    descriptor.field60 = 6;
    descriptor.field61 = 8;
    descriptor.field62 = -1;
    descriptor.field63 = -1;
    descriptor.field64 = -1;
    descriptor.field65 = 0;
    descriptor.field66 = ((u8 *)&arg4)[3];
    func_15130374((s32)&descriptor, 1, 0, ((u8 *)&arg5)[3], arg6);
}
