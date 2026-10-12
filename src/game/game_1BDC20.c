#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1BDC20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_owner_particle_lifecycle.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15190898
 * - func_15190F9C
 * - func_1519108C
 * - func_15191400
 * - func_15191520
 * - func_151918BC
 * - func_15191980
 * - func_15191A84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void func_100226F0(void *, s32);
void func_15191B8C(void *, u8);
u8 func_151D8E20(void);

void *func_15190770(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    void *result;
    struct {
        void *field_0;
        u8 field_4;
    } data;

    data.field_0 = *(void **)arg0;
    data.field_4 = *(u8 *)((u8 *)*(void **)arg0 + 0x3B);
    func_15191B8C(&data, 0xE);
    result = func_15167A68(0x20, arg3, arg1 + 0x300, 1, arg2, 1);
    if (result == 0) {
        return 0;
    }
    func_10022EC0((u8 *)result + 0x10, arg0, 0xC);
    *(void **)((u8 *)result + 0x24) = (u8 *)result + 0x30;
    *(void **)((u8 *)result + 0x28) = (u8 *)result + 0x300;
    *(s32 *)((u8 *)result + 0x20) = 0;
    *(f32 *)((u8 *)result + 0x1C) = 0.0f;
    func_100226F0((u8 *)result + 0x30, 0x2D0);
    *(u8 *)((u8 *)result + 0x2C) = func_151D8E20();
    return result;
}
void func_15191400(u8 *);
void func_15190840(void *arg0) {
    func_15191400(arg0);
    func_15169804(arg0);
}

