#include "types.h"

/*
 * Reviewed source unit: src/game/game_18A8F0.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515D480
 * - func_1515D4D4
 * - func_1515D520
 * - func_1515D5F8
 * - func_1515D6D0
 * - func_1515D914
 * - func_1515E278
 * - func_1515E43C
 * - func_1515E544
 * - func_1515E888
 * - func_1515EB84
 * - func_1515EC78
 * - func_1515EF74
 * - func_1515F008
 * - func_1515F040
 * - func_1515F0AC
 * - func_1515F170
 * - func_1515F338
 * - func_1515F5C4
 * - func_1515F850
 * - func_1515FB70
 * - func_1515FBC4
 * - func_1515FC60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game18A8F0Node {
    u8 pad0[0xC];
    struct Game18A8F0Node *next;
} Game18A8F0Node;

typedef struct Game18A8F0ListNode {
    struct Game18A8F0ListNode *next;
} Game18A8F0ListNode;

typedef struct Game18A8F0ValueNode {
    s32 value;
    f32 field_4;
    f32 field_8;
    s32 field_C;
} Game18A8F0ValueNode;

extern void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_100226F0(void *arg0, s32 arg1);
extern void *D_800DCD78;

void *func_1515D440(void) {
    void *temp_v0;

    temp_v0 = func_10003C40(0x10, 1, 2, 0);
    func_100226F0(temp_v0, 0x10);
    return temp_v0;
}
/* Call context: func_10003C40: unique active project prototype */
void * func_10003C40(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D480 CURRENT (42) */
void *func_1515D480(s32 arg0) {
    s32 sp18;
    void *sp1C;

    sp18 = arg0 * 0x60;
    sp1C = func_10003C40(sp18, 1, 2, 0);
    func_100226F0(sp1C, sp18);
    return sp1C;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D480 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D480.s")
extern s8 D_800DCD20[];
extern u8 D_800DCD27;
extern s32 D_800DCD7C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D4D4 CURRENT (450) */
void func_1515D4D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg3 = arg3 & 0xFF;
    if (arg3 >= (s32)D_800DCD27) {
        D_800DCD20[0] = arg0;
        D_800DCD20[1] = arg1;
        D_800DCD20[2] = arg2;
        D_800DCD7C = 1;
        D_800DCD27 = (u8)arg3;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D4D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D4D4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D520 CURRENT (1065) */
void *func_1515D520(void) {
    s32 *sp1C;
    s32 *var_v0;
    s32 *temp_v0;
    void *var_v1;

    temp_v0 = (s32 *)func_10003C40(0x34, 1, 2, 2);
    if (temp_v0 != 0) {
        sp1C = temp_v0;
        func_100226F0(temp_v0, 0x34);
        temp_v0 = sp1C;
        if (D_800DCD78 != 0) {
            var_v0 = *(s32 **)D_800DCD78;
            var_v1 = D_800DCD78;
            if (var_v0 != 0) {
                do {
                    var_v1 = var_v0;
                    var_v0 = *(s32 **)var_v0;
                } while (var_v0 != 0);
            }
            *(s32 **)var_v1 = temp_v0;
        } else {
            D_800DCD78 = temp_v0;
        }
        *temp_v0 = 0;
    }
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D520 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D520.s")
void func_1515D5AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    func_1515D5F8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, (u8) (s32) arg9);
}
void *func_1515D520();                              /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D5F8 CURRENT (999) */
void *func_1515D5F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    void *temp_v0;

    temp_v0 = func_1515D520();
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 4) = 0;
        *(s8 *)((u8 *)temp_v0 + 5) = (s8) arg4;
        *(s8 *)((u8 *)temp_v0 + 6) = (s8) arg5;
        *(s8 *)((u8 *)temp_v0 + 7) = (s8) arg6;
        *(s8 *)((u8 *)temp_v0 + 8) = (s8) arg7;
        *(s8 *)((u8 *)temp_v0 + 9) = (s8) arg8;
        *(s8 *)((u8 *)temp_v0 + 0xA) = 0;
        *(u8 *)((u8 *)temp_v0 + 0xB) = arg9;
        *(s16 *)((u8 *)temp_v0 + 0xE) = (s16) arg0;
        *(s16 *)((u8 *)temp_v0 + 0x10) = (s16) arg1;
        *(s16 *)((u8 *)temp_v0 + 0x12) = (s16) arg2;
        *(s8 *)((u8 *)temp_v0 + 0x2C) = 0x7F;
        *(s8 *)((u8 *)temp_v0 + 0x2D) = 0;
        *(s8 *)((u8 *)temp_v0 + 0x2E) = 0;
        *(s8 *)((u8 *)temp_v0 + 0x2F) = (s8) arg3;
    }
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D5F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D5F8.s")
void func_1515D69C(void) {
    void *var_v0;

    var_v0 = D_800DCD78;
    if (var_v0 != 0) {
        do {
            *(s8 *)((u8 *)var_v0 + 0xC) = 0;
            *(s8 *)((u8 *)var_v0 + 0x30) = 0;
            var_v0 = *(void **)((u8 *)var_v0 + 0);
        } while (var_v0 != 0);
    }
}
void func_1515D6C8(void) {

}
extern s32 D_800BE628;
extern u8 D_800BE9C0;
extern s32 D_800DCD10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D6D0 CURRENT (11155) */
void *func_1515D6D0(u8 *arg0, s32 arg1) {
    u8 *temp_a2;
    u8 *temp_a2_10;

    u8 *temp_a2_12;
    u8 *temp_a2_2;
    u8 *temp_a2_3;
    u8 *temp_a2_4;
    u8 *temp_a2_5;
    u8 *temp_a2_6;
    u8 *temp_a2_7;
    u8 *temp_a2_8;
    u8 *temp_a2_9;

    *(s32 *)((u8 *)arg0 + 0) = 0xDB020000;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    temp_a2_2 = (void *)(arg0 + 8);
    *(s32 *)((u8 *)temp_a2_2 + 4) = 0x20000;
    *(s32 *)((u8 *)arg0 + 8) = 0xD9FFFFFF;
    arg0 = (void *)(temp_a2_2 + 8);
    func_1515EF74(D_800BE628 + (arg1 * 0x180) + (D_800BE9C0 << 6) + 0x100);
    *(s32 *)((u8 *)arg0 + 0) = 0xDB100000;
    temp_a2_3 = (void *)(arg0 + 8);
    *(s32 *)((u8 *)arg0 + 4) = (s32) ((((s32) *(s32 *)((u8 *)D_800DCD10 + 4) >> 0x10) & 0xFFFF) | (((s32) *(s32 *)((u8 *)D_800DCD10 + 0) >> 0x10) << 0x10));
    *(s32 *)((u8 *)arg0 + 8) = 0xDB100008;
    temp_a2_4 = (void *)(temp_a2_3 + 8);
    *(s32 *)((u8 *)temp_a2_3 + 4) = (s32) ((((s32) *(s32 *)((u8 *)D_800DCD10 + 4) >> 0x10) & 0xFFFF) | (((s32) *(s32 *)((u8 *)D_800DCD10 + 0) >> 0x10) << 0x10));
    *(s32 *)((u8 *)temp_a2_3 + 8) = 0xDB100004;
    temp_a2_5 = (void *)(temp_a2_4 + 8);
    *(s32 *)((u8 *)temp_a2_4 + 4) = (s32) (((s32) *(s32 *)((u8 *)D_800DCD10 + 8) >> 0x10) << 0x10);
    *(s32 *)((u8 *)temp_a2_4 + 8) = 0xDB10000C;
    temp_a2_6 = (void *)(temp_a2_5 + 8);
    *(s32 *)((u8 *)temp_a2_5 + 4) = (s32) (((s32) *(s32 *)((u8 *)D_800DCD10 + 8) >> 0x10) << 0x10);
    *(s32 *)((u8 *)temp_a2_5 + 8) = 0xDB100010;
    temp_a2_7 = (void *)(temp_a2_6 + 8);
    *(s32 *)((u8 *)temp_a2_6 + 4) = (s32) ((*(s32 *)((u8 *)D_800DCD10 + 4) & 0xFFFF) | (*(s32 *)((u8 *)D_800DCD10 + 0) << 0x10));
    *(s32 *)((u8 *)temp_a2_6 + 8) = 0xDB100018;
    temp_a2_8 = (void *)(temp_a2_7 + 8);
    *(s32 *)((u8 *)temp_a2_7 + 4) = (s32) ((*(s32 *)((u8 *)D_800DCD10 + 4) & 0xFFFF) | (*(s32 *)((u8 *)D_800DCD10 + 0) << 0x10));
    *(s32 *)((u8 *)temp_a2_7 + 8) = 0xDB100014;
    temp_a2_9 = (void *)(temp_a2_8 + 8);
    *(s32 *)((u8 *)temp_a2_8 + 4) = (s32) (*(s32 *)((u8 *)D_800DCD10 + 8) << 0x10);
    *(s32 *)((u8 *)temp_a2_8 + 8) = 0xDB10001C;
    temp_a2_10 = (void *)(temp_a2_9 + 8);
    *(s32 *)((u8 *)temp_a2_9 + 4) = (s32) (*(s32 *)((u8 *)D_800DCD10 + 8) << 0x10);
    *(s32 *)((u8 *)temp_a2_9 + 8) = 0xDB100020;
    {
    u8 *temp_a2_11;
    temp_a2_11 = (void *)(temp_a2_10 + 8);
    *(s32 *)((u8 *)temp_a2_10 + 4) = 0;
    *(s32 *)((u8 *)temp_a2_10 + 8) = 0xDB100024;
    temp_a2_12 = (void *)(temp_a2_11 + 8);
    *(s32 *)((u8 *)temp_a2_11 + 4) = (s32) (*(s32 *)((u8 *)D_800DCD10 + 0xC) << 0x10);
    *(s32 *)((u8 *)temp_a2_11 + 8) = 0xDB100028;
    }
    temp_a2 = (void *)(temp_a2_12 + 8);
    *(s32 *)((u8 *)temp_a2_12 + 4) = 0;
    *(s32 *)((u8 *)temp_a2_12 + 8) = 0xDB10002C;
    *(s32 *)((u8 *)temp_a2 + 4) = (s32) (*(s32 *)((u8 *)D_800DCD10 + 0xC) << 0x10);
    return temp_a2 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D6D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D6D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D914.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E278.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E43C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E544.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E888.s")
typedef struct Game18A8F0SearchActor {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0xC];
    f32 field_2C;
    f32 field_30;
    f32 field_34;
    u8 pad38[0x148];
    f32 field_180;
    u8 pad184[0x1A8];
} Game18A8F0SearchActor;

