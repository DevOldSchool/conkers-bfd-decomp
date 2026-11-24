#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1028F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D5A6C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
typedef struct Game1028F0D5440Packet {
    void *owner;
    u8 type;
    u8 pad5[3];
    f32 value;
} Game1028F0D5440Packet;

void func_150D5440(void *arg0, u8 arg1, s32 arg2) {
    Game1028F0D5440Packet packet;
    u8 *temp_v0;

    packet.owner = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.value = 0.0f;
    temp_v0 = func_15149130(0x12C, -1, 0x38, -1, 0, 0x28, 0xC, (s32)arg1, arg2);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
    }
}
typedef struct Game1028F0Actor {
    s32 field0;
    u8 pad4[0x10];
    Vec3f position14;
    u8 pad20[0x8];
    f32 field28;
    Vec3f field2C;
    u8 pad38[0x3];
    u8 field3B;
    u8 pad3C[0x4];
    f32 field40;
    u8 pad44[0x30];
    u8 field74;
    u8 pad75[0xD7];
    f32 field14C;
    f32 field150;
    u8 pad154[0x2C];
    f32 field180;
    s32 field184;
    u8 pad188[0x4C];
    s32 field1D4;
    u8 pad1D8[0x140];
    struct Game1028F0Link *field318;
} Game1028F0Actor;

typedef struct Game1028F0Link {
    u8 pad0[0x23D];
    u8 field23D;
} Game1028F0Link;

typedef struct Game1028F0Emitter {
    Game1028F0Actor *target;
    u8 type;
    u8 pad5[3];
    f32 timer;
} Game1028F0Emitter;

typedef struct Game1028F0Owner {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD;
    s16 fieldE;
    u8 pad10[0x18];
    Game1028F0Emitter emitter;
} Game1028F0Owner;

typedef struct Game1028F0Spawn {
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s32 fieldC;
    s32 field10;
    u8 colors14[9];
    u8 field1D;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    Vec3f position30;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    f32 field50;
    f32 field54;
    s32 field58;
    s32 field5C;
    s8 fields60[6];
    u8 field66;
    u8 pad67;
} Game1028F0Spawn;

f32 func_150ADA68();
void func_1514373C(f32, f32, f32 *, f32 *);
extern Vec3f D_800A5480;
extern f32 D_800BE9A4;

