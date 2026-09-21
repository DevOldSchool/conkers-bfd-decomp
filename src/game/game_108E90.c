#include "types.h"

/*
 * Reviewed source unit: src/game/game_108E90.c
 * Boundary evidence: docs/evidence/game_raw_narrow_effect_record_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DB9E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_108E90/func_150DB9E0.s")
typedef struct Game108E90Packet {
    f32 field00;
    f32 field04;
    f32 field08;
    f32 field0C;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    s16 field24;
    s16 field26;
    s16 field28;
    s16 field2A;
    s16 field2C;
    s16 field2E;
    s16 field30;
    s16 field32;
    s16 field34;
    s16 field36;
    s8 field38;
    s8 field39;
    u8 pad3A[2];
    s32 field3C;
    s32 field40;
    s32 field44;
    s32 field48;
    s32 field4C;
    s32 field50;
    u8 field54;
    u8 field55;
} Game108E90Packet;

void func_15152F70(void *, u8, void *);
extern f32 D_800A0C24;
extern f32 D_800A0C28;
extern f32 D_800A0C2C;
extern f32 D_800A0C30;

void func_150DBC60(void *arg0) {
    Game108E90Packet packet;

    packet.field00 = D_800A0C24;
    packet.field24 = 1;
    packet.field26 = 2;
    packet.field28 = -0x4B;
    packet.field2C = -0x26;
    packet.field2A = 0x16;
    packet.field2E = 0x23;
    packet.field30 = 3;
    packet.field32 = 2;
    packet.field34 = 0x29;
    packet.field36 = 0;
    packet.field0C = 2.0f;
    packet.field10 = 2.0f;
    packet.field38 = 0xA;
    packet.field39 = 0x28;
    packet.field3C = 1;
    packet.field40 = 0;
    packet.field44 = 0;
    packet.field48 = 0;
    packet.field4C = 0;
    packet.field50 = 0;
    packet.field54 = 0xFF;
    packet.field55 = 0xFF;
    packet.field04 = D_800A0C28;
    packet.field08 = D_800A0C2C;
    packet.field1C = 7.0f;
    packet.field20 = 5.0f;
    packet.field14 = D_800A0C30;
    packet.field18 = 0.0f;
    func_15152F70(&packet, *(u8 *)((u8 *)arg0 + 0xC), arg0);
}
