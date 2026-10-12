#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1E9A30.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BC5A4
 * - func_151BC794
 * - func_151BCA90
 * - func_151BD21C
 * - func_151BD2F8
 * - func_151BD43C
 * - func_151BD828
 * - func_151BDD8C
 * - func_151BE0AC
 * - func_151BE138
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_151BC580(void *arg0) {
    s32 *value_ptr = *(s32 **)((u8 *)arg0 + 0x40);
    s32 result = 1;

    if (*value_ptr == 0) {
        return 0;
    }
    return result;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BC5A4 CURRENT (10) */
void func_151BC5A4(void *arg0, void *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_v1;
    void *temp_v0;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x40);
    if (arg2 == 0) {
        if ((temp_v1 == *(s32 *)arg1) || (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x44))) {
            func_1516972C((s32)arg0);
        }
    } else {
        temp_v0 = (u8 *)arg0 + 0x40;
        if (arg2 == 0x2D) {
            temp_a0 = *(s32 *)temp_v0;
            temp_v1 = *(s32 *)arg1;
            if (temp_v1 == temp_a0) {
                *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
                *(s32 *)temp_v0 = temp_v1;
                *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BC5A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC5A4.s")
typedef struct Game1E9A30Trail {
    s32 x;
    s32 y;
    s32 z;
    s16 lifetime;
    u8 alpha;
    u8 pad_F[5];
} Game1E9A30Trail;

typedef struct Game1E9A30Position {
    s32 x;
    s32 y;
    s32 z;
} Game1E9A30Position;

extern s32 D_800BE9E4;

s32 func_151BC64C(u8 *actor) {
    Game1E9A30Trail *entries;
    Game1E9A30Trail *entry;
    s32 cursor;
    s16 lifetime;
    s32 opacity;

    entries = *(Game1E9A30Trail **)(actor + 0x94);
    if ((*(s8 *)(actor + 0x2C) < 2) && (*(u16 *)(actor + 0x1E) & 8)) {
        return 0;
    }
    cursor = *(s8 *)(actor + 0x2E);
    if (cursor != *(s8 *)(actor + 0x2D)) {
        do {
            cursor--;
            if (cursor < 0) {
                cursor = actor[0x25] - 1;
            }
            entry = &entries[cursor];
            entry->lifetime -= D_800BE9E4;
            lifetime = entry->lifetime;
            if (lifetime < 0) {
                if (cursor != *(s8 *)(actor + 0x2D)) {
                    do {
                        *(s8 *)(actor + 0x2D) += 1;
                        if (actor[0x25] == *(s8 *)(actor + 0x2D)) {
                            *(s8 *)(actor + 0x2D) = 0;
                        }
                        *(s8 *)(actor + 0x2C) -= 1;
                    } while (cursor != *(s8 *)(actor + 0x2D));
                }
            } else if (lifetime < 0xA) {
                opacity = lifetime * 0x19;
                if (opacity < entry->alpha) {
                    entry->alpha = opacity;
                }
            }
        } while (cursor != *(s8 *)(actor + 0x2D));
    }
    if (*(s8 *)(actor + 0x2C) > 0) {
        *(Game1E9A30Position *)(actor + 0x54) = *(Game1E9A30Position *)((u8 (*)[sizeof(Game1E9A30Trail)])entries)[*(s8 *)(actor + 0x2D)];
    } else {
        *(f32 *)(actor + 0x54) = 0.0f;
        *(f32 *)(actor + 0x58) = 0.0f;
        *(f32 *)(actor + 0x5C) = 0.0f;
    }
    return 1;
}
extern f32 D_800AA848;
extern f32 D_800AA84C;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BC794 CURRENT (2670) */
s32 func_151BC794(u8 *arg0) {
    u8 *sp9C;
    s32 sp98;
    typedef struct { f32 x, y, z; } Point;
    Point delta;
    Point position;
    volatile f32 sp4C;
    f32 stepX;
    f32 stepY;
    f32 stepZ;
    f32 stepAngle;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa1;
    f32 var_ft4;
    s8 temp_v1;
    u8 *temp_a2;
    u8 *temp_t3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_a2 = (void *)(*(void **)((u8 *)arg0 + 0x98));
    sp98 = *(s32 *)((u8 *)arg0 + 0x94);
    temp_v0 = (void *)(*(void **)((u8 *)temp_a2 + 0));
    if ((*(s32 *)((u8 *)temp_v0 + 0) == 0) || (*(u8 *)((u8 *)temp_a2 + 4) != *(u8 *)((u8 *)temp_v0 + 0x3B))) {
        *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        return 1;
    }
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) *(f32 *)((u8 *)temp_v0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) *(f32 *)((u8 *)temp_v0 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) *(f32 *)((u8 *)temp_v0 + 0x1C);
    delta.x = *(f32 *)((u8 *)arg0 + 0x10) - *(f32 *)((u8 *)temp_a2 + 8);
    delta.y = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)temp_a2 + 0xC);
    sp9C = temp_a2;
    delta.z = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)temp_a2 + 0x10);
    temp_fv0 = func_15143E64(&delta);
    *(f32 *)((u8 *)sp9C + 0x14) = (f32) (*(f32 *)((u8 *)sp9C + 0x14) + (temp_fv0 * D_800AA848 * D_800BE9A4));
    temp_fv1 = *(f32 *)((u8 *)sp9C + 0x14);
    *(f32 *)((u8 *)sp9C + 0x1C) = (f32) (*(f32 *)((u8 *)sp9C + 0x1C) + (temp_fv0 * D_800AA84C));
    sp4C = temp_fv1;
    if (temp_fv1 > 1.0f) {
        temp_t3 = (void *)(sp9C + 8);
        temp_fv0_2 = 1.0f / sp4C;
        position = *(Point *)temp_t3;
        var_ft4 = *(f32 *)((u8 *)sp9C + 0x18) + D_800BE9A4;
        temp_fv1_2 = *(f32 *)((u8 *)sp9C + 0x20);
        var_fa1 = temp_fv1_2;
        temp_fs0 = -(var_ft4 * temp_fv0_2);
        stepX = delta.x * temp_fv0_2;
        stepY = delta.y * temp_fv0_2;
        stepZ = delta.z * temp_fv0_2;
        stepAngle = (*(f32 *)((u8 *)sp9C + 0x1C) - temp_fv1_2) * temp_fv0_2;
        do {
            temp_v0_2 = (void *)((*(s8 *)((u8 *)arg0 + 0x2E) * 0x14) + sp98);
            *(Point *)temp_v0_2 = position;
            *(s16 *)((u8 *)temp_v0_2 + 0xC) = 0xC;
            *(s8 *)((u8 *)temp_v0_2 + 0xE) = 0x64;
            *(f32 *)((u8 *)temp_v0_2 + 0x10) = var_fa1;
            if (var_fa1 > 16384.0f) {
                do {
                    *(f32 *)((u8 *)temp_v0_2 + 0x10) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x10) - 32768.0f);
                } while (*(f32 *)((u8 *)temp_v0_2 + 0x10) > 16384.0f);
            }
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(s8 *)((u8 *)arg0 + 0x2E) + 1);
            if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2E)) {
                *(s8 *)((u8 *)arg0 + 0x2E) = 0;
            }
            temp_v1 = *(s8 *)((u8 *)arg0 + 0x2D);
            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) + 1);
            if (temp_v1 == *(s8 *)((u8 *)arg0 + 0x2E)) {
                *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (temp_v1 + 1);
                if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2D)) {
                    *(s8 *)((u8 *)arg0 + 0x2D) = 0;
                }
                *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) - 1);
            }
            var_fa1 += stepAngle;
            position.x += stepX;
            position.y += stepY;
            var_ft4 += temp_fs0;
            position.z += stepZ;
            *(f32 *)((u8 *)sp9C + 0x14) = (f32) (*(f32 *)((u8 *)sp9C + 0x14) - 1.0f);
        } while (*(f32 *)((u8 *)sp9C + 0x14) > 1.0f);
        *(Point *)temp_t3 = position;
        *(f32 *)((u8 *)sp9C + 0x20) = var_fa1;
        *(f32 *)((u8 *)sp9C + 0x18) = var_ft4;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BC794 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC794.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BCA90.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BD21C CURRENT (830) */
