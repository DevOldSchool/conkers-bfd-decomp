#include "types.h"

/*
 * Reviewed source unit: src/game/game_113D60.c
 * Boundary evidence: docs/evidence/game_raw_actor_classification_emitter.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E68B0
 * - func_150E6B84
 * - func_150E6E34
 * - func_150E6F18
 * - func_150E6FAC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E68B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6B84.s")
f32 func_150ADA68();                                /* extern */
extern s32 func_150ADA20(void);
extern void *D_80088A44[];
extern void *D_80088A3C;
extern void *D_80088A40;
extern f32 D_800A130C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E6E34 CURRENT (40) */
void func_150E6E34(void *arg0) {
    void *var_v0;

    if (func_150ADA68() < D_800A130C) {
        var_v0 = D_80088A3C;
    } else {
        var_v0 = D_80088A40;
    }
    {
        void * sp1C = var_v0;
    {
        f32 temp_fv0 = func_150ADA68();
    {
        f32 temp_fv1 = *(f32 *)((u8 *)var_v0 + 0);
    *(f32 *)((u8 *)arg0 + 0) = (f32) (((*(f32 *)((u8 *)var_v0 + 0xC) - temp_fv1) * temp_fv0) + temp_fv1);
    {
        f32 temp_fa0 = *(f32 *)((u8 *)var_v0 + 4);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (((*(f32 *)((u8 *)var_v0 + 0x10) - temp_fa0) * temp_fv0) + temp_fa0);
    {
        f32 temp_fa1 = *(f32 *)((u8 *)var_v0 + 8);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (((*(f32 *)((u8 *)var_v0 + 0x14) - temp_fa1) * temp_fv0) + temp_fa1);
    }
    }
    }
    }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E6E34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6E34.s")
extern s32 func_150ADA20(void);
extern s32 D_800D9A20[];
extern void func_1514470C(s32 arg0, s32 arg1);

void func_150E6ED8(s32 arg0) {
    func_1514470C(D_800D9A20[func_150ADA20() & 1], arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E6F18 CURRENT (90) */
void func_150E6F18(void *arg0) {
    s32 sp1C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_v1;

    temp_v1 = (s32)D_80088A44[func_150ADA20() % 6U];
    sp1C = temp_v1;
    temp_fv0 = func_150ADA68();
    temp_fv1 = *(f32 *)((u8 *)sp1C + 0);
    *(f32 *)((u8 *)arg0 + 0) =
        (f32)(((*(f32 *)((u8 *)sp1C + 0xC) - temp_fv1) * temp_fv0) + temp_fv1);
    temp_fa0 = *(f32 *)((u8 *)sp1C + 4);
    *(f32 *)((u8 *)arg0 + 4) =
        (f32)(((*(f32 *)((u8 *)sp1C + 0x10) - temp_fa0) * temp_fv0) + temp_fa0);
    temp_fa1 = *(f32 *)((u8 *)sp1C + 8);
    *(f32 *)((u8 *)arg0 + 8) =
        (f32)(((*(f32 *)((u8 *)sp1C + 0x14) - temp_fa1) * temp_fv0) + temp_fa1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E6F18 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6F18.s")
s32 func_1514ECE0();
f32 func_151423D8(u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E6FAC CURRENT (1025) */
void func_150E6FAC(f32 *arg0, u8 *arg1) {
    void *sp34;
    f32 sp2C;
    s16 sp2A;
    f32 sp24;
    f32 temp_fv0;
    s16 temp_t6;
    u8 *temp_v0;

    if (func_1514ECE0(*(s32 *)(arg1 + 0x2F4), 0x16, &sp34) != 0) {
        sp2C = (func_150ADA68() * 100.0f) + 80.0f;
        temp_t6 = func_150ADA20() & 0xFF;
        sp2A = temp_t6;
        sp24 = func_151423D8((temp_t6 - 0x40) & 0xFF);
        temp_fv0 = func_151423D8(*((u8 *)&sp2A + 1));
        temp_v0 = *(u8 **)((u8 *)sp34 + 0x10);
        arg0[0] = *(f32 *)(arg1 + 0x14) +
                  (*(f32 *)(temp_v0 + 0x38) * -80.0f) + (sp24 * sp2C);
        arg0[1] = *(f32 *)(arg1 + 0x18) +
                  (*(f32 *)(temp_v0 + 0x3C) * -80.0f) + 100.0f;
        arg0[2] = *(f32 *)(arg1 + 0x1C) +
                  (*(f32 *)(temp_v0 + 0x40) * -80.0f) + (temp_fv0 * sp2C);
        return;
    }
    arg0[0] = *(f32 *)(arg1 + 0x14);
    arg0[1] = *(f32 *)(arg1 + 0x18);
    arg0[2] = *(f32 *)(arg1 + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E6FAC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6FAC.s")
void func_150E70CC(f32 *arg0, f32 *arg1) {
    arg0[0] = arg1[5];
    arg0[1] = arg1[6];
    arg0[2] = arg1[7];
}
/* Call context: func_150484A0: unique active project prototype */
f32 func_150484A0(f32, f32);
extern f32 D_800A1310;
extern f32 D_800A1314;
extern f32 D_800A1318;
extern f32 D_800A131C;
extern f32 D_800A1320;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

void func_150E70EC(s32 arg0, s32 arg1, void *arg2, void *arg3) {
    f32 temp_ft4;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg3 + 0) = func_150484A0(*(f32 *)((u8 *)arg2 + 0), *(f32 *)((u8 *)arg2 + 8));
    *(f32 *)((u8 *)arg3 + 8) = (f32) (func_150ADA68() * D_800A1310);
    *(f32 *)((u8 *)arg3 + 0x10) = (f32) (func_150ADA68() * D_800A1314);
    *(f32 *)((u8 *)arg3 + 0x18) = (f32) (func_150ADA68() * 0.5f);
    temp_fv1 = *(f32 *)((u8 *)arg2 + 0);
    temp_ft4 = *(f32 *)((u8 *)arg2 + 8);
    *(f32 *)((u8 *)arg3 + 4) = (f32) (func_150484A0(sqrtf((temp_fv1 * temp_fv1) + (temp_ft4 * temp_ft4)), *(f32 *)((u8 *)arg2 + 4)) - D_800A1318);
    *(f32 *)((u8 *)arg3 + 0xC) = (f32) (func_150ADA68() * D_800A131C);
    *(f32 *)((u8 *)arg3 + 0x14) = (f32) (func_150ADA68() * D_800A1320);
    *(f32 *)((u8 *)arg3 + 0x1C) = (f32) (func_150ADA68() * 0.5f);
}
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
