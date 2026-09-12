#include "types.h"

/*
 * Reviewed source unit: src/game/game_11A680.c
 * Boundary evidence: docs/evidence/game_raw_state_resource_helpers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150ED234
 * - func_150ED298
 * - func_150ED578
 * - func_150ED638
 * - func_150ED748
 * - func_150EEC84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_15144BC8: unique active project prototype */
f32 func_15144BC8(f32);

f32 func_150ED1D0(f32 arg0, f32 arg1) {
    f32 temp_fv0;
    f32 var_fv1;

    arg0 = func_15144BC8(arg0);
    temp_fv0 = func_15144BC8(func_15144BC8(arg1) - arg0);
    var_fv1 = temp_fv0;
    if (temp_fv0 > 180.0f) {
        var_fv1 = -360.0f + temp_fv0;
    }
    return var_fv1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED234.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED298.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED578.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED638.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED748.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150EEC84.s")
void func_151045E0(s32, s32, s32);
void func_15052590(void *);

void func_150EEDA8(void *arg0) {
    if (*(u8 *)((u8 *)arg0 + 5) != 3) {
        func_151045E0((s32)arg0, 0xF, 0x437A0000);
        *(u8 *)((u8 *)arg0 + 5) = 3;
        *(s16 *)((u8 *)arg0 + 0xE4) = 0;
        *(u8 *)((u8 *)arg0 + 0x125) = 0xFF;
    }
    func_15052590(arg0);
}