void func_150D54C8(Game1028F0Owner *arg0) {
    Game1028F0Emitter *emitter;
    Game1028F0Actor *target;
    f32 sideX;
    f32 sideZ;
    Game1028F0Spawn spawn;
    f32 forward[2];
    u8 side;
    f32 offset;
    Vec3f *motion;
    f32 spread;
    f32 rand;
    f32 speed;
    s32 flags;

    emitter = &arg0->emitter;
    target = emitter->target;
    if (target->field0 == 0 || target->field3B != emitter->type) {
        arg0->fieldE = -1;
        return;
    }
    if (target->field28 < 8.0f && (target->field184 & 0x1F) == 0xE) {
        emitter->timer += (3.0000002f + func_150ADA68() * (f32)1) * D_800BE9A4;
        if (emitter->timer > 1.0f) {
            if (func_1515C0F8((struct Game1890A0State *)target, (u8 **)&motion) == 0) {
                motion = &D_800A5480;
            }
            func_1514373C(target->field40 * 0.017453292f, 1.0f, &forward[0], &forward[1]);
            sideX = forward[1];
            sideZ = -forward[0];
            spawn.field1D = 0x28;
            spawn.field8 = 0x2203;
            spawn.field0 = 0x200005;
            spawn.field4 = 0;
            spawn.fieldC = 0;
            spawn.field10 = 0;
            spawn.colors14[0] = 0xFF;
            spawn.colors14[1] = 0xFF;
            spawn.colors14[2] = 0xFF;
            spawn.colors14[3] = 0xFF;
            spawn.colors14[4] = 0xFF;
            spawn.colors14[5] = 0xFF;
            spawn.colors14[6] = 0xFF;
            spawn.colors14[8] = 0xFF;
            spawn.field1E = 5;
            spawn.field20 = 0x33;
            spawn.field22 = 1;
            spawn.field3C = 0.0f;
            spawn.field40 = 0.0f;
            spawn.field44 = 0.0f;
            spawn.field24 = 1.0f;
            spawn.field58 = 0x84C207;
            spawn.fields60[0] = 6;
            spawn.fields60[1] = 8;
            spawn.fields60[2] = -1;
            spawn.fields60[3] = -1;
            spawn.fields60[4] = -1;
            spawn.fields60[5] = 0;
            spawn.field5C = 0;
            spawn.field66 = 0xFF;
            for (;;) {
                side = func_150ADA20() & 1;
                spread = func_150ADA68();
                rand = func_150ADA68();
                offset = side ? 35.0f : -35.0f;
                spawn.position30.x = forward[0] * 180.0f * spread
                    + (target->position14.x + sideX * offset - forward[0] * 180.0f * 0.5f);
                spawn.position30.y = target->field180;
                spawn.position30.z = forward[1] * 180.0f * spread
                    + (target->position14.z + sideZ * offset - forward[1] * 180.0f * 0.5f);
                switch (side) {
                case 0:
                    speed = rand * 2.907f + 6.0000005f;
                    break;
                default:
                    speed = rand * 2.907f + 6.0000005f;
                    break;
                }
                spawn.field48 = (side ? speed : -speed) * sideX - motion->x * 0.564f;
                spawn.field4C = 3.1560001f * speed;
                spawn.field50 = (side ? speed : -speed) * sideZ - motion->z * 0.564f;
                spawn.fieldA = func_150ADA20() % 10U + 0x1F;
                spawn.colors14[7] = func_150ADA20() % 76U + 0xB4;
                spawn.field28 = spawn.field2C = func_150ADA68() * 364.0f + 111.0f;
                spawn.field54 = func_150ADA68() * 0.157f + -2.111f;
                spawn.field58 &= ~0xC0;
                flags = ((func_150ADA20() & 1) ? 0x80 : 0) | ((func_150ADA20() & 1) ? 0x40 : 0);
                spawn.field58 |= flags;
                func_15130280(&spawn, 1, NULL, 0, arg0->fieldC, arg0->field1);
                emitter->timer -= 1.0f;
                if (!(emitter->timer > 1.0f)) {
                    break;
                }
            }
        }
    }
}
void func_150D596C(void *arg0, void *arg1, u8 arg2) {
    u8 *state;
    s32 other;

    state = (u8 *)arg0 + 0x28;
    if ((arg2 == 0) || (arg2 == 0x2F) || (arg2 == 3)) {
        other = *(s32 *)arg1;
        if ((other == *(s32 *)state) || (*(u8 *)(state + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)state) {
            *(s32 *)state = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(state + 4) = *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)state) {
            *(s32 *)state = *(s32 *)arg1;
            *(u8 *)(state + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
void func_150D5A2C(void *arg0) {
    func_1514933C(arg0);
}
void func_150D5A4C(void *arg0) {
    func_15149368(arg0);
}
typedef struct Game1028F0Surface {
    s16 data[9];
} Game1028F0Surface;

typedef struct Game1028F0Burst {
    f32 first, second, width, height;
    Vec3f angles, scale, position, velocity, acceleration;
    f32 scalar4C;
    s32 flags;
    s16 life, kind;
    u8 byte58, pad59[3];
    s32 word5C;
    u8 colors[9], pad69, variant, pad6B;
    void *parent;
    u8 parentKind, pad71;
    s16 value72, value74;
    u8 pad76[2];
    s32 field78;
    u8 pad7C[4];
} Game1028F0Burst;

s32 func_15134070(void *);
void func_10010630(u16, void *, s32, s32, s32);
void func_15145A50(u8 *);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *,
                  f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
s32 func_15144E80(void *, void *, void *, void *);
f32 func_15144A74(void *, void *);
s32 func_15146078(void *, void *, void *);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
void func_151C0360(s32, s32, u8, s32);
void func_150D65F0(s32, s32, u8, s32);
void func_150D6434(s32, u8, s32);
void func_150D6388(f32 *, u8, s32);
void func_150D66A4(u8, u8, s32);
extern s32 *D_80089A20[];
extern s32 D_800A3F14[];
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D5A6C CURRENT (686) */
typedef struct Game1028F0Ids {
    s32 values[3];
} Game1028F0Ids;

static const Game1028F0Ids sGame1028F0Ids = { { 0x6C, 0x6D, 0x6E } };

void func_150D5A6C(Game1028F0Actor *arg0, u8 arg1, s32 arg2) {
    Vec3f pos;
    Vec3f delta;
    Vec3f hitPos;
    u8 hit;
    Game1028F0Surface surface;
    f32 len0;
    f32 len1;
    s32 flags;
    s32 kind;
    f32 distance;
    Vec3f normal;
    Vec3f tangent;
    Vec3f bitangent;
    Game1028F0Burst burst;
    f32 len2;
    f32 len3;
    f32 len4;
    f32 len5;
    f32 len6;
    f32 len7;
    Game1028F0Ids ids;
    s32 j;
    f32 s;
    f32 c;
    s32 valid;
    s32 fallback;
    f32 s2;
    f32 c2;
    f32 scale;
    s32 i;

    hit = 0;
    pos.x = arg0->position14.x;
    pos.y = arg0->position14.y + 50.0f;
    pos.z = arg0->position14.z;
    delta.x = arg0->position14.x - arg0->field2C.x;
    delta.y = arg0->position14.y - arg0->field2C.y;
    delta.z = arg0->position14.z - arg0->field2C.z;
    kind = func_15134070(arg0);
    if (kind == 0x63) {
        return;
    }
    if ((arg0->field184 & 0x1F) == 0xE) {
        func_10010630(0x434, arg0, 0x7D00, 0x2BC, 0x7D0);
    } else {
        func_10010630(0x4C8, arg0, -0x7D00, 0x2BC, 0x7D0);
    }
    func_10010630((func_150ADA20() & 1) + 0x2B6, arg0, 0x7D00, 0x3E8, 0xBB8);
    func_10010630((func_150ADA20() & 3) + 0x2B1, arg0, 0x7D00, 0x2BC, 0x7D0);
    func_151C05A4(&pos.x, arg1, arg2);
    func_151C05F0(&pos.x, arg1, arg2);
    func_15145A50((u8 *)arg0);
    if (arg0->field1D4 == 0) {
        return;
    }
    if ((arg0->field74 & 0xF) == 0xF) {
        return;
    }
    if (func_15145128(&delta.x, &delta.x, &len0, &len1) != 0) {
        valid = 1;
    } else {
        valid = 0;
    }
    if (valid) {
        s32 func_15145128(f32 *, f32 *, f32 *, f32 *);

        if (func_150AC9C0(arg0->field2C.x, arg0->field2C.y, arg0->field2C.z,
                          delta.x, delta.y, delta.z, NULL, surface.data,
                          &hitPos.x, &hitPos.y, &hitPos.z, &distance, NULL, &flags, 0.0f) != 0
            && distance < 397.0f) {
            hit = 1;
        }
    }
    {
        s32 func_15144E80(void *, void *, void *, void *);

    if (hit) {
        fallback = 0;
        if (func_15144E80(&surface, &tangent, &bitangent, &normal) != 0) {
            s32 func_15145128(f32 *, f32 *, f32 *, f32 *);

            func_15145128(&tangent.x, &tangent.x, &len2, &len3);
            func_15145128(&bitangent.x, &bitangent.x, &len4, &len5);
            func_15145128(&normal.x, &normal.x, &len6, &len7);
            if (func_15144A74(&normal, &delta) > 0.0f) {
                normal.x = -normal.x;
                normal.y = -normal.y;
                normal.z = -normal.z;
            }
        } else {
            fallback = 1;
        }
    } else {
        fallback = 1;
    }
    }
    if (fallback) {
        if (valid) {
            normal.x = -delta.x;
            normal.y = -delta.y;
            normal.z = -delta.z;
            func_15146078(&normal, &tangent, &bitangent);
        } else {
            normal.x = 0.0f;
            normal.y = 1.0f;
            normal.z = 0.0f;
            tangent.x = 1.0f;
            tangent.y = 0.0f;
            tangent.z = 0.0f;
            bitangent.x = 0.0f;
            bitangent.y = 0.0f;
            bitangent.z = 1.0f;
        }
    }
    normal.x *= 1000.0f;
    normal.y *= 1000.0f;
    normal.z *= 1000.0f;
    burst.first = 1.0f;
    burst.second = 1.0f;
    burst.width = arg0->field14C;
    burst.height = arg0->field150;
    burst.scale.x = 1.0f;
    burst.scale.y = 1.0f;
    burst.scale.z = 1.0f;
    burst.position = pos;
    burst.flags = 0x21E8;
    burst.byte58 = 0;
    burst.word5C = 0;
    burst.colors[0] = 0xFF;
    burst.colors[1] = 8;
    burst.colors[2] = 0;
    burst.colors[3] = 0;
    burst.colors[4] = 0;
    burst.colors[5] = 0;
    burst.colors[6] = 0;
    burst.colors[7] = 0;
    burst.colors[8] = 2;
    burst.variant = 1;
    burst.parent = arg0;
    burst.parentKind = arg0->field3B;
    burst.field78 = 0;
    burst.acceleration.y = 0.0f;
    {
        f32 func_150ADA68();

    ids = sGame1028F0Ids;
    burst.value72 = 0xC;
    burst.value74 = 0x15;
    for (j = 0; j < 3; j++) {
        scale = func_150ADA68() * 0.0132f + 0.0298f;
        func_15143874((s16)(func_150ADA20() & 0xFF), func_150ADA68() * 759.0f, &c, &s);
        burst.velocity.x = (tangent.x * c + bitangent.x * s + normal.x) * scale;
        burst.velocity.y = (tangent.y * c + bitangent.y * s + normal.y) * scale;
        burst.velocity.z = (tangent.z * c + bitangent.z * s + normal.z) * scale;
        burst.angles.x = func_150ADA68() * 360.0f;
        burst.angles.y = func_150ADA68() * 360.0f;
        burst.angles.z = func_150ADA68() * 360.0f;
        burst.acceleration.x = func_150ADA68() * 38.444f + -19.222f;
        burst.acceleration.z = func_150ADA68() * 38.444f + -19.222f;
        burst.scalar4C = func_150ADA68() * 0.648f + -1.3970001f;
        burst.life = func_150ADA20() % 21U + 0x1E;
        burst.kind = ids.values[j];
        func_15132A4C(&burst, 0, 0, 0, arg1, arg2);
    }
    burst.value72 = 0xC;
    burst.value74 = 0x15;
    for (i = 2; i < D_800A3F14[kind]; i++) {
        scale = func_150ADA68() * 0.02f + 0.0052f;
        func_15143874((s16)(func_150ADA20() & 0xFF), func_150ADA68() * 723.0f, &c2, &s2);
        burst.velocity.x = (tangent.x * c2 + bitangent.x * s2 + normal.x) * scale;
        burst.velocity.y = (tangent.y * c2 + bitangent.y * s2 + normal.y) * scale;
        burst.velocity.z = (tangent.z * c2 + bitangent.z * s2 + normal.z) * scale;
        burst.angles.x = func_150ADA68() * 360.0f;
        burst.angles.y = func_150ADA68() * 360.0f;
        burst.angles.z = func_150ADA68() * 360.0f;
        burst.acceleration.x = func_150ADA68() * 40.45f + -20.225f;
        burst.acceleration.z = func_150ADA68() * 40.45f + -20.225f;
        burst.scalar4C = func_150ADA68() * 0.62600005f + -1.0890001f;
        burst.life = func_150ADA20() % 41U + 0x28;
        burst.kind = D_80089A20[kind][i];
        func_15132A4C(&burst, 0, 0, 0, arg1, arg2);
    }
    if (arg0->field318 != NULL && D_80082FA0 <= 0) {
        func_150D66A4(arg0->field318->field23D, arg1, arg2);
    }
    if (hit && arg0->field318 != NULL) {
        if ((flags & 0x1F) == 0xE) {
            func_150D65F0((s32)&surface, (s32)&hitPos, arg1, arg2);
        } else {
            func_151C0360((s32)&surface, (s32)&hitPos, arg1, arg2);
        }
    }
    func_150D6434((s32)&pos, arg1, arg2);
    func_150D6388(&pos.x, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D5A6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1028F0/func_150D5A6C.s")
void *func_151541B8(void *, f32, f32, f32, f32, u8, s32);
f32 func_150ADA68();

void func_150D6388(f32 *arg0, u8 arg1, s32 arg2) {
    struct {
        f32 value;
        u32 random;
    } locals;

    locals.value = func_150ADA68();
    locals.random = func_150ADA20();
    func_151541B8(arg0, (locals.value * 4.0f) + 15.0f, 1.37457f,
                 (f32)((locals.random % 56U) + 0xC8), 0.0f, arg1, arg2);
}
void *func_15154884(void *, f32, f32, f32, u8, s32);
extern f32 D_800A0AB0;
extern f32 D_800A0AB4;

void func_150D6434(s32 arg0, u8 arg1, s32 arg2) {
    f32 rand3;
    f32 rand2;
    f32 rand1;

    rand1 = func_150ADA68();
    rand2 = func_150ADA68();
    rand3 = func_150ADA68();
    func_15154884((void *)arg0, (rand1 * 3.0f) + 8.0f,
                  (rand2 * D_800A0AB0) + D_800A0AB4,
                  (rand3 * 50.0f) + 100.0f, arg1, arg2);
}
extern s32 D_80082FA0;
extern s8 D_8008FD8C;
extern f32 D_800A0AB8;
extern f32 D_800A0ABC;
extern f32 D_800A0AC0;
extern f32 D_800A0AC4;
extern f32 D_800A0AC8;

void func_150D64E8(void *arg0, f32 *arg1) {
    *(s32 *)((u8 *)arg0 + 0) = 6;
    *(s32 *)((u8 *)arg0 + 4) = 3;
    *arg1 = D_800A0AB8;
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) D_800A0ABC;
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) D_800A0AC0;
    *(f32 *)((u8 *)arg0 + 0x1C) = 150.0f;
    *(f32 *)((u8 *)arg0 + 0x20) = 105.0f;
    *(f32 *)((u8 *)arg0 + 0x24) = 396.0f;
    *(f32 *)((u8 *)arg0 + 0x28) = 612.0f;
    *(s32 *)((u8 *)arg0 + 0x2C) = 4;
    *(s32 *)((u8 *)arg0 + 0x30) = 3;
    *(f32 *)((u8 *)arg0 + 0x34) = 25.0f;
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) D_800A0AC4;
    *(f32 *)((u8 *)arg0 + 0x3C) = -2.0f;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) D_800A0AC8;
    *(s16 *)((u8 *)arg0 + 0x44) = 0x14;
    *(s16 *)((u8 *)arg0 + 0x46) = 0x1E;
    *(s16 *)((u8 *)arg0 + 0x48) = 0x64;
    *(s16 *)((u8 *)arg0 + 0x4A) = 0x64;
    *(s16 *)((u8 *)arg0 + 0x4C) = 0xC;
    *(s16 *)((u8 *)arg0 + 0x4E) = 0x14;
    if ((D_80082FA0 >= 2) || (D_8008FD8C >= 8)) {
        *(s8 *)((u8 *)arg0 + 0x50) = -1;
        return;
    }
    *(s8 *)((u8 *)arg0 + 0x50) = 0;
}
void *func_151A5D58(f32, u8, s32, f32 *, s16, u8, u8, u8, s32);

void func_150D65F0(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    struct {
        f32 value;
        u32 random_value;
        u32 final_random;
    } locals;

    locals.value = func_150ADA68();
    locals.random_value = func_150ADA20();
    locals.final_random = func_150ADA20();
    func_151A5D58((locals.value * 100.0f) + 150.0f,
                  (locals.random_value % 71U) + 0x82,
                  arg0, (f32 *)arg1, (locals.final_random % 31U) + 0x32,
                  0, 1, (u32)arg2, arg3);
}
void func_15182670(s32, s32, s32, s32, s32, s32, s32, s32);

void func_150D66A4(u8 arg0, u8 arg1, s32 arg2) {
    u32 time;
    u32 value;

    value = func_150ADA20();
    time = func_150ADA20();
    func_15182670(0xFF, 0xFF, 0xFF, ((value % 56U) + 0xC8) & 0xFF, (time % 6U) + 0x19, (s32) arg0, (s32) arg1, arg2);
}
