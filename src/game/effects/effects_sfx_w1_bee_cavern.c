#include "types.h"

/*
 * Reviewed source unit: src/game/effects/effects_sfx_w1_bee_cavern.c
 * Boundary evidence: docs/evidence/game_beta_camera_rope_bee.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BDF0C
 * - func_150BE1C4
 * - func_150BE210
 * - func_150BE2E8
 * - func_150BE438
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BE1C4 CURRENT (10) */
s32 func_150BE1C4(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + (*(f32 *)((u8 *)arg0 + 0x80) * D_800BE9A4));
    if (*(f32 *)((u8 *)arg0 + 0x14) > 120.0f) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BE1C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sfx_w1_bee_cavern/func_150BE1C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sfx_w1_bee_cavern/func_150BE210.s")
extern f32 D_800A0068;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BE2E8 CURRENT (7035) */
void func_150BE2E8(void *arg0) {
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fs1;

    temp_fa0 = (f32) *(s16 *)((u8 *)arg0 + 0x80);
    temp_fv1 = (f32) *(s16 *)((u8 *)arg0 + 0x7E);
    temp_fv0 = (f32) *(s16 *)((u8 *)arg0 + 0x7C);
    temp_fs0 = (f32) *(s16 *)((u8 *)arg0 + 0x3C) * 0.000061035156f;
    temp_fs0_2 = temp_fs0 - (temp_fs0 * D_800A0068);
    var_fs1 = ((f32) *(s16 *)((u8 *)arg0 + 0x3E) * 0.000061035156f) + (temp_fs0_2 * (f32) D_800BE9E4);
    *(s16 *)((u8 *)arg0 + 0x10) = (s16) (s32) ((((f32) *(s16 *)((u8 *)arg0 + 0x82) - temp_fv0) * var_fs1) + temp_fv0);
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((((f32) *(s16 *)((u8 *)arg0 + 0x84) - temp_fv1) * var_fs1) + temp_fv1);
    *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) ((((f32) *(s16 *)((u8 *)arg0 + 0x86) - temp_fa0) * var_fs1) + temp_fa0);
    if (var_fs1 > 1.0f) {
        var_fs1 = 1.0f;
    }
    *(s16 *)((u8 *)arg0 + 0x3C) = (s16) (s32) (temp_fs0_2 * 16384.0f);
    *(s16 *)((u8 *)arg0 + 0x3E) = (s16) (s32) (var_fs1 * 16384.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BE2E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sfx_w1_bee_cavern/func_150BE2E8.s")
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BE438 CURRENT (580) */
void *func_150BE438(void *arg0, s32 arg1) {
    u8 *temp_v1;

    *(s16 *)arg0 = 0x68;
    temp_v1 = (arg1 * 0x32C) + &D_800CC2D0;
    *(s16 *)((u8 *)arg0 + 4) = 0xE;
    *(s16 *)((u8 *)arg0 + 2) = *(s32 *)((u8 *)temp_v1 + 0x2E8);
    *(s16 *)((u8 *)arg0 + 6) = *(s32 *)((u8 *)temp_v1 + 0x2E4);
    return (u8 *)arg0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BE438 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sfx_w1_bee_cavern/func_150BE438.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sfx_w1_bee_cavern/func_150BE494.s")
