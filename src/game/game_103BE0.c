#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_103BE0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_owner_particle_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D6730
 * - func_150D6CC4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_103BE0/func_150D6730.s")
void func_150D6C98(void *arg0, void *arg1) {
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + 60.0f);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}

void func_15131958(void *, f32);
extern f32 D_800BE9A4;
extern f32 D_800BE9A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D6CC4 CURRENT (372) */
s32 func_150D6CC4(u8 *arg0, s32 arg1) {
    u8 *state;
    u8 *object;
    Vec3f previous;
    f32 changeX;
    f32 changeY;
    f32 changeZ;

    state = arg0 + 0xA8;
    object = *(u8 **)state;
    if (*(s32 *)object == 0 || state[4] != object[0x3B]) {
        return 0;
    }
    func_150D6C98(object, arg0 + 0x40);
    previous = *(Vec3f *)(arg0 + 0x58);
    *(f32 *)(arg0 + 0x5C) += *(f32 *)(arg0 + 0x64) * D_800BE9A4;
    func_15131958(arg0 + 0x58, *(f32 *)(state + 8));
    changeX = (*(f32 *)(arg0 + 0x58) - previous.x) * D_800BE9A8;
    changeY = (*(f32 *)(arg0 + 0x5C) - previous.y) * D_800BE9A8;
    changeZ = (*(f32 *)(arg0 + 0x60) - previous.z) * D_800BE9A8;
    *(f32 *)(arg0 + 0x4C) += previous.x * D_800BE9A4 +
        changeX * D_800BE9A4 * D_800BE9A4 * 0.5f;
    *(f32 *)(arg0 + 0x50) += previous.y * D_800BE9A4 +
        changeY * D_800BE9A4 * D_800BE9A4 * 0.5f;
    *(f32 *)(arg0 + 0x54) += previous.z * D_800BE9A4 +
        changeZ * D_800BE9A4 * D_800BE9A4 * 0.5f;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D6CC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_103BE0/func_150D6CC4.s")

void func_150D6E60(void *arg0, void *arg1, u8 arg2) {
    s32 temp_t6;
    u8 *temp_v0;

    temp_t6 = arg2;
    temp_v0 = (u8 *)arg0 + 0xA8;
    if (temp_t6 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0) {
            u8 *dst = temp_v0;

            *(s32 *)dst = *(s32 *)arg1;
            *(u8 *)(dst + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if (temp_t6 == 0) {
        s32 temp_v1 = *(s32 *)arg1;

        if ((temp_v1 == *(s32 *)temp_v0) ||
            (temp_v0[4] == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    }
}
/* Call context: func_150D6C98: unique active project prototype */
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

s32 func_150D6F0C(u8 *arg0, s32 arg1) {
    u8 *temp_a3;
    u8 *temp_v0;

    temp_a3 = (void *)(*(void **)((u8 *)arg0 + 0xA8));
    temp_v0 = (void *)(arg0 + 0xA8);
    if ((*(s32 *)((u8 *)temp_a3 + 0) == 0) || (*(u8 *)((u8 *)temp_v0 + 4) != *(u8 *)((u8 *)temp_a3 + 0x3B))) {
        return 0;
    }
    func_150D6C98(temp_a3, arg0 + 0x40);
    *(f32 *)((u8 *)arg0 + 0x38) =
        *(f32 *)((u8 *)arg0 + 0x3C) =
        *(f32 *)((u8 *)temp_v0 + 0x10) * sqrtf(*(f32 *)((u8 *)temp_v0 + 8));
    *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) (*(f32 *)((u8 *)temp_v0 + 0x14) - (*(f32 *)((u8 *)temp_v0 + 8) * (*(f32 *)((u8 *)temp_v0 + 8) * *(f32 *)((u8 *)temp_v0 + 0x18))));
    *(f32 *)((u8 *)temp_v0 + 8) = (f32) (*(f32 *)((u8 *)temp_v0 + 8) + D_800BE9A4);
    if (*(f32 *)((u8 *)temp_v0 + 0xC) < *(f32 *)((u8 *)temp_v0 + 8)) {
        return 0;
    }
    return 1;
}
void func_150D7068(void *arg0, void *arg1, u8 arg2) {
    s32 temp_t6;
    u8 *temp_v0;

    temp_t6 = arg2;
    temp_v0 = (u8 *)arg0 + 0xA8;
    if (temp_t6 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0) {
            u8 *dst = temp_v0;

            *(s32 *)dst = *(s32 *)arg1;
            *(u8 *)(dst + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if (temp_t6 == 0) {
        s32 temp_v1 = *(s32 *)arg1;

        if ((temp_v1 == *(s32 *)temp_v0) ||
            (temp_v0[4] == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    }
}
