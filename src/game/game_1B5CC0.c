#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B5CC0.c
 * Boundary evidence: docs/evidence/game_raw_child_chain_render_lists.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15188810
 * - func_1518894C
 * - func_15188A58
 * - func_15188B74
 * - func_15188D00
 * - func_15188E48
 * - func_15188F84
 * - func_15189118
 * - func_151895F4
 * - func_151897A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1502DB20(s32);
extern void *D_800DF7C8;
void *func_10003C40(s32, s32, s32, s32);
void func_10004074(s32);
void func_100226F0(void *, s32);
void func_15188A58(void *, void **);
void func_10023A10(void *, void *, s32);
extern void *D_800DF7CC;
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15188810 CURRENT (1442) */
void func_15188810(void *arg0, s32 arg1, s32 arg2) {
    s32 sp20;
    s32 temp_t0;
    s32 temp_t8;
    s32 temp_v0_2;
    void *temp_v0;
    void *temp_v0_3;
    u8 *var_s0;

    var_s0 = D_800DF7C8;
    temp_t8 = arg1;
    if (var_s0 != 0) {
        do {
            if (arg0 == *(void **)(var_s0 + 0x10)) {
                if (*(s16 *)(var_s0 + 6) < temp_t8) {
                    *(s16 *)(var_s0 + 6) = (s16)temp_t8;
                }
                *(s8 *)(var_s0 + 4) = (s8)arg2;
                return;
            }
            var_s0 = *(u8 **)(var_s0 + 0xC);
        } while (var_s0 != 0);
    }

    temp_v0 = func_10003C40(0x18, 1, 0, 0);
    if (temp_v0 != 0) {
        temp_v0_2 = func_1502DB20(*(u8 *)((u8 *)arg0 + 4));
        if (temp_v0_2 == 0) {
            func_10004074((s32)temp_v0);
            return;
        }
        temp_t0 = temp_v0_2 * 0x180;
        sp20 = temp_t0;
        temp_v0_3 = func_10003C40(temp_t0, 1, 1, 1);
        if (temp_v0_3 == 0) {
            func_10004074((s32)temp_v0);
            return;
        }
        *(u8 *)temp_v0 = 0;
        *((u8 *)temp_v0 + 1) = 3;
        *((u8 *)temp_v0 + 2) = 0;
        *((u8 *)temp_v0 + 3) = 0x14;
        *((s8 *)temp_v0 + 4) = (s8)arg2;
        *(s16 *)((u8 *)temp_v0 + 6) = (s16)arg1;
        *(void **)((u8 *)temp_v0 + 8) = temp_v0_3;
        *(void **)((u8 *)temp_v0 + 0x10) = arg0;
        *(s32 *)((u8 *)temp_v0 + 0x14) = 0;
        func_100226F0(temp_v0_3, sp20);
        func_15188A58(temp_v0, &D_800DF7C8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15188810 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188810.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518894C CURRENT (855) */
void func_1518894C(s32 arg0, volatile s32 arg1, s32 arg2) {
    void *temp_v0;
    void *temp_v0_2;
    u8 *var_s0;

    var_s0 = D_800DF7CC;
    if (var_s0 != 0) {
        do {
            if (arg0 == *(s32 *)(var_s0 + 0x10)) {
                if (*(s16 *)(var_s0 + 6) < arg1) {
                    *(s16 *)(var_s0 + 6) = arg1;
                }
                *(s8 *)(var_s0 + 4) = arg2;
                return;
            }
            var_s0 = *(u8 **)(var_s0 + 0xC);
        } while (var_s0 != 0);
    }
    temp_v0 = func_10003C40(0x14, 1, 0, 0);
    if (temp_v0 != 0) {
        temp_v0_2 = func_10003C40(0x180, 1, 1, 0);
        if (temp_v0_2 == 0) {
            func_10004074((s32)temp_v0);
            return;
        }
        *(s8 *)temp_v0 = 1;
        *(s8 *)((u8 *)temp_v0 + 1) = 3;
        *(s8 *)((u8 *)temp_v0 + 2) = 0;
        *(s8 *)((u8 *)temp_v0 + 3) = 0x14;
        *(s8 *)((u8 *)temp_v0 + 4) = arg2;
        *(void **)((u8 *)temp_v0 + 8) = temp_v0_2;
        *(s32 *)((u8 *)temp_v0 + 0x10) = arg0;
        *(s16 *)((u8 *)temp_v0 + 6) = arg1;
        func_100226F0(temp_v0_2, 0x180);
        func_15188A58(temp_v0, &D_800DF7CC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518894C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_1518894C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15188A58 CURRENT (55) */
void func_15188A58(void *arg0, void **arg1) {
    void *temp_v0;
    void *var_a1;
    void *var_v1;

    *(s32 *)((u8 *)arg0 + 0xC) = 0;
    temp_v0 = *arg1;
    if (temp_v0 != 0) {
        var_a1 = *(void **)((u8 *)temp_v0 + 0xC);
        var_v1 = temp_v0;
        if (var_a1 != 0) {
            do {
                var_v1 = var_a1;
                var_a1 = *(void **)((u8 *)var_a1 + 0xC);
            } while (var_a1 != 0);
        }
        *(void **)((u8 *)var_v1 + 0xC) = arg0;
        return;
    }
    *arg1 = arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15188A58 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188A58.s")
extern void *D_800DF7C8;

void func_15188A9C(s32 arg0) {
    void *var_v0;

    var_v0 = D_800DF7C8;
    if (var_v0 != 0) {
        do {
            if (arg0 == *(s32 *)((u8 *)var_v0 + 0x10)) {
                *(s16 *)((u8 *)var_v0 + 6) = 0;
            }
            var_v0 = *(void **)((u8 *)var_v0 + 0xC);
        } while (var_v0 != 0);
    }
}
typedef struct Game1B5CC0Node {
    u8 pad0[8];
    s32 resource;
    struct Game1B5CC0Node *next;
    s32 key;
} Game1B5CC0Node;

void func_10004074(s32);
void func_100043B4();

void func_15188AD0(s32 arg0) {
    Game1B5CC0Node *temp_s0;
    Game1B5CC0Node *var_s1;
    Game1B5CC0Node *var_s2;
    s32 var_s3;
    Game1B5CC0Node *var_s4;

    var_s3 = arg0;
    var_s4 = (Game1B5CC0Node *)D_800DF7C8;
    var_s2 = 0;
    var_s1 = var_s4;
    if (var_s1 != 0) {
        do {
            temp_s0 = var_s1->next;
            if (var_s3 == var_s1->key) {
                if (var_s2 == 0) {
                    D_800DF7C8 = temp_s0;
                } else {
                    var_s2->next = temp_s0;
                }
                func_100043B4(var_s1->resource, 2);
                func_10004074((s32)var_s1);
            } else {
                var_s2 = var_s1;
            }
            var_s1 = temp_s0;
        } while (temp_s0 != 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188B74.s")
extern u8 D_80089470[];
extern void *(*D_8008D590[])(void *, void *, s16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15188D00 CURRENT (4845) */
void *func_15188D00(void *arg0, s32 arg1, s16 arg2) {
    u32 *display;
    u32 *command;
    u8 *node;
    void *(*callback)(void *, void *, s16);

    display = arg0;
    node = ((void **)&D_800DF7C8)[arg1];
    if (node == 0) {
        return display;
    }
    command = display;
    command[1] = (u32)D_80089470;
    display += 2;
    command[0] = 0xDA380003;
    command = display;
    command[0] = 0xD9FFFFFF;
    command[1] = 0x200004;
    display += 2;
    command = display;
    command[0] = 0xD9EEFFFF;
    command[1] = 0;
    display += 2;
    command = display;
    command[0] = 0xE7000000;
    command[1] = 0;
    display += 2;
    command = display;
    command[0] = 0xE2001E01;
    command[1] = 0;
    display += 2;
    command = display;
    command[1] = 0xFF;
    command[0] = 0xEC000000;
    display += 2;
    do {
        callback = D_8008D590[*node];
        display = callback(display, node, arg2);
        node = *(u8 **)(node + 0xC);
    } while (node != 0);
    return display;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15188D00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188D00.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15188E48 CURRENT (3061) */
void func_15188E48(void *arg0) {
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_v0;
    s32 var_a2;
    s32 var_a3;
    s32 var_s1;
    s32 var_v1;
    u8 temp_s3;
    u8 temp_v0_2;
    void *temp_a1;
    void *var_a0;
    u8 *base;

    base = arg0;
    temp_s3 = base[1];
    temp_v0 = func_1502DB20((s32)(*(u8 **)(base + 0x10))[4]);
    temp_lo = temp_v0 * temp_s3;
    temp_s0 = temp_v0;
    var_a3 = 0;
    var_s1 = 1;
    temp_s4 = D_800BE9C0 * temp_lo;
    temp_s5 = (D_800BE9C0 ^ 1) * temp_lo;
    if ((s32)temp_s3 > 0) {
loop_1:
        if (temp_s3 == var_s1) {
            temp_a1 = *(void **)(*(u8 **)(base + 0x10) + 0x1D4);
            if (temp_a1 == 0) {
                base[2] = 0;
                return;
            }
            var_a0 = temp_a1;
            var_a2 = temp_s0 << 6;
            var_v1 = (var_a3 * temp_s0) + temp_s4;
            goto block_6;
        }
        var_a2 = temp_s0 << 6;
        var_a0 = (u8 *)*(void **)(base + 8) + (((var_s1 * temp_s0) + temp_s5) << 6);
        var_v1 = (var_a3 * temp_s0) + temp_s4;
block_6:
        func_10023A10(var_a0, (u8 *)*(void **)(base + 8) + (var_v1 << 6), var_a2);
        var_a3 = var_s1;
        var_s1 += 1;
        if (var_s1 == temp_s3) {
            goto block_7;
        }
        goto loop_1;
    }
block_7:
    temp_v0_2 = base[2];
    if (base[1] != temp_v0_2) {
        base[2] = temp_v0_2 + 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15188E48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188E48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188F84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15189118.s")
void func_100043B4(s32 arg0, s32 arg1, void *arg2);

void func_151895A4(u8 *arg0) {
    func_100043B4(*(s32 *)(arg0 + 8), 2, arg0);
}
void func_151895CC(u8 *arg0) {
    func_100043B4(*(s32 *)(arg0 + 8), 2, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_151895F4.s")
s32 func_151137D4(s32, void *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151897A4 CURRENT (2440) */
s32 func_151897A4(s32 arg0, u8 *arg1, s16 arg2) {
    struct {
        s32 saved;
        u8 pad48[0x20];
    } sp44;
    s32 temp_v0;
    register s32 var_s0;
    register s32 var_s1;
    register s32 var_s2;
    register s32 var_s4;
    register s32 var_s5;
    u8 temp_a0;
    u8 temp_a3;

    var_s4 = arg0;
    temp_a3 = arg1[2];
    if (temp_a3 == 0) {
        return var_s4;
    }
    temp_a0 = arg1[3];
    var_s1 = temp_a0 * 0x60;
    var_s0 = 0;
    sp44.saved = (*(u8 **)(arg1 + 0x10))[0x8A];
    var_s5 = temp_a3;
    var_s2 = D_800BE9C0 * arg1[1];
    if (temp_a3 > 0) {
        do {
            (*(u8 **)(arg1 + 0x10))[0x8A] = var_s1 >> 8;
            temp_v0 = func_151137D4(
                var_s4, *(void **)(arg1 + 0x10),
                *(s32 *)(arg1 + 8) + (var_s2 << 6), arg2, 0, 0);
            var_s0++;
            var_s1 += temp_a0 << 5;
            var_s2++;
            var_s4 = temp_v0;
        } while (var_s0 != var_s5);
    }
    (*(u8 **)(arg1 + 0x10))[0x8A] = sp44.saved;
    return var_s4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151897A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_151897A4.s")
void func_151898C0(s32 arg0, s32 arg1) {
    void *var_v0;

    var_v0 = D_800DF7C8;
    if (var_v0 != 0) {
loop_1:
        if (arg0 == *(s32 *)((u8 *)var_v0 + 0x10)) {
            *(s32 *)((u8 *)var_v0 + 0x14) = arg1;
            return;
        }
        var_v0 = *(void **)((u8 *)var_v0 + 0xC);
        if (var_v0 == 0) {

        } else {
            goto loop_1;
        }
    }
}
