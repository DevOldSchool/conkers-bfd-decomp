#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1DD500.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B0050
 * - func_151B03B8
 * - func_151B09BC
 * - func_151B0B88
 * - func_151B118C
 * - func_151B14AC
 * - func_151B1828
 * - func_151B1918
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_800AA28C;
extern f32 D_800AA290;
extern f32 D_800AA294;
extern f32 D_800AA298;
extern f32 D_800AA29C;
f32 func_150ADA68(void);
u32 func_150ADA20(void);
void func_15143794(s16, s16, f32, void *);
void func_151DA6F8(f32 *, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B0050 CURRENT (2168) */
s32 func_151B0050(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s16 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, u8 arg14) {
    f32 position[3];
    f32 velocity[3];
    u32 random_int2;
    struct {
        volatile f32 float0;
        u32 int0;
        u32 int1;
        f32 float1;
    } random;

    position[0] = arg2;
    position[1] = arg3;
    position[2] = arg4;
    func_15143794(arg9, arg8, (func_150ADA68() * D_800AA28C) + D_800AA290, velocity);
    random.float0 = func_150ADA68();
    random.int0 = func_150ADA20();
    random.int1 = func_150ADA20();
    random.float1 = func_150ADA68();
    random_int2 = func_150ADA20();
    func_151DA6F8(position, velocity, (random.float0 * 0.0f) + D_800AA294, (s16) ((random.int0 % 20U) + 0x1F), (random.int1 % 101U) + 0x9B, (random.float1 * D_800AA298) + D_800AA29C, (random_int2 & 1) + 3, 1, 1.0f, 1.0f, 0, 0, 0, 0x10, 0xF, 0, arg14, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B0050 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B0050.s")
typedef struct Game1DD500Impact {
    s16 field00;
    s16 field02;
    s16 field04;
    s16 field06;
    f32 position[3];
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    s16 field2C;
    s16 field2E;
    s16 field30;
    s16 field32;
    s16 field34;
    s16 field36;
    s16 field38;
    s16 field3A;
    s8 field3C;
    f32 field40;
    s16 field44;
    s16 field46;
    s32 field48;
} Game1DD500Impact;
typedef struct Game1DD500Hit { f32 height; u8 geometry[0x20]; } Game1DD500Hit;
void func_1504715C(void *, void *);
s32 func_15134070(void *);
void func_15143134(f32 *, f32 *, s32);
void func_15153F18(s16 *, void *, s32, s32, s32);
extern u8 D_800A3FD8[];
extern f32 D_800AA120;
extern f32 D_800AA2A0;
extern f32 D_800AA2A4;
extern f32 D_800AA2A8;
extern f32 D_800AA2AC;
extern f32 D_800AA2B0;

/*
 * The optional arg1 actor supplies the effect profile; arg0 supplies the
 * position/transform. Model bytes 83/165 or an absent arg1 select profile 4
 * locally, before the descriptor-variant checks.
 */
void func_151B01B8(void *arg0, void *arg1) {
    Game1DD500Impact packet;
    u8 shade;
    Game1DD500Hit hit;
    s32 effectProfileIndex;

    if ((arg0 != 0) && (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) && ((*(u8 *)((u8 *)arg0 + 0x74) & 0xF) != 0xF)) {
        func_1504715C(&hit, arg0);
        effectProfileIndex = arg1 != 0 ?
            ((*(u8 *)((u8 *)arg1 + 4) == 0x53 || *(u8 *)((u8 *)arg1 + 4) == 0xA5) ?
                4 : func_15134070(arg1)) : 4;
        if (effectProfileIndex != 0x63) {
            if (D_800A3FD8[effectProfileIndex * 0x10 + 0xE] != 2) {
                shade = ((s32) *(u16 *)((u8 *)arg0 + 0x7A) >> 8) + 0x40;
                func_15143134(&D_800AA120, &packet.position[0], *(s32 *)((u8 *)arg0 + 0x1D4) + 0x180);
                packet.field2C = 0xA;
                packet.field2E = 0x14;
                packet.field00 = shade - 0x68;
                packet.field14 = D_800AA2A0;
                packet.field02 = 0xD0;
                packet.field04 = -0x1B;
                packet.field06 = 0x36;
                packet.field30 = 3;
                packet.field32 = 2;
                packet.field34 = 0x1E;
                packet.field36 = 0x28;
                packet.field38 = 0x9B;
                packet.field3A = 0x64;
                packet.field18 = D_800AA2A4;
                packet.field1C = D_800AA2A8;
                packet.field20 = D_800AA2AC;
                packet.field24 = 6.0f;
                packet.field28 = D_800AA2B0;
                packet.field40 = 0.5f;
                if (D_800A3FD8[effectProfileIndex * 0x10 + 0xE] == 1) {
                    packet.field3C = 1;
                } else {
                    packet.field3C = 0;
                }
                packet.field44 = 0x10;
                packet.field46 = 0xF;
                packet.field48 = 0;
                func_15153F18(&packet.field00, &packet.position[0], (s32) &hit, 0xFF, 1);
            }
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B03B8.s")
void *func_10022EC0(void *, const void *, u32);
/* The independent wrapper preserves the allocator result in v0. */
void *func_151491F4(s16, s8, s8, u8, u8, s32, u8, s32);
void func_151494E0(s32, u8);
s32 func_15134070(void *);
extern u8 D_800A3FE6[];

typedef struct Game1DD500Owner {
    u8 pad0[0x3B];
    u8 id;
} Game1DD500Owner;

typedef struct Game1DD500Node {
    s32 object;
    s32 state;
    s32 value;
} Game1DD500Node;

typedef struct Game1DD500Packet {
    Game1DD500Owner *owner;
    u8 id;
    s32 count;
    Game1DD500Node nodes[11];
    f32 time;
    u8 kind;
} Game1DD500Packet;

typedef struct Game1DD500Marker {
    Game1DD500Owner *owner;
    u8 id;
} Game1DD500Marker;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B09BC CURRENT (1476) */
void *func_151B09BC(Game1DD500Owner *arg0, u8 *arg1, s16 arg2, u8 arg3, s32 arg4) {
    void *saved;
    Game1DD500Packet packet;
    Game1DD500Marker marker;
    s32 classification;
    u8 kind;
    u8 timed;
    s16 lifetime;
    s32 index;
    void *result;

    if (arg0 == 0) {
        return 0;
    }
    classification = 4;
    if (arg1 != 0) {
        if ((arg1[4] == 0x53) || (arg1[4] == 0xA5)) {
            classification = 4;
        } else {
            classification = func_15134070(arg1);
        }
    }
    if (classification == 0x63) {
        return 0;
    }
    kind = D_800A3FE6[classification * 0x10];
    if (kind == 2) {
        return 0;
    }
    if (kind == 1) {
        packet.kind = 1;
    } else {
        packet.kind = 0;
    }
    marker.owner = arg0;
    marker.id = arg0->id;
    func_151494E0((s32)&marker, 0x13);
    timed = 0;
    if (arg2 == -1) {
        lifetime = 0x12C;
    } else {
        lifetime = arg2;
        timed = 1;
    }
    packet.owner = arg0;
    packet.id = arg0->id;
    packet.count = 0;
    packet.time = 0.0f;
    for (index = 0; index < 11; index++) {
        packet.nodes[index].object = 0;
        packet.nodes[index].state = 0;
        packet.nodes[index].value = 0;
    }
    result = func_151491F4(lifetime, -1, 0x13, timed, 0xF, 0x98, arg3, arg4);
    if (result != 0) {
        saved = result;
        func_10022EC0((u8 *)result + 0x28, &packet, 0x98);
        result = saved;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B09BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B09BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B0B88.s")
s32 func_15046C80(f32 *, u16, f32, void *);
void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);
void func_151DAB58(u8, f32, u8, f32 *, s32, u8, s32);
extern f32 D_800AA2F0;
extern f32 D_800AA2F4;
extern f32 D_800AA2F8;
extern f32 D_800BE9A4;

typedef struct Game1B118CHorizontal { f32 x, z; } Game1B118CHorizontal;
typedef struct Game1B118CVertical { f32 delta, speed; } Game1B118CVertical;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B118C CURRENT (5955) */
s32 func_151B118C(void *arg0) {
    f32 displacementZ;
    f32 oldY;
    Game1B118CHorizontal previous;
    f32 collisionPosition[3];
    f32 effectPosition[3];
    f32 effectSize;
    u8 *motion;
    Game1B118CVertical vertical;
    register f32 displacementX;
    register f32 displacementY;
    register f32 x;
    register f32 y;
    register f32 z;
    f32 blend;
    s8 alive;

    oldY = *(f32 *)((u8 *)arg0 + 0x38);
    motion = (u8 *)arg0 + 0x110;
    previous.x = *(f32 *)motion;
    previous.z = *(f32 *)(motion + 8);
    alive = 1;
    *(f32 *)motion = previous.x * (0.25f * D_800BE9A4);
    *(f32 *)(motion + 8) = previous.z * (0.25f * D_800BE9A4);
    vertical.speed = *(f32 *)(motion + 4);
    displacementX = (*(f32 *)motion + previous.x) * 0.5f * D_800BE9A4;
    vertical.delta = *(f32 *)(motion + 0xC) * D_800BE9A4;
    displacementY = vertical.speed * D_800BE9A4 + vertical.delta * D_800BE9A4 * 0.5f;
    displacementZ = (*(f32 *)(motion + 8) + previous.z) * 0.5f * D_800BE9A4;
    *(f32 *)(motion + 4) = vertical.speed + vertical.delta;
    *(f32 *)((u8 *)arg0 + 0x38) = oldY + displacementY;
    y = *(f32 *)((u8 *)arg0 + 0x38);
    *(f32 *)((u8 *)arg0 + 0x34) += displacementX;
    x = *(f32 *)((u8 *)arg0 + 0x34);
    *(f32 *)((u8 *)arg0 + 0x3C) += displacementZ;
    *(f32 *)((u8 *)arg0 + 0x40) += displacementX;
    z = *(f32 *)((u8 *)arg0 + 0x3C);
    *(f32 *)((u8 *)arg0 + 0x44) += displacementY;
    *(f32 *)((u8 *)arg0 + 0x48) += displacementZ;
    blend = D_800AA2F0;
    *(f32 *)((u8 *)arg0 + 0x40) = x + (*(f32 *)((u8 *)arg0 + 0x40) - x) * blend;
    *(f32 *)((u8 *)arg0 + 0x44) = y + (*(f32 *)((u8 *)arg0 + 0x44) - y) * blend;
    *(f32 *)((u8 *)arg0 + 0x48) = z + (*(f32 *)((u8 *)arg0 + 0x48) - z) * blend;
    if (motion[0x24] != 0) {
        collisionPosition[0] = x;
        collisionPosition[1] = oldY - *(f32 *)((u8 *)arg0 + 0x30);
        collisionPosition[2] = *(f32 *)((u8 *)arg0 + 0x3C);
        if (func_15046C80(collisionPosition, 0,
                         *(f32 *)((u8 *)arg0 + 0x38) - *(f32 *)((u8 *)arg0 + 0x30),
                         (u8 *)arg0 + 0x78) != 0) {
            effectPosition[0] = collisionPosition[0];
            effectPosition[2] = collisionPosition[2];
            effectPosition[1] = *(f32 *)((u8 *)arg0 + 0x78) + 5.0f;
            effectSize = (*(f32 *)(motion + 0x14) + *(f32 *)(motion + 0x1C) * 0.5f +
                          (*(f32 *)(motion + 0x18) + *(f32 *)(motion + 0x20) * 0.5f)) * 0.5f;
            if (func_150ADA20() & 1) {
                func_151D9B8C(motion[0x25], effectSize * D_800AA2F4,
                             *((u8 *)arg0 + 0x5C), (s32)((u8 *)arg0 + 0x7C),
                             effectPosition, 0x64, 0, 1, 0,
                             *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 1));
            } else {
                func_151DAB58(motion[0x25], effectSize * D_800AA2F8,
                             *((u8 *)arg0 + 0x5C), effectPosition, 1,
                             *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 1));
            }
            alive = 0;
        }
    }
    return alive;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B118C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B118C.s")
s32 func_151B1478(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B14AC.s")
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B1828 CURRENT (303) */
s32 func_151B1828(u8 *arg0) {
    f32 sp24;
    u8 *volatile sp1C;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 *temp_v1;

    *(u8 *)(arg0 + 0x120) += *(s8 *)(arg0 + 0x122) * D_800BE9E4;
    *(u8 *)(arg0 + 0x121) += *(s8 *)(arg0 + 0x123) * D_800BE9E4;
    sp24 = func_151423D8(*(u8 *)(arg0 + 0x120) - 0x40);
    temp_v1 = (void *)(arg0 + 0x110);
    sp1C = temp_v1;
    temp_fv0 = func_151423D8(*(u8 *)(temp_v1 + 0x11) - 0x40);
    temp_v1 = sp1C;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)(arg0 + 0x2C) += ((*(f32 *)(temp_v1 + 0x14) + *(f32 *)(temp_v1 + 0x1C) * sp24) - temp_fv1) * 0.5f;
    *(f32 *)(arg0 + 0x30) += ((*(f32 *)(temp_v1 + 0x18) + *(f32 *)(temp_v1 + 0x20) * temp_fv0) - temp_fa0) * 0.5f;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B1828 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1828.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B1918 CURRENT (520) */
void func_151B1918(s32 arg0) {
    s32 var_s3;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s2;

    var_s2 = (u8 *)(arg0 + 0x28);
    *(s32 *)((u8 *)arg0 + 0x30) = 0;
    var_s0 = var_s2 + 0xC;
    var_s3 = 0;
    *(f32 *)((u8 *)arg0 + 0xB8) = 0.0f;
    do {
        var_s1 = var_s0;
        if (*(s32 *)(var_s2 + 0xC) != 0) {
            func_1516972C(*(s32 *)var_s0);
        }
        *(s32 *)(var_s1 + 4) = 0;
        *(s32 *)(var_s1 + 8) = 0;
        var_s3 += 0xC;
        var_s2 += 0xC;
        var_s0 += 0xC;
    } while (var_s3 != 0x84);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B1918 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1918.s")
void func_151B19A4(void *arg0, void *arg1, u8 arg2) {
    s32 temp_v1;
    u8 *temp_v0;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x28);
    if ((arg2 == 0) || (arg2 == 0x13)) {
        if ((temp_v1 == *(s32 *)arg1) ||
            (*(u8 *)((u8 *)arg0 + 0x2C) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else {
        temp_v0 = (u8 *)arg0 + 0x28;
        if (arg2 == 0x2D) {
            if (*(s32 *)arg1 == *(s32 *)temp_v0) {
                *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0) {
                *(s32 *)temp_v0 = *(s32 *)arg1;
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
void func_151B1918(s32 arg0);
void func_1514933C(s32 arg0);
void func_15149368(s32 arg0);

void func_151B1A58(s32 arg0) {
    func_151B1918(arg0);
    func_1514933C(arg0);
}
void func_151B1A84(s32 arg0) {
    func_151B1918(arg0);
    func_15149368(arg0);
}
