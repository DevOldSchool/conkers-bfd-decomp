#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D9F10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_owner_point_lifecycle.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151ACB60
 * - func_151ACBD4
 * - func_151AD174
 * - func_151AD92C
 * - func_151AE0E4
 * - func_151AE2BC
 * - func_151AE3A8
 * - func_151AE590
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1D9F10Record {
    u8 pad0[0x10];
    s32 field10;
    s32 field14;
    u8 pad18[4];
    void *field1C;
    u8 field20;
    u8 pad21[3];
    s32 field24;
    f32 field28;
} Game1D9F10Record;

s32 func_151ACB38(void *, s8 *);
extern u8 D_800CC2D0;

Game1D9F10Record *func_151ACA60(void *arg0, f32 arg1, s32 arg2) {
    Game1D9F10Record *record;

    if (arg0 == 0) {
        return 0;
    }
    record = func_15167A68(0x30, 0, arg2 + 0x30, 1, 0xFF, 1);
    if (record == 0) {
        return 0;
    }
    if (func_151ACB38(arg0, (s8 *)record + 0x18) == 0) {
        func_1516979C((u8 *)record);
        return 0;
    }
    *(void **)((u8 *)record + 0x1C) = arg0;
    *(u8 *)((u8 *)record + 0x20) = *(u8 *)((u8 *)arg0 + 0x3B);
    *(s32 *)((u8 *)record + 0x24) = ((s32)arg0 - (s32)&D_800CC2D0) / 0x32C;
    *(f32 *)((u8 *)record + 0x28) = arg1;
    *(s32 *)((u8 *)record + 0x10) = 1;
    *(s32 *)((u8 *)record + 0x14) = 0;
    return record;
}
s32 func_151ACB38(void *arg0, s8 *arg1) {
    u8 result;

    result = 0;
    if (*(u8 *)((u8 *)arg0 + 0x3B) == 1) {
        *(u8 *)arg1 = 1;
        result = 1;
    }
    return result;
}
void func_151AE3A8(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ACB60 CURRENT (200) */
void func_151ACB60(void *arg0) {
    s32 temp_v0 = *(s32 *)((u8 *)(*(void **)((u8 *)(*(void **)((u8 *)arg0 + 0x1C)) + 0x31C)) + 0x9C);

    if (temp_v0 != 0) {
        func_151AE3A8((s32)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ACB60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151ACB60.s")
void func_151ACB94(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x1C, arg0 + 0x20, arg0);
}
typedef struct Game1D9F10LinePoint {
    f32 x, y, z;
    f32 vx, vy, vz;
} Game1D9F10LinePoint;

typedef struct Game1D9F10LineVertex {
    s16 ob[3];
    s16 flag;
    s16 tc[2];
    u8 color[4];
} Game1D9F10LineVertex;

typedef struct Game1D9F10LineTexture {
    u8 pad0[6];
    u16 width;
    u16 height;
    u8 padA[2];
} Game1D9F10LineTexture;

typedef struct Game1D9F10Line {
    u8 pad0[0x14];
    f32 x;
    f32 top;
    f32 z;
    u8 pad20[4];
    f32 bottom;
    u8 pad28[4];
    f32 length;
    u8 pad30[4];
    f32 inverseLength;
    Game1D9F10LinePoint *points;
    f32 step;
    u16 texture;
    u8 count;
    u8 pad43;
    s32 field44;
    Game1D9F10LineVertex *vertices;
    f32 field4C;
    u8 pad50[2];
    s16 field52;
} Game1D9F10Line;

void *func_10022EC0(void *, const void *, u32);
void *func_10003C40(s32, s32, s32, s32);
extern Game1D9F10LineTexture D_80090B60[];
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ACBD4 CURRENT (15046) */
Game1D9F10Line *func_151ACBD4(void *arg0, s32 arg1) {
    Game1D9F10Line *line;
    s32 i;
    s32 x;
    s32 top;
    s32 z;
    s32 bottom;
    s32 shift;
    s32 r, g, b;
    Game1D9F10LineTexture *texture;
    s32 quarter;
    s32 buffer;
    s32 row;
    s32 t;

    line = func_15167A68(D_800BE9F0 == 0x2C ? 0x4E : 0x2F, 0, arg1 + 0x58, 1, 0xFF, 1);
    if (line == NULL) {
        return NULL;
    }
    func_10022EC0((u8 *)line + 0x10, arg0, 0x24);
    line->inverseLength = 1.0f / line->length;
    line->field44 = 0;
    line->field52 = 0;
    line->points = func_10003C40(0x1E0, 1, 0, 0);
    x = line->x;
    top = line->top;
    z = line->z;
    bottom = line->bottom;
    line->count = 20;
    for (i = 0; i < 20; i++) {
        line->points[i].x = x;
        line->points[i].y = (top - bottom) * i / 19 + bottom;
        line->points[i].z = z;
        line->points[i].vx = 0.0f;
        line->points[i].vy = 0.0f;
        line->points[i].vz = 0.0f;
    }
    line->step = (f32)(top - bottom) / 19;
    line->vertices = func_10003C40(0xA00, 1, 2, 0);
    if (D_800BE9F0 == 0xB) {
        line->texture = 0x37;
        shift = 4;
    } else {
        line->texture = 0x36;
        shift = 5;
    }
    r = 0xFF;
    g = 0xFF;
    if (D_800BE9F0 == 0x39) {
        r = 0x58;
        g = 0x4B;
        b = 0x2C;
    } else {
        b = 0xFF;
    }
    texture = &D_80090B60[line->texture];
    quarter = texture->width >> 2;
    for (buffer = 0; buffer < 2; buffer++) {
        t = 0x100;
        for (row = 0; row < 20; row++) {
            line->vertices[buffer * 80 + row * 4 + 0].flag = 0;
            line->vertices[buffer * 80 + row * 4 + 0].tc[0] = (0 * quarter + 0x100) << 5;
            line->vertices[buffer * 80 + row * 4 + 0].tc[1] = t << shift;
            line->vertices[buffer * 80 + row * 4 + 0].color[0] = r;
            line->vertices[buffer * 80 + row * 4 + 0].color[1] = g;
            line->vertices[buffer * 80 + row * 4 + 0].color[2] = b;
            line->vertices[buffer * 80 + row * 4 + 0].color[3] = 0xFF;
            line->vertices[buffer * 80 + row * 4 + 1].flag = 0;
            line->vertices[buffer * 80 + row * 4 + 1].tc[0] = (1 * quarter + 0x100) << 5;
            line->vertices[buffer * 80 + row * 4 + 1].tc[1] = t << shift;
            line->vertices[buffer * 80 + row * 4 + 1].color[0] = r;
            line->vertices[buffer * 80 + row * 4 + 1].color[1] = g;
            line->vertices[buffer * 80 + row * 4 + 1].color[2] = b;
            line->vertices[buffer * 80 + row * 4 + 1].color[3] = 0xFF;
            line->vertices[buffer * 80 + row * 4 + 2].flag = 0;
            line->vertices[buffer * 80 + row * 4 + 2].tc[0] = (2 * quarter + 0x100) << 5;
            line->vertices[buffer * 80 + row * 4 + 2].tc[1] = t << shift;
            line->vertices[buffer * 80 + row * 4 + 2].color[0] = r;
            line->vertices[buffer * 80 + row * 4 + 2].color[1] = g;
            line->vertices[buffer * 80 + row * 4 + 2].color[2] = b;
            line->vertices[buffer * 80 + row * 4 + 2].color[3] = 0xFF;
            line->vertices[buffer * 80 + row * 4 + 3].flag = 0;
            line->vertices[buffer * 80 + row * 4 + 3].tc[0] = (3 * quarter + 0x100) << 5;
            line->vertices[buffer * 80 + row * 4 + 3].tc[1] = t << shift;
            line->vertices[buffer * 80 + row * 4 + 3].color[0] = r;
            line->vertices[buffer * 80 + row * 4 + 3].color[1] = g;
            line->vertices[buffer * 80 + row * 4 + 3].color[2] = b;
            line->vertices[buffer * 80 + row * 4 + 3].color[3] = 0xFF;
            t += texture->height - 1;
        }
    }
    line->field4C = 0.0f;
    return line;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ACBD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151ACBD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AD174.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AD92C.s")
typedef struct Game1D9F10MotionKey {
    f32 x, y, z;
    u8 other[12];
} Game1D9F10MotionKey;
typedef struct Game1D9F10MotionModel {
    u8 pad00[0x38];
    Game1D9F10MotionKey *keys;
    f32 spacing;
    u8 pad40[2];
    u8 count;
} Game1D9F10MotionModel;
typedef struct {
    u8 pad0[0x98];
    u8 active_type;
    u8 pad99[3];
    Game1D9F10MotionModel *model;
    f32 progress;
    u8 padA4[0xA];
    u8 frame;
} Game1D9F10NestedState;

typedef struct {
    u8 pad0[0x14];
    f32 x, y, z;
    u8 pad20[0x2FC];
    Game1D9F10NestedState *nested;
} Game1D9F10Actor;

typedef struct {
    u8 pad0[0x1B];
    u8 type;
} Game1D9F10Event;

s32 func_151ACB38(void *, s8 *);
void func_151AE0E4(void *, u8);
void func_151AE264(void *);

void func_151AE06C(Game1D9F10Actor *arg0, Game1D9F10Event *arg1) {
    s8 matched;
    u8 type;
    s32 active_type;

    if (func_151ACB38(arg0, &matched) != 0) {
        type = arg1->type;
        active_type = arg0->nested->active_type;
        if (active_type == 0) {
            func_151AE0E4(arg0, type);
            return;
        }
        if ((type - active_type) == 0) {
            return;
        }
        func_151AE264(arg0);
        func_151AE0E4(arg0, type);
    }
}
void *func_151AE590(u8);
void func_151AE2BC(void *, void *, f32, f32, f32);
extern f32 D_800A9290;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE0E4 CURRENT (1249) */
void func_151AE0E4(void *arg0, u8 arg1) {
    u8 *record;
    u32 point_index;
    f32 point[3];
    f32 dx;
    f32 dy;
    f32 dz;

    record = func_151AE590(arg1);
    if (record == 0) {
        for (;;) {
        }
    }
    if (*(s16 *)(record + 0x52) != 0 ||
        *(u8 *)((u8 *)arg0 + 0x1CA) == 0 ||
        *(u8 *)((u8 *)arg0 + 0x104) != 0) {
        return;
    }
    func_151AE2BC(*(u8 **)((u8 *)arg0 + 0x31C) + 0xA0, record,
                   *(f32 *)((u8 *)arg0 + 0x14),
                   *(f32 *)((u8 *)arg0 + 0x18),
                   *(f32 *)((u8 *)arg0 + 0x1C));
    point_index = (u32)(s32)((f32)(s32)((u32)record[0x42] - (u32)(s32)(140.0f / *(f32 *)(record + 0x3C)) - 1U) *
                        *(f32 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xA0));
    point_index *= 0x18U;
    point[0] = *(f32 *)((u32)*(u8 **)(record + 0x38) + point_index);
    point[1] = *(f32 *)((u32)*(u8 **)(record + 0x38) + point_index + 4U);
    point[2] = *(f32 *)((u32)*(u8 **)(record + 0x38) + point_index + 8U);
    dx = point[0] - *(f32 *)((u8 *)arg0 + 0x14);
    dy = point[1] - *(f32 *)((u8 *)arg0 + 0x18);
    dz = point[2] - *(f32 *)((u8 *)arg0 + 0x1C);
    if (D_800A9290 < ((dz * dz) + ((dx * dx) + (dy * dy)))) {
        return;
    }
    (*(u8 **)((u8 *)arg0 + 0x31C))[0x98] = arg1;
    *(s8 *)((u8 *)arg0 + 0x8A) = 0x12;
    *(u8 **)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x9C) = record;
    *(void **)(record + 0x44) = arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE0E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE0E4.s")
extern f32 D_800A9294;

void func_151AE264(void *arg0) {
    f32 temp_fv0;
    void *temp_v0;

    temp_v0 = *(void **)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x9C);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x3C) * D_800A9294;
    *(f32 *)((u8 *)temp_v0 + 0x4C) = temp_fv0;
    *(s8 *)((u8 *)temp_v0 + 0x50) = *(u16 *)((u8 *)arg0 + 0x76) >> 8;
    *(u8 *)((u8 *)temp_v0 + 0x51) = *(u8 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xAE);
    *(s16 *)((u8 *)temp_v0 + 0x52) = 0x14;
    *(s32 *)((u8 *)temp_v0 + 0x44) = 0;
    *(s8 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x98) = 0;
    *(void **)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x9C) = 0;
}
typedef struct {
    f32 field_0;
    f32 field_4;
    u8 pad_8[0x10];
} Game1D9F10CurvePoint;

typedef struct {
    u8 pad_0[0x38];
    Game1D9F10CurvePoint *points;
    u8 pad_3C[6];
    u8 count;
} Game1D9F10Curve;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE2BC CURRENT (2778) */
void func_151AE2BC(s32 arg0, void *arg1, s32 arg2, f32 arg3) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv0;
    s32 temp_a2;
    s32 upper;
    s32 var_v1;
    u8 temp_v0;
    u8 *temp_a0;
    u8 *var_a0;

    temp_v0 = *(u8 *)((u8 *)arg1 + 0x42);
    var_v1 = 0;
    temp_a2 = temp_v0 - 1;
    upper = temp_v0 - 2;
    if (temp_a2 > 0) {
        var_a0 = *(u8 **)((u8 *)arg1 + 0x38);
loop_2:
        if (!(arg3 <= *(f32 *)(var_a0 + 4))) {
            var_v1 += 1;
            var_a0 += 0x18;
            if (var_v1 != temp_a2) {
                goto loop_2;
            }
        }
    }
    if (var_v1 >= upper) {
        *(f32 *)arg0 = 1.0f;
        return;
    }
    if (var_v1 == 0) {
        *(f32 *)arg0 = 0.0f;
        return;
    }
    temp_a0 = *(u8 **)((u8 *)arg1 + 0x38) + (var_v1 * 0x18);
    temp_fv1 = *(f32 *)(temp_a0 - 0x14);
    temp_fv0 = *(f32 *)(temp_a0 + 4) - temp_fv1;
    if (temp_fv0 != 0.0f) {
        var_fv0 = (arg3 - temp_fv1) / temp_fv0;
    } else {
        var_fv0 = 0.0f;
    }
    *(f32 *)arg0 = ((f32)(var_v1 - 1) / (f32)(temp_v0 - 3)) + (var_fv0 / (f32)temp_a2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE2BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE2BC.s")
s32 func_15143E08(u16 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE3A8 CURRENT (5407) */
void func_151AE3A8(s32 arg0) {
    f32 oldZ;
    f32 oldY;
    f32 interpolatedY;
    Game1D9F10Actor *actor;
    Game1D9F10MotionModel *model;
    u8 angle;
    f32 cosine;
    f32 first[3];
    f32 next[3];
    f32 sine;
    f32 fraction;
    f32 progress;
    f32 oldX;
    f32 radius;
    s32 reserve;
    s32 frame;
    Game1D9F10NestedState *state;

    actor = ((Game1D9F10Record *)arg0)->field1C;
    model = actor->nested->model;
    angle = func_15143E08((u16 *)actor) - 0x80;
    cosine = func_151423D8((angle - 0x40) & 0xFF);
    sine = func_151423D8(angle);
    state = actor->nested;
    oldY = actor->y;
    oldX = actor->x;
    radius = ((Game1D9F10Record *)arg0)->field28;
    progress = state->progress;
    oldZ = actor->z;
    reserve = (s32)(140.0f / model->spacing);
    frame = (s32)((f32)(model->count - reserve - 1) * progress);
    state->frame = frame;
    first[0] = model->keys[frame].x;
    fraction = (f32)(model->count - reserve - 1) * progress - (f32)frame;
    first[1] = model->keys[frame].y;
    first[2] = model->keys[frame].z;
    next[0] = model->keys[frame + 1].x;
    next[1] = model->keys[frame + 1].y;
    next[2] = model->keys[frame + 1].z;
    interpolatedY = (next[1] - first[1]) * fraction + first[1];
    actor->x = (((next[0] - first[0]) * fraction + first[0] + radius * cosine) - oldX) + oldX;
    actor->y = (interpolatedY - oldY) + oldY;
    actor->z = (((next[2] - first[2]) * fraction + first[2] + radius * sine) - oldZ) + oldZ;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE3A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE3A8.s")
extern s32 D_800A9270[];
extern void *D_800DCE50[][104];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE590 CURRENT (465) */
void *func_151AE590(u8 arg0) {
    u8 var_v0;
    u8 var_v1;
    void *var_a0;
    void *temp_a2;

    for (var_v0 = 0; var_v0 < 2; var_v0++) {
        for (var_v1 = 0; var_v1 < 2; var_v1++) {
            var_a0 = D_800DCE50[var_v1][D_800A9270[var_v0]];
            while (var_a0 != 0) {
                temp_a2 = *(void **)((u8 *)var_a0 + 8);
                if (arg0 != *(u8 *)((u8 *)var_a0 + 0x10)) {
                    var_a0 = temp_a2;
                } else {
                    return var_a0;
                }
            }
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE590 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE590.s")
void func_151AE640(void *arg0, void *arg1, u8 arg2) {
    if (arg2 == 0) {
        s32 id = *(s32 *)arg1;

        if (id == *(s32 *)((u8 *)arg0 + 0x44)) {
            *(s32 *)((u8 *)arg0 + 0x44) = 0;
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)((u8 *)arg0 + 0x44)) {
            *(s32 *)((u8 *)arg0 + 0x44) = *(s32 *)((u8 *)arg1 + 4);
        } else if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)((u8 *)arg0 + 0x44)) {
            *(s32 *)((u8 *)arg0 + 0x44) = *(s32 *)arg1;
        }
    }
}
