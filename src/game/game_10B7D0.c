#include "types.h"

/*
 * Reviewed source unit: src/game/game_10B7D0.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DE32C
 * - func_150DE458
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150DE320(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B7D0/func_150DE32C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B7D0/func_150DE458.s")
f32 func_15048A40(s32);                             /* extern */
extern f32 D_800A0D48;
extern f32 D_800A0D4C;
extern f32 D_800A0D50;
extern f32 D_800A0D54;
extern s32 D_800BE9E4;

void func_150DE6D8(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((func_15048A40(((s32) *(s32 *)((u8 *)arg0 + 0x7C) >> 3) & 0xFF) * D_800A0D48) + D_800A0D4C);
    *(f32 *)((u8 *)arg0 + 0) = (f32) (func_15048A40(((s32) *(s32 *)((u8 *)arg0 + 0x80) >> 3) & 0xFF) * D_800A0D50);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (func_15048A40(((s32) *(s32 *)((u8 *)arg0 + 0x84) >> 3) & 0xFF) * D_800A0D54);
    *(s32 *)((u8 *)arg0 + 0x7C) = (s32) (*(s32 *)((u8 *)arg0 + 0x7C) + (D_800BE9E4 * 0xC));
    *(s32 *)((u8 *)arg0 + 0x80) = (s32) (*(s32 *)((u8 *)arg0 + 0x80) + (D_800BE9E4 * 0x10));
    *(s32 *)((u8 *)arg0 + 0x84) = (s32) (*(s32 *)((u8 *)arg0 + 0x84) + (D_800BE9E4 * 0x18));
}
