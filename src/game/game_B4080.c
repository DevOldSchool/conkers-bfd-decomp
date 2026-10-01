#include "types.h"

/*
 * Reviewed source unit: src/game/game_B4080.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15086D48
 * - func_15086D94
 * - func_150870D0
 * - func_15087350
 * - func_15087CC0
 * - func_15087E54
 * - func_150881CC
 * - func_15088270
 * - func_150882B0
 * - func_150882E4
 * - func_150883B0
 * - func_1508855C
 * - func_150885EC
 * - func_1508868C
 * - func_150888A8
 * - func_15088A08
 * - func_15088D58
 * - func_15088F30
 * - func_1508907C
 * - func_150891E8
 * - func_150896EC
 * - func_15089BC0
 * - func_15089F9C
 * - func_1508A1BC
 * - func_1508A6FC
 * - func_1508B20C
 * - func_1508B2A8
 * - func_1508B3F8
 * - func_1508B9BC
 * - func_1508BC20
 * - func_1508BF14
 * - func_1508C1A4
 * - func_1508C5B8
 * - func_1508CA88
 * - func_1508CAD8
 * - func_1508D850
 * - func_1508DA1C
 * - func_1508DC24
 * - func_1508E89C
 * - func_1508ECC0
 * - func_1508EE0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 *D_800D2350;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_15086BD0(s32 arg0, s32 arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    s16 (*base)[8];
    u8 *temp_a2;
    u8 *temp_v1;

    if ((arg0 == 0xFF) || (arg1 == 0xFF)) {
        return 0.0f;
    }
    base = (s16 (*)[8])D_800D2350;
    temp_v1 = (u8 *)base[arg0];
    temp_a2 = (u8 *)base[arg1];
    temp_fv1 = (f32) (*(s16 *)((u8 *)temp_v1 + 0) - *(s16 *)((u8 *)temp_a2 + 0));
    temp_fa0 = (f32) (*(s16 *)((u8 *)temp_v1 + 2) - *(s16 *)((u8 *)temp_a2 + 2));
    temp_fa1 = (f32) (*(s16 *)((u8 *)temp_v1 + 4) - *(s16 *)((u8 *)temp_a2 + 4));
    return sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
}
void func_15086C68(void) {

}
void func_150A3194(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4);

void func_15086C70(s32 arg0) {
    s32 offset;
    s32 temp_v1;
    u8 *temp_v0;

    offset = arg0 * 0x10;
    temp_v0 = D_800D2350 + offset;
    temp_v1 = *(s16 *)((u8 *)temp_v0 + 4);
    func_150A3194(3, 0xB, *(s16 *)((u8 *)temp_v0 + 0), *(s16 *)((u8 *)temp_v0 + 2), temp_v1);
}
extern s16 D_80087290;

s32 func_15086CBC(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 temp_v1;

    if ((arg0 < 0) || (arg0 >= D_80087290)) {
        return 0;
    }
    temp_v1 = arg0 * 0x10;
    *arg1 = (f32) *(s16 *)((u8 *)D_800D2350 + temp_v1);
    *arg2 = (f32) *(s16 *)((u8 *)D_800D2350 + temp_v1 + 2);
    *arg3 = (f32) *(s16 *)((u8 *)D_800D2350 + temp_v1 + 4);
    return 1;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15086D48 CURRENT (235) */
