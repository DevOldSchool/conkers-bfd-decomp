#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_177B50.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514A6A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game177B50Vertex {
    s16 x, y, z, flag;
    u8 other[8];
} Game177B50Vertex;

typedef struct Game177B50Beam {
    u8 unknown0[0x2C];
    f32 width;
    f32 progress;
    Vec3f start;
    Vec3f end;
    f32 range;
    u8 unknown50[0x70];
    u8 vertexTemplate[0x40];
    u8 *buffers[1];
} Game177B50Beam;

typedef struct Game177B50Camera {
    u8 unknown0[0x2F8];
    Vec3f position;
    u8 unknown304[0x69C];
} Game177B50Camera;

void *func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern Game177B50Camera *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514A6A0 CURRENT (5884) */
void *func_1514A6A0(Game177B50Beam *arg0, s16 arg1) {
    Game177B50Vertex *vertices;
    void *result;
    f32 progress;
    Vec3f tip;
    f32 dx, dy, dz;
    f32 vx, vy, vz;
    f32 nx, ny, nz;
    f32 lengthSquared;
    f32 distance;
    f32 factor;
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
    tip.z = arg0->start.z + dz * progress;
    tip.y = arg0->start.y + dy * progress;
    tip.x = arg0->start.x + dx * progress;
    eye = &D_800DBFF0[arg1].position;
    dx = tip.x - arg0->start.x;
    dy = tip.y - arg0->start.y;
    dz = tip.z - arg0->start.z;
    distance = dx * dx + dy * dy + dz * dz;
    if (distance < arg0->range * arg0->range) {
        factor = 1.0f - sqrtf(distance) / arg0->range;
        dx += dx * factor;
        dy += dy * factor;
        dz += dz * factor;
    }
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
#endif /* CONKER_DEFERRED_CANDIDATE func_1514A6A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514A6A0.s")
typedef struct {
    Vec3f position;
    f32 field0C;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    s16 field20;
    s16 field22;
    s16 field24;
    u8 color26[4];
    s16 field2A;
    u8 field2C;
    u8 field2D;
    u8 field2E;
    u8 field2F;
    s32 field30;
    u8 field34;
    u8 pad35[3];
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
} Game177B50Particle;

void *func_15149550(f32 *, u8, u8, u8, u8, s32);
f32 func_150ADA68(void);
extern f32 D_800A57B0, D_800A57B4, D_800A57B8, D_800A57BC;
extern f32 D_800A57C0, D_800A57C4, D_800A57C8;

void func_1514AB5C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4,
                   f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                   s16 arg9, s16 arg10, u8 arg11) {
    Game177B50Particle particle;
    f32 radius;
    f32 xScale;
    f32 sine;
    f32 cosine;
    f32 yScale;
    u8 angle;

    if (arg4 > 0) {
        particle.field20 = 0x6231; particle.field22 = 0x1A4D;
        particle.color26[0] = 0;
        particle.color26[1] = 0;
        particle.color26[2] = 0;
        particle.color26[3] = 0xFF;
        particle.field2A = 1;
        particle.field2C = 0xFF;
        particle.field2D = 0xFF;
        particle.field30 = 0;
        particle.field2E = 0;
        particle.field2F = arg11;
        particle.field34 = 0xF;
        particle.position.y = arg1;
        particle.field38 = 0.0f;
        particle.field40 = 0.045f;
        particle.field44 = 0.7f;
        do {
            angle = func_150ADA20() & 0xFF;
            sine = func_151423D8(angle - 0x40);
            cosine = func_151423D8(angle);
            radius = func_150ADA68() * arg3;
            xScale = func_150ADA68() * arg6 + arg5;
            yScale = func_150ADA68();
            particle.position.x = radius * sine + arg0;
            particle.position.z = radius * cosine + arg2;
            particle.field0C = 22.6f * xScale;
            particle.field14 = 13.786f * xScale;
            yScale = yScale * arg8 + arg7;
            particle.field10 = 57.969f * yScale;
            particle.field18 = 42.714f * yScale;
            particle.field1C = 118.763f * yScale;
            particle.field24 = func_150ADA20() % (u32)(arg10 + 1) + arg9;
            func_15149550(&particle.position.x, 0xA, 0, 0, 0xFF, 1);
            arg4 -= 1;
        } while (arg4 != 0);
    }
}

extern f32 D_800A57CC, D_800A57D0, D_800A57D4, D_800A57D8;
extern f32 D_800A57DC, D_800A57E0, D_800A57E4, D_800A57E8;
extern f32 D_800A57EC, D_800A57F0, D_800A57F4, D_800A57F8;
extern f32 D_800A57FC, D_800A5800, D_800A5804;

