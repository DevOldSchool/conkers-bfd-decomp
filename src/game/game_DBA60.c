#include "types.h"
#include "game_functions.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_DBA60.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AEB9C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameDBA60Camera {
    u8 pad00[0x2C];
    s32 flags2C;
    u8 pad30[0x54];
    u32 flags84;
    u8 pad88[0xAC];
    s32 field134;
    u8 pad138[0x7C];
    s16 mode1B4;
} GameDBA60Camera;
s32 func_1509BE40(s32, ...);
void func_151254F4(void *, s32);
void func_15124B18(u8 *);
extern u8 *D_800D2E4C;

void func_150AE5B0(GameDBA60Camera *arg0) {
    s32 flags;

    if (!(D_800D2E4C[4] & 0x80)) {
        if (func_1509BE40(0, 0x2000, 0xBB) != -1) {
            if (func_15123934(arg0, arg0->flags2C, 0, arg0->field134, 8) != 0) {
                arg0->flags84 |= 0x01000000;
                func_151254F4(arg0, D_800CC335 - 1);
            }
        } else if (func_151239CC(arg0, 8) != 0) {
            func_151254F4(arg0, 0);
        }
    }
    arg0->flags84 &= ~0x4000;
    if (!(D_800D2E4C[1] & 4)) {
        if (func_1509BE40(1, 0x2000, 0x95, func_1509BE40(0, 0x2014, 0xB7) | 0x2000) != 0) {
            arg0->flags84 |= 0x01000000;
            flags = arg0->flags2C;
            if ((flags & 1) && (func_15123934(arg0, flags, 0, arg0->field134, 0) != 0)) {
                arg0->mode1B4 = 3;
                arg0->flags84 &= ~4;
                func_15124B18((u8 *)arg0);
            }
        } else if (func_151239CC(arg0, 0) != 0) {
            func_15124B18((u8 *)arg0);
            arg0->flags84 &= 0xFEFFFFFF;
        }
    }
    if (func_1509BE40(1, 0x4082, 6, 0x9000) != 0) {
        arg0->flags84 |= 0x10000;
        return;
    }
    arg0->flags84 &= 0xFFFEFFFF;
}
typedef struct GameDBA60Owner {
    s32 field00;
    u8 pad04[0x37];
    u8 field3B;
    u8 pad3C[0x144];
    f32 field180;
    u32 flags184;
    u8 pad188[0x4C];
    s32 field1D4;
} GameDBA60Owner;

typedef struct GameDBA60Emitter {
    u8 pad00;
    u8 field01;
    u8 pad02[0xA];
    u8 field0C;
    u8 pad0D[0x1B];
    struct GameDBA60Link {
        GameDBA60Owner *owner;
        u8 ownerId;
        u8 attachPoint;
    } link;
} GameDBA60Emitter;

typedef struct GameDBA60Spawn {
    f32 x, y, z;
    s16 lifetime, field0E;
    s32 field10;
    u8 field14, kind;
} GameDBA60Spawn;

typedef struct GameDBA60Motion {
    f32 size, vx, vy, vz, scale;
    f32 field14;
    u8 field18, field19, field1A, alpha;
    u8 pad1C[4];
} GameDBA60Motion;

typedef struct GameDBA60Options {
    s32 field00, field04, field08, field0C, field10, field14, field18;
    u8 field1C, field1D;
} GameDBA60Options;

/* func_15167D84 copies the full 0x38-byte descriptor. */
typedef struct GameDBA60Particle {
    s32 resource;
    s32 field04;
    s32 field08;
    s16 field0C, field0E;
    s16 x, y, z;
    s16 field16, field18, field1A;
    u8 field1C, field1D, field1E;
    u8 kind;
    s16 field20, field22, field24, field26, field28;
    u8 field2A, field2B;
    u8 red, green, blue, alpha;
    u8 field30, field31, field32;
    u8 pad33;
    s16 field34;
    u8 pad36[2];
} GameDBA60Particle;

