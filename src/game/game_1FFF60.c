#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FFF60.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D2AB0
 * - func_151D2B4C
 * - func_151D2DCC
 * - func_151D2E14
 * - func_151D2E5C
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
    u8 temp_t7;
    u8 temp_v1;

    temp_v0 = &D_800E0950[arg0];
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

typedef struct Game1FFF60Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Game1FFF60Vec3;

void *func_151D2BA4(s32 arg0, void *arg1, s32 arg2, u8 arg3, s32 arg4) {
    void *temp_v0;
    void *sp24;

    temp_v0 = func_15167A68(0x3D, arg4, arg2 + 0x48, 1, arg3, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    sp24 = temp_v0;
    func_10022EC0((u8 *)temp_v0 + 0x10, (void *)arg0, 0x24);
    *(Game1FFF60Vec3 *)((u8 *)sp24 + 0x34) = *(Game1FFF60Vec3 *)arg1;
    func_151D3308(sp24);
    return sp24;
}
typedef struct Game1FFF60MotionSource {
    s32 valid;
    u8 id;
    u8 pad5[0x36];
    u8 owner;
    u8 pad3C[0x38];
    u8 flags;
    u8 pad75[0x15F];
    u8 *frames;
} Game1FFF60MotionSource;

typedef struct Game1FFF60Motion {
    u8 pad0[0x10];
    Game1FFF60MotionSource *source;
    u8 owner;
    u8 pad15[3];
    f32 position[3];
    u8 frame;
    u8 pad25;
    s16 timer;
    u8 flags;
    s8 update_callback;
    s8 end_callback;
    u8 pad2B;
    s32 state;
    u8 pad30[4];
    Game1FFF60Vec3 result;
} Game1FFF60Motion;

void func_1516972C();
void func_15143134(f32 *, f32 *, s32);
extern s32 D_800BE9E4;
extern s32 (*D_8008FC40[])(void *, void *);
extern void (*D_8008FC48[])(void *, void *);

void func_151D2C40(Game1FFF60Motion *arg0) {
    struct {
        Game1FFF60Vec3 position;
        s32 padding;
    } local;
    Game1FFF60MotionSource *source;

    source = arg0->source;
    if ((source->valid == 0) || (source->id == 0xFF) || (source->owner != arg0->owner) ||
        (source->frames == 0) || ((source->flags & 0xF) == 0xF)) {
        func_1516972C(arg0);
        return;
    }
    func_15143134(arg0->position, (f32 *)&local.position, (s32)(source->frames + (arg0->frame << 6)));
    if (arg0->flags & 1) {
        arg0->timer = (s16)(arg0->timer - D_800BE9E4);
        if (arg0->timer < 0) {
            if (arg0->end_callback != -1) {
                D_8008FC48[arg0->end_callback](arg0, &local.position);
            }
            arg0->state = 0;
            func_1516972C(arg0);
            return;
        }
    }
    if ((arg0->update_callback != -1) && (D_8008FC40[arg0->update_callback](arg0, &local.position) == 0)) {
        func_1516972C(arg0);
        return;
    }
    arg0->result = local.position;
}
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
void *func_151D2F00(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    void *temp_v0;
    volatile void *sp24;

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
    return (void *)sp24;
}
extern s32 (*D_8008FC4C[])(void *);
extern void (*D_8008FC50[])(void *);
extern void (*D_8008FC54[])(void *);
extern void (*D_8008FC58[])(void *);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2F90 CURRENT (1670) */
void func_151D2F90(u8 *arg0) {
    u8 *actor;
    u8 flags;
    s32 previousMode;
    s32 currentMode;
    s8 callback;

    actor = *(u8 **)(arg0 + 0x10);
    flags = arg0[0x18];
    previousMode = flags & 2;
    if (*(s32 *)actor == 0 || actor[4] == 0xFF || arg0[0x14] != actor[0x3B]) {
        func_1516972C(arg0);
        return;
    }
    if (*(s32 *)(actor + 0x1D4) != 0 && (actor[0x74] & 0xF) != 0xF) {
        arg0[0x18] = flags | 2;
    } else {
        arg0[0x18] = flags & ~2;
    }
    if (arg0[0x18] & 1) {
        *(s16 *)(arg0 + 0x16) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x16) < 0) {
            callback = *(s8 *)(arg0 + 0x1C);
            if (callback != -1) {
                D_8008FC58[callback](arg0);
            }
            func_1516972C(arg0);
            return;
        }
    }
    currentMode = arg0[0x18] & 2;
    if (currentMode != previousMode) {
        if (currentMode != 0) {
            D_8008FC50[*(s8 *)(arg0 + 0x1A)](arg0);
        } else {
            D_8008FC54[*(s8 *)(arg0 + 0x1B)](arg0);
        }
    }
    callback = *(s8 *)(arg0 + 0x19);
    if (callback != -1 && D_8008FC4C[callback](arg0) == 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2F90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2F90.s")
extern void (*D_8008FC48[])(void *, void *);
extern void (*D_8008FC5C[])(s32);
void func_1514EDF0(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3130 CURRENT (415) */
void func_151D3130(s32 arg0) {
    u8 *var_s0;
    u8 *temp_s1;
    s8 temp_v0;

    if (D_8008FC5C[*(u8 *)((u8 *)arg0 + 0x1D)] != 0) {
        D_8008FC5C[*(u8 *)((u8 *)arg0 + 0x1D)](arg0);
    }
    var_s0 = *(u8 **)((u8 *)arg0 + 0x24);
    if (var_s0 != 0) {
        do {
        temp_v0 = *(s8 *)(var_s0 + 0x2A);
        temp_s1 = *(u8 **)(var_s0 + 0x40);
        if (temp_v0 != -1) {
            D_8008FC48[(s32)temp_v0](var_s0, var_s0 + 0x34);
        }
        *(s32 *)(var_s0 + 0x2C) = 0;
        func_1516972C(var_s0);
        var_s0 = temp_s1;
        } while (var_s0 != 0);
    }
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x10));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3130 */
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
extern void (*D_8008FC64[])(void *, void *, u8);
void func_151D33FC(void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D324C CURRENT (1460) */
void func_151D324C(void *arg0, void *arg1, u8 arg2) {
    u8 mode;
    s32 current;
    s32 incoming;
    void (*callback)(void *, void *, u8);

    mode = arg2 & 0xFF;
    if (mode == 0) {
        func_151D33FC(arg0, arg1);
    } else if (mode == 0x2D) {
        current = *(s32 *)((u8 *)arg0 + 0x10);
        incoming = *(s32 *)arg1;
        if (incoming == current) {
            *(s32 *)((u8 *)arg0 + 0x10) = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0x14) = *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == current) {
            *(s32 *)((u8 *)arg0 + 0x10) = incoming;
            *(u8 *)((u8 *)arg0 + 0x14) = *(u8 *)((u8 *)arg1 + 8);
        }
    }
    callback = D_8008FC64[*(u8 *)((u8 *)arg0 + 0x1D)];
    if (callback != 0) {
        callback(arg0, arg1, mode);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D324C */
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
extern void func_15169260(s32 *arg0, s32 arg1, s32 arg2, u8 arg3);
typedef struct {
    s32 value;
} Game1FFF60DispatchDescriptor;
extern Game1FFF60DispatchDescriptor D_800AB168;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D343C CURRENT (100) */
void func_151D343C(s32 arg0, u8 arg1) {
    Game1FFF60DispatchDescriptor sp1C;

    sp1C = D_800AB168;
    func_15169260(&sp1C.value, 1, arg0, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D343C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D343C.s")
