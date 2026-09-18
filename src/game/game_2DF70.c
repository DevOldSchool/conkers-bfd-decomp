#include "types.h"

/*
 * Reviewed source unit: src/game/game_2DF70.c
 * Boundary evidence: docs/evidence/game_2DF70.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15000AD0
 * - func_15001460
 * - func_15001970
 * - func_15001A08
 * - func_15001BC8
 * - func_15001CEC
 * - func_15001DE0
 * - func_15002008
 * - func_15002248
 * - func_15002560
 * - func_15002754
 * - func_150027F8
 * - func_15002878
 * - func_150028BC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern signed char D_800D9E64;
extern s8 *D_800B0DE0;
s32 func_150027F8();

void func_15000AC0(void) {
    D_800D9E64 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15000AD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001460.s")
extern s32 D_800B0DE4;
extern s8 D_800DBE63;
extern s32 D_800BE9F0;
extern s32 D_800DBE18[];
extern s32 D_800DBE1C[3];
extern s32 D_800DBE20;
extern s32 D_800DBE24;
extern s32 D_800B0DC0[];
extern s32 D_800B0DC4;
extern s32 D_800B0DC8;
extern s32 D_80091C04[];
s32 func_10003C40(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001970 CURRENT (10) */
void func_15001970(void) {
    s32 temp_v0;
    s32 sp18;

    D_800B0DE4 = 0;
    D_800DBE63 = 0;
    D_800DBE18[0] = 0;
    D_800DBE1C[0] = 0;
    D_800DBE20 = 0;
    sp18 = D_80091C04[D_800BE9F0];
    D_800DBE24 = 0;
    temp_v0 = func_10003C40(sp18, 1, 0, 0);
    D_800B0DC0[0] = temp_v0;
    D_800B0DC8 = sp18 + D_800B0DC0[0];
    D_800B0DC4 = D_800B0DC0[0];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15001970 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001970.s")
extern s32 D_80000308;
extern s32 D_800B0DCC;
extern s32 D_800B0DD0;
extern s32 D_800B0DDC;
extern s16 D_800DBE30;
extern s16 D_800DBE32;
extern s16 D_800DBE34;
extern s16 D_800DBE36;
extern s32 D_80091AF0[];
extern u8 D_A0000000;
void func_10023720(s32);
void func_10023764(s32);
s32 func_10003C40(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001A08 CURRENT (1064) */
void func_15001A08(void) {
    s32 sp24;
    s32 sp1C;
    s32 temp_a0;
    s32 temp_v0;
    s32 var_a0;

    temp_a0 = D_80091AF0[D_800BE9F0];
    sp24 = temp_a0;
    func_10023720(temp_a0);
    if ((*(volatile s32 *)0xA4600010 & 3) != 0) {
        do {
        } while ((*(volatile s32 *)0xA4600010 & 3) != 0);
    }
    sp24 = temp_a0;
    sp1C = *(s32 *)(D_80000308 | 0xB0000D24 | 0xA0000000);
    func_10023764(temp_a0);
    var_a0 = temp_a0;
    if (sp1C != 0x98CCE31A) {
        var_a0 *= 2;
    }
    temp_v0 = func_10003C40(var_a0, 1, 0, 0);
    D_800B0DDC = temp_v0;
    D_800B0DE0 = (s8 *)temp_v0;
    D_800B0DCC = 0;
    D_800B0DD0 = 0;
    D_800DBE30 = 0;
    D_800DBE32 = 0;
    D_800DBE34 = 0;
    D_800DBE36 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15001A08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001A08.s")
extern s32 D_800B0DCC;

s16 *func_15001B10(void) {
    s16 *temp_v0;

    D_800B0DE0 = (s8 *)(((s32)D_800B0DE0 + 3) & ~3);
    temp_v0 = (s16 *)D_800B0DE0;
    D_800B0DCC += 1;
    *(s16 *)((u8 *)temp_v0 + 0xC) = 0;
    *(s16 *)((u8 *)temp_v0 + 4) = 0;
    D_800B0DE0 += 0xE;
    return temp_v0;
}
void func_15001B5C(u8 arg0) {
    *D_800B0DE0 = arg0;
    D_800B0DE0 += 1;
}
void func_15001B8C(u16 arg0) {
    s32 value;
    u16 low;

    value = arg0 & 0xFFFF;
    *D_800B0DE0 = value >> 8;
    low = value;
    *(D_800B0DE0 + 1) = low;
    D_800B0DE0 += 2;
}
void func_1510F800();
void *func_15001DE0(s32, s32, s32, s32, s32, s16 *);
void func_15002560(void *, void *);
void func_10004074(s32);
extern s32 D_800DBE4C;
extern void *D_800DBE08[];
extern s32 D_800B0DD4;
extern s16 D_800B0DD8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001BC8 CURRENT (300) */
void func_15001BC8(s32 arg0, s16 *arg1, s16 *arg2) {
    s16 *sp20;
    s16 *temp_v0;
    s16 *var_a0;
    s32 var_v1;
    void *temp_v0_2;

    func_1510F800(arg0);
    D_800B0DD8 = 0xA;
    D_800B0DD4 = 0x200;
    temp_v0 = (s16 *)func_10003C40((D_800DBE4C + 1) * 2, 1, 0, 0);
    var_v1 = 0;
    temp_v0[0] = (s16)D_800DBE4C;
    if (D_800DBE4C > 0) {
        var_a0 = temp_v0;
        do {
            var_a0[1] = (s16)var_v1;
            var_v1 += 1;
            var_a0 += 1;
        } while (var_v1 < D_800DBE4C);
    }
    sp20 = temp_v0;
    temp_v0_2 = func_15001DE0(0, 0, 0x8000, 0x8000, 0, temp_v0);
    D_800DBE08[arg0] = temp_v0_2;
    func_15002560(temp_v0_2, (void *)0);
    func_10004074((s32)sp20);
    if (arg1 != (s16 *)0) {
        *arg1 = (s16)D_800B0DCC;
    }
    if (arg2 != (s16 *)0) {
        *arg2 = (s16)D_800B0DD0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15001BC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001BC8.s")
s16 *func_15001B10(void);
void func_15002008(s32, s32, s32, s32, s16 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001CEC CURRENT (735) */
void func_15001CEC(s32 arg0) {
    s16 *sp20;
    s16 *temp_v0;
    s16 *var_a0;
    s32 temp_a0;
    s32 temp_v0_2;
    s32 var_v1;

    func_1510F800(arg0);
    temp_v0 = func_15001B10();
    D_800DBE08[arg0] = temp_v0;
    temp_v0[0] = -0x8000;
    temp_v0[1] = 0x7FFF;
    temp_v0[2] = 0;
    temp_v0[3] = 0x8000;
    temp_v0[4] = 0;
    temp_v0[5] = 0;
    temp_v0[6] = 0;
    temp_a0 = D_800DBE4C + 1;
    temp_v0_2 = temp_a0 * 2;
    temp_v0 = (s16 *)func_10003C40(temp_v0_2, 1, 0, 0);
    var_v1 = 0;
    temp_v0[0] = (s16)D_800DBE4C;
    if (D_800DBE4C > 0) {
        var_a0 = temp_v0;
        do {
            var_a0[1] = (s16)var_v1;
            var_v1 += 1;
            var_a0 += 1;
        } while (var_v1 < D_800DBE4C);
    }
    sp20 = temp_v0;
    func_15002008(-0x8000, 0x8000, -0x8000, 0x8000, temp_v0);
    func_10004074((s32)sp20);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15001CEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001CEC.s")
s32 func_15002248(s32, s32, s32, s32, s32 *, s32 *, s16 *, s16 **); /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001DE0 CURRENT (4729) */
void *func_15001DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s16 *arg5) {
    s32 sp7C;
    s32 sp78;
    s16 *sp58;
    s16 *temp_v0;
    s16 *temp_v0_2;
    s16 *var_s4;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a2;
    s32 temp_a3;
    register s32 temp_s1;
    register s32 temp_s0;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;

    temp_a0 = arg0 - arg2;
    temp_a1 = arg0 + arg2;
    temp_a2 = arg1 - arg3;
    temp_a3 = arg1 + arg3;
    temp_s0 = (u16) D_800B0DD8;
    temp_s1 = D_800B0DD4;
    arg4 = func_15002248(temp_a0, temp_a1, temp_a2, temp_a3, &sp7C, &sp78, arg5, &sp58);
    if ((arg4 < temp_s0) || (arg2 < temp_s1)) {
        temp_v0 = func_15001B10();
        var_s4 = temp_v0;
        D_800B0DD0 += 1;
        ((s16 *)temp_v0)[0] = (s16) sp7C;
        ((s16 *)temp_v0)[3] = (s16) arg2;
        ((s16 *)temp_v0)[4] = (s16) arg0;
        ((s16 *)temp_v0)[5] = (s16) arg1;
        ((s16 *)temp_v0)[2] = 0;
        ((s16 *)temp_v0)[6] = 0;
        ((s16 *)temp_v0)[1] = (s16) sp78;
        func_15002008(temp_a0, temp_a1, temp_a2, temp_a3, sp58);
    } else {
        temp_v0_2 = func_15001B10();
        temp_s0 = arg2 >> 1;
        temp_a0_2 = arg0 - temp_s0;
        ((s16 *)temp_v0_2)[0] = (s16) sp7C;
        ((s16 *)temp_v0_2)[3] = (s16) arg2;
        ((s16 *)temp_v0_2)[4] = (s16) arg0;
        ((s16 *)temp_v0_2)[5] = (s16) arg1;
        ((s16 *)temp_v0_2)[2] = 0;
        ((s16 *)temp_v0_2)[1] = (s16) sp78;
        var_s4 = temp_v0_2;
        temp_s1 = arg3 >> 1;
        temp_a1_2 = arg1 - temp_s1;
        temp_v0_3 = func_15001DE0(temp_a0_2, temp_a1_2, temp_s0, temp_s1, 0, sp58);
        ((s16 *)var_s4)[6] = (s16) ((u8 *)temp_v0_3 - (u8 *)var_s4);
        temp_a1_3 = temp_s1 + arg1;
        temp_v0_4 = func_15001DE0(temp_a0_2, temp_a1_3, temp_s0, temp_s1, 0, sp58);
        ((s16 *)temp_v0_3)[2] = (s16) (temp_v0_4 - temp_v0_3);
        temp_a0_3 = temp_s0 + arg0;
        temp_v0_5 = func_15001DE0(temp_a0_3, temp_a1_2, temp_s0, temp_s1, 0, sp58);
        ((s16 *)temp_v0_4)[2] = (s16) (temp_v0_5 - temp_v0_4);
        ((s16 *)temp_v0_5)[2] = (s16) ((u8 *)func_15001DE0(temp_a0_3, temp_a1_3, temp_s0, temp_s1, 0, sp58) - temp_v0_5);
    }
    func_10004074((s32) sp58);
    return var_s4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15001DE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001DE0.s")

typedef struct Game76710CallArgs {
    s32 words[9];
} Game76710CallArgs;

s32 func_15049260(Game76710CallArgs);
void func_150492CC(f32, f32, f32);
extern s16 **D_800DBE3C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15002008 CURRENT (613) */
void func_15002008(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s16 *arg4) {
    f32 *position;
    s16 *current;
    s32 delta;
    u16 count;
    u16 index;
    Game76710CallArgs triangle;
    s32 previous;
    s16 **source;
    s16 *point;
    s16 *end;

    previous = -1;
    count = (u16)*arg4;
    func_150492CC((f32)(arg1 - arg0), 32000.0f, (f32)(arg3 - arg2));
    current = arg4 + 1;
    if (count > 0) {
        end = &arg4[count] + 1;
        arg4 = (s16 *)(&triangle + 1);
        do {
            index = (u16)*current;
            position = (f32 *)triangle.words;
            source = (s16 **)((u8 *)D_800DBE3C + index * 12);
            do {
                point = *source;
                if ((u32)point > 0x80000000U) {
                    position[0] = (f32)(point[0] - (arg0 + arg1) / 2);
                    position[1] = (f32)(*source)[1];
                    position[2] = (f32)((*source)[2] - (arg2 + arg3) / 2);
                } else {
                    position[0] = 0.0f;
                    position[1] = 0.0f;
                    position[2] = 0.0f;
                }
                position += 3;
                source++;
            } while (position != (f32 *)arg4);
            if (func_15049260(triangle) == 0) {
                delta = index - previous;
                if (previous == -1) {
                    func_15001B8C((u16)(index | 0x8000));
                } else if (delta < 0x80) {
                    func_15001B5C((u8)delta);
                } else {
                    func_15001B8C((u16)(index | 0x8000));
                }
                previous = index;
            }
            current++;
        } while (end != current);
    }
    func_15001B5C(0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15002008 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002008.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002248.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15002560 CURRENT (980) */
void func_15002560(void *arg0, u8 *arg1) {
    s16 temp_v0;
    s16 var_v0;
    u8 *temp_s0;
    u8 *var_a0;
    u8 *var_s1;

    var_a0 = arg0;
loop_1:
    if (var_a0 != 0) {
        if (*(s16 *)((u8 *)var_a0 + 4) == 0) {
            var_v0 = 0;
            if (arg1 != 0) {
                var_v0 = arg1 - var_a0;
            }
            *(s16 *)((u8 *)var_a0 + 4) = var_v0;
        }
        temp_v0 = *(s16 *)((u8 *)var_a0 + 0xC);
        var_s1 = (void *)(var_a0 + temp_v0);
        if (temp_v0 != 0) {
            if (*(s16 *)((u8 *)var_s1 + 4) != 0) {
                do {
                    temp_s0 = (void *)(var_s1 + *(s16 *)((u8 *)var_s1 + 4));
                    func_15002560(var_s1, temp_s0);
                    var_s1 = temp_s0;
                } while (*(s16 *)((u8 *)temp_s0 + 4) != 0);
            }
            var_a0 = var_s1;
            goto loop_1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15002560 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002560.s")
extern s32 D_800BE5D0;
extern s16 D_800DBE2A;
extern s16 D_800DBE2C;
extern s16 D_800DBE28;
s32 func_1502B5C8(s32, s32, s32, s32);
void func_150183D0(s16, s32, s32, s32);

void func_150025FC(void) {
    s32 temp_v0;
    s32 sp20;
    s32 sp1C;
    s32 temp_a3;

    sp20 = (s32)D_800DBE2C;
    temp_v0 = D_800DBE2A;
    D_800DBE28 = (s16)((((temp_v0 + 7) / 8) + 0xF) & 0xFFF0);
    sp1C = func_1502B5C8(0, 2, 5, D_800BE9F0 * 2);
    temp_a3 = func_1502B5C8(0, 2, 5, (D_800BE9F0 * 2) + 1);
    if (sp1C == 0) {
        D_800BE5D0 = 0;
        return;
    }
    func_150183D0(D_800DBE28, sp20, sp1C, temp_a3);
    func_10004074(temp_a3);
}
extern s32 D_800DBE38;
extern s32 D_800B0DE4;
extern s32 D_800DBE18[];
extern s32 D_800DBE1C[3];
extern s32 D_800DBE4C;

void func_150026C4(void) {
    D_800DBE38 = 0;
    func_1510F800();
}
void func_150026E8(s32 arg0) {
    D_800DBE18[arg0] = D_800DBE38;
    D_800DBE4C = D_800DBE38;
    D_800B0DE4 += D_800DBE38;
}
void func_15002724(void) {
    D_800DBE38 += func_150027F8();
}
extern s32 D_800DBDD8[];
extern s32 D_800DBDE8[];
extern s32 D_800DBDF8[];
extern s32 D_800DBE50;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15002754 CURRENT (250) */
void func_15002754(void) {
    s32 temp_a1;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t8;

    temp_t8 = (*D_800B0DC0 + 3) & ~3;
    *D_800B0DC0 = temp_t8;
    temp_a1 = D_800DBE50 * 4;
    D_800DBDD8[D_800DBE50] = temp_t8;
    temp_t0 = temp_t8 + (D_800DBE38 * 0xC);
    *D_800B0DC0 = temp_t0;
    D_800DBDE8[D_800DBE50] = temp_t0;
    temp_t2 = temp_t0 + (D_800DBE38 * 8);
    *D_800B0DC0 = temp_t2;
    D_800DBDF8[D_800DBE50] = temp_t2;
    *D_800B0DC0 = temp_t2 + (D_800DBE38 * 4);
    func_1510F800();
    D_800DBE38 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15002754 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002754.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150027F8 CURRENT (855) */
s32 func_150027F8(s8 *arg0) {
    s32 var_v0;
    s32 var_v1;
    s8 var_a1;

    if (arg0 == 0) {
        return 0;
    }
    var_a1 = *arg0;
    var_v0 = 0;
    var_v1 = 0;
    if (var_a1 != -0x21) {
        do {
            var_v0 += 1;
            if ((var_a1 >> 4) == 1) {
                var_v1 += 4;
            } else if (var_a1 == 6) {
                var_v1 += 2;
            } else if (var_a1 == 5) {
                var_v1 += 1;
            }
            var_a1 = *((var_v0 * 8) + arg0);
        } while (var_a1 != -0x21);
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150027F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_150027F8.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15002878 CURRENT (10) */
s32 func_15002878(void) {
    s32 value;
    s32 maximum;
    s32 i;

    maximum = D_800DBE18[0];
    for (i = 0; i < 3; i++) {
        value = D_800DBE1C[i];
        if (maximum < value) {
            maximum = value;
        }
    }
    return maximum;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15002878 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002878.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_150028BC.s")
extern u8 D_800BE616;
extern f32 D_800DBE64;

void func_15002F40(s32 arg0) {
    if ((arg0 == 0x32) || (arg0 == 0x33)) {
        D_800DBE64 = 150.0f;
        return;
    }
    if (D_800BE616 != 0) {
        D_800DBE64 = 85.0f;
        return;
    }
    D_800DBE64 = 50.0f;
}

s32 func_15002FA0(s32 arg0) {
    return arg0 ^ 0xF0F0F0F0;
}

extern s32 D_8003C8E0;
extern s8 D_8008FD90;
extern void *D_800B0DF0;
extern u8 D_800D2F3C;
extern s32 D_800D2F40;
s32 func_1502B6BC(s32 *, s32, s32 *, s32, s32, s32);
void func_150AD770(void);
void func_151EF040(s32, s32 *);

void func_15002FB4(s32 arg0) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    struct {
        s32 value;
        s32 pad;
    } sp2CState;
    u8 temp_v1;

    sp3C = func_1502B6BC(&sp34, 0, &sp38, 2, 0x15, arg0);
    if ((sp38 != 0) && ((*(s32 *)((u8 *)sp3C + 4) << 8) != 0)) {
        D_800B0DF0 = *(void **)sp3C;
        if (sp34 == 0) {
            D_8003C8E0 = 0x0C000037;
            func_150AD770();
        }
        if (D_800B0DF0 == 0) {
            D_8003C8E0 = 0x0C000037;
            func_150AD770();
        }
    }
    func_151EF040(func_15002FA0(0x40F0FAAC), &sp2CState.value);
    sp2CState.value = func_15002FA0(sp2CState.value);
    if (sp2CState.value != -0x184FF0F7) {
        *((u8 *)D_800B0DF0 + 0x12) = (u8)((u32)*((u8 *)D_800B0DF0 + 0x12) >> 1);
    }
    temp_v1 = *((u8 *)D_800B0DF0 + 0x12);
    if (temp_v1 != 0) {
        D_800D2F3C = temp_v1;
        D_800D2F40 = *(s32 *)((u8 *)sp3C + 8);
    } else {
        D_800D2F3C = 0;
        D_800D2F40 = 0;
    }
    if ((D_8008FD90 >= 2) && (*((u8 *)D_800B0DF0 + 8) == 4)) {
        *((u8 *)D_800B0DF0 + 8) = 2;
    }
}

void D_1500310C(void) {
}
