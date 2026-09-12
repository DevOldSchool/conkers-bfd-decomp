#include "types.h"

/*
 * Reviewed source unit: src/game/game_F2820.c
 * Boundary evidence: docs/evidence/game_raw_path_owner_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C5370
 * - func_150C5470
 * - func_150C54C0
 * - func_150C5510
 * - func_150C553C
 * - func_150C5568
 * - func_150C56A4
 * - func_150C5B88
 * - func_150C5BD4
 * - func_150C5CC4
 * - func_150C5D0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5370.s")
void func_150C5430(void) {
    func_15169804();
}
void func_150C5450(void) {
    func_15169824();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5470.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C54C0.s")
/* Call context: func_150C5430: unique active project prototype */
/* Call context: func_1514EDF0: unique active project prototype */
void func_1514EDF0(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5510 CURRENT (360) */
void func_150C5510(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5430();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5510 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5510.s")
/* Call context: func_150C5450: unique active project prototype */
/* Call context: func_1514EDF0: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C553C CURRENT (360) */
void func_150C553C(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5450();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C553C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C553C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5568.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C56A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5B88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5BD4.s")
void func_1514D3B0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_150C5C74(void *arg0) {
    func_1514D3B0(arg0, 0x15, 1, 0);
}
void func_150C5C9C(void *arg0) {
    func_1514D3B0(arg0, 0x15, 2, 0);
}
extern void (*D_800887C8[])(void *, void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5CC4 CURRENT (237) */
void func_150C5CC4(void *arg0, void *arg1, s32 arg2) {
    void (*temp_v0)(void *, void *, s32);

    arg2 &= 0xFF;
    temp_v0 = D_800887C8[((u8 *)arg0)[0x38]];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5CC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5CC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5D0C.s")