void func_151BD21C(void *arg0, void *arg1, u8 arg2) {
    s32 temp_a3;
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_a3 = *(s32 *)((u8 *)temp_v0 + 0);
    if (arg2 == 0) {
        if ((temp_a3 == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            *(s8 *)((u8 *)arg0 + 0x30) = 0;
            *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        }
    } else if (arg2 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BD21C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD21C.s")
s32 func_151BD2BC(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x28);
    if (*(s32 *)((u8 *)temp_v0 + 0) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 0x2C) != *(u8 *)((u8 *)temp_v0 + 0x3B)) {
        return 0;
    }
    return 1;
}
typedef struct {
    s16 copyValue;
    u8 pad02[2];
    u8 id;
    u8 pad05[3];
    void *object;
    s8 active;
    u8 pad0D[3];
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
    s8 field28;
    u8 pad29;
    s16 field2A;
    s16 field2C;
    s16 field2E;
    u8 pad30[2];
    s8 field32;
    s8 field33;
    s8 field34;
    u8 pad35[3];
    f32 scale;
    s8 field3C;
    s8 field3D;
    u8 pad3E[2];
} Game1E9A30Spawn;

void *func_10022EC0(void *, const void *, u32);
void *func_15134DAC(void *, s32);
extern f32 D_800AA850;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BD2F8 CURRENT (120) */
void func_151BD2F8(void *arg0, s32 arg1, s32 arg2) {
    Game1E9A30Spawn spawn;
    void *result;

    if (arg0 != 0) {
        spawn.id = *(u8 *)((u8 *)arg0 + 0x3B);
        spawn.x1 = 31.0f;
        spawn.y1 = -34.0f;
        spawn.z1 = -117.0f;
        spawn.x2 = 35.0f;
        spawn.y2 = -24.0f;
        spawn.z2 = -182.0f;
        spawn.scale = D_800AA850;
        spawn.object = arg0;
        spawn.active = 1;
        spawn.field28 = 0;
        spawn.field2A = 0x32;
        spawn.field2C = 0x64;
        spawn.field2E = 0x12C;
        spawn.field32 = 4;
        spawn.field33 = 4;
        spawn.field34 = 3;
        spawn.field3C = 5;
        spawn.field3D = -1;
        spawn.copyValue = 0;
        result = func_15134DAC(&spawn.id, 2);
        if (result != 0) {
            func_10022EC0((u8 *)result + 0x80, &spawn.copyValue, 2);
        }
        spawn.x1 = -spawn.x1;
        spawn.x2 = -spawn.x2;
        result = func_15134DAC(&spawn.id, 2);
        if (result != 0) {
            func_10022EC0((u8 *)result + 0x80, &spawn.copyValue, 2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BD2F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD2F8.s")
s32 func_151BD42C(u8 *arg0) {
    *(s16 *)(arg0 + 0x80) = 0;
    return 1;
}
typedef struct Game1E9A30Particle {
    s32 flags, zero4;
    s16 texture, lifetime;
    s32 zeroC, zero10;
    u8 red, green, blue, alpha0, red1, green1, blue1;
    u8 alpha, maximum, kind;
    s16 duration, period, field22;
    f32 field24, width, height;
    f32 x, y, z;
    f32 originX, originY, originZ;
    f32 vx, vy, vz, rotation;
    s32 mode, unused5C;
    s8 field60, field61, field62, field63, field64, field65;
    u8 pad66[0xA];
} Game1E9A30Particle;

typedef struct Game1E9A30Owner {
    void *object;
    u8 id;
} Game1E9A30Owner;

void *func_15130374(s32, u8, s32, u8, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800AA854, D_800AA858, D_800AA85C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BD43C CURRENT (3202) */
void func_151BD43C(f32 *arg0, f32 *arg1, s32 arg2, s32 arg3, f32 arg4, void *arg5) {
    Game1E9A30Particle particle;
    f32 scale;
    void *spawned;
    Game1E9A30Owner owner;
    s32 flag0;
    s32 flag1;

    if ((*(u8 *)((u8 *)*(void **)((u8 *)arg5 + 0x1C) + 0x74) & 0xF) != 0xF) {
        particle.kind = 0x29;
        particle.texture = 0xE03;
        particle.flags = 0x200005;
        particle.zero4 = 0;
        particle.zeroC = 0;
        particle.zero10 = 0;
        particle.rotation = (func_150ADA68() * 251.0f + 44.0f) * D_800AA854;
        particle.duration = 0x14;
        particle.period = 0xC;
        flag0 = (func_150ADA20() & 1) ? 0x40 : 0;
        flag1 = (func_150ADA20() & 1) ? 0x80 : 0;
        particle.mode = flag1 | 7 | flag0 | 0xDE00;
        particle.field60 = 3;
        particle.field61 = 3;
        particle.field63 = -1;
        particle.field64 = -1;
        particle.field65 = 7;
        particle.field22 = 0x22;
        particle.red = 0xDD;
        particle.green = 0xD3;
        particle.blue = 0xCD;
        particle.alpha0 = 0xFF;
        particle.red1 = 0x57;
        particle.green1 = 0x55;
        particle.blue1 = 0x5A;
        scale = D_800AA858;
        particle.field24 = D_800AA85C;
        particle.alpha = func_150ADA20() % 156U + 0x64;
        particle.maximum = 0xFF;
        particle.lifetime = func_150ADA20() % 18U + 0x19;
        particle.width = particle.height = func_150ADA68() * 53.0f + 49.0f;
        particle.vx = (arg1[0] - arg0[0]) * *(f32 *)((u8 *)arg5 + 0x74);
        particle.vy = (arg1[1] - arg0[1]) * *(f32 *)((u8 *)arg5 + 0x74);
        particle.vz = (arg1[2] - arg0[2]) * *(f32 *)((u8 *)arg5 + 0x74);
        particle.x = arg0[0] - *(f32 *)((u8 *)*(void **)((u8 *)arg5 + 0x1C) + 0x14);
        particle.y = arg0[1] - *(f32 *)((u8 *)*(void **)((u8 *)arg5 + 0x1C) + 0x18);
        particle.z = arg0[2] - *(f32 *)((u8 *)*(void **)((u8 *)arg5 + 0x1C) + 0x1C);
        particle.x += particle.vx * arg4;
        particle.y += particle.vy * arg4;
        particle.z += particle.vz * arg4;
        owner.object = *(void **)((u8 *)arg5 + 0x1C);
        particle.field62 = 0x13;
        owner.id = *(u8 *)((u8 *)*(void **)((u8 *)arg5 + 0x1C) + 0x3B);
        particle.originX = *(f32 *)((u8 *)*(void **)((u8 *)arg5 + 0x1C) + 0x14);
        particle.originY = *(f32 *)((u8 *)*(void **)((u8 *)arg5 + 0x1C) + 0x18);
        particle.originZ = *(f32 *)((u8 *)*(void **)((u8 *)arg5 + 0x1C) + 0x1C);
        spawned = func_15130374((s32)&particle, 1, 0x10,
                                *(u8 *)((u8 *)arg5 + 0xC), *(u8 *)((u8 *)arg5 + 1));
        if (spawned != NULL) {
            func_10022EC0((u8 *)spawned + 0xA8, &scale, 4);
            func_10022EC0((u8 *)spawned + 0xB0, &owner, 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BD43C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD43C.s")
extern f32 D_800AA860;
extern f32 D_800AA864;
extern s32 D_800BE9E4;

f32 func_151BD750(void *arg0) {
    s16 temp_v0;
    f32 result;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x80);
    result = (((f32) temp_v0 * 2) * D_800AA860) + D_800AA864;
    *(s16 *)((u8 *)arg0 + 0x80) = (s16) (temp_v0 + D_800BE9E4);
    return result;
}
/* Call context: func_1513170C: unique active project prototype */
s32 func_1513170C(u8 *, s32);

void func_151BD79C(u8 *arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0xB0);
    if ((*(s32 *)((u8 *)temp_v0 + 0) != 0) && (*(u8 *)((u8 *)temp_v0 + 4) != 0xFF)) {
        *(f32 *)((u8 *)arg0 + 0x4C) = (f32) *(f32 *)((u8 *)temp_v0 + 0x14);
        *(f32 *)((u8 *)arg0 + 0x50) = (f32) *(f32 *)((u8 *)temp_v0 + 0x18);
        *(f32 *)((u8 *)arg0 + 0x54) = (f32) *(f32 *)((u8 *)temp_v0 + 0x1C);
    }
    func_1513170C(arg0, arg1);
}

void func_151BD7F4(void *arg0) {
    struct {
        void *sp18;
        u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0(&sp, 0x3B);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD828.s")
void func_15145EA4(s32 *, s32 *, s32, s32);
extern Game1E9A30Position D_800AA778, D_800AA784, D_800AA790, D_800AA79C;
extern u16 **D_800BE728;
extern u8 D_800CC2D0[];

typedef struct { u8 pad0[0x48]; f32 width, height; u8 pad50[8]; u8 flags; } Game1E9A30TrailEffect;
typedef struct { u8 pad0[4]; f32 scale; } Game1E9A30SparkEffect;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BDD8C CURRENT (1840) */
void func_151BDD8C(void *arg0) {
    s32 i;
    u8 *owner;
    Game1E9A30Position starts[2];
    Game1E9A30Position ends[2];
    s32 player;
    Game1E9A30Position *inputs[4];
    Game1E9A30Position *outputs[4];
    u8 *payload;
    u8 *entry;
    u8 *hiddenEntry;
    u8 *scaleEntry;
    u8 *object;
    u8 *secondObject;
    Game1E9A30TrailEffect *hiddenEffect;
    Game1E9A30TrailEffect *trailEffect;
    Game1E9A30SparkEffect *sparkEffect;

    owner = *(u8 **)((u8 *)arg0 + 0x28);
    payload = (u8 *)arg0 + 0x28;
    if ((*(s32 *)owner == 0) || (payload[4] != owner[0x3B])) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        return;
    }
    if ((*(s32 *)(owner + 0x1D4) != 0) && ((owner[0x74] & 0xF) != 0xF)) {
        inputs[0] = &D_800AA778;
        inputs[1] = &D_800AA784;
        inputs[2] = &D_800AA790;
        inputs[3] = &D_800AA79C;
        outputs[0] = &starts[0];
        outputs[1] = &starts[1];
        outputs[2] = &ends[0];
        outputs[3] = &ends[1];
        func_15145EA4((s32 *)inputs, (s32 *)outputs, *(s32 *)(owner + 0x1D4) + 0x40, 4);
        i = 0;
        do {
            entry = payload + i * 4;
            object = *(u8 **)(entry + 8);
            if (object != NULL) {
                object[0x168] |= 1;
                *(Game1E9A30Position *)(object + 0x34) = starts[i];
                *(Game1E9A30Position *)(object + 0x40) = ends[i];
            }
            object = *(u8 **)(entry + 0x10);
            if (object != NULL) {
                *(s32 *)(object + 0x58) |= 2;
                *(s32 *)(object + 0x58) &= ~4;
                *(Game1E9A30Position *)(object + 0x34) = starts[i];
                *(Game1E9A30Position *)(object + 0x40) = ends[i];
            }
            i = (i + 1) & 0xFF;
        } while (i < 2);
    } else {
        i = 0;
        do {
            hiddenEntry = payload + i * 4;
            object = *(u8 **)(hiddenEntry + 8);
            if (object != NULL) {
                hiddenEffect = (Game1E9A30TrailEffect *)(object + 0x110);
                hiddenEffect->flags &= ~1;
            }
            object = *(u8 **)(hiddenEntry + 0x10);
            if (object != NULL) {
                *(s32 *)(object + 0x58) &= ~2;
            }
            i = (i + 1) & 0xFF;
        } while (i < 2);
    }
    player = (s32)(owner - D_800CC2D0) / 812;
    if (player < 4) {
        i = 0;
        do {
            scaleEntry = payload + i * 4;
            object = *(u8 **)(scaleEntry + 8);
            if (object != NULL) {
                trailEffect = (Game1E9A30TrailEffect *)(object + 0x110);
                if (*D_800BE728[(u8)player] & 0x8000) {
                    trailEffect->width = 6.0f;
                    trailEffect->height = 21.0f;
                } else {
                    trailEffect->width = 3.0f;
                    trailEffect->height = 8.0f;
                }
            }
            secondObject = *(u8 **)(scaleEntry + 0x10);
            if (secondObject != NULL) {
                sparkEffect = (Game1E9A30SparkEffect *)(secondObject + 0x170);
                if (*D_800BE728[(u8)player] & 0x8000) {
                    sparkEffect->scale = 1.5f;
                } else {
                    sparkEffect->scale = 1.0f;
                }
            }
            i = (i + 1) & 0xFF;
        } while (i < 2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BDD8C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BDD8C.s")
void func_15169850(s32, u8, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BE0AC CURRENT (260) */
void func_151BE0AC(void *arg0, void *arg1, u8 arg2) {
    u8 *temp_a2;

    temp_a2 = (u8 *)arg0 + 0x28;
    if (arg2 == 0x3B) {
        if ((*(s32 *)temp_a2 == *(s32 *)arg1) ||
            (*(u8 *)(temp_a2 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C((s32)arg0);
        }
    } else {
        func_15169850((s32)arg1, arg2, (s32)temp_a2,
                      (s32)(temp_a2 + 4), (s32)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BE0AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BE0AC.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BE138 CURRENT (421) */
void func_151BE138(u8 *arg0) {
    void *var_v0;
    s32 temp_a0;

    if (*(volatile s32 *)((u8 *)arg0 + 0x30) != 0) {
        func_1516972C(*(s32 *)((u8 *)arg0 + 0x30));
    }
    var_v0 = (void *)((u8 *)arg0 + 0x28);
    temp_a0 = *(s32 *)((u8 *)var_v0 + 0xC);
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
    temp_a0 = *(s32 *)((u8 *)var_v0 + 0x10);
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
    temp_a0 = *(s32 *)((u8 *)var_v0 + 0x14);
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BE138 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BE138.s")
void func_151BE138(u8 *arg0);

void func_151BE1B8(void *arg0) {
    func_151BE138(arg0);
    func_1514933C(arg0);
}
void func_151BE1E4(void *arg0) {
    func_151BE138(arg0);
    func_15149368(arg0);
}
