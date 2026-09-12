#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BF090.c
 * Boundary evidence: docs/evidence/game_raw_composite_emitter_timed_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15191BE0
 * - func_15191D54
 * - func_1519203C
 * - func_15192358
 * - func_151925C4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1BF090/func_15191BE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BF090/func_15191D54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BF090/func_1519203C.s")
typedef struct {
    u8 pad_0[0x38];
    s32 field_38;
    s32 field_3C;
    u8 pad_40[0x68];
    s32 field_A8;
    s16 field_AC;
    s16 field_AE;
    s32 field_B0;
} Game1BF090State;

void func_15131C84(s16 *, s16 *, s32, s32 *, s32 *, s32 *);

s32 func_15192308(s32 arg0, s32 arg1) {
    Game1BF090State *state;

    state = (Game1BF090State *)arg0;
    func_15131C84(&state->field_AC, &state->field_AE, state->field_A8, &state->field_B0,
                  &state->field_38, &state->field_3C);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BF090/func_15192358.s")
s32 func_15192308(s32, s32);                        /* extern */
s32 func_15192358(s32, s32);                        /* extern */

s32 func_1519257C(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = func_15192308(arg0, arg1);
    var_v1 = temp_v0 & 0xFF;
    if (temp_v0 != 0) {
        var_v1 = func_15192358(arg0, arg1) & 0xFF;
    }
    return var_v1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BF090/func_151925C4.s")
void func_1519277C(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
