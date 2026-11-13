#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_808E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_internal_call_callback_clusters.md
 */

void func_1505D2B8(void *, u8);
s32 func_1507D754(u8 *);
void func_15055B0C(u8 *, s32);
void func_15053694(u8 *);
void func_150536D0(u8 *);
extern s16 *D_800D2110;
extern u8 *D_800D1C90[];
void func_15060F28(u8 *, s32);

s32 func_15053430(u8 *arg0) {
    u8 flags;
    u8 index;

    index = arg0[4];
    if (index == 0xFF) {
        func_15060F28(arg0, 1);
        return 1;
    }
    flags = D_800D1C90[index][0x28];
    if (arg0[0x10E] != 0 && arg0[0x10E] < 0xF0) {
        func_1505D2B8(arg0, 9);
    } else {
        s32 result = 0;

        if (arg0[0x10E] < 0xF0 && (flags & 0x20)) {
            func_151669A0(*(f32 *)(arg0 + 0x14), *(f32 *)(arg0 + 0x18) + 50.0f, *(f32 *)(arg0 + 0x1C), 0.5f, 0xFF, 0);
        }
        if (flags & 4) {
            result = func_1507D754(arg0);
        }
        if (flags & 2) {
            *(s32 *)arg0 = 0x2A;
        } else if (flags & 0x80) {
            func_15055B0C(arg0, 0x4B0);
        } else if (flags & 1) {
            func_15053694(arg0);
        } else if (flags & 0x40) {
            D_800D2110[arg0[0x13F]] = 0x4E2;
            func_15060F28(arg0, 1);
        } else if (result == 1) {
            func_150536D0(arg0);
        } else if (result == 0) {
            func_15060F28(arg0, 1);
        }
        return 1;
    }
    return 0;
}

/* Call context: func_15060F28: unique active project prototype */
void func_15060F28(u8 *, s32);
s32 func_15053430(u8 *);
extern u8 *D_800D1C90[];

s32 func_150535F4(u8 *arg0) {
    u8 temp_v0;
    u8 temp_v1;

    if (*(u8 *)(arg0 + 0x1CA) == 0) {
        temp_v1 = *(u8 *)(arg0 + 4);
        if (temp_v1 == 0xFF) {
            func_15060F28(arg0, 1);
            return 1;
        }
        temp_v0 = D_800D1C90[temp_v1][0x28];
        if ((temp_v0 & 0x10) ||
            ((temp_v0 & 8) && (*(f32 *)(arg0 + 0x28) == 0.0f)) ||
            (*(u8 *)(arg0 + 0x10F) == 0)) {
            return func_15053430(arg0);
        }
    }
    return 0;
}
/* Call context: func_1506160C: unique active project prototype */
void func_1506160C(u8 *, s32, s32, s32, u8);

void func_15053694(u8 *arg0) {
    *(s32 *)(arg0 + 0) = 8;
    *(s16 *)(arg0 + 0xE4) = 0;
    *(s16 *)(arg0 + 0xE6) = 0;
    func_1506160C(arg0, 6, 0, 0, 0U);
}
