#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_13BB20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510E950
 * - func_1510F8D8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150AD8B0(f32 *, f32 *, f32 *);
extern s32 D_800D3300;

s32 func_1510E670(s32 arg0) {
    u8 **verts;
    s32 offset;
    s16 *v0;
    s16 *v1;
    s16 *v2;
    f32 edge1[3];
    f32 edge2[3];
    f32 normal[3];
    f32 normal_y;

    verts = *(u8 ***)((u8 *)&D_800D3300 + (arg0 * 0x10) + 4);
    offset = *(s32 *)((u8 *)&D_800D3300 + (arg0 * 0x10) + 8);
    if (verts != 0) {
        v0 = (s16 *)(verts[0] + offset);
        v1 = (s16 *)(verts[1] + offset);
        v2 = (s16 *)(verts[2] + offset);
        edge1[0] = v1[0] - v0[0];
        edge1[1] = v1[1] - v0[1];
        edge1[2] = v1[2] - v0[2];
        edge2[0] = v2[0] - v0[0];
        edge2[1] = v2[1] - v0[1];
        edge2[2] = v2[2] - v0[2];
        func_150AD8B0(edge1, edge2, normal);
        normal_y = normal[1];
        if (normal_y < 0.0f) {
            return 0;
        }
        return 1;
    }
    return 0;
}
void func_1510E950(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, s32, s32, f32, f32, s32);
extern f32 D_800A2D50;
extern f32 D_800A2D54;
extern f32 D_800A2D58;
extern f32 D_800A2D5C;

void func_1510E7A4(
    s32 arg0,
    s32 arg1,
    s32 arg2,
    s32 arg3,
    s32 arg4,
    s32 arg5,
    f32 arg6,
    f32 arg7,
    f32 arg8,
    f32 arg9,
    u16 arg10,
    s32 arg11,
    f32 arg12,
    f32 arg13
) {
    func_1510E950(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg8, arg9, (s32)arg10, arg11, arg12, arg13, 0);
}
void func_1510E82C(
    s32 arg0,
    s32 arg1,
    s32 arg2,
    s32 arg3,
    s32 arg4,
    s32 arg5,
    f32 arg6,
    f32 arg7,
    f32 arg8,
    f32 arg9,
    u16 arg10,
    s32 arg11
) {
    func_1510E950(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7,
                  arg8, arg9, (s32)arg10, arg11, D_800A2D50, D_800A2D54, 0);
}
void func_1510E8BC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    func_1510E950(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9,
                  (s32)arg10, arg11, D_800A2D58, D_800A2D5C, arg14);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510E950.s")
s32 func_150A43E0(s32, s32, s32, void *);
void func_150A44F0(s32, void *, s32);
void func_150A64C8(s16, s16, void *, s32);
void func_1510F800(s32);
extern f32 D_800A2D98;
extern u8 D_800D3830;
extern s32 D_800D3300;

f32 func_1510F648(f32 arg0, f32 arg1, f32 arg2) {
    f32 result;
    s32 output;
    s32 found;

    func_1510F800(2);
    func_150A64C8((s32)arg0, (s32)arg2, &output, (s32)arg1);
    func_150A44F0(output, &D_800D3830, 0);
    found = func_150A43E0((s32)arg0, (s32)arg2, output, &D_800D3830);
    if (found != 0) {
        result = (f32)D_800D3300 * 0.00390625f;
    } else {
        result = D_800A2D98;
    }
    return result;
}
typedef struct Game13BB20Node {
    u8 pad0[4];
    s16 sibling_offset_4;
    u16 size_6;
    s16 x_8;
    s16 y_A;
    s16 child_offset_C;
} Game13BB20Node;

extern Game13BB20Node *D_800DBE48;

#define GAME13BB20_ABS(x) ((x) < 0 ? -(x) : (x))
s32 func_1510F720(s32 arg0, s32 arg1, s32 arg2, void **arg3) {
    s32 d;
    s32 r;
    s32 next;
    s32 count;
    Game13BB20Node *node;

    node = D_800DBE48;
    count = 0;
    while (node != NULL) {
        d = GAME13BB20_ABS(node->x_8 - arg0);
        r = arg2;
        r += node->size_6;
        if (d < r && GAME13BB20_ABS(node->y_A - arg1) < r) {
            if (node->child_offset_C != 0) {
                next = node->child_offset_C;
            } else {
                *arg3++ = node;
                count++;
                next = node->sibling_offset_4;
            }
        } else {
            next = node->sibling_offset_4;
        }
        if (next != 0) {
            node = (Game13BB20Node *)((u8 *)node + next);
        } else {
            node = NULL;
        }
    }
    return count;
}
void func_150A49F4(s32);

