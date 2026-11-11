#include "types.h"
#include "game_functions.h"
#include "../lib/ultralib/include/compiler/ido/stdarg.h"

/*
 * Reviewed source unit: src/game/game_C8950.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509BE40
 * - func_1509BFB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameC8950Node {
    u16 key;
    u8 pad2[8];
    u16 data_offset;
    u8 padC[0xC];
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
GameC8950Node *func_1509B5AC(s32, s32);
s32 func_1509CBD4(u16);
extern s32 D_8003C8E0;
extern u8 D_800D2F3C;
extern u16 *D_800D2F40;

void func_1509B4A0(s16 arg0, s32 arg1) {
    s32 context;
    s32 index;

    context = arg1;
    D_8003C8E0 = 0x05000000;
    func_1509C120();
    func_15096970();
    for (index = 0; index < D_800D2F3C; index++) {
        if (func_1509CBD4(D_800D2F40[index]) == 0) {
            continue;
        }
        func_1509B5AC(D_800D2F40[index], context);
    }
    func_1509C3A0();
    D_8003C8E0 = 0;
}
GameC8950Node *func_1509B704(s16);                  /* extern */

void *func_1509B570(s32 arg0) {
    GameC8950Node *node;

    node = func_1509B704((s16)arg0);
    if (node != NULL) {
        return (u8 *)node + node->data_offset;
    }
    return NULL;
}
GameC8950Node *func_1509B8FC(s16);
void func_1509B810(GameC8950Node *);
void func_150ADAF0(u16 *, s32);
void func_100226F0(void *, u16);
extern void *D_800D2E4C;

GameC8950Node *func_1509B5AC(s32 arg0, s32 arg1) {
    GameC8950Node *node;

    node = func_1509B704((s16)arg0);
    if ((arg1 == 0) && (*((arg0 >> 3) + (u8 *)D_800D2E4C) & (1 << (arg0 & 7)))) {
        return NULL;
    }
    if (node == NULL) {
        node = func_1509B8FC((s16)arg0);
        func_1509B810(node);
        if (!(*(((s32)(node->key & 0xFFFF03FF) >> 3) + (u8 *)D_800D2E4C) & (1 << ((node->key & 0xFFFF03FF) & 7)))) {
            D_8003C8E0 = 0x06000000;
            func_150ADAF0(&node->key, 0);
            D_8003C8E0 = 0;
        }
        if ((arg1 == 0) || (node->key & 0x400)) {
            node->key |= 0x4000;
        }
    } else if (arg1 != 0) {
        if ((node->key & 0x1000) && !(node->key & 0x800)) {
            func_100226F0((u8 *)node + node->data_offset, *(u16 *)((u8 *)node + 6));
        }
    }
    return node;
}
GameC8950Node *func_1509B704(s16 arg0) {
    s32 index;
    s32 mask;
    GameC8950Node *node;

    node = D_800D2F48.head;
    mask = 0xFFFF03FF;
    for (index = 0; index < (s32) D_800D2F48.count; index++) {
        if (arg0 == (node->key & mask)) {
            return node;
        }
        node = node->next;
    }
    return 0;
}
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
void func_1509B810(GameC8950Node *arg0) {
    GameC8950Node *temp_v0;
    GameC8950Node *var_v0;
    s32 var_a3;
    s32 mask;
    s32 key;

    mask = 0xFFFF03FF;
    var_v0 = D_800D2F48.tail;
    key = arg0->key & mask;
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
        do {
        var_a3 += 1;
        if ((var_v0->key & mask) < key) {
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
        } while (var_a3 < (s32)D_800D2F48.count);
    }
    temp_v0 = D_800D2F48.head;
    D_800D2F48.head = arg0;
    arg0->prev = 0;
    arg0->next = temp_v0;
    temp_v0->prev = arg0;
    D_800D2F48.count += 1;
}
typedef struct {
    u16 field_0;
    s16 field_2;
} GameC8950Data;

GameC8950Data *func_1502B5C8(void *, s32, s32, s16);
void *func_1509B950(void *);
extern s32 D_800BE9F0;

