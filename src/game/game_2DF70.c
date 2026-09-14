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
 * - func_15001B10
 * - func_15001B8C
 * - func_15001BC8
 * - func_15001CEC
 * - func_15001DE0
 * - func_15002008
 * - func_15002248
 * - func_15002560
 * - func_150025FC
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
extern s32 D_800DBE1C;
extern s32 D_800DBE20;
extern s32 D_800DBE24;
extern volatile s32 D_800B0DC0[];
extern s32 D_800B0DC4;
extern s32 D_800B0DC8;
extern s32 D_80091C04[];
s32 func_10003C40(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001970 CURRENT (38) */
void func_15001970(void) {
    s32 sp18;
    s32 temp_v0;

    D_800B0DE4 = 0;
    D_800DBE63 = 0;
    D_800DBE18[0] = 0;
    D_800DBE1C = 0;
    D_800DBE20 = 0;
    sp18 = D_80091C04[D_800BE9F0];
    D_800DBE24 = 0;
    temp_v0 = func_10003C40(sp18, 1, 0, 0);
    D_800B0DC0[0] = temp_v0;
    D_800B0DC8 = sp18 + temp_v0;
    D_800B0DC4 = temp_v0;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001B10 CURRENT (140) */
void func_15001B10(void) {
    s32 temp_v0;

    temp_v0 = (s32) (D_800B0DE0 + 3) & ~3;
    D_800B0DE0 = (s8 *) temp_v0;
    D_800B0DCC += 1;
    *(s16 *)((u8 *)temp_v0 + 0xC) = 0;
    *(s16 *)((u8 *)temp_v0 + 4) = 0;
    D_800B0DE0 += 0xE;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15001B10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001B10.s")
void func_15001B5C(u8 arg0) {
    *D_800B0DE0 = arg0;
    D_800B0DE0 += 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001B8C CURRENT (30) */
void func_15001B8C(u16 arg0) {
    D_800B0DE0[0] = arg0 >> 8;
    D_800B0DE0[1] = arg0;
    D_800B0DE0 += 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15001B8C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001B8C.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001DE0.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150025FC CURRENT (111) */
void func_150025FC(void) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 temp_a3;

    sp20 = (s32)D_800DBE2C;
    D_800DBE28 = (s16)((((s32)(D_800DBE2A + 7) / 8) + 0xF) & 0xFFF0);
    sp1C = func_1502B5C8(0, 2, 5, D_800BE9F0 * 2);
    temp_a3 = func_1502B5C8(0, 2, 5, (D_800BE9F0 * 2) + 1);
    if (sp1C == 0) {
        D_800BE5D0 = 0;
        return;
    }
    sp18 = temp_a3;
    func_150183D0(D_800DBE28, sp20, sp1C, temp_a3);
    func_10004074(sp18);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150025FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_150025FC.s")
extern s32 D_800DBE38;
extern s32 D_800B0DE4;
extern s32 D_800DBE18[];
extern s32 D_800DBE1C;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15002878 */
s32 func_15002878(void) {
    u8 *current;
    s32 value;
    s32 maximum;

    maximum = D_800DBE18[0];
    current = (u8 *)&D_800DBE1C;
    do {
        value = *(s32 *)current;
        current += 4;
        if (maximum < value) {
            maximum = value;
        }
    } while (current != (u8 *)&D_800DBE28);
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
        *((u8 *)D_800B0DF0 + 0x12) = (u8)(*((u8 *)D_800B0DF0 + 0x12) >> 1);
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
