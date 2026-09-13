#include "types.h"

/*
 * Reviewed source unit: src/game/game_6C960.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503F4B0
 * - func_1503F62C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game6C960Actor {
    u8 pad0[0x3F5];
    u8 field_3F5;
} Game6C960Actor;

void func_1505E0C4(s32, s32, Game6C960Actor *, s32, s32, s32, s32,
                   f32, f32, f32, f32, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_6C960/func_1503F4B0.s")

void func_1503F5B8(Game6C960Actor *arg0, s32 arg1, s32 arg2, f32 arg3,
                   f32 arg4, s32 arg5) {
    func_1505E0C4(0, 0, arg0, 0, arg1, arg2, arg0->field_3F5, arg3,
                  arg4, 0.0f, 0.0f, arg5);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_6C960/func_1503F62C.s")
extern void func_10004074(s32 arg0);
extern void func_100043B4();

void func_1503F7B8(void *arg0) {
    func_100043B4(*(s32 *)((u8 *)arg0 + 0x3E8), 4);
    func_100043B4(*(s32 *)((u8 *)arg0 + 0x3EC), 4);
    func_10004074((s32) arg0);
}
