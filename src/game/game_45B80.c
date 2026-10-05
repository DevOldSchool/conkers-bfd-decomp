#include "types.h"

/*
 * Reviewed source unit: src/game/game_45B80.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501878C
 * - func_15018F80
 * - func_15019130
 * - func_15019464
 * - func_150195A0
 * - func_150198FC
 * - func_15019BB8
 * - func_15019CC8
 * - func_15019E60
 * - func_15019F20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10001444(void);
s32 func_1501A39C(void);
void func_151E6BFC(void);
s32 func_1501878C(void);
s32 func_151DCFD8(s32);
extern s8 D_800BE5E0;
extern s16 D_800D18A0;
extern s16 D_800D18A2;
extern s32 D_800D18A4;
extern s8 D_800D23A9;
extern s8 D_8002AC60;
extern s16 D_8002AC64;
extern s32 D_800BE728;

void func_150186D0(void) {
    func_10001444();
    func_1501A39C();
    func_151E6BFC();
    D_800BE5E0 = 1;
    D_800D18A0 = 0;
    D_800D18A2 = 0;
    D_800D18A4 = 0;
    D_800D23A9 = 0;
    if (func_1501878C() != 0) {
        do {
        } while (func_1501878C() != 0);
    }
    D_8002AC60 = 1;
    D_8002AC64 = 0xDAC;
    D_800BE728 = func_1501BBB8();
    if (func_151DCFD8(1) != 0) {
        do {
        } while (func_151DCFD8(1) != 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_1501878C.s")
s32 func_150A09D0(s32);
void func_150619A8(void);
void func_1501C870(void);
void func_1502378C(void);
void func_1504A730(void);
void func_15085ABC(s16);
void func_1507C370(void);
void func_1507C8FC(void);
extern u8 D_800BEAC0;
extern s32 D_800BE9E4;
extern u8 D_800C35EA;
extern s16 D_800D2340;

void func_15018DFC(void) {
    func_150A09D0(D_800BE9E4);
    func_150619A8();
    func_1501C870();
    if (D_800BEAC0 == 0) {
        if (D_800C35EA == 1) {
            func_1502378C();
        } else {
            func_1504A730();
        }
        func_15085ABC(D_800D2340);
    }
    func_1507C370();
    func_1507C8FC();
}
s32 func_151674F8(s32, s32, s16, s32);
s32 func_15174B48(s32, s32, s16);
void func_15174AA4(s32, s32, s16);
void func_1517D7B0(s32 *, s32);
extern u8 D_800BE616;
extern s32 D_800BE9F0;

void func_15018E88(s32 arg0, s16 arg1) {
    if (D_800BE616 == 0) {
        func_1517D7B0(&arg0, 1);
    }
    arg0 = func_151674F8(arg0, 0, arg1, 0);
    arg0 = func_151674F8(arg0, 0, arg1, 1);
    func_15174AA4(arg0, D_800BE9F0, arg1);
    return;
}

s32 func_15018F08(s32 arg0, s16 arg1) {
    s32 value;

    value = func_15174B48(arg0, D_800BE9F0, arg1);
    arg0 = value;
    value = func_151674F8(value, 1, arg1, 0);
    arg0 = value;
    arg0 = func_151674F8(value, 1, arg1, 1);
    func_1517D7B0(&arg0, 2);
    return arg0;
}
s32 func_1517F40C(s32);
void func_1517F448(s32);
void func_1501B640(void);
void func_15172D80(s16);
extern s32 D_8003C8E0;
extern s16 D_800D3674;
extern u8 *D_800DBFF0;
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15018F80 CURRENT (1634) */
void func_15018F80(s32 arg0) {
    void *sp24;
    s32 var_s0;

    var_s0 = (s16)arg0;
    sp24 = D_800DBFF0 + (var_s0 * 0x9A0);
    D_8003C8E0 = 0x0A000000;
    if ((func_1517F40C(var_s0) == 0) && (D_800BEAC0 == 0)) {
        func_1517F448(var_s0);
    }
    func_1501B640();
    if (*(f32 *)((u8 *)sp24 + 0x388) < 0.0f) {
        D_800D3674 = -0x3E8;
    } else {
        D_800D3674 = 0x1388;
    }
    func_15172D80((s16)var_s0);
    D_8003C8E0 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15018F80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15018F80.s")
void func_15019F20(void);
void func_1501C1B0(void);
void func_1501BB20(void);
void func_1502C380(void);
void func_10011BB8(void);
void func_10012020(void);
void func_150ADACC(s32);
void func_1000D758(f32, f32, s32);
s32 func_1501BBB8(void);
void func_15169040(s32, u8);
extern u8 D_800BEAC1;
extern u8 D_800BE9C0;
extern void *D_800BE9D8[];
extern s32 D_800BE9D0;
extern s32 D_800BE728;
extern u8 D_800E0B94;

void func_1501905C(void) {
    D_800BE9D0 = (s32)D_800BE9D8[D_800BE9C0];
    D_800BE728 = func_1501BBB8();
    func_15019F20();
    if ((D_800BEAC1 != 0) && (D_800BEAC0 == 0)) {
        func_15169040(0, 0x47);
    }
    func_1501C1B0();
    func_1501BB20();
    func_1502C380();
    func_1000D758(*(f32 *)(D_800DBFF0 + 0x2A4),
                  *(f32 *)(D_800DBFF0 + 0x2A8),
                  *(s32 *)(D_800DBFF0 + 0x2AC));
    func_10011BB8();
    if (D_800E0B94 == 2) {
        func_150ADACC(0x81280783);
    }
    func_10012020();
}
void func_1510D864(void);
void func_10004250(void);
void func_15034F20(void);
void func_1510B690(void);
void func_15113180(void);
void func_15114188(void);
void func_15044A28(void);
void func_15087CC0(void);
void func_15122AE0(void);
void func_1504ADD0(void);
void func_1501C860(void);
void func_1516706C(void);
void func_151671E8(void);
void func_1502BEE4(void);
void func_150A0D8C(void);
void func_15113218(void);
void func_1502C1A4(void);
void func_15113C88(void);
void func_150636F0(void);
void func_15183D28(void);
void func_151670C0(void);
void func_15177A94(void);
void func_151814FC(void);
void func_1517F75C(void);
void func_1517F7B4(void);
void func_15036148(void);
void func_1515D6C8(void);
void func_1509BA04(s32);
void func_1509BBA0(s32);
void func_1501E400(s32);
void func_1510F800(s32);
void func_15113E54(s32);
void func_1501EC38(s32);
void func_15020EC4(s32);
void func_1501E2F8(s32);
void func_1510FC34(s32);
void func_15094EA0(s32);
void func_15112A80(s32);
void func_1511FC20(s32);
void func_15188B74(s32);
void func_151738C4(s32);
void func_150242F8(s32, s32);
void func_151749F8(s32, s32);
extern s8 D_800DCD27;
extern u8 D_800CC2B0;
extern s32 D_80082FA0;
typedef struct { s32 value, counter; } Game45B80Counter;
extern Game45B80Counter D_80043B40[];
extern u8 D_80044B20[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15019130 CURRENT (1415) */
s32 func_15019130(void) {
    s32 index;
    u8 byteIndex;
    Game45B80Counter *counter;
    s32 first, second, third, fourth;

    func_1510D864();
    func_1509BA04(0);
    func_1509BBA0(2);
    D_800DCD27 = 0;
    func_10004250();
    func_1501E400(0);
    func_15034F20();
    func_1510B690();
    func_1510F800(0);
    func_15113180();
    if (D_800BEAC0 == 0) {
        func_15113E54(1);
    }
    if (D_800BEAC0 == 0) {
        func_15114188();
    }
    func_15044A28();
    func_15018DFC();
    func_150242F8(1, 0);
    func_1501EC38(0);
    func_150242F8(0, 0);
    func_15020EC4(0);
    func_1501E2F8(0);
    if (D_800D23A9 != 0) {
        func_15087CC0();
    }
    func_15122AE0();
    func_1504ADD0();
    func_1510F800(0);
    index = 0;
    if (D_80082FA0 >= 0) {
        do {
            func_1510FC34(index);
            index++;
        } while (D_80082FA0 >= index);
    }
    func_1510B690();
    byteIndex = 0;
    if (D_80082FA0 >= 0) {
        do {
            func_15094EA0(byteIndex);
            byteIndex++;
        } while (D_80082FA0 >= byteIndex);
    }
    func_15112A80(0);
    func_151749F8(D_800BE9F0, 0);
    func_1501C860();
    func_1511FC20(D_800BE9C0);
    func_15188B74(0);
    if (D_800BEAC0 == 0) {
        func_1516706C();
        func_151671E8();
    }
    func_1502BEE4();
    if (D_800BE616 == 0) {
        func_150A0D8C();
    }
    func_15113218();
    func_15188B74(1);
    func_151738C4(D_800BE9F0);
    func_1502C1A4();
    func_15113C88();
    if (D_800CC2B0 != 0) {
        func_150636F0();
    }
    if (D_800BEAC0 == 0) {
        func_15183D28();
        func_151670C0();
        func_15177A94();
    }
    if (D_800BEAC0 == 0) {
        func_151814FC();
    }
    func_1517F75C();
    func_1517F7B4();
    func_15036148();
    func_1515D6C8();
    counter = D_80043B40;
    do {
        second = counter[1].counter;
        third = counter[2].counter;
        fourth = counter[3].counter;
        first = counter[0].counter;
        counter += 4;
        counter[-1].counter = (s32)((u32)fourth + 1);
        counter[-2].counter = (s32)((u32)third + 1);
        counter[-3].counter = (s32)((u32)second + 1);
        counter[-4].counter = (s32)((u32)first + 1);
    } while ((u32)counter != (u32)D_80044B20);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15019130 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019130.s")
void func_15167010(void);
void func_1517ABB0(void);
void func_1508F0A4(void);
extern u8 D_800BEAC0;

void func_15019414(void) {
    if (D_800BEAC0 == 0) {
        func_15167010();
    }
    func_1517ABB0();
    if (D_800BE616 == 0) {
        func_1508F0A4();
    }
}
void func_1510B958(s16);
s32 func_1510B9D0(s32, s16);
s32 func_1510FEA0(s32, s32);
s32 func_1515D6D0(s32, s16);
s32 func_1517EFAC(void);
void *func_1501A490(void *, s16, s32, s32, s32, s32);
extern u8 *D_800BE628;
extern s16 D_80084480;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15019464 CURRENT (3234) */
s32 func_15019464(void *arg0, s16 arg1) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;

    func_1510B958(arg1);
    *(s32 *)arg0 = 0xDC080008;
    *(s32 *)((u8 *)arg0 + 4) = (s32)(D_800BE628 + (arg1 * 0x180) + (D_800BE9C0 * 0x10) + 0x40);
    temp_v0 = func_1501A490((u8 *)arg0 + 8, arg1, 0, 0, 0, 0);
    temp_s0_2 = temp_v0;
    if (D_800BEAC0 != 0) {
        return temp_v0;
    }
    if (D_80084480 != 0) {
        return temp_s0_2;
    }
    temp_s0 = func_1510FEA0(temp_s0_2, D_800BE9F0);
    if ((func_1517EFAC() != 0) || (D_800D18A0 & (1 << arg1))) {
        return temp_s0;
    }
    return func_1510B9D0(func_1515D6D0(temp_s0, arg1), arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15019464 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019464.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_150195A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_150198FC.s")
s32 func_1517F4D8(s32, s32);
s32 func_1517F3A0(s32, s32);
s32 func_15180580(s32, s32);
s32 func_1507DB6C(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15019BB8 CURRENT (1060) */
void func_15019BB8(void *arg0, s32 arg1) {
    s16 temp_a2;
    s32 temp_v1;
    s32 var_a0;

    temp_a2 = (s16)arg1;
    *(s32 *)arg0 = 0xDC080008;
    *(s32 *)((u8 *)arg0 + 4) = (s32)(D_800BE628 + (arg1 * 0x180) + (D_800BE9C0 * 0x10) + 0x40);
    temp_v1 = 1 << arg1;
    var_a0 = func_15180580(func_1517F3A0(func_1517F4D8(func_1501A490((u8 *)arg0 + 8, temp_a2, 0, 0, 0, 0), arg1), arg1), arg1);
    if ((D_800D18A0 & temp_v1) || (D_800D18A2 & temp_v1)) {
        var_a0 = func_1507DB6C(var_a0, arg1);
    }
    func_151674F8(func_151674F8(var_a0, 4, temp_a2, 0), 4, temp_a2, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15019BB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019BB8.s")
s32 func_1502BAD0(void *, s32, s16);
extern u8 D_80089470;
extern u8 *D_800DC2A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15019CC8 CURRENT (3120) */
void func_15019CC8(void *arg0, s32 arg1) {
    s16 temp_a2;
    void *temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    void *var_a0;

    var_s0 = arg1;
    temp_a2 = (s16)var_s0;
    *(s32 *)arg0 = 0xDC080008;
    *(s32 *)((u8 *)arg0 + 4) = (s32)(D_800BE628 + (var_s0 * 0x180) + (D_800BE9C0 * 0x10) + 0x40);
    temp_v0 = func_1501A490((u8 *)arg0 + 8, temp_a2, 0, 0, 0, 0);
    *(s32 *)temp_v0 = 0xDA380003;
    *(s32 *)((u8 *)temp_v0 + 4) = (s32)&D_80089470;
    *(s32 *)((u8 *)temp_v0 + 8) = 0xDA380007;
    *(s32 *)((u8 *)temp_v0 + 0xC) = (s32)(D_800BE628 + (var_s0 * 0x180) + (D_800BE9C0 << 6) + 0x100);
    var_a0 = (u8 *)temp_v0 + 0x10;
    if (D_800BE9F0 == 0x1D) {
        var_a0 = (void *)func_1502BAD0(var_a0, 6, temp_a2);
    }
    temp_v0_2 = func_151674F8(func_151674F8((s32)var_a0, 5, 0, 0), 5, 0, 1);
    *(s32 *)temp_v0_2 = 0xDA380007;
    *(s32 *)((u8 *)temp_v0_2 + 4) = (s32)(D_800BE628 + (var_s0 * 0x180) + (D_800BE9C0 << 6) + 0x100);
    *(s32 *)((u8 *)temp_v0_2 + 8) = 0xDA380005;
    *(s32 *)((u8 *)temp_v0_2 + 0xC) = (s32)(D_800DC2A0[D_800BE9C0] + (var_s0 << 6));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15019CC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019CC8.s")
s32 func_151E8620(s32);
void func_15043384(s32);
extern s32 D_80082FA0;
extern s32 D_80082FA4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15019E60 CURRENT (1482) */
void func_15019E60(void *arg0) {
    void *temp_v0;

    temp_v0 = arg0;
    if (D_80082FA0 != 0) {
        D_80082FA4 = D_80082FA0 + 1;
        *(s32 *)temp_v0 = 0xDC080008;
        *(s32 *)((u8 *)temp_v0 + 4) = (s32)(D_800BE628 + (D_80082FA4 * 0x180) + 0x40);
    } else {
        *(s32 *)temp_v0 = 0xDC080008;
        *(s32 *)((u8 *)temp_v0 + 4) = (s32)(D_800BE628 + 0x40);
    }
    func_15043384(func_151E8620(func_1501A490((u8 *)arg0 + 8, 0xFF, 0, 0, 0, 0)));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15019E60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019E60.s")
void func_150A019C(void);
extern f32 D_800BE5E8[10];
extern u32 D_800BE610;
extern u8 D_800BE619;
extern u8 D_800BE61A;
extern u8 D_800BE9A0;
extern f32 D_800BE9A4;
extern f32 D_800BE9A8;
extern s32 D_800BE9AC;
extern s32 D_800BE9B0;
extern f32 D_800BE9B8;
extern f32 D_800BE9BC;
extern s32 D_800BEA08;
extern u8 D_800BEA0C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15019F20 CURRENT (4090) */
void func_15019F20(void) {
    s32 ticks;
    u32 accumulated;
    u32 divisor;
    u32 quotient;
    f32 total;
    s32 i;

    ticks = D_800BE9E4;
    D_800BEA08 = ticks;
    divisor = D_800BEA0C;
    if (divisor != 0) {
        if (divisor == 1) {
            D_800BE9E4 = 0;
            D_800BE5E0 = 0;
            ticks = 0;
            D_800BE9A4 = 0.0f;
        } else {
            accumulated = D_800BE610 + (u32)ticks;
            D_800BE9A4 = (f32)ticks / (f32)divisor;
            D_800BE9E4 = (s32)D_800BE9A4;
            D_800BE9A4 *= 0.5f;
            if (accumulated >= divisor) {
                quotient = accumulated / divisor;
                D_800BE9E4 = (s32)quotient;
                ticks = (s32)quotient;
                D_800BE610 = accumulated - quotient * accumulated;
            } else {
                D_800BE610 = accumulated;
                D_800BE9E4 = 0;
                ticks = 0;
            }
        }
    } else {
        D_800BE9A4 = (f32)ticks * 0.5f;
    }
    D_800BE5E0 = (u8)D_800BE5E0 & 1;
    D_800BE5E0 = (u8)((u32)(u8)D_800BE5E0 + (u32)ticks);
    D_800BE9A0 = (u8)D_800BE5E0 >> 1;
    if (D_800BE9A4 != 0.0f) {
        D_800BE9A8 = 1.0f / D_800BE9A4;
    } else {
        D_800BE9A4 = 0.0f;
        D_800BE9A8 = 0.0f;
    }
    D_800BE9AC = (s32)((u32)D_800BE9AC + (u32)ticks);
    D_800BE9B0 = D_800BE9AC % 30;
    D_800BE5E8[D_800BE619] = D_800BE9A4;
    D_800BE619++;
    if (D_800BE619 == 10) {
        D_800BE619 = 0;
    }
    if (D_800BE61A < 10) {
        D_800BE61A++;
        D_800BE9B8 = D_800BE9A4;
        D_800BE9BC = D_800BE9A8;
    } else {
        total = 0.0f;
        for (i = 0; i < 10; i++) {
            total += D_800BE5E8[i];
        }
        D_800BE9B8 = total * 0.1f;
        if (D_800BE9B8 != 0.0f) {
            D_800BE9BC = 1.0f / D_800BE9B8;
        } else {
            D_800BE9BC = 0.0f;
        }
    }
    func_150A019C();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15019F20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019F20.s")
