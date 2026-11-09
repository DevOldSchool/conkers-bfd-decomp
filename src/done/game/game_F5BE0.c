#include "types.h"

/*
 * Reviewed source unit: src/game/game_F5BE0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 */

s32 func_1503E5F8(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_151EFEB8(void *, s32);
void *func_15073118(void *, s32, s32, f32, f32, f32, f32, f32, f32, f32, s32);
extern f32 D_800A04F0;
extern f32 D_800A04F4;
extern f32 D_800A04F8;
extern f32 D_800A04FC;
extern u8 D_800BE9C0;

s32 func_150C8730(u8 *arg0, u8 *arg1) {
    s32 kind;
    u8 *state;
    s32 base;
    u8 flag;
    void *object;
    f32 *m;
    s32 offset;
    u8 transform[0x40];
    f32 out0;
    f32 out1;
    f32 out2;
    s32 extra0;
    s32 extra1;
    s32 extra2;
    f32 out3;
    f32 out4;
    f32 out5;

    state = *(u8 **)(arg1 + 0x2D0);
    if (state == NULL) {
        return 0;
    }
    kind = *(u16 *)(arg1 + 0x84);
    if ((kind == 0x14 && 10.0f < *(f32 *)(state + 8)) || kind == 0x23) {
        flag = D_800BE9C0;
        base = *(s32 *)(arg0 + 0x34);
        offset = (flag == 0) << 6;
        base += offset;
        func_151EFEB8(transform, base);
        m = (f32 *)transform;
        m[3] = 0.0f;
        m[7] = 0.0f;
        m[11] = 0.0f;
        m[15] = 1.0f;
        func_1503E5F8(transform, (s32)&out0, (s32)&out1, (s32)&out2,
                       (s32)&out3, (s32)&out4, (s32)&out5,
                       (s32)&extra0, (s32)&extra1, (s32)&extra2);
        object = func_15073118(arg1, -1, 0x4E, 0.0f, 0.0f, 0.0f, 0.0f,
                                D_800A04F0, D_800A04F4, D_800A04F8, 0xC8);
        *(f32 *)((u8 *)object + 0x14) = out0;
        *(f32 *)((u8 *)object + 0x18) = out1;
        *(f32 *)((u8 *)object + 0x1C) = out2;
        *(f32 *)((u8 *)object + 0xB8) = out3;
        *(f32 *)((u8 *)object + 0x40) = out4;
        *(f32 *)((u8 *)object + 0xC4) = out5;
        *(s16 *)((u8 *)object + 0x7A) = *(s16 *)((u8 *)object + 0x76) = (s32)((*(f32 *)((u8 *)object + 0x40) - 90.0f) * D_800A04FC);
        return 1;
    }
    return 0;
}
