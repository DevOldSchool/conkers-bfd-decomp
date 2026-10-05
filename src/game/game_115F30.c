#include "types.h"

/*
 * Reviewed source unit: src/game/game_115F30.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E8B1C
 * - func_150E8D5C
 * - func_150E9178
 * - func_150E93DC
 * - func_150E971C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10022EC0(s32, void *, s32);
u32 func_150ADA20(void);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A137C;
extern f32 D_800A1380;
extern f32 D_800A13B0;
extern f32 D_800A13B4;

typedef struct Game115F30Packet {
    f32 field_0;
    f32 field_4;
    f32 field_8;
} Game115F30Packet;

void func_150E8A80(void) {
    s32 temp_v0;
    Game115F30Packet packet;

    packet.field_0 = D_800A137C;
    packet.field_4 = D_800A1380;
    packet.field_8 = 0.0f;
    temp_v0 = func_15149130((s16) ((func_150ADA20() % 41U) + 0x1E), -1, 0x33, -1, 1, 0, 0xC, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 0xC);
    }
}
typedef struct Game115F30WeightedNode {
    void *region;
    s32 unknown4;
    f32 weight;
    struct Game115F30WeightedNode *next;
} Game115F30WeightedNode;

f32 func_150ADA68(void);
s32 func_15144B34(s32);
void func_1514470C(void *, f32 *);
extern f32 D_800A1384;
extern f32 D_800A1388;
extern f32 D_800A138C;
extern f32 D_800BE9A4;
extern s32 D_800BE9E8;
extern f32 D_800DCD90;
extern Game115F30WeightedNode *D_800DCDC4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E8B1C CURRENT (413) */
void func_150E8B1C(u8 *arg0) {
    f32 *state;
    f32 *reference;
    Game115F30WeightedNode *node;
    s32 result;
    f32 packet[6];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 distanceLimit;
    f32 scale;
    f32 speed;
    f32 selection;
    f32 weight;

    reference = (f32 *)func_15144B34(D_800BE9E8);
    state = (f32 *)(arg0 + 0x28);
    state[2] += (state[0] + func_150ADA68() * state[1]) * D_800BE9A4 * D_800DCD90;
    if (state[2] > 1.0f) {
        speed = D_800A1384;
        scale = D_800A1388;
        distanceLimit = D_800A138C;
        do {
            selection = func_150ADA68() * D_800DCD90;
            node = D_800DCDC4;
            weight = node->weight;
            while (weight < selection) {
                node = node->next;
                selection -= weight;
                weight = node->weight;
            }
            func_1514470C(node->region, packet);
            dx = packet[0] - reference[0];
            dy = packet[1] - reference[1];
            dz = packet[2] - reference[2];
            if (dx * dx + dy * dy + dz * dz < distanceLimit) {
                packet[3] = scale;
                packet[4] = speed;
                packet[5] = 0.0f;
                result = func_15149130((s16)((func_150ADA20() % 13U) + 5),
                                      -1, 0x34, -1, 1, 0, 0x18,
                                      arg0[0xC], arg0[1]);
                if (result != 0) {
                    func_10022EC0(result + 0x28, packet, 0x18);
                }
            }
            state[2] -= 1.0f;
        } while (state[2] > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E8B1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E8B1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E8D5C.s")
void func_150E90DC(void) {
    s32 temp_v0;
    Game115F30Packet packet;

    packet.field_0 = D_800A13B0;
    packet.field_4 = D_800A13B4;
    packet.field_8 = 0.0f;
    temp_v0 = func_15149130((s16) ((func_150ADA20() % 26U) + 5), -1, 0x36, -1, 1, 0, 0xC, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 0xC);
    }
}
typedef union {
    f32 words[15];
    s32 integers[15];
    u8 bytes[0x3C];
} Game115F30SpawnPacket;

extern f32 D_800A13B8;
extern f32 D_800A13BC;
extern f32 D_800A13C0;
extern f32 D_800A13C4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E9178 CURRENT (585) */
void func_150E9178(u8 *arg0) {
    f32 *state;
    f32 *reference;
    Game115F30WeightedNode *node;
    f32 distance_limit;
    f32 scale;
    f32 speed;
    f32 phase;
    f32 size;
    f32 selection;
    f32 weight;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 result;
    register u32 divisor;
    Game115F30SpawnPacket packet;

    reference = (f32 *)func_15144B34(D_800BE9E8);
    state = (f32 *)(arg0 + 0x28);
    *(volatile f32 *)&state[2] += (state[0] + func_150ADA68() * state[1]) * D_800BE9A4 * D_800DCD90;
    divisor = 13;
    if (*(volatile f32 *)&state[2] > 1.0f) {
        size = D_800A13B8;
        speed = D_800A13BC;
        scale = D_800A13C0;
        phase = 0.0f;
        distance_limit = D_800A13C4;
        do {
            selection = func_150ADA68() * D_800DCD90;
            node = D_800DCDC4;
            weight = node->weight;
            while (weight < selection) {
                node = node->next;
                selection -= weight;
                weight = node->weight;
            }
            func_1514470C(node->region, packet.words);
            dx = packet.words[0] - reference[0];
            dy = packet.words[1] - reference[1];
            dz = packet.words[2] - reference[2];
            if (dx * dx + dy * dy + dz * dz < distance_limit) {
                packet.words[3] = scale;
                packet.words[4] = speed;
                packet.words[5] = phase;
                packet.words[6] = size;
                packet.integers[12] = 0;
                packet.bytes[0x34] = 0;
                packet.bytes[0x35] = 0;
                packet.integers[14] = 0;
                result = func_15149130((s16)(func_150ADA20() % divisor + 5),
                                      -1, 0x37, -1, 1, 0, 0x3C, arg0[0xC], arg0[1]);
                if (result != 0) {
                    func_10022EC0(result + 0x28, &packet, 0x3C);
                }
            }
            *(volatile f32 *)&state[2] -= 1.0f;
        } while (*(volatile f32 *)&state[2] > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E9178 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E9178.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E93DC.s")
typedef struct Game115F30Owner {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD[0x2B];
    f32 field38;
    f32 field3C;
    f32 field40;
    u8 pad44[0x12C];
    f32 field170;
    s32 field174;
    u8 field178;
} Game115F30Owner;

typedef struct Game115F30Effect {
    s32 field0;
    s16 field4;
    u8 field6;
    u8 field7;
    s32 field8;
    s32 fieldC;
    u8 field10;
    u8 field11;
    u8 field12;
    u8 field13;
    u8 field14;
    u8 field15;
    u8 field16;
    u8 field17;
    s32 field18;
    u8 pad1C[6];
    s16 field22;
    s16 field24;
} Game115F30Effect;

s32 func_151337C0(void *);
void *func_1513C73C(s32 *, s32, s32, void *, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32);
f32 func_150ADA68(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E971C CURRENT (2812) */
s32 func_150E971C(Game115F30Owner *arg0) {
    Game115F30Effect effect;
    f32 scale;
    f32 *timing;
    s32 result;

    func_151337C0(arg0);
    timing = &arg0->field170;
    result = 1;
    if (arg0->field3C < *timing) {
      if ((((s32 *)timing)[1] & 0x1F) == 0xA) {
        scale = func_150ADA68() * 20.0f + 20.0f;
        effect.field0 = 0x9701;
        effect.field4 = 100;
        effect.field6 = 0xB;
        effect.field7 = 0;
        effect.field8 = 0;
        effect.fieldC = 0;
        effect.field10 = 0xFF;
        effect.field11 = 0xFF;
        effect.field12 = 0xFF;
        effect.field13 = 0xFF;
        effect.field14 = 0xFF;
        effect.field15 = 0xFF;
        effect.field16 = 0;
        effect.field17 = 7;
        effect.field18 = 0x3B0003;
        effect.field22 = 0x14;
        effect.field24 = 0xC;
        func_1513C73C((s32 *)&effect, 0, 0, timing + 2,
                       arg0->field38, *timing + 5.0f, arg0->field40,
                       scale, scale, func_150ADA20() & 0xFF, 0, 0,
                       arg0->fieldC, arg0->field1);
      }
      result = 0;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E971C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E971C.s")
