#include "types.h"

/*
 * Reviewed source unit: src/game/game_10CD70.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DF920
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game10CD70Indices {
    u8 values[3];
} Game10CD70Indices;

typedef struct Game10CD70Record {
    u8 pad0[0x14];
    u8 active;
    u8 pad15[0x1F];
} Game10CD70Record;

extern Game10CD70Indices D_80088984;
extern Game10CD70Record *D_800D3098;

s32 func_150DF8C0(s32 arg0) {
    Game10CD70Indices indices = D_80088984;

    if (D_800D3098[indices.values[arg0]].active != 0) {
        return 1;
    }
    return 0;
}

typedef struct Game10CD70Actor {
    u8 pad0[0x14];
    f32 x, y, z;
} Game10CD70Actor;
typedef struct Game10CD70Command { u32 first, second; } Game10CD70Command;

void *func_15083E90(u8);
void func_150A2864(s32, s32);
void func_150A3444(s32, s16, s16, s16);
void func_151749A0(s32, s32);
extern Game10CD70Command *D_800B0E00;
extern s32 D_800BE9E4;
extern u8 D_800D9950[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DF920 CURRENT (5) */
void func_150DF920(s32 arg0) {
    Game10CD70Actor *actor;
    s32 actorId;
    s32 slot;
    s32 oldSlot;
    s32 iteration;
    f32 x;
    f32 y;
    f32 z;
    s32 active;
    Game10CD70Command *commands;
    s32 index;
    s32 opcode;
    s32 vertical;
    u8 *scroll;

    if (arg0 == 0) {
        func_151749A0(5, 4);
        actorId = 6;
        slot = 3;
        for (iteration = 0; iteration < 2; iteration++) {
            actor = func_15083E90(actorId);
            actorId = 7;
            if (actor != NULL) {
                func_150A2864(slot, 0);
                oldSlot = slot;
                slot = 4;
                x = actor->x;
                y = actor->y + 200.0f;
                z = actor->z;
                func_150A3444(oldSlot, x, y, z);
            } else {
                oldSlot = slot;
                slot = 4;
                func_150A2864(oldSlot, 1);
            }
        }
        commands = D_800B0E00;
        for (iteration = 0, scroll = D_800D9950; iteration != 3; iteration++, scroll++) {
            active = func_150DF8C0(iteration);
            index = -1;
            if (active != 0) {
                if (*scroll < 0x60) {
                    *scroll += D_800BE9E4;
                    if (*scroll > 0x60) {
                        *scroll = 0x60;
                    }
                }
            } else {
                *scroll = 0;
            }
            do {
                index++;
                while (*(s8 *)&commands[index].first != -3 && *(s8 *)&commands[index].first != -0x21) {
                    index++;
                }
                if (*(s8 *)&commands[index].first == -0x21) {
                    index = -1;
                    break;
                }
            } while (commands[index].second != (iteration << 24) + 0x02000000);
            if (index != -1) {
                opcode = *(s8 *)&commands[index].first;
                while (opcode != -0xE) {
                    index++;
                    opcode = *(s8 *)&commands[index].first;
                }
            }
            if (index != -1) {
                if (active != 0) {
                    opcode = commands[index].first & 0xFFF;
                    vertical = (commands[index].first >> 12) & 0xFFF;
                    opcode += (*scroll / 16) * D_800BE9E4;
                } else {
                    opcode = 2;
                    vertical = 2;
                }
                commands[index].first = ((vertical & 0xFFF) << 12) | 0xF2000000 | (opcode & 0xFFF);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DF920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10CD70/func_150DF920.s")
