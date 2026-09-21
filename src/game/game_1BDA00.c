#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BDA00.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151905BC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1BDA00CallbackState {
    u8 pad0[0x8A];
    u8 callback_index;
} Game1BDA00CallbackState;

typedef void (*Game1BDA00Callback)(Game1BDA00CallbackState *, void *, u8);

void func_151D33FC(void *, void *);
extern Game1BDA00Callback D_8008D684[];

void func_15190550(Game1BDA00CallbackState *arg0, void *arg1, u8 arg2) {
    Game1BDA00Callback callback;

    if (arg2 == 0x2A) {
        func_151D33FC(arg0, arg1);
    }
    callback = D_8008D684[arg0->callback_index];
    if (callback != 0) {
        callback(arg0, arg1, arg2);
    }
}
void func_1505D024(void *, s32, s32, s32);
extern s32 D_800BE9E4;
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151905BC CURRENT (105) */
s32 func_151905BC(u8 *arg0) {
    s32 temp_t4;
    s32 temp_t8;
    s32 temp_v0;
    u8 *temp_s0;
    u8 *temp_v0_2;

    temp_s0 = arg0 + 0x90;
    temp_t8 = (*(s32 *)(arg0 + 0x94) += D_800BE9E4);
    if (temp_t8 >= *(s32 *)(arg0 + 0x90)) {
        do {
            func_1505D024(*(void **)(arg0 + 0x10), 0x60021, 0,
                          ((s32)(*(u8 **)(temp_s0 + 8) -
                                 (u8 *)&D_800CC2D0)) /
                              812);
            temp_v0 = *(s32 *)temp_s0;
            temp_t4 = (*(s32 *)(temp_s0 + 4) -= temp_v0);
        } while (temp_t4 >= temp_v0);
    }
    temp_v0_2 = *(u8 **)(*(u8 **)(arg0 + 0x10) + 0x31C);
    if ((temp_v0_2 != 0) && (temp_v0_2[0x84] == 0)) {
        *(s16 *)(temp_v0_2 + 0x46) = 0x3E8;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151905BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDA00/func_151905BC.s")
typedef struct Game1BDA00Leaf {
    u8 pad0[0x1AC];
    s8 field_1AC;
} Game1BDA00Leaf;

typedef struct Game1BDA00Inner {
    u8 pad0[0x31C];
    Game1BDA00Leaf *field_31C;
} Game1BDA00Inner;

typedef struct Game1BDA00Object {
    u8 pad0[0x10];
    Game1BDA00Inner *field_10;
} Game1BDA00Object;

void func_151906C4(Game1BDA00Object *arg0) {
    Game1BDA00Leaf *leaf = arg0->field_10->field_31C;

    if (leaf) {
        leaf->field_1AC = 0;
    }
}
