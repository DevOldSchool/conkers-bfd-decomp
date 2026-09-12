#include "types.h"

/*
 * Reviewed source unit: src/game/game_127060.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F9BB0
 * - func_150FA1B8
 * - func_150FA468
 * - func_150FA520
 * - func_150FAA40
 * - func_150FAAEC
 * - func_150FADC8
 * - func_150FAE18
 * - func_150FB188
 * - func_150FB1E8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150F9BB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA1B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FAA40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FAAEC.s")
extern void func_1516972C(s32 arg0);

void func_150FACE4(s32 arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0x4E) || (arg2 == 0x4F)) {
        func_1516972C(arg0);
    }
}
void func_1515F170(s32, s32);
void func_151494E0(s32, s32);
extern s32 D_800D3098;

void func_150FAD28(void) {
    func_1515F170(8, 0);
    func_1515F170(0xB, 1);
    func_151494E0(D_800D3098 + 0x514, 0x30);
    func_151494E0(0, 0x4D);
}
void func_150FAD78(void) {
    func_1515F170(8, 1);
    func_1515F170(7, 0);
    func_151494E0(D_800D3098 + 0x514, 0x31);
    func_151494E0(0, 0x4C);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FADC8 CURRENT (639) */
void func_150FADC8(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_t6;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x53) {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 2);
        return;
    }
    if (temp_t6 == 0x54) {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) & ~2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FADC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FADC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FAE18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FB188.s")
void func_15157F80(s32, s32, s32, s32, s32);
s32 func_151D710C(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FB1E8 CURRENT (452) */
void func_150FB1E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_15157F80(func_151D710C(arg1, arg2, arg3, arg4), arg1, arg2, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FB1E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FB1E8.s")
