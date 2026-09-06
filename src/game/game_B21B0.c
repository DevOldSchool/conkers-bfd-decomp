#include "types.h"

/*
 * Reviewed source unit: src/game/game_B21B0.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15084D00
 * - func_15084D70
 * - func_15085430
 * - func_15085710
 * - func_150859AC
 * - func_15085ABC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameB21B0Inner {
    u8 pad0[0x11B];
    u8 field_11B;
} GameB21B0Inner;

typedef struct GameB21B0Object {
    u8 pad0[0x31C];
    GameB21B0Inner *inner;
} GameB21B0Object;

#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15084D00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15084D70.s")
void func_15085410(GameB21B0Object *arg0, s32 arg1) {
    arg0->inner->field_11B = arg1;
}
u8 func_15085420(GameB21B0Object *arg0) {
    return arg0->inner->field_11B;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085430.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085710.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_150859AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085ABC.s")
