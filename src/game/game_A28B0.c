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
 * - func_15075DE8
 * - func_15075F6C
 * - func_1507602C
 * - func_15076250
 * - func_150763B0
 * - func_1507652C
 * - func_15076624
 * - func_15076678
 * - func_15076768
 * - func_150767F4
 * - func_150768DC
 * - func_15076B94
 * - func_15076D04
 * - func_15076D3C
 * - func_15076F78
 * - func_15076FA8
 * - func_150770E4
 * - func_15077190
 * - func_150771F0
 * - func_15077404
 * - func_15077508
 * - func_150778F0
 * - func_150779D4
 * - func_15077B80
 * - func_15077BE4
 * - func_15077C38
 * - func_15077DBC
 * - func_15077E9C
 * - func_15077F64
 * - func_15078074
 * - func_1507813C
 * - func_150781F4
 * - func_1507839C
 * - func_15078544
 * - func_1507879C
 * - func_15078890
 * - func_15078900
 * - func_15078A60
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
 * - func_15079928
 * - func_15079A98
 * - func_15079B30
 * - func_15079F6C
 * - func_15079FBC
 * - func_1507A100
 * - func_1507A164
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
 * - func_1507A8EC
 * - func_1507A984
 * - func_1507AA48
 * - func_1507AD7C
 * - func_1507ADAC
 * - func_1507ADE0
 * - func_1507AE94
 * - func_1507AF3C
 * - func_1507AF98
 * - func_1507B058
 * - func_1507B178
 * - func_1507B578
 * - func_1507B630
 * - func_1507B734
 * - func_1507B7E8
 * - func_1507B884
 * - func_1507B974
 * - func_1507BA48
 * - func_1507BB28
 * - func_1507BC14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameA28B0NestedState {
    u8 pad0[0x75];
    u8 field_75;
} GameA28B0NestedState;

typedef struct GameA28B0State {
    s32 field_0;
    u8 pad4;
    u8 field_5;
    u8 pad6[0xE];
    f32 position_x;
    f32 position_y;
    f32 position_z;
    u8 pad20[0x4F];
    u8 field_6F;
    u8 field_70;
    u8 field_71;
    u16 field_72;
    u8 pad74[2];
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
    u8 pad255[0xC7];
    GameA28B0NestedState *nested_31C;
} GameA28B0State;

extern GameA28B0State *D_800D154C;
extern u8 D_800D1890;
extern f32 D_800D1898[];
void func_15075548(void);
void func_15075650(void);
void func_150836CC(GameA28B0State *arg0, u8 arg1);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15075400 CURRENT (20) */
void func_15075400(s32 arg0) {
    s32 temp_t4;
    s32 var_a1;
    u8 *temp_v1;
    u8 temp_a2;

    if (arg0 < 0xF7) {
        *(u8 **)((u8 *)D_800D154C + 0x218) = (u8 *) (*(u8 **)((u8 *)D_800D154C + 0x218) + (arg0 * 5));
        return;
    }
    var_a1 = 0;
loop_3:
    temp_t4 = (var_a1 + 1) & 0xFF;
    temp_v1 = *(u8 **)((u8 *)D_800D154C + 0x218);
    temp_a2 = *temp_v1;
    if ((s32) temp_a2 < 0xF7) {
        *(u8 **)((u8 *)D_800D154C + 0x218) = (u8 *) (temp_v1 + 5);
        goto block_7;
    }
    *(u8 **)((u8 *)D_800D154C + 0x218) = (u8 *) (temp_v1 + 1);
    if (arg0 == (temp_a2 & 0xFF)) {
        *(u8 **)((u8 *)D_800D154C + 0x218) = (u8 *) (*(u8 **)((u8 *)D_800D154C + 0x218) - 5);
        return;
    }
block_7:
    var_a1 = temp_t4;
    if (temp_t4 >= 0x64) {
        return;
    }
    goto loop_3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15075400 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075400.s")
extern u8 D_800D1893;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15075498 CURRENT (325) */
void func_15075498(void) {
    s16 temp_t6;

    temp_t6 = D_800D1893 & 0x7F;
    if (temp_t6 != 0x7F) {
        *(s16 *)((u8 *)D_800D154C + 0x244) = temp_t6;
    }
    *(s32 *)((u8 *)D_800D154C + 0xF4) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF4) & ~0x143E);
    if (D_800D1890 == 0xFA) {
        *(s32 *)((u8 *)D_800D154C + 0xF4) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF4) | 0x22);
    } else if (D_800D1890 == 0xFB) {
        *(s32 *)((u8 *)D_800D154C + 0xF4) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF4) | 4);
    }
    if (D_800D1893 & 0x80) {
        *(s32 *)((u8 *)D_800D154C + 0xF4) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF4) | 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15075498 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075498.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075548.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075650.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075884.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075938.s")
