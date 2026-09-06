#include "types.h"

/*
 * Reviewed source unit: src/game/game_144C70.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151177C0
 * - func_151179BC
 * - func_15117D3C
 * - func_15117DA4
 * - func_15117F3C
 * - func_151189AC
 * - func_15118F24
 * - func_151193AC
 * - func_151193F4
 * - func_151194D4
 * - func_151196D4
 * - func_15119938
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151177C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151179BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_15117D3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_15117DA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_15117F3C.s")
void func_151189AC(void *arg0, s32 arg1);

void func_1511896C(void *arg0) {
    func_151189AC(arg0, 0);
}
void func_1511898C(void *arg0) {
    func_151189AC(arg0, 3);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151189AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_15118F24.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151193AC CURRENT (100) */
void func_151193AC(void *arg0, void *arg1) {
    u8 temp_t1;
    u8 temp_v0;

    if ((*(s32 *)((u8 *)arg1 + 0) == 1) && (*(u8 *)((u8 *)arg1 + 0x65) == 0)) {
        temp_v0 = *(u8 *)((u8 *)arg0 + 0x73);
        if (!(temp_v0 & 3)) {
            temp_t1 = temp_v0 & 0xFFFC;
            if (!(temp_v0 & 4)) {
                *(u8 *)((u8 *)arg0 + 0x73) = temp_t1;
                *(u8 *)((u8 *)arg0 + 0x73) = (u8) (temp_t1 | 2);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151193AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151193AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151193F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151194D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151196D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_15119938.s")
