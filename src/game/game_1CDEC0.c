#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1CDEC0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A0C0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_1510F8CC(s32);
extern u8 D_800C35EA;

typedef struct {
    f32 field_0;
    f32 field_4;
    f32 field_8;
    s8 field_C;
    u8 pad_D[3];
    f32 field_10;
} Game1CDEC0Packet;

void func_151A0A10(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    void *temp_v0_2;
    Game1CDEC0Packet packet;
    s32 temp_v0;

    if (arg0 != 0) {
        packet.field_0 = *(f32 *)(arg0 + 0x14);
        packet.field_8 = *(f32 *)(arg0 + 0x1C);
        if (D_800C35EA != 1) {
            packet.field_4 = *(f32 *)(arg0 + 0x180);
            packet.field_10 = 0.0f;
            temp_v0 = func_1510F8CC(*(s32 *)(arg0 + 0x184));
            switch (temp_v0) {
                default:
                    packet.field_C = 0;
                    break;
                case 10:
                    packet.field_C = 0;
                    break;
                case 15:
                case 17:
                    packet.field_C = 1;
                    break;
            }
            temp_v0_2 = func_151491F4(arg1, -1, 1, 1, 0, 0x14, arg2, arg3);
            if (temp_v0_2 != 0) {
                func_10022EC0((u8 *)temp_v0_2 + 0x28, &packet, 0x14);
            }
        }
    }
}
typedef struct Game1CDEC0Emitter {
    u8 pad0[0xC];
    u8 field_C;
    u8 padD[0x1B];
    Game1CDEC0Packet packet;
} Game1CDEC0Emitter;

void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32,
                   s32, s32);
f32 func_150ADA68(void);
extern f32 D_800A8D10;
extern f32 D_800BE9A4;

void func_151A0AF8(Game1CDEC0Emitter *arg0) {
    Game1CDEC0Packet *packet;

    arg0->packet.field_10 += D_800A8D10 * D_800BE9A4;
    if (arg0->packet.field_10 > 1.0f) {
        packet = &arg0->packet;
        do {
            func_1514C678(packet->field_0, packet->field_4,
                          *(s32 *)&packet->field_8,
                          (func_150ADA68() * 25.0f) + 15.0f, 0, 0xFF, 5, 4,
                          *(u8 *)&packet->field_C, 0.0f, 0, arg0->field_C);
            packet->field_10 -= 1.0f;
        } while (packet->field_10 > 1.0f);
    }
}
typedef struct {
    void *descriptor;
    u8 pad4[8];
    s16 fieldC;
    s16 fieldE;
    s16 x;
    s16 y;
    s16 z;
    s16 velocityX;
    s16 velocityZ;
    u8 pad1A[2];
    u8 fractionX;
    u8 fractionY;
    u8 fractionZ;
    s8 field1F;
    s16 velocityY;
    s16 acceleration;
    s16 lifetime;
    s16 initialLifetime;
    s16 field28;
    u8 field2A;
    u8 pad2B;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    s8 field30;
    s8 field31;
    s8 field32;
    u8 pad33;
    s16 field34;
} Game1CDEC0Particle;

u32 func_150ADA20(void);
extern u8 D_8008F8D0[];
extern u8 D_8009187C[];
extern u8 D_800918A0[];
extern f32 D_800A8D14;
extern f32 D_800A8D18;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A0C0C CURRENT (1179) */
s32 func_151A0C0C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    Game1CDEC0Particle particle;
    s16 angle;
    f32 sinAngle;
    f32 cosAngle;
    f32 sinHeading;
    f32 cosHeading;
    f32 horizontalSpeed;
    f32 speed;

    angle = (func_150ADA20() % 15U) - 0x3F;
    sinAngle = func_151423D8((u8)angle);
    cosAngle = func_151423D8((u8)(angle - 0x40));
    sinHeading = func_151423D8(arg8);
    cosHeading = func_151423D8((u8)(arg8 - 0x40));
    speed = (func_150ADA68() * D_800A8D14) + D_800A8D18;
    horizontalSpeed = speed * sinAngle;
    particle.velocityX = (s32)(horizontalSpeed * cosHeading);
    particle.velocityY = (s32)(-speed * cosAngle);
    particle.velocityZ = (s32)(horizontalSpeed * sinHeading);
    particle.acceleration = (func_150ADA20() % 41U) - 0x82;
    particle.field2A = (func_150ADA20() % 3U) + 6;
    particle.lifetime = particle.initialLifetime = (func_150ADA20() % 451U) + 0xFA;
    particle.field30 = 0;
    particle.field31 = 0;
    particle.field32 = 0;
    particle.alpha = 0xFF;
    particle.field1F = -1;
    particle.field34 = 0;
    particle.fieldC = 0;
    particle.fieldE = 0;
    particle.x = (s32)arg2;
    particle.red = particle.green = particle.blue = D_8008F8D0[arg11];
    particle.y = (s32)arg3;
    particle.z = (s32)arg4;
    particle.fractionX = particle.fractionY = particle.fractionZ = (s32)(arg2 * 256.0f);
    switch (arg11) {
        case 0:
            particle.descriptor = D_800918A0;
            break;
        case 1:
            particle.descriptor = D_8009187C;
            break;
    }
    particle.field28 = 0xC8;
    func_15167D84(&particle, 0, 0, -1, (u8)arg14, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A0C0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CDEC0/func_151A0C0C.s")
