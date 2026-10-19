#include "types.h"

/*
 * Reviewed source unit: src/game/game_6E770.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150412C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_80084930[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150412C0 CURRENT (7170) */
void *func_150412C0(u8 *arg0) {
    union Packet {
        u64 command;
        struct { u32 first; u32 second; } words;
    };
    union Packet *cursor;

    cursor = (union Packet *)arg0;
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xD7000002;
        packet->words.second = 0xFFFFFFFF;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xE7000000;
        packet->words.second = 0;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xFCFFFFFF;
        packet->words.second = 0xFFFCF279;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xEF002C0F;
        packet->words.second = 0x0055204C;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xFD90003F;
        packet->words.second = (u32)D_80084930;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xFD900000;
        packet->words.second = (u32)D_80084930;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xF5900000;
        packet->words.second = 0x07000000;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xE6000000;
        packet->words.second = 0;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xF3000000;
        packet->words.second = 0x077FF200;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xE7000000;
        packet->words.second = 0;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xF5800800;
        packet->words.second = 0;
    }
    {
        union Packet *packet = cursor++;
        packet->words.first = 0xF2000000;
        packet->words.second = 0x000FC1FC;
    }
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150412C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150412C0.s")
typedef struct Game6E770Command {
    u32 w0;
    u32 w1;
} Game6E770Command;

Game6E770Command *func_15041508(Game6E770Command *, s32, s32, s32);
s32 func_15041480(u8);
extern u8 D_800848D0[];

Game6E770Command *func_150413FC(Game6E770Command *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    s32 i;

    i = 0;
    while (arg3[i] != 0) {
        arg0 = func_15041508(arg0, arg1 + i * 8, arg2, func_15041480(arg3[i]));
        i++;
    }
    return arg0;
}
s32 func_15041480(u8 arg0) {
    s32 i;

    for (i = 0; i < 0x50; i++) {
        if (arg0 == D_800848D0[i]) {
            return i;
        }
    }
    return i;
}
#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
Game6E770Command *func_15041508(Game6E770Command *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 remainder = arg3 % 8;

    { Game6E770Command *command = arg0++; command->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL((arg1 + 8) << 2, 12, 12) | _SHIFTL((arg2 + 12) << 2, 0, 12); command->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(arg1 << 2, 12, 12) | _SHIFTL(arg2 << 2, 0, 12); }
    { Game6E770Command *command = arg0++; command->w0 = _SHIFTL(0xE1, 24, 8); command->w1 = _SHIFTL((remainder * 8) << 5, 16, 16) | _SHIFTL((((arg3 - remainder) / 8) * 12) << 5, 0, 16); }
    { Game6E770Command *command = arg0++; command->w0 = _SHIFTL(0xF1, 24, 8); command->w1 = _SHIFTL(1 << 10, 16, 16) | _SHIFTL(1 << 10, 0, 16); }
    return arg0;
}
