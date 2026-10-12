#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/effects/effects_sfx_w1_bee_cavern.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_beta_camera_rope_bee.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BDF0C
 * - func_150BE494
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s32 value;
    s16 field4;
} BeeCavernEffectPacket;

void *func_10022EC0(void *, const void *, u32);

void func_150BDE90(s32 arg0, u8 arg1, s32 arg2) {
    BeeCavernEffectPacket packet;
    u8 *effect;

    packet.field4 = 0;
    packet.value = arg0;
    effect = func_15149130(0x12C, -1, 0x4F, -1, 0, 0x3C, 8, arg1, arg2);
    if (effect != 0) {
        func_10022EC0(effect + 0x28, &packet, sizeof(packet));
    }
}
typedef struct {
    f32 field0, field4, field8, fieldC;
    u8 field10, pad11;
    s16 field12;
    u16 field14, field16, field18;
    u8 field1A, field1B, field1C, field1D, field1E;
    u8 field1F, field20, field21, field22, field23;
    s32 field24, field28, field2C, field30, field34, field38, field3C;
    u8 field40, field41, pad42[2], field44, pad45[3];
    f32 field48, field4C, field50, field54;
} BeeCavernSpawn;

typedef struct {
    void *owner;
    u8 pad4[8];
    u8 fieldC, fieldD, padE[2];
    f32 field10;
    u8 tail14[0x44];
} BeeCavernPayload;

s32 func_150ADA20(void);
f32 func_150ADA68(void);
u8 *func_1515548C(void *, u8, s32 *, s32, s32, u8, s32);
extern f32 D_800A0000, D_800A0004;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BDF0C CURRENT (630) */
void func_150BDF0C(u8 *arg0) {
    f32 product;
    BeeCavernSpawn spawn;
    u8 *effect;
    BeeCavernPayload payload;
    BeeCavernEffectPacket *state;

    *(s16 *)(arg0 + 0x2C) -= D_800BE9E4;
    if (*(s16 *)(arg0 + 0x2C) < 0) {
        product = func_150ADA68() * 270.0f;
        spawn.field0 = product + -135.0f;
        spawn.field4 = -120.0f;
        spawn.field8 = func_150ADA68() * 10.0f + 3.0f;
        spawn.fieldC = func_150ADA68() * 17.0f + 9.0f;
        spawn.field10 = 0xAB;
        spawn.field12 = 1000;
        spawn.field14 = 0x31;
        spawn.field16 = 1;
        spawn.field18 = 0xFF;
        spawn.field1A = 7;
        spawn.field1B = 0xFF;
        spawn.field1C = 0xFF;
        spawn.field1D = 0xFF;
        spawn.field1E = (u32)func_150ADA20() % 156U + 100;
        spawn.field1F = 0xFF;
        spawn.field20 = 0xFF;
        spawn.field21 = 0xFF;
        spawn.field22 = 0xFF;
        spawn.field23 = 0xFF;
        spawn.field24 = 0;
        spawn.field28 = 0x200004;
        spawn.field2C = 0x1F0601;
        spawn.field30 = 3;
        spawn.field34 = 0x22;
        spawn.field38 = 0x80;
        spawn.field3C = 0x20;
        spawn.field40 = 0;
        spawn.field41 = 7;
        state = (BeeCavernEffectPacket *)((s32)arg0 + 0x28);
        spawn.field44 = ((u8 *)state->value)[0x23D];
        spawn.field48 = 1.0f;
        spawn.field4C = 1.0f;
        spawn.field50 = 0.0f;
        spawn.field54 = 0.0f;
        payload.owner = (void *)state->value;
        payload.fieldD = 0;
        payload.fieldC = 0;
        payload.field10 = func_150ADA68() * D_800A0000 + D_800A0004;
        effect = func_1515548C(&spawn, 10, 0, 0, 0x58, arg0[0xC], 0);
        if (effect != 0) {
            func_10022EC0(effect + 0x70, &payload, 0x58);
        }
        state->field4 = (u32)func_150ADA20() % 151U + 25;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BDF0C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sfx_w1_bee_cavern/func_150BDF0C.s")

typedef struct BeeCavernActor {
    u8 pad0[0x318];
    void *field_318;
} BeeCavernActor;

typedef struct BeeCavernEffect {
    u8 pad0[0x28];
    BeeCavernActor *field_28;
} BeeCavernEffect;

typedef struct BeeCavernMessage {
    BeeCavernActor *actor;
} BeeCavernMessage;

void func_150BE150(BeeCavernEffect *arg0, BeeCavernMessage *arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (arg1->actor == arg0->field_28) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        BeeCavernActor *actor = arg1->actor;

        if (actor->field_318 == arg0->field_28) {
            func_1516972C(arg0);
        }
    }
}
extern f32 D_800BE9A4;

s32 func_150BE1C4(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) ((*(f32 *)((u8 *)arg0 + 0x80) * D_800BE9A4) + *(f32 *)((u8 *)arg0 + 0x14));
    if (*(f32 *)((u8 *)arg0 + 0x14) > 120.0f) {
        return 0;
    }
    return 1;
}
void func_1511650C(void *, s32, s32, f32);
void func_100111C8(u16);

