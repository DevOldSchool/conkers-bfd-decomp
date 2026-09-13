#include "types.h"

/*
 * Reviewed source unit: src/game/game_61490.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15033FE0
 * - func_150341BC
 * - func_15034420
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_61490/func_15033FE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_61490/func_150341BC.s")
typedef struct Game61490Actor {
    u8 pad0[0x1D1];
    s8 field_1D1;
    u8 pad1D2[0x112];
    s32 field_2E4;
    u8 pad2E8[0x44];
} Game61490Actor;

typedef struct Game61490Command {
    s16 opcode;
    s16 value;
} Game61490Command;

extern Game61490Actor D_800CC2D0[];

Game61490Command *func_15034340(Game61490Command *arg0, s32 arg1) {
    Game61490Actor *actor;

    actor = &D_800CC2D0[arg1];
    if (actor->field_1D1 != 0) {
        arg0->opcode = 6;
        arg0++;
        arg0[-1].value = actor->field_1D1 * 0xC8;
    }
    return arg0;
}
Game61490Command *func_150343B0(Game61490Command *arg0, s32 arg1) {
    Game61490Actor *actor;

    actor = &D_800CC2D0[arg1];
    if (actor->field_1D1 != 0) {
        arg0->opcode = 6;
        arg0++;
        arg0[-1].value = actor->field_1D1 * 0xC8;
    }
    return arg0;
}
extern f32 D_80097D18;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15034420 CURRENT (405) */
Game61490Command *func_15034420(Game61490Command *arg0, s32 arg1) {
    s32 value;
    s32 part;

    arg0[0].opcode = 0;
    arg0[1].opcode = 0x18;
    value = (s32)((f32)D_800CC2D0[arg1].field_2E4 * D_80097D18);
    part = (s16)value >> 4;
    arg0[0].value = part;
    arg0[1].value = (s16)value - part;
    return arg0 + 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15034420 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_61490/func_15034420.s")
