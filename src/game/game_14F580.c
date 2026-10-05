#include "types.h"

/*
 * Reviewed source unit: src/game/game_14F580.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15122170
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15048F90(void *, void *, void *);
f32 func_15048FC8(f32 *);
void *func_15122980(void *);
extern f32 D_800A3460;

void func_151220D0(void *arg0) {
    f32 vector[3];
    f32 temp_fv0;

    if (!((*(u16 **)((u8 *)arg0 + 0x36C))[0] & 4)) {
        func_15048F90((u8 *)arg0 + 0x2F8, (u8 *)arg0 + 0x2BC, vector);
        vector[0] += *(f32 *)((u8 *)arg0 + 0x2C8) - *(f32 *)((u8 *)arg0 + 0x2BC);
        vector[2] += *(f32 *)((u8 *)arg0 + 0x2D0) - *(f32 *)((u8 *)arg0 + 0x2C4);
        temp_fv0 = func_15048FC8(&vector[0]);
        *(f32 *)((u8 *)arg0 + 0x37C) = temp_fv0;
        *(f32 *)((u8 *)arg0 + 0x39C) = temp_fv0 * D_800A3460;
    }
    func_15122980(arg0);
}
f32 func_15048C30(f32, f32);
void func_15049688(void *, f32, void *, f32, f32, f32);
void func_15125330(void *);
void func_15123A54(void *);
void func_1512A390(void *);
void func_1512E140(void *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern f32 D_800A3470, D_800A3474, D_800A3478, D_800A347C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15122170 CURRENT (285) */
void func_15122170(void *arg0) {
    f32 deltaZ;
    f32 deltaX;
    f32 distance;
    f32 angle;
    f32 heading;
    f32 decay;
    f32 *point;
    s32 flags;

    if ((*(u16 **)((u8 *)arg0 + 0x36C))[0] & 4) {
        func_15122980(arg0);
        return;
    }
    angle = *(f32 *)((u8 *)arg0 + 0x5DC);
    decay = angle * D_800A3470;
    *(f32 *)((u8 *)arg0 + 0x6C4) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x5DC) = angle - decay;
    func_15125330(arg0);
    point = *(f32 **)((u8 *)arg0 + 0x614);
    if (point == 0) {
        func_15122980(arg0);
        return;
    }
    deltaX = point[0] - *(f32 *)((u8 *)arg0 + 0x2BC);
    deltaZ = point[2] - *(f32 *)((u8 *)arg0 + 0x2C4);
    distance = sqrtf(deltaX * deltaX + deltaZ * deltaZ);
    if (distance == 0.0f) {
        func_15122980(arg0);
        return;
    }
    angle = func_15048C30(-deltaX / distance, 0.0f);
    if (deltaZ > 0.0f) {
        heading = 270.0f - angle * D_800A3474;
    } else {
        heading = angle * D_800A3478 + 90.0f;
    }
    heading += -90.0f + *(f32 *)((u8 *)arg0 + 0x5DC);
    while (heading < 0.0f) {
        heading += 360.0f;
    }
    while (heading > 360.0f) {
        heading -= 360.0f;
    }
    if (*(s32 *)((u8 *)arg0 + 0x698) == 0) {
        if (*(u8 *)((u8 *)arg0 + 0x23C) != 0) {
            *(f32 *)((u8 *)arg0 + 0x630) = 0.0f;
            *(f32 *)((u8 *)arg0 + 0x37C) = heading;
        } else {
            flags = *(s32 *)((u8 *)arg0 + 0x84);
            if (flags & 0x40000000) {
                func_15049688((u8 *)arg0 + 0x37C, heading, (u8 *)arg0 + 0x630,
                    3.0f, 6.0f, *(f32 *)((u8 *)arg0 + 0x7B4));
            } else if (flags & 0x04000000) {
                func_15049688((u8 *)arg0 + 0x37C, heading, (u8 *)arg0 + 0x630,
                    3.0f, 6.0f, *(f32 *)((u8 *)arg0 + 0x7B4));
            } else {
                func_15049688((u8 *)arg0 + 0x37C, heading, (u8 *)arg0 + 0x630,
                    1.5f, 2.0f, *(f32 *)((u8 *)arg0 + 0x7B4));
            }
        }
        *(f32 *)((u8 *)arg0 + 0x39C) = *(f32 *)((u8 *)arg0 + 0x37C) * D_800A347C;
    }
    func_1512A390(arg0);
    func_15123A54(arg0);
    func_1512E140(arg0);
    if (*(s32 *)((u8 *)arg0 + 0x84) & 0x40000000) {
        func_15123A54(arg0);
        *(f32 *)((u8 *)arg0 + 0x190) = 30.0f;
        func_1512E140(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15122170 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14F580/func_15122170.s")
