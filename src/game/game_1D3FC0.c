#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D3FC0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A6BD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151A6AB8(s32 arg0);
void func_1513CA6C(s32 arg0);
void func_1513CAA0(s32 arg0);

typedef struct Game1D3FC0Actor {
    u8 pad0[0x7A];
    u16 field_7A;
    u8 pad7C[0x2B0];
} Game1D3FC0Actor;

typedef struct Game1D3FC0Node {
    u8 pad0[0x38];
    Game1D3FC0Actor *field_38;
} Game1D3FC0Node;

void func_1505D024(s32, s32, s32, s32);
Game1D3FC0Node *func_151A6BD8(s32);
extern Game1D3FC0Actor D_800CC2D0[];

void func_151A6B10(s32 arg0) {
    func_151A6AB8(arg0);
    func_1513CA6C(arg0);
}
void func_151A6B3C(s32 arg0) {
    func_151A6AB8(arg0);
    func_1513CAA0(arg0);
}
void func_151A6B68(Game1D3FC0Actor *arg0, s32 arg1) {
    Game1D3FC0Node *node;
    Game1D3FC0Actor *actor = 0;
    s32 actor_index;

    node = func_151A6BD8(arg1);
    if (node != 0) {
        actor = node->field_38;
    }
    if (actor != 0) {
        actor_index = actor - D_800CC2D0;
    } else {
        actor_index = -1;
    }
    func_1505D024((s32)arg0, 0x60034, arg0->field_7A, actor_index);
}
extern s32 D_800A5770[];
extern u8 D_800DCE50[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A6BD8 CURRENT (4235) */
Game1D3FC0Node *func_151A6BD8(s32 arg0) {
    s32 outer;
    s32 inner;
    Game1D3FC0Node *node;

    for (outer = 0; outer < 2; outer++) {
        for (inner = 0; inner < 2; inner++) {
            node = *(Game1D3FC0Node **)(D_800DCE50 + inner * 0x1A0 + D_800A5770[outer] * 4);
            while (node != 0) {
                if ((*(u8 *)((u8 *)node + 0x13) == 0x2C) &&
                    (*(s32 *)((u8 *)node + 0x28) == arg0)) {
                    return node;
                }
                node = *(Game1D3FC0Node **)((u8 *)node + 8);
            }
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A6BD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D3FC0/func_151A6BD8.s")