extern u8 D_800D1891;
extern u8 D_800D1892;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15075A50 CURRENT (20) */
void func_15075A50(void) {
    u8 temp_v0;

    temp_v0 = D_800D154C->field_21E;
    if (((D_800D1892 == 0) && (temp_v0 == D_800D1891)) || ((D_800D1892 == 1) && (temp_v0 != D_800D1891))) {
        func_15075400((s32) D_800D1890);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15075A50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075AAC.s")
void func_15075B60(void) {
    func_15075548();
    D_800D154C->pad223[0] = 0xA;
}
void func_15075B8C(void) {
    func_15075650();
    D_800D154C->pad223[0] = 0xA;
}
void func_15075BB8(void) {
    func_15075548();
    *(u16 *)((u8 *)D_800D154C + 0x22C) =
        (u16) (*(u16 *)((u8 *)D_800D154C + 0x22C) | 2);
}
extern u8 D_800D1893;

void func_15075BE8(void) {
    if (D_800D1893 != 0) {
        *(u16 *)((u8 *)D_800D154C + 0x22C) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x22C) | 0x80);
    }
    D_800D154C->pad233[0] = D_800D1890;
}
void func_15075C24(void) {
    if (D_800D1893 != 1) {
        *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) (s16) ((D_800D1892 << 8) | D_800D1890);
    }
    if (D_800D1893 != 2) {
        *(f32 *)((u8 *)D_800D154C + 0x24) = (f32) (s8) D_800D1891;
    }
}
void func_15075CA0(void) {
    func_15075548();
    D_800D154C->pad223[0] = 1;
}
void func_15075CCC(void) {
    func_15075548();
    D_800D154C->pad223[0] = 0x10;
    D_800D154C->pad22A[7] = D_800D1891;
}
void func_15075D0C(void) {
    func_15075548();
    D_800D154C->pad223[0] = 0xF;
}
void func_15075D38(void) {
    func_15075CA0();
    D_800D154C->pad223[0] = 0xE;
}
void func_15075D64(void) {
    func_15075548();
    D_800D154C->pad223[0] = 0xC;
    D_800D154C->field_222 = 0;
}
void func_15075D9C(void) {
    func_15075548();
    D_800D154C->pad223[0] = 9;
}
void func_15075DC8(void) {
    func_15075CA0();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075DE8.s")
void func_15075E6C(void) {
    func_15075548();
    D_800D154C->pad223[0] = 2;
}
void func_15075E98(void) {
    D_800D154C->field_235 = D_800D1890;
}
u32 func_150ADA20();                                /* extern */
extern u8 D_800D1892;

void func_15075EB4(void) {
    if ((u32) (func_150ADA20() % 100U) < (u8) D_800D1892) {
        func_15075400((s32) D_800D1890);
    }
}
extern u8 D_800D1891;
extern u8 D_800D1892;

void func_15075F00(void) {
    D_800D154C->pad233[1] = D_800D1890;
    D_800D154C->field_236 = D_800D1891;
    D_800D154C->pad237 = D_800D1892;
}
void func_15075F40(void) {
    func_15075548();
    D_800D154C->pad223[0] = 3;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15075F6C CURRENT (585) */
void func_15075F6C(void) {
    f32 var_ft0;

    if (D_800D1890 != 0) {
        if (D_800D1892 == 0) {
            *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) D_800D1890;
        } else {
            *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) -(s32) D_800D1890;
        }
    }
    if (D_800D1891 != 0) {
        var_ft0 = (f32) D_800D1891;
        if ((s32) D_800D1891 < 0) {
            var_ft0 += 4294967296.0f;
        }
        *(f32 *)((u8 *)D_800D154C + 0x24) = var_ft0;
    }
    D_800D154C->pad6[0x34] = D_800D1893;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15075F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075F6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507602C.s")
void func_150761C8(void) {
    func_15075650();
    D_800D154C->pad223[0] = 5;
}
void func_150761F4(void) {
    D_800D154C->pad223[0] = 6;
    *(u16 *)((u8 *)D_800D154C + 0x22C) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x22C) & 0xFFFE);
}
void func_15076220(void) {
    func_150761F4();
    *(u16 *)((u8 *)D_800D154C + 0x22C) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x22C) | 1);
}
void func_15060778(s32, GameA28B0State *, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076250 CURRENT (310) */
void func_15076250(void) {
    func_15060778((D_800D1890 << 8) | D_800D1891, D_800D154C, 0x7D00, -0x64,
                  0x1F4, 0x9C4, D_800D1892);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076250 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076250.s")
extern void func_1000CBA8(u8);

void func_150762B0(void) {
    func_1000CBA8(D_800D1890);
}
void func_151669A0(s32, s32, s32, f32, s32, s32);

void func_150762D4(void) {
    func_151669A0((s32)D_800D154C->position_x,
                  (s32)(D_800D154C->position_y + 100.0f),
                  (s32)D_800D154C->position_z, 0.45f, 0xFF, 0);
}
void func_15076340(void) {
    if (D_800D154C->padB1[0x56] == 0) {
        func_15075400((s32) D_800D1890);
    }
    if (D_800D1891 != 0) {
        D_800D154C->padB1[0x56] = 0;
    }
}
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
extern u8 D_800CC3F5[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507652C CURRENT (100) */
void func_1507652C(void) {
    if (D_800D1891 != 0) {
        D_800CC3F5[D_800D154C->pad10F[0x15] * 0x32C] = D_800D1890;
        return;
    }
    D_800D154C->pad10F[0x16] = D_800D1890;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507652C */
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076624 CURRENT (1140) */
void func_15076624(void) {
    *(s32 *)((u8 *)D_800D154C + 0xF8) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF8) | ((D_800D1890 << 0x18) | (D_800D1891 << 0x10) | (D_800D1892 << 8) | D_800D1893));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076624 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076624.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076678 CURRENT (675) */
void func_15076678(void) {
    *(s32 *)((u8 *)D_800D154C + 0xF8) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF8) & ~((D_800D1890 << 0x18) | (D_800D1891 << 0x10) | (D_800D1892 << 8) | D_800D1893));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076678 */
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
void func_1506160C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4);

void func_15076C7C(void) {
    func_1506160C((u8 *)D_800D154C, 1, D_800D1890, 0, 0);
}
void func_15076CB4(void) {
    D_800D154C->field_76 = D_800D154C->field_78;
}
/* Call context: func_15060F28: unique active project prototype */
void func_15060F28(u8 *, s32);

void func_15076CCC(void) {
    *(s16 *)((u8 *)D_800D154C + 0x21C) = 0x2710;
    func_15060F28((u8 *) D_800D154C, 1);
}
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
/* Call context: func_15075548: unique active project prototype */

void func_15076E50(void) {
    func_15075548();
    *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) ((f32) (func_150ADA20() % 20U) + 55.0f);
    *(f32 *)((u8 *)D_800D154C + 0x24) = 2.0f;
    D_800D154C->field_78 = (u16) (func_150ADA20(&D_800D154C) % 65535U);
    *(f32 *)((u8 *)D_800D154C + 0x3C) = (f32) ((func_150ADA20(&D_800D154C) % 20U) + 0xF);
    *(f32 *)((u8 *)D_800D154C + 0x44) = (f32) *(f32 *)((u8 *)D_800D154C + 0x3C);
    D_800D154C->pad223[0] = 7;
}
/* Call context: func_15060F28: unique active project prototype */

