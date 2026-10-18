#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_E7970.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_narrow_effect_record_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BA55C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);

typedef struct GameE7970Packet {
    void *field_0;
    u8 field_4;
    u8 pad5[3];
    f32 field_8;
} GameE7970Packet;

void func_150BA4C0(void *arg0, u8 arg1, s32 arg2) {
    GameE7970Packet packet;
    u8 *temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_8 = 0.0f;
    temp_v0 = func_15149130((s16) ((func_150ADA20() % 9U) + 0xF), -1, 0x52, -1, 1, 0x3F, 0xC, (s32) arg1, arg2);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
    }
}
typedef struct GameBA55COwner {
    s32 active;
    u8 pad04[0x37];
    u8 generation;
    u8 pad3C[0x3A];
    u16 yaw;
    u8 pad78[0x78];
    f32 verticalScale;
    u8 padF4[0x58];
    f32 lowerSize, upperSize;
    u8 pad154[0x80];
    s32 enabled;
} GameBA55COwner;

f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
void *func_1518A3C0(void *, f32 *, f32, f32 *, f32 *, f32, f32,
                    s32, s32, s32, s32, s32, s32);
extern f32 D_8009FE30, D_8009FE34, D_8009FE38, D_8009FE3C;
extern f32 D_8009FE40, D_8009FE44, D_8009FE48, D_8009FE4C;
extern f32 D_8009FE50, D_8009FE54, D_8009FE58, D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BA55C CURRENT (1332) */
void func_150BA55C(u8 *arg0) {
    GameBA55COwner *owner;
    u32 randomYaw;
    s32 heading;
    f32 position[3];
    f32 radius;
    f32 unusedOutput;
    f32 growth[3];
    f32 size;
    f32 spawnPosition[3];
    f32 angles[3];
    f32 velocity[3];
    f32 growthBase;
    f32 growthRange;
    f32 randomLife;
    f32 randomSize;
    f32 speed;

    owner = *(GameBA55COwner **)(arg0 + 0x28);
    if (owner->active == 0 || owner->generation != ((GameE7970Packet *)(arg0 + 0x28))->field_4) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (owner->enabled != 0) {
        ((GameE7970Packet *)(arg0 + 0x28))->field_8 += (D_8009FE30 + func_150ADA68() * D_8009FE34) * D_800BE9A4;
        if (((GameE7970Packet *)(arg0 + 0x28))->field_8 > 1.0f) {
            size = (owner->lowerSize + owner->upperSize) * 0.5f;
            heading = (owner->yaw >> 8) - 0x40;
            func_1515C244(owner, position, &radius, &unusedOutput);
            growthBase = D_8009FE38;
            growthRange = D_8009FE3C;
            growth[1] = 0.0f;
            do {
                randomYaw = func_150ADA20();
                func_15143794((s16)((randomYaw % 127U) + heading - 0x3F),
                              (s16)(func_150ADA20() % 31U - 0x32), radius, spawnPosition);
                spawnPosition[1] *= owner->verticalScale;
                spawnPosition[0] += position[0];
                spawnPosition[1] += position[1];
                spawnPosition[2] += position[2];
                angles[0] = func_150ADA68() * 360.0f;
                angles[1] = func_150ADA68() * 360.0f;
                angles[2] = func_150ADA68() * 360.0f;
                speed = func_150ADA68() * D_8009FE40 + D_8009FE44;
                velocity[0] = (spawnPosition[0] - position[0]) * speed;
                velocity[1] = (spawnPosition[1] - position[1]) * speed;
                velocity[2] = (spawnPosition[2] - position[2]) * speed;
                growth[0] = func_150ADA68() * growthRange + growthBase;
                growth[2] = func_150ADA68() * growthRange + growthBase;
                randomSize = func_150ADA68();
                randomLife = func_150ADA68();
                func_1518A3C0(spawnPosition, angles,
                              (randomSize * D_8009FE48 + D_8009FE4C) * size,
                              velocity, growth, randomLife * D_8009FE50 + D_8009FE54,
                              D_8009FE58, 7, func_150ADA20() % 41U + 0x3C,
                              0, 0, arg0[0xC], arg0[1]);
                ((GameE7970Packet *)(arg0 + 0x28))->field_8 -= 1.0f;
            } while (((GameE7970Packet *)(arg0 + 0x28))->field_8 > 1.0f);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BA55C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E7970/func_150BA55C.s")

void func_150BA8F0(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