void func_150BE210(void *arg0) {

    if ((*(u8 *)((u8 *)arg0 + 0x73) & 3) != 3) {
        func_1511650C(arg0, 1, 0x62C, 500.0f);
        if (*(u8 *)((u8 *)arg0 + 0x4F) & 4) {
            *(f32 *)((u8 *)arg0 + 0x84) += *(f32 *)((u8 *)arg0 + 0x64);
        } else if (*(f32 *)((u8 *)arg0 + 0x84) > 270.0f) {
            *(f32 *)((u8 *)arg0 + 0x84) = 270.0f;
        }
        if (*(f32 *)((u8 *)arg0 + 0x84) > 360.0f) {
            *(u8 *)((u8 *)arg0 + 0x73) &= 0xFFFC;
            *(u8 *)((u8 *)arg0 + 0x73) |= 3;
            *(f32 *)((u8 *)arg0 + 0x64) = 0.0f;
            func_100111C8(*(u16 *)((u8 *)arg0 + 0x74));
            *(u16 *)((u8 *)arg0 + 0x74) = 0;
        }
    }
}
extern f32 D_800A0068;
extern s32 D_800BE9E4;

void func_150BE2E8(void *arg0) {
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fs1;
    f32 dest_x;
    f32 dest_y;
    f32 dest_z;

    temp_fv0 = (f32) *(s16 *)((u8 *)arg0 + 0x7C);
    temp_fv1 = (f32) *(s16 *)((u8 *)arg0 + 0x7E);
    temp_fa0 = (f32) *(s16 *)((u8 *)arg0 + 0x80);
    dest_x = (f32) *(s16 *)((u8 *)arg0 + 0x82);
    dest_y = (f32) *(s16 *)((u8 *)arg0 + 0x84);
    dest_z = (f32) *(s16 *)((u8 *)arg0 + 0x86);
    temp_fs0 = (f32) *(s16 *)((u8 *)arg0 + 0x3C) * 0.000061035156f;
    var_fs1 = (f32) *(s16 *)((u8 *)arg0 + 0x3E) * 0.000061035156f;
    temp_fs0 -= temp_fs0 * D_800A0068;
    var_fs1 += temp_fs0 * (f32) D_800BE9E4;
    *(s16 *)((u8 *)arg0 + 0x10) = (s16) (s32) (((dest_x - temp_fv0) * var_fs1) + temp_fv0);
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) (((dest_y - temp_fv1) * var_fs1) + temp_fv1);
    *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) (((dest_z - temp_fa0) * var_fs1) + temp_fa0);
    if (var_fs1 > 1.0f) {
        var_fs1 = 1.0;
    }
    *(s16 *)((u8 *)arg0 + 0x3C) = (s16) (s32) (temp_fs0 * 16384.0f);
    *(s16 *)((u8 *)arg0 + 0x3E) = (s16) (s32) (var_fs1 * 16384.0f);
}
extern u8 D_800CC2D0;

