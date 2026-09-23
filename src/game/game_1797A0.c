#include "types.h"

/*
 * Reviewed source unit: src/game/game_1797A0.c
 * Boundary evidence: docs/evidence/game_raw_particle_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514C2F0
 * - func_1514C470
 * - func_1514C678
 * - func_1514C858
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef s32 (*Game1797A0Callback)(s32, s16, f32, f32, f32, f32,
                                  f32, f32, s32, s32, f32, s32, f32, s32, s32);
f32 func_151423D8(u8);
extern Game1797A0Callback D_8008AA00[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514C2F0 CURRENT (2223) */
void func_1514C2F0(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                   u8 arg4, volatile s8 arg5, s16 arg6, u8 arg7, s32 arg8,
                   f32 arg9, s32 arg10, u8 arg11) {
    s32 angle = arg4 & 0xFF;
    s16 index = 0;

    if (arg6 > 0) {
        do {
            s32 old_angle = angle;
            f32 start = func_151423D8((angle - 0x40) & 0xFF);
            f32 end_value = (arg3 * func_151423D8(angle & 0xFF)) + arg2;
            Game1797A0Callback callback = D_8008AA00[arg7];

            if (callback != 0 &&
                callback(1, index, (arg3 * start) + arg0, arg1,
                         end_value, arg0, arg1, arg2,
                         old_angle, arg4, arg3, arg8, arg9, arg10, arg11) == 0) {
                return;
            }
            index++;
            angle = (old_angle + arg5) & 0xFF;
        } while (index < arg6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514C2F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1797A0/func_1514C2F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1797A0/func_1514C470.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1797A0/func_1514C678.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1797A0/func_1514C858.s")
