#include "types.h"

/*
 * Reviewed source unit: src/game/game_58F80.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1502BAD0
 * - func_1502BD84
 * - func_1502BEE4
 * - func_1502C1A4
 * - func_1502C380
 * - func_1502C408
 * - func_1502C608
 * - func_1502C6E8
 * - func_1502C974
 * - func_1502CC34
 * - func_1502CCFC
 * - func_1502D54C
 * - func_1502D630
 * - func_1502D824
 * - func_1502DB20
 * - func_1502DB84
 * - func_1502DF38
 * - func_1502E4C4
 * - func_1502EA0C
 * - func_1502EAFC
 * - func_1502EC34
 * - func_1502EE8C
 * - func_1502EEF4
 * - func_1502F01C
 * - func_1502F264
 * - func_1502F3C8
 * - func_1502F490
 * - func_1502F948
 * - func_1502F9FC
 * - func_1502FBE8
 * - func_1502FD70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502BAD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502BD84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502BEE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C1A4.s")
extern u8 D_800BE9C0;
extern s16 D_800C3E7A;
extern void *D_800C3E80[];
void func_150A9984(void *, u16);
typedef struct {
    s32 field_0;
} Game58F80Word;
extern Game58F80Word D_800C3E88;
extern s32 D_800C3E8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502C380 CURRENT (360) */
void func_1502C380(void) {
    void *temp_t8;

    temp_t8 = D_800C3E80[D_800BE9C0];
    D_800C3E88.field_0 = (s32)temp_t8;
    D_800C3E8C = (s32)temp_t8;
    D_800C3E7A = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502C380 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C380.s")
extern u8 D_800CC406[];

u8 func_1502C3BC(s32 arg0) {
    u8 var_v1;

    var_v1 = D_800CC406[arg0 * 0x32C];
    if ((s32)var_v1 >= 0x46) {
        var_v1 = 0xB;
    }
    return var_v1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C408.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C608.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C6E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C974.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502CC34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502CCFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D54C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D824.s")
extern u16 D_800C4ED0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502DB20 CURRENT (200) */
s32 func_1502DB20(s32 arg0) {
    switch (arg0) {
        case 0x3B:
        case 0x75:
        case 0x82:
        case 0x88:
        case 0x90:
        case 0x96:
        case 0x98:
        case 0x9C:
        case 0x9D:
        case 0x9F:
        case 0xA0:
        case 0xB1:
        case 0xB2:
        case 0xB4:
            return D_800C4ED0[arg0] - 4;
        default:
            return D_800C4ED0[arg0];
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502DB20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DB20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DB84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DF38.s")
extern s8 D_800C3E90;

void func_1502E474(void) {
    if ((u16)D_800C3E7A != 0) {
        func_150A9984(D_800C3E80[D_800BE9C0], (u16)D_800C3E7A);
    }
    D_800C3E90 = 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502E4C4.s")
void func_1502E9FC(s32 arg0, s32 arg1) {
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502EA0C CURRENT (860) */
void func_1502EA0C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    *(s8 *)((u8 *)arg0 + 0xA4) = 4;
    *(s8 *)((u8 *)arg0 + 0xA5) = 0;
    *(s8 *)((u8 *)arg0 + 0xA6) = (s8) arg5;
    *(s8 *)((u8 *)arg0 + 0xA7) = 0xFF;
    *(s32 *)((u8 *)arg0 + 0xA0) = (s32) ((arg4 << 0x18) | (arg1 << 0x10) | (arg2 << 8) | arg3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502EA0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EA0C.s")
void func_1502EA50(u8 *arg0) {
    arg0[0xA4] = 5;
}
void func_1502EA60(u8 *arg0, s32 arg1) {
    arg0[0xA4] = 2;
    arg0[0xA5] = 0xFF;
    arg0[0xA6] = arg1;
}
void func_1502EA7C(u8 *arg0, s32 arg1) {
    arg0[0xA4] = 3;
    arg0[0xA5] = 0xFF;
    arg0[0xA6] = arg1;
}
void func_1502EA98(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0xA4);
    if ((temp_v0 != 6) && (temp_v0 != 7)) {
        if (arg5 != 0) {
            *(u8 *)((u8 *)arg0 + 0xA5) = 0xFF;
        } else {
            *(s8 *)((u8 *)arg0 + 0xA5) = 0;
        }
        *(s32 *)((u8 *)arg0 + 0xA0) = (s32) ((arg4 << 0x18) | (arg1 << 0x10) | (arg2 << 8) | arg3);
        *(s8 *)((u8 *)arg0 + 0xA6) = (s8) arg6;
    }
    *(u8 *)((u8 *)arg0 + 0xA4) = 6U;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EAFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EC34.s")
extern u8 D_800CC33A[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502EE8C CURRENT (450) */
s32 func_1502EE8C(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = D_800CC33A[(arg0 * 0x32C) + arg1];
    var_v1 = temp_v0;
    if (temp_v0 >= 2) {
        if (temp_v0 >= 4) {
            var_v1 = 2;
        } else {
            var_v1 = temp_v0 - 2;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502EE8C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EE8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EEF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F01C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F3C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F490.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F948.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F9FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502FBE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502FD70.s")
