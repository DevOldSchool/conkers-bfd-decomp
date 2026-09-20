#include "types.h"

/*
 * Reviewed source unit: src/game/game_1179B0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EA5CC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s32 field0;
    s32 field4;
    u8 field8;
    u8 pad9[3];
    void *fieldC;
    s8 field10;
    u8 pad11[3];
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    s16 field28;
    s8 field2A;
    s8 field2B;
    s8 field2C;
    s8 field2D;
} Game1179B0Packet;

u32 func_1513418C(void *, s32, u8, s32);
extern f32 D_800A1438;

void func_150EA500(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    Game1179B0Packet packet;
    s32 mode;

    packet.field0 = 0;
    packet.field4 = 0;
    packet.field8 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field20 = 25.0f;
    packet.field24 = D_800A1438;
    packet.fieldC = arg0;
    packet.field10 = 1;
    packet.field14 = 0.0f;
    packet.field18 = 0.0f;
    packet.field1C = 0.0f;
    if (arg1 == -1) {
        packet.field28 = 0x12C;
    } else {
        packet.field28 = arg1;
    }
    if (arg1 == -1) {
        mode = 0;
    } else {
        mode = 4;
    }
    packet.field2A = mode | 0xA;
    packet.field2B = 7;
    packet.field2C = -1;
    packet.field2D = 6;
    func_1513418C(&packet, 0, 0xFF, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1179B0/func_150EA5CC.s")