f32 func_150ADA68(void);

void func_150AE790(GameDBA60Emitter *arg0) {
    struct GameDBA60Link *link;
    GameDBA60Owner *owner;
    GameDBA60Spawn spawn;
    GameDBA60Motion motion;
    s32 count;
    GameDBA60Options options;
    f32 speed;
    f32 sinAngle, cosAngle, sinPitch, cosPitch;
    f32 horizontal;
    GameDBA60Particle particle;
    u8 angle;
    f32 duration;
    u8 pitch;
    f32 distance;

    link = &arg0->link;
    if (arg0->link.owner != NULL) {
        owner = link->owner;
        if (owner->field00 != 0) {
            if (owner->field1D4 != 0 && owner->field3B == link->ownerId) {
                func_15142314((void *)owner->field1D4, link->attachPoint, &spawn.x);
                spawn.field10 = 1;
                spawn.field0E = 1;
                motion.field19 = 0;
                motion.field1A = 0xFF - ((link->owner->flags184 >> 5) & 3) * 64;
                motion.field14 = link->owner->field180;
                motion.field18 = 8;
                motion.alpha = 0xFF;
                count = func_150ADA20() % 9U + 12;
                options.field00 = 0;
                options.field04 = 1;
                options.field08 = 0x160600;
                options.field0C = 3;
                options.field10 = 0x10;
                options.field14 = 0x80;
                options.field18 = 0x20;
                options.field1C = 0;
                options.field1D = 9;
                for (; count != 0; count--) {
                    angle = func_150ADA20() & 0xFF;
                    pitch = func_150ADA20() % 51U;
                    sinAngle = func_151423D8(angle);
                    cosAngle = func_151423D8(angle - 0x40);
                    sinPitch = func_151423D8(pitch);
                    cosPitch = func_151423D8(pitch - 0x40);
                    speed = func_150ADA68() * 0.5f + 18.8f;
                    spawn.kind = 4;
                    spawn.lifetime = (func_150ADA20() & 0xF) + 0x23;
                    motion.size = func_150ADA68() * 2.3f + 2.9f;
                    motion.scale = func_150ADA68() * 0.1f + 0.7f;
                    horizontal = speed * sinPitch;
                    motion.vx = horizontal * cosAngle;
                    motion.vy = -speed * cosPitch;
                    motion.vz = horizontal * sinAngle;
                    func_15147DA0(&spawn, &motion, 0, 1, 2, 0, 0, 0, 0, 0, 0,
                                  &options, 0, arg0->field0C, arg0->field01);
                }
                duration = func_150ADA68() + 2.5f;
                distance = func_150ADA68() * 200.0f + 600.0f;
                particle.field1A = distance;
                particle.field26 = 0;
                particle.field04 = distance / duration;
                particle.field24 = 0;
                particle.red = 0xFF;
                particle.green = 0xFF;
                particle.blue = 0xFF;
                particle.field30 = 0;
                particle.field31 = 0;
                particle.field32 = 0;
                particle.field28 = 0x64;
                particle.alpha = 0xFF;
                particle.resource = D_8008CB14;
                particle.field2A = 0;
                particle.field0C = 0;
                particle.field0E = 0;
                particle.x = spawn.x;
                particle.y = spawn.y;
                particle.z = spawn.z;
                particle.field1C = 0;
                particle.field1E = 0;
                particle.field1D = 0;
                particle.field16 = 0;
                particle.field18 = 0;
                particle.field22 = 0;
                particle.field20 = 0;
                particle.kind = 0xB;
                particle.field34 = 0;
                particle.field2B = 0;
                particle.field08 = 0;
                func_15167D84(&particle, 0, 0, -1, arg0->field0C, arg0->field01);
            }
        }
    }
}
typedef struct {
    u8 field_0;
    u8 pad_1;
    s16 field_2;
} GameDBA60Entry;

