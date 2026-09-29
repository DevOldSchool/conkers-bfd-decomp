#include "types.h"

/*
 * Reviewed source unit: src/game/game_FC550.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 */

void func_15117798(u8 *);
void *func_151149AC(u8);
extern void *D_800CC5EC;

void func_150CF0A0(u8 *arg0) {
    void *temp_v0;
    void *temp_v0_2;

    if ((arg0[0x73] & 3) != 2) {
        if ((arg0[0x4F] & 4) && (*(u8 *)((u8 *)D_800CC5EC + 0x57) != 0)) {
            temp_v0 = func_151149AC(0xFE);
            *(u8 *)((u8 *)temp_v0 + 0x73) &= 0xFFFC;
            *(volatile u8 *)((u8 *)temp_v0 + 0x73) = *(u8 *)((u8 *)temp_v0 + 0x73) | 2;
            temp_v0_2 = func_151149AC(0xFD);
            *(u8 *)((u8 *)temp_v0_2 + 0x73) &= 0xFFFC;
            *(volatile u8 *)((u8 *)temp_v0_2 + 0x73) = *(u8 *)((u8 *)temp_v0_2 + 0x73) | 2;
        }
    } else {
        func_15117798(arg0);
    }
}
