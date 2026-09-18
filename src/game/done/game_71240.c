#include "types.h"

/*
 * Reviewed source unit: src/game/game_71240.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 */

/* Call context: func_150A7790: unique active declaration in the allowed source */
/* Call context: func_150A8050: unique active declaration in the allowed source */
void func_150A7790(void *, s32);
void func_150A8050(void *, f32, f32, s32);

typedef struct {
    f32 m[4][4];
} Game71240Work;

void func_15043D90(s32 arg0, f32 arg1, f32 arg2, volatile s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    Game71240Work sp18;

    func_150A8050(&sp18, arg1, arg2, arg3);
    sp18.m[3][0] = arg7;
    sp18.m[3][1] = arg8;
    sp18.m[3][2] = arg9;
    sp18.m[0][0] *= arg4;
    sp18.m[0][1] *= arg4;
    sp18.m[0][2] *= arg4;
    sp18.m[1][0] *= arg5;
    sp18.m[1][1] *= arg5;
    sp18.m[1][2] *= arg5;
    sp18.m[2][0] *= arg6;
    sp18.m[2][1] *= arg6;
    sp18.m[2][2] *= arg6;
    func_150A7790(&sp18, arg0);
}
void func_150A8050(void *, f32, f32, s32);
void func_150A7790(void *, s32);

void func_15043E68(s32 arg0, f32 arg1, f32 arg2, volatile s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    Game71240Work sp18;

    func_150A8050(&sp18, arg1, arg2, arg3);
    sp18.m[3][0] = arg4;
    sp18.m[3][1] = arg5;
    sp18.m[3][2] = arg6;
    func_150A7790(&sp18, arg0);
}
void func_15043EC8(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    *(f32 *)((u8 *)arg0 + 0x30) = arg4;
    *(f32 *)((u8 *)arg0 + 0x34) = arg5;
    *(f32 *)((u8 *)arg0 + 0x38) = arg6;
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) * arg2);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) * arg2);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) * arg2);
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) * arg3);
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) * arg3);
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) * arg3);
}
void func_150A9B0C(void *, f32, f32, s32, f32, f32, f32);

void func_15043F6C(Game71240Work *arg0, f32 arg1, f32 arg2, volatile s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    func_150A9B0C(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    arg0->m[3][0] = arg7;
    arg0->m[3][1] = arg8;
    arg0->m[3][2] = arg9;
    arg0->m[0][3] = 0.0f;
    arg0->m[1][3] = 0.0f;
    arg0->m[2][3] = 0.0f;
    arg0->m[3][3] = 1.0f;
}
typedef struct Game71240Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Game71240Vec3f;

typedef struct Game71240TransformSource {
    u8 pad0[0x18];
    s16 x;
    s16 y;
    s16 z;
    u8 pad1[0x1A];
    s16 dx;
    s16 dy;
    s16 dz;
} Game71240TransformSource;

void func_15043FF0(Game71240Vec3f *arg0, Game71240TransformSource *arg1) {
    arg0->x = (f32)arg1->x;
    arg0->y = (f32)arg1->y;
    arg0->z = (f32)arg1->z;
    arg0->x = arg0->x + ((f32)arg1->dx * 0.000015258789f);
    arg0->y = arg0->y + ((f32)arg1->dy * 0.000015258789f);
    arg0->z = arg0->z + ((f32)arg1->dz * 0.000015258789f);
}
f32 func_10026530(f32);

void func_150440A0(void *arg0, f32 arg1, f32 arg2, f32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    f32 x;
    f32 y;
    f32 z;
    f32 side_x;
    f32 side_y;
    f32 side_z;
    f32 inv_len;

    x = arg4 - arg1;
    y = arg5 - arg2;
    z = arg6 - arg3;
    inv_len = -1.0f / func_10026530((x * x) + (y * y) + (z * z));
    x *= inv_len;
    y *= inv_len;
    z *= inv_len;
    side_x = (arg8 * z) - (arg9 * y);
    side_y = (arg9 * x) - (arg7 * z);
    side_z = (arg7 * y) - (arg8 * x);
    inv_len = 1.0f / func_10026530((side_x * side_x) +
                                   (side_y * side_y) +
                                   (side_z * side_z));
    side_x *= inv_len;
    side_y *= inv_len;
    side_z *= inv_len;
    arg7 = (y * side_z) - (z * side_y);
    arg8 = (z * side_x) - (x * side_z);
    arg9 = (x * side_y) - (y * side_x);
    inv_len = 1.0f / func_10026530((arg7 * arg7) + (arg8 * arg8) + (arg9 * arg9));
    arg7 *= inv_len;
    arg8 *= inv_len;
    arg9 *= inv_len;
    *(f32 *)((u8 *)arg0 + 0x00) = side_x;
    *(f32 *)((u8 *)arg0 + 0x10) = arg7;
    *(f32 *)((u8 *)arg0 + 0x20) = x;
    *(f32 *)((u8 *)arg0 + 0x30) = arg1;
    *(f32 *)((u8 *)arg0 + 0x04) = side_y;
    *(f32 *)((u8 *)arg0 + 0x14) = arg8;
    *(f32 *)((u8 *)arg0 + 0x24) = y;
    *(f32 *)((u8 *)arg0 + 0x34) = arg2;
    *(f32 *)((u8 *)arg0 + 0x08) = side_z;
    *(f32 *)((u8 *)arg0 + 0x18) = arg9;
    *(f32 *)((u8 *)arg0 + 0x28) = z;
    *(f32 *)((u8 *)arg0 + 0x38) = arg3;
    *(f32 *)((u8 *)arg0 + 0x0C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x1C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x2C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x3C) = 1.0f;
}
