#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FFF60.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D2AB0
 * - func_151D2B4C
 * - func_151D2BA4
 * - func_151D2C40
 * - func_151D2DCC
 * - func_151D2E14
 * - func_151D2E5C
 * - func_151D2F00
 * - func_151D2F90
 * - func_151D3130
 * - func_151D324C
 * - func_151D3354
 * - func_151D343C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_1502B5C8(u32 *, s32, s32, u16);
extern u8 D_800E0950[];
extern s32 D_800E0990[];
extern u16 D_800AB140[];
extern s16 D_800E0968[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2AB0 CURRENT (169) */
void func_151D2AB0(s32 arg0) {
    s32 sp18;
    s32 temp_t1;
    u8 *temp_v0;
    u8 temp_t9;
    u32 sp1C;

    temp_v0 = &D_800E0950[arg0];
    temp_t9 = *temp_v0 + 1;
    *temp_v0 = temp_t9;
    if ((temp_t9 & 0xFF) < 2) {
        temp_t1 = arg0 * 2;
        sp18 = temp_t1;
        D_800E0990[arg0] = (s32)func_1502B5C8(&sp1C, 2, 9, *(u16 *)((u8 *)D_800AB140 + temp_t1));
        *(s16 *)((u8 *)D_800E0968 + sp18) = (s16)(sp1C >> 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2AB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2AB0.s")
void func_100043B4(s32, s32, s32);
extern u8 D_800E0950[];
extern s32 D_800E0990[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2B4C CURRENT (30) */
void func_151D2B4C(s32 arg0) {
    u8 *temp_v0;
    u8 temp_v1;
    u8 temp_t7;

    temp_v0 = D_800E0950 + arg0;
    temp_v1 = *temp_v0;
    temp_t7 = temp_v1 - 1;
    if (temp_v1 != 0) {
        *temp_v0 = temp_t7;
        if (!(temp_t7 & 0xFF)) {
            func_100043B4(D_800E0990[arg0], 4, arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2B4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2B4C.s")
void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_10022EC0(void *, void *, s32);
void func_151D3308(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2BA4 CURRENT (50) */
void *func_151D2BA4(s32 arg0, void *arg1, s32 arg2, u8 arg3, s32 arg4) {
    void *temp_v0;
    void *sp24;

    temp_v0 = func_15167A68(0x3D, arg4, arg2 + 0x48, 1, arg3, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    sp24 = temp_v0;
    func_10022EC0((u8 *)temp_v0 + 0x10, (void *)arg0, 0x24, temp_v0);
    *(s32 *)((u8 *)sp24 + 0x34) = *(s32 *)arg1;
    *(s32 *)((u8 *)sp24 + 0x38) = *(s32 *)((u8 *)arg1 + 4);
    *(s32 *)((u8 *)sp24 + 0x3C) = *(s32 *)((u8 *)arg1 + 8);
    func_151D3308(sp24);
    return sp24;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2BA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2BA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2C40.s")
void func_151D3354();

void func_151D2DAC(void) {
    func_151D3354();
}
extern void func_1516972C();
void func_15169804(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2DCC CURRENT (410) */
void func_151D2DCC(void *arg0) {
    s32 temp_v0;

    func_151D2DAC();
    temp_v0 = *(s32 *)((u8 *)arg0 + 0x2C);
    if (temp_v0 != 0) {
        func_1516972C(temp_v0, arg0);
    }
    func_15169804((s32)arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2DCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2DCC.s")
void func_1516979C(s32, void *);
void func_15169824(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2E14 CURRENT (410) */
void func_151D2E14(void *arg0) {
    s32 temp_v0;

    func_151D2DAC();
    temp_v0 = *(s32 *)((u8 *)arg0 + 0x2C);
    if (temp_v0 != 0) {
        func_1516979C(temp_v0, arg0);
    }
    func_15169824((s32)arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2E14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2E14.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2E5C CURRENT (360) */
void func_151D2E5C(void *arg0, void *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    if (arg2 == 0) {
        if ((*(s32 *)((u8 *)arg0 + 0x10) == *(s32 *)arg1) ||
            (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x14))) {
            func_1516972C(arg0, arg1);
        }
    } else if (arg2 == 0x2D) {
        temp_v0 = *(s32 *)arg1;
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x10);
        if (temp_v0 == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x10) = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0x14) = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x10) = temp_v0;
            *(u8 *)((u8 *)arg0 + 0x14) = *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2E5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2E5C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2F00 CURRENT (108) */
void *func_151D2F00(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    void *sp24;
    void *temp_v0;

    temp_v0 = func_15167A68(0x3E, arg3, arg1 + 0x30, 1, arg2, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    sp24 = temp_v0;
    func_10022EC0((u8 *)temp_v0 + 0x10, arg0, 0x10);
    *(s16 *)((u8 *)sp24 + 0x20) = 0;
    *(s32 *)((u8 *)sp24 + 0x24) = 0;
    *(s32 *)((u8 *)sp24 + 0x28) = 0;
    *(u8 *)((u8 *)sp24 + 0x18) = (u8)(*(u8 *)((u8 *)sp24 + 0x18) & 0xFFFD);
    return sp24;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2F00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2F00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2F90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D3130.s")
void func_151D3130(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_151D31F4(s32 arg0) {
    func_151D3130(arg0);
    func_15169804(arg0);
}
void func_151D3220(s32 arg0) {
    func_151D3130(arg0);
    func_15169824(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D324C.s")
void func_151D3308(void *arg0) {
    void *temp_v0;
    void *temp_v1;

    temp_v0 = *(void **)((u8 *)arg0 + 0x30);
    if (temp_v0 != 0) {
        *(void **)((u8 *)arg0 + 0x40) = (void *) *(void **)((u8 *)temp_v0 + 0x24);
        temp_v1 = *(void **)((u8 *)temp_v0 + 0x24);
        if (temp_v1 != 0) {
            *(void **)((u8 *)temp_v1 + 0x44) = arg0;
        } else {
            *(void **)((u8 *)temp_v0 + 0x28) = arg0;
        }
        *(s32 *)((u8 *)arg0 + 0x44) = 0;
        *(void **)((u8 *)temp_v0 + 0x24) = arg0;
        *(s16 *)((u8 *)temp_v0 + 0x20) = (s16) (*(s16 *)((u8 *)temp_v0 + 0x20) + 1);
        *(void **)((u8 *)arg0 + 0x30) = temp_v0;
    }
}
typedef struct Game1FFF60Node Game1FFF60Node;

typedef struct {
    u8 pad_0[0x20];
    s16 count;
    u8 pad_22[2];
    Game1FFF60Node *head;
    Game1FFF60Node *tail;
} Game1FFF60List;

struct Game1FFF60Node {
    u8 pad_0[0x30];
    Game1FFF60List *list;
    u8 pad_34[0xC];
    Game1FFF60Node *next;
    Game1FFF60Node *prev;
};

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3354 CURRENT (250) */
void func_151D3354(Game1FFF60Node *arg0) {
    Game1FFF60Node *temp_a1;
    Game1FFF60List *temp_v0;
    Game1FFF60Node *temp_v0_2;

    temp_v0 = arg0->list;
    if (temp_v0 != 0) {
        temp_a1 = arg0->prev;
        if (temp_a1 != 0) {
            temp_a1->next = arg0->next;
        } else {
            temp_v0->head = arg0->next;
        }
        temp_v0_2 = arg0->next;
        if (temp_v0_2 != 0) {
            temp_v0_2->prev = arg0->prev;
        } else {
            temp_v0->tail = arg0->prev;
        }
        temp_v0->count--;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3354 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D3354.s")
extern void func_1516972C();

void func_151D33B8(void *arg0) {
    if (*(s16 *)((u8 *)arg0 + 0x20) > 0) {
        do {
            func_1516972C(*(void **)((u8 *)arg0 + 0x24));
        } while (*(s16 *)((u8 *)arg0 + 0x20) > 0);
    }
}
extern void func_1516972C(void *arg0, void *arg1);

void func_151D33FC(void *arg0, void *arg1) {
    s32 temp_v0;
    s32 temp_v1;
    u8 temp_a2;
    u8 temp_a3;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x10);
    temp_v1 = *(s32 *)((u8 *)arg1 + 0);
    temp_a2 = *(u8 *)((u8 *)arg0 + 0x14);
    temp_a3 = *(u8 *)((u8 *)arg1 + 4);
    if ((temp_v0 == temp_v1) || (temp_a2 == temp_a3)) {
        func_1516972C(arg0, arg1);
    }
}
extern void func_15169260(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_800AB168;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D343C CURRENT (720) */
void func_151D343C(s32 arg0, s32 arg1) {
    s32 sp1C;

    sp1C = D_800AB168;
    func_15169260(&sp1C, 1, arg0, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D343C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D343C.s")
