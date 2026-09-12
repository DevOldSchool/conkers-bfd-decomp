#include "types.h"

/*
 * Reviewed source unit: src/game/game_64120.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15036C70
 * - func_15036CE8
 * - func_15036F34
 * - func_15037698
 * - func_15037880
 * - func_150379DC
 * - func_150380C0
 * - func_15038468
 * - func_15038620
 * - func_15039A78
 * - func_15039CC8
 * - func_15039ED0
 * - func_1503A08C
 * - func_1503A60C
 * - func_1503A678
 * - func_1503A7F0
 * - func_1503A830
 * - func_1503B708
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15036C70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15036CE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15036F34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15037698.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15037880.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_150379DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_150380C0.s")
/* Call context: func_150484A0: unique active project prototype */
f32 func_150484A0(f32, f32);
extern f32 D_80098648;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15038468 CURRENT (3799) */
void func_15038468(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fv0;

    switch (arg5) {                                 /* irregular */
    case 0:
        *arg0 = func_150484A0(arg2, arg4);
        var_fv0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
block_9:
        *arg1 = var_fv0;
        break;
    case 1:
        *arg0 = func_150484A0(-arg4, arg2);
        var_fv0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        goto block_9;
    case 2:
        *arg0 = func_150484A0(arg4, -arg2);
        var_fv0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        goto block_9;
    case 3:
        *arg0 = func_150484A0(arg4, -arg3);
        var_fv0 = func_150484A0(-arg2, sqrtf((arg3 * arg3) + (arg4 * arg4)));
        goto block_9;
    }
    *arg0 *= D_80098648;
    *arg1 *= D_80098648;
    temp_fv0 = *arg0;
    if (temp_fv0 > 180.0f) {
        *arg0 = temp_fv0 - 360.0f;
    }
    temp_fv0_2 = *arg1;
    if (temp_fv0_2 > 180.0f) {
        *arg1 = temp_fv0_2 - 360.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15038468 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15038468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15038620.s")
typedef struct Game64120Entry {
    u8 data[0x18];
} Game64120Entry;

extern Game64120Entry D_80098068[];

Game64120Entry *func_15039A54(s32 arg0, s32 arg1) {
    return &D_80098068[arg1];
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15039A78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15039CC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15039ED0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A08C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A60C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A678.s")
void func_15036F34(void);
void func_1503A678(void);
extern u8 D_800C3FFA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503A7F0 CURRENT (8) */
void func_1503A7F0(void) {
    s32 sp1C;
    s32 temp_t6;

    temp_t6 = D_800C3FFA;
    D_800C3FFA = 0;
    sp1C = temp_t6;
    func_15036F34();
    D_800C3FFA = sp1C;
    func_1503A678();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503A7F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A7F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A830.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503B708.s")
