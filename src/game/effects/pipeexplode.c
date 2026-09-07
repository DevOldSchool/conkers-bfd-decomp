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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B36AC CURRENT (2535) */
s32 func_150B36AC(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_t1;
    s32 temp_t7;
    s32 temp_t9;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x48);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) + arg4);
    if (*(f32 *)((u8 *)arg0 + 0x170) < temp_fv0) {
        temp_t7 = *(s32 *)((u8 *)arg0 + 0x60) & ~7;
        temp_t9 = temp_t7 & ~8;
        temp_t1 = temp_t9 & ~0x40;
        *(s32 *)((u8 *)arg0 + 0x60) = temp_t7;
        *(s32 *)((u8 *)arg0 + 0x60) = temp_t9;
        *(s32 *)((u8 *)arg0 + 0x60) = temp_t1;
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (temp_t1 & ~0x20);
        *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x48) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
        if (*(s16 *)((u8 *)arg0 + 0x64) >= 0x21) {
            *(s16 *)((u8 *)arg0 + 0x64) = 0x20;
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (-temp_fv0 * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * temp_fv1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B36AC */
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
