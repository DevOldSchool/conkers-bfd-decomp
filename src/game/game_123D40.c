#include "types.h"

/*
 * Reviewed source unit: src/game/game_123D40.c
 * Boundary evidence: docs/evidence/game_raw_record_glyph_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F695C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 field0;
    u8 pad1[3];
    void *field4;
    s8 field8;
    u8 pad9[3];
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    s8 field24;
    u8 pad25;
    s16 field26;
    s16 field28;
    s16 field2A;
    s16 field2C;
    s8 field2E;
    s8 field2F;
    s8 field30;
    u8 pad31[3];
    f32 field34;
    s8 field38;
    s8 field39;
} Game123D40Packet;

void func_15134DAC(u8 *, s32, void *, s16);
extern f32 D_800A1B70;

void func_150F6890(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    Game123D40Packet packet;

    packet.field0 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field1C = D_800A1B70;
    packet.field20 = 8.5f;
    packet.field34 = 1.0f;
    packet.field4 = arg0;
    packet.field8 = 3;
    packet.fieldC = 0.0f;
    packet.field10 = 0.0f;
    packet.field14 = 0.0f;
    packet.field18 = 0.0f;
    packet.field24 = 2;
    packet.field26 = 0x28;
    packet.field28 = 0x10;
    packet.field2A = arg1;
    packet.field2E = 5;
    packet.field2F = 8;
    packet.field30 = -1;
    packet.field38 = 0;
    packet.field39 = -1;
    packet.field2C = 0;
    func_15134DAC(&packet.field0, 0, arg0, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_123D40/func_150F695C.s")
