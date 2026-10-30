#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_12CCF0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FF840
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game12CCF0State {
    u8 pad0[0x1D4];
    s32 field1D4;
} Game12CCF0State;

void func_15145EA4(s32 *, s32 *, s32, s32);

extern u8 D_80088BB0;
extern s32 D_800A2130;

typedef struct Game12CCF0Actor {
    u8 pad0[0x7A];
    u16 field_7A;
    u8 pad7C[0x2B0];
} Game12CCF0Actor;

f32 func_150ADA68(void);
void func_150FFCC8(void *, void *, void *, void *, void *);
void func_150FFC3C(void *);
void func_151D5148(void *);
void func_150FFD84(f32 *, f32 *, u8, s32);
void func_150FFB6C(Vec3f *, void *, Game12CCF0Actor *, s32);
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
s32 func_15081690(void *, f32, f32, f32, f32, f32, f32, void *, f32, s32, s32, s32, s32, s32, s32);
s32 func_15081E78(void *, void *, s32);
extern u8 D_800A213C[];
extern f32 D_800A2170, D_800A2174, D_800A2178, D_800A217C;
extern f32 D_800A2180, D_800A2184, D_800A2188;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FF840 CURRENT (1550) */
void func_150FF840(Game12CCF0Actor *arg0, u8 arg1, u8 arg2, volatile u8 arg3, s32 arg4) {
    Vec3f position, direction, third, fourth;
    f32 motion[2];
    Vec3f end, middle, start;
    u32 scratch[25];
    void *result;
    u8 *state;
    u32 random2;
    u32 random1;

    func_150FFCC8(arg0, &position, &direction, &third, &fourth);
    func_151D5148(arg0);
    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0 && (arg0->pad0[0x74] & 15) != 15) {
        func_151D3F14(&position, arg3, arg4);
        motion[1] = (func_150ADA68() * D_800A2170 + 4800.0f) * D_800A2174;
        motion[0] = (func_150ADA68() * 220.0f + 320.0f) * D_800A2178;
        random1 = func_150ADA20();
        random2 = func_150ADA20();
        func_15102B38((s32)arg0, D_80088BB0, (s32)&D_800A2130, (s32)D_800A213C,
                     motion, random1 % 3U + 4, (random2 & 127) + 128,
                     func_150ADA68() * 450.0f + 780.0f, (s32)&position,
                     255, 0, -1, arg3, arg4);
        func_150FFD84(&position.x, &direction.x, arg3, arg4);
    }
    if (arg1 != 0) {
        start.x = direction.x * D_800A217C + position.x;
        start.y = direction.y * D_800A217C + position.y;
        start.z = direction.z * D_800A217C + position.z;
        middle.x = direction.x * D_800A2180 + position.x;
        middle.y = direction.y * D_800A2180 + position.y;
        middle.z = direction.z * D_800A2180 + position.z;
        end.x = direction.x * D_800A2184 + position.x;
        end.y = direction.y * D_800A2184 + position.y;
        end.z = direction.z * D_800A2184 + position.z;
        func_150FFB6C(&start, &position, arg0, 0x32);
        func_150FFB6C(&middle, &position, arg0, 0x30);
        func_150FFB6C(&end, &position, arg0, 0x31);
    }
    if (arg2 != 0) {
        state = *(u8 **)((u8 *)arg0 + 0x31C);
        if (state != 0) result = state + 0xB0;
        else result = scratch;
        func_15081690(arg0, position.x, position.y, position.z,
                     direction.x * D_800A2188, direction.y * D_800A2188,
                     direction.z * D_800A2188, result, 2000.0f,
                     0, 0, 0, -1, 0, 0);
        func_15081E78(arg0, result, 0x10);
    }
    func_150FFC3C(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FF840 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FF840.s")

s32 func_1505D1C4(f32, f32, f32, s32, s32, s32, s32, s32);
extern u8 D_800CC2D0;

void func_150FFB6C(Vec3f *arg0, void *arg1, Game12CCF0Actor *arg2, s32 arg3) {
    s32 actor_index;
    u16 actor_id;

    actor_index = ((u8 *)arg2 - &D_800CC2D0) / 0x32C;
    actor_id = arg2->field_7A;
    func_1505D1C4(arg0->x, arg0->y, arg0->z, arg3 | 0x60000,
                  actor_index, actor_id, 0, (s32)arg1);
}
void func_150FFBDC(Game12CCF0State *arg0, s32 arg1, s32 arg2) {
    s32 *sp1C;
    s32 sp18;

    sp1C = &D_800A2130;
    sp18 = arg2;
    func_15145EA4((s32 *) &sp1C, &sp18,
                  arg0->field1D4 + (D_80088BB0 << 6), 1);
}
void func_151D8868(s8 *, s32, s32, s32);

void func_150FFC3C(void *arg0) {
    struct {
        s8 field_0;
        s8 pad1;
        s16 field_2;
        s8 field_4;
        s8 field_5;
        s8 field_6;
    } sp18;

    if (*(void **)((u8 *)arg0 + 0x318) != 0) {
        sp18.field_0 = 1;
        sp18.field_2 = (s16) ((func_150ADA20(arg0) % 11U) + 0x14);
        sp18.field_5 = (s8) (1 << *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x318) + 0x23D));
        sp18.field_4 = (s8) ((func_150ADA20(arg0) & 1) + 7);
        sp18.field_6 = -1;
        func_151D8868(&sp18.field_0, 0, 0xFF, 1);
    }
}
void func_151D3E6C(void *, void *, void *, s32);
void func_151D5A18(void *, void *, void *, void *, void *, s32, s32);
extern s32 D_8008FC8C;
extern u8 *D_8008FC94;

