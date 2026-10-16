#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_AD9B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_periodic_actor_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15080828
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_15080738(s32);
extern s8 D_800D1940;
extern void *D_800D199C;
extern u8 D_800D2E60[];
extern s32 D_800D3098;

void func_15080500(u8 *arg0, void *arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0;

    if ((arg0 != 0) && (*(s32 *)arg0 != 0) && (arg0[0x127] != 0xFF)) {
        if ((arg3 == 0x2B) || (arg3 == 0x2C)) {
            D_800D1940 = arg3;
            D_800D199C = arg1;
            arg3 = 0x2A;
        } else {
            if (func_15080738(arg3) != 0) {
                D_800D1940 = arg3;
                if (!(D_800D2E60[arg3 >> 3] & (1 << (arg3 & 7)))) {
                    arg3 = 0x1A;
                }
            }
        }
        if (arg2 == 0) {
            temp_v0 = *(u8 **)(arg0 + 0x31C);
            if (!(temp_v0[0x74] & 0x80)) {
                temp_v0[0x74] = arg3;
            }
        } else {
            temp_v0 = *(u8 **)(arg0 + 0x31C);
            if (!(temp_v0[0x75] & 0x80)) {
                temp_v0[0x75] = arg3;
                (*(u8 **)(arg0 + 0x31C))[0x7A] =
                    ((s32)arg1 - D_800D3098) / 52;
            }
        }
    }
}
extern void * D_800CC5EC;

void func_15080620(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 != 0) {
        arg2 |= 0x80;
    }
    if (arg1 == 0) {
        *(s8 *)((u8 *)*(u8 **)((u8 *)&D_800CC5EC + (arg0 * 0x32C)) + 0x74) = arg2;
        return;
    }
    *(s8 *)((u8 *)*(u8 **)((u8 *)&D_800CC5EC + (arg0 * 0x32C)) + 0x75) = arg2;
}
typedef struct GameAD9B0Nested {
    u8 pad0[0x74];
    u8 field_74;
    u8 field_75;
} GameAD9B0Nested;

typedef struct GameAD9B0Actor {
    u8 pad0[0x31C];
    GameAD9B0Nested *nested;
    u8 pad320[0xC];
} GameAD9B0Actor;

extern GameAD9B0Actor D_800CC2D0[];

void func_150806A8(s32 arg0) {
    GameAD9B0Actor *actor;
    GameAD9B0Nested *nested;
    u8 value_74;
    u8 value_75;

    actor = &D_800CC2D0[arg0];
    nested = actor->nested;
    value_74 = nested->field_74;
    if ((value_74 != 0) && !(value_74 & 0x80)) {
        nested->field_74 = 0;
    }
    nested = actor->nested;
    value_75 = nested->field_75;
    if ((value_75 != 0) && !(value_75 & 0x80)) {
        nested->field_75 = 0;
    }
}
void func_15080718(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg2 = 1 << (arg0 & 7);
    *arg1 = arg0 >> 3;
}
extern u8 D_800BE580[];

s32 func_15080738(s32 arg0) {
    s32 sp1C;
    s32 sp18;

    func_15080718(arg0, &sp1C, &sp18);
    if (D_800BE580[sp1C] & sp18) {
        return 1;
    }
    return 0;
}
void func_1001263C(s32, s32, s32);
extern u8 D_800D1994;
extern u8 D_800D1995;
extern u16 *D_800D1998;

void func_15080784(void) {
    s32 value;

    if (D_800D1998 != 0) {
        if (D_800D1994 != D_800D1995) {
            value = D_800D1998[D_800D1994];
            if (value != 0) {
                func_1001263C(value, 0x7FFF, 0x40);
            }
            D_800D1994++;
        }
    }
}

void func_150807F4(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 0x20) {
        func_15080784();
    }
}
typedef struct GameAD9B0TextResource {
    void *text;
    u8 pad4[4];
    u16 *codes;
    u32 codeBytes;
} GameAD9B0TextResource;
typedef struct GameAD9B0TextDescriptor {
    u32 flags;
    void *text;
    u8 count;
    u8 pad9[0xF];
    f32 *x, *y, *z;
    s16 field24, field26;
    u8 red, green, blue, field2B;
    void (*callback)(s32, s32, s32);
} GameAD9B0TextDescriptor;

