#include "types.h"

/*
 * Reviewed source unit: src/game/game_130240.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15102D90
 * - func_15102EB8
 * - func_15103254
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15145EA4(s32 *, s32 *, s32, s32);
void *func_1503195C(void *, s32, s32);
s32 func_1514654C(void *, s32, s32, void **, void **, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15102D90 CURRENT (2238) */
s32 func_15102D90(void *arg0) {
    void *sp40[2];
    void *sp38[2];
    s16 temp_a1;
    void *temp_v0;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s1 = *(u8 **)((u8 *)arg0 + 0x110);
    *(u8 *)((u8 *)arg0 + 0x124) &= 0xFFFE;
    if ((*(u8 *)((u8 *)arg0 + 0x114) != temp_s1[0x3B]) ||
        (*(s32 *)temp_s1 == 0)) {
        return 0;
    }
    if ((*(s32 *)(temp_s1 + 0x1D4) == 0) ||
        ((temp_s1[0x74] & 0xF) == 0xF)) {
        return 1;
    }
    temp_s0 = (u8 *)arg0 + 0x110;
    sp40[0] = (u8 *)arg0 + 0x34;
    sp40[1] = (u8 *)arg0 + 0x40;
    sp38[0] = temp_s0 + 0x18;
    sp38[1] = temp_s0 + 0x24;
    temp_a1 = *(s16 *)(temp_s0 + 0xC);
    if (temp_a1 != -1) {
        temp_v0 = func_1503195C(temp_s1, temp_a1, 0);
        if (temp_v0 == 0) {
            return 0;
        }
        if (func_1514654C(temp_s1, (s32)temp_v0,
                          *(s32 *)(temp_s0 + 0x10), sp40, sp38, 2) == 0) {
            return 0;
        }
        goto block_12;
    }
    func_15145EA4((s32 *)sp40, (s32 *)sp38,
                  *(s32 *)(temp_s1 + 0x1D4) + *(s32 *)(temp_s0 + 8), 2);
block_12:
    temp_s0[0x14] |= 1;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15102D90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_130240/func_15102D90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_130240/func_15102EB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_130240/func_15103254.s")