void func_150FFCC8(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    func_151D5A18(arg0, arg1, arg2, arg3, arg4, D_8008FC8C, *D_8008FC94);
    func_151D3E6C(arg0, arg1, arg1, 0x8003A);
}
void func_15081E0C(void *, s32, s32);

void func_150FFD2C(s32 arg0, void *arg1, s32 arg2) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg1 + 4);
    if (((temp_v0 == 0x9F) || (temp_v0 == 0xA0)) && !(*(s32 *)((u8 *)arg1 + 0x94) & 0x80)) {
        func_15081E0C(arg1, 4, 0);
    }
}
typedef struct Game12CCF0Particle {
    s32 flags, field4;
    s16 kind, duration;
    s32 fieldC, field10;
    u8 color0[4], color1[4];
    u8 field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, size0, size1;
    Vec3f position;
    Vec3f field3C;
    Vec3f field48;
    f32 field54;
    s32 flags58;
    s32 field5C;
    u8 field60, field61;
    s8 field62, field63, field64;
    u8 field65, field66;
    u8 pad67;
} Game12CCF0Particle;

typedef struct Game12CCF0Colors {
    s32 value[4];
} Game12CCF0Colors;

void func_15143794(s16, s16, f32, void *);
void func_15145974(void *, f32 *, f32 *);
extern Game12CCF0Colors D_800A2160;
extern Vec3f D_800A5480;

void func_150FFD84(f32 *arg0, f32 *arg1, u8 arg2, s32 arg3) {
    u32 random1;
    u32 random0;
    Game12CCF0Particle packet;
    s32 count;
    s16 x;
    s16 y;
    Vec3f angles;
    Game12CCF0Colors colors;

    count = (func_150ADA20() % 9U) + 0xA;
    packet.kind = 0x2203;
    packet.flags = 0x200005;
    packet.field4 = 0;
    packet.fieldC = 0;
    packet.field10 = 0;
    packet.color0[0] = 0xFF;
    packet.color0[1] = 0xFF;
    packet.color0[2] = 0xFF;
    packet.color0[3] = 0xFF;
    packet.color1[0] = 0xFF;
    packet.color1[1] = 0xFF;
    packet.color1[2] = 0xFF;
    packet.field1C = 0xFF;
    packet.position = *(Vec3f *)arg0;
    packet.field3C = D_800A5480;
    packet.field1E = 7;
    packet.field20 = 0x24;
    packet.field22 = 1;
    packet.flags58 = 0x4C207;
    packet.field60 = 0;
    packet.field61 = 7;
    packet.field62 = -1;
    packet.field63 = -1;
    packet.field64 = -1;
    packet.field65 = 0;
    packet.field5C = 0;
    packet.field66 = 0xFF;
    packet.field24 = 1.0f;
    func_15145974(arg1, &angles.y, &angles.x);
    angles.x = 0.0f;
    x = angles.y * 182.04445f;
    y = angles.x * 182.04445f;
    x >>= 8;
    y >>= 8;
    x -= 0x8A;
    y -= 0x8A;
    do {
        colors = D_800A2160;
        packet.field1D = colors.value[func_150ADA20() & 3];
        packet.duration = (func_150ADA20() % 13U) + 0xA;
        packet.color1[3] = (func_150ADA20() % 101U) + 0x9B;
        packet.size0 = packet.size1 = (func_150ADA68() * 155.0f) + 75.0f;
        random1 = func_150ADA20();
        random0 = func_150ADA20();
        func_15143794((random1 % 21U) + x, (random0 % 21U) + y,
                      (func_150ADA68() * 20.0f) + 20.0f, &packet.field48);
        packet.field54 = func_150ADA68() * 0.62100005f + -0.657f;
        packet.flags58 &= ~0xC0;
        random1 = (func_150ADA20() & 1) ? 0x80 : 0;
        random0 = (func_150ADA20() & 1) ? 0x40 : 0;
        packet.flags58 |= (s32)(random0 | random1);
        func_15130280(&packet, 1, NULL, 0, arg2, arg3);
        count--;
    } while (count > 0);
}
