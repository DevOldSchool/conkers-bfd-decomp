#include "types.h"

/*
 * Reviewed source unit: src/game/game_191C30.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15164780
 * - func_1516489C
 * - func_15164EE4
 * - func_15164F0C
 * - func_15165628
 * - func_151658DC
 * - func_15165B80
 * - func_15165BB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15164780.s")
void func_15164888(u8 *arg0) {
    arg0[0x10] |= 2;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_1516489C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15164EE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15164F0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15165628.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_151658DC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15165B80 CURRENT (1296) */
void func_15165B80(u8 *arg0) {
    func_15165BB0(arg0, arg0 + 0x108, *(f32 *)((u8 *)arg0 + 0x114), *(f32 *)((u8 *)arg0 + 0x118), *(f32 *)((u8 *)arg0 + 0x11C));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15165B80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15165B80.s")
f32 func_15143E64(f32 *, void *);                   /* extern */
void *func_15144B34(u8, void *);                    /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15165BB0 CURRENT (1233) */
f32 func_15165BB0(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sp28;
    f32 sp20;
    f32 sp24;
    f32 temp_fv0;
    f32 var_fv1;
    void *temp_v0;

    temp_v0 = func_15144B34(*(u8 *)((u8 *)arg0 + 0x16), arg0);
    sp20 = *(f32 *)((u8 *)arg1 + 0) - *(f32 *)((u8 *)temp_v0 + 0);
    sp24 = *(f32 *)((u8 *)arg1 + 4) - *(f32 *)((u8 *)temp_v0 + 4);
    sp28 = *(f32 *)((u8 *)arg1 + 8) - *(f32 *)((u8 *)temp_v0 + 8);
    temp_fv0 = func_15143E64(&sp20, arg1);
    if (temp_fv0 < arg2) {
        var_fv1 = 1.0f;
    } else if ((arg2 + arg3) < temp_fv0) {
        var_fv1 = 0.0f;
    } else {
        var_fv1 = 1.0f - ((temp_fv0 - arg2) * arg4);
    }
    return var_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15165BB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15165BB0.s")
