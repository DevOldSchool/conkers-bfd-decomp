#include "types.h"

/*
 * Reviewed source unit: src/game/game_1765E0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 */

typedef struct Game1765E0EffectHeader {
    u8 pad_0[0xD];
    u8 flags;
    s16 timer;
    s8 callback_expired;
    s8 callback_tick;
    s8 callback_other;
    u8 field_13;
    u8 data[0x10];
} Game1765E0EffectHeader;

Game1765E0EffectHeader *func_15167A68();
void func_100226F0(void *, s32);

Game1765E0EffectHeader *func_15149130(s16 arg0, s8 arg1, s8 arg2, s8 arg3,
                                      u8 arg4, u8 arg5, s32 arg6, u8 arg7,
                                      s32 arg8) {
    volatile struct {
        s32 pad_20;
        s32 sp24;
        s32 pad_28;
        Game1765E0EffectHeader *sp2C;
    } locals;
    Game1765E0EffectHeader *temp_v0;
    u8 var_v0;

    locals.sp24 = arg6 + 0x28;
    var_v0 = (arg4 & 2) ? 0x5F : 0x23;
    temp_v0 = func_15167A68(var_v0, arg8, locals.sp24, 1, arg7, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    temp_v0->timer = arg0;
    temp_v0->callback_expired = arg1;
    temp_v0->callback_tick = arg2;
    temp_v0->callback_other = arg3;
    temp_v0->flags = arg4;
    temp_v0->field_13 = arg5;
    locals.sp2C = temp_v0;
    func_100226F0(temp_v0->data, 0x10);
    return locals.sp2C;
}

void func_151491F4(s16 arg0, s8 arg1, s8 arg2, u8 arg3, u8 arg4,
                   s32 arg5, u8 arg6, s32 arg7) {
    func_15149130(arg0, arg1, arg2, -1, arg3, arg4, arg5, arg6, arg7);
}
typedef struct Game1765E0Effect {
    u8 pad_0[0xD];
    u8 flags;
    s16 timer;
    s8 callback_expired;
    s8 callback_tick;
} Game1765E0Effect;

extern s32 D_800BE9E4;
extern void (*D_8008A4C0[])(Game1765E0Effect *);
extern void (*D_8008A4E8[])(Game1765E0Effect *);
void func_1516972C(Game1765E0Effect *);

void func_15149264(Game1765E0Effect *arg0) {
    s16 var_v0;
    s8 temp_v0;
    s8 temp_v1;

    if (arg0->flags & 1) {
        arg0->timer = arg0->timer - D_800BE9E4;
    }
    temp_v0 = arg0->callback_tick;
    if (temp_v0 != -1) {
        D_8008A4E8[temp_v0](arg0);
    }
    var_v0 = arg0->timer;
    if (var_v0 < 0) {
        temp_v1 = arg0->callback_expired;
        if (temp_v1 != -1) {
            D_8008A4C0[temp_v1](arg0);
            var_v0 = arg0->timer;
        }
    }
    if (var_v0 < 0) {
        func_1516972C(arg0);
    }
}
void func_15149318(s32 arg0) {
    func_151D5E30(arg0 + 0x14, arg0);
}
void func_15169804(s32);

void func_1514933C(s32 arg0) {
    func_15149318(arg0);
    func_15169804(arg0);
}
void func_15149318(s32 arg0);
void func_15169824(s32 arg0);

void func_15149368(s32 arg0) {
    func_15149318(arg0);
    func_15169824(arg0);
}
typedef struct {
    u8 pad_0[0x13];
    u8 field_13;
} Game1765E0State;

extern void (*D_8008A688[])(void);

void func_15149394(Game1765E0State *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field_13;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    } else if (temp_v0 >= 0x4A) {
        temp_v0 = 0;
    }
    D_8008A688[temp_v0]();
}
extern void (*D_8008A7B0[])(void);

void func_151493E4(Game1765E0State *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field_13;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    } else if (temp_v0 >= 0x4A) {
        temp_v0 = 0;
    }
    D_8008A7B0[temp_v0]();
}
extern void (*D_8008A8D8[])(void *, void *, u8);

void func_15149434(void *arg0, void *arg1, u8 arg2) {
    s32 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x13);
    if ((var_v0 < 0) || (var_v0 >= 0x4A)) {
        var_v0 = 0;
    }
    if (D_8008A8D8[var_v0] != 0) {
        D_8008A8D8[var_v0](arg0, arg1, arg2);
    }
}
typedef struct {
    u8 pad_0[0x12];
    s8 field_12;
} Game1765E0DispatchState;

extern s32 (*D_8008A670[])(s32, Game1765E0DispatchState *, s16);

s32 func_15149490(s32 arg0, Game1765E0DispatchState *arg1, s16 arg2) {
    s8 temp_v0;

    temp_v0 = arg1->field_12;
    if (temp_v0 != -1) {
        arg0 = D_8008A670[temp_v0](arg0, arg1, arg2);
    }
    return arg0;
}
void func_15169260(void *, s32, s32, u8);
extern u8 D_800A5770;

void func_151494E0(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5770, 2, arg0, arg1);
}
void func_15169850(s32, u8, s32, s32, s32);

void func_15149514(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_15169850(arg0, arg1, arg2, arg3, arg4);
}
