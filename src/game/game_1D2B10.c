#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D2B10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A5660
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5660.s")
/* Call context: func_1514933C: unique active project prototype */

extern void func_151A5D2C(u16 arg0, void *arg1);

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
void func_100111C8(u16, void *);

void func_151A5D2C(u16 arg0, void *arg1) {
    func_100111C8(arg0, arg1);
}
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

void *func_1513C650(s32, u8, u8, s32, f32, f32, f32, f32, f32, u8, u8, s32, s32, s32, u8, s32);

void *func_151A5D58(f32 arg0, u8 arg1, s32 arg2, f32 *arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, s32 arg8) {
    s32 visible;
    Game1D2B10Effect effect;

    if (arg4 <= 0) {
        return 0;
    }
    effect.field22 = 0x14;
    effect.field24 = 0xC;
    effect.kind = 0x38;
    effect.field7 = 0;
    visible = (arg4 == -1) ? 0 : 1;
    effect.flags = (arg5 ? 0x400 : 0) | visible | 0x1000 | 0x200 | 0x100 | 0x2000 | 0x8000 | 0x20000;
    effect.duration = (arg4 == -1) ? 0x12C : arg4 + 0x14;
    effect.field8 = 0;
    effect.step = (arg4 == -1) ? 0 : 0x140000 / (arg4 + 0x14);
    effect.field10 = arg1;
    effect.field11 = 0xFF;
    effect.field12 = 0xFF;
    effect.field13 = 0x83;
    effect.field14 = 0x1E;
    effect.field15 = 0xFF;
    effect.field18 = (arg6 ? 2 : 3) + 0x440000;
    effect.field16 = 0;
    effect.field17 = 6;
    effect.field20 = 0xFF;
    return func_1513C650((s32)&effect, 0, 0, arg2, arg3[0], arg3[1], arg3[2], arg0, arg0, func_150ADA20() & 0xFF,
                         (func_150ADA20() & 1) + (func_150ADA20() & 1) * 2, arg5 ? 3 : 0, arg5 ? 0xFF : 0, 0, arg7, arg8);
}
