#include "types.h"

/*
 * Reviewed source unit: src/game/effects/blood.c
 * Boundary evidence: docs/evidence/effects_blood.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15134070
 * - func_1513416C
 * - func_1513418C
 * - func_151342BC
 * - func_151346D0
 * - func_151346EC
 * - func_1513470C
 * - func_1513472C
 * - func_1513477C
 * - func_151347CC
 * - func_15134908
 * - func_151349D0
 * - func_15134C98
 * - func_15134CEC
 * - func_15134DAC
 * - func_15134E48
 * - func_151352EC
 * - func_1513530C
 * - func_1513532C
 * - func_151353A8
 * - func_15135424
 * - func_15135480
 * - func_1513555C
 * - func_151355B8
 * - func_15135658
 * - func_15135670
 * - func_151356D4
 * - func_15135BF8
 * - func_15135DD0
 * - func_15136404
 * - func_15136698
 * - func_151368A8
 * - func_15136918
 * - func_15136A1C
 * - func_15136A50
 * - func_15136AE4
 * - func_15136C3C
 * - func_15136F50
 * - func_15137610
 * - func_1513783C
 * - func_15137C64
 * - func_15137E10
 * - func_15137E60
 * - func_15137F30
 * - func_151380B4
 * - func_15138120
 * - func_151382E0
 * - func_15138424
 * - func_151389A8
 * - func_15138BC0
 * - func_15138C80
 * - func_15138E98
 * - func_15139578
 * - func_15139768
 * - func_15139D74
 * - func_1513A24C
 * - func_1513A48C
 * - func_1513A594
 * - func_1513A5E0
 * - func_1513A6E0
 * - func_1513ABB8
 * - func_1513B0B8
 * - func_1513B0F8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134070.s")
s32 func_1513416C(void *arg0) {
    short temp_v0;

    temp_v0 = *(short *)((char *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        *(char *)((char *)arg0 + 0x28) = (char)(temp_v0 * 8);
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513418C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151342BC.s")
s32 func_151346D0(s32 arg0, void *arg1, s32 arg2) {
    *((unsigned char *)arg1 + 0x3A) =
        (unsigned char)(*((unsigned char *)arg1 + 0x3A) & 0xFFEF);
    return arg0;
}
void func_151346EC(void) {
    func_15169804();
}
void func_1513470C(void) {
    func_15169824();
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513472C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513477C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151347CC.s")
void func_151348F0(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134908.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151349D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134C98.s")
void func_15134CD4(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134CEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134DAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134E48.s")
void func_151352EC(void) {
    func_15169804();
}
void func_1513530C(void) {
    func_15169824();
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513532C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151353A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135424.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135480.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513555C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151355B8.s")
s32 func_15135658(f32 *arg0) {
    arg0[0x1D] = 1.0f;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135670.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151356D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135BF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135DD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136404.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136698.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151368A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136A1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136AE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136C3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136F50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137610.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513783C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137C64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137E10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137E60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137F30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151380B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138120.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151382E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138424.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151389A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138BC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138C80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138E98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139578.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139768.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139D74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A24C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A48C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A594.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A5E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A6E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513ABB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513B0B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513B0F8.s")