void func_1514AD9C(Vec3f *arg0, s32 arg1, s32 arg2) {
    Game177B50Particle particle;
    f32 x_scale;
    f32 y_scale;
    f32 random_y;

    particle.field20 = 0x6231; particle.field22 = 0x1A4D;
    particle.position = *arg0;
    particle.color26[0] = 0;
    particle.color26[1] = 0;
    particle.color26[2] = 0;
    particle.color26[3] = 0xFF;
    particle.field2D = 0xFF;
    particle.field2E = 0;
    particle.field2F = 1;
    particle.field30 = 0;
    particle.field2A = 1;
    particle.field34 = 0x1C;
    particle.field3C = 0.0f;
    particle.field40 = D_800A57CC;
    particle.field44 = D_800A57D0;
    x_scale = (func_150ADA68() * D_800A57D4 + D_800A57D8) * D_800A57DC;
    random_y = func_150ADA68();
    particle.field0C = D_800A57E0 * x_scale;
    particle.field14 = D_800A57E4 * x_scale;
    y_scale = (random_y * D_800A57E8 + D_800A57EC) * D_800A57F0;
    particle.field10 = D_800A57F4 * y_scale;
    particle.field18 = D_800A57F8 * y_scale;
    particle.field1C = D_800A57FC * y_scale;
    particle.field24 = func_150ADA20() % 17U + 0x10;
    particle.field38 = (func_150ADA68() * D_800A5800 + 50.0f) * D_800A5804;
    particle.field2C = func_150ADA20() % 156U + 0x64;
    func_15149550(&particle.position.x, 10, 0, 0, ((u8 *)&arg1)[3], arg2);
}
extern f32 D_800BE9A4;

typedef struct Game177B50Decay {
    u8 pad0[0x2C];
    f32 width, height, unk34, offset;
    u8 pad3C[0x10];
    f32 acceleration, velocity;
    u8 pad54[0xFC];
    f32 decay;
} Game177B50Decay;

s32 func_1514AF74(Game177B50Decay *arg0) {
    f32 *dt = &D_800BE9A4;

    arg0->width = arg0->width - (arg0->width * arg0->decay);
    arg0->height = arg0->height - (arg0->height * arg0->decay);
    arg0->offset += (arg0->velocity * *dt) + (((0.5f * arg0->acceleration) * *dt) * *dt);
    arg0->velocity += arg0->acceleration * *dt;
    if ((arg0->width < 10.0f) || (arg0->height < 10.0f)) {
        return 0;
    }
    return 1;
}

void func_1514B034(Vec3f *arg0, u8 arg1, s32 arg2) {
    f32 count;
    Game177B50Particle particle;
    f32 xScale;
    f32 yScale;

    count = (func_150ADA68() * 20.0f + 29.0f) * 0.0001f * 5541.7695f;
    if (count > 1.0f) {
        particle.field20 = 0x6231;
        particle.field22 = 0x1A4D;
        particle.position.y = arg0->y;
        particle.field3C = 0.0f;
        particle.color26[0] = 0;
        particle.color26[1] = 0;
        particle.color26[2] = 0;
        particle.color26[3] = 0xFF;
        particle.field2D = 0xFF;
        particle.field2E = 0;
        particle.field2F = 1;
        particle.field30 = 0;
        particle.field2A = 1;
        particle.field34 = 0x1C;
        do {
            func_15143874((s16)(func_150ADA20() & 0xFF), func_150ADA68() * 42.0f,
                          &particle.position.x, &particle.position.z);
            particle.position.x += arg0->x;
            particle.position.z += arg0->z;
            particle.field40 = (func_150ADA68() * 16.0f + 29.0f) * 0.001f;
            particle.field44 = (func_150ADA68() * 600.0f + 400.0f) * 0.001f;
            xScale = (func_150ADA68() * 1205.0f + 304.0f) * 0.001f;
            yScale = (func_150ADA68() * 1006.0f + 504.0f) * 0.001f;
            particle.field0C = 22.6f * xScale;
            particle.field14 = 13.786f * xScale;
            particle.field10 = 57.969f * yScale;
            particle.field18 = 42.714f * yScale;
            particle.field1C = 118.763f * yScale;
            particle.field24 = func_150ADA20() % 31U + 0x14;
            particle.field38 = func_150ADA68() * 497.0f * 0.001f;
            particle.field2C = func_150ADA20() % 156U + 0x64;
            func_15149550(&particle.position.x, 10, 0, 0, arg1, arg2);
            count -= 1.0f;
        } while (count > 1.0f);
    }
}

