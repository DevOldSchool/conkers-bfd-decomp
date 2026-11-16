#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1DF510.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_render_effect_lifecycles.md
 */

typedef struct Game1DF510EffectSlots {
    u8 pad0[0x10];
    void *effects[3];
    void *field_1C;
} Game1DF510EffectSlots;

typedef struct Game1DF510EffectOwner {
    u8 pad0[0x28];
    Game1DF510EffectSlots slots;
} Game1DF510EffectOwner;

void func_151B222C();

typedef struct {
    void *field_0;
    u8 field_4;
    u8 pad_5[3];
    s32 field_8;
    u8 field_C;
    s8 field_D;
    u8 pad_E[2];
    u8 field_10[0xC];
    s32 field_1C;
} Game1DF510Packet;

void func_100226F0(void *, s32);
void *func_10022EC0(void *, const void *, u32);
s32 func_15083E90(s32, void *);

void func_151B2060(void *arg0) {
    s32 id;
    Game1DF510Packet packet;
    u8 *object;

    if (arg0 != 0) {
        packet.field_0 = arg0;
        packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
        id = func_15083E90(1, arg0);
        packet.field_8 = id;
        packet.field_C = 1;
        packet.field_D = 0;
        func_100226F0(packet.field_10, 0xC);
        packet.field_1C = 0;
        object = func_151491F4(0x12C, -1, 0x16, 0, 0x12, 0x20, 0xFF, 1);
        if (object != 0) {
            func_10022EC0(object + 0x28, &packet, 0x20);
        }
    }
}
s32 func_151B22F4();
void func_151B2348();
void func_151B2690();

void func_151B2100(void *arg0) {
    u8 *temp_v1;
    u8 *temp_a1;
    u8 *temp_v0;
    u8 previous_state;
    s16 state;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x28);
    temp_a1 = *(u8 **)((u8 *)arg0 + 0x30);
    temp_v1 = (u8 *)arg0 + 0x28;
    if ((*(s32 *)temp_v0 == 0) || (temp_v0[4] == 0xFF) ||
        (temp_v1[4] != temp_v0[0x3B]) || (*(s32 *)temp_a1 == 0) ||
        (temp_a1[4] == 0xFF) || (temp_v1[0xC] != temp_a1[0x3B])) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        return;
    }
    previous_state = temp_v1[0xD];
    temp_v1[0xD] = func_151B22F4(arg0);
    if (previous_state != temp_v1[0xD]) {
        func_151B222C(arg0);
        state = temp_v1[0xD];
        if (state == 1) {
            func_151B2348(arg0);
            state = temp_v1[0xD];
        }
        if ((state == 2) || (state == 0)) {
            func_151B2690(arg0);
        }
    }
}
void func_151B220C() {
    func_151B222C();
}
void func_151B222C(Game1DF510EffectOwner *arg0) {
    u8 i = 0;
    Game1DF510EffectSlots *slots = &arg0->slots;
    void *effect;

    do {
        effect = slots->effects[i];
        if (effect != 0) {
            func_1516972C(effect);
        }
        i++;
    } while (i < 3);

    effect = slots->field_1C;
    if (effect != 0) {
        func_1516972C(effect);
    }
}

void func_151B229C(void *arg0) {
    func_151B220C(arg0);
    func_1514933C(arg0);
}
void func_151B22C8(void *arg0) {
    func_151B220C(arg0);
    func_15149368(arg0);
}
typedef struct {
    u8 pad_0[0x5C];
    s32 field_5C;
    u8 pad_60[5];
    u8 field_65;
} Game1DF510Entry;

typedef struct {
    u8 pad_0[0x28];
    u8 *field_28;
    u8 pad_2C[4];
    Game1DF510Entry *field_30;
} Game1DF510State;

extern u8 D_800CC2D0;

