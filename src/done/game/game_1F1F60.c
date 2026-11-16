#include "types.h"
#include "game_vec.h"

/*
 * Reviewed source unit: src/game/game_1F1F60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_isolated_selectors_and_calls.md
 */

void func_151C4AB0(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x110);
    if (arg2 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == *(s32 *)((u8 *)temp_v0 + 0x90)) {
            *(s32 *)((u8 *)temp_v0 + 0x90) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 0x94) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)((u8 *)temp_v0 + 0x90)) {
            *(s32 *)((u8 *)temp_v0 + 0x90) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 0x94) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
typedef struct Game1F1F60Hit {
    void *actor;
    f32 dist;
    Vec3f hit;
    Vec3f normal;
    Vec3f point;
    Vec3f start;
    Vec3f end;
    s16 surface[9];
    s16 field_56;
    s8 field_58;
    u8 type;
    s8 field_5A;
    u8 pad5B;
    u8 *field_5C;
    s32 field_60;
} Game1F1F60Hit;

void func_15081690(void *, f32, f32, f32, f32, f32, f32, void *, f32, s32, s32, s32, s8, s32, s32);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
void func_151C2050(void *, Vec3f *, Vec3f *, s32, f32);
extern u8 *D_800DBEF4;

s32 func_151C4B0C(Game1F1F60Hit *arg0, Game1F1F60Hit *arg1, Vec3f *arg2, Vec3f *arg3, f32 *arg4, f32 arg5,
                  u8 arg6, Vec3f *arg7, Vec3f *arg8, u8 *arg9, u8 arg10, f32 arg11, void *arg12, s8 arg13,
                  u8 arg14, u8 arg15, s32 arg16, u8 arg17) {
    Game1F1F60Hit hit;

    if (arg0 != NULL) {
        *arg1 = *arg0;
        if (arg2->x != arg1->start.x || arg2->y != arg1->start.y || arg2->z != arg1->start.z) {
            arg1->end.x = arg1->hit.x - arg2->x;
            arg1->end.y = arg1->hit.y - arg2->y;
            arg1->end.z = arg1->hit.z - arg2->z;
            arg1->start = *arg2;
            if (func_15145128(&arg1->end.x, &arg1->end.x, &arg1->dist, NULL) == 0) {
                return 0;
            }
        }
        if (arg17 != 0 && (arg1->type == 2 || arg1->type == 3)) {
            func_15081690(arg12, arg1->start.x, arg1->start.y, arg1->start.z, arg1->end.x, arg1->end.y,
                          arg1->end.z, &hit, 0.0f, 0, 1, 1, -1, 0, arg16);
            if (hit.type != 0) {
                *arg1 = hit;
            }
        }
        *arg4 = arg1->dist * arg5;
    } else if (arg6 != 0) {
        u8 found;
        s32 index;

        index = -1;
        if (arg7 != NULL && arg8 != NULL) {
            arg1->start = *arg7;
            arg1->end = *arg8;
        } else {
            arg1->start = *arg2;
            arg1->end = *arg3;
        }
        func_15081690(arg12, arg1->start.x, arg1->start.y, arg1->start.z, arg1->end.x, arg1->end.y,
                      arg1->end.z, arg1, 0.0f, 0, arg14 ? 0 : 1, (arg15 != 0 && arg14 != 0) ? 0 : 1, arg13,
                      0, arg16);
        if (arg1->field_5C == NULL) {
            index = -1;
        } else {
            index = (arg1->field_5C - D_800DBEF4) / 160;
        }
        if (arg1->type == 0) {
            found = 0;
        } else if (arg1->type == 1) {
            found = 1;
        } else if (arg7 != NULL && arg8 != NULL) {
            f32 dist;
            Game1F1F60Hit saved;

            saved = *arg1;
            arg1->start = *arg2;
            arg1->end.x = arg1->hit.x - arg2->x;
            arg1->end.y = arg1->hit.y - arg2->y;
            arg1->end.z = arg1->hit.z - arg2->z;
            if (func_15145128(&arg1->end.x, &arg1->end.x, &arg1->dist, NULL) == 0) {
                return 0;
            }
            dist = arg1->dist;
            found = func_150AC9C0(arg1->hit.x, arg1->hit.y, arg1->hit.z, arg1->end.x, arg1->end.y, arg1->end.z,
                                  NULL, arg1->surface, &arg1->hit.x, &arg1->hit.y, &arg1->hit.z, &arg1->dist,
                                  &index, &arg1->field_60, 0.0f);
            if (found) {
                arg1->dist += dist;
                arg1->start = *arg2;
            }
        } else {
            found = func_150AC9C0(arg2->x, arg2->y, arg2->z, arg1->end.x, arg1->end.y, arg1->end.z, NULL,
                                  arg1->surface, &arg1->hit.x, &arg1->hit.y, &arg1->hit.z, &arg1->dist, &index,
                                  &arg1->field_60, 0.0f);
        }
        if (found) {
            *arg4 = arg1->dist * arg5;
            if (arg2->x != arg1->start.x || arg2->y != arg1->start.y || arg2->z != arg1->start.z) {
                arg1->end.x = arg1->hit.x - arg2->x;
                arg1->end.y = arg1->hit.y - arg2->y;
                arg1->end.z = arg1->hit.z - arg2->z;
                arg1->start = *arg2;
                if (func_15145128(&arg1->end.x, &arg1->end.x, &arg1->dist, NULL) == 0) {
                    return 0;
                }
            }
            func_151C2050(arg12, &arg1->hit, &arg1->end, arg1->field_60, arg1->dist);
            if (index == -1) {
                arg1->field_5C = NULL;
            } else {
                arg1->field_5C = D_800DBEF4 + index * 160;
            }
        } else {
            *arg9 &= ~arg10;
            *arg4 = arg11;
            if (arg3 == NULL && arg8 == NULL) {
                return 0;
            }
        }
    } else {
        *arg9 &= ~arg10;
        *arg4 = arg11;
        arg1->start = *arg2;
        if (arg3 != NULL) {
            arg1->end = *arg3;
        } else if (arg8 != NULL) {
            arg1->end = *arg8;
        } else {
            return 0;
        }
    }
    return 1;
}
