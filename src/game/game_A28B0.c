#include "types.h"

/*
 * Reviewed source unit: src/game/game_A28B0.c
 * Boundary evidence: docs/evidence/game_dispatcher_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15075400
 * - func_15075498
 * - func_15075548
 * - func_15075650
 * - func_15075884
 * - func_15075938
 * - func_15075A50
 * - func_15075AAC
 * - func_15075B60
 * - func_15075B8C
 * - func_15075BB8
 * - func_15075BE8
 * - func_15075C24
 * - func_15075CA0
 * - func_15075CCC
 * - func_15075D0C
 * - func_15075D38
 * - func_15075D64
 * - func_15075D9C
 * - func_15075DE8
 * - func_15075E6C
 * - func_15075EB4
 * - func_15075F00
 * - func_15075F40
 * - func_15075F6C
 * - func_1507602C
 * - func_150761C8
 * - func_150761F4
 * - func_15076220
 * - func_15076250
 * - func_150762B0
 * - func_150762D4
 * - func_15076340
 * - func_150763B0
 * - func_15076500
 * - func_1507652C
 * - func_1507659C
 * - func_15076624
 * - func_15076678
 * - func_150766D0
 * - func_15076768
 * - func_150767F4
 * - func_150768DC
 * - func_15076B94
 * - func_15076C7C
 * - func_15076CCC
 * - func_15076D04
 * - func_15076D3C
 * - func_15076E10
 * - func_15076E50
 * - func_15076F40
 * - func_15076F78
 * - func_15076FA8
 * - func_150770E4
 * - func_15077190
 * - func_150771F0
 * - func_15077294
 * - func_150772E8
 * - func_15077318
 * - func_15077364
 * - func_15077404
 * - func_150774B4
 * - func_15077508
 * - func_150778F0
 * - func_150779A8
 * - func_150779D4
 * - func_15077ABC
 * - func_15077B14
 * - func_15077B44
 * - func_15077B80
 * - func_15077BB4
 * - func_15077BE4
 * - func_15077C38
 * - func_15077DBC
 * - func_15077E9C
 * - func_15077F08
 * - func_15077F34
 * - func_15077F64
 * - func_15078074
 * - func_1507813C
 * - func_150781A4
 * - func_150781F4
 * - func_150782E8
 * - func_15078358
 * - func_1507839C
 * - func_15078520
 * - func_15078544
 * - func_1507879C
 * - func_15078890
 * - func_15078900
 * - func_15078A08
 * - func_15078A60
 * - func_1507900C
 * - func_1507903C
 * - func_15079090
 * - func_150790C4
 * - func_1507911C
 * - func_150791F0
 * - func_15079228
 * - func_150792FC
 * - func_15079334
 * - func_15079390
 * - func_150793D8
 * - func_15079570
 * - func_1507965C
 * - func_150796CC
 * - func_15079790
 * - func_15079880
 * - func_150798F8
 * - func_15079928
 * - func_15079988
 * - func_150799B4
 * - func_15079A28
 * - func_15079A58
 * - func_15079A98
 * - func_15079B30
 * - func_15079F24
 * - func_15079F6C
 * - func_15079FBC
 * - func_1507A100
 * - func_1507A164
 * - func_1507A210
 * - func_1507A270
 * - func_1507A2A4
 * - func_1507A2F8
 * - func_1507A3E8
 * - func_1507A428
 * - func_1507A47C
 * - func_1507A4D4
 * - func_1507A528
 * - func_1507A620
 * - func_1507A71C
 * - func_1507A774
 * - func_1507A7DC
 * - func_1507A808
 * - func_1507A838
 * - func_1507A878
 * - func_1507A8A8
 * - func_1507A8EC
 * - func_1507A984
 * - func_1507AA48
 * - func_1507ACB0
 * - func_1507ACE0
 * - func_1507AD30
 * - func_1507AD7C
 * - func_1507ADAC
 * - func_1507ADE0
 * - func_1507AE94
 * - func_1507AF3C
 * - func_1507AF98
 * - func_1507B058
 * - func_1507B178
 * - func_1507B234
 * - func_1507B280
 * - func_1507B2CC
 * - func_1507B318
 * - func_1507B364
 * - func_1507B3B0
 * - func_1507B3FC
 * - func_1507B448
 * - func_1507B494
 * - func_1507B4E0
 * - func_1507B52C
 * - func_1507B578
 * - func_1507B5C4
 * - func_1507B630
 * - func_1507B6E0
 * - func_1507B734
 * - func_1507B7BC
 * - func_1507B7E8
 * - func_1507B884
 * - func_1507B8F4
 * - func_1507B974
 * - func_1507BA48
 * - func_1507BAD0
 * - func_1507BAF8
 * - func_1507BB28
 * - func_1507BC14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameA28B0State {
    s32 field_0;
    u8 pad4;
    u8 field_5;
    u8 pad6[0x70];
    u16 field_76;
    u16 field_78;
    u16 field_7A;
    u8 pad7C[0xD];
    u8 field_89;
    u8 field_8A;
    u8 pad8B[0x1D];
    u8 field_A8;
    u8 padA9[7];
    u8 field_B0;
    u8 padB1[0x5D];
    u8 field_10E;
    u8 pad10F[0xD5];
    u8 field_1E4;
    u8 pad1E5[0x39];
    u8 field_21E;
    u8 pad21F[3];
    u8 field_222;
    u8 pad223[6];
    u8 field_229;
    u8 pad22A[8];
    u8 field_232;
    u8 pad233[2];
    u8 field_235;
    u8 field_236;
    u8 pad237;
    u8 field_238;
    u8 field_239;
    u8 pad23A;
    u8 field_23B;
    u8 pad23C;
    u8 field_23D;
    u8 field_23E;
    u8 pad23F[0xB];
    u8 field_24A;
    u8 pad24B[6];
    u8 field_251;
    u8 pad252[2];
    u8 field_254;
} GameA28B0State;

extern GameA28B0State *D_800D154C;
extern u8 D_800D1890;

#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075498.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075548.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075650.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075884.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075938.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075AAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075B60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075B8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075BB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075BE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075C24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075CA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075CCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075D0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075D38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075D64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075D9C.s")
void func_15075DC8(void) {
    func_15075CA0();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075DE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075E6C.s")
void func_15075E98(void) {
    D_800D154C->field_235 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075EB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075F00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075F40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075F6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507602C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150761C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150761F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076220.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076250.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150762B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150762D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076340.s")
void func_15076394(void) {
    D_800D154C->field_236 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150763B0.s")
void func_150764C8(void) {
    D_800D154C->field_238 = D_800D1890;
}
void func_150764E4(void) {
    D_800D154C->field_239 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076500.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507652C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507659C.s")
void func_15076600(void) {

}
void func_15076608(void) {
    D_800D154C->field_24A = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076624.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076678.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150766D0.s")
void func_15076760(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076768.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150767F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150768DC.s")
void func_15076B5C(void) {
    D_800D154C->field_222 = D_800D154C->field_A8 & 0x7F;
}
void func_15076B78(void) {
    D_800D154C->field_5 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076B94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076C7C.s")
void func_15076CB4(void) {
    D_800D154C->field_76 = D_800D154C->field_78;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076CCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076D04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076D3C.s")
void func_15076DF4(void) {
    D_800D154C->field_0 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076E10.s")
void func_15076E48(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076E50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076F40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076F78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076FA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150770E4.s")
void func_15077174(void) {
    D_800D154C->field_10E = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077190.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150771F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077294.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150772E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077318.s")
void func_1507735C(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077364.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077404.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150774B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077508.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150778F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150779A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150779D4.s")
void func_15077AA0(void) {
    D_800D154C->field_239 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077ABC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077B14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077B44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077B80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077BB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077BE4.s")
void func_15077C1C(void) {
    D_800D154C->field_23D = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077C38.s")
void func_15077DA0(void) {
    D_800D154C->field_21E = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077DBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077E9C.s")
void func_15077EEC(void) {
    D_800D154C->field_254 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077F08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077F34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077F64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078074.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507813C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150781A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150781F4.s")
void func_150782CC(void) {
    D_800D154C->field_23E = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150782E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078358.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507839C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078544.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507879C.s")
void func_15078874(void) {
    D_800D154C->field_251 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078890.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078900.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078A08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078A60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507900C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507903C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079090.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150790C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507911C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150791F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079228.s")
void func_150792E0(void) {
    D_800D154C->field_232 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150792FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079334.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079390.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150793D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079570.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507965C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150796CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079790.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079880.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150798F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079928.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079988.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150799B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079A28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079A58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079A98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079B30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079F24.s")
void func_15079F50(void) {
    D_800D154C->field_23B = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079F6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079FBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A100.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A164.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A210.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A270.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A2A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A2F8.s")
void func_1507A3B4(void) {
    D_800D154C->field_222 = D_800D154C->field_A8;
}
void func_1507A3CC(void) {
    D_800D154C->field_229 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A3E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A428.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A47C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A4D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A528.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A620.s")
typedef struct GameA28B0Entry {
    u16 field_0;
    u8 pad2[4];
} GameA28B0Entry;

extern GameA28B0Entry D_800BE748[];

u16 func_1507A6FC(s32 arg0) {
    return D_800BE748[arg0].field_0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A71C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A774.s")
void func_1507A7C0(void) {
    D_800D154C->field_89 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A7DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A808.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A838.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A878.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A8A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A8EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A984.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AA48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507ACB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507ACE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AD30.s")
void func_1507AD60(void) {
    D_800D154C->field_1E4 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AD7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507ADAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507ADE0.s")
void func_1507AE78(void) {
    D_800D154C->field_229 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AE94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AF3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AF98.s")
void func_1507B040(void) {
    D_800D154C->field_76 = D_800D154C->field_7A;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B058.s")
void func_1507B15C(void) {
    D_800D154C->field_8A = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B178.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B234.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B280.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B2CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B318.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B364.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B3B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B3FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B448.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B494.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B4E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B52C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B578.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B5C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B6E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B734.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B7BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B7E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B884.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B8F4.s")
void func_1507B958(void) {
    D_800D154C->field_B0 = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B974.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507BA48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507BAD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507BAF8.s")
void func_1507BB20(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507BB28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507BC14.s")
