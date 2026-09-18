#include "types.h"

/*
 * Reviewed source unit: src/game/game_AB760.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507E2B0
 * - func_1507E3C0
 * - func_1507E500
 * - func_1507E5C8
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E500.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E5C8.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E73C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E7E4.s")
typedef struct GameAB760ValueRecord {
    s32 value;
    s32 pad4;
} GameAB760ValueRecord;

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

extern GameAB760ValueRecord *D_800D1C90[];

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
