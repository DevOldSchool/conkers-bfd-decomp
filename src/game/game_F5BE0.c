#include "types.h"

/*
 * Reviewed source unit: src/game/game_F5BE0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C8730
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1503E5F8(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_151EFEB8(void *, s32);
void *func_15073118(void *, s32, s32, s32, f32, f32, f32, f32, f32, f32, s32);
extern f32 D_800A04F0;
extern f32 D_800A04F4;
extern f32 D_800A04F8;
extern f32 D_800A04FC;
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C8730 CURRENT (1144) */
s32 func_150C8730(u8 *arg0, u8 *arg1) {
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
    void *object;
    s32 packed;
    u16 kind;
    u8 *state;

    state = *(u8 **)(arg1 + 0x2D0);
    if (state == 0) {
        return 0;
    }
    kind = *(u16 *)(arg1 + 0x84);
    if (kind == 0x14 && 10.0f < *(f32 *)(state + 8)) {
        goto spawn;
    }
    if (kind != 0x23) {
        return 0;
    }
spawn:
    func_151EFEB8(transform, *(s32 *)(arg0 + 0x34) + ((D_800BE9C0 == 0) << 6));
    *(f32 *)(transform + 0x0C) = 0.0f;
    *(f32 *)(transform + 0x1C) = 0.0f;
    *(f32 *)(transform + 0x2C) = 0.0f;
    *(f32 *)(transform + 0x3C) = 1.0f;
    func_1503E5F8(transform, (s32)&out0, (s32)&out1, (s32)&out2,
                   (s32)&out3, (s32)&out4, (s32)&out5,
                   (s32)&extra0, (s32)&extra1, (s32)&extra2);
    object = func_15073118(arg1, -1, 0x4E, 0, 0.0f, 0.0f, 0.0f,
                            D_800A04F0, D_800A04F4, D_800A04F8, 0xC8);
    *(f32 *)((u8 *)object + 0x14) = out0;
    *(f32 *)((u8 *)object + 0x18) = out1;
    *(f32 *)((u8 *)object + 0x1C) = out2;
    *(f32 *)((u8 *)object + 0xB8) = out3;
    *(f32 *)((u8 *)object + 0x40) = out4;
    *(f32 *)((u8 *)object + 0xC4) = out5;
    packed = (s32)((*(f32 *)((u8 *)object + 0x40) - 90.0f) * D_800A04FC);
    *(s16 *)((u8 *)object + 0x76) = packed;
    *(s16 *)((u8 *)object + 0x7A) = packed;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C8730 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5BE0/func_150C8730.s")
