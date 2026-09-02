#include "types.h"

/*
 * Reviewed source unit: src/game/game_2DF70.c
 * Boundary evidence: docs/evidence/game_2DF70.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15000AD0
 * - func_15001460
 * - func_15001970
 * - func_15001A08
 * - func_15001B10
 * - func_15001B8C
 * - func_15001BC8
 * - func_15001CEC
 * - func_15001DE0
 * - func_15002008
 * - func_15002248
 * - func_15002560
 * - func_150025FC
 * - func_15002754
 * - func_150027F8
 * - func_15002878
 * - func_150028BC
 * - func_15002F40
 * - func_15002FB4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern signed char D_800D9E64;
extern s8 *D_800B0DE0;
s32 func_150027F8();

void func_15000AC0(void) {
    D_800D9E64 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15000AD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001460.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001A08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001B10.s")
void func_15001B5C(u8 arg0) {
    *D_800B0DE0 = arg0;
    D_800B0DE0 += 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001B8C */
void func_15001B8C(u16 arg0) {
    D_800B0DE0[0] = arg0 >> 8;
    D_800B0DE0[1] = arg0;
    D_800B0DE0 += 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15001B8C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001B8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001BC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001CEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001DE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002008.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002248.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002560.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_150025FC.s")
extern s32 D_800DBE38;
extern s32 D_800B0DE4;
extern s32 D_800DBE18[];
extern s32 D_800DBE1C;
extern s32 D_800DBE28;
extern s32 D_800DBE4C;

void func_150026C4(void) {
    D_800DBE38 = 0;
    func_1510F800();
}
void func_150026E8(s32 arg0) {
    D_800DBE18[arg0] = D_800DBE38;
    D_800DBE4C = D_800DBE38;
    D_800B0DE4 += D_800DBE38;
}
void func_15002724(void) {
    D_800DBE38 += func_150027F8();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002754.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_150027F8.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15002878 */
s32 func_15002878(void) {
    u8 *current;
    s32 value;
    s32 maximum;

    maximum = D_800DBE18[0];
    current = (u8 *)&D_800DBE1C;
    do {
        value = *(s32 *)current;
        current += 4;
        if (maximum < value) {
            maximum = value;
        }
    } while (current != (u8 *)&D_800DBE28);
    return maximum;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15002878 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002878.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_150028BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002F40.s")

s32 func_15002FA0(s32 arg0) {
    return arg0 ^ 0xF0F0F0F0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002FB4.s")
