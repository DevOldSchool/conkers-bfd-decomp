#include "types.h"
#include "game_functions.h"
#include "game_view.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_34F20.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_early_callback_state_groups.md
 */

void func_15000090(void);
void func_15005270(void);
void func_15008230(void);
void func_15015F40(s16, s32);
void func_15017300(s16, s16);
void func_150175E0(void);
void func_150177F8(void);
void func_1503FB08(void);
void func_15089BB0(void);
extern u8 D_800BE938;
extern u8 D_800D18A8;
extern s32 D_800D2138;
extern u8 D_800DD2C0;

void func_15007A70(s16 arg0, s16 arg1, s16 arg2) {
    D_800BE9B4 = 2;
    func_1503FB08();
    D_800BE9F0 = D_800BE9F4 = arg2;
    func_15172C50(D_800DD2C0);
    func_15008230();
    func_15005270();
    func_15017300(arg0, arg1);
    func_15015F40(D_80087280[D_800D2138], arg2);
    func_150175E0();
    func_150177F8();
    func_15089BB0();
    func_15000090();
    D_800BE938 = 1;
    D_800D18A8 = 0;
    D_800BE9ED = 0;
}
void func_150006E0(s32);
void func_15000AC0(void);
void func_15002F40(s32);
void func_15002FB4(s32);
void func_15003668(s32);
void func_150038A0(void);
void func_150039B0(s32);
void func_15004574(void);
void func_15004D50(void);
void func_15004E00(void);
void func_15004E80(void);
void func_15004F00(void);
void func_15004F10(void);
void func_150081E4(void);
void func_15008248(s32);
void func_150082CC(void);
void func_15008840(void);
void func_15008870(s32);
void func_15008930(s32);
void func_15008A60(void);
void func_15008DD0(void);
void func_15009150(s32);
void func_150091D0(void);
void func_150092DC(void);
void func_1500BE68(void);
void func_1500C2A0(void);
void func_1500E470(s32);
void func_1500E70C(s32);
void func_1500E738(void);
void func_15012780(void);
void func_15012F90(void);
void func_15013000(void);
void func_15015910(void);
void func_15015E80(void);
void func_150162B0(void);
void func_15016370(void);
void func_150163D0(s32);
void func_15016500(void);
void func_15016670(void);
void func_15016690(s32);
void func_1501748C(s16);
void func_15017578(s32);
void func_15017640(void);
void func_15017868(void);
void func_1501A220(s32, s32);
void func_1501B640(s32);
void func_1501BB20(void);
void func_1501C53C(void);
void func_1501CC3C(void);
void func_1502AAF0(void);
void func_1502AAF8(s32);
void func_15044370(void);
void func_1507DFE4(s32, s32);
s32 func_1507E114(s32);
void func_15080200(void);
void func_15085B70(void *);
void func_1509BBA0(s32);
s32 func_1509C2A4(void);
void func_1509C3A0(void);
void func_1510B070(s32);
void func_1511F980(void);
void func_15125690(void *, s32);
void func_151732E0(s32);
void func_15181E18(s32);
void func_15187F90(void);
void func_151BF340(s32, s32);
void func_151D8DE8(void);
void func_151E562C(void);
s8 func_151E5FAC(void);
void func_100014C4(s32);
void func_10003ACC(s32, s32, s32);
void func_10004308(void);
void func_1000F248(s32);
void func_10011FEC(void);
void func_100125CC(s32);
void func_150000B0(void);
void func_15000AD0(s32);
void func_150031EC(s32);
void func_150039E0(s32, s32);
void func_150045C4(s32);
void func_15005290(s32, s32);
void func_1500C1E0(void);
void func_150169A0(s32);
void func_15017930(s32);
void func_15085710(s32, s32, s32);
void func_150A11C4(void *);
void func_151E81EC(void);
extern void *D_800B0DF0;
extern u8 D_800BE3E0;
extern s8 D_800BE619;
extern s8 D_800BE61A;
extern u8 D_800BEA0C;
typedef struct Game34F20Actor {
    s32 field_0;
    u8 pad4[0x123];
    u8 field_127;
    u8 pad128[0x204];
} Game34F20Actor;

