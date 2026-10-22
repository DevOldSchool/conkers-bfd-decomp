#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D2480.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_composite_emitter_timed_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A5170
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1D2480Effect {
    u8 pad_0[0x10];
    s32 field_10;
    s8 field_14;
    s8 field_15;
    s8 field_16;
    s8 field_17;
    s8 field_18;
    u8 field_19;
    s8 field_1A;
} Game1D2480Effect;

Game1D2480Effect *func_151A4FD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                                s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    Game1D2480Effect *effect;

    effect = func_15167A68(0x5A, 0, arg7 + 0x20, 0, 0xFF, 1);
    if (effect == 0) {
        return 0;
    }
    effect->field_14 = (s8)arg0;
    effect->field_10 = arg1;
    effect->field_15 = (s8)arg2;
    effect->field_16 = (s8)arg3;
    effect->field_17 = arg4;
    effect->field_19 = arg6;
    effect->field_18 = 0;
    effect->field_1A = (s8)arg5;
    return effect;
}
void func_10011FA0(s32, void *);
extern s32 D_800BE9E4;

void func_151A5070(u8 *arg0) {
    s32 temp_v0;
    s32 temp_t8;
    s32 var_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x10);
    if (temp_v0 != 0) {
        temp_v0 -= D_800BE9E4;
        if (temp_v0 <= 0) {
            func_1516972C(arg0);
            return;
        }
        *(s32 *)((u8 *)arg0 + 0x10) = temp_v0;
    }
    if (*(u8 *)((u8 *)arg0 + 0x19) == 0) {
        func_10011FA0(2, arg0);
    }
    var_v0 = *(u8 *)((u8 *)arg0 + 0x15);
    temp_t8 = D_800BE9E4 << 1;
    if (*(u8 *)((u8 *)arg0 + 0x18) == 0) {
        var_v0 -= temp_t8;
        if (var_v0 < 0x90) {
            var_v0 = 0x90;
            *(u8 *)((u8 *)arg0 + 0x18) = 1;
        }
    } else {
        var_v0 += temp_t8;
        if (var_v0 >= 0x100) {
            var_v0 = 0xFF;
            *(u8 *)((u8 *)arg0 + 0x18) = 0;
        }
    }
    *(u8 *)((u8 *)arg0 + 0x15) = (u8)var_v0;
}
typedef void (*Func151A5130Callback)(s32 arg0, void *arg1, s16 arg2, s32 arg3);
extern Func151A5130Callback D_8008F900[];

void func_151A5130(s32 arg0, void *arg1, s16 arg2, s32 arg3) {
    D_8008F900[((u8 *) arg1)[0x14]](arg0, arg1, arg2, arg3);
}
#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))

typedef struct Game1D2480Command {
    u32 w0;
    u32 w1;
} Game1D2480Command;

typedef struct Game1D2480View {
    u8 pad0[4];
    f32 width;
    f32 height;
    u8 padC[0x18];
    f32 top;
    u8 pad28[4];
    f32 left;
    u8 pad30[0x150];
} Game1D2480View;

