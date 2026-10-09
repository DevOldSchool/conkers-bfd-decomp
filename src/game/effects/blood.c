#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/effects/blood.c
 * Boundary evidence: docs/evidence/boundaries/effects/effects_blood.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15134070
 * - func_151342BC
 * - func_151349D0
 * - func_15134E48
 * - func_15135480
 * - func_151356D4
 * - func_15135BF8
 * - func_15135DD0
 * - func_15136404
 * - func_15136698
 * - func_15136AE4
 * - func_15136C3C
 * - func_15136F50
 * - func_15137610
 * - func_1513783C
 * - func_15138120
 * - func_151382E0
 * - func_15138424
 * - func_151389A8
 * - func_15138C80
 * - func_15138E98
 * - func_15139578
 * - func_15139768
 * - func_15139D74
 * - func_1513A24C
 * - func_1513A48C
 * - func_1513A594
 * - func_1513A5E0
 * - func_1513A6E0
 * - func_1513ABB8
 * - func_1513B0F8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct BloodState {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[0xA];
    u8 unk28;
    u8 pad29[0x14];
    u8 field3D;
    u8 pad3E[0x6];
    u16 field44;
    u8 pad46[0xA];
    u8 field50;
    u8 pad51[0xF];
    s32 flags60;
    u8 pad64[0x10C];
    s32 unk170;
} BloodState;

void func_151BC5A4(BloodState *arg0, s32 arg1, u8 arg2);
void func_1513A5E0(s32 arg0, s32 arg1, s32 arg2);

enum {
    MODEL_CONKER = 0,
    MODEL_CONKER_VARIANT_1 = 1,
    MODEL_CONKER_VARIANT_2 = 2,
    MODEL_CONKER_VARIANT_3 = 3,
    MODEL_CONKER_VARIANT_4 = 4,
    MODEL_ROCKMAN = 16,
    MODEL_WEASEL_GUARD_TALL_VARIANT = 17,
    MODEL_WEASEL_GUARD_SHORT_SHIELD_VARIANT = 20,
    MODEL_UGA_BUGA_BLUE_HEADGEAR = 22,
    MODEL_TNT_IMP = 52,
    MODEL_ROCKMAN_BOW_TIE = 56,
    MODEL_WISE_GUY = 59,
    MODEL_ROBO_SPIDER = 71,
    MODEL_SHC_SOLDIER = 88,
    MODEL_TEDIZ = 90,
    MODEL_RODENT = 91,
    MODEL_TEDIZ_AMMUNITION_BELT = 95,
    MODEL_GREGG_THE_GRIM_REAPER_SCYTHE = 112,
    MODEL_TEDIZ_VARIANT_1 = 116,
    MODEL_TEDIZ_VARIANT_2 = 117,
    MODEL_TEDIZ_VARIANT_3 = 122,
    MODEL_SHC_SOLDIER_VARIANT = 128,
    MODEL_SHC_SOLDIER_DECORATED_UNIFORM = 135,
    MODEL_UGA_BUGA = 136,
    MODEL_SURF_PUNK_SUNGLASSES = 144,
    MODEL_ROCKWOMAN = 145,
    MODEL_CONKER_BLACK_OUTFIT = 150,
    MODEL_WEASEL_BLACK_HELMET_AND_UNIFORM = 152,
    MODEL_VILLAGER_BROWN_HAT = 156,
    MODEL_VILLAGER_STRIPED_BONNET = 157,
    MODEL_ZOMBIE_DARK_SUIT = 159,
    MODEL_ZOMBIE_PURPLE_DRESS = 160,
    MODEL_SHC_SOLDIER_DECORATED_UNIFORM_VARIANT = 176,
    MODEL_TEDIZ_BROAD_SHOULDERED_VARIANT = 177,
    MODEL_GREGG_THE_GRIM_REAPER_HOODED = 178,
    MODEL_GREGG_THE_GRIM_REAPER_WITHOUT_ROBE = 180,
};

/*
 * Descriptive role: actor_get_fragment_effect_profile_index.
 * Actor model byte +0x04 selects a shared 20-entry descriptor/fragment
 * profile, or 99 when unsupported. The profile indexes D_800A3FD8,
 * D_80089A20 and D_800A3F14; it is not a bank or model ID.
 */
