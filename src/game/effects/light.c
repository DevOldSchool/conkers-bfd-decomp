#include "types.h"

/*
 * Reviewed source unit: src/game/effects/light.c
 * Boundary evidence: docs/evidence/effects_light.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151602C0
 * - func_1516037C
 * - func_151603FC
 * - func_151604A0
 * - func_15160600
 * - func_1516065C
 * - func_15160684
 * - func_151606A8
 * - func_151607A4
 * - func_15160954
 * - func_15160A58
 * - func_15160B74
 * - func_15160CDC
 * - func_15160E30
 * - func_15161238
 * - func_1516127C
 * - func_15161334
 * - func_15161408
 * - func_15161494
 * - func_15161540
 * - func_151615F8
 * - func_151616D0
 * - func_15161714
 * - func_15161740
 * - func_1516176C
 * - func_15161798
 * - func_151617C4
 * - func_151617E4
 * - func_15161804
 * - func_15161860
 * - func_151618BC
 * - func_151619A0
 * - func_15161A68
 * - func_15161E24
 * - func_15161F2C
 * - func_15161F4C
 * - func_15162034
 * - func_15162110
 * - func_151621B8
 * - func_151623F4
 * - func_15162510
 * - func_15162740
 * - func_1516284C
 * - func_1516295C
 * - func_15162B28
 * - func_15162EF8
 * - func_15162F50
 * - func_15162FAC
 * - func_151630F4
 * - func_15163414
 * - func_15163504
 * - func_151635A8
 * - func_15163604
 * - func_15163704
 * - func_1516381C
 * - func_1516387C
 * - func_151638E0
 * - func_151639D0
 * - func_15163A18
 * - func_15163A60
 * - func_15163B98
 * - func_15163BE8
 * - func_15163CD0
 * - func_15163CF8
 * - func_15163DEC
 * - func_15163F50
 * - func_15163FEC
 * - func_151640C0
 * - func_15164134
 * - func_15164208
 * - func_1516429C
 * - func_1516434C
 * - func_151643A8
 * - func_151643F8
 * - func_1516441C
 * - func_151644A8
 * - func_151644F4
 * - func_151645C4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151602C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516037C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151603FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151604A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160600.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516065C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160684.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151606A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151607A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160954.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160A58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160B74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160CDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160E30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161238.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516127C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161334.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161408.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161494.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161540.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151615F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151616D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161714.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516176C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161798.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151617C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151617E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161804.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161860.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151618BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151619A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161A68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161E24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161F2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161F4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162034.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162110.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151621B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151623F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162510.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516284C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516295C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162B28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162EF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162F50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162FAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151630F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163414.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163504.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151635A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163604.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163704.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516381C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516387C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151638E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151639D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163A18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163A60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163B98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163BE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163CD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163CF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163DEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163F50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163FEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151640C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15164134.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15164208.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516429C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516434C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151643A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151643F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516441C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151644A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151644F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151645C4.s")