typedef struct Game1514B364Burst {
    s32 countBase, countRange;
    Vec3f position;
    f32 sizeBase, sizeRange, spreadBase, spreadRange, speedBase, speedRange;
    s16 yawBase, yawRange, pitchBase, pitchRange;
    s32 burstBase, burstRange;
    s16 lifeBase, lifeRange;
    u16 kind;
    u8 field42, field43, field44;
    u8 colorBase[4], colorRange[4], fadeBase[4], fadeRange[4];
    u8 field55, field56, field57, field58;
    u8 pad59[3];
    s32 flags, mode;
    s16 duration, period, repeat;
    u8 field6A, pad6B;
    f32 scale;
    s8 field70, field71, field72, field73;
} Game1514B364Burst;

typedef struct Game1514B364Debris {
    Vec3f position;
    f32 sizeBase, sizeRange, growthBase, growthRange, speedBase, speedRange;
    s16 countBase, countRange, yawBase, yawRange, pitchBase, pitchRange;
    s16 fadeBase, fadeRange, lifeBase, lifeRange;
    u8 green, red, pad3A[2];
    s32 callbacks[6];
    u8 blue, alpha;
} Game1514B364Debris;

typedef struct Game1514B364Packet {
    s8 type;
    s8 mode;
    s16 flags;
    s16 duration;
    u8 pad6[2];
    s32 field8;
    s32 fieldC;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    f32 scaleX;
    f32 scaleY;
    Vec3f position;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 magnitude;
    f32 field38;
    f32 field3C;
    s32 field40;
    u8 selector;
    u8 flag45;
    u8 flag46;
    u8 flag47;
    s32 field48;
    u8 field4C;
    u8 pad4D[3];
    s32 field50;
    s16 field54;
    s16 field56;
} Game1514B364Packet;

s32 func_15046C80(f32 *, u16, f32, void *);
void func_15152B38(void *, u8, s32);
void func_15152F70(void *, u8);

