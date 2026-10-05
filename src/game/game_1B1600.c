#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B1600.c
 * Boundary evidence: docs/evidence/game_raw_clipping_resource_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15184150
 * - func_15184368
 * - func_15184DF0
 * - func_15184FA4
 * - func_15185DD4
 * - func_15185F24
 * - func_1518652C
 * - func_15186794
 * - func_151872B0
 * - func_151873E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game184150Matrix {
    f32 values[16];
} Game184150Matrix;

typedef struct Game184DF0Actor {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0x12C];
    f32 scaleXZ;
    f32 scaleY;
    u8 pad154[0x80];
    Game184150Matrix *matrices;
    u8 pad1D8[0x154];
} Game184DF0Actor;

extern Game184DF0Actor D_800CC2D0[];
extern u8 D_800C3E90;
extern u8 *D_800D1C90[];
s32 func_1502DB20(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15184150 CURRENT (1794) */
void func_15184150(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 kind;
    Game184DF0Actor *actor;
    Game184150Matrix *matrix;
    u8 *model;
    s32 count;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    f32 radius;

    actor = &D_800CC2D0[arg0];
    kind = actor->pad0[4];
    *arg3 = 0.0f;
    *arg2 = 0.0f;
    *arg1 = 0.0f;
    if (actor->matrices == 0 || D_800C3E90 != 0) {
        return;
    }
    count = func_1502DB20(kind);
    for (i = 0; i < count * 0x40; i += 0x40) {
        matrix = (Game184150Matrix *) ((u8 *) actor->matrices + i);
        x = matrix->values[12] - actor->x;
        y = matrix->values[13] - actor->y;
        z = matrix->values[14] - actor->z;
        if (x < 0.0f) {
            x = -x;
        }
        if (*arg1 < x) {
            *arg1 = x;
        }
        if (y < 0.0f) {
            y = -y;
        }
        if (*arg2 < y) {
            *arg2 = y;
        }
        if (z < 0.0f) {
            z = -z;
        }
        if (*arg3 < z) {
            *arg3 = z;
        }
    }
    if (*arg1 == 0.0f || *arg2 == 0.0f || *arg3 == 0.0f) {
        radius = actor->scaleXZ * (f32) *(s16 *)(D_800D1C90[actor->pad0[4]] + 0x1A);
        *arg3 = radius;
        *arg1 = radius;
        model = D_800D1C90[actor->pad0[4]];
        *arg2 = actor->scaleY * (f32) (*(s16 *)(model + 0x1E) + *(s16 *)(model + 0x1C));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15184150 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184150.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184368.s")

typedef struct Game184DF0Camera {
    u8 pad0[0x2F8];
    f32 x;
    f32 y;
    f32 z;
    u8 pad304[0x69C];
} Game184DF0Camera;

s32 func_150AD9A0(s32, s32, s32);
void func_15184150(s32, f32 *, f32 *, f32 *);
extern Game184DF0Camera *D_800DBFF0;
extern f32 D_800A7378;
extern f32 D_800D3688;
extern f32 D_800D368C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15184DF0 CURRENT (1458) */
s32 func_15184DF0(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    Game184DF0Actor *actor;
    Game184DF0Camera *camera;
    s32 distance;
    s32 dx;
    s32 dy;
    s32 dz;
    f32 scale;

    actor = &D_800CC2D0[arg0];
    camera = &D_800DBFF0[arg1];
    dx = (s32)(actor->x - camera->x);
    dy = (s32)(actor->y - camera->y);
    dz = (s32)(actor->z - camera->z);
    distance = func_150AD9A0(dx, dy, dz);
    if (distance >= 0x7D1) {
        D_800D3688 = 0.0f;
        D_800D368C = D_800D3688;
        return 0;
    }
    func_15184150(arg0, arg2, arg3, arg4);
    scale = D_800A7378;
    *arg2 *= scale;
    *arg3 *= scale;
    *arg4 *= scale;
    if ((*arg2 == 0.0f) || (*arg3 == 0.0f) || (*arg4 == 0.0f)) {
        D_800D3688 = 0.0f;
        D_800D368C = D_800D3688;
        return 0;
    }
    return distance;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15184DF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184DF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184FA4.s")
void *func_15185454(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (*(f32 *)(arg0 + 8) - *(f32 *)(arg0 + 4)) /
        ((*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) - (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)));
    *(f32 *)arg2 = (*(f32 *)arg1 - *(f32 *)arg0) * ratio + *(f32 *)arg0;
    *(f32 *)(arg2 + 4) = *(f32 *)(arg2 + 8) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_15185554(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 8) < *(f32 *)((u8 *)arg0 + 4);
}
void *func_1518557C(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (*(f32 *)(arg0 + 8) + *(f32 *)arg0) /
        ((*(f32 *)(arg0 + 8) - *(f32 *)(arg1 + 8)) + (*(f32 *)arg0 - *(f32 *)arg1));
    *(f32 *)arg2 = (*(f32 *)arg1 - *(f32 *)arg0) * ratio + *(f32 *)arg0;
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = -*(f32 *)arg2;
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_1518567C(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 0) < -*(f32 *)((u8 *)arg0 + 8);
}
void *func_151856A8(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (*(f32 *)(arg0 + 8) + *(f32 *)(arg0 + 4)) /
        ((*(f32 *)(arg0 + 8) - *(f32 *)(arg1 + 8)) + (*(f32 *)(arg0 + 4) - *(f32 *)(arg1 + 4)));
    *(f32 *)arg2 = (*(f32 *)arg1 - *(f32 *)arg0) * ratio + *(f32 *)arg0;
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = -*(f32 *)(arg2 + 4);
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_151857B0(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 4) < -*(f32 *)((u8 *)arg0 + 8);
}
void *func_151857DC(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (*(f32 *)(arg0 + 8) - *(f32 *)arg0) /
        ((*(f32 *)arg1 - *(f32 *)arg0) - (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)));
    *(f32 *)arg2 = (*(f32 *)arg1 - *(f32 *)arg0) * ratio + *(f32 *)arg0;
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = *(f32 *)arg2;
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_151858D4(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 8) < *(f32 *)((u8 *)arg0 + 0);
}
extern f32 D_800D3688;

void *func_151858FC(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (D_800D3688 - *(f32 *)(arg0 + 8)) / (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * ratio + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = D_800D3688;
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
extern f32 D_800D3688;

s32 func_151859FC(void *arg0) {
    return D_800D3688 < *(f32 *)((u8 *)arg0 + 8);
}
extern f32 D_800D368C;

void *func_15185A28(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (D_800D368C - *(f32 *)(arg0 + 8)) / (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * ratio + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = D_800D368C;
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
extern f32 D_800D368C;

s32 func_15185B28(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 8) < D_800D368C;
}
void *func_15185B54(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = *(f32 *)arg0 / (*(f32 *)arg0 - *(f32 *)arg1);
    *(f32 *)arg2 = 0.0f;
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)) * ratio + *(f32 *)(arg0 + 8);
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_15185C44(f32 *arg0) {
    return *arg0 <= 0.0f;
}
void *func_15185C6C(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = *(f32 *)(arg0 + 4) / (*(f32 *)(arg0 + 4) - *(f32 *)(arg1 + 4));
    *(f32 *)(arg2 + 4) = 0.0f;
    *(f32 *)arg2 = (*(f32 *)arg1 - *(f32 *)arg0) * ratio + *(f32 *)arg0;
    *(f32 *)(arg2 + 8) = (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)) * ratio + *(f32 *)(arg0 + 8);
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_15185D5C(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 4) <= 0.0f;
}
s32 func_15185D84(f32 *arg0) {
    return *arg0 > 0.0f;
}
s32 func_15185DAC(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 4) > 0.0f;
}
typedef struct {
    s32 words[5];
} Game1B1600Record;

extern Game1B1600Record *(*D_8008D498[])(Game1B1600Record *, Game1B1600Record *, Game1B1600Record *);
extern s32 (*D_8008D4C0[])(Game1B1600Record *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185DD4 CURRENT (724) */
Game1B1600Record *func_15185DD4(Game1B1600Record *arg0, s32 arg1, s32 arg2,
                                  Game1B1600Record *arg3) {
    s32 (*predicate)(Game1B1600Record *);
    Game1B1600Record *(*combine)(Game1B1600Record *, Game1B1600Record *, Game1B1600Record *);
    Game1B1600Record *previous;
    Game1B1600Record *current;
    Game1B1600Record *out;
    s32 index;

    out = arg3;
    previous = arg0 + arg1 - 1;
    combine = D_8008D498[arg2];
    predicate = D_8008D4C0[arg2];
    current = arg0;
    index = 0;
    if (arg1 > 0) {
        do {
            if (predicate(current) != 0) {
                if (predicate(previous) != 0) {
                    out++;
                    out[-1] = *current;
                } else {
                    Game1B1600Record *merged = combine(previous, current, out);
                    out = merged;
                    *out++ = *current;
                }
            } else if (predicate(previous) != 0) {
                out = combine(previous, current, out);
            }
            index++;
            previous = current;
            current++;
        } while (index != arg1);
    }
    return out;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185DD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185DD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185F24.s")
void func_1510F800(s32);
void func_100226F0(void *, s32);
s32 func_1510F720(s32, s32, s32, void **);
s32 func_150A5B90(u32 *, s32, s32, s32);
extern u8 *D_800D3668;
extern u32 *D_800D3694;
extern s8 D_800DE041;
extern s32 D_800D3690, D_800DBE3C;
extern s32 D_800DF0E8, D_800DF0EC, D_800DF0F0, D_800DF0F4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518652C CURRENT (5197) */
s32 func_1518652C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct {
        u32 bits[187];
        s32 count;
        void *items[16];
    } work;
    volatile u32 savedMaximum;
    u32 maximum;
    void **cursor;
    u8 *data;
    u32 index;
    u32 *word;
    u8 code;
    u8 filter;
    s32 end;

    savedMaximum = 0;
    func_1510F800(0);
    work.count = func_1510F720(arg0, arg1, arg2, work.items);
    maximum = savedMaximum;
    if (work.count != 0) {
        savedMaximum = maximum;
        func_100226F0(work.bits, 0x2EC);
        maximum = savedMaximum;
        if (work.count != 0) {
            cursor = work.items + work.count;
            filter = (u8)D_800DE041;
            do {
                data = (u8 *)cursor[-1];
                index = 0;
                cursor--;
                data += 0xE;
                if (filter != 0) {
                    code = *data;
                    if (code != 0) {
                        do {
                            if (code & 0x80) {
                                index = ((code << 8) | data[1]) & 0x7FFF;
                                data += 2;
                            } else {
                                index += code;
                                data++;
                            }
                            if (index < 0x1760U) {
                                word = &work.bits[index >> 5];
                                if (D_800D3668[index] == 1) {
                                    *word |= 1U << (index & 0x1F);
                                    if (maximum < index) {
                                        maximum = index;
                                    }
                                }
                            }
                            code = *data;
                        } while (code != 0);
                    }
                } else {
                    code = *data;
                    if (code != 0) {
                        do {
                            if (code & 0x80) {
                                index = ((code << 8) | data[1]) & 0x7FFF;
                                data += 2;
                            } else {
                                index += code;
                                data++;
                            }
                            if (index < 0x1760U) {
                                word = &work.bits[index >> 5];
                                *word |= 1U << (index & 0x1F);
                                if (maximum < index) {
                                    maximum = index;
                                }
                            }
                            code = *data;
                        } while (code != 0);
                    }
                }
            } while (cursor != work.items);
        }
        D_800D3690 = D_800DBE3C;
        D_800D3694 = &work.bits[maximum >> 5] + 1;
        D_800DF0E8 = (s32)((u32)arg0 - (u32)arg2);
        D_800DF0EC = (s32)((u32)arg0 + (u32)arg2);
        D_800DF0F0 = (s32)((u32)arg1 - (u32)arg2);
        D_800DF0F4 = (s32)((u32)arg1 + (u32)arg2);
        end = func_150A5B90(work.bits, arg3, arg4, arg5);
        return (s32)((u32)end - (u32)arg3) / 20;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518652C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_1518652C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15186794.s")
extern s32 D_800DE01C;
extern s32 D_800DE020;
extern s32 D_800DE024;
extern s32 D_800DE030;
extern s32 D_800DE034;
extern s32 D_800DE038;
extern f32 D_800DE03C;
extern s8 D_800DE040;
extern s8 D_800DE041;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151872B0 CURRENT (1250) */
void func_151872B0(s32 arg0) {
    D_800DE01C = 0x258;
    D_800DE020 = 0xB4;
    D_800DE024 = 0x5A;
    D_800DE030 = 0x3F8;
    D_800DE034 = 0;
    D_800DE038 = 1;
    D_800DE03C = 1.0f;
    D_800DE040 = 1;
    D_800DE041 = 1;
    switch (arg0) {                                 /* irregular */
    case 33:
        D_800DE01C = 0x12C0;
        D_800DE020 = 0x12BF;
        D_800DE024 = 0x12BE;
        D_800DE030 = 0x3F2;
        D_800DE034 = 1;
        D_800DE038 = 4;
        D_800DE040 = 0;
        return;
    case 34:
        D_800DE01C = 0x960;
        D_800DE020 = 0x95F;
        D_800DE024 = 0x95E;
        D_800DE038 = 4;
        D_800DE040 = 0;
        return;
    case 20:
        D_800DE041 = 0;
        return;
    case 41:
        D_800DE01C = 0x4B0;
        D_800DE020 = 0x258;
        D_800DE024 = 0x12C;
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151872B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151872B0.s")
/* Call context: func_150A44F0: unique active project prototype */
void func_150A44F0(s32, void *, s32);

s32 func_150A5E44(void *, s32, s32, s32);
void func_1510F800(s32);
extern s32 D_800D3690;
extern u8 D_800D37E0[];
extern s32 D_800DBE3C;
extern s32 D_800DBEF0;
extern void *D_800DBEF4;
extern s32 D_800DF0E4;
extern s32 D_800DF0E8;
extern s32 D_800DF0EC;
extern s32 D_800DF0F0;
extern s32 D_800DF0F4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151873E4 CURRENT (1154) */
s32 func_151873E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s16 temp_a0_2;
    s16 temp_a0_3;
    s32 var_a3;
    s32 var_s0;
    u16 temp_a0;
    u16 temp_a1;
    s32 var_v1;
    void *var_t0;
    void *entry;

    if (D_800DBEF0 == 0) {
        return arg6;
    }
    func_1510F800(2);
    arg3 += arg6 * 0x14;
    D_800DF0E8 = arg0 - arg2;
    D_800DF0EC = arg0 + arg2;
    D_800DF0F0 = arg1 - arg2;
    D_800DF0F4 = arg1 + arg2;
    var_s0 = 0;
    var_a3 = 0;
    if (D_800DBEF0 > 0) {
        var_t0 = D_800DBEF4;
        do {
            entry = var_t0;
            if ((*(u8 *)((u8 *)entry + 0x6E) == 0) && !(*(u8 *)((u8 *)entry + 0x4F) & 0x60)) {
                temp_a0 = *(u16 *)((u8 *)entry + 0x52);
                temp_a1 = *(u16 *)((u8 *)entry + 0x50);
                var_v1 = temp_a0 < temp_a1 ? temp_a1 : temp_a0;
                temp_a0_2 = *(s16 *)((u8 *)entry + 0x10);
                if ((D_800DF0EC >= (temp_a0_2 - var_v1)) && ((temp_a0_2 + var_v1) >= D_800DF0E8)) {
                    temp_a0_3 = *(s16 *)((u8 *)entry + 0x14);
                    if ((D_800DF0F4 >= (temp_a0_3 - var_v1)) && ((temp_a0_3 + var_v1) >= D_800DF0F0)) {
                        ((s16 *)D_800D37E0)[var_s0] = var_a3;
                        var_s0 += 1;
                    }
                }
            }
            var_a3 += 1;
            var_t0 = (u8 *)var_t0 + 0xA0;
        } while (var_a3 < D_800DBEF0);
    }
    if (var_s0 != 0) {
        func_150A44F0(var_s0, D_800D37E0, 0);
        D_800D3690 = D_800DBE3C;
        D_800DF0E4 = var_s0;
        arg6 = arg6 + ((s32) (func_150A5E44(D_800D37E0, arg3, arg4, arg5) - arg3) / 20);
    }
    return arg6;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151873E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151873E4.s")
