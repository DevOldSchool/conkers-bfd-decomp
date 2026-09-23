#include "types.h"

/*
 * Reviewed source unit: src/game/game_1355D0.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15108120
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15136C3C(void *, s32, s32, s32, s32, s32, s32, s32);
void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
u32 func_150ADA20(void);
void func_150E83AC(void *, s16, u8, s32);
extern u8 D_800A2430;
extern u8 D_800A2434;
extern f32 D_800A2438;
extern f32 D_800A243C;
extern f32 D_800A2440;
extern f32 D_800A2444;

typedef struct Game1355D0Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game1355D0Vec3;

typedef struct Game1355D0Packet {
    s32 field00;
    s32 field04;
    Game1355D0Vec3 position;
    s16 field14;
    s16 field16;
    s16 field18;
    s16 field1A;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    s16 field2C;
    s16 field2E;
    f32 field30;
    f32 field34;
    f32 field38;
} Game1355D0Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108120 CURRENT (2234) */
void func_15108120(void *arg0, u8 arg1, s32 arg2) {
    Game1355D0Vec3 target;
    Game1355D0Vec3 source;
    Game1355D0Packet packet;
    u8 *actor = arg0;

    target.x = *(f32 *)(actor + 0x14);
    target.y = *(f32 *)(actor + 0x18);
    target.z = *(f32 *)(actor + 0x1C);
    source.x = *(f32 *)(actor + 0x14);
    source.y = *(f32 *)(actor + 0x18) + 30.0f;
    source.z = *(f32 *)(actor + 0x1C);
    func_150E83AC(&target, (s16)((func_150ADA20() % 201U) + 0x1F4), arg1, arg2);

    packet.field00 = 0xF;
    packet.field04 = 8;
    packet.position = source;
    packet.field14 = 0;
    packet.field16 = 0xFF;
    packet.field18 = -0x40;
    packet.field1A = 0x29;
    packet.field2C = 0x27;
    packet.field2E = 0x14;
    packet.field30 = D_800A2438;
    packet.field34 = D_800A2438;
    packet.field1C = 8.0f;
    packet.field20 = 10.0f;
    packet.field24 = D_800A243C;
    packet.field28 = D_800A2440;
    packet.field38 = D_800A2444;
    func_15152190(&packet, &D_800A2430, &D_800A2434, 1, 40.0f, 0, arg1, arg2);
    func_15136C3C(arg0, 1, 1, 1, 0, 0, arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108120 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1355D0/func_15108120.s")
