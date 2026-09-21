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
void func_10004514(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502AF04 CURRENT (921) */
s32 func_1502AF04(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    register u8 *temp_s2;
    u8 *temp_t0;
    u8 **entry;

    temp_t0 = arg0 + (arg2 * 8);
    temp_s2 = (u8 *)((arg1 + 8) & ~0xF);
    func_10004514((s32)temp_t0 & ~0xF, (s32)temp_s2,
                  (((s32)temp_t0 & 0xE) + (arg3 * 8) + 0xF) & ~0xF, 1);
    i = 0;
    if (arg3 != 0) {
        do {
            entry = (u8 **)(temp_s2 + ((s32)temp_t0 & 0xF) + (i * 8));
            *entry = arg0 + (s32)*entry;
            i++;
        } while (i != arg3);
    }
    return (s32)(temp_s2 + ((s32)temp_t0 & 0xF));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502AF04 */
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
s32 func_1502AF04(u8 *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B110 CURRENT (2420) */
s32 func_1502B110(u8 *arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4) {
    s32 sp3C;
    s32 sp38;
    u8 *var_s0;
    u32 temp_a3;
    u8 *var_s2;

    var_s2 = arg0;
    sp3C = 1;
    sp38 = 0;
    if (var_s2 == 0) {
        var_s2 = D_AB1950;
    }
    var_s0 = (u8 *)&arg4;
    if (arg3 >= 2U) {
        do {
            var_s0 = (u8 *)(((s32)(var_s0 + 3) & ~3) + 4);
            if (sp3C != 0) {
                var_s2 += func_1502AC88(var_s2, *(s32 *)(var_s0 - 4),
                                        &sp3C);
            }
            temp_a3 = arg3 - 1;
            arg3 = temp_a3;
            sp3C &= 0x0FFFFFFF;
        } while (temp_a3 >= 2U);
    }
    var_s0 = (u8 *)(((s32)(var_s0 + 3) & ~3) + 4);
    if (sp3C != 0) {
        sp38 = func_1502AF04(var_s2, arg2, *(s32 *)(var_s0 - 4), arg1);
    }
    return sp38;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B110 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B110.s")
void func_10004074(s32);
s32 func_10006240(s32, s32, s32);
void func_150AD770(void);
s32 func_10003C40(s32, s32, s32, s32);
extern s32 D_8003809C;
extern s32 D_8003C8E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B224 CURRENT (68) */
s32 func_1502B224(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 original;
    s32 buffer;
    u32 size;

    size = ((arg2 & 0x0FFFFFFF) + 1) & ~1;
    if ((arg3 != 0) && ((u32)arg3 < size)) {
        size = arg3;
    }
    if ((arg2 & 0x70000000) == 0x10000000) {
        buffer = func_10003C40(size, 1, 2, 2);
        if (buffer == 0) {
            return 0;
        }
        func_10004514((s32)arg0, buffer, (size + 0xF) & ~0xF, 1);
        original = *(s32 *)buffer & 0x7FFFFFFF;
        size = func_10006240(buffer, arg1, D_8003809C);
        if (original != size) {
            D_8003C8E0 = 0x0C000036;
            func_150AD770();
        }
        func_10004074(buffer);
    } else {
        func_10004514((s32)arg0, arg1, (size + 0xF) & ~0xF, 1);
    }
    return size;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B224 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B224.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B350.s")
typedef struct {
    s32 offset;
    u32 flags;
} Game57FA0Reloc;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B4A8 CURRENT (3440) */
s32 func_1502B4A8(Game57FA0Reloc *arg0, s32 arg1) {
    u32 temp_flags;
    s32 var_v0;
    Game57FA0Reloc *entry;
    Game57FA0Reloc *end;

    if (arg1 == 0) {
        entry = &arg0[arg1];
        entry++;
        arg1++;
        if (!(entry[-1].flags & 0x80000000)) {
            do {
                temp_flags = entry->flags;
                arg1++;
                entry++;
            } while (!(temp_flags & 0x80000000));
        }
    }
    var_v0 = 0;
    if (arg1 > 0) {
        if (arg1 & 1) {
            arg0[0].flags &= 0x0FFFFFFF;
            if ((arg0[0].offset == -1) || (arg0[0].flags == 0)) {
                arg0[0].offset = 0;
            } else {
                arg0[0].offset += (s32)arg0;
            }
            var_v0 = 1;
            if (arg1 == 1) {
                return arg1;
            }
        }
        entry = &arg0[var_v0];
        end = &arg0[arg1];
        do {
            entry[0].flags &= 0x0FFFFFFF;
            if ((entry[0].offset == -1) || (entry[0].flags == 0)) {
                entry[0].offset = 0;
            } else {
                entry[0].offset += (s32)arg0;
            }
            entry[1].flags &= 0x0FFFFFFF;
            if ((entry[1].offset == -1) || (entry[1].flags == 0)) {
                entry[1].offset = 0;
            } else {
                entry[1].offset += (s32)arg0;
            }
            entry += 2;
        } while (entry != end);
    }
    return arg1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B4A8 */
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
s32 func_1502B350(u8 *, s32, s32 *);
s32 func_1502B4A8(Game57FA0Reloc *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B6BC CURRENT (919) */
s32 func_1502B6BC(s32 *arg0, volatile s32 arg1, s32 *arg2,
                   volatile s32 arg3, s32 arg4) {
    volatile struct {
        s32 component_state;
        u8 pad3C[8];
        s32 state;
    } locals;
    u8 *cursor;
    volatile s32 *state;
    s32 count;
    s32 result;
    u8 *output;

    state = &locals.state;
    if (arg0 != 0) {
        state = arg0;
    }
    *state = 1;
    output = D_AB1950;
    cursor = (u8 *)&arg4;
    if (arg3 != 0) {
        do {
            cursor = (u8 *)(((s32)(cursor + 3) & ~3) + 4);
            if (*state != 0) {
                output += func_1502AC88(output, *(s32 *)(cursor - 4),
                                        (s32 *)&locals.component_state);
            }
            *state = locals.component_state & 0x0FFFFFFF;
            count = arg3 - 1;
            arg3 = count;
        } while (count != 0);
    }
    if (*state != 0) {
        result = func_1502B350(output, locals.component_state, (s32 *)state);
        if ((*state != 0) && (result != 0)) {
            arg1 = func_1502B4A8((Game57FA0Reloc *)result, arg1);
        } else {
            arg1 = 0;
        }
        if (arg2 != 0) {
            *arg2 = arg1;
        }
    } else {
        result = 0;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B6BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B6BC.s")

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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B9B4 CURRENT (1443) */
s32 func_1502B9B4(volatile s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp54;
    s32 sp40;
    s32 sp38;
    register u8 *var_s0;
    s32 *var_s0_2;
    s32 temp_a0;
    s32 var_v1;
    register u8 *var_s1;

    var_v1 = 1;
    var_s1 = D_AB1950;
    var_s0 = (u8 *)&arg1;
    if (arg0 != 0) {
        do {
            var_s0 = (u8 *)(((s32)(var_s0 + 3) & ~3) + 4);
            if (var_v1 != 0) {
                var_s1 += func_1502AC88(var_s1, *(s32 *)(var_s0 - 4), &sp54);
            }
            temp_a0 = arg0 - 1;
            arg0 = temp_a0;
            var_v1 = sp54 & 0x0FFFFFFF;
        } while (temp_a0 != 0);
    }
    if (var_v1 != 0) {
        var_v1 = ((sp54 & 0x0FFFFFFF) + 1) & ~1;
        if ((sp54 & 0x70000000) == 0x10000000) {
            var_s0_2 = &sp38;
            if ((s32)var_s0_2 & 8) {
                var_s0_2 = &sp40;
            }
            func_10004514((s32)var_s1, (s32)var_s0_2, 0x10, 1);
            var_v1 = *var_s0_2;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B9B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B9B4.s")
