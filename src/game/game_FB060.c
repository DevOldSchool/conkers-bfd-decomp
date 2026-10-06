#include "types.h"

/*
 * Reviewed source unit: src/game/game_FB060.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CDBB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
s32 func_15046C80(f32 *, s32, f32, f32 *);
void func_1504715C(f32 *, void *);
u32 func_150ADA20(void);
extern f32 D_800A07B0;

typedef struct GameFB060Trace {
    f32 scratch;
    u8 pad_4[0x20];
    f32 position[3];
} GameFB060Trace;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CDBB0 CURRENT (275) */
void func_150CDBB0(void *arg0, u8 arg1, s32 arg2) {
    GameFB060Trace trace;

    if (arg0 != 0) {
        func_1504715C(&trace.scratch, arg0);
        trace.position[0] = *(f32 *)((u8 *)arg0 + 0x14);
        trace.position[1] = *(f32 *)((u8 *)arg0 + 0x18) + 1000.0f;
        trace.position[2] = *(f32 *)((u8 *)arg0 + 0x1C);
        if (func_15046C80(trace.position, 0,
                          *(f32 *)((u8 *)arg0 + 0x18) - D_800A07B0,
                          &trace.scratch) != 0) {
            trace.position[1] = trace.scratch;
            func_1514C678(trace.position[0], trace.position[1],
                           *(s32 *)&trace.position[2], 251.0f, 0, 0xFF,
                           (func_150ADA20() & 0xF) + 0x23, 0x17, 0,
                           0.0f, 0, arg1);
            func_1514C678(trace.position[0], trace.position[1],
                           *(s32 *)&trace.position[2], 290.0f, 0, 0xFF,
                           (func_150ADA20() % 21U) + 0x1E, 0x18, 0,
                           0.0f, 0, arg1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CDBB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FB060/func_150CDBB0.s")
typedef struct GameFB060Particle {
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
} GameFB060Particle;

void *func_10022EC0(void *, const void *, u32);
void *func_15130374(s32, u8, s32, u8, s32);
void func_15143794(s16, s16, f32, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800A07B4, D_800A07B8, D_800A07BC, D_800A07C0;

s32 func_150CDCF4(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    void *temp_v0;
    GameFB060Particle packet;
    f32 size;
    f32 sp2C;
    f32 fraction;
    u32 sp24;

    packet.field1D = 0x29;
    packet.kind = 0xE03;
    packet.flags = 0x200005;
    packet.field4 = 0;
    packet.duration = (func_150ADA20() % 41U) + 0x32;
    packet.fieldC = 0;
    packet.field10 = 0;
    packet.color1[0] = 0xB0;
    packet.color1[1] = 0xA0;
    packet.color1[2] = 0x2A;
    packet.color0[0] = 0x40;
    packet.color0[1] = 0xB;
    packet.color0[2] = 0x6A;
    packet.color0[3] = 0xFF;
    packet.color1[3] = (func_150ADA20() % 101U) + 0x64;
    packet.field1C = 0xFF;
    packet.field60 = 3;
    packet.field61 = 3;
    size = (func_150ADA68() * D_800A07B4) + 404.0f;
    packet.position[0] = arg2;
    packet.position[1] = arg3;
    packet.position[2] = arg4;
    packet.size0 = size;
    packet.size1 = size;
    sp24 = func_150ADA20();
    fraction = func_150ADA68();
    func_15143794(((s16 *)&arg8)[1], (s16) ((sp24 % 20U) - 0x13), ((fraction * 150.0f) + 150.0f) * D_800A07B8, &packet.direction);
    packet.flags58 = 0xE05;
    packet.field54 = 0.0f;
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x80;
    }
    packet.field62 = 0xA;
    packet.field63 = -1;
    packet.field1E = 0x1E;
    packet.field20 = 8;
    packet.field22 = 0x46;
    packet.field24 = D_800A07BC;
    sp2C = D_800A07C0;
    temp_v0 = func_15130374((s32) &packet, 1U, 4, ((u8 *)&arg14)[3], 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0xA8, &sp2C, 4U);
    }
    return 1;
}
typedef struct GameFB060TransformParticle {
    f32 field0, field4, size0, size1;
    f32 rotation[3], scale[3], position[3], velocity[3];
    f32 rotationRate[3], field4C;
    s32 flags;
    s16 lifetime;
    u16 resource;
    u8 field58, pad59[3];
    s32 field5C;
    u8 alpha, update, secondary, field63, field64, field65;
    u8 cleanup, special, field68, pad69, field6A, pad6B;
    s32 field6C;
    u8 field70, pad71;
    s16 threshold, rate;
    u8 pad76[6];
} GameFB060TransformParticle;

void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_800A07C4, D_800A07C8, D_800A07CC, D_800A07D0;
extern f32 D_800A07D4, D_800A07D8, D_800A07DC, D_800A07E0;

s32 func_150CDF10(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    f32 size;
    GameFB060TransformParticle packet;
    f32 magnitude;
    u32 random;

    packet.position[0] = arg2;
    packet.position[1] = arg3;
    packet.scale[0] = 1.0f;
    packet.scale[1] = 1.0f;
    packet.scale[2] = 1.0f;
    packet.flags = 0x29E8;
    packet.rotation[0] = 0.0f;
    packet.rotation[1] = 0.0f;
    packet.rotation[2] = 0.0f;
    packet.rotationRate[1] = 0.0f;
    packet.field0 = 1.0f;
    packet.resource = 0x20;
    packet.position[2] = arg4;
    packet.field4 = D_800A07C4;
    random = func_150ADA20();
    magnitude = func_150ADA68();
    func_15143794(((s16 *)&arg8)[1], (s16)((random % 41U) - 0x3D),
                 ((magnitude * 101.0f) + 150.0f) * D_800A07C8,
                 packet.velocity);
    packet.rotationRate[0] = ((func_150ADA68() * 260.0f) + -130.0f) * D_800A07CC;
    packet.rotationRate[2] = ((func_150ADA68() * 260.0f) + -130.0f) * D_800A07D0;
    packet.lifetime = (func_150ADA20() % 21U) + 0x32;
    packet.field4C = ((func_150ADA68() * D_800A07D4) + D_800A07D8) * D_800A07DC;
    size = ((func_150ADA68() * 302.0f) + 52.0f) * D_800A07E0;
    packet.field58 = 0;
    packet.field5C = 0;
    packet.size0 = size;
    packet.size1 = size;
    packet.alpha = (func_150ADA20() % 76U) + 0xB4;
    packet.update = 8;
    packet.secondary = 0;
    packet.field63 = 0;
    packet.field64 = 0;
    packet.field65 = 0;
    packet.cleanup = 0;
    packet.special = 0;
    packet.field68 = 0;
    packet.field6A = 2;
    packet.field6C = 0;
    packet.field70 = 0;
    packet.threshold = 0x20;
    packet.rate = 7;
    func_15132A4C(&packet, 3, 0xFF, 0, ((u8 *)&arg14)[3], 0);
    return 1;
}