extern f32 D_800BE9A4;
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15134070 CURRENT (2310) */
s32 func_15134070(void *arg0) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    switch ((s32) temp_v0) {                        /* irregular */
    case MODEL_SHC_SOLDIER_DECORATED_UNIFORM:
    case MODEL_SHC_SOLDIER_DECORATED_UNIFORM_VARIANT:
        return 0xE;
    case MODEL_TEDIZ_BROAD_SHOULDERED_VARIANT:
        return 0xF;
    case MODEL_GREGG_THE_GRIM_REAPER_WITHOUT_ROBE:
        return 0x10;
    case MODEL_GREGG_THE_GRIM_REAPER_SCYTHE:
    case MODEL_GREGG_THE_GRIM_REAPER_HOODED:
        return 0x11;
    case 0xAB:
        return 0x12;
    case MODEL_ROCKMAN:
    case MODEL_ROCKMAN_BOW_TIE:
    case MODEL_ROCKWOMAN:
        return 0xD;
    case MODEL_WEASEL_BLACK_HELMET_AND_UNIFORM:
        return 0xC;
    case MODEL_TNT_IMP:
        return 0xB;
    case MODEL_ROBO_SPIDER:
        return 0xA;
    case MODEL_WEASEL_GUARD_TALL_VARIANT:
    case MODEL_WEASEL_GUARD_SHORT_SHIELD_VARIANT:
    case MODEL_WISE_GUY:
        return 1;
    case MODEL_TEDIZ:
    case MODEL_TEDIZ_AMMUNITION_BELT:
    case MODEL_TEDIZ_VARIANT_1:
    case MODEL_TEDIZ_VARIANT_2:
    case MODEL_TEDIZ_VARIANT_3:
        return 2;
    case MODEL_SHC_SOLDIER:
    case MODEL_RODENT:
    case MODEL_SHC_SOLDIER_VARIANT:
        return 3;
    case MODEL_UGA_BUGA_BLUE_HEADGEAR:
    case MODEL_UGA_BUGA:
    case MODEL_SURF_PUNK_SUNGLASSES:
        return 4;
    case MODEL_VILLAGER_BROWN_HAT:
        return 5;
    case MODEL_VILLAGER_STRIPED_BONNET:
        return 6;
    case MODEL_CONKER_BLACK_OUTFIT:
        return 7;
    case MODEL_ZOMBIE_PURPLE_DRESS:
        return 8;
    case MODEL_ZOMBIE_DARK_SUIT:
        return 9;
    case 0x9A:
        return 0x13;
    case MODEL_CONKER:
    case MODEL_CONKER_VARIANT_1:
    case MODEL_CONKER_VARIANT_2:
    case MODEL_CONKER_VARIANT_3:
    case MODEL_CONKER_VARIANT_4:
        return 0;
    default:
        return 0x63;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15134070 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134070.s")
s32 func_1513416C(void *arg0) {
    short temp_v0;

    temp_v0 = *(short *)((char *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        *(char *)((char *)arg0 + 0x28) = (char)(temp_v0 * 8);
    }
    return 1;
}
void *func_15167A68(s32, s32, s32, s32, s32, s32);
void func_10022EC0(void *, void *, s32);
void func_15143134(f32 *, f32 *, s32);
void func_1516972C(void *);

void *func_1513418C(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    void *temp_v0;
    void *sp24;
    u8 *temp_v1;
    u8 temp_a0;
    void *temp_v0_2;
    f32 one;
    f32 denominator;
    f32 zero;

    temp_v0 = func_15167A68(0x28, arg3, arg1 + 0x58, 1, (s32)arg2, 1);
    if (temp_v0 == (void *)0) {
        return (void *)0;
    }
    sp24 = temp_v0;
    func_10022EC0((u8 *)sp24 + 0x10, (void *)arg0, 0x30);
    temp_a0 = *(u8 *)((u8 *)sp24 + 0x3A);
    if (temp_a0 & 2) {
        temp_v0_2 = *(void **)((u8 *)sp24 + 0x1C);
        if ((*(s32 *)temp_v0_2 == 0) ||
            (*(u8 *)((u8 *)sp24 + 0x18) != *(u8 *)((u8 *)temp_v0_2 + 0x3B))) {
            func_1516972C(sp24);
            return (void *)0;
        }
        temp_v1 = *(u8 **)((u8 *)temp_v0_2 + 0x1D4);
        if ((temp_v1 != 0) && ((*(u8 *)((u8 *)temp_v0_2 + 0x74) & 0xF) != 0xF)) {
            func_15143134((f32 *)((u8 *)sp24 + 0x24),
                          (f32 *)((u8 *)sp24 + 0x40),
                          (s32)((u8 (*)[0x40])temp_v1)[*(u8 *)((u8 *)sp24 + 0x20)]);
        } else {
            *(u8 *)((u8 *)sp24 + 0x3A) = temp_a0 | 8;
        }
    } else {
        *(u8 *)((u8 *)sp24 + 0x3A) = temp_a0 | 0x18;
    }
    *(f32 *)((u8 *)sp24 + 0x4C) = 1.0f / (*(f32 *)((u8 *)sp24 + 0x30) + *(f32 *)((u8 *)sp24 + 0x30));
    *(f32 *)((u8 *)sp24 + 0x50) = 0.0f;
    return sp24;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151342BC.s")
s32 func_151346D0(s32 arg0, void *arg1, s32 arg2) {
    *((unsigned char *)arg1 + 0x3A) =
        (unsigned char)(*((unsigned char *)arg1 + 0x3A) & 0xFFEF);
    return arg0;
}
void func_151346EC(void) {
    func_15169804();
}
void func_1513470C(void) {
    func_15169824();
}
extern void (*D_80089AAC[])(void);

void func_1513472C(BloodState *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field3D;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    }
    if (temp_v0 >= 0xA) {
        temp_v0 = 0;
    }
    D_80089AAC[temp_v0]();
}
extern void (*D_80089AD4[])(void);

void func_1513477C(BloodState *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field3D;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    }
    if (temp_v0 >= 0xA) {
        temp_v0 = 0;
    }
    D_80089AD4[temp_v0]();
}
typedef struct {
    u8 pad00[0x18];
    u8 field18;
    u8 pad19[3];
    s32 field1C;
    u8 pad20[0x1D];
    u8 field3D;
} Blood347CCState;

typedef struct {
    s32 field00;
    union {
        s32 word;
        u8 bytes[4];
    } field04;
    u8 field08;
    u8 field09;
} Blood347CCEvent;

void func_1516972C(void *);

void func_151347CC(Blood347CCState *arg0, Blood347CCEvent *arg1, u8 arg2) {
    s32 temp_v0;

    temp_v0 = arg2;
    if ((arg2 == 0) || (arg2 == 3)) {
        if ((arg1->field00 == arg0->field1C) ||
            (arg0->field18 == arg1->field04.bytes[0])) {
            func_1516972C(arg0);
        }
    } else if (temp_v0 == 0x11) {
        if ((arg0->field3D == 5) &&
            ((arg1->field00 == arg0->field1C) ||
             (arg0->field18 == arg1->field04.bytes[0]))) {
            func_1516972C(arg0);
        }
    } else if (temp_v0 == 0x16) {
        if ((s32)arg1 == arg0->field1C) {
            func_1516972C(arg0);
        }
    } else if (temp_v0 == 0x2D) {
        temp_v0 = arg1->field00;
        if (temp_v0 == arg0->field1C) {
            arg0->field1C = arg1->field04.word;
            arg0->field18 = arg1->field09;
            return;
        }
        if (arg0->field1C != arg1->field04.word) {
            return;
        }
        arg0->field1C = temp_v0;
        arg0->field18 = *((u8 *)arg1 + 8);
    }
}
void func_151348F0(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {

}
/* Call context: func_10022EC0: unique active declaration in the allowed source */
/* Call context: func_15167A68: unique active declaration in the allowed source */
void *func_15134908(void *, s32, u8, s32);

void *func_15134908(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    void *v0;
    f32 **pp;
    f32 f0;
    f32 f18;

    v0 = func_15167A68(0x2A, arg3, arg1 + 0x40, 1, arg2, 1);
    if (v0 == 0) {
        return 0;
    }
    *((u8 *)(((s32)arg0) + 0x16)) |= 2;
    func_10022EC0(((u8 *)v0) + 0x10, arg0, 0x1C);
    f0 = *((f32 *)(((u8 *)v0) + 0x1C));
    pp = (f32 **)(((u8 *)v0) + 0x10);
    f18 = 1.0f / (f0 + f0);
    *((f32 *)(((u8 *)v0) + 0x2C)) = *pp[0];
    *((f32 *)(((u8 *)v0) + 0x30)) = *pp[1];
    *((f32 *)(((u8 *)v0) + 0x34)) = *pp[2];
    *((f32 *)(((u8 *)v0) + 0x38)) = f18;
    *((f32 *)(((u8 *)v0) + 0x3C)) = 0.0f;
    return v0;
}
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} BloodTrailPosition;

typedef struct {
    u8 pad0[0x10];
    f32 *x;
    f32 *y;
    f32 *z;
    f32 radius;
    f32 rate;
    s16 lifetime;
    u8 flags;
    u8 emitter;
    u8 field28;
    s8 callback;
    u8 pad2A[2];
    BloodTrailPosition previous;
    f32 inverseDiameter;
    f32 accumulator;
} BloodTrail;

extern s32 (*D_80089B18[])(void *);
extern void (*D_80089AFC[])(f32, f32, f32, f32, f32, f32, void *);

extern s32 D_800BE9E4;
f32 func_150ADA68(void);
f32 sqrtf(f32);
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151349D0 CURRENT (2481) */
void func_151349D0(BloodTrail *trail) {
    f32 radius;
    BloodTrailPosition position;
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
    f32 diameter;
    f32 fraction;
    f32 randomX;
    f32 randomY;
    f32 randomZ;
    s32 value;

    position.x = *trail->x;
    position.y = *trail->y;
    position.z = *trail->z;
    if (trail->flags & 4) {
        value = trail->callback;
        if ((value != -1) && (D_80089B18[value](trail) == 0)) {
            func_1516972C(trail);
            return;
        }
    }
    value = trail->flags;
    if (value & 2) {
        trail->flags = value & ~2;
    } else {
        deltaX = trail->previous.x - position.x;
        deltaY = trail->previous.y - position.y;
        deltaZ = trail->previous.z - position.z;
        trail->accumulator += ((trail->inverseDiameter *
            sqrtf(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ)) + 1.0f) *
            D_800BE9A4 * trail->rate;
        if (trail->accumulator > 7.0f) {
            trail->accumulator = 7.0f;
        }
        if (trail->accumulator > 1.0f) {
            do {
                diameter = trail->radius + trail->radius;
                fraction = func_150ADA68();
                if (D_80089AFC[trail->emitter] != 0) {
                    randomX = func_150ADA68();
                    randomY = func_150ADA68();
                    randomZ = func_150ADA68();
                    radius = trail->radius;
                    D_80089AFC[trail->emitter](
                        (position.x + deltaX * fraction + radius) - randomX * diameter,
                        (position.y + deltaY * fraction + radius) - randomY * diameter,
                        (position.z + deltaZ * fraction + radius) - randomZ * diameter,
                        deltaX, deltaY, deltaZ, trail);
                }
                trail->accumulator -= 1.0f;
            } while (trail->accumulator > 1.0f);
        }
    }
    trail->previous = position;
    if (trail->flags & 1) {
        trail->lifetime -= D_800BE9E4;
        if (trail->lifetime < 0) {
            func_1516972C(trail);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151349D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151349D0.s")
void func_15134C98(BloodState *arg0, s32 arg1, u8 arg2) {
    if (arg0->unk28 == 1) {
        func_151BC5A4(arg0, arg1, arg2);
    }
}
void func_15134CD4(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {

}
extern f32 D_800A45B0;
extern s32 D_800BE9E4;

s32 func_15134CEC(void *arg0) {
    s32 temp_v1;

    temp_v1 = *(u8 *)((u8 *)arg0 + 0x2E);
    *(f32 *)((u8 *)arg0 + 0x70) = (f32) (*(f32 *)((u8 *)arg0 + 0x70) + (0.125f * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x74) = (f32) (*(f32 *)((u8 *)arg0 + 0x74) + (D_800A45B0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x14) += *(f32 *)((u8 *)arg0 + 0x70) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x1C) += *(f32 *)((u8 *)arg0 + 0x74) * D_800BE9A4;
    if (*(f32 *)((u8 *)arg0 + 0x14) > 130.0f) {
        return 0;
    }
    temp_v1 -= D_800BE9E4 * 2;
    if (temp_v1 < 0) {
        return 0;
    }
    *(u8 *)((u8 *)arg0 + 0x2E) = (u8) temp_v1;
    return 1;
}
/* Call context: func_10022EC0: unique active declaration in the allowed source */
/* Call context: func_15167A68: unique active declaration in the allowed source */
void * func_15167A68(s32, s32, s32, s32, s32, s32);
void *func_15134DAC(void *arg0, s32 arg1) {
    void *v1;
    void *v0;
    void *t8;
    s16 t9;
    f32 f0;

    v1 = func_15167A68(0x29, 0, arg1 + 0x80, 1, 0xFF, 1);
    if (v1 == 0) {
        return 0;
    }
    func_10022EC0((void *)((s32)v1 + 0x18), arg0, 0x3C);
    t8 = arg0;
    v0 = v1;
    f0 = 0.0f;
    t9 = ((((((((((*((s16 *)(((s32)t8) + 0x28))) & 0xFFFF) & 0xFFFF) & 0xFFFF) & 0xFFFF) & 0xFFFF) & 0xFFFF) & 0xFFFF) & 0xFFFF) & 0xFFFF);
    *((s16 *)(((s32)v0) + 0x54)) = -t9;
    *((s32 *)(((s32)v0) + 0x10)) = 1;
    *((s32 *)(((s32)v0) + 0x14)) = 0;
    *((f32 *)(((s32)v0) + 0x70)) = f0;
    *((f32 *)(((s32)v0) + 0x74)) = f0;
    *((f32 *)(((s32)v0) + 0x78)) = f0;
    return v0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134E48.s")
void func_151352EC(void) {
    func_15169804();
}
void func_1513530C(void) {
    func_15169824();
}
/* extern */
extern void (*D_80089B70[])(BloodState *);

void func_100111C8(u16 arg0);
void func_1513532C(struct102 *arg0) {
    void (**tbl)(struct102 *) = D_80089B70;
    s32 idx = *(u8 *)((s32)arg0 + 0x50);
    u16 tmp;

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 6) {
        idx = 0;
    }
    tmp = *(u16 *)((s32)arg0 + 0x44);
    if (tmp != 0) {
        func_100111C8(tmp);
        *(u16 *)((s32)arg0 + 0x44) = 0;
    }
    tbl[idx](arg0);
}
extern void (*D_80089B88[])(BloodState *);

void func_151353A8(struct102 *arg0) {
    void (**tbl)(struct102 *) = D_80089B88;
    s32 idx = *(u8 *)((s32)arg0 + 0x50);
    u16 tmp;

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 6) {
        idx = 0;
    }
    tmp = *(u16 *)((s32)arg0 + 0x44);
    if (tmp != 0) {
        func_100111C8(tmp);
        *(u16 *)((s32)arg0 + 0x44) = 0;
    }
    tbl[idx](arg0);
}
void func_15145EA4(s32 *, s32 *, s32, s32);

void func_15135424(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp20[2];
    s32 sp18[2];

    sp20[0] = arg1;
    sp20[1] = arg2;
    sp18[0] = arg3;
    sp18[1] = arg4;
    func_15145EA4(sp20, sp18, arg0, 2);
}
/* Call context: func_1513555C: unique active declaration in the allowed source */
/* Call context: func_1516972C: unique active declaration in the allowed source */
void func_1513555C(void *, void *, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15135480 CURRENT (1387) */
void func_15135480(void *arg0, void *arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_v1;
    u8 temp_t6;
    u8 temp_v0_2;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_v0 = *(s32 *)((u8 *)arg0 + 0x1C);
        if (temp_v1 == temp_v0) {
            *(s32 *)((u8 *)arg0 + 0x1C) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0x18) = (u8) *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == temp_v0) {
            *(s32 *)((u8 *)arg0 + 0x1C) = temp_v1;
            *(u8 *)((u8 *)arg0 + 0x18) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
    temp_v0_2 = *(u8 *)((u8 *)arg0 + 0x50);
    switch (temp_v0_2) {                            /* irregular */
    case 1:
        func_151355B8(arg0, arg1, (s32) temp_t6);
        return;
    case 2:
        func_1513555C(arg0, arg1, temp_t6);
        return;
    default:
        if ((temp_t6 == 0) && ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x1C)) || ((u8) *(s32 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x18)))) {
            func_1516972C(arg0);
        }
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15135480 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135480.s")
void func_1516972C(void *);

void func_1513555C(void *arg0, void *arg1, u8 arg2) {
    if (((arg2 == 0) || (arg2 == 0x12)) &&
        ((*(void **)arg1 == *(void **)((u8 *)arg0 + 0x1C)) ||
         (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x18)))) {
        func_1516972C(arg0);
    }
}
/* Call context: func_1516972C: unique active declaration in the allowed source */

void func_151355B8(struct102 *arg0, s32 *arg1, u8 arg2) {
    switch (arg2) {
    case 0:
        if ((arg1[0] == *(s32 *)((s32)arg0 + 0x1C)) ||
            (*(u8 *)((s32)arg1 + 4) == *(u8 *)((s32)arg0 + 0x18))) {
            func_1516972C(arg0);
        }
        break;
    case 3:
        if ((arg1[0] == *(s32 *)((s32)arg0 + 0x1C)) ||
            (*(u8 *)((s32)arg1 + 4) == *(u8 *)((s32)arg0 + 0x18))) {
            s32 *p = (s32 *)((s32)arg0 + 0x10);
            s32 t;
            *p &= ~1;
            t = *p;
            *p = t;
        }
        break;
    }
}
s32 func_15135658(f32 *arg0) {
    arg0[0x1D] = 1.0f;
    return 1;
}
s32 func_151422DC(s32, void *, s32, s32, s32, void *, s32);
extern u8 D_800A3FB4;
extern u8 D_800A3FBC;
extern f32 D_800A45B4;

f32 func_15135670(s32 arg0) {
    return (f32)func_151422DC(0, &D_800A3FB4, 0, 0x7D0, 0x3E8,
                             &D_800A3FBC, 0xB7A) * D_800A45B4;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151356D4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15135BF8 CURRENT (6876) */
s32 func_15135BF8(u8 *arg0) {
    f32 spC;
    f32 sp8;
    f32 temp_fa0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_ft3;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_ft0;
    s32 var_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v1 = 1;
    if (*(s16 *)((u8 *)arg0 + 0x70) > 0) {
        temp_v0 = (void *)(arg0 + 0x70);
        *(s16 *)((u8 *)arg0 + 0x70) = (s16) (*(s16 *)((u8 *)arg0 + 0x70) - D_800BE9E4);
        *(f32 *)((u8 *)arg0 + 0x10) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) + (*(f32 *)((u8 *)temp_v0 + 8) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + (*(f32 *)((u8 *)temp_v0 + 0xC) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (*(f32 *)((u8 *)temp_v0 + 4) * D_800BE9A4));
        var_ft0 = *(f32 *)((u8 *)arg0 + 0x1C) + (*(f32 *)((u8 *)temp_v0 + 4) * D_800BE9A4);
    } else {
        temp_v0_2 = (void *)(arg0 + 0x70);
        *(f32 *)((u8 *)&sp8 + 0) = *(f32 *)((u8 *)temp_v0_2 + 8);
        *(f32 *)((u8 *)&sp8 + 4) = (f32) *(f32 *)((u8 *)temp_v0_2 + 0xC);
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + ((*(f32 *)((u8 *)temp_v0_2 + 0xC) * D_800BE9A4) + (*(f32 *)((u8 *)temp_v0_2 + 0x10) * D_800BE9A4 * D_800BE9A4 * 0.5f)));
        *(f32 *)((u8 *)temp_v0_2 + 0xC) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0xC) + (*(f32 *)((u8 *)temp_v0_2 + 0x10) * D_800BE9A4));
        temp_ft2 = sp8 + *(f32 *)((u8 *)temp_v0_2 + 8);
        sp8 = temp_ft2;
        temp_ft3 = temp_ft2 * 0.5f;
        temp_ft1 = spC + *(f32 *)((u8 *)temp_v0_2 + 0xC);
        spC = temp_ft1;
        sp8 = temp_ft3;
        spC = temp_ft1 * 0.5f;
        temp_fa0 = fabsf(temp_ft3) * *(f32 *)((u8 *)temp_v0_2 + 0x14);
        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (temp_fa0 * D_800BE9A4));
        var_ft0 = *(f32 *)((u8 *)arg0 + 0x1C) + (temp_fa0 * D_800BE9A4);
    }
    *(f32 *)((u8 *)arg0 + 0x1C) = var_ft0;
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x10);
    if ((temp_fv0 > 200.0f) || (temp_fv0 < -200.0f) || (temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x14), (temp_fv0_2 > 200.0f)) || (temp_fv0_2 < -200.0f)) {
        var_v1 = 0;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15135BF8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135BF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135DD0.s")
typedef struct Blood364Position {
    f32 x;
    f32 y;
    f32 z;
} Blood364Position;

typedef struct Blood364Actor {
    u8 unknown0[0x14];
    Blood364Position position;
} Blood364Actor;

typedef struct Blood364Hit {
    f32 height;
    s16 vertices[9];
    u8 unknown16[2];
    s32 handle;
    u8 flags;
    u8 type;
    u8 unknown1E[2];
    void *surface;
} Blood364Hit;

void func_1504715C(void *, void *);
void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);
s32 func_15046C80(f32 *, u16, f32, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800A460C;
extern f32 D_800A4610;
extern f32 D_800A4614;
extern f32 D_800A4618;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15136404 CURRENT (1329) */
void func_15136404(Blood364Actor *actor, f32 radius, volatile s32 kind, s32 mode) {
    Blood364Hit hit;
    Blood364Position probe;
    Blood364Position output;
    register f32 scale;
    register f32 count;
    register f32 cutoff;
    register u32 random;
    register u32 spread = 201;
    register s16 *vertices;
    register f32 *position;

    if (actor != 0) {
        scale = D_800A460C * radius * radius;
        count = ((func_150ADA68() * D_800A4610) + 108.0f) * D_800A4614 * scale;
        func_1504715C(&hit, actor);
        vertices = hit.vertices;
        position = &output.x;
        if (count > 1.0f) {
            cutoff = D_800A4618;
            do {
                random = func_150ADA20();
                func_15143874((s16)(random & 0xFF), func_150ADA68() * radius, &probe.x, &probe.z);
                probe.x += actor->position.x;
                probe.z += actor->position.z;
                probe.y = actor->position.y + 500.0f;
                if ((func_15046C80(&probe.x, 0, actor->position.y - cutoff, &hit) != 0) && (hit.type != 3)) {
                    output.x = probe.x;
                    output.y = hit.height;
                    output.z = probe.z;
                    scale = func_150ADA68();
                    random = func_150ADA20();
                    func_151D9B8C(0, (scale * 20.0f) + 10.0f, ((random % 101U) + 100) & 0xFF,
                        (s32)vertices, position, (func_150ADA20() % spread) + 400,
                        1, 1, 0, (u8)kind, mode);
                }
                count -= 1.0f;
            } while (count > 1.0f);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15136404 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136404.s")
typedef struct BloodVec3 {
    f32 x;
    f32 y;
    f32 z;
} BloodVec3;

typedef struct {
    s32 values[4];
} Blood36698Kinds;

typedef struct {
    u8 kind;
    u8 pad01;
    s16 mode;
    s16 lifetime;
    u8 pad06[2];
    s32 field08;
    s32 field0C;
    u8 color[4];
    f32 scale14;
    f32 scale18;
    BloodVec3 position;
    BloodVec3 velocity;
    BloodVec3 scale;
    s32 flags;
    u8 field44;
    u8 field45;
    u8 unknown46[0x12];
} Blood36698Descriptor;

extern Blood36698Kinds D_80089BAC;
u32 func_150ADA20(void);
void *func_1513D594(s32, s32, u8, u8, u8, u8, s16, f32, f32,
                    s32, s32, s32, s32, u8, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15136698 CURRENT (1952) */
void *func_15136698(f32 arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, void *arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10) {
    u8 *result;
    Blood36698Descriptor descriptor;
    f32 rate;
    Blood36698Kinds kinds;
    s32 option;
    s32 intensity;
    s32 mode;
    u32 random1;
    u32 random0;

    kinds = D_80089BAC;
    rate = arg1;
    descriptor.kind = kinds.values[func_150ADA20() & 3];
    if ((u8)arg7 != 0) {
        mode = 2;
    } else {
        mode = 1;
    }
    descriptor.mode = mode + 0x300;
    descriptor.field08 = 0;
    descriptor.field0C = 0;
    descriptor.color[0] = 0;
    descriptor.color[1] = 0;
    descriptor.color[2] = 0;
    descriptor.color[3] = 0xFF;
    descriptor.scale18 = arg0;
    descriptor.scale14 = arg0;
    descriptor.position = *(BloodVec3 *)arg6;
    descriptor.flags = 0;
    descriptor.scale.x = 1.0f;
    descriptor.scale.y = 1.0f;
    descriptor.scale.z = 1.0f;
    descriptor.velocity.x = 0.0f;
    descriptor.velocity.y = 0.0f;
    descriptor.velocity.z = 0.0f;
    if ((s16)arg4 == -1) {
        descriptor.lifetime = 0x12C;
    } else {
        descriptor.lifetime = (s16)arg4 + 0x20;
        descriptor.flags = 1;
    }
    descriptor.field44 = (u8)arg2;
    descriptor.field45 = (u8)arg3;
    if ((u8)arg8 != 0) {
        option = 3;
        intensity = 0xFF;
    } else {
        option = 0;
        intensity = 0;
    }
    random0 = func_150ADA20();
    random1 = func_150ADA20();
    result = func_1513D594((s32)&descriptor, 0, 0, 0x1A, 0,
                          (random1 & 1) + (random0 & 1),
                          func_150ADA20() & 0xFF, 500.0f, 500.0f, 0,
                          arg5, option, intensity, 0, 4, (u8)arg9, arg10);
    if (result != 0) {
        func_10022EC0(result + 0x128, &rate, 4);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15136698 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136698.s")

s32 func_151368A8(struct102 *arg0) {
    s16 tmp = *(s16 *)((s32)arg0 + 0x1C);
    f32 *ptr = (f32 *)((s32)arg0 + 0x128);

    if (tmp < 0x20) {
        s32 value = tmp * 8;
        if (value < *(u8 *)((s32)arg0 + 0x5C)) {
            *(u8 *)((s32)arg0 + 0x5C) = value;
        }
    }
    *(f32 *)((s32)arg0 + 0x2C) += *ptr * D_800BE9A4;
    *(f32 *)((s32)arg0 + 0x30) += *ptr * D_800BE9A4;
    return 1;
}
typedef struct {
    s32 field00;
    s16 field04;
    s8 field06;
    u8 pad07;
    s32 field08;
    s32 field0C;
    u8 bytes10[8];
    s32 field18;
    u8 tailPad[0xC];
} Blood6918Packet;

void *func_1513C73C(s32 *, s32, s32, void *, f32, f32, f32, f32,
                     f32, s32, s32, s32, s32, s32);

void func_15136918(f32 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4,
                   void *arg5, f32 *arg6, u8 arg7, s32 arg8) {
    Blood6918Packet packet;
    f32 *position;
    f32 scale;

    position = arg6;
    scale = arg0;
    packet.field06 = 0x55;
    packet.field00 = 0x300;
    packet.field08 = 0;
    packet.field0C = 0;
    packet.bytes10[0] = arg1;
    packet.bytes10[1] = arg2;
    packet.bytes10[2] = 0;
    packet.bytes10[3] = 0;
    packet.bytes10[4] = 0;
    packet.bytes10[5] = 0;
    packet.field18 = 0x280001;
    packet.bytes10[6] = 1;
    packet.bytes10[7] = 1;
    if (arg3 == -1) {
        packet.field04 = 0x12C;
    } else {
        packet.field00 = 0x301;
        packet.field04 = arg3 + 0x20;
    }
    func_1513C73C(&packet.field00, 0xD, 0, arg5, position[0], position[1],
                  position[2], scale, scale, arg4, 0, 0, arg7, arg8);
}
s32 func_15136A1C(BloodState *arg0) {
    s16 temp_v0 = arg0->unk1C;

    if (temp_v0 < 0x20) {
        s32 temp_v1 = temp_v0 * 8;
        if (temp_v1 < arg0->unk28) {
            arg0->unk28 = temp_v1;
        }
    }
    return 1;
}
/* Call context: func_15134908: unique active project prototype */
void *func_15134908(void *, s32, u8, s32);
extern f32 D_800A461C;
extern f32 D_800A4620;

void func_15136A50(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5) {
    struct {
        s32 x;
        s32 y;
        s32 z;
        f32 scale;
        f32 speed;
        s16 amount;
        s8 kind;
        s8 count;
        s8 mode;
        s8 sentinel;
    } packet;

    packet.x = arg0;
    packet.y = arg1;
    packet.z = arg2;
    packet.scale = D_800A461C;
    packet.speed = D_800A4620;
    packet.amount = arg3;
    packet.kind = 5;
    packet.count = 5;
    packet.mode = 2;
    packet.sentinel = -1;

    func_15134908(&packet.x, 0, arg4, arg5);
}
f32 func_150ADA68(void);
u32 func_150ADA20(void);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32,
                   f32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A4624;
extern f32 D_800A4628;
extern f32 D_800A462C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15136AE4 CURRENT (48) */
void func_15136AE4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, void *arg6) {
    f32 sp6C[3];
    f32 sp60[3];
    u32 sp54;
    u32 sp50;
    f32 sp4C;
    f32 temp_fv1;

    sp6C[0] = arg0;
    sp6C[1] = arg1;
    sp6C[2] = arg2;
    temp_fv1 = ((func_150ADA68() * 112.0f) + 247.0f) * D_800A4624;
    sp60[0] = -arg3 * temp_fv1;
    sp60[1] = -arg4 * temp_fv1;
    sp60[2] = -arg5 * temp_fv1;
    sp4C = func_150ADA68();
    sp50 = func_150ADA20();
    sp54 = func_150ADA20();
    func_151D9014(sp6C, sp60, 0, (sp4C * D_800A4628) + D_800A462C,
                   (sp50 & 0xF) + 0x19, (sp54 % 101U) + 0x9B,
                   (func_150ADA68() * 119.0f) + 129.0f, 0, 1.0f, 1.0f,
                   1, 0, 1, 0, *(u8 *)((u8 *)arg6 + 0xC),
                   *(u8 *)((u8 *)arg6 + 1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15136AE4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136AE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136C3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136F50.s")
typedef struct BloodImpactActor {
    u8 pad0[4];
    u8 kind;
    u8 pad5[0x6F];
    u8 flags74;
    u8 pad75[0x8F];
    u8 state104;
    u8 pad105[0x20];
    u8 state125;
    u8 pad126[0xA4];
    u8 count;
    u8 pad1CB[9];
    void *transforms;
} BloodImpactActor;

void func_151036B4(void *, u8, s32);
void func_15136F50(BloodVec3 *, BloodVec3 *, BloodVec3 *, u8, u8, s32);
void func_151C329C(void *, u8, s32);
void func_151C577C(BloodVec3 *, BloodVec3 *, BloodVec3 *, u8, u8, u8, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15137610 CURRENT (260) */
void func_15137610(BloodImpactActor *arg0, BloodVec3 *arg1, BloodVec3 *arg2,
                   BloodVec3 *arg3, u8 arg4, s32 arg5) {
    s32 mode;

    mode = 0;
    if (arg0 != 0) {
        if (arg0->transforms != 0 && (arg0->flags74 & 0xF) != 0xF &&
            (s32)arg0->count > 0) {
            mode = arg0->kind;
            switch (mode) {
                case 5:
                case 0xAD:
                case 0xAE:
                case 0xAF:
                    mode = 3;
                    break;
                case 0x5B:
                case 0x70:
                case 0xA6:
                case 0xB2:
                case 0xB4:
                    func_151036B4(arg1, arg4, arg5);
                    mode = 2;
                    break;
                case 0x28:
                case 0x77:
                case 0x8A:
                case 0x8C:
                    if ((func_150ADA20() & 1) == 0) {
                        mode = 2;
                        break;
                    }
                    return;
                case 0x42:
                    if ((func_150ADA20() & 3) == 0) {
                        mode = 2;
                        break;
                    }
                    return;
                case 0x5A:
                case 0x5F:
                case 0x74:
                case 0x75:
                case 0x7A:
                case 0x8D:
                case 0xB1:
                    mode = arg0->state125;
                    if (mode == 0xFF) {
                        if ((func_150ADA20() & 0x1F) == 0) {
                            mode = 1;
                            break;
                        }
                    } else if (mode == 0 && arg0->state104 == 0) {
                        mode = 1;
                        break;
                    }
                    return;
                default:
                    if (arg0->state125 == 0 && arg0->state104 == 0) {
                        mode = 0;
                    } else {
                        return;
                    }
                    break;
            }
        } else {
            return;
        }
    }
    switch (mode) {
        case 1:
            func_151C577C(arg1, arg2, arg3, 1, 1, 1, arg4, arg5);
            return;
        case 2:
            func_151C329C(arg1, arg4, arg5);
            return;
        case 3:
            func_15136F50(arg1, arg2, arg3, 1, arg4, arg5);
            return;
        default:
        case 0:
            func_15136F50(arg1, arg2, arg3, 0, arg4, arg5);
            return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15137610 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137610.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513783C.s")
s32 func_15145128(BloodVec3 *, BloodVec3 *, f32 *, f32 *);
s32 func_15146078(void *, void *, void *);

s32 func_15137C64(BloodVec3 *arg0, BloodVec3 *arg1, BloodVec3 *arg2,
                    s32 arg3, s32 arg4, BloodVec3 *arg5,
                    BloodVec3 *arg6, BloodVec3 *arg7) {
    f32 sp2C;
    f32 sp28;

    if (arg5 != 0 && arg6 != 0) {
        *arg0 = *arg5;
        *arg1 = *arg6;
    } else if (arg5 != 0) {
        *arg0 = *arg5;
        *arg1 = *arg5;
    } else if (arg6 != 0) {
        *arg0 = *arg6;
        *arg1 = *arg6;
    } else {
        return 0;
    }
    if (arg7 == 0) {
        arg2->x = arg1->x - arg0->x;
        arg2->y = arg1->y - arg0->y;
        arg2->z = arg1->z - arg0->z;
        if (func_15145128(arg2, arg2, &sp2C, &sp28) == 0) {
            return 0;
        }
    } else {
        *arg2 = *arg7;
    }
    if (func_15146078(arg2, (void *)arg3, (void *)arg4) == 0) {
        return 2;
    }
    return 1;
}
f32 func_150ADA68();                                /* extern */
extern f32 D_800A4828;

s32 func_15137E10(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x74) = (f32) (((func_150ADA68() * 50.0f) + 580.0f) * D_800A4828);
    return 1;
}
typedef struct BloodStruct259 { u8 pad0[0x74]; f32 unk74; } struct259;
void func_15137F30(f32 *, f32 *, f32 *, f32 *, f32, struct259 *, f32 *, f32 *,
                   f32 *, f32 *, s16 *, u8 *, f32 *);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32,
                   f32, s32, s32, s32, s32, s32, s32);

void func_15137E60(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4,
                   u8 *arg5) {
    f32 position[3];
    f32 direction[3];
    f32 vector[3];
    f32 value;
    s16 count;
    s8 alpha;
    f32 scale;

    func_15137F30(arg0, arg1, arg2, arg3, arg4, (struct259 *)arg5, position, direction,
                   vector, &value, &count, &alpha, &scale);
    func_151D9014(position, vector, 0, value, count, (u8)alpha, scale, 0,
                   1.0f, 1.0f, 1, 0, 1, 0, arg5[0xC], arg5[1]);
}
u32 func_150ADA20();                                /* extern */
extern f32 D_800A482C;

void func_15137F30(
    f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3,
    f32 arg4, struct259 *arg5,
    f32 *arg6, f32 *arg7, f32 *arg8,
    f32 *arg9, s16 *argA, u8 *argB, f32 *argC)

{
    arg6[0] = (arg2[0] * arg4) + arg0[0];
    arg6[1] = (arg2[1] * arg4) + arg0[1];
    arg6[2] = (arg2[2] * arg4) + arg0[2];
    arg7[0] = (arg3[0] * arg4) + arg1[0];
    arg7[1] = (arg3[1] * arg4) + arg1[1];
    arg7[2] = (arg3[2] * arg4) + arg1[2];
    arg8[0] = (arg7[0] - arg6[0]) * arg5->unk74;
    arg8[1] = (arg7[1] - arg6[1]) * arg5->unk74;
    arg8[2] = (arg7[2] - arg6[2]) * arg5->unk74;

    *arg9 = ((func_150ADA68() * 217.0f) + (-456.0f)) * D_800A482C;
    *argA = (func_150ADA20() % 31U) + 0x1E;
    *argB = (func_150ADA20() % 156U) + 0x64;
    *argC = (func_150ADA68() * 35.0f) + 40.0f;
}
typedef struct {
    u8 pad_0[0x74];
    u8 field_74;
    u8 pad_75[0x15F];
    u8 *field_1D4;
} Blood1380B4State;

typedef struct {
    f32 values[4];
} Blood1380B4Vector;

void func_15143134(f32 *, f32 *, s32);
extern Blood1380B4Vector D_800A3FD8[];

/*
 * Descriptive role: actor_transform_effect_profile_offset.
 * Transforms the profile's first three floats through actorMatrices +0x300.
 * Returns zero without writing outPosition when actor +0x1D4 is null or
 * (+0x74 & 0xF) is 0xF; otherwise returns one. The descriptor's fourth word
 * contains packed selector/variant data, not another offset component.
 */
s32 func_151380B4(Blood1380B4State *actor, s32 effectProfileIndex, f32 *outPosition) {
    u8 *actorMatrices;

    actorMatrices = actor->field_1D4;
    if (actorMatrices == 0) {
        return 0;
    }
    if ((actor->field_74 & 0xF) == 0xF) {
        return 0;
    }
    func_15143134(D_800A3FD8[effectProfileIndex].values, outPosition, (s32)(actorMatrices + 0x300));
    return 1;
}
extern u8 D_800A4058;
extern u8 D_800A4068;
extern u8 D_1000EBC4;
s32 func_1000FA64(s32, s16, s16, s16, s32, s32, s32, void *, s32, s32, s32, s32);
void *func_15134DAC(void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15138120 CURRENT (969) */
void func_15138120(Blood1380B4State *arg0, s32 arg1, s32 arg2) {
    struct {
        u8 color;
        u8 pad01[3];
        Blood1380B4State *owner;
        s8 type;
        u8 pad09[3];
        f32 values[6];
        s8 mode;
        u8 pad25;
        s16 width;
        s16 height;
        s16 alpha;
        s16 sound;
        s8 count;
        s8 amount;
        s8 loop;
        u8 pad31[3];
        f32 scale;
        s8 byte38;
        s8 byte39;
    } packet;
    Blood1380B4Vector *vector;
    u8 kind;

    vector = &D_800A3FD8[arg1];
    kind = ((u8 *)vector)[0xE];
    if (kind == 2) {
        return;
    }
    packet.owner = arg0;
    packet.color = arg0->pad_0[0x3B];
    if (arg2 & 0xFF) {
        packet.type = 0xC;
    } else {
        packet.type = 1;
    }
    packet.mode = 2;
    packet.width = 0x28;
    packet.height = 0x10;
    packet.values[0] = 0.0f;
    packet.values[1] = 0.0f;
    packet.values[2] = 0.0f;
    packet.values[3] = 0.0f;
    packet.values[5] = 0.0f;
    packet.values[4] = 20.0f;
    if ((u8 *)vector == &D_800A4058 || (u8 *)vector == &D_800A4068) {
        if (*(s32 *)((u8 *)arg0 + 0x94) & 0xE) {
            packet.alpha = 0x78;
        } else {
            packet.alpha = 0xF0;
        }
    } else {
        packet.alpha = 0x258;
    }
    packet.count = 5;
    if (kind == 0) {
        packet.amount = 5;
    } else {
        packet.amount = 6;
    }
    packet.loop = -1;
    packet.byte38 = 0;
    packet.byte39 = -1;
    packet.scale = 1.0f;
    packet.sound = (s16)func_1000FA64(0x4FE,
        (s16)(s32)*(f32 *)((u8 *)arg0 + 0x14),
        (s16)(s32)*(f32 *)((u8 *)arg0 + 0x18),
        (s16)(s32)*(f32 *)((u8 *)arg0 + 0x1C),
        0x5DC0, 0x258, 0x12C, &D_1000EBC4, 0x78, 0, 0, 0);
    func_15134DAC(&packet.color, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15138120 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138120.s")
typedef struct Blood382E0Position {
    s32 x;
    s32 y;
    s32 z;
} Blood382E0Position;

typedef struct Blood382E0Packet {
    s16 field_00;
    s16 field_02;
    s16 field_04;
    s16 field_06;
    Blood382E0Position position;
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    s16 field_2C;
    s16 field_2E;
    s16 field_30;
    s16 field_32;
    s16 field_34;
    s16 field_36;
    s16 field_38;
    s16 field_3A;
    u8 field_3C;
    u8 pad_3D[3];
    f32 field_40;
    s16 field_44;
    s16 field_46;
    s32 field_48;
} Blood382E0Packet;

void func_15153F18(s16 *, void *, s32, s32, s32);
extern u8 D_800A3FE6[];
extern f32 D_800A4830;
extern f32 D_800A4834;
extern f32 D_800A4838;
extern f32 D_800A483C;
extern f32 D_800A4840;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151382E0 CURRENT (1000) */
void func_151382E0(f32 *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4) {
    Blood382E0Packet packet;
    u8 kind;

    kind = D_800A3FE6[arg1 * 0x10];
    if (kind != 2) {
        packet.position = *(Blood382E0Position *)arg0;
        packet.field_14 = D_800A4830;
        packet.field_2C = 0x12;
        packet.field_2E = 7;
        packet.field_02 = 0xFF;
        packet.field_00 = 0;
        packet.field_04 = -0x3F;
        packet.field_06 = 0x4E;
        packet.field_30 = 3;
        packet.field_32 = 3;
        packet.field_34 = 0x14;
        packet.field_36 = 0x1E;
        packet.field_38 = 0x9B;
        packet.field_3A = 0x64;
        packet.field_44 = 0x10;
        packet.field_46 = 0xF;
        packet.field_48 = 0;
        packet.field_18 = D_800A4834;
        packet.field_1C = D_800A4838;
        packet.field_20 = D_800A483C;
        packet.field_24 = 4.0f;
        packet.field_28 = 9.0f;
        packet.field_40 = D_800A4840;
        if (kind == 1) {
            packet.field_3C = 1;
        } else {
            packet.field_3C = 0;
        }
        func_15153F18(&packet.field_00, &packet.position, (s32)arg2,
                       arg3, arg4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151382E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151382E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138424.s")
typedef struct Blood39578Particle {
    u8 pad0;
    u8 color;
    u8 pad2[0xA];
    u8 kind;
    u8 padD[3];
    f32 height;
    f32 bounce;
    f32 size0;
    f32 size1;
    u8 pad20[0x10];
    f32 mode;
    u8 pad34[4];
    BloodVec3 position;
    BloodVec3 velocity;
    BloodVec3 rotation;
    f32 acceleration;
    s32 flags;
} Blood39578Particle;

void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);
extern f32 D_800A486C;
extern f32 D_800A4870;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151389A8 CURRENT (1477) */
s32 func_151389A8(Blood39578Particle *arg0, s32 arg1, s32 arg2,
                  s32 arg3, f32 arg4, s32 arg5) {
    BloodVec3 position;
    u32 random;
    f32 randomScale;
    s32 mode;
    f32 horizontal;
    f32 vertical;
    f32 bounce;

    bounce = arg0->bounce;
    horizontal = arg0->velocity.x * bounce;
    arg0->velocity.y *= -bounce;
    arg0->position.y = arg0->height + arg4;
    vertical = fabsf(arg0->velocity.y);
    arg0->velocity.x = horizontal;
    arg0->velocity.z *= bounce;
    arg0->rotation.x *= bounce;
    arg0->rotation.y *= bounce;
    arg0->rotation.z *= bounce;
    if (vertical < 4.0f) {
        arg0->velocity.x = 0.0f;
        arg0->flags &= ~0x69;
        arg0->velocity.y = 0.0f;
        arg0->velocity.z = 0.0f;
        arg0->rotation.x = 0.0f;
        arg0->rotation.y = 0.0f;
        arg0->rotation.z = 0.0f;
        arg0->acceleration = 0.0f;
    }
    if (arg0->mode != 2.0f) {
        position.y = arg4;
        position.x = arg0->position.x;
        position.z = arg0->position.z;
        if (arg0->mode != 0.0f) {
            mode = 1;
        } else {
            mode = 0;
        }
        randomScale = func_150ADA68();
        random = func_150ADA20();
        func_151D9B8C((u8)mode,
            ((randomScale * D_800A486C) + D_800A4870) *
                ((arg0->size0 + arg0->size1) * 0.5f),
            ((random % 101U) + 0x64) & 0xFF, arg5, &position.x,
            (func_150ADA20() % 101U) + 0x50, 1, 1, 0,
            arg0->kind, arg0->color);
        *(f32 *)((u8 *)arg0 + 0x2C) = 0.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151389A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151389A8.s")
s32 func_15134070(Blood1380B4State *);
void func_15138120(Blood1380B4State *, s32, s32);
void func_151382E0(f32 *, s32, void *, u8, s32);
void func_15138424(Blood1380B4State *, f32 *, s32, void *, s32, s32);

void func_15138BC0(s32 arg0, u8 arg1, s32 arg2) {
    s32 sp50[4];
    u8 sp28[0x20];
    s32 temp_v0;
    u8 *a1p = &arg1;
    temp_v0 = func_15134070(arg0);
    if (temp_v0 != 0x63) {
        sp28[0x1F] = func_151380B4(arg0, temp_v0, (s32)sp50);
        func_15138120(arg0, temp_v0, 1);
        if (sp28[0x1F] != 0) {
            func_1504715C(sp28 - 8, arg0);
            func_151382E0(sp50, temp_v0, (s32)(sp28 - 8), *a1p, arg2);
            func_15138424(arg0, sp50, temp_v0, sp28 - 8, *a1p, arg2);
        }
    }
}
typedef struct {
    f32 height;
    u8 geometry[0x20];
} BloodHitRecord;

void func_1504715C(void *, void *);
void func_151036B4(void *, u8, s32);
void func_151382E0(f32 *, s32, void *, u8, s32);
void func_15138E98(Blood1380B4State *, f32 *, s32, void *, s32, s32);
void func_15139768(Blood1380B4State *, f32 *, f32, void *, s32, s32);
void func_15139D74(Blood1380B4State *, f32 *, void *, s32, s32);
void func_1513A6E0(Blood1380B4State *, f32 *, void *, s32, s32);
void func_1513ABB8(Blood1380B4State *, f32 *, s32, void *, s32, s32);
void func_1513B0F8(Blood1380B4State *, f32 *, void *, s32, s32);
void func_1513A594(void *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15138C80 CURRENT (3009) */
void func_15138C80(Blood1380B4State *arg0, s32 arg1, s32 arg2) {
    s32 kind;
    BloodVec3 position;
    u8 valid;
    BloodHitRecord hit;

    arg1 = arg1 & 0xFF;
    kind = func_15134070(arg0);
    if (kind != 0x63) {
        valid = func_151380B4(arg0, kind, &position.x);
        func_15138120(arg0, kind, 1);
        if (valid != 0) {
            func_1504715C(&hit, arg0);
            func_151382E0(&position.x, kind, &hit, arg1 & 0xFF, arg2);
            switch (kind) {
            case 16:
                func_1513B0F8(arg0, &position.x, &hit, arg1 & 0xFF, arg2);
                return;
            case 17:
                func_151036B4(&position.x, arg1 & 0xFF, arg2);
                return;
            case 0:
            case 7:
                func_1513A6E0(arg0, &position.x, &hit, arg1 & 0xFF, arg2);
                return;
            case 3:
                func_15138E98(arg0, &position.x, 1, &hit, arg1, arg2);
                return;
            case 5:
            case 6:
                func_15138E98(arg0, &position.x, 0, &hit, arg1, arg2);
                return;
            case 15:
                func_15139768(arg0, &position.x, 0.6f, &hit, arg1, arg2);
                return;
            case 2:
                func_15139768(arg0, &position.x, 1.0f, &hit, arg1, arg2);
                return;
            case 4:
                func_1513A594(arg0, (s32)&position.x, (s32)&hit, arg1 & 0xFF, arg2);
                return;
            case 8:
            case 9:
                func_1513ABB8(arg0, &position.x, (kind == 9) & 0xFF,
                             &hit, arg1, arg2);
                return;
            case 10:
            case 11:
            case 14:
            case 18:
            case 19:
                return;
            case 1:
            case 12:
            case 13:
            default:
                func_15139D74(arg0, &position.x, &hit, arg1 & 0xFF, arg2);
                break;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15138C80 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138C80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138E98.s")
extern f32 D_800A48F8;
extern f32 D_800A48FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15139578 CURRENT (1477) */
s32 func_15139578(Blood39578Particle *arg0, s32 arg1, s32 arg2,
                   s32 arg3, f32 arg4, s32 arg5) {
    BloodVec3 position;
    u32 random;
    f32 randomScale;
    s32 mode;
    f32 horizontal;
    f32 vertical;
    f32 bounce;

    bounce = arg0->bounce;
    horizontal = arg0->velocity.x * bounce;
    arg0->velocity.y *= -bounce;
    arg0->position.y = arg0->height + arg4;
    vertical = fabsf(arg0->velocity.y);
    arg0->velocity.x = horizontal;
    arg0->velocity.z *= bounce;
    arg0->rotation.x *= bounce;
    arg0->rotation.y *= bounce;
    arg0->rotation.z *= bounce;
    if (vertical < 4.0f) {
        arg0->velocity.x = 0.0f;
        arg0->flags &= ~0x69;
        arg0->velocity.y = 0.0f;
        arg0->velocity.z = 0.0f;
        arg0->rotation.x = 0.0f;
        arg0->rotation.y = 0.0f;
        arg0->rotation.z = 0.0f;
        arg0->acceleration = 0.0f;
    }
    if (arg0->mode != 2.0f) {
        position.y = arg4;
        position.x = arg0->position.x;
        position.z = arg0->position.z;
        if (arg0->mode != 0.0f) mode = 1; else mode = 0;
        randomScale = func_150ADA68();
        random = func_150ADA20();
        func_151D9B8C((u8)mode,
            ((randomScale * D_800A48F8) + D_800A48FC) *
                ((arg0->size0 + arg0->size1) * 0.5f),
            ((random % 101U) + 100) & 0xFF, arg5, &position.x,
            (func_150ADA20() % 144U) + 80, 1, 1, 0, arg0->kind, arg0->color);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15139578 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139578.s")

#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139768.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139D74.s")
typedef struct BloodA24CDescriptor {
    s32 count, countRange;
    BloodVec3 position;
    s16 angle, angleRange, pitch, pitchRange;
    f32 magnitude, magnitudeRange, field24, field28;
    s16 lifetime, lifetimeRange;
    f32 size, sizeRange, spread, probability;
    u8 variant;
    u8 pad41[3];
} BloodA24CDescriptor;

typedef struct BloodA24CHeader {
    s32 tag;
    u16 value;
    u8 kind, pad7;
    s32 mode;
} BloodA24CHeader;

typedef struct BloodA24CLookup {
    u16 values[4];
} BloodA24CLookup;

void func_15133E3C(s32, u8);
void func_1515080C(BloodA24CDescriptor *, s32 *, f32 *, s32,
                   void *, s32, u8, u8, s8, void *, f32, u8, u8, u8, s32);
extern BloodA24CLookup D_800A4258;
extern f32 D_800A4938, D_800A493C, D_800A4940;
extern f32 D_800A4944, D_800A4948, D_800A494C;
extern u8 D_800BE616;
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513A24C CURRENT (2720) */
void func_1513A24C(BloodVec3 *arg0, s32 *arg1, f32 *arg2, s32 arg3,
                   f32 arg4, u8 arg5, u8 arg6, u8 *arg7, void *arg8,
                   u8 arg9, s32 arg10) {
    BloodA24CDescriptor descriptor;
    BloodA24CHeader header;
    s32 mode;
    BloodA24CLookup lookup;
    u8 index;
    s32 enabled;

    descriptor.count = 0x28;
    descriptor.countRange = 0;
    descriptor.position = *arg0;
    descriptor.size = 1.0f * arg4;
    descriptor.angle = 0;
    descriptor.angleRange = 0xFF;
    descriptor.lifetime = 0x1E0;
    descriptor.lifetimeRange = 0xF0;
    descriptor.sizeRange = 0.0f * arg4;
    header.tag = 4;
    mode = -1;
    descriptor.pitch = -0x40;
    descriptor.pitchRange = 0xC;
    descriptor.magnitudeRange = 5.0f;
    descriptor.probability = 1.0f;
    descriptor.magnitude = 13.0f;
    descriptor.field24 = D_800A4938;
    descriptor.field28 = D_800A493C;
    descriptor.spread = D_800A4940;
    descriptor.variant = arg6;
    if (arg5 != 1) {
        if (arg5 != 0xD) {
            if (arg5 == 0x13 && D_800BE9F0 == 0x3C) {
                descriptor.probability = 0.0f;
            }
        } else {
            descriptor.pitch = -0x2E;
            descriptor.pitchRange = 0x14;
            descriptor.magnitude = 15.0f;
            descriptor.magnitudeRange = 8.0f;
            descriptor.field24 = D_800A4944;
            descriptor.field28 = D_800A4948;
            descriptor.spread = D_800A494C;
        }
    } else {
        lookup = D_800A4258;
        mode = 1;
        index = arg7[0x128];
        if (index >= 4) {
            index = 3;
        }
        header.kind = 6;
        header.mode = 3;
        header.value = lookup.values[index];
    }
    if (D_800BE616 != 0) {
        enabled = 1;
    } else {
        enabled = 0;
    }
    func_1515080C(&descriptor, arg1, arg2, arg3, &header, 0xC,
                  6, 1, mode, arg8, 5.0f, 1, enabled, arg9, arg10);
    func_15133E3C(0, 0x45);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513A24C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A24C.s")

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} BloodA48CPosition;

typedef struct {
    s32 field_0;
    s32 field_4;
    BloodA48CPosition position;
    s16 field_14;
    s16 field_16;
    s16 field_18;
    s16 field_1A;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    s16 field_2C;
    s16 field_2E;
    f32 field_30;
    f32 field_34;
    f32 field_38;
} BloodA48CConfig;

void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
extern u8 D_800A4260[];
extern u8 D_800A4264[];
extern f32 D_800A4950;
extern f32 D_800A4954;
extern f32 D_800A4958;
extern f32 D_800A495C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513A48C CURRENT (610) */
void func_1513A48C(BloodA48CPosition *arg0, u8 arg1, s32 arg2) {
    BloodA48CConfig config;

    config.field_0 = 8;
    config.field_4 = 4;
    config.position = *arg0;
    config.field_14 = 0;
    config.field_16 = 0xFF;
    config.field_18 = -0x37;
    config.field_1A = 0x20;
    config.field_2C = 0x28;
    config.field_2E = 0x14;
    config.field_30 = D_800A4950;
    config.field_34 = D_800A4950;
    config.field_1C = 10.0f;
    config.field_20 = 9.0f;
    config.field_24 = D_800A4954;
    config.field_28 = D_800A4958;
    config.field_38 = D_800A495C;
    func_15152190(&config, D_800A4260, D_800A4264, 1, 0.0f, 1,
                  (s32)arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513A48C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A48C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513A594 CURRENT (924) */
void func_1513A594(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_t6;

    temp_t6 = arg3 & 0xFF;
    func_1513A5E0(arg1, temp_t6 & 0xFF, arg4, temp_t6);
    if (*(s32 *)((u8 *)arg0 + 0x1D4) == 0) {
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513A594 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A594.s")
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} BloodA5E0Position;

typedef struct {
    s32 field_0;
    s32 field_4;
    BloodA5E0Position position;
    s16 field_14;
    s16 field_16;
    s16 field_18;
    s16 field_1A;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    s16 field_2C;
    s16 field_2E;
    f32 field_30;
    f32 field_34;
    f32 field_38;
} BloodA5E0Config;

void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
extern u8 D_800A4268[];
extern u8 D_800A4270[];
extern f32 D_800A4960;
extern f32 D_800A4964;
extern f32 D_800A4968;
extern f32 D_800A496C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513A5E0 CURRENT (847) */
void func_1513A5E0(s32 arg0, s32 arg1, s32 arg2) {
    BloodA5E0Config config;
    register f32 scale;
    register f32 repeated;

    scale = 4.0f;
    repeated = D_800A4960;
    config.field_0 = 7;
    config.field_4 = 7;
    config.position = *(BloodA5E0Position *)arg0;
    config.field_14 = 0;
    config.field_16 = 0xFF;
    config.field_18 = -0x32;
    config.field_1A = 0x1B;
    config.field_1C = scale;
    config.field_20 = scale;
    config.field_2C = 0x19;
    config.field_2E = 0x28;
    config.field_30 = repeated;
    config.field_34 = repeated;
    config.field_24 = D_800A4964;
    config.field_28 = D_800A4968;
    config.field_38 = D_800A496C;
    func_15152190(&config, D_800A4268, D_800A4270, 2, 0.0f, 1,
                  (u8)arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513A5E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A5E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A6E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513ABB8.s")

void func_1513B0B8(BloodState *arg0, s32 arg1, u8 arg2) {
    s32 *counter = &arg0->unk170;

    if (arg2 == 0x45) {
        if (--*counter < 0) {
            arg0->flags60 |= 0x80;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513B0F8.s")
