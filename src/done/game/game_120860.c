#include "types.h"

/*
 * Reviewed source unit: src/game/game_120860.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_isolated_selectors_and_calls.md
 */

extern void *D_800DBFF0;

typedef struct Game120860Flags {
    u8 pad0[0x4F];
    u8 bits : 7;
    u8 flag : 1;
} Game120860Flags;

void func_150F33B0(Game120860Flags *arg0) {
    if (*(f32 *)((u8 *)D_800DBFF0 + 0x300) < -2000.0f) {
        arg0->flag = 0;
        return;
    }
    arg0->flag = 1;
}
extern f32 D_800A1970;
extern s16 *D_800D9A40;

void func_150F33F8(s32 arg0) {
    u8 *temp_v0;

    temp_v0 = (void *)(((u8 *)D_800DBFF0) + (arg0 * 0x9A0));
    if (*(f32 *)((u8 *)temp_v0 + 0x300) < D_800A1970) {
        if (*(f32 *)((u8 *)temp_v0 + 0x2FC) > 840.0f) {
            *D_800D9A40 |= 1 << arg0;
            return;
        }
        *D_800D9A40 &= ~(1 << arg0);
    }
}
