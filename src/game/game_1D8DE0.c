#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D8DE0.c
 * Boundary evidence: docs/evidence/game_raw_model_owner_mode_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AB930
 * - func_151AB9C8
 * - func_151ABD54
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u8 func_151D8E20(void);
void func_10022EC0(void *, void *, s32);
s32 func_151491F4(s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A9014;

typedef struct {
    void *field_0;
    u8 field_4;
    u8 pad_5[3];
    s32 field_8;
    f32 field_C;
    f32 field_10;
    f32 field_14;
    u8 field_18;
} Game1D8DE0Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB930 CURRENT (449) */
void func_151AB930(void *arg0) {
    volatile Game1D8DE0Packet packet;
    s32 temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_10 = D_800A9014;
    packet.field_8 = *(u16 *)((u8 *)arg0 + 0x84);
    packet.field_C = 0.0f;
    packet.field_14 = 3.0f;
    packet.field_18 = func_151D8E20();
    temp_v0 = func_151491F4(0x3C, -1, 0xE, 1, 9, 0x1C, 0xFF, 0);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, (void *)&packet.field_0, 0x1C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB930 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D8DE0/func_151AB930.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D8DE0/func_151AB9C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D8DE0/func_151ABD54.s")
