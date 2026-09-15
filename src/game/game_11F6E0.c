#include "types.h"

/*
 * Reviewed source unit: src/game/game_11F6E0.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 */

void func_15143134(f32 *, f32 *, s32);
s32 func_150ADA20(void);
void func_15143874(s16, s32, f32 *, f32 *);
void func_151C329C(f32 *, u8, s32);

void func_150F2230(void *arg0, u8 arg1, s32 arg2) {
    f32 vector[3];
    f32 transformed[3];

    if (*(s32 *)((u8 *)arg0 + 0x1D4) == 0 ||
        (*(u8 *)((u8 *)arg0 + 0x74) & 0xF) == 0xF) {
        return;
    }
    vector[0] = 0.0f;
    vector[1] = 0.0f;
    vector[2] = 0.0f;
    func_15143874((s16)(func_150ADA20() & 0xFF), 0x42C80000,
                  &vector[0], &vector[2]);
    func_15143134(&vector[0], &transformed[0],
                  *(s32 *)((u8 *)arg0 + 0x1D4) + 0x4C0);
    func_151C329C(&transformed[0], arg1, arg2);
}
