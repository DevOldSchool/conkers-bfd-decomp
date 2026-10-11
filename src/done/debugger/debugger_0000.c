#include "types.h"

/*
 * Debugger source unit: debugger UI, rendering, and controller I/O.
 * US virtual range: 0x16000000..0x16001AD0 (exclusive end).
 * Evidence: docs/evidence/debugger/us_debugger_source_units.md
 */

void func_160012B0(s32 position, const u8 *text);
extern const u8 D_160046AC[];

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
extern const u8 D_160046D0[];
extern const u8 D_160046DC[];
extern const u8 D_160046E8[];
extern const u8 D_160046F4[];
extern const u8 D_16004700[];
extern const u8 D_16004708[];
extern const u8 D_16004710[];
extern const u8 D_1600471C[];
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
extern const u8 D_16004728[];
extern const u8 D_1600472C[];
extern const u8 D_16004734[];
extern const u8 D_16004738[];
extern const u8 D_16004740[];
extern const u8 D_16004748[];
void func_16001338(u8 red, u8 green, u8 blue);
void func_16001044(s32 position, s32 mode, u32 value);

void func_16000424(struct OSThread_s *thread) {
    u32 cause;
    s32 coprocessor;
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
        coprocessor = (cause >> 28) & 3;
        func_16001044(0x6F, 1, coprocessor);
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
extern const u8 D_160047A4[];
extern const u8 D_160047AC[];
void func_16001044(s32 position, s32 mode, u32 value);

void func_16000590(struct OSThread_s *thread) {
    s32 position;
    s32 i;
    s32 base;
    u32 bits;
    u32 page = 0;
    u32 *words = (u32 *)thread;

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
    do {
        func_160012B0(position, D_160047AC);
        func_16001044(position + 2, 1, i + page);
        func_16001044(position + 5, 2, words[base + 1]);
        base += 2;
        position += 0x20;
        i++;
    } while (i < 16);
}
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
    s32 index;

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
extern const u8 D_160047B0[];
extern const u8 D_160047BC[];
extern const u8 D_160047C0[];
extern u8 D_8002D4B0[];
extern u8 D_8002D8B0[];

void func_1600078C(void) {
    u32 *stack;
    s32 decimal_position;
    u32 tag;
    s32 position;
    s32 row;
    u32 value;
    u32 *address;

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
/* Reviewed SDK __osViCurr object; __OSViContext.framep is at +4. */
typedef struct {
    u16 state;
    u16 retraceCount;
    void *framep;
} DebuggerViContext;
extern DebuggerViContext *D_8002BDE0;
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
extern DebuggerControllerPad D_160036F0[4];
void func_16003650(void);
void func_16001678(void);
void func_10024F10(void);
s32 func_16001700(void);
void func_16001830(DebuggerControllerPad *data);

s32 func_16000B14(struct OSThread_s *thread) {
    u32 *context;
    u32 *frame;
    u32 entryLo;
    s32 first;
    s32 state;
    s32 stick;
    u32 pc;
    u32 page;
    s32 odd;
    u32 flags;
    s32 offset;
    s32 *entry;
    u32 *saved;
    void (*draw)(void);
    s32 (*input)(void);

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
    context = D_8003C8E8;
    saved = context;
    D_160038AC[15] = saved[0];
    D_1600392C[15] = saved[1];
    D_160039E8 = saved[2];
    D_16003A68 = saved[3];
    if ((((u32 *)thread)[0x11C / 4] & 0xFF000000) != 0x15000000) {
        D_16003AF0 = 1;
    } else {
        page = ((u32 *)thread)[0x11C / 4] & ~0xFFF;
        odd = page & 0x1000;
        pc = page & ~0x1000;
        page = pc;
        D_16003AF0 = 0;
        for (offset = 0; offset < 32; offset++) {
            if (page == D_160039AC[offset]) {
                entryLo = odd ? D_1600392C[offset] : D_160038AC[offset];
                flags = entryLo;
                if (flags & 2) {
                    D_16003AF0 = 1;
                }
            }
        }
    }
    if ((((u32)D_8003C8E0 >> 24) & 0xFF) == 0xC) {
        thread = &D_80031AE0;
    }
    frame = (u32 *)D_8002BDE0->framep;
    if ((saved = frame) == (u32 *)D_8002AAE8[1]) {
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
            func_16001830(D_160036F0);
            if (first != 0) {
                D_16003898 = D_16003894;
            }
            D_16003894 = D_160036F0[0].button;
            stick = D_160036F0[0].stick_x;
            if (stick >= 0x33) {
                D_16003894 |= 0x20000;
            }
            if (stick < -0x32) {
                D_16003894 |= 0x10000;
            }
            stick = D_160036F0[0].stick_y;
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
extern s32 D_160038A0;
extern const u8 D_160047D0[];
extern const u8 D_160047D4[];
extern const u8 D_160047DC[];
extern const u8 D_160047E0[];
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
extern const u8 D_160047E4[];
extern const u8 D_160047E8[];
extern const u8 D_160047F0[];
extern const u8 D_160047F4[];

void func_16001044(s32 position, s32 mode, u32 value) {
    s32 index;
    s32 started;
    s32 decimal_index;
    s32 digit;
    s32 exponent;
    u8 character;
    DebuggerDecimalPowers powers;
    s32 power;
    u32 mantissa;
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
                power = powers.power[decimal_index];
                digit = (s32)value / power;
                value = (s32)value % power;
                if ((digit > 0) || started || (decimal_index == 0)) {
                    destination = func_160014F0(destination, digit + '0');
                    started = 1;
                }
            }
            break;
        case 2:
            exponent = (s32)(value & 0x7F800000) >> 23;
            mantissa = value << 9;
            if (((exponent <= 0) || (exponent >= 0xFF)) &&
                ((exponent != 0) || mantissa)) {
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
extern const u8 D_16003CE0[];
extern s32 D_160038A8;

u8 *func_160014F0(u8 *destination, u8 character) {
    u16 *pixel;
    u16 color;
    u32 column;
    u16 bits;
    u32 row;
    const u8 *glyph;
    s32 code;
    u16 value;

    pixel = (u16 *)destination;
    color = D_1600388C;
    column = character;
    bits = column;
    code = bits;
    if (code < 0x20) {
        code = 0x20;
    }
    row = 0, glyph = D_16003CE0 + ((code - 0x20) << 3);
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
u32 func_10024770(void);

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
    cursor = (u32 *)D_80042A10, end = (u32 *)&D_80042A50;
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
    u32 status = *(volatile u32 *)0xA4800018;

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

/* Initialized state layout: docs/evidence/debugger/us_debugger_source_units.md. */
DebuggerControllerPad D_160036F0[4] = {{0, 0, 0, 0}};
extern const u8 D_16003FE0[];
extern const u8 D_16003FE4[];
extern const u8 D_16003FF4[];
extern const u8 D_16004000[];
extern const u8 D_16004010[];
extern const u8 D_1600401C[];
extern const u8 D_16004024[];
extern const u8 D_16004030[];
extern const u8 D_16004038[];
extern const u8 D_16004048[];
extern const u8 D_16004058[];
extern const u8 D_16004070[];
extern const u8 D_1600407C[];
extern const u8 D_1600408C[];
extern const u8 D_160040A4[];
extern const u8 D_160040B0[];
extern const u8 D_160040BC[];
extern const u8 D_160040D4[];
extern const u8 D_160040F0[];
extern const u8 D_1600411C[];
extern const u8 D_16004154[];
extern const u8 D_16004170[];
extern const u8 D_16004190[];
extern const u8 D_160041B0[];
extern const u8 D_160041D4[];
extern const u8 D_160041EC[];
extern const u8 D_16004218[];
extern const u8 D_16004244[];
extern const u8 D_16004274[];
extern const u8 D_16004298[];
extern const u8 D_160042C4[];
extern const u8 D_160042E8[];
extern const u8 D_16004304[];
extern const u8 D_1600431C[];
extern const u8 D_16004330[];
extern const u8 D_16004340[];
extern const u8 D_1600434C[];
extern const u8 D_16004364[];
extern const u8 D_16004378[];
extern const u8 D_16004398[];
extern const u8 D_160043C8[];
extern const u8 D_160043EC[];
extern const u8 D_16004410[];
extern const u8 D_16004428[];
extern const u8 D_16004440[];
extern const u8 D_16004454[];
extern const u8 D_16004474[];
extern const u8 D_16004494[];
extern const u8 D_160044B4[];
extern const u8 D_160044D0[];
extern const u8 D_160044F0[];
extern const u8 D_16004514[];
extern const u8 D_16004534[];
extern const u8 D_16004554[];
extern const u8 D_16004570[];
extern const u8 D_16004588[];
extern const u8 D_160045A0[];
extern const u8 D_160045B8[];
extern const u8 D_160045C4[];
extern const u8 D_160045D8[];
extern const u8 D_160045EC[];
extern const u8 D_160045FC[];
extern const u8 D_16004610[];
extern const u8 D_16004620[];
extern const u8 D_16004630[];
extern const u8 D_16004644[];
extern const u8 D_1600464C[];
extern const u8 D_16004658[];
extern const u8 D_16004668[];
extern const u8 D_1600467C[];
extern const u8 D_16004690[];
extern const u8 D_16004698[];
extern const u8 D_1600469C[];
extern const u8 D_160046AC[];
extern const u8 D_160046BC[];
extern const u8 D_160046C8[];
extern const u8 D_160046D0[];
extern const u8 D_160046DC[];
extern const u8 D_160046E8[];
extern const u8 D_160046F4[];
extern const u8 D_16004700[];
extern const u8 D_16004708[];
extern const u8 D_16004710[];
extern const u8 D_1600471C[];
extern const u8 D_16004728[];
extern const u8 D_1600472C[];
extern const u8 D_16004734[];
extern const u8 D_16004738[];
extern const u8 D_16004740[];
extern const u8 D_16004748[];
extern const u8 D_16004754[];
extern const u8 D_16004760[];
extern const u8 D_1600476C[];
extern const u8 D_16004778[];
extern const u8 D_16004784[];
extern const u8 D_16004790[];
extern const u8 D_160047A4[];
extern const u8 D_160047AC[];
extern const u8 D_160047B0[];
extern const u8 D_160047BC[];
extern const u8 D_160047C0[];
extern const u8 D_160047D0[];
extern const u8 D_160047D4[];
extern const u8 D_160047DC[];
extern const u8 D_160047E0[];
extern const u8 D_160047E4[];
extern const u8 D_160047E8[];
extern const u8 D_160047F0[];
extern const u8 D_160047F4[];
const u8 * D_16003708[57] = {D_16003FE0, D_16003FE4, D_16003FF4, D_16004000, D_16004010, D_1600401C, D_16004024, D_16004030, D_16004038, D_16004048, D_16004058, D_16004070, D_1600407C, D_1600408C, D_160040A4, D_160040B0, D_160040BC, D_160040D4, D_160040F0, D_1600411C, D_16004154, D_16004170, D_16004190, D_160041B0, D_160041D4, D_160041EC, D_16004218, D_16004244, D_16004274, D_16004298, D_160042C4, D_160042E8, D_16004304, D_1600431C, D_16004330, D_16004340, D_1600434C, D_16004364, D_16004378, D_16004398, D_160043C8, D_160043EC, D_16004410, D_16004428, D_16004440, D_16004454, D_16004474, D_16004494, D_160044B4, D_160044D0, D_160044F0, D_16004514, D_16004534, D_16004554, D_16004570, D_16004588, D_160045A0};
static u32 debuggerReserved37EC = 0;
u8 D_160037F0[85] = {
    118, 48, 10, 118, 49, 12, 97, 48, 14, 97, 49, 16, 97, 50, 18, 97, 51, 20, 116, 48, 22, 116, 49, 24, 116, 50, 26, 116, 51, 28, 116, 52, 30, 116, 53, 32, 116, 54, 34, 116, 55, 36, 116, 56, 54, 116, 57, 56, 115, 48, 38, 115, 49, 40, 115, 50, 42, 115, 51, 44, 115, 52, 46, 115, 53, 48, 115, 54, 50, 115, 55, 52, 115, 56, 62, 115, 112, 60, 103, 112, 58, 114, 97, 64, 0
};
const u8 * D_16003848[16] = {D_160045B8, D_160045C4, D_160045D8, D_160045EC, D_160045FC, D_16004610, D_16004620, D_16004630, D_16004644, D_1600464C, D_16004658, D_16004668, D_1600467C, D_16004690, D_16004698, D_1600469C};
u8 D_16003888 = 0;
u16 D_1600388C = 0xFFFF;
s32 D_16003890 = 0;
s32 D_16003894 = 0;
s32 D_16003898 = 0;
struct OSThread_s *D_1600389C = 0;
s32 D_160038A0 = 0;
u8 D_160038A4 = 0;
s32 D_160038A8 = 292;
u32 D_160038AC[32] = {0};
u32 D_1600392C[32] = {0};
u32 D_160039AC[32] = {0};
u32 D_16003A2C[32] = {0};
static u32 debuggerReserved3AAC[17] = {0};
s32 D_16003AF0 = 1;
u8 D_16003AF4 = 0;
void (*D_16003AF8[4])(void) = {func_16000000, func_16000058, func_16000314, func_1600078C};
s32 (*D_16003B08[4])(void) = {func_16000028, func_16000224, func_16000384, func_16000A5C};
static u32 debuggerReserved3B18 = 0x80500000;
s8 D_16003B1C = 0;
const u8 * D_16003B20[2] = {D_160046BC, D_160046C8};
s8 D_16003B28 = 0;
static u32 debuggerReserved3B2C = 0;
const u8 * D_16003B30[6] = {D_16004754, D_16004760, D_1600476C, D_16004778, D_16004784, D_16004790};
DebuggerLabel D_16003B48 = {{0, 0, 0x20, 0}};
s32 D_16003B4C = 0;
DebuggerDecimalPowers D_16003B50 = {{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}};
/* Three 80-byte records. The 72 coefficient bytes are independently compared
 * with the reviewed VI records; no OSViMode ABI is inferred from that equality. */
typedef struct {
    u8 type;
    u32 coefficients[18];
    u32 reserved;
} DebuggerVideoRecord;
static DebuggerVideoRecord debuggerVideoRecords[3] = {
    {30, {0x00000140, 0x0404233A, 0x00000271, 0x00150C69, 0x0C6F0C6E, 0x00800300, 0x00000200, 0x00000000, 0x00000280, 0x00000400, 0x005F0239, 0x0009026B, 0x00000002, 0x00000280, 0x00000400, 0x005F0239, 0x0009026B, 0x00000002}, 0},
    {30, {0x00000140, 0x04651E39, 0x0000020D, 0x00040C11, 0x0C190C1A, 0x006C02EC, 0x00000200, 0x00000000, 0x00000280, 0x00000400, 0x002501FF, 0x000E0204, 0x00000002, 0x00000280, 0x00000400, 0x002501FF, 0x000E0204, 0x00000002}, 0},
    {62, {0x00000124, 0x03E52239, 0x0000020D, 0x00000C15, 0x0C150C15, 0x008C02D5, 0x00000200, 0x00000000, 0x00000248, 0x00000400, 0x003D01E8, 0x000E0204, 0x00000002, 0x00000248, 0x00000400, 0x003D01E8, 0x000E0204, 0x00000002}, 0},
};
static u32 debuggerReserved3C68[2] = {0};

/* Locally extracted, editable glyph pixels and text stay ignored. */
#include "../build/us/debugger-assets/ui.inc.c"
