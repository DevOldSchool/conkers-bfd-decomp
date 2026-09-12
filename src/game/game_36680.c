#include "types.h"

/*
 * Reviewed source unit: src/game/game_36680.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150091D0
 * - func_150092DC
 * - func_15009334
 * - func_15009628
 * - func_150096C4
 * - func_15009990
 * - func_15009A38
 * - func_15009BD0
 * - func_15009C7C
 * - func_15009F74
 * - func_1500A2AC
 * - func_1500A2F4
 * - func_1500A6D8
 * - func_1500A7E8
 * - func_1500A990
 * - func_1500ABA0
 * - func_1500AC14
 * - func_1500AD84
 * - func_1500AF08
 * - func_1500B1F4
 * - func_1500B3B0
 * - func_1500B714
 * - func_1500B8F4
 * - func_1500BAB8
 * - func_1500BC7C
 * - func_1500BE68
 * - func_1500BEC0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150091D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150092DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009334.s")
void func_1516127C(s32 arg0, s32 arg1, s32 arg2);

void func_150095D8(s32 arg0, u8 arg1) {
    func_1516127C(arg0, 0xFF, 1);
}
void func_15161334(s32 arg0, s32 arg1, s32 arg2);

void func_15009600(s32 arg0, u8 arg1) {
    func_15161334(arg0, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009628.s")
void func_15161408(s32 arg0, s32 arg1, s32 arg2);

void func_1500969C(s32 arg0, u8 arg1) {
    func_15161408(arg0, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150096C4.s")
void func_15161494(s32 arg0, s32 arg1, s32 arg2);

void func_15009740(s32 arg0, u8 arg1) {
    func_15161494(arg0, 0xFF, 1);
}
s32 func_151615F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_15009768(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 0, 0, 0xE, 0xFF, 1);
}
void func_15161540(s32 arg0, s32 arg1, s32 arg2);

void func_150097A4(s32 arg0, u8 arg1) {
    func_15161540(arg0, 0xFF, 1);
}
void func_150121C0(s32 arg0);

void func_150097CC(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_151615F8(arg0, 0, 2, 0xE, 0xFF, 1);
    if (temp_v0 != 0) {
        func_150121C0(temp_v0);
    }
}
void func_151B8DB0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15009818(void *arg0, u8 arg1) {
    func_151B8DB0(arg0, 0, 0xFF, 1);
}
void func_15009844(void *arg0, u8 arg1) {
    func_151B8DB0(arg0, 1, 0xFF, 1);
}
void func_15108850(s32 arg0);

void func_15009870(s32 arg0, s32 arg1) {
    func_15108850(arg0);
}
void func_15009894(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 1, 0, 0xE, 0xFF, 1);
}
void func_15162034(s32 arg0, s32 arg1, s32 arg2);

void func_150098D0(s32 arg0, u8 arg1) {
    func_15162034(arg0, 0xFF, 1);
}
void func_151623F4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_150098F8(s32 arg0, u8 arg1) {
    func_151623F4(arg0, 1, 0x16, 0, -1, 0x12C, 0xFF, 1);
}
void func_15162740(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_15009944(s32 arg0, u8 arg1) {
    func_15162740(arg0, 1, 6, 0, 0x12C, 2, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009990.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009A38.s")
void func_15162FAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_15009AA0(s32 arg0, u8 arg1) {
    func_15162FAC(arg0, 1, 0, 2, 0x12C, 0xD, 0xFF, 1);
}
void func_15009AEC(s32 arg0, u8 arg1) {
    func_15162740(arg0, 2, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_15009B38(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x14, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_15009B84(s32 arg0, u8 arg1) {
    func_15162740(arg0, 3, 6, 0, 0x12C, 2, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009BD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009C7C.s")
extern void func_15163604(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_15009D28(s32 arg0, u8 arg1) {
    func_15163604(arg0, 1, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_15009D6C(s32 arg0, u8 arg1) {
    func_15163604(arg0, 2, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_15009DB0(s32 arg0, u8 arg1) {
    func_15162740(arg0, 4, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_15009DFC(s32 arg0, u8 arg1) {
    func_15162740(arg0, 5, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_15009E48(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 1, 1, 0xE, 0xFF, 1);
}
void func_15009E84(s32 arg0, u8 arg1) {
    func_15163604(arg0, 3, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1516381C(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15009EC8(void *arg0, u8 arg1) {
    func_1516381C(arg0, 0x20, 0xFF, 1);
}
void func_15009EF4(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 1, 3, 0x23, 0xFF, 1);
}
void func_15009F30(s32 arg0, u8 arg1) {
    func_15163604(arg0, 4, 0x24, 0x12C, 0, 0, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009F74.s")
void func_1500A028(s32 arg0, u8 arg1) {
    func_15163604(arg0, 5, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A06C(s32 arg0, u8 arg1) {
    func_15163604(arg0, 6, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A0B0(s32 arg0, u8 arg1) {
    func_15162740(arg0, 7, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A0FC(s32 arg0, u8 arg1) {
    func_15162740(arg0, 9, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A148(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0xA, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A194(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0xB, 0x26, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A1E0(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 1, 4, 0xE, 0xFF, 1);
}
void func_1500A21C(s32 arg0, u8 arg1) {
    func_15163604(arg0, 7, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A260(s32 arg0, u8 arg1) {
    func_15162FAC(arg0, 2, 0, 2, 0x12C, 0xD, 0xFF, 1);
}
extern s32 D_80095B70;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500A2AC CURRENT (890) */
void func_1500A2AC(void *arg0, s32 arg1) {
    s32 sp1C;

    sp1C = D_80095B70;
    func_151B8DB0(arg0, *((u8 *)&sp1C + arg1 - 0x33), 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500A2AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A2AC.s")
extern void func_15164208(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u16 D_80095B74;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500A2F4 CURRENT (1035) */
void func_1500A2F4(s32 arg0, s32 arg1) {
    u16 sp1C;

    sp1C = D_80095B74;
    func_15164208(arg0, *((u8 *)&sp1C + arg1 - 0x38), 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500A2F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A2F4.s")
void func_1500A33C(s32 arg0, u8 arg1) {
    func_15163604(arg0, 8, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A380(s32 arg0, u8 arg1) {
    func_15163604(arg0, 9, 0x28, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A3C4(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0xF, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A410(s32 arg0, u8 arg1) {
    func_15163604(arg0, 0xA, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A454(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 0, 5, 0xE, 0xFF, 1);
}
void func_1500A490(s32 arg0, u8 arg1) {
    func_15163604(arg0, 0xB, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A4D4(s32 arg0, u8 arg1) {
    func_15163604(arg0, 0xC, 0x29, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A518(s32 arg0, u8 arg1) {
    func_15163604(arg0, 0xD, 0x29, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A55C(s32 arg0, u8 arg1) {
    func_151623F4(arg0, 1, 0x16, 0, -1, 0x12C, 0xFF, 1);
}
void func_1500A5A8(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x11, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A5F4(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x12, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A640(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x13, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A68C(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x15, 6, 0, 0x12C, 2, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A6D8.s")
void func_1500A79C(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x16, 6, 0, 0x12C, 2, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A7E8.s")
void func_1500A8C8(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 0, 6, 0xE, 0xFF, 1);
}
void func_1500A904(s32 arg0, s32 arg1) {
    func_151615F8(arg0, 1, (arg1 - 0x50) & 0xFF, 0xE, 0xFF, 1);
}
typedef void (*Func1500A94CCallback)(s32 arg0, s32 arg1);
extern Func1500A94CCallback D_80082BFC[];

void func_1500A94C(s32 arg0, s32 arg1) {
    Func1500A94CCallback temp_v0;

    if ((arg1 > 0) && (arg1 < 0x59)) {
        temp_v0 = D_80082BFC[arg1];
        if (temp_v0 != 0) {
            temp_v0(arg0, arg1);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500A990.s")
typedef void (*Func1500AB5CCallback)(s32 arg0);
extern Func1500AB5CCallback D_80082D60[];

void func_1500AB5C(s32 arg0) {
    Func1500AB5CCallback temp_v0;

    if ((arg0 > 0) && (arg0 < 6)) {
        temp_v0 = D_80082D60[arg0];
        if (temp_v0 != 0) {
            temp_v0(arg0);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500ABA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500AC14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500AD84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500AF08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B1F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B3B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B714.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B8F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BAB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BC7C.s")
extern s32 D_800DDD0C;
extern s32 D_800DDD10[];

void func_1500BE40(s32 arg0) {
    D_800DDD10[0] = 0;
    D_800DDD10[1] = 0;
    D_800DDD0C = 0x6E;
}
/* Call context: func_1500BE40: unique active project prototype */
extern s8 D_8008CEB0;
extern s32 D_800DDC00;
extern s32 D_800DDC04;
extern s32 D_800DDC08;
extern s8 D_800DDD1C;
extern s32 D_800DDD20;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500BE68 CURRENT (895) */
void func_1500BE68(void) {
    D_800DDD1C = 0;
    D_8008CEB0 = 0;
    D_800DDC00 = 0;
    D_800DDC08 = 0;
    D_800DDC04 = 0;
    D_800DDD20 = 0;
    func_1500BE40(0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500BE68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BE68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BEC0.s")
