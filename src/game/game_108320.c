#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_108320.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 */

typedef struct Game108320BeamPacket {
    s8 kind;
    u8 pad1;
    s16 flags, life;
    u8 pad6[2];
    s32 field8, fieldC;
    u8 color[4];
    u8 pad14[8];
    Vec3f position;
    Vec3f direction;
    Vec3f scale;
    s32 mode;
    u8 field44, field45;
    u8 pad46[0x12];
} Game108320BeamPacket;

typedef struct Game108320BeamOwner {
    u8 pad0[0x1D4];
    s32 transform;
} Game108320BeamOwner;

typedef struct Game108320Vertex {
    s16 x, y, z, flag;
    u8 attributes[8];
} Game108320Vertex;

typedef struct Game108320BeamMotion {
    Vec3f delta;
    f32 field11C, field120, field124, field128;
    f32 field12C, field130, field134;
    u8 field138;
} Game108320BeamMotion;

typedef struct Game108320Geometry {
    u8 pad0[0x2C];
    f32 width, height, x, y, z, directionX;
    u8 pad44[4];
    f32 directionZ;
    u8 pad4C[0x10];
    u8 field5C;
    u8 pad5D[0x63];
    Game108320Vertex templateVertices[4];
    Game108320Vertex *buffers[4];
    Game108320BeamMotion motion;
} Game108320Geometry;

void func_15143134(f32 *, f32 *, s32);
void *func_1513D524(void *, u8, u8, u8, u8, u8, s32, u8, s32);
f32 sqrtf(f32);
f32 fabsf(f32);
#pragma intrinsic(sqrtf, fabsf)
extern f32 D_80088910[][3], D_8008891C[][3];
extern s32 D_80088928[];
extern f32 D_8008892C[];
extern s16 D_80088930[];
extern f32 D_80088934[], D_80088938[], D_8008893C[];
extern u8 D_80088940[];
extern f32 D_80088944[], D_80088948[];

void func_150DAE70(Game108320BeamOwner *arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 transform;
    Vec3f first;
    Vec3f second;
    Vec3f delta;
    Game108320BeamPacket packet;
    Game108320Geometry *result;
    f32 squared;
    f32 inverse;

    if (arg0 != NULL && arg0->transform != 0) {
        transform = arg0->transform + (D_80088928[arg1] << 6);
        func_15143134(D_80088910[arg1], &first.x, transform);
        func_15143134(D_8008891C[arg1], &second.x, transform);
        delta.x = D_8008892C[arg1] * (second.x - first.x);
        delta.y = D_8008892C[arg1] * (second.y - first.y);
        delta.z = D_8008892C[arg1] * (second.z - first.z);
        squared = delta.x * delta.x + delta.z * delta.z;
        if (!(fabsf(squared) < 0.0001f)) {
            packet.kind = 0x17;
            packet.fieldC = 0x243A;
            packet.field8 = 0;
            packet.mode = 0x401;
            packet.life = D_80088930[arg1];
            packet.field44 = 0xFF;
            packet.field45 = 0xFF;
            packet.color[2] = 0xC8, packet.color[1] = 0xC8, packet.color[0] = 0xC8;
            packet.color[3] = 0xC8;
            packet.flags = 0x401;
            packet.position = first;
            packet.scale.x = 1.0f;
            packet.scale.y = 1.0f;
            packet.scale.z = 1.0f;
            inverse = 1.0f / sqrtf(squared);
            packet.direction.x = delta.z * inverse;
            packet.direction.y = 0.0f;
            packet.direction.z = delta.x * inverse;
            result = func_1513D524(&packet, 9, 0, 0, 7, 0, 0x2C, arg2, arg3);
            if (result != NULL) {
                result->motion.delta = delta;
                result->motion.field11C = D_80088934[arg1];
                result->motion.field120 = D_80088938[arg1];
                result->motion.field12C = D_80088944[arg1];
                result->motion.field130 = D_80088948[arg1];
                result->motion.field124 = 1.0f;
                result->motion.field128 = 1.0f;
                result->motion.field134 = D_8008893C[arg1];
                result->motion.field138 = D_80088940[arg1];
            }
        }
    }
}
extern f32 D_800BE9A4;

