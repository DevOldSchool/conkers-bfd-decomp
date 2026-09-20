#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BFCB0.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15192800
 * - func_151928B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1BFCB0Record {
    u8 pad0[4];
    u8 field_4;
} Game1BFCB0Record;

typedef void (*Game1BFCB0Handler)(void *arg0);

extern s32 func_151928B0(void *arg0, s32 *arg1);
extern s32 func_1510F8CC(s32 arg0);
extern Game1BFCB0Handler **D_8008F860[];
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15192800 CURRENT (595) */
void func_15192800(void *arg0, void *arg1) {
    s32 sp2C;
    Game1BFCB0Handler callback;
    s32 temp_v0;
    s32 var_v0;

    if ((arg0 != 0) && (func_151928B0(arg0, &sp2C) != 0)) {
        temp_v0 = func_1510F8CC(*(s32 *)((u8 *)arg0 + 0x184));
        if (temp_v0 != 5) {
            if (temp_v0 != 6) {
                var_v0 = 1;
            } else {
                var_v0 = 3;
            }
        } else if (D_800BE9F0 == 0x14) {
            var_v0 = 2;
        } else {
            var_v0 = 1;
        }
        callback = D_8008F860[sp2C][var_v0];
        if (callback != 0) {
            callback(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15192800 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFCB0/func_15192800.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151928B0 CURRENT (405) */
s32 func_151928B0(Game1BFCB0Record *arg0, s32 *arg1) {
    s32 result = 0;

    switch (arg0->field_4) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            result = 1;
            *arg1 = 0;
            goto done;
        case 0x53:
            result = 1;
            *arg1 = 1;
            goto done;
        default:
            break;
    }
done:
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151928B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFCB0/func_151928B0.s")
