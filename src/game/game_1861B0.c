#include "types.h"

/*
 * Reviewed source unit: src/game/game_1861B0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15158D2C
 * - func_15158FA4
 * - func_15159084
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1514EDF0(s32 arg0, s32 arg1);
void func_15169824(s32 arg0);
void func_1516972C(void *arg0);
void func_1519F400(void *arg0);

void func_15158D00(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_15169824((s32) arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1861B0/func_15158D2C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158FA4 CURRENT (275) */
void func_15158FA4(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = arg2;
    if (temp_v0 == 0) {
        if ((*(s32 *)(arg0 + 0x18) == *(s32 *)arg1) ||
            (arg0[0x1C] == arg1[4])) {
            func_1516972C(arg0);
        }
    } else if (temp_v0 == 0x2D) {
        temp_v0 = *(s32 *)arg1;
        temp_v1 = *(s32 *)(arg0 + 0x18);
        if (temp_v0 == temp_v1) {
            *(s32 *)(arg0 + 0x18) = *(s32 *)(arg1 + 4);
            arg0[0x1C] = arg1[9];
            return;
        }
        if (*(s32 *)(arg1 + 4) != temp_v1) {
            return;
        }
        *(s32 *)(arg0 + 0x18) = temp_v0;
        arg0[0x1C] = arg1[8];
    } else if ((temp_v0 == 4) &&
               ((*(s32 *)(arg0 + 0x18) == *(s32 *)arg1) ||
                (arg0[0x1C] == arg1[4]))) {
        func_1519F400(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158FA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1861B0/func_15158FA4.s")
extern f32 D_800A63A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15159084 CURRENT (900) */
s32 func_15159084(void *arg0, u8 arg1) {
    f32 temp_fv0;
    s32 flags;
    s32 var_v1;

    flags = *(s32 *)((u8 *)arg0 + 0x184) & 0x1F;
    if ((arg1 == 2) || (arg1 == 3)) {
        var_v1 = 0;
    } else {
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x118);
        if ((D_800A63A0 == temp_fv0) && !(flags & 0xA)) {
            var_v1 = 1;
        } else if ((temp_fv0 < *(f32 *)((u8 *)arg0 + 0x18)) || (var_v1 = 0, (*(u8 *)((u8 *)arg0 + 0x137) != 0))) {
            var_v1 = 1;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15159084 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1861B0/func_15159084.s")
