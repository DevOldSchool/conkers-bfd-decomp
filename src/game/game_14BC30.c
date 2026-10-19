#include "types.h"

/*
 * Reviewed source unit: src/game/game_14BC30.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_callback_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511E780
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_14BC30/func_1511E780.s")
extern s32 D_800BE9E4;

void func_1511EC50(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 var_fv1;

    if (*(s32 *)((u8 *)arg0 + 0x7C) == 0) {
        *(f32 *)((u8 *)arg0 + 0x84) = (f32) *(s16 *)((u8 *)arg0 + 0x12);
    }
    var_fv1 = (f32) D_800BE9E4 * 4.0f;
    if (*(s32 *)((u8 *)arg0 + 0x3C) != 0) {
        var_fv1 *= 0.25f;
    }
    if (*(s32 *)((u8 *)arg0 + 0x80) != 0) {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x12) + var_fv1 * 5.0f);
        temp_fa0 = *(f32 *)((u8 *)arg0 + 0x84) + 500.0f;
        if (temp_fa0 < (f32) *(s16 *)((u8 *)arg0 + 0x12)) {
            *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) temp_fa0;
            *(s8 *)((u8 *)arg0 + 0x6E) = 1;
        }
    } else {
        temp_fa0_2 = *(f32 *)((u8 *)arg0 + 0x84);
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x12) - var_fv1);
        if ((f32) *(s16 *)((u8 *)arg0 + 0x12) < temp_fa0_2) {
            *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) temp_fa0_2;
        }
    }
    *(s32 *)((u8 *)arg0 + 0x7C) = 1;
}
void func_1511ED84(void *arg0) {
    f32 step;
    s32 direction;

    if (*(s32 *)((u8 *)arg0 + 0x7C) == 0) {
        *(f32 *)((u8 *)arg0 + 0x84) = (f32) *(s16 *)((u8 *)arg0 + 0x14);
    }
    step = (f32) D_800BE9E4 * 4.0f;
    direction = 1 - (*(u8 *)((u8 *)arg0 + 0x72) & 1);
    if (*(s32 *)((u8 *)arg0 + 0x80) != 0) {
        if (direction & 1) {
            *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x14) + step);
            if (*(f32 *)((u8 *)arg0 + 0x84) < (f32) *(s16 *)((u8 *)arg0 + 0x14)) {
                *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x84);
            }
        } else {
            *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x14) - step);
            if ((f32) *(s16 *)((u8 *)arg0 + 0x14) < *(f32 *)((u8 *)arg0 + 0x84)) {
                *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x84);
            }
        }
    } else if (direction & 1) {
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x14) - step);
        if ((f32) *(s16 *)((u8 *)arg0 + 0x14) < (*(f32 *)((u8 *)arg0 + 0x84) - 350.0f)) {
            *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x84) - 350.0f);
        }
    } else {
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x14) + step);
        if ((*(f32 *)((u8 *)arg0 + 0x84) + 350.0f) < (f32) *(s16 *)((u8 *)arg0 + 0x14)) {
            *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x84) + 350.0f);
        }
    }
    *(s32 *)((u8 *)arg0 + 0x7C) = 1;
}
