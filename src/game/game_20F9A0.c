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
 * - func_151E4264
 * - func_151E4314
 * - func_151E43DC
 * - func_151E4BD8
 * - func_151E4EE8
 * - func_151E50C8
 * - func_151E51EC
 * - func_151E530C
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
 * - func_151E82B8
 * - func_151E83E8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E24F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E2834.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E30C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E327C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E3344.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4314.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E43DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4BD8.s")
extern s8 D_800E0B94;

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
extern s8 D_8008FD80;
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
void func_151E530C(void);
void func_151E55A8(void);
extern s32 D_800E0A90;
extern s16 D_800E0B9A;
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E50C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E51EC.s")
extern u8 D_8008FD74;
extern u8 D_800E0B96;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E530C CURRENT (25) */
void func_151E530C(void) {
    f32 temp_fv0;
    s32 var_v1;
    s32 var_v1_2;

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
                var_v1_2 = (s32) ((temp_fv0 - 0.5f) * 524.0f);
                if (var_v1_2 >= 0x100) {
                    var_v1_2 = 0xFF;
                }
                D_800E0B96 = (u8) var_v1_2;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E530C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E530C.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E55A8 CURRENT (155) */
void func_151E55A8(void) {
    s32 var_a0;
    s32 var_v1;

    if (D_800E0B98 == 0) {
        var_v1 = D_800BE9E4 * 8;
    } else {
        var_v1 = D_800BE9E4 * -8;
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
extern s32 D_800E0BA4;
extern s32 D_800E0BA8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E81EC CURRENT (205) */
void func_151E81EC(void) {
    D_800E0BA4 = 0;
    D_800E0BA4 = 0;
    D_800E0BA8 = 0;
    D_800E0BA8 = 0;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E8214 CURRENT (105) */
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E82B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E83E8.s")
