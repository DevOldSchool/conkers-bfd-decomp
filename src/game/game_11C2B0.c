#include "types.h"

/*
 * Reviewed source unit: src/game/game_11C2B0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EEE00
 * - func_150EEF40
 * - func_150EEF80
 * - func_150EF38C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15143134(f32 *, f32 *, s32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
void func_150EEF80(void *, u8, s32, s32);
void func_150F0A24(f32 *);
extern u8 D_800A15F0[];
extern u8 D_800A1638[];
extern u8 D_800A163C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EEE00 CURRENT (65) */
void func_150EEE00(void *arg0, u8 arg1) {
    struct {
        s32 position[3];
        u8 descriptor[8];
        f32 transformed[3];
    } work;
    u8 *state;
    s32 transform;

    state = arg0;
    if (!(D_800A163C[arg1] & *(s32 *)(state + 0x94))) {
        func_150EEF80(arg0, arg1, 0xFF, 1);
        transform = *(s32 *)(state + 0x1D4);
        if (transform != 0) {
            func_15143134((f32 *)&D_800A15F0[arg1 * 0xC], work.transformed,
                           transform + (D_800A1638[arg1] << 6));
            work.descriptor[0] = 3;
            *(s8 *)&work.descriptor[1] = -1;
            *(s16 *)&work.descriptor[2] = (func_150ADA20() % 3U) + 4;
            work.descriptor[4] = 0;
            work.position[0] = (s32)work.transformed[0];
            work.position[1] = (s32)work.transformed[1];
            work.position[2] = (s32)work.transformed[2];
            func_151602C0(work.descriptor, work.position, 0xFF, 0xFF,
                           0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
            func_150F0A24(work.transformed);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EEE00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EEE00.s")
extern void func_151403A8(void *arg0, s32 arg1, void *arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EEF40 CURRENT (440) */
void func_150EEF40(void *arg0, s32 arg1) {
    struct {
        void *field0;
        u8 field4;
        u8 field5;
    } sp18;

    sp18.field0 = arg0;
    sp18.field5 = arg1 & 0xFF;
    sp18.field4 = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151403A8(&sp18, 0x43, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EEF40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EEF40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EEF80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EF38C.s")
s32 func_150EF784(void *arg0, s32 arg1, s32 arg2) {
    if (*(u8 *)((u8 *)arg0 + 4) == 0x28) {
        return 1;
    }
    return 0;
}
