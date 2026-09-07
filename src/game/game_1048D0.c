#include "types.h"

/*
 * Reviewed source unit: src/game/game_1048D0.c
 * Boundary evidence: docs/evidence/game_raw_callback_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D7420
 * - func_150D74DC
 * - func_150D758C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D7420 CURRENT (260) */
void func_150D7420(void *arg0, u8 *arg1, s32 arg2) {
    u8 temp_v0;

    if ((arg2 & 0xFF) == 0x36) {
        temp_v0 = *arg1;
        switch (temp_v0) {                          /* irregular */
        case 1:
            *(s8 *)((u8 *)arg0 + 0x28) = 0xFF;
            *(s8 *)((u8 *)arg0 + 0x29) = 0;
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 2);
            *(s8 *)((u8 *)arg0 + 0x2A) = 0;
            return;
        case 2:
            *(s8 *)((u8 *)arg0 + 0x28) = 0xFF;
            *(s8 *)((u8 *)arg0 + 0x29) = 0;
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 2);
            *(s8 *)((u8 *)arg0 + 0x2A) = 0;
            return;
        case 3:
            *(s8 *)((u8 *)arg0 + 0x28) = 0;
            *(s8 *)((u8 *)arg0 + 0x29) = 0xFF;
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 2);
            *(s8 *)((u8 *)arg0 + 0x2A) = 0;
            return;
        default:
        case 0:
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) & ~2);
            break;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D7420 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1048D0/func_150D7420.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D74DC CURRENT (225) */
void func_150D74DC(void *arg0, u8 *arg1, s32 arg2) {
    u8 temp_v0;

    if ((arg2 & 0xFF) == 0x36) {
        temp_v0 = *arg1;
        switch (temp_v0) {                          /* irregular */
        case 1:
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) & ~2);
            return;
        case 2:
            *(s8 *)((u8 *)arg0 + 0x28) = 0xFF;
            *(s8 *)((u8 *)arg0 + 0x29) = 0;
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 2);
            *(s8 *)((u8 *)arg0 + 0x2A) = 0;
            return;
        case 3:
            *(s8 *)((u8 *)arg0 + 0x28) = 0;
            *(s8 *)((u8 *)arg0 + 0x29) = 0xFF;
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 2);
            *(s8 *)((u8 *)arg0 + 0x2A) = 0;
            return;
        default:
        case 0:
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) & ~2);
            break;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D74DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1048D0/func_150D74DC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D758C CURRENT (215) */
void func_150D758C(void *arg0, u8 *arg1, s32 arg2) {
    u8 temp_v0;

    if ((arg2 & 0xFF) == 0x36) {
        temp_v0 = *arg1;
        switch (temp_v0) {                          /* irregular */
        case 1:
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) & ~2);
            return;
        case 2:
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) & ~2);
            return;
        case 3:
            *(s8 *)((u8 *)arg0 + 0x28) = 0;
            *(s8 *)((u8 *)arg0 + 0x29) = 0xFF;
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 2);
            *(s8 *)((u8 *)arg0 + 0x2A) = 0;
            return;
        default:
        case 0:
            *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) & ~2);
            break;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D758C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1048D0/func_150D758C.s")
