#include "types.h"

/*
 * Reviewed source unit: src/game/game_981E0.c
 * Boundary evidence: docs/evidence/game_dispatcher_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1506AD30
 * - func_1506AF74
 * - func_1506AFE0
 * - func_1506B020
 * - func_1506B078
 * - func_1506B100
 * - func_1506B14C
 * - func_1506B198
 * - func_1506B1E8
 * - func_1506B228
 * - func_1506B268
 * - func_1506B2BC
 * - func_1506B328
 * - func_1506B370
 * - func_1506B3B8
 * - func_1506B520
 * - func_1506B5E4
 * - func_1506B634
 * - func_1506B740
 * - func_1506B7F4
 * - func_1506B82C
 * - func_1506B860
 * - func_1506B88C
 * - func_1506B8B4
 * - func_1506B8F4
 * - func_1506B91C
 * - func_1506B944
 * - func_1506B984
 * - func_1506B9C0
 * - func_1506BA4C
 * - func_1506BAD8
 * - func_1506BB64
 * - func_1506BBA8
 * - func_1506BC24
 * - func_1506BCC8
 * - func_1506BF1C
 * - func_1506BF5C
 * - func_1506C32C
 * - func_1506C460
 * - func_1506CE6C
 * - func_1506D2E8
 * - func_1506D4F4
 * - func_1506D538
 * - func_1506D584
 * - func_1506D6B4
 * - func_1506D74C
 * - func_1506D898
 * - func_1506D958
 * - func_1506DA94
 * - func_1506DBA0
 * - func_1506DBD4
 * - func_1506DC10
 * - func_1506DD00
 * - func_1506DD6C
 * - func_1506DDC0
 * - func_1506DE04
 * - func_1506DE84
 * - func_1506E0EC
 * - func_1506E2CC
 * - func_1506E46C
 * - func_1506E5FC
 * - func_1506E63C
 * - func_1506E67C
 * - func_1506E6BC
 * - func_1506E6FC
 * - func_1506E73C
 * - func_1506E77C
 * - func_1506E7BC
 * - func_1506E7FC
 * - func_1506E848
 * - func_1506E898
 * - func_1506E8D8
 * - func_1506E918
 * - func_1506E958
 * - func_1506E998
 * - func_1506E9D8
 * - func_1506EA18
 * - func_1506EA58
 * - func_1506EA98
 * - func_1506EBC0
 * - func_1506EC50
 * - func_1506ED0C
 * - func_1506ED68
 * - func_1506EE60
 * - func_1506EEAC
 * - func_1506EEF4
 * - func_1506EF5C
 * - func_1506EFC8
 * - func_1506F004
 * - func_1506F02C
 * - func_1506F05C
 * - func_1506F090
 * - func_1506F0C4
 * - func_1506F0F0
 * - func_1506F11C
 * - func_1506F14C
 * - func_1506F17C
 * - func_1506F1A8
 * - func_1506F524
 * - func_1506F54C
 * - func_1506F8C0
 * - func_1506F8F0
 * - func_1506F9C0
 * - func_1506FA90
 * - func_1506FB60
 * - func_1506FBE8
 * - func_1506FC1C
 * - func_1506FC74
 * - func_1506FC9C
 * - func_1506FCC8
 * - func_1506FCFC
 * - func_1506FD30
 * - func_1506FDF0
 * - func_1506FE1C
 * - func_1506FE48
 * - func_1506FE74
 * - func_1506FEA0
 * - func_1506FECC
 * - func_1506FEF8
 * - func_1506FF24
 * - func_1506FF50
 * - func_1506FF78
 * - func_1506FFAC
 * - func_1506FFE0
 * - func_15070014
 * - func_1507003C
 * - func_15070084
 * - func_150700B4
 * - func_150700E4
 * - func_15070114
 * - func_15070144
 * - func_150701C4
 * - func_150701F4
 * - func_15070224
 * - func_15070300
 * - func_15070690
 * - func_150706C4
 * - func_150706F8
 * - func_15070760
 * - func_15070794
 * - func_150707C8
 * - func_150707F8
 * - func_15070830
 * - func_15070860
 * - func_15070898
 * - func_15070C18
 * - func_15070C40
 * - func_15070D24
 * - func_15070F60
 * - func_15071278
 * - func_150712AC
 * - func_15071360
 * - func_15071434
 * - func_15071470
 * - func_150714AC
 * - func_150714E8
 * - func_15071544
 * - func_1507158C
 * - func_150715D4
 * - func_15071628
 * - func_15071668
 * - func_15071690
 * - func_150716EC
 * - func_15071764
 * - func_150717E0
 * - func_15071830
 * - func_15071860
 * - func_15071888
 * - func_150718E4
 * - func_15071998
 * - func_150719CC
 * - func_15071A00
 * - func_15071A34
 * - func_15071A64
 * - func_15071B18
 * - func_15071D08
 * - func_15071D38
 * - func_15071D78
 * - func_15071DC8
 * - func_15071DF4
 * - func_15071E58
 * - func_15071ED4
 * - func_15071F14
 * - func_15071F54
 * - func_15071FDC
 * - func_150721A4
 * - func_15072208
 * - func_150722F0
 * - func_150723AC
 * - func_150723E0
 * - func_15072420
 * - func_1507266C
 * - func_15072740
 * - func_150727AC
 * - func_150727F0
 * - func_15072918
 * - func_15072940
 * - func_15072968
 * - func_150729D0
 * - func_15072A14
 * - func_15072A40
 * - func_15072A7C
 * - func_15072AF8
 * - func_15072B44
 * - func_15072DD8
 * - func_15072E38
 * - func_15072E98
 * - func_15072EC0
 * - func_15072F10
 * - func_15073078
 * - func_15073118
 * - func_1507342C
 * - func_150738E8
 * - func_150739C0
 * - func_15073A50
 * - func_15073B38
 * - func_15073C50
 * - func_15073CB8
 * - func_15073CF4
 * - func_15073D34
 * - func_15073D74
 * - func_15073DA4
 * - func_15073E2C
 * - func_15073EA4
 * - func_15073F1C
 * - func_15073FA0
 * - func_15074664
 * - func_150746F0
 * - func_150747E4
 * - func_15074840
 * - func_1507488C
 * - func_1507490C
 * - func_15074980
 * - func_15074A44
 * - func_15074A94
 * - func_15074C00
 * - func_15074C80
 * - func_15074E04
 * - func_15074E80
 * - func_15074EE8
 * - func_15074F30
 * - func_15074F48
 * - func_15074FD4
 * - func_150750C4
 * - func_1507515C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AD30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AF74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AFE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B020.s")
void func_1506B070(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B078.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B100.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B14C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B198.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B1E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B228.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B268.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B2BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B328.s")
void func_1506B368(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B370.s")
void func_1506B3B0(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B3B8.s")
void func_1506B4EC(void) {
    func_1506B3B8();
}
extern u8 *D_800D154C;
extern s32 D_800D1580;

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B5E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B634.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B7F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B82C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B860.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B88C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B8B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B8F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B91C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B944.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B984.s")
void func_1506B9AC(void) {
    *(s16 *)(D_800D154C + 0x244) = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B9C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BA4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BAD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BB64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BBA8.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BF1C.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D4F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D538.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DBD4.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DD00.s")
void func_1506DD44(void) {
    *(s32 *)((u8 *)D_800D154C + 0xF8) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF8) & ~D_800D1580);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DD6C.s")
void func_1506DDB8(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DDC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DE04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DE84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E0EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E2CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E46C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E5FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E63C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E67C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E6BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E6FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E73C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E77C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E7BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E7FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E848.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E898.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E8D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E958.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E998.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E9D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EA18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EA58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EA98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EBC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EC50.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506ED0C.s")
void func_1506ED4C(void) {
    D_800D154C[0x100] = (s8)D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506ED68.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EE60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EEAC.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EF5C.s")
void func_1506EFB4(void) {
    *(s16 *)(D_800D154C + 0x282) = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EFC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F004.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F02C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F05C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F090.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F0C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F0F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F11C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F14C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F17C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F1A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F524.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F54C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F8C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F8F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F9C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FA90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FB60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FBE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FC1C.s")
void func_1506FC50(s32 arg0) {
    func_1519E688();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FC74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FC9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FCC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FCFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FD30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FDF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FE1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FE48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FE74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FEA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FECC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FEF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FF24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FF50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FF78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FFAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FFE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070014.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507003C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070084.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150700B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150700E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070114.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070144.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150701C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150701F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070224.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070300.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150706C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150706F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070760.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070794.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150707C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150707F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070830.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070860.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070898.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070C18.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071278.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150712AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071434.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071470.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150714AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150714E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071544.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507158C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150715D4.s")
void func_1507161C(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071628.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071668.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150716EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071764.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150717E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071830.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071860.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071888.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150718E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071998.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150719CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071A00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071A34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071A64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071B18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071D08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071D38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071D78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071DC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071DF4.s")
void func_15071E20(void) {
    D_800D154C[0x247] = (s8)D_800D1580;
}
void func_15071E3C(void) {
    D_800D154C[0x248] = (s8)D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071E58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071ED4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071F14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071F54.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071FDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150721A4.s")
void func_15072208(void *arg0, s32 arg1);

void func_150721E8(void *arg0) {
    func_15072208(arg0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072208.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150723AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150723E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072420.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507266C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150727AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150727F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072940.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072968.s")
void func_150729B4(void) {
    *(s32 *)(D_800D154C + 0x2E4) = D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150729D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072A14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072A40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072A7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072AF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072B44.s")
void func_15072DA0(void) {
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) & 0xFFF8);
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) | D_800D1580);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072DD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072E38.s")
void func_15072E7C(void) {
    *(s16 *)(D_800D154C + 0x10C) = (s16)D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072E98.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073078.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150738E8.s")
void func_150739A4(void) {
    D_800D154C[0x64] = (s8)D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150739C0.s")
void func_15073A28(void) {
    *(f32 *)((u8 *)D_800D154C + 0x44) = (f32) D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073B38.s")
void func_15073C28(void) {
    func_1507F640();
}
void func_15073C48(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073C50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073CB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073CF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073D34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073D74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073DA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073E2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073EA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073F1C.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150747E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074840.s")
void func_15074870(void) {
    D_800D154C[0x24F] = (s8)D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507488C.s")
extern s8 D_800CC3D7;

void func_150748F4(void) {
    D_800CC3D7 = (s8)D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507490C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074980.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074A44.s")
void func_15074A6C(void) {
    if (*(u8 *)((u8 *)D_800D154C + 0x13C) == 0) {
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) + 1);
    }
}
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074EE8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15074F30 CURRENT (10) */
void func_15074F30(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 value = arg1[0x109];

    *(s32 *)(arg0 + 0x218) = 0;
    arg0[0x232] = value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15074F30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074F30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074F48.s")
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