void func_1514B364(Vec3f *arg0, s32 arg1, u8 arg2, s32 arg3) {
    Vec3f position;

    position = *arg0;
    {
        Vec3f probe;
        Game1514B364Burst burst;
        Game1514B364Debris debris;
        Game1514B364Packet packet;

        probe.x = arg0->x;
        probe.y = arg0->y + 200.0f;
        probe.z = arg0->z;
        if (func_15046C80(&probe.x, 0, arg0->y - 200.0f, (void *)arg1) != 0) {
            burst.countBase = 10;
            burst.countRange = 0;
            burst.sizeBase = 9.900001f;
            burst.sizeRange = 21.0f;
            burst.spreadBase = -3.0000002f;
            burst.spreadRange = 1.016f;
            burst.speedBase = 30.0f;
            burst.speedRange = 30.4f;
            burst.yawBase = 0;
            burst.yawRange = 0xFF;
            burst.pitchBase = -0x3F;
            burst.pitchRange = 0x2B;
            burst.burstBase = 4;
            burst.burstRange = 5;
            burst.lifeBase = 0x1E;
            burst.lifeRange = 0x1E;
            burst.kind = 1;
            burst.field42 = 0xC;
            burst.field43 = 2;
            burst.field44 = 3;
            burst.colorBase[0] = 0xB4;
            burst.colorBase[1] = 0;
            burst.colorBase[2] = 0;
            burst.colorBase[3] = 0x9B;
            burst.colorRange[0] = 0x32;
            burst.colorRange[1] = 0x64;
            burst.colorRange[2] = 0;
            burst.colorRange[3] = 0x64;
            burst.fadeBase[0] = 0xFF;
            burst.fadeBase[1] = 0xFF;
            burst.fadeBase[2] = 0xFF;
            burst.fadeBase[3] = 0xFF;
            burst.fadeRange[0] = 0;
            burst.fadeRange[1] = 0;
            burst.fadeRange[2] = 0;
            burst.fadeRange[3] = 0;
            burst.field55 = 0xFF;
            burst.field56 = 0;
            burst.field57 = 1;
            burst.field58 = 0x24;
            burst.flags = 0x200005;
            burst.mode = 0x60600;
            burst.duration = 0x14;
            burst.period = 0xC;
            burst.repeat = 1;
            burst.field6A = 0;
            burst.scale = 1.0;
            burst.field70 = -1;
            burst.field71 = 0;
            burst.field72 = -1;
            burst.field73 = -1;
            burst.position = position;
            func_15152B38(&burst, arg2, arg3);
            debris.position = position;
            debris.sizeBase = 3.99f;
            debris.sizeRange = 8.11f;
            debris.growthBase = 0.60200006f;
            debris.growthRange = 0.407f;
            debris.speedBase = 10.139999f;
            debris.speedRange = 10.2699995f;
            debris.countBase = 8;
            debris.countRange = 8;
            debris.yawBase = 0;
            debris.yawRange = 0xFF;
            debris.pitchBase = -0x40;
            debris.pitchRange = 0x2C;
            debris.fadeBase = 5;
            debris.fadeRange = 4;
            debris.lifeBase = 0x42;
            debris.lifeRange = 0x1E;
            debris.green = 0xA;
            debris.red = 0x21;
            debris.callbacks[0] = 1;
            debris.callbacks[1] = 0xC;
            debris.callbacks[2] = 0;
            debris.callbacks[3] = 0;
            debris.callbacks[4] = 0;
            debris.callbacks[5] = 0;
            debris.blue = 0xFF;
            debris.alpha = func_150ADA20() % 101U + 0x9B;
            func_15152F70(&debris, 0xFF);
            func_1514B034(&position, arg2, arg3);
            {
                f32 height = position.y + 10.0f;
                packet.type = 0x38;
                packet.flags = 1;
                packet.duration = 0x32;
                packet.field8 = 0;
                packet.fieldC = 0x6666;
                packet.alpha = 0xFF;
                packet.scaleX = 1.0f;
                packet.scaleY = 1.0f;
                packet.position.x = position.x;
                packet.position.y = height;
                packet.position.z = position.z;
                packet.field28 = 0.0f;
                packet.field2C = 0.0f;
                packet.field30 = 0.0f;
                packet.field38 = 1.0f;
                packet.field3C = 1.0f;
                packet.field40 = 0x400C0001;
                packet.magnitude = 0.2f;
                packet.selector = func_150ADA20() % 101U + 0x64;
                packet.flag45 = 0xFF;
                packet.flag46 = 0;
                packet.flag47 = 6;
                packet.red = func_150ADA20() % 51U + 0xB4;
                packet.green = func_150ADA20() % 101U;
                packet.blue = func_150ADA20() % 1U;
                func_1513D668((s32)&packet, 0, 0x12, 0x1D, 0,
                              (func_150ADA20() & 1) + (func_150ADA20() & 1),
                              func_150ADA20() & 0xFF, 100.0f, 100.0f, 0, arg1 + 4,
                              0, 0, arg2, arg3);
            }
        }
    }
}
s32 func_1514B844(void *arg0) {
    s16 temp_v1;
    s32 temp_a0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v1 < 0x10) {
        temp_a0 = temp_v1 * 0x10;
        if (temp_a0 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
            *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) temp_a0;
        }
    }
    return 1;
}
extern f32 D_800BE9A4;

s32 func_1514B87C(void *arg0) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
    return 1;
}
s32 func_1514B8B0(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x10) {
        temp_v1 = temp_v0 * 0x10;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    return 1;
}
void *func_10022EC0(void *, const void *, u32);
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
extern u8 D_800A4AA0[];

typedef struct {
    s8 kind, mode;
    u16 texture;
    s16 lifetime;
    u8 pad6[2];
    s32 field8, fieldC;
    u8 color[4];
    f32 field14, field18;
    Vec3f position, origin, scale;
    s32 flags;
    u8 field44, field45, field46, field47;
    s32 field48;
    u8 pad4C[8];
    s16 field54, field56;
} Game177B50Descriptor;

typedef struct {
    f32 values[14];
    Vec3f direction;
    Vec3f velocity;
} Game177B50Motion;

