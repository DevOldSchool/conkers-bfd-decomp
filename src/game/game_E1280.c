#include "types.h"

/*
 * Reviewed source unit: src/game/game_E1280.c
 * Boundary evidence: docs/evidence/game_raw_audio_owner_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B3F5C
 * - func_150B40E8
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
void func_151494E0(s8 *, s32);

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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B40E8 CURRENT (85) */
s32 func_150B40E8(GameE1280TimedObject *arg0) {
    GameE1280TimedState *state = arg0->state;
    GameE1280TimedEntry *entries = arg0->entries;
    GameE1280TimedEntry *entry;
    s32 index;
    s32 current;
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
                    current = arg0->tail + 1;
                    arg0->tail = current;
                    if (arg0->tail == arg0->capacity) {
                        arg0->tail = 0;
                    }
                    arg0->count--;
                } while (index != arg0->tail);
            }
        } while (index != arg0->tail);
    }
    if (arg0->count > 0) {
        entry = (GameE1280TimedEntry *)((u8 *)entries + arg0->tail * 0x24);
        arg0->output = entry->position;
    } else {
        arg0->output.x = 0.0f;
        arg0->output.y = 0.0f;
        arg0->output.z = 0.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B40E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B40E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B4294.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B4710.s")
void func_150B5060(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    *(u8 *)((u8 *)temp_v0 + 0x1C) = (u8) (*(u8 *)((u8 *)temp_v0 + 0x1C) | 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B5088.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B538C CURRENT (200) */
void func_150B538C(void *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 5) {
        func_150B5060(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B538C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B538C.s")