GameC8950Node *func_1509B8FC(s16 arg0) {
    GameC8950Data *temp_v0;
    s32 sp18;

    temp_v0 = func_1502B5C8(&sp18, 2, 0x14, arg0);
    temp_v0->field_0 |= arg0;
    temp_v0->field_2 = D_800BE9F0;
    return func_1509B950(temp_v0);
}
void *func_10003C40(s32, s32, s32, s32);
void func_10023A10(void *, void *, s32);
void func_100226F0(void *, u16);

typedef struct {
    u8 pad0[4];
    u16 size;
    u16 extra;
    u8 pad8[2];
    u16 offset;
} GameC8950Block;

void *func_1509B950(void *arg) {
    GameC8950Block *arg0 = arg;
    GameC8950Block *new;
    s32 align;

    align = 8 - (((s32)arg0 + arg0->size) & 7);
    arg0->offset = arg0->size + align;
    arg0->size = arg0->offset + arg0->extra;
    arg0->size = (arg0->size - (((s32)arg0 + arg0->size) & 7)) + 8;
    new = func_10003C40(arg0->size, 0xFF, 2, 0);
    if (new == NULL) {
        for (;;) {
        }
    }
    func_10023A10(arg0, new, arg0->size);
    func_100226F0((u8 *)new + new->offset, new->extra);
    func_10004074((s32)arg0);
    return new;
}
void func_1509C228(void);
extern u8 D_800D2E69;
extern u8 D_800D2E70[];
extern s32 D_800BE9F0;

void func_1509BA04(s32 arg0) {
    GameC8950Node *node;
    GameC8950Node *next;
    s32 count;
    s32 i;
    s32 key;
    s32 index;
    s32 mask;
    s32 original;

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
            if ((*(u8 *)(index + (u32)D_800D2E4C) & mask) && arg0 == 0) {
                func_1509B764(node);
                D_800D2E70[key] = 3;
            } else if (arg0 != 0 || (original & 0x8000) ||
                       ((original & 0x1000) && D_800BE9F0 != *(u16 *)((u8 *)node + 2))) {
                D_8003C8E0 = 0x06000001;
                func_150ADAF0(&node->key, 3);
                D_8003C8E0 = 0;
                func_1509B764(node);
                if (!(*(u8 *)(index + (u32)D_800D2E4C) & mask)) {
                    D_800D2E70[key] = 0;
                } else {
                    D_800D2E70[key] = 3;
                }
            }
            i++;
            node = next;
        } while (i != count);
    }
}
void func_15096D08(void);
void func_1509B4A0(s16, s32);
s32 func_1509BE40(s32, ...);
extern u8 D_800BE616;
extern s16 D_800BE9F2;
extern s32 D_800D2E48;
extern s32 D_800D2F58;
extern s32 D_800D3858;

