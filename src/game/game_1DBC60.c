#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DBC60.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AE7B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u32 func_1513418C(void *, s32, u8, s32);
void func_1516962C(s32, void *, s32);
extern f32 D_800A9D80;

typedef struct Game1DBC60Packet {
    s32 field_00;
    s32 field_04;
    u8 field_08;
    u8 pad09[3];
    void *field_0C;
    s8 field_10;
    u8 pad11[3];
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    s16 field_28;
    s8 field_2A;
    s8 field_2B;
    s8 field_2C;
    s8 field_2D;
} Game1DBC60Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE7B0 CURRENT (366) */
u32 func_151AE7B0(void *arg0, f32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    volatile s32 sp18;
    Game1DBC60Packet packet;
    f32 temp_ft0;
    f32 temp_ft1;
    s16 temp_v0;
    u8 temp_t6;

    if (arg0 == 0) {
        return 0;
    }
    func_1516962C(0x28, arg0, 0x11);
    packet.field_00 = 0;
    packet.field_04 = 0;
    temp_t6 = *(u8 *)((u8 *)arg0 + 0x3B);
    temp_v0 = arg2;
    temp_ft0 = D_800A9D80;
    temp_ft1 = arg1;
    packet.field_10 = 1;
    packet.field_2A = 2;
    packet.field_0C = arg0;
    packet.field_08 = temp_t6;
    packet.field_14 = 0.0f;
    packet.field_18 = 0.0f;
    packet.field_1C = 0.0f;
    packet.field_20 = temp_ft0;
    packet.field_24 = temp_ft1;
    if (temp_v0 != 0) {
        packet.field_28 = temp_v0;
        packet.field_2A = 6;
    } else {
        packet.field_28 = 0x12C;
    }
    packet.field_2B = 6;
    packet.field_2C = -1;
    packet.field_2D = 5;
    return func_1513418C(&packet, 0, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE7B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DBC60/func_151AE7B0.s")
