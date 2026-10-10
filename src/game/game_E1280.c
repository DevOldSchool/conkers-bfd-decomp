#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_E1280.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_audio_owner_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B3F5C
 * - func_150B4294
 * - func_150B4710
 * - func_150B5088
 * - func_150B538C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameE1280State {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    f32 z;
} GameE1280State;

void func_1000FC18(s32, s16, s16, s16, s32);
void func_151478F4(s32);
void func_15147D64(s32, s32);

void func_150B3DD0(void) {
    struct {
        s8 value;
        u8 pad[3];
    } packet;

    func_15147D64(0, 5);
    packet.value = 0;
    func_151494E0(&packet.value, 0x18);
    packet.value = 2;
    func_151494E0(&packet.value, 0x18);
    packet.value = 4;
    func_151494E0(&packet.value, 0x18);
    packet.value = 1;
    func_151494E0(&packet.value, 0x18);
    packet.value = 3;
    func_151494E0(&packet.value, 0x18);
    packet.value = 5;
    func_151494E0(&packet.value, 0x18);
}

void func_150B3E74(GameE1280State *arg0) {
    func_1000FC18(0x221, (s16)(s32)arg0->x, (s16)(s32)arg0->y,
                  (s16)(s32)arg0->z, 0xFA0);
    func_151478F4((s32)arg0);
}
void func_15147928(s32);

