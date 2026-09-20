#include "types.h"

/*
 * Reviewed source unit: src/game/game_19EDA0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151718F0
 * - func_15171BF4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_19EDA0/func_151718F0.s")
extern void func_150AEEB0(u8 *arg0, s32 arg1);
extern void func_10010154(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_150BD740(u8 *arg0, s32 arg1, s32 arg2);
extern void func_150CDBB0(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15171BF4 CURRENT (495) */
void func_15171BF4(u8 *arg0, s32 arg1) {
    u8 type;

    arg1 &= 0xFF;
    type = arg0[4];
    switch (type) {
    case 0x13:
    case 0x23:
        func_150AEEB0(arg0, arg1);
        func_10010154(0x69, arg0, 0x7D00, 0xC8, 0x7D0);
        break;
    case 0x1E:
        func_150BD740(arg0, arg1, 1);
        break;
    case 0x54:
        func_150CDBB0(arg0, arg1, 1);
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15171BF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19EDA0/func_15171BF4.s")