void func_15076F40(void) {
    *(s16 *)((u8 *)D_800D154C + 0x21C) = 0x3E8;
    func_15060F28((u8 *) D_800D154C, 1);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076F78 CURRENT (470) */
void func_15076F78(void) {
    *(s16 *)((u8 *)D_800D154C + 0xCC) = (s16) (s8) D_800D1890;
    *(s16 *)((u8 *)D_800D154C + 0xCE) = (s16) (s8) D_800D1891;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076F78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076F78.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076FA8 CURRENT (735) */
void func_15076FA8(void) {
    f32 temp_fv0;
    s16 temp_a1;

    if (D_800D1893 == 0) {
        temp_a1 = (func_150ADA20() % (u8) D_800D1890) - ((s32) D_800D1890 / 2);
        *(f32 *)((u8 *)D_800D154C + 0x14) = (f32) (*(f32 *)((u8 *)D_800D154C + 0x14) + ((f32) temp_a1 * 3.0f));
        *(f32 *)((u8 *)D_800D154C + 0x1C) = (f32) (*(f32 *)((u8 *)D_800D154C + 0x1C) + ((f32) (s16) ((func_150ADA20(D_800D1890, temp_a1) % (u8) D_800D1891) - ((s32) D_800D1891 / 2)) * 3.0f));
        return;
    }
    temp_fv0 = (f32) D_800D1893;
    if (*(f32 *)((u8 *)D_800D154C + 0x3C) < temp_fv0) {
        *(f32 *)((u8 *)D_800D154C + 0x3C) = temp_fv0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076FA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076FA8.s")
extern f32 D_800CC30C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150770E4 CURRENT (40) */
void func_150770E4(void) {
    if (*(&D_800CC30C + (D_800D154C->field_222 * 0x32C)) < (f32) D_800D1892) {
        func_15075400((s32) D_800D1893);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150770E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150770E4.s")
void func_15077174(void) {
    D_800D154C->field_10E = D_800D1890;
}
void func_10010630(s32, GameA28B0State *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15077190 CURRENT (180) */
void func_15077190(void) {
    s32 value;
    s32 shiftedByte;

    value = (D_800D1890 << 8) | D_800D1891;
    if (value != 0) {
        shiftedByte = D_800D1892 << 7;
        func_10010630(value & 0xFFFF, D_800D154C, shiftedByte, 0x1F4, 0x9C4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15077190 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077190.s")
/* Call context: func_1502EA60: unique active project prototype */
/* Call context: func_1502EA7C: unique active project prototype */
/* Call context: func_1506160C: unique active project prototype */
void func_1502EA60(u8 *, s32);
void func_1502EA7C(u8 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150771F0 CURRENT (475) */
void func_150771F0(void) {
    s32 var_a1;

    if (D_800D1893 == 0) {
        if (D_800D1892 != 0) {
            var_a1 = 1;
        } else {
            var_a1 = 2;
        }
        func_1506160C((u8 *) D_800D154C, var_a1, (s32) D_800D1890, (s32) D_800D1891, 0U);
        return;
    }
    if (D_800D1892 == 0) {
        func_1502EA60((u8 *) D_800D154C, (s32) D_800D1890);
        return;
    }
    func_1502EA7C((u8 *) D_800D154C, (s32) D_800D1890);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150771F0 */
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
/* Call context: func_1503DE70: unique active project prototype */
void func_1503DE70(void *, s32, s32);

void func_150772E8(void) {
    func_1503DE70(D_800D154C, (s32) D_800D1890, -1);
}
void func_15077318(void) {
    if (D_800D1890 != 0) {
        D_800D154C->padB1[0x50] |= 1;
        return;
    }
    D_800D154C->padB1[0x50] &= 0xFFFE;
}
void func_1507735C(void) {
}
void func_15077364(void) {
    if (D_800D1893 != 0) {
        D_800D1890 += func_150ADA20() % (u8) D_800D1893;
    }
    D_800D154C->pad23F[7] = D_800D1890;
    D_800D154C->pad23F[0xA] = 0;
    D_800D154C->pad23F[8] = D_800D1891;
    D_800D154C->pad23F[9] = D_800D1892;
}
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15077404 CURRENT (1405) */
void func_15077404(void) {
    s16 var_v0;

    if (D_800D1893 != 0) {
        var_v0 = ((D_800D154C->pad23F[7] & 0x1F) << 8) + D_800D154C->pad23F[0xA] + ((s16) ((D_800D1891 << 8) + D_800D1892) * D_800BE9E4);
        if (var_v0 < 0) {
            var_v0 = 0;
        }
        D_800D154C->pad23F[7] = (var_v0 >> 8) | 0x80;
        D_800D154C->pad23F[0xA] = (u8) var_v0;
        return;
    }
    D_800D154C->pad23F[7] = D_800D1890;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15077404 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077404.s")
void func_150774B4(void) {
    u8 temp_v1;

    temp_v1 = D_800D154C->pad1E5[0x2C];
    if ((temp_v1 == D_800D154C->pad1E5[0x2A]) || (temp_v1 == 0xFF)) {
        *(s32 *)((u8 *)D_800D154C + 0x25C) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x25C) | 0x800);
        func_15075400((s32) D_800D1890);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077508.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150778F0.s")
void func_150779A8(void) {
    func_15075650();
    D_800D154C->pad223[0] = 0xB;
}
f32 func_1505A6F8(GameA28B0State *, s32 *);
extern u8 D_800C3E78;
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150779D4 CURRENT (105) */
void func_150779D4(void) {
    s32 *temp_a1;
    u8 var_v0;

    var_v0 = 0;
    if (D_800D1892 != 0) {
        var_v0 = D_800D154C->field_222;
    }
    if ((var_v0 != D_800C3E78) && ((temp_a1 = (var_v0 * 0x32C) + &D_800CC2D0, (*(s32 *)((u8 *)temp_a1 + 0) != 1)) || (*(u8 *)((u8 *)temp_a1 + 0x65) == 0)) && (func_1505A6F8(D_800D154C, temp_a1) < (f32) (D_800D1893 * 8))) {
        func_15075400((s32) D_800D1890);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150779D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150779D4.s")
void func_15077AA0(void) {
    D_800D154C->field_239 = D_800D1890;
}
void func_15077ABC(void) {
    *(u8 *)((u8 *)D_800D154C + 0x258) = (u8) D_800D1890;
    *(u8 *)((u8 *)D_800D154C + 0x257) = D_800D1891;
    D_800D154C->pad7C[0xA] = (u8) (func_150ADA20() % 255U);
}
void func_15077B14(void) {
    D_800D154C->pad24B[1] = D_800D1890;
    D_800D154C->pad24B[2] = D_800D1891;
}
void func_15060A30(s32, GameA28B0State *);

void func_15077B44(void) {
    func_15060A30((D_800D1890 << 8) + D_800D1891, D_800D154C);
}
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
f32 func_1505A72C(GameA28B0State *, s32 *);         /* extern */
extern f32 D_8009A148;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15077C38 CURRENT (3508) */
void func_15077C38(void) {
    f32 temp_fv0;
    f32 var_fs0;
    s32 *var_s0;
    s32 temp_v1;
    u8 temp_v0;
    u8 var_s1;

    var_fs0 = D_8009A148;
    var_s0 = &D_800CC2D0;
    var_s1 = 0;
    D_800D154C->field_222 = 0;
loop_1:
    temp_v1 = *(s32 *)((u8 *)var_s0 + 0);
    if ((temp_v1 != 0) && (*(u8 *)((u8 *)var_s0 + 0x1CA) != 0) && ((temp_v0 = *(u8 *)((u8 *)var_s0 + 0x125), (temp_v0 == 0)) || (temp_v0 == 0xFF)) && ((*(u8 *)((u8 *)var_s0 + 0x65) == 0) || (D_800D1892 != 0)) && ((D_800D1890 == *(u8 *)((u8 *)var_s0 + 4)) || ((D_800D1891 == temp_v1) && (*(u8 *)((u8 *)var_s0 + 0x104) == 0)))) {
        if (D_800D1893 == 0) {
            D_800D154C->field_222 = var_s1;
            return;
        }
        temp_fv0 = func_1505A72C(D_800D154C, var_s0);
        if (temp_fv0 < var_fs0) {
            var_fs0 = temp_fv0;
            D_800D154C->field_222 = var_s1;
        }
        goto block_14;
    }
block_14:
    var_s1 += 1;
    var_s0 += 0x32C;
    if (var_s1 == 0x19) {
        return;
    }
    goto loop_1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15077C38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077C38.s")
void func_15077DA0(void) {
    D_800D154C->field_21E = D_800D1890;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077DBC.s")
/* Call context: func_10012718: unique active project prototype */
void func_10012718(u16, u8 *, s32, s16, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15077E9C CURRENT (20) */
void func_15077E9C(void) {
    func_10012718(((D_800D1890 << 8) + D_800D1891) & 0xFFFF, (u8 *) D_800D154C, 0x5DC0, 0x1F4, 0x9C4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15077E9C */
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
f32 func_1505A6F8(GameA28B0State *, s32 *);         /* extern */
extern u8 D_800C3E78;
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15078074 CURRENT (315) */
void func_15078074(void) {
    f32 temp_fs0;
    s32 *var_s1;
    s32 var_s0;

    var_s1 = &D_800CC2D0;
    var_s0 = 0;
    temp_fs0 = (f32) (D_800D1893 * 8);
loop_1:
    if ((*var_s1 != 0) && (var_s0 != D_800C3E78) && (func_1505A6F8(D_800D154C, var_s1) < temp_fs0)) {
        func_15075400((s32) D_800D1890);
        return;
    }
    var_s0 += 1;
    var_s1 += 0x32C;
    if (var_s0 == 0x19) {
        return;
    }
    goto loop_1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15078074 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078074.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507813C CURRENT (155) */
void func_1507813C(void) {
    if (*(&D_800CC2D0 + (D_800D154C->field_222 * 0x32C)) == 0) {
        func_15075400((s32) D_800D1890);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507813C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507813C.s")
void func_150781A4(void) {
    D_800D154C->pad23F[0] = D_800D1891;
    D_800D154C->pad23F[1] = D_800D1892;
    D_800D154C->pad23F[2] = D_800D1890;
    D_800D154C->pad23F[3] = D_800D1893;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150781F4.s")
void func_150782CC(void) {
    D_800D154C->field_23E = D_800D1890;
}
void func_150782E8(void) {
    if (((D_800D1892 == 0) && (D_800D1891 == D_800D154C->pad6[0x35])) || ((D_800D1892 == 1) && (D_800D1891 != D_800D154C->pad6[0x35]))) {
        func_15075400((s32) D_800D1890);
    }
}
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
void func_15078520(void) {
    func_15075400((s32) D_800D1890);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078544.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507879C.s")
void func_15078874(void) {
    D_800D154C->field_251 = D_800D1890;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15078890 CURRENT (90) */
void func_15078890(void) {
    if (((D_800D1892 == 0) && (D_800D1891 == D_800D154C->field_251)) || ((D_800D1892 == 1) && (D_800D1891 != D_800D154C->field_251))) {
        func_15075400((s32) D_800D1890);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15078890 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078890.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078900.s")
extern u8 D_800CC5A0[];

void func_15078A08(void) {
    void *temp_a0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x2D0);
    temp_a0 = *(void **)(D_800CC5A0 + (D_800D154C->field_222 * 0x32C));
    *(f32 *)((u8 *)temp_v0 + 8) = *(f32 *)((u8 *)temp_a0 + 8);
    *(f32 *)((u8 *)temp_v0 + 0xC) = *(f32 *)((u8 *)temp_a0 + 0xC);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078A60.s")
s32 func_15078A60(u8);

void func_1507900C(void) {
    if (func_15078A60(0U) != 0) {
        func_15075400((s32) D_800D1890);
    }
}
s32 func_15078A60(u8);                              /* extern */
s32 func_1507BB28(s32, u8);                         /* extern */

void func_1507903C(void) {
    if (func_15078A60(0U) != 0) {
        *(s32 *)((u8 *)D_800D154C + 0x218) = func_1507BB28(0, D_800D1890);
        *(s32 *)((u8 *)D_800D154C + 0x218) = *(s32 *)((u8 *)D_800D154C + 0x218) - 5;
    }
}

void func_15079090(void) {
    if (func_15078A60(D_800C3E78) != 0) {
        func_15075400((s32) D_800D1890);
    }
}
extern u8 D_800C3E78;
s32 func_1507BB28(s32, u8);

void func_150790C4(void) {
    if (func_15078A60(D_800C3E78) != 0) {
        *(s32 *)((u8 *)D_800D154C + 0x218) = func_1507BB28(0, D_800D1890);
        *(s32 *)((u8 *)D_800D154C + 0x218) -= 5;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507911C CURRENT (2735) */
void func_1507911C(void) {
    s16 var_a0;
    u8 temp_t1;
    void *temp_a1;

    temp_t1 = D_800D1893 & 1;
    {
        u8 var_v0 = temp_t1;
    if (temp_t1 != 0) {
        var_v0 = D_800C3E78;
    }
    temp_a1 = (var_v0 * 0x32C) + &D_800CC2D0;
    var_a0 = (s16) (s32) *(f32 *)((u8 *)temp_a1 + 0x18);
    if (D_800D1893 & 2) {
        var_a0 = (s16) (s32) *(f32 *)((u8 *)temp_a1 + 0x14);
    }
    if (var_a0 < (s16) ((D_800D1891 << 8) | D_800D1892)) {
        func_15075400((s32) D_800D1890);
    }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507911C */
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15079334 CURRENT (70) */
void func_15079334(void) {
    u8 temp_v0;
    void *temp_v1;

    temp_v0 = D_800D154C->field_A8;
    if (temp_v0 != 0) {
        temp_v1 = ((temp_v0 & 0x7F) * 0x32C) + &D_800CC2D0;
        *(s32 *)((u8 *)temp_v1 + 0x218) = 0;
        *(u8 *)((u8 *)temp_v1 + 0x232) = (u8) D_800D1890;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15079334 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079334.s")
extern void func_1514D3B0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15079390 CURRENT (180) */
void func_15079390(void) {
    u8 temp_v0;

    temp_v0 = D_800D1890;
    func_1514D3B0(D_800D154C, (s32)(s16)temp_v0, (s32)D_800D1891, (s32)D_800D1892);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15079390 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079390.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150793D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079570.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507965C CURRENT (440) */
void func_1507965C(void) {
    u8 temp_v0;
    void *temp_v1;

    temp_v0 = func_15083FB0(D_800D1890);
    if (temp_v0 != -1U) {
        temp_v1 = (temp_v0 * 0x32C) + &D_800CC2D0;
        *(s32 *)((u8 *)temp_v1 + 0x218) = 0;
        *(s8 *)((u8 *)temp_v1 + 0x23A) = 0;
        *(u8 *)((u8 *)temp_v1 + 0x232) = (u8) D_800D1891;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507965C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507965C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150796CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079790.s")
/* Call context: func_15075548: unique active project prototype */
extern f32 D_800CC30C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15079880 CURRENT (25) */
void func_15079880(void) {
    s32 var_v0;

    var_v0 = (s32) (D_800CC30C + (f32) (s8) D_800D1892);
    if (var_v0 < (s32) D_800D1891) {
        var_v0 = (s32) D_800D1891;
    } else if (var_v0 >= 0xFB) {
        var_v0 = 0xFA;
    }
    D_800D1892 = (u8) var_v0;
    func_15075548();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15079880 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079880.s")
void func_150781F4(void);

void func_150798F8(void) {
    D_800D1891 = D_800D154C->field_21E;
    func_150781F4();
}
void func_1507E7E4(GameA28B0State *, u8, u8, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15079928 CURRENT (650) */
void func_15079928(void) {
    s32 value;
    s32 argument;

    value = ((D_800D1891 << 0x10) + D_800D1892) & 0xFFFF;
    argument = value;
    if (value == 0) {
        argument = 0xFFFF;
    }
    func_1507E7E4(D_800D154C, D_800D1890, D_800D1893, argument, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15079928 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079928.s")
/* Call context: func_1507EB4C: unique active project prototype */
void func_1507EB4C(void *, s32);

void func_15079988(void) {
    func_1507EB4C(D_800D154C, (s32) D_800D1890);
}
void func_150799B4(void) {
    s32 var_a0;
    s32 sp1C;

    var_a0 = (D_800D1890 << 8) + D_800D1891;
    if (D_800D1892 != 0) {
        sp1C = var_a0;
        var_a0 += func_150ADA20(var_a0) % (u8) D_800D1892;
    }
    func_15060A30(var_a0, D_800D154C);
}
void func_15079A28(void) {
    D_800D154C->pad252[0] = D_800D1890;
    D_800D154C->pad252[1] = D_800D1891;
}
extern s16 *D_800D2110;

void func_15079A58(void) {
    D_800D2110[D_800D154C->pad10F[0x30]] = (D_800D1890 << 8) + D_800D1891;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079A98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079B30.s")
void func_15079F24(void) {
    *(f32 *)((u8 *)D_800D154C + 0x48) = D_800D1898[D_800D1890];
}
void func_15079F50(void) {
    D_800D154C->field_23B = D_800D1890;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15079F6C CURRENT (150) */
void func_15079F6C(void) {
    *(s16 *)((u8 *)D_800D154C + 0x224) = (s16) ((D_800D1890 << 8) | D_800D1891);
    D_800D154C->pad22A[1] = D_800D1892;
    D_800D154C->pad223[3] = D_800D1893;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15079F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079F6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079FBC.s")
typedef struct {
    u8 pad_0[8];
    s16 values[1][4];
} GameA28B0ValueGrid;

extern GameA28B0ValueGrid **D_800D2104;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A100 CURRENT (220) */
void func_1507A100(void) {
    s16 value;

    value = ((s8)D_800D1892 << 8) | D_800D1893;
    D_800D2104[D_800D154C->pad10F[0x30]]->values[D_800D1890][D_800D1891] =
        value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A100 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A100.s")
extern f32 D_800CC30C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A164 CURRENT (740) */
void func_1507A164(void) {
    s32 var_v0;
    u8 var_v1;

    var_v1 = D_800D1891;
    var_v0 = (s32) (D_800CC30C + (f32) (s8) D_800D1892);
    if (var_v0 < (s32) var_v1) {
        goto block_3;
    }
    var_v1 = D_800D1890;
    if ((s32) var_v1 < var_v0) {
block_3:
        var_v0 = (s32) var_v1;
    }
    *(f32 *)((u8 *)D_800D154C + 0x44) = (f32) var_v0;
    if (*(f32 *)((u8 *)D_800D154C + 0x44) == 1.0f) {
        *(f32 *)((u8 *)D_800D154C + 0x44) = 0.5f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A164 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A164.s")
void func_1507A210(void) {
    D_800D154C->pad223[0] = 0;
    *(s16 *)((u8 *)D_800D154C + 0x21C) = (s16) (D_800D1890 * 0x64);
    *(u16 *)((u8 *)D_800D154C + 0x22C) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x22C) & 0xFD);
    func_15075498();
}
/* Call context: func_1503DE70: unique active project prototype */

void func_1507A270(void) {
    func_1503DE70(D_800D154C, (s32) D_800D1890, (s32) (s8) D_800D1891);
}
/* Call context: func_15075CA0: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A2A4 CURRENT (40) */
void func_1507A2A4(void) {
    D_800D1893 += func_150ADA20() % (u8) D_800D1891;
    func_15075CA0();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A2A4 */
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A71C CURRENT (1170) */
void func_1507A71C(void) {
    s32 temp_t9;

    temp_t9 = ((D_800D1891 << 8) | D_800D1892) & 0xFFFF;
    if (temp_t9 == (func_1507A6FC((s32) D_800D1890) & 0xFFFF & temp_t9)) {
        func_15075400((s32) D_800D1893);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A71C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A71C.s")
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A774 CURRENT (90) */
void func_1507A774(void) {
    if (D_800BE9F0 == (((D_800D1891 << 8) | D_800D1892) & 0xFFFF)) {
        func_15075400((s32) D_800D1890);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A774 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A774.s")
void func_1507A7C0(void) {
    D_800D154C->field_89 = D_800D1890;
}
void func_1507A7DC(void) {
    func_150836CC(D_800D154C, D_800D1890);
}
void func_1507A808(void) {
    *(u16 *)((u8 *)D_800D154C + 0x22C) = (u16) ((*(u16 *)((u8 *)D_800D154C + 0x22C) & D_800D1890) | D_800D1891);
}
void func_1507A838(void) {
    if (D_800D1891 == D_800D154C->pad10F[0xBB]) {
        func_15075400((s32) D_800D1890);
    }
}
void func_1512D748(void *arg0, s32 arg1, s32 arg2);

void func_1507A878(void) {
    func_1512D748(0, (s32) D_800D1890, (s32) D_800D1891);
}
extern u8 D_800BE616;
extern u8 D_800CC335;

void func_1507A8A8(void) {
    if ((D_800CC335 != 0) || (D_800BE616 != 0)) {
        func_15075400((s32) D_800D1890);
    }
}
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
void func_1507AD30(void) {
    *(u8 *)((u8 *)D_800D154C + 0x255) = D_800D1890;
    *(u8 *)((u8 *)D_800D154C + 0x256) = D_800D1891;
}
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
/* Call context: func_15062B1C: unique active project prototype */
/* Call context: func_15062B50: unique active project prototype */
void func_15062B1C(void *, f32);
void func_15062B50(void *, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507B178 CURRENT (50) */
void func_1507B178(void) {
    s16 temp_v1;

    temp_v1 = (D_800D1891 << 8) | D_800D1890;
    if (D_800D1893 == 2) {
        *(s16 *)((u8 *)D_800D154C + 0xE8) = (s16) (s32) ((f32) temp_v1 * *(f32 *)((u8 *)D_800D154C + 0x150));
        return;
    }
    if (D_800D1893 == 1) {
        func_15062B50(D_800D154C, (f32) temp_v1);
        return;
    }
    func_15062B1C(D_800D154C, (f32) temp_v1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507B178 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B178.s")
/* Call context: func_1506BAD8: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */
void func_1506BAD8(s32, s32);
s32 func_1506E46C(u8 *, s32 *, s32);
extern s32 D_800D1580;
s32 func_1507A3E8(void);

void func_1507B234(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x12C, 0x708);
    }
}
/* Call context: func_1506BAD8: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */

void func_1507B280(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x12C, 0xBB8);
    }
}
/* Call context: func_1506BA4C: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */
void func_1506BA4C(s32, s32);

void func_1507B2CC(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x12C, 0x708);
    }
}
/* Call context: func_1506BA4C: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */

void func_1507B318(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x12C, 0xBB8);
    }
}
/* Call context: func_1506BAD8: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */

void func_1507B364(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x2BC, 0xFA0);
    }
}
/* Call context: func_1506BA4C: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */

void func_1507B3B0(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x2BC, 0xFA0);
    }
}
/* Call context: func_1506BAD8: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */

void func_1507B3FC(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0xBB8, 0x1F40);
    }
}
/* Call context: func_1506BAD8: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */

void func_1507B448(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0xBE, 0x514);
    }
}
/* Call context: func_1506BA4C: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */

void func_1507B494(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0xBE, 0x514);
    }
}
/* Call context: func_1506BAD8: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */

void func_1507B4E0(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x64, 0x320);
    }
}
/* Call context: func_1506BA4C: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */

void func_1507B52C(void) {
    D_800D1580 = func_1507A3E8();
    if (func_1506E46C((u8 *) D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x64, 0x320);
    }
}
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
void func_1507B5C4(void) {
    if (D_800D1891 == *(u8 *)((u8 *)D_800D154C->nested_31C + 0x75)) {
        D_800D1892 ^= 1;
    }
    if (D_800D1892 != 0) {
        func_15075400((s32)D_800D1890);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B630.s")
void func_1507B6E0(void) {
    if ((D_800D154C->field_89 != 0) || (*(f32 *)((u8 *)D_800D154C + 0x28) > 5.0f)) {
        *(s32 *)((u8 *)D_800D154C + 0x218) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x218) - 5);
        *(s16 *)((u8 *)D_800D154C + 0x21C) = 0x64;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B734.s")
void func_1507B7BC(void) {
    func_15075548();
    D_800D154C->pad223[0] = 0x11;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507B7E8 CURRENT (85) */
void func_1507B7E8(void) {
    void *temp_v0;

    temp_v0 = (D_800D154C->field_222 * 0x32C) + &D_800CC2D0;
    if ((*(u8 *)((u8 *)temp_v0 + 0x104) != 0) || (*(u8 *)((u8 *)temp_v0 + 0x1CA) == 0)) {
        D_800D1891 ^= 1;
    }
    if (D_800D1891 != 0) {
        func_15075400((s32) D_800D1890);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507B7E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B7E8.s")
typedef void (*GameA28B0Callback)(u8);

extern u8 D_80086150[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507B884 CURRENT (355) */
void func_1507B884(void) {
    GameA28B0State *saved_state;
    s32 saved_index;
    u8 selector;
    GameA28B0Callback callback;

    selector = D_800D1890;
    callback = *(GameA28B0Callback *)(D_80086150 + (selector * 4));
    if (callback != 0) {
        saved_state = D_800D154C;
        saved_index = D_800C3E78;
        callback(selector);
        D_800D154C = saved_state;
        D_800C3E78 = saved_index;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507B884 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507B884.s")
void func_1507B8F4(void) {
    void *temp_v0;

    if ((D_800BE616 != 0) && ((D_800D1891 != 0) || ((temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C), (temp_v0 != 0)) && (*(u8 *)((u8 *)temp_v0 + 0x84) != 0)))) {
        func_15075400((s32) D_800D1890);
    }
}
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
