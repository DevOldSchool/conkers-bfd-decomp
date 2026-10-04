#include "types.h"

/*
 * Reviewed source unit: src/game/effects/effects_sfx_w1_bee_cavern.c
 * Boundary evidence: docs/evidence/game_beta_camera_rope_bee.md
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

void func_10022EC0(void *, void *, s32); /* extern */
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */

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

void func_1516972C(void *);

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
            *(volatile u8 *)((u8 *)arg0 + 0x73) = *(u8 *)((u8 *)arg0 + 0x73) | 3;
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sfx_w1_bee_cavern/func_150BE494.s")
