#include "types.h"

/*
 * Provisional debugger C collection: debugger UI, rendering, and controller I/O.
 * US virtual range: 0x16000000..0x16001AD0 (exclusive end).
 * Evidence: docs/evidence/us_debugger_overlay.md
 *
 * Original source-object ownership remains unreviewed; this collection is
 * not registered as a source unit. Individual full-span C matches are tracked
 * independently. Preserve function order and the canonical GLOBAL_ASM bodies
 * for deferred candidates until their full registered spans match.
 * Loaded data and the privileged TLB capture routine remain separate raw ASM.
 */

void func_160012B0(s32 position, const u8 *text);
extern u8 D_160046AC[];

void func_16000000(void) {
    func_160012B0(0x116, D_160046AC);
}
extern s32 D_16003890;
extern u8 D_16003AF4;

s32 func_16000028(void) {
    if (D_16003890 & 0xC000) {
        D_16003AF4 = 1;
        return 3;
    }
    return 0;
}
struct OSThread_s;
extern struct OSThread_s *D_1600389C;
extern u8 D_160038A4;
extern s32 D_16003AF0;
extern s8 D_16003B1C;
extern const u8 *D_16003B20[2];
extern u8 D_160046D0[];
extern u8 D_160046DC[];
extern u8 D_160046E8[];
extern u8 D_160046F4[];
extern u8 D_16004700[];
extern u8 D_16004708[];
extern u8 D_16004710[];
extern u8 D_1600471C[];
void func_16001338(u8 red, u8 green, u8 blue);
void func_16001044(s32 position, s32 mode, u32 value);

void func_16000058(void) {
    s32 i;
    s32 position;

    func_16001338(0xFF, 0xFF, 0xFF);
    func_160012B0(0x2C, D_160046D0);
    position = 0x6C;
    for (i = 0; i < 2; i++) {
        if (i == D_16003B1C) {
            func_16001338(0xFF, 0, 0);
        } else {
            func_16001338(0xFF, 0xFF, 0xFF);
        }
        func_160012B0(position, D_16003B20[i]);
        position += 0x20;
    }
    if (D_16003B1C == 2) {
        func_16001338(0xFF, 0, 0);
    } else {
        func_16001338(0xFF, 0xFF, 0xFF);
    }
    if (D_16003AF0 != 0) {
        if ((((u32 *)D_1600389C)[0x120 / 4] == 0x20) && (D_160038A4 == 0)) {
            func_160012B0(position, D_160046DC);
        } else if (D_16003AF0 != 0) {
            func_160012B0(position, D_160046E8);
        }
    } else {
        func_160012B0(position, D_160046F4);
    }
    func_16001338(0xFF, 0xFF, 0xFF);
    func_160012B0(0x263, D_16004700);
    func_16001044(0x26B, 1, 0xA3);
    func_160012B0(0x283, D_16004708);
    func_160012B0(0x28B, D_16004710);
    func_160012B0(0x297, D_1600471C);
}
extern s8 D_16003B1C;

s32 func_16000224(void) {
    s32 result = 0;

    if (D_16003890 & 0x40000) {
        result = 1;
        D_16003B1C--;
    }
    if (D_16003890 & 0x80000) {
        result = 1;
        D_16003B1C++;
    }
    if (D_16003B1C >= 3) {
        D_16003B1C = 0;
    }
    if (D_16003B1C < 0) {
        D_16003B1C = 2;
    }
    if (D_16003890 & 0x8000) {
        switch (D_16003B1C) {
        case 0:
            result = 3;
            D_16003AF4 = 2;
            break;
        case 1:
            result = 3;
            D_16003AF4 = 3;
            break;
        case 2:
            result = 4;
            break;
        }
    }
    return result;
}

/* The registered raw span also contains these two empty return bodies. */
void func_16000304(void) {
}

void func_1600030C(void) {
}
struct OSThread_s;
void func_16000424(struct OSThread_s *thread);
void func_16000590(struct OSThread_s *thread);
void func_160006CC(struct OSThread_s *thread);
extern struct OSThread_s *D_1600389C;
extern s8 D_16003B28;

