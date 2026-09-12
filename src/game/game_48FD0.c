#include "types.h"

/*
 * Reviewed source unit: src/game/game_48FD0.c
 * Boundary evidence: docs/evidence/game_raw_controller_io_group.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501BB20
 * - func_1501BBB8
 * - func_1501C010
 * - func_1501C0F0
 * - func_1501C17C
 * - func_1501C1B0
 * - func_1501C53C
 * - func_1501C57C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501BB20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501BBB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C010.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C0F0.s")
extern u8 D_80084060[4];
extern u8 D_800BE93C[4];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C17C CURRENT (205) */
void func_1501C17C(s32 arg0) {
    u8 temp_v0;

    arg0 = arg0 & 0xFF;
    temp_v0 = D_80084060[arg0];
    if ((s32)temp_v0 < 4) {
        D_800BE93C[temp_v0] = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C17C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C17C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C1B0.s")
void func_1501C17C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C53C CURRENT (220) */
void func_1501C53C(void) {
    s32 temp_t6;
    s32 var_s0;

    var_s0 = 0;
    do {
        func_1501C17C(var_s0 & 0xFF);
        temp_t6 = (var_s0 + 1) & 0xFF;
        var_s0 = temp_t6;
    } while (temp_t6 < 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C53C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C53C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C57C.s")
