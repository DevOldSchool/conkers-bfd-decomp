#include "types.h"

/*
 * Reviewed source unit: src/game/game_111670.c
 * Boundary evidence: docs/evidence/game_raw_state_resource_helpers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E41C0
 * - func_150E42F8
 * - func_150E4550
 * - func_150E4928
 * - func_150E4CBC
 * - func_150E4E04
 * - func_150E5558
 * - func_150E5810
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15047D60(f32);
f32 func_15047C00(f32);
extern s16 D_800D99F0[];
extern void *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E41C0 CURRENT (2857) */
void func_150E41C0(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 horizontal;
    f32 depth;
    f32 trig;
    f32 cosine;
    f32 angle;

    x = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
    y = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x2FC);
    z = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x300);
    angle = *(f32 *)((u8 *)D_800DBFF0 + 0x398);
    trig = func_15047D60(angle);
    cosine = func_15047C00(angle);
    horizontal = 500.0f * trig;
    depth = -500.0f * cosine;
    angle = *(f32 *)((u8 *)D_800DBFF0 + 0x3A0);
    trig = func_15047D60(angle);
    cosine = func_15047C00(angle);
    D_800D99F0[0] = (s16)(s32)((f32)x +
                                     (0.0f + (depth * trig)));
    D_800D99F0[2] =
        (s16)(s32)((f32)z + ((depth * cosine) - 0.0f));
    D_800D99F0[1] = (s16)(s32)((f32)y + horizontal);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E41C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E41C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E42F8.s")
void func_150E4514(s32 arg0) {
    func_150E41C0();
    func_150E42F8(arg0 / 30);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4550.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4928.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E4CBC CURRENT (480) */
void func_150E4CBC(void *arg0) {
    s32 temp_t0;
    s32 temp_v0;
    u8 temp_a1;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x90);
    if (temp_v0 < 9) {
        *(s16 *)((u8 *)arg0 + 0xA4) = (s16) (s32) ((f32) (((s32) (temp_v0 * 0x5A) / 9) * *(s16 *)((u8 *)arg0 + 0x96)) * 0.00390625f);
    } else {
        temp_a1 = *(u8 *)((u8 *)arg0 + 0xB4);
        *(s16 *)((u8 *)arg0 + 0xA4) = (s16) (s32) ((f32) ((0x5A - ((s32) ((temp_v0 * 0x5A) - 0x32A) / 600)) * *(s16 *)((u8 *)arg0 + 0x96)) * 0.00390625f);
        temp_t0 = D_800BE9E4 * 0x11;
        if (temp_t0 < (s32) temp_a1) {
            *(u8 *)((u8 *)arg0 + 0xB4) = (u8) (temp_a1 - temp_t0);
        } else {
            *(s16 *)((u8 *)arg0 + 0x98) = -1;
        }
    }
    *(s16 *)((u8 *)arg0 + 0xA2) = (s16) ((s32) ((f32) *(s16 *)((u8 *)arg0 + 0x94) * 14.0f) >> 8);
    if (*(s32 *)((u8 *)arg0 + 0x90) >= 0x261) {
        *(s16 *)((u8 *)arg0 + 0x98) = -1;
    }
    *(s32 *)((u8 *)arg0 + 0x90) = (s32) (*(s32 *)((u8 *)arg0 + 0x90) + D_800BE9E4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E4CBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4CBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4E04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E5558.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E5810.s")
