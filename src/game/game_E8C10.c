#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_E8C10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BBB5C
 * - func_150BC488
 * - func_150BD070
 * - func_150BD740
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameE8C10Particle {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    s32 field50;
    s16 field54;
    s16 field56;
    u8 field58;
    u8 pad59[0x3];
    s32 field5C;
    u8 field60;
    u8 field61;
    u8 field62;
    u8 field63;
    u8 field64;
    u8 field65;
    u8 field66;
    u8 field67;
    u8 field68;
    u8 pad69[0x1];
    u8 field6A;
    u8 pad6B[0x1];
    s32 field6C;
    u8 field70;
    u8 pad71[0x1];
    s16 field72;
    s16 field74;
    u8 pad76[0x6];
} GameE8C10Particle;

f32 func_150ADA68(void);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_8009FE94;
extern f32 D_8009FE98;
extern f32 D_8009FE9C;
extern f32 D_8009FEA0;
extern f32 D_8009FEA4;

s32 func_150BB760(u8 *arg0) {
    GameE8C10Particle particle;
    f32 width;
    f32 height;
    f32 sine;
    f32 cosine;
    f32 offsetX;
    f32 offsetZ;

    if (arg0[4] != 0x20) {
        return 1;
    }
    if (arg0 != NULL && *(s32 *)arg0 != 0 && *(s32 *)(arg0 + 0x1D4) != 0) {
        width = *(s16 *)(arg0 + 0xE4);
        height = *(s16 *)(arg0 + 0xE6);
        sine = func_151423D8(*(u16 *)(arg0 + 0x76) >> 8);
        cosine = func_151423D8((*(u16 *)(arg0 + 0x76) >> 8) + 0x40);
        offsetX = *(f32 *)(arg0 + 0x3C) * sine * 0.5f;
        offsetZ = *(f32 *)(arg0 + 0x3C) * cosine * 0.5f;
        particle.field56 = 1;
        particle.field50 = 0x29E9;
        particle.field58 = 0;
        particle.field5C = 0;
        particle.field60 = 0xFF;
        particle.field61 = 1;
        particle.field62 = 0;
        particle.field63 = 2;
        particle.field64 = 0;
        particle.field65 = 0;
        particle.field66 = 0;
        particle.field67 = 0;
        particle.field68 = 0;
        particle.field6A = 1;
        particle.field6C = (s32)arg0;
        particle.field1C = 1.0f;
        particle.field20 = 1.0f;
        particle.field24 = 1.0f;
        particle.field48 = 0.0f;
        particle.field4C = -1.0f;
        particle.field70 = arg0[0x3B];
        particle.field72 = 0x20;
        particle.field74 = 7;
        {
            u8 angle;
            f32 spreadSine;
            f32 spreadCosine;
            f32 distance;
            f32 spreadX;
            f32 spreadZ;
            u8 heading;
            f32 headingSine;
            f32 headingCosine;
            f32 speed;
            f32 velocityX;
            f32 velocityZ;
            f32 size;

            angle = func_150ADA20();
            spreadSine = func_151423D8(angle);
            spreadCosine = func_151423D8(angle - 0x40);
            distance = func_150ADA68() * width;
            spreadX = spreadSine * distance;
            spreadZ = -spreadCosine * distance;
            heading = (*(u16 *)(arg0 + 0x76) >> 8) - (func_150ADA20() & 0x3F) - 0x20;
            headingSine = func_151423D8(heading);
            headingCosine = func_151423D8(heading - 0x40);
            speed = func_150ADA68() * 5.0f + 3.0f;
            velocityX = headingCosine * speed;
            velocityZ = headingSine * speed;
            size = func_150ADA68() * D_8009FE94 + D_8009FE98;
            distance = func_150ADA68() * D_8009FE9C + D_8009FEA0;
            particle.field8 = size;
            particle.fieldC = distance;
            particle.field0 = (size + distance) * 0.5f;
            particle.field10 = func_150ADA68() * 360.0f;
            particle.field14 = func_150ADA68() * 360.0f;
            particle.field18 = func_150ADA68() * 360.0f;
            particle.field28 = *(f32 *)(arg0 + 0x14) + spreadX;
            particle.field2C = *(f32 *)(arg0 + 0x18) + func_150ADA68() * height + 4.0f;
            particle.field30 = *(f32 *)(arg0 + 0x1C) + spreadZ;
            particle.field34 = velocityX + offsetX;
            particle.field38 = func_150ADA68() * 5.0f + 3.0f;
            particle.field3C = velocityZ + offsetZ;
            particle.field40 = 25.0f - func_150ADA68() * 50.0f;
            particle.field44 = 25.0f - func_150ADA68() * 50.0f;
            particle.field54 = (func_150ADA20() & 0x1F) + 0x3C;
            particle.field4 = func_150ADA68() * D_8009FEA4 + 0.25f;
            func_15132A4C(&particle, 3, 0xFF, 0, 0xFF, 0);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BBB5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BC488.s")
s32 func_150BCBBC(u8 *arg0) {
    f32 width;
    f32 height;
    s32 count;
    s32 ok;
    GameE8C10Particle particle;

    if (arg0[4] != 0x20) {
        return 1;
    }
    if (arg0 != NULL && *(s32 *)arg0 != 0) {
        width = *(s16 *)(arg0 + 0xE4);
        height = *(s16 *)(arg0 + 0xE6);
        count = func_150ADA20() & 1;
        particle.field56 = 1;
        particle.field54 = 0x96;
        particle.field50 = 0x29E9;
        particle.field58 = 0;
        particle.field5C = 0;
        particle.field60 = 0xFF;
        particle.field61 = 1;
        particle.field62 = 0;
        particle.field63 = 2;
        particle.field64 = 0;
        particle.field65 = 0;
        particle.field66 = 0;
        particle.field67 = 0;
        particle.field68 = 0;
        particle.field6A = 0;
        particle.field6C = 0;
        particle.field70 = 0;
        particle.field72 = 0x20;
        particle.field74 = 7;
        ok = 1;
        particle.field1C = 1.0f;
        particle.field20 = 1.0f;
        particle.field24 = 1.0f;
        particle.field4 = 0.3f;
        particle.field48 = 0.0f;
        particle.field4C = -1.0f;
        while (count != 0 && ok != 0) {
            u8 angle;
            f32 spreadSine;
            f32 spreadCosine;
            f32 distance;
            f32 spreadX;
            f32 spreadZ;
            f32 sizeA;
            s32 heading;
            f32 headingSine;
            f32 headingCosine;
            f32 speed;
            f32 velocityX;
            f32 velocityZ;

            angle = func_150ADA20();
            spreadSine = func_151423D8(angle);
            spreadCosine = func_151423D8(angle - 0x40);
            distance = func_150ADA68() * width;
            spreadX = spreadSine * distance;
            spreadZ = -spreadCosine * distance;
            distance = func_150ADA68() * 0.03f + 0.01f;
            sizeA = func_150ADA68() * 0.03f + 0.01f;
            if (func_150ADA20() & 1) {
                heading = (u8)((*(u16 *)(arg0 + 0x76) >> 8) + (s32)(8 - (func_150ADA20() & 0xF)));
            } else {
                heading = (u8)((*(u16 *)(arg0 + 0x76) >> 8) + (s32)(8 - (func_150ADA20() & 0xF)) - 0x80);
            }
            headingSine = func_151423D8(heading);
            headingCosine = func_151423D8(heading - 0x40);
            speed = func_150ADA68() * 5.0f + 3.0f;
            velocityX = headingCosine * speed;
            velocityZ = headingSine * speed;
            particle.field8 = distance;
            particle.fieldC = sizeA;
            particle.field0 = (distance + sizeA) * 0.5f;
            particle.field10 = func_150ADA68() * 360.0f;
            particle.field14 = func_150ADA68() * 360.0f;
            particle.field18 = func_150ADA68() * 360.0f;
            particle.field28 = *(f32 *)(arg0 + 0x14) + spreadX;
            particle.field2C = *(f32 *)(arg0 + 0x18) + func_150ADA68() * height + 4.0f;
            particle.field30 = *(f32 *)(arg0 + 0x1C) + spreadZ;
            particle.field34 = velocityX;
            particle.field38 = func_150ADA68() * 5.0f + 3.0f;
            particle.field3C = velocityZ;
            particle.field40 = 25.0f - func_150ADA68() * 50.0f;
            particle.field44 = 25.0f - func_150ADA68() * 50.0f;
            if (func_15132A4C(&particle, 3, 0xFF, 0, 0xFF, 0) == NULL) {
                ok = 0;
            }
            count--;
        }
    }
}
extern f32 D_8009FEF8;

s32 func_150BCFB8(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_fv0;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10) * D_8009FEF8) + arg4);
    if (-2.0f < (temp_fv0 = *(f32 *)((u8 *)arg0 + 0x48))) {
        *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) & ~0x6F);
        *(f32 *)((u8 *)arg0 + 0x48) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
    } else {
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) * temp_fv1);
        *(f32 *)((u8 *)arg0 + 0x48) = (f32) (-temp_fv0 * temp_fv1);
        *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) * temp_fv1);
        *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) * temp_fv1);
        *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) * temp_fv1);
        *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * temp_fv1);
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BD070.s")
f32 func_150ADA68(void);
void func_15143134(f32 *, f32 *, s32);
void func_1514C470(f32, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, s32);
extern f32 D_8009FF40[12];
extern f32 D_8009FF70[12];
extern f32 D_8009FFA0[12];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BD740 CURRENT (2337) */
void func_150BD740(u8 *arg0, s32 arg1, s32 arg2) {
    f32 pointsA[12];
    f32 pointsB[12];
    f32 pointsC[12];
    f32 direction1[3];
    f32 direction0[3];
    f32 *endC;
    f32 *outC;
    f32 *inA;
    f32 *outA;
    f32 *inB;
    f32 *outB;
    f32 *inC;

    if (arg0 != 0) {
        inA = D_8009FF40;
        outA = pointsA;
        if (*(s32 *)(arg0 + 0x1D4) != 0) {
            inC = D_8009FFA0;
            inB = D_8009FF70;
            outB = pointsB;
            outC = pointsC;
            endC = pointsC + 12;
            do {
                func_15143134(inA, outA, *(s32 *)(arg0 + 0x1D4));
                func_15143134(inB, outB, *(s32 *)(arg0 + 0x1D4));
                func_15143134(inC, outC, *(s32 *)(arg0 + 0x1D4));
                outC += 3;
                inA += 3;
                outA += 3;
                inB += 3;
                outB += 3;
                inC += 3;
            } while (outC != endC);
            direction0[0] = pointsC[6] - pointsB[6];
            direction0[1] = pointsC[7] - pointsB[7];
            direction0[2] = pointsC[8] - pointsB[8];
            func_1514C470(pointsA[6], pointsA[7], pointsA[8],
                           pointsA[9], pointsA[10], pointsA[11],
                           (func_150ADA68() * 6.0f) + 14.0f,
                           0xD, 0, 0.0f, (s32)direction0, (u8)arg1);
            direction1[0] = pointsC[9] - pointsB[9];
            direction1[1] = pointsC[10] - pointsB[10];
            direction1[2] = pointsC[11] - pointsB[11];
            func_1514C470(pointsA[9], pointsA[10], pointsA[11],
                           pointsA[0], pointsA[1], pointsA[2],
                           (func_150ADA68() * 6.0f) + 14.0f,
                           0xD, 0, 0.0f, (s32)direction1, (u8)arg1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BD740 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BD740.s")
f32 func_150ADA68(void);
extern f32 D_8009FFD0, D_8009FFD4, D_8009FFD8, D_8009FFDC, D_8009FFE0, D_8009FFE4;

typedef struct GameE8C10Emission {
    s32 zero, enabled, flags, kind, field10, field14, field18;
    u8 byte1C, byte1D;
    u8 pad1E[6];
    f32 angle, dx, dy, dz, speed, height;
    u8 mode, category, alpha, random;
    u8 pad40[4];
    f32 x, y, z;
    s16 count, one;
    s32 active;
    u8 pad58;
    u8 variant;
} GameE8C10Emission;

s32 func_150BD954(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, f32 arg6, f32 arg7, s32 arg8, s32 arg9,
                   f32 arg10, s32 arg11, f32 arg12, f32 *arg13, u8 arg14) {
    f32 *direction;
    f32 scale;
    GameE8C10Emission emission;

    emission.enabled = 1;
    emission.flags = 0x160600;
    emission.zero = 0;
    emission.kind = 3;
    emission.field10 = 0x10;
    emission.field14 = 0x80;
    emission.field18 = 0x20;
    emission.byte1C = 0;
    emission.byte1D = 9;
    emission.active = 1;
    emission.one = 1;
    emission.x = arg2;
    emission.y = arg3;
    emission.height = arg3;
    emission.category = 9;
    emission.alpha = 0xFF;
    emission.mode = 8;
    emission.z = arg4;
    direction = arg13;
    scale = ((func_150ADA68() * 127.0f) + 85.0f) * D_8009FFD0;
    emission.dx = direction[0] * scale;
    emission.dy = direction[1] * scale;
    emission.dz = direction[2] * scale;
    emission.random = (func_150ADA20() % 86U) + 0xB4;
    emission.variant = (func_150ADA20() & 3) + 3;
    emission.count = (func_150ADA20() % 31U) + 0x27;
    emission.angle = ((func_150ADA68() * D_8009FFD4) + D_8009FFD8) * D_8009FFDC;
    emission.speed = ((func_150ADA68() * 356.0f) + D_8009FFE0) * D_8009FFE4;
    func_15147DA0(&emission.x, &emission.angle, 0, 1, 0xB, 0, 0, 0, 0, 0, 0, &emission.zero, 0, arg14, 1);
    return 1;
}
s32 func_150BDB3C(void *arg0) {
    s32 temp_t6;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    if (temp_t6 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
        *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) temp_t6;
    }
    return 1;
}
