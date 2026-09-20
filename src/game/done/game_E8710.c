#include "types.h"

/*
 * Reviewed source unit: src/game/game_E8710.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 */

extern s32 D_800BE9E4;

s32 func_150BB260(f32 *arg0, s32 arg1) {
    s32 count;
    f32 *damping;

    damping = &arg0[0x2A];
    for (count = D_800BE9E4; count != 0; count--) {
        arg0[0x16] *= *damping;
        arg0[0x18] *= *damping;
    }
    return 1;
}
typedef struct {
    u8 pad000[0x18];
    s32 field18;
    s16 field1C;
    u8 pad01E[0x81 - 0x1E];
    u8 field81;
    u8 pad082[0xB0 - 0x82];
    s16 fieldB0;
    s16 fieldB2;
} Func150BB408State;

extern void func_1513F6C0(void *arg0, s32 arg1, s32 arg2);

void func_150BB408(Func150BB408State *arg0) {
    arg0->field18 |= 1;
    arg0->field1C = 0x32;
    arg0->fieldB0 = arg0->field1C;
    arg0->fieldB2 = 5;
    func_1513F6C0(arg0, 6, arg0->field81);
}
s32 func_150BB450(Func150BB408State *arg0) {
    s16 temp_lo;
    s16 temp_v0;

    temp_v0 = arg0->field1C;
    if (temp_v0 < arg0->fieldB0) {
        temp_lo = temp_v0 * arg0->fieldB2;
        if (temp_lo < (s32)((u8 *)arg0)[0x28]) {
            ((u8 *)arg0)[0x28] = (u8)temp_lo;
        }
    }
    return 1;
}
typedef struct GameE8710Packet {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    s32 field50;
    s16 field54;
    s16 field56;
    s8 field58;
    u8 pad59[0x3];
    s32 field5C;
    u8 field60;
    s8 field61;
    s8 field62;
    s8 field63;
    s8 field64;
    s8 field65;
    s8 field66;
    s8 field67;
    s8 field68;
    u8 pad69[0x1];
    s8 field6A;
    u8 pad6B[0x1];
    s32 field6C;
    s8 field70;
    u8 pad71[0x1];
    s16 field72;
    s16 field74;
    u8 pad76[2];
} GameE8710Packet;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
f32 func_151423D8(s32);
void func_15132A4C(s32, s32, s32, s32, u8, s32);

extern const f32 D_8009FE7C;
extern const f32 D_8009FE80;
extern const f32 D_8009FE84;
extern const f32 D_8009FE88;
extern const f32 D_8009FE8C;

s32 func_150BB498(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                 s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                 s32 arg10, s32 arg11, s32 arg12, s32 arg13, u8 arg14) {
    s16 spBE;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 temp_fa0;
    f32 temp_fv1;
    GameE8710Packet packet;

    spB8 = func_151423D8((arg8 - 0x40) & 0xFF);
    spB4 = func_151423D8((u8) arg8);
    packet.field50 = 0x9E8;
    packet.field18 = packet.field14 = packet.field10 = 0.0f;
    packet.field24 = packet.field20 = packet.field1C = 1.0f;
    packet.field28 = arg2;
    packet.field2C = arg3;
    packet.field30 = arg4;
    packet.field4 = D_8009FE7C;
    spBE = (func_150ADA20() % 13U) - 0x34;
    spB0 = func_151423D8((spBE - 0x40) & 0xFF);
    spAC = func_151423D8((u8) spBE);
    temp_fv1 = (func_150ADA68() * 9.0f) + 3.0f;
    temp_fa0 = temp_fv1 * spAC;
    packet.field34 = temp_fa0 * spB8;
    packet.field38 = -temp_fv1 * spB0;
    packet.field3C = temp_fa0 * spB4;
    packet.field40 = func_150ADA68() * 50.0f + -25.0f;
    packet.field44 = 0.0f;
    packet.field48 = (func_150ADA68() * 50.0f) + -25.0f;
    packet.field54 = (func_150ADA20() % 68U) + 0x26;
    packet.field4C = func_150ADA68() * D_8009FE80 + D_8009FE84;
    packet.field0 = 1.0f;
    temp_fv1 = (func_150ADA68() * D_8009FE88) + D_8009FE8C;
    packet.field56 = 0x1F;
    packet.field58 = 0;
    packet.field5C = 0;
    packet.field8 = temp_fv1;
    packet.field60 = 0xFF;
    packet.field61 = 1;
    packet.field62 = 0;
    packet.field63 = 0;
    packet.field64 = 0;
    packet.field65 = 0;
    packet.field66 = 0;
    packet.field67 = 0;
    packet.field68 = 0;
    packet.field6A = 0;
    packet.field6C = 0;
    packet.field70 = 0;
    packet.field72 = 1;
    packet.field74 = 0xFF;
    packet.fieldC = temp_fv1;
    func_15132A4C((s32) &packet, 3, 0xFF, 0, (u8) (s32) arg14, 0);
    return 1;
}
