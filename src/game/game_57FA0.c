#include "types.h"
#include "../lib/ultralib/include/compiler/ido/stdarg.h"

/*
 * Reviewed source unit: src/game/game_57FA0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1502AC88
 * - func_1502B350
 * - func_1502B4A8
 * - func_1502B9B4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1502AAF0(void) {

}
void func_1502AAF8(s32 arg0) {

}
typedef struct Game2AB04Pair {
    s32 value0;
    s32 value1;
} Game2AB04Pair;

typedef struct Game2AB04Entry {
    s32 address;
    s32 kind;
    Game2AB04Pair values;
} Game2AB04Entry;

void func_10023A10(void *, void *, s32);
extern Game2AB04Entry D_800C3D68[];

void func_1502AB04(s32 arg0, s32 *arg1, s32 arg2, s32 arg3) {
    register s32 saved_arg0 = arg0;
    s32 index;

    if (saved_arg0 != 0) {
        func_10023A10(&D_800C3D68[saved_arg0], D_800C3D68,
                       ((-saved_arg0) << 4) + 0x100);
    }
    index = 0x10 - saved_arg0;
    if ((u32)index < 0x10U) {
        do {
            D_800C3D68[index].values = *(Game2AB04Pair *)arg1;
            D_800C3D68[index].kind = arg2;
            D_800C3D68[index].address = arg3;
            arg1 += 2;
            arg3 += 8;
            index++;
        } while (index != 0x10);
    }
}
void func_10004514(s32, s32, s32, s32);
extern s32 D_800C3D60;
extern Game2AB04Entry D_800C3E58;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502AC88 CURRENT (10) */
s32 func_1502AC88(u8 *arg0, s32 arg1, s32 *arg2) {
    union { u64 alignment; u8 bytes[64]; } transfer;
    s32 *values;
    s32 result;
    s32 aligned;
    u32 index;
    u32 shift;
    Game2AB04Entry saved;

    arg0 = (u8 *)(((u32)arg0 + ((u32)arg1 << 3)) | 0x80000000U);
    for (index = 0; index != 16; index++) {
        if ((s32)arg0 == D_800C3D68[index].address) {
            saved = D_800C3D68[index];
            for (shift = index; shift < 15U; shift++) {
                D_800C3D68[shift] = D_800C3D68[shift + 1];
            }
            D_800C3E58 = saved;
            D_800C3D68[15].kind = D_800C3D60;
            *arg2 = D_800C3D68[15].values.value1;
            return D_800C3D68[15].values.value0;
        }
    }
    aligned = (s32)&transfer.bytes[8] & ~15;
    D_800C3D60++;
    func_10004514((s32)arg0 & 0x7FFFFFF0, aligned,
                   (((s32)arg0 & 14) + 31) & ~15, 1);
    values = (s32 *)(aligned + ((u32)arg0 & 15));
    result = values[0];
    *arg2 = values[1];
    func_1502AB04(2, values, D_800C3D60, (s32)arg0);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502AC88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502AC88.s")

void func_10004514(s32, s32, s32, s32);

s32 func_1502AF04(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    typedef struct { u32 address; u32 flags; } Relocation;
    u32 i;
    s32 source;
    s32 aligned;
    Relocation *entries;

    arg2 <<= 3;
    source = (s32)arg0 + arg2;
    aligned = (arg1 + 8) & ~0xF;
    func_10004514(source & ~0xF, aligned, ((source & 0xE) + (arg3 << 3) + 0xF) & ~0xF, 1);
    entries = (Relocation *)(aligned + (source & 0xFU));
    for (i = 0; i < (u32)arg3; i++) {
        entries[i].address += (u32)arg0;
    }
    return aligned + (source & 0xFU);
}
s32 func_1502AC88(u8 *, s32, s32 *);
extern u8 D_AB1950[];

u8 *func_1502B020(s32 *arg0, s32 arg1, ...) {
    va_list cursor;
    s32 component;
    u8 *output;
    s32 state;

    state = 1;
    output = D_AB1950;
    va_start(cursor, arg1);
    for (; arg1 != 0; arg1--) {
        component = va_arg(cursor, s32);
        if (state != 0) {
            output += func_1502AC88(output, component, &state);
        }
        state &= 0x0FFFFFFF;
    }
    va_end(cursor);
    if (arg0 != 0) {
        *arg0 = state & 0x0FFFFFFF;
    }
    if (state == 0) {
        return 0;
    }
    return output;
}

s32 func_1502AF04(u8 *, s32, s32, s32);

s32 func_1502B110(u8 *arg0, s32 arg1, s32 arg2, u32 arg3, ...) {
    va_list cursor;
    s32 argument;
    s32 state;
    s32 result;

    state = 1;
    result = 0;
    if (arg0 == 0) {
        arg0 = D_AB1950;
    }
    va_start(cursor, arg3);
    for (; arg3 > 1; arg3--) {
        argument = va_arg(cursor, s32);
        if (state != 0) {
            arg0 += func_1502AC88(arg0, argument, &state);
        }
        state &= 0x0FFFFFFF;
    }
    argument = va_arg(cursor, s32);
    if (state != 0) {
        result = func_1502AF04(arg0, arg2, argument, arg1);
    }
    va_end(cursor);
    return result;
}
void func_10004074(s32);
s32 func_10006240(s32, s32, s32);
void func_150AD770(void);
s32 func_10003C40(s32, s32, s32, s32);
extern s32 D_8003809C;
extern s32 D_8003C8E0;

s32 func_1502B224(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 compression;
    u32 aligned;
    s32 original;
    s32 buffer;
    u32 size;

    size = ((arg2 & 0x0FFFFFFF) + 1) & ~1;
    if ((arg3 != 0) && ((u32)arg3 < size)) {
        size = arg3;
    }
    compression = arg2 & 0x70000000;
    aligned = (size + 0xF) & ~0xF;
    if (compression == 0x10000000) {
        buffer = func_10003C40(size, 1, 2, 2);
        if (buffer == 0) {
            return 0;
        }
        func_10004514((s32)arg0, buffer, aligned, 1);
        original = *(s32 *)buffer & 0x7FFFFFFF;
        if ((size = func_10006240(buffer, arg1, D_8003809C)) != original) {
            D_8003C8E0 = 0x0C000036;
            func_150AD770();
        }
        func_10004074(buffer);
    } else {
        func_10004514((s32)arg0, arg1, aligned, 1);
    }
    return size;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B350 CURRENT (330) */
s32 func_1502B350(u8 *arg0, s32 arg1, s32 *arg2) {
    u32 size;
    s32 input;
    s32 result;

    size = ((arg1 & 0x0FFFFFFF) + 1) & ~1;
    input = func_10003C40(size, 1, 2, 2);
    result = input;
    if (input == 0) {
        return 0;
    }
    func_10004514((s32)arg0, input, (size + 0xF) & ~0xF, 1);
    if ((arg1 & 0x70000000) == 0x10000000) {
        *arg2 = *(s32 *)input & 0x7FFFFFFF;
        if (*arg2 != 0) {
            result = 0;
            if ((u32)*arg2 < 0xF4240U) {
                result = func_10003C40(*arg2, 1, 2, 2);
                if (result != 0) {
                    size = func_10006240(input, result, D_8003809C);
                } else {
                    size = 0;
                }
            } else {
                size = 0;
            }
        } else {
            result = 0;
            size = 0;
        }
        func_10004074(input);
    }
    *arg2 = size;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B350 */
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
                arg0[0].offset = (s32)((u32)arg0[0].offset + (u32)arg0);
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
                entry[0].offset = (s32)((u32)entry[0].offset + (u32)arg0);
            }
            entry[1].flags &= 0x0FFFFFFF;
            if ((entry[1].offset == -1) || (entry[1].flags == 0)) {
                entry[1].offset = 0;
            } else {
                entry[1].offset = (s32)((u32)entry[1].offset + (u32)arg0);
            }
            entry += 2;
        } while (entry != end);
    }
    return arg1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B4A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B4A8.s")
