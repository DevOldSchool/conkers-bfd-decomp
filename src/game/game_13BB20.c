#include "types.h"

/*
 * Reviewed source unit: src/game/game_13BB20.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510E670
 * - func_1510E950
 * - func_1510F648
 * - func_1510F720
 * - func_1510F820
 * - func_1510F8D8
 * - func_1510FC34
 * - func_1510FD20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510E670.s")
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
void func_1510F800();
void func_150A64C8(s16, s16, void *, s32);
extern f32 D_800A2D98;
extern u8 D_800D3830;
extern s32 D_800D3300;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510F648 CURRENT (103) */
f32 func_1510F648(f32 arg0, f32 arg1, f32 arg2) {
    s32 sp28;
    s32 sp20;
    s32 sp1C;
    f32 result;
    s32 x;
    s32 z;

    func_1510F800(2);
    x = (s32)arg0;
    z = (s32)arg2;
    sp20 = x;
    sp1C = z;
    func_150A64C8((s16)x, (s16)z, &sp28, (s32)arg1);
    func_150A44F0(sp28, &D_800D3830, 0);
    if (func_150A43E0(sp20, sp1C, sp28, &D_800D3830) != 0) {
        result = (f32)D_800D3300 * 0.00390625f;
    } else {
        result = D_800A2D98;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510F648 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510F648.s")
typedef struct Game13BB20Node {
    u8 pad0[4];
    s16 sibling_offset_4;
    u8 pad6[6];
    s16 child_offset_C;
} Game13BB20Node;

extern Game13BB20Node *D_800DBE48;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510F720 CURRENT (1595) */
s32 func_1510F720(s32 arg0, s32 arg1, s32 arg2, void **arg3) {
    s16 temp_a1_3;
    s16 var_a2_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    void **var_s2;
    u8 *var_v0;

    var_s2 = arg3;
    var_v0 = D_800DBE48;
    var_v1 = 0;
    if (var_v0 != 0) {
        do {
            temp_a1 = *(s16 *)((u8 *)var_v0 + 8) - arg0;
            var_a2 = temp_a1;
            if (temp_a1 < 0) {
                var_a2 = -temp_a1;
            }
            temp_a1_2 = arg2 + *(u16 *)((u8 *)var_v0 + 6);
            if (var_a2 < temp_a1_2) {
                temp_a2 = *(s16 *)((u8 *)var_v0 + 0xA) - arg1;
                var_a3 = temp_a2;
                if (temp_a2 < 0) {
                    var_a3 = -temp_a2;
                }
                if (var_a3 < temp_a1_2) {
                    temp_a1_3 = *(s16 *)((u8 *)var_v0 + 0xC);
                    if (temp_a1_3 != 0) {
                        var_a2_2 = temp_a1_3;
                    } else {
                        *var_s2 = var_v0;
                        var_s2 += 4;
                        var_v1 += 1;
                        goto block_10;
                    }
                } else {
                    goto block_10;
                }
            } else {
block_10:
                var_a2_2 = *(s16 *)((u8 *)var_v0 + 4);
            }
            if (var_a2_2 != 0) {
                var_v0 += var_a2_2;
            } else {
                var_v0 = 0;
            }
        } while (var_v0 != 0);
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510F720 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510F720.s")
void func_1510F800(void) {
    func_150A49F4();
}
void func_1510E388(f32 *, f32 *);
f32 sqrtf(f32);
extern f32 D_800A2D9C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510F820 CURRENT (2483) */
void func_1510F820(f32 *arg2, f32 *arg3, f32 *arg5, f32 *arg6) {
    f32 sp24;
    f32 sp20;
    f32 temp_fv1;

    func_1510E388(&sp24, &sp20);
    *arg5 = sp24;
    *arg6 = sp20;
    temp_fv1 = sqrtf((sp24 * sp24) + (sp20 * sp20)) * D_800A2D9C;
    if (temp_fv1 == 0.0f) {
        *arg2 = 1.0f;
        *arg3 = 0.0f;
        return;
    }
    *arg2 = sp24 / temp_fv1;
    *arg3 = sp20 / temp_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510F820 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510F820.s")
s32 func_1510F8CC(s32 arg0) {
    return arg0 & 0x1F;
}
s32 func_150A3A70(s32, s32);                        /* extern */
extern s32 D_800D3300;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510F8D8 CURRENT (1925) */
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
                if (((var_fv1 >= 0.0f) && (var_fv0 = temp_fa1 - ((f32) *(&D_800D3300 + (var_v1 * 0x10)) * 0.00390625f), (var_fv0 < var_fv1)) && (var_fv0 >= 0.0f)) || ((var_fv1 < 0.0f) && (var_fv0 = temp_fa1 - ((f32) *(&D_800D3300 + (var_v1 * 0x10)) * 0.00390625f), (var_fv1 < var_fv0)))) {
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
            var_v0 = (void *)(&D_800D3300 + (var_v1 * 0x10));
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
        *arg3 = *(s32 *)((u8 *)(&D_800D3300 + (var_a0 * 0x10)) + 4);
    }
    return (s32) ((f32) *(&D_800D3300 + (var_a0 * 0x10)) * 0.00390625f);
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510FC34 CURRENT (80) */
void func_1510FC34(s32 arg0) {
    Game13BB20Node *node;
    u8 *state;
    s32 x;
    s32 z;
    s32 index;

    D_800DBDC0 = arg0;
    state = D_800DBFF0 + (arg0 * 0x9A0);
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
#endif /* CONKER_DEFERRED_CANDIDATE func_1510FC34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510FC34.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510FD20 CURRENT (2625) */
void *func_1510FD20(s32 arg0, s32 arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_a1;
    s32 temp_a1_3;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_t0;
    s32 var_t0_2;
    u16 temp_a1_2;
    u16 temp_a1_4;
    u8 *var_v1;

    var_v1 = D_800DBE48;
    if (var_v1 != 0) {
loop_1:
        temp_v0 = *(s16 *)((u8 *)var_v1 + 0xC);
        if (temp_v0 != 0) {
            temp_a1 = arg0 - *(s16 *)((u8 *)var_v1 + 8);
            var_a2 = temp_a1;
            if (temp_a1 < 0) {
                var_a2 = -temp_a1;
            }
            temp_a1_2 = *(u16 *)((u8 *)var_v1 + 6);
            if ((s32) temp_a1_2 >= var_a2) {
                temp_a2 = arg1 - *(s16 *)((u8 *)var_v1 + 0xA);
                var_t0 = temp_a2;
                if (temp_a2 < 0) {
                    var_t0 = -temp_a2;
                }
                if ((s32) temp_a1_2 >= var_t0) {
                    var_v1 += temp_v0;
                } else {
                    goto block_9;
                }
            } else {
block_9:
                temp_v0_2 = *(s16 *)((u8 *)var_v1 + 4);
                if (temp_v0_2 != 0) {
                    var_v1 += temp_v0_2;
                } else {
                    goto block_21;
                }
            }
            goto block_22;
        }
        temp_a1_3 = arg0 - *(s16 *)((u8 *)var_v1 + 8);
        var_a2_2 = temp_a1_3;
        if (temp_a1_3 < 0) {
            var_a2_2 = -temp_a1_3;
        }
        temp_a1_4 = *(u16 *)((u8 *)var_v1 + 6);
        if ((s32) temp_a1_4 >= var_a2_2) {
            temp_a2_2 = arg1 - *(s16 *)((u8 *)var_v1 + 0xA);
            var_t0_2 = temp_a2_2;
            if (temp_a2_2 < 0) {
                var_t0_2 = -temp_a2_2;
            }
            if ((s32) temp_a1_4 >= var_t0_2) {
                return var_v1;
            }
            goto block_19;
        }
block_19:
        temp_v0_3 = *(s16 *)((u8 *)var_v1 + 4);
        if (temp_v0_3 != 0) {
            var_v1 += temp_v0_3;
        } else {
block_21:
            var_v1 = 0;
        }
block_22:
        if (var_v1 == 0) {
            /* Duplicate return node #23. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510FD20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13BB20/func_1510FD20.s")
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
