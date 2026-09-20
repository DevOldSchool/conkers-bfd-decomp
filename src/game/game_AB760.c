#include "types.h"

/*
 * Reviewed source unit: src/game/game_AB760.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507E2B0
 * - func_1507E3C0
 * - func_1507E6B8
 * - func_1507E73C
 * - func_1507E7E4
 * - func_1507E908
 * - func_1507E968
 * - func_1507E9F8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E2B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E3C0.s")
void func_150302F0(void *, s32);
void func_1507E5C8(u8 *, s32);
u8 *func_1507E908(void *, s32);
void func_1507EA44(void *, s32, s32);
s32 func_1507E968(void *);
u8 *func_1507E9F8(void *, s32 *);
extern void *D_800D1C90[];

void func_1507E500(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *record;
    u8 *values;

    if (arg1 < func_1507E968(arg0)) {
        record = func_1507E908(arg0, arg0[0x6F]);
        if (record[4] != 0) {
            values = func_1507E9F8(arg0, 0);
            if (values != 0) {
                func_150302F0(arg0, values[record[4] - 1]);
            }
        }
        arg0[0x6F] = arg1;
        func_1507E5C8(arg0, arg2);
        if (arg2 != 0) {
            arg0[0x135] = arg2;
            return;
        }
        arg0[0x135] = func_1507E908(arg0, arg1)[3];
    }
}
void func_1507E5C8(u8 *arg0, s32 arg1) {
    u8 *record;
    u8 value;

    record = func_1507E908(arg0, arg0[0x6F]);
    if (record != 0) {
        func_1507EA44(arg0, record[4], *(u16 *)(record + 6));
        value = record[2];
        if (value != arg0[0x134]) {
            arg0[0x134] = value;
            if (arg1 == 0) {
                arg0[0x135] = record[3];
            } else {
                arg0[0x135] = arg1;
            }
        }
        arg0[0x6C] = record[0] + 0xA;
        arg0[0x6D] = record[1] + 0xA;
        value = record[8];
        if (value != 0) {
            arg0[0x68] = value;
        } else {
            arg0[0x68] = *((u8 *)D_800D1C90[arg0[4]] + 0x3B);
        }
        value = record[9];
        if (value != 0) {
            arg0[0x69] = value;
            return;
        }
        arg0[0x69] = *((u8 *)D_800D1C90[arg0[4]] + 0x3C);
    }
}
s32 func_150849A0();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E6B8 CURRENT (820) */
s32 func_1507E6B8(void *arg0) {
    s32 temp_v0;

    if (*(u8 *)((u8 *)arg0 + 0x1CA) == 0) {
        goto block_9;
    }
    if (*(u8 *)((u8 *)arg0 + 0x70) == *(u8 *)((u8 *)arg0 + 0x6F)) {
        return 1;
    }
    temp_v0 = func_150849A0();
    if (temp_v0 == 0) {
        if (*(u8 *)((u8 *)arg0 + 0x6F) == 0x15) {
            return 1;
        }
        goto block_9;
    }
    if (temp_v0 == 0x52) {
        return 1;
    }
block_9:
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E6B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E6B8.s")

typedef struct GameAB760State {
    u8 pad0[0x6A];
    u8 field_6A;
    u8 field_6B;
    u8 field_6C;
    u8 field_6D;
    u8 pad6E[2];
    u8 field_70;
    u8 field_71;
    u16 field_72;
} GameAB760State;

void func_1507E2B0(GameAB760State *);
void func_1507EABC(GameAB760State *);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E73C CURRENT (220) */
void func_1507E73C(GameAB760State *arg0) {
    u32 temp_v0;
    u16 temp_v1;

    if (arg0->pad0[5] != 2) {
        temp_v1 = arg0->field_72;
        if (temp_v1 != 0) {
            if (temp_v1 == 0xFFFE) {
                return;
            }
            temp_v0 = (u32)temp_v1;
            if (temp_v1 != 0xFFFF) {
                if (D_800BE9E4 < (s32)temp_v0) {
                    arg0->field_72 = temp_v0 - D_800BE9E4;
                } else {
                    arg0->field_72 = 0;
                }
            }
        }
        if (func_1507E6B8(arg0) != 0) {
            func_1507E2B0(arg0);
        }
        if ((arg0->field_72 == 0) && (arg0->field_70 != arg0->pad6E[1])) {
            func_1507EABC(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E73C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E73C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E7E4.s")

typedef struct GameAB760ValueRecord {
    s32 value;
    s32 pad4;
} GameAB760ValueRecord;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E908 CURRENT (1129) */
s32 func_1507E908(void *arg0, s32 arg1) {
    s32 value;
    s32 result;
    GameAB760ValueRecord *record;

    record = D_800D1C90[func_150849A0()];
    result = 0;
    if (record != 0) {
        value = record[-1].value;
        if (value != 0) {
            result = (arg1 * 0xA) + value;
        }
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E908 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E908.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E968 CURRENT (1440) */
u32 func_1507E968(void *arg0) {
    GameAB760ValueRecord *temp_v1;
    u32 var_v0;
    s32 var_v0_2;

    var_v0_2 = *(u8 *)((u8 *)arg0 + 4);
    if (var_v0_2 != 0x96) {
        var_v0_2 = func_150849A0();
    }
    if (var_v0_2 == 0xFF) {
        return 0U;
    }
    temp_v1 = D_800D1C90[var_v0_2];
    var_v0 = 0;
    if (temp_v1 != 0) {
        var_v0 = (u32)temp_v1[-1].pad4 / 10U;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E968 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E968.s")
void func_1507E9E8(s32 arg0, s32 arg1) {
}
extern u8 D_8009D910[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E9F8 CURRENT (100) */
void *func_1507E9F8(void *arg0, s32 *arg1) {
    if (func_150849A0() == 0) {
        if (arg1 != 0) {
            *arg1 = 5;
        }
        return D_8009D910;
    }
    if (arg1 != 0) {
        *arg1 = 0;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E9F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E9F8.s")
u8 *func_1507E9F8(void *, s32 *);
void func_15083568(void *, s32, f32, s32);
extern f32 D_8009B8A0;

void func_1507EA44(void *arg0, s32 arg1, s32 arg2) {
    u8 *values;

    if (arg1 != 0) {
        values = func_1507E9F8(arg0, 0);
        if (values != 0) {
            func_15083568(arg0, values[arg1 - 1], (f32)arg2 * D_8009B8A0, 0);
        }
    }
}
void func_1507E7E4(GameAB760State *, u8, u8, s32, s32);

void func_1507EABC(GameAB760State *arg0) {
    func_1507E7E4(arg0, arg0->field_70, 3, 0xFFFF, 0xA);
    arg0->field_71 = 0;
    arg0->field_72 = 0;
    if (arg0->field_6C >= 0xA) {
        arg0->field_6C = 0;
        arg0->field_6A = 0;
    }
    if (arg0->field_6D >= 0xA) {
        arg0->field_6D = 0;
        arg0->field_6B = 0;
    }
}
void func_1507EB4C(GameAB760State *arg0, s32 arg1);

void func_1507EB2C(GameAB760State *arg0) {
    func_1507EB4C(arg0, 0);
}

void func_1507EB4C(GameAB760State *arg0, s32 arg1) {
    if (arg1 != arg0->field_70) {
        arg0->field_70 = (u8)arg1;
        func_1507EABC(arg0);
    }
}
