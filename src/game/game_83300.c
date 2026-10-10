#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_83300.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15055E50
 * - func_15056150
 * - func_15056258
 * - func_150562FC
 * - func_1505693C
 * - func_15056A00
 * - func_15056B08
 * - func_150585F0
 * - func_15058898
 * - func_15058F24
 * - func_150593C4
 * - func_15059444
 * - func_1505959C
 * - func_150599C8
 * - func_15059B54
 * - func_15059C84
 * - func_1505A184
 * - func_1505A250
 * - func_1505A3A8
 * - func_1505A5CC
 * - func_1505A630
 * - func_1505A770
 * - func_1505A9AC
 * - func_1505B5F8
 * - func_1505B9C4
 * - func_1505C1A4
 * - func_1505C1E4
 * - func_1505C7D8
 * - func_1505D024
 * - func_1505D1C4
 * - func_1505D408
 * - func_1505D5D0
 * - func_1505D6F0
 * - func_1505DADC
 * - func_1505DDA8
 * - func_1505E0C4
 * - func_1505E650
 * - func_1505E874
 * - func_1505ED34
 * - func_1505EEF4
 * - func_1505EFD0
 * - func_1505F0AC
 * - func_1505F188
 * - func_1505F298
 * - func_1506045C
 * - func_15060778
 * - func_15060D54
 * - func_15060F28
 * - func_150611E8
 * - func_1506160C
 * - func_150617BC
 * - func_150619A8
 * - func_15061B4C
 * - func_150623F4
 * - func_150626EC
 * - func_15062800
 * - func_15062AC4
 * - func_15062B84
 * - func_15062D10
 * - func_15062E24
 * - func_15062FC0
 * - func_15063168
 * - func_15063254
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15055E50.s")
extern f32 D_80099440;
extern s32 D_800D2104;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15056150 CURRENT (4849) */
void func_15056150(void *arg0) {
    volatile f32 sp1C;
    f32 temp_fa0;
    f32 temp_fa1;
    register f32 temp_fs0;
    register f32 temp_fs1;
    f32 temp_ft3;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_v0;
    void *temp_v1;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x2E8);
    if (temp_v0 != 0) {
        temp_v1 = ((void **)&D_800D2104)[*(u8 *)((u8 *)arg0 + 0x13F)];
        temp_fv1 = (f32)*(s16 *)((u8 *)temp_v1 + 8);
        temp_ft4 = (f32)temp_v0 * 8.0f;
        temp_fa0 = (f32)*(s16 *)((u8 *)temp_v1 + 0xC);
        temp_fa1 = (f32)*(s16 *)((u8 *)temp_v1 + 0xA);
        temp_ft5 = *(f32 *)((u8 *)arg0 + 0x14) - temp_fv1;
        temp_fs0 = *(f32 *)((u8 *)arg0 + 0x1C) - temp_fa0;
        temp_fs1 = *(f32 *)((u8 *)arg0 + 0x18) - temp_fa1;
        temp_fv0 = sqrtf((temp_ft5 * temp_ft5) + (temp_fs0 * temp_fs0) +
                          (temp_fs1 * temp_fs1) + D_80099440);
        temp_ft3 = 1.0f / temp_fv0;
        sp1C = temp_ft3;
        if (temp_ft4 < temp_fv0) {
            *(f32 *)((u8 *)arg0 + 0x14) =
                (temp_ft5 * temp_ft3 * temp_ft4) + temp_fv1;
            *(f32 *)((u8 *)arg0 + 0x1C) =
                (temp_fs0 * temp_ft3 * temp_ft4) + temp_fa0;
            *(f32 *)((u8 *)arg0 + 0x18) =
                (temp_fs1 * temp_ft3 * temp_ft4) + temp_fa1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15056150 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056150.s")
extern f32 D_80099444;
f32 fabsf(f32);
#pragma intrinsic(fabsf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15056258 CURRENT (1290) */
void func_15056258(void *arg0) {
    f32 temp_fa1;
    f32 temp_ft0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x118);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x18);
    temp_ft0 = *(f32 *)((u8 *)arg0 + 0x11C);
    *(f32 *)((u8 *)arg0 + 0x11C) = temp_fv0;
    temp_fv1 = temp_fv0 - temp_ft0;
    var_fa0 = 2.0f * (temp_fa1 - ((temp_fv0 - 60.0f) - 170.0f));
    if (var_fa0 < 0.0f) {
        return;
    }
    if (fabsf(temp_fv1) > 30.0f) {
        return;
    }
    if (var_fa0 > 300.0f) {
        var_fa0 = 300.0f;
    }
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (temp_fa1 + (var_fa0 * temp_fv1 * D_80099444));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15056258 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056258.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150562FC.s")
extern s32 D_800D2104;
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505693C CURRENT (1910) */
s32 func_1505693C(void *arg0, s32 arg1) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    u16 temp_v1;
    u8 *temp_a0;
    u8 *temp_v0;
    u8 index;

    index = *(u8 *)((u8 *)arg0 + 0x13F);
    temp_v0 = ((u8 **)&D_800D2104)[index];
    temp_v1 = *(u16 *)(temp_v0 + 6);
    if (temp_v1 == 0) {
        return 1;
    }
    temp_fv0 = (f32)(temp_v1 * 8);
    temp_a0 = (u8 *)&D_800CC2D0 + (arg1 * 0x32C);
    temp_fv1 = (f32)*(s16 *)(temp_v0 + 0) - *(f32 *)(temp_a0 + 0x14);
    temp_fa0 = (f32)*(s16 *)(temp_v0 + 4) - *(f32 *)(temp_a0 + 0x1C);
    if (((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0)) < (temp_fv0 * temp_fv0)) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505693C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505693C.s")
extern u8 D_80099A3C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15056A00 CURRENT (2855) */
void func_15056A00(void *arg0, u8 arg1, u8 arg2) {
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_v1_2;
    u8 *temp_a1;
    void *temp_v1;
    u8 temp_t5;

    temp_t6 = arg1;
    temp_t7 = arg2;
    temp_v1 = &D_80099A3C + (temp_t7 * 0xA);
    var_v0 = 0;
    if ((s32)*(u8 *)((u8 *)temp_v1 + 7) < temp_t6) {
        var_v0 = 5;
    } else if ((s32)*(u8 *)((u8 *)temp_v1 + 2) < temp_t6) {
        var_v0 = 2;
    }
    temp_v1_2 = *(u16 *)((u8 *)arg0 + 0x76);
    if ((*(u16 *)((u8 *)arg0 + 0x78) - temp_v1_2) & 0x8000) {
        var_v0_2 = (var_v0 + 3) & 0xFF;
    } else {
        var_v0_2 = (var_v0 + 4) & 0xFF;
    }
    temp_a1 = &D_80099A3C + (temp_t7 * 0xA) + var_v0_2;
    if (*temp_a1 != 0xFF) {
        *(s32 *)((u8 *)arg0 + 0x218) -= 5;
        *(s16 *)((u8 *)arg0 + 0x21C) = 0x4E20;
        *(s8 *)((u8 *)arg0 + 0x223) = 0xD;
        *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
        temp_t7_2 = *(s32 *)((u8 *)arg0 + 0xF4) & ~0xE;
        *(s32 *)((u8 *)arg0 + 0xF4) = temp_t7_2;
        temp_t5 = *temp_a1;
        *(s32 *)((u8 *)arg0 + 0xF4) = temp_t7_2 | 4;
        *(u16 *)((u8 *)arg0 + 0x78) = temp_v1_2;
        *(u16 *)((u8 *)arg0 + 0x7A) = temp_v1_2;
        *(s8 *)((u8 *)arg0 + 0x138) = 0;
        *(s16 *)((u8 *)arg0 + 0x244) = (s16)temp_t5;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15056A00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056A00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056B08.s")
typedef struct Game83300Inner {
    u8 pad0[0x28];
    s32 field_28;
    u8 pad2C[4];
    s32 field_30;
    s32 field_34;
    u8 pad38[9];
    u8 field_41;
    u8 pad42[0x1CF];
    u8 field_211;
} Game83300Inner;

typedef struct Game83300Actor {
    u8 pad0[4];
    u8 modelIndex; /* +0x04: bank-01 model index; not an actor-instance ID. */
    u8 pad5[0x23];
    f32 vertical;
    u8 pad2C[0x10];
    f32 speed;
    u8 pad40[0x44];
    s16 field_84;
    u8 pad86[0xC6];
    f32 scale;
    u8 pad150[0x80];
    s8 pitch;
    u8 pad1D1[0x52];
    u8 mode;
    u8 pad224[8];
    u16 motion_flags;
    u8 pad22E[0x16];
    u16 animation;
    u8 rate_flags;
    u8 pad247[2];
    u8 rate_low;
    u8 pad24A[6];
    u8 strength;
    u8 pad251[0x7F];
    Game83300Inner *field_2D0;
} Game83300Actor;


extern s32 D_800418B0[][16];
extern u8 D_800419A0;
extern f32 D_80099468;
extern f32 D_8009946C;
extern f32 D_80099470;
extern f32 D_80099474;
void func_1505E650(Game83300Actor *, s32, f32, f32, f32, f32, s32);

void func_1505841C(Game83300Actor *arg0, f32 arg1) {
    Game83300Inner *inner;
    f32 speed;
    f32 fade;
    f32 rate;
    f32 scaled_speed;
    s32 flags;

    flags = arg0->rate_flags;
    rate = (f32)(((flags & 0x1F) << 8) + arg0->rate_low) * D_80099468;
    if (!(flags & 0x80)) {
        speed = arg0->speed;
        if ((speed <= 1.0f) || ((arg0->motion_flags & 0x10) && (arg0->vertical == 0.0f))) {
            rate = arg1;
        } else {
            scaled_speed = speed;
            scaled_speed *= 0.5f / arg0->scale;
            rate *= 10.0f;
            rate = scaled_speed / rate + D_8009946C;
            if (!(flags & 0x20)) {
                rate += D_80099470;
            }
        }
    }
    if (arg0->mode == 0xD) {
        rate = (f32)(arg0->strength & 0x7F) * D_80099474;
    }
    if (flags == 0xFF) {
        rate = 0.0f;
    }
    func_1505E650(arg0, arg0->animation, rate,
                 (f32)arg0->pitch, 0.0f, 0.0f, 0);
    if (arg0->rate_flags == 0xFF) {
        fade = (f32)D_800418B0[D_800419A0][0];
        if (fade >= 0.0f) {
            inner = arg0->field_2D0;
            *(f32 *)((u8 *)inner + 8) = (*(f32 *)((u8 *)inner + 0x18) * (32768.0f - fade)) / 32768.0f;
        }
    }
}
typedef struct Game83300Child585F0 {
    u8 pad0[0x7D];
    u8 field7D;
} Game83300Child585F0;

typedef struct Game83300State585F0 {
    s32 kind;
    u8 pad4[0x14];
    f32 height18;
    u8 pad1C[4];
    f32 field20, field24, field28;
    u8 pad2C[0x10];
    f32 field3C;
    u8 pad40[0x36];
    u16 angle76, angle78, angle7A;
    u8 pad7C[4];
    u8 field80, field81, pad82, field83;
    u8 pad84[0x29];
    u8 modeAD;
    u8 padAE[0xA];
    f32 fieldB8;
    u8 padBC[0x38];
    s32 flagsF4, flagsF8;
    u8 padFC[8];
    u8 count104;
    u8 pad105[4];
    u8 strength109, pad10A, flags10B;
    s16 timer10C;
    u8 pad10E[0xA];
    f32 ground118;
    u8 pad11C[0xAE];
    u8 field1CA, pad1CB;
    f32 height1CC;
    u8 pad1D0[0x4C];
    s16 cooldown21C;
    u8 pad21E[0x1A];
    u8 owner238, pad239, backup23A;
    u8 pad23B[0xE1];
    Game83300Child585F0 *child31C;
} Game83300State585F0;

void func_1505A3A8(f32, void *, f32, f32, u8);
void func_150599C8(u8 *, s32, u16);
void func_1505E874(u8, void *);
void func_1506B078(void);
extern f32 D_80099478, D_8009947C, D_80099480, D_80099484;
extern u8 D_800BE616, D_800C3E78;
extern s16 D_800CC264;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150585F0 CURRENT (595) */
void func_150585F0(u8 *arg0, register f32 arg1) {
    Game83300State585F0 *actor;
    Game83300Child585F0 *child;
    f32 strength;
    f32 value;
    s32 mode;
    s32 count;
    s32 flags;
    s32 copiedAngle;
    u16 angle;
    s32 owner;

    actor = (void *)arg0;
    strength = (f32)(u32)actor->strength109;
    func_1505A3A8(0.0f, actor, 1.0f, strength * D_80099478, 0);
    if (actor->height1CC < D_8009947C) {
        actor->height1CC = actor->height18;
    }
    mode = actor->modeAD;
    if (mode != 0 && mode < 10) {
        value = actor->field20;
        actor->field24 = 0.0f;
        if (value < 60.0f) {
            actor->field20 = value * D_80099480;
        }
        if ((actor->ground118 - 60.0f) + 40.0f < actor->height18) {
            actor->field81 = 0;
            actor->field83 = 0;
            actor->modeAD = 0;
            actor->fieldB8 = 0.0f;
            actor->field24 = 4.0f;
        }
    }
    if (D_800BE616 == 0 || actor->kind != 1) {
        actor->cooldown21C = 0;
    }
    count = actor->count104;
    if (count != 255) {
        if (count != 254 && (actor->field1CA != 0 || actor->kind != 1)) {
            actor->count104 = count - 1;
        }
        value = actor->field28;
        actor->timer10C -= D_800CC264;
        if (value < D_80099484 && (actor->flagsF4 & 0x100)) {
            actor->timer10C = 0;
        }
        if (actor->timer10C <= 0) {
            child = actor->child31C;
            if (child != 0) {
                child->field7D = 0;
            }
            actor->timer10C = 0;
            func_1505E874(D_800C3E78, actor);
        }
        if (actor->count104 == 0) {
            copiedAngle = actor->angle7A;
            actor->field3C = 0.0f;
            actor->field81 = 0;
            actor->angle78 = copiedAngle;
            actor->angle76 = copiedAngle;
            if (actor->modeAD != 0) {
                actor->field20 = 0.0f;
                if (actor->kind == 1) {
                    func_1506B078();
                }
            } else if (actor->kind == 1) {
                actor->flagsF8 &= 0xFFFF7FFF;
                actor->field24 = 4.0f;
            }
            owner = actor->owner238;
            if (owner != 0) {
                actor->backup23A = owner;
            }
        } else {
            flags = actor->flags10B;
            if (!(flags & 2)) {
                angle = actor->angle76;
                if (flags & 4) {
                    angle = (angle ^ 0x8000) & 0xFFFF;
                }
                actor->field80 = 10;
                func_150599C8(arg0, 12, angle);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150585F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150585F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058898.s")
void func_15058EA4(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x18);
    if (arg1 < temp_fv0) {
        *(f32 *)((u8 *)arg0 + 0x24) = arg2;
    } else if (temp_fv0 < arg3) {
        *(f32 *)((u8 *)arg0 + 0x24) = arg4;
    }
    temp_fv0 = arg5;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x20);
    if (temp_fv0 < temp_fv1) {
        *(f32 *)((u8 *)arg0 + 0x20) = temp_fv0;
        return;
    }
    temp_fv0 = arg6;
    if (temp_fv1 < temp_fv0) {
        *(f32 *)((u8 *)arg0 + 0x20) = temp_fv0;
    }
}
extern f32 D_800994A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15058F24 CURRENT (2480) */
void func_15058F24(void *arg0, register f32 arg1) {
    register f32 temp_fa0;
    register f32 temp_fa1;
    register f32 temp_ft4;
    register f32 temp_fv0;
    register f32 temp_fv1;

    temp_fa0 = arg1;
    temp_ft4 = 0.5f - arg1;
    if (arg1 >= 0.5f) {
        arg1 -= 0.5f;
    }
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x18);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x118) + 9.0f;
    if ((temp_fv1 < temp_fa1) || ((s32) *(u8 *)((u8 *)arg0 + 0xAD) >= 0x64)) {
        if (*(u8 *)((u8 *)arg0 + 0xAD) == 0) {
            *(f32 *)((u8 *)arg0 + 0x18) = temp_fa1;
            *(u8 *)((u8 *)arg0 + 0xAD) = 0x64U;
            *(f32 *)((u8 *)arg0 + 0x24) = (f32) (temp_ft4 * -6.0f);
            *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) * temp_fa0);
        } else {
            if ((temp_fa1 + 100.0f) < temp_fv1) {
                *(u8 *)((u8 *)arg0 + 0xAD) = 0U;
            }
            if (temp_ft4 < 0.0f) {
                *(f32 *)((u8 *)arg0 + 0x24) = (f32) (temp_ft4 * -6.0f);
            } else {
                temp_fv1 = *(f32 *)((u8 *)arg0 + 0x18);
                temp_fa0 = temp_fv1 - ((temp_fa1 + 10.0f) - (120.0f * arg1));
                if ((fabsf(temp_fa0) < 2.0f) && (fabsf(*(f32 *)((u8 *)arg0 + 0x20)) < 2.0f)) {
                    *(f32 *)((u8 *)arg0 + 0x20) = 0.0f;
                    *(f32 *)((u8 *)arg0 + 0x24) = 1.0f;
                    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (temp_fv1 - (temp_fa0 * D_800994A4));
                } else {
                    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x20);
                    if (temp_fa0 > 0.0f) {
                        if (temp_fv0 > 0.0f) {
                            *(f32 *)((u8 *)arg0 + 0x24) = (f32) (temp_ft4 * 6.0f);
                            *(f32 *)((u8 *)arg0 + 0x20) = (f32) (temp_fv0 * 0.5f);
                        }
                    } else {
                        temp_fv1 = temp_ft4 * 80.0f;
                        if (temp_fv1 < temp_fv0) {
                            *(f32 *)((u8 *)arg0 + 0x20) = temp_fv1;
                        }
                        *(f32 *)((u8 *)arg0 + 0x24) = (f32) (temp_ft4 * -6.0f);
                    }
                }
            }
        }
        temp_fv1 = -100.0f * arg1;
        if (*(f32 *)((u8 *)arg0 + 0x20) < temp_fv1) {
            *(f32 *)((u8 *)arg0 + 0x20) = temp_fv1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15058F24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058F24.s")
void func_150511E8(u8 *);
void func_15055E50(u8 *, u8);
void func_15056150(void *);
void func_15056258(void *);
void func_15056B08(u8 *);
void func_15058898(u8 *, s32);
/* Raw caller supplies an unused third float in a2. */
void func_15058F24(void *, f32, f32);
void func_15059444(s32);
void func_15059C84(void *);
void func_1505A250(f32, f32, f32, f32 *, f32 *);
void func_1505A770(void *);
void func_1505B5F8(u8 *, f32);
void func_1505C7D8(s32 *, s32);
void func_1505D6F0(u8 *, u8);
extern s32 D_800CC268;
extern u8 D_800C3E78;
extern u8 D_800BE9A0;
extern f32 D_800994A8;
extern f32 D_800994AC;
extern f32 D_800994B0;
extern f32 D_800994B4;

void func_15059140(u8 *arg0) {
    f32 scale;
    s32 flags;
    s32 value;
    s32 step;

    scale = 0.5f;
    D_800CC268 = 0;
    if ((arg0[0x13D] == 0 || *(u16 *)(arg0 + 0x21C) < 16) &&
        arg0[0x223] != 8) {
        func_15059C84(arg0);
        func_1505A770(arg0);
    }
    func_1505D6F0(arg0, D_800C3E78);
    func_15055E50(arg0, arg0[0x1E4]);
    if (arg0[4] == 8) {
        func_15056150(arg0);
    }
    if (arg0[0x13D] < 100) {
        func_15058898(arg0, *(s32 *)(arg0 + 0x30));
    }
    flags = *(s32 *)(arg0 + 0xF4);
    if ((flags & 0x40000) && ((flags & 0x12000) || D_800CC268 != 0)) {
        *(u16 *)(arg0 + 0x21C) = 0;
    }
    value = *(s8 *)(arg0 + 0xB0);
    if (value != 0) {
        func_15058F24(arg0, (f32)value * D_800994A8, 1.0f);
    }
    if (*(s32 *)(arg0 + 0xF8) & 0x20000) {
        func_15056258(arg0);
    }
    if (arg0[0xAD] != 0) {
        func_15059444((s32)arg0);
    }
    if (arg0[4] == 10) {
        *(f32 *)(arg0 + 0x180) = D_800994AC;
    }
    if (*(s32 *)(arg0 + 0xF8) & 0x180000) {
        func_150511E8(arg0);
    }
    func_1505B5F8(arg0, *(f32 *)(arg0 + 0x180));
    if ((*(s32 *)(arg0 + 0xF4) & 0x1000) &&
        *(f32 *)(arg0 + 0x28) < D_800994B0) {
        func_15056B08(arg0);
    }
    if (*(s32 *)(arg0 + 0xF8) & 0x80000) {
        scale = D_800994B4;
    }
    func_1505A250(0.0f, 0.0f, scale,
                   (f32 *)(arg0 + 0x164), (f32 *)(arg0 + 0x168));
    if (arg0[0xD0] != 0) {
        func_1505C7D8((s32 *)arg0, D_800C3E78);
    }
    if (arg0[0x13D] == 0) {
        value = D_800BE9A0;
        step = arg0[0x10F];
        if (value >= step) {
            arg0[0x10F] = 0;
        } else {
            arg0[0x10F] = step - value;
        }
    }
    value = arg0[0x107];
    if (value != 0) {
        arg0[0x107] = value - 1;
    }
    step = arg0[0x125];
    if (step != 255) {
        value = D_800BE9A0;
        if (value >= step) {
            arg0[0x125] = 0;
        } else {
            arg0[0x125] = step - value;
        }
    }
}
void func_1505A184(u16, f32, s32, f32 *, f32 *, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150593C4 CURRENT (309) */
void func_150593C4(s32 arg0, u16 arg1, f32 arg2, f32 arg3) {
    f32 sp2C;
    f32 sp28;
    s32 sp24;
    f32 temp_fv0;
    f32 temp_fv1;

    func_1505A184(arg1, arg2, 0, &sp2C, &sp28, &sp24);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x16C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x170);
    *(f32 *)((u8 *)arg0 + 0x16C) = temp_fv0 + ((sp2C - temp_fv0) * arg3);
    *(f32 *)((u8 *)arg0 + 0x170) = temp_fv1 + ((sp28 - temp_fv1) * arg3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150593C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150593C4.s")
void func_150593C4(s32, u16, f32, f32);
s32 func_15083E0C(s32);
s32 func_150A29C8(s32, s32);
void func_150611E8(u8 *, s32);
extern s32 D_800BE9F0;
extern u8 D_800C3E78;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15059444 CURRENT (265) */
void func_15059444(s32 arg0) {
    s32 sp1C;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;

    sp1C = -1;
    switch (D_800BE9F0) {
    case 4:
        func_150593C4(arg0, 0x4000U, 50.0f, 0.06f);
        break;
    case 6:
        sp1C = func_15083E0C(0x1C);
        break;
    case 0x29:
        if (func_150A29C8(D_800C3E78, 0x4028) == 0) {
            var_v0_2 = 0xC;
        } else if (func_150A29C8(D_800C3E78, 0x400E) == 0) {
            var_v0_2 = 0xA;
        } else if (func_150A29C8(D_800C3E78, 0x400D) == 0) {
            var_v0_2 = 9;
        } else {
            var_v0_2 = 6;
        }
        sp1C = func_15083E0C(var_v0_2 & 0xFF);
        break;
    case 0x2B:
        sp1C = func_15083E0C(0x12);
        break;
    case 0x41:
        if (func_150A29C8(D_800C3E78, 0x401F) == 0) {
            var_v0_3 = 0x1B;
        } else {
            var_v0_3 = 0x1A;
        }
        sp1C = func_15083E0C(var_v0_3 & 0xFF);
        break;
    }
    if (sp1C != -1) {
        func_150611E8((u8 *)arg0, sp1C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15059444 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059444.s")
typedef struct Game83300AnimationRecord {
    u8 pad00[0x15];
    u8 flags;
    u8 pad16[2];
} Game83300AnimationRecord;

extern u16 D_800860C0[];
extern f32 D_800860CC[];
extern u16 D_800860E4[];
extern void *D_800D1588[];
s32 func_1505A630(f32, f32, s32);
u32 func_1505E7CC(s32, void *);
void func_1505E874(u8, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505959C CURRENT (852) */
void func_1505959C(void *arg0, s32 arg1, register void *arg2) {
    Game83300Actor *other;
    s32 selection;
    s32 offset;

    *(u32 *)((u8 *)arg0 + 0xF8) &= 0xFF7FFFFF;
    *((u8 *)arg0 + 0x13D) = arg1 + 0x64;
    *(u16 *)((u8 *)arg0 + 0x21C) = 0;
    *(u32 *)((u8 *)arg0 + 0x25C) &= ~8;
    other = (Game83300Actor *)((u8 *)&D_800CC2D0 + arg1 * 0x32C);
    *(f32 *)((u8 *)arg0 + 0x24) = 4.0f;
    other->pad40[0x43] = 0xFF;
    other->pad86[3] = 0xFF;
    arg2 = (void *)(u32)*((u8 *)arg0 + 4);
    selection = 0;
    if ((u32)arg2 == 0x57) selection = 1;
    if (other->modelIndex == 0x9B) selection = 2;
    if ((u32)arg2 == 0x5E) selection = 3;
    if ((u32)arg2 == 0x3C) {
        other->pad86[0xB6] = 0;
        selection = 4;
        *(u16 *)((u8 *)other + 0x76) = func_1505A630(
            *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)other + 0x14),
            *(f32 *)((u8 *)other + 0x1C) - *(f32 *)((u8 *)arg0 + 0x1C), 0);
        arg2 = (void *)(u32)*((u8 *)arg0 + 4);
    }
    if ((u32)arg2 == 0x89) selection = 5;
    offset = selection * 2;
    func_1505E650(other, *(u16 *)((u8 *)D_800860C0 + offset), D_800860CC[selection],
        0.0f, 0.0f, 0.0f, 0);
    *((u8 *)arg0 + 0x104) = 0xFE;
    *((u8 *)arg0 + 0x105) = 0;
    *((u8 *)arg0 + 0x106) = func_1505E7CC(*(u16 *)((u8 *)D_800860E4 + offset), arg0);
    *(u16 *)((u8 *)arg0 + 0x84) = 0xFFFF;
    func_1505E874(D_800C3E78, arg0);
    {
        void *entry;
        Game83300AnimationRecord *animations;
        entry = D_800D1588[*((u8 *)arg0 + 4)];
        if (entry != 0) {
            animations = *(Game83300AnimationRecord **)((u8 *)entry - 8);
            if (animations != 0 && (animations[*((u8 *)arg0 + 0x106)].flags & 2)) {
                *(u16 *)((u8 *)arg0 + 0x7A) = *(u16 *)((u8 *)other + 0x7A);
            }
            if (animations == 0 || !(animations[*((u8 *)arg0 + 0x106)].flags & 1)) {
                *((u8 *)arg0 + 0x13E) = (s32)(*(u16 *)((u8 *)arg0 + 0x7A) -
                    *(u16 *)((u8 *)other + 0x7A)) >> 8;
                return;
            }
            *((u8 *)arg0 + 0x13E) = 0;
            return;
        }
        *((u8 *)arg0 + 0x13E) = (s32)(*(u16 *)((u8 *)arg0 + 0x7A) -
            *(u16 *)((u8 *)other + 0x7A)) >> 8;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505959C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505959C.s")
typedef struct Game83300InteractionState {
    u8 pad0[0x18];
    s16 unk18;
    u8 pad1A[0xD];
    u8 unk27;
    u8 pad28[0x173];
    u8 unk19B;
} Game83300InteractionState;

typedef struct Game83300InteractionActor {
    s32 unk0;
    u8 unk4;
    u8 pad5[0x23];
    f32 unk28;
    u8 pad2C[0x10];
    f32 unk3C;
    u8 pad40[0x49];
    u8 unk89;
    u8 pad8A[0x7A];
    u8 unk104;
    u8 pad105[0x22];
    u8 unk127;
    u8 unk128;
    u8 pad129[0x13];
    u8 unk13C;
    u8 unk13D;
    u8 pad13E[0x8C];
    u8 unk1CA;
    u8 pad1CB[0x91];
    s32 unk25C;
    u8 pad260[0xBC];
    Game83300InteractionState *unk31C;
    u8 pad320[0xC];
} Game83300InteractionActor;

extern s8 D_8008FD8C;
extern s32 D_800CC268;
void func_1505959C(void *, s32, void *);

void func_150597FC(struct127 *arg0)
{
  s32 i;
  struct126 *temp_a2;
  struct127 *new_var;
  s32 new_var2;
  struct127 *temp;
  u8 temp_v1;
  s32 one;
  one = 1;
  new_var2 = D_800CC268;
  for (i = 0; i < D_8008FD8C; i++)
  {
    temp = (struct127 *)((u8 *)&D_800CC2D0 + i * 0x32C);
    if (((((((1 << i) & new_var2) && (temp->unk13C == 0)) && (temp->disable_run == 0)) && (temp->interaction_state == one)) && (temp->stunned == 0)) && (temp->unk127 != 0xFF))
    {
      break;
    }
  }

  if (i != D_8008FD8C)
  {
    temp = (struct127 *)((u8 *)&D_800CC2D0 + i * 0x32C);
    if (temp->unk13C == 0)
    {
      temp_a2 = temp->unk31C;
      if ((((((((((temp_a2->unk27 == 0) && (temp->health != 0)) && (arg0->unk13D == (one * 0))) && (((arg0->stunned != 0) || (arg0->unk25C & 0x1000)) || (arg0->id == 0x57))) && (arg0->unk28 == 0.0f)) && (temp->unk28 == 0.0f)) && (arg0->unk25C & 8)) && (temp_a2->unk19B == 0)) && (((temp_v1 = arg0->id, temp_v1 != 0xA9)) || ((*((u8 *) (&temp->pad128))) == 0))) && ((temp_v1 != 0xA8) || ((*((u8 *) (&temp->pad128))) != 0)))
      {
        if (temp_v1)
        {
        }
        (new_var = temp)->unk13C = D_800C3E78 + 0x64;
        new_var->xz_velocity = 0.0f;
        *((s16 *) (((u8 *) temp_a2) + 0x18)) = 0;
        func_1505959C(arg0, i, temp_a2);
      }
    }
  }
}
extern s16 D_800CC264;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150599C8 CURRENT (1385) */
s32 func_150599C8(void *arg0, u8 arg1, u16 arg2) {
    s16 temp_a2;
    s16 temp_t3;
    s16 temp_v1;
    s16 var_a3;
    s32 temp_lo;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t2;
    s32 var_v0;

    var_v0 = (s32) (((arg1 << 8) + *(u8 *)((u8 *)arg0 + 0x1E8)) * D_800CC264) / 100;
    temp_t0 = *(u16 *)((u8 *)arg0 + 0x7A);
    temp_t1 = *(u16 *)((u8 *)arg0 + 0x1EA);
    var_a3 = arg2 - temp_t0;

    if (temp_t1 != 0) {
        temp_t2 = *(u16 *)((u8 *)arg0 + 0x1EC);
        temp_lo = (s32) (temp_t1 * D_800CC264) / 100;
        temp_a2 = temp_t2 + temp_lo;
        temp_t3 = temp_t2 - temp_lo;
        if (temp_a2 < var_a3) {
            var_a3 = temp_a2;
        }
        if (var_a3 < temp_t3) {
            var_a3 = temp_t3;
        }
    }
    temp_v1 = var_a3;
    if (var_a3 < 0) {
        var_a3 ^= 0xFFFF;
    }
    if (var_a3 < var_v0) {
        var_v0 = (s32) var_a3;
    }
    if (!(*(s32 *)((u8 *)arg0 + 0xF4) & 1) && (*(u8 *)((u8 *)arg0 + 0x80) != 0)) {
        if (temp_v1 < 0) {
            *(u16 *)((u8 *)arg0 + 0x7A) = (u16) (temp_t0 - var_v0);
        } else {
            *(u16 *)((u8 *)arg0 + 0x7A) = (u16) (temp_t0 + var_v0);
        }
    }
    return (var_a3 >> 8) & 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150599C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150599C8.s")
extern s16 D_800CC264;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15059B54 CURRENT (925) */
s32 func_15059B54(void *arg0, u16 arg1) {
    s16 temp_a1_2;
    s16 temp_t0;
    s16 temp_t2;
    s16 var_a2;
    s16 var_v0;
    s32 temp_lo;
    u16 temp_a1;
    u16 temp_t1;
    u16 temp_v1;

    temp_v1 = *(u16 *)((u8 *)arg0 + 0x76);
    var_v0 = *(u16 *)((u8 *)arg0 + 0x78) - temp_v1;
    var_a2 = var_v0;
    if (var_v0 < 0) {
        var_a2 = var_v0 ^ 0xFFFF;
    }
    temp_a1 = *(u16 *)((u8 *)arg0 + 0x1EA);
    if (temp_a1 != 0) {
        temp_t1 = *(u16 *)((u8 *)arg0 + 0x1EC);
        temp_lo = (s32) (temp_a1 * D_800CC264) / 100;
        temp_t0 = temp_t1 + temp_lo;
        temp_t2 = temp_t1 - temp_lo;
        if (temp_t0 < var_v0) {
            var_v0 = temp_t0;
        }
        if (var_v0 < temp_t2) {
            var_v0 = temp_t2;
        }
    }
    temp_a1_2 = var_v0;
    if (var_v0 < 0) {
        var_v0 ^= 0xFFFF;
    }
    if (var_v0 < (s32) arg1) {
        arg1 = (u16) var_v0;
    }
    if (!(*(s32 *)((u8 *)arg0 + 0xF4) & 1)) {
        if (temp_a1_2 < 0) {
            *(u16 *)((u8 *)arg0 + 0x76) = (u16) (temp_v1 - arg1);
            *(u16 *)((u8 *)arg0 + 0x1EC) = (u16) -(s32) arg1;
        } else {
            *(u16 *)((u8 *)arg0 + 0x76) = (u16) (temp_v1 + arg1);
            *(u16 *)((u8 *)arg0 + 0x1EC) = arg1;
        }
    }
    return (var_a2 >> 8) & 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15059B54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059B54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059C84.s")
f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern f32 D_800994B8;
extern f32 D_800994BC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A184 CURRENT (589) */
void func_1505A184(u16 arg0, register f32 arg1, s32 arg2, f32 *arg3,
    f32 *arg4, s32 *arg5) {
    union {
        s32 word;
        f32 value;
    } angle_bits;
    f32 first_angle;
    f32 second_angle;
    f32 sine;
    f32 cosine;

    arg1 *= 0.5f;
    angle_bits.word = arg2;
    first_angle = angle_bits.value * D_800994B8;
    *(f32 *)arg5 = func_150AD78C(first_angle) * -arg1;
    arg1 = func_150AD780(first_angle) * arg1;
    second_angle = (f32)arg0 * D_800994BC;
    sine = func_150AD780(second_angle);
    cosine = -func_150AD78C(second_angle);
    *arg3 = sine * arg1;
    *arg4 = cosine * arg1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A184 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A184.s")
extern f32 D_800D1550;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A250 CURRENT (3520) */
void func_1505A250(f32 arg0, register f32 arg1, volatile f32 arg2, f32 *arg3, f32 *arg4) {
    struct { f32 stepX; f32 length; f32 stepY; f32 factor; } motion;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_ft5;

    temp_ft4 = *(volatile f32 *)arg3;
    temp_fv1 = arg0 - temp_ft4;
    temp_ft5 = arg1 - *(volatile f32 *)arg4;
    if ((temp_fv1 != 0.0f) || (temp_ft5 != 0.0f)) {
        motion.factor = arg2 * D_800D1550;
        temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + (temp_ft5 * temp_ft5));
        arg2 = motion.factor;
        motion.length = temp_fv0;
        motion.stepX = fabsf((temp_fv1 / temp_fv0) * motion.factor);
        motion.stepY = fabsf((temp_ft5 / motion.length) * motion.factor);
        if (temp_fv1 >= 0.0f) {
            *(volatile f32 *)arg3 = temp_ft4 + motion.stepX;
            if (arg0 < *(volatile f32 *)arg3) {
                goto block_6;
            }
        } else {
            *(volatile f32 *)arg3 = temp_ft4 - motion.stepX;
            if (*(volatile f32 *)arg3 < arg0) {
block_6:
                *(volatile f32 *)arg3 = arg0;
            }
        }
        if (temp_ft5 >= 0.0f) {
            *(volatile f32 *)arg4 += motion.stepY;
            if (arg1 < *(volatile f32 *)arg4) {
                goto block_11;
            }
        } else {
            *(volatile f32 *)arg4 -= motion.stepY;
            if (*(volatile f32 *)arg4 < arg1) {
block_11:
                *(volatile f32 *)arg4 = arg1;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A250 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A250.s")
extern f32 D_800994C0;
extern f32 D_800994C4;
extern f32 D_800994C8;
extern f32 D_800994CC;
extern f32 D_800994D0;
extern u8 D_800CC27C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A3A8 CURRENT (20) */
void func_1505A3A8(f32 arg0, void *arg1, f32 arg2, f32 arg3, u8 arg4) {
    u8 temp_v0;

    arg3 *= D_800D1550;
    arg2 *= D_800D1550;
    if ((D_800CC27C != 0) && (*(f32 *)((u8 *)arg1 + 0x28) < 5.0f) && (*(s32 *)((u8 *)arg1 + 0) != 0x1E)) {
        arg2 = 0.0f;
    }
    if (*(s32 *)((u8 *)arg1 + 0) == 1) {
        if (*(u8 *)((u8 *)arg1 + 0xAD) != 0) {
            arg3 *= D_800994C0;
            arg2 = 2.0f;
        }
        if (*(u8 *)((u8 *)arg1 + 0xA8) != 0) {
            arg3 *= 0.25f;
        }
        temp_v0 = *(u8 *)((u8 *)arg1 + 0x81);
        if (temp_v0 != 0) {
            if (temp_v0 & 0x40) {
                if (temp_v0 & 0x20) {
                    arg3 = 0.0f;
                } else {
                    arg3 = D_800994C4;
                }
            } else {
                arg3 *= D_800994C8;
                if ((s32) arg4 >= 0x2E) {
                    arg2 *= 0.5f;
                }
                if ((s32) arg4 >= 0x5B) {
                    arg0 *= 0.5f;
                }
            }
        }
        if (*(u8 *)((u8 *)arg1 + 0xAE) != 0) {
            arg3 *= D_800994CC;
        }
    }
    if (arg0 < 0.0f) {
        if (*(f32 *)((u8 *)arg1 + 0x3C) > 0.0f) {
            arg3 += arg2;
        } else {
            arg3 = arg2;
        }
    } else if (*(f32 *)((u8 *)arg1 + 0x3C) < 0.0f) {
        arg2 += arg3;
    }
    if (arg0 < *(f32 *)((u8 *)arg1 + 0x3C)) {
        *(f32 *)((u8 *)arg1 + 0x3C) = (f32) (*(f32 *)((u8 *)arg1 + 0x3C) - arg3);
        if (*(f32 *)((u8 *)arg1 + 0x3C) < arg0) {
            goto block_32;
        }
    } else {
        if ((arg0 - 1.0f) < *(f32 *)((u8 *)arg1 + 0x3C)) {
            arg2 *= D_800994D0;
        }
        *(f32 *)((u8 *)arg1 + 0x3C) = (f32) (*(f32 *)((u8 *)arg1 + 0x3C) + arg2);
        if (arg0 < *(f32 *)((u8 *)arg1 + 0x3C)) {
block_32:
            *(f32 *)((u8 *)arg1 + 0x3C) = arg0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A3A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A3A8.s")
extern f32 D_800994D4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A5CC CURRENT (25) */
f32 func_1505A5CC(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = (f32) *(s8 *)((u8 *)arg0 + 2);
    temp_fa0 = (f32) *(s8 *)((u8 *)arg0 + 3);
    temp_fv1 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0)) * D_800994D4;
    if (temp_fv1 > 35.0f) {
        temp_fv1 = 35.0f;
    }
    return temp_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A5CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A5CC.s")
f32 func_150484A0(f32, f32);
extern f32 D_800994D8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A630 CURRENT (235) */
s32 func_1505A630(f32 arg0, f32 arg1, s32 arg2) {
    return ((u32) (func_150484A0(-arg0, arg1) * D_800994D8) + 0x4000) & 0xFFFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A630 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A630.s")
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_1505A6F8(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)arg1 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)arg1 + 0x1C);
    temp_fv1 *= temp_fv1;
    temp_fa0 *= temp_fa0;
    return sqrtf(temp_fv1 + temp_fa0);
}
f32 func_1505A72C(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)arg1 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)arg1 + 0x1C);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)arg1 + 0x18);
    temp_fv1 *= temp_fv1;
    temp_fa0 *= temp_fa0;
    temp_fa1 *= temp_fa1;
    return sqrtf(temp_fv1 + temp_fa0 + temp_fa1);
}
extern f32 D_800994DC;
extern f32 D_800994E0;
extern f32 D_800994E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A770 CURRENT (190) */
void func_1505A770(void *arg0) {
    f32 velocity;
    f32 decrement;
    s32 count;
    s32 i;

    if ((*(f32 *)((u8 *)arg0 + 0x28) != 0.0f) ||
        (velocity = *(f32 *)((u8 *)arg0 + 0x20), velocity > 0.0f)) {
        count = (s32)(D_800D1550 / 0.1f);
        decrement = *(f32 *)((u8 *)arg0 + 0x24) * 0.1f;
        for (i = 0; i < count; i++) {
            *(f32 *)((u8 *)arg0 + 0x20) -= decrement;
            *(f32 *)((u8 *)arg0 + 0x18) +=
                *(f32 *)((u8 *)arg0 + 0x20) * 0.05f;
        }
        if (*(f32 *)((u8 *)arg0 + 0x20) < -500.0f) {
            *(f32 *)((u8 *)arg0 + 0x20) = -500.0f;
        }
    } else {
        *(f32 *)((u8 *)arg0 + 0x20) = velocity -
            (*(f32 *)((u8 *)arg0 + 0x24) * D_800D1550);
        velocity = *(f32 *)((u8 *)arg0 + 0x20);
        *(f32 *)((u8 *)arg0 + 0x18) += velocity * D_800D1550 * 0.5f;
        if (velocity < -500.0f) {
            *(f32 *)((u8 *)arg0 + 0x20) = -500.0f;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A770 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A770.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A9AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505B5F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505B9C4.s")
typedef struct {
    u8 pad_0[0x14];
    f32 field_14;
    u8 pad_18[4];
    f32 field_1C;
    u8 pad_20[0x5A];
    u16 field_7A;
} Game83300Position;

s32 func_1505A630(f32, f32, s32);

s32 func_1505C140(Game83300Position *arg0, Game83300Position *arg1) {
    s16 temp_v1;
    s32 var_v1;

    temp_v1 = func_1505A630(arg0->field_14 - arg1->field_14,
                           arg1->field_1C - arg0->field_1C, 0);
    temp_v1 = temp_v1 - arg1->field_7A;
    var_v1 = temp_v1;
    if (temp_v1 < 0) {
        temp_v1 = (s16)-temp_v1;
        var_v1 = temp_v1;
    }
    return var_v1;
}
extern s32 D_8009A9F8;
extern void *D_800D1588[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505C1A4 CURRENT (210) */
void *func_1505C1A4(void *arg0) {
    void *var_a0;
    void **var_v0;
    void *temp_v1;
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if ((temp_v0 != 0xFF) && ((temp_v1 = D_800D1588[temp_v0]) != 0)) {
            var_v0 = (void **)((u8 *)temp_v1 - 0xC);
            var_a0 = *var_v0;
    } else {
        var_a0 = &D_8009A9F8;
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505C1A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C1A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C1E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C7D8.s")
s32 func_1505C1E4(s32 *, void *, void *, s32, s32, s32, s32);
void func_1505B9C4(s32 *, void *, void *, void *, s32, s32, s32);
void *func_1505C1A4(void *);
extern u8 D_800C35EA;
extern s32 D_800D121C;
extern u16 D_800D1292;
extern u16 D_800D1296;
extern s8 D_800D1340;
extern void *D_800D154C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D024 CURRENT (5761) */
s32 func_1505D024(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *record;
    s32 index;
    s32 mask;
    s32 result;
    u16 value;

    value = arg2 & 0xFFFF;
    record = &D_8009A9F8;
    if (D_800C35EA == 1) {
        return 0;
    }
    if (arg1 & 0x20000) {
        if (((u8 *)arg0)[0x125]) {
            return 0;
        }
    }
    if (arg1 & 0x40000) {
        if (((u8 *)arg0)[0x104]) {
            return 0;
        }
    }
    if (!(arg1 & 0x100000)) {
        if (!((u8 *)arg0)[0x1CA]) {
            return 0;
        }
    }
    if (arg3 == -1) {
        D_800D1340 = 0;
    } else {
        D_800D1340 = arg3 + 1;
    }
    D_800D1292 = value;
    D_800D1296 = value;
    if (arg1 & 0x10000) {
        record = func_1505C1A4(D_800D154C);
    }
    index = ((s32)arg0 - (s32)&D_800CC2D0) / 812;
    mask = 1 << index;
    if (arg1 & 0x80000) {
        result = func_1505C1E4(&D_800D121C, arg0, record,
                               arg1 & 0xFF, index + 1, 0, 7);
    } else {
        func_1505B9C4(&D_800D121C, arg0, record, record,
                       arg1 & 0xFF, index + 1, 7);
        result = mask;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505D024 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D024.s")
void func_1505F188(u32);
void func_1505C7D8(s32 *, s32);
extern u8 D_800C3E78;
extern s32 D_800D121C;
extern f32 D_800D1230;
extern f32 D_800D1234;
extern f32 D_800D1238;
extern u16 D_800D1292;
extern s8 D_800D12EC;
extern f32 D_800D1330;
extern s8 D_800D1340;
extern s8 D_800D1359;
extern f32 D_800D1368;
extern f32 D_800D136C;
extern s32 D_800D1510;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D1C4 CURRENT (30) */
void func_1505D1C4(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4,
                   u16 arg5, s32 arg6, s32 arg7) {
    volatile struct {
        s32 saved_state;
        s32 pad;
    } local;

    local.saved_state = D_800C3E78;
    func_1505F188((u32)&D_800D121C);
    D_800D1230 = arg0;
    D_800D1234 = arg1;
    D_800D1238 = arg2;
    D_800D1340 = arg4 + 1;
    D_800D1359 = arg6;
    D_800D1292 = arg5;
    D_800C3E78 = 0x19;
    D_800D1510 = arg7;
    D_800D1330 = 100.0f;
    D_800D12EC = arg3 + 1;
    D_800D1368 = 0.5f;
    D_800D136C = 0.5f;
    func_1505C7D8(&D_800D121C, 0x19);
    D_800C3E78 = local.saved_state;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505D1C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D1C4.s")
u32 func_1505E7CC(s32, void *);
void func_1505E874(u8, void *);
extern u8 D_8009A6D8[];
extern u8 D_800C3E78;

void func_1505D2B8(void *arg0, u8 arg1) {
    void *temp_v0;

    temp_v0 = (u8 *)D_8009A6D8 + (arg1 * 0x28);
    *(f32 *)((u8 *)arg0 + 0x20) = *(f32 *)((u8 *)temp_v0 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x3C) = *(f32 *)((u8 *)temp_v0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x24) = *(f32 *)((u8 *)temp_v0 + 0x1C);
    *(u8 *)((u8 *)arg0 + 0x104) = 0xFE;
    *(u8 *)((u8 *)arg0 + 0x105) = 0;
    *(u8 *)((u8 *)arg0 + 0x106) = func_1505E7CC((*(u8 *)((u8 *)arg0 + 0x10E) & 0x7F), arg0);
    *(u8 *)((u8 *)arg0 + 0x10E) = 0xFF;
    func_1505E874(D_800C3E78, arg0);
}
f32 func_150AD780(f32);                             /* extern */
f32 func_150AD78C(f32);                             /* extern */
extern f32 D_80099520;

f32 func_1505D34C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    struct {
        f32 output;
        f32 cosine;
        f32 sine;
    } rotation;
    f32 angle;

    if (arg3 != 1.0f) {
        arg1 *= arg3;
        arg2 *= arg3;
    }
    angle = (arg0 - 90.0f) * D_80099520;
    rotation.sine = func_150AD780(angle);
    rotation.cosine = func_150AD78C(angle);
    rotation.output = (-arg1 * rotation.cosine) + (arg2 * rotation.sine);
    *arg4 = rotation.output;
    return (arg1 * rotation.sine) + (arg2 * rotation.cosine);
}
extern f32 D_80099524;
extern f32 D_80099528;
extern f32 D_8009952C;
extern s32 D_800CC268;
extern s8 D_800CC26C;
extern s8 D_800CC26D;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D408 CURRENT (2569) */
void func_1505D408(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    f32 temp_ft5;
    f32 temp_fv0;
    f32 var_fv1;
    s32 temp_a2;
    s32 temp_t0;
    s32 var_v0;
    s32 var_v1;

    var_fv1 = D_80099524;
    var_v0 = 0;
    var_v1 = 0;
    if (arg5 < 1.0f) {
        arg5 = D_80099528;
    }
    if ((arg2 == 0.0f) && (arg4 == 0.0f)) {
        arg2 = 1.0f;
    }
    D_800CC268 |= 1 << arg7;
    if (!(*(s32 *)((u8 *)arg1 + 0xF8) & 0x10) || (D_800CC26C = (s8) arg7, var_fv1 = D_8009952C, (*(u8 *)((u8 *)arg1 + 4) != 0x61)) || (*(s32 *)((u8 *)arg0 + 0) != 1)) {
        temp_t0 = *(s32 *)((u8 *)arg0 + 0xF8);
        temp_a2 = *(s32 *)((u8 *)arg1 + 0xF8);
        if (temp_t0 & 1) {
            var_v0 = 1;
        }
        if (temp_t0 & 0x200) {
            var_v0 = (var_v0 | 2) & 0xFF;
        }
        if (temp_a2 & 1) {
            var_v1 = 1;
        }
        if (temp_a2 & 0x200) {
            var_v1 = (var_v1 | 2) & 0xFF;
        }
        if (var_v1 >= var_v0) {
            if ((temp_a2 & 0x400) && (*(f32 *)((u8 *)arg1 + 0x28) == 0.0f)) {
                D_800CC26D = arg7 + 0x64;
            }
            temp_fv0 = sqrtf(arg5);
            temp_ft5 = 1.0f / temp_fv0;
            arg6 -= temp_fv0;
            arg2 *= temp_ft5;
            arg3 *= temp_ft5;
            arg4 *= temp_ft5;
            arg6 *= var_fv1;
            *(f32 *)((u8 *)arg0 + 0x14) += arg6 * arg2;
            *(f32 *)((u8 *)arg0 + 0x1C) += arg6 * arg4;
            *(f32 *)((u8 *)arg0 + 0x18) += arg6 * arg3;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505D408 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D408.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D5D0 CURRENT (2108) */
void func_1505D5D0(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12) {
    extern void func_1505D408(void *, void *, f32, f32, f32, f32, f32, s32);
    f32 temp_fa0;
    f32 temp_ft2;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;

    temp_fv0 = func_1505D34C(*(f32 *)((u8 *)arg1 + 0x40), arg11, arg12, *(f32 *)((u8 *)arg1 + 0x14C), &arg12);
    temp_ft2 = arg8 * *(f32 *)((u8 *)arg1 + 0x14C);
    arg8 = temp_ft2;
    temp_fv1 = *(f32 *)((u8 *)arg1 + 0x150);
    temp_ft4 = arg2 - (*(f32 *)((u8 *)arg1 + 0x14) + temp_fv0);
    temp_ft5 = arg4 - (*(f32 *)((u8 *)arg1 + 0x1C) + arg12);
    temp_fa0 = (arg3 - (*(f32 *)((u8 *)arg1 + 0x18) + (arg10 * temp_fv1))) * ((arg5 + (temp_ft2 / (arg9 * temp_fv1))) * 0.5f);
    temp_fv0_2 = arg6 + temp_ft2;
    temp_fv1_2 = (temp_ft4 * temp_ft4) + (temp_fa0 * temp_fa0) + (temp_ft5 * temp_ft5);
    if (temp_fv1_2 < (temp_fv0_2 * temp_fv0_2)) {
        func_1505D408(arg0, arg1, temp_ft4, temp_fa0, temp_ft5, temp_fv1_2, temp_fv0_2, arg7);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505D5D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D5D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D6F0.s")
typedef struct {
    s32 state;
    u8 pad4[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0x5A];
    u16 heading;
    u8 pad7C[0x7C];
    s32 flags;
    u8 padFC[8];
    u8 priority;
    u8 pad105[0xC5];
    u8 active;
    u8 pad1CB[0x12F];
    u8 enabled;
    u8 pad2FB[0x31];
} Game83300AimActor;

extern f32 D_80099534;
extern f32 D_80099538;
f32 func_1505DF10(void *, u8, s16 *, f32 *, f32 *);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *,
                   f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505DADC CURRENT (3102) */
s32 func_1505DADC(Game83300AimActor *self, u16 *angleOut,
                   s32 pitch, s32 excluded, s32 range) {
    s16 angle;
    f32 horizontalSquared;
    f32 vertical;
    s32 hit;
    s16 vertices[9];
    f32 hitX;
    f32 hitY;
    f32 hitZ;
    f32 hitDistance;
    f32 distance;
    f32 bestDistance;
    f32 x;
    f32 y;
    f32 z;
    s32 index;
    s32 result;
    s32 excludeIndex;
    u8 priority;
    Game83300AimActor *other;

    excludeIndex = excluded & 0xFF;
    bestDistance = D_80099534;
    priority = 0;
    result = 0xFF;
    if (excludeIndex == 0xFE) {
        bestDistance = D_80099538;
    }
    index = 0;
    do {
        other = (Game83300AimActor *)((u8 *)&D_800CC2D0 + index * 0x32C);
        if ((other->state != 0) && (other->active != 0) &&
            ((((s32)self - (s32)&D_800CC2D0) / 812) & 0xFF) != index &&
            (other->flags & 0x40) && (excludeIndex != index) &&
            (other->enabled != 0)) {
            distance = func_1505DF10(self, index & 0xFF, &angle,
                                      &horizontalSquared, &vertical);
            if ((distance < bestDistance) || ((other->priority == 0) && (priority != 0))) {
                if ((((s32)((u16)angle - self->heading) >> 8) +
                     (u8)range & 0xFF) < (u8)range * 2) {
                    if (((((func_1505A630(sqrtf(horizontalSquared), -vertical, 0) >> 8) &
                           0xFF) - (u8)pitch + 0x10) & 0xFF) < 0x20) {
                        y = self->y;
                        z = self->z;
                        x = self->x;
                        if ((func_150AC9C0(x, y + 80.0f, z, other->x - x,
                                             other->y - y, other->z - z, &hit,
                                             vertices, &hitX, &hitY, &hitZ, &hitDistance,
                                             0, 0, 0.0f) == 0) ||
                            (hitDistance *= hitDistance, !(hitDistance < distance))) {
                            priority = other->priority;
                            result = index & 0xFF;
                            bestDistance = distance;
                            *angleOut = angle;
                        }
                    }
                }
            }
        }
        index = (index + 1) & 0xFF;
    } while (index < 0x19);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505DADC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DADC.s")
extern s32 D_80082FA0;
extern s32 D_800CC2D0;

f32 func_1505DF10(void *, u8, s16 *, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505DDA8 CURRENT (1964) */
s8 func_1505DDA8(void *arg0, s32 arg1, s32 arg2, f32 arg3) {
    s16 sp6C;
    f32 sp68;
    f32 temp_fs0;
    s32 temp_s2;
    f32 sp64;
    u8 temp_t6;
    u8 var_s0;

    temp_s2 = arg2 & 0xFFFF;
    var_s0 = 0;
    if (D_80082FA0 >= 0) {
loop_2:
        if (*(s32 *)((u8 *)&D_800CC2D0 + (var_s0 * 0x32C)) != 0) {
            temp_fs0 = *(f32 *)((u8 *)arg0 + 0x3C) * arg3 * 0.5f;
            if ((func_1505DF10(arg0, var_s0 & 0xFF, &sp6C, &sp68, &sp64) < (temp_fs0 * temp_fs0)) && ((((*(u16 *)((u8 *)arg0 + 0x76) - (u16) sp6C) + (temp_s2 / 2)) & 0xFFFF) < temp_s2)) {
                return var_s0;
            }
            goto block_7;
        }
block_7:
        temp_t6 = (var_s0 + 1) & 0xFF;
        var_s0 = temp_t6;
        if (D_80082FA0 < temp_t6) {
            goto block_8;
        }
        goto loop_2;
    }
block_8:
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505DDA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DDA8.s")
/* Call context: func_1505A630: unique active project prototype */
extern s32 D_800CC2D0;

f32 func_1505DF10(void *arg0, u8 arg1, s16 *arg2, f32 *arg3, f32 *arg4) {
    u8 *target;
    f32 x;
    f32 y;
    f32 z;

    target = (u8 *)&D_800CC2D0 + arg1 * 0x32C;
    x = *(f32 *)(target + 0x14) - *(f32 *)((u8 *)arg0 + 0x14);
    y = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)(target + 0x18);
    z = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)(target + 0x1C);
    *arg4 = y;
    *arg2 = func_1505A630(x, z, 0);
    x *= x;
    y *= y;
    z *= z;
    *arg3 = x + z;
    return x + y + z;
}

void func_100226F0(void *, s32);
extern u16 D_800C4ED0[];

void func_1505DFDC(Game83300Actor *arg0) {
    s32 sp1C;
    Game83300Inner *sp18;
    u16 *temp_v1;

    sp18 = arg0->field_2D0;
    *(u16 *)&arg0->field_84 = 0xFFFF;
    if (sp18 != 0) {
        sp1C = arg0->modelIndex;
        sp18->field_28 = 0;
        func_100226F0((u8 *)sp18 + 0x40, 0x3A0);
        temp_v1 = &D_800C4ED0[sp1C];
        sp18->field_41 = *temp_v1 + 1;
        sp18->field_211 = (u8)(*temp_v1 + 1);
        sp18->field_30 = 0;
        sp18->field_34 = 0;
    }
}
/* Call context: func_10023A10: unique active project prototype */
void func_10023A10(void *, void *, s32);

void func_1505E060(u8 *arg0) {
    *(u16 *)((u8 *)arg0 + 6) = (u16) *(u16 *)((u8 *)arg0 + 4);
    *(f32 *)((u8 *)arg0 + 0xC) = (f32) *(f32 *)((u8 *)arg0 + 8);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) *(f32 *)((u8 *)arg0 + 0x10);
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) *(f32 *)((u8 *)arg0 + 0x20);
    *(f32 *)((u8 *)arg0 + 0x1C) = (f32) *(f32 *)((u8 *)arg0 + 0x18);
    *(s8 *)((u8 *)arg0 + 0x39) = (s8) *(s8 *)((u8 *)arg0 + 0x38);
    *(s32 *)((u8 *)arg0 + 0x2C) = (s32) *(s32 *)((u8 *)arg0 + 0x28);
    func_10023A10(arg0 + 0x40, arg0 + 0x210, 0x1D0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E0C4.s")
s32 func_150229E4(void *);
void func_1505E0C4(f32, Game83300Actor *, u16 *, Game83300Inner *, s32, s32, s32, s32, f32, f32, f32, f32, s32);
extern u8 D_800C3638;
extern u8 D_800C3654;
extern u16 D_800C5A90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505E650 CURRENT (4967) */
void func_1505E650(Game83300Actor *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    s32 sp40;
    Game83300Inner *sp38;
    Game83300Inner *temp_t0;
    f32 var_fa0;
    u16 *temp_a1;
    u16 temp_v0;
    u16 temp_v0_3;
    u8 temp_a2;
    u8 temp_v1;
    u8 *temp_v0_2;

    var_fa0 = *(f32 *)&arg3;
    temp_a2 = arg0->modelIndex;
    if (D_800C3638 != 0) {
        if (D_800C3654 == 0) {
            return;
        }
        sp40 = temp_a2;
        if (func_150229E4(arg0) != 0) {
            return;
        }
    }
    temp_v1 = arg0->modelIndex;
    if (temp_v1 == 0xFF) {
        return;
    }
    temp_v0 = D_800C5A90[temp_v1];
    if (temp_v0 == 0) {
        return;
    }
    temp_t0 = arg0->field_2D0;
    sp38 = temp_t0;
    if (temp_t0 == 0 || (u16)arg1 >= temp_v0) {
        return;
    }
    temp_v0_2 = D_800D1588[temp_a2];
    if (temp_v0_2 == 0) {
        func_1505DFDC(arg0);
        return;
    }
    if ((u16)arg1 >= D_800C5A90[temp_a2]) {
        return;
    }
    temp_a1 = (u16 *)(temp_v0_2 + (arg1 * 8));
    if (*(u16 *)temp_v0_2 == 0x3E7 || *temp_a1 == 0x3E7) {
        return;
    }
    temp_v0_3 = *temp_a1;
    if (temp_v0_3 >= 0x7530) {
        func_1505DFDC(arg0);
        return;
    }
    if (*(u8 *)((u8 *)arg0 + 0x2FF) == 0) {
        var_fa0 = 0.0f;
    }
    func_1505E0C4(var_fa0, arg0, temp_a1, sp38, 0, 0, arg1, 0, *(f32 *)&arg2, var_fa0, arg4, arg5, arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505E650 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E650.s")
u32 func_1505E7CC(s32 arg0, void *arg1) {
    u32 temp_v0_2;
    u32 var_v1;
    u8 *temp_a0;
    u8 *var_a1;
    u8 temp_v0;
    void *temp_v1;

    temp_v0 = *(u8 *)((u8 *)arg1 + 4);
    if (temp_v0 == 0xFF) {
        return 0U;
    }
    temp_v1 = D_800D1588[temp_v0];
    if (temp_v1 == 0) {
        return 0U;
    }
    temp_v0_2 = *(u32 *)((u8 *)temp_v1 + -4);
    if (temp_v0_2 == 0) {
        return 0U;
    }
    temp_v0_2 /= 24U;
    temp_a0 = *(u8 **)((u8 *)temp_v1 + -8);
    if (temp_a0 == 0) {
        return 0U;
    }
    var_v1 = 0;
    if (temp_v0_2 != 0) {
        var_a1 = temp_a0;
        do {
            if (arg0 == *var_a1) {
                return var_v1;
            }
            var_v1 += 1;
            var_a1 += 0x18;
        } while (var_v1 < temp_v0_2);
    }
    return 0U;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E874.s")
void func_15060F28(u8 *, s32);
extern s32 D_800CC2D0;
extern s32 D_800CC4A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505ED34 CURRENT (715) */
u8 *func_1505ED34(void) {
    s32 var_v0;
    u8 *var_a0;

    var_v0 = 0;
    var_a0 = (u8 *)&D_800CC2D0;
    if (*(volatile s32 *)&D_800CC2D0 != 0) {
loop_1:
        var_v0 += 1;
        var_a0 = (u8 *)((u32)var_a0 + 0x32CU);
        if (var_v0 < 0x19 && *(s32 *)var_a0 != 0) {
            goto loop_1;
        }
    }
    if (var_v0 == 0x19) {
        var_a0 = (u8 *)&D_800CC2D0;
        var_v0 = 0;
        if (*(volatile s32 *)&D_800CC2D0 != 0x27 || D_800CC4A4 != 0) {
loop_6:
            var_v0 += 1;
            var_a0 = (u8 *)((u32)var_a0 + 0x32CU);
            if (var_v0 < 0x19 &&
                (*(s32 *)var_a0 != 0x27 || *(s32 *)((u32)var_a0 + 0x1D4U) != 0)) {
                goto loop_6;
            }
        }
        if (var_v0 != 0x19 && *(s32 *)var_a0 != 0) {
            func_15060F28(var_a0, 0);
        }
    }
    if (var_v0 == 0x19) {
        var_a0 = (u8 *)&D_800CC2D0;
        var_v0 = 0;
        if (*(volatile s32 *)&D_800CC2D0 != 0x27) {
loop_14:
            var_v0 += 1;
            var_a0 = (u8 *)((u32)var_a0 + 0x32CU);
            if (var_v0 < 0x19 && *(s32 *)var_a0 != 0x27) {
                goto loop_14;
            }
        }
        if (var_v0 != 0x19 && *(s32 *)var_a0 != 0) {
            func_15060F28(var_a0, 0);
        }
    }
    if (var_v0 == 0x19 && *(s32 *)var_a0 != 0) {
        func_15060F28(var_a0, 0);
    }
    func_1505F188((u32)var_a0);
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505ED34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505ED34.s")
extern s32 D_800CC2D0;

struct127 *func_1505EEB0(s32 arg0, s32 *arg1) {
    struct127 *tmp = (struct127 *)&D_800CC2D0;
    s32 i = 0;

    while (i < 25 && arg0 != tmp->interaction_state) {
        i++;
        tmp++;
    }
    *arg1 = i;
    return tmp;
}
extern u8 D_800CC40F;
extern s32 D_800CC5FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505EEF4 CURRENT (415) */
s32 *func_1505EEF4(s32 arg0) {
    u8 *var_v1;
    s32 var_v0;

    var_v1 = (u8 *)&D_800CC5FC;
    if ((D_800CC2D0 != 0) && (arg0 == D_800CC40F)) {
        return &D_800CC2D0;
    }
    var_v0 = 1;
loop_4:
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 0x13F))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if ((*(s32 *)var_v1 != 0) && (arg0 == *(u8 *)(var_v1 + 0x13F))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if ((*(s32 *)var_v1 != 0) && (arg0 == *(u8 *)(var_v1 + 0x13F))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    var_v0 += 4;
    if ((*(s32 *)var_v1 != 0) && (arg0 == *(u8 *)(var_v1 + 0x13F))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if (var_v0 == 0x19) {
        return 0;
    }
    goto loop_4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505EEF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EEF4.s")
extern u8 D_800CC3F7;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505EFD0 CURRENT (415) */
s32 *func_1505EFD0(s32 arg0) {
    u8 *var_v1;
    s32 var_v0;

    var_v1 = (u8 *)&D_800CC5FC;
    if ((D_800CC2D0 != 0) && (arg0 == D_800CC3F7)) {
        return &D_800CC2D0;
    }
    var_v0 = 1;
loop_4:
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 0x127))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 0x127))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 0x127))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    var_v0 += 4;
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 0x127))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if (var_v0 == 0x19) {
        return 0;
    }
    goto loop_4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505EFD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EFD0.s")
extern u8 D_800CC2D4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505F0AC CURRENT (415) */
s32 *func_1505F0AC(s32 arg0) {
    u8 *var_v1;
    s32 var_v0;

    var_v1 = (u8 *)&D_800CC5FC;
    if ((D_800CC2D0 != 0) && (arg0 == D_800CC2D4)) {
        return &D_800CC2D0;
    }
    var_v0 = 1;
loop_4:
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 4))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 4))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 4))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    var_v0 += 4;
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 4))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if (var_v0 == 0x19) {
        return 0;
    }
    goto loop_4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505F0AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F0AC.s")
u32 func_150ADA20();                                /* extern */
extern f32 D_8009962C;
extern f32 D_80099630;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505F188 CURRENT (50) */
void func_1505F188(u32 arg0) {
    u32 temp_v1;
    u32 var_v0;
    f32 one;
    f32 initial;

    temp_v1 = arg0 + 0x32C;
    var_v0 = arg0;
    if (arg0 < temp_v1) {
        do {
            var_v0 += 4;
            *(s32 *)((u8 *)var_v0 + -4) = 0;
        } while (var_v0 < temp_v1);
    }
    one = 1.0f;
    initial = D_8009962C;
    *(s8 *)((u8 *)arg0 + 0x2FD) = 2;
    *(s16 *)((u8 *)arg0 + 0x38) = -0x2710;
    *(f32 *)((u8 *)arg0 + 0x14C) = one;
    *(f32 *)((u8 *)arg0 + 0x150) = one;
    *(f32 *)((u8 *)arg0 + 0x118) = initial;
    *(f32 *)((u8 *)arg0 + 0x180) = initial;
    *(f32 *)((u8 *)arg0 + 0x24) = D_80099630;
    *(u8 *)((u8 *)arg0 + 0x1DC) = 0xFF;
    *(u8 *)((u8 *)arg0 + 0x127) = 0xFF;
    *(u16 *)((u8 *)arg0 + 0x84) = 0xFFFF;
    *(u8 *)((u8 *)arg0 + 0x13F) = 0xFF;
    *(s32 *)((u8 *)arg0 + 0x2C4) = (s32) (arg0 + 4);
    *(s8 *)((u8 *)arg0 + 0x2C8) = 1;
    *(s8 *)((u8 *)arg0 + 0x2C9) = 1;
    *(u8 *)((u8 *)arg0 + 4) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0x2CB) = 0x32;
    *(f32 *)((u8 *)arg0 + 0x48) = one;
    *(s8 *)((u8 *)arg0 + 0x6E) = (s8) ((func_150ADA20() % 50U) + 0x32);
    func_150615DC((void *) arg0);
    *(u8 *)((u8 *)arg0 + 0x1DD) = 0xFF;
    *(u8 *)((u8 *)arg0 + 0x1DE) = 0xFF;
    *(u8 *)((u8 *)arg0 + 0x1DF) = 0xFF;
    *(s16 *)((u8 *)arg0 + 0x18C) = 0;
    *(s16 *)((u8 *)arg0 + 0x18E) = 0;
    *(s16 *)((u8 *)arg0 + 0x190) = 0;
    *(s16 *)((u8 *)arg0 + 0x192) = 0;
    *(s16 *)((u8 *)arg0 + 0x194) = 0;
    *(s16 *)((u8 *)arg0 + 0x196) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x198) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x19A) = 0;
    *(s16 *)((u8 *)arg0 + 0x19C) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505F188 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F188.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F298.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506045C.s")
typedef struct {
    u8 pad_0[0x318];
    void *field_318;
} Game83300DispatchState;

void func_1000F85C(u16, s32, s32);
void func_1000F91C(u16, s32, s16, s32, s32, s32, s32, s32, s32, s32);
u16 func_10010E78(s32, s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
u16 func_10010BE8(s32, s32, s32, s32, s32, s32, s32);
s32 func_1001147C(u16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15060778 CURRENT (2818) */
void func_15060778(s32 arg0, Game83300DispatchState *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u32 handle;
    s32 channel;
    s32 mode;
    u16 *slot;
    u16 result;

    handle = 0;
    slot = 0;
    if (arg6 & 8) {
        channel = 0;
    } else {
        channel = (*(u32 *)&arg1->pad_0[0x184] >> 3) & 0x30;
    }
    mode = arg6 & 3;
    switch (mode) {
    case 1:
        slot = (u16 *)&arg1->pad_0[0x8C];
        handle = *(u16 *)&arg1->pad_0[0x8C];
        break;
    case 2:
    case 3:
        slot = (u16 *)&arg1->pad_0[0x8E];
        handle = *(u16 *)&arg1->pad_0[0x8E];
        if (mode == 2) {
            break;
        }
        if ((func_1001147C((u16)handle) == arg0) & 0x7FFF) {
            if (arg6 & 4) {
                func_1000F91C((u16)handle, (u16)((u16)arg2 + channel * 50),
                              (s16)(arg1->pad_0[0x13F] * 10 + arg3), channel & 0xFF, 0,
                              (s32)*(f32 *)&arg1->pad_0[0x14],
                              (s32)*(f32 *)&arg1->pad_0[0x18],
                              (s32)*(f32 *)&arg1->pad_0[0x1C], arg4, arg5);
            } else {
                func_1000F85C((u16)handle, 0x10, arg3);
                func_1000F85C((u16)handle, 8, (u16)arg2 + channel * 50);
            }
            return;
        }
        arg0 |= 0x8000;
        break;
    }
    if (arg6 & 4) {
        result = func_10010E78((u16)handle, arg0, (u16)((u16)arg2 + channel * 50),
                              (s16)arg3, channel, 0,
                              (s32)*(f32 *)&arg1->pad_0[0x14],
                              (s32)*(f32 *)&arg1->pad_0[0x18],
                              (s32)*(f32 *)&arg1->pad_0[0x1C], arg4, arg5);
    } else {
        result = func_10010BE8((u16)handle, arg0, (u16)((u16)arg2 + channel * 50),
                              0x40, arg3, channel, 1);
    }
    if (slot != 0) {
        *slot = result;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15060778 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060778.s")

/* Call context: func_10010344: unique active project prototype */
s32 func_10010344(s32, s32, u32, s16, s32);
void func_10010630(u16, Game83300DispatchState *, s32, s32, s32);
void func_15060778(s32, Game83300DispatchState *, s32, s32, s32, s32, s32);

void func_15060A30(s32 arg0, Game83300DispatchState *arg1) {
    if (arg1->field_318 == 0) {
        func_10010344((u16)arg0, (s32)arg1, 0x6D60U, 0x1F4, 0x9C4);
        return;
    }
    func_15060778(arg0, arg1, 0x5DC0, 0, 0x1F4, 0x9C4, 1);
}

void func_15060A9C(s32 arg0, Game83300DispatchState *arg1) {
    if (arg1->field_318 == 0) {
        func_10010630((u16)arg0, arg1, 0x5DC0, 0x1F4, 0x9C4);
        return;
    }
    func_15060778(arg0, arg1, 0x5DC0, 0, 0x1F4, 0x9C4, 0);
}
void func_15060B04(s32 arg0, Game83300DispatchState *arg1, s32 arg2) {
    if (arg1->field_318 == 0) {
        func_10010630((u16)arg0, arg1, arg2, 0x1F4, 0x9C4);
        return;
    }
    func_15060778(arg0, arg1, (u16)arg2, 0, 0x1F4, 0x9C4, 0);
}
void func_10010154(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15060B70(u16 arg0, s32 arg1) {
    func_10010154(arg0, arg1, 0x6D60, 0x1F4, 0x9C4);
}
s32 func_15060BA4(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0x1CA);
    if (temp_v0 == 6) {
        return 0;
    }
    *(u8 *)((u8 *)arg0 + 0x1CA) = temp_v0 + arg1;
    if (*(u8 *)((u8 *)arg0 + 0x1CA) >= 7) {
        *(u8 *)((u8 *)arg0 + 0x1CA) = 6U;
    }
    return 1;
}
typedef struct Game83300Motion {
    u8 pad0[0x10];
    f32 directionX;
    f32 directionY;
    f32 directionZ;
    u8 pad1C[0x14];
    f32 positionX;
    f32 positionY;
    f32 positionZ;
    u8 pad3C[4];
} Game83300Motion;

typedef struct Game83300MotionInfo {
    u8 pad0[0x14];
    s16 scale;
    u8 pad16[0x11];
    u8 motionIndex;
} Game83300MotionInfo;

typedef struct Game83300MotionOwner {
    u8 pad0[4];
    u8 index;
    u8 pad5[0xF];
    f32 fallbackX;
    f32 fallbackY;
    f32 fallbackZ;
    u8 pad20[0x130];
    f32 scale;
    u8 pad154[0x68];
    s16 resultX;
    s16 resultY;
    s16 resultZ;
    u8 pad1C2[0x12];
    Game83300Motion *motions;
} Game83300MotionOwner;

extern u8 D_800C3E90;
extern u8 *D_800D1C90[];

void func_15060BE0(struct127 *arg0) {
    f32 pad0;
    f32 pad1;
    f32 pad2;
    f32 pad3;
    f32 sp4;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f18;
    f32 var_f2;
    s32 var_v0;
    struct124 *temp_v0;
    u8 *temp_a2;

    var_v0 = 0;
    if (arg0->id != 0xFF) {
        if ((arg0->unk1D4 != 0) && (D_800C3E90 == 0)) {
            temp_v0 = D_800D1C90[arg0->id];
            temp_a2 = (u8 *)arg0->unk1D4;
            temp_a2 += *(u8 *)((u8 *)temp_v0 + 0x27) << 6;
            temp_f2 = (f32) *(s16 *)((u8 *)temp_v0 + 0x14) * arg0->y_scale;
            if (temp_f2) {
                temp_f12 = *(f32 *)(temp_a2 + 0x10);
                temp_f14 = *(f32 *)(temp_a2 + 0x14);
                temp_f16 = *(f32 *)(temp_a2 + 0x18);
                temp_f0 = sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14) + (temp_f16 * temp_f16));
                var_f18 = temp_f0;
                if (temp_f0) {
                    var_f18 = temp_f2 / temp_f0;
                }
                var_f2 = temp_f12 * var_f18;
                var_f0 = temp_f14 * var_f18;
                sp4 = temp_f16 * var_f18;
            } else {
                var_f0 = (sp4 = 0.0f);
                var_f2 = var_f0;
            }
            var_v0 = 1;
            *(s16 *)((u8 *)arg0 + 0x1BC) = (s16) (s32) (*(f32 *)(temp_a2 + 0x30) + var_f2);
            *(s16 *)((u8 *)arg0 + 0x1BE) = (s16) (s32) (*(f32 *)(temp_a2 + 0x34) + var_f0);
            *(s16 *)((u8 *)arg0 + 0x1C0) = (s16) (s32) (*(f32 *)(temp_a2 + 0x38) + sp4);
        }
    }
    if (var_v0 == 0) {
        *(s16 *)((u8 *)arg0 + 0x1BC) = (s16) (s32) arg0->x_position;
        *(s16 *)((u8 *)arg0 + 0x1BE) = (s16) (s32) arg0->y_position;
        *(s16 *)((u8 *)arg0 + 0x1C0) = (s16) (s32) arg0->z_position;
    }
}
typedef struct Game83300ActorLink {
    s32 active;
    u8 pad4[0x61];
    u8 owner_index;
    u8 pad66[0x2C6];
} Game83300ActorLink;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15060D54 CURRENT (2465) */
void func_15060D54(Game83300ActorLink *arg0) {
    Game83300ActorLink *actor;
    s32 i;

    actor = (Game83300ActorLink *)&D_800CC2D0;
    for (i = 0; i < 25; i++, actor++) {
        if ((actor->active != 0) &&
            ((arg0 - (Game83300ActorLink *)&D_800CC2D0) + 1 == actor->owner_index)) {
            actor->owner_index = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15060D54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060D54.s")

typedef struct Game83300CleanupHeader {
    u16 flags;
    u8 released;
} Game83300CleanupHeader;
typedef struct Game83300CleanupChild {
    u8 pad0[0x11C];
    s32 allocation;
} Game83300CleanupChild;
typedef struct Game83300CleanupActor {
    u8 pad0[5], kind, pad6[0x139], slot, pad140[4];
    Game83300CleanupHeader *header;
    u8 pad148[0x90];
    s32 allocation1D8;
    u8 pad1DC[0x84];
    s32 allocations[4];
    u8 pad270[0x60];
    s32 allocation2D0;
    u8 *effect;
    u8 pad2D8[0x2C];
    s32 viewAllocations[4], allocation314;
    u8 pad318[4];
    Game83300CleanupChild *child;
    u8 pad320[4];
    s32 allocation324;
} Game83300CleanupActor;

s32 func_1514D310(void *);
void func_151695F0(void *, u8);
void func_15084558(void *);
void func_150626EC(s32, s32);
void func_1504AF10(void *, s32, s32);
void func_1503E260(s32);
void func_10004074(s32);
void func_100043B4(s32, s32);
void func_10010AA8(u8 *);
s32 func_150303E4(void *);
void func_15060D54(Game83300ActorLink *);
void func_15188AD0(s32);
extern u8 *D_800D210C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15060F28 CURRENT (2525) */
void func_15060F28(u8 *arg0, s32 arg1) {
    Game83300CleanupActor *actor;
    Game83300CleanupHeader *header;
    Game83300CleanupChild *child;
    u8 *entry;
    s32 slot, flags;
    s32 allocation;
    u8 *effect;

    actor = (Game83300CleanupActor *)arg0;
    func_1514D310(arg0);
    func_151695F0(arg0, 0);
    if (actor->kind != 2 && actor->kind != 3) {
        func_15084558(arg0);
        func_150626EC((s32)arg0, arg1);
    }
    if (arg1 == 1) {
        func_1504AF10(arg0, 1, 0);
        func_1503E260((arg0 - (u8 *)&D_800CC2D0) / 0x32C);
    }
    slot = actor->slot;
    if (slot != 0xFF) {
        if (arg1 != 2) {
            header = actor->header;
            if (header != 0) {
                flags = header->flags;
                if (flags & 0x20) {
                    header->released = 1;
                    D_800D210C[actor->slot] = 0;
                } else {
                    if (flags & 1) {
                        entry = D_800D210C + slot;
                        goto clear_entry;
                    }
                    header->released = 1;
                    entry = actor->slot + D_800D210C;
                    *entry &= 0x80;
                }
            } else {
                entry = slot + D_800D210C;
                *entry &= 0x80;
            }
        } else {
            entry = D_800D210C + slot;
clear_entry:
            *entry = 0;
        }
    }
    allocation = actor->allocations[0];
    if (allocation != 0) func_10004074(allocation);
    allocation = actor->allocations[1];
    if (allocation != 0) func_10004074(allocation);
    allocation = actor->allocations[2];
    if (allocation != 0) func_10004074(allocation);
    allocation = actor->allocations[3];
    if (allocation != 0) func_10004074(allocation);
    allocation = actor->allocation1D8;
    if (allocation != 0) func_10004074(allocation);
    effect = actor->effect;
    if (effect != 0) func_1516972C(effect);
    if (actor->viewAllocations[0] != 0) {
        arg1 = 0;
        if (D_80082FA0 >= 0) {
            do {
                func_100043B4(actor->viewAllocations[arg1], 4);
                arg1 = (arg1 + 1) & 0xFF;
            } while (D_80082FA0 >= arg1);
        }
    }
    allocation = actor->allocation314;
    if (allocation != 0) func_100043B4(allocation, 4);
    allocation = actor->allocation2D0;
    if (allocation != 0) func_10004074(allocation);
    allocation = actor->allocation324;
    if (allocation != 0) func_10004074(allocation);
    child = actor->child;
    if (child != 0) {
        allocation = child->allocation;
        if (allocation != 0) func_10004074(allocation);
    }
    func_10010AA8(arg0);
    func_150303E4(arg0);
    func_15060D54((Game83300ActorLink *)arg0);
    func_15188AD0((s32)arg0);
    child = actor->child;
    if (child != 0) func_10004074((s32)child);
    func_1505F188((u32)arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15060F28 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060F28.s")

/* Call context: func_1505A630: unique active declaration in the allowed source */
extern f32 D_8009968C;
extern s32 D_800D2104;
extern s32 D_800D2108;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150611E8 CURRENT (10964) */
void func_150611E8(u8 *arg0, s32 arg1) {
    s32 sp30;
    f32 sp1C;
    f32 sp18;
    f32 var_ft4;
    f32 var_fv1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a1;
    s32 temp_a1_2;
    u8 *temp_a2;
    s16 temp_ft1;
    s16 temp_ft3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a3;
    s32 var_t0;
    s32 var_t4;
    s32 var_t4_2;
    u16 temp_v0_7;
    u8 temp_t5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_v1_6;
    u8 *var_a2;
    u8 *var_a2_2;

    temp_t5 = *(u8 *)(D_800D2108 + arg1);
    if ((s32) temp_t5 >= 3) {
        temp_ft1 = (s32) *(f32 *)((u8 *)arg0 + 0x14);
        var_t0 = 0x7FFFFFFF;
        var_a3 = 0;
        temp_ft3 = (s32) *(f32 *)((u8 *)arg0 + 0x1C);
        for (var_a3 = 0; var_a3 < temp_t5; var_a3++) {
            var_a2 = *(u8 **)(D_800D2104 + arg1 * 4) + var_a3 * 8;
            temp_a0 = temp_ft1 - *(s16 *)(var_a2 + 0);
            temp_a1 = temp_ft3 - *(s16 *)(var_a2 + 4);
            if (temp_a0 * temp_a0 + temp_a1 * temp_a1 < var_t0) {
                sp30 = var_a3;
                var_t0 = temp_a0 * temp_a0 + temp_a1 * temp_a1;
            }
        }
        var_t4_2 = sp30;
        if ((var_t4_2 != 0) && (temp_t5 != (var_t4_2 + 1))) {
            temp_a2 = (void *)(*(u8 **)(D_800D2104 + (arg1 * 4)));
            if (var_t0 >= 0x6D61) {
                temp_a0_6 = (void *)(temp_a2 + (var_t4_2 * 8));
                temp_v0_5 = (s16) temp_ft1 - *(s16 *)((u8 *)temp_a0_6 + 8);
                temp_v1_4 = (s16) temp_ft3 - *(s16 *)((u8 *)temp_a0_6 + 0xC);
                temp_v0_6 = (s16) temp_ft1 - *(s16 *)((u8 *)temp_a0_6 + -8);
                temp_v1_5 = (s16) temp_ft3 - *(s16 *)((u8 *)temp_a0_6 + -4);
                if (((temp_v0_6 * temp_v0_6) + (temp_v1_5 * temp_v1_5)) < ((temp_v0_5 * temp_v0_5) + (temp_v1_4 * temp_v1_4))) {
                    var_t4_2 -= 1;
                }
            }
            temp_a0_7 = (void *)(temp_a2 + (var_t4_2 * 8));
            temp_v0_7 = *(u16 *)((u8 *)temp_a0_7 + 0xE);
            if (temp_v0_7 == 0) {
                var_fv1 = 8.0f;
            } else {
                var_fv1 = (f32)(u32)temp_v0_7;
            }
            var_ft4 = var_fv1 * D_8009968C;
            if (var_ft4 > 1.0f) {
                var_ft4 = 1.0f;
            }
            sp18 = var_ft4;
            sp1C = var_fv1;
            temp_v0_8 = func_1505A630((f32) (*(s16 *)((u8 *)temp_a0_7 + 8) - *(s16 *)((u8 *)temp_a0_7 + 0)), (f32) (*(s16 *)((u8 *)temp_a0_7 + 4) - *(s16 *)((u8 *)temp_a0_7 + 0xC)), 0);
            temp_v1_6 = (void *)(*(void **)((u8 *)arg0 + 0x31C));
            if ((temp_v1_6 != 0) && (var_fv1 > 20.0f)) {
                *(s16 *)((u8 *)temp_v1_6 + 0x68) = (s16) (temp_v0_8 | 1);
            }
            func_150593C4((s32) arg0, temp_v0_8 & 0xFFFF, var_fv1, var_ft4);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150611E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150611E8.s")
void func_150615DC(void *arg0) {
    u8 *p = arg0;

    p[7] = 0xFF;
    p[8] = 0xFF;
    p[0xF] = p[0xA] = p[9] = 0;
    p[0xE] = 0xFF;
    p[0xD] = 0xFF;
    p[0xC] = 0xFF;
    p[0xB] = 0xFF;
}
extern s32 D_800DBFF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506160C CURRENT (2360) */
void func_1506160C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    s32 temp_a3;
    s32 temp_t6;
    s32 var_v1;
    s32 var_a2;
    u8 temp_t7;

    temp_t6 = arg1 & 0xFF;
    temp_t7 = arg2 & 0xFF;
    if (temp_t6 >= 8) {
        if (temp_t6 != 0xA) {
            if (temp_t6 == 8) {
                var_v1 = 1 << arg4;
                *(u8 *)((u8 *)arg0 + 0xF) = (u8) (*(u8 *)((u8 *)arg0 + 0xF) | var_v1);
                var_a2 = 0;
            } else {
                var_a2 = 0xFF;
                var_v1 = 1 << arg4;
                *(u8 *)((u8 *)arg0 + 0xF) = (u8) (*(u8 *)((u8 *)arg0 + 0xF) & ~var_v1);
            }
            temp_a3 = var_v1 * 0x10;
            if (*(u8 *)((u8 *)arg0 + 0xF) & temp_a3) {
                *(s8 *)((u8 *)(arg0 + arg4) + 0xB) = var_a2;
            }
            *(u8 *)((u8 *)arg0 + 0xF) = (u8) (*(u8 *)((u8 *)arg0 + 0xF) & ~temp_a3);
        } else {
            var_a2 = 0;
            *(u8 *)((u8 *)arg0 + 0xF) = (u8) (*(u8 *)((u8 *)arg0 + 0xF) | ((1 << arg4) * 0x10));
        }
        if ((*(u8 *)((u8 *)arg0 + 0x2FD) != 0) || (*((u8 *)&D_800DBFF4 + arg4) != 0)) {
            *(s8 *)((u8 *)(arg0 + arg4) + 0xB) = var_a2;
        }
    } else if (temp_t6 >= (s32) *(u8 *)((u8 *)arg0 + 0xA)) {
        if (temp_t6 == 4) {
            *(u8 *)((u8 *)arg0 + 0xA) = (u8) temp_t6;
            *(u8 *)((u8 *)arg0 + 7) = 0U;
            *(u8 *)((u8 *)arg0 + 8) = 0xFFU;
            *(s8 *)((u8 *)arg0 + 9) = 0x20;
        } else if (temp_t6 == 5) {
            *(u8 *)((u8 *)arg0 + 0xA) = (u8) temp_t6;
            *(u8 *)((u8 *)arg0 + 8) = 0U;
            *(s8 *)((u8 *)arg0 + 9) = 0x20;
        } else if (temp_t6 == 6) {
            *(u8 *)((u8 *)arg0 + 0xA) = (u8) temp_t6;
            *(u8 *)((u8 *)arg0 + 8) = 0U;
            *(s8 *)((u8 *)arg0 + 9) = 8;
        } else if (temp_t6 == 2) {
            *(u8 *)((u8 *)arg0 + 0xA) = (u8) temp_t6;
            *(u8 *)((u8 *)arg0 + 8) = temp_t7;
            *(s8 *)((u8 *)arg0 + 9) = (s8) (arg3 & 0xFF);
        } else if (temp_t6 == 1) {
            *(u8 *)((u8 *)arg0 + 0xA) = 0U;
            *(u8 *)((u8 *)arg0 + 7) = temp_t7;
            *(u8 *)((u8 *)arg0 + 8) = temp_t7;
        }
        if (D_800DBFF4 != 0) {
            *(u8 *)((u8 *)arg0 + 7) = (u8) *(u8 *)((u8 *)arg0 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506160C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506160C.s")
/* Call context: func_15060F28: unique active project prototype */
void func_15060F28(u8 *, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150617BC CURRENT (2200) */
void func_150617BC(u8 *arg0) {
    s32 var_a0;
    s32 selected;
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u8 *var_a1;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0_2;

    if (*(s32 *)((u8 *)arg0 + 0) != 0) {
        var_a0 = D_80082FA0;
        var_a3 = 1;
        var_a2 = 0;
        var_a1 = arg0;
        if (var_a0 >= 0) {
            do {
                selected = *(u8 *)((u8 *)arg0 + 0xF) & var_a3;
                var_a3 *= 2;
                if (selected) {
                    temp_v1 = *(u8 *)((u8 *)var_a1 + 0xB);
                    if ((s32) temp_v1 > 0) {
                        var_v0 = 0;
                        if (*((u8 *)&D_800DBFF4 + var_a2) == 0) {
                            var_v0 = temp_v1 - 0x32;
                            if (var_v0 < 0) {
                                var_v0 = 0;
                            }
                        }
                        *(u8 *)((u8 *)var_a1 + 0xB) = (u8) var_v0;
                        var_a0 = D_80082FA0;
                    }
                } else {
                    temp_v1_2 = *(u8 *)((u8 *)var_a1 + 0xB);
                    if ((s32) temp_v1_2 < 0xFF) {
                        var_v0_2 = 0xFF;
                        if (*((u8 *)&D_800DBFF4 + var_a2) == 0) {
                            var_v0_2 = temp_v1_2 + 0x32;
                            if (var_v0_2 >= 0x100) {
                                var_v0_2 = 0xFF;
                            }
                        }
                        *(u8 *)((u8 *)var_a1 + 0xB) = (u8) var_v0_2;
                        var_a0 = D_80082FA0;
                    }
                }
                var_a2 += 1;
                var_a1 += 1;
            } while (var_a0 >= var_a2);
        }
        if (*(u8 *)((u8 *)arg0 + 0xA) != 0) {
            temp_v1_3 = *(u8 *)((u8 *)arg0 + 8);
            var_a0_2 = *(u8 *)((u8 *)arg0 + 7);
            if (temp_v1_3 != var_a0_2) {
                if ((s32) var_a0_2 < (s32) temp_v1_3) {
                    var_v0_3 = var_a0_2 + *(u8 *)((u8 *)arg0 + 9);
                    if ((s32) temp_v1_3 < var_v0_3) {
                        goto block_22;
                    }
                } else {
                    var_v0_3 = var_a0_2 - *(u8 *)((u8 *)arg0 + 9);
                    if (var_v0_3 < (s32) temp_v1_3) {
block_22:
                        var_v0_3 = (s32) temp_v1_3;
                    }
                }
                *(u8 *)((u8 *)arg0 + 7) = (u8) var_v0_3;
                var_a0_2 = var_v0_3 & 0xFF;
            }
            if (*(u8 *)((u8 *)arg0 + 8) == var_a0_2) {
                temp_v0 = *(u8 *)((u8 *)arg0 + 0xA);
                if (temp_v0 == 6) {
                    func_15060F28(arg0, 1);
                    return;
                }
                if (temp_v0 == 5) {
                    func_15060F28(arg0, 2);
                    return;
                }
                *(u8 *)((u8 *)arg0 + 0xA) = 0U;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150617BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150617BC.s")
s32 func_1506196C(u8 *arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = *(u8 *)((u8 *)arg0 + 7) * *(u8 *)((u8 *)(arg0 + arg1) + 0xB);
    if (var_v1 == 0xFE01) {
        var_v1 = 0xFF;
    } else {
        var_v1 >>= 8;
    }
    return var_v1;
}
s32 func_150623F4(u8 *);                            /* extern */
void *func_15083E90(u8);                            /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150619A8 CURRENT (3880) */
void func_150619A8(void) {
    u8 sp5C[25];
    s32 *var_s0;
    s32 var_s0_2;
    s32 var_s4_2;
    s32 var_s6;
    u8 *var_s5;
    u8 temp_a0;
    u8 temp_v0;
    s32 var_s4;
    u8 *temp_s3;
    u8 *temp_v0_2;
    u8 *var_s1;

    var_s6 = 0;
    var_s0 = &D_800CC2D0;
    var_s4 = 0;
    do {
        if (*(s32 *)((u8 *)var_s0 + 0) != 0) {
            temp_v0 = *(u8 *)((u8 *)var_s0 + 0x2FD);
            if (temp_v0 != 0) {
                *(u8 *)((u8 *)var_s0 + 0x2FD) = (u8) (temp_v0 - 1);
            }
            func_150617BC((u8 *) var_s0);
            if (func_150623F4((u8 *) var_s0) != 0) {
                *(u8 *)((u8 *)var_s0 + 0x2FA) = (u8) (*(u8 *)((u8 *)var_s0 + 0x2FA) | 1);
            } else {
                *(u8 *)((u8 *)var_s0 + 0x2FA) = (u8) (*(u8 *)((u8 *)var_s0 + 0x2FA) & ~1);
                if ((*(u8 *)((u8 *)var_s0 + 0x20B) != 0) || (*(u8 *)((u8 *)var_s0 + 0x20C) != 0) || (*(u8 *)((u8 *)var_s0 + 0x20D) != 0) || (*(u8 *)((u8 *)var_s0 + 0x20E) != 0)) {
                    sp5C[var_s6] = var_s4;
                    var_s6 += 1;
                }
            }
        }
        var_s4 += 1;
        var_s0 = (s32 *)((u8 *)var_s0 + 0x32C);
    } while ((s32) var_s4 < 0x19);
    if (var_s6 != 0) {
        var_s4_2 = 0;
        if (var_s6 > 0) {
            var_s5 = sp5C;
            do {
                temp_s3 = (void *)((*var_s5 * 0x32C) + (u8 *)&D_800CC2D0);
                var_s1 = temp_s3;
                var_s0_2 = 0;
loop_16:
                temp_a0 = *(u8 *)((u8 *)var_s1 + 0x20B);
                if ((temp_a0 != 0) && (temp_v0_2 = func_15083E90(temp_a0), (temp_v0_2 != 0)) && (*(u8 *)((u8 *)temp_v0_2 + 0x2FA) & 1)) {
                    *(u8 *)((u8 *)temp_s3 + 0x2FA) = (u8) (*(u8 *)((u8 *)temp_s3 + 0x2FA) | 1);
                } else {
                    var_s0_2 += 1;
                    var_s1 += 1;
                    if (var_s0_2 != 4) {
                        goto loop_16;
                    }
                }
                var_s4_2 += 1;
                var_s5 += 1;
            } while (var_s4_2 != var_s6);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150619A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150619A8.s")
/* Shared model-specific updates. The 0x15061FA8..0x1506208C branch selects
 * model 75 (Haybot); within that branch +0x69 is its selector phase.
 * Do not name this entire routine or the shared actor field after Haybot.
 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15061B4C.s")
s32 func_150A6360(void *, void *, f32, f32, f32, f32, f32, f32);
extern f32 D_80099694;
extern s32 D_800BE628;
extern u8 D_800D9C10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150623F4 CURRENT (1405) */
s32 func_150623F4(u8 *actor) {
    f32 radius;
    f32 height;
    f32 margin;
    register f32 dx, dz, centerX, centerZ, radiusSquared;
    register s32 count, owner, players;
    s32 index, offset, clear;
    u32 sum;
    register u32 circleRadius;
    register u8 *header, *cursor, *end, *circle;
    u8 *matrix;

    header = *(u8 **)(actor + 0x144);
    if (header != 0) radius = (f32)(u32)*(u16 *)(header + 0x2A);
    else radius = 0.0f;
    if (radius == 0.0f) return 1;
    if (actor[0x127] != 0xFF) return 1;
    if (D_800C3638 != 0 && func_150229E4(actor) != 0) return 1;
    sum = 0;
    cursor = actor;
    count = D_80082FA0;
    if (count >= 0) {
        end = count + actor;
        do {
            sum += cursor[0xB];
            cursor++;
        } while ((u32)cursor <= (u32)end);
    }
    if (sum == 0) return 0;
    if ((actor[0x74] & 0xF) != 0xF) return 1;
    owner = actor[0x13F];
    if (*(owner + (u8 *)D_800D2108) != 0) {
        players = D_8008FD8C;
        clear = 1;
        index = 0;
        if (players > 0) {
            circle = ((u8 **)D_800D2104)[owner];
            cursor = (u8 *)&D_800CC2D0;
            circleRadius = *(u16 *)(circle + 6);
            centerX = *(s16 *)circle;
            centerZ = *(s16 *)(circle + 4);
            radiusSquared = (f32)(s32)(circleRadius * circleRadius);
circle_next:
            index++;
            dx = centerX - *(f32 *)(cursor + 0x14);
            dz = centerZ - *(f32 *)(cursor + 0x1C);
            if (dx * dx + dz * dz < radiusSquared) {
                clear = 0;
            } else {
                cursor += 0x32C;
                if (index < players) goto circle_next;
            }
        }
        if (clear == 0) return 1;
    }
    height = (f32)*(s16 *)(D_800D1C90[actor[4]] + 0x10) * *(f32 *)(actor + 0x150);
    matrix = D_800D9C10;
    index = 0;
    offset = 0;
    if (count >= 0) {
        clear = 1;
        margin = D_80099694;
        do {
            if (func_150A6360(offset + (u8 *)D_800BE628, matrix,
                *(f32 *)(actor + 0x14), *(f32 *)(actor + 0x18) + height,
                *(f32 *)(actor + 0x1C), radius, radius, margin) != 0) {
                clear = 0;
                break;
            }
            index++;
            offset += 0x180;
            matrix += 0x40;
        } while (D_80082FA0 >= index);
    }
    if (clear == 0) return 1;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150623F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150623F4.s")
extern s32 D_800D121C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150626EC CURRENT (1139) */
void func_150626EC(s32 arg0, s32 arg1) {
    s32 var_v0;
    u8 *var_s0;
    u8 *var_s3;

    var_s0 = (u8 *)&D_800CC2D0;
    var_s3 = (u8 *)&D_800CC2D0;
    var_v0 = 0;
    do {
        if ((*(s32 *)var_s0 != 0) && ((((arg0 - (s32)var_s3) / 812) + 1) == var_s0[0x65]) && (var_s0[0x127] == 0xFF)) {
            func_15060F28(var_s0, arg1);
        }
        var_s0 += 0x32C;
    } while (var_s0 != (u8 *)&D_800D121C);
    (void)var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150626EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150626EC.s")
void func_1503B840(void *arg0);
void func_15039CC8(void *arg0);

void func_150627D4(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x2FB) = 0;
    func_1503B840(arg0);
    func_15039CC8(arg0);
}
typedef struct Game83300SwapChild {
    u8 pad0[0x197];
    u8 field197;
} Game83300SwapChild;

typedef struct Game83300SwapView {
    u8 pad0[0x3D4];
    Game83300SwapChild *child;
    u8 pad3D8[0x5C8];
} Game83300SwapView;

/* Whole actor copies and bank arithmetic prove strides 0x32C and 0x9A0. */
typedef struct Game83300SwapActor {
    s32 active;
    u8 pad4[0x37];
    u8 generation;
    u8 pad3C[0x29];
    u8 owner;
    u8 pad66[0xC1];
    s8 slot127;
    u8 pad128[0x14];
    u8 link;
    u8 peer;
    u8 pad13E;
    s8 slot13F;
    u8 pad140[4];
    s32 header;
    u8 pad148[0x18C];
    u8 *effect;
    u8 pad2D8[0x40];
    Game83300SwapView *view;
    Game83300SwapChild *child;
    u8 pad320[0xC];
} Game83300SwapActor;

void func_15146508(void *, void *);
void func_15033EC4(s32, s32);
void func_150615DC(void *);
extern Game83300SwapView *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062800 CURRENT (4339) */
void func_15062800(Game83300SwapActor *arg0, Game83300SwapActor *arg1) {
    Game83300SwapActor copy;
    s32 secondIndex;
    s32 firstIndex;
    s32 secondGeneration;
    s32 firstGeneration;
    s32 header;
    s32 viewOffset;
    s32 i;
    s32 owner;
    Game83300SwapActor *actor;
    Game83300SwapActor *table;

    func_15146508(arg0, arg1);
    func_10023A10(arg1, &copy, 0x32C);
    func_10023A10(arg0, arg1, 0x32C);
    func_10023A10(&copy, arg0, 0x32C);
    table = (Game83300SwapActor *) &D_800CC2D0;
    secondIndex = ((s32) arg1 - (s32) table) / 0x32C;
    firstIndex = ((s32) arg0 - (s32) table) / 0x32C;
    secondGeneration = secondIndex + 1;
    arg1->slot127 = secondIndex;
    arg1->generation = secondGeneration;
    arg1->slot13F = secondIndex;
    viewOffset = secondIndex * 0x9A0;
    arg1->view = (Game83300SwapView *) ((u8 *) D_800DBFF0 + viewOffset);
    firstGeneration = firstIndex + 1;
    arg0->slot127 = firstIndex;
    arg0->generation = firstGeneration;
    arg0->slot13F = firstIndex;
    arg0->view = 0;
    header = arg0->header;
    arg0->header = arg1->header;
    arg1->header = header;
    ((Game83300SwapView *) ((u8 *) D_800DBFF0 + viewOffset))->child = arg1->child;
    arg1->child->field197 = 0;
    func_15033EC4(arg1->generation, arg0->generation);
    if (arg1->effect != 0) {
        func_1516972C(arg1->effect);
        arg1->effect = 0;
    }
    if (arg0->effect != 0) {
        func_1516972C(arg0->effect);
        arg0->effect = 0;
    }
    func_150615DC(arg1);
    i = 0;
    do {
        if (i != secondIndex && i != firstIndex) {
            actor = (Game83300SwapActor *) ((u8 *) &D_800CC2D0 + i * 0x32C);
            if (actor->active != 0) {
                owner = actor->owner;
                if (owner != 0) {
                    owner--;
                    if (owner == secondIndex) {
                        actor->owner = firstGeneration;
                    } else if (owner == firstIndex) {
                        actor->owner = secondGeneration;
                    }
                }
            }
        }
        i++;
    } while (i != 25);
    owner = arg1->link;
    if (owner >= 100) {
        actor = (Game83300SwapActor *) ((u8 *) &D_800CC2D0 + ((owner - 100) & 0xFF) * 0x32C);
        actor->peer = secondIndex + 100;
    }
    func_150627D4(arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062800 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062800.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062AC4 CURRENT (260) */
void func_15062AC4(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0xE6);
    if (temp_v0 != 0) {
        temp_v1 = *(s16 *)((u8 *)arg0 + 0xE4);
        if (temp_v1 != 0) {
            temp_fv0 = (f32) temp_v1;
            temp_fv1 = (f32) temp_v0;
            *(f32 *)((u8 *)arg0 + 0xEC) = (f32) (temp_fv0 / temp_fv1);
            *(f32 *)((u8 *)arg0 + 0xF0) = (f32) (temp_fv1 / temp_fv0);
            return;
        }
    }
    *(f32 *)((u8 *)arg0 + 0xEC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0xF0) = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062AC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062AC4.s")
void func_15062AC4(void *);
void func_15062B84(void *);

void func_15062B1C(void *arg0, f32 arg1) {
    *(s16 *)((u8 *)arg0 + 0xE4) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14C) * arg1);
    func_15062AC4(arg0);
}
void func_15062B50(void *arg0, f32 arg1) {
    *(s16 *)((u8 *)arg0 + 0xE6) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x150) * arg1);
    func_15062AC4(arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062B84 CURRENT (260) */
void func_15062B84(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0xD4);
    if (temp_v0 != 0) {
        temp_v1 = *(s16 *)((u8 *)arg0 + 0xD2);
        if (temp_v1 != 0) {
            temp_fv0 = (f32) temp_v1;
            temp_fv1 = (f32) temp_v0;
            *(f32 *)((u8 *)arg0 + 0xDC) = (f32) (temp_fv0 / temp_fv1);
            *(f32 *)((u8 *)arg0 + 0xE0) = (f32) (temp_fv1 / temp_fv0);
            return;
        }
    }
    *(f32 *)((u8 *)arg0 + 0xDC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0xE0) = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062B84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062B84.s")
extern u8 *D_800D1C90[];

void func_15062BDC(u8 *arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    f32 temp_fv1;
    u8 temp_v1;
    u8 *temp_v0;

    temp_v1 = arg0[4];
    *(f32 *)(arg0 + 0x14C) = arg1;
    *(f32 *)(arg0 + 0x150) = arg2;
    if (temp_v1 != 0xFF) {
        temp_v0 = D_800D1C90[temp_v1];
        temp_fv1 = *(f32 *)(arg0 + 0x14C);
        temp_fv0 = *(f32 *)(arg0 + 0x150);
        *(s16 *)(arg0 + 0xD2) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x20) * temp_fv1);
        *(s16 *)(arg0 + 0xD4) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x22) * temp_fv0);
        *(s16 *)(arg0 + 0xD6) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x24) * temp_fv0);
        *(s16 *)(arg0 + 0xE4) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x1A) * temp_fv1);
        *(s16 *)(arg0 + 0xE6) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x1C) * temp_fv0);
        *(s16 *)(arg0 + 0xE8) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x1E) * temp_fv0);
        func_15062AC4(arg0);
        func_15062B84(arg0);
    }
}
extern u8 D_800C4488[];
extern u8 D_800D19A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062D10 CURRENT (385) */
void func_15062D10(s32 arg0, volatile s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a3;

    temp_v0 = arg0 * 4;
    if (*(s32 *)(D_800D19A0 + temp_v0) != 0) {
        temp_a3 = *(u8 **)(*(u8 **)(D_800C4488 + temp_v0) +
                              (arg4 * 4)) +
                  (arg1 * 8);
        temp_a2 = *(s32 *)(temp_a3 + 4);
        temp_v1 = ((temp_a2 >> 0xC) & 0xFFF) + 2;
        temp_a0 = (temp_a2 & 0xFFF) + 2;
        temp_a2 = *(s32 *)temp_a3;
        if (arg5 != 0) {
            var_v0 = arg2 & 0xFFF;
        } else {
            temp_a1 = ((temp_a2 >> 0xC) & 0xFFF) + arg2;
            var_v0 = temp_a1;
            if (temp_v1 < temp_a1) {
                var_v0 = temp_a1 - temp_v1;
            } else if (temp_a1 < 0) {
                var_v0 = temp_a1 + temp_v1;
            }
        }
        if (arg5 != 0) {
            var_v1 = arg3 & 0xFFF;
        } else {
            temp_a1_2 = (temp_a2 & 0xFFF) + arg3;
            var_v1 = temp_a1_2;
            if (temp_a0 < temp_a1_2) {
                var_v1 = temp_a1_2 - temp_a0;
            } else if (temp_a1_2 < 0) {
                var_v1 = temp_a1_2 + temp_a0;
            }
        }
        *(s32 *)temp_a3 = (temp_a2 & 0xFF000000) |
                           (var_v1 & 0xFFF) | ((var_v0 & 0xFFF) << 0xC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062D10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062D10.s")
void func_15094AB8(s32, s32, s32, f32, s32, s32);
extern u8 D_800BE9C0;
extern u8 *D_800C5338[];
extern void *D_800C6360[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062E24 CURRENT (2370) */
void func_15062E24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6) {
    u8 *actor;
    u8 *table;
    u8 *entry;
    u8 *target;
    s32 i;
    u16 width;
    u16 height;

    table = (u8 *)&D_800C6360[arg0];
    i = 0;
    if (*(s32 *)table != 0) {
        actor = (u8 *)&D_800CC2D0;
        do {
            if (*(s32 *)actor != 0 && actor[4] == arg0 && actor[0x2FA] != 0) {
                entry = D_800C5338[arg0] + (arg5 * 0xC);
                width = *(u16 *)(entry + 8);
                height = *(u16 *)(entry + 0xA);
                if (arg6 != 0) {
                    width *= 2;
                    height *= 2;
                }
                target = (u8 *)&D_800CC2D0 + (i * 0x32C) + (D_800BE9C0 * 4);
                target = *(u8 **)(target + 0x28C);
                if (target != 0) {
                    func_15094AB8((s32)target + (arg1 * 0x10),
                                   *(s32 *)table + (arg3 * 4), arg2,
                                   (f32)arg4, height, width);
                }
            }
            i++;
            actor += 0x32C;
        } while (i != 0x19);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062E24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062E24.s")
typedef struct Game83300MorphVertex {
    u8 pad0[8];
    s16 x;
    s16 y;
    u8 padC[4];
} Game83300MorphVertex;

typedef struct Game83300MorphObject {
    u8 pad0[4];
    u8 modelIndex;
    u8 pad5[0x1C3];
    u8 channel;
    u8 pad1C9[0xC3];
    Game83300MorphVertex *buffers[4];
} Game83300MorphObject;

extern s32 *D_800C4020[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062FC0 CURRENT (315) */
void func_15062FC0(Game83300MorphObject *arg0, s32 arg1, u8 arg2,
                   s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    u8 *channelBase;
    Game83300MorphVertex *source;
    Game83300MorphVertex *target;
    s32 offset;
    s32 i;

    channelBase = (u8 *)arg0 + (arg0->channel * 8);
    target = *(Game83300MorphVertex **)(channelBase + 0x28C + D_800BE9C0 * 4);
    source = *(Game83300MorphVertex **)(channelBase + 0x28C + (D_800BE9C0 == 0) * 4);
    if (target == 0) {
        return;
    }
    if (arg1 != -1) {
        offset = D_800C4020[arg0->modelIndex][arg1] * 0x10;
        target = (Game83300MorphVertex *)((u8 *)target + offset);
        source = (Game83300MorphVertex *)((u8 *)source + offset);
    }
    if (arg6 != 0) {
        if (arg3 < target->x) {
            arg6 -= arg3;
        } else if (target->x < 0) {
            arg6 += arg3;
        }
    }
    if (arg7 != 0) {
        if (arg4 < target->y) {
            arg7 -= arg4;
        } else if (target->y < 0) {
            arg7 += arg4;
        }
    }
    for (i = 0; i < arg5; i++) {
        target[i].x = source[i].x + arg6;
        target[i].y = source[i].y + arg7;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062FC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062FC0.s")
typedef struct Game83300Nested63168 {
    u8 pad0[0x1AC];
    u8 active;
} Game83300Nested63168;

typedef struct Game83300Actor63168 {
    u8 pad0[0x31C];
    Game83300Nested63168 *nested;
    u8 pad320[0xC];
} Game83300Actor63168;

void func_15194FF4(Game83300Actor63168 *, Game83300Actor63168 *, s32);
extern s8 D_8008FD8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063168 CURRENT (675) */
void func_15063168(Game83300Actor63168 *arg0) {
    Game83300Actor63168 *other;
    Game83300Nested63168 *nested;
    s32 index;
    s32 self_index;

    index = 0;
    if (D_8008FD8C > 0) {
        self_index = ((s32)arg0 - (s32)&D_800CC2D0) / 0x32C;
        do {
            if ((index != self_index) && ((1 << index) & D_800CC268)) {
                other = (Game83300Actor63168 *)((u8 *)&D_800CC2D0 + (index * 0x32C));
                nested = other->nested;
                if ((nested != 0) && (nested->active == 0)) {
                    func_15194FF4(arg0, other, 1);
                }
            }
            index++;
        } while (index < D_8008FD8C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063168 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15063168.s")
void func_15082A44(void *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063254 CURRENT (723) */
void func_15063254(u8 *arg0, s32 arg1, s32 arg2, f32 arg3) {
    s32 sp50;
    void *saved_ptr;
    void *volatile sp48;
    volatile f32 sp44;
    volatile f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    volatile s32 sp2C;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_v0;
    void *temp_s1;

    sp50 = arg0[0x13F];
    temp_s1 = *(void **)(arg0 + 0x144);
    *(s8 *)((u8 *)temp_s1 + 4) = arg1;
    *(s8 *)((u8 *)temp_s1 + 3) = arg2;
    *(f32 *)((u8 *)temp_s1 + 0x20) = arg3;
    *(f32 *)((u8 *)temp_s1 + 0x24) = arg3;
    *(s8 *)((u8 *)temp_s1 + 2) = 0;
    sp48 = *(void **)(arg0 + 0x318);
    temp_fv0 = *(f32 *)(arg0 + 0x14);
    temp_fv1 = *(f32 *)(arg0 + 0x18);
    sp3C = *(f32 *)(arg0 + 0x1C);
    sp38 = *(f32 *)(arg0 + 0xB8);
    sp34 = *(f32 *)(arg0 + 0x40);
    sp30 = *(f32 *)(arg0 + 0xC4);
    temp_v0 = *(u16 *)(arg0 + 0x76);
    sp44 = temp_fv0;
    sp40 = temp_fv1;
    sp2C = temp_v0;
    func_15060F28(arg0, 0);
    func_15082A44(temp_s1, sp50, 0, 0,
                  (((s32)arg0 - (s32)&D_800CC2D0) / 812) + 1);
    temp_v0 = sp2C;
    temp_fv0 = sp44;
    temp_fv1 = sp40;
    saved_ptr = sp48;
    *(f32 *)(arg0 + 0x14) = temp_fv0;
    *(f32 *)(arg0 + 0x18) = temp_fv1;
    *(void **)(arg0 + 0x318) = saved_ptr;
    *(f32 *)(arg0 + 0x1C) = sp3C;
    *(f32 *)(arg0 + 0xB8) = sp38;
    *(f32 *)(arg0 + 0x40) = sp34;
    *(u16 *)(arg0 + 0x76) = temp_v0;
    *(u16 *)(arg0 + 0x7A) = temp_v0;
    *(f32 *)(arg0 + 0x2C) = temp_fv0;
    *(f32 *)(arg0 + 0x30) = temp_fv1;
    *(f32 *)(arg0 + 0x1CC) = *(f32 *)(arg0 + 0x18);
    *(f32 *)(arg0 + 0x34) = *(f32 *)(arg0 + 0x1C);
    *(f32 *)(arg0 + 0xC4) = sp30;
    *(s32 *)((u8 *)saved_ptr + 0x3D4) = *(s32 *)(arg0 + 0x31C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063254 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15063254.s")
