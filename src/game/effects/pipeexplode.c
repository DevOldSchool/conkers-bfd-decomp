#include "types.h"

/*
 * Reviewed source unit: src/game/effects/pipeexplode.c
 * Boundary evidence: docs/evidence/effects_pipeexplode.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B2740
 * - func_150B2EB4
 * - func_150B3188
 * - func_150B36AC
 * - func_150B37C8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct PipeExplodeState {
    u8 pad0[0x1B];
    u8 unk1B;
} PipeExplodeState;

typedef struct PipeExplodeActor {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[0x7A];
    PipeExplodeState *state;
} PipeExplodeActor;

#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B2740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B2EB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B3188.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B36AC.s")
s32 func_150B378C(PipeExplodeActor *arg0) {
    s32 var_v1;
    PipeExplodeState *temp_v0 = arg0->state;

    var_v1 = arg0->unk1C << 4;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < temp_v0->unk1B) {
        temp_v0->unk1B = var_v1;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B37C8.s")
