#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D2B10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 radiusX;
    s16 height;
    s16 radiusZ;
    u8 padC[4];
    f32 rotation;
    u8 state;
    u8 flags;
} Game1D2B10Region;

typedef struct {
    Game1D2B10Region *region;
    f32 rate;
    f32 scale;
    f32 pending;
    f32 field10;
    f32 xScaleBase;
    f32 xScaleRange;
    f32 yScaleBase;
    f32 yScaleRange;
    s16 field24Base;
    s16 field24Range;
    f32 field38Base;
    f32 field38Range;
    f32 field40Base;
    f32 field40Range;
    f32 field44Base;
    f32 field44Range;
    u8 useGround;
    u8 field2CBase;
    u8 field2CRange;
    u8 pad43[5];
    f32 groundY;
    u8 pad4C[0x20];
    s16 *shape;
} Game1D2B10Emitter;

typedef struct {
    Vec3f position;
    f32 field0C;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    s16 field20;
    s16 field22;
    s16 field24;
    u8 color26[4];
    s16 field2A;
    u8 field2C;
    u8 field2D;
    u8 field2E;
    u8 field2F;
    s32 field30;
    u8 field34;
    u8 pad35[3];
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
} Game1D2B10Particle;

void *func_15149550(f32 *, u8, u8, u8, u8, s32);
f32 func_150ADA68(void);
s32 func_15046C80(f32 *, u16, f32, void *);
extern f32 D_800BE9A4;

void func_151A5660(u8 *arg0) {
    Game1D2B10Emitter *emitter;
    Game1D2B10Particle particle;
    f32 low;
    f32 high;
    f32 xScale;
    f32 yScale;

    emitter = (Game1D2B10Emitter *)(arg0 + 0x28);
    if (emitter->region == NULL) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (emitter->region->state == 1) {
        return;
    }
    if (emitter->shape != NULL && func_151464B8(emitter->shape) != 0) {
        return;
    }
    emitter->pending += emitter->scale * emitter->rate * D_800BE9A4;
    if (emitter->pending > 1.0f) {
        particle.field20 = 0x6231;
        particle.field22 = 0x1A4D;
        particle.color26[0] = 0;
        particle.color26[1] = 0;
        particle.color26[2] = 0;
        particle.color26[3] = 0xFF;
        particle.field2A = 1;
        particle.field2D = 0xFF;
        particle.field30 = 0;
        particle.field2E = 0;
        particle.field2F = 0;
        particle.field34 = 0x10;
        particle.field3C = emitter->field10;
        do {
            switch (emitter->region->flags & 3) {
            case 2: {
                u8 angle;
                f32 cosine;
                f32 sine;
                f32 x;
                f32 z;

                angle = emitter->region->rotation * 0.7111111f;
                cosine = func_151423D8(angle - 0x40);
                sine = func_151423D8(angle);
                x = func_150ADA68() * (2.0f * emitter->region->radiusX) + -emitter->region->radiusX;
                z = func_150ADA68() * (2.0f * emitter->region->radiusZ) + -emitter->region->radiusZ;
                particle.position.x = emitter->region->x + (x * sine + z * cosine);
                particle.position.z = emitter->region->z + (z * sine - x * cosine);
                high = emitter->region->y + emitter->region->height;
                low = emitter->region->y - emitter->region->height;
            } break;
            case 0: {
                u8 angle;
                f32 cosine;
                f32 sine;
                f32 x;

                angle = func_150ADA20() & 0xFF;
                cosine = func_151423D8(angle - 0x40);
                sine = func_151423D8(angle);
                x = func_150ADA68() * emitter->region->radiusX;
                particle.position.x = emitter->region->x + x * sine;
                particle.position.z = emitter->region->z - x * cosine;
                high = emitter->region->y + emitter->region->height;
                low = emitter->region->y;
            } break;
            case 1: {
                u8 angle;
                f32 cosine;
                f32 sine;
                f32 x;

                angle = func_150ADA20() & 0xFF;
                cosine = func_151423D8(angle - 0x40);
                sine = func_151423D8(angle);
                x = func_150ADA68() * emitter->region->radiusX;
                particle.position.x = emitter->region->x + x * sine;
                particle.position.z = emitter->region->z - x * cosine;
                high = emitter->region->y + emitter->region->height;
                low = emitter->region->y - emitter->region->height;
            } break;
            default:
                particle.position.x = emitter->region->x;
                particle.position.z = emitter->region->z;
                high = emitter->region->y + emitter->region->height;
                low = emitter->region->y - emitter->region->height;
                break;
            }
            if (emitter->useGround != 0) {
                Vec3f probe;

                probe.x = particle.position.x;
                probe.y = high;
                probe.z = particle.position.z;
                if (func_15046C80(&probe.x, 0, low, &emitter->groundY) != 0) {
                    particle.position.y = emitter->groundY;
                } else {
                    particle.position.y = low;
                }
            } else {
                particle.position.y = low;
            }
            xScale = func_150ADA68() * emitter->xScaleRange + emitter->xScaleBase;
            yScale = func_150ADA68() * emitter->yScaleRange + emitter->yScaleBase;
            particle.field0C = 22.6f * xScale;
            particle.field14 = 13.786f * xScale;
            particle.field10 = 57.969f * yScale;
            particle.field18 = 42.714f * yScale;
            particle.field1C = 118.763f * yScale;
            particle.field24 = func_150ADA20() % (emitter->field24Range + 1) + emitter->field24Base;
            particle.field38 = func_150ADA68() * emitter->field38Range + emitter->field38Base;
            particle.field40 = func_150ADA68() * emitter->field40Range + emitter->field40Base;
            particle.field44 = func_150ADA68() * emitter->field44Range + emitter->field44Base;
            particle.field2C = func_150ADA20() % (emitter->field2CRange + 1) + emitter->field2CBase;
            func_15149550(&particle.position.x, 10, 0, 0, arg0[0xC], arg0[1]);
            emitter->pending -= 1.0f;
        } while (emitter->pending > 1.0f);
    }
}
/* Call context: func_1514933C: unique active project prototype */

