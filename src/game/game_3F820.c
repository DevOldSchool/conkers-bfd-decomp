#include "types.h"

/*
 * Reviewed source unit: src/game/game_3F820.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_next_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150124A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1518AADC(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_80088750;

void func_151EF954(void *, f32, f32, f32, f32, f32, f32, f32);
extern s32 D_80082FA0;
extern u8 *D_800BE628;
extern u8 D_800DCC10[];
extern f32 D_80096560;

void func_15012370(void) {
    s32 i;
    f32 foo;

    i = 0;
    if (D_80082FA0 >= 0) {
        foo = D_80096560;
        do {
            func_151EF954((void *)((u8 *)D_800DCC10 + (i << 6)),
                    -(((Cam180 *)D_800BE628)[i].unk4 * 0.5f),
                    (((Cam180 *)D_800BE628)[i].unk4 * 0.5f),
                    -(((Cam180 *)D_800BE628)[i].unk8 * 0.5f),
                    ((Cam180 *)D_800BE628)[i].unk8 * 0.5f,
                    1.0f, foo, 1.0f);
            i = (i + 1) & 0xFF;
        } while (D_80082FA0 >= i);
    }
}
void func_15012470(void) {
    D_80088750 = func_1518AADC(4, 0x12C, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_3F820/func_150124A0.s")
