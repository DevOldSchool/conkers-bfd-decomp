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
 * - func_15076250
 * - func_150762B0
 * - func_150762D4
 * - func_15076340
 * - func_150763B0
 * - func_1507652C
 * - func_15076624
 * - func_15076678
 * - func_15076768
 * - func_150767F4
 * - func_150768DC
 * - func_15076B94
 * - func_15076C7C
 * - func_15076CCC
 * - func_15076D04
 * - func_15076D3C
 * - func_15076E50
 * - func_15076F40
 * - func_15076F78
 * - func_15076FA8
 * - func_150770E4
 * - func_15077190
 * - func_150771F0
 * - func_150772E8
 * - func_15077364
 * - func_15077404
 * - func_150774B4
 * - func_15077508
 * - func_150778F0
 * - func_150779A8
 * - func_150779D4
 * - func_15077ABC
 * - func_15077B44
 * - func_15077B80
 * - func_15077BE4
 * - func_15077C38
 * - func_15077DBC
 * - func_15077E9C
 * - func_15077F64
 * - func_15078074
 * - func_1507813C
 * - func_150781A4
 * - func_150781F4
 * - func_150782E8
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
 * - func_15079228
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
 * - func_1507A838
 * - func_1507A878
 * - func_1507A8A8
 * - func_1507A8EC
 * - func_1507A984
 * - func_1507AA48
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
 * - func_1507B734
 * - func_1507B7BC
 * - func_1507B7E8
 * - func_1507B884
 * - func_1507B8F4
 * - func_1507B974
 * - func_1507BA48
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
extern u8 D_800D1893;

void func_15075BE8(void) {
    if (D_800D1893 != 0) {
        *(u16 *)((u8 *)D_800D154C + 0x22C) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x22C) | 0x80);
    }
    D_800D154C->pad233[0] = D_800D1890;
}
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
void func_150761F4(void) {
    D_800D154C->pad223[0] = 6;
    *(u16 *)((u8 *)D_800D154C + 0x22C) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x22C) & 0xFFFE);
}
void func_15076220(void) {
    func_150761F4();
    *(u16 *)((u8 *)D_800D154C + 0x22C) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x22C) | 1);
}
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
extern u8 D_800D1891;

