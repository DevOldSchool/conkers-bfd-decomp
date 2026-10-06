#include "types.h"

/*
 * Reviewed source unit: src/main/init_11FA0.c
 * Boundary evidence: docs/evidence/boundaries/main/main_allocator_transfer_controller_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80012020
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_80042770;

void func_80011FA0(s32 arg0) {
    D_80042770 = arg0;
}
extern s8 D_80041FD9;
extern s32 D_80042774;

void func_80011FB0(s32 arg0) {
    s32 previous = D_80042774;

    if (previous == 3) {
        D_80041FD9 = 1;
    }
    D_80042774 = arg0;
}
extern s32 D_80042778;

void func_80011FDC(s32 arg0) {
    D_80042778 = arg0;
}
extern s32 D_8004277C;

void func_80011FEC(void) {
    D_80042770 = D_80042774 = D_80042778 = D_8004277C = 0;
}
typedef struct {
    f32 values[2];
} MainSelectorPair;

extern MainSelectorPair D_8002BA10;
extern MainSelectorPair D_8002BA18;
extern u8 *D_800DBFF0;
extern u8 *D_800B0DF0;
extern u8 D_800BE9B4;
extern f32 D_800BE9A4;
extern f32 D_80042780[2];
extern f32 D_80042788[2];
extern f32 D_80042790;
extern f32 D_80042794;
extern f32 D_80042798;
extern f32 D_8002C424;
extern f32 D_8002C428;
extern f32 D_8002C42C;
extern f32 D_8002C430;
extern f32 D_8002C434;
extern f32 D_8002C438;
extern f32 D_8002C43C;
extern f32 D_8002C440;
extern f32 D_8002C444;
f32 func_85047D60(f32);
void func_80008BC0(u8, f32, f32);
void func_80008B60(u8, u8, u8, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80012020 CURRENT (95) */
void func_80012020(void) {
    s32 i;
    f32 volume = 0.0f;
    s32 selector;
    MainSelectorPair gains = D_8002BA10;
    MainSelectorPair frequencies = D_8002BA18;
    f32 scale;

    selector = D_80042770;
    if ((*(u32 *)(D_800DBFF0 + 0x5F0) & 1) && !(D_800B0DF0[0x2A] & 1)) {
        selector = 1;
    }
    if (D_80042774 != 0) {
        selector = D_80042774;
    } else if (D_80042778 != 0) {
        selector = D_80042778;
    }
    if (selector == 6) {
        selector = 0;
    }
    switch (selector) {
        case 1:
            volume = (13.0f - D_80042790) + D_80042790;
            D_8004277C = 0;
            gains.values[0] = 127.0f;
            frequencies.values[0] = ((D_8002C428 + func_85047D60(D_80042798 * D_8002C424) * 200.0f) - D_80042780[0]) + D_80042780[0];
            break;
        case 2:
            D_8004277C = 0;
            volume = 70.0f;
            gains.values[0] = 127.0f;
            frequencies.values[0] = func_85047D60(D_80042798 * D_8002C42C) * 200.0f + 450.0f;
            break;
        case 3:
            volume = (52.0f - D_80042790) * D_8002C430 + D_80042790;
            D_8004277C = 0;
            gains.values[0] = (127.0f - D_80042788[0]) * D_8002C430 + D_80042788[0];
            frequencies.values[0] = ((436.0f + func_85047D60(D_80042798 * D_8002C434) * 282.0f) - D_80042780[0]) * D_8002C438 + D_80042780[0];
            D_80041FD9 = 0;
            break;
        case 4:
            D_8004277C = 4;
            gains.values[1] = 127.0f;
            if (D_800BE9B4 != 0) {
                frequencies.values[1] = 400.0f;
            } else {
                frequencies.values[1] = (400.0f - D_80042780[1]) + D_80042780[1];
            }
            D_80041FD9 = 0;
            break;
        case 5:
            gains.values[1] = 127.0f;
            frequencies.values[1] = 520.0f;
            D_80041FD9 = 0;
            break;
        default:
            if (D_8004277C == 4) {
                frequencies.values[1] = (D_8002C43C - D_80042780[1]) * D_8002C440 + D_80042780[1];
                if (frequencies.values[1] < D_8002C444) {
                    D_8004277C = 4;
                } else {
                    D_8004277C = 0;
                    D_80041FD9 = 1;
                }
            }
            break;
    }
    D_80042798 += D_800BE9A4;
    if (volume != D_80042790 || D_80042794 != 1.0f) {
        scale = volume / 127.0f;
        for (i = 0; i < 3; i++) {
            func_80008BC0((u8)i, scale, 1.0f);
        }
        D_80042790 = volume;
        D_80042794 = 1.0f;
    }
    for (i = 0; i < 2; i++) {
        if (frequencies.values[i] != D_80042780[i]) {
            func_80008B60((u8)i, (u8)i, 9, 0, (s32)frequencies.values[i]);
            D_80042780[i] = frequencies.values[i];
        }
        if (gains.values[i] != D_80042788[i]) {
            func_80008B60((u8)i, (u8)i, 8, 0, (s32)gains.values[i]);
            D_80042788[i] = gains.values[i];
        }
    }
    D_80042770 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80012020 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_11FA0/func_80012020.s")
