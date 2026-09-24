#include "types.h"

/*
 * Reviewed source unit: src/game/effects/effects_sight.c
 * Boundary evidence: docs/evidence/game_beta_sight.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C71A0
 * - func_151C756C
 * - func_151C7E98
 * - func_151C82D0
 * - func_151C86AC
 * - func_151C87E0
 * - func_151C899C
 * - func_151C8FCC
 * - func_151C9198
 * - func_151C94D4
 * - func_151C95D8
 * - func_151C9740
 * - func_151C9BA0
 * - func_151C9DE8
 * - func_151C9ED4
 * - func_151C9F38
 * - func_151CA6A0
 * - func_151CAACC
 * - func_151CAB78
 * - func_151CAD28
 * - func_151CB110
 * - func_151CB5FC
 * - func_151CB970
 * - func_151CBBE0
 * - func_151CBC60
 * - func_151CC1D4
 * - func_151CC2BC
 * - func_151CC524
 * - func_151CC77C
 * - func_151CC840
 * - func_151CCD1C
 * - func_151CCF08
 * - func_151CD224
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C71A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C756C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C7E98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C82D0.s")
void func_151403A8(void **arg0, s32 arg1, void *arg2);

void func_151C8674(void *arg0, s32 arg1) {
    volatile s32 sp1C;
    void *sp18;

    if (arg0 != 0) {
        sp18 = arg0;
        sp1C = arg1;
        func_151403A8(&sp18, 0x20, arg0);
    }
}
s32 func_151C87E0(s32, void *, s32, void *);
void func_151C899C();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C86AC CURRENT (1931) */
void func_151C86AC(void *arg0, void *arg1, s32 arg2) {
    s32 temp_t6;
    u8 temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_t6 = arg2 & 0xFF;
    switch (temp_t6) {
    case 0x20:
        temp_v0 = (u8 *)arg0 + 0x110;
        if ((temp_v0[0x86] & 0x10) &&
            (*(s32 *)(temp_v0 + 0x28) == *(s32 *)((u8 *)arg1 + 4)) &&
            (func_151C87E0(*(s32 *)arg1, arg0, temp_t6, arg1) != 0)) {
            func_151C899C(*(s32 *)arg1, arg0);
        }
        return;
    case 0x3A:
        temp_v0_2 = (u8 *)arg0 + 0x110;
        if (*(s32 *)((u8 *)arg0 + 0x138) == *(s32 *)arg1) {
            temp_v1 = *((u8 *)arg1 + 4);
            switch (temp_v1) {
            case 0:
                temp_v0_2[0x86] |= 2;
                return;
            case 1:
                temp_v0_2[0x86] &= 0xFFFD;
                return;
            case 2:
                func_151C899C(0, arg0);
                break;
            }
        }
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C86AC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C86AC.s")
s32 func_151C87AC(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x18);
    if (!(*(u8 *)((u8 *)temp_v0 + 0x86) & 2)) {
        *arg6 = 0;
    }
    return 0;
}
extern u8 *D_800D1C90[];
void func_1507C3E0(void *, s16 *, s16 *, s16 *);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
s32 func_151451F0(void *, void *, s32, f32, f32, s32, s32, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C87E0 CURRENT (5482) */
s32 func_151C87E0(s32 arg0, void *arg1, s32 arg2, void *arg3) {
    struct {
        f32 inverse;
        u8 pad44[2];
        s16 sample3;
        s16 sample2;
        s16 sample;
        f32 output1;
        f32 output0;
        u8 pad54[0xC];
        u8 result60[0xC];
        f32 length;
        f32 direction[3];
        u8 pad7C[0xC];
        f32 clipped[3];
        u8 pad94[4];
        f32 start[3];
        u8 padA4[4];
        f32 radius;
    } local;
    u8 *actor;
    u8 *sight;
    f32 ratio;

    actor = (u8 *)arg0;
    sight = arg1;
    if ((actor[4] < 0xBB) && (actor[4] != 0xFF)) {
        local.radius = (f32)*(s16 *)(D_800D1C90[actor[4]] + 0x1A) * *(f32 *)(actor + 0x14C);
    } else {
        local.radius = 50.0f;
    }
    func_1507C3E0(actor, &local.sample, &local.sample2, &local.sample3);
    if ((f32)local.sample == 0.0f) {
        return 0;
    }
    ratio = local.radius / ((f32)local.sample * 0.5f);
    local.start[0] = *(f32 *)(actor + 0x14);
    local.start[1] = *(f32 *)(actor + 0x18) + ((f32)local.sample * 0.5f);
    local.start[2] = *(f32 *)(actor + 0x1C);
    local.clipped[0] = *(f32 *)(sight + 0x34);
    local.clipped[1] = ((*(f32 *)(sight + 0x38) - local.start[1]) * ratio) + local.start[1];
    local.clipped[2] = *(f32 *)(sight + 0x3C);
    local.direction[0] = *(f32 *)(sight + 0x40) - local.clipped[0];
    local.direction[1] = (((*(f32 *)(sight + 0x44) - local.start[1]) * ratio) + local.start[1]) - local.clipped[1];
    local.direction[2] = *(f32 *)(sight + 0x48) - local.clipped[2];
    if (func_15145128(local.direction, local.direction, &local.length, &local.inverse) == 0) {
        return 0;
    }
    if (func_151451F0(local.clipped, local.direction, (s32)local.start, local.radius, local.length,
                      (s32)local.result60, (s32)local.pad54, &local.output0, &local.output1) != 0) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C87E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C87E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C899C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C8FCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9198.s")
void func_1513CA6C(s32);
void func_1516972C(void *);
void func_1000FD38(void *, void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C94D4 CURRENT (20) */
void func_151C94D4(void *arg0) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a0_4;
    void *temp_a0_5;
    void *temp_a0_6;
    void *temp_a0_7;
    void *temp_a0_8;
    void *temp_s0;
    register void *temp_s0_2;

    temp_s0 = (u8 *)arg0 + 0x110;
    if (*(s32 *)((u8 *)arg0 + 0x13C) != 0) {
        func_1516972C(*(void **)((u8 *)temp_s0 + 0x2C));
        func_1000FD38((void *)func_151C87AC, temp_s0, 0);
    }
    temp_s0_2 = arg0;
    temp_a0 = *(void **)((u8 *)temp_s0_2 + 0x144);
    temp_s0_2 = (u8 *)temp_s0_2 + 0x110;
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
    temp_a0_2 = *(void **)((u8 *)temp_s0_2 + 0x38);
    if (temp_a0_2 != 0) {
        func_1516972C(temp_a0_2);
    }
    temp_a0_3 = *(void **)((u8 *)temp_s0_2 + 0x3C);
    if (temp_a0_3 != 0) {
        func_1516972C(temp_a0_3);
    }
    temp_a0_4 = *(void **)((u8 *)temp_s0_2 + 0x40);
    if (temp_a0_4 != 0) {
        func_1516972C(temp_a0_4);
    }
    temp_a0_5 = *(void **)((u8 *)temp_s0_2 + 0x44);
    if (temp_a0_5 != 0) {
        func_1516972C(temp_a0_5);
    }
    temp_a0_6 = *(void **)((u8 *)temp_s0_2 + 0x48);
    if (temp_a0_6 != 0) {
        func_1516972C(temp_a0_6);
    }
    temp_a0_7 = *(void **)((u8 *)temp_s0_2 + 0x4C);
    if (temp_a0_7 != 0) {
        func_1516972C(temp_a0_7);
    }
    temp_a0_8 = *(void **)((u8 *)temp_s0_2 + 0x50);
    if (temp_a0_8 != 0) {
        func_1516972C(temp_a0_8);
    }
    func_1513CA6C((s32)arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C94D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C94D4.s")
void func_1513CAA0(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C95D8 CURRENT (20) */
void func_151C95D8(void *arg0) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a0_4;
    void *temp_a0_5;
    void *temp_a0_6;
    void *temp_a0_7;
    void *temp_a0_8;
    void *temp_s0;
    void *temp_s0_2;

    temp_s0 = (u8 *)arg0 + 0x110;
    if (*(s32 *)((u8 *)arg0 + 0x13C) != 0) {
        func_1516972C(*(void **)((u8 *)temp_s0 + 0x2C));
        func_1000FD38((void *)func_151C87AC, temp_s0, 0);
    }
    temp_a0 = *(void **)((u8 *)arg0 + 0x144);
    temp_s0_2 = (u8 *)arg0 + 0x110;
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
    temp_a0_2 = *(void **)((u8 *)temp_s0_2 + 0x38);
    if (temp_a0_2 != 0) {
        func_1516972C(temp_a0_2);
    }
    temp_a0_3 = *(void **)((u8 *)temp_s0_2 + 0x3C);
    if (temp_a0_3 != 0) {
        func_1516972C(temp_a0_3);
    }
    temp_a0_4 = *(void **)((u8 *)temp_s0_2 + 0x40);
    if (temp_a0_4 != 0) {
        func_1516972C(temp_a0_4);
    }
    temp_a0_5 = *(void **)((u8 *)temp_s0_2 + 0x44);
    if (temp_a0_5 != 0) {
        func_1516972C(temp_a0_5);
    }
    temp_a0_6 = *(void **)((u8 *)temp_s0_2 + 0x48);
    if (temp_a0_6 != 0) {
        func_1516972C(temp_a0_6);
    }
    temp_a0_7 = *(void **)((u8 *)temp_s0_2 + 0x4C);
    if (temp_a0_7 != 0) {
        func_1516972C(temp_a0_7);
    }
    temp_a0_8 = *(void **)((u8 *)temp_s0_2 + 0x50);
    if (temp_a0_8 != 0) {
        func_1516972C(temp_a0_8);
    }
    func_1513CAA0((s32)arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C95D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C95D8.s")
s32 func_151C96DC(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x170);
    temp_v0 += 0x110;
    if (*(u8 *)(temp_v0 + 0x86) & 2) {
        return 1;
    }
    return 0;
}
void func_151C970C(s32 arg0, void *arg1) {
    struct {
        void *sp18;
        volatile s8 sp1C;
    } sp;

    sp.sp18 = arg1;
    sp.sp1C = (s8)arg0;
    func_151403A8(&sp.sp18, 0x3A, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9740.s")

typedef struct EffectsSightVec3f {
    f32 x;
    f32 y;
    f32 z;
} EffectsSightVec3f;

typedef struct EffectsSightTransform {
    u8 bytes[0x24];
} EffectsSightTransform;

typedef struct EffectsSightActor {
    u8 pad0[0x14];
    f32 x;
    u8 pad18[4];
    f32 z;
    u8 pad20[0x160];
    f32 y;
} EffectsSightActor;

void func_1504715C(EffectsSightTransform *, EffectsSightActor *);
void func_151ABE40(EffectsSightVec3f *, EffectsSightTransform *, s32, u8, s32);

void func_151C9AC0(EffectsSightActor *arg0, u8 arg1, s32 arg2) {
    EffectsSightVec3f position;
    EffectsSightTransform transform;

    position.x = arg0->x;
    position.y = arg0->y + 2.0f;
    position.z = arg0->z;
    func_1504715C(&transform, arg0);
    func_151ABE40(&position, &transform, 2, arg1, arg2);
}
s32 func_151C9B30(void *arg0) {
    void *temp_v0 = *(void **)((u8 *)arg0 + 0x18);

    if (*(u8 *)((u8 *)temp_v0 + 0x6F) == 0) {
        *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 9) = 0;
    } else {
        *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 9) = 1;
    }
    return 1;
}
s32 func_151C9B64(void *arg0, s8 *arg1) {
    s32 var_v0;
    s32 temp_t7;
    void *temp_v0;

    var_v0 = 1;
    temp_t7 = 1;
    temp_v0 = *(void **)((u8 *)arg0 + 0x188);
    if (*(u8 *)((u8 *)temp_v0 + 0x6F) == 0) {
        *arg1 = temp_t7;
    } else {
        *(s32 *)((u8 *)arg0 + 0x58) = *(s32 *)((u8 *)arg0 + 0x58) & ~2;
        *arg1 = 0;
    }
    return var_v0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9BA0.s")
void func_150BDE90(s32, u8, s32);
s32 func_151C9F38(s32, s32, s32, s8, s32);
s32 func_151CB5FC(s32, s32, s32, s8, s32);
s32 func_151CC524(s32, s32, s32, s32, s32, s32);
s32 func_151CC840(s32, s32, s32, s32, s32, s32);
s32 func_151CCF08(s32, s32, s8, s32);
extern s32 D_800BE9F0;
extern s8 D_8008CD00;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C9DE8 CURRENT (2019) */
void func_151C9DE8(s32 arg0, u8 arg1, s8 arg2, u8 arg3, s32 arg4) {
    func_151C9F38(arg0, 4, arg1, arg2, arg3);
    func_151CC524(arg0, 0, 0x32, 0xFF, arg1, arg3);
    func_151CC840(arg0, 0, 0x32, 0xFF, arg1, arg3);
    func_151CCF08(arg0, arg1, arg2, arg3);
    func_150BDE90(arg0, arg3, arg4);
    func_151CB5FC(arg0, 2, arg1, arg2, arg3);
    if (D_800BE9F0 == 0x27) {
        D_8008CD00 = 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C9DE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9DE8.s")
void func_15160274(void *, u8);
void func_1515572C();
void func_151A561C(void *, u8);
void func_151494E0(void *, u8);
extern s8 D_8008CD00;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C9ED4 CURRENT (1434) */
void func_151C9ED4(void *arg0) {
    void *sp24;

    sp24 = arg0;
    func_15160274(&sp24, 0x21);
    func_1515572C(&sp24, 0x21);
    func_151A561C(&sp24, 0x21);
    func_151494E0(&sp24, 0x21);
    D_8008CD00 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C9ED4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9ED4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9F38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CA6A0.s")
extern void func_1516972C(void *arg0);
extern void (*D_8008FC10[])(void *, void **, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CAACC CURRENT (1474) */
void func_151CAACC(void *arg0, void **arg1, u8 arg2) {
    u8 type;
    void (*callback)(void *, void **, u8);

    type = arg2;
    if (type == 0x21) {
        if (*(void **)((u8 *)arg0 + 0x70) == *arg1) {
            func_1516972C(arg0);
        }
    } else if ((type == 0) && (*(void **)((u8 *)arg0 + 0x70) == *(void **)((u8 *)*arg1 + 0x318))) {
        func_1516972C(arg0);
    }
    callback = D_8008FC10[*(u8 *)((u8 *)arg0 + 0x7D)];
    if (callback != 0) {
        callback(arg0, arg1, type);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CAACC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CAACC.s")
extern s32 D_80082FA0;
void *func_1515548C(void *, s32, s32, s32, s32, s32, s32);
void func_10022EC0(void *, void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CAB78 CURRENT (1557) */
void func_151CAB78(u8 *arg0, u8 arg1) {
    struct {
        f32 x;
        f32 y;
        f32 width;
        f32 height;
        u8 type;
        u8 pad11;
        s16 angle;
        s16 flags;
        s16 count;
        s16 color;
        u8 mode;
        u8 arg1;
        u8 arg2;
        u8 arg3;
        u8 time;
        u8 color0;
        u8 color1;
        u8 color2;
        u8 color3;
        u8 color4;
        s32 field24;
        s32 field28;
        s32 field2C;
        s32 field30;
        s32 field34;
        s32 field38;
        s32 field3C;
        u8 field40;
        u8 field41;
        u8 pad42[2];
        u8 field44;
        u8 pad45[0x13];
    } spawn;
    struct {
        u8 *owner;
        f32 zero;
        f32 scale;
        u8 bytes[2];
        u8 pad[0x4E];
    } payload;
    f32 multiplier;
    s32 mode;
    void *object;

    payload.owner = arg0;
    payload.zero = 0.0f;
    payload.bytes[1] = 0;
    payload.bytes[0] = 0;
    payload.scale = 130.0f;
    if (D_80082FA0 > 0) {
        multiplier = 2.0f;
    } else {
        multiplier = 1.0f;
    }
    spawn.type = 100;
    spawn.angle = 300;
    spawn.height = multiplier * 12.0f;
    spawn.width = spawn.height;
    spawn.color = 255;
    spawn.mode = 7;
    spawn.flags = (1 << (arg0[0x23D] + 11)) | 0x50;
    spawn.count = 1;
    spawn.arg1 = 255;
    spawn.arg2 = 200;
    spawn.time = 130;
    spawn.color0 = 255;
    spawn.color1 = 255;
    spawn.arg3 = 0;
    spawn.color2 = 255;
    spawn.color3 = 255;
    spawn.color4 = 255;
    spawn.field24 = 0;
    spawn.field28 = 0x200004;
    spawn.field2C = 0x1F0601;
    spawn.field30 = 8;
    spawn.field34 = 0x44;
    spawn.field38 = 0x80;
    spawn.field3C = 0x20;
    spawn.field40 = 0;
    spawn.field41 = 10;
    spawn.x = 0.0f;
    spawn.y = 0.0f;
    spawn.field44 = arg0[0x23D];
    mode = arg1 ? 4 : 0;
    object = func_1515548C(&spawn, mode & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (object != 0) {
        func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CAB78 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CAB78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CAD28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB110.s")
typedef struct SightActor {
    u8 pad0[0x318];
    void *field_318;
} SightActor;

typedef struct SightEffect {
    u8 pad0[0x18];
    SightActor *owner;
} SightEffect;

typedef struct SightMessage {
    SightActor *actor;
} SightMessage;

void func_151CB49C(SightEffect *arg0, SightMessage *arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (arg1->actor == arg0->owner) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        SightActor *actor = arg1->actor;

        if (actor->field_318 == arg0->owner) {
            func_1516972C(arg0);
        }
    }
}
extern f32 D_800AAEA8;

void func_151CB510(void *arg0) {
    f32 temp_fv1;
    f32 var_fv0;
    void *temp_v0;
    u8 *var_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x70);
    if ((**(u16 **)((u8 *)temp_v0 + 0x36C) & 0x2000) &&
        (var_v0 = (u8 *)arg0 + 0x70,
         (*(u16 *)(*(u8 **)((u8 *)temp_v0 + 0x3D4) + 0x19E) == 0))) {
        var_fv0 = *(f32 *)(var_v0 + 8);
    } else {
        var_fv0 = 0.0f;
        var_v0 = (u8 *)arg0 + 0x70;
    }
    temp_fv1 = *(f32 *)(var_v0 + 4);
    *(f32 *)(var_v0 + 4) += (var_fv0 - temp_fv1) * D_800AAEA8;
    *(s8 *)((u8 *)arg0 + 0x2E) = (s8)(u32)*(f32 *)(var_v0 + 4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB5FC.s")
void func_151CB918(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x70);
    if ((arg2 == 0x37) && (*(u8 *)((u8 *)arg1 + 0) == *(u8 *)((u8 *)temp_v0 + 0xE)) && (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0)) {
        *(f32 *)((u8 *)temp_v0 + 0x10) = 0.0f;
        *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) (*(u8 *)((u8 *)temp_v0 + 0xC) | 1);
        *(f32 *)((u8 *)temp_v0 + 0x14) = 0.0f;
    }
}
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
extern f32 D_800AAEAC;
extern f32 D_800AAEB0;
extern f32 D_800AAEB4;
extern f32 D_800BE9A4;
f32 func_151CC1D4(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CB970 CURRENT (677) */
s32 func_151CB970(u8 *arg0) {
    f32 sp28;
    void *sp1C;
    f32 temp_fa0;
    f32 temp_fv0;
    s8 temp_t2;
    f32 temp_fv1;
    u8 *temp_v1;

    temp_v1 = (void *)(arg0 + 0x70);
    temp_fv1 = (1.0f - ((func_151CC1D4() - *(f32 *)((u8 *)temp_v1 + 0x18)) * *(f32 *)((u8 *)temp_v1 + 0x20))) * 75.0f;
    if (*(u8 *)((u8 *)temp_v1 + 0xC) & 1) {
        sp28 = temp_fv1;
        sp1C = temp_v1;
        temp_fa0 = 91.0f + temp_fv1;
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) ((func_15047D60(*(f32 *)((u8 *)temp_v1 + 0x10)) * ((112.0f + temp_fv1) - temp_fa0)) + temp_fa0);
        *(f32 *)((u8 *)temp_v1 + 0x10) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x10) + (D_800AAEAC * D_800BE9A4));
        if (D_800AAEB0 <= *(f32 *)((u8 *)temp_v1 + 0x10)) {
            *(f32 *)((u8 *)arg0 + 0x14) = temp_fa0;
            *(u8 *)((u8 *)temp_v1 + 0xC) = (u8) (*(u8 *)((u8 *)temp_v1 + 0xC) & 0xFFFE);
        }
    } else {
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) (91.0f + temp_fv1);
    }
    if (*(u8 *)((u8 *)temp_v1 + 0xD) == 2) {
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) - 20.0f);
    }
    temp_t2 = (u32) *(f32 *)((u8 *)temp_v1 + 0x14) & 0xFF;
    if (*(u8 *)((u8 *)arg0 + 0x20) == 0x7C) {
        *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (0xFF - temp_t2);
    } else {
        *(s8 *)((u8 *)arg0 + 0x2E) = temp_t2;
    }
    temp_fv0 = *(f32 *)((u8 *)temp_v1 + 0x14);
    *(f32 *)((u8 *)temp_v1 + 0x14) = (f32) (temp_fv0 + ((255.0f - temp_fv0) * D_800AAEB4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CB970 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB970.s")
typedef struct SightEffect20 {
    u8 pad0[0x20];
    SightActor *owner;
} SightEffect20;

void func_151CBB6C(SightEffect20 *arg0, SightMessage *arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (arg1->actor == arg0->owner) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        SightActor *actor = arg1->actor;

        if (actor->field_318 == arg0->owner) {
            func_1516972C(arg0);
        }
    }
}
void func_1514373C(f32, f32, f32 *, f32 *);
extern f32 D_800AAEB8;

f32 func_151CC1D4(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CBBE0 CURRENT (340) */
s32 func_151CBBE0(u8 *arg0) {
    f32 temp_fv0;
    u8 *temp_v0;

    temp_fv0 = func_151CC1D4();
    temp_v0 = arg0 + 0x70;
    if (temp_fv0 != *(f32 *)(arg0 + 0x98)) {
        *(f32 *)(temp_v0 + 0x28) = temp_fv0;
        func_1514373C(*(f32 *)(temp_v0 + 0x24) +
                          ((temp_fv0 - *(f32 *)(temp_v0 + 0x18)) *
                           *(f32 *)(temp_v0 + 0x20) * D_800AAEB8),
                      55.0f, (f32 *)(arg0 + 0x10), (f32 *)(arg0 + 0x14));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CBBE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CBBE0.s")
extern f32 D_800AAEBC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CBC60 CURRENT (2370) */
s32 func_151CBC60(u8 *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    u8 *temp_v0;

    temp_fv0 = func_151CC1D4();
    temp_v0 = (void *)(arg0 + 0x70);
    if (temp_fv0 != *(f32 *)((u8 *)temp_v0 + 0x28)) {
        temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0x4C);
        *(f32 *)((u8 *)temp_v0 + 0x28) = temp_fv0;
        *(f32 *)((u8 *)arg0 + 0x1C) = (f32) ((temp_fv1 - ((temp_fv0 - *(f32 *)((u8 *)temp_v0 + 0x18)) * *(f32 *)((u8 *)temp_v0 + 0x20) * temp_fv1)) + 1.0f);
    }
    if (*(u8 *)((u8 *)temp_v0 + 0xC) & 2) {
        *(f32 *)((u8 *)temp_v0 + 0x50) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x50) - D_800BE9A4);
        temp_ft5 = *(f32 *)((u8 *)temp_v0 + 0x50);
        if (temp_ft5 <= 0.0f) {
            *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) *(f32 *)((u8 *)temp_v0 + 0x3C);
            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (u32) *(f32 *)((u8 *)temp_v0 + 0x40);
            *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (u32) *(f32 *)((u8 *)temp_v0 + 0x44);
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (u32) *(f32 *)((u8 *)temp_v0 + 0x48);
            *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) (*(u8 *)((u8 *)temp_v0 + 0xC) & 0xFFFD);
        } else {
            temp_fv0_2 = *(f32 *)((u8 *)temp_v0 + 0x3C);
            *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) (temp_fv0_2 + ((*(f32 *)((u8 *)temp_v0 + 0x2C) - temp_fv0_2) * (temp_ft5 * D_800AAEBC)));
            temp_fv1_2 = *(f32 *)((u8 *)temp_v0 + 0x40);
            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (u32) (temp_fv1_2 + ((*(f32 *)((u8 *)temp_v0 + 0x30) - temp_fv1_2) * (*(f32 *)((u8 *)temp_v0 + 0x50) * D_800AAEBC)));
            temp_fa0 = *(f32 *)((u8 *)temp_v0 + 0x44);
            *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (u32) (temp_fa0 + ((*(f32 *)((u8 *)temp_v0 + 0x34) - temp_fa0) * (*(f32 *)((u8 *)temp_v0 + 0x50) * D_800AAEBC)));
            temp_fa1 = *(f32 *)((u8 *)temp_v0 + 0x48);
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (u32) (temp_fa1 + ((*(f32 *)((u8 *)temp_v0 + 0x38) - temp_fa1) * (*(f32 *)((u8 *)temp_v0 + 0x50) * D_800AAEBC)));
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CBC60 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CBC60.s")
extern f32 D_800AAEC0;
extern s32 D_800C3958;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CC1D4 CURRENT (2315) */
f32 func_151CC1D4(void *arg0) {
    u8 *state;
    f32 lower;
    f32 upper;
    f32 value;
    void *object;

    state = (u8 *)arg0 + 0x70;
    lower = *(f32 *)(state + 0x18);
    upper = *(f32 *)(state + 0x1C);
    if (*(u8 *)((u8 *)arg0 + 0x7C) & 4) {
        value = lower + ((upper - lower) *
                         (*(f32 *)((u8 *)D_800C3958 +
                                   (*(s8 *)(state + 0x54) * 0x44) + 0x28) * D_800AAEC0));
    } else {
        object = *(void **)state;
        value = (*(f32 *)((u8 *)object + 0x19C) +
                 *(f32 *)((u8 *)object + 0x1A0)) * 0.5f;
    }
    if (value < lower) {
        value = lower;
    } else if (upper < value) {
        value = upper;
    }
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CC1D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC1D4.s")
void func_151CC290(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    func_1515572C(&sp1C, 0x46, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC2BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC524.s")
void func_15145974(void *, f32 *, f32 *);
extern f32 D_800AAED4;
extern f32 D_800AAED8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CC77C CURRENT (512) */
s32 func_151CC77C(void *arg0) {
    f32 sp24;
    f32 sp20;
    u8 *temp_a3;
    u8 *temp_v0;
    u8 *temp_v1;
    void *saved_arg0;

    saved_arg0 = arg0;
    temp_a3 = *(u8 **)((u8 *)arg0 + 0x70);
    temp_v1 = *(u8 **)(temp_a3 + 0x3D0);
    if (temp_v1 == 0) {
        return 0;
    }
    temp_v0 = *(u8 **)(temp_v1 + 0x31C);
    if (temp_v0 == 0) {
        return 0;
    }
    func_15145974(temp_v0 + 0x130, &sp24, &sp20);
    if (*(u8 *)((u8 *)saved_arg0 + 0x20) == 0x9A) {
        *(f32 *)((u8 *)saved_arg0 + 0x60) = 2.0f * -(sp24 * D_800AAED4 * 2560.0f);
        return 1;
    }
    *(f32 *)((u8 *)saved_arg0 + 0x64) = 2.0f * (sp20 * D_800AAED8 * 2560.0f);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CC77C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC77C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC840.s")
typedef struct SightEffectPayload {
    void *owner;
    f32 zero;
    f32 scale;
    u8 bytes[2];
    u8 pad[0x4E];
} SightEffectPayload;

typedef struct SightEffectSpawn {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
    u8 type;
    u8 pad11;
    s16 angle;
    s16 flags;
    s16 count;
    s16 color;
    u8 mode;
    u8 arg1;
    u8 arg2;
    u8 arg3;
    u8 time;
    u8 color0;
    u8 color1;
    u8 color2;
    u8 color3;
    u8 color4;
    s32 field24;
    s32 field28;
    s32 field2C;
    s32 field30;
    s32 field34;
    s32 field38;
    s32 field3C;
    u8 field40;
    u8 field41;
    u8 pad42[2];
    u8 field44;
    u8 pad45[3];
} SightEffectSpawn;

void *func_1515548C(void *, s32, s32, s32, s32, s32, s32);
void func_10022EC0(void *, void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CCD1C CURRENT (2834) */
void func_151CCD1C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    SightEffectSpawn spawn;
    SightEffectPayload payload;
    void *object;

    payload.zero = 0.0f;
    payload.bytes[1] = 0;
    payload.bytes[0] = 0;
    spawn.angle = 0x12C;
    payload.owner = arg0;
    payload.scale = 130.0f;
    spawn.flags = (1 << (*(u8 *)((u8 *)arg0 + 0x23D) + 0xB)) | 0x50;
    spawn.count = 1;
    spawn.arg1 = arg1;
    spawn.arg2 = arg2;
    spawn.mode = 7;
    spawn.time = 0xB4;
    spawn.color0 = 0xFF;
    spawn.color1 = 0xFF;
    spawn.color2 = 0xFF;
    spawn.arg3 = arg3;
    spawn.color = 0xFF;
    spawn.color3 = 0xFF;
    spawn.color4 = 0xFF;
    spawn.field24 = 0;
    spawn.field28 = 0x200004;
    spawn.field2C = 0x1F0601;
    spawn.field30 = 8;
    spawn.field34 = 0x44;
    spawn.field38 = 0x80;
    spawn.field3C = 0x20;
    spawn.field40 = 0;
    spawn.field41 = 0xA;
    spawn.x = 0.0f;
    spawn.y = 0.0f;
    spawn.type = 0xB4;
    spawn.width = 65.0f;
    spawn.height = 65.0f;
    spawn.field44 = *(u8 *)((u8 *)arg0 + 0x23D);
    object = func_1515548C(&spawn, 0, 0, 0, 0x58, 0xFF, 1);
    if (object != 0) {
        func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CCD1C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CCD1C.s")
typedef struct SightSpawnOwner {
    u8 pad0[0x23D];
    u8 type;
} SightSpawnOwner;

extern u8 D_800BE616;
s32 func_151A4FD0(s32, s32, s32, s32, s32, s32, s32, s32);
void func_10022EC0(void *, void *, s32);

void func_151CCE94(SightSpawnOwner *arg0) {
    s32 object;
    SightSpawnOwner *owner;

    if (D_800BE616 != 0) {
        owner = arg0;
        object = func_151A4FD0(0, 0, 0, 0xFF, 0, arg0->type, 1, 4);
        if (object != 0) {
            func_10022EC0((void *)(object + 0x20), &owner, sizeof(owner));
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CCF08.s")
f32 func_151CC1D4(void *);                          /* extern */

typedef struct SightUpdateFields {
    u8 pad0[0xD];
    u8 mode;
    u8 padE[0xA];
    f32 start;
    u8 pad1C[4];
    f32 scale;
} SightUpdateFields;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CD224 CURRENT (700) */
void func_151CD224(u8 *arg0) {
    u8 temp_v1;
    SightUpdateFields *state;
    f32 current;

    current = func_151CC1D4(arg0);
    state = (SightUpdateFields *)(arg0 + 0x70);
    {
        f32 temp_fv1 = (1.0f - ((current - state->start) * state->scale)) * 75.0f;
    temp_v1 = state->mode;
    if (temp_v1 == 5) {
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) (92.0f + temp_fv1);
        return;
    }
    if (temp_v1 == 4) {
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) (-92.0f - temp_fv1);
    }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CD224 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CD224.s")
