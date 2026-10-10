#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_179400.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514BF9C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1514BF50(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) *(f32 *)((u8 *)arg0 + 0x34);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + 100.0f);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) *(f32 *)((u8 *)arg0 + 0x3C);
}
void func_1514BF7C(u8 *arg0) {
    func_1514BC08(arg0, arg0 + 0x110);
}
void func_1514BF9C(s32 arg0);
void func_1514BE20(s32 arg0);
typedef struct Game179400MotionVector {
    f32 x;
    f32 y;
    f32 z;
} Game179400MotionVector;

extern s32 D_800BE9E4;
extern f32 D_800BE9A4;
extern f32 D_800BE9A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514BF9C CURRENT (800) */
void func_1514BF9C(s32 arg0) {
    u8 *owner;
    u8 *extension;
    Game179400MotionVector previous;
    u32 ticks;
    f32 delta_x;
    f32 delta_y;
    f32 delta_z;

    owner = (u8 *)arg0;
    previous = *(Game179400MotionVector *)(owner + 0x148);
    extension = owner + 0x110;
    for (ticks = (u32)D_800BE9E4; ticks != 0; ticks--) {
        *(f32 *)(extension + 0x38) *= *(f32 *)(extension + 0x48);
        *(f32 *)(extension + 0x3C) *= *(f32 *)(extension + 0x48);
        *(f32 *)(extension + 0x40) *= *(f32 *)(extension + 0x48);
    }
    *(f32 *)(extension + 0x3C) += *(f32 *)(extension + 0x44) * D_800BE9A4;
    delta_x = (*(f32 *)(extension + 0x38) - previous.x) * D_800BE9A8;
    delta_y = (*(f32 *)(extension + 0x3C) - previous.y) * D_800BE9A8;
    delta_z = (*(f32 *)(extension + 0x40) - previous.z) * D_800BE9A8;
    *(f32 *)(owner + 0x34) +=
        (previous.x + ((0.5f * delta_x) * D_800BE9A4)) * D_800BE9A4;
    *(f32 *)(owner + 0x38) +=
        (previous.y + ((0.5f * delta_y) * D_800BE9A4)) * D_800BE9A4;
    *(f32 *)(owner + 0x3C) +=
        (previous.z + ((0.5f * delta_z) * D_800BE9A4)) * D_800BE9A4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514BF9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179400/func_1514BF9C.s")
s32 func_1514C258(s32 arg0) {
    func_1514BF9C(arg0);
    func_1514BE20(arg0);
    return 1;
}
s32 func_1514C288(s32 arg0) {
    func_1514BF9C(arg0);
    func_1514BF50((void *)arg0);
    return 1;
}
s32 func_1514C2B8(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x72) = 0;
    *(s8 *)((u8 *)arg0 + 0x71) = 0x24;
    *(s16 *)((u8 *)arg0 + 0x1C) = (s16) *(s16 *)((u8 *)arg0 + 0x164);
    *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 0x08000000);
    *(f32 *)((u8 *)arg0 + 0x154) = (f32) *(f32 *)((u8 *)arg0 + 0x160);
    return 1;
}