s32 func_10022EEC(void *);
void func_10023A10(void *, void *, s32);
void *func_10003C40(s32, s32, s32, s32);
void *func_1502B6BC(s32 *, s32, s32 *, s32, ...);
void *func_1516A7B0(s32, s32, s32, void (*)(s32, s32, s32), void *, s32);
extern u8 D_800D1941;
extern s32 D_800D1944;
extern void *D_800D1948;
extern s32 D_800D194C;
extern void *D_800D1950;
extern u8 D_800BEAAB, D_800D2E40, D_800D2E68;
extern GameAD9B0TextDescriptor D_800D1958;
extern f32 D_800D1988, D_800D198C, D_800D1990;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15080828 CURRENT (740) */
void func_15080828(s32 arg0) {
    void *text;
    s32 prepend;
    s32 firstLength;
    s32 secondLength;
    u32 codeBytes;
    s32 total;

    if (arg0 == 0) {
        if (!(D_800D2E68 & 0x10)) {
            prepend = 1;
        } else {
            prepend = 0;
        }
    } else {
        prepend = 0;
    }
    D_800D1944 = (s32)func_1502B6BC(0, 0, 0, 3, 0x1A, D_800BEAAB,
                                   (u8)D_800D1940);
    if (D_800D1944 != 0) {
        D_800D1994 = 0;
        D_800D1998 = ((GameAD9B0TextResource *)D_800D1944)->codes;
        D_800D1995 = ((GameAD9B0TextResource *)D_800D1944)->codeBytes >> 1;
        if (prepend != 0) {
            D_800D1948 = func_1502B6BC(0, 0, 0, 3, 0x1A, D_800BEAAB, 0x43);
            if (D_800D1944 == 0) {
                return;
            }
            firstLength = func_10022EEC(((GameAD9B0TextResource *)D_800D1948)->text) + 1;
            secondLength = func_10022EEC(((GameAD9B0TextResource *)D_800D1944)->text) + 1;
            D_800D194C = (s32)func_10003C40(firstLength + secondLength + 1, 1, 0, 0);
            func_10023A10(((GameAD9B0TextResource *)D_800D1948)->text,
                         (void *)D_800D194C, firstLength);
            ((u8 *)D_800D194C)[firstLength - 1] = 0xBD;
            func_10023A10(((GameAD9B0TextResource *)D_800D1944)->text,
                         (u8 *)D_800D194C + firstLength, secondLength);
            codeBytes = ((GameAD9B0TextResource *)D_800D1948)->codeBytes;
            total = (codeBytes >> 1) + D_800D1995;
            D_800D1998 = func_10003C40(total * 2, 1, 0, 0);
            func_10023A10(((GameAD9B0TextResource *)D_800D1948)->codes,
                         D_800D1998, (codeBytes >> 1) * 2);
            func_10023A10(((GameAD9B0TextResource *)D_800D1944)->codes,
                         D_800D1998 + (codeBytes >> 1), D_800D1995 * 2);
            D_800D1995 = total;
        } else {
            D_800D1948 = NULL;
        }
        D_800D1941 = 1;
        if (prepend != 0) {
            text = (void *)D_800D194C;
        } else {
            text = ((GameAD9B0TextResource *)D_800D1944)->text;
        }
        D_800D1958.flags = 0x38013;
        if ((prepend != 0 || arg0 != 0 ||
             !(D_800D2E60[(s32)(u8)D_800D1940 >> 3] & (1 << ((u8)D_800D1940 & 7)))) &&
            D_800D2E40 == 0) {
            D_800D1958.flags |= 0x60;
        }
        if (arg0 != 0 || (u8)D_800D1940 == 0x42) {
            D_800D1958.flags |= 0x80;
        }
        D_800D1958.text = text;
        D_800D1958.field26 = 100;
        D_800D1958.count = 1;
        D_800D1958.field24 = 0;
        D_800D1958.field2B = 0;
        D_800D1958.x = &D_800D1988;
        D_800D1958.y = &D_800D198C;
        D_800D1958.z = &D_800D1990;
        D_800D1958.red = 255;
        D_800D1958.green = 255;
        D_800D1958.blue = 255;
        D_800D1988 = 78.0f;
        D_800D198C = 48.0f;
        D_800D1990 = 9.0f;
        D_800D1950 = func_1516A7B0(0, 0, 0, func_150807F4, &D_800D1958, 0);
        *((u8 *)D_800D1950 + 0x14) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15080828 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080828.s")

void func_10004074(s32);
void func_151F2D6C(s32, s32);
extern void *D_800D199C;
extern u8 D_800D2E60[];
extern s32 D_800BE9F0;

void func_15080BE8(void) {
    D_800D1941 = 0;
    func_1516D2E0((void *)D_800D1950);
    func_10004074(D_800D1944);
    if ((void *)D_800D1948 != 0) {
        func_10004074((s32)D_800D1948);
        func_10004074(D_800D194C);
        func_10004074((s32)D_800D1998);
        D_800D1948 = 0;
    }
    func_151F2D6C(0, 0x5622);
}
void func_15080BE8(void);

void func_15080C64(void) {
    if ((D_800D1941 != 0) && (*(u8 *)((u8 *)D_800D1950 + 0x15) == 0)) {
        func_15080BE8();
        if ((D_800BE9F0 != 0x29) && (D_800BE9F0 != 0x2E)) {
            D_800D2E60[8] = (u8)(D_800D2E60[8] | 0x10);
        }
        if (D_800D199C != 0) {
            *(u8 *)((u8 *)D_800D199C + 0x14) = 1;
            D_800D199C = 0;
        }
    }
}

s32 func_15080CF4(void) {
    if (D_800D1941 == 0) {
        return 1;
    }
    return 0;
}
