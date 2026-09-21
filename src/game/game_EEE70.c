#include "types.h"

/*
 * Reviewed source unit: src/game/game_EEE70.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C1A40
 * - func_150C1E34
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameEEE70State {
    u8 pad0[0x1D4];
    s32 field_1D4;
} GameEEE70State;

void func_15142314(s32, s32, void *);

s32 func_150C19C0(void *arg0, GameEEE70State *arg1, u8 arg2) {
    s32 index;

    switch (arg2) {
    case 1:
        index = 0x18;
        break;
    case 2:
        index = 0x15;
        break;
    }
    func_15142314(arg1->field_1D4, index, arg0);
    return 1;
}
s32 func_150C1A2C(s32 arg0, s32 arg1) {
    return 7;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EEE70/func_150C1A40.s")
void func_151429E0(u8, u8 *, u8 *, u8 *);
void func_1518CA80(void *, s32);
s32 func_150ADA20(void);
extern f64 D_800A0228;

typedef struct GameEEE70EffectPacket {
    f32 position[3];
    u8 pad0C[0xA];
    s16 values[9];
    u8 colors[10];
} GameEEE70EffectPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C1E34 CURRENT (3641) */
s32 func_150C1E34(s32 arg0, s32 arg1, f32 arg2, f32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7,
                   f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12) {
    GameEEE70EffectPacket packet;
    s32 integer;
    s32 scaled;

    packet.position[2] = arg4;
    packet.position[0] = arg2;
    packet.position[1] = arg3;
    packet.values[6] = 0x96;
    packet.values[8] = 0x258;
    integer = (s32)arg12;
    packet.values[4] = (s32)((arg2 - arg5) * 10.0f);
    packet.values[7] = 0x14;
    packet.values[5] = (s32)((arg4 - arg7) * 10.0f);
    packet.values[0] = integer;
    scaled = (s32)((f64)arg12 * D_800A0228);
    packet.values[1] = integer;
    packet.values[3] = scaled;
    packet.values[2] = scaled;
    func_151429E0(0, &packet.colors[0], &packet.colors[1], &packet.colors[2]);
    func_151429E0(0, &packet.colors[3], &packet.colors[4], &packet.colors[5]);
    packet.colors[6] = 0xFF;
    packet.colors[7] = 0xFF;
    packet.colors[8] = (func_150ADA20() & 0xF) + 0xC;
    packet.colors[9] = 1;
    func_1518CA80(&packet, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C1E34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EEE70/func_150C1E34.s")
