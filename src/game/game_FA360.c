#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FA360.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CD59C
 * - func_150CD7F8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameFA360Range {
    f32 low;
    f32 high;
} GameFA360Range;

typedef struct GameFA360Emitter {
    Vec3f position;
    Vec3f velocity;
    f32 drag;
    f32 gravity;
    u8 color[3];
    u8 alpha;
    s32 life;
    GameFA360Range range;
    f32 minVy;
} GameFA360Emitter;

typedef struct GameFA360Packet {
    s8 kind;
    u8 pad1;
    s16 flags;
    s16 life;
    u8 pad6[2];
    s32 field8;
    s32 fieldC;
    u8 color[4];
    GameFA360Range range;
    Vec3f position;
    Vec3f direction;
    Vec3f scale;
    s32 mode;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    u8 pad48[0x10];
} GameFA360Packet;

typedef struct GameFA360DriftInit {
    Vec3f velocity;
    f32 gravity;
    f32 drag;
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    u8 pad20[4];
    f32 swayAngle;
    f32 swaySpeed;
    f32 swayRadius;
    f32 phase;
    f32 phaseSpeed;
    f32 phaseScale;
    f32 minVy;
} GameFA360DriftInit;

void *func_10022EC0(void *, const void *, u32);
f32 func_150ADA68(void);
void *func_1513D524(s32, u8, u8, u8, u8, u8, s32, u8, s32);
extern f32 D_800A0710;
extern f32 D_800A0714;
extern f32 D_800A0718;
extern f32 D_800A071C;
extern f32 D_800A0720;
extern f32 D_800A0724;
extern f32 D_800A0728;
extern f32 D_800A072C;
extern f32 D_800A0730;
extern f32 D_800A0734;
extern f32 D_800A0738;
extern f32 D_800A073C;
extern f32 D_800A0740;
extern f32 D_800A0744;
extern f32 D_800A0748;

void *func_150CCEB0(GameFA360Emitter *arg0, u8 arg1, u8 arg2) {
    void *result;
    GameFA360Packet packet;
    GameFA360DriftInit drift;

    packet.kind = 0x57;
    packet.flags = 0x2D03;
    packet.life = arg0->life;
    packet.field8 = 0;
    packet.fieldC = 0;
    packet.color[0] = arg0->color[0];
    packet.color[1] = arg0->color[1];
    packet.color[2] = arg0->color[2];
    packet.color[3] = 0xFF;
    packet.range = arg0->range;
    packet.position = arg0->position;
    packet.direction.x = func_150ADA68() * 360.0f;
    packet.direction.y = func_150ADA68() * 360.0f;
    packet.direction.z = func_150ADA68() * 360.0f;
    packet.mode = 0xC03E1;
    packet.scale.x = 0.0f;
    packet.scale.y = 0.0f;
    packet.scale.z = 0.0f;
    packet.field44 = arg0->alpha;
    packet.field45 = 0xFF;
    packet.field46 = 0;
    packet.field47 = 6;
    drift.velocity = arg0->velocity;
    drift.minVy = arg0->minVy;
    drift.drag = arg0->drag;
    drift.gravity = arg0->gravity;
    drift.offsetX = (func_150ADA68() * D_800A0710 + D_800A0714) * D_800A0718;
    drift.offsetY = (func_150ADA68() * D_800A071C + D_800A0720) * D_800A0724;
    drift.offsetZ = (func_150ADA68() * D_800A0728 + D_800A072C) * D_800A0730;
    drift.swayAngle = 0.0f;
    drift.swaySpeed = (func_150ADA68() * 206.0f + 58.0f) * D_800A0734;
    drift.swayRadius = func_150ADA68() * 360.0f;
    drift.phase = 0.0f;
    drift.phaseSpeed = func_150ADA68() * D_800A0738 * D_800A073C;
    drift.phaseScale = (func_150ADA68() * D_800A0740 + D_800A0744) * D_800A0748;
    result = func_1513D524((s32)&packet, 0x13, 0x1E, 0, 0x11, 0, 0x40, arg1, arg2);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x110, &drift, 0x40);
    }
    return result;
}
typedef struct GameFA360Drift {
    f32 vx;
    f32 vy;
    f32 vz;
    f32 gravity;
    f32 drag;
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    u8 pad20[4];
    f32 swayAngle;
    f32 swaySpeed;
    f32 swayRadius;
    f32 phase;
    f32 phaseSpeed;
    f32 phaseScale;
    f32 minVy;
} GameFA360Drift;

