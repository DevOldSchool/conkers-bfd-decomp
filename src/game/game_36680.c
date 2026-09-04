#include "types.h"

/*
 * Reviewed source unit: src/game/game_36680.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150091D0
 * - func_150092DC
 * - func_15009334
 * - func_150095D8
 * - func_15009600
 * - func_15009628
 * - func_1500969C
 * - func_150096C4
 * - func_15009740
 * - func_15009768
 * - func_150097A4
 * - func_150097CC
 * - func_15009818
 * - func_15009844
 * - func_15009870
 * - func_15009894
 * - func_150098D0
 * - func_150098F8
 * - func_15009944
 * - func_15009990
 * - func_15009A38
 * - func_15009AA0
 * - func_15009AEC
 * - func_15009B38
 * - func_15009B84
 * - func_15009BD0
 * - func_15009C7C
 * - func_15009D28
 * - func_15009D6C
 * - func_15009DB0
 * - func_15009DFC
 * - func_15009E48
 * - func_15009E84
 * - func_15009EC8
 * - func_15009EF4
 * - func_15009F30
 * - func_15009F74
 * - func_1500A028
 * - func_1500A06C
 * - func_1500A0B0
 * - func_1500A0FC
 * - func_1500A148
 * - func_1500A194
 * - func_1500A1E0
 * - func_1500A21C
 * - func_1500A260
 * - func_1500A2AC
 * - func_1500A2F4
 * - func_1500A33C
 * - func_1500A380
 * - func_1500A3C4
 * - func_1500A410
 * - func_1500A454
 * - func_1500A490
 * - func_1500A4D4
 * - func_1500A518
 * - func_1500A55C
 * - func_1500A5A8
 * - func_1500A5F4
 * - func_1500A640
 * - func_1500A68C
 * - func_1500A6D8
 * - func_1500A79C
 * - func_1500A7E8
 * - func_1500A8C8
 * - func_1500A904
 * - func_1500A94C
 * - func_1500A990
 * - func_1500AB5C
 * - func_1500ABA0
 * - func_1500AC14
 * - func_1500AD84
 * - func_1500AF08
 * - func_1500B1F4
 * - func_1500B3B0
 * - func_1500B714
 * - func_1500B8F4
 * - func_1500BAB8
 * - func_1500BC7C
 * - func_1500BE40
 * - func_1500BE68
 * - func_1500BEC0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150091D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150092DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009334.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150095D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009600.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009628.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500969C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150096C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009768.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150097A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150097CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009818.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009844.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009870.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009894.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150098D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150098F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009944.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009990.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009A38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009AA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009AEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009B38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009B84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009BD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009C7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009D28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009D6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009DB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009DFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009E48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009E84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009EC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009EF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009F30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009F74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A028.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A06C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A0B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A0FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A148.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A194.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A1E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A21C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A2AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A2F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A33C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A380.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A3C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A410.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A454.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A490.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A4D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A518.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A55C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A5A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A5F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A640.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A68C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A6D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A79C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A7E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A8C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A904.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A94C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A990.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500AB5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500ABA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500AC14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500AD84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500AF08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B1F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B3B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B714.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B8F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BAB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BC7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BE40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BE68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BEC0.s")
