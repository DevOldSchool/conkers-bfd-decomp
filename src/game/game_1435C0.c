#include "types.h"
#include "game_functions.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_1435C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15116110
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1435C0State {
    u8 pad0[0x3C];
    s32 packed;
    u8 pad40[0x3C];
    s32 handle;
} Game1435C0State;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15116110 CURRENT (844) */
void func_15116110(Game1435C0State *arg0) {
    s32 packed;
    s32 low;
    s32 high;
    s32 middle;

    if (arg0->handle == 0) {
        packed = arg0->packed;
        low = packed;
        high = packed >> 24;
        middle = packed >> 16;
        low &= 0x7FFF;
        middle &= 0xFF;
        high &= 0xFF;
        arg0->handle = func_15195FB0(arg0, low, packed >> 15, -1, 0, high,
                                      middle);
        arg0->packed = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15116110 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1435C0/func_15116110.s")
f32 func_1510F648(f32, f32, f32);                   /* extern */
extern u16 D_800CC354;

f32 fabsf(f32);
#pragma intrinsic(fabsf)

void func_1511617C(void *arg0) {
    s32 sp20[2];
    s16 sp1C[2];
    f32 temp_fv0;
    s16 temp_v0;
    s32 var_v1;
    f32 delta;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x12);
    sp1C[1] = temp_v0;
    temp_fv0 = func_1510F648((f32) *(s16 *)((u8 *)arg0 + 0x10), (f32) temp_v0, (f32) *(s16 *)((u8 *)arg0 + 0x14));
    *(f32 *)((u8 *)arg0 + 0x7C) = temp_fv0;
    if (fabsf(temp_fv0 - (f32) *(s16 *)((u8 *)arg0 + 0x12)) > 200.0f) {
        *(s32 *)((u8 *)arg0 + 0x3C) = 0;
    }
    if (!(*(u8 *)((u8 *)arg0 + 0x4F) & 4)) {
        delta = -*(s32 *)((u8 *)arg0 + 0x3C);
        *(s32 *)((u8 *)arg0 + 0x3C) = *(s32 *)((u8 *)arg0 + 0x3C) + delta * D_800A2FA8;
    } else {
        var_v1 = -0x14;
        if (D_800CC354 == 0x4B) {
            var_v1 = -0x28;
        }
        delta = var_v1 - *(s32 *)((u8 *)arg0 + 0x3C);
        *(s32 *)((u8 *)arg0 + 0x3C) = *(s32 *)((u8 *)arg0 + 0x3C) + delta * D_800A2FAC;
    }
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((f32) *(s32 *)((u8 *)arg0 + 0x3C) + *(f32 *)((u8 *)arg0 + 0x7C));
    *(s16 *)((u8 *)arg0 + 0x5C) = (s16) (*(s16 *)((u8 *)arg0 + 0x12) - sp1C[1]);
}
f32 func_15047C00(f32);                             /* extern */

void func_151162D4(void *arg0) {
    f32 scale;
    u32 step;
    s16 prev;
    f32 offset;

    prev = *(f32 *)((u8 *)arg0 + 0x18) + (f32) *(s16 *)((u8 *)arg0 + 0x12);
    scale = (s16) (*(s32 *)((u8 *)arg0 + 0x3C) & 0xFFFF);
    step = (*(s32 *)((u8 *)arg0 + 0x3C) >> 16) & 0xFFFF;
    offset = func_15047C00((f32) *(s32 *)((u8 *)arg0 + 0x7C) * 0.0054931640625f) * scale;
    *(f32 *)((u8 *)arg0 + 0x18) = offset;
    *(s32 *)((u8 *)arg0 + 0x7C) += step * D_800BE9E4;
    *(s16 *)((u8 *)arg0 + 0x5C) = ((f32) *(s16 *)((u8 *)arg0 + 0x12) + offset) - prev;
}