void func_15001A08(void);
extern GameDBA60Entry *D_800886E4;
extern u8 D_800DCE50[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AEB9C CURRENT (2269) */
void func_150AEB9C(void *arg0) {
    u32 *cursor;
    u32 checksum;
    s32 index;
    s32 offset;
    u8 *effect;

    if (arg0 != 0) {
        cursor = (u32 *)(void *)func_15001A08;
        checksum = 0;
        while ((u32)cursor < (u32)&D_15001B08) {
            checksum = (checksum ^ *cursor++) * 2;
        }
        if (checksum != 0xB4E42D60) {
            *(s32 *)(D_800DCE50 + 0x8C) = 0;
            *(s32 *)(D_800DCE50 + 0x22C) = 0;
        }
        index = 0;
        offset = 0;
        if (D_800886E0 > 0) {
            do {
                effect = func_151491F4(*(s16 *)((u8 *)D_800886E4 + offset + 2),
                                       0, -1, 1, 0x27, 8, 0xFF, 0);
                if (effect == 0) {
                    return;
                }
                *(void **)(effect + 0x28) = arg0;
                effect[0x2C] = *(u8 *)((u8 *)arg0 + 0x3B);
                effect[0x2D] = *(u8 *)((u8 *)D_800886E4 + offset);
                index++;
                offset += 4;
            } while (index < D_800886E0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AEB9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AEB9C.s")

void func_150AECCC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x96) = (s16) ((*(s16 *)((u8 *)arg0 + 0x94) * D_800BE9E4) + *(s16 *)((u8 *)arg0 + 0x96));
    if (*(s16 *)((u8 *)arg0 + 0x96) >= 0x1401) {
        *(s16 *)((u8 *)arg0 + 0x96) = 0x1400;
    }
    *(s16 *)((u8 *)arg0 + 0x9E) = (s16) (*(s16 *)((u8 *)arg0 + 0x9E) - (*(s16 *)((u8 *)arg0 + 0x96) >> 8));
    *(s16 *)((u8 *)arg0 + 0xA4) = (s16) (*(s16 *)((u8 *)arg0 + 0xA4) + D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0xA4) >= 0x1A) {
        *(s16 *)((u8 *)arg0 + 0xA4) = 0x19;
    }
}

void func_150AED4C(void *arg0) {
    s32 value;
    s32 limit;

    *(s16 *)((u8 *)arg0 + 0x34) += *(s32 *)((u8 *)arg0 + 0x14) * (u32)D_800BE9E4;
    value = *(s16 *)((u8 *)arg0 + 0x34);
    limit = *(s16 *)((u8 *)arg0 + 0x2A);
    if (limit < value) {
        *(s16 *)((u8 *)arg0 + 0x34) = limit;
        *(s8 *)((u8 *)arg0 + 0x3A) = 0x46;
        value = *(s16 *)((u8 *)arg0 + 0x34);
    }
    *(s16 *)((u8 *)arg0 + 0x36) = value;
}
s32 func_150AED9C(void *arg0) {
    s32 value;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    value = *(s16 *)((u8 *)arg0 + 0x1C);
    value *= 8;
    if (value >= 0x100) {
        value = 0xFF;
    }
    *(s8 *)((u8 *)temp_v0 + 0x1B) = value;
    if ((value & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
typedef struct GameDBA60Object {
    u8 pad0[0x1C];
    s16 field_1C;
    u8 pad1E[0xA];
    s8 field_28;
} GameDBA60Object;

s32 func_150AEDD8(GameDBA60Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x20) {
        arg0->field_28 = value * 8;
    }

    return 1;
}
/* Call context: func_1516972C: unique active declaration in the allowed source */

void func_150AEDF8(void *arg0, void *arg1, u8 arg2) {
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
            func_1516972C(arg0);
        }
    }
}
