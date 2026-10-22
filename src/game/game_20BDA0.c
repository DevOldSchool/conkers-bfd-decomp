#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_20BDA0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dispatch_controller_core.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151DE8F0
 * - func_151DF1BC
 * - func_151DF574
 * - func_151DFF38
 * - func_151E0424
 * - func_151E09DC
 * - func_151E0B70
 * - func_151E1744
 * - func_151E22BC
 * - func_151E2404
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151DE8F0.s")
typedef struct GameDF1BCActor {
    u8 pad0[0x1FF];
    u8 active;
    u8 pad200;
    s8 duration;
    u8 pad202[0x16];
    s32 animation;
    s16 frame;
    u8 pad21E[0x14];
    u8 animationId;
} GameDF1BCActor;
void func_1000DE1C(s32, s32);
void func_1001263C(s32, s32, s32);
u16 func_1000EA94(s32);
void func_15007668(void);
s32 func_1507BB28(s32, s32);
void *func_15083E90(u8);
s32 func_151F2CDC(void);
void func_151E7E9C(void);
extern f32 D_8008FDE8;
extern u8 D_8008FE34;
extern s8 D_8008FEF8;
extern u8 D_800AB800[];
extern s8 D_800BE9EC, D_800C3E78;
extern u8 D_800CC2D0[];
extern void *D_800D154C;
extern u8 D_800E0A94, D_800E0A97;
extern s8 D_800E0BE9;
extern s32 D_800E9D00;
extern u8 *D_8008FDD4;
void func_151E3344(s32, s32, s32, s32, s32);
extern s32 D_800BE9E4;
extern u8 D_800E0A95;
extern s8 D_800E0A96;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DF1BC CURRENT (4070) */
void func_151DF1BC(void) {
    u32 buttons;
    s32 alpha;
    s32 animation;
    GameDF1BCActor *actor;

    *(GameDF1BCActor *volatile *)&actor = func_15083E90(9);
    if (D_800E0A96 != -1) {
        alpha = D_800E0A95 - (D_800BE9E4 << 5);
        if (alpha <= 0) {
            alpha = 0;
            D_8008FEF8 = D_8008FEF8 == 0;
            if (D_8008FEF8 == 0) {
                animation = 0xE;
                func_1001263C((func_150ADA20() & 1) + 0xC8, 0x7D00, 0x40);
            } else {
                animation = 0xF;
                func_1001263C(func_150ADA20() % 3U + 0xBE, 0x7D00, 0x40);
            }
            if (actor != NULL) {
                actor->animationId = animation;
                D_800D154C = actor;
                D_800C3E78 = ((u8 *)actor - D_800CC2D0) / 0x32C;
                actor->animation = func_1507BB28(0, actor->animationId);
                actor->frame = 0;
                actor->duration = 0x14;
            }
            D_800E0A96 = -1;
        }
        *(u16 *)(D_8008FDD4 + 0x20) &= 0xFFCF;
    } else {
        alpha = D_800E0A95 + (D_800BE9E4 << 5);
        if (alpha >= 0x100) alpha = 0xFF;
    }
    D_800E0A95 = alpha;
    alpha = (D_800E0A94 * alpha) >> 8;
    if (alpha >= 0xFE) alpha = 0xFF;
    if (D_8008FEF8 == 0) {
        func_151E3344(0x200200, 0, 1, (u8)alpha, 1);
        if (D_8008FE34 == 9 && (*(u16 *)(D_8008FDD4 + 0x20) & 0xC)) {
            func_151E7E9C();
            func_1000DE1C(D_800E0A97, 0);
            D_800E0A97 = func_1000EA94(D_800E0BE9);
        }
        buttons = *(u16 *)(D_8008FDD4 + 0x20);
        if ((buttons & 0x10) && D_8008FE34 == 0x15 && D_8008FDE8 == 0.0f) {
            D_800E0A96 = 1;
            *(u16 *)(D_8008FDD4 + 0x20) &= 0xFFCF;
            buttons = *(u16 *)(D_8008FDD4 + 0x20);
        }
        if (buttons & 0x20) func_15007668();
    }
    if (actor != NULL) {
        if (func_151F2CDC() == 1) {
            if (actor->active == 0) actor->active = 1;
        } else actor->active = 0;
    }
    if (D_8008FEF8 != 0) {
        if (*(u16 *)(D_8008FDD4 + 0x20) & 0x20) D_800E0A96 = 1;
        *(u16 *)(D_8008FDD4 + 0x20) &= 0xFFDF;
        if (D_8008FEF8 != 0) {
            func_1504332C(0xFF, 0, 0, (u8)alpha);
            func_15042D94(0x94, 0x14, 0x81, (s32)D_800AB800, 0x10);
        }
        D_800BE9EC = 0;
        if (D_800E9D00 & 0x400000) D_800BE9EC = 1;
        if (D_800E9D00 & 0x800000) D_800BE9EC = 2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DF1BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151DF1BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151DF574.s")
typedef struct Game20BDA0Record {
    u32 time;
    s32 score;
    s32 index;
    s8 status;
    u8 padD;
    s8 character;
    u8 padF;
} Game20BDA0Record;

void func_10010F30(s32, s32, s32, s32, s32);
void func_150076BC(s32);
void func_15007750(s32);
void func_15017790(void);
void func_150432BC(f32);
void func_150432FC(s16, s16);
void func_151E327C(void);
extern s8 D_80082BC0;
extern s8 D_8008FD74;
extern s8 D_8008FDA4;
extern s8 D_8008FDA8;
extern s8 D_8008FE2C;
extern u8 D_800AB814[];
extern u8 D_800AB818[];
extern u8 D_800AB828[];
extern u8 D_800AB82C[];
extern u8 D_800AB830[];
extern u8 D_800AB834[];
extern u8 D_800AB838[];
extern u8 D_800AB83C[];
extern u8 D_800AB840[];
extern s16 D_800BE3DC;
extern s8 D_800BE3DF;
extern s8 D_800BE3E0;
extern s32 D_800BE3E4;
extern Game20BDA0Record D_800BE3F8[];
extern void (*D_800E0A88)(void);
extern s8 D_800E0B94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DFF38 CURRENT (2447) */
void func_151DFF38(void) {
    s32 slot;
    u8 alpha;
    s32 sound;
    s32 score;
    s32 option;

    alpha = D_800E0A94;
    option = D_8008FE2C;
    sound = 0;
    slot = *(s8 *)(D_8008FDD4 + 0x2C) - 3;
    if (option < 2) {
        if (*(u16 *)(D_8008FDD4 + 0x20) & 0xC) {
            D_8008FE2C = 1 - option;
            sound = 0x62D;
        }
    } else if (*(u16 *)(D_8008FDD4 + 0x20) & 0xC) {
        D_8008FE2C = 5 - option;
        sound = 0x62D;
    }
    func_150432FC(0x94, 0x46);
    if (D_800BE3F8[slot].index == -1) {
        D_8008FE2C = 0;
    }
    if (slot == 2) {
        func_1504332C(0xFF, 0x37, 0x37, alpha);
    } else if (slot == 1) {
        func_1504332C(0x78, 0xFF, 0x16, alpha);
    } else {
        func_1504332C(0x20, 0x55, 0xFF, alpha);
    }
    if (D_800BE3F8[slot].index != -1) {
        s32 y;
        u32 seconds;
        u32 minutes;

        score = D_800BE3F8[slot].score;
        y = 0;
        if (score == 0x7D00) {
            score = 1000000;
            func_150432BC(0.75f);
            y = 2;
        }
        func_15042D94(0x70, y + 0x33, 0, (s32)D_800AB814, score);
        func_150432BC(1.0f);
        seconds = D_800BE3F8[slot].time % 60;
        minutes = D_800BE3F8[slot].time / 60;
        func_15042D94(0xA4, 0x33, 0, (s32)D_800AB818, minutes / 60, minutes % 60, seconds);
    }
    func_1504332C(0xFF, 0xFF, 0xFF, alpha);
    if (D_800BE3F8[slot].index >= 0) {
        func_15042D94(0x94, 0xAF, 1, (s32)D_800AB828, 0x1A);
        func_150432FC(0x58, 0xAF);
        if (D_8008FE2C < 2) {
            func_15042E3C((s32)D_800AB82C, (D_8008FE2C == 0) + 0x16, 1);
        } else {
            func_15042D94(0x94, 0x91, 1, (s32)D_800AB830, 0x19);
        }
    } else {
        func_15042D94(0x94, 0x6E, 1, (s32)D_800AB834, 0x31);
    }
    func_150432FC(0xD0, 0xAF);
    if (D_8008FE2C < 2) {
        if (D_800BE3F8[slot].index >= 0) {
            func_15042E3C((s32)D_800AB838, (D_8008FE2C != 0) + 0x18, 1);
        }
        if (D_8008FE2C == 0) {
            if (*(u16 *)(D_8008FDD4 + 0x20) & 0x10) {
                D_800E0B94 = 7;
                D_800E0A88 = func_151E327C;
                D_8008FD74 = 3;
                D_8008FDA8 = slot;
                D_800BE3DC = -1;
                D_80082BC0 = 0;
                func_150076BC(D_800BE3F8[slot].character);
                sound = 0x500;
            }
        } else if (*(u16 *)(D_8008FDD4 + 0x20) & 0x10) {
            D_8008FE2C = 2;
            sound = 0x500;
        }
    } else {
        func_15042D94(0x6C, 0xAF, 1, (s32)D_800AB83C, (D_8008FE2C == 3) + 0x1F);
        func_15042D94(0xBC, 0xAF, 1, (s32)D_800AB840, (D_8008FE2C == 2) + 0x1D);
        if (*(u16 *)(D_8008FDD4 + 0x20) & 0x10) {
            if (D_8008FE2C == 3) {
                D_8008FE2C = 0;
                func_15007750(slot);
                D_800BE3DF = 0x29;
                D_800BE3E0 = 0;
                D_800BE3E4 = 0;
                func_15017790();
                D_800BE3F8[slot].status = 0x18;
                D_800BE3F8[slot].score = 0;
                D_800BE3F8[slot].index = -1;
                D_8008FDA4 = 0;
            } else {
                D_8008FE2C = 1;
            }
            sound = 0x500;
        } else if (*(u16 *)(D_8008FDD4 + 0x20) & 0x20) {
            D_8008FE2C = 1;
        }
        *(u16 *)(D_8008FDD4 + 0x20) &= 0xFFDF;
    }
    if (sound != 0) {
        func_10010F30(sound, 0x4650, 0x40, 0, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DFF38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151DFF38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E0424.s")
void func_15042D78(u8);
void func_151E2404(void);
extern s8 D_8008FDE0;
extern u8 *D_8008FDD4;
extern s8 D_800AB690[];
extern s32 D_800AB754[];
extern u8 D_800AB850[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E09DC CURRENT (725) */
void func_151E09DC(void) {
    volatile s32 sp24;
    s32 var_v1;

    func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
    func_15042D94(0x94, 0x7E, 1, (s32)D_800AB850, 0x1A);
    func_15042D78(0x81);
    sp24 = D_800AB754[D_800AB690[*(s8 *)(D_8008FDD4 + 0x42) * 10]];
    if (D_800E0A96 == 0) {
        *(u16 *)(D_8008FDD4 + 0x20) &= 0xFFDF;
        var_v1 = D_800E0A95 - (D_800BE9E4 << 5);
        if (var_v1 <= 0) {
            D_8008FDD4[0x3F] = 0;
            if (D_8008FDE0 != 0) {
                func_151E2404();
            }
            D_8008FDE0 = 0;
            D_800E0A96 = -1;
            return;
        }
        D_800E0A95 = var_v1;
        goto block_8;
    }
    var_v1 = D_800E0A95 + (D_800BE9E4 << 5);
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
block_8:
    D_800E0A95 = var_v1;
    if (var_v1 != 0xFF) {
        *(u16 *)(D_8008FDD4 + 0x20) = 0;
    }
    func_151E3344(sp24, 1, 0, var_v1 & 0xFF, 0);
    if (*(u16 *)(D_8008FDD4 + 0x20) & 0x20) {
        D_800E0A96 = 0;
    }
    *(u16 *)(D_8008FDD4 + 0x20) &= 0xFFDF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E09DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E09DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E0B70.s")
void func_10010F30(s32, s32, s32, s32, s32);
void func_150432FC(s16, s16);
void func_151E2834(void);
void func_151E4314(void);
extern s8 D_8008FD74;
extern s8 D_8008FDA0;
extern s8 D_8008FE40;
extern s8 D_8008FE44[];
extern s8 D_8008FEE3[];
extern s8 D_800AB74C[][4];
extern u8 D_800AB858[];
extern u8 D_800AB85C[];
extern u8 D_800AB860[];
extern void (*D_800E0A88)(void);
extern s8 D_800E0B94;
extern s8 D_800E0C00[];

void func_151E1214(void) {
    s32 alpha;
    s8 *limits;
    s32 limit;
    s32 i;
    s32 x;

    if (D_800E0A96 != -1) {
        *(u16 *)(D_8008FDD4 + 0x20) &= 0xFFDF;
        alpha = D_800E0A95 - (D_800BE9E4 << 5);
        if (alpha <= 0) {
            D_800E0A95 = 0;
            D_8008FDD4[0x3F] = D_800E0A96;
            D_800E0A96 = -1;
            return;
        }
        D_800E0A95 = alpha;
    } else {
        alpha = D_800E0A95 + (D_800BE9E4 << 5);
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        D_800E0A95 = alpha;
    }
    func_1504332C(0xFF, 0xFF, 0xFF, alpha);
    limits = D_800AB74C[D_8008FEE3[-D_800AB690[*(s8 *)(D_8008FDD4 + 0x42) * 10 + 1]]];
    limit = *(limits - 1 + D_8008FE40);
    for (i = 0; i < D_8008FE40; i++) {
        if (D_8008FE44[i] >= 0) {
            if (((u16 *)(D_8008FDD4 + 0x22))[D_8008FE44[i]] & 9) {
                D_8008FDA0++;
                if (limit >= D_8008FE40 + D_8008FDA0) {
                    func_10010F30(0x4FF, 0x4650, 0x40, 0, 0);
                }
            }
            if (((u16 *)(D_8008FDD4 + 0x22))[D_8008FE44[i]] & 6) {
                D_8008FDA0--;
                if (D_8008FDA0 >= 0) {
                    func_10010F30(0x4FF, 0x4650, 0x40, 0, 0);
                }
            }
            if (D_8008FDA0 < 0) {
                D_8008FDA0 = 0;
            }
        }
    }
    if (limit < D_8008FE40 + D_8008FDA0) {
        D_8008FDA0 = limit - D_8008FE40;
    }
    limit = D_8008FE40 + D_8008FDA0;
    if (limit < 2) {
        limit = 2;
    }
    D_8008FDA0 = limit - D_8008FE40;
    for (i = D_8008FE40; i < limit; i++) {
        D_8008FE44[i] = -2;
        D_800E0C00[i] = 0;
    }
    for (i = limit; i < 16; i++) D_8008FE44[i] = -1;
    if (alpha == 0xFF && (*(u16 *)(D_8008FDD4 + 0x20) & 0x10)) {
        D_800E0B94 = 7;
        D_8008FD74 = 8;
        func_10010F30(0x500, 0x7D00, 0x40, 0, 0);
        if (D_800AB690[*(s8 *)(D_8008FDD4 + 0x42) * 10 + 2] == -1) {
            D_800E0A88 = func_151E2834;
        } else {
            D_800E0A88 = func_151E4314;
        }
    }
    func_15042D94(0x94, 0x55, 1, (s32)D_800AB858, 0x1A);
    x = 0xA1 - D_8008FE40 * 13 - D_8008FDA0 * 10;
    for (i = 0; i < limit; i++) {
        func_150432FC(x, 0x82);
        if (D_8008FE44[i] >= 0) {
            func_15042E3C((s32)D_800AB85C, D_8008FE44[i] + 1);
            x += 0x1A;
        } else {
            func_15042E3C((s32)D_800AB860, 5);
            x += 0x14;
        }
    }
    if (alpha == 0xFF && (*(u16 *)(D_8008FDD4 + 0x20) & 0x20)) {
        D_800E0A96 = 4;
    }
    *(u16 *)(D_8008FDD4 + 0x20) &= 0xFFDF;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E1744.s")
void func_151E530C(void);
void func_151E43DC(void);
extern s8 D_8008FD80;

void func_151E2284(void) {
    D_8008FD80 = 3;
    func_151E530C();
    func_151E43DC();
    D_8008FD80 = 0;
}
extern volatile s8 D_800E0BE0[];
extern u8 *D_8008FDD4;
extern s8 D_800AB690[];
extern s8 *D_80082BBC;
void func_151DD9E4();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E22BC CURRENT (4755) */
void func_151E22BC(void) {
    s32 index;
    u8 *record;
    volatile s8 *state;
    s32 value;

    index = D_800AB690[*(s8 *)(D_8008FDD4 + 0x42) * 10];
    record = (u8 *)D_80082BBC + index * 10;
    value = record[3];
    if (value >= 5) {
        record[3] = 4;
        value = 4;
    }
    if (value < 0) {
        record[3] = 0;
    }
    value = *(s8 *)(record + 1);
    state = D_800E0BE0;
    if (value <= 0) {
        record[1] = 1;
        value = *(s8 *)(record + 1);
    }
    state[2] = value;
    state[0xB] = 0;
    state[3] = *(s8 *)(record + 2);
    state[0x10] = record[3];
    state[0x11] = record[4];
    switch (index) {
        case 0:
            state[4] = record[5];
            break;
        case 1:
            state[0xD] = record[5];
            state[0xE] = record[6];
            break;
        case 2:
            state[0x12] = record[5];
            break;
        case 3:
            state[0x11] = 0;
            state[0x12] = record[5];
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            state[7] = record[5];
            state[0x11] = 1;
            state[3] = 2;
            state[0x13] = record[6];
            break;
    }
    state[0x16] = record[8];
    state[6] = record[9];
    func_151DD9E4();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E22BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E22BC.s")
extern volatile s8 D_800E0BE0[];
extern u8 *D_8008FDD4;
extern s8 D_800AB690[];
extern s8 *D_80082BBC;
void func_150076A0(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E2404 */
void func_151E2404(void) {
    volatile s8 *source;
    s8 *record;
    s32 index;

    source = D_800E0BE0;
    index = D_800AB690[*(s8 *)(D_8008FDD4 + 0x42) * 10];
    record = D_80082BBC + (index * 10);
    record[0] = 0;
    record[1] = source[2];
    record[2] = source[3];
    record[3] = source[0x10];
    record[4] = source[0x11];
    switch (index) {
        case 0:
            record[5] = source[4];
            break;
        case 1:
            record[5] = source[0xD];
            record[6] = source[0xE];
            break;
        case 2:
            record[5] = source[0x12];
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            record[5] = source[7];
            record[6] = source[0x13];
            break;
    }
    record[8] = source[0x16];
    record[9] = source[6];
    func_150076A0();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E2404 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E2404.s")
