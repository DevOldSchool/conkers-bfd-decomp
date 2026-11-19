#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_100810.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_owner_audio_effect.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D3A68
 * - func_150D3FD4
 * - func_150D4300
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150D4C2C(void *arg0);

void *func_1503195C(void *, s32, s32);
s32 func_150D4AE0(f32 *arg0, f32 *arg1, void *arg2, s32 arg3);
s32 func_150D5124(u8 *, s32, u32 *, s32, s32 *, s32, u16 *);
extern s8 D_8008FD8C;
extern s32 D_800A09C0[];

typedef struct Game100810Link {
    u8 *id;
    u8 slot;
    u8 active;
    u8 pad6[2];
    void *handle;
    s32 effects[2];
    f32 field14;
    f32 field18;
} Game100810Link;

typedef struct Game100810Spawn {
    Vec3f position;
    s16 life;
    u16 flags;
    s32 mode;
    u8 kind;
    u8 rate;
    s32 field18;
} Game100810Spawn;

typedef struct Game100810EffectDescriptor {
    u8 kind, mode;
    u16 flags;
    s16 lifetime;
    u8 pad6[2];
    s32 callback0, callback1;
    u8 colors[4];
    f32 field14, field18;
    Vec3f position, direction;
    f32 scales[3];
    u32 options;
    u8 channels[4];
    s32 parameter;
    u8 field4C;
    u8 pad4D[0xB];
} Game100810EffectDescriptor;

typedef struct Game100810EffectParameters {
    f32 values[9];
    s32 handles[4];
    s32 links[4];
    s32 count;
    f32 multiplier;
    s16 angles[4];
    u8 colors[4];
    u8 state;
    s8 mode;
} Game100810EffectParameters;

typedef struct Game100810EffectLink {
    s16 timer;
    f32 scale;
} Game100810EffectLink;

void *func_10022EC0(void *, const void *, u32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, u8, s32);
s32 func_151407D0(void *, u32, void *, u8, u8, u8, u8, s8, u8, s32);

