#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1E26F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B5328
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_15083E90(u8);
extern f32 D_800AA418;

s32 func_151B5240(s16 arg0, u8 arg1, s32 arg2) {
    s32 temp_v0;
    f32 temp_fv0;
    u8 packet[0x5A8];

    packet[0x584] = 0x17;
    packet[0x58C] = 0x16;
    *(s32 *)(packet + 0x580) = func_15083E90(0x17);
    *(s32 *)(packet + 0x588) = func_15083E90(packet[0x58C]);
    temp_fv0 = 250.0f;
    *(f32 *)(packet + 0x598) = temp_fv0;
    *(f32 *)(packet + 0x590) = 18.0f;
    *(f32 *)(packet + 0x594) = 0.0f;
    *(f32 *)(packet + 0x5A0) = D_800AA418;
    *(f32 *)(packet + 0x59C) = 1.0f / temp_fv0;
    temp_v0 = func_15149130(arg0, -1, -1, 1, 1, 0x15, 0x5A8, arg1, arg2);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), packet, 0x5A8);
    }
    return temp_v0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E26F0/func_151B5328.s")
typedef struct {
    s32 first;
    s32 second;
    u8 firstFlag;
    u8 secondFlag;
} Game1E26F0Pair;

typedef struct {
    u8 pad0[0x580];
    s32 first;
    u8 firstFlag;
    u8 pad585[3];
    s32 second;
    u8 secondFlag;
} Game1E26F0State;

void func_151B5A9C(u8 *arg0, void *arg1, u8 arg2) {
    Game1E26F0State *state = (Game1E26F0State *)(arg0 + 0x28);

    if (arg2 == 0x2D) {
        Game1E26F0Pair *pair = arg1;

        if (state->first == pair->first) {
            state->first = pair->second;
            state->firstFlag = pair->secondFlag;
        } else if (state->first == pair->second) {
            state->first = pair->first;
            state->firstFlag = pair->firstFlag;
        }
        if (state->second == pair->first) {
            state->second = pair->second;
            state->secondFlag = pair->secondFlag;
        } else if (state->second == pair->second) {
            state->second = pair->first;
            state->secondFlag = pair->firstFlag;
        }
    } else if (arg2 == 0) {
        s32 current = *(s32 *)arg1;

        if (current == state->first || current == state->second ||
            state->firstFlag == ((u8 *)arg1)[4] || state->secondFlag == ((u8 *)arg1)[4]) {
            func_1516972C(arg0);
        }
    }
}
