#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D2480.c
 * Boundary evidence: docs/evidence/game_raw_composite_emitter_timed_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A4FD0
 * - func_151A5070
 * - func_151A5170
 * - func_151A561C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad_0[0x10];
    s32 field_10;
    s8 field_14;
    s8 field_15;
    s8 field_16;
    s8 field_17;
    volatile s8 field_18;
    u8 field_19;
    s8 field_1A;
} Game1D2480Effect;

void *func_15167A68(s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4FD0 CURRENT (320) */
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
    effect->field_17 = (s8)arg4;
    effect->field_18 = 0;
    effect->field_19 = arg6;
    effect->field_1A = (s8)arg5;
    return effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4FD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2480/func_151A4FD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2480/func_151A5070.s")
typedef void (*Func151A5130Callback)(s32 arg0, void *arg1, s16 arg2, s32 arg3);
extern Func151A5130Callback D_8008F900[];

void func_151A5130(s32 arg0, void *arg1, s16 arg2, s32 arg3) {
    D_8008F900[((u8 *) arg1)[0x14]](arg0, arg1, arg2, arg3);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2480/func_151A5170.s")
extern void (*D_8008F904[])(void *, s32, u8);

void func_151A55D4(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008F904[*(u8 *)((u8 *)arg0 + 0x19)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
extern void func_15169260(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_800A8D70;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A561C CURRENT (720) */
void func_151A561C(s32 arg0, s32 arg1) {
    s32 sp1C;
    s32 temp_a3;

    temp_a3 = arg1 & 0xFF;
    sp1C = D_800A8D70;
    func_15169260(&sp1C, 1, arg0, temp_a3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A561C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2480/func_151A561C.s")
