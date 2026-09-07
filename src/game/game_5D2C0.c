#include "types.h"

/*
 * Reviewed source unit: src/game/game_5D2C0.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1502FE10
 * - func_1502FFD8
 * - func_15030158
 * - func_15030310
 * - func_150303E4
 * - func_15030468
 * - func_15030AF4
 * - func_15030D54
 * - func_15030E08
 * - func_15030F94
 * - func_15031070
 * - func_150311C4
 * - func_1503192C
 * - func_1503195C
 * - func_150319CC
 * - func_15031A50
 * - func_15031C14
 * - func_15031E2C
 * - func_15031E7C
 * - func_15031FC8
 * - func_150331B8
 * - func_1503327C
 * - func_15033328
 * - func_150333A8
 * - func_15033440
 * - func_150334B8
 * - func_150335C8
 * - func_150337E4
 * - func_15033838
 * - func_150339C8
 * - func_15033AD8
 * - func_15033BDC
 * - func_15033E28
 * - func_15033E84
 * - func_15033EC4
 * - func_15033F0C
 * - func_15033F70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1502FE10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1502FFD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030158.s")
void func_15030310(void *arg0, s32 arg1, s32 arg2);

void func_150302F0(void *arg0, s32 arg1) {
    func_15030310(arg0, arg1, 0xFF);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030310.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150303E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030AF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030D54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030E08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030F94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150311C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1503192C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1503195C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150319CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031C14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031E2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031E7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031FC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150331B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1503327C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033328.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150333A8.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15033440 CURRENT (1050) */
s32 func_15033440(void *arg0, void *arg1) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 1);
    if (temp_v0 != 0x27) {
        if (temp_v0 != 0x29) {
            if (temp_v0 == 0x35) {
                goto block_3;
            }
        } else if (*(u8 *)((u8 *)arg1 + 5) == 5) {
            *(s8 *)((u8 *)arg0 + 2) = 0;
        }
    } else {
block_3:
        if (*(u8 *)((u8 *)arg1 + 5) == 5) {
            *(s8 *)((u8 *)arg0 + 2) = 0;
            *(s16 *)((u8 *)arg0 + 0x22) = (s16) (*(s16 *)((u8 *)arg0 + 0x22) + (D_800BE9E4 * 0xAAA));
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15033440 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033440.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150334B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150335C8.s")
s32 func_1503378C(void *arg0, void *arg1) {
    u16 temp_v0;

    temp_v0 = *(u16 *)((u8 *)arg1 + 0x84);
    if ((*(u8 *)((u8 *)arg0 + 1) == 0x11) && ((temp_v0 == 0x3E) || (temp_v0 == 0x3D) || (temp_v0 == 0x41) || (temp_v0 == 0xD9) || (temp_v0 == 0x138) || (temp_v0 == 0x139))) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150337E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033838.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150339C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033AD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033BDC.s")
s32 func_15033E00(s32 arg0, void *arg1) {
    if (*(u8 *)((u8 *)arg1 + 5) == 3) {
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033E28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033E84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033EC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033F0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033F70.s")