s32 func_1502B350(u8 *, s32, s32 *);

s32 func_1502B5C8(s32 *arg0, s32 arg1, ...) {
    u8 *output;
    va_list cursor;
    s32 *state;
    s32 status;
    s32 argument;
    s32 component;
    s32 result;

    state = &status;
    if (arg0 != 0) {
        state = arg0;
    }
    *state = 1;
    output = D_AB1950;
    va_start(cursor, arg1);
    if (arg1 != 0) {
        do {
            argument = va_arg(cursor, s32);
            if (*state != 0) {
                output += func_1502AC88(output, argument, &component);
            }
            *state = component & 0x0FFFFFFF;
        } while (--arg1 != 0);
    }
    va_end(cursor);
    if (*state != 0) {
        result = func_1502B350(output, component, state);
    } else {
        result = 0;
    }
    return result;
}
s32 func_1502B4A8(Game57FA0Reloc *, s32);

s32 func_1502B6BC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...) {
    u8 *output;
    va_list cursor;
    s32 status;
    s32 *state;
    s32 argument;
    s32 component;
    s32 result;

    state = &status;
    if (arg0 != 0) {
        state = arg0;
    }
    *state = 1;
    output = D_AB1950;
    va_start(cursor, arg3);
    if (arg3 != 0) {
        do {
            argument = va_arg(cursor, s32);
            if (*state != 0) {
                output += func_1502AC88(output, argument, &component);
            }
            *state = component & 0x0FFFFFFF;
        } while (--arg3 != 0);
    }
    va_end(cursor);
    if (*state != 0) {
        result = func_1502B350(output, component, state);
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

s32 func_1502B7F0(s32 *arg0, s32 arg1, ...) {
    va_list cursor;
    u8 *output;
    s32 value;
    s32 state;
    s32 component;

    state = 1;
    output = D_AB1950;
    va_start(cursor, arg1);
    for (; arg1 != 0; arg1--) {
        value = va_arg(cursor, s32);
        if (state != 0) {
            output += func_1502AC88(output, value, &component);
        }
        state = component & 0x0FFFFFFF;
    }
    va_end(cursor);
    if (state != 0) {
        *arg0 = func_1502B350(output, component, &state);
    } else {
        *arg0 = 0;
    }
    return state;
}
s32 func_1502AC88(u8 *, s32, s32 *);
s32 func_1502B224(u8 *, s32, s32, s32);
extern u8 D_AB1950[];

s32 func_1502B8E0(s32 arg0, s32 arg1, s32 arg2, ...) {
    u8 *output;
    va_list cursor;
    s32 result;
    s32 argument;
    s32 state;

    result = 1;
    output = D_AB1950;
    va_start(cursor, arg2);
    for (; arg2 != 0; arg2--) {
        argument = va_arg(cursor, s32);
        if (result != 0) {
            output += func_1502AC88(output, argument, &state);
        }
        result = state & 0x0FFFFFFF;
    }
    va_end(cursor);
    if (result != 0) {
        result = func_1502B224(output, arg0, state, arg1);
    }
    return result;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502B9B4 CURRENT (200) */
s32 func_1502B9B4(s32 arg0, ...) {
    u8 *output;
    va_list cursor;
    s32 result;
    s32 argument;
    s32 state;
    u64 buffer[3];
    s32 *data;

    result = 1;
    output = D_AB1950;
    va_start(cursor, arg0);
    for (; arg0 != 0; arg0--) {
        argument = va_arg(cursor, s32);
        if (result != 0) {
            output += func_1502AC88(output, argument, &state);
        }
        result = state & 0x0FFFFFFF;
    }
    va_end(cursor);
    if (result != 0) {
        result = ((state & 0x0FFFFFFF) + 1) & ~1;
        if ((state & 0x70000000) == 0x10000000) {
            data = (s32 *)&buffer[0];
            if ((s32)data & 8) {
                data = (s32 *)&buffer[1];
            }
            func_10004514((s32)output, (s32)data, 0x10, 1);
            result = *data;
        }
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502B9B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_57FA0/func_1502B9B4.s")
