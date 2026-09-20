#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BFDD0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15192920
 * - func_151929A4
 * - func_15192D48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10022EC0(void *, void *, s32);
s32 func_151491F4(s16, s32, s32, s32, s32, s32, s32, s32);
typedef struct Game1BFDD0Packet {
    void *owner;
    u8 type;
    u8 pad5[3];
    f32 value;
} Game1BFDD0Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15192920 CURRENT (507) */
void func_15192920(void *arg0) {
    Game1BFDD0Packet packet;
    s32 temp_v0;

    if (arg0 != 0) {
        packet.owner = arg0;
        packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
        packet.value = 0.0f;
        temp_v0 = func_151491F4(0x23, -1, 0x14, 1, 0x10, 0xC, 0xFF, 1);
        if (temp_v0 != 0) {
            func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15192920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFDD0/func_15192920.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFDD0/func_151929A4.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15192D48 CURRENT (146) */
s32 func_15192D48(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    Game1BFDD0Packet packet;
    s32 temp_v0;
    s32 var_v1;

    if (arg0 == 0) {
        return 0;
    }
    packet.owner = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.value = 0.0f;
    temp_v0 = func_151491F4(arg1, -1, 0x18, 1, 0x16, 0xC, (s32)arg2, arg3);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0xC);
        var_v1 = temp_v0;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15192D48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFDD0/func_15192D48.s")
