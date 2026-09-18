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
 * - func_151C96DC
 * - func_151C9740
 * - func_151C9B30
 * - func_151C9BA0
 * - func_151C9DE8
 * - func_151C9ED4
 * - func_151C9F38
 * - func_151CA6A0
 * - func_151CAACC
 * - func_151CAB78
 * - func_151CAD28
 * - func_151CB110
 * - func_151CB510
 * - func_151CB5FC
 * - func_151CB918
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C87E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C899C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C8FCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9198.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C94D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C95D8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C96DC CURRENT (120) */
s32 func_151C96DC(void *arg0, s32 arg1) {
    u8 *temp_v0;
    s32 temp_t6;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x170);
    temp_t6 = *(u8 *)(temp_v0 + 0x196);
    temp_v0 += 0x110;
    if (temp_t6 & 2) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C96DC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C96DC.s")
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C9B30 CURRENT (100) */
s32 func_151C9B30(void *arg0) {
    s32 var_v0;
    s32 temp_t7;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    var_v0 = 1;
    temp_t7 = 1;
    temp_v0 = *(void **)((u8 *)arg0 + 0x18);
    if (*(u8 *)((u8 *)temp_v0 + 0x6F) == 0) {
        temp_v1_2 = *(void **)((u8 *)arg0 + 0x14);
        *(u8 *)((u8 *)temp_v1_2 + 9) = 0;
    } else {
        temp_v1 = *(void **)((u8 *)arg0 + 0x14);
        *(u8 *)((u8 *)temp_v1 + 9) = temp_t7;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C9B30 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9B30.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CAACC.s")
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

void func_1516972C(void *);

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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB510.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB5FC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CB918 CURRENT (215) */
void func_151CB918(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x70);
    if (((arg2 & 0xFF) == 0x37) && (*(u8 *)((u8 *)arg1 + 0) == *(u8 *)((u8 *)temp_v0 + 0xE)) && (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)((u8 *)arg0 + 0x70))) {
        *(f32 *)((u8 *)temp_v0 + 0x10) = 0.0f;
        *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) (*(u8 *)((u8 *)temp_v0 + 0xC) | 1);
        *(f32 *)((u8 *)temp_v0 + 0x14) = 0.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CB918 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB918.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
extern f32 D_800AAEAC;
extern f32 D_800AAEB0;
extern f32 D_800AAEB4;
extern f32 D_800BE9A4;
f32 func_151CC1D4(void);

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

f32 func_151CC1D4(void);

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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC1D4.s")
void func_151CC290(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    func_1515572C(&sp1C, 0x46, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC2BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC524.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC77C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC840.s")
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
f32 func_151CC1D4();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CD224 CURRENT (281) */
void func_151CD224(u8 *arg0) {
    u8 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x70);
    temp_v1 = *(u8 *)((u8 *)temp_v0 + 0xD);
    {
        f32 temp_fv1 = (1.0f - ((func_151CC1D4() - *(f32 *)((u8 *)temp_v0 + 0x18)) * *(f32 *)((u8 *)temp_v0 + 0x20))) * 75.0f;
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