void func_16000314(void) {
    switch (D_16003B28) {
    case 0:
        func_16000424(D_1600389C);
        func_160006CC(D_1600389C);
        return;
    case 1:
    case 2:
        func_16000590(D_1600389C);
        return;
    }
}
s32 func_16000384(void) {
    s32 result = 0;

    if (D_16003890 & 5) {
        D_16003B28++;
        if (D_16003B28 >= 3) {
            D_16003B28 = 0;
        }
        return 3;
    }
    if (D_16003890 & 0xA) {
        D_16003B28--;
        if (D_16003B28 < 0) {
            D_16003B28 = 2;
        }
        return 3;
    }
    if (D_16003890 & 0x4000) {
        D_16003AF4 = 1;
        result = 3;
    }
    return result;
}
extern const u8 *D_16003848[16];
extern u8 D_160038A4;
extern u8 D_16004728[];
extern u8 D_1600472C[];
extern u8 D_16004734[];
extern u8 D_16004738[];
extern u8 D_16004740[];
extern u8 D_16004748[];
void func_16001338(u8 red, u8 green, u8 blue);
void func_16001044(s32 position, s32 mode, u32 value);

void func_16000424(struct OSThread_s *thread) {
    u32 cause;
    s32 unused;
    s32 exception;

    func_16001338(0xFF, 0xFF, 0xFF);
    func_160012B0(0x23, D_16004728);
    func_16001044(0x2B, 0, ((u32 *)thread)[0x11C / 4]);
    func_160012B0(0x43, D_1600472C);
    func_16001044(0x4B, 0, ((u32 *)thread)[0x120 / 4]);
    func_16001338(0x80, 0x80, 0xFF);
    cause = ((u32 *)thread)[0x120 / 4];
    exception = (cause >> 2) & 0xF;
    func_160012B0(0x6B, D_16003848[exception]);
    if (exception == 0xB) {
        func_16001044(0x6F, 1, (cause >> 28) & 3);
    }
    func_16001338(0xFF, 0xFF, 0xFF);
    func_160012B0(0x83, D_16004734);
    func_16001044(0x8B, 0, ((u32 *)thread)[0x118 / 4]);
    func_160012B0(0xA3, D_16004738);
    func_16001044(0xAB, 0, ((u32 *)thread)[0x124 / 4]);
    func_160012B0(0xC3, D_16004740);
    func_16001044(0xCB, 1, ((u32 *)thread)[0x14 / 4]);
    if (D_160038A4 != 0) {
        func_160012B0(0x34, D_16004748);
    }
}
extern const u8 *D_16003B30[6];
extern u8 D_160047A4[];
extern u8 D_160047AC[];
void func_16001044(s32 position, s32 mode, u32 value);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_16000590 CURRENT (145) */
void func_16000590(struct OSThread_s *thread) {
    s32 position;
    s32 i;
    s32 base;
    u32 bits;
    u32 page = 0;
    register u32 *words = (u32 *)thread;

    bits = words[0x12C / 4];
    func_160012B0(3, D_160047A4);
    func_16001044(0xA, 0, bits);
    bits >>= 12;
    position = 0x2C;
    for (i = 0; i < 6; i++, bits >>= 1) {
        if (bits & 1) {
            func_160012B0(position, D_16003B30[i]);
            position += 0x20;
        }
    }
    i = 0;
    position = 0xC3;
    if (D_16003B28 == 1) {
        base = 0x4C;
    } else {
        base = 0x6C;
        page = 0x10;
    }
    for (; i < 16; base += 2, position += 0x20, i++) {
        func_160012B0(position, D_160047AC);
        func_16001044(position + 2, 1, i + page);
        func_16001044(position + 5, 2, words[base + 1]);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_16000590 */
#pragma GLOBAL_ASM("asm/us/nonmatchings/debugger/debugger_0000/func_16000590.s")
typedef struct {
    u8 bytes[4];
} DebuggerLabel;

extern u8 D_160037F0[];
extern DebuggerLabel D_16003B48;
void func_16001338(u8 red, u8 green, u8 blue);
void func_16001044(s32 position, s32 mode, u32 value);

void func_160006CC(struct OSThread_s *thread) {
    DebuggerLabel label = D_16003B48;
    s32 position = 0x123;
    u8 *descriptor = D_160037F0;
    register s32 index;

    func_16001338(0xC0, 0xC0, 0xFF);
    do {
        label.bytes[0] = descriptor[0];
        label.bytes[1] = descriptor[1];
        func_160012B0(position, label.bytes);
        position += 3;
        index = descriptor[2];
        func_16001044(position, 0, ((u32 *)thread)[index + 1]);
        position += 13;
        descriptor += 3;
    } while (descriptor[0] != 0);
}
extern s32 D_16003B4C;
extern u8 D_160047B0[];
extern u8 D_160047BC[];
extern u8 D_160047C0[];
extern u8 D_8002D4B0[];
extern u8 D_8002D8B0[];

void func_1600078C(void) {
    register u32 *stack;
    register s32 decimal_position;
    register u32 tag;
    register s32 position;
    register s32 row;
    register u32 value;
    register u32 *address;

    stack = (u32 *)(u32)((u64 *)D_1600389C)[0xF0 / 8];
    func_16001338(0, 0xFF, 0);
    func_160012B0(0xB, D_160047B0);
    address = stack + D_16003B4C;
    if (!((u32)address & 3) && ((u32)address >= 0x80000000U) &&
        ((u32)address < 0x80800001U)) {
        if (D_16003B4C == 0) {
            func_16001338(0xFF, 0, 0);
        } else if (((u32)address >= (u32)D_8002D4B0) &&
                   ((u32)address < ((u32)D_8002D4B0 + 0x400))) {
            func_16001338(0x80, 0x80, 0xFF);
        } else if (((u32)address >= (u32)D_8002D8B0) &&
                   ((u32)address < ((u32)D_8002D8B0 + 0x4000))) {
            func_16001338(0xFF, 0x80, 0x80);
        } else {
            func_16001338(0xFF, 0xFF, 0xFF);
        }
        position = 0x61;
        row = 0;
        do {
            func_16001044(position, 0, (u32)address);
            func_160012B0(position + 8, D_160047BC);
            value = *address;
            tag = (value >> 24) & 0xFF;
            if (tag == 0x80) {
                func_16001338(0x80, 0x80, 0xFF);
            } else if (tag == 0x15) {
                func_16001338(0xFF, 0, 0);
            } else if (tag == 0x16) {
                func_16001338(0x80, 0xFF, 0x80);
            } else if (tag == 0x10) {
                func_16001338(0xFF, 0, 0);
            } else {
                func_16001338(0xFF, 0xFF, 0xFF);
            }
            func_16001044(position + 0xC, 0, value);
            decimal_position = position + 0x16;
            func_160012B0(decimal_position, D_160047C0);
            func_16001338(0xFF, 0xFF, 0xFF);
            func_16001044(decimal_position, 1, value);
            if (((u32)address >= (u32)D_8002D4B0) &&
                ((u32)address < ((u32)D_8002D4B0 + 0x400))) {
                func_16001338(0x80, 0x80, 0xFF);
            } else if (((u32)address >= (u32)D_8002D8B0) &&
                       ((u32)address < ((u32)D_8002D8B0 + 0x4000))) {
                func_16001338(0xFF, 0x80, 0x80);
            } else {
                func_16001338(0xFF, 0xFF, 0xFF);
            }
            row++;
            position += 0x20;
            address++;
        } while (row != 0x16);
    }
}
extern s8 D_160036F3;
extern s32 D_16003B4C;

s32 func_16000A5C(void) {
    s32 result = 0;

    if ((D_160036F3 >= 0x29) || (D_16003890 & 8)) {
        D_16003B4C--;
        if (D_16003B4C < 0) {
            D_16003B4C = 0;
        } else {
            result = 3;
        }
    } else if ((D_160036F3 < -0x28) || (D_16003890 & 4)) {
        D_16003B4C++;
        if (D_16003B4C >= 0xC9) {
            D_16003B4C = 0xC8;
        }
        result = 3;
    }
    if (D_16003890 & 0x4000) {
        D_16003AF4 = 1;
        result = 3;
    }
    return result;
}
/* SDK OSContPad and __OSContReadFormat layouts used by this debugger copy. */
typedef struct {
    u16 button;
    s8 stick_x;
    s8 stick_y;
    u8 errno;
} DebuggerControllerPad;
extern u8 D_16003888;
extern u8 *D_8002AAE8[];
extern u8 **D_8002BDE0;
extern u8 D_8002AC5C;
extern struct OSThread_s D_80031AE0;
typedef struct {
    u8 reserved00[8];
    u32 tlb[4];
} DebuggerCapture;

extern s32 D_8003C8E0;
/* DebuggerCapture.tlb at +8 in the 0x18-byte D_8003C8E0 region.
 * func_16000B14 loads four words through this subobject address. */
extern u32 D_8003C8E8[4];
extern u8 D_150AD770[];
/* COP0 EntryLo0, EntryLo1, EntryHi and PageMask captured by func_16003650. */
extern u32 D_160038AC[32];
extern u32 D_1600392C[32];
extern u32 D_160039AC[32];
extern u32 D_16003A2C[32];
extern u32 D_160039E8;
extern u32 D_16003A68;
extern s32 D_16003894;
extern s32 D_16003898;
extern void (*D_16003AF8[4])(void);
extern s32 (*D_16003B08[4])(void);
extern DebuggerControllerPad D_160036F0;
void func_16003650(void);
void func_16001678(void);
void func_10024F10(void);
s32 func_16001700(void);
void func_16001830(DebuggerControllerPad *data);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_16000B14 CURRENT (1600) */
s32 func_16000B14(struct OSThread_s *thread) {
    s32 unused[3];
    s32 first;
    register s32 state;
    register s32 stick;
    register u32 pc;
    register s32 page;
    register s32 odd;
    register u32 flags;
    register s32 offset;
    register s32 *entry;
    u32 *saved;
    register void (*draw)(void);
    register s32 (*input)(void);

    state = 0;
    first = 1;
    if (D_8002AC5C != 0) {
        return 0;
    }
    D_16003888 = 0;
    if ((D_8002AAE8[0] == 0) || (D_8002AAE8[1] == 0)) {
        D_8002AAE8[0] = (u8 *)0x80350000;
        D_8002AAE8[1] = (u8 *)0x80350000;
        return 0;
    }
    func_16003650();
    saved = D_8003C8E8;
    D_160038AC[15] = saved[0];
    D_1600392C[15] = saved[1];
    D_160039E8 = saved[2];
    D_16003A68 = saved[3];
    pc = ((u32 *)thread)[0x11C / 4];
    if ((pc & 0xFF000000) != 0x15000000) {
        D_16003AF0 = 1;
    } else {
        pc &= ~0xFFF;
        odd = pc & 0x1000;
        pc &= ~0x1000;
        D_16003AF0 = 0;
        for (offset = 0; offset < 32; offset++) {
            if (pc == D_160039AC[offset]) {
                flags = odd ? D_1600392C[offset] : D_160038AC[offset];
                if (flags & 2) {
                    D_16003AF0 = 1;
                }
            }
        }
    }
    if ((((u32)D_8003C8E0 >> 24) & 0xFF) == 0xC) {
        thread = &D_80031AE0;
    }
    if (D_8002BDE0[1] == D_8002AAE8[1]) {
        *(s8 *)&D_16003888 = 1;
    }
    D_1600389C = thread;
    D_160038A4 = 0;
    if ((((s32 *)thread)[0x120 / 4] == 0x20) &&
        ((u32)D_150AD770 == ((u32 *)thread)[0x11C / 4])) {
        *(s8 *)&D_160038A4 = 1;
    }
    do {
        if ((first == 0) && (state & 2)) {
            func_16001678();
        }
        draw = D_16003AF8[D_16003AF4];
        if (draw != 0) {
            draw();
        }
        func_10024F10();
        do {
            state = 0;
            D_16003898 = D_16003894;
            func_16001700();
            func_16001830(&D_160036F0);
            if (first != 0) {
                D_16003898 = D_16003894;
            }
            D_16003894 = D_160036F0.button;
            stick = D_160036F0.stick_x;
            if (stick >= 0x33) {
                D_16003894 = D_160036F0.button | 0x20000;
            }
            if (stick < -0x32) {
                D_16003894 |= 0x10000;
            }
            stick = D_160036F0.stick_y;
            if (stick >= 0x33) {
                D_16003894 |= 0x40000;
            }
            if (stick < -0x32) {
                D_16003894 |= 0x80000;
            }
            D_16003890 = (D_16003894 ^ D_16003898) & D_16003894;
            input = D_16003B08[D_16003AF4];
            if (input != 0) {
                state = input();
            }
        } while (!(state & 5));
        first = 0;
    } while (!(state & 4));
    if (D_16003AF0 == 0) {
        ((s16 *)thread)[0x10 / 2] = 4;
        ((s16 *)thread)[0x12 / 2] = 0;
        return 1;
    }
    if ((((s32 *)thread)[0x120 / 4] == 0x20) && (D_160038A4 == 0)) {
        ((s32 *)thread)[0x11C / 4] += 4;
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_16000B14 */
#pragma GLOBAL_ASM("asm/us/nonmatchings/debugger/debugger_0000/func_16000B14.s")
extern s32 D_160038A0;
extern u8 D_160047D0[];
extern u8 D_160047D4[];
extern u8 D_160047DC[];
extern u8 D_160047E0[];
s32 func_16001B34(u8 *buffer, const u8 *format, ...);

void func_16000F8C(s32 position, f32 value) {
    f32 copy;
    u8 buffer[44];
    u32 exponent;

    if ((position >= (D_160038A0 << 5)) && (position < 0x341)) {
        copy = value;
        exponent = (u32)(*(s32 *)&copy & 0x7F800000) >> 23;
        if (((exponent == 0) || (exponent >= 0xFF)) &&
            ((exponent = *(s32 *)&copy * 2) != 0)) {
            func_160012B0(position, D_160047D0);
            return;
        }
        func_16001B34(buffer, D_160047D4, D_160047DC, D_160047E0,
                      (f64)value);
        func_160012B0(position, buffer);
    }
}
u8 *func_1600160C(s32 position);
u8 *func_160014F0(u8 *destination, u8 character);

typedef struct DebuggerDecimalPowers {
    s32 power[10];
} DebuggerDecimalPowers;
extern DebuggerDecimalPowers D_16003B50;
extern u8 D_160047E4[];
extern u8 D_160047E8[];
extern u8 D_160047F0[];
extern u8 D_160047F4[];

void func_16001044(s32 position, s32 mode, u32 value) {
    s32 index;
    s32 started;
    s32 decimal_index;
    s32 digit;
    s32 exponent;
    u8 character;
    DebuggerDecimalPowers powers;
    s32 unused[2];
    f32 copy;
    u8 buffer[36];
    u8 *destination;

    powers = D_16003B50;
    if ((position >= (D_160038A0 << 5)) && (position < 0x341)) {
        destination = func_1600160C(position);
        switch (mode) {
        case 0:
            destination += 0x70;
            index = 0;
            do {
                character = value & 0xF;
                if (character >= 10) {
                    character += 7;
                }
                character += '0';
                func_160014F0(destination, character);
                value = (s32)value >> 4;
                index++;
                destination -= 0x10;
            } while (index != 8);
            break;
        case 1:
            if ((s32)value < 0) {
                destination = func_160014F0(destination, '-');
                value = -value;
            }
            started = 0;
            for (decimal_index = 9; decimal_index >= 0; decimal_index--) {
                digit = (s32)value / powers.power[decimal_index];
                value = (s32)value % powers.power[decimal_index];
                if ((digit > 0) || started || (decimal_index == 0)) {
                    destination = func_160014F0(destination, digit + '0');
                    started = 1;
                }
            }
            break;
        case 2:
            exponent = (s32)(value & 0x7F800000) >> 23;
            if (((exponent <= 0) || (exponent >= 0xFF)) &&
                ((exponent != 0) || (value << 9))) {
                func_160012B0(position, D_160047E4);
                return;
            }
            *(s32 *)&copy = value;
            func_16001B34(buffer, D_160047E8, D_160047F0, D_160047F4,
                          (f64)copy);
            func_160012B0(position, buffer);
            break;
        }
    }
}
u8 *func_1600160C(s32 position);
u8 *func_160014F0(u8 *destination, u8 character);
extern s32 D_160038A0;

void func_160012B0(s32 position, const u8 *text) {
    u8 *destination;
    u8 character;

    if ((text != 0) && (position >= (D_160038A0 << 5)) &&
        (position < 0x341)) {
        destination = func_1600160C(position);
        while ((character = *text) != 0) {
            destination = func_160014F0(destination, character);
            text++;
        }
    }
}
extern u16 D_1600388C;

void func_16001338(u8 red, u8 green, u8 blue) {
    D_1600388C = ((red & 0xF8) << 8) | ((green & 0xF8) << 3) |
                ((blue & 0xF8) >> 2) | 1;
}
extern s32 D_160038A8;

void func_16001390(s16 left, s16 top, s16 right, s16 bottom) {
    u16 *pixel;
    s32 count;

    if ((right < left) || (bottom < top)) {
        return;
    }
    if ((left < 0) || (top < 0)) {
        return;
    }
    right++;
    bottom++;
    pixel = (u16 *)func_1600160C(0);
    pixel += left + top * D_160038A8;
    right -= left;
    bottom -= top;
    while (bottom > 0) {
        for (count = right; count > 0; count--) {
            *pixel++ = D_1600388C;
        }
        bottom--;
        pixel += D_160038A8 - right;
    }
}
extern u8 D_16003CE0[];
extern s32 D_160038A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_160014F0 CURRENT (100) */
u8 *func_160014F0(u8 *destination, u8 character) {
    u16 *pixel;
    u16 color;
    s32 column;
    u16 bits;
    s32 row;
    u8 *glyph;
    s32 code;
    u16 value;

    pixel = (u16 *)destination;
    color = D_1600388C;
    code = character;
    if (code < 0x20) {
        code = 0x20;
    }
    glyph = D_16003CE0 + ((code - 0x20) << 3);
    row = 0;
    for (; row < 8; row++, glyph++) {
        for (column = 0, bits = *glyph; column < 8; column++) {
            value = (bits & 0x80) ? color : 1;
            bits <<= 1;
            *pixel++ = value;
        }
        pixel += D_160038A8 - 8;
    }
    return destination + 0x10;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_160014F0 */
#pragma GLOBAL_ASM("asm/us/nonmatchings/debugger/debugger_0000/func_160014F0.s")
extern u8 D_16003888;
extern s32 D_160038A8;
extern u8 *D_8002AAE8[];

u8 *func_1600160C(s32 position) {
    s32 row = position & 0xFFE0;
    s32 offset = row;

    if (D_160038A8 != 0x124) {
        offset = (row >> 2) + row;
    }
    offset = (offset >> 2) * (D_160038A8 << 1);
    offset += (position & 0x1F) << 4;
    offset += D_160038A8 << 2;
    offset += 0x10;
    return D_8002AAE8[D_16003888] + offset;
}
void func_16001678(void) {
    u32 *cursor = (u32 *)D_8002AAE8[D_16003888];
    s32 height;
    u32 *end;

    if (D_160038A8 == 0x124) {
        height = 0xD7;
    } else {
        height = 0x108;
    }
    end = (D_160038A8 >> 1) * height + cursor;
    while (cursor < end) {
        cursor[0] = 0x10001;
        cursor[1] = 0x10001;
        cursor[2] = 0x10001;
        cursor[3] = 0x10001;
        cursor += 4;
    }
}
s32 func_160016F4(s32 arg0) {
    return arg0;
}
extern u8 D_80042A10[];
extern u8 D_80042A50;
extern s32 D_80042A4C;
void func_160018BC(void);
s32 func_160019A8(s32 direction, void *buffer);
s32 func_10024770(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_16001700 CURRENT (20) */
s32 func_16001700(void) {
    s32 result;
    s32 dummy;
    s32 read_dummy;
    u32 deadline;
    u32 read_deadline;
    u32 *cursor;
    u32 *end;

    if (D_80042A50 != 1) {
        func_160018BC();
        func_160019A8(1, D_80042A10);
        dummy = 0;
        deadline = func_10024770() + 0x30D40;
        while ((u32)func_10024770() < deadline) {
            dummy = func_160016F4(dummy);
        }
        func_160016F4(dummy);
    }
    end = (u32 *)&D_80042A50;
    cursor = (u32 *)D_80042A10;
    do {
        *cursor++ = 0xFF;
    } while (cursor < end);
    D_80042A4C = 0;
    result = func_160019A8(0, D_80042A10);
    D_80042A50 = 1;
    read_dummy = 0;
    read_deadline = func_10024770() + 0xC3500;
    while ((u32)func_10024770() < read_deadline) {
        read_dummy = func_160016F4(read_dummy);
    }
    func_160016F4(read_dummy);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_16001700 */
#pragma GLOBAL_ASM("asm/us/nonmatchings/debugger/debugger_0000/func_16001700.s")



typedef struct {
    u8 dummy;
    u8 txsize;
    u8 rxsize;
    u8 command;
    u16 button;
    s8 stick_x;
    s8 stick_y;
} DebuggerControllerRead;

extern u8 D_80042A10[];
extern u8 D_80042A51;

void func_16001830(DebuggerControllerPad *data) {
    u8 *ptr = D_80042A10;
    DebuggerControllerRead packet;
    s32 i;

    for (i = 0; i < D_80042A51; i++, ptr += sizeof(packet), data++) {
        packet = *(DebuggerControllerRead *)ptr;
        data->errno = (packet.rxsize & 0xC0) >> 4;
        if (data->errno != 0) {
            continue;
        }
        data->button = packet.button;
        data->stick_x = packet.stick_x;
        data->stick_y = packet.stick_y;
    }
}
extern u8 D_80042A50;

void func_160018BC(void) {
    u8 *ptr = D_80042A10;
    DebuggerControllerRead packet;
    s32 i;

    for (i = 0; i < 16; i++) {
        ((u32 *)D_80042A10)[i] = 0;
    }
    ((u32 *)D_80042A10)[15] = 1;
    packet.dummy = 0xFF;
    packet.txsize = 1;
    packet.rxsize = 4;
    packet.command = 1;
    packet.button = 0xFFFF;
    packet.stick_x = -1;
    packet.stick_y = -1;
    for (i = 0; i < D_80042A51; i++, ptr += sizeof(packet)) {
        *(DebuggerControllerRead *)ptr = packet;
    }
    *ptr = 0xFE;
}
s32 func_16001984(void) {
    register u32 status = *(volatile u32 *)0xA4800018;

    if (status & 3) {
        return 1;
    } else {
        return 0;
    }
}
s32 func_16001984(void);
void func_10022D10(void *address, s32 size);
u32 func_100233C0(void *address);
void func_10023D20(void *address, s32 size);
extern u32 D_A4800000;
extern u32 D_A4800004;
extern u32 D_A4800010;

s32 func_160019A8(s32 direction, void *buffer) {
    if ((u32)buffer & 3) {
        return -1;
    }
    if (func_16001984()) {
        return -1;
    }
    if (direction == 1) {
        func_10023D20(buffer, 0x40);
    }
    *(volatile u32 *)0xA4800000 = func_100233C0(buffer);
    if (direction == 0) {
        *(volatile u32 *)0xA4800004 = 0x1FC007C0;
    } else {
        *(volatile u32 *)0xA4800010 = 0x1FC007C0;
    }
    if (direction == 0) {
        func_10022D10(buffer, 0x40);
    }
    return 0;
}

void func_16001A64(void) {
}

s32 func_16001A6C(f32 value) {
    s32 bits = *(s32 *)&value;
    s32 exponent;

    if (((u32)bits << 1) == 0) {
        return 0;
    }
    exponent = (bits & 0x7F800000) >> 23;
    if ((exponent <= 0) || (exponent >= 0xFF)) {
        return 1;
    }
    return 0;
}
void func_16001AB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}
