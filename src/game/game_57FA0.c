#include "types.h"

/*
 * Reviewed source unit: src/game/game_57FA0.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1502AB04
 * - func_1502AC88
 * - func_1502AF04
 * - func_1502B020
 * - func_1502B110
 * - func_1502B224
 * - func_1502B350
 * - func_1502B4A8
 * - func_1502B5C8
 * - func_1502B6BC
 * - func_1502B7F0
 * - func_1502B8E0
 * - func_1502B9B4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1502AAF0(void) {

}
void func_1502AAF8(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502AB04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502AC88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502AF04.s")
s32 func_1502AC88(u8 *, s32, s32 *);
extern u8 D_AB1950[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B020 CURRENT (1836) */
u8 *func_1502B020(s32 *arg0, volatile s32 arg1, s32 arg2, s32 arg3) {
    volatile s32 state;
    u8 *cursor;
    s32 count;
    u8 *output;

    state = 1;
    output = D_AB1950;
    cursor = (u8 *)&arg2;
    if (arg1 != 0) {
        do {
            cursor = (u8 *)(((s32)(cursor + 3) & ~3) + 4);
            if (state != 0) {
                output += func_1502AC88(output, *(s32 *)(cursor - 4), (s32 *)&state);
            }
            count = arg1 - 1;
            arg1 = count;
            state &= 0x0FFFFFFF;
        } while (count != 0);
    }
    if (arg0 != 0) {
        *arg0 = state & 0x0FFFFFFF;
    }
    if (state == 0) {
        return 0;
    }
    return output;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B020 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B020.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B110.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B224.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B350.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B4A8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B5C8 CURRENT (696) */
s32 func_1502B5C8(s32 *arg0, volatile s32 arg1, s32 arg2, s32 arg3) {
    volatile struct {
        s32 component_state;
        u8 pad04[4];
        s32 state;
        u8 pad0C[8];
    } locals;
    u8 *var_s1;
    volatile s32 *var_s2;
    s32 temp_t3;
    s32 var_v1;
    u8 *var_s0;

    var_s2 = &locals.state;
    if (arg0 != 0) {
        var_s2 = arg0;
    }
    *var_s2 = 1;
    var_s0 = D_AB1950;
    var_s1 = (u8 *)&arg2;
    if (arg1 != 0) {
        do {
            var_s1 = (u8 *)(((s32)(var_s1 + 3) & ~3) + 4);
            if (*var_s2 != 0) {
                var_s0 += func_1502AC88(var_s0, *(s32 *)(var_s1 - 4),
                                        (s32 *)&locals.component_state);
            }
            *var_s2 = locals.component_state & 0x0FFFFFFF;
            temp_t3 = arg1 - 1;
            arg1 = temp_t3;
        } while (temp_t3 != 0);
    }
    if (*var_s2 != 0) {
        var_v1 = func_1502B350(var_s0, locals.component_state, (s32 *)var_s2);
    } else {
        var_v1 = 0;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B5C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B5C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B6BC.s")
s32 func_1502B350(u8 *, s32, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B7F0 CURRENT (1980) */
s32 func_1502B7F0(s32 *arg0, volatile s32 arg1, s32 arg2, s32 arg3) {
    volatile struct {
        s32 component_state;
        s32 state;
    } locals;
    u8 *cursor;
    s32 count;
    u8 *output;

    locals.state = 1;
    output = D_AB1950;
    cursor = (u8 *)&arg2;
    if (arg1 != 0) {
        do {
            cursor = (u8 *)(((s32)(cursor + 3) & ~3) + 4);
            if (locals.state != 0) {
                output += func_1502AC88(output, *(s32 *)(cursor - 4), (s32 *)&locals.component_state);
            }
            count = arg1 - 1;
            arg1 = count;
            locals.state = locals.component_state & 0x0FFFFFFF;
        } while (count != 0);
    }
    if (locals.state != 0) {
        *arg0 = func_1502B350(output, locals.component_state, (s32 *)&locals.state);
    } else {
        *arg0 = 0;
    }
    return locals.state;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B7F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B7F0.s")
s32 func_1502AC88(u8 *, s32, s32 *);
s32 func_1502B224(u8 *, s32, s32, s32);
extern u8 D_AB1950[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B8E0 CURRENT (1202) */
s32 func_1502B8E0(s32 arg0, s32 arg1, volatile s32 arg2, s32 arg3) {
    s32 state;
    u8 *cursor;
    u8 *output;
    s32 result;

    result = 1;
    output = D_AB1950;
    cursor = (u8 *)&arg3;
    if (arg2 != 0) {
        do {
            cursor = (u8 *)(((s32)(cursor + 3) & ~3) + 4);
            if (result != 0) {
                output += func_1502AC88(output, *(s32 *)(cursor - 4), &state);
            }
            arg2--;
            result = state & 0x0FFFFFFF;
        } while (arg2 != 0);
    }
    if (result != 0) {
        result = func_1502B224(output, arg0, state, arg1);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B8E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B8E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B9B4.s")
