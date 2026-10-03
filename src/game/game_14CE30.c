#include "types.h"

/*
 * Reviewed source unit: src/game/game_14CE30.c
 * Boundary evidence: docs/evidence/game_raw_record_transform_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511F990
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800DBFC0;

void func_1511F980(void) {
    D_800DBFC0 = 0;
}
typedef struct Game14CE30Actor {
    u8 pad00[4];
    f32 value04;
    u8 pad08[0x34];
    s32 packed3C;
    u8 pad40[0x33];
    u8 flags73;
} Game14CE30Actor;

typedef struct Game14CE30CacheEntry {
    Game14CE30Actor *actor;
    s32 initial_group;
} Game14CE30CacheEntry;

extern Game14CE30CacheEntry D_800DBFC8[4];
extern void *D_800CC5EC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511F990 CURRENT (370) */
void func_1511F990(Game14CE30Actor *actor, s32 initial_mode) {
    s32 group;
    s32 mode;
    s32 flag;
    s32 added;
    s32 index;
    s32 i;
    s32 other_mode;

    group = (s8)(actor->packed3C >> 16);
    mode = actor->flags73 & 3;
    flag = actor->flags73 & 4;
    added = 0;
    for (index = 0; index < D_800DBFC0; index++) {
        if (D_800DBFC8[index].actor == actor) {
            break;
        }
    }
    if (index == D_800DBFC0) {
        if (index >= 4) {
            return;
        }
        D_800DBFC8[index].actor = actor;
        D_800DBFC8[index].initial_group = group;
        D_800DBFC0++;
        added = 1;
    }
    if (group >= 0) {
        if (added) {
            if (group == ((u8 *)D_800CC5EC)[0x11B]) {
                if (initial_mode == 0) {
                    if (mode != 0 && mode != 1) {
                        mode = 1;
                    }
                    actor->value04 = (f32)((s32)((u32)actor->packed3C << 22) >> 22);
                } else if (initial_mode == 1) {
                    mode = 3;
                } else if (initial_mode == 2) {
                    mode = 2;
                } else if (initial_mode == 3) {
                    if (mode != 0 && mode != 1) {
                        if (flag != 0) {
                            mode = 1;
                        }
                    } else if (flag == 0) {
                        mode = 3;
                    }
                    actor->value04 = (f32)((s32)((u32)actor->packed3C << 22) >> 22);
                }
            } else if (initial_mode == 0 || initial_mode == 2 || initial_mode == 3) {
                if (initial_mode != 3 || flag != 0) {
                    mode = 0;
                } else {
                    mode = 3;
                }
            }
        } else if (mode == 1 || mode == 2) {
            for (i = 0; i < D_800DBFC0; i++) {
                if (i != index && D_800DBFC8[i].initial_group == group &&
                    (flag != 0 || !(D_800DBFC8[i].actor->flags73 & 4))) {
                    other_mode = D_800DBFC8[i].actor->flags73 & 3;
                    if (!(other_mode == 3 && mode == 2) &&
                        !(other_mode == 0 && mode == 1)) {
                        D_800DBFC8[i].actor->flags73 &= ~3;
                        D_800DBFC8[i].actor->flags73 |= mode;
                    }
                }
            }
        }
    }
    actor->flags73 &= ~3;
    actor->flags73 |= mode;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511F990 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14CE30/func_1511F990.s")
