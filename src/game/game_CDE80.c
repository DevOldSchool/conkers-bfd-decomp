#include "types.h"

/*
 * Reviewed source unit: src/game/game_CDE80.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A09D0
 * - func_150A0D14
 * - func_150A0D8C
 * - func_150A104C
 * - func_150A11C4
 * - func_150A1DA0
 * - func_150A23E4
 * - func_150A24C0
 * - func_150A25D4
 * - func_150A278C
 * - func_150A2864
 * - func_150A2940
 * - func_150A29C8
 * - func_150A2AEC
 * - func_150A2CA4
 * - func_150A2D84
 * - func_150A2E4C
 * - func_150A2EE4
 * - func_150A2FA4
 * - func_150A3058
 * - func_150A3194
 * - func_150A32B4
 * - func_150A3330
 * - func_150A3398
 * - func_150A3444
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A09D0.s")
f32 func_150AD780(f32);                             /* extern */
f32 func_150AD78C(f32);                             /* extern */
extern f32 D_8009F5A0;
extern f32 D_8009F5A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A0D14 CURRENT (1514) */
void func_150A0D14(void *arg0) {
    f32 temp_fs0;
    f32 temp_fs0_2;

    temp_fs0 = *(f32 *)((u8 *)arg0 + 0xC) * D_8009F5A0;
    *(f32 *)((u8 *)arg0 + 0x24) = func_150AD78C(temp_fs0);
    *(f32 *)((u8 *)arg0 + 0x28) = func_150AD780(temp_fs0);
    temp_fs0_2 = *(f32 *)((u8 *)arg0 + 0x10) * D_8009F5A4;
    *(f32 *)((u8 *)arg0 + 0x2C) = func_150AD78C(temp_fs0_2);
    *(f32 *)((u8 *)arg0 + 0x30) = func_150AD780(temp_fs0_2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A0D14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A0D14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A0D8C.s")
s32 func_150A1040(s32 arg0) {
    return arg0 + 0x400;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A104C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A11C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A1DA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A23E4.s")
s32 func_15183290(s16, s32, s16, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A24C0 CURRENT (1541) */
void func_150A24C0(void *arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;

    if (arg1 != 0xFF) {
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x1C);
        {
            s32 temp_a0 = temp_v1 & 0xFF;
        if ((temp_a0 == 0) || (*(u8 *)((u8 *)arg0 + 0x17) == 9)) {
            temp_v0 = func_15183290(*(s16 *)((u8 *)arg0 + 0), *(s16 *)((u8 *)arg0 + 2) + (*(u8 *)((u8 *)arg0 + 0x1D) * 0x10), *(s16 *)((u8 *)arg0 + 4), *(s32 *)((u8 *)arg0 + 0x18) & 0xFF, (s32) *(u8 *)((u8 *)arg0 + 0x17), (s32) *(s16 *)((u8 *)arg0 + 6), arg1, (s32) (s16) *(s32 *)((u8 *)arg0 + 0x18), (s32) *(u8 *)((u8 *)arg0 + 0x1A), (s32) (u8) *(s32 *)((u8 *)arg0 + 0x1C), *(s32 *)((u8 *)arg0 + 0x20));
            if ((temp_v0 != -1) && (*(u8 *)((u8 *)arg0 + 0x17) != 9)) {
                *(s32 *)((u8 *)arg0 + 0x1C) = (s32) ((temp_v0 << 8) | 0xF0 | (*(s32 *)((u8 *)arg0 + 0x1C) & 0xFFFF0000));
            }
        } else {
            var_v0 = temp_a0;
            if (temp_a0 < 2) {
                var_v0 = 2;
            }
            *(s32 *)((u8 *)arg0 + 0x1C) = (s32) ((temp_v1 & ~0xFF) | var_v0);
        }
    }
        }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A24C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A24C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A25D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A278C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2864.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2940.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A29C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2AEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2CA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2D84.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A2E4C CURRENT (2248) */
s32 func_150A2E4C(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fa1;

    temp_fa1 = arg2 - (f32) *(s16 *)((u8 *)arg0 + 2);
    arg3 = temp_fa1 - (f32) *(s16 *)((u8 *)arg0 + 4);
    if (((((arg3 * *(f32 *)((u8 *)arg0 + 0x30)) + ((arg1 - (f32) *(s16 *)((u8 *)arg0 + 0)) * *(f32 *)((u8 *)arg0 + 0x2C))) * *(f32 *)((u8 *)arg0 + 0x28)) - (temp_fa1 * *(f32 *)((u8 *)arg0 + 0x24))) <= 0.0f) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A2E4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2E4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2EE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2FA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A3058.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A3194.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A32B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A3330.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A3398.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A3444.s")
