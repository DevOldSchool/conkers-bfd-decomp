#include "types.h"

/*
 * Reviewed source unit: src/game/game_137D20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_callback_table_runs.md
 */

void func_1510A870(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 temp_v1;

    temp_v0 = (void *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
void func_1510A8CC(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;

    temp_v0 = arg0 + 0x28;
    if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)arg1;
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
    }
}
