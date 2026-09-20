#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B9210.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518BD60
 * - func_1518C0B8
 * - func_1518C540
 * - func_1518C57C
 * - func_1518C69C
 * - func_1518C850
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518BD60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518C0B8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518C540 CURRENT (615) */
s32 func_1518C540(void *arg0) {
    s32 temp_t6;
    s32 var_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    if (temp_t6 < 0x100) {
        var_v1 = temp_t6;
    } else {
        var_v1 = -1;
    }
    *(s8 *)((u8 *)temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518C540 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518C540.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518C57C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518C69C.s")
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518C850 CURRENT (515) */
void func_1518C850(void *arg0, void *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    if (arg2 == 0x2D) {
        temp_v0 = *(s32 *)arg1;
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x24);
        if (temp_v0 == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x24) = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0x28) = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x24) = temp_v0;
            *(u8 *)((u8 *)arg0 + 0x28) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if ((arg2 == 0) &&
               ((*(s32 *)arg1 == *(s32 *)((u8 *)arg0 + 0x24)) ||
                (*(u8 *)((u8 *)arg0 + 0x28) == *(u8 *)((u8 *)arg1 + 4)))) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518C850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518C850.s")
