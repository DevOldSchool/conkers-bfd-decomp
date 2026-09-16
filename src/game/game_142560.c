#include "types.h"

/*
 * Reviewed source unit: src/game/game_142560.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151152A8
 * - func_15115368
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151150B0(s32 arg0) {

}
extern s32 D_800BE9E4;

typedef struct Game142560Rotation {
    f32 angleX;
    f32 angleY;
    f32 angleZ;
    u8 pad0C[0x30];
    s32 packedSpeed;
    u8 pad40[0x20];
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
} Game142560Rotation;

void func_151150BC(Game142560Rotation *arg0) {
    f32 angle;
    f32 full_turn = 360.0f;

    arg0->deltaZ = ((arg0->packedSpeed >> 16) * D_800BE9E4) * 0.00390625f;
    arg0->angleZ = arg0->angleZ + arg0->deltaZ;
    angle = arg0->angleZ;
    if (angle < 0.0f) {
        arg0->angleZ = angle + full_turn;
        return;
    }
    if (angle >= full_turn) {
        arg0->angleZ = angle - full_turn;
    }
}

void func_1511515C(Game142560Rotation *arg0) {
    f32 angle;
    f32 full_turn = 360.0f;

    arg0->deltaY = ((arg0->packedSpeed >> 16) * D_800BE9E4) * 0.00390625f;
    arg0->angleY = arg0->angleY + arg0->deltaY;
    angle = arg0->angleY;
    if (angle < 0.0f) {
        arg0->angleY = angle + full_turn;
        return;
    }
    if (angle >= full_turn) {
        arg0->angleY = angle - full_turn;
    }
}

void func_151151FC(Game142560Rotation *arg0) {
    f32 angle;
    f32 full_turn = 360.0f;

    arg0->deltaX = ((arg0->packedSpeed >> 16) * D_800BE9E4) * 0.00390625f;
    arg0->angleX = arg0->angleX + arg0->deltaX;
    angle = arg0->angleX;
    if (angle < 0.0f) {
        arg0->angleX = angle + full_turn;
        return;
    }
    if (angle >= full_turn) {
        arg0->angleX = angle - full_turn;
    }
}

void func_1511529C(s32 arg0) {

}
extern f32 D_800A2F8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151152A8 CURRENT (130) */
void func_151152A8(void *arg0) {
    s16 temp_v1;
    s32 temp_a1;
    s32 var_v0;

    var_v0 = *(s32 *)((u8 *)arg0 + 0x7C);
    if (var_v0 == 0) {
        var_v0 = (s32) *(s16 *)((u8 *)arg0 + 0x12);
        *(s32 *)((u8 *)arg0 + 0x7C) = var_v0;
    }
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x12);
    if (*(u8 *)((u8 *)arg0 + 0x4F) & 4) {
        temp_a1 = *(s32 *)((u8 *)arg0 + 0x3C);
        if ((var_v0 - temp_v1) < (s16) temp_a1) {
            *(s16 *)((u8 *)arg0 + 0x12) = (s16) (temp_v1 - ((s16) (temp_a1 >> 0x10) * D_800BE9E4));
        }
    } else {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((f32) temp_v1 + ((f32) (var_v0 - temp_v1) * D_800A2F8C * (f32) D_800BE9E4));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151152A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151152A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15115368.s")