s32 func_150DB114(Game108320Geometry *arg0) {
    Game108320BeamMotion *motion = &arg0->motion;
    s16 remaining = arg0->field5C;

    motion->delta.x *= motion->field134;
    motion->delta.y *= motion->field134;
    motion->delta.z *= motion->field134;
    arg0->x += motion->delta.x * D_800BE9A4;
    arg0->y += motion->delta.y * D_800BE9A4;
    arg0->z += motion->delta.z * D_800BE9A4;
    motion->field124 += motion->field12C * D_800BE9A4;
    if (motion->field124 > 1.2f) {
        motion->field124 = 1.2f;
        motion->field12C = -motion->field12C;
    } else if (motion->field124 < 0.8f) {
        motion->field124 = 0.8f;
        motion->field12C = -motion->field12C;
    }
    motion->field128 += motion->field130 * D_800BE9A4;
    if (motion->field128 > 1.2f) {
        motion->field128 = 1.2f;
        motion->field130 = -motion->field130;
    } else if (motion->field128 < 0.8f) {
        motion->field128 = 0.8f;
        motion->field130 = -motion->field130;
    }
    motion->field11C += motion->field120 * D_800BE9A4;
    arg0->width = motion->field11C * motion->field124;
    arg0->height = motion->field11C * motion->field128;
    remaining -= motion->field138;
    if (remaining < 0) {
        arg0->field5C = 0;
        return 0;
    }
    arg0->field5C = remaining;
    return 1;
}

void *func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);

void *func_150DB2D8(Game108320Geometry *arg0, s16 arg1) {
    void *vertices;
    Game108320Vertex *result;
    f32 offsetX;
    f32 offsetZ;
    u8 created;

    func_151D5D60(arg0->buffers, arg1, 0x40,
                 &vertices, &created);
    result = vertices;
    if (vertices != 0) {
        if (created != 0) {
            func_10022EC0(arg0->buffers[arg1], arg0->templateVertices, 0x40U);
            func_10022EC0(arg0->buffers[arg1] + 4, arg0->templateVertices, 0x40U);
        }
    } else {
        return 0;
    }
    {
        offsetX = arg0->width * arg0->directionX;
        offsetZ = -arg0->width * arg0->directionZ;
        ((Game108320Vertex *)vertices)[0].x = (s32)(arg0->x + offsetX);
        ((Game108320Vertex *)vertices)[0].y = (s32)(arg0->y + arg0->height);
        ((Game108320Vertex *)vertices)[0].z = (s32)(arg0->z + offsetZ);
        ((Game108320Vertex *)vertices)[0].flag = 0;
        ((Game108320Vertex *)vertices)[1].x = (s32)(arg0->x + offsetX);
        ((Game108320Vertex *)vertices)[1].y = (s32)(arg0->y - arg0->height);
        ((Game108320Vertex *)vertices)[1].z = (s32)(arg0->z + offsetZ);
        ((Game108320Vertex *)vertices)[1].flag = 0;
        ((Game108320Vertex *)vertices)[2].x = (s32)(arg0->x - offsetX);
        ((Game108320Vertex *)vertices)[2].y = (s32)(arg0->y - arg0->height);
        ((Game108320Vertex *)vertices)[2].z = (s32)(arg0->z - offsetZ);
        ((Game108320Vertex *)vertices)[2].flag = 0;
        ((Game108320Vertex *)vertices)[3].x = (s32)(arg0->x - offsetX);
        ((Game108320Vertex *)vertices)[3].y = (s32)(arg0->y + arg0->height);
        ((Game108320Vertex *)vertices)[3].z = (s32)(arg0->z - offsetZ);
        ((Game108320Vertex *)vertices)[3].flag = 0;
        return result;
    }
}
typedef struct Game108320SpawnConfig {
    s8 field_00;
    u8 pad01;
    s16 field_02;
    s16 field_04;
    u8 pad06[2];
    s32 field_08;
    s32 field_0C;
    u8 colour[4];
    u8 pad14[0x2C];
    s32 field_40;
    u8 field_44;
    u8 field_45;
    u8 tail_pad[0x10];
} Game108320SpawnConfig;

void *func_1513D524(void *, u8, u8, u8, u8, u8, s32, u8, s32);

void func_150DB518(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s16 arg5, u8 arg6, s32 arg7) {
    Game108320SpawnConfig config;
    u8 *result;

    if ((arg0 != 0) && (arg1 != 0) && (arg2 != 0) && (arg3 != 0) &&
        (arg4 != 0) && (arg5 != 0)) {
        config.field_00 = 0x17;
        config.field_0C = 0x243A;
        config.field_40 = 0x401;
        config.field_44 = 0xFF;
        config.field_08 = 0;
        config.field_04 = arg5;
        config.field_45 = 0xFF;
        /* Keep this grouping to preserve IDO's t6/t7/t8/t9 constant materialisation order. */
        config.colour[2] = 0xC8, config.colour[1] = 0xC8, config.colour[0] = 0xC8;
        config.colour[3] = 0xC8;
        config.field_02 = 0x401;
        result = func_1513D524(&config, 0, 0xA, 0, 8, 0, 0x14,
                               arg6, arg7);
        if (result != 0) {
            *(s32 *)(result + 0x110) = arg0;
            *(s32 *)(result + 0x114) = arg1;
            *(s32 *)(result + 0x118) = arg2;
            *(s32 *)(result + 0x11C) = arg4;
            *(s32 *)(result + 0x120) = arg3;
        }
    }
}
