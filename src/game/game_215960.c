#include "types.h"

/*
 * Reviewed source unit: src/game/game_215960.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151E86E4
 * - func_151E89A0
 * - func_151E966C
 * - func_151E9D18
 * - func_151EA15C
 * - func_151EADFC
 * - func_151EB06C
 * - func_151EB96C
 * - func_151EBB50
 * - func_151EC1F0
 * - func_151EC3E8
 * - func_151EC648
 * - func_151ED09C
 * - func_151ED1E0
 * - func_151ED29C
 * - func_151ED430
 * - func_151ED90C
 * - func_151EDBDC
 * - func_151EDF4C
 * - func_151EE184
 * - func_151EEBE8
 * - func_151EEFF0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Keep address symbols for linking and registered match evidence. */
#define ui_release_model_resources func_151EDB58

typedef void *(*Game215960Dispatch)(void *);
typedef struct {
    u8 pad0[0x1D0];
    s32 field_1D0;
} Game215960State;

void *func_151ED1E0(void *);
void func_15042D94(s32, s32, s32, s32);
void func_1504332C(s32, s32, s32, s32);
extern s32 D_8003C8E0;
extern s32 D_80000300;
extern s8 D_8008FD90;
extern Game215960Dispatch D_8008FFF4[];
extern u8 D_800BE616;
extern u8 D_800BE740;
extern s8 D_800E0BD3;
extern Game215960State *D_800E0BD8;
extern u8 D_800E0B94;

void *func_151E84B0(void *arg0) {
    s32 effect = 0;
    Game215960Dispatch callback;

    D_8003C8E0 = 0x09000001;
    arg0 = func_151ED1E0(arg0);
    callback = D_8008FFF4[D_800E0B94];
    if (callback != 0) {
        arg0 = callback(arg0);
    }
    if (D_80000300 != 0) {
        if ((D_800BE616 != 0) && (D_8008FD90 >= 2)) {
            if ((D_800BE740 & 0xF) == 0) {
                if (D_800E0BD3 == 1) {
                    effect = 0x33;
                } else if (D_800E0BD3 == 2) {
                    effect = 0x16;
                }
            }
        } else if ((D_800BE740 & 1) == 0) {
            if (D_800E0BD3 == 1) {
                effect = 0x32;
            } else if (D_800E0BD3 == 2) {
                effect = 0x15;
            }
        }
    }
    if (effect != 0) {
        func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
        func_15042D94(0x94, 0xC8, 0x81, ((s32 *)D_800E0BD8)[effect]);
    }
    D_8003C8E0 = 0;
    return arg0;
}
typedef s32 (*Game215960Callback)(s32, s32);

extern s32 D_8003C8E0;
extern Game215960Callback D_8008FFC0[];
extern s32 D_80090058;
extern u8 D_800BE9C0;
extern s32 D_800BE9C8[];
extern s32 D_800BEBA4;
extern u8 D_800E0B94;
extern s16 D_800E0C78;

