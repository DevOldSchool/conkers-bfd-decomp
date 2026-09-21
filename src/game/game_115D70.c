#include "types.h"

/*
 * Reviewed source unit: src/game/game_115D70.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E8930
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game115D70State {
    u8 pad0[0x28];
    f32 timer_28;
} Game115D70State;

f32 func_150ADA68(void);
void func_150E8930();
extern f32 D_800A1378;
extern f32 D_800BE9A4;

void func_150E88C0(Game115D70State *arg0) {
    arg0->timer_28 -= D_800BE9A4;
    if (arg0->timer_28 < 0.0f) {
        arg0->timer_28 = (func_150ADA68() * D_800A1378) + 201.0f;
        func_150E8930(arg0);
    }
}
typedef struct Game115D70Pair {
    s32 first;
    s32 second;
} Game115D70Pair;

typedef struct Game115D70Spawn {
    s8 active;
    u8 pad1;
    s16 duration;
    s8 size;
    s8 enabled;
    s8 sentinel;
    u8 pad7;
} Game115D70Spawn;

extern Game115D70Pair D_80088A80;
extern u8 D_800BE9EB;
extern s32 D_800DCDC4;
void func_15169260(Game115D70Pair *, s32, s32, s32);
void func_15164F0C(u8, u8, void *, u8, s32);
u32 func_150ADA20(void);
void func_151D8868(Game115D70Spawn *, s32, s32, s32);
void func_150E8A80(void);
void func_150E90DC(void);
void func_10010F30(s32, s32, s32, s16, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E8930 CURRENT (40) */
void func_150E8930(void) {
    Game115D70Pair sp30;
    Game115D70Spawn sp28;
    s32 active;

    sp30 = D_80088A80;
    func_15169260(&sp30, 2, 0, 0x1B);
    func_15164F0C(0, D_800BE9EB, 0, 0xFF, 1);
    sp28.active = 1;
    sp28.duration = (func_150ADA20() % 21U) + 0x14;
    sp28.enabled = 1;
    sp28.size = (func_150ADA20() % 6U) + 3;
    sp28.sentinel = -1;
    func_151D8868(&sp28, 0, 0xFF, 1);
    active = D_800DCDC4;
    if (active != 0) {
        func_150E8A80();
        active = D_800DCDC4;
    }
    if (active != 0) {
        func_150E90DC();
    }
    func_10010F30(0x4C8, 0x7FFF, 0x40,
                   (s16)(0x200 - (func_150ADA20() & 0x400)), 0);
    func_10010F30(0x4CD, 0x5DC0, 0x40,
                   (s16)(0x200 - (func_150ADA20() & 0x400)), 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E8930 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_115D70/func_150E8930.s")
