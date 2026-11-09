#include "types.h"

/*
 * Reviewed source unit: src/game/game_122A40.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 */

void func_150F55C8(void *);

void func_150F5590(void *arg0) {
    s32 temp_v0;

    temp_v0 = 0x1000 - (*(s16 *)((u8 *)arg0 + 0x24) * 4);
    *(s16 *)((u8 *)arg0 + 0x38) = (s16) temp_v0;
    *(s16 *)((u8 *)arg0 + 0x3A) = (s16) *(s16 *)((u8 *)arg0 + 0x38);
    func_150F55C8(arg0);
}
void func_150F55C8(void *arg0) {
    s32 lo1C;
    s32 hi18;
    s32 lo18;
    s32 hi1C;
    s32 diff;

    lo1C = *(s32 *)((u8 *)arg0 + 0x1C) & 0xFFFF;
    hi18 = *(s32 *)((u8 *)arg0 + 0x18) >> 16;
    lo18 = *(s32 *)((u8 *)arg0 + 0x18) & 0xFFFF;
    hi1C = *(s32 *)((u8 *)arg0 + 0x1C) >> 16;
    diff = lo1C - hi18;
    if (diff < *(s16 *)((u8 *)arg0 + 0x24)) {
        *(u8 *)((u8 *)arg0 + 0x45) = ((lo1C - *(s16 *)((u8 *)arg0 + 0x24)) * 0xFF) / hi18;
        return;
    }
    if (diff - lo18 < *(s16 *)((u8 *)arg0 + 0x24)) {
        *(u8 *)((u8 *)arg0 + 0x45) = 0xFF;
        return;
    }
    *(u8 *)((u8 *)arg0 + 0x45) = (*(s16 *)((u8 *)arg0 + 0x24) * 0xFF) / hi1C;
}
void func_150F568C(s32 arg0) {
    func_15179008(0);
}
