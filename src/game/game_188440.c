#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_188440.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_quad_actor_effect_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515AF90
 * - func_1515B21C
 * - func_1515B674
 * - func_1515B994
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515AF90.s")
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
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void *func_1515548C(void *, u8, s32, s32, s32, u8, s32);
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515B994 CURRENT (355) */
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
    f32 temp_fa1;
    f32 temp_fv1;

    temp_fv1 = motion->velocity;
    temp_fa1 = motion->acceleration;
    motion->x += (temp_fv1 * D_800BE9A4) + (0.5f * temp_fa1 * D_800BE9A4);
    motion->velocity = (f32) (temp_fv1 + (temp_fa1 * D_800BE9A4));
    motion->z = (f32) (motion->base + (motion->scale * (motion->velocity + temp_fv1) * 0.5f));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515B994 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515B994.s")
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
