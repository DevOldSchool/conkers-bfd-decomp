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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DF920 CURRENT (1696) */
void func_150DF920(s32 arg0) {
    Game10CD70Actor *actor;
    Game10CD70Command *commands, *command;
    u8 *scroll;
    s32 actorId, slot, iteration, oldSlot;
    s32 active, index, opcode, vertical;
    f32 x, y, z;
    u32 word;
    u8 nextScroll;

    if (arg0 == 0) {
        func_151749A0(5, 4);
        actorId = 6;
        slot = 3;
        iteration = 0;
        do {
            actor = func_15083E90(actorId);
            actorId = 7;
            if (actor != 0) {
                func_150A2864(slot, 0);
                oldSlot = slot;
                slot = 4;
                x = actor->x;
                y = actor->y + 200.0f;
                z = actor->z;
                func_150A3444(oldSlot, (s16)(s32)x, (s16)(s32)y, (s16)(s32)z);
            } else {
                oldSlot = slot;
                slot = 4;
                func_150A2864(oldSlot, 1);
            }
            iteration++;
        } while (iteration < 2);
        commands = D_800B0E00;
        scroll = D_800D9950;
        iteration = 0;
        do {
            index = -1;
            active = func_150DF8C0(iteration);
            if (active != 0) {
                opcode = *scroll;
                if (opcode < 0x60) {
                    nextScroll = opcode + D_800BE9E4;
                    *scroll = nextScroll;
                    if (nextScroll >= 0x61) {
                        *scroll = 0x60;
                    }
                }
            } else {
                *scroll = 0;
            }
search_header:
            index++;
            opcode = *(s8 *)&commands[index].first;
            if (opcode != -3 && opcode != -0x21) {
search_header_tail:
                index++;
                opcode = *(s8 *)&commands[index].first;
                if (opcode != -3 && opcode != -0x21) {
                    goto search_header_tail;
                }
            }
            if (opcode == -0x21) {
                index = -1;
            } else if (((u32)iteration << 24) + 0x02000000U != commands[index].second) {
                goto search_header;
            }
            iteration++;
            if (index != -1) {
                if (*(s8 *)&commands[index].first != -0xE) {
                    do {
                        index++;
                    } while (*(s8 *)&commands[index].first != -0xE);
                }
                if (index != -1) {
                    command = &commands[index];
                    if (active != 0) {
                        word = command->first;
                        vertical = (word >> 12) & 0xFFF;
                        opcode = (word & 0xFFF) + ((s32)*scroll / 16) * D_800BE9E4;
                    } else {
                        opcode = 2;
                        vertical = 2;
                    }
                    command->first = ((vertical & 0xFFF) << 12) | 0xF2000000U | (opcode & 0xFFF);
                }
            }
            scroll++;
        } while (iteration != 3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DF920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10CD70/func_150DF920.s")