void *func_150BE438(void *arg0, s32 arg1) {
    u8 *temp_v1;

    *(s16 *)arg0 = 0x68;
    temp_v1 = (arg1 * 0x32C) + &D_800CC2D0;
    *(s16 *)((u8 *)arg0 + 2) = *(s32 *)((u8 *)temp_v1 + 0x2E8);
    *(s16 *)((u8 *)arg0 + 4) = 0xE;
    *(s16 *)((u8 *)arg0 + 6) = *(s32 *)((u8 *)temp_v1 + 0x2E4);
    return (u8 *)arg0 + 8;
}
typedef struct BeeCavernBounds {
    u8 pad0[0x14C];
    f32 lower, upper;
} BeeCavernBounds;
typedef struct BeeCavernWords { s32 x, y, z; } BeeCavernWords;
typedef struct BeeCavernHit {
    f32 height;
    s16 vertices[9];
    u8 pad16[2];
    s32 field18;
    u8 field1C, field1D, pad1E[2];
    void *field20;
} BeeCavernHit;
typedef struct BeeCavernPrimary {
    s32 count, countRange;
    BeeCavernWords position;
    s16 yaw, yawRange, pitch, pitchRange;
    f32 speed, speedRange, field24, field28;
    s16 timer, timerRange;
    f32 radius, field34, field38, field3C;
    s8 kind;
    u8 pad41[3];
} BeeCavernPrimary;
typedef struct BeeCavernSecondary {
    s32 count, countRange;
    BeeCavernWords position;
    s16 yaw, yawRange, pitch, pitchRange;
    f32 speed, speedRange, field24, field28;
    s16 timer, timerRange;
    f32 field30, field34, field38;
} BeeCavernSecondary;
typedef struct BeeCavernParticles {
    BeeCavernWords position;
    f32 fieldC, field10, field14, field18, field1C, field20;
    s16 count, countRange, timer, timerRange;
    s16 field2C, field2E, field30, field32;
    s8 kind;
    u8 pad35[3];
    f32 field38;
    s16 field3C, field3E;
    s32 field40;
} BeeCavernParticles;
void func_1504715C(void *, void *);
void func_1515080C(void *, s32 *, f32 *, s32, void *, s32, u8, u8, s8, void *, f32, u8, u8, u8, s32);
void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
void func_15153F18(s16 *, void *, void *, s32, s32);
extern s32 D_800A0010[], D_800A0060[];
extern f32 D_800A0038[], D_800A0064[];
extern f32 D_800A006C, D_800A0070, D_800A0074, D_800A0078;
extern f32 D_800A007C, D_800A0080, D_800A0084, D_800A0088;
extern f32 D_800A008C, D_800A0090, D_800A0094, D_800A0098;
extern f32 D_800A009C, D_800A00A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BE494 CURRENT (3231) */
void func_150BE494(void *arg0, u8 arg1, s32 arg2) {
    BeeCavernWords position;
    f32 upper;
    f32 lower;
    f32 radius;
    BeeCavernHit hit;
    BeeCavernPrimary primary;
    BeeCavernSecondary secondary;
    BeeCavernParticles particles;
    struct { s16 yaw, yawRange, pitch, pitchRange; } angles;

    if (arg0 != NULL) {
        radius = (((BeeCavernBounds *)arg0)->lower + ((BeeCavernBounds *)arg0)->upper) * 0.5f;
        func_1515C244(arg0, &position, &upper, &lower);
        func_1504715C(&hit, arg0);
        primary.count = 10;
        primary.countRange = 0;
        primary.position = position;
        primary.speed = 13.0f;
        primary.speedRange = 9.0f;
        primary.field24 = D_800A006C;
        primary.yaw = 0;
        primary.yawRange = 0xFF;
        primary.pitch = -0x40;
        primary.pitchRange = 0x32;
        primary.timer = 0x4B;
        primary.timerRange = 0x28;
        primary.kind = 0xB;
        primary.field34 = 0.0f;
        primary.field28 = D_800A0070;
        primary.field38 = D_800A0074;
        primary.field3C = 1.0f;
        primary.radius = radius;
        func_1515080C(&primary, D_800A0010, D_800A0038, 10, NULL, 0, 0, 1, -1, &hit, 55.0f, 0, 0, arg1, arg2);
        secondary.count = 0x11;
        secondary.countRange = 9;
        secondary.position = position;
        secondary.speed = 14.0f;
        secondary.speedRange = 11.0f;
        secondary.yaw = 0;
        secondary.yawRange = 0xFF;
        secondary.pitch = -0x3F;
        secondary.pitchRange = 0x4B;
        secondary.timer = 0x28;
        secondary.timerRange = 0x14;
        secondary.field24 = D_800A0078;
        secondary.field28 = D_800A007C;
        secondary.field30 = D_800A0080;
        secondary.field34 = D_800A0084;
        secondary.field38 = D_800A0088;
        func_15152190(&secondary, D_800A0060, D_800A0064, 1, 10.0f, 0, arg1, arg2);
        particles.position = position;
        particles.fieldC = D_800A008C;
        particles.count = 4;
        particles.countRange = 3;
        angles.yawRange = 0xFF;
        angles.yaw = 0;
        angles.pitch = -0x2B;
        angles.pitchRange = 0x1A;
        particles.timer = 3;
        particles.timerRange = 3;
        particles.field2C = 0x1E;
        particles.field2E = 0x14;
        particles.field30 = 0x9B;
        particles.field32 = 0x64;
        particles.field3C = 0x10;
        particles.field3E = 0xF;
        particles.field40 = 0;
        particles.kind = 0;
        particles.field10 = D_800A0090;
        particles.field14 = D_800A0094;
        particles.field18 = D_800A0098;
        particles.field1C = D_800A009C;
        particles.field20 = D_800A00A0;
        particles.field38 = 0.5f;
        func_15153F18(&angles.yaw, &particles, &hit, (u8)arg1, arg2);
        particles.kind = 2;
        func_15153F18(&angles.yaw, &particles, &hit, (u8)arg1, arg2);
        particles.kind = 0xA;
        func_15153F18(&angles.yaw, &particles, &hit, (u8)arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BE494 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sfx_w1_bee_cavern/func_150BE494.s")
