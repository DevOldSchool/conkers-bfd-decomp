#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D92F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151ABE40
 * - func_151AC078
 * - func_151AC408
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1D92F0Position {
    f32 x, y, z;
} Game1D92F0Position;

typedef struct Game1D92F0Surface {
    u8 pad0[4];
    f32 normal[3];
    u8 pad10[0xC];
    u8 flags;
} Game1D92F0Surface;

typedef struct Game1D92F0Selection {
    s8 first, firstStyle, second, secondStyle, third;
} Game1D92F0Selection;

typedef struct Game1D92F0Range {
    f32 radius;
    s16 base;
    u16 range;
} Game1D92F0Range;

typedef struct Game1D92F0Impact {
    f32 scale;
    s16 duration;
    u8 pad6[2];
    f32 magnitude;
} Game1D92F0Impact;

typedef struct Game1D92F0Payload {
    Game1D92F0Surface *surface;
    s32 allocatorArg;
    u8 kind;
} Game1D92F0Payload;

extern Game1D92F0Selection D_800A9020[];
extern Game1D92F0Range D_800A9040[], D_800A9158[];
extern Game1D92F0Impact D_800A925C[];
u32 func_150ADA20(void);
u8 func_151D8E20(void);
void func_1514C678(f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, void *, s32);
void func_151DBE80(u8, f32, f32, s32, void *, void *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ABE40 CURRENT (3115) */
void func_151ABE40(Game1D92F0Position *arg0, Game1D92F0Surface *arg1,
                   s32 arg2, s32 arg3, s32 arg4) {
    u8 kind;
    Game1D92F0Payload firstPayload;
    Game1D92F0Range *first;
    Game1D92F0Payload secondPayload;
    Game1D92F0Range *second;
    Game1D92F0Selection *selection;
    Game1D92F0Impact *impact;
    s8 third;

    kind = func_151D8E20();
    if (arg1 != 0) {
        selection = &D_800A9020[arg2];
        if (selection->first != -1) {
            firstPayload.surface = arg1;
            firstPayload.kind = kind;
            firstPayload.allocatorArg = arg4;
            first = &D_800A9040[selection->first];
            func_1514C678(arg0->x, arg0->y, arg0->z, first->radius, 0, 0xFF,
                         (func_150ADA20() % (u32)(first->range + 1)) + first->base,
                         0xB, arg2, 0.0f, &firstPayload, ((u8 *)&arg3)[3]);
        }
        if (selection->second != -1) {
            secondPayload.surface = arg1;
            secondPayload.allocatorArg = arg4;
            secondPayload.kind = kind;
            second = &D_800A9158[selection->second];
            func_1514C678(arg0->x, arg0->y, arg0->z, second->radius, 0, 0xFF,
                         (func_150ADA20() % (u32)(second->range + 1)) + second->base,
                         0xC, arg2, 0.0f, &secondPayload, ((u8 *)&arg3)[3]);
        }
        third = selection->third;
        if ((third != -1) && (arg1->flags & 1)) {
            impact = &D_800A925C[third];
            func_151DBE80(kind, impact->scale, impact->magnitude, impact->duration,
                         arg0, arg1->normal, 0x96, 0, ((u8 *)&arg3)[3], arg4);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ABE40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151ABE40.s")
typedef struct {
    u8 alphaBase, alphaRange;
    s16 pitchBase;
    u16 pitchRange;
    u8 pad06[2];
    f32 speedBase, speedRange;
    s32 fadeBase, fadeRange;
    s16 lifeBase;
    u16 lifeRange;
    f32 sizeBase, sizeRange, growthBase, growthRange, chance;
} Game1D92F0ParticleStyle;

typedef struct {
    Game1D92F0Position position;
    s16 life, enabled;
    s32 active;
    u8 field14, fade, pad16[2];
} Game1D92F0Spawn;

typedef struct {
    f32 size;
    Game1D92F0Position velocity;
    f32 growth, height;
    u8 flags, mode, blue, alpha;
    u8 pad1C[4];
} Game1D92F0Motion;

typedef struct {
    s32 words[7];
    u8 callback, endCallback, pad1E[2];
} Game1D92F0Flags;

extern s8 D_800A9021[];
extern Game1D92F0ParticleStyle D_800A9068[];
extern u8 D_800AB3F4[], D_800AB404[];
f32 func_150ADA68(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AC078 CURRENT (2740) */
s32 func_151AC078(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, Game1D92F0Payload *arg13,
                   s32 arg14) {
    Game1D92F0ParticleStyle *style;
    Game1D92F0Spawn spawn;
    Game1D92F0Motion motion;
    s32 colorFlag;
    Game1D92F0Flags flags;
    f32 sineYaw;
    f32 cosineYaw;
    f32 speed;
    f32 horizontal;
    s32 yawArgument;
    s16 pitch;
    f32 sinePitch;
    f32 cosinePitch;
    s32 fullPitch;
    s32 firstFlag;
    s32 secondFlag;
    s32 styleIndex;

    styleIndex = D_800A9021[arg11 * 5];
    style = &D_800A9068[styleIndex];
    sineYaw = func_151423D8(((u8 *)&arg8)[3]);
    yawArgument = arg8 - 0x40;
    cosineYaw = func_151423D8((u8)yawArgument);
    flags.words[0] = 0;
    flags.words[1] = 1;
    flags.words[2] = 0x160600;
    flags.words[3] = 1;
    flags.words[4] = 0x10;
    flags.words[5] = 0x80;
    flags.words[6] = 0x20;
    flags.callback = 0;
    flags.endCallback = 9;
    spawn.active = 1;
    spawn.enabled = 1;
    spawn.position.y = arg3;
    motion.height = arg3;
    spawn.position.x = arg2;
    spawn.position.z = arg4;
    motion.mode = D_800AB3F4[arg13->kind];
    motion.blue = 0xFF;
    colorFlag = D_800AB404[arg13->kind] != 0 ? 0x20 : 0;
    motion.flags = colorFlag | 8;
    if (func_150ADA68() < style->chance) {
        motion.flags |= 3;
        firstFlag = 6;
        secondFlag = 2;
    } else {
        firstFlag = 0;
        secondFlag = 0;
        motion.flags &= 0xFFFC;
    }
    motion.alpha = func_150ADA20() % (u32)(style->alphaRange + 1) + style->alphaBase;
    fullPitch = func_150ADA20() % (u32)(style->pitchRange + 1) + style->pitchBase;
    pitch = fullPitch;
    sinePitch = func_151423D8((u8)fullPitch);
    cosinePitch = func_151423D8((u8)(pitch - 0x40));
    speed = func_150ADA68() * style->speedRange + style->speedBase;
    horizontal = speed * sinePitch;
    motion.velocity.x = horizontal * cosineYaw;
    motion.velocity.y = -speed * cosinePitch;
    motion.velocity.z = horizontal * sineYaw;
    spawn.fade = func_150ADA20() % (u32)(style->fadeRange + 1) + style->fadeBase;
    spawn.life = func_150ADA20() % (u32)(style->lifeRange + 1) + style->lifeBase;
    motion.size = func_150ADA68() * style->sizeRange + style->sizeBase;
    motion.growth = func_150ADA68() * style->growthRange + style->growthBase;
    func_15147DA0(&spawn, &motion, 0, 1, 8, 0, firstFlag, secondFlag, 0, 0, 0,
                  &flags, (s32)arg13->surface, ((u8 *)&arg14)[3], arg13->allocatorArg);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AC078 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AC078.s")
s32 func_151AC3CC(void *arg0) {
    s32 var_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    var_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    var_v1 *= 8;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
        *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) var_v1;
    }
    return 1;
}
u8 func_151D8E20(void);
void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);

typedef struct Game1D92F0Entry {
    f32 field_0;
    u8 pad_4[4];
    f32 field_8;
    u8 pad_C[8];
} Game1D92F0Entry;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AC408 CURRENT (128) */
s32 func_151AC408(void *arg0, s32 arg1, s32 arg2, s32 arg3,
                  f32 arg4, s32 arg5) {
    f32 position[3];
    u8 effect;
    Game1D92F0Entry *source;
    u8 *state;

    source = *(Game1D92F0Entry **)((u8 *)arg0 + 0x94);
    position[0] = source[*(s8 *)((u8 *)arg0 + 0x2D)].field_0;
    state = *(u8 **)((u8 *)arg0 + 0x98);
    position[1] = arg4;
    position[2] = source[*(s8 *)((u8 *)arg0 + 0x2D)].field_8;
    effect = func_151D8E20();
    if (func_150ADA20() & 1) {
        func_151D9B8C(effect, *(f32 *)state * 6.0f, state[0x1B], arg5,
                       position, (func_150ADA20() % 41U) + 0x50, 1, 1, 0,
                       *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
    } else {
        func_151DAB58(effect, *(f32 *)state * 1.5f, state[0x1B],
                       position, 1, *(u8 *)((u8 *)arg0 + 0xC),
                       *(u8 *)((u8 *)arg0 + 1));
    }
    state[0x20] = 4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AC408 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AC408.s")
