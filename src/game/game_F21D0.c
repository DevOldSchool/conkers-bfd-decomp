#include "types.h"

/*
 * Reviewed source unit: src/game/game_F21D0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C4D20
 * - func_150C4E9C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameF21D0Mover {
    f32 angle;
    u8 pad04[0xC];
    s16 field10;
    s16 field12;
    s16 field14;
    u8 pad16[0x39];
    u8 flags;
    u8 pad50[0x10];
    f32 velocity;
    u8 pad64[0x18];
    s32 timer;
} GameF21D0Mover;

s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_15048A40(s32);
extern f32 D_800A03F0;
extern f32 D_800A03F4;
extern f32 D_800A03F8;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C4D20 CURRENT (3828) */
void func_150C4D20(GameF21D0Mover *arg0) {
    f32 sp44;
    s32 sp38;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_ft0;
    s32 var_v0;

    var_fv0 = arg0->angle;
    if (var_fv0 > 180.0f) {
        var_fv0 -= 360.0f;
    }
    var_v0 = arg0->timer + D_800BE9E4;
    temp_fa0 = (f32)var_v0;
    temp_fv1 = arg0->velocity - (var_fv0 * D_800A03F0);
    if (temp_fa0 >= 256.0f) {
        temp_ft0 = (s32)(temp_fa0 - 256.0f);
        sp44 = temp_fv1;
        sp38 = temp_ft0;
        func_10010F88(0xF, 0x55F0U, 0, 0, 0, arg0->field10, arg0->field12, arg0->field14, 0x1F4, 0x3E8);
        var_v0 = temp_ft0;
    }
    arg0->timer = var_v0;
    sp44 = temp_fv1;
    var_fv1 = temp_fv1 + (func_15048A40(var_v0 & 0xFF) * D_800A03F4);
    if ((arg0->flags & 4) == 4) {
        var_fv1 += D_800A03F4;
    }
    temp_fv1_2 = var_fv1 * D_800A03F8;
    arg0->velocity = temp_fv1_2;
    arg0->angle = arg0->angle + temp_fv1_2;
    temp_fv0 = arg0->angle;
    if (temp_fv0 < 0.0f) {
        arg0->angle = temp_fv0 + 360.0f;
        return;
    }
    if (temp_fv0 >= 360.0f) {
        arg0->angle = temp_fv0 - 360.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C4D20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F21D0/func_150C4D20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F21D0/func_150C4E9C.s")
void func_1516972C(s32);
extern s32 D_800D98D0;
extern s32 D_800D98E0;

void func_150C522C(void) {
    s32 *var_s0;
    s32 *var_s1;
    s32 temp_a0;

    var_s1 = (var_s0 = &D_800D98D0, &D_800D98E0);
    do {
        temp_a0 = *var_s0;
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        var_s0++;
        var_s0[-1] = 0;
    } while (var_s0 != var_s1);
}
