#include "types.h"

/*
 * Reviewed source unit: src/game/game_E4FF0.c
 * Boundary evidence: docs/evidence/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B7B40
 * - func_150B82D0
 * - func_150B85C0
 * - func_150B879C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_E4FF0/func_150B7B40.s")
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
void func_1518A3C0(f32 *, f32 *, f32, f32 *, f32 *, f32, f32,
                   s32, s32, s32, s32, s32, s32);
extern f32 D_8009FD68;
extern f32 D_8009FD6C;
extern f32 D_8009FD70;
extern f32 D_8009FD74;
extern f32 D_8009FD78;
extern f32 D_8009FD7C;
extern f32 D_8009FD80;
extern f32 D_8009FD84;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B82D0 CURRENT (5069) */
void func_150B82D0(f32 *arg0, s32 arg1, f32 *arg2, f32 *arg3) {
    f32 position[3];
    f32 rotation[3];
    f32 velocity[3];
    f32 acceleration[3];
    s16 yaw;
    s16 pitch;
    s32 count;
    f32 randomSize;
    f32 randomScale;

    count = (func_150ADA20() % 26U) + 0x23;
    if (count > 0) {
        do {
            yaw = func_150ADA20() & 0xFF;
            pitch = (func_150ADA20() % 61U) - 0x3F;
            func_15143794(yaw, pitch, *arg2, position);
            position[1] *= *arg3;
            position[0] += arg0[0];
            position[1] += arg0[1];
            position[2] += arg0[2];
            rotation[0] = func_150ADA68() * 360.0f;
            rotation[1] = func_150ADA68() * 360.0f;
            rotation[2] = func_150ADA68() * 360.0f;
            func_15143794(yaw, pitch,
                           (func_150ADA68() * D_8009FD74 + D_8009FD78) * 0.00999999978f,
                           velocity);
            acceleration[0] = (func_150ADA68() * 3140.0f + -1570.0f) * 0.00999999978f;
            acceleration[1] = 0.0f;
            acceleration[2] = (func_150ADA68() * 3140.0f + -1570.0f) * 0.00999999978f;
            randomSize = (func_150ADA68() * 104.0f + 78.0f) * D_8009FD7C;
            randomScale = func_150ADA68() * D_8009FD80;
            func_1518A3C0(position, rotation,
                           randomSize,
                           velocity, acceleration,
                           (randomScale + -1064.0f) * D_8009FD7C,
                           D_8009FD84, 1, (func_150ADA20() % 51U) + 0x4B,
                           0, 0, 0xFF, 1);
            count--;
        } while (count != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B82D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4FF0/func_150B82D0.s")
typedef struct GameE4FF0Vector {
    f32 x, y, z;
} GameE4FF0Vector;

typedef struct GameE4FF0Descriptor {
    s32 flags;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s32 fieldC;
    s32 field10;
    u8 color14[4];
    u8 color18[4];
    u8 alpha;
    u8 kind;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    GameE4FF0Vector position;
    GameE4FF0Vector velocity;
    GameE4FF0Vector acceleration;
    f32 field54;
    s32 field58;
    s32 field5C;
    u8 field60;
    u8 field61;
    s8 field62;
    s8 field63;
    s8 field64;
    s8 field65;
    u8 pad66[0xA];
} GameE4FF0Descriptor;

u32 func_150ADA20(void);
void *func_15130374(s32, u8, s32, u8, s32);
extern f32 D_8009FD88;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B85C0 CURRENT (285) */
void func_150B85C0(GameE4FF0Vector *arg0, f32 *arg1, f32 *arg2, s32 arg3, s32 arg4) {
    GameE4FF0Descriptor descriptor;
    s32 second;
    s32 first;

    descriptor.kind = 0x29;
    descriptor.field8 = 0xE03;
    descriptor.flags = 0x200005;
    descriptor.field4 = 0;
    descriptor.fieldA = (func_150ADA20() % 11U) + 0x23;
    descriptor.fieldC = 0;
    descriptor.field10 = 0;
    descriptor.color18[0] = 0xB0;
    descriptor.color18[1] = 0xA0;
    descriptor.color18[2] = 0x2A;
    descriptor.color14[0] = 0x40;
    descriptor.color14[1] = 0xB;
    descriptor.color14[2] = 0x6A;
    descriptor.color14[3] = 0xFF;
    descriptor.color18[3] = (func_150ADA20() % 51U) + 0x64;
    descriptor.alpha = 0xFF;
    descriptor.field60 = 3;
    descriptor.field61 = 3;
    descriptor.field28 = *arg2 * 20.0f;
    descriptor.field2C = *arg1 * 20.0f;
    descriptor.position = *arg0;
    descriptor.velocity.x = 0.0f;
    descriptor.velocity.y = 0.0f;
    descriptor.velocity.z = 0.0f;
    descriptor.acceleration.x = 0.0f;
    descriptor.acceleration.y = 0.0f;
    descriptor.acceleration.z = 0.0f;
    descriptor.field54 = 0.0f;
    first = (func_150ADA20() & 1) ? 0x40 : 0;
    if (func_150ADA20() & 1) {
        second = 0x80;
    } else {
        second = 0;
    }
    descriptor.field58 = second | 0xE01 | first | 0xC000;
    descriptor.field62 = -1;
    descriptor.field63 = -1;
    descriptor.field1E = 0x19;
    descriptor.field20 = 0xA;
    descriptor.field22 = 0x28;
    descriptor.field64 = -1;
    descriptor.field65 = 0;
    descriptor.field24 = D_8009FD88;
    func_15130374((s32)&descriptor, 1, 0, (u8)arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B85C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4FF0/func_150B85C0.s")
f32 func_150ADA68(void);
void func_15143874(s16, f32, f32 *, f32 *);
void *func_10022EC0(void *, const void *, u32);
extern f32 D_8009FD8C;
extern f32 D_8009FD90;
extern f32 D_8009FD94;
extern f32 D_8009FD98;
extern f32 D_8009FD9C;
extern f32 D_8009FDA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B879C CURRENT (435) */
s32 func_150B879C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    f32 extra;
    f32 scale;
    GameE4FF0Descriptor descriptor;
    void *object;
    s32 second;
    s32 first;

    descriptor.kind = 0x29;
    descriptor.field8 = 0xE03;
    descriptor.flags = 0x200005;
    descriptor.field4 = 0;
    extra = D_8009FD8C;
    descriptor.fieldA = (func_150ADA20() & 0xF) + 0x19;
    descriptor.fieldC = 0;
    descriptor.field10 = 0;
    descriptor.color18[0] = 0xB0;
    descriptor.color18[1] = 0xA0;
    descriptor.color18[2] = 0x2A;
    descriptor.color14[0] = 0x40;
    descriptor.color14[1] = 0xB;
    descriptor.color14[2] = 0x6A;
    descriptor.color14[3] = 0xFF;
    descriptor.color18[3] = (func_150ADA20() % 71U) + 0x3C;
    descriptor.alpha = 0xFF;
    descriptor.field60 = 3;
    descriptor.field61 = 3;
    scale = (func_150ADA68() * D_8009FD90 + D_8009FD94) * D_8009FD98;
    descriptor.field28 = scale;
    descriptor.field2C = scale;
    descriptor.position.x = arg2;
    descriptor.position.y = arg3;
    descriptor.position.z = arg4;
    descriptor.velocity.x = 0.0f;
    descriptor.velocity.y = 0.0f;
    descriptor.velocity.z = 0.0f;
    func_15143874((s16)arg8, (func_150ADA68() * 154.0f + 205.0f) * D_8009FD9C,
                   &descriptor.acceleration.x, &descriptor.acceleration.z);
    descriptor.acceleration.y = 0.0f;
    descriptor.field54 = 0.0f;
    first = (func_150ADA20() & 1) ? 0x40 : 0;
    if (func_150ADA20() & 1) {
        second = 0x80;
    } else {
        second = 0;
    }
    descriptor.field58 = second | 0xE05 | first | 0xC000;
    descriptor.field62 = 0xA;
    descriptor.field63 = -1;
    descriptor.field1E = 0x1C;
    descriptor.field20 = 9;
    descriptor.field22 = 0x19;
    descriptor.field64 = -1;
    descriptor.field65 = 0;
    descriptor.field24 = D_8009FDA0;
    object = func_15130374((s32)&descriptor, 1, 4, (u8)arg14, 1);
    if (object != 0) {
        func_10022EC0((u8 *)object + 0xA8, &extra, 4);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B879C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4FF0/func_150B879C.s")
