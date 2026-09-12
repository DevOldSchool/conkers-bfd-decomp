#include "types.h"

/*
 * Reviewed source unit: src/game/game_183640.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15156190
 * - func_15156388
 * - func_151563B8
 * - func_151564F8
 * - func_151568F8
 * - func_15156B54
 * - func_15156D24
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156190.s")
void func_15156190(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15156388 CURRENT (510) */
void func_15156388(s32 arg0, s32 arg1, s32 arg2) {
    func_15156190(arg0, arg1 & 0xFF, arg2, 0xFF, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15156388 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156388.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151563B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151564F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151568F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156B54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156D24.s")
void func_15156F94(s32 arg0) {
    func_151D5E30(arg0 + 0x88, arg0);
}
void func_15169804(s32);

void func_15156FB8(s32 arg0) {
    func_15156F94(arg0);
    func_15169804(arg0);
}
void func_15169824(s32 arg0);

void func_15156FE4(s32 arg0) {
    func_15156F94(arg0);
    func_15169824(arg0);
}
