#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DEF60.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B1AB0
 * - func_151B1B34
 * - func_151B1FAC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10022EC0(void *, void *, s32);
s32 func_151491F4(s16, s8, s8, u8, u8, s32, u8, s32);
typedef struct Game1DEF60B1AB0Packet {
    void *owner;
    u8 type;
    u8 pad5[3];
    f32 value;
} Game1DEF60B1AB0Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B1AB0 CURRENT (507) */
void func_151B1AB0(void *arg0) {
    Game1DEF60B1AB0Packet packet;
    s32 temp_v0;

    if (arg0 != 0) {
        packet.owner = arg0;
        packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
        packet.value = 0.0f;
        temp_v0 = func_151491F4(0x3C, -1, 0x15, 1, 0x11, 0xC, 0xFF, 1);
        if (temp_v0 != 0) {
            func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B1AB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DEF60/func_151B1AB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DEF60/func_151B1B34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DEF60/func_151B1FAC.s")
