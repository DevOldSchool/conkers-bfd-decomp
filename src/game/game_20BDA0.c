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
 * - func_151E1214
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
u32 func_150ADA20(void);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E1214.s")
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
