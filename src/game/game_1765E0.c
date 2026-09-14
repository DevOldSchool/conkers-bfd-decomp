#include "types.h"

/*
 * Reviewed source unit: src/game/game_1765E0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15149130
 * - func_151491F4
 * - func_15149264
 * - func_151494E0
 * - func_15149514
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_15149130.s")
void *func_15149130(s16, s8, s8, s8, u8, u8, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151491F4 CURRENT (100) */
void func_151491F4(s16 arg0, s8 arg1, s8 arg2, u8 arg3, u8 arg4,
                   s32 arg5, u8 arg6, s32 arg7) {
    func_15149130(arg0, arg1, arg2, -1, arg3, arg4, arg5, arg6, arg7);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151491F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_151491F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_15149264.s")
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
void func_15169260(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_800A5770;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151494E0 CURRENT (400) */
void func_151494E0(s32 arg0, s32 arg1) {
    func_15169260(&D_800A5770, 2, arg0, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151494E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_151494E0.s")
void func_15169850(s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15149514 CURRENT (173) */
void func_15149514(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg1 = arg1 & 0xFF;
    func_15169850(arg0, arg1, arg2, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15149514 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_15149514.s")
