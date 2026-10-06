#include "types.h"

/*
 * Reviewed source unit: src/game/game_12C1E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FED30
 * - func_150FF084
 * - func_150FF2D4
 * - func_150FF474
 * - func_150FF6E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_150FF288(void *);
void func_150FF2AC(void *, void *, void *, void *);
void func_150FF2D4(u8 *, void *, f32 *, void *, void *, f32 *, s32, s32,
                  s32, s32, s32, s32, f32 *, f32 *, s32);
void func_150FF474(void *, void *, u8, s32);
void func_151D3F14(void *, u8, s32);
void func_151D4408(void *, void *, s32, void *, f32, s32, s32);
void func_151D5148(void *);
void func_151C229C(f32 *, f32 *, s32, s32, s32, s32, f32, f32, f32,
                  f32, f32, s32, f32 *, s32, s32, s32, s32, s32, s32,
                  s32, s32, f32, s32, s32, s32, s32, s32);
extern f32 D_800A2110;
extern u8 D_800BE616;

typedef struct Game12C1E0EmissionOwner {
    u8 pad0[4];
    u8 kind;
    u8 pad5[0x6F];
    u8 flags74;
    u8 pad75[0x15F];
    s32 resource1D4;
} Game12C1E0EmissionOwner;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FED30 CURRENT (3188) */
void func_150FED30(f32 *arg0, s32 arg1, s32 arg2) {
    f32 position[3];
    f32 endpoint[3];
    f32 direction[3];
    f32 axis0[3];
    f32 axis1[3];
    f32 hit[3];
    f32 normal[3];
    f32 output0[3];
    f32 output1[3];
    f32 points[6][3];
    s32 value0;
    s32 value1;
    s32 lookup;
    u8 valid;
    register s32 randomWord;
    register s32 kind;
    register s32 directionSign;
    f32 random1;
    f32 random0;

    lookup = func_150FF288(arg0);
    if (lookup != 0) {
        func_151D5148(arg0);
        func_150FF2AC(arg0, direction, axis0, axis1);
        if (((Game12C1E0EmissionOwner *)arg0)->resource1D4 != 0 &&
            (((Game12C1E0EmissionOwner *)arg0)->flags74 & 0xF) != 0xF) {
            valid = 1;
        } else {
            valid = 0;
        }
        func_150FF2D4(&valid, points, position, hit, normal, direction,
                     (s32)axis0, (s32)axis1, (s32)output0, (s32)output1,
                     (s32)&value0, (s32)&value1, endpoint, arg0, lookup);
        random0 = func_150ADA68();
        random1 = func_150ADA68();
        randomWord = func_150ADA20();
        if (D_800BE616 != 0) {
            kind = 0x35;
        } else {
            kind = 0x1A;
        }
        if (((Game12C1E0EmissionOwner *)arg0)->kind == 0x98) {
            directionSign = 1;
        } else {
            directionSign = -1;
        }
        func_151C229C(endpoint, direction, value0, value1, 1, 0,
                     300.0f, D_800A2110, random0 * 10.0f + 25.0f,
                     random1 * 200.0f + 600.0f, 50.0f,
                     ((u32)randomWord % 156U) + 0x64, arg0,
                     0x63, 1, 1, 1, 0, 1, 0, kind, 0.0f, 0xFF,
                     directionSign, 0, *(volatile u8 *)((u8 *)&arg1 + 3), arg2);
        if (valid != 0) {
            func_151D3F14(position, *(volatile u8 *)((u8 *)&arg1 + 3), arg2);
            func_151D4408(hit, normal,
                ((Game12C1E0EmissionOwner *)arg0)->resource1D4 +
                (*(u8 *)(lookup + 2) << 6), arg0, 1.0f, *(volatile u8 *)((u8 *)&arg1 + 3), arg2);
            func_150FF474(position, points, *(volatile u8 *)((u8 *)&arg1 + 3), arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FED30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FED30.s")
extern s32 func_1503195C(void *arg0, s32 arg1, s32 arg2);
s32 func_1514654C(void *, s32, s32, void **, void **, s32);
extern u8 D_800A2050;

void func_150FEFD0(void *arg0, s16 arg1, void *arg2) {
    u8 *sp34;
    void *sp30;
    s32 result;

    if (arg1 == -1) {
        *(f32 *)((u8 *)arg2 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg2 + 4) = *(f32 *)((u8 *)arg0 + 0x18);
        *(f32 *)((u8 *)arg2 + 8) = *(f32 *)((u8 *)arg0 + 0x1C);
        return;
    }
    result = func_1503195C(arg0, arg1, 0);
    if (result == 0) {
        *(f32 *)((u8 *)arg2 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg2 + 4) = *(f32 *)((u8 *)arg0 + 0x18);
        *(f32 *)((u8 *)arg2 + 8) = *(f32 *)((u8 *)arg0 + 0x1C);
        return;
    }
    sp34 = &D_800A2050;
    sp30 = arg2;
    func_1514654C(arg0, result, 0, (void **)&sp34, &sp30, 1);
}
s32 func_150ADA20(void);
s32 func_150FF288(void *);
void func_150FF2AC(void *, void *, void *, void *);
void func_150FF2D4(u8 *, void *, f32 *, void *, void *, f32 *, s32, s32,
                    s32, s32, s32, s32, f32 *, f32 *, s32);
void func_150FF474(void *, void *, u8, s32);
void func_151D3F14(void *, u8, s32);
void func_151D4408(void *, void *, s32, void *, f32, s32, s32);
void func_151D5148(void *);
void func_150F7470(f32 *, f32 *, s32, s32, s32, s32, f32, f32, f32,
                    void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A2114, D_800A2118;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FF084 CURRENT (2758) */
void func_150FF084(u8 *arg0, s32 arg1, s32 arg2) {
    f32 position[3];
    f32 endpoint[3];
    f32 direction[3];
    f32 axis0[3];
    f32 axis1[3];
    f32 hit[3];
    f32 normal[3];
    f32 output0[3];
    f32 output1[3];
    f32 points[6][3];
    s32 value0;
    s32 value1;
    s32 lookup;
    u8 valid;
    s32 enabled;

    lookup = func_150FF288(arg0);
    if (lookup != 0) {
        func_151D5148(arg0);
        func_150FF2AC(arg0, direction, axis0, axis1);
        if (*(s32 *)(arg0 + 0x1D4) != 0) {
            valid = 1;
        } else {
            valid = 0;
        }
        func_150FF2D4(&valid, points, position, hit, normal, direction,
                        (s32)axis0, (s32)axis1, (s32)output0, (s32)output1,
                        (s32)&value0, (s32)&value1, endpoint, (f32 *)arg0, lookup);
        enabled = 1;
        if (value1 == 0) {
            enabled = 0;
        }
        func_150F7470(position, direction, value0, value1, enabled, 0,
                        D_800A2114, D_800A2118, 300.0f, arg0, 1, 1, 1, 0,
                        0x1A, 1, ((u32)func_150ADA20() % 5U) + 0x327, 0,
                        (u8)arg1, arg2);
        if (valid != 0) {
            func_151D3F14(position, (u8)arg1, arg2);
            func_151D4408(hit, normal,
                            *(s32 *)(arg0 + 0x1D4) + (*(u8 *)(lookup + 2) << 6),
                            arg0, 1.0f, (u8)arg1, arg2);
            func_150FF474(position, points, (u8)arg1, arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FF084 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF084.s")

s32 func_150FF288(void *arg0) {
    return func_1503195C(arg0, 0x82, 0);
}
void func_15145740(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4);
extern f32 D_800A211C;

void func_150FF2AC(void *arg0, void *arg1, void *arg2, void *arg3) {
    func_15145740(arg0, arg1, arg2, arg3, D_800A211C);
}
s32 func_150FF6E0(void *, void *, void *, void *, void *, void *, s32);
void func_151D5174(void *, void *, void *, s32, s32, s32, s32, s32, s32, void *);
f32 fabsf(f32);
f32 sqrtf(f32);
#pragma intrinsic(fabsf)
#pragma intrinsic(sqrtf)
extern f32 D_800A2120;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FF2D4 CURRENT (1702) */
void func_150FF2D4(u8 *arg0, void *arg1, f32 *arg2, void *arg3,
                    void *arg4, f32 *arg5, s32 arg6, s32 arg7, s32 arg8,
                    s32 arg9, s32 arg10, s32 arg11, f32 *arg12,
                    f32 *arg13, s32 arg14) {
    f32 directionX;
    f32 directionZ;
    f32 x;
    f32 z;
    f32 length;
    u8 result;

    result = *arg0;
    if (result != 0) {
        result = func_150FF6E0(arg1, arg2, arg3, arg4, arg12, arg13, arg14);
        *arg0 = result;
    }
    if (result == 0) {
        x = arg5[0];
        if (D_800A2120 < fabsf(x) || D_800A2120 < fabsf(arg5[2])) {
            z = arg5[2];
            length = 1.0f / sqrtf((x * x) + (z * z));
            directionX = z * length;
            directionZ = -x * length;
        } else {
            directionX = 1.0f;
            directionZ = 0.0f;
        }
        arg2[0] = arg13[5] + (34.0f * directionZ);
        arg2[1] = arg13[6] + 49.0f;
        arg2[2] = arg13[7] + (34.0f * directionX);
        ((u32 *)arg12)[0] = ((u32 *)arg2)[0];
        ((u32 *)arg12)[1] = ((u32 *)arg2)[1];
        ((u32 *)arg12)[2] = ((u32 *)arg2)[2];
    }
    func_151D5174(arg13, arg2, arg5, arg6, arg7, arg8, arg9,
                   arg10, arg11, arg12);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FF2D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF2D4.s")
typedef struct Game12C1E0VectorBits {
    s32 x, y, z;
} Game12C1E0VectorBits;

typedef struct Game12C1E0Particle {
    u8 kind, mode;
    u16 resource;
    s16 duration;
    u8 pad6[2];
    s32 field8, fieldC;
    u8 red, green, blue, alpha;
    f32 size, magnitude;
    Game12C1E0VectorBits position, direction;
    f32 zeroX, zeroY, zeroZ;
    u32 flags;
    u8 brightness, field45, field46, field47;
    s32 field48;
    u8 field4C;
    u8 tail[0xB];
} Game12C1E0Particle;

f32 func_150ADA68(void);
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
extern f32 D_800A2124, D_800A2128, D_800A212C;
extern u8 D_800A4AA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FF474 CURRENT (1272) */
void func_150FF474(void *arg0, void *arg1, u8 arg2, s32 arg3) {
    u8 index;
    Game12C1E0Particle packet;
    register f32 sizeRange;
    register f32 magnitudeRange;
    register f32 magnitudeBase;
    register s32 variant;

    packet.kind = 0x5F;
    packet.mode = 5;
    packet.resource = 0x2203;
    packet.field8 = 0;
    packet.fieldC = 0;
    packet.red = 0xFF;
    packet.green = 0xFF;
    packet.blue = 0xFF;
    packet.alpha = 0xFF;
    packet.position = *(Game12C1E0VectorBits *)arg0;
    packet.zeroX = 0.0f;
    packet.zeroY = 0.0f;
    packet.zeroZ = 0.0f;
    packet.flags = 0x40CC0009;
    packet.field45 = 0xFF;
    packet.field46 = 0;
    packet.field47 = 7;
    packet.field4C = 0xFF;
    packet.field48 = 0;
    packet.duration = (func_150ADA20() & 3) + 3;
    magnitudeBase = D_800A2124;
    magnitudeRange = D_800A2128;
    sizeRange = D_800A212C;
    index = 0;
    do {
        packet.size = func_150ADA68() * sizeRange + 5.0f;
        packet.magnitude = func_150ADA68() * magnitudeRange + magnitudeBase;
        packet.direction = ((Game12C1E0VectorBits *)arg1)[index];
        packet.brightness = ((u32)func_150ADA20() % 156U) + 0x64;
        if (func_150ADA20() & 1) {
            variant = 2;
        } else {
            variant = 0;
        }
        func_1513D2F0((s32)&packet, (s32)&D_800A4AA0,
                     0, 0, 0, 0x1B, variant + 1, 0, 0, 0, arg2, arg3);
        index++;
    } while (index < 6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FF474 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF474.s")
s32 func_150FF6B4(void *arg0, s32 arg1, s32 arg2) {
    if (*(u8 *)((u8 *)arg0 + 4) == 0x98) {
        return 0;
    }
    return 1;
}
s32 func_150ADA20(void);
extern u8 D_800A205C;
extern u8 D_800A2068;
extern u8 D_800A2074;
extern u8 D_800A2080;

typedef struct Game12C1E0Pointers {
    void *head[4];
    void *elements[6];
} Game12C1E0Pointers;

typedef struct Game12C1E0InputPointers {
    void *head[4];
    void *elements[6];
    u32 pad;
} Game12C1E0InputPointers;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FF6E0 CURRENT (1880) */
s32 func_150FF6E0(s32 arg0, void *arg1, void *arg2, f32 *arg3,
                  s32 arg4, void *arg5, s32 arg6) {
    Game12C1E0InputPointers input;
    Game12C1E0Pointers output;
    s32 index;
    s32 variant;

    variant = (func_150ADA20() & 1) * 0x48;
    input.head[0] = &D_800A2050;
    input.head[1] = &D_800A2068;
    input.head[2] = &D_800A2074;
    input.head[3] = &D_800A205C;
    index = 0;
    do {
        input.elements[index] = (u8 *)&D_800A2080 + variant + index * 0xC;
        output.elements[index] = (void *)(arg0 + index * 0xC);
        index = (u8)(index + 1);
    } while (index < 6);
    output.head[0] = arg1;
    output.head[1] = arg2;
    output.head[2] = arg3;
    output.head[3] = (void *)arg4;
    if (func_1514654C(arg5, arg6, 0, input.head, output.head, 0xA) != 0) {
        arg3[0] -= ((f32 *)arg2)[0];
        arg3[1] -= ((f32 *)arg2)[1];
        arg3[2] -= ((f32 *)arg2)[2];
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FF6E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF6E0.s")