s32 func_151B22F4(Game1DF510State *arg0) {
    u8 *owner;
    Game1DF510Entry *entry;

    owner = arg0->field_28;
    entry = arg0->field_30;
    if ((entry->field_65 == ((owner - &D_800CC2D0) / 0x32C + 1)) && (entry->field_5C == 1)) {
        return 1;
    }
    return 2;
}

typedef struct Game1DF510Actor {
    u8 pad0[0x14];
    Vec3f position;
    u8 pad20[0x1B];
    u8 generation;
} Game1DF510Actor;

typedef struct Game1DF510Anchor {
    Game1DF510Actor *actor;
    u8 generation;
    u8 mode;
    u8 pad6[2];
    Vec3f offset;
} Game1DF510Anchor;

/* The raw copy spans are 0x30, 0x28 and 0x38 bytes. */
typedef struct Game1DF510Pair {
    Game1DF510Anchor first;
    Game1DF510Anchor second;
    Game1DF510EffectOwner *owner;
    u8 active;
    u8 pad2D[3];
} Game1DF510Pair;

typedef struct Game1DF510Line {
    Game1DF510Anchor anchor;
    Vec3f end;
    f32 radius;
    Game1DF510EffectOwner *owner;
} Game1DF510Line;

typedef struct Game1DF510Request {
    u8 flags;
    u8 pad1;
    s16 timer;
    Vec3f start;
    Vec3f end;
    s8 firstIndex;
    s8 secondIndex;
    s8 drawIndex;
    u8 pad1F;
    f32 radius;
    s8 callback;
    u8 pad25[3];
    f32 angle;
    f32 field2C;
    f32 field30;
    u8 state;
    u8 pad35[3];
} Game1DF510Request;

extern Vec3f D_800AA320;
extern Vec3f D_800AA32C;
extern Vec3f D_800AA368;
extern Vec3f D_800AA374;
extern f32 D_800AA388;
extern f32 D_800AA38C;

extern Vec3f D_800AA338, D_800AA344, D_800AA350, D_800AA35C;
extern f32 D_800AA380, D_800AA384;

void func_151B2348(void *arg0) {
    Game1DF510Actor *actor;
    Game1DF510Actor *other;
    Game1DF510EffectSlots *slots;
    Game1DF510Request request;
    Game1DF510Pair pair;

    actor = *(Game1DF510Actor **)((u8 *)arg0 + 0x30);
    other = *(Game1DF510Actor **)((u8 *)arg0 + 0x28);
    pair.owner = arg0;
    pair.active = 2;
    pair.first.actor = actor;
    pair.first.generation = actor->generation;
    pair.first.mode = 5;
    pair.first.offset = D_800AA350;
    pair.second.actor = actor;
    pair.second.generation = actor->generation;
    pair.second.mode = 10;
    pair.second.offset = D_800AA35C;
    request.state = 0;
    request.flags = 0;
    request.timer = 1000;
    request.start.x = actor->position.x;
    request.start.y = actor->position.y;
    request.start.z = actor->position.z;
    request.end.x = actor->position.x;
    request.end.y = actor->position.y;
    request.end.z = actor->position.z;
    request.firstIndex = 1;
    request.secondIndex = 1;
    request.drawIndex = 0;
    request.callback = 3;
    request.radius = 5.0f;
    request.angle = 80.0f;
    request.field2C = D_800AA380;
    request.field30 = D_800AA384;
    slots = &((Game1DF510EffectOwner *)arg0)->slots;
    slots->effects[2] = func_151B30B0(&request, 0.0015f, 0x30, 0xFF, 0);
    if (slots->effects[2] != NULL) {
        func_10022EC0((u8 *)slots->effects[2] + 0x150, &pair, 0x30U);
    }
    pair.active = 1;
    pair.first.actor = other;
    pair.first.generation = other->generation;
    pair.first.mode = 5;
    pair.first.offset = D_800AA320;
    pair.second.actor = actor;
    pair.second.generation = actor->generation;
    pair.second.mode = 5;
    pair.second.offset = D_800AA338;
    request.start.x = other->position.x;
    request.start.y = other->position.y;
    request.start.z = other->position.z;
    request.end.x = actor->position.x;
    request.end.y = actor->position.y;
    request.end.z = actor->position.z;
    request.drawIndex = 0;
    request.angle = 170.0f;
    slots->effects[1] = func_151B30B0(&request, 0.0015f, 0x30, 0xFF, 0);
    if (slots->effects[1] != NULL) {
        func_10022EC0((u8 *)slots->effects[1] + 0x150, &pair, 0x30U);
    }
    pair.active = 0;
    pair.first.actor = other;
    pair.first.generation = other->generation;
    pair.first.mode = 5;
    pair.first.offset = D_800AA32C;
    pair.second.actor = actor;
    pair.second.generation = actor->generation;
    pair.second.mode = 10;
    pair.second.offset = D_800AA344;
    request.start.x = other->position.x;
    request.start.y = other->position.y;
    request.start.z = other->position.z;
    request.end.x = actor->position.x;
    request.end.y = actor->position.y;
    request.end.z = actor->position.z;
    request.drawIndex = 0;
    slots->effects[0] = func_151B30B0(&request, 0.0015f, 0x30, 0xFF, 0);
    if (slots->effects[0] != NULL) {
        func_10022EC0((u8 *)slots->effects[0] + 0x150, &pair, 0x30U);
    }
}

