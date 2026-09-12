#include "types.h"

/*
 * Reviewed source unit: src/game/game_981E0.c
 * Boundary evidence: docs/evidence/game_dispatcher_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1506AD30
 * - func_1506AF74
 * - func_1506B078
 * - func_1506B100
 * - func_1506B2BC
 * - func_1506B370
 * - func_1506B3B8
 * - func_1506B520
 * - func_1506B634
 * - func_1506B740
 * - func_1506B9C0
 * - func_1506BA4C
 * - func_1506BAD8
 * - func_1506BBA8
 * - func_1506BC24
 * - func_1506BCC8
 * - func_1506BF5C
 * - func_1506C32C
 * - func_1506C460
 * - func_1506CE6C
 * - func_1506D2E8
 * - func_1506D4F4
 * - func_1506D584
 * - func_1506D6B4
 * - func_1506D74C
 * - func_1506D898
 * - func_1506D958
 * - func_1506DA94
 * - func_1506DBA0
 * - func_1506DC10
 * - func_1506DE04
 * - func_1506DE84
 * - func_1506E0EC
 * - func_1506E2CC
 * - func_1506E46C
 * - func_1506EA98
 * - func_1506EBC0
 * - func_1506EEF4
 * - func_1506EF5C
 * - func_1506F02C
 * - func_1506F11C
 * - func_1506F14C
 * - func_1506F1A8
 * - func_1506F54C
 * - func_1506F8F0
 * - func_1506F9C0
 * - func_1506FA90
 * - func_1506FB60
 * - func_1506FD30
 * - func_15070084
 * - func_150700B4
 * - func_150700E4
 * - func_15070114
 * - func_15070144
 * - func_150701C4
 * - func_150701F4
 * - func_15070224
 * - func_15070300
 * - func_150706F8
 * - func_150707C8
 * - func_15070830
 * - func_15070898
 * - func_15070C40
 * - func_15070D24
 * - func_15070F60
 * - func_150712AC
 * - func_15071360
 * - func_150714E8
 * - func_15071690
 * - func_150716EC
 * - func_15071764
 * - func_150717E0
 * - func_15071830
 * - func_15071888
 * - func_150718E4
 * - func_15071A34
 * - func_15071A64
 * - func_15071B18
 * - func_15071D08
 * - func_15071D78
 * - func_15071FDC
 * - func_150721A4
 * - func_15072208
 * - func_150722F0
 * - func_15072420
 * - func_1507266C
 * - func_15072740
 * - func_150727F0
 * - func_15072A7C
 * - func_15072B44
 * - func_15072EC0
 * - func_15072F10
 * - func_15073118
 * - func_1507342C
 * - func_150738E8
 * - func_15073A50
 * - func_15073B38
 * - func_15073C50
 * - func_15073DA4
 * - func_15073E2C
 * - func_15073EA4
 * - func_15073FA0
 * - func_15074664
 * - func_150746F0
 * - func_150747E4
 * - func_1507488C
 * - func_1507490C
 * - func_15074980
 * - func_15074A94
 * - func_15074C00
 * - func_15074C80
 * - func_15074E04
 * - func_15074E80
 * - func_15074F30
 * - func_15074F48
 * - func_15074FD4
 * - func_150750C4
 * - func_1507515C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AD30.s")
/* Call context: func_1505E650: unique active project prototype */
void func_1505E650(u8 *, s32, s32, s32, f32, f32, s32);
extern u8 * D_800D154C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506AF74 CURRENT (115) */
void func_1506AF74(void) {
    u8 var_v1;

    var_v1 = *(u8 *)((u8 *)D_800D154C + 0x100);
    if (var_v1 & 8) {
        *(u8 *)((u8 *)D_800D154C + 0x100) = (u8) (var_v1 | 4);
        var_v1 = *(u8 *)((u8 *)D_800D154C + 0x100);
    }
    *(u8 *)((u8 *)D_800D154C + 0x100) = (u8) (var_v1 & 0xF7);
    func_1505E650(D_800D154C, 0x38, 0x3F800000, 0x40A00000, 0.0f, 0.0f, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506AF74 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AF74.s")
extern u8 *D_800D154C;
extern s32 D_800CC2D0;
void func_1507D4F8(u8 arg0);
extern void func_1505E650(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6);

void func_1506AFE0(void) {
    func_1505E650(D_800D154C, 0x48, 0x3F800000, 0x40A00000, 0.0f, 0.0f, 0);
}
/* Call context: func_1505E650: unique active project prototype */

void func_1506B020(void) {
    *(s8 *)((u8 *)D_800D154C + 0x1CB) = 1;
    func_1505E650(D_800D154C, 0x39, 0x3F800000, 0x40A00000, 0.0f, 0.0f, 0);
}
void func_1506B070(void) {

}
/* Call context: func_1506B100: unique active project prototype */
void func_1506B100(s32, f32, f32);
extern f32 D_80099C34;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506B078 CURRENT (20) */
void func_1506B078(void) {
    f32 temp_fv0;
    f32 var_fv0;

    temp_fv0 = (*(f32 *)((u8 *)D_800D154C + 0x18) - (*(f32 *)((u8 *)D_800D154C + 0x118) - 150.0f)) * D_80099C34;
    if (temp_fv0 < 0.0f) {
        var_fv0 = 1.0f;
    } else {
        var_fv0 = temp_fv0 + 1.0f;
    }
    func_1506B100(0xD1, var_fv0, 4.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506B078 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B078.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506B100 CURRENT (911) */
void func_1506B100(s32 arg0, f32 arg1, f32 arg2) {
    func_1505E650(D_800D154C, (s32)(u16)arg0, *(s32 *)&arg1, *(s32 *)&arg2, 0.0f, 0.0f, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506B100 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B100.s")
/* Call context: func_1505E650: unique active project prototype */

void func_1506B14C(void) {
    func_1505E650(D_800D154C, (*(u16 *)((u8 *)D_800D154C + 0x84) + 1) & 0xFFFF, *(s32 *)((u8 *)D_800D154C + 0x4C), 0x40400000, 0.0f, 0.0f, 0);
}
/* Call context: func_1505E650: unique active project prototype */

void func_1506B198(void) {
    func_1505E650(D_800D154C, (*(u16 *)((u8 *)D_800D154C + 0x84) + 1) & 0xFFFF, *(s32 *)((u8 *)D_800D154C + 0x4C), 0x40400000, 0.0f, 0.0f, 1);
}
void func_1506B1E8(void) {
    func_1505E650(D_800D154C, 0x3C, 0x3F800000, 0x40400000, 0.0f, 0.0f, 0);
}
void func_1506B228(void) {
    func_1505E650(D_800D154C, 0x54, 0x3F800000, 0x40400000, 0.0f, 0.0f, 0);
}
/* Call context: func_1505E650: unique active project prototype */

void func_1506B268(void) {
    *(s8 *)((u8 *)D_800D154C + 0x83) = 0;
    *(s8 *)((u8 *)D_800D154C + 0x89) = 0;
    func_1505E650(D_800D154C, 0xF, 0x3F800000, 0x40C00000, 0.0f, 0.0f, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B2BC.s")
void func_1506B328(void) {
    func_1505E650(D_800D154C, 0x3E, 0x3F800000, 0x40A00000, 0.0f, 0.0f, 0);
}
void func_1506B368(void) {

}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506B370 CURRENT (105) */
void func_1506B370(void) {
    func_1507D4F8((D_800D154C - (u8 *)&D_800CC2D0) / 0x32C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506B370 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B370.s")
void func_1506B3B0(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B3B8.s")
void func_1506B4EC(void) {
    func_1506B3B8();
}
extern s32 D_800D1580;
void func_15141A7C(u8 *arg0, s32 arg1);
void func_15192800(u8 *arg0, s32 arg1);
void func_1507C8E0(u8 *arg0, s32 arg1);
void func_1507F640(void);
void func_1512D748(void *arg0, s32 arg1, s32 arg2);

void func_1506B50C(void) {
    *(s16 *)(D_800D154C + 0x21C) = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B520.s")
void func_1506B5A4(void) {
}
void func_1506B5AC(void) {
}
void func_1506B5B4(void) {
    D_800D154C[0x1CB] = 1;
}
void func_1506B5CC(void) {
    D_800D154C[0x1CB] = 1;
}
void func_1506160C(u8 *, s32, s32, s32, u8);

void func_1506B5E4(void) {
    func_1506160C(D_800D154C, 2, 7, 8, 0U);
    *(f32 *)(D_800D154C + 0x4C) = 0.0f;
    *(f32 *)(*(u8 **)(D_800D154C + 0x2D0) + 0x10) = 0.0f;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B634.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B740.s")
void func_1506B634(s32 arg0);

void func_1506B7F4(void) {
    D_800D154C[0x89] = 0;
    D_800D154C[0x83] = 0;
    func_1506B634(2);
}
void func_1506B82C(void) {
    *(u8 *)(D_800D154C + 0x89) = 0;
    *(u8 *)(D_800D154C + 0x83) = 0;
    func_1507F640();
}
void func_1506B100(s32 arg0, f32 arg1, f32 arg2);

void func_1506B860(void) {
    func_1506B100(0xB5, 0.63f, 5.0f);
}
void func_1506B88C(void) {
    func_1506B100(0xB6, 1.0f, 4.0f);
}
void func_1506B8B4(void) {
    *(u8 *)(*(u8 **)(D_800D154C + 0x31C) + 0x78) = 0;
    *(u8 *)(D_800D154C + 0x89) = 0;
    *(u8 *)(D_800D154C + 0x83) = 0;
    func_1507F640();
}
void func_1506B8F4(void) {
    func_1506B100(0xDE, 0.75f, 4.0f);
}
void func_1506B91C(void) {
    func_1506B100(0xBF, 1.0f, 4.0f);
}
/* Call context: func_1506B100: unique active project prototype */

void func_1506B944(void) {
    *(s8 *)((u8 *)D_800D154C + 0x89) = 0;
    *(s8 *)((u8 *)D_800D154C + 0x83) = 0;
    func_1506B100(0xC5, 1.0f, 4.0f);
}
void func_1506B984(void) {
    func_1506B100(0xAF, 1.0f, 4.0f);
}
void func_1506B9AC(void) {
    *(s16 *)(D_800D154C + 0x244) = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B9C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BA4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BAD8.s")
extern u16 D_800D1582;
extern void func_10012718(u16 arg0, u8 *arg1, s32 arg2, s16 arg3, s32 arg4);
void func_1506BB64(s32 arg0, s32 arg1) {
    func_10012718(D_800D1582, D_800D154C, 0x6D60, (s16) arg0, arg1);
}
/* Call context: func_10010154: unique active project prototype */
void func_10010154(s32, s32, s32, s32, s32);
void func_1506BBA8(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506BBA8 CURRENT (60) */
void func_1506BBA8(s32 arg0, s32 arg1) {
    u8 *sp24;

    sp24 = D_800D154C;
    if (*(s32 *)((u8 *)D_800D154C + 0x318) == 0) {
        func_10010154((s32) D_800D1582, (s32) D_800D154C, 0x36B0, (s32) (s16) arg0, arg1);
        return;
    }
    func_10010154((s32) D_800D1582, (s32) sp24, 0x2EE0, 0x1F4, 0x9C4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506BBA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BBA8.s")
/* Call context: func_10010344: unique active project prototype */
s32 func_10010344(s32, s32, u32, s16, s32);
extern u16 D_800D1582;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506BC24 CURRENT (700) */
void func_1506BC24(s16 arg0, s32 arg1) {
    u8 *sp24;

    sp24 = D_800D154C;
    if (*(s32 *)((u8 *)D_800D154C + 0x318) == 0) {
        func_10010344((s32) D_800D1582, (s32) D_800D154C, 0x36B0U, arg0, arg1);
        return;
    }
    func_10010344((s32) D_800D1582, (s32) sp24, 0x2EE0U, 0x1F4, 0x9C4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506BC24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BC24.s")
void func_1506BCA0(void) {
    *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) D_800D1580;
}
s32 func_151EF610(u8 **);                           /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506BCC8 CURRENT (570) */
void func_1506BCC8(void) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_ft1;
    u8 *temp_v1;

    temp_v1 = D_800D154C;
    if (*(s32 *)((u8 *)temp_v1 + 0) == 0x16) {
        if (*(f32 *)((u8 *)temp_v1 + 0x180) == *(f32 *)((u8 *)temp_v1 + 0x18)) {
            *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) ((func_151EF610(&D_800D154C) % 8) + D_800D1580);
            temp_fv0 = *(f32 *)((u8 *)D_800D154C + 0x3C);
            if (temp_fv0 != 0.0f) {
                var_ft1 = *(f32 *)((u8 *)D_800D154C + 0x20) * (temp_fv0 / 40.0f);
                goto block_8;
            }
            *(f32 *)((u8 *)D_800D154C + 0x20) = 0.0f;
        }
    } else {
        temp_fv0_2 = *(f32 *)((u8 *)temp_v1 + 0x18) - *(f32 *)((u8 *)temp_v1 + 0x180);
        if ((temp_fv0_2 > -5.0f) && (temp_fv0_2 < 5.0f)) {
            var_ft1 = (f32) D_800D1580;
block_8:
            *(f32 *)((u8 *)temp_v1 + 0x20) = var_ft1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506BCC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BCC8.s")
extern f32 D_80099C40;

void func_1506BDE8(void) {
    if (*(f32 *)((u8 *)D_800D154C + 0x18) < D_80099C40) {
        *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) D_800D1580;
    }
}
void func_1506BE2C(void) {
    *(f32 *)((u8 *)D_800D154C + 0x24) = (f32) D_800D1580;
}
extern f32 D_80099C44;

void func_1506BE54(void) {
    *(f32 *)((u8 *)D_800D154C + 0x24) = (f32) ((f32) D_800D1580 * D_80099C44);
}
void func_1506BE84(void) {
    D_800D154C[0x89] = 0;
}
void func_1506BE98(void) {
    *(f32 *)((u8 *)D_800D154C + 0xC0) = (f32) D_800D1580;
}
void func_1506BEC0(void) {
    D_800D154C[0x89] = (s8)D_800D1580;
}
void func_1506BEDC(void) {
    *(s8 *)((u8 *)D_800D154C + 0xD0) = (s8) D_800D1580;
    *(f32 *)((u8 *)D_800D154C + 0x114) = (f32) ((s32) D_800D1580 >> 8);
}
extern void func_1506BF5C(void);

void func_1506BF1C(void) {
    if (*(f32 *)(D_800D154C + 0x118) <= *(f32 *)(D_800D154C + 0x18)) {
        func_1506BF5C();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BF5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C32C.s")
void func_1506C418(void) {
    func_10010A3C(D_800D154C);
}
void func_1506C43C(void) {
    func_100109D0(D_800D154C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C460.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506CE6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D2E8.s")
void func_1506D4EC(void) {
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506D4F4 CURRENT (370) */
void func_1506D4F4(void) {
    union {
        f32 f;
        s32 i;
    } temp;

    temp.f = 0.0f;
    func_1505E650(D_800D154C, *(u16 *)(D_800D154C + 0x84), 0x3C23D70A, temp.i, 0.0f, 0.0f, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506D4F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D4F4.s")
extern u8 D_800C35EA;
extern u8 D_800C3E78;

void func_1506D538(void) {
    if (D_800C35EA != 1) {
        func_1507D4F8(D_800C3E78);
    }
}
void func_1506D570(void) {
    D_800D154C[0x6E] = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D584.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D6B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D74C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D898.s")
void func_1506D934(void) {
    D_800D154C[0x103] = (s8)D_800D1580;
}
void func_1506D950(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D958.s")
void func_1506DA78(void) {
    D_800D154C[0x125] = (s8)D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DA94.s")
void func_15076760(void);
extern s8 D_800D1890;

void func_1506DB30(void) {
    D_800D1890 = (s8) D_800D1580;
    func_15076760();
}
void func_1506DB5C(void) {
    *(f32 *)((u8 *)D_800D154C + 0x3C) = (f32) D_800D1580;
}
void func_1506DB84(void) {
    D_800D154C[0x239] = (s8)D_800D1580;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506DBA0 CURRENT (50) */
void func_1506DBA0(void) {
    *(s8 *)((u8 *)D_800D154C + 0x1E5) = (s8) D_800D1580;
    *(s8 *)((u8 *)D_800D154C + 0x1E6) = (s8) ((s32) D_800D1580 >> 8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506DBA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DBA0.s")
void func_15054A5C(u8 *, void *);
void *func_15072208(void *, s32);

void func_1506DBD4(void) {
    void *temp_v0;

    temp_v0 = func_15072208(D_800D154C, 0);
    if (temp_v0 != 0) {
        func_15054A5C(temp_v0, D_800D154C);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DC10.s")
void func_1506DCA4(void) {
    *(s32 *)(D_800D154C + 0x2E8) = D_800D1580;
}
void func_1506DCC0(void) {
    *(s32 *)(D_800D154C + 0x2EC) = D_800D1580;
}
void func_1506DCDC(void) {
    D_800D154C[0x1CA] = (s8)D_800D1580;
}
void func_1506DCF8(void) {
}
void func_1506DD00(void) {
    if (D_800D1580 == 0) {
        *(s32 *)(D_800D154C + 0xF8) = *(s32 *)(*(u8 **)(D_800D154C + 0x144) + 0x18);
        return;
    }
    *(s32 *)(D_800D154C + 0xF8) |= D_800D1580;
}
void func_1506DD44(void) {
    *(s32 *)((u8 *)D_800D154C + 0xF8) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF8) & ~D_800D1580);
}
void func_1506DD6C(void) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x7D) = (s8) (D_800D1580 & 0x7F);
    }
    if (D_800D1580 == 0) {
        *(u16 *)((u8 *)D_800D154C + 0x76) = (u16) *(u16 *)((u8 *)D_800D154C + 0x7A);
    }
}
void func_1506DDB8(void) {
}
extern s32 D_800BE9F0;
extern u8 D_800C3E78;
extern s32 func_15178E50(s32 arg0);
extern void func_1516EED4(u8 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1506DDC0(void) {
    if (func_15178E50(D_800BE9F0) != 0) {
        func_1516EED4(D_800C3E78, D_800D1580, 0xFF, 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DE04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DE84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E0EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E2CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E46C.s")
extern void func_1506BA4C(s32 arg0, s32 arg1);
extern s32 func_1506E46C(u8 *arg0, s32 *arg1, s32 arg2);

void func_1506E5FC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x12C, 0x708);
    }
}
void func_1506E63C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x64, 0x320);
    }
}
void func_1506E67C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0xBE, 0x514);
    }
}
void func_1506E6BC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x12C, 0xBB8);
    }
}
void func_1506E6FC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x2BC, 0xFA0);
    }
}
void func_1506E73C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0xBB8, 0x1F40);
    }
}
extern void func_1506BBA8(s32 arg0, s32 arg1);

void func_1506E77C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BBA8(0x12C, 0x708);
    }
}
void func_1506E7BC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BBA8(0x12C, 0xBB8);
    }
}
/* Call context: func_1506E5FC: unique active project prototype */

void func_1506E7FC(void) {
    if ((*(f32 *)((u8 *)D_800D154C + 0x28) == 0.0f) && (*(u8 *)((u8 *)D_800D154C + 0x107) == 0)) {
        func_1506E5FC();
    }
}
/* Call context: func_1506BA4C: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */
s32 func_1000F4D8(u16);                             /* extern */

void func_1506E848(void) {
    if ((func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) && (func_1000F4D8(D_800D1582) == 0)) {
        func_1506BA4C(0x50, 0x320);
    }
}
extern void func_1506BB64(s32 arg0, s32 arg1);

void func_1506E898(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 2) != 0) {
        func_1506BB64(0x12C, 0x708);
    }
}
extern void func_1506BAD8(s32 arg0, s32 arg1);

void func_1506E8D8(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x12C, 0x708);
    }
}
void func_1506E918(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x64, 0x320);
    }
}
void func_1506E958(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0xBE, 0x514);
    }
}
void func_1506E998(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x12C, 0xBB8);
    }
}
void func_1506E9D8(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x2BC, 0xFA0);
    }
}
void func_1506EA18(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0xBB8, 0x1F40);
    }
}
extern void func_1506BC24(s16 arg0, s32 arg1);