extern Game34F20Actor D_800CC2D0[];
extern u8 D_800D121C[];
extern u16 D_800D2340;
extern s8 D_800D2E43;
extern void *D_800D2E4C;
extern u8 D_800DDE38;
extern s32 D_800E0920;
extern u8 D_800E0A00;
extern u8 D_800E0B94;
extern u8 D_800E0B99;
extern u8 D_800C35EA;

void func_15007B3C(void) {
    s32 i;
    s32 resource;
    s32 slot;
    s32 value;
    s32 j;
    s32 count;

    if (D_800BE9B4 == 0) {
        D_800BE9B4 = 1;
    }
    func_10004308();
    func_15002FB4(D_800BE9F4);
    switch (D_800BE9F4) {
    case 0x1A:
    case 0x24:
    case 0x2B:
    case 0x2D:
    case 0x30:
    case 0x33:
    case 0x34:
    case 0x3F:
        value = 0x103;
        if (D_800BE9F4 == 0x24) {
            value = 0xF3;
        }
        if (D_800BE9F4 == 0x33) {
            value -= 8;
        }
        if (D_800BE9F4 == 0x3F) {
            value -= 8;
        }
        if (D_800BE9F4 == 0x34) {
            value += 8;
        }
        break;
    case 0x13:
        value = 0xEB;
        if (!(*((u8 *)D_800D2E4C + 0x11) & 4)) {
            value = *((s8 *)D_800B0DF0 + 0x11) + 0xEB;
        }
        break;
    default:
        value = *((s8 *)D_800B0DF0 + 0x11) + 0xEB;
        break;
    }
    func_100014C4(value);
    D_800E0A00 = 0;
    func_1500E738();
    func_1500C2A0();
    D_800DC9F0 = 0;
    D_800E0920 = 0;
    func_15008840();
    D_8003E384 = 1;
    resource = D_800DD2C0;
    slot = func_1507E114((s32)&resource);
    if (D_800E0B94 == 2) {
        resource = D_800E0BD1;
    }
    D_800BE9F8 = D_800BE9F0;
    D_800BE9F0 = D_800BE9F4;
    func_150091D0();
    func_15187F90();
    D_800BE619 = 0;
    D_800BE61A = 0;
    D_800BEA0C = 0;
    func_150081E4();
    if (D_800BE9ED != 0) {
        func_10003ACC(0xFF, 0xFF, 0xFF);
        D_800BE9ED = 0;
    } else {
        func_10003ACC(0, 0, 0);
    }
    if ((D_800BE616 == 0) && !(*((u8 *)D_800D2E4C + 0x18) & 1)) {
        D_800D2457 = D_800D2456 = 3;
        func_15085710(0, 5, 3);
    }
    func_15002F40(D_800BE9F0);
    func_1501C53C();
    func_15015E80();
    func_150162B0();
    func_15017930(D_800BE9F0);
    func_15016500();
    func_1501A220(D_800BE9E8, 1);
    func_15012F90();
    func_15008A60();
    func_15000AC0();
    func_15012780();
    func_1500BE68();
    func_15044370();
    func_15016670();
    func_15004F00();
    func_15004E80();
    func_15017868();
    func_151732E0(D_800BE9F0);
    func_1502AAF0();
    func_1502AAF8(D_800BE9F0);
    func_150031EC(D_800BE9F0);
    func_150039E0(D_800BE9F0, 1);
    func_15004574();
    func_1511F980();
    func_15003668(D_800BE9F0);
    func_150038A0();
    func_150039B0(D_800BE9F0);
    func_15017578(D_800BE9F0);
    func_150045C4(D_800BE9F0);
    func_15008248(D_800BE9F0);
    func_150000B0();
    func_1000F248(D_800BE9F0);
    func_100125CC(D_800BE9F0);
    func_10011FEC();
    func_1501BB20();
    func_15008870(1);
    func_15008930(1);
    func_15016690(D_800BE9F0);
    func_150169A0(D_800BE9F0);
    func_15005290(D_800BE9F0, resource);
    func_15016370();
    func_150006E0(D_800BE9F0);
    func_1510B070(0);
    for (i = 0; i <= D_80082FA0; i++) {
        func_15125690(&D_800DBFF0[i], 1);
    }
    func_1500E70C(D_800BE9F0);
    func_150163D0(D_800BE9F0);
    func_150092DC();
    func_15000AD0(D_800BE9F0);
    if (D_800BE9F0 == 0x1D) {
        func_151E81EC();
    }
    func_1500E470(D_800BE9F0);
    func_15009150(D_800BE9F0);
    func_15085B70((void *)D_800BE9F0);
    func_15008DD0();
    func_1501B640(0);
    func_15080200();
    D_800BE9E4 = 2;
    func_15015910();
    func_15004F10();
    func_1501748C(D_800D2340);
    func_1500C1E0();
    func_15004E00();
    func_15004D50();
    func_150082CC();
    if (D_800BE616 == 0) {
        func_15085710(0, 9, D_800BE3E4);
    }
    if (func_1509C2A4() != 0) {
        D_800BE3E0 = resource & 0xFF;
    }
    D_800D2E43 = 1;
    func_1509BBA0(4);
    func_1509BBA0(1);
    func_15013000();
    if (slot != 0) {
        func_1507DFE4(resource, slot - 1);
    }
    func_151E562C();
    if ((D_800E0B99 != 0) || (D_800DDE38 == 2)) {
        u32 enabled = 1;

        if ((D_800C35EA == 1U) || (D_800DDE38 == 1U)) {
            enabled = 0;
        }
        if (enabled) {
            count = func_151E5FAC();
            for (j = 0; j < count; j++) {
                func_15181E18(j);
            }
        }
        D_800E0B99 = 0;
    }
    func_15017640();
    func_1501CC3C();
    for (i = 0; i < 25; i++) {
        if ((D_800CC2D0[i].field_0 != 0) && (D_800CC2D0[i].field_127 != 0xFF)) {
            func_150A11C4(&D_800CC2D0[i]);
        }
    }
    if ((D_800D18A8 != 0) && (D_800BE9F0 != 0x22)) {
        D_800D18A8 = 0;
        func_151BF340(0xFF, 1);
    }
    func_1509C3A0();
    D_800BE9F4 = D_800BE9F0;
    func_151D8DE8();
}
extern s32 D_800CBE00;
extern s32 D_800D245C;
extern s32 D_800D3668;
extern s32 D_800DDD64;
extern s32 D_800DF7C8;
extern s32 D_800DF7D0;

