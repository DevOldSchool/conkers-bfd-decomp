#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1EBD00.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BE850
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1EBD00Shades {
    u8 value[3];
} Game1EBD00Shades;

typedef struct Game1EBD00Trail {
    f32 rate;
    Vec3f position;
    u8 mode;
    u8 pad11[3];
} Game1EBD00Trail;

typedef struct Game1EBD00Packet {
    u8 flags;
    u8 field01, field02, field03;
    s8 field04;
    u8 pad05;
    s16 duration;
    s32 field08, field0C, field10, field14, field18, field1C, field20, field24, field28;
    u8 field2C, field2D;
    u8 pad2E[2];
    u8 color[8];
    u8 shade;
    u8 pad39[3];
    s32 field3C;
    u8 field40, field41;
    u8 pad42[2];
    Vec3f position;
    s32 surface;
} Game1EBD00Packet;

typedef struct Game1EBD00Settings {
    u8 pad0[0x19];
    u8 flags;
} Game1EBD00Settings;

void *func_10022EC0(void *, const void *, u32);
void func_1510F800(s32);
s32 func_15157010(s32, s32, f32, s32, s32, s32, s32, s32);
s32 func_151BEEE0(f32, f32 *, s32, u8, s32, s32, s32, s32, s32);
s32 func_1510FD20(s32, s32);
extern Game1EBD00Shades D_800AA8B0;
extern f32 D_800AA8DC;
extern s32 D_800BE9F0;
extern Game1EBD00Settings *D_800D2E4C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BE850 CURRENT (4070) */
s32 func_151BE850(Vec3f *arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4) {
    s32 result;
    s32 surface;
    s32 bits;
    Game1EBD00Packet packet;
    Game1EBD00Trail trail;
    Game1EBD00Shades shades;
    Vec3f offset;
    f32 scale;
    u8 shade;

    func_1510F800(0);
    surface = func_1510FD20(arg0->x, arg0->z);
    if (arg4 >= 3) {
        return 0;
    }
    if ((D_800D2E4C->flags & 4) || arg4 == 2) {
        shades = D_800AA8B0;
        trail.rate = arg1;
        packet.field3C = 0;
        packet.field40 = 0;
        packet.field41 = 0;
        packet.position = *arg0;
        trail.mode = arg2;
        scale = arg1 * D_800AA8DC;
        func_151436B4(scale, 0.0f, 39.0f, &offset);
        trail.position.x = arg0->x + offset.x;
        trail.position.y = arg0->y + offset.y - 40.0f;
        trail.position.z = arg0->z + offset.z;
        shade = shades.value[arg4];
        packet.shade = shade;
        bits = 0;
        if (arg3 != 0) {
            bits = 0x10;
        }
        packet.flags = bits | 0xE;
        packet.field01 = 1;
        if (D_800BE9F0 == 7) {
            packet.field02 = 6;
        } else {
            packet.field02 = 2;
        }
        packet.field04 = -1;
        packet.duration = 0x12C;
        packet.field08 = 0xA2;
        packet.field14 = 0x620405;
        packet.field0C = 8;
        packet.field18 = 0x40200;
        packet.field1C = 0x14;
        packet.field20 = 0x37;
        packet.field24 = 0x80;
        packet.field28 = 0x20;
        packet.field2D = 8;
        packet.color[0] = 0xFF;
        packet.color[2] = 0xFF;
        packet.field03 = 0;
        packet.field10 = 0;
        packet.field2C = 0;
        packet.color[1] = 0xFF;
        packet.color[3] = 0xFF;
        packet.color[4] = 0xFF;
        packet.color[5] = 0xFF;
        packet.color[6] = 0xFF;
        packet.color[7] = 0xFF;
        packet.surface = surface;
        result = func_15157010((s32)&packet, 0, 1.0f, 3, 0xFF, 0x18, 0xFF, 1);
        if (result != 0) {
            func_10022EC0((u8 *)result + 0x120, &trail, 0x18);
        }
        return result;
    }
    return func_151BEEE0(arg1, &arg0->x, 3, 0xFF, arg4, arg3, surface, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BE850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EBD00/func_151BE850.s")