s32 func_151E8620(s32 arg0) {
    Game215960Callback callback;
    s32 original;
    s32 result;
    u8 mode;

    mode = D_800E0B94;
    original = arg0;
    D_8003C8E0 = 0x09000000;
    callback = D_8008FFC0[mode];
    if (callback != 0) {
        arg0 = callback(arg0, (s32) callback);
    }
    if (D_800E0B94 != 0) {
        D_80090058 = 0;
        D_800E0C78 = 0;
    }
    D_8003C8E0 = 0;
    if (D_800BEBA4 < ((arg0 - D_800BE9C8[D_800BE9C0]) >> 3)) {
        result = 1;
    } else {
        result = 0;
    }
    if (result != 0) {
        return original;
    }
    return arg0;
}
extern f32 D_8008FE1C;
extern f32 D_8008FE20;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E86E4 CURRENT (5240) */
void *func_151E86E4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s16 var_t0;
    s16 var_t0_2;
    s16 var_t1;
    s16 var_t1_2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    s32 var_t1_3;
    s32 var_t2;
    s32 var_v0;
    s32 var_v0_2;
    typedef struct { u32 hi; u32 lo; } Packet;
    Packet *packet;
    Packet *second;
    Packet *third;

    if (D_8008FE1C != 1.0f) {
        arg1 = (s32) ((f32) arg1 * D_8008FE1C);
        arg3 = (s32) ((f32) arg3 * D_8008FE1C);
        arg2 = (s32) ((f32) arg2 * D_8008FE20);
        arg4 = (s32) ((f32) arg4 * D_8008FE20);
        arg8 = (s32) ((f32) arg8 / D_8008FE1C);
        arg9 = (s32) ((f32) arg9 / D_8008FE20);
    }
    packet = (Packet *)arg0;
    arg0 += sizeof(Packet);
    if ((s16) arg3 > 0) {
        var_t0 = (s16) arg3;
    } else {
        var_t0 = 0;
    }
    if ((s16) arg4 > 0) {
        var_t1 = (s16) arg4;
    } else {
        var_t1 = 0;
    }
    packet->hi = (s32) ((var_t1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
    if ((s16) arg1 > 0) {
        var_t0_2 = (s16) arg1;
    } else {
        var_t0_2 = 0;
    }
    if ((s16) arg2 > 0) {
        var_t1_2 = (s16) arg2;
    } else {
        var_t1_2 = 0;
    }
    packet->lo = (s32) ((var_t1_2 & 0xFFF) | ((arg5 & 7) << 0x18) | ((var_t0_2 & 0xFFF) << 0xC));
    second = (Packet *)arg0;
    second->hi = 0xE1000000;
    arg0 += sizeof(Packet);
    if ((s16) arg1 < 0) {
        if ((s16) arg8 < 0) {
            temp_t5 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t5 > 0) {
                var_t2 = temp_t5;
            } else {
                var_t2 = 0;
            }
        } else {
            var_v0 = 0;
            temp_t4 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t4 < 0) {
                var_v0 = temp_t4;
            }
            var_t2 = var_v0;
        }
    } else {
        var_t2 = 0;
    }
    if (arg2 < 0) {
        if ((s16) arg9 < 0) {
            temp_t7 = (s32) ((s16) arg2 * (s16) arg9) >> 7;
            if (temp_t7 > 0) {
                var_t1_3 = temp_t7;
            } else {
                var_t1_3 = 0;
            }
        } else {
            var_v0_2 = 0;
            temp_t6 = (s32) ((s16) arg2 * (s16) arg9) >> 7;
            if (temp_t6 < 0) {
                var_v0_2 = temp_t6;
            }
            var_t1_3 = var_v0_2;
        }
    } else {
        var_t1_3 = 0;
    }
    second->lo = (s32) (((arg7 - var_t1_3) & 0xFFFF) | ((arg6 - var_t2) << 0x10));
    third = (Packet *)arg0;
    third->hi = 0xF1000000;
    third->lo = (s32) ((arg8 << 0x10) | (arg9 & 0xFFFF));
    arg0 += sizeof(Packet);
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E86E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E86E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E89A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E966C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E9D18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EA15C.s")
typedef struct GameEADFCCommand { u32 upper; u32 lower; } GameEADFCCommand;
typedef struct GameEADFCPowers { s32 value[7]; } GameEADFCPowers;
extern GameEADFCPowers D_8009009C;
extern s32 D_80090074[];
s32 func_1510D0EC(s32, s32 *, s32, s32);
void *func_151E86E4(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151EADFC CURRENT (3192) */
void *func_151EADFC(GameEADFCCommand *arg0, s32 arg1, s32 arg2, s32 arg3) {
    GameEADFCPowers powers;
    s32 *cursor;
    s32 *first;
    s32 *textures;
    s32 digit;
    s32 divisor;
    s32 started;
    s32 texture;
    GameEADFCCommand *command;

    powers = D_8009009C;
    arg1 = (u32)arg1 << 2;
    arg2 = (u32)arg2 << 2;
    if (arg3 >= 10000000) arg3 = 9999999;
    started = 0;
    if (arg3 < 0) arg3 = 0;
    textures = D_80090074;
    first = powers.value;
    cursor = &powers.value[6];
    do {
        divisor = *cursor;
        digit = arg3 / divisor;
        arg3 %= divisor;
        if (digit > 0 || started != 0 || cursor == first) {
            started = 1;
            texture = func_1510D0EC(textures[digit], 0, 3, 0);
            if ((u32)texture != 0x80000000U) {
                command = arg0++;
                command->upper = 0xFD180000;
                command->lower = texture;
                command = arg0++;
                command->upper = 0xF5180000;
                command->lower = 0x07094250;
                command = arg0++;
                command->upper = 0xE6000000;
                command->lower = 0;
                command = arg0++;
                command->lower = 0x073FF000;
                command->upper = 0xF3000000;
                command = arg0++;
                command->upper = 0xE7000000;
                command->lower = 0;
                command = arg0++;
                command->upper = 0xF5181000;
                command->lower = 0x94250;
                command = arg0++;
                command->upper = 0xF2000000;
                command->lower = 0x7C07C;
                arg0 = func_151E86E4((u8 *)arg0, arg1, arg2,
                         (u32)arg1 + 0x80, (u32)arg2 + 0x80,
                         0, 0, 0, 0x400, 0x400);
            }
            arg1 = (u32)arg1 + 0x60;
        }
        cursor = (s32 *)((u32)cursor - 4);
    } while ((u32)cursor >= (u32)powers.value);
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151EADFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EADFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EB06C.s")
extern s16 D_8008FDCC;
extern s32 func_151EA15C(s32, s32, s16, s32);

s32 func_151EB930(s32 arg0) {
    if (D_8008FDCC != 0) {
        arg0 = func_151EA15C(arg0, 0x6A, D_8008FDCC, 0);
    }
    return arg0;
}
extern s16 D_800E0A80;
extern s32 D_800E0A90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151EB96C CURRENT (1254) */
s32 func_151EB96C(s32 arg0) {
    s32 count;
    s16 index;
    s16 alpha;
    s32 x;
    s32 firstX;
    u8 opacity;
    s32 spacing;
    u8 *text;

    if (D_800E0A80 < 0) {
        return arg0;
    }
    if (D_800E0A90 < 0x168) {
        alpha = D_800E0A90 * 4;
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
    } else {
        alpha = (0x1A9 - D_800E0A90) * 4;
        if (alpha < 0) {
            alpha = 0;
        }
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
    }
    index = D_800E0A80;
    count = 0;
    opacity = alpha & 0xFF;
    while (((u8 **)D_800E0BD8)[index][0] != 0x2A) {
        index++;
        count++;
    }
    if (count >= 0xE) {
        spacing = 0xB;
    } else {
        spacing = 0x11;
    }
    func_1504332C(0xFF, 0, 0, opacity & 0xFF);
    index = D_800E0A80;
    text = ((u8 **)D_800E0BD8)[index];
    x = (0xD0 - count * spacing) >> 1;
    firstX = x;
    while (text[0] != 0x2A) {
        func_15042D94(0x94, x, 1, (s32)text);
        func_1504332C(0xFF, 0xFF, 0xFF, opacity & 0xFF);
        if (x == firstX) {
            x += 0xC;
        }
        index++;
        text = ((u8 **)D_800E0BD8)[index];
        x += spacing;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151EB96C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EB96C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EBB50.s")

void func_15042D94(s32, s32, s32, s32);
void func_1504332C(s32, s32, s32, s32);
extern s32 D_800E0A90;
extern Game215960State *D_800E0BD8;

s32 func_151EC178(s32 arg0) {
    s32 alpha;

    if (D_800E0A90 >= 0x5DD) {
        alpha = D_800E0A90 - 0x5DC;
        alpha <<= 3;
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        func_1504332C(0xFF, 0xFF, 0xFF, alpha & 0xFF);
        func_15042D94(0xDC, 0x130, 1, D_800E0BD8->field_1D0);
    }
    return arg0;
}

typedef struct Game215960Command {
    u32 w0;
    u32 w1;
} Game215960Command;

/* Raw helper15096934 returns its incoming command pointer plus eight bytes. */
void *func_15096934(void *);
void *func_151ED430(void *, void *, s32, s32, s32, s32, f32, s32);
extern u8 D_80090028[];
extern u8 D_800917F8[];
extern u8 D_80091804[];
extern u8 D_80091810[];
extern s32 D_800BE9F0;
extern s32 D_800E0A74;
extern u8 D_800E0B97;
extern u8 D_800E0B96;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151EC1F0 CURRENT (655) */
Game215960Command *func_151EC1F0(Game215960Command *arg0) {
    s32 alpha;
    Game215960Command *command;

    command = arg0;
    if (D_800BE9F0 == 33) return arg0;
    arg0++;
    command->w0 = 0xDE000000;
    command->w1 = (u32)D_80090028;
    alpha = D_800E0A90;
    if (alpha >= 301) {
        alpha = 428 - alpha;
        alpha *= 2;
        if (alpha < 0) alpha = 0;
    } else {
        alpha = D_800E0A90 * 8;
        if (alpha >= 256) alpha = 255;
    }
    if (alpha != 0) {
        command = arg0++;
        command->w0 = 0xFB000000;
        command->w1 = (alpha & 255) | ~255;
        arg0 = func_151ED430(arg0, D_800917F8, 146, 99, 5, 6, 1.0f, 0);
    }
    command = arg0++;
    command->w0 = 0xFB000000;
    command->w1 = -1;
    command = func_151ED430(arg0, D_80091804, 146, 203, 5, 2, 1.0f, 0);
    command[0].w0 = 0xFCFFD3FF;
    command[0].w1 = 0xFFA6FF7F;
    command[1].w0 = 0xFB000000;
    command[1].w1 = D_800E0B97 | 0x20FF2000;
    arg0 = func_15096934(func_151ED430(command + 2, D_80091810, 146, 203, 5, 2, 1.0f, 0));
    alpha = 490 - D_800E0A74;
    if (alpha < 0) alpha = 0;
    else {
        alpha *= 16;
        if (alpha >= 256) alpha = 255;
    }
    D_800E0B96 = 255 - alpha;
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151EC1F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EC1F0.s")

typedef struct {
    f32 amount;
    u8 pad04[4];
    f32 transition;
    u8 pad0C[0x20];
    s8 selection;
    u8 pad2D[0x11];
    s8 mode;
} Game215960Menu;

typedef struct {
    s32 value;
    u8 id;
    u8 pad05[0xB];
} Game215960MenuOption;

extern Game215960Menu *D_8008FDD4;
extern s8 D_8008FEF8;
extern s32 D_80090060;
extern s32 D_800900BC[];
extern u8 D_800900D4;
extern u8 D_800BE3F8[];
extern s32 D_800BE9E4;
extern u8 D_800C35EA;
extern u8 D_800E0A95;
void *func_151EC648(void *);
void *func_151EE184(void *);
void *func_151EEBE8(void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151EC3E8 CURRENT (3247) */
Game215960Command *func_151EC3E8(Game215960Command *arg0) {
    s32 fade;
    s32 selection;
    s32 mode;
    Game215960Command *cursor;
    Game215960Command *command;
    Game215960Command *next;
    Game215960MenuOption *option;

    cursor = arg0;
    if (D_800C35EA == 1) {
        D_800900D4 = 0;
        return cursor;
    }
    fade = D_800900D4 + D_800BE9E4 * 4;
    if (fade >= 0x100) fade = 0xFF;
    D_800900D4 = fade;
    command = cursor++;
    command->w0 = 0xDE000000;
    command->w1 = (u32)D_80090028;
    mode = D_8008FDD4->mode;
    if (1 == mode) return func_151EC648(cursor);
    if (mode == 0) {
        selection = D_8008FDD4->selection;
        if (1 == selection && D_8008FEF8 != 0) {
            cursor = func_151EE184(cursor);
        } else {
            s32 alpha;
            alpha = (s32)((D_8008FDD4->amount - 0.5f) * 512.0f);
            if (alpha < 0) alpha = -alpha;
            if (alpha >= 0x100) alpha = 0xFF;
            if (D_800900D4 < alpha) alpha = D_800900D4;
            if (1 == selection) {
                alpha = (D_800E0A95 * alpha) >> 8;
                if (alpha >= 0xFE) alpha = 0xFF;
            }
            command = cursor++;
            command->w1 = (alpha & 0xFF) | ~0xFF;
            command->w0 = 0xFB000000;
            next = cursor;
            next->w0 = 0xEF002C3F;
            next->w1 = 0x00504244;
            cursor++;
            D_80090060 = D_800900BC[D_8008FDD4->selection];
            cursor = func_151ED430(cursor, &D_80090060, 0x94, 0x1E, 3, 1, 1.0f, 0);
        }
        if (D_8008FDD4->transition >= 0.5f) {
            selection = D_8008FDD4->selection;
            if (selection >= 3) {
                option = (Game215960MenuOption *)(D_800BE3F8 + selection * 0x10 - 0x28);
                if (option->value != -1) cursor = func_151EEBE8(cursor, option->id);
            }
        }
    }
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151EC3E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EC3E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EC648.s")
void *func_15096934(void *);
void *func_151ED430(void *, void *, s32, s32, s32, s32, f32, s32);
extern u8 D_80090028[];
extern u8 D_8009181C[];
extern u8 D_80091828[];
extern u8 D_800E0B97;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ED09C CURRENT (2769) */
void func_151ED09C(void *arg0) {
    s32 saved_alpha;
    s32 scaled;
    s32 alpha;
    u8 *command;
    u8 *result;

    *(u32 *)arg0 = 0xDE000000;
    *(void **)((u8 *)arg0 + 4) = D_80090028;
    command = (u8 *)arg0 + 8;
    scaled = D_800E0A90 * 4;
    alpha = scaled;
    if (scaled >= 0x100) {
        alpha = 0xFF;
    }
    *(u32 *)command = 0xFB000000;
    *(u32 *)(command + 4) = (alpha & 0xFF) | ~0xFF;
    saved_alpha = alpha;
    result = func_151ED430(command + 8, D_8009181C, 0x92, 0x6C,
                           8, 3, 1.0f, 0);
    *(u32 *)result = 0xE7000000;
    *(u32 *)(result + 4) = 0;
    *(u32 *)(result + 8) = 0xFCFFD3FF;
    *(u32 *)(result + 0xC) = 0xFFA6FF7F;
    *(u32 *)(result + 0x10) = 0xFB000000;
    *(u32 *)(result + 0x14) = (((D_800E0B97 * (saved_alpha + 1)) >> 8) & 0xFF) | 0xFF802000;
    func_15096934(func_151ED430(result + 0x18, D_80091828, 0x92, 0x6C,
                                  8, 3, 1.0f, 0));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ED09C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED09C.s")
void *func_1501A6CC(void *, s32, s32, s32, s32);
extern s32 D_800BE620;
extern s32 D_800BE624;
extern u8 D_800E0B96;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ED1E0 CURRENT (210) */
void *func_151ED1E0(void *arg0) {
    if (D_800E0B96 == 0) {
        return arg0;
    }
    {
        u32 *command = arg0;
        arg0 = command + 2;
        command[0] = 0xE7000000;
        command[1] = 0;
    }
    {
        u32 *command = arg0;
        arg0 = command + 2;
        command[0] = 0xEF082C3F;
        command[1] = 0x00504340;
    }
    {
        u32 *command = arg0;
        arg0 = command + 2;
        command[0] = 0xFCFFFFFF;
        command[1] = 0xFFFEFB7D;
    }
    {
        u32 *command = arg0;
        arg0 = command + 2;
        command[0] = 0xFB000000;
        command[1] = D_800E0B96;
    }
    return func_1501A6CC(arg0, 0, 0, D_800BE620, D_800BE624);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ED1E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED1E0.s")
extern u8 D_8009DEB0[];
extern u8 D_8009DEB4[];
extern u8 D_8009DEB8[];
extern u8 D_8009DEBC[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ED29C CURRENT (4255) */
void *func_151ED29C(u32 *arg0, u8 *arg1, s32 *arg2) {
    s32 temp_at;
    s32 temp_at_2;
    s32 temp_t2;
    s32 temp_t5;
    s32 temp_t6;
    s32 var_a2;
    s32 var_t1;
    s32 var_v0;
    u16 temp_t0;
    u16 temp_v1;
    u8 temp_a3;
    u8 temp_a3_2;
    u32 *cursor;

    temp_a3 = arg1[0xB];
    var_v0 = 1;
    var_t1 = 2;
    *arg2 = (D_8009DEB0[temp_a3] +
             (*(u16 *)(arg1 + 6) * *(u16 *)(arg1 + 8))) >>
            D_8009DEB4[temp_a3];
    temp_t0 = *(u16 *)(arg1 + 6);
    if (temp_t0 >= 3) {
        do {
            temp_t5 = var_t1 * 2;
            temp_at = temp_t5 < temp_t0;
            var_t1 = temp_t5;
            var_v0 += 1;
        } while (temp_at != 0);
        var_t1 = 2;
    }
    temp_v1 = *(u16 *)(arg1 + 8);
    var_a2 = 1;
    cursor = arg0;
    if (temp_v1 >= 3) {
        do {
            temp_t6 = var_t1 * 2;
            temp_at_2 = temp_t6 < temp_v1;
            var_t1 = temp_t6;
            var_a2 += 1;
        } while (temp_at_2 != 0);
    }
    cursor[0] = 0xE7000000;
    cursor[1] = 0;
    cursor += 2;
    temp_t2 = ((arg1[0xA] & 7) << 21) | 0xF5000000;
    cursor[0] = ((D_8009DEBC[arg1[0xB]] & 3) << 19) | temp_t2;
    cursor[1] = 0x07000000;
    cursor += 2;
    temp_a3_2 = arg1[0xB];
    cursor[0] = (((((D_8009DEB8[temp_a3_2] * *(u16 *)(arg1 + 6)) + 7) >> 3)
                & 0x1FF) << 9) | temp_t2 | ((temp_a3_2 & 3) << 19);
    cursor[1] = ((var_a2 & 0xF) << 14) | 0x80000 | 0x200 | ((var_v0 & 0xF) * 0x10);
    cursor += 2;
    cursor[0] = 0xF2000000;
    cursor[1] = ((((*(u16 *)(arg1 + 6) - 1) * 4) & 0xFFF) << 12) |
              (((*(u16 *)(arg1 + 8) - 1) * 4) & 0xFFF);
    cursor += 2;
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ED29C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED29C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED430.s")
typedef struct {
    u8 pad0[0x3E0];
    f32 *matrix0;
    f32 *matrix1;
} Game1ED90CActor;

typedef struct {
    Game215960Command **original;
    Game215960Command *copies[4];
    u8 count;
    u8 flags;
    u8 pad16[6];
    void *field1C;
    void *field20;
    Game1ED90CActor *actor;
    f32 matrix0[16];
    f32 matrix1[16];
} Game1ED90CObject;

s32 func_10003C40(s32, s32, s32, s32);
void func_10004074(s32);
s32 func_1503F62C(s32, s32, Game215960Command ***, u8 *, void **, void **, Game1ED90CActor **);
void func_150A7BC0(void *);
void func_1503F5B8(Game1ED90CActor *, s32, s32, f32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ED90C CURRENT (370) */
Game1ED90CObject *func_151ED90C(s32 arg0, s32 arg1, s32 arg2, f32 arg3) {
    Game1ED90CObject *object;
    f32 *matrix0;
    f32 *matrix1;
    s32 index;
    s32 offset;
    u8 *cursor;
    s32 size;
    u8 *cleanup;
    Game215960Command *scanSource;
    Game215960Command *source;
    Game215960Command *destination;
    u32 scanWord;
    u32 word;
    u32 opcode;

    object = (Game1ED90CObject *)func_10003C40(0xA8, 1, 0, 1);
    if (object == 0) {
        return 0;
    }
    object->flags = 1;
    if (func_1503F62C(arg0, arg1, &object->original, &object->count,
                       &object->field1C, &object->field20, &object->actor) != 0) {
        func_10004074((s32)object);
        return 0;
    }
    matrix0 = object->matrix0;
    func_150A7BC0(matrix0);
    matrix1 = object->matrix1;
    func_150A7BC0(matrix1);
    object->actor->matrix0 = matrix0;
    object->actor->matrix1 = matrix1;
    func_1503F5B8(object->actor, 1, arg2, arg3, 0.0f, 0);
    index = 0;
    offset = 0;
    cursor = (u8 *)object;
    if ((s32)object->count > 0) {
        do {
            size = 0;
            scanSource = *(Game215960Command **)((u8 *)object->original + offset);
            do {
                scanWord = scanSource->w0;
                scanSource++;
                size += 8;
            } while (((scanWord >> 24) & 0xFF) != 0xDF);
            destination = (Game215960Command *)func_10003C40(size, 1, 1, 1);
            *(Game215960Command **)(cursor + 4) = destination;
            if (destination == 0) {
                size = 0;
                if (index > 0) {
                    cleanup = (u8 *)object;
                    do {
                        func_10004074((s32)*(Game215960Command **)(cleanup + 4));
                        size++;
                        cleanup += 4;
                    } while (size != index);
                }
                func_10004074((s32)object);
                return 0;
            }
            index++;
            offset += 4;
            cursor += 4;
        } while (index < (s32)object->count);
        index = 0;
    }
    if ((s32)object->count > 0) {
        offset = 0;
        cursor = (u8 *)object;
        do {
            destination = *(Game215960Command **)(cursor + 4);
            source = *(Game215960Command **)((u8 *)object->original + offset);
            do {
                word = source->w0;
                source++;
                destination->w0 = word;
                opcode = (word >> 24) & 0xFF;
                destination->w1 = source[-1].w1;
                if (opcode == 0xEF) {
                    destination->w0 = word & 0xFFFEFFFF;
                    destination->w1 = 0x5041C8;
                }
                if (opcode == 0xFC) {
                    destination->w0 = 0;
                }
                destination++;
            } while (opcode != 0xDF);
            index++;
            offset += 4;
            cursor += 4;
        } while (index < (s32)object->count);
    }
    return object;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ED90C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED90C.s")
void func_100043B4(void *, s32);
void func_1503F7B8(s32);

/* Descriptive role: ui_release_model_resources.
 * Evidence: docs/evidence/model_resource_role_names.md.
 */
void ui_release_model_resources(void *uiModel) {
    s32 displayListIndex;
    void *displayListCursor;

    if (uiModel != 0) {
        func_1503F7B8(*(s32 *)((u8 *)uiModel + 0x24));
        func_100043B4(uiModel, 4);
        displayListIndex = 0;
        displayListCursor = uiModel;
        if ((s32) *(u8 *)((u8 *)uiModel + 0x14) > 0) {
            do {
                func_100043B4(*(void **)((u8 *)displayListCursor + 4), 4);
                displayListIndex += 1;
                displayListCursor = (void *)((u8 *)displayListCursor + 4);
            } while (displayListIndex < (s32) *(u8 *)((u8 *)uiModel + 0x14));
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EDBDC.s")
/* The 0x1A8 owner contains two text banks and thirty 12-byte resources. */
typedef struct {
    Game215960Command *commands;
} Game215960ResourceHeader;

typedef struct {
    Game215960Command *commands;
    Game215960ResourceHeader *allocation;
    void *dependencies;
} Game215960Resource;

typedef struct {
    u8 text[2][0x20];
    Game215960Resource resources[30];
} Game215960ResourceState;

typedef struct {
    s16 position[3];
    u16 flag;
    s16 texture[2];
    u8 color[4];
} Game215960Vertex;

s32 func_10003C40(s32, s32, s32, s32);
s32 func_1502B6BC(s32 *, s32, s32 *, s32, ...);
s32 func_1510CE60(s32, s32, s32, s32, void *);
extern Game215960Resource *D_80090138;
extern Game215960ResourceState *D_800E0C7C;
extern s8 D_800E0C80;
extern s8 D_800E0C81;
extern s8 D_800E0C82;
extern s8 D_800E0C83;
extern s8 D_800E0C84;

/* Descriptive role: ui_text_entry_key_models_load.
 * Loads bank-09 entries 453..482 into thirty 12-byte resource records and
 * initializes text-entry state and model commands. Per-model load results
 * are dereferenced without a local failure check.
 * Evidence: docs/evidence/text_entry_model_role_names.md.
 */
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151EDF4C CURRENT (611) */
void func_151EDF4C(void) {
    s32 resourceId;
    s32 index;
    Game215960ResourceHeader *resource;
    Game215960Command *command;
    Game215960Vertex *vertex;
    u32 opcode;

    D_80090138 = 0;
    D_800E0C7C = (Game215960ResourceState *)func_10003C40(0x1A8, 1, 0, 0);
    if (D_800E0C7C != 0) {
        D_80090138 = D_800E0C7C->resources;
        resourceId = 0x1C5;
        index = 0;
        do {
            resource = (Game215960ResourceHeader *)func_1502B6BC(0, 1, 0, 2, 9, resourceId);
            D_80090138[index].allocation = resource;
            D_80090138[index].commands = resource->commands;
            func_1510CE60((s32)D_80090138[index].commands, 0, 1, 0x3E,
                         &D_80090138[index].dependencies);
            command = D_80090138[index].commands;
            do {
                opcode = (command->w0 >> 24) & 0xFF;
                if (opcode == 1) {
                    command->w1 += (u32)resource;
                    vertex = (Game215960Vertex *)(command->w1 | 0x80000000U);
                    vertex->color[0] = 0;
                    vertex->color[1] = 0;
                    vertex->color[2] = 0;
                    vertex->color[3] = 0xFF;
                    vertex++;
                    vertex->color[0] = 0;
                    vertex->color[1] = 0;
                    vertex->color[2] = 0;
                    vertex->color[3] = 0xFF;
                }
                if (opcode == 0xFC) {
                    command->w0 = 0xFC127E05;
                    command->w1 = 0xFFFFF3F8;
                }
                if (opcode == 0xEF) {
                    command->w0 |= 0x100000;
                    command->w1 = 0x0F0A4000;
                }
                command++;
            } while (opcode != 0xDF);
            resourceId++;
            index++;
        } while (resourceId != 0x1E3);
        D_800E0C80 = 0;
        D_800E0C81 = 0;
        D_800E0C82 = 0;
        D_800E0C83 = 0;
        D_800E0C7C->text[0][0] = 0;
        D_800E0C7C->text[1][0] = 0;
        D_800E0C84 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151EDF4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EDF4C.s")
/* Descriptive role: ui_text_entry_update_and_draw.
 * Updates selection/text, evaluates submitted text against loaded tables,
 * and submits all thirty key display lists with selected-key state.
 * Evidence: docs/evidence/text_entry_model_role_names.md.
 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EE184.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EEBE8.s")
extern s32 D_800E9D00;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151EEFF0 CURRENT (505) */
void func_151EEFF0(void) {
    volatile s32 zero = 0;

    D_800E9D00 = zero;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151EEFF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EEFF0.s")
