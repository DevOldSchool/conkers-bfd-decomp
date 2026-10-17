#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1DEF60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B1B34
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
typedef struct Game1DEF60B1AB0Packet {
    void *owner;
    u8 type;
    u8 pad5[3];
    f32 value;
} Game1DEF60B1AB0Packet;

void func_151B1AB0(void *arg0) {
    u8 *temp_v0;
    Game1DEF60B1AB0Packet packet;

    if ((s32)arg0 != 0) {
        packet.owner = arg0;
        packet.type = *(u8 *)((u8 *)packet.owner + 0x3B);
        packet.value = 0.0f;
        temp_v0 = func_151491F4(0x3C, -1, 0x15, 1, 0x11, 0xC, 0xFF, 1);
        if (temp_v0 != 0) {
            func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DEF60/func_151B1B34.s")

void func_151B1FAC(void *arg0, void *arg1, u8 arg2) {
    s32 temp_t6;
    u8 *temp_v0;

    temp_t6 = arg2;
    temp_v0 = (u8 *)arg0 + 0x28;
    if (temp_t6 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0) {
            u8 *dst = temp_v0;

            *(s32 *)dst = *(s32 *)arg1;
            *(u8 *)(dst + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if (temp_t6 == 0) {
        s32 temp_v1 = *(s32 *)arg1;

        if ((temp_v1 == *(s32 *)temp_v0) ||
            (temp_v0[4] == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    }
}
