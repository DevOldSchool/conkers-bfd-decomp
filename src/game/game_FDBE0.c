#include "types.h"

/*
 * Reviewed source unit: src/game/game_FDBE0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D0730
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_150A29C8(s32, s32);
u32 func_150ADA20(void);
void func_151827D0(void);
extern s32 D_800BE9E4;
extern s32 D_800D3098;
extern u8 D_800D98F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D0730 CURRENT (60) */
void func_150D0730(s32 arg0) {
    s32 selected = 0;
    u32 random;
    u8 *entry;

    func_151827D0();
    if (D_800D98F0 != 0) {
        if (D_800BE9E4 < (s32)D_800D98F0) {
            D_800D98F0 -= D_800BE9E4;
            return;
        }
        D_800D98F0 = 0;
        return;
    }
    if (func_150A29C8(0, 0x15) == 0) {
        selected = 0x15;
    } else if (func_150A29C8(0, 0x1A) == 0) {
        selected = 0x1A;
    } else if (func_150A29C8(0, 0x1B) == 0) {
        selected = 0x1B;
    } else if (func_150A29C8(0, 0x1C) == 0) {
        selected = 0x1C;
    } else if (func_150A29C8(0, 0x1D) == 0) {
        selected = 0x1D;
    } else if (func_150A29C8(0, 0x20) == 0) {
        selected = 0x20;
    }
    if (selected != 0) {
        D_800D98F0 = (func_150ADA20() & 0x7F) + 0x80;
        random = func_150ADA20();
        entry = (u8 *)(D_800D3098 + (selected * 0x34));
        func_10010F88((random % 3U) + 0x6C, 0x5DC0U, 0, 0, 0,
                      *(s16 *)(entry + 0), *(s16 *)(entry + 2),
                      *(s16 *)(entry + 4), 0x320, 0x5DC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D0730 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FDBE0/func_150D0730.s")
