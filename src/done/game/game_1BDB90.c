#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1BDB90.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_isolated_selectors_and_calls.md
 */

void func_151906E0(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x90);
    if (arg2 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == *(s32 *)((u8 *)temp_v0 + 8)) {
            *(s32 *)((u8 *)temp_v0 + 8) = (s32) *(s32 *)((u8 *)arg1 + 4);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)((u8 *)temp_v0 + 8)) {
            *(s32 *)((u8 *)temp_v0 + 8) = temp_v1;
        }
    }
}
void func_151D343C();

void func_1519072C(void *arg0) {
    struct {
        void *object;
        u8 kind;
    } descriptor;

    descriptor.object = arg0;
    descriptor.kind = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151D343C((s32)&descriptor, 0x2A);
    func_1518F45C((s32)&descriptor, 0x49);
}
