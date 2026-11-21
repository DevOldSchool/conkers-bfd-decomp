#include "types.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1AC2F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517F564
 * - func_1517FB9C
 * - func_15180580
 * - func_15181EE0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1AC2F0Color {
    u8 red;
    u8 green;
    u8 blue;
} Game1AC2F0Color;

extern Game1AC2F0Color D_800DDDA0[];
extern u8 D_800DDDC0[];
extern s8 D_800DDDAC[];
extern s32 D_800DDE28[];
extern s32 D_800DDDB0[];
void func_1517EE40(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 arg4, s32 arg5) {
    Game1AC2F0Color *temp_a0;
    s8 *temp_v0;

    temp_v0 = &D_800DDDAC[arg5];
    if ((arg4 != *temp_v0) || (D_800DDDB0[arg5] < D_800DDE28[arg5]) || (D_800DDDC0[arg5] != 0)) {
        temp_a0 = &D_800DDDA0[arg5];
        temp_a0->green = (u8)arg1;
        temp_a0->blue = (u8)arg2;
        temp_a0->red = (u8)arg0;
        D_800DDE28[arg5] = arg3;
        D_800DDDB0[arg5] = 0;
        *temp_v0 = arg4;
        D_800DDDC0[arg5] = 0;
    }
}

s32 func_1517EF00(s32 arg0) {
    s32 intensity;

    if (D_800DDDC0[arg0] != 0) {
        intensity = D_800DDDC0[arg0];
    } else {
        if (D_800DDE28[arg0] != 0) {
            intensity = (D_800DDDB0[arg0] * 0xFF) / D_800DDE28[arg0];
            intensity = (intensity < 0x100) ? intensity : 0xFF;
        } else {
            intensity = 0xFF;
        }
        if (D_800DDDAC[arg0] == 0) {
            intensity = 0xFF - intensity;
        }
    }
    return intensity;
}

s32 func_1517EF00(s32);

s32 func_1517EFAC(s32 arg0) {
    if (func_1517EF00(arg0) == 0xFF) {
        return 1;
    }
    return 0;
}
extern s32 D_80082FA0;
extern f32 D_800DDDC8[];

s32 func_1517EFDC(void) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;

    temp_v0 = D_80082FA0;
    var_s1 = -1;
    var_s0 = 0;
    if (temp_v0 >= 0) {
        do {
            if ((func_1517EF00(var_s0) > 0) || (D_800DDDC8[var_s0] > 0.0f)) {
                var_s1 += 1;
            }
            var_s0 += 1;
        } while ((temp_v0 = D_80082FA0) >= var_s0);
    }
    if (var_s1 == temp_v0) {
        return 1;
    }
    return 0;
}
typedef struct Game1AC2F0FillCommand {
    u32 word0;
    u32 word1;
} Game1AC2F0FillCommand;

typedef struct Game1AC2F0FillViewportPrefix {
    u8 unknown00[0x24];
    f32 top24;
    f32 bottom28;
    f32 left2C;
    f32 right30;
} Game1AC2F0FillViewportPrefix;

extern s32 D_800BE628;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
s32 func_1517F08C(s32 arg0, s32 alpha, s32 red, s32 green, s32 blue, s32 viewport_index) {
    { Game1AC2F0FillCommand *command = (Game1AC2F0FillCommand *)arg0; arg0 += sizeof(Game1AC2F0FillCommand); command->word0 = _SHIFTL(0xE7, 24, 8); command->word1 = 0; }
    { Game1AC2F0FillCommand *command = (Game1AC2F0FillCommand *)arg0; arg0 += sizeof(Game1AC2F0FillCommand); command->word0 = 0xFCFFFFFF; command->word1 = 0xFFFDF6FB; }
    { Game1AC2F0FillCommand *command = (Game1AC2F0FillCommand *)arg0; arg0 += sizeof(Game1AC2F0FillCommand); command->word0 = _SHIFTL(0xFA, 24, 8) | _SHIFTL(0, 8, 8) | _SHIFTL(0, 0, 8); command->word1 = _SHIFTL(red, 24, 8) | _SHIFTL(green, 16, 8) | _SHIFTL(blue, 8, 8) | _SHIFTL(alpha, 0, 8); }
    { Game1AC2F0FillCommand *command = (Game1AC2F0FillCommand *)arg0; arg0 += sizeof(Game1AC2F0FillCommand); command->word0 = 0xEF002CFF; command->word1 = 0x00504344; }
    { Game1AC2F0FillCommand *command = (Game1AC2F0FillCommand *)arg0; arg0 += sizeof(Game1AC2F0FillCommand); command->word0 = _SHIFTL(0xF6, 24, 8) | _SHIFTL(((Game1AC2F0FillViewportPrefix *)((u8 *)D_800BE628 + viewport_index * 0x180))->bottom28, 2, 10) | _SHIFTL(((Game1AC2F0FillViewportPrefix *)((u8 *)D_800BE628 + viewport_index * 0x180))->right30, 14, 10); command->word1 = _SHIFTL(((Game1AC2F0FillViewportPrefix *)((u8 *)D_800BE628 + viewport_index * 0x180))->top24, 2, 10) | _SHIFTL(((Game1AC2F0FillViewportPrefix *)((u8 *)D_800BE628 + viewport_index * 0x180))->left2C, 14, 10); }
    return arg0;
}

