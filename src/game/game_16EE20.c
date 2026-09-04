#include "types.h"

/*
 * Reviewed source unit: src/game/game_16EE20.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15141970
 * - func_15141990
 * - func_151419B0
 * - func_151419D0
 * - func_15141A7C
 * - func_15141C0C
 * - func_15141CC0
 * - func_15141DA4
 * - func_15141E38
 * - func_15141F78
 * - func_151420F8
 * - func_15142180
 * - func_151422C0
 * - func_151422DC
 * - func_151422F8
 * - func_15142314
 * - func_151423D8
 * - func_15142444
 * - func_151424F4
 * - func_15142600
 * - func_15142838
 * - func_15142914
 * - func_151429E0
 * - func_15142A5C
 * - func_15142A80
 * - func_15142AC0
 * - func_15142B04
 * - func_15142B44
 * - func_15142B7C
 * - func_15142C10
 * - func_15142CF0
 * - func_15142E24
 * - func_15142FBC
 * - func_15143044
 * - func_1514306C
 * - func_15143134
 * - func_151432BC
 * - func_151436B4
 * - func_1514373C
 * - func_15143794
 * - func_15143834
 * - func_15143874
 * - func_151438D8
 * - func_15143D18
 * - func_15143DA8
 * - func_15143E08
 * - func_15143E24
 * - func_15143E64
 * - func_15143E94
 * - func_1514401C
 * - func_151441A4
 * - func_151442FC
 * - func_151444DC
 * - func_15144528
 * - func_15144598
 * - func_1514462C
 * - func_1514470C
 * - func_15144A74
 * - func_15144AA8
 * - func_15144B34
 * - func_15144B68
 * - func_15144BC8
 * - func_15144C2C
 * - func_15144C8C
 * - func_15144CEC
 * - func_15144E80
 * - func_151450B4
 * - func_15145128
 * - func_151451F0
 * - func_151452C4
 * - func_151454BC
 * - func_15145548
 * - func_1514563C
 * - func_15145740
 * - func_15145974
 * - func_15145A0C
 * - func_15145A50
 * - func_15145AD8
 * - func_15145C90
 * - func_15145CD0
 * - func_15145DB4
 * - func_15145EA4
 * - func_15146078
 * - func_151462C8
 * - func_151464B8
 * - func_15146508
 * - func_1514654C
 * - func_1514672C
 * - func_151467A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141990.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151419B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151419D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141A7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141C0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141CC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141DA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141E38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141F78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151420F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142180.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151422C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151422DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151422F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142314.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151423D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142444.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151424F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142600.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142838.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142914.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151429E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142A5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142A80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142AC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142B04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142B44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142B7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142C10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142CF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142E24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142FBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143044.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514306C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143134.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151432BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151436B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514373C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143794.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143834.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143874.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151438D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143D18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143DA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143E08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143E24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143E64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143E94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514401C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151441A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151442FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151444DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144528.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144598.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514462C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514470C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144A74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144AA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144B34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144B68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144BC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144C2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144C8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144CEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144E80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151450B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145128.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151451F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151452C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151454BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145548.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514563C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145974.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145A0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145AD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145C90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145CD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145DB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145EA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15146078.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151462C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151464B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15146508.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514654C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514672C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151467A4.s")
