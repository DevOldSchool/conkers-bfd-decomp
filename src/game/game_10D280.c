#include "types.h"

/*
 * Reviewed source unit: src/game/game_10D280.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DFDD0
 * - func_150DFEFC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[0x13];
    s8 state;
    u8 pad14[0x10];
    s8 **commands;
} Game10D280Object;

typedef struct {
    u8 pad0[0x2D8];
    f32 timer;
    f32 scale;
    u8 pad2E0[0xC];
    s32 active;
} Game10D280State;

extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DFDD0 CURRENT (1395) */
s32 func_150DFDD0(Game10D280Object *arg0, Game10D280State *arg1) {
    f32 timer;
    f32 intensity;
    s32 index;
    s32 tile;
    volatile s8 *commands;
    u32 *command;

    if (arg1->active != 0) {
        arg0->state = 2;
        arg1->timer = arg1->timer - D_800BE9A4;
        timer = arg1->timer;
        if (timer < 0.0f) {
            arg1->active = 0;
            return 1;
        }
        intensity = 1.0f - (arg1->scale * timer);
    } else {
        intensity = 0.0f;
        arg0->state = 0;
    }

    commands = *arg0->commands;
    if (commands != 0) {
        index = 0;
        if (*commands != -0xE) {
            do {
                index++;
            } while (*(commands + (index * 8)) != -0xE);
        }
        command = (u32 *) ((s8 *) commands + (index * 8));
        tile = 2 - ((s32) ((*command >> 12) & 0xFFF) / 3);
        if (tile < 0) {
            do {
                tile += 0x40;
            } while (tile < 0);
        }
        *command = (((s32) ((500.0f * intensity) + 2.0f) & 0xFFF) << 12) |
                   0xF2000000 | (tile & 0xFFF);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DFDD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D280/func_150DFDD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D280/func_150DFEFC.s")
void func_150E02C0(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
