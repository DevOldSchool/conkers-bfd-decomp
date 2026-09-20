#include "types.h"

/*
 * Reviewed source unit: src/game/game_68C70.c
 * Boundary evidence: docs/evidence/game_raw_actor_classification_emitter.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503B840
 * - func_1503B9BC
 * - func_1503CB98
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game68C70Leaf {
    u8 pad0[0x44];
    f32 field_44;
    u8 pad48[4];
    s16 field_4C;
} Game68C70Leaf;

typedef struct Game68C70Nested {
    u8 pad0[0x11C];
    Game68C70Leaf *field_11C;
} Game68C70Nested;

typedef struct Game68C70Actor {
    u8 pad0[0x31C];
    Game68C70Nested *field_31C;
} Game68C70Actor;

void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
u32 func_150ADA20(void);

void func_1503B7C0(Game68C70Actor *arg0) {
    arg0->field_31C->field_11C = func_10003C40(0x50, 1, 0, 0);
    func_100226F0(arg0->field_31C->field_11C, 0x50);
    arg0->field_31C->field_11C->field_44 = 30.0f;
    arg0->field_31C->field_11C->field_4C = (s16)(func_150ADA20() % 30U);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503B840.s")
extern u8 D_800CC5CB;

s32 func_1503B95C(s32 arg0, void *arg1) {
    s32 temp_v0;

    temp_v0 = *(u8 *)((u8 *)&D_800CC5CB + (arg0 * 0x32C));
    if (temp_v0 & 2) {
        *(s8 *)((u8 *)arg1 + 0x4E) = 0;
        return 0;
    }
    if (temp_v0 & 1) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503B9BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503CB98.s")
