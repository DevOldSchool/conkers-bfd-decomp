#include "types.h"

/*
 * Reviewed source unit: src/game/game_10B7D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DE32C
 * - func_150DE458
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150DE320(s32 arg0) {

}
typedef struct {
    u8 bytes[8];
} Game10B7D0Lookup8;

void func_150A2864(s32, s32);
s32 func_150A32B4(s32, s32, s32, s32);
void *func_151149AC(u8, s32);
extern Game10B7D0Lookup8 D_80088950;
extern Game10B7D0Lookup8 D_80088958;
extern s32 D_800D3098;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DE32C CURRENT (1175) */
void func_150DE32C(s32 arg0, s32 arg1, s32 arg2) {
    u8 *id;
    void *object;
    Game10B7D0Lookup8 ids;
    Game10B7D0Lookup8 actions;
    s32 i;
    u8 action;

    ids = D_80088950;
    actions = D_80088958;
    i = 0;
    id = ids.bytes;
    do {
        if (func_150A32B4((*id * 0x34) + D_800D3098, arg0, arg1, arg2) != 0) {
            action = actions.bytes[i];
            if (action != 0) {
                object = func_151149AC(action, 1);
                *((u8 *) object + 0x73) = (*((u8 *) object + 0x73) & ~3) | 3;
            } else {
                func_150A2864(*id, 1);
            }
        }
        i++;
        id++;
    } while (i != 8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DE32C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B7D0/func_150DE32C.s")
typedef struct GameDE458State {
    volatile f32 rotation[3];
    u8 pad0C[4];
    s16 position[3];
    u8 pad16[0x26];
    s32 gravity;
    u8 pad40[0x14];
    u16 flags;
    u8 pad56[4];
    s16 velocity[3];
    f32 spin[3];
    u8 pad6C[2];
    u8 dead;
    u8 pad6F[4];
    u8 state;
    u8 pad74[8];
    s32 kind;
    u8 pad80[10];
    u8 timer;
} GameDE458State;

s32 func_1510D0EC(s32, s32 *, s32, s32);
void func_1510D874(s32, s32, s32, s32, s32);
extern s32 D_800BE9E4, D_80090204[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DE458 CURRENT (767) */
void func_150DE458(void *arg0) {
    GameDE458State *state = arg0;
    s32 size;
    f32 step, angle;
    f32 old0, old1, old2;
    s32 timer, result, first, second;
    s32 *cursor;

    if ((state->state & 3) == 3) {
        step = (f32)D_800BE9E4;
        old0 = state->rotation[0];
        state->rotation[0] = old0 + state->spin[0] * step;
        angle = state->rotation[0];
        if (angle < 0.0f) state->rotation[0] = angle + 360.0f;
        else if (angle >= 360.0f) state->rotation[0] = angle - 360.0f;
        old1 = state->rotation[1];
        state->rotation[1] = old1 + state->spin[1] * step;
        angle = state->rotation[1];
        if (angle < 0.0f) state->rotation[1] = angle + 360.0f;
        else if (angle >= 360.0f) state->rotation[1] = angle - 360.0f;
        old2 = state->rotation[2];
        state->rotation[2] = old2 + state->spin[2] * step;
        angle = state->rotation[2];
        if (angle < 0.0f) state->rotation[2] = angle + 360.0f;
        else if (angle >= 360.0f) state->rotation[2] = angle - 360.0f;
        timer = state->timer;
        state->velocity[1] = (s16)((u32)state->velocity[1] - (u32)state->gravity * (u32)D_800BE9E4);
        state->position[0] = (s16)((u32)state->position[0] + (u32)state->velocity[0] * (u32)D_800BE9E4);
        state->position[1] = (s16)((u32)state->position[1] + (u32)state->velocity[1] * (u32)D_800BE9E4);
        state->position[2] = (s16)((u32)state->position[2] + (u32)state->velocity[2] * (u32)D_800BE9E4);
        timer = (s32)((u32)timer - (u32)D_800BE9E4);
        if (timer > 0) state->timer = timer;
        else state->dead = 1;
    }
    if ((state->flags & 0xFFFF7FFF) == 12) {
        first = 4;
        cursor = D_80090204 + ((u32)state->kind << 1);
        second = 5;
        do {
            result = func_1510D0EC(*cursor, &size, 3, 0);
            func_1510D874((s32)arg0, result, (s32)((u32)size + (u32)result - 0x200), first, second);
            second += 2;
            cursor++;
            first += 2;
        } while (second != 9);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DE458 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B7D0/func_150DE458.s")
f32 func_15048A40(s32);                             /* extern */
extern f32 D_800A0D48;
extern f32 D_800A0D4C;
extern f32 D_800A0D50;
extern f32 D_800A0D54;
extern s32 D_800BE9E4;

void func_150DE6D8(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((func_15048A40(((s32) *(s32 *)((u8 *)arg0 + 0x7C) >> 3) & 0xFF) * D_800A0D48) + D_800A0D4C);
    *(f32 *)((u8 *)arg0 + 0) = (f32) (func_15048A40(((s32) *(s32 *)((u8 *)arg0 + 0x80) >> 3) & 0xFF) * D_800A0D50);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (func_15048A40(((s32) *(s32 *)((u8 *)arg0 + 0x84) >> 3) & 0xFF) * D_800A0D54);
    *(s32 *)((u8 *)arg0 + 0x7C) = (s32) (*(s32 *)((u8 *)arg0 + 0x7C) + (D_800BE9E4 * 0xC));
    *(s32 *)((u8 *)arg0 + 0x80) = (s32) (*(s32 *)((u8 *)arg0 + 0x80) + (D_800BE9E4 * 0x10));
    *(s32 *)((u8 *)arg0 + 0x84) = (s32) (*(s32 *)((u8 *)arg0 + 0x84) + (D_800BE9E4 * 0x18));
}
