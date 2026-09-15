#include "types.h"

/*
 * Reviewed source unit: src/game/game_E7970.c
 * Boundary evidence: docs/evidence/game_raw_narrow_effect_record_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BA55C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10022EC0(void *, void *, s32);
u32 func_150ADA20(void);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct GameE7970Packet {
    void *field_0;
    u8 field_4;
    u8 pad5[3];
    f32 field_8;
} GameE7970Packet;

void func_150BA4C0(void *arg0, u8 arg1, s32 arg2) {
    GameE7970Packet packet;
    s32 temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_8 = 0.0f;
    temp_v0 = func_15149130((s16) ((func_150ADA20() % 9U) + 0xF), -1, 0x52, -1, 1, 0x3F, 0xC, (s32) arg1, arg2);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E7970/func_150BA55C.s")
void func_150BA8F0(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
