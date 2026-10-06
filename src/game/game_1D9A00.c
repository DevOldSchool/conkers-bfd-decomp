#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D9A00.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AC61C
 * - func_151AC810
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u8 func_151D8E20(void);
void func_151DBCBC(s32, f32, u8, s32, f32 *, s32, s32);

s32 func_151AC550(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4,
                  s32 arg5) {
    void *object;
    struct Record {
        f32 first;
        u8 pad4[4];
        f32 third;
        u8 padC[8];
    } *records;
    f32 values[3];

    object = *(void **)(arg0 + 0x98);
    records = *(struct Record **)(arg0 + 0x94);
    values[0] = records[*(s8 *)(arg0 + 0x2D)].first;
    values[1] = arg4;
    values[2] = records[*(s8 *)(arg0 + 0x2D)].third;
    func_151DBCBC(func_151D8E20() & 0xFF,
                  *(f32 *)object * 7.0f,
                  *(u8 *)((u8 *)object + 0x1B), arg5, values,
                  arg0[0xC], arg0[1]);
    *(s8 *)((u8 *)object + 0x20) = 4;
    return 1;
}
typedef struct Game1D9A00EmitterConfig {
    u8 pad0[4];
    s16 angle;
    u16 angleRange;
    f32 speed;
    f32 speedRange;
    s16 life;
    u16 lifeRange;
    u8 alpha;
    u8 alphaRange;
    u8 pad16[2];
    f32 size;
    f32 sizeRange;
    f32 rate;
    f32 rateRange;
    f32 probability;
} Game1D9A00EmitterConfig;

typedef struct Game1D9A00EmitterOwner {
    s32 first;
    s32 second;
    u8 kind;
} Game1D9A00EmitterOwner;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32,
                   s32, f32, f32, s32, s32, s32, s32, s32, s32);
extern s8 D_800A9023[];
extern Game1D9A00EmitterConfig D_800A9180[];

/* D_8008AA00[12] points here; its existing callback declaration fixes the slots. */
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AC61C CURRENT (209) */
s32 func_151AC61C(s32 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, f32 arg6, f32 arg7, s32 arg8, s32 arg9,
                   f32 arg10, s32 arg11, f32 arg12, Game1D9A00EmitterOwner *arg13,
                   s32 arg14) {
    f32 position[3];
    f32 direction[3];
    u32 random0;
    f32 randomSize;
    u32 random1;
    f32 randomRate;
    Game1D9A00EmitterConfig *config;

    config = &D_800A9180[D_800A9023[arg11 * 5]];
    position[0] = arg2;
    position[1] = arg3;
    position[2] = arg4;
    random0 = func_150ADA20();
    func_15143794((s16)arg8,
        (s16)((random0 % (u32)(config->angleRange + 1)) + config->angle),
        func_150ADA68() * config->speedRange + config->speed, direction);
    randomRate = func_150ADA68();
    random1 = func_150ADA20();
    random0 = func_150ADA20();
    randomSize = func_150ADA68();
    func_151D9014(position, direction, arg13->kind,
        randomRate * config->rateRange + config->rate,
        (random1 % (u32)(config->lifeRange + 1)) + config->life,
        (random0 % (u32)(config->alphaRange + 1)) + config->alpha,
        randomSize * config->sizeRange + config->size,
        func_150ADA68() < config->probability,
        1.0f, 1.0f, 1, arg13->first, 1, 0, (u8)arg14, arg13->second);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AC61C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9A00/func_151AC61C.s")

typedef struct Game1D9A00Vertex {
    s16 x, y, z, flag;
    u8 other[8];
} Game1D9A00Vertex;

typedef struct Game1D9A00Quad {
    u8 pad0[0x2C];
    f32 scale;
    f32 height;
    f32 x, y, z;
    u8 pad40[0xC];
    f32 scaleMultiplier;
    f32 heightMultiplier;
    u8 pad54[0x6C];
    u8 templateData[0x40];
    u8 *buffers[1];
} Game1D9A00Quad;

void *func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);
extern f32 D_800DD1D8[];
extern f32 D_800DD1E8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AC810 CURRENT (796) */
void *func_151AC810(Game1D9A00Quad *arg0, s32 arg1) {
    Game1D9A00Vertex *vertices;
    void *result;
    f32 scale;
    f32 height;
    f32 offsetZ;
    f32 offsetX;
    u8 fresh;

    func_151D5D60(arg0->buffers, (s16)arg1, 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            func_10022EC0(arg0->buffers[(s16)arg1], arg0->templateData, 0x40);
            func_10022EC0(arg0->buffers[(s16)arg1] + 0x40, arg0->templateData, 0x40);
        }
    } else {
        return 0;
    }
    scale = arg0->scale * arg0->scaleMultiplier;
    height = arg0->height * arg0->heightMultiplier;
    offsetZ = D_800DD1D8[(s16)arg1] * scale;
    offsetX = D_800DD1E8[(s16)arg1] * scale;
    vertices[0].flag = 0;
    vertices[1].flag = 0;
    vertices[2].flag = 0;
    vertices[3].flag = 0;
    vertices[0].x = vertices[3].x = (s32)(arg0->x + offsetX);
    vertices[0].y = vertices[1].y = (s32)arg0->y;
    vertices[0].z = vertices[3].z = (s32)(arg0->z - offsetZ);
    vertices[1].x = vertices[2].x = (s32)(arg0->x - offsetX);
    vertices[2].y = vertices[3].y = (s32)(arg0->y + height);
    vertices[1].z = vertices[2].z = (s32)(arg0->z + offsetZ);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AC810 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9A00/func_151AC810.s")
extern f32 D_800BE9A4;

s32 func_151AC9EC(void *arg0) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
    return 1;
}
s32 func_151ACA20(void *arg0) {
    s16 temp_v1;
    s16 var_v0;

    var_v0 = 0xFF;
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v1 < 0x10) {
        var_v0 = temp_v1 * 0x10;
    }
    if (var_v0 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
        *(u8 *)((u8 *)arg0 + 0x5C) = (u8) var_v0;
    }
    return 1;
}
