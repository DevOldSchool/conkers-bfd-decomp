#include "types.h"

/*
 * Reviewed source unit: src/game/game_49D30.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501C880
 * - func_1501CC3C
 * - func_1501CDC0
 * - func_1501CE54
 * - func_1501CFF8
 * - func_1501D044
 * - func_1501D1D4
 * - func_1501D258
 * - func_1501D2C4
 * - func_1501D348
 * - func_1501DAAC
 * - func_1501DE18
 * - func_1501DF04
 * - func_1501E05C
 * - func_1501E1B4
 * - func_1501E2F8
 * - func_1501E400
 * - func_1501E540
 * - func_1501E73C
 * - func_1501E81C
 * - func_1501EA18
 * - func_1501EC38
 * - func_1501F72C
 * - func_1501FC8C
 * - func_1501FE68
 * - func_1501FFE8
 * - func_15020388
 * - func_15020878
 * - func_15020EC4
 * - func_1502178C
 * - func_15021DB8
 * - func_15022024
 * - func_15022190
 * - func_150221E8
 * - func_15022234
 * - func_15022248
 * - func_1502225C
 * - func_150222E0
 * - func_15022398
 * - func_15022528
 * - func_15022640
 * - func_150226BC
 * - func_15022754
 * - func_150227BC
 * - func_15022848
 * - func_150228E4
 * - func_15022998
 * - func_150229E4
 * - func_15022B08
 * - func_15022BA4
 * - func_15023264
 * - func_150233BC
 * - func_150233E4
 * - func_15023440
 * - func_150234A4
 * - func_150235DC
 * - func_1502378C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501C880.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CC3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CDC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CE54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CFF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D044.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D1D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D258.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D2C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D348.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501DAAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501DE18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501DF04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E05C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E1B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E2F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E540.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E73C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E81C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501EA18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501EC38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501F72C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501FC8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501FE68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501FFE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15020388.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15020878.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15020EC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1502178C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15021DB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022024.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022190.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150221E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022234.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022248.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1502225C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150222E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022398.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022528.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022640.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150226BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022754.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150227BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022848.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150228E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022998.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150229E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022B08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022BA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15023264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150233BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150233E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15023440.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150234A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150235DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1502378C.s")
