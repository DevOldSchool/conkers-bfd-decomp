#include "types.h"

/*
 * Reviewed source unit: src/game/game_F5D80.c
 * Boundary evidence: docs/evidence/game_raw_radial_composite_effect.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C88D0
 * - func_150C8A68
 * - func_150C8DB8
 * - func_150C99B4
 * - func_150C9BDC
 * - func_150C9DC4
 * - func_150CA07C
 * - func_150CA150
 * - func_150CAA04
 * - func_150CADD0
 * - func_150CB008
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
f32 func_15047D60(f32);
f32 func_15047C00(f32);
void *func_15167A68(s32, s32, s32, s32, s32, s32);
extern f32 D_800A0528;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C88D0 CURRENT (2675) */
void *func_150C88D0(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    f32 angle;
    f32 zero;
    u8 *effect;
    s32 count;
    s32 index;
    s32 offset;
    s32 five;

    count = *(s32 *)(arg0 + 0x14);
    effect = func_15167A68(0x31, arg3, arg1 + (count * 8) + (count * 0xA0) + 0x408,
                           1, arg2, 1);
    five = 5;
    if (effect == 0) {
        return 0;
    }
    func_10022EC0(effect + 0x10, arg0, 0x30);
    *(u8 **)(effect + 0x360) = effect + 0x368;
    *(u8 **)(effect + 0x54) = effect + (*(s32 *)(arg0 + 0x14) * 8) + 0x368;
    zero = 0.0f;
    *(u8 **)(effect + 0x58) = effect + (*(s32 *)(arg0 + 0x14) * 8) + ((*(s32 *)(arg0 + 0x14) * five) * 0x10) + 0x3B8;
    *(f32 *)(effect + 0x40) = zero;
    *(f32 *)(effect + 0x44) = zero;
    *(u8 **)(effect + 0x364) = effect + (*(s32 *)(arg0 + 0x14) * 8) + ((*(s32 *)(arg0 + 0x14) * five) * 0x20) + 0x408;
    *(f32 *)(effect + 0x50) = zero;
    *(s16 *)(effect + 0x4C) = *(s16 *)(effect + 0x28);
    *(f32 *)(effect + 0x48) = D_800A0528 / (f32)*(s32 *)(effect + 0x24);
    angle = zero;
    index = 0;
    offset = 0;
    if (*(s32 *)(effect + 0x24) > 0) {
        do {
            *(f32 *)(*(u8 **)(effect + 0x360) + offset) = func_15047D60(angle);
            index++;
            *(f32 *)(*(u8 **)(effect + 0x360) + offset + 4) = func_15047C00(angle);
            offset += 8;
            angle += *(f32 *)(effect + 0x48);
        } while (index < *(s32 *)(effect + 0x24));
    }
    return effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C88D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C88D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C8A68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C8DB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C99B4.s")
typedef struct GameF5D80Actor {
    s32 active;
    u8 kind;
    u8 pad05[0xF];
    f32 x;
    u8 pad18[4];
    f32 z;
    u8 pad20[8];
    f32 radius;
    u8 pad2C[0x39];
    u8 enabled65;
    u8 pad66[0x14];
    u16 sound;
    u8 pad7C[0xD];
    u8 state89;
    u8 pad8A[0x9A];
    u8 owner, disabled;
    u8 pad126[0x16];
    u8 mode13C;
    u8 pad13D[0xDB];
    s32 counter218;
    u8 pad21C[0x16];
    u8 state232;
    u8 pad233[0xF9];
} GameF5D80Actor;
typedef struct GameF5D80Wave {
    u8 pad00[0x10];
    f32 x;
    u8 pad14[4];
    f32 z;
    u8 pad1C[0x28];
    f32 radius;
} GameF5D80Wave;
extern u8 D_800CC2D0[];
extern u8 D_800D121C[];
void func_1505D024(void *, s32, s32, s32);
f32 sqrtf(f32);
__pragma(1, sqrtf);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C9BDC CURRENT (1177) */
void func_150C9BDC(GameF5D80Wave *arg0, s32 arg1) {
    GameF5D80Actor *actor;
    f32 dx, dz, adjusted, distance, delta;
    s32 active;
    s32 kind;

    actor = (GameF5D80Actor *)D_800CC2D0;
    do {
        active = actor->active;
        if ((active != 0) && (actor->radius < 20.0f) &&
            (actor->disabled == 0) &&
            (((kind = actor->kind) == 0x53) || (active == 1))) {
            dx = actor->x - arg0->x;
            dz = actor->z - arg0->z;
            distance = sqrtf(dx * dx + dz * dz) - 100.0f;
            adjusted = distance;
            if ((kind == 0x53) && (actor->mode13C == 0)) {
                adjusted = distance - 150.0f;
            }
            delta = arg0->radius - adjusted;
            if ((delta >= 0.0f) && (delta < 250.0f)) {
                if (kind == 0x53) {
                    actor->state89 = 0xA;
                    actor->counter218 = 0;
                    actor->state232 = 0x13;
                    if (D_800CC2D0[actor->owner * 0x32C + 0x65] != 0) {
                        actor->state232 = 0x14;
                    }
                } else {
                    func_1505D024(actor, 0x6000E, actor->sound, -1);
                }
            }
        }
        actor++;
    } while (actor != (GameF5D80Actor *)D_800D121C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C9BDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C9BDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C9DC4.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CA07C CURRENT (120) */
s32 func_150CA07C(void *arg0) {
    f32 rate;
    f32 temp_fa0;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg0 + 0x38) += *(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4;
    rate = D_800BE9A4;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x48);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x5C);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + ((temp_fv1 * rate) + (temp_fa0 * rate * rate * 0.5f)));
    *(f32 *)((u8 *)arg0 + 0x40) += *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x48) = temp_fa0 * D_800BE9A4 + temp_fv1;
    *(f32 *)((u8 *)arg0 + 0x20) += *(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x24) += *(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x28) += *(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CA07C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CA07C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CA150.s")
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

void func_150CA930(void *arg0) {
    s16 sp3E;

    sp3E = (s16)((func_150ADA20() % 21U) + 0xA);
    func_1514C678(*(f32 *)((u8 *)arg0 + 0),
                  *(f32 *)((u8 *)arg0 + 4),
                  *(s32 *)((u8 *)arg0 + 8),
                  (func_150ADA68() * 59.0f) + 170.0f,
                  0, 0xFF, (s32)sp3E, 0x13, 0, 0.0f, 0, 0xFF);
}
s32 func_150CA9D0(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x28)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) temp_v1;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CAA04.s")
extern s32 D_800BE9E4;

s32 func_150CAC28(void *arg0, s32 arg1) {
    f32 *factor;
    s32 remaining;

    factor = (f32 *)((u8 *)arg0 + 0xA8);
    remaining = D_800BE9E4;
    while (remaining != 0) {
        *(f32 *)((u8 *)arg0 + 0x58) *= *factor;
        *(f32 *)((u8 *)arg0 + 0x60) *= *factor;
        remaining--;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CADD0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CB008 CURRENT (120) */
s32 func_150CB008(void *arg0) {
    f32 rate;
    f32 temp_fa0;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg0 + 0x38) += *(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4;
    rate = D_800BE9A4;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x48);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x5C);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + ((temp_fv1 * rate) + (temp_fa0 * rate * rate * 0.5f)));
    *(f32 *)((u8 *)arg0 + 0x40) += *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (temp_fv1 + (temp_fa0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x20) += *(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x24) += *(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x28) += *(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CB008 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CB008.s")
