#include "types.h"

/*
 * Reviewed source unit: src/game/game_209B50.c
 * Boundary evidence: docs/evidence/game_raw_loader_transfer_emission_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151DC6A0
 * - func_151DC8BC
 * - func_151DC97C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_209B50/func_151DC6A0.s")
void *func_151DC6A0(void *, u8, s32);
void *func_10022EC0(void *, const void *, u32);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DC8BC CURRENT (1426) */
void func_151DC8BC(void *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    struct {
        s32 first;
        s32 second;
        s32 third;
        f32 value;
        u8 byte;
    } packet;
    s32 temp_v0;

    if (arg2 != 0) {
        func_151DC6A0(arg0, arg4, arg5);
    }
    packet.first = *(s32 *)arg0;
    packet.second = *(s32 *)((u8 *)arg0 + 4);
    packet.third = *(s32 *)((u8 *)arg0 + 8);
    packet.value = 0.0f;
    packet.byte = arg3;
    temp_v0 = func_15149130(arg1, -1, 0x5B, -1, 1, 0, 0x14, (s32)arg4, arg5);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0x14U);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DC8BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_209B50/func_151DC8BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_209B50/func_151DC97C.s")