void func_150B3EE8(GameE1280State *arg0) {
    func_1000FC18(0x221, (s16)(s32)arg0->x, (s16)(s32)arg0->y,
                  (s16)(s32)arg0->z, 0xFA0);
    func_15147928((s32)arg0);
}
void *func_10022EC0(void *, const void *, u32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
u32 func_150ADA20(void);
extern u8 D_1000EF40[];

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} GameE1280Vec3;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B3F5C CURRENT (366) */
void *func_150B3F5C(u8 *arg0, f32 *volatile arg1, s32 arg2) {
    struct {
        void *result;
        struct {
            u8 copied[0x40];
            f32 combined_copy;
            f32 zero_a;
            u8 flag_a;
            u8 pad_49[3];
            f32 combined;
            u8 flag_b;
            u8 pad_51[3];
            f32 zero_b;
            GameE1280Vec3 position;
            s16 mode;
            s16 subtype;
            s32 number;
            u8 pad_6c;
            u8 color;
            u8 pad_6e[2];
            s32 trailing_pad;
        } packet;
    } locals;
    u32 sound_flags;
    f32 first;
    f32 second;
    f32 *audio_position;

    func_10022EC0(&locals.packet, arg0, 0x40);
    locals.packet.flag_a = 0;
    locals.packet.subtype = 2;
    locals.packet.mode = 0x1F4;
    locals.packet.zero_a = 0.0f;
    locals.packet.color = (u8)*(s16 *)((u8 *)&arg2 + 2);
    second = *(f32 *)(arg0 + 0x18);
    first = *(f32 *)(arg0 + 0x14);
    locals.packet.flag_b = 0;
    locals.packet.combined = first + second;
    locals.packet.zero_b = 0.0f;
    locals.packet.combined_copy = locals.packet.combined;
    locals.packet.position = *(GameE1280Vec3 *)arg1;
    locals.packet.number = 9;
    locals.result = func_15147A80(&locals.packet.position, (void *)0x58, 0x24,
                            7, 7, 7, 0, 0, 0, 0xFF, 1);
    if (locals.result != 0) {
        sound_flags = func_150ADA20() & 0x40;
        audio_position = arg1;
        func_1000FA64(0x221, (s16)(s32)audio_position[0], (s16)(s32)audio_position[1],
                      (s16)(s32)audio_position[2], 0x61A8, 0xFA0, 0x258,
                      D_1000EF40, 0, 0, 8, sound_flags);
        func_10022EC0(*(void **)((u8 *)locals.result + 0x98), &locals.packet, 0x58);
    }
    return locals.result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B3F5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B3F5C.s")
typedef struct GameE1280TimedEntry {
    GameE1280Vec3 position;
    f32 velocityC;
    f32 velocity10;
    f32 velocity14;
    f32 velocity18;
    s16 state1C;
    s16 life1E;
    u8 pad20[4];
} GameE1280TimedEntry;

typedef struct GameE1280TimedState {
    u8 pad0[0xC];
    f32 speedC;
    u8 pad10[0xC];
    u8 flags1C;
    u8 pad1D[0xB];
    f32 speed28;
} GameE1280TimedState;

typedef struct GameE1280TimedObject {
    u8 pad0[0x25];
    u8 capacity;
    u8 pad26[6];
    s8 count;
    s8 tail;
    s8 head;
    u8 pad2F[0x25];
    GameE1280Vec3 output;
    u8 pad60[0x34];
    GameE1280TimedEntry *entries;
    GameE1280TimedState *state;
} GameE1280TimedObject;

extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

s32 func_150B40E8(GameE1280TimedObject *arg0) {
    GameE1280TimedState *state = arg0->state;
    GameE1280TimedEntry *entries = arg0->entries;
    GameE1280TimedEntry *entry;
    s32 index;
    s32 expired;

    if (arg0->count < 2 && (state->flags1C & 1)) {
        return 0;
    }
    index = arg0->head;
    if (index != arg0->tail) {
        do {
            index--;
            expired = 0;
            if (index < 0) {
                index = arg0->capacity - 1;
            }
            entry = (GameE1280TimedEntry *)((u8 *)entries + index * 0x24);
            entry->state1C = 0xFF;
            entry->life1E -= D_800BE9E4;
            if (entry->life1E < 0) {
                expired = 1;
            }
            entry->velocity10 += state->speedC * D_800BE9A4;
            entry->position.x += entry->velocityC * D_800BE9A4;
            entry->position.y += entry->velocity10 * D_800BE9A4;
            entry->position.z += entry->velocity14 * D_800BE9A4;
            entry->velocity18 += state->speed28 * D_800BE9A4;
            if (expired != 0 && index != arg0->tail) {
                do {
                    arg0->tail = arg0->tail + 1;
                    if (arg0->tail == arg0->capacity) {
                        arg0->tail = 0;
                    }
                    arg0->count--;
                } while (index != arg0->tail);
            }
        } while (index != arg0->tail);
    }
    if (arg0->count > 0) {
        arg0->output = ((GameE1280TimedEntry *)((u8 *)entries + arg0->tail * 0x24))->position;
    } else {
        arg0->output.x = 0.0f;
        arg0->output.y = 0.0f;
        arg0->output.z = 0.0f;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B4294.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B4710.s")
void func_150B5060(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    *(u8 *)((u8 *)temp_v0 + 0x1C) = (u8) (*(u8 *)((u8 *)temp_v0 + 0x1C) | 1);
}
f32 func_150ADA68(void);
void *func_15147DA0(void *, void *, s32, s32, s32, s32, s32, s32, s32,
                   s32, s32, void *, s32, u8, s32);
extern u8 D_8009FBF0[];

typedef struct GameE1280TrailHeader {
    GameE1280Vec3 position;
    s16 life;
    u16 flags;
    s32 kind;
    u8 unused14;
    u8 capacity;
    u8 unused16[6];
} GameE1280TrailHeader;

typedef struct GameE1280TrailParameters {
    f32 width;
    GameE1280Vec3 velocity;
    f32 gravity;
    u8 unused14[4];
    u8 flags;
    u8 texture;
    u8 color;
    u8 alpha;
    u8 unused1C[4];
} GameE1280TrailParameters;

typedef struct GameE1280TrailStyle {
    s32 mode;
    s32 first;
    s32 second;
    s32 texture;
    s32 scale;
    s32 primary;
    s32 secondary;
    s8 colorMode;
    s8 alphaMode;
    u8 padding[2];
} GameE1280TrailStyle;

typedef struct GameE1280TrailPreset {
    f32 radius;
    f32 speed;
    f32 speedRange;
    f32 width;
    f32 widthRange;
    f32 gravity;
    f32 gravityRange;
    s16 life;
    s16 lifeRange;
    s16 capacity;
    s16 capacityRange;
} GameE1280TrailPreset;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B5088 CURRENT (3487) */
void func_150B5088(void *arg0) {
    GameE1280TrailStyle style;
    GameE1280TrailHeader header;
    GameE1280TrailParameters parameters;
    f32 z;
    f32 speed;
    f32 cosine1;
    f32 sine1;
    f32 cosine2;
    f32 x;
    f32 y;
    register f32 radius;
    register f32 horizontal;
    register f32 gravity;
    register s32 angle1;
    register s32 angle2;
    GameE1280TrailPreset *preset;
    u8 *state;

    state = *(u8 **)((u8 *)arg0 + 0x98);
    preset = (GameE1280TrailPreset *)(D_8009FBF0 + state[0x38] * 0x24);
    style.mode = 0;
    style.first = 1;
    style.second = 0x160600;
    style.texture = 3;
    style.scale = 0x10;
    style.primary = 0x80;
    style.secondary = 0x20;
    style.colorMode = 0;
    style.alphaMode = 9;
    header.flags = 1;
    parameters.texture = 6;
    parameters.flags = 8;
    parameters.color = state[0x24];
    parameters.alpha = (s8)*(s16 *)(state + 0x26);
    header.position = *(GameE1280Vec3 *)((u8 *)arg0 + 0x10);
    do {
        speed = func_150ADA68() * preset->speedRange + preset->speed;
        angle1 = func_150ADA20();
        angle1 &= 0xFF;
        angle2 = func_150ADA20();
        angle2 &= 0xFF;
        cosine1 = func_151423D8((angle1 - 0x40) & 0xFF);
        sine1 = func_151423D8(angle1 & 0xFF);
        cosine2 = func_151423D8((angle2 - 0x40) & 0xFF);
        horizontal = func_151423D8(angle2 & 0xFF);
        radius = preset->radius;
        horizontal = radius * horizontal;
        x = *(f32 *)(state + 0) + horizontal * cosine1;
        y = *(f32 *)(state + 4) - radius * cosine2;
        z = *(f32 *)(state + 8) + horizontal * sine1;
        header.capacity = func_150ADA20() % (u32)(preset->capacityRange + 1) + preset->capacity;
        header.life = func_150ADA20() % (u32)(preset->lifeRange + 1) + preset->life;
        parameters.width = func_150ADA68() * preset->widthRange + preset->width;
        gravity = func_150ADA68() * preset->gravityRange + preset->gravity;
        parameters.velocity.x = speed * x;
        parameters.gravity = gravity;
        parameters.velocity.y = speed * y;
        parameters.velocity.z = speed * z;
        func_15147DA0(&header, &parameters, 0, 1, 7, 0, 0, 0, 0, 0, 0,
                     &style, 0, *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
        *(f32 *)(state + 0x54) -= 1.0f;
    } while (*(f32 *)(state + 0x54) > 1.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B5088 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B5088.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B538C CURRENT (200) */
void func_150B538C(void *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 5) {
        func_150B5060(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B538C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B538C.s")