s32 func_15086D48(s32 arg0) {
    s32 var_v1;
    u8 *var_a1;

    var_v1 = 0;
    if (D_80087290 > 0) {
        var_a1 = D_800D2350;
        do {
            if (arg0 == var_a1[7]) {
                return var_v1;
            }
            var_v1 += 1;
            var_a1 += 0x10;
        } while (var_v1 < D_80087290);
    }
    return 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15086D48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15086D48.s")
s32 func_15085DA8(f32);                             /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15086D94 CURRENT (9527) */
f32 func_15086D94(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sp54;
    f32 sp50;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs0;
    f32 var_fs4;
    f32 var_ft4;
    s16 temp_a0;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_v1_2;
    s32 temp_v0;
    s32 var_t0;
    s32 var_t3;
    u8 temp_v1;
    u8 *temp_a1;
    u8 *temp_t2;
    u8 *var_t1;

    temp_v0 = func_15085DA8(arg1);
    var_t3 = 0;
    sp50 = 100.0f;
    if (D_80087290 > 0) {
        var_fs4 = sp54;
        do {
            temp_t2 = (void *)((var_t3 * 0x10) + D_800D2350);
            if (*(u8 *)((u8 *)temp_t2 + 0xE) == 1) {
                var_t0 = 0;
                var_t1 = temp_t2;
                if (temp_v0 == *(u8 *)((u8 *)temp_t2 + 6)) {
                    do {
                        temp_v1 = *(u8 *)((u8 *)var_t1 + 9);
                        var_t0 += 1;
                        if ((temp_v1 != 0xFF) && (var_t3 < (s32) temp_v1)) {
                            temp_a1 = (void *)((temp_v1 * 0x10) + D_800D2350);
                            if ((*(u8 *)((u8 *)temp_a1 + 0xE) == 1) && (((temp_a2 = *(s16 *)((u8 *)temp_a1 + 4), temp_v1_2 = *(s16 *)((u8 *)temp_t2 + 4), temp_a0 = *(s16 *)((u8 *)temp_t2 + 0), temp_a3 = *(s16 *)((u8 *)temp_a1 + 0), temp_fa0 = (f32) (temp_a2 - temp_v1_2), temp_fs2 = (f32) temp_a0, temp_fs3 = (f32) temp_v1_2, temp_fa1 = -(f32) (temp_a3 - temp_a0), temp_fv0 = -((temp_fs2 * temp_fa0) + (temp_fa1 * temp_fs3)), temp_ft5 = (arg0 * temp_fa0) + (arg2 * temp_fa1) + temp_fv0, var_ft4 = temp_ft5, temp_fv1 = ((arg0 + arg3) * temp_fa0) + ((arg2 + arg4) * temp_fa1) + temp_fv0, var_fs0 = temp_fv1, (temp_fv1 < 0.0f)) && (temp_ft5 >= 0.0f)) || ((temp_ft5 < 0.0f) && (temp_fv1 >= 0.0f)))) {
                                if (temp_fv1 < 0.0f) {
                                    var_fs0 = -temp_fv1;
                                }
                                if (temp_ft5 < 0.0f) {
                                    var_ft4 = -temp_ft5;
                                }
                                temp_fa0_2 = -temp_fa1;
                                temp_fv1_2 = var_ft4 / (var_ft4 + var_fs0);
                                var_fs4 = temp_fv1_2;
                                temp_fv0_2 = -((temp_fs2 * temp_fa0_2) + (temp_fa0 * temp_fs3));
                                temp_ft4 = (((temp_fv1_2 * arg3) + arg0) * temp_fa0_2) + (((temp_fv1_2 * arg4) + arg2) * temp_fa0) + temp_fv0_2;
                                temp_fs0 = ((f32) temp_a3 * temp_fa0_2) + (temp_fa0 * (f32) temp_a2) + temp_fv0_2;
                                if ((((temp_fs0 > 0.0f) && (temp_ft4 > 0.0f) && (temp_ft4 <= temp_fs0)) || ((temp_fs0 < 0.0f) && (temp_ft4 < 0.0f) && (temp_fs0 <= temp_ft4))) && (var_fs4 < sp50)) {
                                    sp50 = var_fs4;
                                }
                            }
                        }
                        var_t1 += 1;
                    } while (var_t0 != 5);
                }
            }
            var_t3 += 1;
        } while (var_t3 < D_80087290);
        sp54 = var_fs4;
    }
    if (sp50 <= 1.0f) {
        return sqrtf((arg3 * arg3) + (arg4 * arg4)) * sp54;
    }
    return -1.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15086D94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15086D94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150870D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087350.s")
void func_150891E8(void *, void *);
void func_150896EC(void *, void *, s32);
extern s32 D_800872A0;
extern s8 D_800D2398;
extern s8 D_800D23A9;
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15087CC0 CURRENT (844) */
void func_15087CC0(void) {
    s32 var_s0;
    s32 var_s1;
    s8 var_v0;
    u8 *temp_a0;
    u8 *temp_a1;

    D_800D23A9 = 0;
    if (D_800872A0 != 0) {
        var_v0 = D_800D2398;
        var_s0 = 0;
        var_s1 = 0;
        if (var_v0 > 0) {
            do {
                temp_a0 = (u8 *)(var_s1 + D_800872A0);
                temp_a1 = &D_800CC2D0 + (*(s8 *)(temp_a0 + 0x31) * 0x32C);
                if (*(s32 *)(temp_a1 + 0x318) != 0) {
                    if (*(s8 *)(temp_a0 + 0x30) >= 2) {
                        func_150891E8(temp_a0, temp_a1);
                        var_v0 = D_800D2398;
                    } else if (*(u8 *)(temp_a0 + 0x48) == 0) {
                        func_150896EC(temp_a0, temp_a1, 0);
                        var_v0 = D_800D2398;
                    } else if (*(s8 *)(temp_a0 + 0x49) != 0) {
                        func_150896EC(temp_a0, temp_a1, 1);
                        var_v0 = D_800D2398;
                    }
                }
                var_s0++;
                var_s1 += 0x84;
            } while (var_s0 < var_v0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15087CC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087CC0.s")
void func_15087DCC(s32 arg0, s32 arg1) {
    u8 *temp_v1;
    void *sp1C;
    s8 temp_v0;

    if (D_800872A0 != 0) {
        temp_v1 = (void *)((arg0 * 0x84) + D_800872A0);
        if (arg1 != *(s8 *)((u8 *)temp_v1 + 0x2F)) {
            if (arg1 != 0) {
                sp1C = temp_v1;
                temp_v0 = func_150888A8((s32) *(u8 *)((u8 *)temp_v1 + 0x2B), *(u8 *)((u8 *)temp_v1 + 0x2C), 1);
                *(s8 *)((u8 *)temp_v1 + 0x2D) = temp_v0;
                *(s8 *)((u8 *)temp_v1 + 0x2E) = func_150888A8((s32) *(u8 *)((u8 *)temp_v1 + 0x2C), temp_v0 & 0xFF, 1);
            }
            *(s8 *)((u8 *)temp_v1 + 0x2F) = (s8) arg1;
        }
    }
}
/* Call context: func_1505A630: unique active project prototype */
s32 func_1505A630(f32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15087E54 CURRENT (10) */
void func_15087E54(s32 arg0, u8 *arg1) {
    s32 angle;
    s32 delta;
    u16 temp_t7;
    u16 temp_t9;
    u8 *temp_v0;

    if (D_800872A0 != 0) {
        temp_v0 = (void *)((arg0 * 0x84) + D_800872A0);
        angle = (func_1505A630(*(f32 *)((u8 *)temp_v0 + 0x10), *(f32 *)((u8 *)temp_v0 + 0xC), 0) + 0x4000);
        temp_t7 = angle;
        delta = temp_t7 - *(u16 *)((u8 *)arg1 + 0x76);
        temp_t9 = delta & 0xFFFF;
        if (temp_t9 & 0x8000) {
            if (temp_t9 < 0xDBFF) {
                *(u16 *)((u8 *)arg1 + 0x76) = (u16) (temp_t7 + 0x2400);
            }
        } else if (temp_t9 >= 0x2401) {
            *(u16 *)((u8 *)arg1 + 0x76) = (u16) (temp_t7 - 0x2400);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15087E54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087E54.s")
/* Call context: func_1505A630: unique active declaration in the allowed source */
extern s8 D_800D23A8;

void func_15087EF0(s32 arg0, u8 *arg1) {
    union { u8 *entry; s32 angle; } value;
    s32 temp_v0;

    if (D_800872A0 != 0) {
        value.entry = (void *)((arg0 * 0x84) + D_800872A0);
        temp_v0 = func_1505A630(*(f32 *)((u8 *)value.entry + 0x10), *(f32 *)((u8 *)value.entry + 0xC), 0);
        if (D_800D23A8 == 0) {
            if (*(f32 *)((u8 *)value.entry + 0) < 0.5f) {
                value.angle = (temp_v0 + 0x4A00) & 0xFFFF;
            } else {
                value.angle = (temp_v0 + 0x3600) & 0xFFFF;
            }
        } else {
            if (*(f32 *)value.entry >= 0.5f) {
                value.angle = (temp_v0 + 0x4A00) & 0xFFFF;
            } else {
                value.angle = (temp_v0 + 0x3600) & 0xFFFF;
            }
        }
        *(s16 *)((u8 *)arg1 + 0x76) = value.angle;
    }
}
extern s32 D_800872A0;

void func_15087FC4(s32 arg0, s32 arg1) {
    u8 *entry;

    if (D_800872A0 != 0) {
        entry = (u8 *)((arg0 * 0x84) + D_800872A0);
        *(s8 *)(entry + 0x31) = arg1;
    }
}
extern s32 D_800872A0;

void func_15087FEC(s32 arg0, s32 arg1) {
    u8 *entry;

    if (D_800872A0 != 0) {
        entry = (u8 *)((arg0 * 0x84) + D_800872A0);
        *(f32 *)(entry + 4) = (f32) ((f32) arg1 * 0.00390625f);
    }
}
s32 func_1507BB28(s32, s32);
extern u8 D_800CC2D0;
extern s8 D_800C3E78;
extern void *D_800D154C;
extern u16 D_800D18A0;

s32 func_1508802C(u8 *arg0, u8 *arg1, s32 arg2) {
    void *object;

    object = *(void **)(arg1 + 0x31C);
    if (*(u8 *)((u8 *)object + 0x120) != 0) {
        return 1;
    }
    if (D_800D18A0 & (1 << ((arg1 - &D_800CC2D0) / 0x32C))) {
        return 1;
    }
    *(u8 *)((u8 *)object + 0x84) = 1;
    *(s32 *)arg1 = 0xC;
    *(s8 *)(arg1 + 0x232) = arg2;
    D_800D154C = arg1;
    D_800C3E78 = *(s8 *)(arg0 + 0x31);
    *(s32 *)(arg1 + 0x218) = func_1507BB28(0, arg2);
    *(s16 *)(arg1 + 0x21C) = 0;
    *(u8 *)(arg1 + 0x125) = 0xFF;
    *(s8 *)(arg0 + 0x30) = 2;
    return 0;
}
extern s8 D_800D239A;

s32 func_150880F8(s32 arg0, s32 arg1) {
    u8 *entry;
    u8 *actor;
    s32 result;
    s8 state;

    result = 0;
    if (D_800872A0 == 0) {
        return 0;
    }
    entry = (u8 *)(D_800872A0 + (arg0 * 0x84));
    state = *(s8 *)(entry + 0x30);
    actor = (u8 *)&D_800CC2D0 + (*(s8 *)(entry + 0x31) * 0x32C);
    if (state == 0) {
        result = func_1508802C(entry, actor, arg1);
    } else if (state == 1) {
        *(s8 *)(entry + 0x30) = 2;
        *(u8 *)(actor + 0x125) = 0xFF;
    }
    *(s8 *)(entry + 0x2A) = D_800D239A;
    D_800D239A++;
    return result;
}
extern s32 D_800872A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150881CC CURRENT (110) */
s32 func_150881CC(u8 *arg0) {
    s32 temp_v1;

    temp_v1 = D_800872A0;
    if (temp_v1 == 0) {
        return 0;
    }
    return (s32) (*(f32 *)((u8 *)temp_v1 + ((s32) arg0 * 0x84)) * 256.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150881CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150881CC.s")
extern s32 D_800872A0;

s32 func_15088218(s32 arg0) {
    u8 *temp_a0;
    s32 temp_a2;
    s32 temp_v0;

    if (D_800872A0 == 0) {
        return 0;
    }
    temp_a0 = (void *)((arg0 * 0x84) + D_800872A0);
    temp_a2 = *(s16 *)((u8 *)temp_a0 + 0x24);
    temp_v0 = temp_a2 * 0x10;
    temp_v0 += (s32) (*(f32 *)((u8 *)temp_a0 + 8) * 16.0f);
    return temp_v0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15088270 CURRENT (195) */
s32 func_15088270(s32 arg0) {
    s32 base = D_800872A0;
    s32 index = arg0;

    if (base == 0) {
        return 0;
    }
    arg0 = (index * 0x84) + base;
    return (s32) *(f32 *)((u8 *)arg0 + 0x14);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15088270 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15088270.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150882B0 CURRENT (220) */
s8 func_150882B0(s32 arg0) {
    if (D_800872A0 == 0) {
        return 0;
    }
    return *(s8 *)((u8 *)((arg0 * 0x84) + D_800872A0) + 0x27);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150882B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150882B0.s")
extern s8 D_800D2398;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150882E4 CURRENT (20) */
s32 func_150882E4(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_a2;
    void *temp_v1;
    s32 var_a3;
    s32 group;

    if (D_800872A0 == 0) {
        return 0x10;
    }
    temp_v1 = (void *)((arg0 * 0x84) + D_800872A0);
    group = *(s8 *)((u8 *)temp_v1 + 0x29) + arg1;
    var_a3 = 0;
    if (D_800D2398 > 0) {
        var_a2 = D_800872A0;
        do {
        if ((group == *(s8 *)((u8 *)var_a2 + 0x29)) && (var_a3 != arg0)) {
            var_a0 = (*(s16 *)((u8 *)temp_v1 + 0x24) * 0x10) + (s32)(*(f32 *)((u8 *)temp_v1 + 8) * 16.0f);
            var_a0 = (var_a0 - *(s16 *)((u8 *)var_a2 + 0x24) * 0x10) - (s32)(*(f32 *)((u8 *)var_a2 + 8) * 16.0f);
            if (var_a0 < 0) {
                var_a0 = -var_a0;
            }
            return (var_a0 << 8) | var_a3;
        }
        var_a3++;
        var_a2 += 0x84;
        } while (var_a3 < D_800D2398);
    }
    return 0x10;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150882E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150882E4.s")
typedef struct GameB4080SearchEntry {
    f32 value0;
    f32 value4;
    f32 phase8;
    f32 directionC;
    f32 direction10;
    u8 pad14[0x18];
    u8 node2C;
    u8 pad2D[2];
    s8 group2F;
    u8 pad30;
    s8 actor31;
    u8 pad32[0x52];
} GameB4080SearchEntry;

typedef struct GameB4080SearchActor {
    u8 pad0[0x14];
    f32 field14;
    f32 field18;
    f32 field1C;
    u8 pad20[0x20];
    f32 angle40;
    u8 pad44[0x32];
    s16 rotation76;
    s16 rotation78;
    s16 rotation7A;
    u8 pad7C[0xA8];
    u8 field124;
} GameB4080SearchActor;

extern f32 D_8009DA00;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150883B0 CURRENT (1234) */
void *func_150883B0(s32 arg0, s32 arg1, f32 *arg2, s32 *arg3) {
    GameB4080SearchEntry *entry;
    GameB4080SearchEntry *other;
    GameB4080SearchActor *actor;
    GameB4080SearchActor *otherActor;
    GameB4080SearchActor *winner;
    f32 best;
    f32 baseline;
    f32 dz;
    f32 dx;
    f32 sign;
    f32 distance;
    s32 index;
    s32 byteOffset;
    s8 group;
    s8 actorIndex;

    if (D_800872A0 == 0) {
        return 0;
    }
    entry = (GameB4080SearchEntry *)(D_800872A0 + arg0 * 0x84);
    if (arg1 >= 0) {
        sign = -1.0f;
    } else {
        sign = 1.0f;
    }
    dx = entry->directionC * sign;
    dz = entry->direction10 * sign;
    group = entry->group2F;
    actor = (GameB4080SearchActor *)((u8 *)&D_800CC2D0 + entry->actor31 * 0x32C);
    actorIndex = (s8)(actor->field124 - 1);
    baseline = -((dx * actor->field14) + (dz * actor->field1C));
    winner = 0;
    best = D_8009DA00;
    index = 0;
    if (D_800D2398 > 0) {
        byteOffset = 0;
        do {
            other = (GameB4080SearchEntry *)(byteOffset + D_800872A0);
            index++;
            if (actorIndex != other->actor31 &&
                (group == 0 || group == other->group2F)) {
                otherActor = (GameB4080SearchActor *)((u8 *)&D_800CC2D0 + other->actor31 * 0x32C);
                distance = (dx * otherActor->field14) + (dz * otherActor->field1C) + baseline;
                if (distance > 0.0f && distance < best) {
                    best = distance;
                    *arg2 = other->value0;
                    *arg3 = other->group2F;
                    winner = (GameB4080SearchActor *)((u8 *)&D_800CC2D0 + other->actor31 * 0x32C);
                }
            }
            byteOffset += 0x84;
        } while (index < D_800D2398);
    }
    return winner;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150883B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150883B0.s")
extern u8 D_800CC2D0;
extern s8 D_800D2399;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508855C CURRENT (785) */
s32 func_1508855C(s32 arg0) {
    u8 *temp_v1;
    s32 temp_a1;
    s32 temp_lo;
    s32 var_a0;
    u8 *var_a2;

    temp_v1 = (u8 *) D_800872A0;
    if (temp_v1 == 0) {
        return -1;
    }
    temp_lo = (s32) (arg0 - (s32) &D_800CC2D0) / 0x32C;
    if (temp_lo == 0) {
        return 0;
    }
    var_a0 = 1;
    var_a2 = temp_v1 + 0x84;
    temp_a1 = D_800D2398 + D_800D2399;
    if (temp_a1 >= 2) {
loop_5:
        if (temp_lo == *(s8 *)(var_a2 + 0x31)) {
            return var_a0;
        }
        var_a0 += 1;
        if (var_a0 < temp_a1) {
            var_a2 += 0x84;
            goto loop_5;
        }
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508855C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508855C.s")
void func_10023A10(void *, void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150885EC CURRENT (289) */
void func_150885EC(s32 arg0, s32 arg1) {
    s32 sp24;
    s32 sp20;
    s32 temp_lo;
    void *temp_v0;

    if (D_800872A0 != 0) {
        temp_lo = arg1 * 0x84;
        temp_v0 = (u8 *)(D_800872A0 + temp_lo);
        sp24 = (s32)*(s8 *)((u8 *)temp_v0 + 0x31);
        sp20 = (s32)*(s8 *)((u8 *)temp_v0 + 0x30);
        func_10023A10((void *)((arg0 * 0x84) + D_800872A0),
                      (void *)(temp_lo + D_800872A0), 0x84);
        *(s8 *)((u8 *)D_800872A0 + temp_lo + 0x31) = (s8)sp24;
        *(s8 *)((u8 *)D_800872A0 + temp_lo + 0x30) = (s8)sp20;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150885EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150885EC.s")
void func_15088824(void *);
extern s32 D_800D2394;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508868C CURRENT (64) */
s32 func_1508868C(s32 arg0) {
    s32 temp_a2;
    s32 var_v0;
    s32 var_v1;

    if (D_800872A0 == 0) {
        return -1;
    }
    var_v0 = 1;
    var_v1 = 0;
    if (D_800D2399 > 0) {
        do {
            if (!(D_800D2394 & var_v0)) {
                var_v1 += D_800D2398;
                temp_a2 = var_v1 * 0x84;
                D_800D2394 |= var_v0;
                func_15088824((void *)(temp_a2 + D_800872A0));
                *(s8 *)(D_800872A0 + temp_a2 + 0x30) = 1;
                *(s8 *)(D_800872A0 + temp_a2 + 0x31) =
                    (s8)((arg0 - (s32)&D_800CC2D0) / 812);
                return var_v1;
            }
            var_v1++;
            var_v0 *= 2;
        } while (var_v1 < D_800D2399);
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508868C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508868C.s")
s32 func_1508855C(s32);                             /* extern */
extern s32 D_800D2394;

void func_15088780(s32 arg0) {
    s32 temp_v0;

    if (D_800872A0 != 0) {
        temp_v0 = func_1508855C(arg0);
        *(s8 *)((u8 *)(D_800872A0 + (temp_v0 * 0x84)) + 0x31) = 0;
        D_800D2394 &= ~(1 << (temp_v0 - D_800D2398));
    }
}
s32 func_150887F8(void) {
    if (D_800872A0 == 0) {
        return 0;
    }
    return *(u8 *)((u8 *)D_800872A0 + 0x46) == 0xFF;
}
void func_15088824(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x2B) = 0;
    *(s8 *)((u8 *)arg0 + 0x2C) = 0;
    *(s8 *)((u8 *)arg0 + 0x2D) = 0;
    *(s8 *)((u8 *)arg0 + 0x2E) = 0;
    *(s8 *)((u8 *)arg0 + 0x28) = 0;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0;
    *(s32 *)((u8 *)arg0 + 0x18) = 0;
    *(s32 *)((u8 *)arg0 + 0x20) = -1;
    *(s8 *)((u8 *)arg0 + 0x2F) = 0;
    *(f32 *)((u8 *)arg0 + 8) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0) = 0.5f;
    *(f32 *)((u8 *)arg0 + 4) = 0.5f;
    *(s16 *)((u8 *)arg0 + 0x24) = 0;
    *(s8 *)((u8 *)arg0 + 0x26) = 0;
    *(s8 *)((u8 *)arg0 + 0x27) = 0;
    *(s8 *)((u8 *)arg0 + 0x31) = 0;
    *(f32 *)((u8 *)arg0 + 0xC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x14) = 0.0f;
    *(s8 *)((u8 *)arg0 + 0x33) = 2;
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(s8 *)((u8 *)arg0 + 0x2A) = 0x7F;
    *(s8 *)((u8 *)arg0 + 0x49) = 0;
    *(f32 *)((u8 *)arg0 + 0x10) = 1.0f;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150888A8 CURRENT (2887) */
s32 func_150888A8(s32 arg0, u8 arg1, s8 arg2) {
    s32 temp_s0;
    s32 var_a0;
    s32 var_a3;
    s32 var_t0;
    s32 var_t4;
    s32 var_v1;
    u8 temp_a2_2;
    u8 temp_a2_3;
    u8 temp_t0;
    u8 temp_t2;
    u8 temp_t3_2;
    u8 *temp_a2;
    u8 *temp_t1;
    u8 *temp_t2_2;
    u8 *temp_t3;
    u8 *var_t1;

    temp_s0 = arg0 & 0xFF;
    var_v1 = 0xFF;
    var_a3 = 0xFF;
    if (arg2 != 0) {
        var_a0 = 1;
    } else {
        var_a0 = 2;
    }
    temp_a2 = (void *)((arg1 * 0x10) + D_800D2350);
    temp_t0 = *(u8 *)((u8 *)temp_a2 + 9);
    if ((temp_t0 != 0xFF) && (temp_s0 != temp_t0)) {
        temp_t1 = (void *)((temp_t0 * 0x10) + D_800D2350);
        if (*(u8 *)((u8 *)temp_t1 + 0xE) == 0) {
            if (var_a0 != *(u8 *)((u8 *)temp_t1 + 0xF)) {
                var_v1 = temp_t0 & 0xFF;
            } else {
                var_a3 = temp_t0 & 0xFF;
            }
        }
    }
    var_t0 = 1;
    var_t1 = (void *)(temp_a2 + 1);
    var_t4 = var_v1;
    do {
        temp_a2_2 = *(u8 *)((u8 *)var_t1 + 9);
        var_t0 += 2;
        if ((temp_a2_2 != 0xFF) && (temp_s0 != temp_a2_2)) {
            temp_t3 = (void *)((temp_a2_2 * 0x10) + D_800D2350);
            if (*(u8 *)((u8 *)temp_t3 + 0xE) == 0) {
                temp_t2 = *(u8 *)((u8 *)temp_t3 + 0xF);
                if (var_a0 != temp_t2) {
                    if ((var_t4 == 0xFF) || (temp_t2 != 0)) {
                        var_v1 = temp_a2_2 & 0xFF;
                        var_t4 = var_v1;
                    }
                } else {
                    var_a3 = temp_a2_2 & 0xFF;
                }
            }
        }
        temp_t3_2 = *(u8 *)((u8 *)var_t1 + 0xA);
        if ((temp_t3_2 != 0xFF) && (temp_s0 != temp_t3_2)) {
            temp_t2_2 = (void *)((temp_t3_2 * 0x10) + D_800D2350);
            if (*(u8 *)((u8 *)temp_t2_2 + 0xE) == 0) {
                temp_a2_3 = *(u8 *)((u8 *)temp_t2_2 + 0xF);
                if (var_a0 != temp_a2_3) {
                    if ((var_t4 == 0xFF) || (temp_a2_3 != 0)) {
                        var_v1 = temp_t3_2 & 0xFF;
                        var_t4 = var_v1;
                    }
                } else {
                    var_a3 = temp_t3_2 & 0xFF;
                }
            }
        }
        var_t1 += 2;
    } while (var_t0 != 5);
    if (var_t4 == 0xFF) {
        var_v1 = var_a3 & 0xFF;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150888A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150888A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15088A08.s")
void func_15088A08(void *, f32);
void func_15088F30(f32 *, f32 *, f32 *, f32 *);
f32 func_150497E0(f32 *, s32, f32);
f32 func_150498A4(f32 *, s32, f32, f32 *);
f32 func_15144BC8(f32);
extern f32 D_8009DA04;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15088D58 CURRENT (20) */
void func_15088D58(GameB4080SearchActor *arg0) {
    GameB4080SearchEntry *entry;
    f32 angle;
    f32 x_derivative;
    f32 z_derivative;
    f32 xs[4];
    f32 ys[4];
    f32 zs[4];
    s32 rotation;
    s32 index;
    s32 i;
    s32 link;
    s32 again;
    u8 *target;
    u8 *cursor;

    index = func_1508855C((s32)arg0);
    if (index >= 0) {
        entry = (GameB4080SearchEntry *)(D_800872A0 + index * 0x84);
        entry->value0 = 0.5f;
        entry->value4 = 0.5f;
        entry->phase8 = 0.5f;
        do {
            again = 0;
            i = 0;
            cursor = D_800D2350 + entry->node2C * 0x10;
            do {
                link = cursor[9];
                i++;
                if (link != 0xFF) {
                    target = D_800D2350 + link * 0x10;
                    if (target[0xE] == 4) {
                        again = target[0xF];
                    }
                }
                cursor++;
            } while (i != 5);
            if (again != 0) {
                func_15088A08(entry, 1.0f);
            }
        } while (again != 0);
        entry->phase8 = 0.0f;
        func_15088F30((f32 *)entry, xs, ys, zs);
        arg0->field14 = func_150498A4(xs, 0, entry->phase8, &x_derivative);
        arg0->field18 = func_150497E0(ys, 0, entry->phase8);
        arg0->field1C = func_150498A4(zs, 0, entry->phase8, &z_derivative);
        angle = func_15144BC8((f32)(func_1505A630(entry->direction10, entry->directionC, 0) + 0x8000) * 0.005493164f);
        arg0->angle40 = angle;
        rotation = (s32)(angle * D_8009DA04) - 0x4000;
        arg0->rotation7A = rotation;
        arg0->rotation78 = rotation;
        arg0->rotation76 = rotation;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15088D58 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15088D58.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15088F30 CURRENT (1423) */
void func_15088F30(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 x_delta;
    f32 z_delta;
    f32 *var_t2;
    f32 *var_t3;
    f32 *var_t4;
    u8 *var_v1;
    s32 var_t1;
    s32 var_v0;
    s32 temp_a1;
    u8 *temp_a2;
    u8 *var_t0;

    var_v0 = 0;
    var_v1 = (u8 *)arg0;
    var_t2 = arg1;
    var_t3 = arg2;
    var_t4 = arg3;
    do {
        temp_a1 = *(u8 *)((u8 *)var_v1 + 0x2B);
        var_v1 += 1;
        if (temp_a1 != 0xFF) {
            var_t1 = 0;
            temp_a2 = (u8 *)((temp_a1 * 0x10) + (s32)D_800D2350);
            var_t0 = temp_a2;
            do {
                temp_a1 = *(u8 *)((u8 *)(temp_a2 + var_t1) + 9);
                if ((temp_a1 != 0xFF) && (*(u8 *)((u8 *)((s32)D_800D2350 + (temp_a1 * 0x10)) + 0xE) == 4)) {
                    var_t0 = (u8 *)((temp_a1 * 0x10) + (s32)D_800D2350);
                    var_t1 = 5;
                }
                var_t1 += 1;
            } while (var_t1 < 5);
            temp_a1 = *(s16 *)((u8 *)temp_a2 + 0);
            x_delta = (f32) (*(s16 *)((u8 *)var_t0 + 0) - temp_a1);
            z_delta = (f32) (*(s16 *)((u8 *)var_t0 + 4) - *(s16 *)((u8 *)temp_a2 + 4));
            *var_t2 = (x_delta * *arg0) + (f32) temp_a1;
            *var_t3 = (f32) *(s16 *)((u8 *)temp_a2 + 2);
            *var_t4 = (z_delta * *arg0) + (f32) *(s16 *)((u8 *)temp_a2 + 4);
        } else {
            *var_t2 = (f32) (var_v0 << 6);
            *var_t3 = 0.0f;
            *var_t4 = 0.0f;
        }
        var_v0 += 1;
        var_t2++;
        var_t3++;
        var_t4++;
    } while (var_v0 != 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15088F30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15088F30.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508907C CURRENT (2936) */
u8 func_1508907C(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    u8 *entry;
    u8 *neighbor;
    u8 *cursor;
    u8 candidate;
    u8 fallback;
    s32 offset;

    fallback = 0xFF;
    if (arg0 >= D_80087290) {
        return 0xFF;
    }
    entry = D_800D2350 + (arg0 * 0x10);
    candidate = entry[9];
    if ((candidate != 0xFF) && (arg2 != candidate) &&
        ((neighbor = D_800D2350 + (candidate * 0x10), arg1 == neighbor[0xE]) || (arg1 == 0xFF))) {
        fallback = candidate;
        if (arg3 == neighbor[0xF]) {
            return candidate;
        }
    }
    offset = 1;
    cursor = entry + 1;
loop_9:
    candidate = cursor[9];
    if ((candidate != 0xFF) && (arg2 != candidate) &&
        ((neighbor = D_800D2350 + (candidate * 0x10), arg1 == neighbor[0xE]) || (arg1 == 0xFF))) {
        fallback = candidate;
        if (arg3 == neighbor[0xF]) {
            return candidate;
        }
    }
    candidate = cursor[0xA];
    offset += 2;
    if ((candidate != 0xFF) && (arg2 != candidate) &&
        ((neighbor = D_800D2350 + (candidate * 0x10), arg1 == neighbor[0xE]) || (arg1 == 0xFF))) {
        fallback = candidate;
        if (arg3 == neighbor[0xF]) {
            return candidate;
        }
    }
    cursor += 2;
    if (offset != 5) {
        goto loop_9;
    }
    return fallback;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508907C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508907C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150891E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150896EC.s")
extern s32 D_800D23B0;

void func_15089BB0(void) {
    D_800D23B0 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15089BC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15089F9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508A1BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508A6FC.s")
extern s8 D_8008FD90;
extern s32 D_8008FDD4;

s16 func_1508B194(s32 arg0) {
    s32 offset;

    if (arg0 >= D_8008FD90) {
        return 0;
    }
    offset = arg0 * 0xC;
    return *(s16 *)((u8 *)(D_8008FDD4 + offset) + 0x70);
}
extern s8 D_8008FD90;
extern s32 D_8008FDD4;

void func_1508B1D4(s32 arg0) {
    if (arg0 < D_8008FD90) {
        *(s16 *)((u8 *)(D_8008FDD4 + (arg0 * 0xC)) + 0x70) = 0;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508B20C CURRENT (145) */
void func_1508B20C(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 temp_a1;
    s8 temp_v1;

    if (D_800D23B0 != 0) {
        temp_v1 = *(s8 *)((u8 *)D_800D23B0 + 0x1745);
        if (temp_v1 < 8) {
            *(s8 *)((u8 *)D_800D23B0 + 0x1745) = (s8) (temp_v1 + 1);
            temp_a1 = temp_v1 * 0xC;
            *(s16 *)((u8 *)(D_800D23B0 + temp_a1) + 0x174C) = (s16) (s32) arg0;
            *(s16 *)((u8 *)(D_800D23B0 + temp_a1) + 0x174E) = (s16) (s32) arg1;
            *(s16 *)((u8 *)(D_800D23B0 + temp_a1) + 0x1750) = (s16) (s32) arg2;
            *(f32 *)((u8 *)(D_800D23B0 + temp_a1) + 0x1748) = (f32) (arg3 * arg3);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508B20C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508B20C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508B2A8 CURRENT (230) */
void func_1508B2A8(u8 arg0, u8 *state) {
    u8 *entry;
    s32 i;
    s32 neighborIndex;
    u8 neighbor;
    u8 *mark;
    f32 dx;
    f32 dz;

    mark = state + (arg0 >> 3);
    mark[0x36] |= 1 << (arg0 & 3);
    entry = D_800D2350 + arg0 * 0x10;
    dx = (f32)*(s16 *)entry - *(f32 *)state;
    dz = (f32)*(s16 *)(entry + 4) - *(f32 *)(state + 4);
    dz = dx * dx + dz * dz;
    if (*(f32 *)(state + 8) < dz) {
        if (*(s16 *)(state + 0x2C) < 8) {
            state[0x2E + *(s16 *)(state + 0x2C)] = arg0;
            *(f32 *)(state + 0xC + *(s16 *)(state + 0x2C) * 4) = dz;
            *(s16 *)(state + 0x2C) += 1;
        }
    } else {
        for (i = 0; i < 5; i++) {
            neighbor = entry[9 + i];
            neighborIndex = (u8)neighbor;
            if (neighbor != 0xFF &&
                !(state[0x36 + (neighborIndex >> 3)] & (1 << (neighborIndex & 3)))) {
                func_1508B2A8(neighbor, state);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508B2A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508B2A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508B3F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508B9BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508BC20.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508BF14 CURRENT (11632) */
s32 func_1508BF14(void) {
    s32 spA4;
    s8 sp7C;
    s32 *sp6C;
    s32 *sp68;
    u8 *sp64;
    u8 *sp60;
    s32 *var_s7;
    s32 *var_t5;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s3;
    s32 temp_s5;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_a3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s6;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t4;
    s32 var_v0_3;
    s32 var_v1;
    s8 *temp_v0_3;
    s8 *var_v0;
    s8 *var_v0_2;
    u8 *temp_s4;
    u8 *temp_t2;

    var_t1 = 0;
    temp_s3 = *(s32 *)((u8 *)D_800D23B0 + 0x10);
    sp6C = (void *)(D_800D23B0 + 0x15C);
    sp68 = (void *)(D_800D23B0 + 0x39C);
    temp_s4 = (void *)(D_800D23B0 + 0xE64);
    sp64 = (void *)(D_800D23B0 + 0x45C);
    sp60 = (void *)(D_800D23B0 + 0x49C);
    temp_s5 = *(temp_s4 + (*(s32 *)((u8 *)D_800D23B0 + 4) * 4));
    temp_t2 = (void *)(D_800D23B0 + 0x5DC);
    if (temp_s3 > 0) {
        temp_a0 = temp_s3 & 3;
        if (temp_a0 != 0) {
            var_v0 = &sp7C;
            do {
                var_t1 += 1;
                *var_v0 = 0;
                var_v0 += 1;
            } while (temp_a0 != var_t1);
            if (var_t1 != temp_s3) {
                goto block_5;
            }
        } else {
block_5:
            var_v0_2 = &(&sp7C)[var_t1];
            do {
                var_v0_2 += 4;
                *(s8 *)((u8 *)var_v0_2 + -4) = 0;
                *(s8 *)((u8 *)var_v0_2 + -3) = 0;
                *(s8 *)((u8 *)var_v0_2 + -2) = 0;
                *(s8 *)((u8 *)var_v0_2 + -1) = 0;
            } while (var_v0_2 != &(&sp7C)[temp_s3]);
        }
    }
    spA4 = 0;
    do {
        var_t1_2 = 0;
        if (temp_s3 > 0) {
            var_s6 = 0;
            var_s7 = sp6C;
            do {
                temp_v0 = *var_s7;
                var_s7 += 4;
                var_a0 = 0;
                if ((temp_v0 == 2) || (temp_v0 == 3)) {
                    var_a0 = 1;
                }
                if (((var_a0 != 0) && (spA4 == 0)) || ((var_a0 == 0) && (spA4 != 0))) {
                    var_s1 = -1;
                    var_s0 = 0x989680;
                    if (temp_s5 == *(temp_s4 + var_s6)) {
                        var_a3 = 0;
                        if (temp_s3 > 0) {
                            var_t4 = 0;
                            var_t5 = sp68;
                            do {
                                temp_t8 = *var_t5;
                                var_t5 += 4;
                                if (temp_t8 > 0) {
                                    temp_v0_2 = var_a3 * 0x10;
                                    var_a2 = -1;
                                    temp_a1 = temp_v0_2 + 0x10;
                                    if (temp_s5 != *(temp_s4 + var_t4)) {
                                        var_a0_2 = temp_v0_2;
                                        if (temp_v0_2 < temp_a1) {
                                            var_v0_3 = temp_v0_2 * 4;
                                            if (*(temp_t2 + (temp_v0_2 * 4)) != -1) {
                                                var_v1 = *(temp_t2 + var_v0_3);
loop_25:
                                                var_a0_2 += 1;
                                                if (var_t1_2 == var_v1) {
                                                    var_a2 = *(u8 *)(D_800D23B0 + 0x9DC + var_v0_3);
                                                    var_a0_2 = temp_a1;
                                                }
                                                var_v0_3 = var_a0_2 * 4;
                                                if (var_a0_2 < temp_a1) {
                                                    var_v1 = *(temp_t2 + var_v0_3);
                                                    if (var_v1 != -1) {
                                                        goto loop_25;
                                                    }
                                                }
                                            }
                                        }
                                        if (var_a2 != -1) {
                                            temp_a2 = var_a2 << (&sp7C)[var_a3];
                                            if (temp_a2 < var_s0) {
                                                var_s0 = temp_a2;
                                                var_s1 = var_a3;
                                            }
                                        }
                                    }
                                }
                                var_a3 += 1;
                                var_t4 += 4;
                            } while (var_a3 != temp_s3);
                        }
                        temp_v0_3 = &(&sp7C)[var_s1];
                        *temp_v0_3 += 1;
                        *(sp64 + var_s6) = var_s0;
                        *(sp60 + var_s6) = var_s1;
                    }
                }
                var_t1_2 += 1;
                var_s6 += 4;
            } while (var_t1_2 != temp_s3);
        }
        temp_t6 = spA4 + 1;
        spA4 = temp_t6;
    } while (temp_t6 != 2);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508BF14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508BF14.s")
s32 func_1508C194(s32 arg0) {
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508C1A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508C5B8.s")
extern s8 D_8008FD8C;
extern u16 D_800D18A0;
extern s32 D_800D23B0;
extern u8 D_800CC2D0;

s32 func_1508C9CC(void) {
    s8 current;
    s32 found;
    s32 scanned;
    void *actor;
    void *object;

    scanned = 0;
    found = -1;
    current = *(s8 *)((u8 *)D_800D23B0 + 0x1702);
    do {
        current += 1;
        if (current >= D_8008FD8C) {
            current = 0;
        }
        actor = (u8 *)&D_800CC2D0 + current * 0x32C;
        if (*(s32 *)actor != 0) {
            object = *(void **)((u8 *)actor + 0x31C);
            if (object != 0 && *(u8 *)((u8 *)object + 0x84) != 0 &&
                !(D_800D18A0 & (1 << current))) {
                scanned = D_8008FD8C;
                found = current;
            }
        }
        scanned += 1;
    } while (scanned < D_8008FD8C);
    *(s8 *)((u8 *)D_800D23B0 + 0x1702) = current;
    return found;
}
extern s8 D_8008FD90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508CA88 CURRENT (210) */
s8 func_1508CA88(void) {
    s8 var_v1;

    *(s8 *)((u8 *)D_800D23B0 + 0x1703) = (s8) (*(s8 *)((u8 *)D_800D23B0 + 0x1703) + 1);
    var_v1 = *(s8 *)((u8 *)D_800D23B0 + 0x1703);
    if (var_v1 >= D_8008FD90) {
        *(s8 *)((u8 *)D_800D23B0 + 0x1703) = 0;
        var_v1 = *(s8 *)((u8 *)D_800D23B0 + 0x1703);
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508CA88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508CA88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508CAD8.s")
typedef struct GameB4080TargetState {
    u8 pad0[0x129];
    s8 target129;
    s8 active12A;
} GameB4080TargetState;

typedef struct GameB4080TargetActor {
    u8 pad0[0x14];
    f32 x14;
    u8 pad18[4];
    f32 z1C;
    u8 pad20[0x2FC];
    GameB4080TargetState *state31C;
} GameB4080TargetActor;

void func_1508EB90(s32, s32, s32);
f32 func_150ADA68(void);
extern s8 D_800872E8[];
extern s16 D_80087320[][3];
extern s8 D_800E0BD0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508D850 CURRENT (1752) */
s32 func_1508D850(s32 arg0) {
    s32 *target_base;
    s32 *timer_base;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 *temp_a3;
    s32 *temp_t0;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v0;
    GameB4080TargetActor *temp_t1;
    GameB4080TargetActor *temp_v0;

    target_base = (s32 *)((u8 *)D_800D23B0 + 0x11C);
    timer_base = (s32 *)((u8 *)D_800D23B0 + 0x29C);
    temp_a2 = arg0 * 4;
    temp_t0 = (s32 *)((u8 *)target_base + temp_a2);
    temp_t1 = (GameB4080TargetActor *)(&D_800CC2D0 + arg0 * 0x32C);
    temp_t1->state31C->target129 = (s8)*temp_t0;
    temp_a1 = *temp_t0;
    if (temp_a1 < 0) {
        return 0;
    }
    temp_v0 = (GameB4080TargetActor *)(&D_800CC2D0 + temp_a1 * 0x32C);
    temp_fv1 = temp_v0->x14 - temp_t1->x14;
    temp_fa0 = temp_v0->z1C - temp_t1->z1C;
    temp_fv0 = sqrtf(temp_fv1 * temp_fv1 + temp_fa0 * temp_fa0);
    if (5000.0f < temp_fv0) {
        var_v0 = 0;
    } else if (temp_fv0 > 2000.0f) {
        var_v0 = 1;
    } else {
        var_v0 = 2;
    }
    temp_a3 = (s32 *)((u8 *)timer_base + temp_a2);
    if (D_80087320[D_800E0BD0][var_v0] < *temp_a3) {
        *temp_a3 = 0;
        if ((0x10000 << *temp_t0) & *(s32 *)((u8 *)D_800D23B0 + temp_a2 + 0x16C0)) {
            func_1508EB90(arg0, 0x61, 0x2000);
        }
    }
    if (*temp_a3 == 0) {
        temp_t1->state31C->active12A = 0;
        if (D_800872E8[D_800E0BD0] < (s32)(func_150ADA68() * 100.0f)) {
            temp_t1->state31C->active12A = 1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508D850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508D850.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508DA1C CURRENT (1090) */
void func_1508DA1C(void) {
    s32 *var_t2;
    s32 *var_t2_2;
    s32 *var_t3;
    s32 *var_t4;
    s32 *var_v0;
    s32 *var_v1;
    s32 var_t1;
    s32 *first;
    s32 *second;
    s32 *third;
    s32 *fourth;
    s32 *fifth;
    s32 *sixth;

    first = (s32 *)((u8 *)D_800D23B0 + 0xEB0);
    second = (s32 *)((u8 *)D_800D23B0 + 0xF70);
    third = (s32 *)((u8 *)D_800D23B0 + 0xFF0);
    fourth = (s32 *)((u8 *)D_800D23B0 + 0x1070);
    fifth = (s32 *)((u8 *)D_800D23B0 + 0x10F0);
    sixth = (s32 *)((u8 *)D_800D23B0 + 0x12F4);
    var_t1 = 0;
    if (*(s32 *)((u8 *)D_800D23B0 + 0x10) > 0) {
        var_t2 = first;
        do {
            *var_t2 = -1;
            var_t1 += 1;
            var_t2 += 1;
        } while (var_t1 < *(s32 *)((u8 *)D_800D23B0 + 0x10));
        var_t1 = 0;
    }
    var_v1 = third;
    var_t2_2 = fifth;
    if (*(s32 *)((u8 *)D_800D23B0 + 0xEA4) > 0) {
        var_v0 = second;
        var_t3 = fourth;
        var_t4 = sixth;
        do {
            *var_v0 = -1;
            *var_v1 = 0;
            *var_t2_2 = -1;
            *var_t3 = 1;
            *var_t4 = 0;
            var_t1 += 1;
            var_v0 += 1;
            var_v1 += 1;
            var_t2_2 += 1;
            var_t3 += 1;
            var_t4 += 1;
        } while (var_t1 < *(s32 *)((u8 *)D_800D23B0 + 0xEA4));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508DA1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508DA1C.s")
s32 func_1508DAEC(s32 arg0, s32 arg1) {
    s32 *base;
    u8 *entry;
    u8 *actor;
    s32 current;
    s32 offset;
    s32 value;

    base = (s32 *)D_800D23B0;
    if (base == 0) {
        return 0;
    }
    current = (base + arg0)[0x3AC];
    if (current >= 0) {
        if (arg1 < 0) {
            return 1;
        }
        (base + arg0)[0x3AC] = -1;
        offset = current * 4;
        entry = (u8 *)D_800D23B0 + offset;
        if (!(*(s32 *)(entry + 0x11F4) & 2)) {
            *(s32 *)(entry + 0xF70) = -1;
            *(s32 *)((u8 *)D_800D23B0 + offset + 0x10F0) = -1;
            actor = &D_800CC2D0 + (arg0 * 0x32C);
            value = *(s32 *)((u8 *)D_800D23B0 + 0xEAC);
            if (arg1 == 1) {
                *(s32 *)((u8 *)D_800D23B0 + offset + 0x12F4) = 0x12C;
                *(s32 *)((u8 *)D_800D23B0 + offset + 0x1374) =
                    (s32)*(f32 *)(actor + 0x14);
                *(s32 *)((u8 *)D_800D23B0 + offset + 0x13F4) =
                    (s32)(*(f32 *)(actor + 0x18) + 50.0f);
                *(s32 *)((u8 *)D_800D23B0 + offset + 0x1474) =
                    (s32)*(f32 *)(actor + 0x1C);
                value = 4;
            }
            *(s32 *)((u8 *)D_800D23B0 + offset + 0x1070) = value;
        }
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508DC24.s")
void func_1508E6C8(void) {

}
s32 func_1508E6D0(s32 arg0) {
    switch (arg0) {
    case 0x3F:
        return 0x708;
    case 0x14:
        return 0xC80;
    case 0x22:
        return 0x1F4;
    case 0x23:
        return 0x2710;
    case 0x16:
        return 0x186A0;
    case 0x15:
        return 0x1F4;
    case 0x21:
        return 0x1F4;
    case 0x24:
        return 0x186A0;
    case 0x19:
    case 0x40:
        return 0x1F4;
    case 0x9:
        return 0x1388;
    case 0x38:
        return 0x1388;
    case 0x18:
    case 0x41:
        return 0x186A0;
    case 0x3:
        return 0x2EE;
    case 0x37:
        return 0x5DC;
    default:
        return 0x186A0;
    }
}
s32 func_1508E780(s32 arg0) {
    if (*(s16 *)((u8 *)D_800D23B0 + 0x16BC) != 0xB8) {
        switch (arg0) {                             /* switch 1 */
        case 0x14:                                  /* switch 1 */
            return 0x28;
        case 0x3F:                                  /* switch 1 */
            return 0x2F;
        case 0x22:                                  /* switch 1 */
            return 0x56;
        case 0x23:                                  /* switch 1 */
            return 0x16;
        case 0x16:                                  /* switch 1 */
            return 0x24;
        case 0x15:                                  /* switch 1 */
            return 0x4B;
        case 0x21:                                  /* switch 1 */
            return 0x58;
        case 0x24:                                  /* switch 1 */
            return 0x63;
        case 0x19:                                  /* switch 1 */
            return 0x57;
        case 0x40:                                  /* switch 1 */
            return 0x21;
        case 0x9:                                   /* switch 1 */
            return 0x1D;
        case 0x38:                                  /* switch 1 */
            return 0x7B;
        case 0x39:                                  /* switch 1 */
            return 0x82;
        case 0x37:                                  /* switch 1 */
            return 0x85;
        case 0x18:                                  /* switch 1 */
            return 0x55;
        case 0x41:                                  /* switch 1 */
            return 0x2E;
        case 0x25:                                  /* switch 1 */
            return 0x1060;
        default:                                    /* switch 1 */
            return -1;
        }
    } else {
        switch (arg0) {                             /* switch 2; irregular */
        case 8:                                     /* switch 2 */
            return -1;
        case 1:                                     /* switch 2 */
            return 0x105C;
        case 16:                                    /* switch 2 */
            return 0x1019;
        case 2:                                     /* switch 2 */
            return 0x1059;
        default:                                    /* switch 2 */
            return -1;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508E89C.s")
typedef struct {
    u8 field_0;
    u8 pad_1[0x32B];
} GameB4080EntityIdRecord;

extern GameB4080EntityIdRecord D_800CC40F[];
void func_1509BFB0(s32, s32, s32, s32);

void func_1508EB90(s32 arg0, s32 arg1, s32 arg2) {
    u8 temp_v0;

    temp_v0 = D_800CC40F[arg0].field_0;
    func_1509BFB0(1, temp_v0 | 0x2000, arg1, arg2);
}
void func_1508EBF8(s32 arg0, s32 arg1) {
    u8 temp_v0;

    temp_v0 = D_800CC40F[arg0].field_0;
    func_1509BFB0(1, temp_v0 | 0x2000, 0x14, arg1);
}
void func_1508EC5C(s32 arg0, s32 arg1) {
    u8 temp_v0;

    temp_v0 = D_800CC40F[arg0].field_0;
    func_1509BFB0(1, temp_v0 | 0x2000, 0x61, arg1);
}
extern u32 D_80087380;
extern s32 D_800D23C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508ECC0 CURRENT (2869) */
s32 func_1508ECC0(u16 arg0, u16 arg1, u16 arg2) {
    u8 *record;
    u16 value;
    u16 count;
    u32 selected;
    u32 index;
    u32 other;
    u8 *base;
    u8 *cursor;
    u8 *selectedCursor;

    index = 0;
    if (D_80087380 != 0) {
        record = (u8 *)D_800D23C0;
        do {
            count = *(u16 *)(record + 2);
            selected = 0;
            if (count != 0) {
                base = (u8 *)D_800D23C0 + index * 0x18;
                selectedCursor = base;
                do {
                    if ((u16)((arg0 << 12) + arg1) == *(u16 *)(selectedCursor + 8)) {
                        other = 0;
                        if (count != 0) {
                            cursor = base;
                            do {
                                value = *(u16 *)(cursor + 8);
                                if ((arg2 == (value >> 12)) && (other != selected)) {
                                    return value & 0xFFF;
                                }
                                other++;
                                cursor += 2;
                            } while (other < count);
                        }
                        return -1;
                    }
                    selected++;
                    selectedCursor += 2;
                } while (selected < count);
            }
            index++;
            record += 0x18;
        } while (index < (u32)D_80087380);
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508ECC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508ECC0.s")
extern u32 D_80087380;
extern s32 D_800D23C0;

void func_1508EDBC(u32 arg0) {
    s32 temp_v0;

    if (arg0 < (u32) D_80087380) {
        temp_v0 = arg0 * 0x18;
        *(s16 *)((u8 *)D_800D23C0 + temp_v0 + 2) = 0;
        *(s32 *)((u8 *)D_800D23C0 + temp_v0 + 4) = 0;
        *(s16 *)((u8 *)D_800D23C0 + temp_v0) = 0;
    }
}
void func_1503DDD0(s32);
void func_15114B94(u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508EE0C CURRENT (4678) */
void func_1508EE0C(s32 arg0, s32 arg1) {
    u32 row;
    u32 rowOffset;
    u32 index;
    u32 actionIndex;
    u32 actionOffset;
    u16 count;
    u16 value;
    u16 key;
    u16 group = arg0;
    u16 item = arg1;
    u8 *table;
    u8 *rowPointer;
    u8 *entry;

    row = 0;
    if (D_80087380 == 0) {
        return;
    }
    table = (u8 *)D_800D23C0;
    rowOffset = 0;
    rowPointer = table;
    do {
        count = *(u16 *)(rowPointer + 2);
        index = 0;
        if (count != 0) {
            key = ((group << 12) + item) & 0xFFFF;
            entry = table + (((row << 2) - row) << 3) + 8;
            do {
                index++;
                if (key == *(u16 *)entry) {
                    actionIndex = 0;
                    if (count != 0) {
                        actionOffset = 0;
                        do {
                            value = *(u16 *)(table + (((row << 2) - row) << 3) + actionOffset + 8);
                            if ((value >> 12) == 2) {
                                func_15114B94(value & 0xFFF);
                                table = (u8 *)D_800D23C0;
                                count = *(u16 *)(table + rowOffset + 2);
                            } else if ((value >> 12) == 3) {
                                func_1503DDD0(value & 0xFFF);
                                table = (u8 *)D_800D23C0;
                                count = *(u16 *)(table + rowOffset + 2);
                            }
                            actionIndex++;
                            actionOffset += 2;
                        } while (actionIndex < count);
                    }
                    func_1508EDBC(row);
                    return;
                }
                entry += 2;
            } while (index < count);
        }
        row++;
        rowOffset += 0x18;
        rowPointer += 0x18;
    } while (row < D_80087380);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508EE0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508EE0C.s")
