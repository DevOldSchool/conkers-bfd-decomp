#include "types.h"

/*
 * Reviewed source unit: src/game/game_183640.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15156190
 * - func_15156388
 * - func_151563B8
 * - func_151564F8
 * - func_151568F8
 * - func_15156B54
 * - func_15156D24
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156190.s")
void func_15156190(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15156388 CURRENT (510) */
void func_15156388(s32 arg0, s32 arg1, s32 arg2) {
    func_15156190(arg0, arg1 & 0xFF, arg2, 0xFF, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15156388 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156388.s")
void func_1516972C(u8 *);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151563B8 CURRENT (30) */
void func_151563B8(u8 *arg0) {
    s32 value;
    s16 product;
    s32 expired;

    expired = 0;
    if (arg0[0x40] & 1) {
        *(s16 *)(arg0 + 0x42) = *(s16 *)(arg0 + 0x42) - D_800BE9E4;
        if (*(s16 *)(arg0 + 0x42) < 0) {
            expired = 1;
        }
    }
    if (expired == 0) {
        *(f32 *)(arg0 + 0x10) += *(f32 *)(arg0 + 0x1C) * D_800BE9A4;
        *(f32 *)(arg0 + 0x14) += *(f32 *)(arg0 + 0x20) * D_800BE9A4;
        *(f32 *)(arg0 + 0x18) += *(f32 *)(arg0 + 0x24) * D_800BE9A4;
        *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x34) * D_800BE9A4;
        *(f32 *)(arg0 + 0x2C) += *(f32 *)(arg0 + 0x38) * D_800BE9A4;
        *(f32 *)(arg0 + 0x30) += *(f32 *)(arg0 + 0x3C) * D_800BE9A4;
        if (arg0[0x40] & 8) {
            value = *(s16 *)(arg0 + 0x42);
            if (value < *(s16 *)(arg0 + 0x4E)) {
                product = value * *(s16 *)(arg0 + 0x50);
                if (product < arg0[0x4C]) {
                    arg0[0x4C] = product;
                }
            }
        }
    }
    if (expired != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151563B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151563B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151564F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151568F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156B54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156D24.s")
void func_15156F94(s32 arg0) {
    func_151D5E30(arg0 + 0x88, arg0);
}
void func_15169804(s32);

void func_15156FB8(s32 arg0) {
    func_15156F94(arg0);
    func_15169804(arg0);
}
void func_15169824(s32 arg0);

void func_15156FE4(s32 arg0) {
    func_15156F94(arg0);
    func_15169824(arg0);
}
