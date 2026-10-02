#include "types.h"

/*
 * Reviewed source unit: src/game/game_50D20.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 */

void *func_1505EEF4(void *);
extern void *D_800C35F0[];

void func_15023870(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    void *temp_v0;

    if ((arg0 == 0xB) && (arg1 == 2)) {
        temp_v0 = func_1505EEF4(arg3);
        if (temp_v0 != 0) {
            *(u8 *)((u8 *)D_800C35F0[arg2] + 0x2A) = *(u8 *)((u8 *)temp_v0 + 0x3B);
        }
    }
}
