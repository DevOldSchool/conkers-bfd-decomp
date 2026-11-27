#include "types.h"
#include "game_functions.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_127060.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FA1B8
 * - func_150FA520
 * - func_150FAAEC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game127060State {
    u8 pad0[0x54];
    f32 field54;
    f32 field58;
    f32 field5C;
} Game127060State;

typedef struct Game127060Transform {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
} Game127060Transform;

void *func_10022EC0(void *, const void *, u32);
typedef struct Game127060Event {
    u8 type;
    u8 pad1;
    s16 duration;
    u8 field4;
    u8 field5;
    s8 field6;
    u8 pad7;
} Game127060Event;
void *func_151D8868(void *, s32, u8, s32);
struct225 *func_15160A58(struct127 *arg0, u8 arg1, void *arg2, u8 arg3, s16 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s8 argB, s32 argC, u8 argD, u8 argE, s32 argF);
void *func_1513D2F0(void *, void *, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
s32 func_151407D0(void *, u32, void *, u8, u8, u8, u8, s8, u8, s32);
extern u8 D_800A4AA0[];
extern Vec3f D_800A5480;

typedef struct Game127060BurstData {
    void *owner;
    u8 id;
    u8 pad05[3];
    void *sparks[2];
    void *glows[2];
} Game127060BurstData;

typedef struct Game127060BurstSpark {
    void *owner;
    u8 id;
    u8 index;
    u8 pad06[2];
    f32 field08;
    f32 field0C;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    void *object;
    f32 field54;
    s8 field58;
    u8 pad59[3];
} Game127060BurstSpark;

typedef struct Game127060BurstEffect {
    u8 kind;
    u8 mode;
    s16 flags;
    s16 lifetime;
    u8 pad06[2];
    s32 field08;
    s32 field0C;
    u8 color[4];
    f32 field14;
    f32 field18;
    Vec3f field1C;
    Vec3f field28;
    f32 field34;
    f32 field38;
    f32 field3C;
    s32 field40;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    s32 field48;
    u8 field4C;
    u8 pad4D[0xB];
} Game127060BurstEffect;

typedef struct Game127060BurstGlowShape {
    f32 field00;
    f32 field04;
    f32 field08;
    f32 field0C;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    s32 field24;
    s32 field28;
    s32 field2C;
    s32 field30;
    s32 field34;
    s32 field38;
    s32 field3C;
    s32 field40;
    s32 field44;
    f32 field48;
    s16 field4C;
    s16 field4E;
    s16 field50;
    s16 field52;
    u8 field54;
    u8 field55;
    u8 field56;
    u8 field57;
    u8 field58;
    s8 field59;
    u8 pad5A[2];
} Game127060BurstGlowShape;

typedef struct Game127060BurstGlow {
    s16 field00;
    u8 pad02[2];
    f32 field04;
    void *object;
    u8 index;
    u8 pad0D[3];
    void *owner;
    u8 id;
    u8 pad15[3];
} Game127060BurstGlow;

void func_150F9BB0(u8 *arg0, u8 arg1, s32 arg2) {
    void *object;
    Game127060BurstData burst;
    Game127060BurstData *data;

    burst.owner = arg0;
    burst.id = arg0[0x3B];
    burst.sparks[0] = 0;
    burst.sparks[1] = 0;
    burst.glows[0] = 0;
    burst.glows[1] = 0;
    object = func_15149130(0x46, -1, 0x4D, -1, 1, 0x33, 0x18, arg1, arg2);
    if (object != NULL) {
        data = (Game127060BurstData *)((u8 *)object + 0x28);
        func_10022EC0(data, &burst, sizeof(burst));
        {
            Game127060BurstSpark spark;
            Game127060BurstEffect sparkEffect;

            spark.field58 = 0;
            spark.field54 = (*(f32 *)(arg0 + 0x150) + *(f32 *)(arg0 + 0x14C)) * 0.5f;
            spark.owner = arg0;
            spark.id = arg0[0x3B];
            spark.field08 = 15.045272f;
            spark.field10 = 5.8676558f;
            spark.field18 = 12.111444f;
            spark.field0C = 0.396174f;
            spark.field24 = 0.0f;
            spark.field28 = 0.0f;
            spark.field38 = 0.0f;
            sparkEffect.field14 = 0.0f;
            sparkEffect.field18 = 0.0f;
            spark.field3C = 0.0f;
            spark.field48 = 1.0f;
            spark.field40 = 1.0f;
            spark.field4C = 1.0f;
            spark.field44 = 1.0f;
            spark.object = object;
            sparkEffect.kind = 0x5F;
            sparkEffect.mode = 8;
            sparkEffect.flags = 0x2203;
            sparkEffect.lifetime = 0x12C;
            sparkEffect.field08 = 0;
            sparkEffect.field0C = 0;
            sparkEffect.color[0] = 0xFF;
            sparkEffect.color[1] = 0xFF;
            sparkEffect.color[2] = 0xFF;
            sparkEffect.color[3] = 0xFF;
            spark.field14 = 0.1042563f;
            spark.field20 = 0.5197371f;
            spark.field1C = 0.34404588f;
            spark.field2C = 160.0f;
            spark.field30 = 95.0f;
            spark.field34 = 207.5f;
            sparkEffect.field1C = D_800A5480;
            sparkEffect.field28 = D_800A5480;
            sparkEffect.field34 = 1.0f;
            sparkEffect.field38 = 1.0f;
            sparkEffect.field3C = 1.0f;
            sparkEffect.field40 = 0x40EC0000;
            sparkEffect.field44 = 0;
            sparkEffect.field45 = 0xFF;
            sparkEffect.field46 = 0;
            sparkEffect.field47 = 7;
            sparkEffect.field48 = 0;
            for (spark.index = 0; spark.index < 2; spark.index++) {
                data->sparks[spark.index] = func_1513D2F0(&sparkEffect, D_800A4AA0, 0, 0x25, 0, 0x1D,
                    ((func_150ADA20() & 1) ? 2 : 0) + 1, 0, 0, 0x5C, arg1, arg2);
                if (data->sparks[spark.index] != 0) {
                    func_10022EC0((u8 *)data->sparks[spark.index] + 0x110, &spark, sizeof(spark));
                }
            }
        }
        {
            Game127060BurstGlowShape shape;
            Game127060BurstEffect glowEffect;
            Game127060BurstGlow glow;

            glow.field00 = 0;
            glow.field04 = 1.0f;
            glow.owner = arg0;
            glow.object = object;
            glow.id = arg0[0x3B];
            shape.field00 = 50.3f;
            shape.field04 = 50.3f;
            shape.field08 = 30.9f;
            shape.field0C = 30.9f;
            shape.field10 = 0.1f;
            shape.field14 = 0.1f;
            shape.field1C = 0.7f;
            shape.field20 = 0.000001f;
            shape.field24 = -1;
            shape.field34 = -1;
            shape.field28 = -1;
            shape.field38 = -1;
            shape.field2C = -1;
            shape.field3C = -1;
            shape.field30 = -1;
            shape.field40 = -1;
            shape.field18 = 1.0f;
            shape.field44 = 0;
            shape.field48 = 1.0f;
            shape.field4C = 0;
            shape.field4E = 0;
            shape.field50 = 0;
            shape.field52 = 0;
            shape.field54 = 0;
            shape.field55 = 0;
            shape.field56 = 0;
            shape.field57 = 0;
            shape.field58 = 0xF;
            shape.field59 = -1;
            glowEffect.kind = 0x60;
            glowEffect.mode = 3;
            glowEffect.flags = 0x2203;
            glowEffect.lifetime = 0x12C;
            glowEffect.field08 = 0;
            glowEffect.field0C = 0;
            glowEffect.color[0] = 0xFF;
            glowEffect.color[1] = 0xFF;
            glowEffect.color[2] = 0xFF;
            glowEffect.color[3] = 0xFF;
            glowEffect.field14 = 100.0f;
            glowEffect.field18 = 100.0f;
            glowEffect.field1C = D_800A5480;
            glowEffect.field28 = D_800A5480;
            glowEffect.field34 = 1.0f;
            glowEffect.field38 = 1.0f;
            glowEffect.field3C = 1.0f;
            glowEffect.field40 = 0xCD2002;
            glowEffect.field44 = 0xFF;
            glowEffect.field45 = 0xFF;
            glowEffect.field46 = 0;
            glowEffect.field47 = 7;
            glowEffect.field48 = 0;
            glowEffect.field4C = 0xFF;
            for (glow.index = 0; glow.index < 2; glow.index++) {
                data->glows[glow.index] = (void *)func_151407D0(&shape, 0x78, &glowEffect, 0, 0x2A, 0, 0, -1, arg1, arg2);
                if (data->glows[glow.index] != 0) {
                    func_10022EC0((u8 *)data->glows[glow.index] + 0x170, &glow, sizeof(glow));
                }
            }
        }
    }
    {
        Game127060Event event;

        event.type = 1;
        event.duration = 0x46;
        event.field5 = 1;
        event.field4 = 8;
        event.field6 = -1;
        func_151D8868(&event, 0, arg1, arg2);
    }
    func_15160A58((struct127 *)arg0, 1, D_800A1CC0, 3, 0x46, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, arg1, arg2);
}
typedef struct {
    u8 pad0[0x48];
    f32 width, height;
    u8 pad50[8];
    u8 flags;
} Game127060FirstParams;
typedef struct {
    u8 pad0[0x34];
    Vec3f position, direction;
    u8 pad4C[0xC4];
    Game127060FirstParams params;
} Game127060First;
typedef struct { u8 pad0[4]; f32 size; } Game127060SecondParams;
typedef struct {
    u8 pad0[0x34];
    Vec3f position, direction;
    u8 pad4C[0xC];
    volatile u32 flags;
    u8 pad5C[0x114];
    Game127060SecondParams params;
} Game127060Second;
typedef struct {
    s32 active;
    u8 pad4[0x37];
    u8 generation;
    u8 pad3C[0x198];
    u8 *transform;
} Game127060Owner;
typedef struct {
    Game127060Owner *owner;
    u8 generation;
    u8 pad5[3];
    Game127060First *first[2];
    Game127060Second *second[2];
} Game127060Group;
typedef struct {
    u8 pad0[0xE];
    s16 age;
    u8 pad10[0x18];
    Game127060Group group;
} Game127060Effect;

void func_15145EA4(s32 *, s32 *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FA1B8 CURRENT (2446) */
void func_150FA1B8(Game127060Effect *effect) {
    Vec3f first[2];
    Vec3f second[2];
    Vec3f *inputs[4];
    Vec3f *outputs[4];
    Game127060Group *group;
    Game127060Owner *owner;
    void *object;
    s32 i;
    u32 next;
    Game127060Group *cursor;
    Game127060FirstParams *firstParams;
    Game127060SecondParams *secondParams;
    f32 width, height, size;

    owner = effect->group.owner;
    group = &effect->group;
    if (!owner->active || owner->generation != group->generation) {
        effect->age = -1;
        return;
    }
    if (owner->transform) {
        inputs[0] = &D_800A1CCC;
        inputs[1] = &D_800A1CD8;
        inputs[2] = &D_800A1CE4;
        inputs[3] = &D_800A1CF0;
        outputs[0] = &first[0];
        outputs[1] = &first[1];
        outputs[2] = &second[0];
        outputs[3] = &second[1];
        func_15145EA4((s32 *)inputs, (s32 *)outputs, (s32)(owner->transform + 0x40), 4);
        i = 0;
        do {
            cursor = (Game127060Group *)((u8 *)group + i * 4);
            object = cursor->first[0];
            if (object) {
                ((Game127060First *)object)->params.flags |= 1;
                ((Game127060First *)object)->position = first[i];
                ((Game127060First *)object)->direction = second[i];
            }
            object = cursor->second[0];
            if (object) {
                next = ((Game127060Second *)object)->flags | 2;
                ((Game127060Second *)object)->flags = next;
                ((Game127060Second *)object)->flags = next & ~4;
                ((Game127060Second *)object)->position = first[i];
                ((Game127060Second *)object)->direction = second[i];
            }
            next = (i + 1) & 0xFF;
            i = next;
        } while (i < 2);
    } else {
        i = 0;
        do {
            cursor = (Game127060Group *)((u8 *)group + i * 4);
            object = cursor->first[0];
            if (object) {
                firstParams = &((Game127060First *)object)->params;
                firstParams->flags &= ~1;
            }
            object = cursor->second[0];
            if (object) ((Game127060Second *)object)->flags &= ~2;
            next = (i + 1) & 0xFF;
            i = next;
        } while (i < 2);
    }
    height = 15.0f;
    width = 6.0f;
    size = D_800A1D94;
    i = 0;
    do {
        cursor = (Game127060Group *)((u8 *)group + i * 4);
        object = cursor->first[0];
        if (object) {
            firstParams = &((Game127060First *)object)->params;
            if (effect->age < 10) {
                firstParams->width = 0.0f;
                firstParams->height = 0.0f;
            } else {
                firstParams->width = width;
                firstParams->height = height;
            }
        }
        object = cursor->second[0];
        if (object) {
            secondParams = &((Game127060Second *)object)->params;
            if (effect->age < 10) secondParams->size = 0.0f;
            else secondParams->size = size;
        }
        next = (i + 1) & 0xFF;
        i = next;
    } while (i < 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FA1B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA1B8.s")
void func_1515D4D4(s32, s32, s32, u8);

void func_150FA468(void *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4C) {
        *(s8 *)((u8 *)arg0 + 0x11) = -1;
        func_1515D4D4(0, 0, 0, 0xFF);
        return;
    }
    if (arg2 == 0x4D) {
        *(s8 *)((u8 *)arg0 + 0x11) = 0x1E;
        return;
    }
    if (arg2 == 0x4E) {
        *(s8 *)((u8 *)arg0 + 0x11) = -1;
        return;
    }
    if (arg2 == 0x4F) {
        *(s8 *)((u8 *)arg0 + 0x11) = -1;
        func_1515D4D4(0xFF, 0xFF, 0xFF, 0xFF);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA520.s")
extern u8 D_80088B60;
extern u8 *D_800D3098;

void func_150FAA40(u8 arg0, s32 arg1) {
    struct { u8 *first; u8 *second; f32 value; } packet;
    u8 *temp_v0;

    if (D_80088B60 == 0) {
        packet.first = D_800D3098 + 0x71C;
        packet.second = D_800D3098 + 0x6E8;
        packet.value = 0.0f;
        temp_v0 = func_15149130(0x12C, -1, 0x57, -1, 0, 0x46, 0xC, (s32)arg0, arg1);
        if (temp_v0 != 0) {
            D_80088B60 = 1;
        }
        if (temp_v0 != 0) {
            func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0xCU);
        }
    }
}
typedef struct Game127060Emission {
    s32 first;
    s32 second;
    f32 count;
} Game127060Emission;

f32 func_150ADA68(void);
void func_1514470C(s32, void *);
void func_150F4570(Vec3f *, Vec3f *, u8, f32, f32, f32, u8, s32, u8, s32);
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FAAEC CURRENT (2754) */
void func_150FAAEC(u8 *arg0) {
    f32 first[3];
    f32 second[3];
    f32 duration;
    f32 random;
    f32 range;
    s32 index;
    Game127060Emission *emission;

    emission = (Game127060Emission *)(arg0 + 0x28);
    emission->count += (D_800A1DB8 + func_150ADA68() * D_800A1DBC) * D_800BE9A4;
    if (emission->count > 1.0f) {
        range = 1.0f;
        do {
            func_1514470C(emission->first, first);
            func_1514470C(emission->second, second);
            index = (func_150ADA20() % D_80088B2C) & 0xFF;
            duration = func_150ADA68() * 25.0f + 30.0f;
            random = func_150ADA68();
            func_150F4570(first, second, D_80088B30[index * 2 + 1], duration,
                1.0f / duration, (random * range + range) * D_80088B34[index],
                1, func_150ADA20() % 3U + 750, arg0[0xC], arg0[1]);
            emission->count -= 1.0f;
        } while (emission->count > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FAAEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FAAEC.s")

void func_150FACE4(void *arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0x4E) || (arg2 == 0x4F)) {
        func_1516972C(arg0);
    }
}
extern u8 *D_800D3098;

void func_150FAD28(void) {
    func_1515F170(8, 0);
    func_1515F170(0xB, 1);
    func_151494E0(D_800D3098 + 0x514, 0x30);
    func_151494E0(0, 0x4D);
}
void func_150FAD78(void) {
    func_1515F170(8, 1);
    func_1515F170(7, 0);
    func_151494E0(D_800D3098 + 0x514, 0x31);
    func_151494E0(0, 0x4C);
}
void func_150FADC8(void *arg0, s32 arg1, u8 arg2) {

    if (arg2 == 0x53) {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 2);
        return;
    }
    if (arg2 == 0x54) {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) & ~2);
    }
}
typedef struct {
    u8 flags, mode, type, extra, field04, pad05;
    s16 id;
    s32 field08, field0C, field10, field14, field18;
    s32 field1C, field20, field24, field28;
    u8 field2C, field2D, pad2E[2];
    u8 colors[8];
    u8 field38, pad39[3];
    s32 field3C;
    u8 field40, field41, pad42[2];
    Vec3f position;
    s32 field50;
    s16 field54, field56;
} Game127060Model;

typedef struct {
    f32 x, y, width, height;
    u8 kind, pad11;
    s16 id, flags, field16, field18;
    u8 field1A, colors[9];
    s32 field24, field28, field2C, field30, field34, field38, field3C;
    u8 field40, field41, pad42[2];
    u8 field44, pad45[3];
    f32 field48, field4C, field50, field54;
} Game127060Sprite;

typedef struct { s16 values[8]; } Game127060Kinds;
extern Game127060Kinds D_800A1D20;
s32 func_15157010(s32, s32, f32, s32, s32, s32, s32, s32);

void func_150FAE18(s16 arg0, u8 arg1, s32 arg2) {
    s16 id[1];

    id[0] = arg0;
    {
        Game127060Model model;
        u8 *object;

        model.flags = 0x61;
        model.mode = 3;
        model.type = 4;
        model.extra = 2;
        model.field08 = 0xA5;
        model.field0C = 0x17;
        model.field14 = 0x200405;
        model.field18 = 0x60200;
        model.field2D = 8;
        model.field1C = 1;
        model.field20 = 0x38;
        model.field24 = 0x80;
        model.field38 = 0;
        model.field04 = 0;
        model.id = arg0;
        model.field10 = 0;
        model.field2C = 0;
        model.field28 = 0x20;
        model.colors[0] = 0xFF;
        model.colors[1] = 0xFF;
        model.colors[2] = 0xFF;
        model.colors[3] = 0xFF;
        model.colors[4] = 0xFF;
        model.colors[5] = 0xFF;
        model.colors[6] = 0xFF;
        model.colors[7] = 0xFF;
        model.field3C = 0;
        model.field40 = 0;
        model.field41 = 1;
        model.position = D_800A5480;
        model.field54 = 10;
        model.field56 = 25;
        object = (u8 *)func_15157010((s32)&model, 0, 1, 0, 0, 2, arg1, arg2);
        if (object != 0) {
            func_10022EC0(object + 0x120, id, 2);
        }
        {
            Game127060Sprite sprite;
            u8 index;
            Game127060Kinds kinds;

            kinds = D_800A1D20;
            sprite.flags = 0x29;
            sprite.field16 = 10;
            sprite.field18 = 25;
            sprite.colors[0] = 0xFF;
            sprite.colors[1] = 0xFF;
            sprite.colors[2] = 0xFF;
            sprite.colors[3] = 0xFF;
            sprite.colors[4] = 0xFF;
            sprite.colors[5] = 0xFF;
            sprite.id = arg0;
            sprite.width = 16.0f;
            sprite.height = 16.0f;
            sprite.field1A = 0;
            sprite.colors[6] = 0xFF;
            sprite.colors[7] = 0xFF;
            sprite.colors[8] = 0xFF;
            sprite.field24 = 0;
            sprite.field28 = 0x200405;
            sprite.field2C = 0x60200;
            sprite.field40 = 0;
            sprite.field41 = 7;
            sprite.field30 = 25;
            sprite.field34 = 0x22;
            sprite.field38 = 0x80;
            sprite.field3C = 0x20;
            sprite.field44 = 0;
            sprite.field48 = 1.0f;
            sprite.field4C = 1.0f;
            sprite.field50 = 0.0f;
            sprite.field54 = 0.0f;
            sprite.y = 62.0f;
            for (index = 0; index < 8; index++) {
                sprite.x = -65.0f + index * 24.75f;
                sprite.kind = kinds.values[index];
                object = func_1515548C(&sprite, 14, 0, 0, 2, arg1, arg2);
                if (object != 0) {
                    func_10022EC0(object + 0x70, id, 2);
                }
            }
        }
    }
}

s32 func_150FB188(Game127060State *arg0) {
    Game127060Transform transform;

    arg0->field5C = 0.0f;
    arg0->field54 = -95.0f;
    arg0->field58 = -80.0f;
    transform.field0 = 0.0f;
    transform.field4 = 0.0f;
    transform.field8 = 0.0f;
    transform.fieldC = 0.3f;
    transform.field10 = 0.3f;
    func_15157DEC((u8 *)arg0, (u8 *)&transform);
    return 1;
}

void *func_15157F80(s32, s32, s32, s32, s32);
s32 func_151D710C(s32, s32, s32, s32, s32);

void func_150FB1E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_15157F80(func_151D710C(arg0, arg1, arg2, arg3, arg4), arg1, arg2, arg3, arg4);
}
