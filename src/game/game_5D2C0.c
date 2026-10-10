#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_5D2C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1502FE10
 * - func_1502FFD8
 * - func_15030158
 * - func_15030310
 * - func_15030468
 * - func_15030AF4
 * - func_15031070
 * - func_150311C4
 * - func_1503195C
 * - func_150319CC
 * - func_15031C14
 * - func_15031E7C
 * - func_15031FC8
 * - func_150331B8
 * - func_15033838
 * - func_15033BDC
 * - func_15033EC4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1510CE60(s32, s32, s32, s32, void *);
void func_15168E54(s32, s32 *);
s32 func_1502B6BC(s32 *, s32, s32 *, s32, s32, s32);
extern u8 D_800DF7D0[];
extern s32 D_800DF9B8[];
extern s32 *D_800E0148[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502FE10 CURRENT (1904) */
s32 func_1502FE10(u8 arg0, void *arg1, void *arg2, void **arg3, void *arg4, s32 arg5, s32 arg6) {
    u8 *savedCount;
    s32 *allocated;
    s32 *header;
    s32 offset;
    s32 index;
    u32 count;
    u8 *usage;
    s32 *entry;

    usage = &D_800DF7D0[arg0];
    if (*usage == 0) {
        savedCount = usage;
        allocated = (s32 *)func_1502B6BC(0, 0, 0, 2, 9, arg0);
        header = allocated;
        if (allocated == 0) {
            return 1;
        }
        index = 0;
        offset = 0;
        *(s32 *)arg1 = allocated[0];
        count = (u32)allocated[1] >> 2;
        *(u8 *)arg2 = count;
        if ((s32)(count & 0xFF) > 0) {
            do {
                entry = (s32 *)(*(s32 *)arg1 + offset);
                *entry += (s32)header;
                func_1510CE60(*(s32 *)(*(s32 *)arg1 + offset), 0, 1, 0x3E, &D_800DF9B8[arg0]);
                func_15168E54(*(s32 *)(*(s32 *)arg1 + offset), header);
                index++;
                offset += 4;
            } while (index < *(u8 *)arg2);
        }
        D_800E0148[arg0] = header;
        usage = savedCount;
    } else {
        header = D_800E0148[arg0];
        *(s32 *)arg1 = header[0];
        *(u8 *)arg2 = (u32)header[1] >> 2;
    }
    *usage += 1;
    *arg3 = (u8 *)header + 0x18;
    if (arg4 != 0) {
        *(s32 *)arg4 = header[4];
    }
    if (arg5 != 0) {
        *(s32 *)arg5 = header[2];
        if (arg6 != 0) {
            *(u32 *)arg6 = (u32)header[3] >> 4;
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502FE10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1502FE10.s")

void *func_10003C40(s32, s32, s32, s32);
void func_10004074(s32);
void func_10023A10(void *, void *, s32);
s32 func_1502FE10(u8, void *, void *, void **, void *, s32, s32);
s32 func_1503F62C(u8, s8, void *, void *, void **, void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502FFD8 CURRENT (1473) */
s32 func_1502FFD8(u8 *arg0, u8 *arg1) {
    void *sp3C;
    s32 sp34;
    s32 size;
    s8 mode;
    void *temp_v0;
    void *temp_v0_2;

    if (*(s32 *)(arg0 + 0x24) == 0) {
    mode = *(s8 *)(arg0 + 0x17);
    if (mode == -1) {
        if (func_1502FE10(arg0[1], arg0 + 0x24, arg0 + 0x14,
                          &sp3C, arg0 + 0x30, 0, 0) != 0) {
            return 1;
        }
    } else {
        if (func_1503F62C(arg0[1], mode, arg0 + 0x24, arg0 + 0x14,
                          &sp3C, arg0 + 0x30, arg0 + 0x48) != 0) {
            return 1;
        }
    }
    size = (s32)(*(u32 *)(arg0 + 0x24) - (u32)sp3C);
    if (!(arg0[4] & 0x10) && ((arg1[0x66] & 0xC) == 8) &&
        *(s32 *)(arg0 + 0x30) != 0) {
        sp34 = size;
        temp_v0 = func_10003C40(size, 1, 2, 2);
        *(void **)(arg0 + 0x28) = temp_v0;
        if (temp_v0 == 0) {
            return 1;
        }
        temp_v0_2 = func_10003C40(sp34, 1, 2, 2);
        *(void **)(arg0 + 0x2C) = temp_v0_2;
        if (temp_v0_2 == 0) {
            func_10004074((s32)*(void **)(arg0 + 0x28));
            *(void **)(arg0 + 0x28) = 0;
            return 1;
        }
        func_10023A10(sp3C, *(void **)(arg0 + 0x28), sp34);
        func_10023A10(sp3C, *(void **)(arg0 + 0x2C), sp34);
        arg0[8] = 1;
    } else {
        *(void **)(arg0 + 0x28) = sp3C;
        *(void **)(arg0 + 0x2C) = sp3C;
    }
    arg0[9] = 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502FFD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1502FFD8.s")
void func_15031C14(void *);
void func_100043B4(s32, s32);
void func_1518CA04(s32);
extern void *D_800C3EE0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15030158 CURRENT (775) */
void func_15030158(u8 *arg0, s32 volatile arg1) {
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_v0;
    s32 first_mode;
    s32 has_alloc;
    void *temp_v0_2;
    void *temp_v0_3;

    if (arg1 == 0) {
        func_15031C14(arg0);
    }
    if (arg0[9] != 0) {
        has_alloc = arg0[8];
        first_mode = arg1;
        if (has_alloc != 0) {
            if (first_mode != 0) {
                func_10004074(*(s32 *)(arg0 + 0x28));
                func_10004074(*(s32 *)(arg0 + 0x2C));
            } else {
                func_100043B4(*(s32 *)(arg0 + 0x28), 4);
                func_100043B4(*(s32 *)(arg0 + 0x2C), 4);
            }
        }
        temp_a0 = *(void **)(arg0 + 0x48);
        if (temp_a0 != 0) {
            func_1503F7B8(temp_a0);
        }
        func_1518CA04(arg0[1]);
    }
    temp_a0_2 = *(s32 *)(arg0 + 0x34);
    if (temp_a0_2 != 0) {
        if (arg1 != 0) {
            func_10004074(temp_a0_2);
        } else {
            func_100043B4(temp_a0_2, 4);
        }
    }
    temp_v0 = *(s32 *)(arg0 + 0x44);
    if (temp_v0 != 0) {
        func_10004074(temp_v0);
    }
    temp_a0_3 = *(s32 *)(arg0 + 0x4C);
    if (temp_a0_3 != 0) {
        if (arg1 != 0) {
            func_10004074(temp_a0_3);
        } else {
            func_100043B4(temp_a0_3, 4);
        }
    }
    temp_a0_4 = *(s32 *)(arg0 + 0x50);
    if (temp_a0_4 != 0) {
        if (arg1 != 0) {
            func_10004074(temp_a0_4);
        } else {
            func_100043B4(temp_a0_4, 4);
        }
    }
    if (arg0 == D_800C3EE0) {
        D_800C3EE0 = *(void **)(arg0 + 0x54);
    }
    temp_v0_2 = *(void **)(arg0 + 0x58);
    if (temp_v0_2 != 0) {
        *(void **)((u8 *)temp_v0_2 + 0x54) = *(void **)(arg0 + 0x54);
    }
    temp_v0_3 = *(void **)(arg0 + 0x54);
    if (temp_v0_3 != 0) {
        *(void **)((u8 *)temp_v0_3 + 0x58) = *(void **)(arg0 + 0x58);
    }
    func_10004074((s32)arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15030158 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030158.s")
s32 func_15030310(void *arg0, s32 arg1, s32 arg2);

void func_150302F0(void *arg0, s32 arg1) {
    func_15030310(arg0, arg1, 0xFF);
}
/* Call context: func_15030158: unique active declaration in the allowed source */
void func_15030158(u8 *, s32);
extern void * D_800C3EE0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15030310 CURRENT (814) */
s32 func_15030310(void *arg0, s32 arg1, s32 arg2) {
    void *temp_s1;
    void *var_a0;
    s32 var_s5;

    if (*(u8 *)((u8 *)arg0 + 0x3B) == 0) {
        return 0;
    }
    var_a0 = D_800C3EE0;
    var_s5 = 0;
    if (var_a0 != 0) {
loop:
        temp_s1 = *(void **)((u8 *)var_a0 + 0x54);
        if ((*(u8 *)((u8 *)arg0 + 0x3B) == *(u8 *)var_a0) &&
            (arg1 == *(u8 *)((u8 *)var_a0 + 6))) {
            if ((arg2 != 0xFF) && (arg2 != 0)) {
                arg2 -= 1;
                var_a0 = temp_s1;
                goto advance;
            }
            var_s5 = 1;
            func_15030158(var_a0, 0);
            if (arg2 != 0) {
                goto next;
            }
        } else {
next:
            var_a0 = temp_s1;
advance:
            if (var_a0 != 0) {
                goto loop;
            }
        }
    }
    return var_s5;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15030310 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030310.s")
extern void *D_800C3EE0;
void func_15030158(u8 *, s32);

s32 func_150303E4(void *arg0) {
    s32 var_s1;
    void *temp_s0;
    void *var_a0;

    if (*(u8 *)((u8 *)arg0 + 0x3B) == 0) {
        return 0;
    }
    var_a0 = D_800C3EE0;
    var_s1 = 0;
    if (var_a0 != 0) {
        do {
            temp_s0 = *(void **)((u8 *)var_a0 + 0x54);
            if (*(u8 *)((u8 *)arg0 + 0x3B) == *(u8 *)var_a0) {
                var_s1 = 1;
                func_15030158(var_a0, 0);
            }
            var_a0 = temp_s0;
        } while (temp_s0 != 0);
    }
    return var_s1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030468.s")
typedef struct GameCoreNode {
    u8 owner;
    u8 type;
    u8 index;
    u8 visible;
    u8 flags;
    u8 field_5;
    u8 tag;
    u8 callback;
    u8 allocated;
    u8 loaded;
    u16 x;
    u16 y;
    u16 z;
    u8 pad_10[3];
    u8 field_13;
    u8 field_14;
    u8 field_15;
    u8 field_16;
    s8 mode;
    s16 field_18;
    s16 field_1A;
    u16 field_1C;
    u16 child;
    u16 childOffset;
    u16 field_22;
    void *field_24;
    void *field_28;
    void *field_2C;
    void *field_30;
    void *field_34;
    s32 field_38;
    s32 field_3C;
    f32 scale;
    void *field_44;
    void *field_48;
    void *field_4C;
    void *field_50;
    struct GameCoreNode *next;
    struct GameCoreNode *previous;
} GameCoreNode;

s32 func_1502FFD8(u8 *, u8 *);
void func_15031A50(u8 *, u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15030AF4 CURRENT (1667) */
GameCoreNode *func_15030AF4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3,
                           s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                           s32 arg8, u16 *arg9, s32 arg10, s32 arg11,
                           s32 arg12) {
    s32 failed;
    GameCoreNode *node;
    GameCoreNode *next;
    void *matrices;
    u8 owner;

    owner = arg0[0x3B];
    if (owner == 0) {
        return 0;
    }
    if (!(arg3 & 8)) {
        node = D_800C3EE0;
        while (node != 0) {
            next = node->next;
            if ((owner == node->owner) && (arg7 == node->tag) &&
                (arg1 == node->type)) {
                return 0;
            }
            node = next;
        }
    }
    node = func_10003C40(0x5C, 1, 0, 2);
    if (node == 0) {
        return 0;
    }
    failed = 0;
    if (D_800C3EE0 != 0) {
        ((GameCoreNode *)D_800C3EE0)->previous = node;
    }
    node->next = D_800C3EE0;
    node->previous = 0;
    D_800C3EE0 = node;
    node->owner = arg0[0x3B];
    node->type = arg1;
    node->field_24 = 0;
    node->field_28 = 0;
    node->field_2C = 0;
    node->field_30 = 0;
    node->visible = 0xFF;
    node->field_44 = 0;
    node->flags = arg3;
    node->tag = arg7;
    node->scale = 1.0f;
    node->index = arg2;
    node->field_38 = 0;
    node->field_3C = 0;
    node->allocated = 0;
    node->loaded = 0;
    node->field_18 = 0;
    node->field_1A = 0;
    node->callback = arg8;
    node->x = arg9[0];
    node->y = arg9[1];
    node->z = arg9[2];
    node->field_48 = 0;
    node->mode = arg10;
    node->field_16 = arg5;
    node->field_15 = arg4;
    node->child = arg11;
    node->field_13 = 0;
    node->field_4C = 0;
    node->field_50 = 0;
    node->field_5 = 0;
    node->field_22 = 0;
    node->childOffset = arg12;
    if ((arg5 == 4) || (arg3 & 4)) {
        matrices = func_10003C40(0x80, 1, 2, 2);
        node->field_34 = matrices;
        if (matrices == 0) {
            failed = 1;
        }
    } else {
        node->field_34 = 0;
    }
    if (arg6 == 0) {
        node->field_1C = 0xFFFF;
    } else {
        node->field_1C = arg6;
    }
    if (failed == 0) {
        failed |= func_1502FFD8((u8 *)node, arg0);
    }
    if (failed != 0) {
        func_15030158((u8 *)node, 1);
        return 0;
    }
    func_15031A50((u8 *)node, arg0);
    return node;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15030AF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030AF4.s")
extern void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15030D54(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 *temp_v0;

    temp_v0 = (f32 *)func_10003C40(0x18, 1, 0, 2);
    *(f32 **)((u8 *)arg0 + 0x44) = temp_v0;
    if (temp_v0 != 0) {
        (*(f32 **)((u8 *)arg0 + 0x44))[0] = arg1;
        (*(f32 **)((u8 *)arg0 + 0x44))[1] = arg2;
        (*(f32 **)((u8 *)arg0 + 0x44))[2] = arg3;
        (*(f32 **)((u8 *)arg0 + 0x44))[3] = arg4;
        (*(f32 **)((u8 *)arg0 + 0x44))[4] = arg5;
        (*(f32 **)((u8 *)arg0 + 0x44))[5] = arg6;
        if (*(void **)((u8 *)arg0 + 0x34) == 0) {
            *(void **)((u8 *)arg0 + 0x34) = func_10003C40(0x80, 1, 2, 2);
        }
    }
}
/* Call context: func_15083E90: unique active project prototype */
void * func_15083E90(u8);
s32 func_150311C4(s32, void *, void *, s32, s32);   /* extern */
extern void * D_800C3EE0;

s32 func_15030E08(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0_2;
    s32 temp_v1;
    void *temp_s2;
    void *temp_v0;
    void *var_s0;

    var_s0 = D_800C3EE0;
    while (var_s0 != 0) {
        temp_s2 = *(void **)((u8 *)var_s0 + 0x54);
        if (*(u8 *)((u8 *)var_s0 + 3) == 0) {
            var_s0 = temp_s2;
            continue;
        }
        temp_v0 = func_15083E90(*(u8 *)var_s0);
        if ((temp_v0 == 0) || (*(s32 *)((u8 *)temp_v0 + 0x1D4) == 0) || (temp_v1 = 1 << arg1, (temp_v1 == (*(u8 *)((u8 *)temp_v0 + 0x74) & temp_v1)))) {
            var_s0 = temp_s2;
            continue;
        }
        if (arg2 == 2) {
            if (*(u8 *)((u8 *)temp_v0 + 5) != 7) {
                var_s0 = temp_s2;
                continue;
            }
        } else {
            temp_v0_2 = func_1506196C(temp_v0, arg1);
            if (arg2 == 1) {
                if (!(*(u8 *)((u8 *)var_s0 + 4) & 2) && (temp_v0_2 == 0xFF) && (*(u8 *)((u8 *)temp_v0 + 5) != 1)) {
                    var_s0 = temp_s2;
                    continue;
                }
            } else if ((*(u8 *)((u8 *)var_s0 + 4) & 2) || (temp_v0_2 < 0xFF) || (*(u8 *)((u8 *)temp_v0 + 5) == 1)) {
                var_s0 = temp_s2;
                continue;
            }
        }
        arg0 = func_150311C4(arg0, var_s0, temp_v0, arg1, 0);
        var_s0 = temp_s2;
    }
    return arg0;
}
/* Call context: func_150311C4: unique active project prototype */

s32 func_15030F94(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    void *temp_s1;
    void *var_s0;

    if ((arg1 == 0) || (*(s32 *)((u8 *)arg1 + 0x1D4) == 0) || (*(u8 *)((u8 *)arg1 + 0x3B) == 0)) {
        return arg0;
    }
    var_s0 = D_800C3EE0;
    while (var_s0 != 0) {
        temp_s1 = *(void **)((u8 *)var_s0 + 0x54);
        if ((*(u8 *)((u8 *)arg1 + 0x3B) != *(u8 *)var_s0) || (*(u8 *)((u8 *)var_s0 + 3) == 0)) {
            var_s0 = temp_s1;
            continue;
        }
        arg0 = func_150311C4(arg0, var_s0, arg1, arg2, arg3);
        var_s0 = temp_s1;
    }
    return arg0;
}
void *func_1503195C(void *, s32, s32);
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15031070 CURRENT (660) */
s32 func_15031070(void *arg0, void *arg1, s32 *arg2, s32 *arg3) {
    u8 *model;
    s32 base;
    s32 value;
    u16 child;
    void *object;

    model = *(u8 **)((u8 *)arg0 + 0x48);
    if (model != 0) {
        if (model[0x3F6] == 0) {
            return 0;
        }
        *arg2 = *(s32 *)(model + 0x3E8 + D_800BE9C0 * 4);
        *arg3 = *(s32 *)(*(u8 **)((u8 *)arg0 + 0x48) + 0x3E0 + D_800BE9C0 * 4);
        goto success;
    }
    base = *(s32 *)((u8 *)arg0 + 0x34);
    if (base != 0) {
        *arg2 = base + (D_800BE9C0 << 6);
        *arg3 = *(s32 *)((u8 *)arg1 + 0x1D4) + (((u8 *)arg0)[2] << 6);
        goto success;
    }
    child = *(u16 *)((u8 *)arg0 + 0x1E);
    if (child != 0) {
        object = func_1503195C(arg1, child, 0);
        if (object == 0) {
            return 0;
        }
        if (func_15031070(object, arg1, arg2, arg3) == 0) {
            return 0;
        }
        *arg2 += *(u16 *)((u8 *)arg0 + 0x20) << 6;
        return 1;
    }
    value = *(s32 *)((u8 *)arg1 + 0x1D4);
    *arg2 = value;
    value += ((u8 *)arg0)[2] << 6;
    *arg2 = value;
    *arg3 = value;
success:
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15031070 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150311C4.s")
void *func_1503195C(void *arg0, s32 arg1, s32 arg2);

void func_1503192C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = func_1503195C(arg0, arg1, arg3);
    if (temp_v0 != 0) {
        *(u8 *)((u8 *)temp_v0 + 3) = (u8) arg2;
    }
}
extern void * D_800C3EE0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503195C CURRENT (495) */
void *func_1503195C(void *arg0, s32 arg1, s32 arg2) {
    u8 temp_v0;
    void *var_v1;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0x3B);
    if (temp_v0 == 0) {
        return 0;
    }
    var_v1 = D_800C3EE0;
    while (var_v1 != 0) {
        arg0 = *(void **)((u8 *)var_v1 + 0x54);
        if ((temp_v0 == *(u8 *)var_v1) && (arg1 == *(u8 *)((u8 *)var_v1 + 6))) {
            if (arg2--) {
                var_v1 = arg0;
                continue;
            }
            return var_v1;
        }
        var_v1 = arg0;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503195C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1503195C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150319CC CURRENT (245) */
void *func_150319CC(s32 arg0, void *arg1) {
    s32 requested = arg0;
    void *next;
    void *cursor;

    if (arg1 != 0) {
        cursor = D_800C3EE0;
        if (cursor != 0) {
            arg0 = *(u8 *)((u8 *)arg1 + 0x3B);
            do {
                next = *(void **)((u8 *)cursor + 0x54);
                if ((arg0 == *(u8 *)cursor) && (requested == *(u8 *)((u8 *)cursor + 6))) {
                    return cursor;
                }
                cursor = next;
            } while (next != 0);
        }
    }
    cursor = D_800C3EE0;
    if (cursor != 0) {
        do {
            next = *(void **)((u8 *)cursor + 0x54);
            if (requested == *(u8 *)((u8 *)cursor + 6)) {
                return cursor;
            }
            cursor = next;
        } while (next != 0);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150319CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150319CC.s")
s32 func_150859AC(s32, s32);
void func_150D5440(void *, u8, s32);
void func_151D74B0(void *, u8, s8, u8, s32);
void func_150D3360(void *, u8, s32);
void func_151001B4(void *);
void func_15163BE8(void *, u8, s32);
void func_151BD828(void *, u8, s32);
extern s32 D_80090228;
extern s32 D_8009022C;

void func_15031A50(u8 *arg0, u8 *arg1) {
    s32 type = arg0[1];
    u8 *node;

    switch (type) {
    case 0x37:
        func_151001B4(arg1);
        break;
    case 0x5A:
        node = *(u8 **)(arg1 + 0x31C);
        if (node != 0) {
            *(u16 *)(node + 0x1A6) += 0xAA;
        }
        break;
    case 0x90:
        *(u32 *)(arg1 + 0x9C) |= 0x70;
        break;
    case 0x8F:
        *(u32 *)(arg1 + 0x9C) |= 0xE00;
        break;
    case 0x49:
        func_15163BE8(arg1, 0xFF, 1);
        break;
    case 0x5D:
        func_150D3360(arg1, 0xFF, 1);
        func_150D5440(arg1, 0xFF, 1);
        break;
    case 0x3D:
        func_151BD828(arg1, 0xFF, 1);
        break;
    case 0x1D:
        func_151D74B0(arg1, 0, 2, 0xFF, 1);
        break;
    case 0x5E:
    case 0x85:
        *(u32 *)(arg1 + 0x9C) |= 0x6000;
        break;
    case 0x8D:
        if (func_150859AC(0, 6) < 0x64) {
            *(s16 *)(arg0 + 0x18) = D_80090228;
        } else {
            *(s16 *)(arg0 + 0x18) = D_8009022C;
        }
        break;
    case 0x82:
        func_151D74B0(arg1, 6, -1, 0xFF, 1);
        break;
    }
}
typedef struct {
    void *object;
    u8 id;
} GameCoreMessage;

void func_1000FD38(void *, void *, s32);
s32 func_15033BDC();
void func_15100180(void *);
void func_151027E8(void *);
void func_15147D64(s32, s32);
void func_151BD7F4(void *);
void func_151D4668(void *);
void func_151D747C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15031C14 CURRENT (440) */
void func_15031C14(void *arg0) {
    u8 *object;
    GameCoreMessage first;
    GameCoreMessage second;
    GameCoreMessage *message;

    object = func_15083E90(*(u8 *)arg0);
    if (object != 0) {
        switch (((u8 *)arg0)[1]) {
        case 0x5A:
            if (*(u8 **)(object + 0x31C) != 0) {
                *(u16 *)(*(u8 **)(object + 0x31C) + 0x1A6) -= 0xAA;
            }
            break;
        case 0x90:
            *(u32 *)(object + 0x9C) &= ~0x70;
            break;
        case 0x8F:
            *(u32 *)(object + 0x9C) &= ~0xE00;
            break;
        case 0x37:
        case 0x4B:
        case 0x4C:
            func_1000FD38((void *)&func_15033BDC, arg0, (s32)object);
            if (((u8 *)arg0)[1] == 0x37) {
                func_15100180(object);
            }
            break;
        case 0x49:
            first.object = object;
            first.id = object[0x3B];
            func_151616D0(0x10, 0x29, (s32)&first);
            break;
        case 0x5D:
            second.object = object;
            message = &second;
            second.id = object[0x3B];
            func_15147D64((s32)&second, 0x2E);
            func_151494E0((s32)message, 0x2F);
            break;
        case 0x3D:
            func_151BD7F4(object);
            break;
        case 0x1A:
        case 0x1B:
        case 0x5F:
        case 0x65:
        case 0x66:
            func_151D4668(object);
            break;
        case 0x1D:
        case 0x82:
            func_151D747C(object);
            break;
        case 0x5E:
        case 0x85:
            *(u32 *)(object + 0x9C) &= ~0x6000;
            break;
        }
        if ((((u8 *)arg0)[6] == 0x16) || (((u8 *)arg0)[6] == 0x63) ||
            (((u8 *)arg0)[6] == 0x89)) {
            func_151027E8(object);
            func_151D4668(object);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15031C14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031C14.s")
typedef struct {
    u8 pad_0[0x18];
    s16 field_18;
    u8 pad_1A[0x1E];
    s32 field_38;
    s32 field_3C;
} Game5D2C0State;

extern s32 D_800902BC[];

s32 func_15031E2C(Game5D2C0State *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = arg0->field_38;
    if (var_v0 >= 3) {
        var_v0 = 5 - var_v0;
    }
    arg0->field_18 = (s16)D_800902BC[var_v0];
    arg0->field_38 = arg0->field_38 + 1;
    if (arg0->field_38 >= 6) {
        arg0->field_38 = 0;
    }
    return 0;
}
extern f32 D_800970DC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15031E7C CURRENT (1205) */
s32 func_15031E7C(u8 *arg0, u8 *arg1) {
    u8 *object;
    u32 commands;
    f32 factor;
    f32 progress;
    u32 index;
    s32 count;
    s32 marker;
    u16 kind;

    object = *(u8 **)(arg1 + 0x2D0);
    if (object == 0) {
        return 0;
    }
    commands = **(u32 **)(arg0 + 0x24);
    if (commands == 0) {
        return 0;
    }
    kind = *(u16 *)(arg1 + 0x84);
    marker = -14;
    if (kind == 0x55) {
        factor = 1.0f;
    } else if (kind == 0x56) {
        factor = 0.0f;
    } else {
        progress = *(f32 *)(object + 8);
        if ((progress >= 0.0f) && (progress <= 120.0f)) {
            factor = progress * D_800970DC;
            factor = 1.0f - factor;
        } else {
            factor = 0.0f;
        }
    }
    index = 0;
    count = 4;
    do {
        count--;
        if (*(s8 *)(commands + (index << 3)) != marker) {
            do {
                index++;
            } while (*(s8 *)(commands + (index << 3)) != marker);
        }
        if (count != 0) {
            index++;
        }
    } while (count != 0);
    *(s32 *)(commands + (index << 3)) = (((s32)(25.0f * factor + 2.0f)) & 0xFFF) | 0xF2002000;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15031E7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031E7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031FC8.s")
void func_1503F5B8(void *, s32, s32, s32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150331B8 CURRENT (2021) */
s32 func_150331B8(void *arg0, void *arg1) {
    void *temp_v0;
    u8 *state;
    u8 *state_after;
    s32 temp_t7;
    f32 temp_fv0;

    temp_v0 = *(void **)((u8 *)arg1 + 0x2D0);
    state = *(u8 **)((u8 *)arg0 + 0x48);
    if (state != 0) {
        temp_t7 = *(s32 *)((u8 *)arg1 + 0x2E4) & 0xFF;
        if (temp_t7 != 0xFF) {
            func_1503F5B8(state, 0, temp_t7, 0x3F800000, 0.0f, 1);
        }
        if (temp_v0 != 0) {
            state_after = *(u8 **)((u8 *)arg0 + 0x48);
            *(f32 *)(state_after + 8) = *(f32 *)((u8 *)temp_v0 + 8);
            temp_fv0 = *(f32 *)(state_after + 0x18);
            if (temp_fv0 <= *(f32 *)(state_after + 8)) {
                *(f32 *)(state_after + 8) = temp_fv0 - 1.0f;
            }
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150331B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150331B8.s")
void func_1503F5B8(void *, s32, s32, s32, f32, s32);

s32 func_1503327C(void *arg0, s32 arg1) {
    void *var_s0;

    var_s0 = *(void **)((u8 *)arg0 + 0x48);
    if (var_s0 == 0) {
        return 0;
    }
    if ((*(u16 *)((u8 *)var_s0 + 4) & 0x8000) != 0x8000) {
        func_1503F5B8(var_s0, 0, 0, 0x3F800000, 0.0f, 1);
        var_s0 = *(void **)((u8 *)arg0 + 0x48);
    }
    if ((*(f32 *)((u8 *)var_s0 + 0x18) - 1.0f) <= *(f32 *)((u8 *)var_s0 + 8)) {
        return 1;
    }
    return 0;
}
extern s32 D_800BE9E4;
extern u8 D_800C35EA;

s32 func_15033328(void *arg0, void *arg1) {
    if (D_800C35EA == 1) {
        return 0;
    }
    if ((*(u8 *)((u8 *)arg1 + 0xAD) == 0) && (*(f32 *)((u8 *)arg1 + 0x118) < *(f32 *)((u8 *)arg1 + 0x180))) {
        if (*(s32 *)((u8 *)arg0 + 0x38) > D_800BE9E4) {
            *(s32 *)((u8 *)arg0 + 0x38) = (s32) (*(s32 *)((u8 *)arg0 + 0x38) - D_800BE9E4);
            return 0;
        }
        return 1;
    }
    *(s32 *)((u8 *)arg0 + 0x38) = 0x1E;
    return 0;
}
extern f32 D_80097B68;

s32 func_150333A8(void *arg0, void *arg1) {
    void *temp_v0;

    if (D_800C35EA == 1) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg1 + 0xAD) != 0) {
        temp_v0 = *(void **)((u8 *)arg1 + 0x31C);
        if (temp_v0 != 0) {
            *(s8 *)((u8 *)temp_v0 + 0x11A) = 0;
        }
        return 1;
    }
    if ((D_80097B68 != *(f32 *)((u8 *)arg1 + 0x118)) && (*(f32 *)((u8 *)arg1 + 0x18) < (*(f32 *)((u8 *)arg1 + 0x118) + 300.0f))) {
        *(s8 *)((u8 *)arg0 + 3) = 0;
    } else {
        *(u8 *)((u8 *)arg0 + 3) = 0xFF;
    }
    return 0;
}
extern s32 D_800BE9E4;

s32 func_15033440(void *arg0, void *arg1) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 1);
    switch (temp_v0) {
    case 0x27:
    case 0x35:
        if (*(u8 *)((u8 *)arg1 + 5) == 5) {
            *(s8 *)((u8 *)arg0 + 2) = 0;
            *(s16 *)((u8 *)arg0 + 0x22) = (s16) (*(s16 *)((u8 *)arg0 + 0x22) + (D_800BE9E4 * 0xAAA));
        }
        break;
    case 0x29:
        if (*(u8 *)((u8 *)arg1 + 5) == 5) {
            *(s8 *)((u8 *)arg0 + 2) = 0;
        }
        break;
    }
    return 0;
}
s32 func_150334B8(u8 *arg0, void *arg1) {
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a1;
    s32 var_t1;
    s32 var_t3;
    u8 *var_v0;
    s32 var_v1;
    u8 *temp_a2;

    var_v0 = 0;
    var_v1 = 0;
    var_a1 = 0;
    if (*(u8 *)((u8 *)arg0 + 1) == 0x37) {
        var_v1 = 4;
        var_a1 = -0x64;
        var_v0 = (void *)(**(s32 **)((u8 *)arg0 + 0x24));
    }
    if (var_v0 != 0) {
        var_a0 = 0;
        if (var_v1 != 0) {
            do {
                var_v1 -= 1;
                if (*(s8 *)((var_a0 << 3) + (s32)var_v0) != -0xE) {
                    do {
                        var_a0 += 1;
                    } while (*(s8 *)((var_a0 << 3) + (s32)var_v0) != -0xE);
                }
                if (var_v1 != 0) {
                    var_a0 += 1;
                }
            } while (var_v1 != 0);
        }
        temp_a2 = var_v0;
        temp_a2 += var_a0 << 3;
        var_v1 = *(s32 *)((u8 *)temp_a2 + 0);
        temp_a3 = *(s32 *)((u8 *)temp_a2 + 4);
        temp_t0 = ((temp_a3 >> 0xC) & 0xFFF) + 2;
        temp_t2 = var_t1 = ((var_v1 >> 0xC) & 0xFFF) + var_a1;
        temp_t4 = var_t3 = var_v1 & 0xFFF;
        if (temp_t2 >= temp_t0) {
            var_t1 = temp_t2 - temp_t0;
        }
        if (var_t1 < 0) {
            var_t1 += temp_t0;
        }
        temp_v0 = (temp_a3 & 0xFFF) + 2;
        if (temp_t4 >= temp_v0) {
            var_t3 = temp_t4 - temp_v0;
        }
        if (var_t3 < 0) {
            var_t3 += temp_v0;
        }
        *(s32 *)((u8 *)temp_a2 + 0) = (s32) (((var_t1 & 0xFFF) << 0xC) | 0xF2000000 | (var_t3 & 0xFFF));
    }
    return 0;
}
s32 func_1503E5F8(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_15048B10(u8 *, void *);
void func_150A7A48(void *, void *, void *);
void func_150A9B0C(void *, f32, f32, s32, f32, f32, f32);
void func_151EFEB8(void *, s32);
s32 func_15083568(s32, s32, f32, s32);

void *func_150335C8(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *sp164;
    u8 sp124[0x40];
    f32 spE4[16];
    f32 spA4[16];
    u8 sp64[0x40];
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    u32 sp54;
    u32 sp50;
    u32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 temp_fv0;
    void *temp_v0;

    if (*(s32 *)((u8 *)arg1 + 0x1D4) == 0) {
        return 0;
    }
    temp_v0 = (void *)func_15083568((s32)arg1, arg2, 1.0f, 0);
    sp164 = temp_v0;
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 2) = (s8) arg3;
        *(f32 *)((u8 *)temp_v0 + 0x40) = (f32) *(f32 *)((u8 *)arg0 + 0x14C);
        if (arg4 != 0) {
            *(u8 *)((u8 *)temp_v0 + 0x16) = (u8) (*(u8 *)((u8 *)temp_v0 + 0x16) & 0xFFFB);
        } else {
            *(u8 *)((u8 *)temp_v0 + 0x16) = (u8) (*(u8 *)((u8 *)temp_v0 + 0x16) | 4);
        }
        func_151EFEB8(sp124, *(s32 *)((u8 *)arg1 + 0x1D4) + (arg3 << 6));
        func_15048B10(sp124, spE4);
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x14C);
        func_150A9B0C(spA4, *(f32 *)((u8 *)arg0 + 0xB8), *(f32 *)((u8 *)arg0 + 0x40), *(s32 *)((u8 *)arg0 + 0xC4), temp_fv0, *(f32 *)((u8 *)arg0 + 0x150), temp_fv0);
        spA4[12] = *(f32 *)((u8 *)arg0 + 0x14);
        spA4[13] = *(f32 *)((u8 *)arg0 + 0x18);
        spA4[14] = *(f32 *)((u8 *)arg0 + 0x1C);
        spA4[3] = 0.0f;
        spA4[7] = 0.0f;
        spA4[11] = 0.0f;
        spA4[15] = 1.0f;
        func_150A7A48(spA4, spE4, sp64);
        func_1503E5F8(sp64, (s32) &sp60, (s32) &sp5C, (s32) &sp58, (s32) &sp48, (s32) &sp44, (s32) &sp40, (s32) &sp54, (s32) &sp50, (s32) &sp4C);
        if (arg5 != 0) {
            sp58 = 0.0f;
            sp5C = 0.0f;
            sp60 = 0.0f;
        }
        func_15030D54(sp164, sp60, sp5C, sp58, sp48, sp44, sp40);
        return sp164;
    }
    return 0;
}
s32 func_1503378C(void *arg0, void *arg1) {
    u16 temp_v0;

    temp_v0 = *(u16 *)((u8 *)arg1 + 0x84);
    if ((*(u8 *)((u8 *)arg0 + 1) == 0x11) && ((temp_v0 == 0x3E) || (temp_v0 == 0x3D) || (temp_v0 == 0x41) || (temp_v0 == 0xD9) || (temp_v0 == 0x138) || (temp_v0 == 0x139))) {
        return 0;
    }
    return 1;
}
extern s32 D_800BE9E4;
extern s32 D_800902FC[];

s32 func_150337E4(Game5D2C0State *arg0, s32 arg1) {
    arg0->field_38 += D_800BE9E4;
    if (arg0->field_38 >= 0x10) {
        arg0->field_38 = 0;
        arg0->field_3C ^= 1;
    }
    arg0->field_18 = D_800902FC[arg0->field_3C];
    return 0;
}
void func_151027E8(void *);
void func_151026BC(void *, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15033838 CURRENT (195) */
s32 func_15033838(u8 *arg0, u8 *arg1) {
    s32 mode;
    s32 valid;
    u16 kind;
    u8 category;
    u8 *object;
    u8 *object2;

    valid = 0;
    category = arg0[6];
    if (category == 0x16) {
        mode = 4;
        if (*(u16 *)(arg1 + 0x84) == 0x165) {
            goto valid_kind;
        }
    } else if (category == 0x89) {
        mode = 6;
        kind = *(u16 *)(arg1 + 0x84);
        if (((kind == 0x221) || (kind == 0x223) || (kind == 0x31B)) &&
            (*(u8 *)(*(u8 **)(arg1 + 0x31C) + 0x198) == 2)) {
            goto valid_kind;
        }
    } else {
        mode = 5;
        if (*(u16 *)(arg1 + 0x84) == 0x157) {
valid_kind:
            valid = 1;
        }
    }
    if (*(s32 *)(arg0 + 0x38) == 0) {
        if ((valid != 0) &&
            ((object = *(u8 **)(arg1 + 0x31C), object[0x197] != 0) || (mode == 6)) &&
            ((*(u16 *)(object + 0x8A) & 0x2000) == 0x2000) &&
            (*(u16 *)(object + 0x19E) == 0)) {
            *(s32 *)(arg0 + 0x38) = 1;
            func_151026BC(arg1, -1, mode, 1, 0xFF, 1);
        }
    } else if ((valid == 0) ||
               (object2 = *(u8 **)(arg1 + 0x31C),
                ((*(u16 *)(object2 + 0x8A) & 0x2000) == 0)) ||
               ((object2[0x197] == 0) && (mode != 6))) {
        *(s32 *)(arg0 + 0x38) = 0;
        func_151027E8(arg1);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15033838 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033838.s")
s32 func_150334B8(u8 *, void *);
void func_1000FD38(void *, void *, s32);
s32 func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *,
                   void *, void *, s32, s32);
s32 func_15033BDC();
extern u8 D_800BEA0C;

s32 func_150339C8(u8 *arg0, void *arg1) {
    func_150334B8(arg0, arg1);
    if (D_800C35EA != 1) {
        if (D_800BEA0C != 0) {
            if (*(s32 *)(arg0 + 0x3C) != 0) {
                func_1000FD38((void *)&func_15033BDC, arg0, (s32)arg1);
            }
            *(s32 *)(arg0 + 0x3C) = 0;
        } else if (*(s32 *)(arg0 + 0x3C) == 0) {
            *(s32 *)(arg0 + 0x3C) = func_1000FA64(
                0x448, (s16)(s32)*(f32 *)((u8 *)arg1 + 0x14),
                (s16)(s32)*(f32 *)((u8 *)arg1 + 0x18),
                (s16)(s32)*(f32 *)((u8 *)arg1 + 0x1C),
                0x7D00, 0x3E8, 0x1F4, (void *)&func_15033BDC,
                arg0, arg1, 0, 0) | 0x80000000;
        }
    }
    return 0;
}
void func_1508B20C(f32, f32, f32, s32);
s32 func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *,
                   void *, void *, s32, s32);
s32 func_15033BDC();
extern u8 D_800BE616;

s32 func_15033AD8(void *arg0, void *arg1) {
    s32 temp_v0;

    if (D_800BE616 != 0) {
        func_1508B20C(*(f32 *)((u8 *)arg1 + 0x14),
                      *(f32 *)((u8 *)arg1 + 0x18),
                      *(f32 *)((u8 *)arg1 + 0x1C), 0x44610000);
    }
    if (*(s32 *)((u8 *)arg0 + 0x38) == 0) {
        temp_v0 = *(s32 *)((u8 *)arg0 + 0x3C);
        if (temp_v0 < 0x1E) {
            *(s32 *)((u8 *)arg0 + 0x3C) = temp_v0 + D_800BE9E4;
        } else {
            *(s32 *)((u8 *)arg0 + 0x3C) = func_1000FA64(
                0x513, (s16)(s32)*(f32 *)((u8 *)arg1 + 0x14),
                (s16)(s32)*(f32 *)((u8 *)arg1 + 0x18),
                (s16)(s32)*(f32 *)((u8 *)arg1 + 0x1C),
                0x7D00, 0x3E8, 0x1F4, &func_15033BDC,
                arg0, arg1, 0, 0);
            *(s32 *)((u8 *)arg0 + 0x38) = 0x513;
        }
    }
    return 0;
}
typedef struct {
    u8 pad_0;
    u8 type;
    u8 pad_2[0x36];
    s32 sound;
    s32 handle;
} GameCoreSoundOwner;

typedef struct {
    u8 pad_0[0x19C];
    u16 timer;
} GameCoreSoundChild;

typedef struct {
    s32 active;
    u8 pad_4[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 pad_20[0x64];
    u16 kind;
    u8 pad_86[0x296];
    GameCoreSoundChild *child;
} GameCoreSoundActor;

typedef struct {
    u8 pad_0[2];
    s16 x;
    s16 y;
    s16 z;
    u8 pad_8[0x10];
    GameCoreSoundOwner *owner;
    GameCoreSoundActor *actor;
    u8 pad_20[4];
    u16 sound;
} GameCoreSoundHandle;

void func_10010FFC(s32, s32, s32, s32, s32, void *);
void func_100111C8(s32, void *);
u32 func_150ADA20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15033BDC CURRENT (120) */
s32 func_15033BDC(GameCoreSoundHandle *arg0, s32 arg1, s32 *arg2,
                  s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    GameCoreSoundOwner *owner;
    GameCoreSoundActor *actor;
    GameCoreSoundChild *child;
    s32 sound;
    s32 previousSound;
    u16 kind;
    u16 handle;

    owner = arg0->owner;
    actor = arg0->actor;
    if ((owner != 0) && (actor != 0) && (actor->active != 0)) {
        arg0->x = (s16)(s32)actor->x;
        arg0->y = (s16)(s32)actor->y;
        arg0->z = (s16)(s32)actor->z;
        if (*arg2 != 0) {
            if (owner->type == 0x37) {
                previousSound = owner->sound;
                kind = actor->kind;
                sound = -1;
                if ((kind != (previousSound & 0xFFFF)) && (kind == 0x15F)) {
                    sound = (func_150ADA20() & 3) + 0x444;
                }
                if (sound != -1) {
                    func_10010FFC(0, sound, 0x5DC0, 0, 0, actor);
                }
                owner->sound = actor->kind;
            } else {
                child = actor->child;
                if ((child != 0) && (child->timer < 0x78) && (owner->sound == 0x513)) {
                    owner->sound = 0x3A1;
                    owner->handle = func_1000FA64(
                        0x3A1, (s16)(s32)actor->x, (s16)(s32)actor->y,
                        (s16)(s32)actor->z, 0x7D00, 0x3E8, 0x1F4,
                        (void *)&func_15033BDC, owner, actor, 0, 0);
                    return 1;
                }
            }
            return 0;
        }
        if (owner->type == 0x37) {
            handle = arg0->sound;
            if (handle != 0) {
                func_100111C8(handle, arg0);
                arg0->sound = 0;
            }
            *arg6 = 0;
            return 0;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15033BDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033BDC.s")
s32 func_15033E00(s32 arg0, void *arg1) {
    if (*(u8 *)((u8 *)arg1 + 5) == 3) {
        return 1;
    }
    return 0;
}
extern void *D_800C3EE0;

s32 func_15033E28(void *arg0, void **arg1) {
    s32 var_v1;
    void *temp_v0;
    void *var_a0;

    var_v1 = 0;
    if (D_800C3EE0 == 0) {
        return 0;
    }
    var_a0 = D_800C3EE0;
    if (D_800C3EE0 != 0) {
        do {
            temp_v0 = *(void **)((u8 *)var_a0 + 0x54);
            if (*(u8 *)((u8 *)arg0 + 0x3B) == *(u8 *)var_a0) {
                arg1[var_v1] = var_a0;
                var_v1 += 1;
            }
            var_a0 = temp_v0;
        } while (temp_v0 != 0);
    }
    return var_v1;
}

void *func_15033E84(void *arg0) {
    void *temp_v0;
    void *var_v1;

    var_v1 = D_800C3EE0;
    while (var_v1 != 0) {
        temp_v0 = *(void **)((u8 *)var_v1 + 0x54);
        if (*(u8 *)((u8 *)arg0 + 0x3B) == *(u8 *)((u8 *)var_v1 + 0)) {
            return var_v1;
        }
        var_v1 = temp_v0;
    }
    return 0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15033EC4 CURRENT (240) */
void func_15033EC4(s32 arg0, s32 arg1) {
    u8 temp_a1;
    void *temp_v1;
    void *var_v0;

    var_v0 = D_800C3EE0;
    if (var_v0 != 0) {
        do {
            temp_a1 = *(u8 *)((u8 *)var_v0 + 0);
            temp_v1 = *(void **)((u8 *)var_v0 + 0x54);
            if (arg0 == temp_a1) {
                *(u8 *)((u8 *)var_v0 + 0) = arg1;
            } else if (arg1 == temp_a1) {
                *(u8 *)((u8 *)var_v0 + 0) = arg0;
            }
            var_v0 = temp_v1;
        } while (temp_v1 != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15033EC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033EC4.s")
extern u8 D_800C35EA;

s32 func_15033F0C(s32 arg0, void *arg1) {
    void *temp_v1;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp_v1 = *(void **)((u8 *)arg1 + 0x31C);
    if ((temp_v1 != 0) && (*(u8 *)((u8 *)temp_v1 + 0x78) != 9) && (*(u8 *)((u8 *)temp_v1 + 0x11A) != 3)) {
        *(u8 *)((u8 *)temp_v1 + 0x11A) = 0U;
        return 1;
    }
    return 0;
}
s32 func_15033F70(s32 arg0, void *arg1) {
    u8 temp_v0;
    void *temp_v1;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp_v1 = *(void **)((u8 *)arg1 + 0x31C);
    if (temp_v1 != 0) {
        temp_v0 = *(u8 *)((u8 *)temp_v1 + 0x78);
        if ((temp_v0 != 0xC) && (temp_v0 != 0x16) && (*(u8 *)((u8 *)temp_v1 + 0x11A) != 3)) {
            *(u8 *)((u8 *)temp_v1 + 0x11A) = 0U;
            return 1;
        }
    }
    return 0;
}
