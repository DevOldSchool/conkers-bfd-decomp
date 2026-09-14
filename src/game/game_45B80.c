#include "types.h"

/*
 * Reviewed source unit: src/game/game_45B80.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501878C
 * - func_15018E88
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15018E88 CURRENT (100) */
void func_15018E88(s32 arg0, s16 arg1) {
    if (D_800BE616 == 0) {
        func_1517D7B0(&arg0, 1);
    }
    arg0 = func_151674F8(arg0, 0, arg1, 0);
    arg0 = func_151674F8(arg0, 0, arg1, 1);
    func_15174AA4(arg0, D_800BE9F0, arg1);
    return;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15018E88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15018E88.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019F20.s")