void func_1509BBA0(s32 mode) {
    GameC8950Node *node;
    u16 key;
    s32 marked;
    s32 index;
    s32 flags;

    node = D_800D2F48.head;
    func_15096D08();
    if ((D_800BE616 == 0) && (D_800BE9F0 != 0x32) &&
        (func_1509BE40(0, 0x2000, 0x93) == 0) && (mode == 2)) {
        return;
    }
    func_1509C228();
    index = 0;
    if ((s32)D_800D2F48.count > 0) {
        do {
            key = node->key & 0x3FF;
            D_800D2E48 = key;
            flags = node->key;
            marked = flags & 0x8000;
            if (marked != 0) {
                node = node->next;
                goto loop_tail;
            }
            if (mode == 4) {
                if (*(u8 *)((key >> 3) + (u32)D_800D2E4C) & (1 << (key & 7))) {
                    D_8003C8E0 = 0x06000002;
                    func_150ADAF0(&node->key, 4);
                    D_8003C8E0 = 0;
                    D_800D2E70[key] = 3;
                    node->key |= 0x8000;
                    node = node->next;
                    goto loop_tail;
                }
            } else if (!(*(u8 *)((key >> 3) + (u32)D_800D2E4C) & (1 << (key & 7)))) {
                if (flags & 0x4000) {
                    D_8003C8E0 = 0x06000003;
                    func_150ADAF0(&node->key, 1);
                    D_8003C8E0 = 0;
                    marked = (flags = node->key &= 0xBFFF) & 0x8000;
                }
                if (marked != 0) {
                    node = node->next;
                    goto loop_tail;
                }
                if (!(flags & 0x2000) || (D_800BE9F0 == *(u16 *)((u8 *)node + 2))) {
                    if (mode == 2 || ((mode == 1) && !(flags & 0x400))) {
                        D_8003C8E0 = 0x06000004;
                        func_150ADAF0(&node->key, mode);
                        D_8003C8E0 = 0;
                    }
                    if (mode == 2) {
                        D_800D2E70[key] = 1;
                    }
                } else {
                    D_800D2E70[key] = 2;
                }
            } else {
                D_800D2E70[key] = 3;
            }
            node = node->next;
loop_tail:
            index++;
        } while (index < (s32)D_800D2F48.count);
    }
    if (D_800D2F58 != 0) {
        D_800D2F58 = 0;
        func_1509B4A0(D_800BE9F2, 0);
    }
    D_800D3858 = 0;
}
extern s32 D_800D2F60[];
extern s32 D_800D3840;
extern s32 (*D_80088498[])(s32, s32, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509BE40 CURRENT (929) */
s32 func_1509BE40(s32 count, ...) {
    va_list args;
    s32 old_count;
    s32 descriptor;
    s32 first;
    s32 type;
    s32 index;
    s32 result;

    va_start(args, count);
    descriptor = va_arg(args, s32);
    first = va_arg(args, s32);
    old_count = D_800D3840;
    type = ((descriptor & 0xF000) >> 12) - 1;
    descriptor &= 0xFFF;
    D_800D2F60[0] = descriptor;
    D_800D2F60[1] = first;
    for (index = 0; index < count; index++) {
        D_800D2F60[index + 2] = va_arg(args, s32);
    }
    va_end(args);
    D_800D3840 = count + 2;
    result = D_80088498[type](descriptor, first, D_800D2F60);
    D_800D3840 = old_count;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509BE40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BE40.s")

extern s32 (*D_800884D4[])(s32, s32, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509BFB0 CURRENT (929) */
void func_1509BFB0(s32 count, ...) {
    va_list args;
    s32 old_count;
    s32 descriptor;
    s32 first;
    s32 type;
    s32 index;

    va_start(args, count);
    descriptor = va_arg(args, s32);
    first = va_arg(args, s32);
    old_count = D_800D3840;
    type = ((descriptor & 0xF000) >> 12) - 1;
    descriptor &= 0xFFF;
    D_800D2F60[0] = descriptor;
    D_800D2F60[1] = first;
    for (index = 0; index < count; index++) {
        D_800D2F60[index + 2] = va_arg(args, s32);
    }
    va_end(args);
    D_800D3840 = count + 2;
    D_800884D4[type](descriptor, first, D_800D2F60);
    D_800D3840 = old_count;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509BFB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BFB0.s")

extern void *D_800D2E4C;

typedef struct {
    void *old;
    void *entries[4];
} GameC8950SwapLocals;

void func_1509C120(void) {
    s32 n;
    s32 i;
    void *entries[4];
    void *old;

    n = func_150ADA20() & 3;
    old = D_800D2E4C;
    if (old == NULL || (func_150ADA20() & 4)) {
        for (i = 0; i <= n; i++) {
            entries[i] = func_10003C40(0x1B, 0xFF, 2, 0);
        }
        for (i = 0; i <= n; i++) {
            if (i != n) {
                func_10004074((s32)entries[i]);
            }
        }
        D_800D2E4C = entries[n];
        if (old != NULL) {
            func_10023A10(old, D_800D2E4C, 0x1B);
            func_10004074((s32)old);
        }
    }
}
typedef struct {
    u8 pad0[0xF];
    u8 flags_F;
} GameC8950GlobalState;

void func_1509BFB0(s32, ...);
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
