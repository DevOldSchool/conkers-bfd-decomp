#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D4140.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A6C90
 * - func_151A6F00
 * - func_151A743C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4140/func_151A6C90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4140/func_151A6F00.s")
typedef struct {
    f32 field_0;
    void *field_4;
    u8 spawn;
    u8 alternate;
    s16 first;
    s16 last;
} Game1D4140Entry;

typedef struct {
    u8 pad_0[0x10];
    f32 base_height;
    f32 bounce;
    f32 scale;
    u8 pad1C[0x20];
    f32 height;
    u8 pad40[4];
    f32 velocity_x;
    f32 velocity_y;
    f32 velocity_z;
    f32 rotation_x;
    f32 rotation_y;
    f32 rotation_z;
    u8 pad5C[4];
    s32 flags;
    s16 field_64;
    u8 pad_66[0x10A];
    Game1D4140Entry field_170;
} Game1D4140State;

void func_1516972C(void *);

s32 func_151A73EC(Game1D4140State *arg0) {
    Game1D4140Entry *temp_v0;

    temp_v0 = &arg0->field_170;
    if (arg0->field_64 < 0x20) {
        if (temp_v0->field_4 != 0) {
            func_1516972C(temp_v0->field_4);
            temp_v0->field_4 = 0;
        }
    }
    return 1;
}
u32 func_150ADA20(void);
void func_1514AB5C(f32, f32, f32, f32, s32, f32, f32, f32, f32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A743C CURRENT (90) */
s32 func_151A743C(Game1D4140State *arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    Game1D4140Entry *state;
    u8 alternate;

    state = (Game1D4140Entry *)((u8 *)arg0 + 0x170);
    arg0->height = arg0->base_height + arg4;
    if (arg0->field_170.field_4 != 0) {
        func_1516972C(state->field_4);
        state->field_4 = 0;
    }
    state = (Game1D4140Entry *)((u8 *)arg0 + 0x170);
    if (state->field_0 < arg0->velocity_y) {
        arg0->flags &= ~7;
        arg0->flags &= ~8;
        arg0->flags &= ~0x40;
        arg0->flags &= ~0x20;
        arg0->velocity_x = 0.0f;
        arg0->velocity_y = 0.0f;
        arg0->velocity_z = 0.0f;
        if (arg0->field_64 >= 0x21) {
            arg0->field_64 = 0x20;
        }
        if (state->spawn != 0) {
            alternate = 0;
            if (state->alternate != 0) {
                alternate = 1;
            }
            func_1514AB5C(arg1, arg4, arg3, arg0->scale * 35.0f,
                         func_150ADA20() % 3U + 2,
                         arg0->scale, arg0->scale * 0.5f,
                         arg0->scale, arg0->scale * 0.5f,
                         state->first, state->last, alternate);
        }
    } else {
        arg0->velocity_x *= arg0->bounce;
        arg0->velocity_y = -arg0->velocity_y * arg0->bounce;
        arg0->velocity_z *= arg0->bounce;
        arg0->rotation_x *= arg0->bounce;
        arg0->rotation_y *= arg0->bounce;
        arg0->rotation_z *= arg0->bounce;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A743C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4140/func_151A743C.s")