typedef struct Game18A8F0SearchEntry {
    u8 pad0[0x14];
    u8 field_14;
    u8 field_15;
    u8 pad16[2];
    u32 flags_18;
} Game18A8F0SearchEntry;

typedef struct Game18A8F0SearchNode {
    struct Game18A8F0SearchNode *next;
    Game18A8F0SearchEntry *entry;
} Game18A8F0SearchNode;

s32 func_150A1DA0(Game18A8F0SearchActor *, Game18A8F0SearchEntry *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515EB84 CURRENT (20) */
void *func_1515EB84(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                    Game18A8F0SearchNode *arg4) {
    Game18A8F0SearchActor actor;
    Game18A8F0SearchEntry *entry;

    actor.y = (f32)arg1;
    actor.field_180 = (f32)arg1;
    actor.field_30 = (f32)arg1;
    actor.x = (f32)arg0;
    actor.field_2C = (f32)arg0;
    actor.z = (f32)arg2;
    actor.field_34 = (f32)arg2;
    if (arg4 != 0) {
        do {
            entry = arg4->entry;
            if ((entry->field_14 == 0) &&
                ((arg3 == 0) || (((entry->flags_18 >> 24) & arg3) != 0)) &&
                (((entry->field_15 >> 2) == 0x18) ||
                 ((entry->flags_18 >> 31) == 0)) &&
                (func_150A1DA0(&actor, entry, 0) == 0)) {
                return arg4->entry;
            }
            arg4 = arg4->next;
        } while (arg4 != 0);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515EB84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515EB84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515EC78.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515EF74 CURRENT (2244) */
void func_1515EF74(s32 arg0) {
    func_1515F040(1.0f / func_1515F008(arg0, 0), 0);
    func_1515F040(1.0f / func_1515F008(arg0, 5), 1);
    func_1515F040(1.0f / func_1515F008(arg0, 0xA), 2);
    func_1515F0AC(-func_1515F008(arg0, 0xE), 3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515EF74 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515EF74.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F008 CURRENT (50) */
f32 func_1515F008(s32 arg0, s32 arg1) {
    s16 *temp_v1;

    temp_v1 = (s16 *)arg0 + arg1;
    return (f32) (*(u16 *)((u8 *)temp_v1 + 0x20) | (*temp_v1 << 0x10)) * 0.000015258789f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F008 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F008.s")
extern f32 D_800A6520;
extern s32 D_800DCD10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F040 CURRENT (860) */
void func_1515F040(f32 arg0, s32 arg1) {
    f32 var_fa0;
    f32 var_fv0;

    var_fa0 = arg0;
    var_fv0 = D_800A6520;
    if (var_fv0 <= var_fa0) {
        goto block_3;
    }
    var_fv0 = -32768.0f;
    if (var_fa0 < -32768.0f) {
block_3:
        var_fa0 = var_fv0;
    }
    D_800DCD10[arg1] = (s32) (var_fa0 * 65536.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F040 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F040.s")
extern f32 D_800A6524;
extern s32 D_800DCD10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F0AC CURRENT (220) */
void func_1515F0AC(f32 arg0, s32 arg1) {
    f32 var_fv0;

    var_fv0 = D_800A6524;
    if (arg0 >= var_fv0) {
        arg0 = var_fv0;
    } else if (arg0 < -32768.0f) {
        arg0 = -32768.0f;
    }
    D_800DCD10[arg1] = (s32) arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F0AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F0AC.s")
void func_10004074(s32);

void func_1515F10C(Game18A8F0ListNode *arg0) {
    Game18A8F0ListNode *var_a1;
    Game18A8F0ListNode *var_v0;

    var_a1 = D_800DCD78;
    var_v0 = 0;
    if (var_a1 != arg0) {
        do {
            var_v0 = var_a1;
            var_a1 = var_a1->next;
        } while (var_a1 != arg0);
    }
    if (var_v0 != 0) {
        var_v0->next = var_a1->next;
    } else {
        D_800DCD78 = var_a1->next;
    }
    func_10004074((s32)var_a1);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F170 CURRENT (315) */
void func_1515F170(s32 arg0, s32 arg1) {
    void *var_v0;

    var_v0 = D_800DCD78;
    if (var_v0 != 0) {
        do {
            if (arg0 == *(u8 *)((u8 *)var_v0 + 0xB)) {
                *(s8 *)((u8 *)var_v0 + 9) = (s8) (arg1 & 0xFF);
            }
            var_v0 = *(void **)((u8 *)var_v0 + 0);
        } while (var_v0 != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F170 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F170.s")
extern Game18A8F0ValueNode *func_10003C6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern f32 func_15144598(s32 arg0);
extern f32 func_1514462C(s32 arg0);

Game18A8F0ValueNode *func_1515F1B0(s32 arg0) {
    Game18A8F0ValueNode *var_v1;

    var_v1 = func_10003C6C(0x10, 1, 2, 0, 1);
    if (var_v1 == 0) {
        return 0;
    }
    var_v1->value = arg0;
    if (arg0 != 0) {
        var_v1->field_4 = func_1514462C(arg0);
    } else {
        var_v1->field_4 = 0.0f;
    }
    if (arg0 != 0) {
        var_v1->field_8 = func_15144598(arg0);
    } else {
        var_v1->field_8 = 0.0f;
    }
    var_v1->field_C = 0;
    return var_v1;
}
void func_1515F25C(Game18A8F0Node **arg0, Game18A8F0Node *arg1) {
    arg1->next = *arg0;
    *arg0 = arg1;
}
extern void (*D_8008B090[])(void *, void *);

void func_1515F270(void *arg0, void *arg1) {
    void (*temp_v1)(void *, void *);
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg1 + 0x18);
    if ((temp_v0 >= 0) && (temp_v0 < 0xC)) {
        temp_v1 = D_8008B090[temp_v0];
        if (temp_v1 != 0) {
            temp_v1(arg0, arg1);
        }
    }
}
void func_1505D024(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1515F2B8(void *arg0, s32 arg1) {
    func_1505D024((s32)arg0, 0x6001D, *(u16 *)((u8 *)arg0 + 0x7A), -1);
}
typedef struct {
    u8 pad_0[0x3B];
    u8 field_3B;
} Game18A8F0State;

typedef struct {
    u8 pad_0[0x1C];
    s32 field_1C;
} Game18A8F0Selection;

extern void (*D_8008B0C0[])(void);

void func_1515F2E8(Game18A8F0State *arg0, Game18A8F0Selection *arg1) {
    s32 temp_v0;

    if (arg0->field_3B == 1) {
        temp_v0 = arg1->field_1C;
        if ((temp_v0 >= 0) && (temp_v0 < 3)) {
            D_8008B0C0[temp_v0]();
        }
    }
}
extern f32 D_800DCD94;
extern f32 D_800DCD98;
extern f32 D_800DCD9C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F338 */
void func_1515F338(s32 arg0, s32 arg1) {
    u8 var_t0;
    u8 var_t1;
    u8 var_v1;

    var_v1 = (u8) *(s8 *)((u8 *)D_800DCD20 + 0);
    var_t0 = *(u8 *)((u8 *)D_800DCD20 + 1);
    var_t1 = *(u8 *)((u8 *)D_800DCD20 + 2);
    if (D_800DCD94 != 97.0f) {
        D_800DCD94 += (97.0f - D_800DCD94) * 0.5f;
        var_v1 = (u32) D_800DCD94 & 0xFF;
    }
    if (D_800DCD98 != 96.0f) {
        D_800DCD98 += (96.0f - D_800DCD98) * 0.5f;
        var_t0 = (u32) D_800DCD98 & 0xFF;
    }
    if (D_800DCD9C != 98.0f) {
        D_800DCD9C += (98.0f - D_800DCD9C) * 0.5f;
        var_t1 = (u32) D_800DCD9C & 0xFF;
    }
    func_1515D4D4((s32) var_v1, (s32) var_t0, (s32) var_t1, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F338 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F338.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F5C4 */
void func_1515F5C4(s32 arg0, s32 arg1) {
    u8 var_t0;
    u8 var_t1;
    u8 var_v1;

    var_v1 = (u8) *(s8 *)((u8 *)D_800DCD20 + 0);
    var_t0 = *(u8 *)((u8 *)D_800DCD20 + 1);
    var_t1 = *(u8 *)((u8 *)D_800DCD20 + 2);
    if (D_800DCD94 != 229.0f) {
        D_800DCD94 += (229.0f - D_800DCD94) * 0.5f;
        var_v1 = (u32) D_800DCD94 & 0xFF;
    }
    if (D_800DCD98 != 253.0f) {
        D_800DCD98 += (253.0f - D_800DCD98) * 0.5f;
        var_t0 = (u32) D_800DCD98 & 0xFF;
    }
    if (D_800DCD9C != 160.0f) {
        D_800DCD9C += (160.0f - D_800DCD9C) * 0.5f;
        var_t1 = (u32) D_800DCD9C & 0xFF;
    }
    func_1515D4D4((s32) var_v1, (s32) var_t0, (s32) var_t1, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F5C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F5C4.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32, f32);                        /* extern */
extern f32 D_800A6530;
extern f32 D_800BE9A4;
extern f32 D_800DCDA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F850 CURRENT (1647) */
void func_1515F850(s32 arg0, s32 arg1) {
    f32 sp28;
    f32 sp24;
    u8 sp1E;
    u8 sp1D;
    u8 sp1C;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;

    sp1C = (u8) *(s8 *)((u8 *)D_800DCD20 + 0);
    sp1D = *(u8 *)((u8 *)D_800DCD20 + 1);
    sp1E = *(u8 *)((u8 *)D_800DCD20 + 2);
    temp_fv0 = func_15047D60(D_800DCDA0);
    temp_fa1 = (temp_fv0 * 29.5f) + 127.5f;
    temp_ft4 = (temp_fv0 * 71.0f) + 109.0f;
    sp28 = temp_fa1;
    sp24 = temp_ft4;
    temp_ft5 = (temp_fv0 * 26.0f) + 26.0f;
    {
        f32 sp20 = temp_ft5;
    D_800DCDA0 += D_800A6530 * D_800BE9A4;
    D_800DCDA0 = func_15144B68(D_800DCDA0, temp_fa1);
    if (temp_fa1 != D_800DCD94) {
        D_800DCD94 += (temp_fa1 - D_800DCD94) * 0.5f;
        sp1C = (u8) (u32) D_800DCD94;
    }
    if (temp_ft4 != D_800DCD98) {
        D_800DCD98 += (temp_ft4 - D_800DCD98) * 0.5f;
        sp1D = (u8) (u32) D_800DCD98;
    }
    if (temp_ft5 != D_800DCD9C) {
        D_800DCD9C += (temp_ft5 - D_800DCD9C) * 0.5f;
        sp1E = (u8) (u32) D_800DCD9C;
    }
    func_1515D4D4((s32) sp1C, (s32) sp1D, (s32) sp1E, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F850.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515FB70 CURRENT (300) */
void func_1515FB70(void *arg0, void *arg1) {
    if ((*(u8 *)((u8 *)arg0 + 0x3B) == 1) && (*(s32 *)((u8 *)arg1 + 0x1C) >= 0)) {

    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515FB70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FB70.s")
void func_1515FB94(void *arg0, s32 arg1) {
    func_1505D024((s32)arg0, 0x6002D, *(u16 *)((u8 *)arg0 + 0x7A), -1);
}
typedef struct Game18A8F0Actor {
    u8 pad0[0x7A];
    u16 field_7A;
    u8 pad7C[0x2B0];
} Game18A8F0Actor;

typedef struct Game18A8F0LookupResult {
    u8 pad0[0x98];
    Game18A8F0Actor *actor_98;
} Game18A8F0LookupResult;

Game18A8F0LookupResult *func_15105C24(s32);
extern Game18A8F0Actor D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515FBC4 CURRENT (382) */
void func_1515FBC4(Game18A8F0Actor *arg0, s32 arg1) {
    Game18A8F0Actor * volatile sp18;
    Game18A8F0Actor *actor;
    Game18A8F0LookupResult *result;
    s32 actor_index;

    sp18 = 0;
    result = func_15105C24(arg1);
    actor = sp18;
    if (result != 0) {
        actor = result->actor_98;
    }
    if (actor != 0) {
        actor_index = actor - D_800CC2D0;
    } else {
        actor_index = -1;
    }
    func_1505D024((s32)arg0, 0x6002E, arg0->field_7A, actor_index);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515FBC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FBC4.s")
void func_1505D024(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1515FC34(s32 arg0, s32 arg1) {
    func_1505D024(arg0, 0x33, 0xC000, -1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FC60.s")
