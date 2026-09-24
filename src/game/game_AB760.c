#include "types.h"

/*
 * Reviewed source unit: src/game/game_AB760.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507E2B0
 * - func_1507E3C0
 * - func_1507E73C
 * - func_1507E7E4
 * - func_1507E908
 * - func_1507E968
 * - func_1507E9F8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

struct GameAB760State;
u32 func_150ADA20(void);
extern u8 D_800C35EA;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E2B0 CURRENT (255) */
void func_1507E2B0(struct GameAB760State *arg0) {
    u8 *state = (u8 *)arg0;
    u8 temp_t6;
    u8 temp_v0;
    s32 one;

    if ((state[4] != 0x2B) && (D_800C35EA != 1)) {
        if ((state[0x127] != 0xFF) &&
            (*(u8 *)((u8 *)*(void **)(state + 0x31C) + 0x120) != 0)) {
            one = 1;
            state[0x6A] = one;
            state[0x6B] = one;
            return;
        }
        if ((s32)state[0x6A] >= 3) {
            state[0x6A] = 0;
        }
        if ((s32)state[0x6B] >= 3) {
            state[0x6B] = 0;
        }
        temp_v0 = state[0x6E];
        one = 1;
        if ((s32)temp_v0 >= D_800BE9E4) {
            state[0x6E] = temp_v0 - D_800BE9E4;
            return;
        }
        state[0x6E] = 0;
        if (state[0x6C] != 1) {
            temp_t6 = state[0x6A] ^ 1;
            state[0x6A] = temp_t6;
            state[0x6B] ^= 1;
            if (!(temp_t6 & 0xFF)) {
                state[0x6E] = (func_150ADA20() % 140U) + 0xA;
                return;
            }
            state[0x6E] = one;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E2B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E2B0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E3C0 CURRENT (1296) */
void func_1507E3C0(void *arg0) {
    s32 values[2];
    s32 *var_v1;
    s32 temp_t2;
    s32 temp_v0_2;
    u8 temp_t6;
    u8 temp_v0;
    u8 *var_a1;
    u8 *state;

    state = arg0;
    temp_v0 = state[4];
    var_v1 = values;
    var_a1 = state;
    if ((temp_v0 == 0xF) || (temp_v0 == 0x46) || (temp_v0 == 0x4C)) {
        do {
            temp_t6 = var_a1[0x6C];
            *var_v1 = temp_t6;
            if (temp_t6 >= 0xA) {
                temp_v0_2 = temp_t6 - 0xA;
                *var_v1 = temp_v0_2;
                if (temp_v0_2 == 5) {
                    *var_v1 = 0;
                } else if (temp_v0_2 == 1) {
                    *var_v1 = 1;
                } else {
                    *var_v1 = 2;
                }
            } else if (temp_t6 < 2) {
                *var_v1 = temp_t6 + 1;
            }
            var_v1++;
            var_a1++;
        } while (var_v1 != &values[2]);
        temp_t2 = *(s32 *)(state + 0x94) | 0x7E;
        *(s32 *)(state + 0x94) = temp_t2;
        if (values[0] == 0) {
            *(s32 *)(state + 0x94) = temp_t2 & ~8;
        } else if (values[0] == 1) {
            *(s32 *)(state + 0x94) &= ~0x10;
        } else {
            *(s32 *)(state + 0x94) &= ~4;
        }
        if (values[1] == 0) {
            *(s32 *)(state + 0x94) &= ~0x20;
        } else if (values[1] == 1) {
            *(s32 *)(state + 0x94) &= ~0x40;
        } else {
            *(s32 *)(state + 0x94) &= ~2;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E3C0 */
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

s32 func_1507E6B8(void *arg0) {
    s32 temp_v0;
    u8 value;

    if (*(u8 *)((u8 *)arg0 + 0x1CA) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 0x70) == *(u8 *)((u8 *)arg0 + 0x6F)) {
        return 1;
    }
    temp_v0 = func_150849A0();
    value = *(u8 *)((u8 *)arg0 + 0x6F);
    if (temp_v0 == 0) {
        if (value == 0x15) {
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E7E4 CURRENT (132) */
void func_1507E7E4(GameAB760State *arg0, u8 arg1, u8 arg2, u16 arg3, s32 arg4) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 temp_v1;

    temp_v1 = arg0->pad6E[1];
    if (((arg1 != temp_v1) || (arg2 != arg0->field_71) ||
         (arg0->field_72 != arg3)) &&
        ((arg2 == 3) || (temp_v1 == arg0->field_70) ||
         (temp_v1 == arg1) || (arg0->field_72 == 0) ||
         ((s32)arg0->field_71 < arg2))) {
        if ((s32)arg1 < func_1507E968(arg0)) {
            temp_v0 = func_1507E908(arg0, (s32)arg0->pad6E[1]);
            if (temp_v0[4] != 0) {
                temp_v0_2 = func_1507E9F8(arg0, 0);
                if (temp_v0_2 != 0) {
                    func_150302F0(arg0, (s32)temp_v0_2[temp_v0[4] - 1]);
                }
            }
            arg0->pad6E[1] = arg1;
            arg0->field_72 = arg3;
            arg0->field_71 = arg2;
            func_1507E5C8(arg0->pad0, arg4);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E7E4 */
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