void func_1510F800(s32 arg0) {
    func_150A49F4(arg0);
}
void func_1510E388(void *, void *, f32 *, f32 *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern f32 D_800A2D9C;

void func_1510F820(void *arg0, void *arg1, f32 *arg2, f32 *arg3, s32 arg4,
                   f32 *arg5, f32 *arg6) {
    f32 sp24;
    f32 sp20;
    f32 length;
    f32 zero;

    zero = 0.0f;
    func_1510E388(arg0, arg1, &sp24, &sp20);
    length = sqrtf((sp24 * sp24) + (sp20 * sp20));
    *arg5 = sp24;
    *arg6 = sp20;
    length = length * D_800A2D9C;
    if (zero == length) {
        *arg2 = 1.0f;
        *arg3 = zero;
        return;
    }
    *arg2 = sp24 / length;
    *arg3 = sp20 / length;
}
s32 func_1510F8CC(s32 arg0) {
    return arg0 & 0x1F;
}
s32 func_150A3A70(s32, s32);                        /* extern */
extern s32 D_800D3300;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510F8D8 CURRENT (1955) */
s32 func_1510F8D8(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    s32 temp_t8;
    s32 temp_v0;
    s32 var_a0;
    s32 var_v1;
    u8 *var_v0;

    func_1510F800();
    temp_v0 = func_150A3A70(arg0, arg2);
    if (temp_v0 == 0) {
        return -0x2710;
    }
    var_a0 = 0;
    temp_t8 = (temp_v0 - 1) & 3;
    temp_fa1 = (f32) arg1;
    var_v1 = 1;
    var_fv1 = temp_fa1 - ((f32) D_800D3300 * 0.00390625f);
    if (temp_v0 >= 2) {
        if (temp_t8 != 0) {
            do {
                if (((var_fv1 >= 0.0f) && (var_fv0 = temp_fa1 - ((f32) *(s32 *)((u8 *)&D_800D3300 + (var_v1 * 0x10)) * 0.00390625f), (var_fv0 < var_fv1)) && (var_fv0 >= 0.0f)) || ((var_fv1 < 0.0f) && (var_fv0 = temp_fa1 - ((f32) *(s32 *)((u8 *)&D_800D3300 + (var_v1 * 0x10)) * 0.00390625f), (var_fv1 < var_fv0)))) {
                    var_fv1 = var_fv0;
                    var_a0 = var_v1;
                }
                var_v1 += 1;
            } while ((temp_t8 + 1) != var_v1);
            if (var_v1 != temp_v0) {
                goto block_13;
            }
        } else {
block_13:
            var_v0 = (u8 *)&D_800D3300 + (var_v1 * 0x10);
            do {
                if (((var_fv1 >= 0.0f) && (var_fv0_2 = temp_fa1 - ((f32) *(s32 *)((u8 *)var_v0 + 0) * 0.00390625f), (var_fv0_2 < var_fv1)) && (var_fv0_2 >= 0.0f)) || ((var_fv1 < 0.0f) && (var_fv0_2 = temp_fa1 - ((f32) *(s32 *)((u8 *)var_v0 + 0) * 0.00390625f), (var_fv1 < var_fv0_2)))) {
                    var_fv1 = var_fv0_2;
                    var_a0 = var_v1;
                }
                temp_fv0 = temp_fa1 - ((f32) *(s32 *)((u8 *)var_v0 + 0x10) * 0.00390625f);
                if (((var_fv1 >= 0.0f) && (temp_fv0 < var_fv1) && (temp_fv0 >= 0.0f)) || ((var_fv1 < 0.0f) && (var_fv1 < temp_fv0))) {
                    var_fv1 = temp_fv0;
                    var_a0 = var_v1 + 1;
                }
                temp_fv0_2 = temp_fa1 - ((f32) *(s32 *)((u8 *)var_v0 + 0x20) * 0.00390625f);
                if (((var_fv1 >= 0.0f) && (temp_fv0_2 < var_fv1) && (temp_fv0_2 >= 0.0f)) || ((var_fv1 < 0.0f) && (var_fv1 < temp_fv0_2))) {
                    var_fv1 = temp_fv0_2;
                    var_a0 = var_v1 + 2;
                }
                temp_fv0_3 = temp_fa1 - ((f32) *(s32 *)((u8 *)var_v0 + 0x30) * 0.00390625f);
                if (((var_fv1 >= 0.0f) && (temp_fv0_3 < var_fv1) && (temp_fv0_3 >= 0.0f)) || ((var_fv1 < 0.0f) && (var_fv1 < temp_fv0_3))) {
                    var_fv1 = temp_fv0_3;
                    var_a0 = var_v1 + 3;
                }
                var_v1 += 4;
                var_v0 += 0x40;
            } while (var_v1 != temp_v0);
        }
    }
    if (arg3 != 0) {
        *arg3 = *(s32 *)(((u8 *)&D_800D3300 + (var_a0 * 0x10)) + 4);
    }
    return (s32) ((f32) *(s32 *)((u8 *)&D_800D3300 + (var_a0 * 0x10)) * 0.00390625f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510F8D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510F8D8.s")

Game13BB20Node *func_1510FD20(s32, s32);
s32 func_1510FE30(Game13BB20Node *);
void func_150A6760(s32);
void func_150F33F8(s32);
extern s32 D_800BE9F0;
extern s32 D_800DBDC0;
extern s32 D_800DBDC4;
extern Game13BB20Node *D_800DBDC8;
extern f32 D_800DBDCC;
extern f32 D_800DBDD0;
extern s16 D_800DBE30[];
extern u8 *D_800DBFF0;

void func_1510FC34(s32 arg0) {
    Game13BB20Node *node;
    u8 *state;
    s32 x;
    s32 z;
    s32 index;

    D_800DBDC0 = arg0;
    x = arg0 * 0x9A0;
    state = D_800DBFF0 + x;
    x = (s32)*(f32 *)(state + 0x2F8);
    z = (s32)*(f32 *)(state + 0x300);
    D_800DBDCC = (f32)x;
    D_800DBDD0 = (f32)z;
    node = func_1510FD20(x, z);
    D_800DBDC8 = node;
    index = func_1510FE30(node);
    D_800DBDC4 = index;
    if (index != D_800DBE30[arg0]) {
        D_800DBE30[arg0] = index;
        func_150A6760(arg0);
    }
    if (D_800BE9F0 == 0x3C) {
        func_150F33F8(arg0);
    }
}
Game13BB20Node *func_1510FD20(s32 arg0, s32 arg1) {
    Game13BB20Node *node;
    s32 off;

    node = D_800DBE48;
    while (node != NULL) {
        off = node->child_offset_C;
        if (off != 0) {
            if (GAME13BB20_ABS(arg0 - node->x_8) <= node->size_6 &&
                GAME13BB20_ABS(arg1 - node->y_A) <= node->size_6) {
                node = (Game13BB20Node *)((u8 *)node + off);
                continue;
            }
            off = node->sibling_offset_4;
            if (off != 0) {
                node = (Game13BB20Node *)((u8 *)node + off);
            } else {
                node = NULL;
            }
        } else {
            if (GAME13BB20_ABS(arg0 - node->x_8) <= node->size_6 &&
                GAME13BB20_ABS(arg1 - node->y_A) <= node->size_6) {
                return node;
            }
            off = node->sibling_offset_4;
            if (off != 0) {
                node = (Game13BB20Node *)((u8 *)node + off);
            } else {
                node = NULL;
            }
        }
    }
    return NULL;
}
s32 func_1510FE30(Game13BB20Node *arg0) {
    s16 offset;
    s32 index;
    Game13BB20Node *node;

    node = D_800DBE48;
    index = 0;
    while (node != 0) {
        if (node == arg0) {
            return index;
        }
        offset = node->child_offset_C;
        if (offset != 0) {
            node = (Game13BB20Node *)((u8 *)node + offset);
        } else {
            offset = node->sibling_offset_4;
            node = (Game13BB20Node *)((u8 *)node + offset);
            if (offset != 0) {
                index++;
            } else {
                node = 0;
            }
        }
    }
    return 0;
}