void func_15076500(void) {
    *(s16 *)((u8 *)D_800D154C + 0x22E) = (s16) ((D_800D1890 << 8) | D_800D1891);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507652C.s")
void func_1507659C(void) {
    *(f32 *)((u8 *)D_800D154C + 0x18) = (f32) (*(f32 *)((u8 *)D_800D154C + 0x18) + (f32) (D_800D1890 * 0x64));
    if (D_800D1893 != 0) {
        *(f32 *)((u8 *)D_800D154C + 0x18) = 1800.0f;
    }
}
void func_15076600(void) {

}
void func_15076608(void) {
    D_800D154C->field_24A = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076624.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076678.s")
void func_150766D0(void) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)D_800D154C + 0x28);
    if (((temp_fv0 > 0.0f) && (D_800D1890 == 0)) || (((f32) (D_800D1890 * 0x32) < temp_fv0) && (D_800D1890 != 0))) {
        *(s16 *)((u8 *)D_800D154C + 0x21C) = 0x63;
        *(s32 *)((u8 *)D_800D154C + 0x218) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x218) - 5);
    }
}
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076D04 CURRENT (595) */
void func_15076D04(void) {
    f32 var_ft1;

    var_ft1 = (f32) D_800D1890;
    if ((s32) D_800D1890 < 0) {
        var_ft1 += 4294967296.0f;
    }
    *(f32 *)((u8 *)D_800D154C + 0x3C) = var_ft1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076D04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076D04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076D3C.s")
void func_15076DF4(void) {
    D_800D154C->field_0 = D_800D1890;
}
void func_15076E10(void) {
    D_800D154C->pad10F[0xC1] = D_800D1890;
    *(u16 *)((u8 *)D_800D154C + 0x22C) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x22C) | D_800D1891);
}
void func_15076E48(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076E50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076F40.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076F78 CURRENT (470) */
void func_15076F78(void) {
    *(s16 *)((u8 *)D_800D154C + 0xCC) = (s16) (s8) D_800D1890;
    *(s16 *)((u8 *)D_800D154C + 0xCE) = (s16) (s8) D_800D1891;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076F78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076F78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076FA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150770E4.s")
void func_15077174(void) {
    D_800D154C->field_10E = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077190.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150771F0.s")
void func_15077294(void) {
    switch (D_800D1891) {                           /* irregular */
    case 0:
        D_800D154C->pad10F[0xBB] = D_800D1890;
        return;
    case 1:
        D_800D154C->pad10F[0xBB] -= 1;
        return;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150772E8.s")
void func_15077318(void) {
    if (D_800D1890 != 0) {
        D_800D154C->padB1[0x50] |= 1;
        return;
    }
    D_800D154C->padB1[0x50] &= 0xFFFE;
}
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
void func_15077B14(void) {
    D_800D154C->pad24B[1] = D_800D1890;
    D_800D154C->pad24B[2] = D_800D1891;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077B44.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15077B80 CURRENT (55) */
void func_15077B80(void) {
    *(s32 *)((u8 *)D_800D154C + 0x25C) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x25C) | ((D_800D1890 << 8) + D_800D1891));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15077B80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077B80.s")
void *func_1505F0AC(u8);                            /* extern */

void func_15077BB4(void) {
    void *temp_v0;

    temp_v0 = func_1505F0AC(D_800D1891);
    *(s32 *)((u8 *)temp_v0 + 0x218) = 0;
    *(u8 *)((u8 *)temp_v0 + 0x232) = (u8) D_800D1890;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15077BE4 CURRENT (80) */
void func_15077BE4(void) {
    *(s32 *)((u8 *)D_800D154C + 0x25C) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x25C) & ~((D_800D1890 << 8) + D_800D1891));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15077BE4 */
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
void func_15077F08(void) {
    *(s16 *)((u8 *)D_800D154C + 0x1EA) = (s16) ((D_800D1890 << 8) | D_800D1891);
}
void func_15077F34(void) {
    D_800D154C->pad24B[4] = D_800D1890;
    D_800D154C->pad24B[5] = D_800D1891;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077F64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078074.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507813C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150781A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150781F4.s")
void func_150782CC(void) {
    D_800D154C->field_23E = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150782E8.s")
u8 func_15083FB0(u8);                               /* extern */

void func_15078358(void) {
    u8 temp_v0;

    temp_v0 = func_15083FB0(D_800D1890);
    D_800D154C->field_222 = temp_v0;
    if (temp_v0 == -1U) {
        D_800D154C->field_222 = 0;
    }
}
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
void func_150791F0(void) {
    if ((s32) *(u8 *)((u8 *)D_800D154C + 0x2C9) < (s32) D_800D1890) {
        D_800D154C->pad10F[0xBA] = 0xFF;
        return;
    }
    D_800D154C->pad10F[0xBA] = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079228.s")
void func_150792E0(void) {
    D_800D154C->field_232 = D_800D1890;
}
void func_150792FC(void) {
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) & 0xFFF8);
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) | D_800D1890);
}
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
void func_15079A28(void) {
    D_800D154C->pad252[0] = D_800D1890;
    D_800D154C->pad252[1] = D_800D1891;
}
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
extern u8 D_800D1892;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A3E8 CURRENT (540) */
s32 func_1507A3E8(void) {
    return (D_800D1890 << 0x18) | (D_800D1891 << 0x10) | (D_800D1892 << 8) | D_800D1893;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A3E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A3E8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A428 CURRENT (340) */
void func_1507A428(void) {
    *(s32 *)((u8 *)D_800D154C + 0x94) = (s32) ~((D_800D1890 << 0x18) | (D_800D1891 << 0x10) | (D_800D1892 << 8) | 1 | D_800D1893);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A428 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A428.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A47C CURRENT (865) */
void func_1507A47C(void) {
    *(s32 *)((u8 *)D_800D154C + 0x94) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x94) & ~((D_800D1890 << 0x18) | (D_800D1891 << 0x10) | (D_800D1892 << 8) | D_800D1893));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A47C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A47C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A4D4 CURRENT (970) */
void func_1507A4D4(void) {
    *(s32 *)((u8 *)D_800D154C + 0x94) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x94) | ((D_800D1890 << 0x18) | (D_800D1891 << 0x10) | (D_800D1892 << 8) | D_800D1893));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A4D4 */
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
void func_1507A808(void) {
    *(u16 *)((u8 *)D_800D154C + 0x22C) = (u16) ((*(u16 *)((u8 *)D_800D154C + 0x22C) & D_800D1890) | D_800D1891);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A838.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A878.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A8A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A8EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A984.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AA48.s")
void func_1507ACB0(void) {
    D_800D154C->pad21F[1] = D_800D1890;
    D_800D154C->pad21F[0] = D_800D1891;
}
void func_1507ACE0(void) {
    D_800D154C->pad1E5[0] = D_800D1890;
    D_800D154C->pad1E5[1] = D_800D1890;
    D_800D154C->pad1E5[2] = D_800D1891;
    D_800D154C->pad1E5[3] = D_800D1891;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AD30.s")
void func_1507AD60(void) {
    D_800D154C->field_1E4 = D_800D1890;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507AD7C CURRENT (10) */
void func_1507AD7C(void) {
    *(s32 *)((u8 *)D_800D154C + 0xF4) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF4) | func_1507A3E8());
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507AD7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AD7C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507ADAC CURRENT (10) */
void func_1507ADAC(void) {
    *(s32 *)((u8 *)D_800D154C + 0xF4) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF4) & ~func_1507A3E8());
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507ADAC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507ADAC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507ADE0 CURRENT (185) */
void func_1507ADE0(void) {
    s32 temp_a2;
    s32 temp_lo;
    s32 var_a1;

    temp_a2 = D_800D154C->field_78 - D_800D154C->field_7A;
    var_a1 = temp_a2;
    if (temp_a2 < 0) {
        var_a1 = -temp_a2;
    }
    if (var_a1 >= 0x8001) {
        var_a1 += 0xFFFF0000;
    }
    if (var_a1 < 0) {
        var_a1 = -var_a1;
    }
    temp_lo = var_a1 / (s32) D_800D1890;
    D_800D154C->pad1E5[1] = (u8) (temp_lo >> 8);
    D_800D154C->pad1E5[3] = temp_lo & 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507ADE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507ADE0.s")
void func_1507AE78(void) {
    D_800D154C->field_229 = D_800D1890;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507AE94 CURRENT (50) */
void func_1507AE94(void) {
    *(s16 *)((u8 *)D_800D154C + 0xD2) = (s16) ((D_800D1890 << 8) | D_800D1891);
    *(s16 *)((u8 *)D_800D154C + 0xD4) = (s16) ((D_800D1892 << 8) | D_800D1893);
    *(s16 *)((u8 *)D_800D154C + 0xD2) = (s16) (s32) ((f32) *(s16 *)((u8 *)D_800D154C + 0xD2) * *(f32 *)((u8 *)D_800D154C + 0x14C));
    *(s16 *)((u8 *)D_800D154C + 0xD4) = (s16) (s32) ((f32) *(s16 *)((u8 *)D_800D154C + 0xD4) * *(f32 *)((u8 *)D_800D154C + 0x150));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507AE94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AE94.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507AF3C CURRENT (25) */
void func_1507AF3C(void) {
    *(s16 *)((u8 *)D_800D154C + 0xD6) = (s16) ((D_800D1890 << 8) | D_800D1891);
    *(s16 *)((u8 *)D_800D154C + 0xD6) = (s16) (s32) ((f32) *(s16 *)((u8 *)D_800D154C + 0xD6) * *(f32 *)((u8 *)D_800D154C + 0x150));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507AF3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507AF3C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507AF98 CURRENT (50) */
void func_1507AF98(void) {
    *(s16 *)((u8 *)D_800D154C + 0xD8) = (s16) ((D_800D1890 << 8) | D_800D1891);
    *(s16 *)((u8 *)D_800D154C + 0xDA) = (s16) ((D_800D1892 << 8) | D_800D1893);
    *(s16 *)((u8 *)D_800D154C + 0xD8) = (s16) (s32) ((f32) *(s16 *)((u8 *)D_800D154C + 0xD8) * *(f32 *)((u8 *)D_800D154C + 0x14C));
    *(s16 *)((u8 *)D_800D154C + 0xDA) = (s16) (s32) ((f32) *(s16 *)((u8 *)D_800D154C + 0xDA) * *(f32 *)((u8 *)D_800D154C + 0x14C));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507AF98 */
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507B578 CURRENT (595) */
void func_1507B578(void) {
    f32 var_ft1;

    D_800D154C->padB1[0x1F] = D_800D1890;
    var_ft1 = (f32) D_800D1891;
    if ((s32) D_800D1891 < 0) {
        var_ft1 += 4294967296.0f;
    }
    *(f32 *)((u8 *)D_800D154C + 0x114) = var_ft1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507B578 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B578.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B5C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B630.s")
void func_1507B6E0(void) {
    if ((D_800D154C->field_89 != 0) || (*(f32 *)((u8 *)D_800D154C + 0x28) > 5.0f)) {
        *(s32 *)((u8 *)D_800D154C + 0x218) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x218) - 5);
        *(s16 *)((u8 *)D_800D154C + 0x21C) = 0x64;
    }
}
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
s32 func_1507A3E8();                                /* extern */

void func_1507BAD0(void) {
    *(s32 *)((u8 *)D_800D154C + 0xFC) = func_1507A3E8();
}
void func_1507BAF8(void) {
    *(s32 *)((u8 *)D_800D154C + 0x2CC) = func_1507A3E8();
}
void func_1507BB20(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507BB28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507BC14.s")
