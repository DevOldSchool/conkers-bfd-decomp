#include "types.h"

/*
 * Reviewed source unit: src/game/game_5D2C0.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1502FE10
 * - func_1502FFD8
 * - func_15030158
 * - func_15030310
 * - func_15030468
 * - func_15030AF4
 * - func_15030D54
 * - func_15030E08
 * - func_15030F94
 * - func_15031070
 * - func_150311C4
 * - func_1503195C
 * - func_150319CC
 * - func_15031A50
 * - func_15031C14
 * - func_15031E2C
 * - func_15031E7C
 * - func_15031FC8
 * - func_150331B8
 * - func_1503327C
 * - func_15033440
 * - func_150334B8
 * - func_150335C8
 * - func_150337E4
 * - func_15033838
 * - func_15033BDC
 * - func_15033E84
 * - func_15033EC4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1502FE10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1502FFD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030158.s")
void func_15030310(void *arg0, s32 arg1, s32 arg2);

void func_150302F0(void *arg0, s32 arg1) {
    func_15030310(arg0, arg1, 0xFF);
}
/* Call context: func_15030158: unique active declaration in the allowed source */
void func_15030158(void *, s32);
extern void * D_800C3EE0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15030310 CURRENT (2735) */
void func_15030310(void *arg0, s32 arg1, s32 arg2) {
    s32 var_s0;
    void *temp_s1;
    void *var_a0;

    var_s0 = arg2;
    if (*(u8 *)((u8 *)arg0 + 0x3B) == 0) {
        return;
    }
    var_a0 = D_800C3EE0;
    if (var_a0 != 0) {
loop_3:
        temp_s1 = *(void **)((u8 *)var_a0 + 0x54);
        if ((*(u8 *)((u8 *)arg0 + 0x3B) == *(u8 *)((u8 *)var_a0 + 0)) && (arg1 == *(u8 *)((u8 *)var_a0 + 6))) {
            if ((var_s0 != 0xFF) && (var_s0 != 0)) {
                var_s0 -= 1;
                var_a0 = temp_s1;
                goto block_10;
            }
            func_15030158(var_a0, 0);
            if (var_s0 != 0) {
                goto block_9;
            }
        } else {
block_9:
            var_a0 = temp_s1;
block_10:
            if (var_a0 != 0) {
                goto loop_3;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15030310 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030310.s")
extern void *D_800C3EE0;
void func_15030158(void *, s32);

s32 func_150303E4(void *arg0) {
    s32 var_s1;
    void *temp_s0;
    void *var_a0;

    if (*(u8 *)((u8 *)arg0 + 0x3B) == 0) {
        return 0;
    }
    var_a0 = D_800C3EE0;
    var_s1 = 0;
    if (var_a0 != 0) {
        do {
            temp_s0 = *(void **)((u8 *)var_a0 + 0x54);
            if (*(u8 *)((u8 *)arg0 + 0x3B) == *(u8 *)var_a0) {
                var_s1 = 1;
                func_15030158(var_a0, 0);
            }
            var_a0 = temp_s0;
        } while (temp_s0 != 0);
    }
    return var_s1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030AF4.s")
extern void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15030D54 CURRENT (1571) */
void func_15030D54(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 *temp_v0;

    temp_v0 = (f32 *)func_10003C40(0x18, 1, 0, 2);
    *(f32 **)((u8 *)arg0 + 0x44) = temp_v0;
    if (temp_v0 != 0) {
        temp_v0[0] = arg1;
        temp_v0[1] = arg2;
        temp_v0[2] = arg3;
        temp_v0[3] = arg4;
        temp_v0[4] = arg5;
        temp_v0[5] = arg6;
        if (*(void **)((u8 *)arg0 + 0x34) == 0) {
            *(void **)((u8 *)arg0 + 0x34) = func_10003C40(0x80, 1, 2, 2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15030D54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030D54.s")
/* Call context: func_15083E90: unique active project prototype */
void * func_15083E90(u8);
s32 func_150311C4(s32, void *, void *, s32, s32);   /* extern */
s32 func_1506196C(void *, s32);                     /* extern */
extern void * D_800C3EE0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15030E08 CURRENT (2824) */
s32 func_15030E08(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s6;
    void *temp_s2;
    void *temp_v0;
    void *var_s0;

    var_s6 = arg0;
    var_s0 = D_800C3EE0;
    if (var_s0 != 0) {
        do {
            temp_s2 = *(void **)((u8 *)var_s0 + 0x54);
            if (*(u8 *)((u8 *)var_s0 + 3) == 0) {

            } else {
                temp_v0 = func_15083E90(*(u8 *)((u8 *)var_s0 + 0));
                if ((temp_v0 == 0) || (*(s32 *)((u8 *)temp_v0 + 0x1D4) == 0) || (temp_v1 = 1 << arg1, (temp_v1 == (*(u8 *)((u8 *)temp_v0 + 0x74) & temp_v1)))) {

                } else if (arg2 == 2) {
                    if (*(u8 *)((u8 *)temp_v0 + 5) != 7) {

                    } else {
                        goto block_19;
                    }
                } else {
                    temp_v0_2 = func_1506196C(temp_v0, arg1);
                    if (arg2 == 1) {
                        if (!(*(u8 *)((u8 *)var_s0 + 4) & 2) && (temp_v0_2 == 0xFF) && (*(u8 *)((u8 *)temp_v0 + 5) != 1)) {

                        } else {
                            goto block_19;
                        }
                    } else if ((*(u8 *)((u8 *)var_s0 + 4) & 2) || (temp_v0_2 < 0xFF) || (*(u8 *)((u8 *)temp_v0 + 5) == 1)) {

                    } else {
block_19:
                        var_s6 = func_150311C4(var_s6, var_s0, temp_v0, arg1, 0);
                    }
                }
            }
            var_s0 = temp_s2;
        } while (var_s0 != 0);
    }
    return var_s6;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15030E08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030E08.s")
/* Call context: func_150311C4: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15030F94 CURRENT (2340) */
s32 func_15030F94(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 var_s3;
    void *temp_s1;
    void *var_s0;

    var_s3 = arg0;
    if ((arg1 == 0) || (*(s32 *)((u8 *)arg1 + 0x1D4) == 0) || (*(u8 *)((u8 *)arg1 + 0x3B) == 0)) {

    } else {
        var_s0 = D_800C3EE0;
        if (var_s0 != 0) {
            do {
                temp_s1 = *(void **)((u8 *)var_s0 + 0x54);
                if ((*(u8 *)((u8 *)arg1 + 0x3B) != *(u8 *)((u8 *)var_s0 + 0)) || (*(u8 *)((u8 *)var_s0 + 3) == 0)) {

                } else {
                    var_s3 = func_150311C4(var_s3, var_s0, arg1, arg2, arg3);
                }
                var_s0 = temp_s1;
            } while (var_s0 != 0);
        }
    }
    return var_s3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15030F94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030F94.s")
void *func_1503195C(void *, s32, s32);
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15031070 CURRENT (660) */
s32 func_15031070(void *arg0, void *arg1, s32 *arg2, s32 *arg3) {
    u8 *model;
    s32 base;
    s32 value;
    u16 child;
    void *object;

    model = *(u8 **)((u8 *)arg0 + 0x48);
    if (model != 0) {
        if (model[0x3F6] == 0) {
            return 0;
        }
        *arg2 = *(s32 *)(model + 0x3E8 + D_800BE9C0 * 4);
        *arg3 = *(s32 *)(*(u8 **)((u8 *)arg0 + 0x48) + 0x3E0 + D_800BE9C0 * 4);
        goto success;
    }
    base = *(s32 *)((u8 *)arg0 + 0x34);
    if (base != 0) {
        *arg2 = base + (D_800BE9C0 << 6);
        *arg3 = *(s32 *)((u8 *)arg1 + 0x1D4) + (((u8 *)arg0)[2] << 6);
        goto success;
    }
    child = *(u16 *)((u8 *)arg0 + 0x1E);
    if (child != 0) {
        object = func_1503195C(arg1, child, 0);
        if (object == 0) {
            return 0;
        }
        if (func_15031070(object, arg1, arg2, arg3) == 0) {
            return 0;
        }
        *arg2 += *(u16 *)((u8 *)arg0 + 0x20) << 6;
        return 1;
    }
    value = *(s32 *)((u8 *)arg1 + 0x1D4);
    *arg2 = value;
    value += ((u8 *)arg0)[2] << 6;
    *arg2 = value;
    *arg3 = value;
success:
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15031070 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150311C4.s")
void *func_1503195C(void *arg0, s32 arg1, s32 arg2);

void func_1503192C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = func_1503195C(arg0, arg1, arg3);
    if (temp_v0 != 0) {
        *(u8 *)((u8 *)temp_v0 + 3) = (u8) arg2;
    }
}
extern void * D_800C3EE0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503195C CURRENT (110) */
void *func_1503195C(void *arg0, s32 arg1, s32 arg2) {
    s32 var_a2;
    u8 temp_v0;
    void *var_v1;

    var_a2 = arg2;
    temp_v0 = *(u8 *)((u8 *)arg0 + 0x3B);
    if (temp_v0 == 0) {
        return 0;
    }
    var_v1 = D_800C3EE0;
    if (var_v1 != 0) {
loop_3:
        if ((temp_v0 == *(u8 *)((u8 *)var_v1 + 0)) && (arg1 == *(u8 *)((u8 *)var_v1 + 6))) {
            var_a2 -= 1;
            if (var_a2 != 0) {
                goto block_8;
            }
            return var_v1;
        }
block_8:
        var_v1 = *(void **)((u8 *)var_v1 + 0x54);
        if (var_v1 == 0) {
            /* Duplicate return node #9. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_3;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503195C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1503195C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150319CC CURRENT (255) */
void *func_150319CC(s32 arg0, void *arg1) {
    void *temp_v0;
    void *temp_v0_2;
    void *var_v1;
    void *var_v1_2;

    if (arg1 != 0) {
        var_v1_2 = D_800C3EE0;
        if (var_v1_2 != 0) {
loop_3:
            temp_v0 = *(void **)((u8 *)var_v1_2 + 0x54);
            if ((*(u8 *)((u8 *)arg1 + 0x3B) == *(u8 *)((u8 *)var_v1_2 + 0)) && (arg0 == *(u8 *)((u8 *)var_v1_2 + 6))) {
                return var_v1_2;
            }
            var_v1_2 = temp_v0;
            if (temp_v0 == 0) {
                goto block_7;
            }
            goto loop_3;
        }
    }
block_7:
    var_v1 = D_800C3EE0;
    if (var_v1 != 0) {
loop_8:
        temp_v0_2 = *(void **)((u8 *)var_v1 + 0x54);
        if (arg0 == *(u8 *)((u8 *)var_v1 + 6)) {
            return var_v1;
        }
        var_v1 = temp_v0_2;
        if (temp_v0_2 == 0) {
            /* Duplicate return node #11. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_8;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150319CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150319CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031C14.s")
typedef struct {
    u8 pad_0[0x18];
    s16 field_18;
    u8 pad_1A[0x1E];
    s32 field_38;
    s32 field_3C;
} Game5D2C0State;

extern s32 D_800902BC[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15031E2C CURRENT (150) */
s32 func_15031E2C(Game5D2C0State *arg0, s16 arg1) {
    s32 temp_v1;
    s32 var_v0;
    s32 temp_t9;

    temp_v1 = arg0->field_38;
    var_v0 = temp_v1;
    if (temp_v1 >= 3) {
        var_v0 = 5 - var_v0;
    }
    arg0->field_18 = (s16)D_800902BC[var_v0];
    temp_t9 = temp_v1 + 1;
    arg0->field_38 = temp_t9;
    if (temp_t9 >= 6) {
        arg0->field_38 = 0;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15031E2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031E2C.s")
extern f32 D_800970DC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15031E7C CURRENT (2460) */
s32 func_15031E7C(u8 *arg0, u8 *arg1) {
    u8 *object;
    s32 commands;
    f32 factor;
    f32 progress;
    s32 index;
    s32 count;
    s32 marker;
    u16 kind;

    object = *(u8 **)(arg1 + 0x2D0);
    if (object == 0) {
        return 0;
    }
    commands = **(s32 **)(arg0 + 0x24);
    if (commands == 0) {
        return 0;
    }
    kind = *(u16 *)(arg1 + 0x84);
    marker = -14;
    if (kind == 0x55) {
        factor = 1.0f;
    } else if (kind == 0x56) {
        factor = 0.0f;
    } else {
        progress = *(f32 *)(object + 8);
        if ((progress >= 0.0f) && (progress <= 120.0f)) {
            factor = 1.0f - progress * D_800970DC;
        } else {
            factor = 0.0f;
        }
    }
    index = 0;
    count = 4;
    do {
        count--;
        if (*(s8 *)(commands + index * 8) != marker) {
            do {
                index++;
            } while (*(s8 *)(commands + index * 8) != marker);
        }
        if (count != 0) {
            index++;
        }
    } while (count != 0);
    *(s32 *)(commands + index * 8) = (((s32)(25.0f * factor + 2.0f)) & 0xFFF) | 0xF2002000;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15031E7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031E7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031FC8.s")
void func_1503F5B8(void *, s32, s32, s32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150331B8 CURRENT (2021) */
s32 func_150331B8(void *arg0, void *arg1) {
    void *temp_v0;
    u8 *state;
    u8 *state_after;
    s32 temp_t7;
    f32 temp_fv0;

    temp_v0 = *(void **)((u8 *)arg1 + 0x2D0);
    state = *(u8 **)((u8 *)arg0 + 0x48);
    if (state != 0) {
        temp_t7 = *(s32 *)((u8 *)arg1 + 0x2E4) & 0xFF;
        if (temp_t7 != 0xFF) {
            func_1503F5B8(state, 0, temp_t7, 0x3F800000, 0.0f, 1);
        }
        if (temp_v0 != 0) {
            state_after = *(u8 **)((u8 *)arg0 + 0x48);
            *(f32 *)(state_after + 8) = *(f32 *)((u8 *)temp_v0 + 8);
            temp_fv0 = *(f32 *)(state_after + 0x18);
            if (temp_fv0 <= *(f32 *)(state_after + 8)) {
                *(f32 *)(state_after + 8) = temp_fv0 - 1.0f;
            }
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150331B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150331B8.s")
void func_1503F5B8(void *, s32, s32, s32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503327C CURRENT (805) */
s32 func_1503327C(void *arg0, s32 arg1) {
    s32 var_v0;
    void *var_s0;

    var_s0 = *(void **)((u8 *)arg0 + 0x48);
    if (var_s0 == 0) {
        return 0;
    }
    if ((*(u16 *)((u8 *)var_s0 + 4) & 0x8000) != 0x8000) {
        func_1503F5B8(var_s0, 0, 0, 0x3F800000, 0.0f, 1);
        var_s0 = *(void **)((u8 *)arg0 + 0x48);
    }
    var_v0 = 0;
    if ((*(f32 *)((u8 *)var_s0 + 0x18) - 1.0f) <= *(f32 *)((u8 *)var_s0 + 8)) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503327C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1503327C.s")
extern s32 D_800BE9E4;
extern u8 D_800C35EA;

s32 func_15033328(void *arg0, void *arg1) {
    if (D_800C35EA == 1) {
        return 0;
    }
    if ((*(u8 *)((u8 *)arg1 + 0xAD) == 0) && (*(f32 *)((u8 *)arg1 + 0x118) < *(f32 *)((u8 *)arg1 + 0x180))) {
        if (*(s32 *)((u8 *)arg0 + 0x38) > D_800BE9E4) {
            *(s32 *)((u8 *)arg0 + 0x38) = (s32) (*(s32 *)((u8 *)arg0 + 0x38) - D_800BE9E4);
            return 0;
        }
        return 1;
    }
    *(s32 *)((u8 *)arg0 + 0x38) = 0x1E;
    return 0;
}
extern f32 D_80097B68;

s32 func_150333A8(void *arg0, void *arg1) {
    void *temp_v0;

    if (D_800C35EA == 1) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg1 + 0xAD) != 0) {
        temp_v0 = *(void **)((u8 *)arg1 + 0x31C);
        if (temp_v0 != 0) {
            *(s8 *)((u8 *)temp_v0 + 0x11A) = 0;
        }
        return 1;
    }
    if ((D_80097B68 != *(f32 *)((u8 *)arg1 + 0x118)) && (*(f32 *)((u8 *)arg1 + 0x18) < (*(f32 *)((u8 *)arg1 + 0x118) + 300.0f))) {
        *(s8 *)((u8 *)arg0 + 3) = 0;
    } else {
        *(u8 *)((u8 *)arg0 + 3) = 0xFF;
    }
    return 0;
}
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15033440 CURRENT (1050) */
s32 func_15033440(void *arg0, void *arg1) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 1);
    if (temp_v0 != 0x27) {
        if (temp_v0 != 0x29) {
            if (temp_v0 == 0x35) {
                goto block_3;
            }
        } else if (*(u8 *)((u8 *)arg1 + 5) == 5) {
            *(s8 *)((u8 *)arg0 + 2) = 0;
        }
    } else {
block_3:
        if (*(u8 *)((u8 *)arg1 + 5) == 5) {
            *(s8 *)((u8 *)arg0 + 2) = 0;
            *(s16 *)((u8 *)arg0 + 0x22) = (s16) (*(s16 *)((u8 *)arg0 + 0x22) + (D_800BE9E4 * 0xAAA));
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15033440 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033440.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150334B8 CURRENT (1760) */
s32 func_150334B8(u8 *arg0, s32 arg1) {
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_t1;
    s32 var_t3;
    u8 *var_v0;
    s32 var_v1;
    u8 *temp_a2;

    var_v0 = 0;
    var_v1 = 0;
    var_a1 = 0;
    if (*(u8 *)((u8 *)arg0 + 1) == 0x37) {
        var_v1 = 4;
        var_a1 = -0x64;
        var_v0 = (void *)(**(s32 **)((u8 *)arg0 + 0x24));
    }
    if (var_v0 != 0) {
        var_a0 = 0;
        if (var_v1 != 0) {
            do {
                var_v1 -= 1;
                if (*((var_a0 * 8) + var_v0) != -0xE) {
                    do {
                        var_a0 += 1;
                    } while (*((var_a0 * 8) + var_v0) != -0xE);
                }
                if (var_v1 != 0) {
                    var_a0 += 1;
                }
            } while (var_v1 != 0);
        }
        temp_a2 = (void *)(var_v0 + (var_a0 * 8));
        temp_v1 = *(s32 *)((u8 *)temp_a2 + 0);
        temp_a3 = *(s32 *)((u8 *)temp_a2 + 4);
        temp_t2 = ((temp_v1 >> 0xC) & 0xFFF) + var_a1;
        temp_t0 = ((temp_a3 >> 0xC) & 0xFFF) + 2;
        temp_t4 = temp_v1 & 0xFFF;
        var_t1 = temp_t2;
        var_t3 = temp_t4;
        if (temp_t2 >= temp_t0) {
            var_t1 = temp_t2 - temp_t0;
        }
        if (var_t1 < 0) {
            var_t1 += temp_t0;
        }
        temp_v0 = (temp_a3 & 0xFFF) + 2;
        if (temp_t4 >= temp_v0) {
            var_t3 = temp_t4 - temp_v0;
        }
        if (var_t3 < 0) {
            var_t3 += temp_v0;
        }
        *(s32 *)((u8 *)temp_a2 + 0) = (s32) (((var_t1 & 0xFFF) << 0xC) | 0xF2000000 | (var_t3 & 0xFFF));
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150334B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150334B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150335C8.s")
s32 func_1503378C(void *arg0, void *arg1) {
    u16 temp_v0;

    temp_v0 = *(u16 *)((u8 *)arg1 + 0x84);
    if ((*(u8 *)((u8 *)arg0 + 1) == 0x11) && ((temp_v0 == 0x3E) || (temp_v0 == 0x3D) || (temp_v0 == 0x41) || (temp_v0 == 0xD9) || (temp_v0 == 0x138) || (temp_v0 == 0x139))) {
        return 0;
    }
    return 1;
}
extern s32 D_800BE9E4;
extern s32 D_800902FC[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150337E4 CURRENT (85) */
s32 func_150337E4(Game5D2C0State *arg0, s32 arg1) {
    s32 temp_t8;

    temp_t8 = arg0->field_38 + D_800BE9E4;
    arg0->field_38 = temp_t8;
    if (temp_t8 >= 0x10) {
        arg0->field_38 = 0;
        arg0->field_3C ^= 1;
    }
    arg0->field_18 = D_800902FC[arg0->field_3C];
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150337E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150337E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033838.s")
void func_150334B8(u8 *, void *);
void func_1000FD38(void *, void *, s32);
s32 func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *,
                   void *, void *, s32, s32);
s32 func_15033BDC();
extern u8 D_800BEA0C;

s32 func_150339C8(u8 *arg0, void *arg1) {
    func_150334B8(arg0, arg1);
    if (D_800C35EA != 1) {
        if (D_800BEA0C != 0) {
            if (*(s32 *)(arg0 + 0x3C) != 0) {
                func_1000FD38((void *)&func_15033BDC, arg0, (s32)arg1);
            }
            *(s32 *)(arg0 + 0x3C) = 0;
        } else if (*(s32 *)(arg0 + 0x3C) == 0) {
            *(s32 *)(arg0 + 0x3C) = func_1000FA64(
                0x448, (s16)(s32)*(f32 *)((u8 *)arg1 + 0x14),
                (s16)(s32)*(f32 *)((u8 *)arg1 + 0x18),
                (s16)(s32)*(f32 *)((u8 *)arg1 + 0x1C),
                0x7D00, 0x3E8, 0x1F4, (void *)&func_15033BDC,
                arg0, arg1, 0, 0) | 0x80000000;
        }
    }
    return 0;
}
void func_1508B20C(f32, f32, f32, s32);
s32 func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *,
                   void *, void *, s32, s32);
s32 func_15033BDC();
extern u8 D_800BE616;

s32 func_15033AD8(void *arg0, void *arg1) {
    s32 temp_v0;

    if (D_800BE616 != 0) {
        func_1508B20C(*(f32 *)((u8 *)arg1 + 0x14),
                      *(f32 *)((u8 *)arg1 + 0x18),
                      *(f32 *)((u8 *)arg1 + 0x1C), 0x44610000);
    }
    if (*(s32 *)((u8 *)arg0 + 0x38) == 0) {
        temp_v0 = *(s32 *)((u8 *)arg0 + 0x3C);
        if (temp_v0 < 0x1E) {
            *(s32 *)((u8 *)arg0 + 0x3C) = temp_v0 + D_800BE9E4;
        } else {
            *(s32 *)((u8 *)arg0 + 0x3C) = func_1000FA64(
                0x513, (s16)(s32)*(f32 *)((u8 *)arg1 + 0x14),
                (s16)(s32)*(f32 *)((u8 *)arg1 + 0x18),
                (s16)(s32)*(f32 *)((u8 *)arg1 + 0x1C),
                0x7D00, 0x3E8, 0x1F4, &func_15033BDC,
                arg0, arg1, 0, 0);
            *(s32 *)((u8 *)arg0 + 0x38) = 0x513;
        }
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033BDC.s")
s32 func_15033E00(s32 arg0, void *arg1) {
    if (*(u8 *)((u8 *)arg1 + 5) == 3) {
        return 1;
    }
    return 0;
}
extern void *D_800C3EE0;

s32 func_15033E28(void *arg0, void **arg1) {
    s32 var_v1;
    void *temp_v0;
    void *var_a0;

    var_v1 = 0;
    if (D_800C3EE0 == 0) {
        return 0;
    }
    var_a0 = D_800C3EE0;
    if (D_800C3EE0 != 0) {
        do {
            temp_v0 = *(void **)((u8 *)var_a0 + 0x54);
            if (*(u8 *)((u8 *)arg0 + 0x3B) == *(u8 *)var_a0) {
                arg1[var_v1] = var_a0;
                var_v1 += 1;
            }
            var_a0 = temp_v0;
        } while (temp_v0 != 0);
    }
    return var_v1;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15033E84 CURRENT (360) */
void *func_15033E84(void *arg0) {
    void *temp_v0;
    void *var_v1;

    var_v1 = D_800C3EE0;
    if (var_v1 != 0) {
loop_2:
        temp_v0 = *(void **)((u8 *)var_v1 + 0x54);
        if (*(u8 *)((u8 *)arg0 + 0x3B) == *(u8 *)((u8 *)var_v1 + 0)) {
            return var_v1;
        }
        var_v1 = temp_v0;
        if (temp_v0 == 0) {
            /* Duplicate return node #5. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_2;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15033E84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033E84.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15033EC4 CURRENT (1545) */
void func_15033EC4(u8 arg0, u8 arg1) {
    u8 temp_a1;
    void *temp_v1;
    void *var_v0;

    var_v0 = D_800C3EE0;
    if (var_v0 != 0) {
        do {
            temp_a1 = *(u8 *)((u8 *)var_v0 + 0);
            temp_v1 = *(void **)((u8 *)var_v0 + 0x54);
            if (arg0 == temp_a1) {
                *(u8 *)((u8 *)var_v0 + 0) = arg1;
            } else if (arg1 == temp_a1) {
                *(u8 *)((u8 *)var_v0 + 0) = arg0;
            }
            var_v0 = temp_v1;
        } while (temp_v1 != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15033EC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033EC4.s")
extern u8 D_800C35EA;

s32 func_15033F0C(s32 arg0, void *arg1) {
    void *temp_v1;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp_v1 = *(void **)((u8 *)arg1 + 0x31C);
    if ((temp_v1 != 0) && (*(u8 *)((u8 *)temp_v1 + 0x78) != 9) && (*(u8 *)((u8 *)temp_v1 + 0x11A) != 3)) {
        *(u8 *)((u8 *)temp_v1 + 0x11A) = 0U;
        return 1;
    }
    return 0;
}
s32 func_15033F70(s32 arg0, void *arg1) {
    u8 temp_v0;
    void *temp_v1;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp_v1 = *(void **)((u8 *)arg1 + 0x31C);
    if (temp_v1 != 0) {
        temp_v0 = *(u8 *)((u8 *)temp_v1 + 0x78);
        if ((temp_v0 != 0xC) && (temp_v0 != 0x16) && (*(u8 *)((u8 *)temp_v1 + 0x11A) != 3)) {
            *(u8 *)((u8 *)temp_v1 + 0x11A) = 0U;
            return 1;
        }
    }
    return 0;
}
