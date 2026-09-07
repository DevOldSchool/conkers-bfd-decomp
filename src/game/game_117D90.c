#include "types.h"

/*
 * Reviewed source unit: src/game/game_117D90.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EA904
 * - func_150EA944
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150EA8E0(s32 arg0) {
    func_150E5AE0();
}
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EA904 CURRENT (60) */
void func_150EA904(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = D_800DBEF4 + (arg1 * 0xA0);
    if (*(u8 *)((u8 *)temp_v0 + 0x72) == 0xE0) {
        *(u8 *)((u8 *)temp_v0 + 0x73) = (u8) (*(u8 *)((u8 *)temp_v0 + 0x73) | 3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EA904 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_117D90/func_150EA904.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EA944 CURRENT (640) */
void func_150EA944(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    s32 temp_t3;
    s32 temp_v0;

    if ((*(u8 *)((u8 *)arg0 + 0x73) & 3) == 3) {
        temp_fv0 = (f32) D_800BE9E4;
        *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + (*(f32 *)((u8 *)arg0 + 0x60) * temp_fv0));
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
        if (temp_fv1 < 0.0f) {
            *(f32 *)((u8 *)arg0 + 0) = (f32) (temp_fv1 + 360.0f);
        } else if (temp_fv1 >= 360.0f) {
            *(f32 *)((u8 *)arg0 + 0) = (f32) (temp_fv1 - 360.0f);
        }
        *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + (*(f32 *)((u8 *)arg0 + 0x64) * temp_fv0));
        temp_fv1_2 = *(f32 *)((u8 *)arg0 + 4);
        if (temp_fv1_2 < 0.0f) {
            *(f32 *)((u8 *)arg0 + 4) = (f32) (temp_fv1_2 + 360.0f);
        } else if (temp_fv1_2 >= 360.0f) {
            *(f32 *)((u8 *)arg0 + 4) = (f32) (temp_fv1_2 - 360.0f);
        }
        *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + (*(f32 *)((u8 *)arg0 + 0x68) * temp_fv0));
        temp_fv1_3 = *(f32 *)((u8 *)arg0 + 8);
        if (temp_fv1_3 < 0.0f) {
            *(f32 *)((u8 *)arg0 + 8) = (f32) (temp_fv1_3 + 360.0f);
        } else if (temp_fv1_3 >= 360.0f) {
            *(f32 *)((u8 *)arg0 + 8) = (f32) (temp_fv1_3 - 360.0f);
        }
        *(s16 *)((u8 *)arg0 + 0x5C) = (s16) (*(s16 *)((u8 *)arg0 + 0x5C) - (*(s32 *)((u8 *)arg0 + 0x3C) * D_800BE9E4));
        *(s16 *)((u8 *)arg0 + 0x10) = (s16) (*(s16 *)((u8 *)arg0 + 0x10) + (*(s16 *)((u8 *)arg0 + 0x5A) * D_800BE9E4));
        temp_t3 = *(s32 *)((u8 *)arg0 + 0x7C) + (*(s16 *)((u8 *)arg0 + 0x5C) * D_800BE9E4);
        *(s32 *)((u8 *)arg0 + 0x7C) = temp_t3;
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (temp_t3 >> 3);
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) (*(s16 *)((u8 *)arg0 + 0x14) + (*(s16 *)((u8 *)arg0 + 0x5E) * D_800BE9E4));
        temp_v0 = *(u8 *)((u8 *)arg0 + 0x8A) - (D_800BE9E4 * 4);
        if (temp_v0 > 0) {
            *(u8 *)((u8 *)arg0 + 0x8A) = (u8) temp_v0;
            return;
        }
        *(s8 *)((u8 *)arg0 + 0x6E) = 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EA944 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_117D90/func_150EA944.s")