s32 func_1517F08C(s32, s32, s32, s32, s32, s32);

s32 func_1517F3A0(s32 arg0, s32 arg1) {
    s32 intensity;
    Game1AC2F0Color *color;

    intensity = func_1517EF00(arg1);
    if (intensity == 0) {
        return arg0;
    }
    color = &D_800DDDA0[arg1];
    return func_1517F08C(arg0, intensity, color->red, color->green,
                          color->blue, arg1);
}
extern s32 D_800BE9E4;

s32 func_1517F40C(s32 arg0) {
    if (D_800DDDB0[arg0] >= D_800DDE28[arg0]) {
        return 1;
    }
    return 0;
}
void func_1517F448(s32 arg0) {
    if (D_800DDDB0[arg0] != D_800DDE28[arg0]) {
        D_800DDDB0[arg0] += D_800BE9E4;
    }
}
extern Game1AC2F0Color D_800DDD90[];
extern s8 D_800DDD9C[];
extern u16 D_800DDE10[];

void func_1517F488(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Game1AC2F0Color *color = &D_800DDD90[arg5];

    color->red = arg0;
    color->green = arg1;
    color->blue = arg2;
    D_800DDD9C[arg5] = arg3;
    D_800DDE10[arg5] = arg4;
}
s32 func_1517F4D8(s32 arg0, s32 arg1) {
    s32 temp_a1;
    u8 *temp_v0;
    u8 *entry = (u8 *)D_800DDD9C + arg1;

    if (*(u16 *)((u8 *)D_800DDE10 + (arg1 * 2)) == 0) {
        return arg0;
    }
    temp_a1 = *entry;
    if (temp_a1 == 0) {
        return arg0;
    }
    temp_v0 = (u8 *)D_800DDD90 + (arg1 * 3);
    return func_1517F08C(arg0, (s32)temp_a1, temp_v0[0], temp_v0[1], temp_v0[2], arg1);
}
extern s8 D_800DDD88;
extern s8 D_800DDD89;
extern s8 D_800DDD8A;
extern s8 D_800DDD8B;
extern s8 D_800DDD8C;
extern s16 D_800DDE08;
extern u8 D_8008D010[][6];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F564 CURRENT (3177) */
s32 func_1517F564(s32 arg0) {
    f32 fraction;
    f32 scale;
    f32 red;
    f32 green;
    f32 blue;
    s32 intensity;
    u8 *colors;
    u8 red0;
    u8 green0;
    u8 blue0;

    if ((u16)D_800DDE08 == 0) {
        return arg0;
    }
    if ((u8)D_800DDD8B == 0) {
        return arg0;
    }
    intensity = (u8)D_800DDD8B;
    if ((u8)D_800DDD8C != 0) {
        scale = (func_15048A40((u8)D_800DDD89, intensity) + 1.0f) * 0.5f;
        intensity = (s32)((f32)(u8)D_800DDD8B * scale);
        fraction = 0.0f;
    }
    colors = D_8008D010[(u8)D_800DDD8A];
    red0 = colors[0];
    red = (f32)red0 + (f32)(colors[3] - red0) * fraction;
    green0 = colors[1];
    green = (f32)green0 + (f32)(colors[4] - green0) * fraction;
    blue0 = colors[2];
    blue = (f32)blue0 + (f32)(colors[5] - blue0) * fraction;
    return func_1517F08C(arg0, intensity, (s32)red, (s32)green, (s32)blue, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517F564 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F564.s")

void func_1517F720(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    D_800DDE08 = arg1;
    D_800DDD88 = arg2;
    D_800DDD89 = 0;
    D_800DDD8A = arg0;
    D_800DDD8B = arg3;
    D_800DDD8C = (s8) arg4;
}
extern s32 D_80082FA0;
extern s32 D_800BE9E4;

void func_1517F75C(void) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (D_800BE9E4 < D_800DDE10[i]) {
            D_800DDE10[i] -= D_800BE9E4;
        } else {
            D_800DDE10[i] = 0;
        }
    }
}
void func_1517F7B4(void) {
    u32 remaining;
    s32 elapsed;

    if ((u16) D_800DDE08 != 0) {
        elapsed = D_800BE9E4;
        remaining = (u16)D_800DDE08;
        if (elapsed < (s32)remaining) {
            D_800DDE08 = (u32)(u16) D_800DDE08 - (u32)elapsed;
        } else {
            D_800DDE08 = 0;
        }
        D_800DDD89 = (u32)(u8) D_800DDD89 + ((u32)(u8) D_800DDD88 * (u32)elapsed);
    }
}
typedef struct Game1AC2F0Viewport {
    u8 pad00[0xC];
    f32 halfWidth, halfHeight;
    u8 pad14[0x10];
    f32 offsetY;
    u8 pad28[4];
    f32 offsetX;
    u8 pad30[0x150];
} Game1AC2F0Viewport;
void func_150A7A00(void *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
extern u8 D_800D9D10[];
extern s32 D_800BE628;
extern u8 D_800DDDE8[];

void func_1517F814(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    Game1AC2F0Viewport *view;
    f32 *output;

    if (arg0 == 0) {
        func_150A7A00((void *)((u32)D_800D9D10 + ((u32)arg4 << 6)), arg1, arg2, arg3, &x, &y, &z, &w);
        if (w == 0.0f) {
            w = 1.0f;
        }
        view = (Game1AC2F0Viewport *)((u32)D_800BE628 + (u32)arg4 * 0x180U);
        x = (view->halfWidth * x) / w;
        y = (view->halfHeight * y) / w;
        x += view->halfWidth;
        y = view->halfHeight - y;
        x += view->offsetX;
        y += view->offsetY;
    } else {
        x = arg1;
        y = arg2;
        view = (Game1AC2F0Viewport *)((u32)D_800BE628 + (u32)arg4 * 0x180U);
    }
    if (x > 10000.0f) {
        x = 10000.0f;
    } else if (x < -10000.0f) {
        x = -10000.0f;
    }
    if (y > 10000.0f) {
        y = 10000.0f;
    } else if (y < -10000.0f) {
        y = -10000.0f;
    }
    output = (f32 *)(D_800DDDE8 + arg4 * 8);
    output[0] = x - view->halfWidth;
    output[1] = y - view->halfHeight;
}
extern s32 D_800BE628;

void *func_1517F9F4(Game1AC2F0FillCommand *arg0, s32 x1, s32 y1, s32 x2, s32 y2, s32 viewport_index) {
    s32 left;
    s32 bottom;
    s32 top;
    s32 right;
    s32 clamped;
    u8 *view;

    if (x2 < x1) {
        left = x1;
        x1 = x2;
        x2 = left;
    }
    if (y2 < y1) {
        left = y1;
        y1 = y2;
        y2 = left;
    }
    view = (u8 *)D_800BE628 + viewport_index * 0x180;
    left = (s32)*(f32 *)(view + 0x2C);
    top = (s32)*(f32 *)(view + 0x24);
    right = (s32)*(f32 *)(view + 0x30);
    bottom = (s32)*(f32 *)(view + 0x28);
    if ((y1 >= bottom) || (top >= y2) || (x1 >= right) || (left >= x2)) {
        return arg0;
    }
    clamped = x1 < left ? left : (right < x1 ? right : x1);
    x1 = clamped;
    clamped = y1 < top ? top : (bottom < y1 ? bottom : y1);
    y1 = clamped;
    clamped = x2 < left ? left : (right < x2 ? right : x2);
    x2 = clamped;
    clamped = y2 < top ? top : (bottom < y2 ? bottom : y2);
    { Game1AC2F0FillCommand *command = arg0++; command->word0 = _SHIFTL(0xF6, 24, 8) | _SHIFTL(x2, 14, 10) | _SHIFTL(clamped, 2, 10); command->word1 = _SHIFTL(x1, 14, 10) | _SHIFTL(y1, 2, 10); }
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517FB9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15180580.s")
typedef struct Game1AC2F0Mode {
    u8 unknown000[0x120];
    u8 state;
    u8 unknown121[3];
    s16 timer;
} Game1AC2F0Mode;

typedef struct Game1AC2F0Player {
    s32 kind;
    u8 unknown004[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 unknown020[0x130];
    f32 height;
    u8 unknown154[0x80];
    u8 *model;
    u8 unknown1D8[0x144];
    Game1AC2F0Mode *mode;
    u8 unknown320[0xC];
} Game1AC2F0Player;

void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
extern f32 D_800A7260[];
extern f32 D_800A7270[];
extern u8 D_800BE9B4;
extern Game1AC2F0Player D_800CC2D0[];
extern u8 D_800DDD70[];
extern u8 D_800DDD74[];
extern u16 D_800DDD80[];
extern f32 D_800DDDD8[];
extern s8 D_800DDE20[];
extern s8 D_800DDE3C;
f32 fabsf(f32);
#pragma intrinsic(fabsf)

void func_151814FC(void) {
    s32 i;
    Game1AC2F0Player *player;

    for (i = 0; i <= D_80082FA0; i++) {
        if ((u8)D_800DDE20[i] != 0) {

            player = &D_800CC2D0[i];
            D_800DDDC8[i] += D_800DDDD8[i] * D_800BE9E4;
            if (player->mode == NULL) {
                D_800DDDC8[i] = 1.0f;
            } else if (player->mode->state == 3) {
                if (D_800A7260[D_80082FA0] <= D_800DDDC8[i]) {
                    D_800DDDC8[i] = D_800A7260[D_80082FA0];
                    player->mode->state = 4;
                    D_800DDD70[i] = 30;
                    D_800DDD74[i] = 0;
                }
            } else if (player->mode->state == 4) {
                if (D_800DDD70[i]) {
                    f32 scale;

                    if (D_800DDD70[i] >= D_800BE9E4) {
                        D_800DDD70[i] -= D_800BE9E4;
                    } else {
                        D_800DDD70[i] = 0;
                    }
                    D_800DDD74[i] += D_800BE9E4 * 20;
                    if (D_800DDD70[i] < 30) {
                        scale = (D_800DDD70[i] * 0.01f) / 30.0f;
                    } else {
                        scale = 0.01f;
                    }
                    D_800DDDC8[i] = D_800A7260[D_80082FA0] + scale * func_15048A40(D_800DDD74[i]);
                } else {
                    D_800DDDC8[i] = D_800A7260[D_80082FA0];
                    player->mode->state = 5;
                }
            } else if (player->mode->state == 5) {
                D_800DDDC8[i] = D_800A7260[D_80082FA0];
            } else if (player->mode->state == 6) {
                D_800DDDD8[i] = 0.009f;
                if (D_800A7270[D_80082FA0] <= D_800DDDC8[i]) {
                    D_800DDDC8[i] = D_800A7270[D_80082FA0];
                    player->mode->state = 7;
                    player->mode->timer = 30;
                    D_800DDDD8[i] = 0.0f;
                }
            } else if (player->mode->state == 8) {
                D_800DDDD8[i] = 0.004f;
                if (D_800DDDC8[i] >= 1.0f) {
                    D_800DDDC8[i] = 1.0f;
                    player->mode->state = 9;
                }
            }
        } else if ((u8)(&D_800DDE3C)[i] != 0) {
            Game1AC2F0Player *player;
            f32 x;
            f32 y;
            f32 z;
            f32 prevX;
            f32 prevY;
            f32 rate;
            f32 diff;
            f32 step;
            s32 sign;

            player = &D_800CC2D0[i];
            D_800DDDC8[i] += D_800DDDD8[i] * D_800BE9E4;
            if (player->model != NULL) {
                u8 *model;
                f32 height;

                model = player->model;
                if (player->kind == 1) {
                    model += 0x300;
                }
                height = player->height * 40.0f;
                func_150A7960(model, 0.0f, height, 0.0f, &x, &y, &z);
            } else {
                x = player->x;
                y = player->y;
                z = player->z;
            }
            prevX = ((f32 *)(D_800DDDE8 + i * 8))[0];
            prevY = ((f32 *)(D_800DDDE8 + i * 8))[1];
            func_1517F814(0, x, y, z, i);
            x = ((f32 *)(D_800DDDE8 + i * 8))[0];
            y = ((f32 *)(D_800DDDE8 + i * 8))[1];
            if (D_800BE9B4 != 0) {
                rate = 1.0f;
            } else {
                rate = 0.05f;
            }
            diff = x - prevX;
            step = diff;
            if (fabsf(diff) > 15.0f) {
                sign = (diff < 0) ? -1 : 1;
                step = sign * 15.0f;
                prevX = x - step;
            }
            step *= rate;
            prevX += step;
            diff = y - prevY;
            step = diff;
            if (fabsf(diff) > 11.25f) {
                sign = (diff < 0) ? -1 : 1;
                step = sign * 11.25f;
                prevY = y - step;
            }
            step *= rate;
            prevY += step;
            ((f32 *)(D_800DDDE8 + i * 8))[0] = prevX;
            ((f32 *)(D_800DDDE8 + i * 8))[1] = prevY;
            if ((u8)(&D_800DDE3C)[i] == 1) {
                if (D_800DDDC8[i] <= 0.9f) {
                    D_800DDD70[i] = 30;
                    D_800DDDC8[i] = 0.9f;
                    D_800DDDD8[i] = 0.0f;
                    (&D_800DDE3C)[i] = 2;
                }
            } else if ((u8)(&D_800DDE3C)[i] == 2) {
                if (D_800DDD70[i]) {
                    f32 scale;

                    if (D_800DDD70[i] >= D_800BE9E4) {
                        D_800DDD70[i] -= D_800BE9E4;
                    } else {
                        D_800DDD70[i] = 0;
                    }
                    D_800DDD74[i] -= D_800BE9E4 * 20;
                    if (D_800DDD70[i] < 30) {
                        scale = (D_800DDD70[i] * 0.01f) / 30.0f;
                    } else {
                        scale = 0.01f;
                    }
                    D_800DDDC8[i] = func_15048A40(D_800DDD74[i]) * scale + 0.9f;
                } else {
                    D_800DDDC8[i] = 0.9f;
                    (&D_800DDE3C)[i] = 3;
                    D_800DDD80[i] = 60;
                }
            } else if ((u8)(&D_800DDE3C)[i] == 3) {
                if (D_800BE9E4 < D_800DDD80[i]) {
                    D_800DDD80[i] -= D_800BE9E4;
                } else {
                    (&D_800DDE3C)[i] = 4;
                    D_800DDDD8[i] = -0.009f;
                }
            } else if (D_800DDDC8[i] <= 0.0f) {
                (&D_800DDE3C)[i] = 0;
                D_800DDDC8[i] = 0.0f;
            }
        } else if (D_800DDDD8[i] != 0.0f) {
            f32 speed;

            speed = D_800DDDD8[i];
            if (speed > 0.0f) {
                if (D_800DDDC8[i] >= 1.0f) {
                    D_800DDDD8[i] = 0.0f;
                    D_800DDDC8[i] = 1.0f;
                }
            } else if (D_800DDDC8[i] <= 0.0f) {
                D_800DDDD8[i] = 0.0f;
                D_800DDDC8[i] = 0.0f;
            }
            D_800DDDC8[i] += D_800DDDD8[i] * D_800BE9E4;
        }
    }
}
extern f32 D_800DDDC8[];

s32 func_15181CC8(s32 arg0) {
    if (D_800DDDC8[arg0] == 0.0f) {
        return 1;
    }
    return 0;
}
typedef struct Game1AC2F0Vector {
    f32 field_0;
    f32 field_4;
} Game1AC2F0Vector;

extern f32 D_800A72AC;
extern f32 D_800DDDD8[];
extern u8 D_800DDDE8[];
extern s8 D_800DDE1C[];

void func_15181D00(s32 arg0, s32 arg1) {
    Game1AC2F0Vector *vector;

    if (arg1 == 0) {
        D_800DDDC8[arg0] = 0.0f;
    } else {
        D_800DDDD8[arg0] = 0.0f;
        vector = (Game1AC2F0Vector *)(D_800DDDE8 + (arg0 * 8));
        D_800DDDC8[arg0] = D_800A72AC;
        vector->field_0 = 0.0f;
        vector->field_4 = 0.0f;
    }
    D_800DDE1C[arg0] = arg1;
}
extern f32 D_800A72B0;
extern f32 D_800DDDD8[];
extern f32 D_800DDDC8[];
extern u8 D_800DDDE8[];
extern s8 D_800DDE20[];

void func_15181D70(s32 arg0) {
    void *temp_v1;

    D_800DDDD8[arg0] = D_800A72B0;
    D_800DDDC8[arg0] = 0.0f;
    temp_v1 = D_800DDDE8 + (arg0 * 8);
    *(f32 *)temp_v1 = 0.0f;
    *(f32 *)((u8 *)temp_v1 + 4) = 0.0f;
    D_800DDE20[arg0] = 1;
}
extern f32 D_800DDDD8[];
extern u8 D_800DDDE8[];
extern s8 D_800DDE20[];

void func_15181DC8(s32 arg0) {
    f32 temp_ft0;
    f32 *pair;

    temp_ft0 = 0.0f;
    D_800DDDD8[arg0] = 0;
    D_800DDDC8[arg0] = temp_ft0;
    pair = (f32 *)(D_800DDDE8 + arg0 * 8);
    pair[0] = temp_ft0;
    pair[1] = temp_ft0;
    D_800DDE20[arg0] = 0;
}
extern f32 D_800A72B4;
extern u8 D_800BE616;
extern s8 D_800DDE3C;

void func_15181E18(s32 arg0) {
    Game1AC2F0Color *temp_v0;
    void *temp_v0_2;

    if (D_800BE616 != 0) {
        temp_v0 = &D_800DDDA0[arg0];
        temp_v0->red = 0;
        temp_v0->green = 0;
        temp_v0->blue = 0;
        D_800DDE28[arg0] = 0x19;
        D_800DDDB0[arg0] = 0;
        D_800DDDAC[arg0] = 0;
        D_800DDDC0[arg0] = 0;
        return;
    }
    *(&D_800DDE3C + arg0) = 1;
    D_800DDDC8[arg0] = 1.0f;
    temp_v0_2 = (arg0 * 8) + D_800DDDE8;
    *(f32 *)((u8 *)temp_v0_2 + 0) = 0.0f;
    *(f32 *)((u8 *)temp_v0_2 + 4) = 0.0f;
    D_800DDDD8[arg0] = D_800A72B4;
}
typedef struct Game1AC2F0RectView {
    u8 unknown00[4];
    f32 width;
    f32 field08;
    u8 unknown0C[0x18];
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
} Game1AC2F0RectView;

s32 func_1510D0EC(s32, s32 *, s32, s32);
extern s32 D_800902C8;
extern s32 D_800902CC;
extern f32 D_800A72B8;
extern f32 D_800A72BC;
extern f32 D_800A72C0;
extern f32 *D_800DDE18;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15181EE0 CURRENT (8017) */
Gfx *func_15181EE0(Gfx *gdl) {
    f32 topf;
    s16 left;
    s16 bottom;
    s16 right;
    s32 y1;
    s32 y2;
    s32 dsdx;
    f32 alpha;

    if (D_800DDE18 == NULL) {
        return gdl;
    }
    alpha = *D_800DDE18 * D_800A72B8;
    alpha = (alpha < 0.0f) ? 0.0f : ((alpha > 1.0f) ? 1.0f : alpha);
    if (alpha == 0.0f) {
        return gdl;
    }
    gDPPipeSync(gdl++);
    gDPSetFillColor(gdl++, 0x10001);
    gSPClearGeometryMode(gdl++, G_ZBUFFER | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD);
    gSPSetGeometryMode(gdl++, G_SHADE | G_SHADING_SMOOTH);
    gDPSetOtherMode(gdl++, 0x302C0F, 4);
    bottom = ((Game1AC2F0RectView *)D_800BE628)->bottom;
    left = ((Game1AC2F0RectView *)D_800BE628)->left;
    topf = ((Game1AC2F0RectView *)D_800BE628)->top;
    right = ((Game1AC2F0RectView *)D_800BE628)->right;
    y1 = (topf - 30.0f) +
         ((((Game1AC2F0RectView *)D_800BE628)->field08 * D_800A72BC) + 30.0f) * alpha;
    gdl = func_1517F9F4((Game1AC2F0FillCommand *)gdl, left, (s16)topf, right, (s16)y1, 0);
    y2 = (((Game1AC2F0RectView *)D_800BE628)->bottom + 30.0f) -
         ((((Game1AC2F0RectView *)D_800BE628)->field08 * (1.0f - D_800A72C0)) + 30.0f) * alpha;
    gdl = func_1517F9F4((Game1AC2F0FillCommand *)gdl, left, (s16)y2, right, bottom, 0);
    gDPPipeSync(gdl++);
    gSPTexture(gdl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetOtherMode(gdl++, 0x2CFF, 0x5011C4);
    gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFFF3F9);
    gDPSetTextureImage(gdl++, G_IM_FMT_I, G_IM_SIZ_16b, 1, func_1510D0EC(D_800902C8, NULL, 3, 0));
    gDPSetTile(gdl++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
    gDPLoadBlock(gdl++, G_TX_LOADTILE, 0, 0, 0x7FF, 0);
    gDPSetTile(gdl++, G_IM_FMT_I, G_IM_SIZ_4b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 7, G_TX_NOLOD, G_TX_CLAMP, 7, G_TX_NOLOD);
    gDPSetTileSize(gdl++, G_TX_RENDERTILE, 2, 2, 0x1FE, 0xFE);
    dsdx = (128.0f / ((Game1AC2F0RectView *)D_800BE628)->width) * 1024.0f;
    gSPScisTextureRectangle(gdl++, left << 2, (s16)y1 << 2, right << 2, (s16)(y1 + 30) << 2, G_TX_RENDERTILE, 0, 0, dsdx, 0x222);
    gDPSetTextureImage(gdl++, G_IM_FMT_I, G_IM_SIZ_16b, 1, func_1510D0EC(D_800902CC, NULL, 3, 0));
    gDPSetTile(gdl++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
    gDPLoadBlock(gdl++, G_TX_LOADTILE, 0, 0, 0x7FF, 0);
    gDPSetTile(gdl++, G_IM_FMT_I, G_IM_SIZ_4b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 7, G_TX_NOLOD, G_TX_CLAMP, 7, G_TX_NOLOD);
    gDPSetTileSize(gdl++, G_TX_RENDERTILE, 2, 2, 0x1FE, 0xFE);
    gSPScisTextureRectangle(gdl++, left << 2, (s16)(y2 - 30) << 2, right << 2, (s16)y2 << 2, G_TX_RENDERTILE, 0, 0, dsdx, 0x222);
    gSPSetGeometryMode(gdl++, G_ZBUFFER);
    return gdl;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15181EE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181EE0.s")
void *func_10022EC0(void *, const void *, u32);

void func_15182670(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4,
                   u8 arg5, u8 arg6, s32 arg7) {
    void *result;
    struct {
        u8 value0;
        u8 value1;
        u8 value2;
        u8 value3;
        u8 value4;
        s16 quotient;
    } payload;

    if (arg4 <= 0) {
        return;
    }
    payload.value0 = arg0;
    payload.value1 = arg1;
    payload.value2 = arg2;
    payload.value3 = arg3;
    payload.value4 = arg5;
    payload.quotient = arg3 / arg4;
    result = func_15149130(arg4, -1, 0x39, 3, 1, 0, 8, arg6, arg7);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x28, &payload, 8);
    }
}
typedef struct Game1AC2F0Object {
    u8 pad0[0xE];
    s16 field_E;
    u8 pad10[0x1B];
    s8 field_2B;
    u8 pad2C[2];
    s16 field_2E;
} Game1AC2F0Object;

void func_15182748(Game1AC2F0Object *arg0) {
    arg0->field_2B = arg0->field_2E * arg0->field_E;
}
s32 func_1517F08C(s32, s32, s32, s32, s32, s32);  /* extern */

s32 func_15182768(s32 arg0, u8 *arg1, s16 arg2) {
    u8 *temp_v0;

    temp_v0 = (void *)(arg1 + 0x28);
    if (arg2 == *(u8 *)((u8 *)arg1 + 0x2C)) {
        arg0 = func_1517F08C(arg0, *(u8 *)((u8 *)temp_v0 + 3),
                                *(u8 *)temp_v0,
                                *(u8 *)((u8 *)temp_v0 + 1),
                                (s32)*(u8 *)((u8 *)temp_v0 + 2),
                                (s32)*(u8 *)((u8 *)temp_v0 + 4));
    }
    return arg0;
}
