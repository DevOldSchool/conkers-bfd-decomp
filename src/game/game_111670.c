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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E41C0 CURRENT (2357) */
void func_150E41C0(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 zero;
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
    zero = 0.0f;
    x = (s32)((f32)x + (zero + (depth * trig)));
    z = (s32)((f32)z + ((depth * cosine) - zero));
    y = (s32)((f32)y + horizontal);
    D_800D99F0[0] = x;
    D_800D99F0[2] = z;
    D_800D99F0[1] = y;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E41C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E41C0.s")
/* Call context: func_1510F8CC: matched US definition in src/game/game_13BB20.c */
s32 func_1510F8CC(s32);

s32 func_150ADA20(void);                                /* extern */
void func_150E4550(f32, f32, f32, s32, s32, s32, s32); /* extern */
s32 func_1510F8D8(s32, s32, s32, s32 *);        /* extern */
extern f32 D_800A1060;
extern s32 D_800DBE3C;
extern s32 D_800DBE4C;
extern s32 *D_800DBE5C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E42F8 CURRENT (80) */
void func_150E42F8(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_a2;
    s32 sp70;
    s32 temp_v0_2;
    s32 sp68;
    s32 temp_lo;
    s32 var_s3;
    f32 temp_fs0;
    s32 sp58;

    sp58 = 0;
    var_s3 = 0;
    sp70 = (s32) D_800D99F0[0];
    sp68 = (s32) D_800D99F0[2];
    if (arg0 > 0) {
        temp_fs0 = D_800A1060;
        do {
            temp_s0 = (func_150ADA20() % 500) + sp70;
            temp_a2 = (func_150ADA20() % 500) + sp68;
            temp_v0 = func_1510F8D8(temp_s0, 0x2710, temp_a2, &sp58);
            if ((temp_fs0 != (f32) temp_v0) && (sp58 != 0)) {
                temp_lo = (s32) (sp58 - D_800DBE3C) / 12;
                if ((temp_lo >= 0) && (temp_lo < D_800DBE4C)) {
                    temp_v0_2 = func_1510F8CC(D_800DBE5C[temp_lo]);
                    if (temp_v0_2 != 0) {
                        func_150E4550((f32) temp_s0, (f32) temp_v0, (f32) temp_a2, 0, temp_v0_2, sp58, 0xFF);
                    }
                }
            }
            var_s3 += 1;
        } while (var_s3 != arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E42F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E42F8.s")
void func_150E4514(s32 arg0) {
    func_150E41C0();
    func_150E42F8(arg0 / 30);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4550.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4928.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E4CBC CURRENT (175) */
void func_150E4CBC(void *arg0) {
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_a1;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x90);
    if (temp_v0 < 9) {
        *(s16 *)((u8 *)arg0 + 0xA4) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x96) * ((s32) (temp_v0 * 0x5A) / 9)) * 0.00390625f);
    } else {
        temp_a1 = *(u8 *)((u8 *)arg0 + 0xB4);
        *(s16 *)((u8 *)arg0 + 0xA4) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x96) * (0x5A - ((s32) ((temp_v0 * 0x5A) - 0x32A) / 600))) * 0.00390625f);
        temp_t0 = D_800BE9E4 * 0x11;
        if (temp_t0 < (s32) temp_a1) {
            *(u8 *)((u8 *)arg0 + 0xB4) = (u8) (temp_a1 - temp_t0);
            temp_v0 = *(s32 *)((u8 *)arg0 + 0x90);
        } else {
            *(s16 *)((u8 *)arg0 + 0x98) = -1;
            temp_v0 = *(s32 *)((u8 *)arg0 + 0x90);
        }
    }
    *(s16 *)((u8 *)arg0 + 0xA2) = (s16) ((s32) ((f32) *(s16 *)((u8 *)arg0 + 0x94) * 14.0f) >> 8);
    if (temp_v0 >= 0x261) {
        *(s16 *)((u8 *)arg0 + 0x98) = -1;
        temp_v0 = *(s32 *)((u8 *)arg0 + 0x90);
    }
    *(s32 *)((u8 *)arg0 + 0x90) = (s32) (temp_v0 + D_800BE9E4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E4CBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4CBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4E04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E5558.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E5810.s")
