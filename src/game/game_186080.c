#include "types.h"

/*
 * Reviewed source unit: src/game/game_186080.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15158BD0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad00[0x10];
    s32 field10;
    s32 field14;
    void *owner;
    u8 ownerId;
    s8 data1D[3];
    f32 x;
    f32 y;
    f32 z;
    s8 field2C;
    s8 field2D;
    s8 field2E;
    s8 field2F;
    s8 field30;
    s8 field31;
    u8 pad32[0x1E];
    s8 field50;
} Game186080Effect;

void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_1516979C(u8 *);
s32 func_15159370(void *, s8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158BD0 CURRENT (150) */
u8 *func_15158BD0(void *arg0, u8 arg1, s32 arg2) {
    u8 *effect;

    if (arg0 == 0) {
        return 0;
    }
    effect = func_15167A68(0x2E, 0, arg2 + 0x58, 1, 0xFF, 1);
    if (effect == 0) {
        return 0;
    }
    *(void **)(effect + 0x18) = arg0;
    *(u8 *)(effect + 0x1C) = *(u8 *)((u8 *)arg0 + 0x3B);
    *(s8 *)(effect + 0x2C) = 2;
    *(s8 *)(effect + 0x2D) = 2;
    *(s8 *)(effect + 0x2E) = 2;
    *(s8 *)(effect + 0x2F) = 3;
    *(s8 *)(effect + 0x30) = 0;
    *(f32 *)(effect + 0x20) = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)(effect + 0x24) = *(f32 *)((u8 *)arg0 + 0x18);
    *(s8 *)(effect + 0x31) = 0;
    *(f32 *)(effect + 0x28) = *(f32 *)((u8 *)arg0 + 0x1C);
    if (arg1 != 0) {
        *(s8 *)(effect + 0x31) = 1;
    }
    *(s32 *)(effect + 0x10) = 1;
    *(s32 *)(effect + 0x14) = 0;
    if (func_15159370(arg0, (s8 *)(effect + 0x1D)) == 0) {
        func_1516979C(effect);
        return 0;
    }
    *(s8 *)(effect + 0x50) = 0;
    return effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158BD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_186080/func_15158BD0.s")
/* Call context: func_1514EDF0: unique active project prototype */
/* Call context: func_15169804: unique active project prototype */
void func_1514EDF0(s32, s32);
void func_15169804(s32);

void func_15158CD4(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_15169804((s32) arg0);
}
