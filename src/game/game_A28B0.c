#include "types.h"

/*
 * Reviewed source unit: src/game/game_A28B0.c
 * Boundary evidence: docs/evidence/game_dispatcher_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15075400
 * - func_15075650
 * - func_15075938
 * - func_15075F6C
 * - func_15076768
 * - func_150768DC
 * - func_15076B94
 * - func_15076D3C
 * - func_15076FA8
 * - func_15077404
 * - func_15077508
 * - func_15077C38
 * - func_1507839C
 * - func_15078544
 * - func_15078A60
 * - func_1507911C
 * - func_15079228
 * - func_15079B30
 * - func_15079F6C
 * - func_1507A2F8
 * - func_1507A3E8
 * - func_1507A428
 * - func_1507A47C
 * - func_1507A4D4
 * - func_1507AA48
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15075400 CURRENT (60) */
void func_15075400(s32 arg0) {
    u8 count;
    u8 value;

    if (arg0 < 0xF7) {
        *(u8 **) ((u8 *) D_800D154C + 0x218) += arg0 * 5;
        return;
    }
    for (count = 0; count < 100; count++) {
        value = **(u8 **) ((u8 *) D_800D154C + 0x218);
        if (value < 0xF7) {
            *(u8 **) ((u8 *) D_800D154C + 0x218) += 5;
        } else {
            *(u8 **) ((u8 *) D_800D154C + 0x218) += 1;
            if (arg0 == (value & 0xFF)) {
                *(u8 **) ((u8 *) D_800D154C + 0x218) -= 5;
                return;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15075400 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075400.s")
extern u8 D_800D1893;

void func_15075498(void) {
    u32 value;

    value = D_800D1893;
    if ((value &= 0x7F) != 0x7F) {
        *(s16 *)((u8 *)D_800D154C + 0x244) = value;
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
extern f32 D_8009A13C;
extern u8 D_800BE616;
extern u8 D_800D1892;

void func_15075548(void) {
    D_800D154C->pad223[0] = 0;
    *(s16 *)((u8 *)D_800D154C + 0x21C) = (s16) (D_800D1890 * 0x64);
    if (D_800D1892 != 0xFF) {
        *(f32 *)((u8 *)D_800D154C + 0x44) = (f32) (u32) D_800D1892;
        if (*(f32 *)((u8 *)D_800D154C + 0x44) == 1.0f) {
            *(f32 *)((u8 *)D_800D154C + 0x44) = 0.5f;
        }
        if ((D_800BE616 != 0) && (D_800D154C->pad4 == 0x28) && (*(u8 *)((u8 *)D_800D154C->nested_31C + 0x128) & 1)) {
            *(f32 *)((u8 *)D_800D154C + 0x44) = (f32) (*(f32 *)((u8 *)D_800D154C + 0x44) * D_8009A13C);
        }
    }
    func_15075498();
}
extern u8 *D_800D2108;
extern u8 D_800D1891;
u32 func_150ADA20();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15075650 CURRENT (3069) */
void func_15075650(void) {
    u8 count;
    u8 previous;
    u8 limit;
    u8 minimum;
    u8 override;
    u8 current;
    u8 selected;

    limit = D_800D2108[D_800D154C->pad10F[0x30]] - 1;
    override = D_800D154C->pad21F[0];
    if (override != 0) {
        limit = override;
    }
    minimum = D_800D154C->pad21F[1];
    count = limit;
    count -= minimum;
    if (D_800D1891 == 0xFF) {
        if (D_800D154C->pad223[0] != 13) {
            D_800D154C->field_21E = func_150ADA20() % count + D_800D154C->pad21F[1];
            goto reload_state;
        }
    } else if (D_800D1891 == 0xFE) {
        if (D_800D154C->pad223[0] != 13) {
            current = D_800D154C->field_21E;
            previous = current - 1;
            if (minimum >= current) {
                previous = limit - 1;
            }
            selected = func_150ADA20() % count + D_800D154C->pad21F[1];
            if (previous != selected) {
                D_800D154C->field_21E = selected;
            }
        }
    } else {
        if (D_800D1891 == 0xFF) {
            D_800D154C->field_21E = limit - 1;
        } else {
            D_800D154C->field_21E = D_800D1891;
        }
    }
reload_state:
    D_800D154C->pad223[0] = 0;
    *(s16 *) ((u8 *) D_800D154C + 0x21C) = D_800D1890 * 100;
    if (D_800D1892 != 0xFF) {
        *(f32 *) ((u8 *) D_800D154C + 0x44) = (f32) (u32) D_800D1892;
        if (*(f32 *) ((u8 *) D_800D154C + 0x44) == 1.0f) {
            *(f32 *) ((u8 *) D_800D154C + 0x44) = 0.5f;
        }
    }
    current = D_800D154C->pad21F[1];
    if (D_800D154C->field_21E < current) {
        D_800D154C->field_21E = current;
    }
    func_15075498();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15075650 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075650.s")
typedef struct {
    u8 pad_0[8];
    s16 values[1][4];
} GameA28B0ValueGrid;

extern GameA28B0ValueGrid **D_800D2104;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern u8 D_800D1891;

void func_15075884(void) {
    f32 x;
    f32 z;
    f32 distance;
    u8 *point;

    func_15075548();
    point = (u8 *) D_800D2104[D_800D154C->pad10F[0x30]] + D_800D154C->field_21E * 8;
    x = (f32) *(s16 *) (point + 8) - D_800D154C->position_x;
    z = (f32) *(s16 *) (point + 12) - D_800D154C->position_z;
    distance = sqrtf(x * x + z * z);
    x = (f32) (u32) D_800D1891;
    *(f32 *) ((u8 *) D_800D154C + 0x44) = 2.0f * (distance / x);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15075938 CURRENT (305) */
void func_15075938(void) {
    GameA28B0State *state;
    u8 *table;
    s32 position;
    s32 matched;
    s32 count;
    s32 desired;

    matched = 0;
    state = D_800D154C;
    position = state->field_21E - (s8)state->pad21F[2];
    if (position < 0) {
        table = D_800D2108;
        count = table[state->pad10F[0x30]];
        position += count;
        position--;
    } else {
        count = D_800D2108[state->pad10F[0x30]];
        if (position >= count - 1) {
            position = position - count + 1;
        }
    }
    desired = D_800D1891 == 0xFF ? count - 2 : D_800D1891;
    if (D_800D1892 == 0) {
        if (desired == position) {
            matched = 1;
        }
    } else if (D_800D1892 == 1) {
        if (desired != position) {
            matched = 1;
        }
    } else if (D_800D1892 == 2) {
        if (desired < position) {
            matched = 1;
        }
    } else if (position < desired) {
        matched = 1;
    }
    if (matched != 0) {
        func_15075400(D_800D1890);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15075938 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075938.s")
extern u8 D_800D1891;
extern u8 D_800D1892;

void func_15075A50(void) {
    u8 temp_v0;

    temp_v0 = D_800D154C->field_21E;
    if (((D_800D1892 == 0) && (D_800D1891 == temp_v0)) || ((D_800D1892 == 1) && (D_800D1891 != temp_v0))) {
        func_15075400((s32) D_800D1890);
    }
}
f32 fabsf(f32);
#pragma intrinsic(fabsf)

void func_15075AAC(void) {
    f32 absolute_x;
    f32 x;
    f32 z;
    u8 *point;

    func_15075548();
    point = (u8 *) D_800D2104[D_800D154C->pad10F[0x30]] + D_800D1891 * 8;
    x = (f32) *(s16 *) point - D_800D154C->position_x;
    z = (f32) *(s16 *) (point + 4) - D_800D154C->position_z;
    absolute_x = fabsf(x);
    if (fabsf(z) + absolute_x < 40.0f) {
        *(s16 *) ((u8 *) D_800D154C + 0x21C) = 0;
        *(f32 *) ((u8 *) D_800D154C + 0x3C) = 0.0f;
    }
}
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
s32 func_1507BB28(s32, s32);

void func_15075DE8(void) {
    if (D_800D1891 == 0) {
        D_800D1891 = D_800D154C->field_232;
    }
    if (D_800D1893 != 0) {
        D_800D154C->field_232 = D_800D1893;
    }
    *(s32 *)((u8 *)D_800D154C + 0x218) =
        func_1507BB28(0, D_800D1891);
    *(s32 *)((u8 *)D_800D154C + 0x218) =
        *(s32 *)((u8 *)D_800D154C + 0x218) - 5;
}
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15075F6C CURRENT (30) */
void func_15075F6C(void) {
    s32 value;

    value = D_800D1890;
    if (value != 0) {
        if (D_800D1892 == 0) {
            *(f32 *)((u8 *)D_800D154C + 0x20) = (f32)(u32)value;
        } else {
            *(f32 *)((u8 *)D_800D154C + 0x20) = (f32)-(s32)D_800D1890;
        }
    }
    if (D_800D1891 != 0) {
        *(f32 *)((u8 *)D_800D154C + 0x24) = (f32)(u32)D_800D1891;
    }
    D_800D154C->pad6[0x34] = D_800D1893;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15075F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15075F6C.s")
/* Call context: func_15075548: unique active declaration in the allowed source */
void func_15075548(void);

extern f32 D_8009A140;

void func_1507602C(void) {
    f32 temp_fa0;
    f32 temp_fv1;
    f32 var_fa1;
    void *temp_v1;

    func_15075548();
    D_800D154C->field_21E = D_800D1891;
    temp_v1 = (u8 *)D_800D2104[D_800D154C->pad10F[0x30]] + (D_800D1891 * 8);
    temp_fv1 = (f32) *(s16 *)((u8 *)temp_v1 + 8) - D_800D154C->position_x;
    temp_fa0 = (f32) *(s16 *)((u8 *)temp_v1 + 0xC) - D_800D154C->position_z;
    var_fa1 = 2.0f * (sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0)) / *(f32 *)((u8 *)D_800D154C + 0x44));
    if (var_fa1 < 12.0f) {
        *(f32 *)((u8 *)D_800D154C + 0x44) *= var_fa1 * D_8009A140;
        var_fa1 = 12.0f;
    }
    *(s16 *)((u8 *)D_800D154C + 0x21C) = (s16) (u32) (var_fa1 * 100.0f);
    *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) (*(f32 *)((u8 *)D_800D154C + 0x24) * var_fa1 * 0.5f);
    D_800D154C->pad223[0] = 4;
}
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

void func_15076250(void) {
    s32 id;

    id = (D_800D1890 << 8) | D_800D1891;
    func_15060778(id, D_800D154C, 0x7D00, -100, 500, 2500, D_800D1892);
}
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
void func_150763B0(void) {
    if (D_800D1890 == 0x80) {
        D_800D154C->pad1E5[0] = (*(u8 **)((u8 *)D_800D154C + 0x144))[0xF];
    } else {
        D_800D154C->pad1E5[0] = D_800D1890;
    }
    D_800D154C->pad1E5[2] = 0;
    if (D_800D1892 != 0) {
        D_800D154C->pad1E5[0] += func_150ADA20() % (u8) D_800D1892;
    }
    if (D_800D1893 == 1) {
        D_800D154C->pad1E5[1] = 0;
        D_800D154C->pad1E5[3] = 0;
        return;
    }
    if (D_800D1893 == 2) {
        D_800D154C->pad1E5[1] = D_800D1891;
        D_800D154C->pad1E5[3] = 0;
        return;
    }
    if (D_800D1891 == 0) {
        D_800D154C->pad1E5[1] = D_800D154C->pad1E5[0];
        D_800D154C->pad1E5[3] = 0;
    }
}
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

void func_1507652C(void) {
    if (D_800D1891 != 0) {
        D_800CC3F5[*(u8 *)((u8 *)D_800D154C + 0x124) * 0x32C] = D_800D1890;
        return;
    }
    *(u8 *)((u8 *)D_800D154C + 0x125) = D_800D1890;
}
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
void func_15076624(void) {
    s32 mask = (D_800D1890 << 24) | (D_800D1891 << 16) | (D_800D1892 << 8) | D_800D1893;

    *(s32 *) ((u8 *) D_800D154C + 0xF8) |= mask;
}
void func_15076678(void) {
    s32 mask = (D_800D1890 << 24) | (D_800D1891 << 16) | (D_800D1892 << 8) | D_800D1893;

    *(s32 *) ((u8 *) D_800D154C + 0xF8) &= ~mask;
}
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
typedef struct GameA28B0Transform {
    f32 height;
    s16 points[9];
    s32 object;
    u8 flags;
    u8 active;
    u8 pad1E[2];
    s32 field20;
} GameA28B0Transform;

typedef struct GameA28B0Position {
    f32 x;
    f32 y;
    f32 z;
} GameA28B0Position;

void func_1504715C(void *, GameA28B0State *);
void func_1514B364(f32 *, void *, s32, s32);
void func_15197A7C(GameA28B0State *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076768 CURRENT (120) */
void func_15076768(void) {
    GameA28B0Position position;
    GameA28B0Transform hit;

    switch (D_800D1890) {
    case 0:
        func_15197A7C(D_800D154C);
        return;
    case 1:
        position.x = D_800D154C->position_x;
        position.y = -390.0f;
        position.z = D_800D154C->position_z;
        func_1504715C(&hit, D_800D154C);
        func_1514B364(&position.x, &hit, 0xFF, 0);
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076768 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076768.s")
s32 func_1505A630(f32, f32, s32);
extern s32 D_800CC2D0;
extern u16 D_800CC34A;

void func_150767F4(void) {
    GameA28B0State *other;
    u16 angle;

    other = (GameA28B0State *) ((u8 *)&D_800CC2D0 + D_800D154C->field_222 * 0x32C);
    angle = func_1505A630(other->position_x - D_800D154C->position_x,
                        D_800D154C->position_z - other->position_z, 0);
    if ((((angle >> 8) -
           (*(u16 *)((u8 *)&D_800CC34A + D_800D154C->field_222 * 0x32C) >> 8) +
          D_800D1891) & 0xFF) < D_800D1891 * 2) {
        func_15075400(D_800D1890);
    }
}
typedef struct GameA28B0ObjectSlot {
    u8 bytes[0x32C];
} GameA28B0ObjectSlot;

f32 func_1505A72C(GameA28B0State *, s32 *);
extern void *D_800D1C90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150768DC CURRENT (800) */
void func_150768DC(void) {
    f32 distance;
    f32 nearest;
    GameA28B0State *other;
    GameA28B0State *selected;
    s32 index;
    s32 current_index;
    s32 width;
    u8 direction;
    u8 *record;

    nearest = D_800D1890 * 8;
    D_800D154C->field_A8 = 0;
    current_index = (GameA28B0ObjectSlot *)D_800D154C - (GameA28B0ObjectSlot *)&D_800CC2D0;
    other = (GameA28B0State *)&D_800CC2D0;
    index = 0;
    do {
        if ((other->field_0 != 0) && (*(u8 *)((u8 *)other + 0x1CA) != 0) &&
            (*(s32 *)((u8 *)other + 0xF8) & 0x20) && (index != current_index) &&
            ((D_800D1891 != 0) || (other->pad4 != D_800D154C->pad4)) &&
            !(fabsf(D_800D154C->position_y - other->position_y) > 50.0f)) {
            distance = func_1505A72C(D_800D154C, (s32 *)other);
            if (distance < nearest) {
                record = D_800D1C90[D_800D154C->pad4];
                width = record[0x17];
                direction = func_1505A630(other->position_x - D_800D154C->position_x,
                    D_800D154C->position_z - other->position_z, 0) >> 8;
                if ((((s8)D_800D154C->pad255[0x75] + (D_800D154C->field_76 >> 8) -
                    direction + width / 2) & 0xFF) < width) {
                    D_800D154C->field_A8 = index + 0x80;
                    nearest = distance;
                }
            }
        }
        index++;
        other = (GameA28B0State *)((u8 *)other + 0x32C);
    } while (index != 25);
    if (D_800D154C->field_A8 != 0) {
        *(s32 *)((u8 *)D_800D154C + 0x218) = func_1507BB28(0, D_800D1893);
        *(s32 *)((u8 *)D_800D154C + 0x218) -= 5;
        if (D_800D1892 != 0) {
            selected = (GameA28B0State *)((u8 *)&D_800CC2D0 + (D_800D154C->field_A8 & 0x7F) * 0x32C);
            *(s32 *)((u8 *)selected + 0x218) = 0;
            selected->field_232 = D_800D1892;
            selected->field_222 = current_index;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150768DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_150768DC.s")
void func_15076B5C(void) {
    D_800D154C->field_222 = D_800D154C->field_A8 & 0x7F;
}
void func_15076B78(void) {
    D_800D154C->field_5 = D_800D1890;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076B94 CURRENT (1080) */
void func_15076B94(void) {
    s32 index;
    GameA28B0ObjectSlot *entry;

    index = (GameA28B0ObjectSlot *)D_800D154C - (GameA28B0ObjectSlot *)&D_800CC2D0;
    if (D_800D1891 != 0) {
        index = 25;
    }
    if (index != 0) {
        entry = (GameA28B0ObjectSlot *)&D_800CC2D0 + index;
        do {
            if ((D_800D1890 == entry[-1].bytes[4]) && (entry[-1].bytes[0x1CA] != 0)) {
                func_15075548();
                D_800D154C->pad223[0] = 9;
                D_800D154C->field_222 = index - 1;
                *(s16 *)((u8 *)D_800D154C + 0x21C) = 1000;
                return;
            }
            index--;
            entry--;
        } while (index != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076B94 */
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
void func_15076D04(void) {
    *(f32 *)((u8 *)D_800D154C + 0x3C) = (f32)(u32)D_800D1890;
}
void func_15062BDC(GameA28B0State *, f32, f32);
extern f32 D_8009A144;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076D3C CURRENT (180) */
void func_15076D3C(void) {
    f32 scale = D_8009A144;
    s16 x = D_800D1890 | (D_800D1891 << 8);
    s16 y = D_800D1892 | (D_800D1893 << 8);

    *(f32 *) ((u8 *) D_800D154C + 0x14C) = (f32) x * scale;
    *(f32 *) ((u8 *) D_800D154C + 0x150) = (f32) y * scale;
    *(f32 *) ((u8 *) D_800D154C + 0x154) = *(f32 *) ((u8 *) D_800D154C + 0x14C);
    *(f32 *) ((u8 *) D_800D154C + 0x158) = *(f32 *) ((u8 *) D_800D154C + 0x150);
    func_15062BDC(D_800D154C, *(f32 *) ((u8 *) D_800D154C + 0x14C), *(f32 *) ((u8 *) D_800D154C + 0x150));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076D3C */
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
void func_15076F78(void) {
    s32 value;

    value = *(s8 *)&D_800D1890;
    *(s16 *)((u8 *)D_800D154C + 0xCC) = value;
    value = *(s8 *)&D_800D1891;
    *(s16 *)((u8 *)D_800D154C + 0xCE) = value;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15076FA8 CURRENT (390) */
void func_15076FA8(void) {
    f32 minimum;
    s16 offset;

    if (D_800D1893 == 0) {
        offset = (func_150ADA20() % D_800D1890) - ((s32)D_800D1890 / 2);
        D_800D154C->position_x += (f32)offset * 3.0f;
        offset = (func_150ADA20() % D_800D1891) - ((s32)D_800D1891 / 2);
        D_800D154C->position_z += (f32)offset * 3.0f;
        return;
    }
    minimum = (f32)(u32)D_800D1893;
    if (*(f32 *)((u8 *)D_800D154C + 0x3C) < minimum) {
        *(f32 *)((u8 *)D_800D154C + 0x3C) = minimum;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15076FA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15076FA8.s")
extern f32 D_800CC30C;

void func_150770E4(void) {
    if (*(f32 *)((u8 *) &D_800CC30C + (D_800D154C->field_222 * 0x32C)) < (f32)(u32)D_800D1892) {
        func_15075400((s32) D_800D1893);
    }
}
void func_15077174(void) {
    D_800D154C->field_10E = D_800D1890;
}
void func_10010630(u16, GameA28B0State *, s32, s32, s32);

void func_15077190(void) {
    s32 value;
    s32 shiftedByte;

    value = (D_800D1890 << 8) | D_800D1891;
    if (value != 0) {
        shiftedByte = D_800D1892 << 7;
        func_10010630(value, D_800D154C, shiftedByte, 0x1F4, 0x9C4);
    }
}
/* Call context: func_1502EA60: unique active project prototype */
/* Call context: func_1502EA7C: unique active project prototype */
/* Call context: func_1506160C: unique active project prototype */
void func_1502EA60(u8 *, s32);
void func_1502EA7C(u8 *, s32);

void func_150771F0(void) {
    s32 first;
    s32 second;
    s32 mode;

    if (D_800D1893 == 0) {
        first = D_800D1890;
        second = D_800D1891;
        if (D_800D1892 != 0) {
            mode = 1;
        } else {
            mode = 2;
        }
        func_1506160C((u8 *) D_800D154C, mode, first, second, 0U);
        return;
    }
    if (D_800D1892 == 0) {
        func_1502EA60((u8 *) D_800D154C, (s32) D_800D1890);
        return;
    }
    func_1502EA7C((u8 *) D_800D154C, (s32) D_800D1890);
}
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15077404 CURRENT (260) */
void func_15077404(void) {
    s16 var_v0;
    s16 delta;

    if (D_800D1893 != 0) {
        var_v0 = D_800D154C->pad23F[0xA] + ((D_800D154C->pad23F[7] & 0x1F) << 8);
        delta = (D_800D1891 << 8) + D_800D1892;
        var_v0 += delta * D_800BE9E4;
        if (var_v0 < 0) {
            var_v0 = 0;
        }
        D_800D154C->pad23F[7] = (var_v0 >> 8) | 0x80;
        D_800D154C->pad23F[0xA] = (u8) var_v0;
    } else {
        D_800D154C->pad23F[7] = D_800D1890;
    }
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
s32 func_15086CBC(s32, f32 *, f32 *, f32 *);
s32 func_15086098(f32, f32, f32, s8, s8, u8 *, u8 *);
s32 func_15086364(s32, s8, s8, u8 *, u8 *);
f32 func_150ADA68(void);
extern u8 *D_800D2350;
extern s32 D_800D2354;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15077508 CURRENT (8222) */
void func_15077508(void) {
    s32 target;
    f32 x;
    f32 y;
    f32 z;
    s8 first_flag;
    s8 second_flag;
    s32 index;
    s32 choice;
    f32 best;
    f32 random;
    f32 width;
    f32 dx;
    f32 dz;
    f32 length;
    u8 *node;

    target = 0xFF;
    if (D_800D1890 != 1) {
        if (D_800D154C->pad1E5[0x2C] == D_800D154C->pad1E5[0x2A]) {
            *(s16 *)((u8 *)D_800D154C + 0x216) = 0;
            *(s32 *)((u8 *)D_800D154C + 0x25C) |= 0x800;
            return;
        }
        if (D_800D154C->pad1E5[0x2C] == 0xFF) {
            *(s16 *)((u8 *)D_800D154C + 0x216) = 0;
        }
    }
    *(s32 *)((u8 *)D_800D154C + 0x25C) &= ~0x800;
    if (D_800D2108[D_800D154C->pad10F[0x30]] - 1 > 0) {
        second_flag = 0;
        first_flag = 0;
        if (D_800D154C->pad1E5[0x2C] != 0xFF) {
            first_flag = 1;
        }
        if (D_800D154C->pad1E5[0x2D] != 0xFF) {
            second_flag = 1;
        }
        if (D_800D154C->pad1E5[0x2A] == 0xFF) {
            if (D_800D1890 == 1) {
                second_flag = 0;
                first_flag = 0;
                target = D_800D154C->pad1E5[0x2B];
            }
            if (target == 0xFF) {
                target = func_15086098(D_800D154C->position_x, D_800D154C->position_y,
                    D_800D154C->position_z, first_flag, second_flag,
                    &D_800D154C->pad1E5[0x2C], &D_800D154C->pad1E5[0x2D]);
            }
        } else if (D_800D154C->pad1E5[0x2A] != 0xFF) {
            if (D_800D1890 == 1) {
                choice = 0xFF;
                if (D_800D154C->pad1E5[0x2B] != 0xFF) {
                }
                best = 10.0f;
                index = 0;
                node = D_800D2350 + D_800D154C->pad1E5[0x2A] * 16;
                do {
                    if (node[9] != 0xFF && D_800D154C->pad1E5[0x2B] != node[9]) {
                        random = func_150ADA68();
                        if (random < best) {
                            best = random;
                            choice = node[9];
                        }
                    }
                    index++;
                    node++;
                } while (index != 5);
                target = choice;
                if (choice == 0xFF) {
                    *(s32 *)((u8 *)D_800D154C + 0x25C) |= 0x800;
                    target = D_800D154C->pad1E5[0x2B];
                }
            } else {
                target = func_15086364(D_800D154C->pad1E5[0x2A], first_flag, second_flag,
                    &D_800D154C->pad1E5[0x2C], &D_800D154C->pad1E5[0x2D]);
            }
        }
        if (target != 0xFF) {
            D_800D154C->field_21E = 0;
            if (func_15086CBC(target, &x, &y, &z) != 0) {
                *(s16 *)((u8 *)D_800D154C + 0x216) = D_800D2354;
                D_800D154C->pad1E5[0x2B] = D_800D154C->pad1E5[0x2A];
                D_800D154C->pad1E5[0x2A] = target;
                width = (f32)(u32)D_800D2350[target * 16 + 8];
                dx = x - D_800D154C->position_x;
                dz = z - D_800D154C->position_z;
                width = 2.0f * width;
                length = sqrtf(dx * dx + dz * dz);
                if (length > 1.0f) {
                    length = func_150ADA68() * width / length;
                    x -= dz * length;
                    z += dx * length;
                }
                D_800D2104[D_800D154C->pad10F[0x30]]->values[0][0] = (s32)x;
                D_800D2104[D_800D154C->pad10F[0x30]]->values[0][1] = (s32)y;
                D_800D2104[D_800D154C->pad10F[0x30]]->values[0][2] = (s32)z;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15077508 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15077508.s")
void func_150778F0(void) {
    u8 limit;
    u8 override;
    u8 minimum;

    limit = D_800D2108[D_800D154C->pad10F[0x30]] - 1;
    override = D_800D154C->pad21F[0];
    if (override != 0) {
        limit = override;
    }
    D_800D154C->field_21E += (s8) D_800D154C->pad21F[2];
    D_800D154C->field_21E += limit;
    D_800D154C->field_21E %= limit;
    minimum = D_800D154C->pad21F[1];
    if (D_800D154C->field_21E < minimum) {
        D_800D154C->field_21E = minimum;
    }
}
void func_150779A8(void) {
    func_15075650();
    D_800D154C->pad223[0] = 0xB;
}
f32 func_1505A6F8(GameA28B0State *, s32 *);
extern u8 D_800C3E78;
extern s32 D_800CC2D0;

void func_150779D4(void) {
    s32 *temp_a1;
    u8 var_v0;
    f32 distance;
    f32 threshold;

    var_v0 = 0;
    if (D_800D1892 != 0) {
        var_v0 = D_800D154C->field_222;
    }
    if ((var_v0 != *(u8 *) &D_800C3E78) && ((temp_a1 = (s32 *) ((u8 *) &D_800CC2D0 + var_v0 * 0x32C), (*(s32 *)((u8 *)temp_a1 + 0) != 1)) || (*(u8 *)((u8 *)temp_a1 + 0x65) == 0)) && ((distance = func_1505A6F8(D_800D154C, temp_a1)) < (threshold = (f32) (D_800D1893 * 8)))) {
        func_15075400((s32) D_800D1890);
    }
}
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
void func_15077B80(void) {
    s32 mask;

    mask = (D_800D1890 << 8) + D_800D1891;
    *(s32 *)((u8 *)D_800D154C + 0x25C) |= mask;
}
void *func_1505F0AC(u8);                            /* extern */

void func_15077BB4(void) {
    void *temp_v0;

    temp_v0 = func_1505F0AC(D_800D1891);
    *(s32 *)((u8 *)temp_v0 + 0x218) = 0;
    *(u8 *)((u8 *)temp_v0 + 0x232) = (u8) D_800D1890;
}
void func_15077BE4(void) {
    s32 mask;

    mask = (D_800D1890 << 8) + D_800D1891;
    mask = ~mask;
    *(s32 *)((u8 *)D_800D154C + 0x25C) &= mask;
}
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
void func_15077DBC(void) {
    if (D_800D1890 != 0xFA) {
        D_800D154C->field_21E = D_800D1890;
    }
    D_800D154C->position_x = D_800D2104[D_800D154C->pad10F[0x30]]->values[D_800D154C->field_21E][0];
    D_800D154C->position_y = D_800D2104[D_800D154C->pad10F[0x30]]->values[D_800D154C->field_21E][1];
    D_800D154C->position_z = D_800D2104[D_800D154C->pad10F[0x30]]->values[D_800D154C->field_21E][2];
}
/* Call context: func_10012718: unique active project prototype */
void func_10012718(u16, u8 *, s32, s16, s32);

void func_15077E9C(void) {
    s32 id = (D_800D1890 << 8) + D_800D1891;

    func_10012718(id, (u8 *) D_800D154C, 0x5DC0, 0x1F4, 0x9C4);
}
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
void func_15056A00(GameA28B0State *, u8, u8);
extern u8 D_80099A3C;

void func_15077F64(void) {
    s32 pad[2];
    u8 angle;
    u8 mode;
    s16 *point;
    f32 x;
    f32 z;

    mode = D_800D1890 - 1;
    point = (s16 *)((u8 *)D_800D2104[D_800D154C->pad10F[0x30]] + D_800D154C->field_21E * 8);
    x = (f32)point[4] - D_800D154C->position_x;
    z = D_800D154C->position_z - (f32)point[6];
    D_800D154C->field_78 = func_1505A630(x, z, 0);
    angle = (D_800D154C->field_78 - D_800D154C->field_76) >> 8;
    if (angle & 0x80) {
        angle = -angle;
    }
    if ((&D_80099A3C)[mode * 10] < angle) {
        D_800D154C->pad24B[5] = D_800D1891;
        func_15056A00(D_800D154C, angle, mode);
    }
}
f32 func_1505A6F8(GameA28B0State *, s32 *);         /* extern */
extern u8 D_800C3E78;
extern s32 D_800CC2D0;

void func_15078074(void) {
    f32 temp_fs0;
    s32 var_s0;
    s32 *var_s1;

    temp_fs0 = (f32) (D_800D1893 * 8);
    for (var_s0 = 0, var_s1 = &D_800CC2D0; var_s0 < 0x19; var_s0++, var_s1 = (s32 *) ((u8 *) var_s1 + 0x32C)) {
        if ((*var_s1 != 0) && (var_s0 != D_800C3E78) && (func_1505A6F8(D_800D154C, var_s1) < temp_fs0)) {
            func_15075400((s32) D_800D1890);
            return;
        }
    }
}
void func_1507813C(void) {
    s32 index = D_800D154C->field_222;

    if (*(s32 *) ((u8 *) &D_800CC2D0 + index * 0x32C) == 0) {
        func_15075400((s32) D_800D1890);
    }
}
void func_150781A4(void) {
    D_800D154C->pad23F[0] = D_800D1891;
    D_800D154C->pad23F[1] = D_800D1892;
    D_800D154C->pad23F[2] = D_800D1890;
    D_800D154C->pad23F[3] = D_800D1893;
}
void func_150781F4(void) {
    f32 x;
    f32 z;
    f32 distance;
    s16 *point;
    s32 index;

    index = D_800D1891 + 1;
    point = (s16 *)((u8 *)D_800D2104[D_800D154C->pad10F[0x30]] + index * 8);
    x = (f32)point[0] - D_800D154C->position_x;
    z = (f32)point[2] - D_800D154C->position_z;
    distance = sqrtf(x * x + z * z);
    x = (f32)(D_800D1893 * 8);
    if (((D_800D1892 == 0) && (distance < x)) ||
        ((D_800D1892 != 0) && (x < distance))) {
        func_15075400(D_800D1890);
    }
}
void func_150782CC(void) {
    D_800D154C->field_23E = D_800D1890;
}
void func_150782E8(void) {
    if (((D_800D1892 == 0) && (D_800D1891 == D_800D154C->pad6[0x35])) || ((D_800D1892 == 1) && (D_800D1891 != D_800D154C->pad6[0x35]))) {
        func_15075400((s32) D_800D1890);
    }
}
s32 func_15083FB0(s32);

void func_15078358(void) {
    s32 temp_v0;

    temp_v0 = func_15083FB0(D_800D1890);
    D_800D154C->field_222 = temp_v0;
    if (temp_v0 == -1) {
        D_800D154C->field_222 = 0;
    }
}
extern f32 D_800CC2E8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507839C CURRENT (1670) */
void func_1507839C(void) {
    f32 var_fv0;
    f32 var_fv1;

    if (D_800D1892 == 0) {
        var_fv0 = func_1505A6F8(D_800D154C, (D_800D154C->field_222 * 0x32C) + &D_800CC2D0);
    } else if (D_800D1892 == 1) {
        var_fv0 = func_1505A72C(D_800D154C, (D_800D154C->field_222 * 0x32C) + &D_800CC2D0);
    } else {
        var_fv0 = fabsf(D_800D154C->position_y - *(&D_800CC2E8 + (D_800D154C->field_222 * 0x32C)));
    }
    var_fv1 = (f32) (D_800D1893 * 8);
    if (D_800D1893 == 0xFF) {
        var_fv1 = (f32) (D_800D154C->field_23D * 8);
    }
    if (((D_800D1891 == 0) && (var_fv0 < var_fv1)) || ((D_800D1891 == 1) && (var_fv1 < var_fv0))) {
        func_15075400((s32) D_800D1890);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507839C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507839C.s")
void func_15078520(void) {
    func_15075400((s32) D_800D1890);
}
f32 func_15047D60(f32);
f32 func_150484A0(f32, f32);
f32 func_15047C00(f32);
f32 func_150489B0(u8);
f32 func_15048A40(u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15078544 CURRENT (555) */
void func_15078544(void) {
    f32 x;
    f32 y;
    f32 z;
    f32 offset_x;
    f32 offset_z;
    f32 cosine;
    f32 sine;
    f32 radians;
    u8 angle;
    GameA28B0State *other;
    s32 mode;
    s32 command;

    command = D_800D1890;
    mode = command >> 6;
    D_800D1890 = command & 0x3F;
    other = (GameA28B0State *)((u8 *)&D_800CC2D0 + D_800D154C->field_222 * 0x32C);
    x = other->position_x;
    y = other->position_y;
    z = other->position_z;
    offset_x = (((s8)D_800D1891 * 16) | (D_800D1893 >> 4)) * 8;
    offset_z = (((s8)D_800D1892 * 16) | (D_800D1893 & 15)) * 8;
    if (mode == 0) {
        angle = (other->field_7A >> 8) - 0x40;
        cosine = func_15048A40(angle);
        sine = func_150489B0(angle);
    } else if (mode == 1) {
        cosine = 0.0f;
        sine = 1.0f;
    } else {
        radians = func_150484A0(D_800D154C->position_x - x, D_800D154C->position_z - z);
        cosine = func_15047D60(radians);
        sine = func_15047C00(radians);
    }
    x += offset_x * sine + offset_z * cosine;
    z += offset_z * sine - offset_x * cosine;
    *(s16 *)((u8 *)D_800D2104[D_800D154C->pad10F[0x30]] + D_800D1890 * 8 + 8) = (s32)x;
    *(s16 *)((u8 *)D_800D2104[D_800D154C->pad10F[0x30]] + D_800D1890 * 8 + 10) = (s32)y;
    *(s16 *)((u8 *)D_800D2104[D_800D154C->pad10F[0x30]] + D_800D1890 * 8 + 12) = (s32)z;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15078544 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078544.s")
extern u8 D_800CC5A0[];

void func_1507879C(void) {
    f32 value;
    f32 *state;

    state = *(f32 **)(D_800CC5A0 + D_800D154C->field_222 * 0x32C);
    value = state[2];
    if (((D_800D1892 == 0) && (value < (f32)(u32)D_800D1891)) ||
        ((D_800D1892 == 1) && ((f32)(u32)D_800D1891 < value))) {
        func_15075400(D_800D1890);
    }
}
void func_15078874(void) {
    D_800D154C->field_251 = D_800D1890;
}
void func_15078890(void) {
    u32 mode = D_800D1892;

    if (((mode == 0) && (D_800D1891 == *(u8 *)((u8 *)D_800D154C + 0x251))) || ((mode == 1) && (D_800D1891 != *(u8 *)((u8 *)D_800D154C + 0x251)))) {
        func_15075400((s32) D_800D1890);
    }
}
extern u8 D_800CC521;

void func_15078900(void) {
    if (D_800D1893 != 0) {
        if (D_800D154C->field_222 == 0) {
            func_15075400((s32) D_800D1890);
        }
    } else if (((D_800D1892 == 0) && (D_800D1891 == *(&D_800CC521 + (D_800D154C->field_222 * 0x32C)))) || ((D_800D1892 == 1) && (D_800D1891 != *(&D_800CC521 + (D_800D154C->field_222 * 0x32C))))) {
        func_15075400((s32) D_800D1890);
    }
}
extern u8 D_800CC5A0[];

void func_15078A08(void) {
    void *temp_a0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x2D0);
    temp_a0 = *(void **)(D_800CC5A0 + (D_800D154C->field_222 * 0x32C));
    *(f32 *)((u8 *)temp_v0 + 8) = *(f32 *)((u8 *)temp_a0 + 8);
    *(f32 *)((u8 *)temp_v0 + 0xC) = *(f32 *)((u8 *)temp_a0 + 0xC);
}
extern f32 D_8009A198;
extern u8 D_800BE9EC;
extern f32 D_800CC2F8;
extern f32 D_800CC314;
extern u8 D_800CC359;
extern u8 D_800CC3D2;
extern u8 D_800CC3D4[];
extern u8 D_800CC40C;
extern u8 D_800CC49A;
extern u8 D_800CC502;
extern s32 D_800CC5B4;
extern s32 D_800CC5B8;
extern s32 D_800CC5BC;
extern void *D_800CC5EC;
extern u8 D_800CC2D4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15078A60 CURRENT (1620) */
s32 func_15078A60(s32 arg0) {
    s32 value;
    u8 heading;
    s32 difference;
    GameA28B0State *other;
    u8 *nested;

    switch (D_800D1892) {
    case 0:
        value = (s32)*(f32 *)((u8 *)&D_800CC30C + arg0 * 0x32C);
        break;
    case 1:
        value = *(s32 *)((u8 *)&D_800CC5B4 + arg0 * 0x32C);
        break;
    case 2:
        value = *(s32 *)((u8 *)&D_800CC5B8 + arg0 * 0x32C);
        break;
    case 3:
        value = *(s32 *)((u8 *)&D_800CC5BC + arg0 * 0x32C);
        break;
    case 4:
        value = (s32)*(f32 *)((u8 *)&D_800CC2E8 + arg0 * 0x32C);
        break;
    case 5:
        value = (s32)*(f32 *)((u8 *)&D_800CC314 + arg0 * 0x32C);
        break;
    case 6:
        other = (GameA28B0State *)((u8 *)&D_800CC2D0 + arg0 * 0x32C);
        heading = (other->field_7A >> 8) - 0x40;
        difference = ((u32)(func_150484A0(other->position_x - D_800D154C->position_x,
            other->position_z - D_800D154C->position_z) * D_8009A198) - heading) & 0xFF;
        value = difference;
        if (difference > 128) {
            value = 256 - difference;
        }
        break;
    case 7:
        value = *((u8 *)&D_800CC40C + arg0 * 0x32C);
        break;
    case 8:
        value = D_800CC3D4[arg0 * 0x32C];
        break;
    case 9:
        nested = *(u8 **)((u8 *)&D_800CC5EC + arg0 * 0x32C);
        value = 0;
        if (*(s16 *)(nested + 8) != 0 && nested[0x16] != 0) {
            value = 2;
        }
        break;
    case 10:
        value = (s32)*(f32 *)((u8 *)&D_800CC2F8 + arg0 * 0x32C);
        break;
    case 11:
        value = *((u8 *)D_800CC5EC + 0x78);
        break;
    case 12:
        value = *((u8 *)D_800CC5EC + 0x7D);
        break;
    case 13:
        value = D_800CC3D2;
        break;
    case 14:
        value = D_800BE9EC;
        break;
    case 15:
        value = *((u8 *)&D_800CC2D4 + D_800D154C->field_222 * 0x32C);
        break;
    case 16:
        value = *((u8 *)&D_800CC49A + arg0 * 0x32C);
        break;
    case 17:
        value = *((u8 *)&D_800CC502 + D_800D154C->field_222 * 0x32C);
        break;
    case 18:
        value = *((u8 *)&D_800CC359 + arg0 * 0x32C);
        break;
    }
    if (((D_800D1891 == 0) && (value == D_800D1893)) ||
        ((D_800D1891 == 1) && (value != D_800D1893)) ||
        ((D_800D1891 == 2) && (value < D_800D1893)) ||
        ((D_800D1891 == 3) && (D_800D1893 < value)) ||
        ((D_800D1891 == 4) && (D_800D1893 >= value)) ||
        ((D_800D1891 == 5) && (value >= D_800D1893))) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15078A60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15078A60.s")
s32 func_15078A60(s32);

void func_1507900C(void) {
    if (func_15078A60(0U) != 0) {
        func_15075400((s32) D_800D1890);
    }
}
s32 func_15078A60(s32);                              /* extern */
s32 func_1507BB28(s32, s32);                         /* extern */

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
s32 func_1507BB28(s32, s32);

void func_150790C4(void) {
    if (func_15078A60(D_800C3E78) != 0) {
        *(s32 *)((u8 *)D_800D154C + 0x218) = func_1507BB28(0, D_800D1890);
        *(s32 *)((u8 *)D_800D154C + 0x218) -= 5;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507911C CURRENT (740) */
void func_1507911C(void) {
    s16 threshold;
    s16 coordinate;
    s32 index;
    GameA28B0State *state;

    threshold = (D_800D1891 << 8) | D_800D1892;
    index = D_800D1893;
    index &= 1;
    if (index != 0) {
        index = D_800C3E78;
    }
    state = (GameA28B0State *)((u8 *)&D_800CC2D0 + index * 0x32C);
    coordinate = (s32)state->position_y;
    if (D_800D1893 & 2) {
        coordinate = (s32)state->position_x;
    }
    if (coordinate < threshold) {
        func_15075400(D_800D1890);
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
/* Call context: func_1505A630: unique active project prototype */
/* Call context: func_1505D024: unique active project prototype */
s32 func_1505A630(f32, f32, s32);
void func_1505D024(s32, s32, s32, s32);
extern s32 D_800D3098;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15079228 CURRENT (70) */
void func_15079228(void) {
    s16 *temp_v0;
    f32 x;
    f32 z;
    s32 temp_v0_2;
    s32 var_a2;

    temp_v0 = (s16 *) ((u8 *) D_800D3098 + D_800D154C->field_251 * 0x34);
    x = (f32) temp_v0[0];
    z = (f32) temp_v0[2];
    temp_v0_2 = func_1505A630(D_800D154C->position_x - x, z - D_800D154C->position_z, 0);
    var_a2 = temp_v0_2 & 0xFFFF;
    if (temp_v0_2 == 0) {
        var_a2 = 1;
    }
    func_1505D024((s32) D_800D154C, (s32) D_800D1890, var_a2, -1);
    *(s32 *)((u8 *)D_800D154C + 0x218) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x218) - 5);
    *(s16 *)((u8 *)D_800D154C + 0x21C) = 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15079228 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079228.s")
void func_150792E0(void) {
    D_800D154C->field_232 = D_800D1890;
}
void func_150792FC(void) {
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) & 0xFFF8);
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) | D_800D1890);
}
void func_15079334(void) {
    u8 *temp_v1;
    u32 temp_v0;

    temp_v0 = D_800D154C->field_A8;
    if (temp_v0 != 0) {
        temp_v1 = (u8 *) &D_800CC2D0 + ((temp_v0 & 0x7F) * 0x32C);
        *(s32 *)((u8 *)temp_v1 + 0x218) = 0;
        *(u8 *)((u8 *)temp_v1 + 0x232) = (u8) D_800D1890;
    }
}
/* Raw callee sign-extends arg1 to 16 bits and returns its result in v0. */
extern s32 func_1514D3B0(void *arg0, s16 arg1, s32 arg2, s32 arg3);

void func_15079390(void) {
    s32 temp_v0;
    s32 second;
    s32 third;

    temp_v0 = D_800D1890;
    second = D_800D1891;
    third = D_800D1892;
    func_1514D3B0(D_800D154C, temp_v0, second, third);
}
void func_1505A184(u16, f32, f32, f32 *, f32 *, f32 *);

void func_150793D8(void) {
    f32 offset_x;
    f32 offset_z;
    f32 offset_y;
    u32 random;
    u16 angle;
    s16 x;
    s16 z;

    x = (s32)((GameA28B0State *)&D_800CC2D0)->position_x;
    z = (s32)((GameA28B0State *)&D_800CC2D0)->position_z;
    if ((x < -1180) || (x > 1180) || (z < -1180) || (z > 1180)) {
        x = 0;
        z = 0;
    }
    random = func_150ADA20();
    angle = random;
    func_1505A184(angle, 550.0f, 0.0f, &offset_x, &offset_z, &offset_y);
    x = (s32)(x + offset_x);
    z = (s32)(z + offset_z);
    if (x < -1200) {
        x = -1200;
    }
    if (x > 1200) {
        x = 1200;
    }
    if (z < -1200) {
        z = -1200;
    }
    if (z > 1200) {
        z = 1200;
    }
    *(s16 *)((u8 *)D_800D2104[D_800D154C->pad10F[0x30]] + D_800D1890 * 8 + 8) = x;
    *(s16 *)((u8 *)D_800D2104[D_800D154C->pad10F[0x30]] + D_800D1890 * 8 + 0xC) = z;
}
extern f32 D_800CC2E8;

void func_15079570(void) {
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = func_1505A6F8(D_800D154C, (s32 *) ((u8 *) &D_800CC2D0 + D_800D154C->field_222 * 0x32C));
    *(f32 *)((u8 *)D_800D154C + 0x44) = (f32) *(f32 *)((u8 *)D_800D154C + 0x3C);
    temp_fv1 = 2.0f * (temp_fv0 / *(f32 *)((u8 *)D_800D154C + 0x44));
    *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) (*(f32 *)((u8 *)D_800D154C + 0x24) * temp_fv1 * 0.5f);
    *(f32 *)((u8 *)D_800D154C + 0x20) += 2.0f * ((*(f32 *) ((u8 *) &D_800CC2E8 + D_800D154C->field_222 * 0x32C) - D_800D154C->position_y) / temp_fv1);
}
typedef struct GameA28B0ResetState {
    u8 pad0[0x218];
    s32 timer;
    u8 pad21C[0x16];
    u8 mode;
    u8 pad233[7];
    s8 flag;
} GameA28B0ResetState;

void func_1507965C(void) {
    s32 index;
    GameA28B0ResetState *state;

    index = func_15083FB0(D_800D1890);
    if (index != -1) {
        state = (GameA28B0ResetState *) ((u8 *) &D_800CC2D0 + index * 0x32C);
        state->mode = D_800D1891;
        state->timer = 0;
        state->flag = 0;
    }
}
extern u8 D_800CC3D4[];

void func_150796CC(void) {
    s32 index;

    index = func_15083FB0(D_800D1890);
    if (D_800D1892 != 0) {
        if (index != -1) {
            D_800CC3F5[index * 0x32C] = D_800D1891;
        }
    } else if (index != -1 && D_800CC3D4[index * 0x32C] != 0) {
        func_15075400(D_800D1891);
    }
}
void func_15079790(void) {
    s16 x;
    s16 z;

    if (D_800D1892 != 0) {
        D_800D154C->pad4 = 0xFF;
        return;
    }
    D_800D154C->pad4 = 0x3A;
    x = (func_150ADA20() % 500U) - 250;
    z = (func_150ADA20() % 500U) - 250;
    D_800D154C->position_x = (f32) (*(s16 *) D_800D2104[D_800D154C->pad10F[0x30]] + x);
    D_800D154C->position_z = (f32) (*(s16 *) ((u8 *) D_800D2104[D_800D154C->pad10F[0x30]] + 4) + z);
}
/* Call context: func_15075548: unique active project prototype */
extern f32 D_800CC30C;

void func_15079880(void) {
    s32 var_v0;

    var_v0 = (s32) (*(f32 *)&D_800CC30C + (f32) (s8) D_800D1892);
    if (var_v0 < (s32) D_800D1891) {
        var_v0 = (s32) D_800D1891;
    } else if (var_v0 >= 0xFB) {
        var_v0 = 0xFA;
    }
    D_800D1892 = (u8) var_v0;
    func_15075548();
}
void func_150781F4(void);

void func_150798F8(void) {
    D_800D1891 = D_800D154C->field_21E;
    func_150781F4();
}
void func_1507E7E4(GameA28B0State *, u8, u8, s32, s32);

void func_15079928(void) {
    s32 value;

    value = (D_800D1891 << 16) + D_800D1892;
    if ((value &= 0xFFFF) == 0) {
        value = 0xFFFF;
    }
    func_1507E7E4(D_800D154C, D_800D1890, D_800D1893, value, 0);
}
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

/* Call context: func_1505A630: unique active declaration in the allowed source */
s32 func_1505A630(f32, f32, s32);

s32 func_15079A98(s32 arg0) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (u8 *)D_800D2104[D_800D154C->pad10F[0x30]];
    temp_v1 = (u8 *)&D_800CC2D0 + (arg0 * 0x32C);
    return func_1505A630((f32)*(s16 *)((u8 *)temp_v0 + 0) - *(f32 *)(temp_v1 + 0x14),
                  *(f32 *)(temp_v1 + 0x1C) - (f32)*(s16 *)((u8 *)temp_v0 + 4),
                  0);
}
extern s16 D_800CC264;
extern f32 D_800CC388;
extern f32 D_800CC398;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15079B30 CURRENT (1230) */
void func_15079B30(void) {
    s32 selection;
    s32 *counter;
    GameA28B0State *saved_state;
    s32 saved_index;
    u16 angle;
    s32 index;

    selection = D_800D1891;
    if ((selection == 0) || (selection == 1)) {
        index = D_800C3E78;
    } else {
        selection = func_15083FB0((selection - 2) & 0xFF);
        index = selection;
        if (selection == -1) {
            return;
        }
    }
    switch (D_800D1892) {
    case 1:
        counter = (s32 *)(index * 0x32C + 0x2E4 + (u8 *)&D_800CC2D0);
        break;
    case 2:
        counter = (s32 *)(index * 0x32C + 0x2E8 + (u8 *)&D_800CC2D0);
        break;
    case 3:
        counter = (s32 *)(index * 0x32C + 0x2EC + (u8 *)&D_800CC2D0);
        break;
    case 4:
    case 5:
        saved_state = D_800D154C;
        saved_index = D_800C3E78;
        D_800D154C = (GameA28B0State *)((u8 *)&D_800CC2D0 + index * 0x32C);
        D_800C3E78 = index;
        if (D_800D154C->field_232 != D_800D1890) {
            D_800D154C->field_232 = D_800D1890;
            *(s32 *)((u8 *)D_800D154C + 0x218) = func_1507BB28(0, D_800D154C->field_232);
            *(s16 *)((u8 *)D_800D154C + 0x21C) = 0;
        }
        D_800C3E78 = saved_index;
        D_800D154C = saved_state;
        return;
    case 6:
        *(f32 *)((u8 *)&D_800CC398 + index * 0x32C) = (f32)(u32)D_800D1890;
        return;
    case 7:
        *(f32 *)((u8 *)&D_800CC388 + index * 0x32C) = 0.0f;
        return;
    case 8:
        angle = func_15079A98(D_800D154C->field_222);
        if ((func_15079A98(D_800C3E78) - angle) & 0x8000) {
            D_800D154C->pad21F[2] = D_800D1890;
        }
        return;
    case 9:
        *(s16 *)((u8 *)D_800D154C + 0x244) = (D_800D1893 << 8) | D_800D1890;
        return;
    case 10:
        D_800D154C->field_236 = D_800D154C->field_23D + (s8)D_800D1890;
        return;
    case 11:
        D_800D154C->pad22A[0] = D_800D1890;
        return;
    }    switch (D_800D1893) {
    case 0:
        *counter = D_800D1890;
        break;
    case 1:
        *counter -= 1;
        break;
    case 2:
        *counter += D_800BE9E4;
        break;
    case 3:
        *counter += 1;
        break;
    case 4:
        *counter -= D_800BE9E4;
        break;
    case 5:
        *counter -= D_800CC264;
        break;
    case 6:
        *counter += D_800CC264;
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15079B30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079B30.s")

void func_15079F24(void) {
    *(f32 *)((u8 *)D_800D154C + 0x48) = D_800D1898[D_800D1890];
}
void func_15079F50(void) {
    D_800D154C->field_23B = D_800D1890;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15079F6C CURRENT (50) */
void func_15079F6C(void) {
    u32 high = D_800D1890;
    u8 *low = &D_800D1891;

    *(s16 *)((u8 *)D_800D154C + 0x224) = (s16) ((high << 8) | *low);
    *(u8 *) ((u8 *) D_800D154C + 0x22B) = D_800D1892;
    *(u8 *) ((u8 *) D_800D154C + 0x226) = D_800D1893;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15079F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_15079F6C.s")
extern f32 D_8009A1E4;

void func_15079FBC(void) {
    s16 speed;

    if ((*(u8 *)((u8 *)&D_800CC2D0 + 0x65) == 0) ||
        (*(f32 *)((u8 *)&D_800CC2D0 + 0x44) < 5.0f)) {
        D_800D154C->field_232 = D_800D1891;
        *(s32 *)((u8 *)D_800D154C + 0x218) = func_1507BB28(0, D_800D154C->field_232);
        *(s32 *)((u8 *)D_800D154C + 0x218) -= 5;
        return;
    }
    D_800D154C->field_78 = *(u16 *)((u8 *)((GameA28B0State *)&D_800CC2D0)->nested_31C + 0x4C);
    if (*(s8 *)((u8 *)((GameA28B0State *)&D_800CC2D0)->nested_31C + 0x4A) != 0) {
        speed = (s32)*(f32 *)((u8 *)&D_800CC2D0 + 0x44);
    } else {
        speed = (s32)(*(f32 *)((u8 *)&D_800CC2D0 + 0x44) * D_8009A1E4);
    }
    if (speed < 17) {
        D_800D1893++;
        D_800D1890 = 8;
    }
    D_800D1892 = speed;
    func_15075F40();
    *(s32 *)((u8 *)D_800D154C + 0xF4) |= 0x40;
}
void func_1507A100(void) {
    s32 value;

    value = ((s8)D_800D1892 << 8) | D_800D1893;
    D_800D2104[D_800D154C->pad10F[0x30]]->values[D_800D1890][D_800D1891] =
        value;
}
extern f32 D_800CC30C;

void func_1507A164(void) {
    s32 var_v0;
    s32 var_v1;

    var_v0 = (s32) (*(f32 *) &D_800CC30C + (f32) (s8) D_800D1892);
    var_v1 = D_800D1891;
    if (var_v0 < var_v1) {
        var_v0 = var_v1;
    } else {
        var_v1 = D_800D1890;
        if (var_v1 < var_v0) {
            var_v0 = var_v1;
        }
    }
    *(f32 *)((u8 *)D_800D154C + 0x44) = (f32) var_v0;
    if (*(f32 *)((u8 *)D_800D154C + 0x44) == 1.0f) {
        *(f32 *)((u8 *)D_800D154C + 0x44) = 0.5f;
    }
}
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

void func_1507A2A4(void) {
    D_800D1893 = (func_150ADA20() % (u8) D_800D1891) + D_800D1893;
    func_15075CA0();
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A2F8 CURRENT (469) */
void func_1507A2F8(void) {
    u32 count;
    u8 candidates[25];
    u8 *state;
    s32 index;
    u8 *selected;

    count = 0;
    for (index = 0, state = (u8 *) &D_800CC2D0; index < 25; index++, state += 0x32C) {
        if (*(s32 *) state != 0 && D_800D1890 == state[4]) {
            candidates[count++] = index;
        }
    }
    if (count != 0) {
        selected = candidates + func_150ADA20() % count;
        D_800D154C->field_A8 = D_800D154C->field_222;
        D_800D154C->field_222 = *selected;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A2F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A2F8.s")
void func_1507A3B4(void) {
    D_800D154C->field_222 = D_800D154C->field_A8;
}
void func_1507A3CC(void) {
    D_800D154C->field_229 = D_800D1890;
}
extern u8 D_800D1892;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A3E8 CURRENT (525) */
s32 func_1507A3E8(void) {
    s32 word;

    word = D_800D1890 << 24;
    word |= D_800D1891 << 16;
    word |= D_800D1892 << 8;
    word |= D_800D1893;
    return word;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A3E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A3E8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A428 CURRENT (440) */
void func_1507A428(void) {
    *(s32 *)((u8 *)D_800D154C + 0x94) = (s32) ~((D_800D1890 << 0x18) | (D_800D1891 << 0x10) | (D_800D1892 << 8) | 1 | D_800D1893);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A428 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A428.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A47C CURRENT (540) */
void func_1507A47C(void) {
    s32 mask = (D_800D1890 << 24) | (D_800D1891 << 16) | (D_800D1892 << 8) | D_800D1893;

    *(s32 *) ((u8 *) D_800D154C + 0x94) &= ~mask;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A47C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A47C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507A4D4 CURRENT (910) */
void func_1507A4D4(void) {
    s32 mask = (D_800D1890 << 24) | (D_800D1891 << 16) | (D_800D1892 << 8) | D_800D1893;

    *(s32 *)((u8 *)D_800D154C + 0x94) |= mask;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507A4D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507A4D4.s")
void func_1507A528(void) {
    s32 var_a1;
    s8 temp_v1;
    s32 var_a0;

    if (D_800D1890 == 0) {
        D_800D154C->pad21F[2] = D_800D1891;
        return;
    }
    if (D_800D1890 == 1) {
        D_800D154C->pad21F[2] = (u8) -(s8) D_800D154C->pad21F[2];
        return;
    }
    if (D_800D1890 == 2) {
        var_a0 = D_800D1892 ? D_800D1892 : D_800D2108[D_800D154C->pad10F[0x30]] - 1;
        D_800D154C->pad21F[2] = -(s8)D_800D154C->pad21F[2];
        temp_v1 = (s8) D_800D154C->pad21F[2];
        var_a1 = D_800D154C->field_21E + temp_v1;
        if (temp_v1 > 0) {
            var_a1 += D_800D1893;
        } else {
            var_a1 -= D_800D1893;
        }
        if (var_a1 >= (s32) var_a0) {
            var_a1 -= var_a0;
        } else if (var_a1 < 0) {
            var_a1 += var_a0;
        }
        D_800D154C->field_21E = (u8) var_a1;
    }
}
/* Call context: func_1505A630: unique active declaration in the allowed source */

void func_1507A620(void) {
    GameA28B0State *other;
    GameA28B0State *state;
    u16 angle;

    state = D_800D154C;
    angle = state->field_222;
    if (D_800D1891 != 0) {
        angle = state->field_78 >> 8;
    } else {
        other = (GameA28B0State *) ((u8 *)&D_800CC2D0 + angle * 0x32C);
        angle = (D_800D154C->field_7A - func_1505A630(other->position_x - state->position_x,
                           state->position_z - other->position_z, 0)) >> 8;
    }
    if (((angle - D_800D1892) & 0xFF) < ((D_800D1893 - D_800D1892) & 0xFF)) {
        func_15075400(D_800D1890);
    }
}
typedef struct GameA28B0Entry {
    u16 field_0;
    u8 pad2[4];
} GameA28B0Entry;

extern GameA28B0Entry D_800BE748[];

u16 func_1507A6FC(s32 arg0) {
    return D_800BE748[arg0].field_0;
}
void func_1507A71C(void) {
    s32 flags;
    u16 mask;

    flags = func_1507A6FC(D_800D1890);
    mask = (D_800D1891 << 8) | D_800D1892;
    if (((flags & 0xFFFF) & mask) == mask) {
        func_15075400(D_800D1893);
    }
}
extern s32 D_800BE9F0;

void func_1507A774(void) {
    u16 value;

    value = (D_800D1891 << 8) | D_800D1892;
    if (value == D_800BE9F0) {
        func_15075400((s32)D_800D1890);
    }
}
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
extern u8 D_800CC2D4;

void func_1507A8EC(void) {
    if (D_800D1891 == *(&D_800CC2D4 + (D_800D154C->field_222 * 0x32C))) {
        D_800D1892 ^= 1;
    }
    if (D_800D1892 != 0) {
        func_15075400((s32) D_800D1890);
    }
}
void *func_15083E90(s32);

void func_1507A984(void) {
    void *temp_v0;

    if (D_800D1890 != 0) {
        temp_v0 = func_15083E90(D_800D1890);
        if (temp_v0 != 0) {
            if (D_800D1892 == 0) {
                D_800D154C->padB1[0x50] |= 4;
            }
            if (D_800D1893 != 0) {
                D_800D154C->padB1[0x50] |= 0x40;
            }
            D_800D154C->pad20[0x45] = ((s32) ((u8 *)temp_v0 - (u8 *)&D_800CC2D0) / 812) + 1;
            *(s32 *)((u8 *)D_800D154C + 0x5C) = (s32) D_800D1891;
        }
    } else {
        D_800D154C->pad20[0x45] = 0;
    }
}
extern f32 D_8009A20C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507AA48 CURRENT (620) */
void func_1507AA48(void) {
    u16 angle;
    s32 rotation;
    GameA28B0ValueGrid *points;
    s16 *second;
    s16 *first;

    angle = (D_800D1890 << 8) | D_800D1891;
    switch (D_800D1892) {
    case 0:
        D_800D154C->field_78 = D_800D154C->field_76 + angle;
        break;
    case 1:
        D_800D154C->field_78 = D_800D154C->field_76 - angle;
        break;
    case 2:
        D_800D154C->field_78 = angle;
        break;
    case 3:
        D_800D154C->field_76 = D_800D154C->field_78;
        D_800D154C->field_7A = D_800D154C->field_78;
        break;
    case 4:
        points = D_800D2104[D_800D154C->pad10F[0x30]];
        second = (s16 *)((u8 *)points + D_800D1891 * 8);
        first = (s16 *)((u8 *)points + D_800D1890 * 8);
        rotation = (u16)(func_150484A0(second[4] - first[4], second[6] - first[6]) * D_8009A20C) + (D_800D1893 << 8);
        D_800D154C->field_78 = rotation + 0x4000;
        break;
    case 5:
        D_800D154C->field_78 = func_150ADA20();
        break;
    case 6:
        D_800D154C->field_78 = D_800D154C->field_76;
        break;
    case 7:
        D_800D154C->field_76 = *(u16 *)((u8 *)&D_800CC34A + D_800D154C->field_222 * 0x32C) + angle;
        break;
    case 8:
        D_800D154C->field_76 = D_800D154C->field_7A;
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507AA48 */
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
void func_1507AD7C(void) {
    s32 mask;

    mask = func_1507A3E8();
    *(s32 *)((u8 *)D_800D154C + 0xF4) |= mask;
}
void func_1507ADAC(void) {
    s32 mask;

    mask = ~func_1507A3E8();
    *(s32 *)((u8 *)D_800D154C + 0xF4) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF4) & mask);
}
void func_1507ADE0(void) {
    s32 previous;
    s32 current;
    s32 var_a1;
    s32 temp_lo;

    previous = D_800D154C->field_7A;
    current = D_800D154C->field_78;
    var_a1 = current - previous;
    if (var_a1 < 0) {
        var_a1 = -var_a1;
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
void func_1507AE78(void) {
    D_800D154C->field_229 = D_800D1890;
}
void func_1507AE94(void) {
    *(s16 *)((u8 *)D_800D154C + 0xD2) = (s16) ((D_800D1890 << 8) | D_800D1891);
    *(s16 *)((u8 *)D_800D154C + 0xD4) = (s16) ((D_800D1892 << 8) | D_800D1893);
    *(s16 *)((u8 *)D_800D154C + 0xD2) = (s16) (s32) (*(f32 *)((u8 *)D_800D154C + 0x14C) * (f32) *(s16 *)((u8 *)D_800D154C + 0xD2));
    *(s16 *)((u8 *)D_800D154C + 0xD4) = (s16) (s32) (*(f32 *)((u8 *)D_800D154C + 0x150) * (f32) *(s16 *)((u8 *)D_800D154C + 0xD4));
}
void func_1507AF3C(void) {
    *(s16 *)((u8 *)D_800D154C + 0xD6) = (s16) ((D_800D1890 << 8) | D_800D1891);
    *(s16 *)((u8 *)D_800D154C + 0xD6) = (s16) (s32) (*(f32 *)((u8 *)D_800D154C + 0x150) * (f32) *(s16 *)((u8 *)D_800D154C + 0xD6));
}
void func_1507AF98(void) {
    *(s16 *)((u8 *)D_800D154C + 0xD8) = (s16) ((D_800D1890 << 8) | D_800D1891);
    *(s16 *)((u8 *)D_800D154C + 0xDA) = (s16) ((D_800D1892 << 8) | D_800D1893);
    *(s16 *)((u8 *)D_800D154C + 0xD8) = (s16) (s32) (*(f32 *)((u8 *)D_800D154C + 0x14C) * (f32) *(s16 *)((u8 *)D_800D154C + 0xD8));
    *(s16 *)((u8 *)D_800D154C + 0xDA) = (s16) (s32) (*(f32 *)((u8 *)D_800D154C + 0x14C) * (f32) *(s16 *)((u8 *)D_800D154C + 0xDA));
}
void func_1507B040(void) {
    D_800D154C->field_76 = D_800D154C->field_7A;
}
void *func_15072208(void *, s32);
void func_1506160C(u8 *, s32, s32, s32, u8);
s32 func_1507BB28(s32, s32);

void func_1507B058(void) {
    GameA28B0State *sp24;
    s32 sp20;

    sp24 = D_800D154C;
    sp20 = (s32) D_800C3E78;
    D_800D154C = func_15072208(D_800D154C, 0);
    D_800C3E78 = (u8) ((s32) ((u8 *) D_800D154C - (u8 *) &D_800CC2D0) / 812);
    if (D_800D154C != 0) {
        switch (D_800D1890) {
        case 0:
            func_1506160C((u8 *) D_800D154C, 1, (s32) D_800D1891, 0, 0U);
            break;
        case 1:
            D_800D154C->field_232 = D_800D1891;
        case 2:
            *(s32 *) ((u8 *) D_800D154C + 0x218) = func_1507BB28(0, D_800D1891);
            *(s16 *) ((u8 *) D_800D154C + 0x21C) = 0;
            break;
        }
    }
    D_800C3E78 = (u8) sp20;
    D_800D154C = sp24;
}
void func_1507B15C(void) {
    D_800D154C->field_8A = D_800D1890;
}
/* Call context: func_15062B1C: unique active project prototype */
/* Call context: func_15062B50: unique active project prototype */
void func_15062B1C(void *, f32);
void func_15062B50(void *, f32);

typedef struct GameA28B0ScaleState {
    u8 pad0[0xE8];
    s16 value;
    u8 padEA[0x66];
    f32 scale;
} GameA28B0ScaleState;

void func_1507B178(void) {
    s16 temp_v1;

    temp_v1 = (D_800D1891 << 8) | D_800D1890;
    if (D_800D1893 == 2) {
        ((GameA28B0ScaleState *)D_800D154C)->value = (s16) (s32) ((f32) temp_v1 * ((GameA28B0ScaleState *)D_800D154C)->scale);
        return;
    }
    if (D_800D1893 == 1) {
        func_15062B50(D_800D154C, (f32) temp_v1);
        return;
    }
    func_15062B1C(D_800D154C, (f32) temp_v1);
}
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
void func_1507B578(void) {
    D_800D154C->padB1[0x1F] = D_800D1890;
    *(f32 *)((u8 *)D_800D154C + 0x114) = (f32)(u32)D_800D1891;
}
void func_1507B5C4(void) {
    if (D_800D1891 == *(u8 *)((u8 *)D_800D154C->nested_31C + 0x75)) {
        D_800D1892 ^= 1;
    }
    if (D_800D1892 != 0) {
        func_15075400((s32)D_800D1890);
    }
}
void func_1507B630(void) {
    GameA28B0NestedState *temp_v1;

    if ((D_800D154C->field_89 == 0) && (*(f32 *)((u8 *) D_800D154C + 0x28) == 0.0f)) {
        if (*(u8 *)((u8 *) D_800D154C->nested_31C + 0x78) != 0) {
            D_800D1890 ^= 1;
        }
        if (D_800D1890 != 0) {
            temp_v1 = D_800D154C->nested_31C;
            *(u16 *)((u8 *) temp_v1 + 0x8C) = (u16) (*(u16 *)((u8 *) temp_v1 + 0x8C) | 0x4000);
            *(s8 *)((u8 *) D_800D154C->nested_31C + 0x8F) = 0;
        }
    } else {
        *(s32 *)((u8 *) D_800D154C + 0x218) = (s32) (*(s32 *)((u8 *) D_800D154C + 0x218) - 5);
    }
    *(s16 *)((u8 *) D_800D154C + 0x21C) = 0x64;
}
void func_1507B6E0(void) {
    if ((D_800D154C->field_89 != 0) || (*(f32 *)((u8 *)D_800D154C + 0x28) > 5.0f)) {
        *(s32 *)((u8 *)D_800D154C + 0x218) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x218) - 5);
        *(s16 *)((u8 *)D_800D154C + 0x21C) = 0x64;
    }
}
void func_1507B734(void) {
    s32 temp_t9;

    temp_t9 = ((D_800D1890 << 8) | D_800D1891) & 0xFFFF;
    if (D_800D1893 != 0) {
        *(s16 *) ((u8 *) D_800D154C->nested_31C + 0x8C) = temp_t9;
        *(u8 *) ((u8 *) D_800D154C->nested_31C + 0x8F) = (u8) D_800D1892;
        return;
    }
    *(s16 *) ((u8 *) D_800D154C->nested_31C + 0x8A) = temp_t9;
    *(u8 *) ((u8 *) D_800D154C->nested_31C + 0x8E) = (u8) D_800D1892;
}
void func_1507B7BC(void) {
    func_15075548();
    D_800D154C->pad223[0] = 0x11;
}
void func_1507B7E8(void) {
    void *temp_v0;

    temp_v0 = (u8 *)&D_800CC2D0 + (D_800D154C->field_222 * 0x32C);
    if ((*(u8 *)((u8 *)temp_v0 + 0x104) != 0) || (*(u8 *)((u8 *)temp_v0 + 0x1CA) == 0)) {
        D_800D1891 ^= 1;
    }
    if (D_800D1891 != 0) {
        func_15075400((s32) D_800D1890);
    }
}
typedef void (*GameA28B0Callback)(s32);

extern GameA28B0Callback D_80086150[];

void func_1507B884(void) {
    GameA28B0State *saved_state;
    s32 saved_index;
    u8 selector;
    GameA28B0Callback callback;

    selector = D_800D1890;
    callback = D_80086150[selector];
    if (callback != 0) {
        saved_state = D_800D154C;
        saved_index = D_800C3E78;
        callback(selector);
        D_800D154C = saved_state;
        D_800C3E78 = saved_index;
    }
}
void func_1507B8F4(void) {
    void *temp_v0;

    if ((D_800BE616 != 0) && ((D_800D1891 != 0) || ((temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C), (temp_v0 != 0)) && (*(u8 *)((u8 *)temp_v0 + 0x84) != 0)))) {
        func_15075400((s32) D_800D1890);
    }
}
void func_1507B958(void) {
    D_800D154C->field_B0 = D_800D1890;
}
void func_1507B974(void) {
    GameA28B0State *var_v1;
    s32 temp_a0;

    temp_a0 = D_800D154C->pad20[0x45];
    var_v1 = D_800D154C;
    if (temp_a0 != 0) {
        var_v1 = (GameA28B0State *) ((temp_a0 * 0x32C - 0x32C) + (u8 *)&D_800CC2D0);
    }
    if (D_800D1891 == *(u16 *) (((u8 *)D_800D2104[var_v1->pad10F[0x30]] + (var_v1->field_21E * 8) + (D_800D1893 * 8)) + 6)) {
        D_800D1892 ^= 1;
    }
    if (D_800D1892 != 0) {
        func_15075400((s32) D_800D1890);
    }
}
void func_15060A9C(s32, GameA28B0State *);

void func_1507BA48(void) {
    u16 value;

    value = (D_800D1892 << 8) | D_800D1893;
    if (D_800D1890 != 0) {
        value += func_150ADA20() % D_800D1890;
    }
    func_15060A9C(value, D_800D154C);
}
s32 func_1507A3E8();                                /* extern */

void func_1507BAD0(void) {
    *(s32 *)((u8 *)D_800D154C + 0xFC) = func_1507A3E8();
}
void func_1507BAF8(void) {
    *(s32 *)((u8 *)D_800D154C + 0x2CC) = func_1507A3E8();
}
void func_1507BB20(void) {
}
typedef struct GameA28B0ScriptEntry {
    s32 value;
    u8 key;
    u8 pad5[3];
} GameA28B0ScriptEntry;

extern void *D_800D1588[];
extern s32 D_80086A88;
extern u8 D_8009A120[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507BB28 CURRENT (325) */
s32 func_1507BB28(s32 arg0, s32 arg1) {
    void *data;
    GameA28B0ScriptEntry *entries;
    GameA28B0ScriptEntry *cursor;
    s32 index;

    data = D_800D1588[D_800D154C->pad4];
    if (data == 0) {
        return (s32)D_8009A120;
    }
    entries = *(GameA28B0ScriptEntry **)((u8 *)data - 0x10);
    if (entries == 0) {
        return (s32)D_8009A120;
    }
    index = 0;
    while (arg1 != entries[index].key) {
        if (entries[index].value == 0) {
            index = 0;
            entries = (GameA28B0ScriptEntry *)&D_80086A88;
            if (arg1 != ((GameA28B0ScriptEntry *)&D_80086A88)->key) {
                cursor = entries;
                do {
                    if (entries->value == 0) {
                        for (;;) {
                        }
                    }
                    index++;
                    cursor++;
                    entries++;
                } while (arg1 != cursor->key);
            }
            return ((GameA28B0ScriptEntry *)&D_80086A88)[index].value;
        }
        index++;
    }
    return entries[index].value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507BB28 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507BB28.s")
typedef struct GameA28B0ScriptState {
    u8 pad0[0xF4];
    s32 flags;
    u8 padF8[0x120];
    u8 *command;
    u16 timer;
    u8 pad21E[0x14];
    u8 script;
} GameA28B0ScriptState;

typedef void (*GameA28B0ScriptCommand)(void);
extern GameA28B0ScriptCommand D_80086730[];
extern s16 D_800CC264;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507BC14 CURRENT (100) */
void func_1507BC14(GameA28B0ScriptState *state) {
    if ((state->timer != 0) && (state->command != 0)) {
        if (state->timer != 25500) {
            state->timer -= D_800CC264;
        }
        if ((state->timer >= 50000) || (state->timer == 0)) {
            state->timer = 0;
            if (state->flags & 0x400) {
                state->timer = 20000;
                state->flags &= ~0x400;
                state->flags |= 4;
            }
        } else {
            return;
        }
    }
    if (state->command == 0) {
        state->command = (u8 *)func_1507BB28(0, state->script);
        state->timer = 0;
    }
    while (state->timer == 0) {
        if (*state->command >= 0xF7) {
            state->command++;
        } else {
            D_800D1890 = state->command[1];
            D_800D1891 = state->command[2];
            D_800D1892 = state->command[3];
            D_800D1893 = state->command[4];
            D_80086730[*state->command]();
            state->command += 5;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507BC14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A28B0/func_1507BC14.s")
