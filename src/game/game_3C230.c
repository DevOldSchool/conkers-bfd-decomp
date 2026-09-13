#include "types.h"

/*
 * Reviewed source unit: src/game/game_3C230.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500ED80
 * - func_1500EE94
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_3C230/func_1500ED80.s")

typedef struct {
    u8 pad0[0x3B];
    u8 type;
} Game3C230Actor;

typedef struct {
    Game3C230Actor *owner;
    u8 type;
    u8 pad5[3];
} Game3C230Packet;

void func_10022EC0(void *, void *, s32);
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_1500EE18(Game3C230Actor *arg0, s32 arg1, s32 arg2) {
    Game3C230Packet packet;
    u8 *object;

    packet.owner = arg0;
    packet.type = arg0->type;
    object = func_15149130(0x12C, -1, 0x45, -1, 0, 0, 8, 0xFF, 1);
    if (object != 0) {
        func_10022EC0(object + 0x28, &packet, sizeof(packet));
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_3C230/func_1500EE94.s")