Game1D2480Command *func_1501A490(Game1D2480Command *, s16, s32, s32, s32, s32);
Game1D2480Command *func_15142FBC(Game1D2480Command *, s32, s32, u8 *);
extern s32 D_8002AAE8[];
extern s32 D_800BE620;
extern Game1D2480View *D_800BE628;
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A5170 CURRENT (1845) */
void func_151A5170(Game1D2480Command *arg0, Game1D2480Effect *arg1, s32 arg2) {
    s32 y;
    s32 pass;
    s32 left;
    s32 columns;
    s32 rows;
    s32 width;
    s32 height;
    u8 sync;
    s32 next;
    f32 end;

    { Game1D2480Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
    { Game1D2480Command *command = arg0++; command->w0 = 0xFC119623; command->w1 = 0xFF2FFFFF; }
    { Game1D2480Command *command = arg0++; command->w0 = _SHIFTL(0xFA, 24, 8) | _SHIFTL(1, 8, 8) | _SHIFTL(0, 0, 8); command->w1 = _SHIFTL((u8)arg1->field_15, 24, 8) | _SHIFTL((u8)arg1->field_16, 16, 8) | _SHIFTL((u8)arg1->field_17, 8, 8) | _SHIFTL(0xFF, 0, 8); }
    func_1501A490(arg0, arg2, 0, 0, 0, 3);
    sync = 0;
    arg0 = func_15142FBC(arg0, 0xC00, 0x0F0A4004, &sync);
    width = D_800BE628[(u8)arg1->field_1A].width;
    height = D_800BE628[(u8)arg1->field_1A].height;
    for (pass = 0; pass < 2; pass++) {
        if (pass == 0) {
            left = D_800BE628[(u8)arg1->field_1A].left;
            rows = 8;
            end = D_800BE628[(u8)arg1->field_1A].top + height;
            y = D_800BE628[(u8)arg1->field_1A].top;
            columns = (width > 256) ? 256 : width;
        } else {
            if (width <= 256) {
                break;
            }
            columns = width - 256;
            rows = 0x36;
            left = D_800BE628[(u8)arg1->field_1A].left + 256.0f;
            end = D_800BE628[(u8)arg1->field_1A].top + height;
            y = D_800BE628[(u8)arg1->field_1A].top;
        }
        while (y < end) {
            next = y + rows;
            if (end < next) {
                rows = end - y;
                next = y + rows;
            }
            { Game1D2480Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
            { Game1D2480Command *command = arg0++; command->w0 = _SHIFTL(0xFD, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(D_800BE620 - 1, 0, 12); command->w1 = D_8002AAE8[D_800BE9C0]; }
            { Game1D2480Command *command = arg0++; command->w0 = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(((columns * 2) + 7) >> 3, 9, 9) | _SHIFTL(0, 0, 9); command->w1 = _SHIFTL(7, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(2, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(2, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); }
            { Game1D2480Command *command = arg0++; command->w0 = _SHIFTL(0xF4, 24, 8) | _SHIFTL(left << 2, 12, 12) | _SHIFTL(y << 2, 0, 12); command->w1 = _SHIFTL(7, 24, 3) | _SHIFTL((left + columns - 1) << 2, 12, 12) | _SHIFTL((next - 1) << 2, 0, 12); }
            { Game1D2480Command *command = arg0++; command->w0 = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(((columns * 2) + 7) >> 3, 9, 9) | _SHIFTL(0, 0, 9); command->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(2, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(2, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); }
            { Game1D2480Command *command = arg0++; command->w0 = _SHIFTL(0xF2, 24, 8) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); command->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(columns << 2, 12, 12) | _SHIFTL(rows << 2, 0, 12); }
            { Game1D2480Command *command = arg0++; command->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL((left + columns) << 2, 12, 12) | _SHIFTL(next << 2, 0, 12); command->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(left << 2, 12, 12) | _SHIFTL(y << 2, 0, 12); }
            { Game1D2480Command *command = arg0++; command->w0 = _SHIFTL(0xE1, 24, 8); command->w1 = _SHIFTL(0, 16, 16) | _SHIFTL(0, 0, 16); }
            { Game1D2480Command *command = arg0++; command->w0 = _SHIFTL(0xF1, 24, 8); command->w1 = _SHIFTL(1 << 10, 16, 16) | _SHIFTL(1 << 10, 0, 16); }
            y = next;
            end = D_800BE628[(u8)arg1->field_1A].top + height;
        }
    }
    { Game1D2480Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
    func_15142FBC(arg0, 0x2C00, 0x0F0A4004, &sync);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A5170 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2480/func_151A5170.s")
extern void (*D_8008F904[])(void *, s32, u8);

void func_151A55D4(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008F904[*(u8 *)((u8 *)arg0 + 0x19)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
extern void func_15169260(s32 *arg0, s32 arg1, s32 arg2, u8 arg3);
typedef struct {
    s32 value;
} Game1D2480DispatchDescriptor;
extern Game1D2480DispatchDescriptor D_800A8D70;

void func_151A561C(s32 arg0, u8 arg1) {
    Game1D2480DispatchDescriptor sp1C;

    sp1C = D_800A8D70;
    func_15169260(&sp1C.value, 1, arg0, arg1);
}
