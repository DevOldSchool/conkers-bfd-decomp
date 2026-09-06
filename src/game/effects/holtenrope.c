#include "types.h"

/*
 * Reviewed source unit: src/game/effects/holtenrope.c
 * Boundary evidence: docs/evidence/game_beta_camera_rope_bee.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B3184
 * - func_151B32C8
 * - func_151B3A34
 * - func_151B3A7C
 * - func_151B3CF0
 * - func_151B3F28
 * - func_151B3FDC
 * - func_151B42A4
 * - func_151B47D8
 * - func_151B48DC
 * - func_151B498C
 * - func_151B4A14
 * - func_151B4B78
 * - func_151B4C1C
 * - func_151B4C98
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct HoltenRopeEffect {
    u8 pad0[0x10];
    u8 flags;
    u8 pad11;
    s16 timer;
    u8 primaryState[0xC];
    u8 secondaryState[0xC];
    s8 primaryCallback;
    s8 secondaryCallback;
    u8 pad2E[6];
    s8 updateCallback;
    u8 pad35[3];
    f32 radius;
    u8 pad3C[0xFC];
    f32 doubledRadiusSquared;
    s32 scaledRadius;
    u8 resetState[1];
} HoltenRopeEffect;

typedef s32 (*HoltenRopeStateCallback)(HoltenRopeEffect *, void *, s32);
typedef s32 (*HoltenRopeUpdateCallback)(HoltenRopeEffect *);

void func_100226F0(void *, s32);
void func_10022EC0(void *, void *, s32);
HoltenRopeEffect *func_15167A68(s32, s32, s32, s32, s32, s32);
extern f32 D_800AA390;
extern s32 D_800BE9E4;
extern HoltenRopeStateCallback D_8008FAF0[];
extern HoltenRopeUpdateCallback D_8008FAF8[];

HoltenRopeEffect *func_151B30B0(void *arg0, f32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    HoltenRopeEffect *result;
    f32 radius;

    result = func_15167A68(0x33, arg4, arg2 + 0x150, 1, arg3, 1);
    if (result == 0) {
        return 0;
    }
    func_10022EC0(&result->flags, arg0, 0x38);
    radius = result->radius;
    result->flags |= 0xE;
    result->doubledRadiusSquared = 2.0f * ((radius * radius) / D_800AA390);
    result->scaledRadius = (s32)(radius * arg1 * 4096.0f);
    func_100226F0(result->resetState, 0x10);
    return result;
}
void func_1516972C(HoltenRopeEffect *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B3184 CURRENT (24) */
void func_151B3184(HoltenRopeEffect *arg0) {
    u8 finished = 0;
    s32 callback;

    if (arg0->flags & 1) {
        arg0->timer -= D_800BE9E4;
        if (arg0->timer < 0) {
            finished = 1;
        }
    }
    if (finished == 0) {
        callback = arg0->primaryCallback;
        if (callback != -1) {
            if (D_8008FAF0[callback](arg0, arg0->primaryState, 1) == 0) {
                finished = 1;
            }
        }
        callback = arg0->secondaryCallback;
        if (callback != -1) {
            if (D_8008FAF0[callback](arg0, arg0->secondaryState, 0) == 0) {
                finished = 1;
            }
        }
        if ((arg0->flags & 4) || (arg0->flags & 8)) {
            arg0->flags |= 2;
        } else {
            callback = arg0->updateCallback;
            if (callback != -1) {
                if (D_8008FAF8[callback](arg0) == 0) {
                    finished = 1;
                }
            }
        }
    }
    if (finished != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B3184 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3184.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B32C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3A34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3A7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3CF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3F28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3FDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B42A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B47D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B48DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B498C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B4A14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B4B78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B4C1C.s")
void func_151B4C6C(s32 arg0) {
    func_151B4C1C(arg0);
    func_15169824(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B4C98.s")