void func_1506EA58(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BC24(0x12C, 0xBB8);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EA98.s")
extern f32 D_80099DA4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506EBC0 CURRENT (615) */
void func_1506EBC0(void) {
    u8 temp_a0;
    void *temp_a0_2;

    temp_a0 = *(u8 *)((u8 *)D_800D154C + 0x13C);
    if (temp_a0 != 0) {
        temp_a0_2 = (((temp_a0 - 0x64) & 0xFF) * 0x32C) + &D_800CC2D0;
        if ((s32) *(u8 *)((u8 *)temp_a0_2 + 0x13D) >= 0x64) {
            *(s8 *)((u8 *)temp_a0_2 + 0x65) = 0;
            *(u8 *)((u8 *)temp_a0_2 + 0x13D) = 0U;
            *(f32 *)((u8 *)temp_a0_2 + 0x3C) = 0.0f;
            *(f32 *)((u8 *)temp_a0_2 + 0x20) = 0.0f;
            *(f32 *)((u8 *)temp_a0_2 + 0x24) = 6.0f;
            *(f32 *)((u8 *)temp_a0_2 + 0x1CC) = (f32) D_80099DA4;
        }
        *(u8 *)((u8 *)D_800D154C + 0x13C) = 0U;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506EBC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EBC0.s")
extern f32 D_80099DA8;
extern f32 D_800CC2E8;
extern f32 D_800D1878;
extern s32 D_800D1880;

void func_1506EC50(void) {
    if ((D_80099DA8 < *(f32 *)((u8 *)D_800D154C + 0x28)) && (!(D_800D1580 & 0x8000) || (D_800CC2E8 < *(f32 *)((u8 *)D_800D154C + 0x18)))) {
        D_800D1878 = (f32) (D_800D1580 & 0xFF);
        D_800D1880 = 0;
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) - 1);
    }
}
typedef struct Game981E0Flags {
    u8 pad0[4];
    u16 flags;
} Game981E0Flags;

void func_1506ECD0(void) {
    Game981E0Flags *entry = *(Game981E0Flags **)(D_800D154C + 0x2D0);

    entry->flags |= 0x8000;
}
void func_1506ECF0(void) {
    D_800D154C[0x3A] = (s8)D_800D1580;
}
void func_1506ED0C(void) {
    D_800D154C[0x83] = (s8) D_800D1580;
    D_800D154C[0x100] = (s8) (D_800D154C[0x100] | 0x10);
    (*(u8 **)(D_800D154C + 0x31C))[0x31] = 1;
}
void func_1506ED4C(void) {
    D_800D154C[0x100] = (s8)D_800D1580;
}
void func_1506ED68(void) {
    D_800D154C[0xA9] = 5;
    (*(u8 **)(D_800D154C + 0x31C))[0x31] = 0;
}
void func_1506ED90(void) {
    *(s16 *)(D_800D154C + 0x21C) = (s16)D_800D1580;
}
void func_1506EDAC(void) {
    *(s32 *)(D_800D154C + 0xF4) = D_800D1580;
}
void func_1506EDC8(void) {
    *(s32 *)((u8 *)D_800D154C + 0xF4) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF4) & ~D_800D1580);
}
void func_1506EDF0(void) {
    *(s32 *)(D_800D154C + 0xF4) |= D_800D1580;
}
void func_1506EE14(void) {
    *(s32 *)(D_800D154C + 0x25C) |= D_800D1580;
}
void func_1506EE38(void) {
    *(s32 *)((u8 *)D_800D154C + 0x25C) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x25C) & ~D_800D1580);
}
void func_15188810(u8 *arg0, s32 arg1, s32 arg2);
void func_15188A9C(s32 arg0);

