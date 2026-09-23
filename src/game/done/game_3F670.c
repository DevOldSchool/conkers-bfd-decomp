#include "types.h"

/*
 * Reviewed source unit: src/game/game_3F670.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 */

typedef struct Game3F670Packet {
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
} Game3F670Packet;

void *func_10022EC0(void *, const void *, u32);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
/* The raw caller forwards ignored integer arguments to this legacy entry. */
void func_1510F800();
void *func_1510FD20(s32, s32);
typedef struct Game3F670Matrix {
    f32 m[4][4];
} Game3F670Matrix;
extern Game3F670Matrix D_80089470;
extern f32 D_80096550[];

void func_150121C0(s32 arg0) {
    s32 var_s0;
    void *temp_v0;
    Game3F670Packet packet;
    s32 sp34;

    packet.field0 = 1.0f;
    packet.field4 = 1.0f;
    packet.field8 = 1.0f;
    packet.fieldC = 1.0f;
    packet.field10 = 0.0f;
    packet.field14 = 0.0f;
    packet.field18 = 0.0f;
    packet.field1C = 1.0f;
    packet.field20 = 1.0f;
    packet.field24 = 1.0f;
    packet.field28 = 0.0f;
    packet.field2C = 0.0f;
    packet.field30 = 0.0f;
    packet.field34 = 0.0f;
    packet.field38 = 0.0f;
    packet.field3C = 0.0f;
    packet.field40 = 0.0f;
    packet.field44 = 0.0f;
    packet.field48 = 0.0f;
    packet.field4C = 0.0f;
    packet.field50 = 0xC0500;
    packet.field54 = 0x12C;
    packet.field56 = 0x21;
    sp34 = arg0;
    packet.field58 = 0;
    func_1510F800(0, arg0);
    packet.field5C = (s32)func_1510FD20((s32) D_80096550[0], (s32) D_80096550[2]);
    packet.field60 = 0xFF;
    packet.field61 = 0;
    packet.field62 = 6;
    packet.field63 = 0;
    packet.field64 = 0;
    packet.field65 = 0;
    packet.field66 = 0;
    packet.field67 = 0;
    packet.field68 = 3;
    packet.field6A = 0;
    packet.field6C = 0;
    packet.field70 = 0;
    packet.field72 = 1;
    packet.field74 = 0xFF;
    temp_v0 = func_15132A4C(&packet, 0, 0, 4, 0xFFU, 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x170, &sp34, 4U);
        for (var_s0 = 0; var_s0 < 2; var_s0++, var_s0 = (u8)var_s0) {
            func_10022EC0((u8 *)temp_v0 + (var_s0 << 6) + 0x90, &D_80089470, 0x40U);
        }
    }
}
