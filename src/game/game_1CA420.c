#include "types.h"

/*
 * Reviewed source unit: src/game/game_1CA420.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1519CF70
 * - func_1519D454
 * - func_1519D9F4
 * - func_1519E570
 * - func_1519E818
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15147D64(u8 *arg0, s32 arg1);
void func_1519CF70(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519CF70 CURRENT (400) */
void func_1519CF70(s32 arg0) {
    u8 data[4];

    data[0] = arg0;
    func_15147D64(data, 6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519CF70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519CF70.s")
typedef struct Game1CA420Packet {
    u8 pad0[6];
    u8 flags;
} Game1CA420Packet;

typedef struct Game1CA420Actor {
    u8 pad0[0x1E];
    u16 flags;
    u8 pad20[0x10];
    u8 state;
    u8 pad31[0x67];
    Game1CA420Packet *packet;
} Game1CA420Actor;

void func_1519CFA0(Game1CA420Actor *arg0) {
    Game1CA420Packet *packet;

    packet = arg0->packet;
    arg0->state = 0;
    arg0->flags &= ~2;
    packet->flags = (packet->flags |= 1) | 4;
}
/* Call context: func_151478F4: unique active project prototype */
/* Call context: func_1514EDF0: unique active project prototype */
void func_151478F4(s32);
void func_1514EDF0(s32, s32);

void func_1519CFD0(void *arg0) {
    s32 *temp_v0;

    temp_v0 = *(s32 **)((u8 *)arg0 + 0x98);
    func_1514EDF0((s32) arg0, *temp_v0);
    func_151478F4((s32) arg0);
}
/* Call context: func_15147928: unique active project prototype */
/* Call context: func_1514EDF0: unique active project prototype */
void func_15147928(s32);

void func_1519D000(void *arg0) {
    s32 *temp_v0;

    temp_v0 = *(s32 **)((u8 *)arg0 + 0x98);
    func_1514EDF0((s32) arg0, *temp_v0);
    func_15147928((s32) arg0);
}
typedef struct Game1CA420Vector {
    f32 x;
    f32 y;
    f32 z;
} Game1CA420Vector;

typedef struct Game1CA420TrailOwner {
    s32 active;
    u8 pad4[0x10];
    Game1CA420Vector position;
    u8 pad20[0x1B];
    u8 generation;
    u8 pad3C[0x2B8];
    void *links;
} Game1CA420TrailOwner;

typedef struct Game1CA420TrailSpec {
    f32 field0;
    f32 field4;
    u8 field8;
    u8 pad9[3];
    s32 fieldC;
    u8 field10;
    u8 pad11[3];
    Game1CA420Vector position;
    s16 field20;
    s16 field22;
    s16 field24;
    u8 pad26[2];
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    s16 field38;
    s16 field3A;
    u8 field3C;
    u8 field3D;
    u8 field3E;
    u8 field3F;
} Game1CA420TrailSpec;

typedef struct Game1CA420TrailData {
    void *owner;
    u8 generation;
    u8 index;
    u8 flags;
    u8 pad7;
    Game1CA420Vector position;
    Game1CA420Vector transformed;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    u8 field40;
    u8 pad41;
    s16 field42;
    s16 field44;
    s16 field46;
    s16 field48;
    s16 field4A;
    u8 field4C;
    u8 pad4D[3];
    Game1CA420Vector origin;
    u8 field5C;
    u8 field5D;
    u8 field5E;
    u8 field5F;
} Game1CA420TrailData;

typedef struct Game1CA420TrailSpawn {
    Game1CA420Vector position;
    s16 lifetime;
    u16 flags;
    s32 kind;
    u8 pad14;
    u8 type;
    u8 pad16[2];
} Game1CA420TrailSpawn;

struct Game1CA420Transform;
s32 func_1519E304(struct Game1CA420Transform *, f32 *, f32, f32, f32, f32);
void *func_10022EC0(void *, const void *, u32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern Game1CA420TrailSpec D_800A8B80[];

s32 func_1519D030(void *arg0, s32 arg1, s16 arg2, u8 arg3, u8 arg4, s32 arg5) {
    s32 unused;
    struct {
        Game1CA420TrailData data;
        Game1CA420TrailSpawn spawn;
    } locals;
    Game1CA420Actor *result;
    s32 flags;
    Game1CA420TrailSpec *spec;

    if (arg0 == 0) {
        return 0;
    }
    locals.data.field20 = 0.0f;
    flags = 0;
    locals.data.origin.x = ((Game1CA420TrailOwner *)arg0)->position.x;
    spec = &D_800A8B80[arg1];
    locals.data.origin.y = ((Game1CA420TrailOwner *)arg0)->position.y;
    locals.data.origin.z = ((Game1CA420TrailOwner *)arg0)->position.z;
    locals.data.owner = arg0;
    locals.data.generation = ((Game1CA420TrailOwner *)arg0)->generation;
    locals.data.flags = 2;
    locals.data.pad7 = 0;
    locals.data.field4C = arg1;
    locals.spawn.lifetime = arg2;
    locals.data.field2C = 0.0f;
    flags = arg3 ? 1 : 0;
    locals.spawn.flags = flags | 2;
    locals.data.field24 = spec->field0;
    locals.data.field28 = spec->field4;
    locals.data.field40 = spec->field8;
    locals.spawn.type = spec->fieldC;
    locals.data.index = spec->field10;
    locals.data.position = spec->position;
    locals.data.field42 = spec->field20;
    locals.data.field44 = spec->field22;
    locals.data.field46 = spec->field24;
    locals.data.field38 = spec->field28;
    locals.data.field34 = spec->field2C;
    locals.data.field30 = spec->field30;
    locals.data.field3C = spec->field34;
    locals.data.field48 = spec->field38;
    locals.data.field4A = spec->field3A;
    locals.data.field5C = spec->field3C;
    locals.data.field5D = spec->field3D;
    locals.data.field5E = spec->field3E;
    locals.data.field5F = spec->field3F;
    if (func_1519E304((struct Game1CA420Transform *)&locals.data,
                      &locals.spawn.position.x, 0.0f, 0.0f, 0.0f, 1.0f) != 0) {
        locals.data.transformed = locals.spawn.position;
        locals.spawn.flags |= 4;
    }
    locals.spawn.kind = 4;
    result = func_15147A80(&locals.spawn, (void *)0x60, 0x24, 3, 3, 3,
                           0, 0, 0, arg4, arg5);
    if (result != 0) {
        func_10022EC0(result->packet, &locals.data, sizeof(locals.data));
    }
    return (s32)result;
}
typedef struct Game1CA420Particle {
    Game1CA420Vector position;
    Game1CA420Vector velocity;
    f32 angle;
    s16 fade;
    s16 delay;
    u8 active;
    u8 shade;
    u8 pad22[2];
} Game1CA420Particle;

typedef struct Game1CA420Trail {
    u8 pad0[0x10];
    Game1CA420Vector current;
    s16 lifetime;
    u16 flags;
    u8 pad20[5];
    u8 capacity;
    u8 pad26[6];
    s8 count;
    s8 head;
    s8 tail;
    u8 pad2F[0x25];
    Game1CA420Vector position;
    u8 pad60[0x34];
    Game1CA420Particle *particles;
    Game1CA420TrailData *data;
} Game1CA420Trail;

extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

s32 func_1519D240(Game1CA420Trail *arg0) {
    s16 delay;
    s32 offset;
    s32 base;
    s32 index;
    Game1CA420Particle *particle;
    Game1CA420Particle *velocity;
    Game1CA420TrailData *data;

    data = arg0->data;
    base = (s32)arg0->particles;
    if (arg0->count < 2 && (data->flags & 1)) {
        return 0;
    }
    index = arg0->tail;
    if (index != arg0->head) {
        do {
            index--;
            if (index < 0) {
                index = arg0->capacity - 1;
            }
            offset = index * 0x24;
            particle = (Game1CA420Particle *)(offset + base);
            particle->active = 0xFF;
            velocity = &((Game1CA420Particle *)base)[index];
            delay = particle->delay;
            particle->velocity.x *= data->field30;
            particle->velocity.y += data->field24 * D_800BE9A4;
            particle->velocity.z *= data->field30;
            particle->position.x += velocity->velocity.x * D_800BE9A4;
            particle->position.y += velocity->velocity.y * D_800BE9A4;
            particle->position.z += velocity->velocity.z * D_800BE9A4;
            if (delay > 0) {
                particle->delay = delay - D_800BE9E4;
            } else {
                particle->fade -= D_800BE9E4 * data->field46;
            }
            particle->angle += D_800BE9A4 * data->field34;
            if (particle->fade < 0) {
                data->flags &= ~2;
                if (index != arg0->head) {
                    do {
                        arg0->head++;
                        if (arg0->head == arg0->capacity) {
                            arg0->head = 0;
                        }
                        arg0->count--;
                    } while (index != arg0->head);
                }
                ((Game1CA420Particle *)(base + arg0->head * 0x24))->fade = 0;
            }
        } while (index != arg0->head);
    }
    if (arg0->count > 0) {
        arg0->position = ((Game1CA420Particle *)base)[arg0->head].position;
    } else {
        arg0->position.x = 0.0f;
        arg0->position.y = 0.0f;
        arg0->position.z = 0.0f;
    }
    return 1;
}
s32 func_151491F4(s16, s8, s8, u8, u8, s32, u8, s32);
void func_1514EC1C(s32, s32, s32);
s32 func_1514ED3C(void *, s32, void **);
u32 func_150ADA20(void);
extern f32 D_800BE9A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519D454 CURRENT (10755) */
s32 func_1519D454(Game1CA420Trail *arg0) {
    f32 oldX;
    f32 oldZ;
    struct {
        Game1CA420TrailOwner *actor;
        u8 generation;
        u8 pad5[3];
        s32 value;
    } link;
    f32 time;
    f32 stepTime;
    Game1CA420Vector delta;
    f32 angleDelta;
    Game1CA420Vector position;
    f32 inverse;
    f32 currentX;
    f32 currentZ;
    f32 previousAngle;
    f32 differenceX;
    Game1CA420Vector velocity;
    Game1CA420Vector *previous;
    f32 stepX;
    f32 stepY;
    f32 stepZ;
    f32 stepAngle;
    f32 angle;
    f32 originX;
    f32 differenceZ;
    Game1CA420TrailData *data;
    s32 base;
    Game1CA420TrailOwner *actor;
    Game1CA420Vector *current;
    Game1CA420Particle *particle;
    s32 initialized;
    s32 spawnFlags;
    s32 effect;
    s32 index;
    s32 head;

    data = arg0->data;
    base = (s32)arg0->particles;
    actor = data->owner;
    if (actor->active == 0) {
        return 0;
    }
    if (data->generation != actor->generation) {
        return 0;
    }
    initialized = 0;
    if (!(arg0->flags & 4)) {
        current = &arg0->current;
        if (func_1519E304((struct Game1CA420Transform *)data,
                          &current->x, 0.0f, 0.0f, 0.0f, 1.0f) != 0) {
            initialized = 1;
            data->transformed = *current;
            arg0->flags |= 4;
        } else {
            return 1;
        }
    }
    currentX = arg0->current.x;
    oldX = currentX;
    currentZ = arg0->current.z;
    oldZ = currentZ;
    if (initialized == 0 &&
        func_1519E304((struct Game1CA420Transform *)data, &arg0->current.x,
                      currentX, arg0->current.y, currentZ, data->field3C) == 0) {
        func_1519CFA0((Game1CA420Actor *)arg0);
        link.actor = data->owner;
        spawnFlags = 0;
        link.generation = ((Game1CA420TrailOwner *)data->owner)->generation;
        link.value = data->field4C;
        spawnFlags = (arg0->flags & 1) ? 1 : 0;
        effect = func_151491F4(arg0->lifetime, -1, 8, spawnFlags & 0xFF,
                              2, 0xC, 0xFF, 0);
        if (effect != 0) {
            func_10022EC0((u8 *)effect + 0x28, &link, sizeof(link));
            if (func_1514ED3C(((Game1CA420TrailOwner *)data->owner)->links,
                              (s32)arg0, 0) != 0) {
                func_1514EC1C(effect, (s32)data->owner, 0x11);
            }
        }
        return 1;
    }
    data->field2C += data->field28 * D_800BE9A4;
    if (data->field2C > 1.0f) {
        inverse = 1.0f / data->field2C;
        previous = &data->transformed;
        position = *previous;
        time = data->field20 + D_800BE9A4;
        currentX = arg0->current.x;
        previousAngle = data->field38;
        differenceX = currentX - data->transformed.x;
        stepTime = time * inverse;
        delta.x = differenceX;
        angle = previousAngle + data->field34 * time;
        delta.y = arg0->current.y - data->transformed.y;
        angleDelta = previousAngle - angle;
        delta.z = arg0->current.z - data->transformed.z;
        velocity.y = 0.0f;
        velocity.x = (currentX - oldX) * D_800BE9A8;
        velocity.z = (arg0->current.z - oldZ) * D_800BE9A8;
        stepX = differenceX * inverse;
        stepY = delta.y * inverse;
        stepZ = delta.z * inverse;
        stepAngle = angleDelta * inverse;
        do {
            particle = (Game1CA420Particle *)(arg0->tail * 0x24 + base);
            particle->position.x = position.x;
            particle->position.y = position.y;
            particle->position.z = position.z;
            particle->velocity = velocity;
            particle->angle = angle;
            particle->shade = data->pad7;
            particle->fade = data->field42;
            particle->delay = data->field44;
            data->pad7 = data->pad7 + data->field48 +
                         func_150ADA20() % (u32)(data->field4A + 1);
            particle->active = 0xFF;
            particle->velocity.y += data->field24 * time;
            particle->position.x += particle->velocity.x * time;
            differenceZ = particle->velocity.z * time;
            particle->position.y += particle->velocity.y * time;
            time -= stepTime;
            particle->position.z += differenceZ;
            arg0->tail++;
            if (arg0->capacity == arg0->tail) {
                arg0->tail = 0;
            }
            head = arg0->head;
            arg0->count++;
            if (head == arg0->tail) {
                arg0->head = head + 1;
                if (arg0->capacity == arg0->head) {
                    arg0->head = 0;
                }
                arg0->count--;
            }
            position.x += stepX;
            position.y += stepY;
            angle += stepAngle;
            position.z += stepZ;
            data->field2C -= 1.0f;
        } while (data->field2C > 1.0f);
        *previous = position;
        data->field20 = time;
    }
    actor = data->owner;
    index = arg0->tail;
    originX = actor->position.x;
    if (index != arg0->head) {
        do {
            index--;
            if (index < 0) {
                index = arg0->capacity - 1;
            }
            particle = (Game1CA420Particle *)(index * 0x24 + base);
            particle->position.x += originX - data->origin.x;
            particle->position.y += actor->position.y - data->origin.y;
            particle->position.z += actor->position.z - data->origin.z;
        } while (index != arg0->head);
        originX = ((Game1CA420TrailOwner *)data->owner)->position.x;
    }
    data->origin.x = originX;
    data->origin.y = ((Game1CA420TrailOwner *)data->owner)->position.y;
    data->origin.z = ((Game1CA420TrailOwner *)data->owner)->position.z;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519D454 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519D454.s")
typedef struct Game1CA420Vertex {
    s16 x, y, z;
    u16 flags;
    s16 s, t;
    u8 r, g, b, a;
} Game1CA420Vertex;

typedef struct Game1CA420Command {
    u32 first;
    u32 second;
} Game1CA420Command;

s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
s32 func_1513F4E4(s32, u8, u8 *);
s32 *func_15142B7C(s32 *, s32, s32);
void *func_15142C10(void *, s32, s32, s32, s32, u8 *);
void *func_15142FBC(void *, s32, s32, u8 *);
void func_151D5D60(void *, s16, s32, void **, u8 *);
extern u8 D_80090CD4[];
extern s32 D_800D2C9C;
extern f32 D_800DD1D8[];
extern f32 D_800DD1E8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519D9F4 CURRENT (13737) */
void *func_1519D9F4(Game1CA420Trail *arg0, s32 arg1, s16 arg2) {
    Game1CA420Vertex *vertex;
    Game1CA420TrailData *data;
    Game1CA420Vector nextPosition;
    Game1CA420Vector position;
    s32 index;
    u8 shade;
    u8 previousShade;
    s16 alpha;
    u8 state;
    f32 widthZ;
    f32 widthX;
    f32 previousWidthZ;
    f32 previousWidthX;
    f32 *directionX;
    f32 *directionZ;
    f32 x;
    f32 z;
    f32 angle;
    s16 previousAlpha;
    s16 texture;
    s16 remaining;
    s32 fade;
    s32 base;
    s32 cursor;
    s32 last;
    Game1CA420Particle *particle;
    s32 commands;
    u8 intensity;

    commands = arg1;
    if (arg0->count >= 2) {
        func_151D5D60((u8 *)arg0 + 0x84, arg2,
                      (arg0->capacity << 5) + 0xA0, (void **)&vertex, 0);
        if (vertex != 0) {
            data = arg0->data;
            base = (s32)arg0->particles;
            state = 1;
            fade = 0;
            if (data->flags & 2) {
                remaining = data->field5C;
                cursor = arg0->head;
                do {
                    ((Game1CA420Particle *)(base + cursor * 0x24))->active = fade;
                    cursor++;
                    fade = (fade + data->field5D) & 0xFF;
                    if (cursor == arg0->capacity) {
                        cursor = 0;
                    }
                    remaining--;
                } while (remaining != 0 && cursor != arg0->tail);
            }
            if (data->flags & 4) {
                fade = 0;
                remaining = data->field5E;
                cursor = arg0->tail - 1;
                if (cursor < 0) {
                    cursor = arg0->capacity - 1;
                }
                do {
                    particle = (Game1CA420Particle *)(base + cursor * 0x24);
                    cursor--;
                    particle->active = (particle->active * fade) >> 8;
                    remaining--;
                    fade = (fade + data->field5F) & 0xFF;
                    if (cursor < 0) {
                        cursor = arg0->capacity - 1;
                    }
                } while (remaining != 0 && cursor != arg0->tail);
            }
            commands = func_15142E24(commands, (s32)D_80090CD4,
                0, 0, 0, 0, 0x1F, 0, 0, &state, 3);
            intensity = data->field40;
            commands = (s32)func_15142FBC(func_15142B7C((s32 *)func_1513F4E4(
                (s32)func_15142C10((void *)commands,
                intensity, intensity, intensity, 0xFF, &state), 6, &state),
                1, 0x160600), D_800D2C9C | 0x80000 | 0x2CA0, 0x5049D8, &state);
            if (arg0->flags & 2) {
                index = arg0->tail - 1;
                if (index < 0) {
                    index = arg0->capacity - 1;
                }
                position = arg0->current;
                particle = (Game1CA420Particle *)(base + index * 0x24);
                directionX = &D_800DD1E8[arg2];
                x = *directionX;
                angle = particle->angle;
                directionZ = &D_800DD1D8[arg2];
                z = *directionZ;
                previousWidthX = x * angle;
                previousShade = particle->shade;
                previousWidthZ = z * angle;
                previousAlpha = (particle->active * particle->fade) >> 8;
            } else {
                cursor = arg0->tail - 1;
                if (cursor < 0) {
                    cursor = arg0->capacity - 1;
                }
                index = cursor - 1;
                if (index < 0) {
                    index = arg0->capacity - 1;
                }
                particle = (Game1CA420Particle *)(base + cursor * 0x24);
                position = particle->position;
                angle = particle->angle;
                directionX = &D_800DD1E8[arg2];
                x = *directionX;
                directionZ = &D_800DD1D8[arg2];
                z = *directionZ;
                previousWidthX = x * angle;
                previousShade = particle->shade;
                previousWidthZ = z * angle;
                previousAlpha = (particle->active * particle->fade) >> 8;
                particle = (Game1CA420Particle *)(base + index * 0x24);
            }
            nextPosition = particle->position;
            angle = particle->angle;
            shade = particle->shade;
            texture = previousShade << 6;
            widthX = x * angle;
            widthZ = z * angle;
            alpha = (particle->active * particle->fade) >> 8;
            vertex->x = (s32)(position.x + previousWidthX);
            vertex->y = (s32)position.y;
            vertex->z = (s32)(position.z - previousWidthZ);
            vertex->s = texture;
            vertex->t = 0x7C0;
            vertex->r = 0xFF;
            vertex->g = 0xFF;
            vertex->b = 0xFF;
            vertex->a = previousAlpha;
            vertex->flags = 0;
            vertex++;
            vertex->x = (s32)(position.x - previousWidthX);
            vertex->y = (s32)position.y;
            vertex->z = (s32)(position.z + previousWidthZ);
            vertex->s = texture;
            vertex->t = 0;
            vertex->r = 0xFF;
            vertex->g = 0xFF;
            vertex->b = 0xFF;
            vertex->a = previousAlpha;
            vertex->flags = 0;
            vertex++;
            do {
                texture = shade << 6;
                vertex->x = (s32)(nextPosition.x + widthX);
                vertex->y = (s32)nextPosition.y;
                vertex->z = (s32)(nextPosition.z - widthZ);
                vertex->s = texture;
                vertex->t = 0x7C0;
                vertex->r = 0xFF;
                vertex->g = 0xFF;
                vertex->b = 0xFF;
                vertex->a = alpha;
                vertex->flags = 0;
                vertex++;
                vertex->x = (s32)(nextPosition.x - widthX);
                vertex->y = (s32)nextPosition.y;
                vertex->z = (s32)(nextPosition.z + widthZ);
                vertex->s = texture;
                vertex->t = 0;
                vertex->r = 0xFF;
                vertex->g = 0xFF;
                vertex->b = 0xFF;
                vertex->a = alpha;
                vertex->flags = 0;
                vertex++;
                {
                    Game1CA420Command *command = (Game1CA420Command *)commands;
                    commands += sizeof(Game1CA420Command);
                    command->first = 0x01004008;
                    command->second = (u32)(vertex - 4);
                }
                {
                    Game1CA420Command *command = (Game1CA420Command *)commands;
                    commands += sizeof(Game1CA420Command);
                    command->first = 0x05000204;
                    command->second = 0;
                }
                {
                    Game1CA420Command *command = (Game1CA420Command *)commands;
                    commands += sizeof(Game1CA420Command);
                    command->first = 0x05020604;
                    command->second = 0;
                }
                if (previousShade < shade) {
                    func_10022EC0(vertex, vertex - 2, 0x20);
                    vertex[-2].s -= 0x4000;
                    vertex++;
                    vertex[-2].s -= 0x4000;
                    vertex++;
                }
                last = index;
                index--;
                if (index < 0) {
                    index = arg0->capacity - 1;
                }
                if (last != arg0->head) {
                    previousShade = shade & 0xFF;
                    position = ((Game1CA420Particle *)(base + last * 0x24))->position;
                    particle = (Game1CA420Particle *)(base + index * 0x24);
                    nextPosition = particle->position;
                    angle = particle->angle;
                    widthX = *directionX * angle;
                    shade = particle->shade;
                    widthZ = *directionZ * angle;
                    alpha = (particle->active * particle->fade) >> 8;
                }
            } while (last != arg0->head);
        }
    }
    return (void *)commands;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519D9F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519D9F4.s")
void func_1519E1F4(void *arg0, void *arg1, u8 arg2) {
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    if (arg2 == 0) {
        if ((*(s32 *)((u8 *)temp_v0 + 0) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1519CFA0(arg0);
        }
    } else if (arg2 == 6) {
        if (*(u8 *)arg1 == *(u8 *)((u8 *)temp_v0 + 0x4C)) {
            func_1519CFA0(arg0);
        }
    } else if (arg2 == 7) {
        if ((*(s32 *)((u8 *)temp_v0 + 0) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1519CFA0(arg0);
        }
    } else if (arg2 == 0x2D) {
        arg0 = *(void **)arg1;
        temp_v1 = *(s32 *)temp_v0;
        if ((s32)arg0 == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        temp_v1 = ((s32 *)arg1)[1] ^ temp_v1;
        if (temp_v1 == 0) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32)arg0;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}

typedef struct Game1CA420TransformActor {
    u8 pad0[0x1D4];
    u8 *matrices;
} Game1CA420TransformActor;

typedef struct Game1CA420Transform {
    Game1CA420TransformActor *actor;
    u8 generation;
    u8 index;
    u8 flags;
    u8 pad7;
    f32 position[3];
} Game1CA420Transform;

void func_15143134(f32 *, f32 *, s32);

s32 func_1519E304(Game1CA420Transform *arg0, f32 *arg1,
                    f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 transformed[3];
    u8 *matrix;

    matrix = arg0->actor->matrices;
    if (matrix == 0) {
        return 0;
    }
    func_15143134(arg0->position, transformed, (s32)matrix + (arg0->index << 6));
    arg1[0] = ((transformed[0] - arg2) * arg5) + arg2;
    arg1[1] = ((transformed[1] - arg3) * arg5) + arg3;
    arg1[2] = ((transformed[2] - arg4) * arg5) + arg4;
    return 1;
}
void func_1519E688(void);
s32 func_1519D030(void *, s32, s16, u8, u8, s32);
s32 func_151491F4(s16, s8, s8, u8, u8, s32, u8, s32);

void func_1519E3BC(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    func_1519E688();
    func_1519D030(arg0, 3, 0x12C, 0, arg2, arg3);
    func_1519D030(arg0, 4, 0x12C, 0, arg2, arg3);
    func_151491F4(arg1, 6, -1, 1, 3, 0, arg2, arg3);
}
typedef struct Game1CA420Owner {
    s32 active;
    u8 pad4[0x37];
    u8 generation;
    u8 pad3C[0x48];
    u16 kind;
    u8 pad86[0x14E];
    void *matrices;
    u8 pad1D8[0x11C];
    void *links;
} Game1CA420Owner;

typedef struct Game1CA420OwnerLink {
    Game1CA420Owner *actor;
    u8 generation;
    u8 pad5[3];
    s32 value;
} Game1CA420OwnerLink;

typedef struct Game1CA420Effect {
    u8 pad0;
    u8 mode;
    u8 pad2[0xA];
    u8 strength;
    u8 flags;
    s16 timer;
    u8 pad10[0x18];
    Game1CA420OwnerLink link;
} Game1CA420Effect;

s32 func_1514ED3C(void *, s32, void **);
void func_1514EC1C(s32, s32, s32);

void func_1519E464(Game1CA420Effect *arg0) {
    struct {
        s32 result;
        u8 pad4[3];
        u8 remove;
        Game1CA420OwnerLink *link;
    } locals;

    locals.remove = 0;
    locals.link = &arg0->link;
    if (arg0->link.actor->active == 0) {
        locals.remove = 1;
    }
    if (locals.link->actor->generation != locals.link->generation) {
        locals.remove = 1;
    }
    if (locals.remove == 0 && locals.link->actor->matrices != 0) {
        locals.remove = 1;
        locals.result = func_1519D030(locals.link->actor, locals.link->value, arg0->timer,
                               arg0->flags & 1, arg0->strength, arg0->mode);
        if (locals.result != 0) {
            if (func_1514ED3C(locals.link->actor->links, (s32)arg0, 0) != 0) {
                func_1514EC1C(locals.result, (s32)locals.link->actor, 0x10);
            }
        }
    }
    if (locals.remove != 0) {
        arg0->timer = -1;
        arg0->flags |= 1;
    }
}
void func_1516972C(s32);

typedef struct Game1CA420Link {
    u8 *actor;
    u8 generation;
    u8 pad5[3];
    s32 value;
} Game1CA420Link;

typedef struct Game1CA420LinkedEffect {
    u8 pad0[0x28];
    Game1CA420Link link;
} Game1CA420LinkedEffect;

typedef union Game1CA420Event {
    Game1CA420Link removed;
    struct {
        u8 *first;
        u8 *second;
        u8 firstGeneration;
        u8 secondGeneration;
    } swapped;
} Game1CA420Event;

void func_1516972C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519E570 CURRENT (250) */
void func_1519E570(u8 *arg0, Game1CA420Event *arg1, u8 arg2) {
    Game1CA420Link *link;
    u8 *first;
    s32 actor;

    if (arg2 == 0) {
        link = (Game1CA420Link *)(arg0 + 0x28);
        if (arg1->removed.actor == link->actor ||
            arg1->removed.generation == link->generation) {
            func_1516972C((s32)arg0);
        }
    } else {
        link = (Game1CA420Link *)(arg0 + 0x28);
        if (arg2 == 0x2D) {
            actor = (s32)link->actor;
            first = arg1->swapped.first;
            if ((s32)first == actor) {
                link->actor = arg1->swapped.second;
                link->generation = arg1->swapped.secondGeneration;
            } else {
                actor = (s32)arg1->swapped.second ^ actor;
                if (actor == 0) {
                    link->actor = first;
                    link->generation = arg1->swapped.firstGeneration;
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519E570 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E570.s")

extern void func_1516972C(s32 arg0);

void func_1519E61C(s32 arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0) || (arg2 == 9)) {
        func_1516972C(arg0);
    }
}
void func_1519E65C(s32 arg0) {
    func_1519CF70(3);
    func_1519CF70(4);
}
void func_1519E688(void) {
    func_1519CF70(3);
    func_1519CF70(4);
    func_15147D64((u8 *)0, 9);
}
void func_1519E688(void);
void *func_10022EC0(void *, const void *, u32);
s32 func_151491F4(s16, s8, s8, u8, u8, s32, u8, s32);
extern s32 D_800E0920[1];

void func_1519E6BC(u8 *arg0) {
    Game1CA420Link link;
    s32 result;

    func_1519E688();
    if (D_800E0920[0] == 0) {
        link.value = 0;
        link.actor = arg0;
        link.generation = arg0[0x3B];
        result = func_151491F4(0x12C, -1, 9, 0, 4, 0xC, 0xFF, 0);
        if ((D_800E0920[0] = result) != 0) {
            func_10022EC0((u8 *)result + 0x28, &link, sizeof(link));
        }
    }
}

extern s32 D_800BE9E4;

void func_1519E754(Game1CA420Effect *arg0) {
    Game1CA420OwnerLink *link;
    u8 remove;

    remove = 0;
    link = &arg0->link;
    if (arg0->link.actor->active == 0) {
        remove = 1;
    }
    if (link->actor->generation != link->generation) {
        remove = 1;
    }
    if (remove == 0) {
        link->value += D_800BE9E4;
        if (link->actor->kind != 0x7C) {
            remove = 1;
            if (link->value > 200) {
                func_1519E3BC(link->actor, 0x12C, arg0->strength, arg0->mode);
            }
        }
    }
    if (remove != 0) {
        D_800E0920[0] = 0;
        arg0->timer = -1;
        arg0->flags |= 1;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519E818 CURRENT (520) */
void func_1519E818(u8 *arg0, Game1CA420Event *arg1, u8 arg2) {
    Game1CA420Link *link;
    u8 *first;
    u8 *actor;

    if (arg2 == 0) {
        link = (Game1CA420Link *)(arg0 + 0x28);
        if (arg1->removed.actor == link->actor ||
            arg1->removed.generation == link->generation) {
            func_1516972C((s32)arg0);
            D_800E0920[0] = 0;
        }
    } else {
        link = (Game1CA420Link *)(arg0 + 0x28);
        if (arg2 == 0x2D) {
        actor = link->actor;
        first = arg1->swapped.first;
        if (first == actor) {
            link->actor = arg1->swapped.second;
            link->generation = arg1->swapped.secondGeneration;
        } else if (actor == arg1->swapped.second) {
            link->actor = first;
            link->generation = arg1->swapped.firstGeneration;
        }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519E818 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E818.s")
/* Call context: func_1514933C: unique active project prototype */
/* Call context: func_1514EDF0: unique active project prototype */
void func_1514933C(s32);
void func_1514EDF0(s32, s32);
void func_15149368();

void func_1519E8CC(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x28));
    func_1514933C((s32) arg0);
}
void func_1519E8F8(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x28));
    func_15149368((s32) arg0);
}
/* Call context: func_1514933C: unique active project prototype */
void func_1514933C(s32);
extern s32 D_800E0920[1];

void func_1519E924(s32 arg0) {
    D_800E0920[0] = 0;
    func_1514933C(arg0);
}
void func_1519E948(void) {
    D_800E0920[0] = 0;
    func_15149368();
}
