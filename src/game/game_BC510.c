#include "types.h"

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
 * - func_15091534
 * - func_150916B4
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508F060 CURRENT (625) */
void func_1508F060(void) {
    s32 temp_v0;
    u8 *temp_v1;

    D_800D246D = 0;
    D_800D247D = 0;
    temp_v0 = 2;
    temp_v1 = D_800D2460[temp_v0];
    temp_v1[0x1D] = 0;
    temp_v1[0x2D] = 0;
    temp_v1[0x3D] = 0;
    temp_v1[0xD] = 0;
    D_800D24C0 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508F060 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F060.s")
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

u32 func_150ADA20(void);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F9F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508FD38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150900F0.s")
typedef struct GameBC510Command {
    u32 w0;
    u32 w1;
} GameBC510Command;

typedef struct GameBC510Entry {
    s16 x;
    s16 y;
    u8 pad4[2];
    s16 size;
    u8 pad8[2];
    s16 timer;
    u8 padC;
    u8 state;
    u8 padE;
    u8 phase;
} GameBC510Entry;

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

f32 func_15048A40(u8);
s32 func_15095A48(s32, void *, f32, f32);
s32 func_1510D0EC(s32, s32 *, s32, s32);
s32 func_15094F70(s32, void *, s32, void *, s32, s32, s32, s32, s32);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150911F4.s")
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern u8 D_D16;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15091534 CURRENT (6295) */
void *func_15091534(void *arg0, s32 arg1, s8 *arg2) {
    u8 *cursor = arg0;
    u8 *next;
    s32 address;

    *arg2 = 0;
    address = func_1510D0EC((s32)&D_D16 + arg1, 0, 3, 0);
    if (address != 0x80000000) {
        *(u32 *)cursor = 0xFD500000;
        *(u32 *)(cursor + 4) = address;
        next = cursor + 8;
        *(u32 *)(cursor + 8) = 0xF5500000;
        *(u32 *)(next + 4) = 0x07098260;
        cursor = next + 8;
        *(u32 *)(next + 8) = 0xE6000000;
        *(u32 *)(cursor + 4) = 0;
        next = cursor + 8;
        *(u32 *)(cursor + 8) = 0xF3000000;
        *(u32 *)(next + 4) = 0x073FF000;
        cursor = next + 8;
        *(u32 *)(next + 8) = 0xE7000000;
        *(u32 *)(cursor + 4) = 0;
        next = cursor + 8;
        *(u32 *)(cursor + 8) = 0xF5400800;
        *(u32 *)(next + 4) = 0x00098260;
        cursor = next + 8;
        *(u32 *)(next + 8) = 0xF2000000;
        *(u32 *)(cursor + 4) = 0x000FC0FC;
        next = cursor + 8;
        *(u32 *)(next + 4) = address + 0x800;
        *(u32 *)(cursor + 8) = 0xFD100000;
        cursor = next + 8;
        *(u32 *)(next + 8) = 0xE6000000;
        *(u32 *)(cursor + 4) = 0;
        next = cursor + 8;
        *(u32 *)(cursor + 8) = 0xF0000000;
        *(u32 *)(next + 4) = 0x0603C000;
        cursor = next + 8;
        *(u32 *)(next + 8) = 0xEF00AC3F;
        *(u32 *)(cursor + 4) = 0x00504244;
        cursor += 8;
        *arg2 = 1;
    }
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15091534 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15091534.s")
void func_15042D94(s32, s32, u8, s32, ...);
extern char D_8009DCC0[];
extern char D_8009DCC4[];
extern char D_8009DCCC[];
extern char D_8009DCD4[];
extern char D_8009DCD8[];
extern char D_8009DCE0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150916B4 CURRENT (8) */
void func_150916B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 seconds;
    s32 minutes;
    s32 shift;
    s32 hundredths;

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
        func_15042D94(arg0, arg1, arg3, (s32)D_8009DCC4, seconds % 60);
        func_15042D94(arg0 + 0x10, arg1, arg3, (s32)D_8009DCCC, hundredths);
    } else {
        func_15042D94(arg0 - 8, arg1, arg3, (s32)D_8009DCD4);
        func_15042D94(arg0, arg1, arg3, (s32)D_8009DCD8);
        func_15042D94(arg0 + 0x10, arg1, arg3, (s32)D_8009DCE0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150916B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150916B4.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150938BC CURRENT (2285) */
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
        {
            GameBC510Command *packet = dl;
            packet->w0 = 0xDB060000 | ((digit * 4) & 0xFFFF);
            dl++;
            packet->w1 = address;
        }
        if (digit == 3) {
            value = (D_800D2450 / 30) / 60;
        } else {
            value /= 10;
        }
        digit--;
    } while (digit != 0);
    func_150A7D00((volatile s64 *)((u8 *)D_800D244C + (D_800BE9C0 << 6)),
                  (f32)0x78, (f32)0x81, (f32)-0x12F);
    {
        GameBC510Command *packet = dl++;
        packet->w0 = 0xDA380003;
        packet->w1 = (u32)((u8 *)D_800D244C + (D_800BE9C0 << 6));
    }
    {
        GameBC510Command *packet = dl++;
        packet->w0 = 0xDE000000;
        packet->w1 = D_800D2448;
    }
    return dl;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150938BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150938BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15093B58.s")
