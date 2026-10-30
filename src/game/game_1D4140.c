#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D4140.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A6C90
 * - func_151A6F00
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1D4140Smoke {
    s16 count;
    u8 pad2[2];
    Vec3f position;
    s16 field10;
    u8 pad12[2];
    f32 field14;
    s16 field18, field1A, field1C, field1E;
    f32 field20, field24, field28, field2C;
    f32 field30, field34, field38, field3C;
    f32 field40, field44, field48, field4C, field50;
    s8 field54, field55;
    s16 field56, field58;
    u8 pad5A[2];
} Game1D4140Smoke;

void func_151A6F00(s16 *, s32, u8, s32);
f32 func_150ADA68(void);
void func_151D5514(f32 *, u8, s32);
void func_151541B8(f32 *, f32, f32, f32, f32, u8, s32);
void func_151D5334(f32 *, f32, f32, f32, s32, s32, s32);
extern f32 D_800A8DB0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A6C90 CURRENT (200) */
void func_151A6C90(void *arg0, u8 arg1, s32 arg2) {
    Vec3f position;
    Game1D4140Smoke smoke;

    position.x = ((Vec3f *)((u8 *)arg0 + 0x14))->x;
    position.y = ((Vec3f *)((u8 *)arg0 + 0x14))->y;
    position.z = ((Vec3f *)((u8 *)arg0 + 0x14))->z;
    if (arg0 != NULL) {
        smoke.count = (func_150ADA20() & 3) + 6;
        smoke.position = position;
        smoke.field14 = 60.0f;
        smoke.field20 = 0.0f;
        smoke.field24 = 35.0f;
        smoke.field10 = 0x50;
        smoke.field18 = 0;
        smoke.field1A = 0xFF;
        smoke.field1C = -0x3F;
        smoke.field1E = 0x50;
        smoke.field54 = 0;
        smoke.field55 = 0;
        smoke.field56 = 0x32;
        smoke.field58 = 0x19;
        smoke.field44 = -1.0f;
        smoke.field48 = -1.0f;
        smoke.field30 = 0;
        smoke.field34 = 0;
        smoke.field38 = 0;
        smoke.field28 = 10.0f;
        smoke.field2C = 40.0f;
        smoke.field3C = D_800A8DB0;
        smoke.field40 = 0.5f;
        smoke.field4C = -2.0f;
        smoke.field50 = 4.0f;
        func_151A6F00(&smoke.count, 0, arg1, arg2);
        func_151D5334(&position.x, 506.0f, 1013.0f, 0.000987166888f, 5, arg1, arg2);
        func_151D3FF4(&position.x, arg1, arg2);
        func_151D5514(&position.x, arg1, arg2);
        func_151541B8(&position.x, func_150ADA68() * 4.0f + 12.0f, 1.6409999f, func_150ADA20() % 56U + 0xC8, 0.0f, arg1, arg2);
        func_151D5404(&position, 1502.0f, 3000.0f, 0.00033333333f, 0xC, 0xF, 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A6C90 */
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
void func_1514AB5C(f32, f32, f32, f32, s32, f32, f32, f32, f32, s32, s32, s32);

s32 func_151A743C(Game1D4140State *arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    Game1D4140Entry *state;
    u8 alternate;

    state = &arg0->field_170;
    arg0->height = arg0->base_height + arg4;
    if (arg0->field_170.field_4 != 0) {
        func_1516972C(state->field_4);
        state->field_4 = 0;
    }
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