void *func_1514B8E4(Vec3f *arg0, f32 *arg1, s16 arg2, u8 arg3,
                     Vec3f *arg4, f32 arg5, f32 arg6, f32 arg7,
                     u8 arg8, u8 arg9, u8 arg10, s32 arg11, u8 arg12,
                     s16 arg13, s16 arg14, s32 arg15, u8 arg16, s32 arg17) {
    void *result;
    Game177B50Descriptor particle;
    Game177B50Motion motion;
    s32 flag1;
    s32 timed;
    s32 flag2;

    if (arg4 != NULL) {
        motion.direction = *arg4;
    } else {
        motion.direction.x = 0.0f;
        motion.direction.y = 0.0f;
        motion.direction.z = 0.0f;
    }
    motion.velocity.x = arg5;
    motion.values[7] = 0.0f;
    motion.values[8] = 0.0f;
    motion.values[12] = 0.0f;
    particle.fieldC = 0x3E3F;
    motion.values[13] = 15935.0f;
    motion.values[11] = 15935.0f;
    motion.velocity.y = arg6;
    motion.velocity.z = arg7;
    motion.values[9] = 6733.0f;
    motion.values[10] = 18404.0f;
    motion.values[0] = arg1[0] * 15.045272f;
    motion.values[2] = arg1[0] * 5.8676558f;
    motion.values[4] = arg1[0] * 12.111444f;
    particle.field14 = 0.0f;
    motion.values[1] = arg1[1] * 0.396174f;
    motion.values[3] = arg1[1] * 0.1042563f;
    motion.values[6] = arg1[1] * 0.5197371f;
    motion.values[5] = arg1[1] * 0.34404588f;
    particle.field18 = 0.0f;
    particle.mode = 0;
    particle.kind = arg11;
    particle.texture = 0x2203;
    if (arg2 == -1) particle.lifetime = 300;
    else particle.lifetime = arg2;
    particle.field8 = 0;
    particle.color[0] = 255;
    particle.color[1] = 255;
    particle.color[2] = 255;
    particle.color[3] = 255;
    particle.position = *arg0;
    particle.origin.x = arg0->x;
    particle.origin.y = arg0->y + 100.0f;
    particle.origin.z = arg0->z;
    particle.scale.x = 1.0f;
    particle.scale.y = 1.0f;
    particle.scale.z = 1.0f;
    flag1 = (arg12 & 1) ? 0x800000 : 0;
    timed = (arg2 == -1) ? 0 : 1;
    flag2 = (arg12 & 2) ? 0x2000000 : 0;
    particle.flags = flag2 | timed | 0x40000 | 0x80000 | 0x200000 | 0x400000 | flag1 | 0x40000000;
    particle.field44 = arg3;
    particle.field45 = 255;
    particle.field46 = 0;
    particle.field47 = 7;
    particle.field48 = 0;
    particle.field54 = arg13;
    particle.field56 = arg14;
    if (func_150ADA20() & 1) flag2 = 1;
    else flag2 = 0;
    result = func_1513D2F0((s32)&particle, (s32)D_800A4AA0, arg8, arg9, arg10,
                           0x1C, flag2 | 2, 0, 0, arg15 + 0x50, arg16, arg17);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x110, &motion, 0x50);
    }
    return result;
}
extern f32 D_800A5888;
extern f32 D_800A588C;
extern f32 D_800A5890;

s32 func_1514BC08(void *arg0, void *arg1) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;

    *(f32 *)((u8 *)arg1 + 0x1C) = (f32) (*(f32 *)((u8 *)arg1 + 0x1C) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x1C) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x1C) = (f32) (func_150ADA68() * 4.0f);
        *(f32 *)((u8 *)arg1 + 0x10) = (f32) (*(f32 *)((u8 *)arg1 + 0) + *(f32 *)((u8 *)arg1 + 8) * func_150ADA68());
    }
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x2C) += (*(f32 *)((u8 *)arg1 + 0x10) - temp_fv0) * D_800A5888;
    *(f32 *)((u8 *)arg1 + 0x20) = (f32) (*(f32 *)((u8 *)arg1 + 0x20) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x20) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x20) = (f32) (func_150ADA68() * 9.0f);
        if (func_150ADA20() & 1) {
            *(f32 *)((u8 *)arg1 + 0x14) = (f32) (*(f32 *)((u8 *)arg1 + 4) + *(f32 *)((u8 *)arg1 + 0xC) * func_150ADA68());
        } else {
            *(f32 *)((u8 *)arg1 + 0x14) = (f32) (*(f32 *)((u8 *)arg1 + 4) + *(f32 *)((u8 *)arg1 + 0x18) * func_150ADA68());
        }
    }
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x30) += (*(f32 *)((u8 *)arg1 + 0x14) - temp_fv0_2) * D_800A588C;
    *(f32 *)((u8 *)arg1 + 0x30) = (f32) (*(f32 *)((u8 *)arg1 + 0x30) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x30) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x30) = (f32) (func_150ADA68() * 7.0f);
        *(f32 *)((u8 *)arg1 + 0x2C) = (f32) (*(f32 *)((u8 *)arg1 + 0x24) + *(f32 *)((u8 *)arg1 + 0x28) * func_150ADA68());
    }
    temp_fv0_3 = *(f32 *)((u8 *)arg1 + 0x34);
    *(f32 *)((u8 *)arg1 + 0x34) += (*(f32 *)((u8 *)arg1 + 0x2C) - temp_fv0_3) * D_800A5890;
    *(s32 *)((u8 *)arg0 + 0x24) = (s32) *(f32 *)((u8 *)arg1 + 0x34);
    return 1;
}
