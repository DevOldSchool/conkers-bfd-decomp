#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FC5F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 */

typedef struct GameFC5F0Surface {
    f32 height;
    s16 vertices[9];
    u8 pad16[2];
    s32 value18;
    u8 flags, kind, pad1E[2];
    void *object;
} GameFC5F0Surface;

void func_1504715C(GameFC5F0Surface *, void *);
f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
void *func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32,
                      f32, f32, s32, void *, s32, s32, s32, s32);
extern f32 D_800BE9A4;

void func_150CF140(u8 *arg0) {
    u8 angle;
    u8 *owner;
    Vec3f origin;
    f32 radius;
    GameFC5F0Surface surface;
    f32 upper, lower;
    Vec3f position, direction;
    u8 *state;

    owner = *(u8 **)(arg0 + 0x28);
    state = arg0 + 0x28;
    if (*(s32 *)owner == 0 || state[4] != owner[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)(owner + 0x1D4) != 0) {
        *(f32 *)(state + 8) += (0.06f + func_150ADA68() * 0.0704f) * D_800BE9A4;
        func_1515C244(owner, &origin, &upper, &lower);
        radius = (upper + lower) * 0.5f;
        func_1504715C(&surface, owner);
        while (*(f32 *)(state + 8) > 1.0f) {
            angle = func_150ADA20() & 0xFF;
            func_15143794(angle, (s16)((func_150ADA20() % 76U) - 0x40), radius, &position);
            position.x += origin.x;
            position.y += origin.y;
            position.z += origin.z;
            func_15143794(angle, (s16)((func_150ADA20() % 54U) - 0x38),
                           func_150ADA68() * 1.4430001f + 2.2680001f, &direction);
            func_151D9014(&position.x, &direction.x, 5, func_150ADA68() * 0.286f + -0.78700006f,
                           (func_150ADA20() % 21U) + 0x1E, (func_150ADA20() % 156U) + 0x64,
                           func_150ADA68() * 50.0f + 48.0f, 1, 1.0f, 1.0f,
                           0, &surface, 1, 0, arg0[0xC], arg0[1]);
            *(f32 *)(state + 8) -= 1.0f;
        }
    }
}


void func_150CF484(void *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 first;

    temp_v0 = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
        first = *(s32 *)arg1;
        if ((first == *(s32 *)temp_v0) || (temp_v0[4] == arg1[4])) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)(arg1 + 4);
            temp_v0[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)arg1;
            temp_v0[4] = arg1[8];
        }
    }
}
