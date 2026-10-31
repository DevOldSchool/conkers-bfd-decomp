#include "types.h"
#include "game_functions.h"
#include "game_collision.h"
#include "game_view.h"

/*
 * Reviewed source unit: src/game/game_188440.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_quad_actor_effect_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515AF90
 * - func_1515B21C
 * - func_1515B674
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
f32 func_150ADA68(void);
typedef struct GameAF90Packet {
    Vec3f position;
    f32 scale;
    f32 zero;
    f32 ground;
} GameAF90Packet;

s32 func_1504697C(Vec3f *, u16, f32, Game71820Hit *);
extern f32 D_800A6420;
extern f32 D_800A6424;
extern f32 D_800A6428;
extern f32 D_800A642C;
extern f32 D_800A6430;
extern f32 D_800A6434;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515AF90 CURRENT (2718) */
void func_1515AF90(s16 arg0) {
    void *result;
    GameAF90Packet packet;
    Vec3f *base;
    s32 offset;
    u8 valid;
    s16 angle;
    f32 radius;
    f32 cosine;
    f32 sine;
    Game71820Hit hit;
    Vec3f query;
    Game71820Hit lowerHit;
    Vec3f lowerQuery;
    f32 lowerHeight;

    if (!(func_150ADA20() & 0xF)) {
        valid = 1;
        base = (Vec3f *)&D_800DBFF0[arg0].unk2F8;
        offset = D_800DBFF0[arg0].unk380 * D_800A6420;
        angle = (func_150ADA20() % 41U) + offset - 0x14;
        radius = func_150ADA68() * D_800A6424 + 107.0f;
        cosine = func_151423D8(angle);
        sine = func_151423D8(angle - 0x40);
        packet.position.x = base->x - radius * sine;
        packet.position.z = base->z - radius * cosine;
        query.x = packet.position.x;
        hit.object = 0;
        hit.flags = 0;
        hit.active = 0;
        hit.field20 = 0;
        query.y = D_800A6428;
        query.z = packet.position.z;
        hit.height = D_800A642C;
        if (func_1504697C(&query, 0, base->y, &hit) != 0) {
            packet.ground = hit.height;
        } else {
            valid = 0;
        }
        if (valid) {
            lowerHeight = base->y + -250.0f;
            lowerHit.field20 = 0;
            lowerHit.active = 0;
            lowerHit.flags = 0;
            lowerHit.object = 0;
            lowerHit.height = D_800A6430;
            lowerQuery.x = packet.position.x;
            lowerQuery.y = base->y;
            lowerQuery.z = packet.position.z;
            if (func_1504697C(&lowerQuery, 0, lowerHeight, &lowerHit) != 0) {
                packet.position.y = lowerHit.height;
            } else {
                packet.position.y = lowerHeight;
            }
        }
        func_150ADA68();
        packet.zero = 0.0f;
        packet.scale = 195.0f * D_800A6434;
        if (valid) {
            angle = (func_150ADA20() % 61U) + 5;
            result = func_151491F4(angle, -1, 0xC, 1, 7, 0x18, 0xFF, 0);
            if (result != NULL) {
                func_10022EC0((u8 *)result + 0x28, &packet, sizeof(packet));
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515AF90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515AF90.s")

typedef struct {
    s32 flags, zero4;
    s16 texture, lifetime;
    s32 zeroC, zero10;
    u8 zero14, zero15, zero16, zero17, zero18, zero19, zero1A;
    u8 alpha, maximum, kind;
    s16 duration, period, zero22;
    f32 zero24, width, height;
    Vec3f position;
    f32 zero3C, zero40, zero44;
    Vec3f velocity;
    f32 rotation;
    s32 mode, unused5C;
    s8 field60, field61, field62, field63;
    u8 pad64[0xC];
} GameB21CParticle;

typedef struct {
    f32 size;
    u8 phase0, phase1, step0, step1;
    f32 amount0, amount1, speed, damping;
    u8 phase2, phase3, step2, step3;
    f32 amount2, amount3, limit;
} GameB21CMotion;

typedef struct {
    Vec3f position;
    f32 rate, count, limit;
} GameB21CEmitter;

void *func_10022EC0(void *, const void *, u32);
f32 func_150ADA68(void);
void *func_151303BC(s32, u8, s32);
extern f32 D_800BE9A4;
extern f32 D_800A6438, D_800A643C, D_800A6440, D_800A6444;
extern f32 D_800A6448, D_800A644C, D_800A6450, D_800A6454;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515B21C CURRENT (5086) */
void func_1515B21C(void *arg0) {
    void *result;
    GameB21CParticle particle;
    GameB21CMotion motion;
    f32 amountBase;
    f32 amountScale;
    f32 smallBase;
    GameB21CEmitter *emitter;

    ((GameB21CEmitter *)((u8 *)arg0 + 0x28))->count +=
        ((GameB21CEmitter *)((u8 *)arg0 + 0x28))->rate * D_800BE9A4;
    emitter = (GameB21CEmitter *)((u8 *)arg0 + 0x28);
    if (emitter->count > 1.0f) {
        particle.kind = 0x2F;
        particle.texture = 0xC01;
        particle.flags = 0x200005;
        particle.zero4 = 0;
        particle.zero1A = 0;
        particle.zero19 = 0;
        particle.zero18 = 0;
        particle.zero17 = 0;
        particle.zero16 = 0;
        particle.zero15 = 0;
        particle.zero14 = 0;
        particle.zero10 = 0;
        particle.zeroC = 0;
        particle.maximum = 0xFF;
        particle.zero22 = 0;
        particle.zero24 = 0.0f;
        particle.mode = 0x3207;
        particle.field60 = 5;
        particle.field61 = 5;
        particle.field62 = 4;
        particle.field63 = -1;
        particle.position = emitter->position;
        particle.zero3C = 0.0f;
        particle.zero40 = 0.0f;
        particle.zero44 = 0.0f;
        particle.duration = 50;
        particle.period = 5;
        motion.phase0 = 0;
        motion.phase1 = 0;
        motion.phase2 = 0;
        motion.phase3 = 0;
        particle.velocity.x = 0.0f;
        particle.velocity.z = 0.0f;
        motion.speed = D_800A6438;
        motion.damping = D_800A643C;
        motion.limit = emitter->limit;
        if (func_150ADA20() & 1) particle.mode |= 0x40;
        if (func_150ADA20() & 1) particle.mode |= 0x80;
        amountBase = D_800A6440;
        amountScale = D_800A6444;
        smallBase = D_800A6448;
        do {
            particle.velocity.y = func_150ADA68() * 12.0f * D_800A644C;
            particle.lifetime = func_150ADA20() % 152U + 150;
            particle.alpha = func_150ADA20() % 151U + 55;
            particle.height = func_150ADA68() * 200.0f + 100.0f;
            particle.width = particle.height;
            motion.size = particle.height;
            motion.step0 = func_150ADA20() % 5U + 4;
            motion.step1 = func_150ADA20() % 5U + 4;
            motion.amount0 = (func_150ADA68() * 0.25f + smallBase) * motion.size;
            motion.amount1 = (func_150ADA68() * 0.25f + smallBase) * motion.size;
            motion.step2 = (func_150ADA20() & 3) + 2;
            motion.step3 = (func_150ADA20() & 3) + 2;
            motion.amount2 = (func_150ADA68() * amountScale + amountBase) * motion.size;
            motion.amount3 = (func_150ADA68() * amountScale + amountBase) * motion.size;
            particle.rotation = (func_150ADA68() * D_800A6450 + 600.0f) * D_800A6454;
            result = func_151303BC((s32)&particle, 2, 0x28);
            if (result != 0) func_10022EC0((u8 *)result + 0xA8, &motion, 0x28);
            emitter->count -= 1.0f;
        } while (emitter->count > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515B21C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515B21C.s")

void func_1515572C(s16 *arg0, s32 arg1, s16 arg2);

void func_1515B5F4(s16 arg0) {
    struct {
        s16 sp1C;
        s16 pad1E;
    } sp;

    sp.sp1C = arg0;
    func_1515572C(&sp.sp1C, 0xB, arg0);
}
void func_1515B62C(void *arg0, s16 *arg1, u8 arg2) {
    if ((arg2 == 0xB) && (*(s16 *)((u8 *)arg0 + 0x70) == *arg1)) {
        func_1516972C(arg0);
    }
}
void *func_10022EC0(void *, const void *, u32);
u8 func_151D8E20(void);
f32 func_150ADA68(void);
extern s32 (*D_8008FD04[])(void);
extern f32 D_800A6458, D_800A645C, D_800A6460, D_800A6464, D_800A6468;

typedef struct {
    f32 x, y, width, height;
    u8 texture;
    u8 pad11;
    s16 lifetime;
    u16 flags;
    s16 duration, period;
    u8 mode, red, green, blue, alpha, maximum;
    u8 endRed, endGreen, endBlue, endAlpha;
    s32 zero24, zero28, zero2C;
    s32 field30, field34, field38, field3C;
    u8 field40, field41;
    u8 pad42[2];
    s8 owner;
    u8 pad45[0x13];
} Game188440Particle;

typedef struct {
    s16 owner;
    s16 pad2;
    f32 acceleration, velocity, base, scale;
    f32 pad14;
} Game188440Motion;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515B674 CURRENT (5500) */
void func_1515B674(s16 arg0) {
    s16 count;
    Game188440Particle particle;
    void *result;
    Game188440Motion motion;
    register f32 speedScale;
    register f32 sizeScale;
    register f32 motionScale;

    func_150ADA20();
    count = 10;
    particle.flags = 0x19;
    particle.mode = 1;
    particle.duration = 20;
    particle.period = 12;
    particle.red = 255;
    particle.green = 255;
    particle.blue = 255;
    particle.maximum = 255;
    motion.owner = arg0;
    particle.owner = arg0;
    particle.endRed = 255;
    particle.endGreen = 255;
    particle.endBlue = 255;
    particle.endAlpha = 255;
    particle.zero24 = 0;
    particle.zero28 = 0;
    particle.zero2C = 0;
    particle.field40 = 0;
    particle.field41 = 9;
    particle.field30 = 7;
    particle.field34 = 60;
    particle.field38 = 128;
    particle.field3C = 32;
    if (count--) {
        speedScale = D_800A6458;
        sizeScale = D_800A645C;
        motionScale = D_800A6460;
        do {
            motion.acceleration = (func_150ADA68() * 105.0f + 105.0f) * motionScale;
            motion.velocity = func_150ADA68() * 3008.0f * motionScale;
            motion.base = (func_150ADA68() * speedScale + D_800A6464) * sizeScale;
            particle.width = motion.base;
            particle.height = motion.base;
            motion.scale = (func_150ADA68() * D_800A6468 + 94.0f) * sizeScale;
            particle.x = func_150ADA68() * 200.0f + -100.0f;
            particle.y = func_150ADA68() * 148.0f + -100.0f;
            particle.texture = D_8008FD04[func_151D8E20()]();
            particle.lifetime = (func_150ADA20() % 51U) + 50;
            particle.alpha = (func_150ADA20() % 101U) + 100;
            if (func_150ADA20() & 1) particle.flags |= 2;
            if (func_150ADA20() & 1) particle.flags |= 4;
            result = func_1515548C(&particle, 2, 0, 0, 0x18, 255, 1);
            if (result != 0) {
                func_10022EC0((u8 *)result + 0x70, &motion, 0x18);
            }
        } while (count--);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515B674 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515B674.s")
extern f32 D_800BE9A4;

void func_1515AF90(s16 arg0);
void func_1515B5F4(s16 arg0);
void func_1515B674(s16 arg0);

s32 func_1515B994(void *arg0) {
    typedef struct {
        u8 pad0[0x14];
        f32 x;
        u8 pad18[4];
        f32 z;
        u8 pad20[0x54];
        f32 acceleration;
        f32 velocity;
        f32 base;
        f32 scale;
    } Motion;
    Motion *motion = arg0;
    f32 previous;

    previous = motion->velocity;
    motion->x += previous * D_800BE9A4 + 0.5f * motion->acceleration * D_800BE9A4;
    motion->velocity = motion->velocity + motion->acceleration * D_800BE9A4;
    motion->z = motion->base + motion->scale * (motion->velocity + previous) * 0.5f;
    return 1;
}
void func_1515BA10(s32 arg0) {

}
void func_1515BA1C(s16 arg0) {
    func_1515AF90(arg0);
}
void func_1515BA48(s32 arg0) {

}
void func_1515BA54(s16 arg0) {
    func_1515B674(arg0);
}
void func_1515BA80(s16 arg0) {
    func_1515B5F4(arg0);
}
void func_1515BAAC(s16 arg0) {
    func_1515B5F4(arg0);
}
