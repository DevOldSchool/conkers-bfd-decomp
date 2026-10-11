#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D2B10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A5660
 * - func_151A5D2C
 * - func_151A5D58
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5660.s")
/* Call context: func_1514933C: unique active project prototype */

extern void func_151A5D2C(s32 arg0, void *arg1);

void func_151A5CAC(void *arg0) {
    u8 *state;

    state = (u8 *)arg0 + 0x58;
    if (*(u16 *)((u8 *)arg0 + 0x6C) != 0) {
        func_151A5D2C(*(u16 *)(state + 0x14), arg0);
    }
    func_1514933C(arg0);
}

void func_151A5CEC(void *arg0) {
    u8 *state;

    state = (u8 *)arg0 + 0x58;
    if (*(u16 *)((u8 *)arg0 + 0x6C) != 0) {
        func_151A5D2C(*(u16 *)(state + 0x14), arg0);
    }
    func_15149368(arg0);
}
/* Call context: func_100111C8: unique active project prototype */
void func_100111C8(s32, u16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A5D2C CURRENT (419) */
void func_151A5D2C(s32 arg0, u16 arg1) {
    func_100111C8(arg0 & 0xFFFF, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A5D2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5D2C.s")
typedef struct Game1D2B10Effect {
    s32 flags;
    s16 duration;
    u8 kind;
    u8 field7;
    s32 field8;
    s32 step;
    u8 field10, field11, field12, field13;
    u8 field14, field15, field16, field17;
    s32 field18;
    u8 pad1C[4];
    u8 field20;
    u8 pad21;
    s16 field22;
    s16 field24;
    u8 pad26[2];
} Game1D2B10Effect;

s32 func_150ADA20(void);
void *func_1513C650(s32, u8, u8, s32, f32, f32, f32, f32, f32, u8, u8, s32, s32, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A5D58 CURRENT (994) */
void *func_151A5D58(f32 arg0, s32 arg1, s32 arg2, f32 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    Game1D2B10Effect effect;
    s32 sp4C;
    s32 sp48;
    s32 temp_t0;
    s32 var_v0;
    s32 var_v1;

    if (((s16 *)&arg4)[1] <= 0) {
        return 0;
    }
    effect.field22 = 0x14;
    effect.field24 = 0xC;
    effect.kind = 0x38;
    effect.field7 = 0;
    if (((s16 *)&arg4)[1] == -1) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    var_v0 = 0;
    if (((u8 *)&arg5)[3] != 0) {
        var_v0 = 0x400;
    }
    effect.flags = var_v0 | var_v1 | 0x1300 | 0x2000 | 0x8000 | 0x20000;
    if (((s16 *)&arg4)[1] == -1) {
        effect.duration = 0x12C;
    } else {
        effect.duration = ((s16 *)&arg4)[1] + 0x14;
    }
    effect.field8 = 0;
    if (((s16 *)&arg4)[1] == -1) {
        effect.step = 0;
    } else {
        effect.step = 0x140000 / (s32) (((s16 *)&arg4)[1] + 0x14);
    }
    effect.field11 = 0xFF;
    effect.field12 = 0xFF;
    effect.field13 = 0x83;
    effect.field14 = 0x1E;
    effect.field15 = 0xFF;
    effect.field10 = ((u8 *)&arg1)[3];
    if (((u8 *)&arg6)[3] != 0) {
        var_v0 = 2;
    } else {
        var_v0 = 3;
    }
    effect.field18 = var_v0 + 0x440000;
    effect.field16 = 0;
    effect.field17 = 6;
    effect.field20 = 0xFF;
    sp48 = func_150ADA20();
    sp4C = func_150ADA20();
    temp_t0 = func_150ADA20();
    if (((u8 *)&arg5)[3] != 0) {
        var_v1 = 3;
    } else {
        var_v1 = 0;
    }
    if (((u8 *)&arg5)[3] != 0) {
        var_v0 = 0xFF;
    } else {
        var_v0 = 0;
    }
    return func_1513C650((s32) &effect, 0U, 0U, arg2, arg3[0], arg3[1], arg3[2], arg0, arg0, (u8) (sp48 & 0xFF), (u8) (((temp_t0 & 1) * 2) + (sp4C & 1)), var_v1, var_v0, 0, (u8) (s32) ((u8 *)&arg7)[3], arg8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A5D58 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5D58.s")
