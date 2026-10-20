#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_BC510.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1508F060
 * - func_1508F0D4
 * - func_1508F9F4
 * - func_1508FD38
 * - func_150900F0
 * - func_15090630
 * - func_1509093C
 * - func_150911F4
 * - func_150918EC
 * - func_150938BC
 * - func_15093B58
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800D2460[][0x10];
extern s8 D_800D246D;
extern s8 D_800D247D;
extern s32 D_800D24C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508F060 CURRENT (20) */
void func_1508F060(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        D_800D2460[i][13] = 0;
    }
    D_800D24C0 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508F060 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F060.s")
void func_1508F9F4(void);

void func_1508F0A4(void) {
    func_1508F0D4();
    func_1508F9F4();
    func_1509093C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F0D4.s")
typedef struct GameBC510Node {
    u8 pad0[0x80];
    struct GameBC510Node *next;
    f32 field84[3];
    f32 field90[3];
    f32 field9C[3];
    f32 fieldA8[3];
    u8 fieldB4;
    u8 padB5[3];
} GameBC510Node;

void *func_10003C40(s32, s32, s32, s32);
void func_151EFEB8(void *, s32);
s32 func_1503E5F8(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern u8 D_800D2456;
extern GameBC510Node *D_800D245C;
extern u8 D_800BE9C0;
extern u8 D_800D2590[];
extern f32 D_800D2890[];

void func_1508F7BC(void) {
    f32 matrix[4][4];
    f32 unused;
    GameBC510Node *node;
    f32 value;

    D_800D2456--;
    D_800D2890[0] = (f32)(func_150ADA20() % 5U);
    value = D_800D2890[0];
    D_800D2890[2] = sqrtf(25.0f - value * value);
    node = func_10003C40(sizeof(*node), 1, 1, 0);
    node->next = D_800D245C;
    D_800D245C = node;
    func_151EFEB8(matrix, (s32)&D_800D2590[(D_800D2456 << 7) +
                                          ((D_800BE9C0 ^ 1) << 6)]);
    func_1503E5F8((u8 *)matrix, (s32)&node->field84[0],
                  (s32)&node->field84[1], (s32)&node->field84[2],
                  (s32)&node->field9C[0], (s32)&node->field9C[1],
                  (s32)&node->field9C[2], (s32)&unused, (s32)&unused,
                  (s32)&unused);
    node->field90[0] = (f32)((func_150ADA20() & 0xFU) + 10);
    node->field90[1] = (f32)((func_150ADA20() & 0x1FU) + 20);
    node->field90[2] = 0.0f;
    node->fieldA8[0] = (f32)(func_150ADA20() & 0xFU);
    node->fieldA8[1] = (f32)(func_150ADA20() & 0xFU);
    node->fieldA8[2] = (f32)(func_150ADA20() & 0xFU);
    node->fieldB4 = 0x78;
}
extern f32 D_800D2410[];
extern u8 D_800D2456;

void func_1508F9C4(void) {
    D_800D2410[D_800D2456] = 0.0f;
    D_800D2456 += 1;
}
typedef struct GameBC510Entry {
    s16 x;
    s16 y;
    s16 originX;
    s16 size;
    s16 radius;
    s16 timer;
    u8 acceleration;
    u8 state;
    u8 angle;
    u8 phase;
} GameBC510Entry;

extern u8 D_800CC2D0[];
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508F9F4 CURRENT (4979) */
void func_1508F9F4(void) {
    GameBC510Entry *entry;
    s32 timer;
    s32 enabled;
    s32 value;
    s32 duration;
    s32 i;
    s32 step;
    f32 wave;

    if (D_800D24C0 != 0) {
        timer = D_800D24C0 - D_800BE9E4;
        if (timer < 0) timer = 0;
        D_800D24C0 = timer;
    }
    if (D_800CC2D0[0xAD] != 0) {
        value = *(u16 *)(D_800CC2D0 + 0xB2);
    } else {
        value = 0;
    }
    /* The original leaves enabled and duration unset on some paths. */
    if (value >= 0x5B) {
        duration = value / 240;
        if (duration >= 7) duration = 6;
        duration = 6 - duration;
        duration *= 9;
        if (duration == 0) enabled = 0;
    } else {
        enabled = 0;
    }
    entry = (GameBC510Entry *)D_800D2460;
    do {
        if (entry->state == 2) {
            timer = entry->timer - D_800BE9E4;
            if (timer <= 0) {
                timer = 6;
                entry->state = 3;
            }
            entry->timer = timer;
        }
        switch (entry->state) {
        case 0:
            if (enabled != 0 && D_800D24C0 == 0) {
                D_800D24C0 = 10;
                entry->state = 1;
                entry->x = 0xFC;
                entry->y = 0x60;
                entry->size = 0;
                entry->acceleration = 0;
                value = func_150ADA20();
                entry->angle = value;
                entry->radius = 0x500;
                entry->originX = 0xFC - ((s32)(func_15048A40(value) * (f32)entry->radius) >> 8);
                entry->phase = 0;
                entry->timer = duration;
            }
            break;
        case 1:
            timer = entry->size + D_800BE9E4 * 200;
            if (timer >= 0x666) {
                entry->state = 2;
                timer = 0x666;
            }
            entry->size = timer;
            break;
        case 2:
            step = D_800BE9E4;
            value = entry->acceleration;
            i = 0;
            if (value < 0x20) {
                value += step;
                if (value >= 0x21) value = 0x20;
                entry->acceleration = value;
                value = (u8)value;
            }
            entry->y -= (step * value) >> 4;
            timer = entry->size;
            if (step > 0) {
                do {
                    i++;
                    timer = (timer * 0x104) >> 8;
                } while (i < step);
            }
            entry->size = timer;
            value = entry->angle + step * 5;
            entry->angle = value;
            entry->radius += step * 30;
            wave = func_15048A40(value) * (f32)entry->radius;
            entry->phase += D_800BE9E4 * 10;
            entry->x = ((s32)wave >> 8) + entry->originX;
            break;
        case 3:
            if (entry->timer == 0) entry->state = 0;
            break;
        }
        entry++;
    } while (entry != (GameBC510Entry *)&D_800D24C0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508F9F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F9F4.s")
typedef struct GameBC510Command {
    u32 w0;
    u32 w1;
} GameBC510Command;
GameBC510Command *func_150900F0(GameBC510Command *, s32);
GameBC510Command *func_150918EC(GameBC510Command *);
GameBC510Command *func_150938BC(GameBC510Command *);
GameBC510Command *func_15093B58(GameBC510Command *, s32, s16 *, s32, s32);
GameBC510Command *func_15090630(GameBC510Command *);
GameBC510Command *func_150911F4(GameBC510Command *);
void *func_15094F40(void *);
void *func_15096934(void *);
void func_1518CA04(s32);
extern u8 D_8008CD00, D_800BE616, D_800C35EA, D_800D2458;
extern f32 D_8008FE1C, D_800D2428;
extern s16 D_8009DCB4;
extern u16 D_800D2454;
extern s32 D_800BE9F0, D_800BEBA4, D_800D2588;
extern GameBC510Command *D_800BE9C8[];
extern u8 D_800D23D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508FD38 CURRENT (73) */
GameBC510Command *func_1508FD38(register GameBC510Command *arg0) {
    GameBC510Command *original;
    s32 index;
    s32 step;
    s32 overflow;
    s16 rows[33];

    original = arg0;
    if (D_800BE9F0 == 0x1D) return arg0;
    { GameBC510Command *packet0 = arg0++; packet0->w0 = 0xDB0E0000; packet0->w1 = D_800D2454; }
    { GameBC510Command *packet1 = arg0++; packet1->w0 = 0xDA380007; packet1->w1 = (u32)D_800D23D0; }
    if (D_800BE616 != 0) {
        arg0 = func_150918EC(arg0);
        overflow = D_800BEBA4 < arg0 - *(D_800BE9C8 + D_800BE9C0) ? 1 : 0;
        if (overflow != 0) return original;
        return arg0;
    }
    if (D_800D2458 != 0) arg0 = func_150938BC(arg0);
    if (D_800C35EA == 1) return arg0;
    if (D_8008CD00 != 0) {
        step = 0x400;
        if (D_8008FE1C != 1.0f) {
            step = (s32)((f32)step / D_8008FE1C);
            for (index = 0; index < 33; index++) *(rows + index) = (s32)((f32)index * D_8008FE1C);
        } else {
            for (index = 0; index < 33; index++) *(rows + index) = index;
        }
        arg0 = func_15093B58(arg0, step, rows, 0x2C30, 1);
    }
    if (D_800D2428 != (f32)D_8009DCB4) arg0 = func_150900F0(arg0, 0);
    else if (D_800D2588 != 0) {
        func_1518CA04(0xB8);
        D_800D2588 = 0;
    }
    arg0 = func_15096934(func_15090630(func_15094F40(func_150911F4(arg0))));
    overflow = D_800BEBA4 < arg0 - *(D_800BE9C8 + D_800BE9C0) ? 1 : 0;
    if (overflow != 0) return original;
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508FD38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508FD38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150900F0.s")

typedef struct GameBC510Sprite {
    u8 pad0[6];
    s16 width;
    s16 height;
    u8 alpha;
    u8 padB[2];
    u8 flags;
    u8 padE[2];
    void *texture;
} GameBC510Sprite;

s32 func_15095A48(s32, void *, f32, f32);
s32 func_1510D0EC(s32, s32 *, s32, s32);
s32 func_15094F70();
extern s32 D_800903D4;
extern s32 D_80091840;
extern f32 D_8009DD20;
extern f32 D_8009DD24;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15090630 CURRENT (2940) */
GameBC510Command *func_15090630(GameBC510Command *dl) {
    GameBC510Sprite sprite;
    f32 scaleY;
    f32 scaleX;
    GameBC510Entry *entry;
    s32 first;
    s32 loaded;
    f32 wave;
    f32 size;
    s16 x;
    s16 y;
    s32 flags;
    s32 remaining;

    sprite.alpha = 0xFF;
    sprite.flags = 0;
    {
        GameBC510Command *packet = dl;
        packet->w0 = 0xE7000000;
        packet->w1 = 0;
        dl++;
    }
    {
        GameBC510Command *packet = dl;
        packet->w0 = 0xFCFFB5FF;
        packet->w1 = 0xFFFCFE38;
        dl++;
    }
    {
        GameBC510Command *packet = dl;
        packet->w0 = 0xEF102C0F;
        packet->w1 = 0x0C184244;
        dl++;
    }
    scaleY = D_8009DD20;
    scaleX = D_8009DD24;
    first = 1;
    entry = (GameBC510Entry *)D_800D2460;
    do {
        if (entry->state == 1 || entry->state == 2) {
            if (first != 0) {
                first = 0;
                func_1510D0EC(D_80091840, &loaded, 3, 0);
                dl = (GameBC510Command *)func_15094F70((s32)dl, &D_800903D4,
                                                       0, &sprite, 0, 0, 0, 2, 3);
            }
            wave = func_15048A40(entry->phase);
            size = (f32)entry->size;
            x = entry->x;
            y = entry->y;
            sprite.width = (s32)(size * ((scaleX * wave) + 1.0f));
            sprite.height = (s32)(size * ((scaleY * wave) + 1.0f));
            dl = (GameBC510Command *)func_15095A48((s32)dl, &sprite, (f32)x, (f32)y);
        }
        entry++;
    } while ((u32)entry < (u32)&D_800D24C0);
    first = 1;
    entry = (GameBC510Entry *)D_800D2460;
    do {
        flags = 0;
        if (entry->state == 3) {
            sprite.width = entry->size;
            sprite.height = entry->size;
            x = entry->x;
            y = entry->y;
            if ((func_150ADA20() & 0xFFU) < 0x80U) {
                flags = 1;
            }
            if ((func_150ADA20() & 0xFFU) < 0x80U) {
                flags |= 2;
            }
            sprite.flags = flags;
            if (first != 0) {
                first = 0;
                dl = (GameBC510Command *)func_15094F70((s32)dl, &D_80091840,
                                                       0, &sprite, 0, 0, 0, 2, 3);
            }
            dl = (GameBC510Command *)func_15095A48((s32)dl, &sprite, (f32)x, (f32)y);
            remaining = entry->timer - D_800BE9E4;
            if (remaining < 0) {
                remaining = 0;
            }
            entry->timer = remaining;
        }
        entry++;
    } while (entry != (GameBC510Entry *)&D_800D24C0);
    return dl;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15090630 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15090630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1509093C.s")
void func_15043D90(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern u8 D_80083440[], D_800835C0[], D_80084160[], D_80084190[];
extern f32 D_8009DD40, D_8009DD44, D_8009DD48;

typedef struct GameBC510DisplayState {
    u8 matrices[0x80];
    u32 displayList;
    u32 buffers[2];
    u8 pad8C[0x14];
    f32 x, fieldA4, y;
    u8 padAC[4];
    u16 resources[4];
    u8 padB8[2];
    u8 alpha;
} GameBC510DisplayState;
extern u8 D_800D24C8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150911F4 CURRENT (2853) */
GameBC510Command *func_150911F4(GameBC510Command *dl) {
    s32 resource0, resource1, resource2, resource3;
    s32 address;
    s32 loaded;
    GameBC510DisplayState *state;

    state = (GameBC510DisplayState *)(u32)D_800D24C8;
    if (state->alpha == 0) {
        return dl;
    }
    { GameBC510Command *packet = dl++; packet->w0 = 0xDE000000; packet->w1 = (u32)D_80084160; }
    { GameBC510Command *packet = dl++; packet->w0 = 0xD9FFFFFF; packet->w1 = 0x400; }
    { GameBC510Command *packet = dl++; packet->w0 = 0xD9F1FDFE; packet->w1 = 0; }
    { GameBC510Command *packet = dl++; packet->w0 = 0xD9BDFFFF; packet->w1 = 0; }
    if (state->alpha < 0xFF) {
        { GameBC510Command *packet = dl++; packet->w0 = 0xDB060020; packet->w1 = (u32)D_80083440; }
    } else {
        { GameBC510Command *packet = dl++; packet->w0 = 0xDB060020; packet->w1 = (u32)D_800835C0; }
    }
    func_15043D90((s32)(state->matrices + (D_800BE9C0 << 6)),
                  -1.0f - state->x, -11.0f + state->y, 0.0f,
                  D_8009DD40, D_8009DD40, D_8009DD40,
                  D_8009DD44, 152.0f, D_8009DD48);
    { GameBC510Command *packet = dl++; packet->w0 = 0xDA380003; packet->w1 = (u32)(state->matrices + (D_800BE9C0 << 6)); }
    { GameBC510Command *packet = dl++; packet->w0 = 0xF8000000; packet->w1 = 0xFF; }
    { GameBC510Command *packet = dl++; packet->w0 = 0xFA00F200; packet->w1 = 0; }
    { GameBC510Command *packet = dl++; packet->w0 = 0xFB000000; packet->w1 = state->alpha; }
    { GameBC510Command *packet = dl++; packet->w0 = 0xDB06000C; packet->w1 = (u32)(state->matrices + (D_800BE9C0 << 6)); }
    { GameBC510Command *packet = dl++; packet->w0 = 0xDB060004; packet->w1 = state->buffers[D_800BE9C0]; }
    resource0 = state->resources[0];
    if (resource0 != 0) {
        address = func_1510D0EC(resource0, &loaded, 3, 0);
        { GameBC510Command *packet = dl++; packet->w0 = 0xdb060018; packet->w1 = address; }
    }
    resource1 = state->resources[1];
    if (resource1 != 0) {
        address = func_1510D0EC(resource1, &loaded, 3, 0);
        { GameBC510Command *packet = dl++; packet->w0 = 0xdb06001c; packet->w1 = address; }
    }
    resource2 = state->resources[2];
    if (resource2 != 0) {
        address = func_1510D0EC(resource2, &loaded, 3, 0);
        { GameBC510Command *packet = dl++; packet->w0 = 0xdb060028; packet->w1 = address; }
    }
    resource3 = state->resources[3];
    if (resource3 != 0) {
        address = func_1510D0EC(resource3, &loaded, 3, 0);
        { GameBC510Command *packet = dl++; packet->w0 = 0xdb06002c; packet->w1 = address; }
    }
    { GameBC510Command *packet = dl++; packet->w0 = 0xDE000000; packet->w1 = state->displayList; }
    { GameBC510Command *packet = dl++; packet->w0 = 0xDE000000; packet->w1 = (u32)D_80084190; }
    return dl;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150911F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150911F4.s")
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern u8 D_D16;

GameBC510Command *func_15091534(GameBC510Command *arg0, s32 arg1, s8 *arg2) {
    s32 address;

    *arg2 = 0;
    address = func_1510D0EC((s32)&D_D16 + arg1, 0, 3, 0);
    if (address != 0x80000000) {
        { GameBC510Command *command = arg0++; command->w0 = 0xFD500000; command->w1 = address; }
        { GameBC510Command *command = arg0++; command->w0 = 0xF5500000; command->w1 = 0x07098260; }
        { GameBC510Command *command = arg0++; command->w0 = 0xE6000000; command->w1 = 0; }
        { GameBC510Command *command = arg0++; command->w0 = 0xF3000000; command->w1 = 0x073FF000; }
        { GameBC510Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
        { GameBC510Command *command = arg0++; command->w0 = 0xF5400800; command->w1 = 0x00098260; }
        { GameBC510Command *command = arg0++; command->w0 = 0xF2000000; command->w1 = 0x000FC0FC; }
        { GameBC510Command *command = arg0++; command->w0 = 0xFD100000; command->w1 = address + 0x800; }
        { GameBC510Command *command = arg0++; command->w0 = 0xE6000000; command->w1 = 0; }
        { GameBC510Command *command = arg0++; command->w0 = 0xF0000000; command->w1 = 0x0603C000; }
        { GameBC510Command *command = arg0++; command->w0 = 0xEF00AC3F; command->w1 = 0x00504244; }
        *arg2 = 1;
    }
    return arg0;
}
extern char D_8009DCC0[];
extern char D_8009DCC4[];
extern char D_8009DCCC[];
extern char D_8009DCD4[];
extern char D_8009DCD8[];
extern char D_8009DCE0[];

void func_150916B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 seconds;
    s32 minutes;
    s32 shift;
    s32 hundredths;
    s32 rem;

    if (arg2 >= 0x57030) {
        arg2 = 0x57030;
    }
    hundredths = ((arg2 % 60) * 100) / 60;
    if (hundredths >= 100) {
        hundredths = 99;
    }
    arg0 -= 8;
    if (arg2 >= 0) {
        seconds = arg2 / 60;
        minutes = seconds / 60;
        if (minutes >= 10) {
            shift = 5;
        } else {
            shift = 0;
        }
        func_15042D94(arg0 - shift - 8, arg1, arg3, (s32)D_8009DCC0, minutes);
        rem = seconds % 60;
        func_15042D94(arg0, arg1, arg3, (s32)D_8009DCC4, rem);
        func_15042D94(arg0 + 0x10, arg1, arg3, (s32)D_8009DCCC, hundredths);
    } else {
        func_15042D94(arg0 - 8, arg1, arg3, (s32)D_8009DCD4);
        func_15042D94(arg0, arg1, arg3, (s32)D_8009DCD8);
        func_15042D94(arg0 + 0x10, arg1, arg3, (s32)D_8009DCE0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150918EC.s")
/* Call context: func_15093878: unique active project prototype */
void func_15093878(void);
extern u8 D_800D2458;

/* Descriptive role: timer_display_set_enabled.
 * Evidence: docs/evidence/assets/naming/model_resource_role_names.md.
 */
void func_15093818(s32 enabled) {
    if ((enabled != 0) && (D_800D2458 == 0)) {
        D_800D2458 = 1;
        func_15093878();
        return;
    }
    if ((enabled == 0) && (D_800D2458 != 0)) {
        D_800D2458 = 0;
    }
}
extern void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_1518C900(s32 arg0);
extern s32 D_800D2448;
extern void *D_800D244C;

/* Descriptive role: timer_display_init.
 * Evidence: docs/evidence/assets/naming/model_resource_role_names.md.
 */
void func_15093878(void) {
    D_800D2448 = func_1518C900(0xBA);
    D_800D244C = func_10003C40(0x80, 1, 1, 0);
}
void func_150A7D00(volatile s64 *, f32, f32, f32);
extern u8 D_11AD;
extern s32 D_800D2450;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150938BC CURRENT (2020) */
GameBC510Command *func_150938BC(GameBC510Command *dl) {
    s32 digit;
    s32 value;
    s32 address;

    digit = 4;
    value = (D_800D2450 / 30) % 60;
    do {
        address = func_1510D0EC((s32)&D_11AD + value % 10, 0, 3, 0);
        if (address == 0x80000000) {
            return dl;
        }
        { GameBC510Command *packet = dl++; packet->w0 = _SHIFTL(0xDB, 24, 8) | _SHIFTL(6, 16, 8) | _SHIFTL(digit * 4, 0, 16); packet->w1 = address; }
        if (digit == 3) {
            value = (D_800D2450 / 30) / 60;
        } else {
            value /= 10;
        }
        digit--;
    } while (digit != 0);
    func_150A7D00((volatile s64 *)((u8 *)D_800D244C + (D_800BE9C0 << 6)), (f32)0x78, (f32)0x81, (f32)-0x12F);
    { GameBC510Command *packet = dl++; packet->w0 = 0xDA380003; packet->w1 = (u32)((u8 *)D_800D244C + (D_800BE9C0 << 6)); }
    { GameBC510Command *packet = dl++; packet->w0 = 0xDE000000; packet->w1 = D_800D2448; }
    return dl;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150938BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150938BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15093B58.s")
