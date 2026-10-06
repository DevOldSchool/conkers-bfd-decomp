#include "types.h"

/*
 * Reviewed source unit: src/game/game_F21D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
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
f32 func_15048A40(u8);
extern f32 D_800A03F0;
extern f32 D_800A03F4;
extern f32 D_800A03F8;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C4D20 CURRENT (1731) */
void func_150C4D20(GameF21D0Mover *arg0) {
    struct {
        s32 timer;
        f32 velocity;
    } state;
    f32 angle;
    f32 elapsed;

    angle = arg0->angle;
    state.velocity = arg0->velocity;
    if (angle > 180.0f) {
        angle -= 360.0f;
    }
    state.timer = (s32)((u32)arg0->timer + (u32)D_800BE9E4);
    elapsed = (f32)state.timer;
    state.velocity -= angle * D_800A03F0;
    if (elapsed >= 256.0f) {
        state.timer = (s32)(elapsed - 256.0f);
        func_10010F88(0xF, 0x55F0U, 0, 0, 0, arg0->field10, arg0->field12, arg0->field14, 0x1F4, 0x3E8);
    }
    arg0->timer = state.timer;
    state.velocity += func_15048A40(state.timer & 0xFF) * D_800A03F4;
    if ((arg0->flags & 4) == 4) {
        state.velocity += D_800A03F4;
    }
    state.velocity *= D_800A03F8;
    arg0->velocity = state.velocity;
    arg0->angle = arg0->angle + state.velocity;
    angle = arg0->angle;
    if (angle < 0.0f) {
        arg0->angle = angle + 360.0f;
        return;
    }
    if (angle >= 360.0f) {
        arg0->angle = angle - 360.0f;
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