extern void func_151A5D2C(u16 arg0, void *arg1);

void func_151A5CAC(void *arg0) {
    u8 *state;

    state = (u8 *)arg0 + 0x58;
    if (*(u16 *)((u8 *)arg0 + 0x6C) != 0) {
        func_151A5D2C(*(u16 *)(state + 0x14), arg0);
    }
    func_1514933C(arg0);
}

void func_151A5CEC(void *arg0) {
    u8 *state;

    state = (u8 *)arg0 + 0x58;
    if (*(u16 *)((u8 *)arg0 + 0x6C) != 0) {
        func_151A5D2C(*(u16 *)(state + 0x14), arg0);
    }
    func_15149368(arg0);
}
/* Call context: func_100111C8: unique active project prototype */
void func_100111C8(u16, void *);

void func_151A5D2C(u16 arg0, void *arg1) {
    func_100111C8(arg0, arg1);
}
typedef struct Game1D2B10Effect {
    s32 flags;
    s16 duration;
    u8 kind;
    u8 field7;
    s32 field8;
    s32 step;
    u8 field10, field11, field12, field13;
    u8 field14, field15, field16, field17;
    s32 field18;
    u8 pad1C[4];
    u8 field20;
    u8 pad21;
    s16 field22;
    s16 field24;
    u8 pad26[2];
} Game1D2B10Effect;

void *func_1513C650(s32, u8, u8, s32, f32, f32, f32, f32, f32, u8, u8, s32, s32, s32, u8, s32);

void *func_151A5D58(f32 arg0, u8 arg1, s32 arg2, f32 *arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, s32 arg8) {
    s32 visible;
    Game1D2B10Effect effect;

    if (arg4 <= 0) {
        return 0;
    }
    effect.field22 = 0x14;
    effect.field24 = 0xC;
    effect.kind = 0x38;
    effect.field7 = 0;
    visible = (arg4 == -1) ? 0 : 1;
    effect.flags = (arg5 ? 0x400 : 0) | visible | 0x1000 | 0x200 | 0x100 | 0x2000 | 0x8000 | 0x20000;
    effect.duration = (arg4 == -1) ? 0x12C : arg4 + 0x14;
    effect.field8 = 0;
    effect.step = (arg4 == -1) ? 0 : 0x140000 / (arg4 + 0x14);
    effect.field10 = arg1;
    effect.field11 = 0xFF;
    effect.field12 = 0xFF;
    effect.field13 = 0x83;
    effect.field14 = 0x1E;
    effect.field15 = 0xFF;
    effect.field18 = (arg6 ? 2 : 3) + 0x440000;
    effect.field16 = 0;
    effect.field17 = 6;
    effect.field20 = 0xFF;
    return func_1513C650((s32)&effect, 0, 0, arg2, arg3[0], arg3[1], arg3[2], arg0, arg0, func_150ADA20() & 0xFF,
                         (func_150ADA20() & 1) + (func_150ADA20() & 1) * 2, arg5 ? 3 : 0, arg5 ? 0xFF : 0, 0, arg7, arg8);
}
