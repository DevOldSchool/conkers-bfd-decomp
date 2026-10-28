#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1C02A0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_subranges.md
 */

typedef struct Game1C02A0Particle {
    s32 flags, field4;
    s16 kind, duration;
    s32 fieldC, field10;
    u8 color0[4], color1[4];
    u8 field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, size0, size1;
    f32 position[3];
    u8 pad3C[0xC];
    f32 direction[3];
    f32 field54;
    s32 flags58;
    u8 pad5C[4];
    u8 field60, field61, field62;
    s8 field63;
    u8 pad64[0xC];
} Game1C02A0Particle;

void *func_10022EC0(void *, const void *, u32);
void *func_15130374(void *, u8, s32, u8, s32);
void func_15143134(f32 *, f32 *, s32);
void func_15143794(s16, s16, f32, void *);
f32 func_150ADA68(void);
extern f32 D_800A8194;
extern f32 D_800A8198;
extern f32 D_800A819C;
extern f32 D_800A81A0;
extern f32 D_800A81A4;
extern f32 D_800A81A8;
extern f32 D_800BE9A4;

void func_15192DF0(void *arg0) {
    u8 *data;
    Game1C02A0Particle packet;
    u8 *owner;
    f32 factor;
    void *spawned;
    f32 offset[3];
    u32 random;
    s16 angle;
    s16 base;

    data = (u8 *)arg0 + 0x28;
    *(f32 *)(data + 8) += (792.0f + func_150ADA68() * D_800A8194) * D_800A8198 * D_800BE9A4;
    if (*(f32 *)(data + 8) > 1.0f) {
        owner = *(u8 **)data;
        if (*(s32 *)(owner + 0x1D4) == 0) {
            while (*(f32 *)(data + 8) > 1.0f) {
            }
        } else {
            base = (*(u16 *)(owner + 0x7A) >> 8) + 0x40;
            packet.field1D = 0x29;
            packet.kind = 0xE03;
            packet.flags = 0x200005;
            packet.color1[0] = 0xB0;
            packet.color1[1] = 0xA0;
            packet.color1[2] = 0x2A;
            packet.color0[0] = 0x40;
            packet.color0[1] = 0xB;
            packet.color0[2] = 0x6A;
            packet.field4 = 0;
            packet.fieldC = 0;
            packet.field10 = 0;
            packet.color0[3] = 0xFF;
            packet.field1C = 0xFF;
            packet.field60 = 3;
            packet.field61 = 3;
            packet.flags58 = 0xE05;
            packet.field54 = 0.0f;
            packet.field62 = 0xA;
            packet.field63 = -1;
            packet.field1E = 0x19;
            packet.field20 = 0xA;
            packet.field22 = 0x23;
            packet.field24 = D_800A819C;
            factor = D_800A81A0;
            do {
                angle = (func_150ADA20() % 51U) - 0x82;
                offset[0] = func_150ADA68() * 20.0f + 30.0f;
                offset[1] = func_150ADA68() * 60.0f + -20.0f;
                offset[2] = 0.0f;
                if (func_150ADA20() & 1) {
                    offset[0] = -offset[0];
                    angle = angle + base;
                } else {
                    angle = base - angle;
                }
                packet.duration = (func_150ADA20() % 11U) + 0x1E;
                packet.color1[3] = (func_150ADA20() % 101U) + 0x64;
                packet.size0 = packet.size1 = func_150ADA68() * 150.0f + 100.0f;
                func_15143134(offset, packet.position, *(s32 *)(*(u8 **)data + 0x1D4) + 0x40);
                random = func_150ADA20();
                func_15143794(angle, (s16)((random % 28U) - 0x19),
                              func_150ADA68() * D_800A81A4 * D_800A81A8, packet.direction);
                packet.flags58 &= ~0xC0;
                if (func_150ADA20() & 1) {
                    packet.flags58 |= 0x40;
                }
                if (func_150ADA20() & 1) {
                    packet.flags58 |= 0x80;
                }
                spawned = func_15130374(&packet, 1, 4, ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
                if (spawned != NULL) {
                    func_10022EC0((u8 *)spawned + 0xA8, &factor, 4);
                }
                *(f32 *)(data + 8) -= 1.0f;
            } while (*(f32 *)(data + 8) > 1.0f);
        }
    }
}

void func_15193234(void *arg0, void *arg1, u8 arg2) {
    s32 temp_t6;
    u8 *temp_v0;

    temp_t6 = arg2;
    temp_v0 = (u8 *)arg0 + 0x28;
    if (temp_t6 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0) {
            u8 *dst = temp_v0;

            *(s32 *)dst = *(s32 *)arg1;
            *(u8 *)(dst + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if (temp_t6 == 0) {
        s32 temp_v1 = *(s32 *)arg1;

        if ((temp_v1 == *(s32 *)temp_v0) ||
            (temp_v0[4] == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C((u8 *)arg0);
        }
    }
}
void func_151932E0(void *arg0, void *arg1, u8 arg2) {
    s32 temp_t6;
    u8 *temp_v0;

    temp_t6 = arg2;
    temp_v0 = (u8 *)arg0 + 0x28;
    if (temp_t6 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0) {
            u8 *dst = temp_v0;

            *(s32 *)dst = *(s32 *)arg1;
            *(u8 *)(dst + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if (temp_t6 == 0) {
        s32 temp_v1 = *(s32 *)arg1;

        if ((temp_v1 == *(s32 *)temp_v0) ||
            (temp_v0[4] == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C((u8 *)arg0);
        }
    }
}