void func_150D3360(void *arg0, u8 arg1, s32 arg2) {
    Game100810Spawn spawn;
    Game100810Link owner;
    void *object;
    Vec3f direction;
    Game100810Link *link;

    spawn.rate = 0x19;
    spawn.life = 0x12C;
    spawn.flags = 0x12;
    spawn.mode = 0xF;
    spawn.kind = 1;
    owner.field18 = 20.0f;
    owner.field14 = 20.0f;
    owner.active = 1;
    owner.effects[0] = 0;
    owner.effects[1] = 0;
    owner.id = arg0;
    owner.slot = *(u8 *)((u8 *)arg0 + 0x3B);
    owner.handle = func_1503195C(arg0, (*(u8 *)((u8 *)arg0 + 4) == 0x48) ? 0x7A : 0x79, 0);
    if (owner.handle == NULL) {
        return;
    }
    if (func_150D4AE0(&spawn.position.x, &direction.x, arg0, (s32)owner.handle) != 0) {
        spawn.flags |= 4;
    } else {
        spawn.position.x = 0.0f;
        spawn.position.y = 0.0f;
        spawn.position.z = 0.0f;
        direction.x = 0.0f;
        direction.z = 0.0f;
        direction.y = 500.0f;
    }
    object = func_15147A80(&spawn, (void *)0x20, 0x14, 0, 0xD, 0xD, 0, 0, 0, arg1, arg2);
    if (object == NULL) {
        return;
    }
    link = *(Game100810Link **)((u8 *)object + 0x98);
    func_10022EC0(link, &owner, 0x1C);
    if (D_8008FD8C < 5) {
        func_1000FA64(0x5B3, *(f32 *)(link->id + 0x14), *(f32 *)(link->id + 0x18),
                      *(f32 *)(link->id + 0x1C), 1000, 1000, 200, func_150D5124, (s32)link, 0x5B3, 0xC, 0);
    }
    func_1000FA64(0x5B4, *(f32 *)(link->id + 0x14), *(f32 *)(link->id + 0x18),
                  *(f32 *)(link->id + 0x1C), 1000, 1000, 200, func_150D5124, (s32)link, 0x5B4, 0xC, 0);
    if (D_8008FD8C < 7 || *(s32 *)((u8 *)arg0 + 0x318) != 0) {
        func_1000FA64(0x5BC, *(f32 *)(link->id + 0x14), *(f32 *)(link->id + 0x18),
                      *(f32 *)(link->id + 0x1C), 1000, 1000, 200, func_150D5124, (s32)link, 0x5BC, 0xC, 0);
    }
    {
        Game100810EffectParameters glowParameters;
        Game100810EffectDescriptor glow;

        glowParameters.values[0] = 200.0f;
        glowParameters.values[1] = 40.0f;
        glowParameters.values[2] = 40.0f;
        glowParameters.values[3] = 40.0f;
        glowParameters.values[4] = 0.05f;
        glowParameters.values[5] = 0.05f;
        glowParameters.values[6] = 0.45f;
        glowParameters.values[7] = 0.3f;
        glowParameters.values[8] = 0.000001f;
        glowParameters.handles[0] = -1;
        glowParameters.links[0] = -1;
        glowParameters.handles[1] = -1;
        glowParameters.links[1] = -1;
        glowParameters.handles[2] = -1;
        glowParameters.links[2] = -1;
        glowParameters.handles[3] = -1;
        glowParameters.links[3] = -1;
        glowParameters.count = 0;
        glowParameters.multiplier = 1.0f;
        glowParameters.angles[0] = 0;
        glowParameters.angles[1] = 0;
        glowParameters.angles[2] = 0;
        glowParameters.angles[3] = 0;
        glowParameters.colors[0] = 0;
        glowParameters.colors[1] = 0;
        glowParameters.colors[2] = 0;
        glowParameters.colors[3] = 0;
        glowParameters.state = 0;
        glowParameters.mode = -1;
        glow.kind = 0x15;
        glow.mode = 3;
        glow.flags = 0x5503;
        glow.lifetime = 0x12C;
        glow.callback0 = 0;
        glow.callback1 = 0;
        glow.colors[0] = 0xFF;
        glow.colors[1] = 0xFF;
        glow.colors[2] = 0xFF;
        glow.colors[3] = 0xFF;
        glow.field14 = 100.0f;
        glow.field18 = 100.0f;
        glow.position = spawn.position;
        glow.direction = direction;
        glow.scales[0] = 1.0f;
        glow.scales[1] = 1.0f;
        glow.scales[2] = 1.0f;
        glow.options = 0xCD2006;
        glow.channels[0] = 0xFF;
        glow.channels[1] = 0xFF;
        glow.channels[2] = 0;
        glow.channels[3] = 6;
        glow.parameter = 0;
        glow.field4C = 0xFF;
        link->effects[0] = func_151407D0(&glowParameters, 0x60, &glow, 0, 0, 0, 0, -1, arg1, arg2);
    }
    {
        Game100810EffectParameters sparkParameters;
        Game100810EffectDescriptor spark;
        Game100810EffectLink sparkLink;

        sparkLink.timer = 0;
        sparkLink.scale = 1.0f;
        sparkParameters.values[1] = 45.0f;
        sparkParameters.values[0] = 45.0f;
        sparkParameters.values[3] = 25.5f;
        sparkParameters.values[2] = 25.5f;
        sparkParameters.values[4] = 0.1f;
        sparkParameters.values[5] = 0.1f;
        sparkParameters.values[6] = 1.0f;
        sparkParameters.handles[0] = -1;
        sparkParameters.links[0] = -1;
        sparkParameters.handles[1] = -1;
        sparkParameters.links[1] = -1;
        sparkParameters.handles[2] = -1;
        sparkParameters.links[2] = -1;
        sparkParameters.handles[3] = -1;
        sparkParameters.links[3] = -1;
        sparkParameters.count = 0;
        sparkParameters.multiplier = 1.0f;
        sparkParameters.angles[0] = 0;
        sparkParameters.angles[1] = 0;
        sparkParameters.angles[2] = 0;
        sparkParameters.angles[3] = 0;
        sparkParameters.colors[0] = 0;
        sparkParameters.colors[1] = 0;
        sparkParameters.colors[2] = 0;
        sparkParameters.colors[3] = 0;
        sparkParameters.state = 0;
        sparkParameters.mode = -1;
        sparkParameters.values[7] = 0.8f;
        sparkParameters.values[8] = 0.000001f;
        spark.kind = D_800A09C0[func_150ADA20() & 3];
        spark.mode = 3;
        spark.flags = 0x2203;
        spark.lifetime = 0x12C;
        spark.callback0 = 0;
        spark.callback1 = 0;
        spark.colors[0] = 0xFF;
        spark.colors[1] = 0xFF;
        spark.colors[2] = 0xFF;
        spark.colors[3] = 0xFF;
        spark.field14 = 100.0f;
        spark.field18 = 100.0f;
        spark.position = spawn.position;
        spark.direction = direction;
        spark.options = 0xCD2006;
        spark.channels[0] = 0xFF;
        spark.channels[1] = 0xFF;
        spark.channels[2] = 0;
        spark.channels[3] = 7;
        spark.parameter = 0;
        spark.field4C = 0xFF;
        spark.scales[0] = 1.0f;
        spark.scales[1] = 1.0f;
        spark.scales[2] = 1.0f;
        link->effects[1] = func_151407D0(&sparkParameters, 0x68, &spark, 0, 0x27, 0, 0, -1, arg1, arg2);
        if (link->effects[1] != 0) {
            func_10022EC0((void *)(link->effects[1] + 0x170), &sparkLink, 8);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3A68.s")
extern f32 D_800A0A10;
extern u8 D_800C35EA;
extern void *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D3FD4 CURRENT (6598) */
s32 func_150D3FD4(void *arg0) {
    void **volatile sp8C;
    u8 *sp88;
    volatile f32 sp84;
    volatile f32 sp80;
    u8 *sp7C;
    f32 sourceX;
    f32 sourceY;
    f32 sourceZ;
    f32 scale;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fs2;
    f32 var_fs3;
    f32 var_fv0;
    f32 var_fv1;
    void **temp_t6;
    s32 temp_a1;
    s32 var_a0;
    u8 *var_t0;
    s32 var_v0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_t6 = *(void ***)((u8 *)arg0 + 0x98);
    sp8C = temp_t6;
    var_t0 = *(u8 **)((u8 *)arg0 + 0x94);
    if (D_800C35EA != 1) {
        sp88 = var_t0;
        var_t0 = sp88;
        if (func_1515C0F8(*temp_t6, &sp7C) != 0) {
            var_fv1 = func_15143E64(sp7C);
        } else {
            var_fv1 = 0.0f;
        }
    } else if (*(s32 *)((u8 *)D_800DBFF0 + 0x5F0) & 4) {
        var_fv1 = 0.0f;
    } else {
        var_fv1 = 128.0f;
    }
    if (var_fv1 < 10.0f) {
        var_fs3 = 0.0f;
    } else if (var_fv1 > 70.0f) {
        var_fs3 = 600.0f;
    } else {
        var_fs3 = (var_fv1 - 10.0f) * D_800A0A10 * 600.0f;
    }
    if (*(s8 *)((u8 *)arg0 + 0x2C) >= 2) {
        var_fs2 = 0.0f;
        var_a0 = *(s8 *)((u8 *)arg0 + 0x2E) - 1;
        if (var_a0 < 0) {
            var_a0 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
        }
        if (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D)) {
            do {
                temp_a1 = var_a0;
                var_a0 -= 1;
                if (var_a0 < 0) {
                    var_a0 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
                }
                temp_v1 = (temp_a1 * 0x14) + var_t0;
                temp_ft4 = *(f32 *)((u8 *)temp_v1 + 0xC);
                var_fs2 += temp_ft4;
                if (var_fs3 < var_fs2) {
                    if (temp_ft4 != 0.0f) {
                        temp_fa1 = (var_fs2 - var_fs3) / temp_ft4;
                        sourceX = *(f32 *)((u8 *)temp_v1 + 0);
                        sourceY = *(f32 *)((u8 *)temp_v1 + 4);
                        sourceZ = *(f32 *)((u8 *)temp_v1 + 8);
                        temp_v0 = (var_a0 * 0x14) + var_t0;
                        temp_fv0 = *(f32 *)((u8 *)temp_v0 + 0);
                        temp_fv1 = *(f32 *)((u8 *)temp_v0 + 4);
                        temp_fa0 = *(f32 *)((u8 *)temp_v0 + 8);
                        *(f32 *)((u8 *)temp_v0 + 0) = (f32) (temp_fv0 - ((temp_fv0 - sourceX) * temp_fa1));
                        *(f32 *)((u8 *)temp_v0 + 4) = (f32) (temp_fv1 - ((temp_fv1 - sourceY) * temp_fa1));
                        *(f32 *)((u8 *)temp_v0 + 8) = (f32) (temp_fa0 - ((temp_fa0 - sourceZ) * temp_fa1));
                        *(f32 *)((u8 *)temp_v1 + 0xC) = (f32) (*(f32 *)((u8 *)temp_v1 + 0xC) * (1.0f - temp_fa1));
                    }
                    var_fs2 = var_fs3;
                    if (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D)) {
                        do {
                            *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (*(s8 *)((u8 *)arg0 + 0x2D) + 1);
                            if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2D)) {
                                *(s8 *)((u8 *)arg0 + 0x2D) = 0;
                            }
                            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) - 1);
                        } while (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D));
                    }
                }
            } while (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D));
        }
        if (var_fs2 != 0.0f) {
            var_fa0 = 1.0f / var_fs2;
        } else {
            var_fa0 = 0.0f;
        }
        sp80 = var_fa0;
        sp84 = var_fs2;
    }
    if (*(s8 *)((u8 *)arg0 + 0x2C) >= 2) {
        var_v0 = *(s8 *)((u8 *)arg0 + 0x2E);
        var_fv0 = sp84;
        scale = *(f32 *)((u8 *)sp8C + 0x14) * sp80;
        do {
            var_v0 -= 1;
            if (var_v0 < 0) {
                var_v0 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
            }
            temp_v1_2 = (var_v0 * 0x14) + var_t0;
            *(f32 *)((u8 *)temp_v1_2 + 0x10) = (f32) (var_fv0 * scale);
            var_fv0 -= *(f32 *)((u8 *)temp_v1_2 + 0xC);
        } while (var_v0 != *(s8 *)((u8 *)arg0 + 0x2D));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D3FD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3FD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D4300.s")

typedef struct { u8 *a; u8 *b; u8 c8; u8 c9; } Game100810Msg;
void func_150D49C0(u8 *arg0, Game100810Msg *arg1, u8 arg2) {
    Game100810Link *link;
    u8 *other;

    link = *(Game100810Link **)(arg0 + 0x98);
    if ((arg2 == 0) || (arg2 == 0x2E) || (arg2 == 3)) {
        other = arg1->a;
        if ((other == link->id) || (link->slot == *(u8 *)&arg1->b)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (link->id == arg1->a) {
            link->id = arg1->b;
            link->slot = arg1->c9;
            link->handle = func_1503195C(link->id, (link->id[4] == 0x48) ? 0x7A : 0x79, 0);
        } else if (link->id == arg1->b) {
            link->id = arg1->a;
            link->slot = arg1->c8;
            link->handle = func_1503195C(link->id, (link->id[4] == 0x48) ? 0x7A : 0x79, 0);
        }
    }
}
s32 func_1514654C(void *, s32, s32, void **, void **, s32);
extern u8 D_800A09D0;
extern u8 D_800A09DC;

s32 func_150D4AE0(f32 *arg0, f32 *arg1, void *arg2, s32 arg3) {
    void *sp30[2];
    void *sp28[2];

    if (*(s32 *)((u8 *)arg2 + 0x1D4) != 0) {
        sp30[0] = &D_800A09D0;
        sp30[1] = &D_800A09DC;
        sp28[0] = arg0;
        sp28[1] = arg1;
        if (func_1514654C(arg2, arg3, 0, sp30, sp28, 2) != 0) {
            return 1;
        }
        return 0;
    }
    arg0[0] = *(f32 *)((u8 *)arg2 + 0x14);
    arg0[1] = *(f32 *)((u8 *)arg2 + 0x18) + 100.0f;
    arg0[2] = *(f32 *)((u8 *)arg2 + 0x1C);
    arg1[0] = *(f32 *)((u8 *)arg2 + 0x14);
    arg1[1] = *(f32 *)((u8 *)arg2 + 0x18) + 100.0f + 500.0f;
    arg1[2] = *(f32 *)((u8 *)arg2 + 0x1C);
    return 2;
}
void func_150D4BD4(void *arg0) {
    func_150D4C2C(arg0);
    func_151478F4(arg0);
}
void func_150D4C00(void *arg0) {
    func_150D4C2C(arg0);
    func_15147928(arg0);
}
void func_1000FD38(void *, void *, s32);

void func_150D4C2C(void *arg0) {
    void *temp_s0;

    temp_s0 = *(void **)((u8 *)arg0 + 0x98);
    if (D_8008FD8C < 5) {
        func_1000FD38((void *)&func_150D5124, temp_s0, 0x5B3);
    }
    func_1000FD38((void *)&func_150D5124, temp_s0, 0x5B4);
    func_1000FD38((void *)&func_150D5124, temp_s0, 0x5BC);
    if (*(void **)((u8 *)temp_s0 + 0xC) != 0) {
        func_1516972C(*(void **)((u8 *)temp_s0 + 0xC));
    }
    if (*(void **)((u8 *)temp_s0 + 0x10) != 0) {
        func_1516972C(*(void **)((u8 *)temp_s0 + 0x10));
    }
}
extern s32 D_800BE9E4;
extern f32 D_800A0A14;

s32 func_150D4CC4(void *arg0) {
    f32 temp_fv0;
    void *temp_v1;

    temp_v1 = (u8 *)arg0 + 0x110;
    *(s16 *)((u8 *)arg0 + 0x170) =
        (s16)(*(s16 *)((u8 *)arg0 + 0x170) - D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0x170) < 0) {
        *(s8 *)((u8 *)arg0 + 0x18) =
            (s8)D_800A09C0[func_150ADA20() & 3];
        *(s16 *)((u8 *)arg0 + 0x170) =
            (s16)((func_150ADA20() & 7) + 3);
    }
    temp_fv0 = *(f32 *)((u8 *)temp_v1 + 0x48);
    *(f32 *)((u8 *)temp_v1 + 0x48) +=
        (*(f32 *)((u8 *)arg0 + 0x174) - temp_fv0) * D_800A0A14;
    return 1;
}

typedef struct {
    s32 field00, field04;
    s16 field08, field0A;
    s32 field0C, field10;
    u8 colors[8];
    u8 field1C, field1D;
    s16 field1E, field20, field22;
    f32 scale, size1, size2;
    Vec3f position, base, velocity;
    f32 field54;
    s32 flags, field5C;
    u8 field60, field61;
    s8 field62, field63, field64;
    u8 field65, field66, pad67[9];
} Game100810Descriptor;

f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
extern Vec3f D_800A5480;

void func_150D4D58(Vec3f *arg0, Vec3f *arg1, f32 arg2, u8 arg3, s32 arg4) {
    Game100810Descriptor packet;
    u32 random1;
    u32 random0;
    s32 count;
    s16 yaw;
    f32 speed;

    count = (func_150ADA20() % 11U) + 10;
    packet.field08 = 0x2203;
    packet.field00 = 0x200005;
    packet.field04 = 0;
    packet.field0C = 0;
    packet.field10 = 0;
    packet.colors[0] = 0xFF;
    packet.colors[1] = 0xFF;
    packet.colors[2] = 0xFF;
    packet.colors[3] = 0xFF;
    packet.colors[4] = 0xFF;
    packet.colors[5] = 0xFF;
    packet.colors[6] = 0xFF;
    packet.field1C = 0xFF;
    packet.position = *arg0;
    packet.base = D_800A5480;
    packet.field1E = 10;
    packet.field20 = 25;
    packet.field22 = 1;
    packet.flags = 0x4C207;
    packet.field60 = 0;
    packet.field61 = 7;
    packet.field62 = -1;
    packet.field63 = -1;
    packet.field64 = -1;
    packet.field65 = 0;
    packet.field5C = 0;
    packet.field66 = 0xFF;
    packet.scale = 1.0f;
    yaw = arg2 * 182.04445f;
    yaw >>= 8;
    yaw += 0x40;
    do {
        speed = func_150ADA68() * 0.223f + 0.80500007f;
        packet.field1D = D_800A09C0[func_150ADA20() & 3];
        packet.field0A = (func_150ADA20() % 18U) + 27;
        packet.colors[7] = (func_150ADA20() % 156U) + 100;
        packet.size1 = packet.size2 = (func_150ADA68() * 233.0f) + 199.0f;
        random1 = func_150ADA20();
        random0 = func_150ADA20();
        func_15143794((random1 % 130U) + yaw, (random0 % 81U) - 64,
                      (func_150ADA68() * 10.0f) + 5.0f, &packet.velocity);
        packet.velocity.x -= arg1->x * speed;
        packet.velocity.z -= arg1->z * speed;
        packet.field54 = func_150ADA68() * 0.646f + -0.794f;
        packet.flags &= ~0xC0;
        random1 = (func_150ADA20() & 1) ? 0x80 : 0;
        random0 = (func_150ADA20() & 1) ? 0x40 : 0;
        packet.flags |= (s32)(random0 | random1);
        func_15130280(&packet, 1, NULL, 0, arg3, arg4);
        count--;
    } while (count > 0);
}

void func_100111C8(u16);

s32 func_150D5124(u8 *arg0, s32 arg1, u32 *arg2, s32 arg3, s32 *arg4, s32 arg5, u16 *arg6) {
    s32 target = 0;
    s32 pitch = 0;
    u8 *state;
    s32 level;
    s32 currentPitch;
    u8 *owner;

    state = *(u8 **)(arg0 + 0x18);
    level = *(s32 *)(arg0 + 0xC);
    currentPitch = *arg4;
    if ((*(s32 *)(arg0 + 0x1C)) == 0x5B3) {
        owner = *(u8 **)state;
        if (owner != 0) {
            target = (*(f32 *)(owner + 0x28)) * 25.0f;
            if (target > 5000) {
                target = 5000;
            } else if (target < 500) {
                target = 0;
            }
            pitch += (*(f32 *)(owner + 0x28)) * 5.0f;
            if (pitch > 1000) {
                pitch = 1000;
            }
        }
        if (state[5] == 2) {
            target += 7000;
        } else if (state[5] == 1) {
            target += 7000;
            pitch = 400;
        } else {
            pitch = 400;
            if (target != 0) {
                level = target;
            }
        }
    } else if ((*(s32 *)(arg0 + 0x1C)) == 0x5BC) {
        target = 24000;
        if (state[5] == 0) {
            level = 24000;
        } else {
            target = 400;
        }
    } else if ((*(s32 *)(arg0 + 0x1C)) == 0x5B4) {
        if (state[5] == 0) {
            target = 16000;
            pitch = 400;
            level = 16000;
        } else if (state[5] == 1 || D_8008FD8C >= 5) {
            target = 12000;
        } else {
            pitch = 400;
        }
    }
    if (level != target) {
        if (level < target) {
            level += D_800BE9E4 << 8;
            if (level > target) {
                level = target;
            }
        } else {
            level -= D_800BE9E4 << 8;
            if (level < target) {
                level = target;
            }
        }
    }
    if (currentPitch != pitch) {
        if (currentPitch < pitch) {
            currentPitch += D_800BE9E4 << 8;
            if (currentPitch > pitch) {
                currentPitch = pitch;
            }
        } else {
            currentPitch -= D_800BE9E4 * 8;
            if (currentPitch < pitch) {
                currentPitch = pitch;
            }
        }
    }
    if (level < 500) {
        level = 0;
    } else if (*arg6 == 0) {
        *(s16 *)arg0 = (*(s32 *)(arg0 + 0x1C));
        *arg6 = (*(s32 *)(arg0 + 0x1C));
    }
    *(s16 *)(arg0 + 2) = (s32)*(f32 *)(*(u8 **)state + 0x14);
    *(s16 *)(arg0 + 4) = (s32)*(f32 *)(*(u8 **)state + 0x18);
    *(s16 *)(arg0 + 6) = (s32)*(f32 *)(*(u8 **)state + 0x1C);
    if (D_800C35EA == 1) {
        *(s32 *)(arg0 + 0xC) = level >> 1;
        *arg2 >>= 1;
    } else {
        *(s32 *)(arg0 + 0xC) = level;
    }
    *(s16 *)(arg0 + 0x20) = currentPitch;
    *arg4 = (s16)currentPitch;
    if (*arg2 == 0) {
        if (*(u16 *)(arg0 + 0x24) != 0) {
            func_100111C8(*(u16 *)(arg0 + 0x24));
            *(u16 *)(arg0 + 0x24) = 0;
        }
        *arg6 = 0;
    }
    return 0;
}
