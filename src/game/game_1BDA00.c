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
