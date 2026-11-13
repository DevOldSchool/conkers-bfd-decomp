#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_10E510.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_timed_actor_emitter.md
 */

typedef struct Game10E510Object1060 {
    u8 pad0[0x10];
    s16 field_10;
    u8 pad12[2];
    s16 field_14;
} Game10E510Object1060;

typedef struct Game10E510Payload1060 {
    u8 index;
    u8 pad1[3];
    Game10E510Object1060 *object;
    s32 value;
    f32 zero;
} Game10E510Payload1060;

void *func_10022EC0(void *, const void *, u32);
void func_1510F800(s32);
s32 func_1510FD20(s16, s16);
extern u8 D_800A0FE0[];

s32 func_150E1060(u8 arg0, u8 arg1, s32 arg2) {
    s32 result;
    Game10E510Payload1060 payload;

    if (arg0 < 0) {
        return 0;
    }
    if (arg0 >= 2) {
        return 0;
    }
    payload.index = arg0;
    payload.object = func_151149AC(D_800A0FE0[arg0]);
    if (payload.object == 0) {
        return 0;
    }
    func_1510F800(0);
    payload.value = func_1510FD20(payload.object->field_10, payload.object->field_14);
    payload.zero = 0.0f;
    result = (s32)func_15149130(0x12C, -1, 0x1F, -1, 0, 0x1F, 0x10, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x28, &payload, 0x10U);
    }
    return result;
}
typedef struct Game10E510Descriptor {
    s32 flags;
    s32 field4;
    s16 field8;
    s16 lifetime;
    s32 fieldC;
    s32 field10;
    u8 color14[4];
    u8 color18[4];
    u8 alpha;
    s8 kind;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 position[3];
    f32 velocity[3];
    f32 acceleration[3];
    f32 field54;
    u32 field58;
    s32 field5C;
    s8 field60;
    s8 field61;
    s8 field62;
    s8 field63;
    s8 field64;
    s8 field65;
    u8 pad66[0xA];
} Game10E510Descriptor;

f32 func_150ADA68(void);
void func_15145CD0(Game10E510Object1060 *, f32 **, f32 **, s32);
void *func_15130374(void *, u8, s32, u8, s32);
extern s32 D_80082FA0;
extern f32 D_800A0FE4[][3];
extern f32 D_800A0FFC[][3];
extern f32 D_800BE9A4;

void func_150E114C(u8 *arg0) {
    Game10E510Payload1060 *payload;
    s32 i;
    s16 mask;
    Game10E510Descriptor descriptor;
    f32 extra;
    f32 offset[3];

    payload = (Game10E510Payload1060 *)(arg0 + 0x28);
    payload->zero += (204.0f + func_150ADA68() * 159.0f) * 0.001f * D_800BE9A4;
    if (payload->zero > 1.0f) {
        i = 0;
        mask = 0;
        for (; i <= D_80082FA0; i++) {
            mask |= 1 << i;
        }
        if (!(((s16 *)payload->value)[1] & mask)) {
            do {
                payload->zero -= 1.0f;
            } while (payload->zero > 1.0f);
            return;
        }
        {
            f32 *sources[2];
            f32 *targets[2];

            descriptor.kind = 0x29;
            descriptor.field8 = 0x4403;
            descriptor.flags = 0x200005;
            descriptor.field1E = 0x21;
            descriptor.field20 = 7;
            descriptor.field58 = 0x1CE05;
            descriptor.field60 = 6;
            descriptor.field61 = 8;
            descriptor.field62 = 0x10;
            descriptor.field63 = -1;
            descriptor.field4 = 0;
            descriptor.fieldC = 0;
            descriptor.field10 = 0;
            descriptor.field54 = 0.0f;
            descriptor.field64 = -1;
            descriptor.field65 = 0;
            descriptor.field22 = 0x27;
            descriptor.color14[0] = 0xDD;
            descriptor.color14[1] = 0xD3;
            descriptor.color14[2] = 0xCD;
            descriptor.color14[3] = 0xFF;
            descriptor.color18[0] = 0x57;
            descriptor.color18[1] = 0x55;
            descriptor.color18[2] = 0x5A;
            descriptor.alpha = 0xFF;
            extra = 0.962339f;
            descriptor.field24 = 1.011462f;
            sources[0] = D_800A0FE4[payload->index];
            sources[1] = D_800A0FFC[payload->index];
            targets[0] = descriptor.position;
            targets[1] = offset;
            func_15145CD0(payload->object, sources, targets, 2);
            offset[0] -= descriptor.position[0];
            offset[1] -= descriptor.position[1];
            offset[2] -= descriptor.position[2];
        }
        do {
            void *object;
            s32 second;
            f32 size;
            f32 speed;

            descriptor.field58 &= ~0xC0;
            second = (func_150ADA20() & 1) ? 0x80 : 0;
            descriptor.field58 |= ((func_150ADA20() & 1) ? 0x40 : 0) | second;
            descriptor.velocity[0] = 0.0f;
            descriptor.velocity[1] = 0.0f;
            descriptor.velocity[2] = 0.0f;
            descriptor.color18[3] = 0xFF;
            descriptor.lifetime = (func_150ADA20() % 17U) + 0x32;
            size = func_150ADA68() * 165.0f + 357.0f;
            descriptor.field28 = size;
            descriptor.field2C = size;
            speed = (func_150ADA68() * 195.0f + 356.0f) * 0.001f;
            descriptor.acceleration[0] = offset[0] * speed;
            descriptor.acceleration[1] = offset[1] * speed;
            descriptor.acceleration[2] = offset[2] * speed;
            object = func_15130374(&descriptor, 1, 4, arg0[0xC], arg0[1]);
            if (object != NULL) {
                func_10022EC0((u8 *)object + 0xA8, &extra, 4);
            }
            payload->zero -= 1.0f;
        } while (payload->zero > 1.0f);
    }
}