void func_1519086C(void *arg0) {
    func_15191400(arg0);
    func_15169824(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15190898.s")
/* Call context: func_151423D8: unique active project prototype */
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15190F9C CURRENT (303) */
s32 func_15190F9C(u8 *arg0) {
    f32 sp24;
    u8 *volatile sp1C;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 *temp_v1;

    *(u8 *)(arg0 + 0x131) += *(s8 *)(arg0 + 0x133) * D_800BE9E4;
    *(u8 *)(arg0 + 0x132) += *(s8 *)(arg0 + 0x134) * D_800BE9E4;
    sp24 = func_151423D8((*(u8 *)(arg0 + 0x131) - 0x40));
    temp_v1 = (void *)(arg0 + 0x110);
    sp1C = temp_v1;
    temp_fv0 = func_151423D8((*(u8 *)((u8 *)temp_v1 + 0x22) - 0x40));
    temp_v1 = sp1C;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)(arg0 + 0x2C) += ((*(f32 *)(temp_v1 + 0x28) + *(f32 *)(temp_v1 + 0x30) * sp24) - temp_fv1) * 0.5f;
    *(f32 *)(arg0 + 0x30) += ((*(f32 *)(temp_v1 + 0x2C) + *(f32 *)(temp_v1 + 0x34) * temp_fv0) - temp_fa0) * 0.5f;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15190F9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15190F9C.s")
void func_151D5D60(void *, s16, s32, void **, u8 *);
f32 func_15047C00(f32);
f32 func_15047D60(f32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern f32 D_800A8018, D_800BE9A8;
extern u8 D_800DD1D8[], D_800DD1E8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519108C CURRENT (1399) */
void *func_1519108C(u8 *arg0, s16 arg1) {
    void *vertices;
    void *base;
    f32 sine;
    volatile f32 heightCos;
    volatile f32 heightSin;
    f32 widthCos;
    f32 widthSin;
    f32 angle;
    f32 sign;
    u8 fresh;
    u8 *buffers;
    f32 *axisZ;
    f32 *axisX;

    func_151D5D60(arg0 + 0x100, arg1, 0x40, &vertices, &fresh);
    base = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            buffers = arg0 + arg1 * 4;
            axisZ = (f32 *)(arg0 + 0xC0);
            func_10022EC0(*(void **)(buffers + 0x100), axisZ, 0x40U);
            func_10022EC0(*(u8 **)(buffers + 0x100) + 0x40, axisZ, 0x40U);
        }
    } else {
        return 0;
    }
    axisZ = (f32 *)(D_800DD1E8 + arg1 * 4);
    axisX = (f32 *)(D_800DD1D8 + arg1 * 4);
    sign = -1.0f;
    angle = (*axisZ * (*(f32 *)(arg0 + 0x40) - *(f32 *)(arg0 + 0x34)) -
             *axisX * (*(f32 *)(arg0 + 0x48) - *(f32 *)(arg0 + 0x3C))) * D_800BE9A8;
    if (angle < 0.0f) {
        sign = 1.0f;
        angle = -angle;
    }
    angle = sqrtf(angle) * *(f32 *)(arg0 + 0x12C);
    if (D_800A8018 < angle) angle = D_800A8018;
    angle *= sign;
    sine = func_15047D60(angle);
    angle = func_15047C00(angle);
    sign = *(f32 *)(arg0 + 0x30);
    widthCos = *(f32 *)(arg0 + 0x2C) * angle;
    widthSin = *(f32 *)(arg0 + 0x2C) * sine;
    heightCos = sign * angle;
    heightSin = sign * sine;
    angle = -widthCos;
    *(s16 *)vertices = (s32)(*axisZ * angle + *(f32 *)(arg0 + 0x34));
    *(s16 *)((u8 *)vertices + 2) = (s32)(*(f32 *)(arg0 + 0x38) + widthSin);
    *(s16 *)((u8 *)vertices + 4) = (s32)(*(f32 *)(arg0 + 0x3C) - *axisX * angle);
    *(s16 *)((u8 *)vertices + 6) = 0;
    *(s16 *)((u8 *)vertices + 0x10) = (s32)(*axisZ * widthCos + *(f32 *)(arg0 + 0x34));
    *(s16 *)((u8 *)vertices + 0x12) = (s32)(*(f32 *)(arg0 + 0x38) - widthSin);
    *(s16 *)((u8 *)vertices + 0x14) = (s32)(*(f32 *)(arg0 + 0x3C) - *axisX * widthCos);
    *(s16 *)((u8 *)vertices + 0x16) = 0;
    angle = widthCos - heightSin;
    *(s16 *)((u8 *)vertices + 0x20) = (s32)(*axisZ * angle + *(f32 *)(arg0 + 0x34));
    *(s16 *)((u8 *)vertices + 0x22) = (s32)(*(f32 *)(arg0 + 0x38) - widthSin - heightCos);
    *(s16 *)((u8 *)vertices + 0x24) = (s32)(*(f32 *)(arg0 + 0x3C) - *axisX * angle);
    *(s16 *)((u8 *)vertices + 0x26) = 0;
    angle = -(widthCos + heightSin);
    *(s16 *)((u8 *)vertices + 0x30) = (s32)(*axisZ * angle + *(f32 *)(arg0 + 0x34));
    *(s16 *)((u8 *)vertices + 0x32) = (s32)(*(f32 *)(arg0 + 0x38) + widthSin - heightCos);
    *(s16 *)((u8 *)vertices + 0x34) = (s32)(*(f32 *)(arg0 + 0x3C) - *axisX * angle);
    *(s16 *)((u8 *)vertices + 0x36) = 0;
    return base;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519108C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_1519108C.s")
u32 func_150ADA20(void);
extern u8 D_800A9D40[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15191400 CURRENT (835) */
void func_15191400(u8 *arg0) {
    s32 var_s2;
    u8 *var_s0;
    s16 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    var_s2 = 0;
    *(f32 *)(arg0 + 0x1C) = 0.0f;
    *(s32 *)(arg0 + 0x20) = 0;
    var_s0 = *(u8 **)(arg0 + 0x24);
    do {
        temp_v1 = *(u8 **)var_s0;
        temp_v0 = temp_v1 + 0x110;
        if (temp_v1 != 0) {
            *(f32 *)(temp_v0 + 0) = 0.0f;
            *(f32 *)(temp_v0 + 4) = 0.0f;
            *(f32 *)(temp_v0 + 8) = 0.0f;
            temp_s1 = (s16 *)(D_800A9D40 + (*(u8 *)(temp_v0 + 0x20) * 0x14));
            func_1513F680(*(void **)var_s0, 0xD, 0x12, 0, 0xD);
            *(s16 *)(*(u8 **)var_s0 + 0x1C) =
                (func_150ADA20() % (u32)(temp_s1[1] + 1)) + temp_s1[0];
            temp_v1_2 = *(u8 **)var_s0;
            *(s32 *)(temp_v1_2 + 0x58) |= 1;
        }
        var_s2 += 1;
        var_s0 += 0xC;
    } while (var_s2 != 0x3C);
    func_100226F0(*(void **)(arg0 + 0x24), 0x2D0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15191400 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191400.s")
s32 func_1514672C(f32 *);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_151DBCBC(s32, f32, s32, s32, f32 *, s32, s32);
void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);
extern f32 D_800BE9A4, D_800A801C, D_800A8020;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15191520 CURRENT (5362) */
s32 func_15191520(u8 *arg0) {
    f32 dx;
    f32 dz;
    f32 dy;
    s8 alive;
    volatile f32 oldY;
    volatile f32 oldZ;
    volatile f32 oldX;
    f32 position[3];
    f32 *motion;
    f32 damping;
    volatile f32 oldVelocityY;
    volatile f32 acceleration;

    oldY = *(f32 *)(arg0 + 0x38);
    oldX = *(f32 *)(arg0 + 0x110);
    motion = (f32 *)(arg0 + 0x110);
    oldZ = *(f32 *)(arg0 + 0x118);
    alive = 1;
    damping = *(f32 *)(arg0 + 0x120);
    *(f32 *)(arg0 + 0x110) = oldX * (damping * D_800BE9A4);
    *(f32 *)(arg0 + 0x118) = oldZ * (damping * D_800BE9A4);
    oldVelocityY = *(f32 *)(arg0 + 0x114);
    dx = (*(f32 *)(arg0 + 0x110) + oldX) * 0.5f * D_800BE9A4;
    acceleration = *(f32 *)(arg0 + 0x11C) * D_800BE9A4;
    dy = oldVelocityY * D_800BE9A4 + acceleration * D_800BE9A4 * 0.5f;
    dz = (*(f32 *)(arg0 + 0x118) + oldZ) * 0.5f * D_800BE9A4;
    *(f32 *)(arg0 + 0x114) = oldVelocityY + acceleration;
    *(f32 *)(arg0 + 0x34) += dx;
    *(f32 *)(arg0 + 0x38) = oldY + dy;
    *(f32 *)(arg0 + 0x3C) += dz;
    *(f32 *)(arg0 + 0x40) += dx;
    *(f32 *)(arg0 + 0x44) += dy;
    *(f32 *)(arg0 + 0x48) += dz;
    *(f32 *)(arg0 + 0x40) = *(f32 *)(arg0 + 0x34) + (*(f32 *)(arg0 + 0x40) - *(f32 *)(arg0 + 0x34)) * motion[6];
    *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x38) + (*(f32 *)(arg0 + 0x44) - *(f32 *)(arg0 + 0x38)) * motion[6];
    *(f32 *)(arg0 + 0x48) = *(f32 *)(arg0 + 0x3C) + (*(f32 *)(arg0 + 0x48) - *(f32 *)(arg0 + 0x3C)) * motion[6];
    position[0] = *(f32 *)(arg0 + 0x34);
    position[1] = oldY - *(f32 *)(arg0 + 0x30);
    position[2] = *(f32 *)(arg0 + 0x3C);
    if (func_1514672C(position) == 0) {
        return 0;
    }
    if (func_15046C80(position, 0, *(f32 *)(arg0 + 0x38) - *(f32 *)(arg0 + 0x30), (u8 *)motion + 0x38) != 0) {
        position[1] = motion[14];
        if (((u8 *)motion)[0x55] == 3) {
            func_151DBCBC(((u8 *)motion)[0x5C], *(f32 *)(arg0 + 0x2C) * *(f32 *)(arg0 + 0x30) * 0.25f,
                         arg0[0x5C], (s32)((u8 *)motion + 0x3C), position, arg0[0xC], arg0[1]);
        } else if (func_150ADA20() & 1) {
            func_151D9B8C(((u8 *)motion)[0x5C], *(f32 *)(arg0 + 0x2C) * *(f32 *)(arg0 + 0x30) * D_800A801C,
                         arg0[0x5C], (s32)((u8 *)motion + 0x3C), position, func_150ADA20() % 41U + 0x50,
                         1, 1, 0, arg0[0xC], arg0[1]);
        } else {
            func_151DAB58(((u8 *)motion)[0x5C], *(f32 *)(arg0 + 0x2C) * *(f32 *)(arg0 + 0x30) * D_800A8020,
                         arg0[0x5C], position, 1, arg0[0xC], arg0[1]);
        }
        alive = 0;
    }
    return alive;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15191520 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191520.s")
s32 func_1519187C(void *arg0) {
    s16 temp_v0;
    s32 temp_lo;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0x124)) {
        temp_lo = temp_v0;
        temp_lo *= *(s16 *)((u8 *)arg0 + 0x126);
        if (temp_lo < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_lo;
        }
    }
    return 1;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151918BC CURRENT (895) */
void func_151918BC(void *arg0) {
    u8 sp27;
    s32 var_v0;
    u8 *temp_a0;
    u8 *temp_v1;

    temp_v1 = *(u8 **)((u8 *)arg0 + 0x28);
    var_v0 = 0;
    if (*(s32 *)temp_v1 == 0) {
        var_v0 = 1;
    } else if (*(u8 *)((u8 *)arg0 + 0x2C) != *(u8 *)(temp_v1 + 0x3B)) {
        var_v0 = 1;
    }
    if ((var_v0 == 0) && (*(s32 *)(temp_v1 + 0x1D4) != 0)) {
        temp_a0 = (u8 *)arg0 + 0x28;
        if ((*(u8 *)((u8 *)arg0 + 0xD) & 1) != 0) {
            *(u8 *)(temp_a0 + 8) |= 1;
            *(s16 *)(temp_a0 + 6) = *(s16 *)((u8 *)arg0 + 0xE);
        } else {
            *(s16 *)(temp_a0 + 6) = 0x12C;
        }
        sp27 = 1;
        func_15190770(temp_a0, 0, *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
        var_v0 = sp27;
    }
    if (var_v0 != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151918BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_151918BC.s")
void func_15169850(void *, u8, s32 *, u8 *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15191980 CURRENT (725) */
void func_15191980(void *arg0, void *arg1, u8 arg2) {
    void *temp_s0;

    temp_s0 = arg0;
    if (arg2 == 0xD) {
        if ((*(s32 *)((u8 *)temp_s0 + 0x10) == *(s32 *)arg1) ||
            (*(u8 *)((u8 *)temp_s0 + 0x14) == *(u8 *)((u8 *)arg1 + 4))) {
            *(s16 *)((u8 *)temp_s0 + 0x16) = 0x64;
            *(u8 *)((u8 *)temp_s0 + 0x18) |= 1;
        }
    } else if ((arg2 == 0xC) || (arg2 == 0x50) || (arg2 == 0xE)) {
        if ((*(s32 *)((u8 *)temp_s0 + 0x10) == *(s32 *)arg1) ||
            (*(u8 *)((u8 *)temp_s0 + 0x14) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(temp_s0);
        }
    } else {
        if (arg2 == 0x4E) {
            func_1516972C(temp_s0);
            return;
        }
        func_15169850(arg1, arg2, (s32 *)((u8 *)temp_s0 + 0x10),
                      (u8 *)temp_s0 + 0x14, temp_s0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15191980 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191980.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15191A84 CURRENT (890) */
void func_15191A84(void *arg0, void *arg1, u8 arg2) {
    void *temp_a2;

    temp_a2 = (u8 *)arg0 + 0x28;
    if ((arg2 == 0xC) || (arg2 == 0xE) || (arg2 == 0x50)) {
        if ((*(s32 *)temp_a2 == *(s32 *)arg1) ||
            (*((u8 *)temp_a2 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else {
        if (arg2 == 0x4E) {
            func_1516972C(arg0);
            return;
        }
        if (arg2 == 0xD) {
            if ((*(s32 *)temp_a2 == *(s32 *)arg1) ||
                (*((u8 *)temp_a2 + 4) ==
                 *(u8 *)((u8 *)arg1 + 4))) {
                *(s16 *)((u8 *)arg0 + 0xE) = 0x64;
                *(u8 *)((u8 *)arg0 + 0xD) |= 1;
            }
        } else {
            func_15169850(arg1, arg2, temp_a2,
                          (u8 *)temp_a2 + 4, arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15191A84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191A84.s")
void func_15169260(s32 *, s32, void *, u8);
extern s32 D_800A8010;

void func_15191B8C(void *arg0, u8 arg1) {
    s32 sp1C;

    sp1C = D_800A8010;
    func_151494E0(arg0, arg1);
    func_15169260(&sp1C, 1, arg0, arg1);
}
