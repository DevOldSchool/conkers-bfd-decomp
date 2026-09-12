#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E5820.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 */

void func_1516972C(void *arg0);

void func_151B8370(void *arg0) {
    s32 *temp_v0;
    s32 temp_a1;

    temp_v0 = *(s32 **)((u8 *)arg0 + 0x98);
    temp_a1 = *temp_v0;
    if (temp_a1 != 0) {
        func_1516972C((void *)temp_a1);
    }
}
void func_15147928(s32 arg0);

void func_151B83A0(s32 arg0) {
    func_151B8370((void *)arg0);
    func_151478F4(arg0);
}
void func_151B83CC(void *arg0) {
    func_151B8370(arg0);
    func_15147928((s32)arg0);
}
