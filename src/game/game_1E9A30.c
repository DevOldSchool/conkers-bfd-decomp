#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E9A30.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BC5A4
 * - func_151BC64C
 * - func_151BC794
 * - func_151BCA90
 * - func_151BD21C
 * - func_151BD2F8
 * - func_151BD43C
 * - func_151BD750
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
void func_1516972C(s32, ...);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BC5A4 CURRENT (1577) */
void func_151BC5A4(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0) {
        if ((*(s32 *)((u8 *)arg0 + 0x40) == *(s32 *)arg1) || (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x44))) {
            func_1516972C((s32)arg0, arg1, temp_t6);
        }
    } else {
        temp_v0 = (u8 *)arg0 + 0x40;
        if (temp_t6 == 0x2D) {
            temp_a0 = *(s32 *)((u8 *)arg0 + 0x40);
            temp_v1 = *(s32 *)arg1;
            if (temp_v1 == temp_a0) {
                *(s32 *)((u8 *)arg0 + 0x40) = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
                *(s32 *)((u8 *)arg0 + 0x40) = temp_v1;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BC64C CURRENT (10) */
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
        *(Game1E9A30Position *)(actor + 0x54) = *(Game1E9A30Position *)&entries[*(s8 *)(actor + 0x2D)];
    } else {
        *(f32 *)(actor + 0x54) = 0.0f;
        *(f32 *)(actor + 0x58) = 0.0f;
        *(f32 *)(actor + 0x5C) = 0.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BC64C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC64C.s")
f32 func_15143E64(f32 *, void *, void *);           /* extern */
extern f32 D_800AA848;
extern f32 D_800AA84C;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BC794 CURRENT (5435) */
s32 func_151BC794(u8 *arg0) {
    u8 *sp9C;
    s32 sp98;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp4C;
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
    temp_v0 = (void *)(*(void **)((u8 *)temp_a2 + 0));
    if ((*(s32 *)((u8 *)temp_v0 + 0) == 0) || (*(u8 *)((u8 *)temp_a2 + 4) != *(u8 *)((u8 *)temp_v0 + 0x3B))) {
        *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        return 1;
    }
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) *(f32 *)((u8 *)temp_v0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) *(f32 *)((u8 *)temp_v0 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) *(f32 *)((u8 *)temp_v0 + 0x1C);
    sp88 = *(f32 *)((u8 *)arg0 + 0x10) - *(f32 *)((u8 *)temp_a2 + 8);
    sp8C = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)temp_a2 + 0xC);
    sp98 = *(s32 *)((u8 *)arg0 + 0x94);
    sp9C = temp_a2;
    sp90 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)temp_a2 + 0x10);
    temp_fv0 = func_15143E64(&sp88, arg0, temp_a2);
    *(f32 *)((u8 *)sp9C + 0x14) = (f32) (*(f32 *)((u8 *)sp9C + 0x14) + (temp_fv0 * D_800AA848 * D_800BE9A4));
    temp_fv1 = *(f32 *)((u8 *)sp9C + 0x14);
    *(f32 *)((u8 *)sp9C + 0x1C) = (f32) (*(f32 *)((u8 *)sp9C + 0x1C) + (temp_fv0 * D_800AA84C));
    sp4C = temp_fv1;
    if (temp_fv1 > 1.0f) {
        temp_t3 = (void *)(sp9C + 8);
        temp_fv0_2 = 1.0f / sp4C;
        *(f32 *)((u8 *)&sp6C + 0) = *(f32 *)((u8 *)sp9C + 8);
        *(s32 *)((u8 *)&sp6C + 4) = (s32) *(s32 *)((u8 *)temp_t3 + 4);
        var_ft4 = *(f32 *)((u8 *)sp9C + 0x18) + D_800BE9A4;
        *(s32 *)((u8 *)&sp6C + 8) = (s32) *(s32 *)((u8 *)temp_t3 + 8);
        temp_fv1_2 = *(f32 *)((u8 *)sp9C + 0x20);
        var_fa1 = temp_fv1_2;
        temp_fs0 = -(var_ft4 * temp_fv0_2);
        do {
            temp_v0_2 = (void *)((*(s8 *)((u8 *)arg0 + 0x2E) * 0x14) + sp98);
            *(f32 *)((u8 *)temp_v0_2 + 0) = (f32) *(f32 *)((u8 *)&sp6C + 0);
            *(s32 *)((u8 *)temp_v0_2 + 4) = (s32) *(s32 *)((u8 *)&sp6C + 4);
            *(s16 *)((u8 *)temp_v0_2 + 0xC) = 0xC;
            *(s8 *)((u8 *)temp_v0_2 + 0xE) = 0x64;
            *(f32 *)((u8 *)temp_v0_2 + 0x10) = var_fa1;
            *(s32 *)((u8 *)temp_v0_2 + 8) = (s32) *(s32 *)((u8 *)&sp6C + 8);
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
            var_fa1 += (*(f32 *)((u8 *)sp9C + 0x1C) - temp_fv1_2) * temp_fv0_2;
            sp6C += sp88 * temp_fv0_2;
            sp70 += sp8C * temp_fv0_2;
            var_ft4 += temp_fs0;
            sp74 += sp90 * temp_fv0_2;
            *(f32 *)((u8 *)sp9C + 0x14) = (f32) (*(f32 *)((u8 *)sp9C + 0x14) - 1.0f);
        } while (*(f32 *)((u8 *)sp9C + 0x14) > 1.0f);
        *(f32 *)((u8 *)sp9C + 8) = (f32) *(f32 *)((u8 *)&sp6C + 0);
        *(s32 *)((u8 *)temp_t3 + 4) = (s32) *(s32 *)((u8 *)&sp6C + 4);
        *(s32 *)((u8 *)temp_t3 + 8) = (s32) *(s32 *)((u8 *)&sp6C + 8);
        *(f32 *)((u8 *)sp9C + 0x20) = var_fa1;
        *(f32 *)((u8 *)sp9C + 0x18) = var_ft4;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BC794 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC794.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BCA90.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BD21C CURRENT (1285) */
void func_151BD21C(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_a3 = *(s32 *)((u8 *)temp_v0 + 0);
    if (temp_t6 == 0) {
        if ((temp_a3 == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            *(s8 *)((u8 *)arg0 + 0x30) = 0;
            *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        }
    } else if (temp_t6 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32) *(u8 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if ((s32) *(u8 *)((u8 *)arg1 + 4) == temp_a3) {
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
s32 func_15134DAC();
extern f32 D_800AA850;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BD2F8 CURRENT (215) */
void func_151BD2F8(void *arg0, s32 arg1, s32 arg2) {
    Game1E9A30Spawn spawn;
    s32 result;

    if (arg0 != 0) {
        spawn.active = 1;
        spawn.id = *(u8 *)((u8 *)arg0 + 0x3B);
        spawn.x1 = 31.0f;
        spawn.y1 = -34.0f;
        spawn.z1 = -117.0f;
        spawn.x2 = 35.0f;
        spawn.y2 = -24.0f;
        spawn.z2 = -182.0f;
        spawn.scale = D_800AA850;
        spawn.object = arg0;
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
        result = func_15134DAC(&spawn.id, 2, arg0);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD43C.s")
extern f32 D_800AA860;
extern f32 D_800AA864;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BD750 CURRENT (705) */
f32 func_151BD750(void *arg0) {
    union {
        u32 bits;
        f32 value;
    } scale;
    s16 temp_v0;
    f32 result;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x80);
    scale.bits = 0x40000000;
    result = (((f32) temp_v0 * scale.value) * D_800AA860) + D_800AA864;
    *(s16 *)((u8 *)arg0 + 0x80) = (s16) (temp_v0 + D_800BE9E4);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BD750 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD750.s")
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
void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_151BD7F4(void *arg0) {
    struct {
        void *sp18;
        volatile u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32 *)&sp, 0x3B, (s32)arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD828.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BDD8C.s")
void func_1516972C(s32, ...);
void func_15169850(s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BE0AC CURRENT (1334) */
void func_151BE0AC(void *arg0, void *arg1, s32 arg2) {
    u8 *temp_a2;

    temp_a2 = (u8 *)arg0 + 0x28;
    if ((u8)arg2 == 0x3B) {
        if ((*(s32 *)temp_a2 == *(s32 *)arg1) ||
            (*(u8 *)(temp_a2 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C((s32)arg0);
        }
    } else {
        func_15169850((s32)arg1, (s32)(u8)arg2, (s32)temp_a2,
                      (s32)(temp_a2 + 4), (s32)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BE0AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BE0AC.s")
void func_1516972C(s32, ...);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BE138 CURRENT (921) */
void func_151BE138(s32 arg0) {
    void *sp18;
    void *var_v0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;

    if (*(s32 *)((u8 *)arg0 + 0x30) != 0) {
        func_1516972C(*(s32 *)((u8 *)arg0 + 0x30), arg0);
    }
    var_v0 = (void *)((u8 *)arg0 + 0x28);
    temp_a0 = *(s32 *)((u8 *)var_v0 + 0xC);
    if (temp_a0 != 0) {
        sp18 = var_v0;
        func_1516972C(temp_a0, arg0);
        var_v0 = sp18;
    }
    temp_a0_2 = *(s32 *)((u8 *)var_v0 + 0x10);
    if (temp_a0_2 != 0) {
        sp18 = var_v0;
        func_1516972C(temp_a0_2);
        var_v0 = sp18;
    }
    temp_a0_3 = *(s32 *)((u8 *)var_v0 + 0x14);
    if (temp_a0_3 != 0) {
        func_1516972C(temp_a0_3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BE138 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BE138.s")
void func_151BE138(s32 arg0);
void func_1514933C(s32 arg0);
void func_15149368(s32 arg0);

void func_151BE1B8(s32 arg0) {
    func_151BE138(arg0);
    func_1514933C(arg0);
}
void func_151BE1E4(s32 arg0) {
    func_151BE138(arg0);
    func_15149368(arg0);
}
