#include "types.h"

/*
 * Reviewed source unit: src/game/game_AD6B0.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15080200
 * - func_15080348
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800D1928;
extern s32 D_800D192C;
extern s32 D_800D1930;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15080200 CURRENT (420) */
void func_15080200(void) {
    D_800D192C = 0;
    D_800D1928 = 0;
    D_800D1930 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15080200 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD6B0/func_15080200.s")
void func_15080430(u8 *, s32, s32);
s32 func_100126E8(u8 *, s32);
extern u8 D_800CC2D0;
extern u8 D_800D18D0;

void func_15080228(void) {
    u8 buffer[0x100];
    s32 var_a2;

    if (func_100126E8(buffer, 0x100) != 0) {
        do {
            if (buffer[0] == 0x4C) {
                var_a2 = buffer[4] & 0x7F;
                var_a2 = (buffer[5] & 0x7F) | (var_a2 << 7);
                var_a2 = (buffer[6] & 0x7F) | (var_a2 << 7);
                var_a2 = (buffer[7] & 0x7F) | (var_a2 << 7);
                var_a2 /= 367;
                if (var_a2 == 0) {
                    var_a2 = 0x14;
                }
                func_15080430(&D_800CC2D0 + (D_800D18D0 * 0x32C),
                              buffer[3] - 1, var_a2);
            }
        } while (func_100126E8(buffer, 0x100) != 0);
    }
}
s32 func_151EF610(void);
extern s32 D_800427F0;
extern s32 D_8009BD10;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15080348 CURRENT (113) */
void func_15080348(u8 *arg0) {
    s32 sp1C;
    s32 var_v1;

    if ((D_800D1928 != 0) && (arg0 != 0)) {
        if (D_800D1928 == 1) {
            if (D_800427F0 < 0x3E8) {
                arg0[0x1FF] = 0;
            } else {
                arg0[0x1FF] = 1;
            }
        } else {
            var_v1 = D_800D192C;
            if (D_800427F0 >= 0x3E9) {
                var_v1 += 1;
                if ((arg0[0x135] - D_800BE9E4) < 0) {
                if (var_v1 >= 5) {
                    var_v1 = 0;
                }
                arg0[0x134] = (s8)*(&D_8009BD10 + var_v1);
                sp1C = var_v1;
                arg0[0x135] = (u8)((func_151EF610() % 7) + 4);
                D_800D192C = var_v1;
                }
            }
        }
        D_800427F0 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15080348 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD6B0/func_15080348.s")
void func_1507E500(u8 *, s32, s32);
s32 func_1507E968(void *);

void func_15080430(u8 *arg0, s32 arg1, s32 arg2) {
    s32 active;

    if (arg0 != 0) {
        if (func_1507E968(arg0) > 0) {
            if (arg1 == 0) {
                D_800D1928 = 0;
                *(s16 *)(arg0 + 0x72) = 0x14;
                func_1507E500(arg0, 0, 0xA);
                return;
            }
            *(u16 *)(arg0 + 0x72) = 0xFFFE;
            if (arg1 == 1) {
                D_800D1928 = 2;
                return;
            }
            if (arg2 != 0) {
                if (arg2 >= 0x15) {
                    arg2 = 0x14;
                }
                if (arg2 <= 0) {
                    arg2 = 1;
                }
            }
            func_1507E500(arg0, arg1, arg2);
            return;
        }
        active = arg1 != 0;
        D_800D1928 = active;
        if (active == 0) {
            arg0[0x1FF] = 0;
        }
    }
}
