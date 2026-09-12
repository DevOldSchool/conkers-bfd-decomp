#include "types.h"

/*
 * Reviewed source unit: src/game/game_BC510.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1508F060
 * - func_1508F0D4
 * - func_1508F7BC
 * - func_1508F9F4
 * - func_1508FD38
 * - func_150900F0
 * - func_15090630
 * - func_1509093C
 * - func_150911F4
 * - func_15091534
 * - func_150916B4
 * - func_150918EC
 * - func_15093818
 * - func_150938BC
 * - func_15093B58
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800D2460[][0x10];
extern s8 D_800D246D;
extern s8 D_800D247D;
extern s32 D_800D24C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508F060 CURRENT (625) */
void func_1508F060(void) {
    s32 temp_v0;
    u8 *temp_v1;

    D_800D246D = 0;
    D_800D247D = 0;
    temp_v0 = 2;
    temp_v1 = D_800D2460[temp_v0];
    temp_v1[0x1D] = 0;
    temp_v1[0x2D] = 0;
    temp_v1[0x3D] = 0;
    temp_v1[0xD] = 0;
    D_800D24C0 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508F060 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F060.s")
void func_1508F0A4(void) {
    func_1508F0D4();
    func_1508F9F4();
    func_1509093C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F0D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F7BC.s")
extern f32 D_800D2410[];
extern u8 D_800D2456;

void func_1508F9C4(void) {
    D_800D2410[D_800D2456] = 0.0f;
    D_800D2456 += 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F9F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508FD38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150900F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15090630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1509093C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150911F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15091534.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150916B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150918EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15093818.s")
extern void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_1518C900(s32 arg0);
extern s32 D_800D2448;
extern void *D_800D244C;

void func_15093878(void) {
    D_800D2448 = func_1518C900(0xBA);
    D_800D244C = func_10003C40(0x80, 1, 1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150938BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15093B58.s")
