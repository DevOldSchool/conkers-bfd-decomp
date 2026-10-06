#include "types.h"

/*
 * Reviewed source unit: src/game/game_3DF10.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15010A60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct { f32 x, y, z; } Game3DF10Vec;
typedef struct {
    f32 scale[10];
    Game3DF10Vec position;
    f32 motion[7];
    u32 flags;
    s16 life, resource;
    u8 mode, pad59[3];
    void *surface;
    u8 values[12];
    s32 word6C;
    u8 byte70, pad71;
    s16 half72, half74;
    u8 pad76[6];
} Game3DF10Particle;
typedef struct {
    u8 mode, kind, count, pad03;
    s16 life;
    u8 pad06[0x2A];
    s32 resource, model;
    u8 byte38, pad39[3];
} Game3DF10Model;
typedef struct { f32 values[6]; Game3DF10Vec position; f32 zero[2]; } Game3DF10Motion;
typedef struct { u8 kind, mode; s16 life; u8 flags, pad05; } Game3DF10Light;
void *func_10022EC0(void *, const void *, u32);
u32 func_10024770(void);
u32 func_150ADA20(void);
void func_150E8854(void);
void func_1510F800(void);
void *func_1510FD20(s32, s32);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
void *func_1513B5E0(s8 *, u8, s32, u8, s32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern Game3DF10Vec D_80096450[];
extern u8 D_80096498[], D_8009649E[];
extern f32 D_800964A0, D_800964A4, D_800964A8, D_800964AC, D_800964B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15010A60 CURRENT (5702) */
void func_15010A60(void) {
    Game3DF10Particle particle;
    Game3DF10Model model;
    Game3DF10Motion motion;
    f32 values[6];
    Game3DF10Light light;
    s32 position[3];
    void *owner;
    Game3DF10Vec point;
    Game3DF10Vec *entry;
    u8 *enabled;
    void *effect;
    s32 lightEffect;
    u32 ticks;
    f32 base, range, size, speed, randomScale;
    f32 value;

    func_150E8854();
    base = D_800964A0;
    range = D_800964A4;
    size = D_800964A8;
    model.kind = 3;
    model.count = 6;
    model.life = 300;
    model.resource = 9;
    speed = D_800964AC;
    model.mode = 0;
    model.model = 0x1AF;
    model.byte38 = 0;
    particle.flags = 0xD00;
    particle.life = 300;
    particle.resource = 0x56;
    particle.mode = 0;
    particle.values[0] = 255;
    particle.values[1] = 16;
    particle.values[2] = 0;
    particle.values[3] = 0;
    particle.values[4] = 0;
    particle.values[5] = 0;
    particle.values[6] = 0;
    particle.values[7] = 0;
    particle.values[8] = 2;
    particle.values[10] = 2;
    particle.word6C = 0;
    particle.byte70 = 0;
    particle.half72 = 1;
    particle.half74 = 255;
    enabled = D_80096498;
    entry = D_80096450;
    randomScale = D_800964B0;
    particle.scale[4] = 0.0f;
    particle.scale[5] = 0.0f;
    particle.scale[6] = 0.0f;
    particle.motion[0] = 0.0f;
    particle.motion[1] = 0.0f;
    particle.motion[2] = 0.0f;
    particle.motion[3] = 0.0f;
    particle.motion[4] = 0.0f;
    particle.motion[5] = 0.0f;
    particle.motion[6] = 0.0f;
    motion.zero[0] = 0.0f;
    motion.zero[1] = 0.0f;
    particle.scale[0] = 1.0f;
    particle.scale[1] = 1.0f;
    particle.scale[3] = 1.0f;
    particle.scale[2] = 1.0f;
    particle.scale[7] = 1.0f;
    particle.scale[8] = 1.0f;
    particle.scale[9] = 1.0f;
    do {
        point = *entry;
        particle.position = point;
        motion.position = point;
        func_1510F800();
        particle.surface = func_1510FD20((s32) particle.position.x, (s32) particle.position.z);
        ticks = func_10024770();
        value = 2.0f * ((f32) ((func_150ADA20() * ticks) & 0xFFFF) * randomScale) * speed;
        motion.values[0] = value;
        values[0] = value;
        ticks = func_10024770();
        value = 2.0f * ((f32) ((func_150ADA20() * ticks) & 0xFFFF) * randomScale) * speed;
        motion.values[1] = value;
        values[1] = value;
        ticks = func_10024770();
        value = (f32) ((func_150ADA20() * ticks) & 0xFFFF) * randomScale * size + 2.0f;
        motion.values[4] = value;
        values[4] = value;
        ticks = func_10024770();
        value = (f32) ((func_150ADA20() * ticks) & 0xFFFF) * randomScale * size + 2.0f;
        motion.values[5] = value;
        values[5] = value;
        ticks = func_10024770();
        value = (f32) ((func_150ADA20() * ticks) & 0xFFFF) * randomScale * range + base;
        motion.values[2] = value;
        values[2] = value;
        ticks = func_10024770();
        value = (f32) ((func_150ADA20() * ticks) & 0xFFFF) * randomScale * range + base;
        motion.values[3] = value;
        values[3] = value;
        owner = func_15132A4C(&particle, 3, 255, 0x18, 255, 1);
        if (owner != 0) {
            func_10022EC0((u8 *) owner + 0x170, values, 0x18);
        }
        if (*enabled != 0) {
            effect = func_1513B5E0((s8 *) &model, 0, 0x2C, 255, 1);
            if (effect != 0) {
                func_10022EC0((u8 *) effect + *(s32 *) ((u8 *) effect + 0x50) + 0xF8, &motion, 0x2C);
            }
            position[0] = (s32) entry->x;
            position[1] = (s32) entry->y;
            light.kind = 2;
            light.mode = 0x16;
            light.life = 300;
            light.flags = 0;
            position[2] = (s32) entry->z;
            lightEffect = func_151602C0((u8 *) &light, position, 12, 255, 255, 255, 255, 0, 4, 255, 1);
            if (lightEffect != 0) {
                func_10022EC0((u8 *) lightEffect + 0x18, &owner, 4);
            }
        }
        enabled++;
        entry++;
    } while (enabled != D_8009649E);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15010A60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3DF10/func_15010A60.s")
