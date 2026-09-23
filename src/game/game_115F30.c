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
