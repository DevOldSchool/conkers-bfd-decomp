#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DF510.c
 * Boundary evidence: docs/evidence/game_raw_render_effect_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B2100
 * - func_151B22F4
 * - func_151B2348
 * - func_151B2690
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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

void func_1516972C(void *);
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
void func_10022EC0(s32, void *, s32);
s32 func_15083E90(s32, void *);
s32 func_151491F4(s32, s32, s32, s32, s32, s32, s32, s32);

void func_151B2060(void *arg0) {
    struct {
        Game1DF510Packet packet;
        s32 padding;
    } frame;
    s32 object;

    if (arg0 != 0) {
        frame.packet.field_0 = arg0;
        frame.packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
        frame.packet.field_8 = func_15083E90(1, arg0);
        frame.packet.field_C = 1;
        frame.packet.field_D = 0;
        func_100226F0(frame.packet.field_10, 0xC);
        frame.packet.field_1C = 0;
        object = func_151491F4(0x12C, -1, 0x16, 0, 0x12, 0x20, 0xFF, 1);
        if (object != 0) {
            func_10022EC0(object + 0x28, &frame.packet, 0x20);
        }
    }
}
s32 func_151B22F4();
void func_151B2348();
void func_151B2690();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B2100 CURRENT (148) */
void func_151B2100(void *arg0) {
    u8 sp2B;
    u8 *temp_v1;
    u8 *temp_a1;
    u8 *temp_v0;
    u8 temp_v0_2;
    u8 var_v0;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x28);
    temp_a1 = *(u8 **)((u8 *)arg0 + 0x30);
    temp_v1 = (u8 *)arg0 + 0x28;
    if ((*(s32 *)temp_v0 == 0) || (temp_v0[4] == 0xFF) ||
        (temp_v1[4] != temp_v0[0x3B]) || (*(s32 *)temp_a1 == 0) ||
        (temp_a1[4] == 0xFF) || (temp_v1[0xC] != temp_a1[0x3B])) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        return;
    }
    sp2B = temp_v1[0xD];
    temp_v0_2 = func_151B22F4(arg0);
    temp_v1[0xD] = temp_v0_2;
    if (sp2B != temp_v0_2) {
        func_151B222C(arg0);
        var_v0 = temp_v1[0xD];
        if (var_v0 == 1) {
            func_151B2348(arg0);
            var_v0 = temp_v1[0xD];
        }
        if ((var_v0 == 2) || (var_v0 == 0)) {
            func_151B2690(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B2100 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2100.s")
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
void func_1514933C(s32);
void func_15149368(s32);

void func_151B229C(s32 arg0) {
    func_151B220C(arg0);
    func_1514933C(arg0);
}
void func_151B22C8(s32 arg0) {
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B22F4 CURRENT (885) */
s32 func_151B22F4(Game1DF510State *arg0) {
    Game1DF510Entry *temp_v1;

    temp_v1 = arg0->field_30;
    if (((((arg0->field_28 - &D_800CC2D0) / 0x32C) + 1) == temp_v1->field_65) && (temp_v1->field_5C == 1)) {
        return 1;
    }
    return 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B22F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B22F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2348.s")
typedef struct Game1DF510Vector {
    f32 x, y, z;
} Game1DF510Vector;

typedef struct Game1DF510Actor {
    u8 pad0[0x14];
    Game1DF510Vector position;
    u8 pad20[0x1B];
    u8 generation;
} Game1DF510Actor;

typedef struct Game1DF510Anchor {
    Game1DF510Actor *actor;
    u8 generation;
    u8 mode;
    u8 pad6[2];
    Game1DF510Vector offset;
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
    Game1DF510Vector end;
    f32 radius;
    Game1DF510EffectOwner *owner;
} Game1DF510Line;

typedef struct Game1DF510Request {
    u8 flags;
    u8 pad1;
    s16 timer;
    Game1DF510Vector start;
    Game1DF510Vector end;
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

u8 *func_151B30B0(void *, f32, s32, u8, s32);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern Game1DF510Vector D_800AA320;
extern Game1DF510Vector D_800AA32C;
extern Game1DF510Vector D_800AA368;
extern Game1DF510Vector D_800AA374;
extern f32 D_800AA388;
extern f32 D_800AA38C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B2690 CURRENT (4223) */
void func_151B2690(Game1DF510EffectOwner *arg0) {
    struct {
        Game1DF510Line line;
        Game1DF510Pair pair;
        Game1DF510Request request;
    } packets;
    Game1DF510Actor *actor;
    register u8 *cursor;
    u8 *effect;
    s32 lineEffect;

    cursor = (u8 *) arg0;
    actor = *(Game1DF510Actor **) (cursor + 0x28);
    packets.pair.owner = (Game1DF510EffectOwner *) cursor;
    packets.pair.active = 1;
    packets.pair.first.actor = actor;
    packets.pair.first.generation = actor->generation;
    packets.pair.first.mode = 5;
    packets.pair.first.offset = D_800AA320;
    packets.pair.second.actor = actor;
    packets.pair.second.generation = actor->generation;
    packets.pair.second.mode = 2;
    packets.pair.second.offset = D_800AA368;
    packets.request.state = 0;
    packets.request.flags = 0;
    packets.request.timer = 100;
    packets.request.start.x = actor->position.x;
    packets.request.radius = 5.0f;
    packets.request.start.y = actor->position.y;
    packets.request.angle = 180.0f;
    packets.request.start.z = actor->position.z;
    packets.request.field2C = D_800AA388;
    packets.request.end.x = actor->position.x;
    packets.request.field30 = D_800AA38C;
    packets.request.end.y = actor->position.y;
    packets.request.end.z = actor->position.z;
    packets.request.firstIndex = 1;
    packets.request.secondIndex = 1;
    packets.request.drawIndex = 1;
    packets.request.callback = 3;
    effect = func_151B30B0(&packets.request, 0.0015f, 0x30, 0xFF, 0);
    cursor += 0x28;
    ((Game1DF510EffectSlots *) cursor)->effects[1] = effect;
    if (effect != 0) {
        func_10022EC0((s32) (effect + 0x150), &packets.pair, 0x30);
    }
    packets.pair.active = 0;
    packets.pair.first.offset = D_800AA32C;
    packets.pair.second.offset = D_800AA374;
    packets.request.drawIndex = 1;
    effect = func_151B30B0(&packets.request, 0.0015f, 0x30, 0xFF, 0);
    ((Game1DF510EffectSlots *) cursor)->effects[0] = effect;
    if (effect != 0) {
        func_10022EC0((s32) (effect + 0x150), &packets.pair, 0x30);
    }
    packets.line.anchor.actor = actor;
    packets.line.anchor.generation = actor->generation;
    packets.line.anchor.mode = 2;
    packets.line.anchor.offset = D_800AA368;
    packets.line.end = D_800AA374;
    packets.line.radius = 5.0f;
    packets.line.owner = arg0;
    lineEffect = func_15149130(0x12C, -1, -1, 0, 0, 0x13, 0x28, 0xFF, 1);
    ((Game1DF510EffectSlots *) cursor)->field_1C = (void *) lineEffect;
    if (lineEffect != 0) {
        func_10022EC0(lineEffect + 0x28, &packets.line, 0x28);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B2690 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2690.s")
