#include "types.h"

/*
 * Reviewed source unit: src/game/game_139FC0.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510CB10
 * - func_1510CDB8
 * - func_1510CE60
 * - func_1510D0EC
 * - func_1510D404
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510CB10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510CDB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510CE60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510D0EC.s")
extern u8 D_1A37E0;
extern u8 D_80091D20;

u8 *func_1510D374(s32 arg0) {
    u8 *var_v1;
    s32 var_v0;

    var_v1 = &D_1A37E0;
    var_v0 = 0;
    while (var_v0 < arg0) {
        var_v1 += ((u16 *)&D_80091D20)[var_v0];
        var_v0++;
    }
    return var_v1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510D404.s")
extern s8 D_800BC448[];

void func_1510D608(s32 arg0, s32 arg1) {
    s8 *temp_v0;
    s8 temp_v1;

    temp_v0 = &D_800BC448[arg0];
    temp_v1 = *temp_v0;
    if (temp_v1 != 0) {
        *temp_v0 = (temp_v1 & 0x40) | arg1;
    }
}
