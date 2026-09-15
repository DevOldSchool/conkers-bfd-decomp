#include "types.h"

/*
 * Reviewed source unit: src/game/game_1897A0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515C388
 * - func_1515C534
 * - func_1515C6F4
 * - func_1515CF9C
 * - func_1515D088
 * - func_1515D130
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10022EC0(void *, void *, s32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void *func_1515C2F0(void *arg0, void *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    void *temp_v0;
    void *sp3C;

    *(s32 *)((u8 *)arg0 + 0x10) = 0xA;
    temp_v0 = func_15147A80(arg0, (u8 *)arg1 + 0x40, 0x10, 8, 8, 8, 0, 0,
                            arg3, arg4, arg5);
    if (temp_v0 == 0) {
        return 0;
    }
    sp3C = temp_v0;
    func_10022EC0(*(void **)((u8 *)temp_v0 + 0x98), (void *)arg2, 0x3C);
    return sp3C;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C388.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C534.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C6F4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515CF9C CURRENT (370) */
s32 func_1515CF9C(void *arg0, void *arg1) {
    s8 temp_v0;
    s32 *temp_v1;
    s32 *temp_t1;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x2C);
    if (temp_v0 < (*(u8 *)((u8 *)arg0 + 0x25) - 1)) {
        temp_v1 = *(s32 **)((u8 *)arg0 + 0x94);
        temp_t1 = (s32 *)((u8 *)temp_v1 + (*(s8 *)((u8 *)arg0 + 0x2E) * 0x10));
        *(s8 *)((u8 *)arg0 + 0x2C) = (s8)(temp_v0 + 1);
        temp_t1[0] = *(s32 *)((u8 *)arg0 + 0x10);
        temp_t1[1] = *(s32 *)((u8 *)arg0 + 0x14);
        temp_t1[2] = *(s32 *)((u8 *)arg0 + 0x18);
        *(f32 *)((u8 *)temp_v1 + (*(s8 *)((u8 *)arg0 + 0x2E) * 0x10) + 0xC) = *(f32 *)((u8 *)arg1 + 8);
        *(s8 *)((u8 *)arg0 + 0x2E) = (s8)(*(s8 *)((u8 *)arg0 + 0x2E) + 1);
        if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2E)) {
            *(s8 *)((u8 *)arg0 + 0x2E) = 0;
        }
    } else {
        *(s8 *)((u8 *)arg1 + 0x39) = -1;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515CF9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515CF9C.s")
s32 func_1515D030(void *arg0, s32 arg1) {
    s32 var_v1;
    s8 temp_v0;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x2C);
    var_v1 = 1;
    if (temp_v0 >= 3) {
        *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (temp_v0 - 1);
        *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(s8 *)((u8 *)arg0 + 0x2E) - 1);
        if (*(s8 *)((u8 *)arg0 + 0x2E) < 0) {
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(u8 *)((u8 *)arg0 + 0x25) - 1);
        }
    } else {
        var_v1 = 0;
    }
    return var_v1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515D088.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515D130.s")
