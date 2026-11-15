#include "types.h"
#include "game_functions.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>

/*
 * Reviewed source unit: src/game/game_1FEA80.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D15D0
 * - func_151D197C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 *owner;
    u8 pad04[8];
    f32 limit;
    f32 widthBase;
    f32 widthScale;
    f32 alphaScale;
    f32 ownerScale;
} Game1FEA80TrailState;

typedef struct {
    f32 x, y, z, length;
    u8 pad10[4];
    u8 alpha;
    u8 pad15[7];
    f32 width;
    u8 pad20[8];
} Game1FEA80TrailPoint;

typedef struct Game1FEA80Vec2 {
    f32 x, z;
} Game1FEA80Vec2;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_15144528(f32, f32, f32);
extern f32 D_800AB0A8, D_800AB0AC;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D15D0 CURRENT (1558) */
s32 func_151D15D0(u8 *arg0) {
    Game1FEA80TrailState *state;
    Game1FEA80TrailPoint *points;
    u8 *ownerBase;
    Game1FEA80TrailPoint *middle;
    Game1FEA80TrailPoint *current;
    f32 length;
    register f32 x;
    f32 z;
    f32 previousInverse;
    Game1FEA80Vec2 nextDirection;
    Game1FEA80Vec2 previousDirection;
    s16 index, previous;
    f32 currentInverse;
    Game1FEA80Vec2 normal;
    volatile f32 magnitude;
    Game1FEA80TrailPoint *older;
    register u8 *owner;
    f32 inverse;

    state = *(Game1FEA80TrailState **)(arg0 + 0x98);
    points = *(Game1FEA80TrailPoint **)(arg0 + 0x94);
    ownerBase = state->owner;
    if (D_800BE9E4 > 0) {
        owner = ownerBase + 0x28;
        *(Vec3f *)(arg0 + 0x10) = *(Vec3f *)(owner + 0x18);
        *(u16 *)(arg0 + 0x1E) |= 4;
        current = points + *(s8 *)(arg0 + 0x2E);
        *(Vec3f *)&current->x = *(Vec3f *)(arg0 + 0x10);
        current->length = *(f32 *)(owner + 0x30);
        x = *(f32 *)(owner + 0x24);
        z = *(f32 *)(owner + 0x2C);
        length = sqrtf(x * x + z * z);
        if (length == 0.0f) *(f32 *)current->pad10 = 1.0f;
        else *(f32 *)current->pad10 = 1.0f / length;
        current->width = 100.0f;
        current->alpha = 255;
        *(f32 *)((u8 *)current + 0x18) = *(f32 *)state->pad04;
        *(f32 *)state->pad04 += current->length * D_800AB0A8;
        *(f32 *)state->pad04 = func_15144528(*(f32 *)state->pad04, 8192.0f, 0.0f);
        if (length != 0.0f) {
            inverse = *(f32 *)current->pad10;
            *(f32 *)current->pad20 = -*(f32 *)(owner + 0x2C) * inverse;
            *(f32 *)(current->pad20 + 4) = *(f32 *)(owner + 0x24) * inverse;
        } else {
            *(f32 *)current->pad20 = 0;
            *(f32 *)(current->pad20 + 4) = 0;
        }
        (*(s8 *)(arg0 + 0x2E))++;
        if (arg0[0x25] == *(s8 *)(arg0 + 0x2E)) *(s8 *)(arg0 + 0x2E) = 0;
        (*(s8 *)(arg0 + 0x2C))++;
        if (*(s8 *)(arg0 + 0x2D) == *(s8 *)(arg0 + 0x2E)) {
            (*(s8 *)(arg0 + 0x2D))++;
            if (arg0[0x25] == *(s8 *)(arg0 + 0x2D)) *(s8 *)(arg0 + 0x2D) = 0;
            (*(s8 *)(arg0 + 0x2C))--;
        }
        if (*(s8 *)(arg0 + 0x2C) >= 3) {
            index = *(s8 *)(arg0 + 0x2E) - 1;
            if (index < 0) index = arg0[0x25] - 1;
            index--;
            if (index < 0) index = arg0[0x25] - 1;
            previous = index - 1;
            if (previous < 0) previous = arg0[0x25] - 1;
            if (current->length != 0.0f) {
                middle = points + index;
                if (middle->length != 0.0f) {
                    older = points + previous;
                    x = middle->x;
                    z = middle->z;
                    currentInverse = *(f32 *)current->pad10;
                    previousInverse = *(f32 *)middle->pad10;
                    nextDirection.x = (current->x - x) * currentInverse;
                    nextDirection.z = (current->z - z) * currentInverse;
                    previousDirection.x = (older->x - x) * previousInverse;
                    previousDirection.z = (older->z - z) * previousInverse;
                    normal.x = -(nextDirection.z - previousDirection.z);
                    normal.z = nextDirection.x - previousDirection.x;
                    inverse = normal.x * normal.x + normal.z * normal.z;
                    magnitude = inverse;
                    if (D_800AB0AC < inverse) {
                        inverse = 1.0f / sqrtf(inverse);
                        normal.x *= inverse;
                        normal.z *= inverse;
                        *(Game1FEA80Vec2 *)middle->pad20 = normal;
                        return 1;
                    } else {
                        *(f32 *)middle->pad20 = 0;
                        *(f32 *)(middle->pad20 + 4) = 0;
                    }
                }
            }
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D15D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FEA80/func_151D15D0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D197C CURRENT (3782) */
s32 func_151D197C(u8 *arg0) {
    f32 savedTotal;
    f32 savedInverse;
    f32 total;
    f32 inverse;
    f32 remaining;
    f32 widthFactor;
    f32 alphaFactor;
    f32 length;
    f32 ratio;
    f32 sourceX, sourceY, sourceZ;
    f32 x, y, z;
    s32 index;
    s32 previous;
    Game1FEA80TrailState *state;
    Game1FEA80TrailPoint *points;
    Game1FEA80TrailPoint *point;
    Game1FEA80TrailPoint *next;

    state = *(Game1FEA80TrailState **)(arg0 + 0x98);
    points = *(Game1FEA80TrailPoint **)(arg0 + 0x94);
    if (state->owner != 0) {
        state->ownerScale = *(f32 *)(*(u8 **)(state->owner + 0x28) + 0x14C);
    }
    if (*(s8 *)(arg0 + 0x2C) >= 2) {
        total = 0.0f;
        index = *(s8 *)(arg0 + 0x2E) - 1;
        if (index < 0) {
            index = arg0[0x25] - 1;
        }
        if (index != *(s8 *)(arg0 + 0x2D)) {
            do {
                previous = index;
                index--;
                if (index < 0) {
                    index = arg0[0x25] - 1;
                }
                point = &points[previous];
                length = point->length;
                total += length;
                if (state->limit < total) {
                    if (length != 0.0f) {
                        ratio = (total - state->limit) / length;
                        sourceX = point->x;
                        sourceY = point->y;
                        sourceZ = point->z;
                        next = &points[index];
                        x = next->x;
                        y = next->y;
                        z = next->z;
                        next->x = x - (x - sourceX) * ratio;
                        next->y = y - (y - sourceY) * ratio;
                        next->z = z - (z - sourceZ) * ratio;
                        point->length *= 1.0f - ratio;
                    }
                    if (index != *(s8 *)(arg0 + 0x2D)) {
                        do {
                            (*(s8 *)(arg0 + 0x2D))++;
                            if (arg0[0x25] == *(s8 *)(arg0 + 0x2D)) {
                                *(s8 *)(arg0 + 0x2D) = 0;
                            }
                            (*(s8 *)(arg0 + 0x2C))--;
                        } while (index != *(s8 *)(arg0 + 0x2D));
                    }
                    total = state->limit;
                }
            } while (index != *(s8 *)(arg0 + 0x2D));
        }
        if (total != 0.0f) {
            inverse = 1.0f / total;
        } else {
            inverse = 0.0f;
        }
        savedInverse = inverse;
        savedTotal = total;
    }
    inverse = savedInverse;
    total = savedTotal;
    if (*(s8 *)(arg0 + 0x2C) >= 2) {
        index = *(s8 *)(arg0 + 0x2E);
        remaining = total;
        widthFactor = state->widthScale * state->ownerScale * inverse;
        alphaFactor = state->alphaScale * inverse;
        do {
            index--;
            if (index < 0) {
                index = arg0[0x25] - 1;
            }
            point = &points[index];
            point->width = state->widthBase * state->ownerScale +
                           remaining * widthFactor;
            point->alpha = (u32)(remaining * alphaFactor);
            remaining -= point->length;
        } while (index != *(s8 *)(arg0 + 0x2D));
    }
    if ((*(u16 *)(arg0 + 0x1E) & 1) && (*(u16 *)(arg0 + 0x1E) & 8)) {
        *((s8 *)state + 8) = *(s16 *)(arg0 + 0x1C) * 6;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D197C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FEA80/func_151D197C.s")
typedef struct Game1FEA80RibbonPoint {
    Vec3f position;
    u8 pad0C[8];
    u8 alpha;
    u8 pad15[3];
    f32 texture;
    f32 width;
    f32 directionX;
    f32 directionZ;
} Game1FEA80RibbonPoint;

typedef struct Game1FEA80RibbonVertex {
    s16 x, y, z;
    s16 flag;
    s16 s, t;
    u8 r, g, b, a;
} Game1FEA80RibbonVertex;

typedef struct Game1FEA80RibbonState {
    u8 pad0[8];
    u8 alpha;
} Game1FEA80RibbonState;

void *func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);
s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
Gfx *func_15142B7C(Gfx *, s32, s32);
Gfx *func_1513F4E4(Gfx *, u8, u8 *);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
extern u8 D_80091430[];
extern s32 D_800A4AC8[][2];
extern s32 D_800D2C9C;

Gfx *func_151D1C98(u8 *arg0, Gfx *arg1, s16 arg2) {
    Game1FEA80RibbonState *state;
    Vec3f next;
    Vec3f first;
    Game1FEA80RibbonPoint *points;
    s32 index;
    s32 previous;
    u8 flag;
    u8 nextAlpha;
    f32 firstX;
    f32 firstZ;
    f32 nextX;
    f32 nextZ;
    f32 firstTexture;
    f32 nextTexture;
    u16 firstAlpha;
    Game1FEA80RibbonVertex *vtx;

    if (*(s8 *)(arg0 + 0x2C) < 2) {
        return arg1;
    }
    state = *(Game1FEA80RibbonState **)(arg0 + 0x98);
    points = *(Game1FEA80RibbonPoint **)(arg0 + 0x94);
    func_151D5D60(arg0 + 0x84, arg2, (arg0[0x25] * 2 + 10) * sizeof(Game1FEA80RibbonVertex), (void **)&vtx, NULL);
    if (vtx == NULL) {
        return arg1;
    }
    flag = 1;
    arg1 = (Gfx *)func_15142E24((s32)arg1, (s32)D_80091430, 0, 0, 0, 0, 0xBC, 0, 0, &flag, 3);
    arg1 = func_15142B7C(arg1, 0x220005, 0x1D0600);
    arg1 = func_1513F4E4(arg1, 0x4C, &flag);
    arg1 = func_15142FBC(arg1, D_800D2C9C | 0x80000 | 0x2000 | 0xC00 | 0x80 | 0x20, D_800A4AC8[1][0] | D_800A4AC8[1][1], &flag);
    previous = *(s8 *)(arg0 + 0x2E) - 1;
    if (previous < 0) {
        previous = arg0[0x25] - 1;
    }
    index = previous - 1;
    if (index < 0) {
        index = arg0[0x25] - 1;
    }
    first = points[previous].position;
    firstX = points[previous].width * points[previous].directionX;
    firstZ = points[previous].width * points[previous].directionZ;
    firstAlpha = (points[previous].alpha * state->alpha) >> 8;
    firstTexture = points[previous].texture;
    next = points[index].position;
    nextX = points[index].width * points[index].directionX;
    nextZ = points[index].width * points[index].directionZ;
    nextAlpha = (points[index].alpha * state->alpha) >> 8;
    nextTexture = points[index].texture;
    vtx->x = first.x + firstX;
    vtx->y = first.y;
    vtx->z = first.z + firstZ;
    vtx->a = firstAlpha;
    vtx->t = firstTexture;
    vtx->s = 0x7FF;
    vtx->flag = 0;
    vtx++;
    vtx->x = first.x - firstX;
    vtx->y = first.y;
    vtx->z = first.z - firstZ;
    vtx->a = firstAlpha;
    vtx->t = firstTexture;
    vtx->s = 0;
    vtx->flag = 0;
    vtx++;
    do {
        vtx->x = next.x + nextX;
        vtx->y = next.y;
        vtx->z = next.z + nextZ;
        vtx->a = nextAlpha;
        vtx->t = nextTexture;
        vtx->s = 0x7FF;
        vtx->flag = 0;
        vtx++;
        vtx->x = next.x - nextX;
        vtx->y = next.y;
        vtx->z = next.z - nextZ;
        vtx->a = nextAlpha;
        vtx->t = nextTexture;
        vtx->s = 0;
        vtx->flag = 0;
        vtx++;
        gSPVertex(arg1++, vtx - 4, 4, 0);
        gSP2Triangles(arg1++, 0, 1, 2, 0, 1, 3, 2, 0);
        if (firstTexture < nextTexture) {
            func_10022EC0(vtx, vtx - 2, 0x20);
            vtx[-2].t -= 0x2000;
            vtx++;
            vtx[-2].t -= 0x2000;
            vtx++;
        }
        previous = index;
        index--;
        if (index < 0) {
            index = arg0[0x25] - 1;
        }
        if (previous != *(s8 *)(arg0 + 0x2D)) {
            next = points[index].position;
            nextX = points[index].width * points[index].directionX;
            firstTexture = points[previous].texture;
            nextZ = points[index].width * points[index].directionZ;
            nextTexture = points[index].texture;
            nextAlpha = (points[index].alpha * state->alpha) >> 8;
        }
    } while (previous != *(s8 *)(arg0 + 0x2D));
    return arg1;
}
typedef struct Game1FEA80Leaf {
    u8 pad0[0x30];
    s32 field_30;
} Game1FEA80Leaf;

typedef struct Game1FEA80Object {
    u8 pad0[0x98];
    Game1FEA80Leaf **field_98;
} Game1FEA80Object;

void func_151D223C(Game1FEA80Object *arg0) {
    register Game1FEA80Leaf **link = arg0->field_98;
    register Game1FEA80Leaf *leaf = *link;

    if (leaf) {
        leaf->field_30 = 0;
    }
}
void func_151D2258(Game1FEA80Object *arg0) {
    func_151D223C(arg0);
    func_151478F4(arg0);
}
void func_151D2284(Game1FEA80Object *arg0) {
    func_151D223C(arg0);
    func_15147928(arg0);
}
