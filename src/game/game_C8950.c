#include "types.h"

/*
 * Reviewed source unit: src/game/game_C8950.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509B4A0
 * - func_1509B570
 * - func_1509B5AC
 * - func_1509B704
 * - func_1509B810
 * - func_1509B950
 * - func_1509BA04
 * - func_1509BBA0
 * - func_1509BE40
 * - func_1509BFB0
 * - func_1509C120
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameC8950Node {
    u16 key;
    u8 pad2[0x16];
    struct GameC8950Node *next;
    struct GameC8950Node *prev;
} GameC8950Node;

typedef struct GameC8950List {
    u16 count;
    u8 pad2[2];
    GameC8950Node *head;
    GameC8950Node *tail;
} GameC8950List;

extern GameC8950List D_800D2F48;

void func_15096970(void);
void func_1509C120(void);
void func_1509C3A0(void);
void func_1509B5AC(u16, s32);
s32 func_1509CBD4(u16);
extern s32 D_8003C8E0;
extern u8 D_800D2F3C;
extern u16 *D_800D2F40;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509B4A0 CURRENT (10) */
void func_1509B4A0(s32 arg0, s32 arg1) {
    u8 *count_ptr;
    s32 context;
    s32 offset;
    s32 index;

    context = arg1;
    D_8003C8E0 = 0x05000000;
    func_1509C120();
    func_15096970();
    count_ptr = &D_800D2F3C;
    index = 0;
    offset = 0;
    if ((s32)*count_ptr > 0) {
        do {
            if (func_1509CBD4(*(u16 *)((u8 *)D_800D2F40 + offset)) != 0) {
                func_1509B5AC(*(u16 *)((u8 *)D_800D2F40 + offset), context);
            }
            index++;
            offset += 2;
        } while (index < (s32)*count_ptr);
    }
    func_1509C3A0();
    D_8003C8E0 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509B4A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B4A0.s")
GameC8950Node *func_1509B704(s16);                  /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509B570 CURRENT (10) */
void *func_1509B570(s32 arg0) {
    s32 temp_v0;

    temp_v0 = (s32) func_1509B704((s16)arg0);
    if (temp_v0 != 0) {
        return (void *)(temp_v0 + *(u16 *)(temp_v0 + 0xA));
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509B570 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B570.s")
void func_1509B8FC(s16);
void func_1509B810(GameC8950Node *);
void func_150ADAF0(u16 *, s32);
void func_100226F0(void *, u16);
extern void *D_800D2E4C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509B5AC CURRENT (1430) */
GameC8950Node *func_1509B5AC(u16 arg0, s32 arg1) {
    s32 sp20;
    GameC8950Node *temp_s0;
    GameC8950Node *temp_v0;
    s32 temp_v0_2;
    u16 temp_v1;

    sp20 = (s16)arg0;
    temp_v0 = func_1509B704((s16)arg0);
    temp_s0 = temp_v0;
    if ((arg1 == 0) && (((u8 *)D_800D2E4C)[((s32)arg0) >> 3] & (1 << (arg0 & 7)))) {
        return 0;
    }
    if (temp_v0 == 0) {
        func_1509B8FC((s16)sp20);
        /* The active callee is void; re-find the node it just created. */
        temp_s0 = func_1509B704((s16)arg0);
        func_1509B810(temp_s0);
        temp_v0_2 = temp_s0->key & 0xFFFF03FF;
        if (!(((u8 *)D_800D2E4C)[temp_v0_2 >> 3] & (1 << (temp_v0_2 & 7)))) {
            D_8003C8E0 = 0x06000000;
            func_150ADAF0(&temp_s0->key, 0);
            D_8003C8E0 = 0;
        }
        if ((arg1 == 0) || (temp_s0->key & 0x400)) {
            temp_s0->key |= 0x4000;
        }
    } else if (arg1 != 0) {
        temp_v1 = temp_v0->key;
        if ((temp_v1 & 0x1000) && !(temp_v1 & 0x800)) {
            func_100226F0((u8 *)temp_s0 + *(u16 *)((u8 *)temp_s0 + 0xA),
                            *(u16 *)((u8 *)temp_s0 + 6));
        }
    }
    return temp_s0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509B5AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B5AC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509B704 CURRENT (220) */
GameC8950Node *func_1509B704(s16 arg0) {
    s32 index;
    s32 mask;
    GameC8950Node *node;

    node = D_800D2F48.head;
    mask = 0xFFFF03FF;
    index = 0;
    if ((s32) D_800D2F48.count > 0) {
        do {
            index += 1;
            if (arg0 == (node->key & mask)) {
                return node;
            }
            node = node->next;
        } while (index < (s32) D_800D2F48.count);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509B704 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B704.s")
void func_10004074(s32);

void func_1509B764(GameC8950Node *arg0) {
    if (D_800D2F48.count == 1) {
        D_800D2F48.head = 0;
        D_800D2F48.tail = 0;
    } else {
        if (arg0 == D_800D2F48.head) {
            D_800D2F48.head = arg0->next;
            arg0->next->prev = 0;
        } else {
            arg0->prev->next = arg0->next;
        }
        if (arg0 == D_800D2F48.tail) {
            D_800D2F48.tail = arg0->prev;
            arg0->prev->next = 0;
        } else {
            arg0->next->prev = arg0->prev;
        }
    }
    func_10004074((s32)arg0);
    D_800D2F48.count -= 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509B810 CURRENT (1545) */
void func_1509B810(GameC8950Node *arg0) {
    GameC8950Node *temp_v0;
    GameC8950Node *var_v0;
    s32 var_a3;

    var_v0 = D_800D2F48.tail;
    if (D_800D2F48.count == 0) {
        D_800D2F48.head = arg0;
        D_800D2F48.tail = arg0;
        arg0->next = 0;
        arg0->prev = 0;
        D_800D2F48.count += 1;
        return;
    }
    var_a3 = 0;
    if ((s32) D_800D2F48.count > 0) {
loop_3:
        var_a3 += 1;
        if ((var_v0->key & 0xFFFF03FF) < (arg0->key & 0xFFFF03FF)) {
            if (var_v0 == D_800D2F48.tail) {
                arg0->prev = var_v0;
                arg0->next = 0;
                var_v0->next = arg0;
                D_800D2F48.tail = arg0;
                D_800D2F48.count += 1;
                return;
            }
            arg0->prev = var_v0;
            arg0->next = var_v0->next;
            var_v0->next->prev = arg0;
            var_v0->next = arg0;
            D_800D2F48.count += 1;
            return;
        }
        var_v0 = var_v0->prev;
        if (var_a3 >= (s32) D_800D2F48.count) {
            /* Duplicate return node #8. Try simplifying control flow for better match */
            temp_v0 = D_800D2F48.head;
            D_800D2F48.head = arg0;
            arg0->prev = 0;
            arg0->next = temp_v0;
            temp_v0->prev = arg0;
            D_800D2F48.count += 1;
            return;
        }
        goto loop_3;
    }
    temp_v0 = D_800D2F48.head;
    D_800D2F48.head = arg0;
    arg0->prev = 0;
    arg0->next = temp_v0;
    temp_v0->prev = arg0;
    D_800D2F48.count += 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509B810 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B810.s")
typedef struct {
    u16 field_0;
    s16 field_2;
} GameC8950Data;

GameC8950Data *func_1502B5C8(void *, s32, s32, s16);
void *func_1509B950(void *);
extern s32 D_800BE9F0;

void func_1509B8FC(s16 arg0) {
    GameC8950Data *temp_v0;
    s32 sp18;

    temp_v0 = func_1502B5C8(&sp18, 2, 0x14, arg0);
    temp_v0->field_0 |= arg0;
    temp_v0->field_2 = D_800BE9F0;
    func_1509B950(temp_v0);
}
void *func_10003C40(s32, s32, s32, s32);
void func_10023A10(void *, void *, s32);
void func_100226F0(void *, u16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509B950 CURRENT (910) */
void *func_1509B950(void *arg0) {
    u16 temp_v0;
    u16 temp_t0;
    u16 temp_v0_2;
    u16 temp_t6;
    void *temp_v0_3;
    void *temp_s0;

    temp_s0 = arg0;
    temp_v0 = *(u16 *)((u8 *)temp_s0 + 4);
    temp_t0 = temp_v0 + (8 - ((s32)((u8 *)temp_s0 + temp_v0) & 7));
    temp_v0_2 = temp_t0 + *(u16 *)((u8 *)temp_s0 + 6);
    *(u16 *)((u8 *)temp_s0 + 4) = temp_v0_2;
    temp_t6 = (temp_v0_2 - ((s32)((u8 *)temp_s0 + temp_v0_2) & 7)) + 8;
    *(u16 *)((u8 *)temp_s0 + 0xA) = temp_t0;
    *(u16 *)((u8 *)temp_s0 + 4) = temp_t6;
    temp_v0_3 = func_10003C40(temp_t6 & 0xFFFF, 0xFF, 2, 0);
    if (temp_v0_3 == 0) {
        for (;;) {
        }
    }
    func_10023A10(temp_s0, temp_v0_3, *(u16 *)((u8 *)temp_s0 + 4));
    func_100226F0((u8 *)temp_v0_3 + *(u16 *)((u8 *)temp_v0_3 + 0xA),
                  *(u16 *)((u8 *)temp_v0_3 + 6));
    func_10004074((s32)temp_s0);
    return temp_v0_3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509B950 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B950.s")
void func_1509C228(void);
extern u8 D_800D2E69;
extern u8 D_800D2E70[];
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509BA04 CURRENT (260) */
void func_1509BA04(s32 arg0) {
    GameC8950Node *node;
    GameC8950Node *next;
    s32 count;
    s32 i;
    s32 key;
    s32 index;
    s32 mask;
    u16 original;

    count = D_800D2F48.count;
    node = D_800D2F48.head;
    if (D_800D2E69 != 0) {
        func_1509C228();
        D_800D2E69 = 0;
    }
    i = 0;
    if (count > 0) {
        do {
            original = node->key;
            key = original & 0xFFFF03FF;
            index = key >> 3;
            mask = 1 << (key & 7);
            next = node->next;
            if ((((u8 *)D_800D2E4C)[index] & mask) && arg0 == 0) {
                func_1509B764(node);
                D_800D2E70[key] = 3;
            } else if (arg0 != 0 || (original & 0x8000) ||
                       ((original & 0x1000) && D_800BE9F0 != *(u16 *)((u8 *)node + 2))) {
                D_8003C8E0 = 0x06000001;
                func_150ADAF0(&node->key, 3);
                D_8003C8E0 = 0;
                func_1509B764(node);
                if (((u8 *)D_800D2E4C)[index] & mask) {
                    D_800D2E70[key] = 3;
                } else {
                    D_800D2E70[key] = 0;
                }
            }
            i++;
            node = next;
        } while (i != count);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509BA04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BA04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BBA0.s")
extern s32 D_800D2F60[];
extern s32 D_800D3840;
extern void (*D_80088498[])(s32, s32, s32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509BE40 CURRENT (7368) */
void func_1509BE40(s32 count, s32 descriptor, s32 first, ...) {
    s32 *args;
    s32 old_count;
    s32 payload;
    s32 index;

    old_count = D_800D3840;
    payload = descriptor & 0xFFF;
    D_800D2F60[0] = payload;
    D_800D2F60[1] = first;
    args = &first + 1;
    for (index = 0; index < count; index++) {
        D_800D2F60[index + 2] = *args++;
    }
    D_800D3840 = count + 2;
    D_80088498[((descriptor & 0xF000) >> 12) - 1](payload, first, D_800D2F60, payload);
    D_800D3840 = old_count;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509BE40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BE40.s")
extern void (*D_800884D4[])(s32, s32, s32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509BFB0 CURRENT (7368) */
void func_1509BFB0(s32 count, s32 descriptor, s32 first, s32 arg3, s32 arg4) {
    s32 *args;
    s32 old_count;
    s32 payload;
    s32 index;

    old_count = D_800D3840;
    payload = descriptor & 0xFFF;
    D_800D2F60[0] = payload;
    D_800D2F60[1] = first;
    args = &first + 1;
    for (index = 0; index < count; index++) {
        D_800D2F60[index + 2] = *args++;
    }
    D_800D3840 = count + 2;
    D_800884D4[((descriptor & 0xF000) >> 12) - 1](payload, first, D_800D2F60, payload);
    D_800D3840 = old_count;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509BFB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BFB0.s")
s32 func_150ADA20(void);
extern void *D_800D2E4C;

typedef struct {
    void *old;
    void *entries[4];
} GameC8950SwapLocals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509C120 CURRENT (1144) */
void func_1509C120(void) {
    GameC8950SwapLocals locals;
    s32 temp_s1;
    s32 temp_s2;
    void **var_s0_2;
    s32 temp_s3;
    s32 var_s0;

    temp_s3 = func_150ADA20() & 3;
    locals.old = D_800D2E4C;
    if ((D_800D2E4C == 0) || (func_150ADA20() & 4)) {
        var_s0 = 0;
        if (temp_s3 >= 0) {
            var_s0_2 = &locals.entries[0];
            temp_s1 = (s32)&var_s0_2[temp_s3 + 1];
            do {
                *var_s0_2 = func_10003C40(0x1B, 0xFF, 2, 0);
                var_s0_2++;
            } while (temp_s1 != (s32)var_s0_2);
            var_s0 = 0;
        }
        if (temp_s3 >= 0) {
            temp_s1 = temp_s3 + 1;
            temp_s2 = (s32)&locals.entries[0];
            do {
                if (var_s0 != temp_s3) {
                    func_10004074(*(s32 *)(temp_s2 + (var_s0 * 4)));
                }
                var_s0++;
            } while (temp_s1 != var_s0);
        }
        temp_s2 = (s32)&locals.entries[0];
        D_800D2E4C = *(void **)(temp_s2 + (temp_s3 * 4));
        if (locals.old != 0) {
            func_10023A10(locals.old, D_800D2E4C, 0x1B);
            func_10004074((s32)locals.old);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509C120 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509C120.s")
typedef struct {
    u8 pad0[0xF];
    u8 flags_F;
} GameC8950GlobalState;

void func_1509BFB0(s32, s32, s32, s32, s32);
extern u8 D_800D2E68;

void func_1509C228(void) {
    if ((D_800D2E68 & 8) ||
        (((GameC8950GlobalState *)D_800D2E4C)->flags_F & 1)) {
        func_1509BFB0(2, 0x2000, 0x36, 0, 1);
        return;
    }
    func_1509BFB0(2, 0x2000, 0x36, 1, 1);
}

extern s32 D_800BE9F0;
extern u8 D_800D2E44;

s32 func_1509C2A4(void) {
    if ((D_800BE9F0 == 3) || (D_800BE9F0 == 5) || (D_800BE9F0 == 9) || (D_800BE9F0 == 0xD) || (D_800BE9F0 == 0xF) || (D_800BE9F0 == 0x11) || (D_800BE9F0 == 0x15) || (D_800BE9F0 == 0x16) || (D_800BE9F0 == 0x18) || (D_800BE9F0 == 0x1A) || (D_800BE9F0 == 0x1D) || (D_800BE9F0 == 0x1F) || (D_800BE9F0 == 0x20) || (D_800BE9F0 == 0x21) || (D_800BE9F0 == 0x22) || (D_800BE9F0 == 0x24) || (D_800BE9F0 == 0x25) || (D_800BE9F0 == 0x2A) || (D_800BE9F0 == 0x2B) || (D_800BE9F0 == 0x2D) || (D_800BE9F0 == 0x30) || (D_800BE9F0 == 0x33) || (D_800BE9F0 == 0x34) || (D_800BE9F0 == 0x38) || (D_800BE9F0 == 0x3E) || (D_800BE9F0 == 0x3F) || (D_800D2E44 != 0)) {
        return 0;
    }
    return 1;
}
void func_15007718(s8);
extern s8 D_8008FDA8;
extern s8 D_800BE3DF;
extern s32 D_800BE9F4;
extern u8 D_800C35C4;
extern u8 D_800D2E43;

void func_1509C3A0(void) {
    if ((D_800D2E43 != 0) && (D_800D2E44 == 0) &&
        (func_1509C2A4() != 0)) {
        D_800BE3DF = D_800BE9F4;
        if (D_800C35C4 == 0) {
            func_15007718(D_8008FDA8);
        }
        D_800D2E43 = 0;
    }
}
s32 func_1509C414(s32 arg0) {
    return ((*(u8 *)((u8 *)D_800D2E4C + 3) & 1) << 0xA) + arg0 + 0x1400;
}
