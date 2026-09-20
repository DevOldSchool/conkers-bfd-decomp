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
 * - func_1502CCFC
 * - func_1502D54C
 * - func_1502D630
 * - func_1502D824
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
typedef struct Game58F80ActorC608 {
    u8 pad0[7];
    u8 field_7;
    u8 pad8[0x58];
    s16 field_60;
    s16 field_62;
} Game58F80ActorC608;

extern u8 D_800BEAC0;
extern u8 D_800CC2D0;
extern u8 *D_8008CA4C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502C608 CURRENT (821) */
void func_1502C608(s32 arg0) {
    s16 sp22;
    s16 sp20;
    void *sp18;
    s16 temp_a2;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 var_v1;
    s32 temp_t2;
    void *temp_a1;

    if (D_800BEAC0 == 0) {
        temp_a1 = (u8 *)&D_800CC2D0 + (arg0 * 0x32C);
        temp_v1 = *(s16 *)((u8 *)temp_a1 + 0x60);
        temp_a2 = *(s16 *)((u8 *)temp_a1 + 0x62);
        if (*(u8 *)((u8 *)temp_a1 + 7) != 0) {
            sp22 = temp_v1;
            sp18 = temp_a1;
            sp20 = temp_a2;
            temp_t2 = D_8008CA4C[func_1502C3BC(arg0)][4] << 8;
            temp_v1 = sp22;
            temp_a2 = sp20;
            temp_a1 = sp18;
            temp_v1_2 = temp_v1 + temp_a2;
            var_v1 = temp_v1_2;
            if (temp_v1_2 >= temp_t2) {
                var_v1 = temp_v1_2 - temp_t2;
            } else if (var_v1 < 0) {
                var_v1 += temp_t2;
            }
            *(s16 *)((u8 *)temp_a1 + 0x60) = var_v1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502C608 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C608.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C6E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C974.s")
void func_1502EC34(u8 *, s32 *, s32 *, s32 *, s32 *);
extern u8 D_800D9B68[];
extern u8 D_800D9B78[];

void func_1502CC34(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *arg10, s32 *arg11, s32 *arg12, s32 *arg13) {
    s32 offset;
    u8 *first;
    u8 *second;

    offset = arg1 * 3;
    first = D_800D9B68 + offset;
    *arg4 = first[0];
    second = D_800D9B78 + offset;
    *arg5 = first[1];
    *arg6 = first[2];
    *arg7 = second[0];
    *arg8 = second[1];
    *arg9 = second[2];
    *arg10 = 0;
    *arg11 = 0;
    *arg12 = 0;
    *arg13 = arg3[3];
    if (arg0[0xA4] != 0) {
        func_1502EC34(arg0, arg10, arg11, arg12, arg13);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502CCFC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502D54C CURRENT (335) */
void func_1502D54C(s32 arg0, void *arg1) {
    s32 temp_t1;
    void *temp_v0;

    temp_v0 = (u8 *)&D_800CC2D0 + (arg0 * 0x32C);
    if ((*(u8 *)((u8 *)temp_v0 + 0x66) & 0xC) == 4) {
        *(s32 *)((u8 *)arg1 + 0) =
            (s32)(*(u8 *)((u8 *)temp_v0 + 0x1E0) + *(u8 *)((u8 *)temp_v0 + 0x1DD)) / 2;
        *(s32 *)((u8 *)arg1 + 4) =
            (s32)(*(u8 *)((u8 *)temp_v0 + 0x1E1) + *(u8 *)((u8 *)temp_v0 + 0x1DE)) / 2;
        temp_t1 = (s32)(*(u8 *)((u8 *)temp_v0 + 0x1E2) +
                              *(u8 *)((u8 *)temp_v0 + 0x1DF)) / 2;
        *(s32 *)((u8 *)arg1 + 8) = temp_t1;
        *(s32 *)((u8 *)arg1 + 0) = 0xFF - *(s32 *)((u8 *)arg1 + 0);
        *(s32 *)((u8 *)arg1 + 4) = 0xFF - *(s32 *)((u8 *)arg1 + 4);
        *(s32 *)((u8 *)arg1 + 8) = 0xFF - temp_t1;
        return;
    }
    *(s32 *)((u8 *)arg1 + 8) = 0xFF;
    *(s32 *)((u8 *)arg1 + 4) = 0xFF;
    *(s32 *)((u8 *)arg1 + 0) = 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502D54C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D54C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D824.s")
extern u16 D_800C4ED0[];

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
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502EAFC CURRENT (1345) */
void func_1502EAFC(void *arg0) {
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_t1;
    u8 temp_t6;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;

    temp_t6 = *(u8 *)((u8 *)arg0 + 0xA4);
    switch (temp_t6) {
    case 2:
    case 3:
        temp_v1 = *(u8 *)((u8 *)arg0 + 0xA5);
        temp_lo = *(u8 *)((u8 *)arg0 + 0xA6) * D_800BE9E4;
        if (temp_lo < (s32) temp_v1) {
            *(u8 *)((u8 *)arg0 + 0xA5) = (u8) (temp_v1 - temp_lo);
            return;
        }
        *(u8 *)((u8 *)arg0 + 0xA5) = 0U;
        return;
    case 5:
        temp_v1_2 = *(u8 *)((u8 *)arg0 + 0xA7);
        temp_t1 = D_800BE9E4 * 0xA;
        if (temp_t1 < (s32) temp_v1_2) {
            *(u8 *)((u8 *)arg0 + 0xA7) = (u8) (temp_v1_2 - temp_t1);
        } else {
            *(u8 *)((u8 *)arg0 + 0xA4) = 0U;
        }
        /* fallthrough */
    case 4:
        *(u8 *)((u8 *)arg0 + 0xA5) = (u8) (*(u8 *)((u8 *)arg0 + 0xA5) + (*(u8 *)((u8 *)arg0 + 0xA6) * D_800BE9E4));
        return;
    case 6:
        temp_v1_3 = *(u8 *)((u8 *)arg0 + 0xA5);
        temp_lo_2 = *(u8 *)((u8 *)arg0 + 0xA6) * D_800BE9E4;
        if ((s32) temp_v1_3 < (0xFF - temp_lo_2)) {
            *(u8 *)((u8 *)arg0 + 0xA5) = (u8) (temp_v1_3 + temp_lo_2);
        } else {
            *(u8 *)((u8 *)arg0 + 0xA5) = 0xFFU;
        }
        *(u8 *)((u8 *)arg0 + 0xA4) = 7U;
        return;
    case 7:
        temp_v1_4 = *(u8 *)((u8 *)arg0 + 0xA5);
        temp_lo_3 = *(u8 *)((u8 *)arg0 + 0xA6) * D_800BE9E4;
        if (temp_lo_3 < (s32) temp_v1_4) {
            *(u8 *)((u8 *)arg0 + 0xA5) = (u8) (temp_v1_4 - temp_lo_3);
            return;
        }
        *(u8 *)((u8 *)arg0 + 0xA4) = 0U;
    default:
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502EAFC */
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
typedef struct Game58F80Actor {
    s32 active;
    u8 pad4[0x10];
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    u8 pad20[0x160];
    f32 field_180;
    u8 pad184[0x1A];
    u16 field_19E;
    u8 pad1A0[0xD4];
    u8 field_274;
    u8 pad275[0xB7];
} Game58F80Actor;

void func_1502F490(Game58F80Actor *, f32 *, f32 *, f32 *, s32);
extern u8 D_800CC2D0;
extern u8 D_800D121C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502F3C8 CURRENT (979) */
void func_1502F3C8(void) {
    Game58F80Actor *actor;
    f32 limit;
    f32 current;
    u8 other_index;

    actor = (Game58F80Actor *) &D_800CC2D0;
    do {
        if (actor->active != 0) {
            other_index = actor->field_274;
            if (other_index != 0) {
                actor->field_18 = actor->field_180;
                func_1502F490((Game58F80Actor *) ((u8 *) &D_800CC2D0 + (other_index * 0x32C) - 0x32C), &actor->field_14, &actor->field_18, &actor->field_1C, actor->field_19E);
                current = actor->field_18;
                limit = actor->field_180;
                if (current < limit) {
                    actor->field_18 = limit;
                } else {
                    actor->field_180 = current;
                }
            }
        }
        actor += 1;
    } while (actor != (Game58F80Actor *) &D_800D121C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502F3C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F3C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F490.s")
extern void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_10023A10(void *arg0, void *arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502F948 CURRENT (660) */
void func_1502F948(void *arg0) {
    s32 sp24;
    u8 temp_v1;
    void *temp_v0;

    if ((*(s32 *)((u8 *)arg0 + 0xF8) & 0x4000) == 0 ||
        *(s32 *)((u8 *)arg0 + 0x264) == 0 ||
        *(void **)((u8 *)arg0 + 0x1D4) == 0) {
        return;
    }
    temp_v1 = *(u8 *)((u8 *)arg0 + 4);
    temp_v0 = *(void **)((u8 *)arg0 + 0x1D8);
    if (temp_v0 == 0) {
        sp24 = temp_v1;
        temp_v0 = func_10003C40(D_800C4ED0[temp_v1] << 6, 1, 1, 2);
        *(void **)((u8 *)arg0 + 0x1D8) = temp_v0;
        if (temp_v0 == 0) {
            return;
        }
    }
    func_10023A10(*(void **)((u8 *)arg0 + 0x1D4), temp_v0, D_800C4ED0[temp_v1] << 6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502F948 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F948.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F9FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502FBE8.s")
extern u8 D_80038080;
extern s32 D_800BE9F0;
extern u8 D_800D2040;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502FD70 CURRENT (240) */
void func_1502FD70(void *arg0) {
    s32 temp_v0_3;
    u8 *temp_v1;
    u8 temp_a1;
    u8 temp_a2;
    u8 temp_v0;
    void *temp_v0_2;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if ((D_80038080 == 0) && (D_800BE9F0 == 0x1D)) {
        *(&D_800D2040 + temp_v0) = 2;
        return;
    }
    temp_v1 = &D_800D2040 + temp_v0;
    temp_a1 = *temp_v1;
    if (temp_a1 != 0xFF) {
        temp_v0_2 = *(void **)((u8 *)arg0 + 0x144);
        if (temp_v0_2 != 0) {
            temp_a2 = *(u8 *)((u8 *)temp_v0_2 + 0x2E);
            if (temp_a2 != 0xFF) {
                if (temp_a2 != 0) {
                    temp_v0_3 = temp_a2 * 0x1E;
                    if ((s32)temp_a1 < temp_v0_3) {
                        *temp_v1 = (u8)temp_v0_3;
                    }
                } else {
                    goto block_9;
                }
            }
        } else {
block_9:
            *temp_v1 = 3;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502FD70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502FD70.s")
