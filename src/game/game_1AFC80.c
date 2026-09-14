#include "types.h"

/*
 * Reviewed source unit: src/game/game_1AFC80.c
 * Boundary evidence: docs/evidence/game_raw_scene_setup_emission_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151827D0
 * - func_15182C5C
 * - func_15182FDC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_151827D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_15182C5C.s")
typedef struct Game1AFC80Value {
    f32 value;
    u8 pad4[0x14];
} Game1AFC80Value;

extern Game1AFC80Value D_8008D058[];
extern u8 D_800DDE54[];

f32 func_15182F58(s32 arg0, s32 arg1) {
    f32 var_fv1;

    var_fv1 = D_8008D058[D_800DDE54[arg1]].value * (f32)(arg0 * 0x28);
    if (var_fv1 < 0.0f) {
        var_fv1 = 0.0f;
    } else if (var_fv1 > 39.0f) {
        var_fv1 = 39.0f;
    }
    return var_fv1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_15182FDC.s")
