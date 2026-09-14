#include "types.h"

/*
 * Reviewed source unit: src/game/game_3E890.c
 * Boundary evidence: docs/evidence/game_3E890.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150113E0
 * - func_1501175C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_3E890/func_150113E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_3E890/func_1501175C.s")
void func_10022EC0(void *, void *, s32);
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game3E890Packet {
    void *owner;
    u8 type;
    u8 pad5;
    s16 field6;
} Game3E890Packet;

void func_15011A78(void *arg0, u8 arg1, s32 arg2) {
    Game3E890Packet packet;
    u8 *temp_v0;

    packet.owner = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field6 = 0;
    temp_v0 = func_15149130(0x12C, -1, 0x55, -1, 0, 0x42, 8, (s32)arg1, arg2);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 8);
    }
}
