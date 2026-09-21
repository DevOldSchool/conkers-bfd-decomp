#include "types.h"

/*
 * Reviewed source unit: src/game/game_130B40.c
 * Boundary evidence: docs/evidence/game_raw_extended_code_selected_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151036B4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15103690(s32 arg0) {
    func_15103828();
}
void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
extern s32 D_800A2350;
extern s32 D_800A2354;
extern f32 D_800A2358;
extern f32 D_800A235C;
extern f32 D_800A2360;
extern f32 D_800A2364;
extern f32 D_800A2368;

typedef struct Game130B40Params {
    s32 field_0;
    s32 field_4;
    s32 field_8[3];
    s16 field_14;
    s16 field_16;
    s16 field_18;
    s16 field_1A;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    s16 field_2C;
    s16 field_2E;
    f32 field_30;
    f32 field_34;
    f32 field_38;
} Game130B40Params;

typedef struct Game130B40Locals {
    s32 field_2C;
    s32 field_30;
    Game130B40Params params;
} Game130B40Locals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151036B4 CURRENT (3513) */
void func_151036B4(void *arg0, u8 arg1, s32 arg2) {
    Game130B40Locals locals;

    locals.field_30 = D_800A2350;
    locals.field_2C = D_800A2354;
    locals.params.field_0 = 8;
    locals.params.field_4 = 4;
    locals.params.field_8[0] = *(s32 *)((u8 *)arg0 + 0);
    locals.params.field_8[1] = *(s32 *)((u8 *)arg0 + 4);
    locals.params.field_8[2] = *(s32 *)((u8 *)arg0 + 8);
    locals.params.field_1C = 8.0f;
    locals.params.field_20 = 4.0f;
    locals.params.field_14 = 0;
    locals.params.field_16 = 0xFF;
    locals.params.field_18 = -0x40;
    locals.params.field_1A = 0x5D;
    locals.params.field_2C = 0x14;
    locals.params.field_2E = 0xA;
    locals.params.field_24 = D_800A2358;
    locals.params.field_28 = D_800A235C;
    locals.params.field_30 = D_800A2360;
    locals.params.field_34 = D_800A2364;
    locals.params.field_38 = D_800A2368;
    func_15152190(&locals.params, &locals.field_30, &locals.field_2C,
                  1, 0.0f, 1, (s32)arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151036B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_130B40/func_151036B4.s")
s32 func_151037DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}
