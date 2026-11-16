#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_118400.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_callback_clusters.md
 */

typedef struct Game118400Record Game118400Record;

s32 func_151420F8();
extern s32 D_800BE9F0;

s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);

s32 func_150EAF50(f32 *arg0, u8 *arg1, void *arg2, u8 arg3) {
    f32 position[3];
    s32 var_a1;

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }
    if (arg3 == 1) {
        var_a1 = 0x21;
    } else {
        var_a1 = 0x1D;
    }
    func_15142314(*(void **)(arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 10.0f;
    position[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 50.0f, arg2);
}

s32 func_150EB030(s32 arg0, Game118400Record *arg1) {
    if (arg0 == 1) {
        if (D_800BE9F0 == 4) {
            if (func_151420F8(arg1) != 0) {
                return 6;
            }
            return 3;
        }
        return -1;
    }
    return -1;
}

void func_15141F78(s32, void *, f32, s32, f32 *, s32);
extern f32 D_800A1470;
extern f32 D_800A1474;

void func_150EB090(u8 *arg0, s32 arg1, s32 arg2) {
    f32 position[3];
    s32 work[9];

    if (*(s32 *)(arg0 + 0x1D4) == 0) {
        return;
    }
    if (func_150EAF50(position, arg0, work, (u8)arg1) != 0) {
        func_15141F78(0xA, work, (f32)arg2 * D_800A1470,
                      (u32)(*(f32 *)(arg0 + 0x40) * D_800A1474) & 0xFF,
                      position, (u8)arg1);
    }
}
