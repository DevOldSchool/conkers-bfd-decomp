#include "types.h"

/*
 * Reviewed source unit: src/game/game_981E0.c
 * Boundary evidence: docs/evidence/game_dispatcher_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1506AD30
 * - func_1506AF74
 * - func_1506AFE0
 * - func_1506B020
 * - func_1506B078
 * - func_1506B100
 * - func_1506B14C
 * - func_1506B198
 * - func_1506B1E8
 * - func_1506B228
 * - func_1506B268
 * - func_1506B2BC
 * - func_1506B328
 * - func_1506B370
 * - func_1506B3B8
 * - func_1506B4EC
 * - func_1506B50C
 * - func_1506B520
 * - func_1506B5B4
 * - func_1506B5CC
 * - func_1506B5E4
 * - func_1506B634
 * - func_1506B740
 * - func_1506B7F4
 * - func_1506B82C
 * - func_1506B860
 * - func_1506B88C
 * - func_1506B8B4
 * - func_1506B8F4
 * - func_1506B91C
 * - func_1506B944
 * - func_1506B984
 * - func_1506B9AC
 * - func_1506B9C0
 * - func_1506BA4C
 * - func_1506BAD8
 * - func_1506BB64
 * - func_1506BBA8
 * - func_1506BC24
 * - func_1506BCA0
 * - func_1506BCC8
 * - func_1506BDE8
 * - func_1506BE2C
 * - func_1506BE54
 * - func_1506BE84
 * - func_1506BE98
 * - func_1506BEC0
 * - func_1506BEDC
 * - func_1506BF1C
 * - func_1506BF5C
 * - func_1506C32C
 * - func_1506C418
 * - func_1506C43C
 * - func_1506C460
 * - func_1506CE6C
 * - func_1506D2E8
 * - func_1506D4F4
 * - func_1506D538
 * - func_1506D570
 * - func_1506D584
 * - func_1506D6B4
 * - func_1506D74C
 * - func_1506D898
 * - func_1506D934
 * - func_1506D958
 * - func_1506DA78
 * - func_1506DA94
 * - func_1506DB30
 * - func_1506DB5C
 * - func_1506DB84
 * - func_1506DBA0
 * - func_1506DBD4
 * - func_1506DC10
 * - func_1506DCA4
 * - func_1506DCC0
 * - func_1506DCDC
 * - func_1506DD00
 * - func_1506DD44
 * - func_1506DD6C
 * - func_1506DDC0
 * - func_1506DE04
 * - func_1506DE84
 * - func_1506E0EC
 * - func_1506E2CC
 * - func_1506E46C
 * - func_1506E5FC
 * - func_1506E63C
 * - func_1506E67C
 * - func_1506E6BC
 * - func_1506E6FC
 * - func_1506E73C
 * - func_1506E77C
 * - func_1506E7BC
 * - func_1506E7FC
 * - func_1506E848
 * - func_1506E898
 * - func_1506E8D8
 * - func_1506E918
 * - func_1506E958
 * - func_1506E998
 * - func_1506E9D8
 * - func_1506EA18
 * - func_1506EA58
 * - func_1506EA98
 * - func_1506EBC0
 * - func_1506EC50
 * - func_1506ECD0
 * - func_1506ECF0
 * - func_1506ED0C
 * - func_1506ED4C
 * - func_1506ED68
 * - func_1506ED90
 * - func_1506EDAC
 * - func_1506EDC8
 * - func_1506EDF0
 * - func_1506EE14
 * - func_1506EE38
 * - func_1506EE60
 * - func_1506EEAC
 * - func_1506EED8
 * - func_1506EEF4
 * - func_1506EF5C
 * - func_1506EFB4
 * - func_1506EFC8
 * - func_1506F004
 * - func_1506F02C
 * - func_1506F05C
 * - func_1506F090
 * - func_1506F0C4
 * - func_1506F0F0
 * - func_1506F11C
 * - func_1506F14C
 * - func_1506F17C
 * - func_1506F1A8
 * - func_1506F524
 * - func_1506F54C
 * - func_1506F8C0
 * - func_1506F8F0
 * - func_1506F9C0
 * - func_1506FA90
 * - func_1506FB60
 * - func_1506FBE8
 * - func_1506FC1C
 * - func_1506FC50
 * - func_1506FC74
 * - func_1506FC9C
 * - func_1506FCC8
 * - func_1506FCFC
 * - func_1506FD30
 * - func_1506FDF0
 * - func_1506FE1C
 * - func_1506FE48
 * - func_1506FE74
 * - func_1506FEA0
 * - func_1506FECC
 * - func_1506FEF8
 * - func_1506FF24
 * - func_1506FF50
 * - func_1506FF78
 * - func_1506FFAC
 * - func_1506FFE0
 * - func_15070014
 * - func_1507003C
 * - func_15070084
 * - func_150700B4
 * - func_150700E4
 * - func_15070114
 * - func_15070144
 * - func_150701C4
 * - func_150701F4
 * - func_15070224
 * - func_15070300
 * - func_15070690
 * - func_150706C4
 * - func_150706F8
 * - func_15070760
 * - func_15070794
 * - func_150707C8
 * - func_150707F8
 * - func_15070830
 * - func_15070860
 * - func_15070898
 * - func_15070C18
 * - func_15070C40
 * - func_15070CDC
 * - func_15070D00
 * - func_15070D24
 * - func_15070F60
 * - func_15071230
 * - func_15071254
 * - func_15071278
 * - func_150712AC
 * - func_15071360
 * - func_15071434
 * - func_15071470
 * - func_150714AC
 * - func_150714E8
 * - func_15071544
 * - func_1507158C
 * - func_150715D4
 * - func_1507161C
 * - func_15071628
 * - func_15071668
 * - func_15071690
 * - func_150716EC
 * - func_15071764
 * - func_150717E0
 * - func_15071830
 * - func_15071860
 * - func_15071888
 * - func_150718E4
 * - func_15071998
 * - func_150719CC
 * - func_15071A00
 * - func_15071A34
 * - func_15071A64
 * - func_15071B18
 * - func_15071D08
 * - func_15071D38
 * - func_15071D78
 * - func_15071DC8
 * - func_15071DF4
 * - func_15071E20
 * - func_15071E3C
 * - func_15071E58
 * - func_15071ED4
 * - func_15071F14
 * - func_15071F54
 * - func_15071F80
 * - func_15071FB0
 * - func_15071FDC
 * - func_150721A4
 * - func_150721E8
 * - func_15072208
 * - func_150722F0
 * - func_1507233C
 * - func_15072360
 * - func_15072388
 * - func_150723AC
 * - func_150723E0
 * - func_15072420
 * - func_1507266C
 * - func_15072740
 * - func_150727AC
 * - func_150727F0
 * - func_15072918
 * - func_15072940
 * - func_15072968
 * - func_150729B4
 * - func_150729D0
 * - func_15072A14
 * - func_15072A40
 * - func_15072A7C
 * - func_15072AF8
 * - func_15072B44
 * - func_15072DA0
 * - func_15072DD8
 * - func_15072E38
 * - func_15072E7C
 * - func_15072E98
 * - func_15072EC0
 * - func_15072EF4
 * - func_15072F10
 * - func_15073054
 * - func_15073078
 * - func_150730A4
 * - func_150730D0
 * - func_15073118
 * - func_1507342C
 * - func_150738E8
 * - func_150739A4
 * - func_150739C0
 * - func_15073A28
 * - func_15073A50
 * - func_15073B38
 * - func_15073C28
 * - func_15073C50
 * - func_15073CB8
 * - func_15073CF4
 * - func_15073D34
 * - func_15073D74
 * - func_15073DA4
 * - func_15073E2C
 * - func_15073EA4
 * - func_15073F1C
 * - func_15073F5C
 * - func_15073F78
 * - func_15073FA0
 * - func_15074644
 * - func_15074664
 * - func_150746F0
 * - func_150747E4
 * - func_15074840
 * - func_15074870
 * - func_1507488C
 * - func_150748F4
 * - func_1507490C
 * - func_15074980
 * - func_15074A44
 * - func_15074A6C
 * - func_15074A94
 * - func_15074B7C
 * - func_15074BD8
 * - func_15074BEC
 * - func_15074C00
 * - func_15074C80
 * - func_15074DEC
 * - func_15074E04
 * - func_15074E80
 * - func_15074EE8
 * - func_15074F30
 * - func_15074F48
 * - func_15074FD4
 * - func_15075050
 * - func_150750A4
 * - func_150750C4
 * - func_1507515C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AD30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AF74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AFE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B020.s")
void func_1506B070(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B078.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B100.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B14C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B198.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B1E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B228.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B268.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B2BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B328.s")
void func_1506B368(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B370.s")
void func_1506B3B0(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B3B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B4EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B50C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B520.s")
void func_1506B5A4(void) {
}
void func_1506B5AC(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B5B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B5CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B5E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B634.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B7F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B82C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B860.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B88C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B8B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B8F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B91C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B944.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B984.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B9AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B9C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BA4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BAD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BB64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BBA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BC24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BCA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BCC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BDE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BE2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BE54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BE84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BE98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BEC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BEDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BF1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BF5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C32C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C418.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C43C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C460.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506CE6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D2E8.s")
void func_1506D4EC(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D4F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D538.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D570.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D584.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D6B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D74C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D898.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D934.s")
void func_1506D950(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D958.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DA78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DA94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DB30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DB5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DB84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DBA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DBD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DC10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DCA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DCC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DCDC.s")
void func_1506DCF8(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DD00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DD44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DD6C.s")
void func_1506DDB8(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DDC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DE04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DE84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E0EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E2CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E46C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E5FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E63C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E67C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E6BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E6FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E73C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E77C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E7BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E7FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E848.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E898.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E8D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E958.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E998.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E9D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EA18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EA58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EA98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EBC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EC50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506ECD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506ECF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506ED0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506ED4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506ED68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506ED90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EDAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EDC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EDF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EE14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EE38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EE60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EEAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EED8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EEF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EF5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EFB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EFC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F004.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F02C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F05C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F090.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F0C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F0F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F11C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F14C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F17C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F1A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F524.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F54C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F8C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F8F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F9C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FA90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FB60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FBE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FC1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FC50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FC74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FC9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FCC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FCFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FD30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FDF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FE1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FE48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FE74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FEA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FECC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FEF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FF24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FF50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FF78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FFAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FFE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070014.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507003C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070084.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150700B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150700E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070114.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070144.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150701C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150701F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070224.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070300.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150706C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150706F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070760.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070794.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150707C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150707F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070830.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070860.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070898.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070C18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070C40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070CDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070D00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070D24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070F60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071230.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071254.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071278.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150712AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071434.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071470.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150714AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150714E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071544.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507158C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150715D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507161C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071628.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071668.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150716EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071764.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150717E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071830.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071860.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071888.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150718E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071998.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150719CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071A00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071A34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071A64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071B18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071D08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071D38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071D78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071DC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071DF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071E20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071E3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071E58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071ED4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071F14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071F54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071F80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071FB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071FDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150721A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150721E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072208.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150722F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507233C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072388.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150723AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150723E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072420.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507266C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150727AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150727F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072940.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072968.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150729B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150729D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072A14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072A40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072A7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072AF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072B44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072DA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072DD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072E38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072E7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072E98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072EC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072EF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072F10.s")
void func_1507304C(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073054.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073078.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150730A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150730D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073118.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507342C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150738E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150739A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150739C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073A28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073B38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073C28.s")
void func_15073C48(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073C50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073CB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073CF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073D34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073D74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073DA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073E2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073EA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073F1C.s")
void func_15073F54(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073F5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073F78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073FA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074644.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074664.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150746F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150747E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074840.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074870.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507488C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150748F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507490C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074980.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074A44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074A6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074A94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074B7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074BD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074BEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074C00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074C80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074DEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074E04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074E80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074EE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074F30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074F48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074FD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15075050.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150750A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150750C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507515C.s")
