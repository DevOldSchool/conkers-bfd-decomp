#include "types.h"

/*
 * Reviewed source unit: src/game/game_144C70.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151177C0
 * - func_151179BC
 * - func_15117D3C
 * - func_15117DA4
 * - func_15117F3C
 * - func_151189AC
 * - func_15118F24
 * - func_151193AC
 * - func_151193F4
 * - func_151194D4
 * - func_151196D4
 * - func_15119938
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151177C0.s")
f32 func_15047C00(f32);                             /* extern */
f32 func_15047D60(f32);                             /* extern */
s32 func_150AD9A0(s32, s32, s32, s16);              /* extern */
extern f32 D_800A2FDC;
extern f32 D_800A2FE0;
extern f32 D_800A2FE4;
extern f32 D_800A2FE8;
extern f32 D_800A2FEC;
extern f32 D_800A2FF0;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151179BC CURRENT (10363) */
void func_151179BC(void *arg0) {
    s16 sp56;
    s16 sp54;
    s16 sp52;
    s16 sp50;
    s32 sp48;
    s32 sp3C;
    s32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 var_v1_2;
    s32 temp_a0;
    s32 temp_a0_2;
    u8 temp_t1;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_t7;
    u8 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_t0;
    s32 var_v1;
    u8 temp_t9;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x3C);
    var_v1 = *(s32 *)((u8 *)arg0 + 0x80);
    temp_t7 = temp_v0 >> 0x10;
    temp_t6 = *(u8 *)((u8 *)arg0 + 0x73) & 3;
    temp_t1 = temp_v0 & 0xFFFF;
    if (var_v1 == 0) {
        var_v1 = *(s16 *)((u8 *)arg0 + 0x14) | 0x80000000;
        *(s32 *)((u8 *)arg0 + 0x7C) = (s32) ((*(s16 *)((u8 *)arg0 + 0x10) & 0xFFFF) | (*(s16 *)((u8 *)arg0 + 0x12) << 0x10));
        *(s32 *)((u8 *)arg0 + 0x80) = var_v1;
    }
    temp_v0_2 = *(s32 *)((u8 *)arg0 + 0x7C);
    temp_t3 = temp_v0_2 >> 0x10;
    if (temp_t6 == 0) {
        *(s16 *)((u8 *)arg0 + 0x10) = (s16) temp_v0_2;
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) temp_t3;
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) var_v1;
        return;
    }
    sp52 = (s16) var_v1;
    sp54 = (s16) temp_t3;
    sp56 = (s16) temp_v0_2;
    sp38 = temp_t1;
    sp3C = temp_t6;
    sp50 = (s16) temp_t7;
    temp_v0_3 = func_150AD9A0((s16) temp_v0_2 - *(s16 *)((u8 *)arg0 + 0x10), (s16) temp_t3 - *(s16 *)((u8 *)arg0 + 0x12), (s16) var_v1 - *(s16 *)((u8 *)arg0 + 0x14), (s16) temp_t7);
    var_t0 = temp_t6;
    if (var_t0 == 3) {
        if ((s16) temp_t7 < 0) {
            sp48 = (s32) -(s16) temp_t7;
        } else {
            sp48 = (s32) (s16) temp_t7;
        }
        if ((temp_t1 != 0) && !(*(u8 *)((u8 *)arg0 + 0x4F) & 4) && !(*(u8 *)((u8 *)arg0 + 0x73) & 4)) {
            temp_a0 = *(s32 *)((u8 *)arg0 + 0x84);
            if (D_800BE9E4 < temp_a0) {
                *(s32 *)((u8 *)arg0 + 0x84) = (s32) (temp_a0 - D_800BE9E4);
            } else {
                var_t0 = 1;
            }
        } else {
            *(s32 *)((u8 *)arg0 + 0x84) = temp_t1;
        }
    } else {
        temp_a0_2 = temp_v0_3 + 6;
        if (var_t0 == 2) {
            sp48 = temp_a0_2;
            if ((s16) temp_t7 < 0) {
                var_v1_2 = -(s16) temp_t7;
            } else {
                var_v1_2 = (s16) temp_t7;
            }
            if (temp_a0_2 >= var_v1_2) {
                var_t0 = 3;
                if ((s16) temp_t7 < 0) {
                    sp48 = (s32) -(s16) temp_t7;
                } else {
                    sp48 = (s32) (s16) temp_t7;
                }
                *(s32 *)((u8 *)arg0 + 0x84) = temp_t1;
            }
        } else if (var_t0 == 1) {
            if (temp_v0_3 < 3) {
                sp48 = 0;
                var_t0 = 0;
            } else {
                sp48 = temp_v0_3 - 3;
            }
        }
    }
    if (temp_v0_3 != sp48) {
        sp3C = var_t0;
        sp50 = (s16) temp_t7;
        sp34 = func_15047C00(*(f32 *)((u8 *)arg0 + 0) * D_800A2FDC);
        sp30 = func_15047D60(*(f32 *)((u8 *)arg0 + 0) * D_800A2FE0);
        sp2C = func_15047C00(*(f32 *)((u8 *)arg0 + 4) * D_800A2FE4);
        sp28 = func_15047D60(*(f32 *)((u8 *)arg0 + 4) * D_800A2FE8);
        sp24 = func_15047C00(*(f32 *)((u8 *)arg0 + 8) * D_800A2FEC);
        temp_fv0 = func_15047D60(*(f32 *)((u8 *)arg0 + 8) * D_800A2FF0);
        if ((s16) temp_t7 < 0) {
            sp48 = -sp48;
        }
        temp_fa0 = sp34 * sp28;
        temp_fv1 = (f32) sp48;
        *(s16 *)((u8 *)arg0 + 0x10) = (s16) (s32) ((f32) sp56 + (temp_fv1 * ((temp_fa0 * sp24) + (sp30 * temp_fv0))));
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((f32) sp54 + (temp_fv1 * ((temp_fa0 * temp_fv0) - (sp30 * sp24))));
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) ((f32) sp52 + (temp_fv1 * sp34 * sp2C));
    }
    temp_t9 = *(u8 *)((u8 *)arg0 + 0x73) & 0xFFFC;
    *(u8 *)((u8 *)arg0 + 0x73) = temp_t9;
    *(u8 *)((u8 *)arg0 + 0x73) = (u8) (temp_t9 | var_t0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151179BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151179BC.s")
typedef struct Game144C70NestedState {
    u8 pad0[0x57];
    u8 enabled;
} Game144C70NestedState;

typedef struct Game144C70EventState {
    s32 kind;
    u8 pad4[0x318];
    Game144C70NestedState *nested;
} Game144C70EventState;

typedef struct Game144C70MotionState {
    u8 pad0[0x3C];
    s32 packed;
    u8 pad40[0xF];
    u8 flags;
    u8 pad50[0x23];
    volatile u8 motion;
} Game144C70MotionState;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15117D3C CURRENT (560) */
void func_15117D3C(Game144C70MotionState *arg0, Game144C70EventState *arg1) {
    s32 temp_v0;
    u8 temp_t5;
    u8 temp_v1;

    temp_v0 = arg0->packed;
    if ((arg1->kind == 1) && (arg0->flags & 4)) {
        temp_v1 = arg0->motion;
        if (!(temp_v1 & 3) && !(temp_v1 & 4) &&
            ((temp_t5 = temp_v1 & 0xFFFC, ((temp_v0 & 0xFFFF) == 0)) ||
             (arg1->nested->enabled == 1))) {
            arg0->motion = temp_t5;
            arg0->motion = temp_t5 | 2;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15117D3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_15117D3C.s")
f32 func_15047C00(f32);
f32 func_15047D60(f32);
void *func_151149AC(u8);
void func_1511F31C(void *);
extern f32 D_800A2FF4;
extern f32 D_800A2FF8;
extern f32 D_800A2FFC;
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15117DA4 CURRENT (210) */
void func_15117DA4(u8 *arg0, f32 arg1, f32 arg2, f32 arg3,
                   volatile f32 *arg4) {
    f32 angle;
    f32 sine;
    f32 cosine;
    f32 x;
    f32 z;

    if (*(u16 *)(arg0 + 0x54) == 0x8006 && D_800BE9F0 == 0x35) {
        arg0 = func_151149AC(0xFD);
        func_1511F31C(arg0);
        arg2 = D_800A2FF4;
        arg1 = 0.0f;
        arg3 = 0.0f;
    }
    angle = *(f32 *)arg0 * D_800A2FF8;
    sine = func_15047D60(angle);
    cosine = func_15047C00(angle);
    arg4[0] = arg1;
    arg4[1] = (arg2 * cosine) - (arg3 * sine);
    arg4[2] = (arg2 * sine) + (arg3 * cosine);
    angle = *(f32 *)(arg0 + 4) * D_800A2FFC;
    sine = func_15047D60(angle);
    cosine = func_15047C00(angle);
    z = arg4[2];
    x = arg4[0];
    arg4[0] = (z * sine) + (x * cosine);
    arg4[2] = (z * cosine) + (-x * sine);
    arg4[0] += (f32)*(s16 *)(arg0 + 0x10);
    arg4[1] += (f32)*(s16 *)(arg0 + 0x12);
    arg4[2] += (f32)*(s16 *)(arg0 + 0x14);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15117DA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_15117DA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_15117F3C.s")
void func_151189AC(void *arg0, s32 arg1);

void func_1511896C(void *arg0) {
    func_151189AC(arg0, 0);
}
void func_1511898C(void *arg0) {
    func_151189AC(arg0, 3);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151189AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_15118F24.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151193AC CURRENT (25) */
void func_151193AC(void *arg0, void *arg1) {
    s32 temp_t1;
    s32 temp_v0;

    if ((*(s32 *)((u8 *)arg1 + 0) == 1) && (*(u8 *)((u8 *)arg1 + 0x65) == 0)) {
        temp_v0 = *(u8 *)((u8 *)arg0 + 0x73);
        if (!(temp_v0 & 3)) {
            temp_t1 = temp_v0 & 0xFFFC;
            if (!(temp_v0 & 4)) {
                *(volatile u8 *)((u8 *)arg0 + 0x73) = temp_t1;
                *(u8 *)((u8 *)arg0 + 0x73) = (u8) (temp_t1 | 2);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151193AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151193AC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151193F4 CURRENT (1120) */
void func_151193F4(void *arg0) {
    s16 temp_t0;
    s16 temp_v0;
    s32 temp_v1;

    if (*(s32 *)((u8 *)arg0 + 0x84) == 0) {
        *(s32 *)((u8 *)arg0 + 0x84) = (s32) (*(s16 *)((u8 *)arg0 + 0x12) | 0x80000000);
    }
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x7C);
    if (temp_v1 != 0) {
        temp_v0 = *(s16 *)((u8 *)arg0 + 0x12);
        *(u8 *)((u8 *)arg0 + 0x73) = (u8) (*(u8 *)((u8 *)arg0 + 0x73) & 0xFFFC);
        temp_t0 = ((s32) ((((s32) *(s32 *)((u8 *)arg0 + 0x3C) >> 0x10) & 0xFFFF) * *(s32 *)((u8 *)arg0 + 0x80)) / 256) + (s16) *(s32 *)((u8 *)arg0 + 0x84);
        {
            s32 temp_a1 = temp_v0 - temp_t0;
        if (temp_t0 != temp_v0) {
            if (temp_a1 < 0) {
                if (-temp_a1 < temp_v1) {
                    *(s16 *)((u8 *)arg0 + 0x12) = temp_t0;
                } else {
                    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (temp_v0 + temp_v1);
                }
            } else if (temp_a1 < temp_v1) {
                *(s16 *)((u8 *)arg0 + 0x12) = temp_t0;
            } else {
                *(s16 *)((u8 *)arg0 + 0x12) = (s16) (temp_v0 - temp_v1);
            }
            *(u8 *)((u8 *)arg0 + 0x73) = (u8) *(u8 *)((u8 *)arg0 + 0x73);
            return;
        }
        *(u8 *)((u8 *)arg0 + 0x73) = (u8) (*(u8 *)((u8 *)arg0 + 0x73) | 3);
    }
        }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151193F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151193F4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151194D4 CURRENT (2379) */
void func_151194D4(void *arg0, void *arg1, s32 arg2, u16 arg3) {
    s8 *sp4C;
    u32 sp44;
    s16 temp_v0;
    s16 temp_v1_2;
    s32 var_s1_2;
    s32 var_v0_2;
    s8 *var_t0;
    s8 var_v0;
    u32 temp_v1;
    u32 var_s0;
    u32 var_s0_2;
    u32 var_s1;
    u32 var_s5;
    void *temp_a1;
    void *temp_a1_2;

    var_t0 = *(s8 **)((u8 *)arg0 + 0x1C);
    var_v0 = *var_t0;
    var_s5 = sp44;
    if (var_v0 != -0x21) {
        do {
            switch (var_v0) {                       /* irregular */
            case 1:
                var_s5 = (u32) (*(u32 *)((u8 *)var_t0 + 4) & 0xFFFFFF) >> 4;
                break;
            case 5:
                sp4C = var_t0;
                temp_v1 = *(u32 *)((u8 *)var_t0 + 4);
                var_v0_2 = 0;
                var_s1 = 0;
                var_s0 = temp_v1;
                do {
                    temp_a1 = *(s32 *)((u8 *)arg0 + 0x28) + ((((u32) (var_s0 & 0xFF) / 10U) + var_s5) * 0x10);
                    var_s1 += 1;
                    if ((*(s16 *)((u8 *)temp_a1 + 0) == *(s16 *)((u8 *)arg1 + 0)) && (*(s16 *)((u8 *)temp_a1 + 2) == *(s16 *)((u8 *)arg1 + 2)) && (*(s16 *)((u8 *)temp_a1 + 4) == *(s16 *)((u8 *)arg1 + 4))) {
                        var_v0_2 = 1;
                        *(u16 *)((u8 *)temp_a1 + 6) = arg3;
                    } else {
                        var_s0 = var_s0 >> 8;
                    }
                } while (var_s1 < 3U);
                var_s0_2 = temp_v1;
                if (var_v0_2 != 0) {
                    var_s1_2 = 0;
                    do {
                        temp_a1_2 = *(s32 *)((u8 *)arg0 + 0x28) + ((((u32) (var_s0_2 & 0xFF) / 10U) + var_s5) * 0x10);
                        if (*(u16 *)((u8 *)temp_a1_2 + 6) == 0) {
                            temp_v1_2 = *(s16 *)((u8 *)temp_a1_2 + 4);
                            temp_v0 = *(s16 *)((u8 *)temp_a1_2 + 0);
                            if (arg2 < ((temp_v1_2 * temp_v1_2) + (temp_v0 * temp_v0))) {
                                *(u16 *)((u8 *)temp_a1_2 + 6) = arg3;
                                func_151194D4(arg0, temp_a1_2, arg2, arg3);
                            }
                        }
                        var_s1_2 += 1;
                        var_s0_2 = var_s0_2 >> 8;
                    } while (var_s1_2 != 3);
                }
                var_t0 = sp4C;
                break;
            }
            var_v0 = *(s8 *)((u8 *)var_t0 + 8);
            var_t0 += 8;
        } while (var_v0 != -0x21);
        sp44 = var_s5;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151194D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151194D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_151196D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_144C70/func_15119938.s")
