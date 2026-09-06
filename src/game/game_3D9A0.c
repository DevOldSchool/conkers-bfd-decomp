#include "types.h"

/*
 * Reviewed source unit: src/game/game_3D9A0.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150104F0
 * - func_15010538
 * - func_15010600
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_3D9A0/func_150104F0.s")

void func_10022EC0(void *arg0, void *arg1, s32 arg2);
u8 *func_15149130(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_15161E24(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);

typedef struct Game3D9A0Packet {
    void *owner;
    u8 type;
    u8 pad5;
    s16 x;
    s16 y;
    s16 z;
} Game3D9A0Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15010538 CURRENT (195) */
void func_15010538(void *arg0) {
    Game3D9A0Packet packet;
    u8 *object;

    func_15161E24(arg0, 2, 2, 0x12C, 0x1E, 0x64, 0xC8, 0xFF, 0xFF, 1);
    packet.owner = arg0;
    packet.x = 0;
    packet.y = 0;
    packet.z = 0;
    packet.type = ((u8 *)arg0)[0x3B];

    object = func_15149130(0x12C, -1, 0x50, -1, 0, 0x3D, 0xC, 0xFF, 1);
    if (object != 0) {
        func_10022EC0(object + 0x28, &packet, sizeof(packet));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15010538 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3D9A0/func_15010538.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_3D9A0/func_15010600.s")
