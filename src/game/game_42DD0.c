#include "types.h"

/*
 * Reviewed source unit: src/game/game_42DD0.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15015920
 * - func_15015A38
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game42DD0Range {
    u8 *start;
    u8 *end;
} Game42DD0Range;

extern Game42DD0Range D_80082F80[];
u8 *func_10003C6C(s32, s32, s32, s32, s32);
void func_10004514(s32, s32, s32, s32);
void func_10004074(s32);
void func_15015A38(void *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15015920 CURRENT (804) */
void func_15015920(s16 arg0) {
    u8 *buffer;
    u8 *cursor;
    s32 index;
    register u8 *range;

    buffer = func_10003C6C(0x2800, 1, 2, 1, 0);
    range = (u8 *)&D_80082F80[arg0];
    func_10004514(*(s32 *)range, (s32)buffer,
                  *(s32 *)(range + 4) - *(s32 *)range, 1);
    cursor = buffer;
    index = 0;
    if ((u32)(buffer + 0xF) <
        (u32)((buffer + *(s32 *)(range + 4)) - *(s32 *)range)) {
        do {
            func_15015A38(cursor, index, arg0);
            cursor += (cursor[4] << 24) + (cursor[5] << 16) +
                      (cursor[6] << 8) + cursor[7];
            index++;
        } while ((u32)(cursor + 0xF) <
                 (u32)((buffer + *(s32 *)(range + 4)) - *(s32 *)range));
    }
    func_10004074((s32)buffer);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15015920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_42DD0/func_15015920.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_42DD0/func_15015A38.s")