void func_150081E4(void) {
    s32 i;

    D_800D3668 = 0;
    D_800CBE00 = 0;
    D_800DDD64 = 0;
    for (i = 0; i < 2; i++) {
        (&D_800DF7C8)[i] = 0;
    }
    D_800D245C = 0;
    D_800D2548 = 0;
}
extern s8 D_800C3C88;

void func_15008230(void) {
    D_800C35C4 = 0;
    D_800C3C88 = 0;
}
extern u8 D_800C3638;
extern u8 D_800C3670;
extern u8 D_800C3671;
extern u8 D_800C3681;
extern u8 D_800C3682;
typedef struct Game34F20Slot {
    s16 field_0;
    u8 pad2[0xA];
    s8 field_C;
    u8 padD[0x2B];
} Game34F20Slot;

extern Game34F20Slot D_800C3CA0[];
extern Game34F20Slot D_800C3D48[];
void func_1501D044(s32);

void func_15008248(s32 arg0) {
    s32 i;

    D_800C3638 = 0;
    D_800C3671 = 0;
    D_800C3670 = 0;
    func_1501D044(0);
    func_1501D044(1);
    D_800C3663 = 0;
    for (i = 0; i < 3; i++) {
        D_800C3CA0[i].field_0 = 0;
        D_800C3CA0[i].field_C = 0;
    }
    D_800C3681 = 0;
    D_800C3682 = 0;
    D_800C3683 = 0;
}

void func_1501D348(s32, s32, s32, u8, s32);

void func_150082CC(void) {
    s32 index = D_800C35C4 - 1;

    if (D_800C35C4 != 0) {
        if (D_800C35C5 == 0) {
            D_800C35EA = 2;
        }
        D_800C35C4 = 0;
        func_1501D348(D_800BE9F0, index, 0, D_800C3C90, D_800C3C94);
    }
}
