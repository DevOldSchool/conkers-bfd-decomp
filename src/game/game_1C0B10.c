#include "types.h"

/*
 * Reviewed source unit: src/game/game_1C0B10.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15193660
 * - func_151938FC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C0B10/func_15193660.s")
typedef struct {
    u8 id;
    u8 pad1[3];
    void *object;
    s8 field8;
    u8 pad9[3];
    f32 values[6];
    s8 field24;
    u8 pad25;
    s16 field26;
    s16 field28;
    s16 field2A;
    u8 pad2C[2];
    s8 field2E;
    s8 field2F;
    s8 field30;
    u8 pad31[3];
    f32 field34;
    s8 field38;
    s8 field39;
} Game1C0B10Packet;

void func_15134DAC(u8 *, s32, void *);
extern f32 D_800A81E4;

void func_151937F4(void *arg0, s32 arg1, s32 arg2) {
    Game1C0B10Packet packet;

    if ((arg0 != 0) && (*(s32 *)arg0 != 0)) {
        packet.id = *(u8 *)((u8 *)arg0 + 0x3B);
        packet.values[0] = -28.0f;
        packet.object = arg0;
        packet.field8 = 0;
        packet.field24 = 2;
        packet.field26 = 0x1E;
        packet.field28 = 0x19;
        packet.field2A = 0x2EE;
        packet.field2E = 3;
        packet.field2F = 3;
        packet.field30 = -1;
        packet.field38 = 4;
        packet.field39 = -1;
        packet.values[1] = 6.0f;
        packet.values[2] = 1.0f;
        packet.values[3] = -58.0f;
        packet.values[4] = -3.0f;
        packet.values[5] = -31.0f;
        packet.field34 = D_800A81E4;
        func_15134DAC(&packet.id, 0, arg0);
    }
}
extern f32 D_800A81E8;

s32 func_151938E4(u8 *arg0) {
    *(f32 *)(arg0 + 0x74) = D_800A81E8;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C0B10/func_151938FC.s")