typedef struct GameFA360Drifter {
    u8 pad0[0x34];
    f32 x;
    f32 y;
    f32 z;
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    f32 sway[3];
    u8 pad58[0xB8];
    GameFA360Drift drift;
} GameFA360Drifter;

f32 func_15047D60(f32);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

s32 func_150CD17C(GameFA360Drifter *arg0) {
    GameFA360Drift *drift;
    s32 i;
    f32 wave;
    f32 angle;
    f32 period;

    drift = &arg0->drift;
    arg0->x += drift->vx * D_800BE9A4;
    arg0->y += drift->vy * D_800BE9A4 + 0.5f * drift->gravity * D_800BE9A4 * D_800BE9A4;
    arg0->z += drift->vz * D_800BE9A4;
    drift->vy += drift->gravity * D_800BE9A4;
    for (i = D_800BE9E4; i != 0; i--) {
        drift->vx *= drift->drag;
        drift->vz *= drift->drag;
    }
    if (drift->vy > 0.0f) {
        for (i = D_800BE9E4; i != 0; i--) {
            drift->vy *= drift->drag;
        }
    }
    if (drift->vy < drift->minVy) {
        drift->vy = drift->minVy;
    }
    if (drift->vy < 0.0f) {
        wave = func_15047D60(drift->phase);
        angle = drift->phaseScale * wave + 1.5707964f;
        func_151436B4(drift->swayRadius, angle, drift->swayAngle, arg0->sway);
        period = 6.2831855f;
        drift->swayAngle += drift->swaySpeed * D_800BE9A4;
        drift->phase += drift->phaseSpeed * D_800BE9A4;
        while (drift->phase > period) {
            drift->phase -= period;
        }
        while (drift->phase < 0.0f) {
            drift->phase += period;
        }
    }
    arg0->offsetX += drift->offsetX;
    arg0->offsetY += drift->offsetY;
    arg0->offsetZ += drift->offsetZ;
    return 1;
}
void *func_10022EC0(void *, const void *, u32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A8050(void *, f32, f32, f32);
void func_151D5D60(void *, s16, s32, void **, u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CD59C CURRENT (2665) */
void *func_150CD59C(u8 *arg0, s32 arg1) {
    void *vertices;
    void *base;
    f32 matrix[16];
    f32 corners[4][3];
    u8 fresh;
    u8 *buffers;
    u8 *template;
    f32 *point;
    s32 i;
    s32 next_i;

    arg1 = (s16)arg1;
    func_151D5D60(arg0 + 0x100, (s16)arg1, 0x40, &vertices, &fresh);
    base = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            buffers = arg0 + arg1 * 4;
            template = arg0 + 0xC0;
            func_10022EC0(*(void **)(buffers + 0x100), template, 0x40U);
            func_10022EC0(*(u8 **)(buffers + 0x100) + 0x40, template, 0x40U);
        }
    } else {
        return 0;
    }
    corners[0][0] = *(f32 *)(arg0 + 0x2C);
    corners[0][2] = 0.0f;
    corners[0][1] = *(f32 *)(arg0 + 0x30);
    corners[1][0] = -*(f32 *)(arg0 + 0x2C);
    corners[1][2] = 0.0f;
    corners[1][1] = *(f32 *)(arg0 + 0x30);
    corners[2][0] = -*(f32 *)(arg0 + 0x2C);
    corners[2][2] = 0.0f;
    corners[2][1] = -*(f32 *)(arg0 + 0x30);
    corners[3][0] = *(f32 *)(arg0 + 0x2C);
    corners[3][2] = 0.0f;
    corners[3][1] = -*(f32 *)(arg0 + 0x30);
    func_150A8050(matrix, *(f32 *)(arg0 + 0x40),
                 *(f32 *)(arg0 + 0x44), *(f32 *)(arg0 + 0x48));
    matrix[12] = *(f32 *)(arg0 + 0x34);
    matrix[13] = *(f32 *)(arg0 + 0x38);
    matrix[14] = *(f32 *)(arg0 + 0x3C);
    if (*(f32 *)(arg0 + 0x114) < 0.0f) {
        matrix[12] += *(f32 *)(arg0 + 0x4C);
        matrix[13] += *(f32 *)(arg0 + 0x50);
        matrix[14] += *(f32 *)(arg0 + 0x54);
    }
    i = 0;
    do {
        point = corners[i];
        func_150A7960(matrix, point[0], point[1], 0.0f,
                     &point[0], &point[1], &point[2]);
        *(s16 *)vertices = (s32)point[0];
        next_i = (i + 1) & 0xFF;
        *(s16 *)((u8 *)vertices + 2) = (s32)point[1];
        *(s16 *)((u8 *)vertices + 4) = (s32)point[2];
        *(s16 *)((u8 *)vertices + 6) = 0;
        vertices = (u8 *)vertices + 0x10;
        i = next_i;
    } while (i < 4);
    return base;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CD59C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CD59C.s")
typedef struct {
    s32 countBase, countRange;
    Vec3f position;
    s16 angleBase, angleRange, pitchBase, pitchRange;
    f32 speedBase, speedRange, field24;
    f32 scaleBase, scaleRange;
    s8 colorIndex;
    u8 pad31;
    s16 lifeBase, lifeRange;
    u8 pad36[2];
    f32 field38, field3C, field40, field44, field48;
} GameFA360Particle;
typedef struct { f32 values[5]; } GameFA360Angles;

f32 func_150ADA68(void);
void func_1514373C(f32, f32, f32 *, f32 *);
void func_15152874(GameFA360Particle *, u8, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)
extern s32 D_80082FA4;
extern GameFA360Angles D_80088874;
extern u8 *D_800DBFF0;
extern f32 D_800BE9A4;
extern f32 D_800A0754, D_800A0758, D_800A075C;
extern f64 D_800A0760, D_800A0768;
extern f32 D_800A0770, D_800A0774, D_800A0778, D_800A077C, D_800A0780;
extern f32 D_800A0784, D_800A0788, D_800A078C, D_800A0790;
extern f32 D_800A0794, D_800A0798, D_800A079C, D_800A07A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CD7F8 CURRENT (1565) */
void func_150CD7F8(u8 *arg0) {
    f32 random;
    GameFA360Particle particle;
    GameFA360Angles angles;
    f32 angle;
    f32 yaw;
    f64 radiusBase;
    f64 radiusRange;
    s32 index;
    f32 *pending;

    pending = (f32 *)(arg0 + 0x28);
    *pending += D_800A0754 * D_800BE9A4 * *(f32 *)(arg0 + 0x2C);
    if (*pending > 1.0f) {
        particle.pitchBase = -23;
        particle.pitchRange = 6;
        particle.colorIndex = 0;
        particle.field24 = D_800A0758;
        particle.field48 = D_800A075C;
        radiusBase = D_800A0760;
        radiusRange = D_800A0768;
        do {
            angles = D_80088874;
            index = (func_150ADA20() % 5U) & 0xFF;
            angle = func_150ADA68() * D_800A0770 + angles.values[index];
            yaw = *(f32 *)(D_800DBFF0 + D_80082FA4 * 0x9A0 + 0x380) - 180.0f;
            if (yaw > 360.0f) {
                do { yaw -= 360.0f; } while (yaw > 360.0f);
            }
            if (yaw < 0.0f) {
                do { yaw += 360.0f; } while (yaw < 0.0f);
            }
            yaw *= D_800A0774;
            if (fabsf(angle - yaw) < D_800A0778) {
                random = func_150ADA68();
                particle.position.y = D_800A077C * random + D_800A0780 + 500.0f;
                func_1514373C(angle, (f32)((f64)random * radiusRange + radiusBase),
                              &particle.position.x, &particle.position.z);
                particle.countBase = 15;
                particle.countRange = 20;
                particle.angleRange = 12;
                particle.lifeBase = 0x226;
                particle.lifeRange = 0;
                particle.field3C = 15.0f;
                particle.field38 = 15.0f;
                particle.field44 = D_800A0784;
                particle.field40 = D_800A0784;
                particle.angleBase = (s32)((angle + D_800A0788 - D_800A078C) * D_800A0790);
                particle.speedBase = D_800A0794;
                particle.speedRange = D_800A0798;
                particle.scaleBase = D_800A079C;
                particle.scaleRange = D_800A07A0;
                func_15152874(&particle, arg0[0xC], arg0[1]);
            }
            *pending -= 1.0f;
        } while (*pending > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CD7F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CD7F8.s")

extern s32 D_80088870;
extern f32 D_800A07A4;

void func_150CDB6C(s32 arg0) {
    f32 *value;

    if ((arg0 >= 0) && (arg0 < 0x100) && (D_80088870 != 0)) {
        value = (f32 *)(D_80088870 + 0x28);
        value[1] = (f32) arg0 * D_800A07A4;
    }
}
