#include "types.h"

/*
 * Reviewed source unit: src/game/game_137ED0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510AA44
 * - func_1510ADD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1510AA20(s32 arg0) {
    func_15179008(0);
}
/* Call context: func_15114D24: unique active declaration in the allowed source */
void func_15114D24(s32, s32, s32, s16, s32, s32);
extern s32 D_800BE3E4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510AA44 CURRENT (4588) */
void func_1510AA44(void *arg0) {
    s32 sp38;
    f32 sp24;
    f32 temp_fv1;
    s32 temp_ft0;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_t2;
    s32 temp_t9;
    s32 temp_v0;
    s32 var_t0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u32 temp_hi;

    var_v0 = *(s32 *)((u8 *)arg0 + 0x3C);
    var_v1 = (s32) (var_v0 / 3600) % 60;
    if ((*(s32 *)((u8 *)arg0 + 0x84) == 0) && (D_800BE3E4 != 0)) {
        *(s32 *)((u8 *)arg0 + 0x84) = 1;
        temp_hi = (u32) (D_800BE3E4 * 0xB4) % 43200U;
        *(s32 *)((u8 *)arg0 + 0x3C) = (s32) temp_hi;
        temp_lo = temp_hi * 0x3C;
        var_v0 = temp_lo;
        *(s32 *)((u8 *)arg0 + 0x3C) = temp_lo;
        var_v1 = (s32) (temp_lo / 3600) % 60;
    }
    if (var_v1 < 0) {
        var_v1 += 0x3C;
    }
    temp_t9 = var_v0 + D_800BE9E4;
    *(s32 *)((u8 *)arg0 + 0x3C) = temp_t9;
    var_v0_2 = temp_t9;
    if (temp_t9 >= 0x278D00) {
        temp_t2 = var_v0_2 + 0xFFD87300;
        *(s32 *)((u8 *)arg0 + 0x3C) = temp_t2;
        var_v0_2 = temp_t2;
    }
    temp_lo_2 = var_v0_2 / 60;
    temp_fv1 = (f32) (temp_lo_2 / 300) * 2.5f;
    if (temp_fv1 > 360.0f) {
        *(s32 *)((u8 *)arg0 + 0x3C) = (s32) (var_v0_2 + 0xFFD87300);
    }
    var_t0 = (s32) (temp_lo_2 / 60) % 60;
    if (var_t0 < 0) {
        var_t0 += 0x3C;
    }
    if (var_v1 != var_t0) {
        temp_lo_3 = var_t0 / 15;
        if (temp_lo_3 != (var_v1 / 15)) {
            if (!(temp_lo_3 & 3)) {
                temp_ft0 = (s32) (temp_fv1 / 30.0f);
                *(s32 *)((u8 *)arg0 + 0x7C) = temp_ft0;
                if (temp_ft0 == 0) {
                    *(s32 *)((u8 *)arg0 + 0x7C) = 0xC;
                }
            } else {
                *(s32 *)((u8 *)arg0 + 0x7C) = 1;
            }
            *(s32 *)((u8 *)arg0 + 0x80) = -1;
        }
    }
    temp_v0 = *(s32 *)((u8 *)arg0 + 0x7C);
    if ((temp_v0 != 0) && (temp_lo_2 != *(s32 *)((u8 *)arg0 + 0x80))) {
        *(s32 *)((u8 *)arg0 + 0x80) = temp_lo_2;
        *(s32 *)((u8 *)arg0 + 0x7C) = (s32) (temp_v0 - 1);
        sp24 = temp_fv1;
        sp38 = var_t0;
        func_15114D24((s32) arg0, 0x4CC, 0x7FFF, 0xC8, 0x3E8, 0xC);
    }
    *(f32 *)((u8 *)arg0 + 0x68) = 5.0f;
    *(f32 *)((u8 *)arg0 + 0x108) = 5.0f;
    *(f32 *)((u8 *)arg0 + 0xA8) = (f32) -temp_fv1;
    *(f32 *)((u8 *)arg0 + 8) = (f32) -((f32) var_t0 * 6.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510AA44 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_137ED0/func_1510AA44.s")
/* Call context: func_15114D24: unique active project prototype */
void func_15114D24(s32, s32, s32, s16, s32, s32);
f32 func_15047C00(f32);                             /* extern */
extern f32 D_800A26B0;
extern f32 D_800A26B4;
extern f32 D_800A26B8;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510ADD8 CURRENT (1170) */
void func_1510ADD8(void *arg0) {
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg0 + 0x80) = (f32) (*(f32 *)((u8 *)arg0 + 0x80) + ((D_800A26B0 * (f32) D_800BE9E4) / 60.0f));
    temp_fv1 = func_15047C00(*(f32 *)((u8 *)arg0 + 0x80)) * 10.0f;
    temp_ft4 = *(f32 *)((u8 *)arg0 + 0) - temp_fv1;
    *(f32 *)((u8 *)arg0 + 0) = temp_fv1;
    *(f32 *)((u8 *)arg0 + 0x60) = temp_ft4;
    if (*(s32 *)((u8 *)arg0 + 0x7C) == 0) {
        if (D_800A26B4 <= *(f32 *)((u8 *)arg0 + 0x80)) {
            *(s32 *)((u8 *)arg0 + 0x7C) = 1;
            func_15114D24((s32) arg0, 0x4CA, 0x2EE0, 0xC8, 0x3E8, 4);
        }
    } else {
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x80);
        if (D_800A26B8 <= temp_fv0) {
            *(s32 *)((u8 *)arg0 + 0x7C) = 0;
            *(f32 *)((u8 *)arg0 + 0x80) = (f32) (temp_fv0 - D_800A26B8);
            func_15114D24((s32) arg0, 0x4CB, 0x2EE0, 0xC8, 0x3E8, 4);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510ADD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_137ED0/func_1510ADD8.s")
