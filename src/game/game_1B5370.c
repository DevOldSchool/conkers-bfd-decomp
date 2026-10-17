#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B5370.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_display_transition_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151880C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *, s32);
extern s32 D_800DF7B4;

typedef struct Game1B5370Fade {
    u8 color[6];
    u8 start[3];
    u8 pad9[7];
    s32 type;
    f32 rate;
    u8 work[0xC];
} Game1B5370Fade;

extern Game1B5370Fade D_800DF700[];

s32 func_15187EC0(s32 arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    if (D_800DF7B4 < 5) {
        D_800DF700[D_800DF7B4].type = arg0;
        D_800DF700[D_800DF7B4].rate = arg1;
        D_800DF700[D_800DF7B4].color[0] = D_800DF700[D_800DF7B4].start[0] = arg2;
        D_800DF700[D_800DF7B4].color[1] = D_800DF700[D_800DF7B4].start[1] = arg3;
        D_800DF700[D_800DF7B4].color[2] = D_800DF700[D_800DF7B4].start[2] = arg4;
        D_800DF700[D_800DF7B4].color[3] = arg5;
        D_800DF700[D_800DF7B4].color[4] = arg6;
        D_800DF700[D_800DF7B4].color[5] = arg7;
        func_100226F0(D_800DF700[D_800DF7B4].work, 0xC);
        D_800DF7B4++;
        return D_800DF7B4 - 1;
    }
    return -1;
}
void func_100226F0(void *arg0, s32 arg1);
extern s32 D_800DF7B4;

void func_15187F90(void) {
    func_100226F0(&D_800DF700, 0xB4);
    D_800DF7B4 = 0;
}
void func_15187FC0(s32 arg0, void *arg1) {
    void *temp_v0;

    if ((arg0 < D_800DF7B4) && (arg0 >= 0)) {
        temp_v0 = (u8 *)&D_800DF700 + (arg0 * 0x24);
        *(s32 *)((u8 *)arg1 + 0) = (s32) *(u8 *)((u8 *)temp_v0 + 6);
        *(s32 *)((u8 *)arg1 + 4) = (s32) *(u8 *)((u8 *)temp_v0 + 7);
        *(s32 *)((u8 *)arg1 + 8) = (s32) *(u8 *)((u8 *)temp_v0 + 8);
    }
}
extern f32 D_800DF70C[];

void func_15188010(s32 arg0, f32 *arg1) {
    if ((arg0 < D_800DF7B4) && (arg0 >= 0)) {
        *arg1 = *(f32 *)((u8 *)D_800DF70C + (arg0 * 0x24));
    }
}
void func_1518804C(s32 arg0, f32 arg1) {
    if ((arg0 < D_800DF7B4) && (arg0 >= 0)) {
        if (arg1 > 1.0f) {
            arg1 = 1.0f;
        } else if (arg1 < 0.0f) {
            arg1 = 0.0f;
        }
        *(f32 *)((u8 (*)[0x24])D_800DF70C)[arg0] = arg1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5370/func_151880C0.s")
