#include "types.h"

/*
 * Reviewed source unit: src/game/game_100810.c
 * Boundary evidence: docs/evidence/game_raw_owner_audio_effect.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D3360
 * - func_150D3A68
 * - func_150D3FD4
 * - func_150D4300
 * - func_150D49C0
 * - func_150D4C2C
 * - func_150D4CC4
 * - func_150D4D58
 * - func_150D5124
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150D4C2C(s32 arg0);
void func_15147928(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3A68.s")
f32 func_15143E64(s32);                             /* extern */
s32 func_1515C0F8(s32, s32 *, void *);              /* extern */
extern f32 D_800A0A10;
extern u8 D_800C35EA;
extern void *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D3FD4 CURRENT (7755) */
s32 func_150D3FD4(void *arg0) {
    s32 *sp8C;
    s32 sp88;
    f32 sp84;
    f32 sp80;
    s32 sp7C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fs2;
    f32 var_fs3;
    f32 var_fv0;
    f32 var_fv1;
    s32 *temp_t6;
    s32 temp_a1;
    s32 var_a0;
    s32 var_t0;
    s8 var_v0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_t6 = *(s32 **)((u8 *)arg0 + 0x98);
    sp8C = temp_t6;
    var_t0 = *(s32 *)((u8 *)arg0 + 0x94);
    if (D_800C35EA != 1) {
        sp88 = var_t0;
        var_t0 = sp88;
        if (func_1515C0F8(*temp_t6, &sp7C, arg0) != 0) {
            var_fv1 = func_15143E64(sp7C);
        } else {
            var_fv1 = 0.0f;
        }
    } else if (*(s32 *)((u8 *)D_800DBFF0 + 0x5F0) & 4) {
        var_fv1 = 0.0f;
    } else {
        var_fv1 = 128.0f;
    }
    if (var_fv1 < 10.0f) {
        var_fs3 = 0.0f;
    } else if (var_fv1 > 70.0f) {
        var_fs3 = 600.0f;
    } else {
        var_fs3 = (var_fv1 - 10.0f) * D_800A0A10 * 600.0f;
    }
    if (*(s8 *)((u8 *)arg0 + 0x2C) >= 2) {
        var_fs2 = 0.0f;
        var_a0 = *(s8 *)((u8 *)arg0 + 0x2E) - 1;
        if (var_a0 < 0) {
            var_a0 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
        }
        if (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D)) {
            do {
                temp_a1 = var_a0;
                var_a0 -= 1;
                if (var_a0 < 0) {
                    var_a0 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
                }
                temp_v1 = (temp_a1 * 0x14) + var_t0;
                temp_ft4 = *(f32 *)((u8 *)temp_v1 + 0xC);
                var_fs2 += temp_ft4;
                if (var_fs3 < var_fs2) {
                    if (temp_ft4 != 0.0f) {
                        temp_fa1 = (var_fs2 - var_fs3) / temp_ft4;
                        temp_v0 = (var_a0 * 0x14) + var_t0;
                        temp_fv0 = *(f32 *)((u8 *)temp_v0 + 0);
                        temp_fv1 = *(f32 *)((u8 *)temp_v0 + 4);
                        temp_fa0 = *(f32 *)((u8 *)temp_v0 + 8);
                        *(f32 *)((u8 *)temp_v0 + 0) = (f32) (temp_fv0 - ((temp_fv0 - *(f32 *)((u8 *)temp_v1 + 0)) * temp_fa1));
                        *(f32 *)((u8 *)temp_v0 + 4) = (f32) (temp_fv1 - ((temp_fv1 - *(f32 *)((u8 *)temp_v1 + 4)) * temp_fa1));
                        *(f32 *)((u8 *)temp_v0 + 8) = (f32) (temp_fa0 - ((temp_fa0 - *(f32 *)((u8 *)temp_v1 + 8)) * temp_fa1));
                        *(f32 *)((u8 *)temp_v1 + 0xC) = (f32) (*(f32 *)((u8 *)temp_v1 + 0xC) * (1.0f - temp_fa1));
                    }
                    var_fs2 = var_fs3;
                    if (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D)) {
                        do {
                            *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (*(s8 *)((u8 *)arg0 + 0x2D) + 1);
                            if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2D)) {
                                *(s8 *)((u8 *)arg0 + 0x2D) = 0;
                            }
                            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) - 1);
                        } while (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D));
                    }
                }
            } while (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D));
        }
        if (var_fs2 != 0.0f) {
            var_fa0 = 1.0f / var_fs2;
        } else {
            var_fa0 = 0.0f;
        }
        sp80 = var_fa0;
        sp84 = var_fs2;
    }
    if (*(s8 *)((u8 *)arg0 + 0x2C) >= 2) {
        var_v0 = *(s8 *)((u8 *)arg0 + 0x2E);
        var_fv0 = sp84;
        do {
            var_v0 -= 1;
            if (var_v0 < 0) {
                var_v0 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
            }
            temp_v1_2 = (var_v0 * 0x14) + var_t0;
            *(f32 *)((u8 *)temp_v1_2 + 0x10) = (f32) (var_fv0 * (*(f32 *)((u8 *)sp8C + 0x14) * sp80));
            var_fv0 -= *(f32 *)((u8 *)temp_v1_2 + 0xC);
        } while (var_v0 != *(s8 *)((u8 *)arg0 + 0x2D));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D3FD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3FD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D4300.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D49C0.s")
s32 func_1514654C(void *, s32, s32, void **, void **, s32);
extern u8 D_800A09D0;
extern u8 D_800A09DC;

s32 func_150D4AE0(f32 *arg0, f32 *arg1, void *arg2, s32 arg3) {
    void *sp30[2];
    void *sp28[2];

    if (*(s32 *)((u8 *)arg2 + 0x1D4) != 0) {
        sp30[0] = &D_800A09D0;
        sp30[1] = &D_800A09DC;
        sp28[0] = arg0;
        sp28[1] = arg1;
        if (func_1514654C(arg2, arg3, 0, sp30, sp28, 2) != 0) {
            return 1;
        }
        return 0;
    }
    arg0[0] = *(f32 *)((u8 *)arg2 + 0x14);
    arg0[1] = *(f32 *)((u8 *)arg2 + 0x18) + 100.0f;
    arg0[2] = *(f32 *)((u8 *)arg2 + 0x1C);
    arg1[0] = *(f32 *)((u8 *)arg2 + 0x14);
    arg1[1] = *(f32 *)((u8 *)arg2 + 0x18) + 100.0f + 500.0f;
    arg1[2] = *(f32 *)((u8 *)arg2 + 0x1C);
    return 2;
}
void func_150D4BD4(s32 arg0) {
    func_150D4C2C(arg0);
    func_151478F4(arg0);
}
void func_150D4C00(s32 arg0) {
    func_150D4C2C(arg0);
    func_15147928(arg0);
}
void func_1000FD38(void *, void *, s32);
void func_1516972C(s32);
extern s8 D_8008FD8C;
void func_150D5124(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D4C2C CURRENT (118) */
void func_150D4C2C(s32 arg0) {
    void *sp20;
    void *temp_s0;

    temp_s0 = *(void **)((u8 *)arg0 + 0x98);
    if (D_8008FD8C < 5) {
        func_1000FD38((void *)&func_150D5124, temp_s0, 0x5B3);
    }
    sp20 = (void *)&func_150D5124;
    func_1000FD38((void *)&func_150D5124, temp_s0, 0x5B4);
    func_1000FD38(sp20, temp_s0, 0x5BC);
    if (*(s32 *)((u8 *)temp_s0 + 0xC) != 0) {
        func_1516972C(*(s32 *)((u8 *)temp_s0 + 0xC));
    }
    if (*(s32 *)((u8 *)temp_s0 + 0x10) != 0) {
        func_1516972C(*(s32 *)((u8 *)temp_s0 + 0x10));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D4C2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D4C2C.s")
extern s32 D_800BE9E4;
extern s32 D_800A09C0[];
extern f32 D_800A0A14;
s32 func_150ADA20();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D4CC4 CURRENT (20) */
s32 func_150D4CC4(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    void *temp_v1;

    temp_v1 = (u8 *)arg0 + 0x110;
    *(s16 *)((u8 *)arg0 + 0x170) =
        (s16)(*(s16 *)((u8 *)arg0 + 0x170) - D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0x170) < 0) {
        *(s8 *)((u8 *)arg0 + 0x18) =
            (s8)D_800A09C0[func_150ADA20() & 3];
        *(s16 *)((u8 *)arg0 + 0x170) =
            (s16)((func_150ADA20(arg0) & 7) + 3);
    }
    temp_fv0 = *(f32 *)((u8 *)temp_v1 + 0x48);
    temp_fv1 = (*(f32 *)((u8 *)arg0 + 0x174) - temp_fv0) * D_800A0A14;
    temp_fv0 += temp_fv1;
    *(f32 *)((u8 *)temp_v1 + 0x48) = temp_fv0;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D4CC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D4CC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D4D58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D5124.s")