void func_151B2690(void *arg0) {
    Game1DF510Actor *actor;
    Game1DF510EffectSlots *slots;
    Game1DF510Request request;
    Game1DF510Pair pair;
    Game1DF510Line line;

    actor = *(Game1DF510Actor **)((u8 *)arg0 + 0x28);
    pair.owner = arg0;
    pair.active = 1;
    pair.first.actor = actor;
    pair.first.generation = actor->generation;
    pair.first.mode = 5;
    pair.first.offset = D_800AA320;
    pair.second.actor = actor;
    pair.second.generation = actor->generation;
    pair.second.mode = 2;
    pair.second.offset = D_800AA368;
    request.state = 0;
    request.flags = 0;
    request.timer = 100;
    request.start.x = actor->position.x;
    request.start.y = actor->position.y;
    request.start.z = actor->position.z;
    request.end.x = actor->position.x;
    request.end.y = actor->position.y;
    request.end.z = actor->position.z;
    request.firstIndex = 1;
    request.secondIndex = 1;
    request.drawIndex = 1;
    request.callback = 3;
    request.radius = 5.0f;
    request.angle = 180.0f;
    request.field2C = D_800AA388;
    request.field30 = D_800AA38C;
    slots = &((Game1DF510EffectOwner *)arg0)->slots;
    slots->effects[1] = func_151B30B0(&request, 0.0015f, 0x30, 0xFF, 0);
    if (slots->effects[1] != NULL) {
        func_10022EC0((u8 *)slots->effects[1] + 0x150, &pair, 0x30U);
    }
    pair.active = 0;
    pair.first.offset = D_800AA32C;
    pair.second.offset = D_800AA374;
    request.drawIndex = 1;
    slots->effects[0] = func_151B30B0(&request, 0.0015f, 0x30, 0xFF, 0);
    if (slots->effects[0] != NULL) {
        func_10022EC0((u8 *)slots->effects[0] + 0x150, &pair, 0x30U);
    }
    line.anchor.actor = actor;
    line.anchor.generation = actor->generation;
    line.anchor.mode = 2;
    line.anchor.offset = D_800AA368;
    line.end = D_800AA374;
    line.radius = 5.0f;
    line.owner = arg0;
    slots->field_1C = func_15149130(0x12C, -1, -1, 0, 0, 0x13, 0x28, 0xFF, 1);
    if (slots->field_1C != NULL) {
        func_10022EC0((u8 *)slots->field_1C + 0x28, &line, 0x28U);
    }
}
