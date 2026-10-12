#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FC5F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CF140
 * - func_150CF484
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameFC5F0Vector { f32 x, y, z; } GameFC5F0Vector;
typedef struct GameFC5F0Surface {
    f32 height;
    s16 vertices[9];
    u8 pad16[2];
    s32 value18;
    u8 flags, kind, pad1E[2];
    void *object;
} GameFC5F0Surface;

void func_1504715C(GameFC5F0Surface *, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
void *func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32,
                      f32, f32, s32, void *, s32, s32, s32, s32);
extern f32 D_800A0840, D_800A0844, D_800A0848, D_800A084C;
extern f32 D_800A0850, D_800A0854, D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF140 CURRENT (1228) */
void func_150CF140(u8 *arg0) {
    s16 angle;
    u8 *owner;
    GameFC5F0Vector origin;
    f32 radius;
    GameFC5F0Surface surface;
    f32 upper, lower;
    GameFC5F0Vector position, direction;
    f32 randomSize, speedRange, speedBase, sizeRange, sizeBase;
    u32 random1, random2;
    u8 *state;

    owner = *(u8 **)(arg0 + 0x28);
    state = arg0 + 0x28;
    if (*(s32 *)owner == 0 || state[4] != owner[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)(owner + 0x1D4) != 0) {
        *(f32 *)(state + 8) += (D_800A0840 + func_150ADA68() * D_800A0844) * D_800BE9A4;
        func_1515C244(owner, &origin, &upper, &lower);
        radius = (upper + lower) * 0.5f;
        func_1504715C(&surface, owner);
        if (*(f32 *)(state + 8) > 1.0f) {
            sizeBase = D_800A0848;
            sizeRange = D_800A084C;
            speedBase = D_800A0850;
            speedRange = D_800A0854;
            do {
                angle = func_150ADA20() & 0xFF;
                func_15143794(angle, (s16)((func_150ADA20() % 76U) - 0x40), radius, &position);
                position.x += origin.x;
                position.y += origin.y;
                position.z += origin.z;
                random1 = func_150ADA20();
                func_15143794(angle, (s16)((random1 % 54U) - 0x38),
                               func_150ADA68() * speedRange + speedBase, &direction);
                randomSize = func_150ADA68();
                random1 = func_150ADA20();
                random2 = func_150ADA20();
                func_151D9014(&position.x, &direction.x, 5, randomSize * sizeRange + sizeBase,
                               (random1 % 21U) + 0x1E, (random2 % 156U) + 0x64,
                               func_150ADA68() * 50.0f + 48.0f, 1, 1.0f, 1.0f,
                               0, &surface, 1, 0, arg0[0xC], arg0[1]);
                *(volatile f32 *)(state + 8) -= 1.0f;
            } while (*(volatile f32 *)(state + 8) > 1.0f);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF140 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC5F0/func_150CF140.s")


#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF484 CURRENT (1010) */
void func_150CF484(void *arg0, void *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_a3;
    u8 *temp_v0;

    temp_a3 = arg0;
    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0) {
        if ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)temp_a3 + 0x28)) ||
            (*(u8 *)((u8 *)temp_a3 + 0x2C) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(temp_a3);
        }
    } else {
        temp_v0 = (u8 *)temp_a3 + 0x28;
        if (temp_t6 == 0x2D) {
            temp_a0 = *(s32 *)temp_v0;
            temp_v1 = *(s32 *)arg1;
            if (temp_v1 == temp_a0) {
                *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
                *(s32 *)temp_v0 = temp_v1;
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF484 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC5F0/func_150CF484.s")
