#include "types.h"

/*
 * Reviewed source unit: src/game/game_20B0D0.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151DDC20
 * - func_151DE6D4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_20B0D0/func_151DDC20.s")
void func_151DE6CC(void) {

}
void func_1501C730(s32, s32, s32, s32, s32);
void func_151E530C(void);
extern s32 D_80000300;
extern u8 D_800CC2D0;
extern s32 D_800E0A90;
extern s16 D_800E0B9A;
extern s8 D_8008FE28;
extern s8 D_800E0B94;
extern s8 D_800D2E40;
extern s8 D_800E0B96;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DE6D4 CURRENT (815) */
void func_151DE6D4(void) {
    s32 var_v0;

    func_151E530C();
    *(s32 *)((u8 *)&D_800CC2D0 + 0x25C) |= 0x200;
    *(f32 *)((u8 *)&D_800CC2D0 + 0x18) = 1000.0f;
    if (D_80000300 == 0) {
        D_800E0A90 = 0;
    }
    var_v0 = D_800E0A90;
    if ((var_v0 >= 0x14B) && (D_800E0B9A & 0x8000)) {
        if (var_v0 < 0x1E0) {
            D_800E0A90 = var_v0 = 0x1E0;
        }
        if ((var_v0 >= 0x259) && (var_v0 < 0x2D0)) {
            D_800E0A90 = var_v0 = 0x2D0;
        }
    }
    if (var_v0 >= 0x349) {
        D_8008FE28 = 2;
        D_800E0B94 = 1;
        D_800D2E40 = 0;
        func_1501C730(6, 0x21, 0, 0, 1);
        D_800E0B96 = 0xFF;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DE6D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20B0D0/func_151DE6D4.s")
extern s32 D_800E0A90;
extern s8 D_800E0B97;
extern s8 D_800E0B98;
extern s8 D_800E0A8C;
extern s8 D_8008FE28;
void func_151DE85C(void);

void func_151DE7D4(void) {
    D_800E0A90 = 0;
    D_800E0B97 = 0;
    D_800E0B98 = 0;
    D_800E0A8C = 0;
    D_8008FE28 = 2;
    func_151DE85C();
}
void func_1500764C(void);
extern s8 D_8008FD74;
extern s8 D_8008FE30;
extern s8 D_800E0B96;

void func_151DE81C(void) {
    D_8008FD74 = 4;
    D_800E0B96 = 0;
    if (D_8008FE30 == 0) {
        func_1500764C();
    }
}
/* Call context: func_1501C730: unique active project prototype */
void func_1501C730(s32, s32, s32, s32, s32);
extern s8 D_8008FD80;
extern s8 D_8008FDA4;
extern void *D_8008FDD4;
extern s8 D_800D2E40;
extern s8 D_800E0B94;

void func_151DE85C(void) {
    D_800D2E40 = 0;
    func_1501C730(6, 0x1D, 0, 0, 1);
    D_800E0B94 = 3;
    D_8008FD80 = 1;
    D_8008FE28 = 2;
    D_8008FDA4 = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x3E) = 0;
    *(s8 *)((u8 *)D_8008FDD4 + 0x2B) = 5;
    *(s8 *)((u8 *)D_8008FDD4 + 0x2C) = (s8) *(s8 *)((u8 *)D_8008FDD4 + 0x2B);
}
void func_151DE8E8(void) {

}
