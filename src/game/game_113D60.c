#include "types.h"

/*
 * Reviewed source unit: src/game/game_113D60.c
 * Boundary evidence: docs/evidence/game_raw_actor_classification_emitter.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E68B0
 * - func_150E6B84
 * - func_150E6E34
 * - func_150E6ED8
 * - func_150E6F18
 * - func_150E6FAC
 * - func_150E70EC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E68B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6B84.s")
f32 func_150ADA68();                                /* extern */
extern void *D_80088A3C;
extern void *D_80088A40;
extern f32 D_800A130C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E6E34 CURRENT (82) */
void func_150E6E34(void *arg0) {
    void *sp1C;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    void *var_v0;

    if (func_150ADA68() < D_800A130C) {
        var_v0 = D_80088A3C;
    } else {
        var_v0 = D_80088A40;
    }
    sp1C = var_v0;
    temp_fv0 = func_150ADA68();
    temp_fv1 = *(f32 *)((u8 *)var_v0 + 0);
    *(f32 *)((u8 *)arg0 + 0) = (f32) (((*(f32 *)((u8 *)var_v0 + 0xC) - temp_fv1) * temp_fv0) + temp_fv1);
    {
        f32 temp_fa0 = *(f32 *)((u8 *)var_v0 + 4);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (((*(f32 *)((u8 *)var_v0 + 0x10) - temp_fa0) * temp_fv0) + temp_fa0);
    temp_fa1 = *(f32 *)((u8 *)var_v0 + 8);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (((*(f32 *)((u8 *)var_v0 + 0x14) - temp_fa1) * temp_fv0) + temp_fa1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E6E34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6E34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6ED8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6F18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6FAC.s")
void func_150E70CC(f32 *arg0, f32 *arg1) {
    arg0[0] = arg1[5];
    arg0[1] = arg1[6];
    arg0[2] = arg1[7];
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E70EC.s")
f32 func_150484A0(f32, f32);                        /* extern */
extern f32 D_800A1324;
extern f32 D_800A1328;
extern f32 D_800A132C;
extern f32 D_800A1330;
extern f32 D_800A1334;
extern f32 D_800A1338;
extern f32 D_800A133C;

void func_150E71E4(s32 arg0, s32 arg1, void *arg2, void *arg3) {
    *(f32 *)((u8 *)arg3 + 0) = func_150484A0(*(f32 *)((u8 *)arg2 + 0), *(f32 *)((u8 *)arg2 + 8));
    *(f32 *)((u8 *)arg3 + 8) = (f32) D_800A1324;
    *(f32 *)((u8 *)arg3 + 0x10) = (f32) (func_150ADA68() * D_800A1328);
    *(f32 *)((u8 *)arg3 + 0x18) = (f32) (func_150ADA68() * D_800A132C);
    *(f32 *)((u8 *)arg3 + 4) = (f32) D_800A1330;
    *(f32 *)((u8 *)arg3 + 0xC) = (f32) D_800A1334;
    *(f32 *)((u8 *)arg3 + 0x14) = (f32) (func_150ADA68() * D_800A1338);
    *(f32 *)((u8 *)arg3 + 0x1C) = (f32) (func_150ADA68() * D_800A133C);
}
