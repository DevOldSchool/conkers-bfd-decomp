#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D4AC0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A7610
 * - func_151A77C0
 * - func_151A787C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_151A26EC(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A8DC8;
extern f32 D_800A8DCC;
extern f32 D_800A8DD0;
extern f32 D_800BE9A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A7610 CURRENT (2637) */
void func_151A7610(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 position[3];
    f32 velocity[3];
    f32 zero[3];
    f32 radius;
    f32 spread;
    f32 random0;
    f32 random1;
    u32 random2;
    u32 random3;
    f32 factor;
    f32 unit;
    f32 size;

    position[0] = arg0;
    position[1] = arg1;
    position[2] = arg2;
    radius = *(f32 *)(arg6 + 0x40);
    factor = func_150ADA68();
    unit = D_800BE9A8;
    zero[0] = 0.0f;
    zero[1] = 0.0f;
    zero[2] = 0.0f;
    factor = (factor * 166.0f + 160.0f) * D_800A8DC8;
    velocity[0] = -arg3 * unit * factor;
    velocity[1] = -arg4 * unit * factor;
    velocity[2] = -arg5 * unit * factor;
    random0 = func_150ADA68();
    random1 = func_150ADA68();
    random2 = func_150ADA20();
    random3 = func_150ADA20();
    spread = ((random0 * D_800A8DCC) + -600.0f) * D_800A8DD0;
    size = (random1 * 500.0f + 400.0f) * radius;
    func_151A26EC(position, zero, velocity, 1.0f, spread,
                  size,
                  (random2 % 21U) + 15, (random3 % 101U) + 100,
                  15, 20, 0, -1, 86, 39, 0, arg6[0xC], arg6[1]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A7610 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4AC0/func_151A7610.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A77C0 CURRENT (240) */
void func_151A77C0(u8 *arg0) {
    s16 temp_v1;
    s32 temp_lo;
    s8 temp_lo_2;
    u8 *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    temp_v0 = (void *)(arg0 + 0x50);
    if (temp_v1 < *(s16 *)((u8 *)arg0 + 0x54)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (temp_v1 * *(s16 *)((u8 *)arg0 + 0x56));
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 8)) {
        temp_lo = *(s16 *)((u8 *)temp_v0 + 0xA) * D_800BE9E4;
        *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + temp_lo);
        *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) + temp_lo);
    }
    if (*(s16 *)((u8 *)arg0 + 0x38) < *(s16 *)((u8 *)arg0 + 0x50)) {
        *(s8 *)((u8 *)arg0 + 0x2F) = 0x15;
        *(u16 *)((u8 *)arg0 + 0x44) = (u16) (*(u16 *)((u8 *)arg0 + 0x44) | 0x201);
        temp_lo_2 = *(s16 *)((u8 *)arg0 + 0x38) * *(s16 *)((u8 *)temp_v0 + 2);
        *(s32 *)((u8 *)arg0 + 0x14) = 0xC000F;
        *(s8 *)((u8 *)arg0 + 0x42) = temp_lo_2;
        *(s8 *)((u8 *)arg0 + 0x41) = temp_lo_2;
        *(s8 *)((u8 *)arg0 + 0x40) = temp_lo_2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A77C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4AC0/func_151A77C0.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A787C CURRENT (155) */
void func_151A787C(u8 *arg0) {
    s16 temp_v1;
    s32 temp_lo;
    s8 temp_lo_2;
    u8 *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    temp_v0 = (void *)(arg0 + 0x50);
    if (temp_v1 < *(s16 *)((u8 *)arg0 + 0x54)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (temp_v1 * *(s16 *)((u8 *)arg0 + 0x56));
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 8)) {
        temp_lo = *(s16 *)((u8 *)temp_v0 + 0xA) * D_800BE9E4;
        *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + temp_lo);
        *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) + temp_lo);
    }
    temp_lo_2 = *(s16 *)((u8 *)arg0 + 0x38) * *(s16 *)((u8 *)temp_v0 + 2);
    *(s8 *)((u8 *)arg0 + 0x42) = temp_lo_2;
    *(s8 *)((u8 *)arg0 + 0x41) = temp_lo_2;
    *(s8 *)((u8 *)arg0 + 0x40) = temp_lo_2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A787C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4AC0/func_151A787C.s")
void func_1516972C(s32, void *);

void func_151A7908(void *arg0) {
    void *temp_v0;

    temp_v0 = (u8 *)arg0 + 0x170;
    if (*(s32 *)((u8 *)arg0 + 0x174) != 0) {
        func_1516972C(*(s32 *)((u8 *)temp_v0 + 4), arg0);
        *(s32 *)((u8 *)temp_v0 + 4) = 0;
    }
}
