#include "types.h"

/*
 * Reviewed source unit: src/game/game_20F9A0.c
 * Boundary evidence: docs/evidence/game_raw_extended_code_selected_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151E24F0
 * - func_151E2834
 * - func_151E30C4
 * - func_151E327C
 * - func_151E3344
 * - func_151E43DC
 * - func_151E4BD8
 * - func_151E4EE8
 * - func_151E50C8
 * - func_151E53E8
 * - func_151E55A8
 * - func_151E565C
 * - func_151E5F64
 * - func_151E5FF4
 * - func_151E6964
 * - func_151E6C1C
 * - func_151E7DC0
 * - func_151E7EF8
 * - func_151E7F60
 * - func_151E81EC
 * - func_151E8214
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E24F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E2834.s")
void func_15017790(void);
void func_1509CC94();
void func_1509CDDC();
s32 func_1509CF28(s8, s32 *);
void func_1509D054(void);
s32 func_1509D08C(s8, u8, s32 *, s32 *);
u16 func_1509CA30(s32);
s32 func_1509CA50(s32);
void func_15085710(s16, s32, s32);
void func_151E7EF8(void);
void func_1501C730(s32, s32, s32, s32, s32);
extern s8 D_80087260;
extern s8 D_80087270;
extern s8 D_8008FD70;
extern s8 D_8008FD8C;
extern s8 D_8008FD90;
extern s8 D_8008FD94;
extern s8 D_8008FDA8;
extern s16 D_8008FDAC;
extern u8 D_8008FDB4;
extern s16 D_8008FDBC;
extern s8 D_8008FF00;
extern u8 D_8008FF04;
extern s32 D_800BE3E4;
extern s32 D_800BE9F4;
extern s8 D_800BE618;
extern s8 D_800D18A8;
extern s8 D_800D23A8;
extern s8 D_800D2E40;
extern u8 D_800DD2C0;
extern u8 D_800E0B94;
extern s8 D_800E0B99;
extern s8 D_800E0BB1;
extern u8 D_800E0BD1;
extern s32 D_800E9D00;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E30C4 CURRENT (275) */
void func_151E30C4(void) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;

    sp24 = 0;
    if (D_8008FDB4 != 0) {
        sp28 = D_8008FDAC;
    } else {
        func_1509CF28(D_8008FF00, &sp2C);
        func_1509D08C(D_8008FF00, D_8008FF04, &sp28, &sp24);
        func_1509D054();
    }
    func_15017790();
    func_1509CC94(sp28);
    func_1509CDDC(sp28);
    D_800BE9F4 = func_1509CA30(sp28);
    func_15085710(0, 9, sp24);
    D_800BE3E4 = sp24;
    D_800DD2C0 = func_1509CA50(sp28);
    if (D_8008FDB4 == 2) {
        D_800DD2C0 = D_800E0BD1;
    }
    D_8008FD70 = 0;
    D_800D23A8 = 0;
    D_8008FDBC = 0;
    D_8008FDA8 = -1;
    D_800E0B94 = 0;
    D_800E0B99 = 1;
    D_8008FD8C = 1;
    D_8008FD90 = 1;
    D_8008FD94 = 1;
    D_800BE618 = 1;
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    D_80087270 = 0;
    D_800D18A8 = 0;
    D_800E0BB1 = 1;
    func_151E7EF8();
    D_800D2E40 = 1;
    func_1501C730(6, D_800BE9F4, func_1509CA50(sp28), 0, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E30C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E30C4.s")
/* Call context: func_1501C730: unique active declaration in the allowed source */
void func_1501C730(s32, s32, s32, s32, s32);
extern s8 D_80087260;
extern s8 D_80087270;
extern s8 D_8008FD94;
extern s16 D_8008FDBC;
extern s8 D_800BE3DF;
extern u8 D_800BE3E0;
extern s8 D_800BE618;
extern s8 D_800D23A8;
extern s8 D_800E0B99;
extern s8 D_800E0BB1;
extern s32 D_800E9D00;
extern s8 D_8008FD8C;
extern s8 D_8008FD90;
extern s8 D_800D2E40;
extern u8 D_800E0B94;
extern s16 D_800E0B9A;
extern u8 D_8008FD80;
extern void func_151E2834(void);
extern s32 func_151F2CDC(void);
extern void func_151F2D6C(s32 arg0, s32 arg1);
extern void func_151E530C(void);
extern u8 D_800C35EA;
extern void (*D_800E0A88)(void);
extern u8 D_8008FD74;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E327C CURRENT (210) */
void func_151E327C(void) {
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    D_80087270 = 0;
    D_8008FD8C = 1;
    D_8008FD90 = 1;
    D_8008FD94 = 1;
    D_8008FDBC = 0;
    D_800BE618 = 1;
    D_800D23A8 = 0;
    D_800E0B94 = 0;
    D_800D2E40 = 0;
    func_1501C730(6, (s32) D_800BE3DF, (s32) D_800BE3E0, 0, 1);
    D_800E0B99 = 1;
    D_800E0BB1 = 1;
    func_151E7EF8();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E327C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E327C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E3344.s")
void func_151E4264(void) {
    if (D_8008FD80 != 0) {
        D_8008FD80 = 0;
        return;
    }
    func_151E530C();
    if ((D_800E0B9A != 0) || (D_800C35EA != 1)) {
        if ((D_800C35EA == 1) && (func_151F2CDC() == 1)) {
            func_151F2D6C(0, 0x2DE0);
        }
        D_800E0B94 = 7;
        D_800E0A88 = func_151E2834;
        D_8008FD74 = 8;
    }
}
typedef struct {
    s16 value;
    s8 alternate;
    s8 selected;
} Game20F9A0Selection;

void func_1501D348(s32, s32, s32, u8, s32);
extern void *D_8008FDD4;
extern s8 D_800AB692[];
extern Game20F9A0Selection D_800AB7A4[];
extern s8 D_800E0C00[];

void func_151E4314(void) {
    Game20F9A0Selection *entry;
    s8 index;
    s8 choice;

    index = D_800AB692[*(s8 *)((u8 *)D_8008FDD4 + 0x42) * 10];
    if (index >= 0) {
        entry = &D_800AB7A4[index];
        if (D_800E0C00[0] != 0) {
            choice = entry->selected;
        } else {
            choice = entry->alternate;
        }
        func_1501D348(entry->value, choice, 0, 0, 0);
        D_8008FD80 = 1;
        D_800E0B94 = 5;
        D_8008FD8C = 1;
        D_8008FD90 = 1;
    } else {
        func_151E2834();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E43DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4BD8.s")
extern u8 D_800E0B94;

void func_151E4DC4(void) {
    D_800E0B94 = 0xA;
}
extern s16 D_800E0B9A;

void func_151E4DD8(void) {
    if (D_800E0B9A & 0x8020) {
        D_800E0B94 = 4;
    }
}
void func_151E557C(void);
void func_1501C730(s32, s32, s32, s32, s32);
extern s16 D_8008FDCC;
extern s8 D_8008FDA4;
extern s8 D_800D2E40;

void func_151E4E00(void) {
    D_8008FDCC = 0;
    func_151E557C();
    D_800E0B94 = 3;
    D_8008FDA4 = 0;
    D_8008FD80 = 0;
    D_800D2E40 = 0;
    func_1501C730(6, 0x1D, 0, 0, 1);
}
void func_151E55A8(void);
extern s32 D_800E0A90;
extern void (*D_800E0A88)(void);
extern u8 D_8008FD74;

void func_151E4E64(void) {
    func_151E530C();
    func_151E55A8();
    if (D_800E0A90 >= 0x4B1) {
        D_800E0B9A |= 0x8000;
    }
    if (D_800E0B9A != 0) {
        D_800E0B94 = 7;
        D_800E0A88 = func_151E4E00;
        D_8008FD74 = 8;
    }
}
extern f32 D_8008FDD0;
extern f32 D_800ABA2C;
extern f32 D_800ABA30;
extern f32 D_800ABA34;
extern f32 D_800DDDC8;
extern f32 D_800DDDD8;
extern u8 D_800E0B96;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E4EE8 CURRENT (3785) */
void func_151E4EE8(void) {
    f32 var_ft1;
    s32 var_v0_2;
    u8 temp_t7;
    u8 var_v0;

    var_v0 = D_800E0B96;
    var_ft1 = (f32) var_v0;
    if ((s32) var_v0 < 0) {
        var_ft1 += 4294967296.0f;
    }
    D_8008FDD0 = 1.0f - (var_ft1 / 255.0f);
    if (D_8008FD74 == 0xFF) {
        if (D_800ABA2C < D_800DDDC8) {
            temp_t7 = var_v0 + D_800BE9E4;
            var_v0 = temp_t7 & 0xFF;
            D_800E0B96 = temp_t7;
            if ((s32) var_v0 < 0x55) {
                D_800DDDD8 = D_800ABA30;
            } else {
                D_800DDDD8 = D_800ABA34;
            }
        }
        if (!(D_800DDDC8 < 1.0f)) {
            if ((s32) var_v0 < 0x6E) {
                return;
            }
            goto block_14;
        }
    } else {
        if (var_v0 != 0xFF) {
            var_v0_2 = var_v0 + (D_800BE9E4 * D_8008FD74);
            if (var_v0_2 >= 0x100) {
                var_v0_2 = 0xFF;
            }
            D_800E0B96 = (u8) var_v0_2;
            return;
        }
block_14:
        D_800E0B96 = 0xFF;
        D_8008FD74 = 8;
        D_8008FDD0 = 1.0f;
        D_800E0A88();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E4EE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4EE8.s")
extern void *D_8008FDD4;

void func_151E5034(void) {
    *(f32 *)((u8 *)D_8008FDD4 + 0) = 0.0f;
    *(f32 *)((u8 *)D_8008FDD4 + 4) = 0.0f;
    *(s8 *)((u8 *)D_8008FDD4 + 0x2B) = 0;
    *(s16 *)((u8 *)D_8008FDD4 + 0x20) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x3E) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x3F) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x41) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x43) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x44) = 0;
    *(f32 *)((u8 *)D_8008FDD4 + 0x10) = 0.0f;
    *(s8 *)((u8 *)D_8008FDD4 + 0x2A) = 0;
    *(f32 *)((u8 *)D_8008FDD4 + 0x14) = 0.0f;
    *(f32 *)((u8 *)D_8008FDD4 + 0x18) = 0.0f;
    *(f32 *)((u8 *)D_8008FDD4 + 0x1C) = 0.0f;
    *(f32 *)((u8 *)D_8008FDD4 + 0xC) = 0.0f;
    *(f32 *)((u8 *)D_8008FDD4 + 8) = 0.0f;
}
void func_15017790(void);
void func_151E6BFC(void);

extern s8 D_8008FE54;
extern s8 D_8008FE55;
extern s8 D_8008FE56;
extern s8 D_8008FE57[];
extern s8 D_8008FE6B[];
extern u8 D_800AB570[];
extern u8 D_800E0AF0[];
extern s8 D_800E0BE0;
extern s8 D_800E0BE1;
extern s8 D_800E0BE2;
extern s8 D_800E0BE3[];
extern s32 D_800E0A90;
extern u8 D_800E0B95;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E50C8 CURRENT (9135) */
void func_151E50C8(void) {
    s32 *var_v0;
    s32 *var_v1;
    s8 temp_t0;
    s8 temp_t1;
    s8 temp_t2;
    s8 temp_t9;

    var_v0 = (s32 *)D_8008FE57;
    var_v1 = (s32 *)D_800E0BE3;
    D_800E0BE2 = D_8008FE56;
    D_800E0BE1 = D_8008FE55;
    D_800E0BE0 = D_8008FE54;
    do {
        temp_t9 = *((s8 *)var_v0 + 0);
        temp_t0 = *((s8 *)var_v0 + 1);
        temp_t1 = *((s8 *)var_v0 + 2);
        temp_t2 = *((s8 *)var_v0 + 3);
        var_v0++;
        var_v1++;
        *((s8 *)var_v1 - 4) = temp_t9;
        *((s8 *)var_v1 - 3) = temp_t0;
        *((s8 *)var_v1 - 2) = temp_t1;
        *((s8 *)var_v1 - 1) = temp_t2;
    } while (var_v0 != (s32 *)D_8008FE6B);
    D_800E0A90 = 0;
    func_151E6BFC();
    if (D_8008FDD4 == 0) {
        D_8008FDD4 = D_800E0AF0;
        func_151E5034();
        if (*(s8 *)((u8 *)D_8008FDD4 + 0x3E) == 1) {
            s8 index = *(s8 *)((u8 *)D_8008FDD4 + 0x2C);
            *(s8 *)((u8 *)D_8008FDD4 + 0x2C) = D_800AB570[index];
        }
    }
    func_15017790();
    D_800E0B94 = 0xB;
    D_800D2E40 = 0;
    func_1501C730(6, 0x25, 0, 0, 1);
    D_800E0B95 = D_800E0B94;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E50C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E50C8.s")
void func_15042D78(u8);
void func_151E6964(s32);
extern s32 D_8003C8E0;
extern void (*D_8008FDEC[])(void);
extern s8 D_8008FE28;
extern u16 D_800BE930;
extern s32 D_800BE9E4;
extern u8 D_800E0B95;
extern u8 D_800E0BDC;

void func_151E51EC(void) {
    u8 sp1F;

    sp1F = D_800E0B94;
    D_8003C8E0 = 0x08000000;
    D_800E0BDC = 0xFF;
    func_15042D78(0x81);
    D_800E0B9A = D_800BE930;
    if (D_8008FE28 != 0) {
        D_8008FE28 -= 1;
        D_800E0B9A = 0;
    }
    if ((u8)D_800E0B94 == 0) {
        func_151E6964(2);
    } else if ((u8)D_800E0B94 == 8) {
        func_151E6964(4);
    } else {
        func_151E6964(1);
    }
    D_8008FDEC[(u8)D_800E0B94]();
    if ((u8)D_800E0B94 != 7) {
        D_800E0A90 += D_800BE9E4;
        if (D_800E0B94 != sp1F) {
            D_800E0B95 = sp1F;
            D_800E0A90 = 0;
        }
    }
    D_8003C8E0 = 0;
}
extern u8 D_8008FD74;
extern u8 D_800E0B96;
extern s32 D_800BE9E4;

void func_151E530C(void) {
    f32 temp_fv0;
    s32 var_v1;

    if ((u8) D_800E0B94 != 2) {
        if (D_800E0B96 != 0) {
            var_v1 = D_800E0B96 - (D_800BE9E4 * D_8008FD74);
            if (var_v1 < 0) {
                var_v1 = 0;
            }
            D_800E0B96 = (u8) var_v1;
        }
        if ((D_8008FDD4 != 0) && (*(s8 *)((u8 *)D_8008FDD4 + 0x2B) == 0) && (*(f32 *)((u8 *)D_8008FDD4 + 0xC) > 0.0f)) {
            temp_fv0 = *(f32 *)((u8 *)D_8008FDD4 + 8);
            if (temp_fv0 > 0.5f) {
                var_v1 = (s32) ((temp_fv0 - 0.5f) * 524.0f);
                if (var_v1 >= 0x100) {
                    var_v1 = 0xFF;
                }
                D_800E0B96 = (u8) var_v1;
            }
        }
    }
}
void func_151DDBA0(void);
void func_151E4BD8(void);
extern u16 D_8008FDC0;
extern s8 D_8008FE2C;
extern s8 D_800AB68C[];
extern u8 D_800CC2D0[];
extern s8 D_800E0A86;
extern u8 D_800BE616;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E53E8 CURRENT (1530) */
void func_151E53E8(s32 arg0) {
    u8 *var_a0;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_t7;

    D_800E0A90 = 0;
    D_8008FE2C = 0;
    D_80087270 = 0;
    if (D_800BE616 != 0) {
        D_800E0B94 = 7;
        D_8008FD74 = 8;
        var_v1 = 0;
        if (D_800AB68C[(*(s8 *)((u8 *)D_8008FDD4 + 0x42) * 10) + 7] != -1) {
            *(s8 *)((u8 *)D_8008FDD4 + 0x3F) = 4;
            D_800E0A88 = func_151E4BD8;
        } else {
            *(s8 *)((u8 *)D_8008FDD4 + 0x3F) = 3;
            D_800E0A88 = func_151DDBA0;
        }
        var_v0 = 0;
        var_a0 = D_800CC2D0;
        if (D_8008FD90 > 0) {
            do {
                var_v0 += 1;
                temp_t7 = (u8 *)D_8008FDD4 + var_v1;
                var_v1 += 0xC;
                *(s16 *)(temp_t7 + 0x6C) =
                    *(s16 *)(*(u8 **)(var_a0 + 0x31C) + 0x1AA);
                var_a0 += 0x32C;
            } while (var_v0 < D_8008FD90);
        }
        D_8008FDC0 &= 0xE35F;
        D_800E0A86 = arg0;
        if (D_800AB68C[(*(s8 *)((u8 *)D_8008FDD4 + 0x42) * 10) + 7] == -2) {
            if (arg0 == 0) {
                func_151E4BD8();
                return;
            }
            D_800E0A88 = func_151DDBA0;
            *(s8 *)((u8 *)D_8008FDD4 + 0x3F) = 3;
        }
    } else {
        D_800E0B94 = 4;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E53E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E53E8.s")
extern u8 D_80084060[4];

void func_151E557C(void) {
    D_80084060[0] = 0;
    D_80084060[1] = 1;
    D_80084060[2] = 2;
    D_80084060[3] = 3;
}
extern s32 D_800BE9E4;
extern u8 D_800E0B97;
extern u8 D_800E0B98;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E55A8 CURRENT (160) */
void func_151E55A8(void) {
    s32 var_a0;
    s32 var_v1;

    if (D_800E0B98 == 0) {
        var_v1 = D_800BE9E4 * 8;
    } else {
        var_v1 = -D_800BE9E4;
        var_v1 *= 8;
    }
    var_a0 = D_800E0B97 + var_v1;
    if (var_a0 >= 0x100) {
        var_a0 = 0x1FE - var_a0;
        D_800E0B98 ^= 1;
    } else if (var_a0 < 0) {
        var_a0 = -var_a0;
        D_800E0B98 ^= 1;
    }
    D_800E0B97 = (u8) var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E55A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E55A8.s")
extern u8 D_800E0A8C;

void func_151E562C(void) {
    if (D_800E0A8C != 0) {
        D_800E0A8C = 0;
    }
}
extern s8 D_8008FDC8;

s8 func_151E564C(void) {
    return D_8008FDC8;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E565C.s")
extern u8 D_800BE616;
extern s8 D_800E0C00[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E5F64 CURRENT (530) */
s8 func_151E5F64(s8 arg0) {
    s8 var_v1;

    if ((D_800BE616 != 0) || (D_800E0B94 != 0)) {
        var_v1 = D_800E0C00[(s32)arg0];
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        return var_v1;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E5F64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E5F64.s")
extern s8 D_8008FD8C;
extern s8 D_8008FD90;
extern s8 D_800E0BEB;

s8 func_151E5FAC(void) {
    if (D_800E0BEB != 0) {
        if (D_8008FD8C >= 5) {
            return D_8008FD90;
        }
        return D_8008FD8C;
    }
    return D_8008FD90;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E5FF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E6964.s")
extern s32 D_8008FDD8;
extern s8 D_800E0BD3;
extern s32 D_800E0BD4;

void func_151E6BFC(void) {
    D_800E0BD3 = 0;
    D_800E0BD4 = 0;
    D_8008FDD8 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E6C1C.s")
void *func_151149AC(u8);
extern u8 D_8008FFB0[];
extern f32 D_800ABA8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E7DC0 CURRENT (375) */
void func_151E7DC0(void) {
    s32 index;

    index = 0;
    if (*(f32 *)((u8 *)D_8008FDD4 + 8) < D_800ABA8C) {
        if (*(s8 *)((u8 *)D_8008FDD4 + 0x3E) == 0) {
            return;
        }
    }
    {
        do {
            u8 resource_id;
            void *resource;

            if (*(s8 *)((u8 *)D_8008FDD4 + 0x3E) == 0) {
                resource_id = D_8008FFB0[(((index << 2) - index) << 1) +
                    *(s8 *)((u8 *)D_8008FDD4 + 0x2C)];
            } else {
                resource_id = D_8008FFB0[index * 6];
            }
            resource = func_151149AC(resource_id);
            index++;
            if (resource != 0) {
                *(s32 *)((u8 *)resource + 0x80) = 2;
            }
        } while (index != 2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E7DC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E7DC0.s")
void func_10017870(s32);
extern s8 D_800E0BE9;

void func_151E7E9C(void) {
    if (D_800E0BE9 == 2) {
        func_10017870(1);
        return;
    }
    if (D_800E0BE9 == 0) {
        func_10017870(2);
        return;
    }
    func_10017870(4);
}
extern s32 D_10003330[];
extern s32 func_151DDC20[];
extern s32 func_151DE7D4[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E7EF8 CURRENT (280) */
void func_151E7EF8(void) {
    s32 *var_v0;
    s32 temp_t6;
    s32 var_v1;

    func_151E7E9C();
    var_v0 = func_151DDC20;
    var_v1 = 0;
    if ((u32)var_v0 < (u32)func_151DE7D4) {
        do {
            temp_t6 = *var_v0;
            var_v0++;
            var_v1 += temp_t6;
        } while ((u32)var_v0 < (u32)func_151DE7D4);
    }
    if (var_v1 != 0xBFC924E3) {
        D_10003330[0] = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E7EF8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E7EF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E7F60.s")
extern s8 D_8008FD84;
extern s32 D_800E0BA0;
extern s32 D_800E0BA4;
extern s32 D_800E0BA8;
extern s32 D_800E0BAC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E81EC CURRENT (400) */
void func_151E81EC(void) {
    D_800E0BA4 = 0;
    D_800E0BA0 = 0;
    D_800E0BA8 = 0;
    D_800E0BAC = 0;
    D_8008FD84 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E81EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E81EC.s")
s32 func_1517EFDC();                                /* extern */
extern s8 D_8008FDA4;
extern s16 D_8008FDCC;
extern s8 D_800D2E43;
extern s16 D_800E0A80;
extern s32 D_800E0A90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E8214 CURRENT (205) */
void func_151E8214(void) {
    if ((u8) D_800E0B94 != 8) {
        if (func_1517EFDC() == 0) {
            D_800E0A90 = 0;
        }
        if (D_800E0A90 >= 0xA1) {
            D_8008FDCC = 0;
            D_800E0B94 = 8;
            D_8008FD8C = 1;
            D_8008FD90 = 1;
            D_8008FDA4 = 0;
            D_800E0A80 = -2;
            D_800E0A90 = 0;
            D_800D2E43 = 1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E8214 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E8214.s")
void func_1501C730(s32, s32, s32, s32, s32);
extern u8 **D_800E0BD8;

void func_151E82B8(void) {
    func_151E530C();
    if ((D_800E0A80 == -1) && (D_800E0A90 >= 0x79)) {
        D_800E0B94 = 9;
        D_800E0A90 = 0;
        D_8008FDCC = 0xFF;
        D_800E0A80 = 0;
        func_1501C730(6, 0x1D, 0, 0, 1);
        return;
    }
    if (D_800E0A80 == -2) {
        D_800E0A80 = 0;
    }
    if ((D_800E0A90 >= 0x1BE) && (D_800E0A80 >= 0)) {
        if (D_800E0BD8[D_800E0A80][0] != 0x2A) {
            do {
                D_800E0A80 += 1;
            } while (D_800E0BD8[D_800E0A80][0] != 0x2A);
        }
        D_800E0A80 += 1;
        if (D_800E0BD8[D_800E0A80][0] == 0x3D) {
            D_800E0A80 = -1;
        }
        D_800E0A90 = 0;
    }
}
/* Call context: func_1501C730: unique active declaration in the allowed source */
/* Call context: func_1501D348: unique active project prototype */
/* Call context: func_151E5034: unique active declaration in the allowed source */
/* Call context: func_151E530C: unique active declaration in the allowed source */
void func_1501D348(s32, s32, s32, u8, s32);

void func_151E83E8(void) {
    if (D_800E0A80 == 0) {
        D_800E0A80 = -1;
        func_1501D348(0x1D, 6, 0, 0U, 0);
    }
    func_151E530C();
    if (func_1517EFDC() == 0) {
        D_800E0A90 = 0;
    }
    if (D_800E0A90 >= 0x65) {
        func_151E5034();
        D_8008FDA4 = 0;
        D_800E0B94 = 1;
        D_800E0A90 = 0;
        D_800D2E40 = 0;
        func_1501C730(6, 0x21, 0, 0, 1);
    }
}