void func_1506EE60(void) {
    if (D_800D1580 != 0) {
        func_15188810(D_800D154C, D_800D1580 & 0xFFFF, (s32)D_800D1580 >> 0x10);
        return;
    }
    func_15188A9C((s32)D_800D154C);
}
/* Call context: func_151898C0: unique active project prototype */
void func_151898C0(s32, s32);

void func_1506EEAC(void) {
    func_151898C0((s32) D_800D154C, D_800D1580);
}
void func_1506EED8(void) {
    D_800D154C[0x24E] = (s8)D_800D1580;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506EEF4 CURRENT (120) */
void func_1506EEF4(void) {
    *(s8 *)((u8 *)D_800D154C + 0x276) = (s8) ((s32) D_800D1580 >> 0x10);
    *(s16 *)((u8 *)D_800D154C + 0x278) = (s16) (((s32) D_800D1580 >> 0x18) & 0xFF);
    *(s16 *)((u8 *)D_800D154C + 0x282) = (s16) D_800D1580;
    *(s8 *)((u8 *)D_800D154C + 0x284) = 0;
    *(s8 *)((u8 *)D_800D154C + 0x285) = 0;
    *(s8 *)((u8 *)D_800D154C + 0x286) = 0;
    *(s8 *)((u8 *)D_800D154C + 0x287) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506EEF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EEF4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506EF5C CURRENT (1545) */
void func_1506EF5C(void) {
    s32 temp_t6;

    *(s16 *)((u8 *)D_800D154C + 0x282) = 0xFFFF;
    *(s8 *)((u8 *)D_800D154C + 0x276) = 5;
    temp_t6 = (((s32) D_800D1580 >> 0x10) & 0xFF) * 2;
    *(s8 *)((u8 *)(D_800D154C + temp_t6) + 0x284) = (s8) ((s32) D_800D1580 >> 8);
    *(s8 *)((u8 *)(temp_t6 + D_800D154C) + 0x285) = (s8) D_800D1580;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506EF5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EF5C.s")
void func_1506EFB4(void) {
    *(s16 *)(D_800D154C + 0x282) = 0;
}
void func_150BB760(u8 *);

void func_1506EFC8(s32 arg0) {
    if (D_800D154C[4] != 0x8C) {
        func_150BB760(D_800D154C);
    }
}
void func_150BCBBC(u8 *arg0);

void func_1506F004(s32 arg0) {
    func_150BCBBC(D_800D154C);
}
void func_150BA4C0(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506F02C CURRENT (100) */
void func_1506F02C(void) {
    func_150BA4C0(D_800D154C, 0xFF, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506F02C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F02C.s")
void func_151925C4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1506F05C(s32 arg0) {
    func_151925C4(D_800D154C, 0x32, 0xFF, 1);
}
void func_1506F090(s32 arg0) {
    func_151925C4(D_800D154C, -1, 0xFF, 1);
}
void func_150C1260(u8 *arg0, s32 arg1);

void func_1506F0C4(s32 arg0) {
    func_150C1260(D_800D154C, 0);
}
void func_1506F0F0(s32 arg0) {
    func_150C1260(D_800D154C, 1);
}
void func_150BABE0(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506F11C CURRENT (100) */
void func_1506F11C(void) {
    func_150BABE0(D_800D154C, 0, 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506F11C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F11C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506F14C CURRENT (100) */
void func_1506F14C(void) {
    func_150BABE0(D_800D154C, 1, 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506F14C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F14C.s")
void func_150AEEB0(u8 *arg0, s32 arg1);

void func_1506F17C(s32 arg0) {
    func_150AEEB0(D_800D154C, 0xFF);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F1A8.s")
void func_15197A7C(void *arg0);

void func_1506F524(s32 arg0) {
    func_15197A7C(D_800D154C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F54C.s")
/* Call context: func_1519EF70: unique active project prototype */
void func_1519EF70(s32, s32, s32);

void func_1506F8C0(s32 arg0) {
    func_1519EF70((s32) D_800D154C, 0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F8F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F9C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FA90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FB60.s")
void func_151A0A10(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1506FBE8(s32 arg0) {
    func_151A0A10(D_800D154C, 0x46, 0xFF, 0);
}
void func_1506FC1C(s32 arg0) {
    func_151A0A10(D_800D154C, 0x28, 0xFF, 0);
}
void func_1506FC50(s32 arg0) {
    func_1519E688();
}
void func_1519E6BC(u8 *arg0);

void func_1506FC74(s32 arg0) {
    func_1519E6BC(D_800D154C);
}
void func_150B3AB0(u8 *arg0, s32 arg1);

void func_1506FC9C(s32 arg0) {
    func_150B3AB0(D_800D154C, 0xFF);
}
void func_15196438(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1506FCC8(s32 arg0) {
    func_15196438(D_800D154C, 6, 0xFF, 0);
}
void func_1506FCFC(s32 arg0) {
    func_15196438(D_800D154C, 5, 0xFF, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FD30.s")
void func_151AABC4(u8 *arg0, s32 arg1);

void func_1506FDF0(s32 arg0) {
    func_151AABC4(D_800D154C, 0);
}
void func_1506FE1C(s32 arg0) {
    func_151AABC4(D_800D154C, 1);
}

void func_1506FE48(s32 arg0) {
    func_151AABC4(D_800D154C, 0);
}
/* Call context: func_151AABC4: unique active project prototype */

void func_1506FE74(s32 arg0) {
    func_151AABC4(D_800D154C, 1);
}
/* Call context: func_151AABC4: unique active project prototype */

void func_1506FEA0(s32 arg0) {
    func_151AABC4(D_800D154C, 2);
}
/* Call context: func_151AABC4: unique active project prototype */

void func_1506FECC(s32 arg0) {
    func_151AABC4(D_800D154C, 3);
}
/* Call context: func_151AB920: unique active project prototype */
void func_151AB920(s32, s32);

void func_1506FEF8(s32 arg0) {
    func_151AB920((s32) D_800D154C, 0);
}
/* Call context: func_151AB920: unique active project prototype */

void func_1506FF24(s32 arg0) {
    func_151AB920((s32) D_800D154C, 1);
}
void func_151AB930(u8 *arg0);

void func_1506FF50(s32 arg0) {
    func_151AB930(D_800D154C);
}
void func_150CBF80(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1506FF78(s32 arg0) {
    func_150CBF80(D_800D154C, 0, 1, 0xFF);
}
void func_1506FFAC(s32 arg0) {
    func_150CBF80(D_800D154C, 1, 1, 0xFF);
}
void func_1506FFE0(s32 arg0) {
    func_150CBF80(D_800D154C, 2, 1, 0xFF);
}
void func_150CA150(u8 *arg0);

void func_15070014(s32 arg0) {
    func_150CA150(D_800D154C);
}
extern void func_151B01B8(u8 *arg0, s32 arg1);
extern void func_151B09BC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_1507003C(s32 arg0) {
    func_151B01B8(D_800D154C, 0);
    func_151B09BC(D_800D154C, 0, 0x3E8, 0xFF, 0);
}
void func_151AECA0(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15070084 CURRENT (100) */
void func_15070084(void) {
    func_151AECA0(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15070084 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070084.s")
void func_151B03B8(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150700B4 CURRENT (100) */
void func_150700B4(void) {
    func_151B03B8(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150700B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150700B4.s")
void func_15193660(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150700E4 CURRENT (100) */
void func_150700E4(void) {
    func_15193660(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150700E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150700E4.s")
void func_151937F4(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15070114 CURRENT (100) */
void func_15070114(void) {
    func_151937F4(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15070114 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070114.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070144.s")
void func_151C5280(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150701C4 CURRENT (100) */
void func_150701C4(void) {
    func_151C5280(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150701C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150701C4.s")
void func_151C9740(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150701F4 CURRENT (100) */
void func_150701F4(void) {
    func_151C9740(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150701F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150701F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070224.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070300.s")
void func_150EEE00(u8 *arg0, s32 arg1, s32 arg2);

void func_15070690(s32 arg0) {
    func_150EEE00(D_800D154C, (arg0 - 0x3E) & 0xFF, arg0);
}
void func_150EEF40(u8 *arg0, s32 arg1, s32 arg2);

void func_150706C4(s32 arg0) {
    func_150EEF40(D_800D154C, (arg0 - 0x3E) & 0xFF, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150706F8.s")
void func_150EBEC0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15070760(s32 arg0) {
    func_150EBEC0(D_800D154C, 0, 0xFF, 1);
}
void func_15070794(s32 arg0) {
    func_150EBEC0(D_800D154C, 1, 0xFF, 1);
}
void func_150FDDA0(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150707C8 CURRENT (100) */
void func_150707C8(void) {
    func_150FDDA0(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150707C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150707C8.s")
void func_150FDF38(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150707F8(s32 arg0) {
    func_150FDF38(D_800D154C, 0xFF, 1, 0, 0);
}
void func_150FE320(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15070830 CURRENT (100) */
void func_15070830(void) {
    func_150FE320(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15070830 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070830.s")
void func_150FE49C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15070860(s32 arg0) {
    func_150FE49C(D_800D154C, 0xFF, 1, 0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070898.s")
void func_15199834(void *arg0);

void func_15070C18(s32 arg0) {
    func_15199834(D_800D154C);
}
void func_15070C40(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070C40.s")
void func_15070CDC(s32 arg0) {
    func_15070C40(1);
}
void func_15070D00(s32 arg0) {
    func_15070C40(0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070D24.s")
void func_15070F60(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070F60.s")
void func_15071230(s32 arg0) {
    func_15070F60(0);
}
void func_15071254(s32 arg0) {
    func_15070F60(1);
}
void func_150FC438(u8 *arg0, s32 arg1, s32 arg2, u8 arg3);

void func_15071278(s32 arg0) {
    func_150FC438(D_800D154C, 0, 1, D_800D154C[0x85]);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150712AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071360.s")
void func_150FF840(u8 *, s32, s32, s32, s32);

void func_15071434(s32 arg0) {
    func_150FF840(D_800D154C, 1, 0, 0xFF, 1);
}
void func_15071470(s32 arg0) {
    func_150FF840(D_800D154C, 0, 0, 0xFF, 1);
}
void func_150714AC(s32 arg0) {
    func_150FF840(D_800D154C, 0, 1, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150714E8.s")
extern void func_151D4668(void *arg0);
extern void func_151D469C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15071544(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 4, 0x78, 0xFF, 1);
}
void func_1507158C(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 2, 0x78, 0xFF, 1);
}
void func_150715D4(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 3, 0x78, 0xFF, 1);
}
void func_1507161C(s32 arg0) {

}
extern void func_151D0058(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15071628(s32 arg0) {
    func_151D0058(D_800D154C, (arg0 - 0x55) & 0xFF, 0xFF, 1);
}
void func_151D0024(u8 *arg0);

void func_15071668(s32 arg0) {
    func_151D0024(D_800D154C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150716EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071764.s")
void *func_15083E90(u8);
typedef struct {
    void *field_0;
    u8 field_4;
} Game981E0MenuInput;

void func_15131D4C(Game981E0MenuInput *, s32);
void func_151494E0(Game981E0MenuInput *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150717E0 CURRENT (300) */
void func_150717E0(s32 arg0) {
    Game981E0MenuInput sp20;
    Game981E0MenuInput *sp18;
    void *temp_v0;

    temp_v0 = func_15083E90(0x12U);
    if (temp_v0 != 0) {
        sp20.field_0 = temp_v0;
        sp18 = &sp20;
        sp20.field_4 = ((u8 *)temp_v0)[0x3B];
        func_15131D4C(sp18, 0x43);
        func_151494E0(sp18, 0x43);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150717E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150717E0.s")
void func_150F9BB0(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15071830 CURRENT (100) */
void func_15071830(void) {
    func_150F9BB0(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15071830 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071830.s")
void func_1519072C(u8 *arg0);

void func_15071860(s32 arg0) {
    func_1519072C(D_800D154C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071888.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150718E4.s")
void func_150FA520(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15071998(s32 arg0) {
    func_150FA520(D_800D154C, 0, 0xFF, 1);
}
void func_150719CC(s32 arg0) {
    func_150FA520(D_800D154C, 1, 0xFF, 1);
}
void func_15071A00(s32 arg0) {
    func_150FA520(D_800D154C, 2, 0xFF, 1);
}
void func_151D09A8(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15071A34 CURRENT (100) */
void func_15071A34(void) {
    func_151D09A8(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15071A34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071A34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071A64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071B18.s")
void func_150F2230(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15071D08 CURRENT (100) */
void func_15071D08(void) {
    func_150F2230(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15071D08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071D08.s")
extern void (*D_80086150[])(s32);

void func_15071D38(void) {
    void (*temp_v0)(s32);

    temp_v0 = D_80086150[D_800D1580];
    if (temp_v0 != 0) {
        temp_v0(D_800D1580);
    }
}
/* Call context: func_15071D38: unique active project prototype */
/* Call context: func_150721E8: unique active project prototype */
void * func_150721E8(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15071D78 CURRENT (325) */
void func_15071D78(void) {
    u8 *sp18;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_v0 = func_150721E8(D_800D154C);
    if (temp_v0 != 0) {
        temp_t6 = D_800D154C;
        D_800D154C = temp_v0;
        sp18 = temp_t6;
        func_15071D38();
        D_800D154C = sp18;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15071D78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071D78.s")
void func_15071DC8(void) {
    func_15141A7C(D_800D154C, D_800D1580);
}
void func_15071DF4(void) {
    func_15192800(D_800D154C, D_800D1580);
}
void func_15071E20(void) {
    D_800D154C[0x247] = (s8)D_800D1580;
}
void func_15071E3C(void) {
    D_800D154C[0x248] = (s8)D_800D1580;
}
/* Call context: func_1505E650: unique active project prototype */

void func_15071E58(void) {
    D_800D1878 = (f32) (D_800D1580 & 0xFF);
    *(u16 *)((u8 *)D_800D154C + 0x244) = (u16) (((s32) D_800D1580 >> 8) & 0xFF);
    func_1505E650(D_800D154C, (s32) *(u16 *)((u8 *)D_800D154C + 0x244), 0x3F99999A, 0x40400000, D_800D1878, 0.0f, 0);
}
void func_15071ED4(void) {
    func_1505E650(D_800D154C, 0x59, 0x3F800000, 0x40400000, 0.0f, 0.0f, 0);
}
void func_15071F14(void) {
    func_1505E650(D_800D154C, 0x24, 0x3F800000, 0x40400000, 0.0f, 0.0f, 0);
}
void func_15071F54(void) {
    func_1507C8E0(D_800D154C, D_800D1580);
}
extern u8 D_800C35EA;

void func_15071F80(void) {
    if (D_800C35EA == 1) {
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) + 1);
    }
}
void func_15071FB0(void) {
    if (*(f32 *)((u8 *)D_800D154C + 0x28) == 0.0f) {
        *(s16 *)((u8 *)D_800D154C + 0x10C) = 0;
    }
}
/* Call context: func_1505E650: unique active project prototype */
extern f32 D_80099F48;
extern f32 D_800CC2F0;
extern f32 D_800CC2F4;
extern f32 D_800CC30C;
extern u16 D_800CC346;
extern s8 D_800CC351;
extern f32 D_800CC49C;
extern u8 D_800CC544;
extern void *D_800CC5E8;
extern void *D_800CC5EC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15071FDC CURRENT (3665) */
void func_15071FDC(void) {
    s32 sp2C;
    s32 *var_v1;
    s32 var_a2;
    s32 var_t0;
    s32 var_t1;
    s32 var_v0;

    var_t1 = 1;
    var_t0 = 0x194;
    if (D_800D1580 == 0) {
        var_a2 = -1;
        var_v1 = &D_800CC2D0;
        var_v0 = 0;
loop_2:
        if ((D_800C3E78 + 1) == *(u8 *)((u8 *)var_v1 + 0x65)) {
            var_a2 = var_v0;
        } else {
            var_v0 += 1;
            var_v1 += 0x32C;
            if (var_v0 != 0x19) {
                goto loop_2;
            }
        }
        if ((var_a2 + 1) == D_800CC544) {
            D_800CC346 = *(u16 *)((u8 *)D_800D154C + 0x76) + 0x8000;
            D_800CC49C = D_80099F48;
            goto block_13;
        }
    } else {
        if (*(s32 *)((u8 *)D_800D154C + 0x2E8) >= 0x71) {
            var_t0 = 0x2E5;
            *(f32 *)((u8 *)D_800D154C + 0x2E0) = 0.0f;
        } else {
            var_t0 = 0x32;
            D_800CC346 = *(u16 *)((u8 *)D_800D154C + 0x76);
            var_t1 = 0;
            if (*(u8 *)((u8 *)D_800D154C + 0x251) != 0) {
                D_800CC49C = D_800CC2E8 + 800.0f;
            }
        }
        *(s32 *)((u8 *)D_800D154C + 0x2E4) = 0x32;
block_13:
        D_800CC2F0 = *(f32 *)((u8 *)D_800D154C + 0x2D8);
        D_800CC2F4 = *(f32 *)((u8 *)D_800D154C + 0x2DC);
        sp2C = var_t1;
        D_800CC30C = *(f32 *)((u8 *)D_800D154C + 0x2E0);
        D_800CC351 = 1;
        func_1505E650((u8 *) &D_800CC2D0, var_t0 & 0xFFFF, 0x3F800000, 0x40000000, 6.0f, 0.0f, 0);
        *(s8 *)((u8 *)D_800CC5EC + 0x31) = (s8) var_t1;
        if (D_800CC5E8 != 0) {
            *(s32 *)((u8 *)D_800CC5E8 + 0x5F0) = (s32) (*(s32 *)((u8 *)D_800CC5E8 + 0x5F0) | 0x400);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15071FDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071FDC.s")
extern void func_1506160C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150721A4 CURRENT (260) */
void func_150721A4(void) {
    s32 *temp_v0;
    s32 temp_v1;
    s32 temp_t6;
    s32 temp_t7;

    temp_v0 = &D_800D1580;
    temp_v1 = *temp_v0;
    temp_t6 = temp_v1 >> 8;
    temp_t7 = temp_v1 >> 0x10;
    func_1506160C(D_800D154C, temp_t7 & 0xFF, temp_v1 & 0xFF, temp_t6 & 0xFF, 0U);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150721A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150721A4.s")
void *func_15072208(void *arg0, s32 arg1);

void *func_150721E8(void *arg0) {
    return func_15072208(arg0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072208.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150722F0 CURRENT (130) */
void func_150722F0(void) {
    u8 *temp_v0;

    temp_v0 = func_150721E8(D_800D154C);
    if (temp_v0 != 0) {
        func_1506160C(temp_v0, 2, (D_800D1580 >> 8) & 0xFF, D_800D1580 & 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150722F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150722F0.s")
void func_1507233C(void) {
    *(s32 *)(D_800D154C + 0x94) = ~(D_800D1580 | 1);
}
void func_15072360(void) {
    *(s32 *)((u8 *)D_800D154C + 0x94) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x94) & ~D_800D1580);
}
void func_15072388(void) {
    *(s32 *)(D_800D154C + 0x94) |= D_800D1580;
}
/* Call context: func_15060F28: unique active project prototype */
/* Call context: func_15083E90: unique active project prototype */
void func_15060F28(u8 *, s32);
void * func_15083E90(u8);
extern u8 D_800D1583;

void func_150723AC(void) {
    u8 *temp_v0;

    temp_v0 = func_15083E90(D_800D1583);
    if (temp_v0 != 0) {
        func_15060F28(temp_v0, 0);
    }
}
/* Call context: func_15060F28: unique active project prototype */
/* Call context: func_15083E90: unique active project prototype */

void func_150723E0(void) {
    u8 *temp_v0;

    temp_v0 = func_15083E90(D_800D1583);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x65) != 0)) {
        func_15060F28(temp_v0, 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072420.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507266C.s")
void func_15072740(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15072740 CURRENT (1845) */
void func_15072740(void) {
    void *temp_v1;

    temp_v1 = (*(u8 *)((u8 *)D_800D154C + 0x222) * 0x32C) + &D_800CC2D0;
    *(s8 *)((u8 *)temp_v1 + 0x65) = (s8) (D_800C3E78 + 1);
    *(s32 *)((u8 *)temp_v1 + 0x5C) = (s32) ((s32) D_800D1580 >> 0x10);
    *(s8 *)((u8 *)temp_v1 + 0x101) = 4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15072740 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072740.s")
extern f32 D_80099F4C;

void func_150727AC(void) {
    *(f32 *)(D_800D154C + 0x4C) = (f32) D_800D1580 * D_80099F4C;
    *(f32 *)(*(u8 **)(D_800D154C + 0x2D0) + 0x10) = *(f32 *)(D_800D154C + 0x4C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150727F0.s")
void func_15060F28(u8 *arg0, s32 arg1);

void func_15072918(void) {
    func_15060F28(D_800D154C, 0);
}
void func_15072940(void) {
    func_15060F28(D_800D154C, 1);
}
/* Call context: func_1505E650: unique active project prototype */

void func_15072968(void) {
    func_1505E650(D_800D154C, 0x2C, 0x3FC00000, 0x41400000, 0.0f, 0.0f, 0);
    *(s8 *)((u8 *)D_800D154C + 0x89) = 0x19;
}
void func_150729B4(void) {
    *(s32 *)(D_800D154C + 0x2E4) = D_800D1580;
}
extern void func_1507EB4C(void *arg0, s32 arg1);

void func_150729D0(void) {
    *(s16 *)(*(u8 **)(D_800D154C + 0x31C) + 8) = 1;
    func_1507EB4C(D_800D154C, 0x15);
    func_1506B82C();
}
void func_15072A14(void) {
    *(s16 *)(*(u8 **)(D_800D154C + 0x31C) + 0x66) = 0;
    func_1507F640();
}
void func_15072A40(void) {
    *(s8 *)((u8 *)(*(void **)(D_800D154C + 0x31C)) + 0x19B) = 0;
    *(s8 *)((u8 *)(*(void **)(D_800D154C + 0x31C)) + 0x78) = 0;
    func_1507F640();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072A7C.s")
/* Call context: func_1505E650: unique active project prototype */

void func_15072AF8(void) {
    func_1505E650(D_800D154C, (*(u16 *)((u8 *)D_800D154C + 0x84) + 1) & 0xFFFF, 0x3F800000, 0x40C00000, 0.0f, 0.0f, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072B44.s")
void func_15072DA0(void) {
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) & 0xFFF8);
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) | D_800D1580);
}
/* Call context: func_15083568: unique active project prototype */
void func_15083568(void *, s32, s32, s32);

void func_15072DD8(void) {
    void *temp_v0;

    func_15083568(D_800D154C, D_800D1580, 0x3F800000, 0);
    temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x11A) == 1)) {
        *(u8 *)((u8 *)temp_v0 + 0x11A) = 2U;
    }
}
extern void func_150836CC(u8 *arg0, s32 arg1);

void func_15072E38(void) {
    u8 *temp_v0;

    func_150836CC(D_800D154C, D_800D1580);
    temp_v0 = *(u8 **)(D_800D154C + 0x31C);
    if (temp_v0 != 0) {
        temp_v0[0x11A] = 0;
    }
}
void func_15072E7C(void) {
    *(s16 *)(D_800D154C + 0x10C) = (s16)D_800D1580;
}
extern f32 D_800D1874;

void func_15072E98(void) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x2D0);
    *(f32 *)((u8 *)temp_v0 + 0x10) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x10) * D_800D1874);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15072EC0 CURRENT (35) */
void func_15072EC0(void) {
    u8 *temp_v1 = D_800D154C;
    u8 *temp_v0 = *(u8 **)(temp_v1 + 0x2D0);

    if (*(f32 *)(temp_v0 + 0x10) < D_800D1874) {
        *(s16 *)(temp_v1 + 0x10C) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15072EC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072EC0.s")
void func_15072EF4(void) {
    D_800D154C[0x104] = (s8)D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072F10.s")
void func_1507304C(void) {
}
void func_15073054(void) {
    *(s16 *)(D_800D154C + 0x22E) = (s16)D_800D1580;
}

void func_15073070(void) {
}
void func_15073078(void) {
    func_1512D748(0, D_800D1580, 1);
}
void func_150730A4(void) {
    *(s8 *)((u8 *)D_800D154C + 0x1FF) = 3;
    *(s8 *)((u8 *)D_800D154C + 0x200) = (s8) D_800D1580;
}
void func_150730D0(void) {
    if (D_800D1580 == 1) {
        *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) | 0x100);
        return;
    }
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) & 0xFEFF);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073118.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507342C.s")
/* Call context: func_1505E650: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150738E8 CURRENT (1043) */
void func_150738E8(void) {
    u8 temp_v0;
    void *temp_v0_2;

    temp_v0 = *(u8 *)((u8 *)D_800D154C + 0x13C);
    if (temp_v0 != 0) {
        *(u8 *)((u8 *)D_800D154C + 0x13C) = 0U;
        temp_v0_2 = (((temp_v0 - 0x64) & 0xFF) * 0x32C) + &D_800CC2D0;
        *(s32 *)((u8 *)temp_v0_2 + 0xF8) = 0x8200;
        *(s8 *)((u8 *)temp_v0_2 + 0x13D) = 0;
        *(s8 *)((u8 *)temp_v0_2 + 0x65) = 0;
        *(s8 *)((u8 *)temp_v0_2 + 0x232) = 6;
        *(s32 *)((u8 *)temp_v0_2 + 0x218) = 0;
        *(s8 *)((u8 *)temp_v0_2 + 0x104) = 0;
        *(s16 *)((u8 *)temp_v0_2 + 0x7A) = 0xE000;
        *(u16 *)((u8 *)temp_v0_2 + 0x76) = (u16) *(u16 *)((u8 *)D_800D154C + 0x7A);
        func_1505E650(D_800D154C, 0x97, 0x3F800000, 0x40A00000, 0.0f, 0.0f, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150738E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150738E8.s")
void func_150739A4(void) {
    D_800D154C[0x64] = (s8)D_800D1580;
}
extern u8 D_800BE9A0;
extern f32 D_800D1878;
extern s32 D_800D1880;

void func_150739C0(void) {
    *(s8 *)((u8 *)D_800D154C + 0x64) = (s8) (*(s8 *)((u8 *)D_800D154C + 0x64) - D_800BE9A0);
    if (*(s8 *)((u8 *)D_800D154C + 0x64) >= 0) {
        D_800D1880 = 0;
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) - 1);
        D_800D1878 = (f32) D_800D1580;
    }
}
void func_15073A28(void) {
    *(f32 *)((u8 *)D_800D154C + 0x44) = (f32) D_800D1580;
}
/* Call context: func_1505D024: unique active project prototype */
void func_1505D024(s32, s32, s32, s32);
extern f32 D_8009A0D8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15073A50 CURRENT (645) */
void func_15073A50(void) {
    s32 sp20;
    s32 temp_v0;
    void *sp18;
    void *temp_a0;

    temp_a0 = (*(u8 *)((u8 *)D_800D154C + 0x124) * 0x32C) + &D_800CC2D0;
    if (*(u8 *)((u8 *)temp_a0 + 0x65) != 0) {
        temp_v0 = D_800D1580;
        *(s8 *)((u8 *)D_800D154C + 0x13C) = 0;
        *(s8 *)((u8 *)temp_a0 + 0x125) = 0;
        sp18 = temp_a0;
        sp20 = temp_v0;
        func_1505D024((s32) temp_a0, D_800D1580 & 0xFF00FF, 0, (s32) D_800C3E78);
        *(f32 *)((u8 *)temp_a0 + 0x1CC) = (f32) D_8009A0D8;
        if (temp_v0 & 0x40000000) {
            *(f32 *)((u8 *)temp_a0 + 0x1CC) = (f32) *(f32 *)((u8 *)D_800D154C + 0x18);
        }
        *(s8 *)((u8 *)temp_a0 + 0x125) = 0x14;
        *(s16 *)((u8 *)temp_a0 + 0x76) = (s16) (*(u16 *)((u8 *)D_800D154C + 0x7A) + temp_v0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15073A50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073B38.s")
void func_15073C28(void) {
    func_1507F640();
}
void func_15073C48(void) {
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15073C50 CURRENT (45) */
void func_15073C50(void) {
    *(s16 *)((u8 *)D_800D154C + 0x224) = (s16) (s32) (*(&D_800CC2E8 + (*(u8 *)((u8 *)D_800D154C + 0x222) * 0x32C)) + (f32) D_800D1580);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15073C50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073C50.s")
/* Call context: func_1505F0AC: unique active project prototype */
void * func_1505F0AC(u8);

void func_15073CB8(void) {
    void *temp_v0;

    temp_v0 = func_1505F0AC(0x53U);
    if ((temp_v0 != 0) && (*(u16 *)((u8 *)temp_v0 + 0x244) == 0x1F)) {
        *(s16 *)((u8 *)temp_v0 + 0x21C) = 0;
    }
}
/* Call context: func_15062B1C: unique active project prototype */
void func_15062B1C(void *, f32);

void func_15073CF4(void) {
    func_15062B1C(D_800D154C, (f32) D_800D1580);
}
/* Call context: func_15062B50: unique active project prototype */
void func_15062B50(void *, f32);

void func_15073D34(void) {
    func_15062B50(D_800D154C, (f32) D_800D1580);
}
void *func_15083E90(u8);                            /* extern */
extern u8 D_800D1583;

void func_15073D74(void) {
    void *temp_v0;

    temp_v0 = func_15083E90(D_800D1583);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x65) = 0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073DA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073E2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073EA4.s")
void *func_1503195C(u8 *arg0, s32 arg1, s32 arg2);

void func_15073F1C(void) {
    void *temp_v0;

    temp_v0 = func_1503195C(D_800D154C, 0x3C, 0);
    if (temp_v0 != 0) {
        *(s32 *)((u8 *)temp_v0 + 0x38) = 0x960;
    }
}
void func_15073F54(void) {
}
void func_15073F5C(void) {
    D_800D154C[0x2CB] = (s8)D_800D1580;
}
void func_15073F78(void) {
    *(u8 *)((u8 *)D_800D154C + 0x10B) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x10B) & ~D_800D1580);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073FA0.s")
typedef struct Game981E0NestedState {
    u8 pad0[0x11A];
    s8 field_11A;
} Game981E0NestedState;

void func_15074644(void) {
    (*(Game981E0NestedState **)(D_800D154C + 0x31C))->field_11A = (s8)D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074664.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150746F0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150747E4 CURRENT (585) */
void func_150747E4(void) {
    u8 temp_v0;
    void *temp_a0;

    temp_v0 = *(u8 *)((u8 *)D_800D154C + 0x65);
    if (temp_v0 != 0) {
        temp_a0 = ((temp_v0 - 1) * 0x32C) + &D_800CC2D0;
        *(s32 *)((u8 *)temp_a0 + 0x218) = 0;
        *(s8 *)((u8 *)temp_a0 + 0x232) = (s8) D_800D1580;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150747E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150747E4.s")
void func_15074840(void) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
    if (temp_v0 != 0) {
        *(s16 *)((u8 *)temp_v0 + 0x1AA) = (s16) (*(s16 *)((u8 *)temp_v0 + 0x1AA) + D_800D1580);
    }
}
void func_15074870(void) {
    D_800D154C[0x24F] = (s8)D_800D1580;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507488C CURRENT (570) */
void func_1507488C(void) {
    s32 temp_t8;
    s32 var_a1;

    temp_t8 = D_800D1580 & 1;
    var_a1 = temp_t8;
    if (*(s32 *)((u8 *)(D_800D154C + ((((s32) D_800D1580 >> 0x10) & 0xFF) * 4)) + 0x2E4) & (((s32) D_800D1580 >> 8) & 0xFF)) {
        var_a1 = (temp_t8 ^ 1) & 0xFF;
    }
    if (var_a1 != 0) {
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) + ((s32) D_800D1580 >> 0x18));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507488C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507488C.s")
extern s8 D_800CC3D7;

void func_150748F4(void) {
    D_800CC3D7 = (s8)D_800D1580;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507490C CURRENT (610) */
void func_1507490C(void) {
    u8 temp_v1;
    void *temp_v1_2;

    temp_v1 = *(u8 *)((u8 *)D_800D154C + 0x13C);
    if (temp_v1 != 0) {
        temp_v1_2 = (((temp_v1 - 0x64) & 0xFF) * 0x32C) + &D_800CC2D0;
        if ((s32) *(u8 *)((u8 *)temp_v1_2 + 0x13D) >= 0x64) {
            *(s32 *)((u8 *)temp_v1_2 + 0x218) = 0;
            *(s8 *)((u8 *)temp_v1_2 + 0x104) = 0;
            *(s8 *)((u8 *)temp_v1_2 + 0x232) = (s8) D_800D1580;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507490C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507490C.s")
f32 func_1505A72C(u8 *, s32 *);                     /* extern */
extern s8 D_8008FD8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15074980 CURRENT (35) */
void func_15074980(void) {
    f32 temp_fs0;
    s32 *var_s0;
    s32 var_s1;
    void *temp_v0;

    var_s1 = 0;
    temp_fs0 = (f32) (D_800D1580 * 8);
    if (D_8008FD8C > 0) {
        var_s0 = &D_800CC2D0;
        do {
            if (func_1505A72C(D_800D154C, var_s0) < temp_fs0) {
                temp_v0 = *(void **)((u8 *)var_s0 + 0x31C);
                if (temp_v0 != 0) {
                    *(s8 *)((u8 *)temp_v0 + 0x4B) = 0x14;
                }
            }
            var_s1 += 1;
            var_s0 += 0x32C;
        } while (var_s1 < D_8008FD8C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15074980 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074980.s")
void func_15074A44(void) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x26) = (s8) D_800D1580;
    }
}
void func_15074A6C(void) {
    if (*(u8 *)((u8 *)D_800D154C + 0x13C) == 0) {
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) + 1);
    }
}
extern f32 D_8009A0E8;
extern f32 D_8009A0EC;
extern f32 D_8009A0F0;
extern f32 D_8009A0F4;
extern f32 D_8009A0F8;
extern f32 D_8009A0FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15074A94 CURRENT (95) */
void func_15074A94(void) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_fv1;

    temp_fv0 = func_1505A72C((u8 *) &D_800CC2D0, (s32 *) D_800D154C);
    if (*(f32 *)((u8 *)D_800D154C + 0x148) < D_8009A0E8) {
        *(f32 *)((u8 *)D_800D154C + 0x148) = (f32) *(f32 *)((u8 *)D_800D154C + 0x154);
    }
    if (temp_fv0 < 200.0f) {
        var_fv1 = D_8009A0EC;
    } else {
        temp_fa1 = *(f32 *)((u8 *)D_800D154C + 0x148);
        if (D_8009A0F0 < temp_fv0) {
            var_fv1 = temp_fa1;
        } else {
            var_fv1 = (((temp_fv0 - 200.0f) / D_8009A0F8) * (temp_fa1 - D_8009A0F4)) + D_8009A0F4;
        }
    }
    *(f32 *)((u8 *)D_800D154C + 0x158) = var_fv1;
    *(f32 *)((u8 *)D_800D154C + 0x154) = (f32) *(f32 *)((u8 *)D_800D154C + 0x158);
    *(f32 *)((u8 *)D_800D154C + 0x15C) = (f32) D_8009A0FC;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15074A94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074A94.s")
extern f32 D_8009A100;
extern f32 D_800D1878;
extern s32 D_800D1880;

void func_15074B7C(void) {
    D_800D1880 = 0;
    D_800D1878 = (f32) D_800D1580;
    if (D_800D1580 == 0) {
        D_800D1878 = D_8009A100;
        *(u8 *)((u8 *)D_800D154C + 0x1FC) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x1FC) | 4);
        *(s8 *)((u8 *)D_800D154C + 0x138) = 0;
    }
}
void func_15074BD8(s32 arg0, s32 arg1, s32 arg2) {
}
void func_15074BEC(s32 arg0, s32 arg1, s32 arg2) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074C00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074C80.s")
void func_15074DEC(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x2E8) = 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074E04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074E80.s")
extern void func_15072740(void);

void func_15074EE8(u8 *arg0, u8 *arg1, s32 arg2) {
    if (*(s32 *)arg1 == 1) {
        arg0[0x125] = 0xFF;
        arg1[0x125] = 0xC8;
        D_800D1580 = 0x70000;
        func_15072740();
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15074F30 CURRENT (10) */
void func_15074F30(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 value = arg1[0x109];

    *(s32 *)(arg0 + 0x218) = 0;
    arg0[0x232] = value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15074F30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074F30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074F48.s")
/* Call context: func_15072740: unique active project prototype */
/* Call context: func_151942B0: unique active project prototype */
void func_151942B0(s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15074FD4 CURRENT (10) */
void func_15074FD4(void *arg0, void *arg1, s32 arg2) {
    if (*(s32 *)((u8 *)arg1 + 0) == 1) {
        *(s8 *)((u8 *)arg0 + 0x125) = 0xFF;
        *(s8 *)((u8 *)arg1 + 0x125) = 0xC8;
        D_800D1580 = 0x60000;
        if (*(u8 *)((u8 *)arg0 + 4) == 0x8E) {
            D_800D1580 = 0x140000;
        }
        func_15072740();
    }
    func_151942B0((s32) arg0, (s32) arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15074FD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074FD4.s")
void func_15075050(void *arg0, s32 arg1, s32 arg2) {
    *(f32 *)((u8 *)arg0 + 0xB8) = 5.0f;
    if (*(f32 *)((u8 *)arg0 + 0x3C) > 0.0f) {
        *(f32 *)((u8 *)arg0 + 0xB8) = -5.0f;
    }
    *(f32 *)((u8 *)arg0 + 0x24) = 5.0f;
    *(f32 *)((u8 *)arg0 + 0x20) = 12.0f;
}
void func_150750A4(f32 *arg0, s32 arg1, s32 arg2) {
    arg0[9] = 5.0f;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150750C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507515C.s")
