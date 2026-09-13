#include "types.h"

/*
 * Reviewed source unit: src/game/game_45B80.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150186D0
 * - func_1501878C
 * - func_15018DFC
 * - func_15018E88
 * - func_15018F80
 * - func_1501905C
 * - func_15019130
 * - func_15019464
 * - func_150195A0
 * - func_150198FC
 * - func_15019BB8
 * - func_15019CC8
 * - func_15019E60
 * - func_15019F20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_150186D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_1501878C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15018DFC.s")
s32 func_151674F8(s32, s32, s16, s32);
s32 func_15174B48(s32, s32, s16);
void func_15174AA4(s32, s32, s16);
void func_1517D7B0(s32 *, s32);
extern u8 D_800BE616;
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15018E88 CURRENT (100) */
void func_15018E88(s32 arg0, s16 arg1) {
    s32 value;

    if (D_800BE616 == 0) {
        func_1517D7B0(&arg0, 1);
    }
    value = func_151674F8(arg0, 0, arg1, 0);
    arg0 = value;
    value = func_151674F8(value, 0, arg1, 1);
    arg0 = value;
    func_15174AA4(value, D_800BE9F0, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15018E88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15018E88.s")

s32 func_15018F08(s32 arg0, s16 arg1) {
    s32 value;

    value = func_15174B48(arg0, D_800BE9F0, arg1);
    arg0 = value;
    value = func_151674F8(value, 1, arg1, 0);
    arg0 = value;
    arg0 = func_151674F8(value, 1, arg1, 1);
    func_1517D7B0(&arg0, 2);
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15018F80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_1501905C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019130.s")
void func_15167010(void);
void func_1517ABB0(void);
void func_1508F0A4(void);
extern u8 D_800BEAC0;

void func_15019414(void) {
    if (D_800BEAC0 == 0) {
        func_15167010();
    }
    func_1517ABB0();
    if (D_800BE616 == 0) {
        func_1508F0A4();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019464.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_150195A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_150198FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019BB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019CC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019E60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019F20.s")
