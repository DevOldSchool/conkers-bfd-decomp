#include "types.h"

/*
 * Reviewed source unit: src/game/game_13F9D0.c
 * Boundary evidence: docs/evidence/game_raw_complete_code_selected_segments.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15112520
 * - func_15112A80
 * - func_15113180
 * - func_15113218
 * - func_151135C4
 * - func_151137D4
 * - func_15113C88
 * - func_15113E54
 * - func_151140C4
 * - func_15114188
 * - func_15114348
 * - func_1511473C
 * - func_151149AC
 * - func_15114A1C
 * - func_15114B94
 * - func_15114D24
 * - func_15114F44
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15112520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15112A80.s")
extern s32 D_800DBEF0;
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15113180 CURRENT (215) */
void func_15113180(void) {
    s32 var_v0;
    s32 var_v1;
    u8 temp_a1;
    void *temp_a0;
    void *temp_a0_2;

    var_v0 = 0;
    var_v1 = 0;
    if (D_800DBEF0 > 0) {
        do {
            temp_a0 = D_800DBEF4 + var_v1;
            *(u8 *)((u8 *)temp_a0 + 0x6F) = (u8) (*(u8 *)((u8 *)temp_a0 + 0x6F) & ~0x40);
            temp_a0_2 = D_800DBEF4 + var_v1;
            temp_a1 = *(u8 *)((u8 *)temp_a0_2 + 0x6F);
            if (((temp_a1 & 0xF) || ((*(u8 *)((u8 *)temp_a0_2 + 0x70) & 4) == 4)) && (*(s32 *)((u8 *)temp_a0_2 + 0x38) != 0)) {
                *(u8 *)((u8 *)temp_a0_2 + 0x6F) = (u8) (temp_a1 | 0x40);
            }
            var_v0 += 1;
            var_v1 += 0xA0;
        } while (var_v0 < D_800DBEF0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15113180 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113180.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113218.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151135C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151137D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113C88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113E54.s")

typedef struct Game13F9D0Entry {
    u8 pad0[0x4F];
    u8 flags;
    u8 pad50[0x50];
} Game13F9D0Entry;

extern u32 *D_800DBF94;

s32 func_15114050(Game13F9D0Entry *arg0, s32 arg1) {
    if (arg0->flags & 0x80) {
        if (arg1 == -1) {
            return 1;
        }
        if (D_800DBF94[arg0 - (Game13F9D0Entry *)D_800DBEF4] &
            (1 << arg1)) {
            return 1;
        }
    }
    return 0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151140C4 CURRENT (305) */
s32 func_151140C4(u8 *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 var_v1;
    u32 temp_v0;

    var_v1 = 0;
    if (*(u8 *)((u8 *)arg0 + 0x4F) & 0x80) {
        temp_v0 = D_800DBF94[(s32) (arg0 - D_800DBEF4) / 160];
loop_2:
        temp_a0_3 = var_v1 + 1;
        if (temp_v0 & (1 << var_v1)) {
            return var_v1;
        }
        if (temp_v0 & (1 << temp_a0_3)) {
            return temp_a0_3;
        }
        temp_a0_2 = var_v1 + 2;
        if (temp_v0 & (1 << temp_a0_2)) {
            return temp_a0_2;
        }
        temp_a0 = var_v1 + 3;
        var_v1 += 4;
        if (temp_v0 & (1 << temp_a0)) {
            return temp_a0;
        }
        if (var_v1 == 0x20) {
            /* Duplicate return node #11. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_2;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151140C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151140C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114188.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114348.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_1511473C.s")
typedef struct {
    u8 transform[0x30];
    f32 position_x;
    f32 position_y;
    f32 position_z;
    u8 pad_3C[4];
} Game13F9D0Transform;

typedef struct {
    f32 field_0;
    f32 field_4;
    f32 field_8;
} Game13F9D0TransformArgs;

typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s32 field_24;
    s32 field_28;
    s32 field_2C;
    s32 field_30;
    s32 field_34;
    u32 field_38;
    f32 field_3C;
} Game13F9D0Matrix;

typedef struct {
    u8 pad_0[0x10];
    s16 field_10;
    s16 field_12;
    s16 field_14;
    u8 pad_16[2];
    f32 field_18;
    u8 pad_1C[0x10];
    s32 field_2C;
    s32 field_30;
    s32 field_34;
} Game13F9D0MotionArgs;

void func_150A7A48(void *, void *, void *);
void func_150A8050(void *, f32, f32, f32);

void func_151148A8(Game13F9D0Transform *arg0, Game13F9D0TransformArgs *arg1) {
    Game13F9D0Transform sp18;

    func_150A8050(arg0, 0.0f, arg1->field_4, 0.0f);
    func_150A8050(&sp18, arg1->field_0, 0.0f, arg1->field_8);
    func_150A7A48(&sp18, arg0, arg0);
}
void func_150A7CB0(Game13F9D0Matrix *, s32, s32, s32);

void func_1511490C(Game13F9D0Transform *arg0,
                   Game13F9D0MotionArgs *arg1) {
    Game13F9D0Matrix sp20;

    func_151148A8(arg0, (Game13F9D0TransformArgs *)arg1);
    arg0->position_x = (f32)arg1->field_10;
    arg0->position_y = (f32)arg1->field_12 + arg1->field_18;
    arg0->position_z = (f32)arg1->field_14;
    func_150A7CB0(&sp20, arg1->field_2C, arg1->field_30, arg1->field_34);
    func_150A7A48(&sp20, arg0, arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151149AC CURRENT (410) */
s32 func_151149AC(s32 arg0) {
    s32 temp_t6;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;

    temp_t6 = arg0 & 0xFF;
    if (temp_t6 == 0) {
        return 0;
    }
    var_v1 = 0;
    if (D_800DBEF0 > 0) {
        var_a2 = 0;
        var_a3 = D_800DBEF4;
loop_4:
        var_v1 += 1;
        var_a3 += 0xA0;
        if (temp_t6 == *(u8 *)((u8 *)var_a3 + 0x72)) {
            return var_a2 + D_800DBEF4;
        }
        var_a2 += 0xA0;
        if (var_v1 >= D_800DBEF0) {
            /* Duplicate return node #7. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_4;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151149AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151149AC.s")
/* Call context: func_10004074: unique active project prototype */
void func_10004074(s32);
extern s32 D_800DBEF8;
extern s32 D_800DBEFC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15114A1C CURRENT (2263) */
void func_15114A1C(void) {
    s32 temp_a1;
    s32 temp_s1;
    s32 var_a0;
    s32 var_s0;
    s32 var_s4;
    u8 *temp_v0_2;
    u8 temp_v1;
    u8 *temp_v0;

    var_a0 = D_800DBEF0;
    var_s0 = 0;
    var_s4 = 0;
    if (var_a0 > 0) {
        do {
            temp_v0 = (void *)(D_800DBEF4 + var_s4);
            if ((*(u8 *)((u8 *)temp_v0 + 0x70) & 1) != 1) {
                temp_s1 = var_s0 * 4;
                temp_a1 = *(u8 *)(D_800DBEF8 + temp_s1);
                if (temp_a1 != 0) {
                    if ((*(u8 *)((u8 *)temp_v0 + 0x4E) != 3) && !(*(u8 *)((u8 *)temp_v0 + 0x6F) & 0x80)) {
                        func_10004074(temp_a1);
                        *(u8 *)(D_800DBEF8 + temp_s1) = 0;
                    } else {
                        temp_v0_2 = (void *)(D_800DBEFC + var_s0);
                        temp_v1 = *temp_v0_2;
                        if (temp_v1 != 0) {
                            *temp_v0_2 = temp_v1 - 1;
                        } else {
                            func_10004074(temp_a1);
                            *(u8 *)(D_800DBEF8 + temp_s1) = 0;
                        }
                    }
                    goto block_12;
                }
            } else if (!(*(u8 *)((u8 *)temp_v0 + 0x6F) & 0x80)) {
                *(u8 *)(D_800DBEF8 + (var_s0 * 4)) = 0;
block_12:
                var_a0 = D_800DBEF0;
            }
            var_s0 += 1;
            var_s4 += 0xA0;
        } while (var_s0 < var_a0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15114A1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114A1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114B94.s")
s32 func_15114CC4(void *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x18);
    if ((temp_v1 != 0) && ((*arg2 != 0) || (*(s32 *)((u8 *)arg0 + 0x1C) == 0))) {
        *(s32 *)((u8 *)arg0 + 0x1C) = 1;
        *(s16 *)((u8 *)arg0 + 2) = (s16) *(s16 *)((u8 *)temp_v1 + 0x10);
        *(s16 *)((u8 *)arg0 + 4) = (s16) *(s16 *)((u8 *)temp_v1 + 0x12);
        *(s16 *)((u8 *)arg0 + 6) = (s16) *(s16 *)((u8 *)temp_v1 + 0x14);
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114D24.s")
extern s32 func_1001001C(s32 (*arg0)(void *, s32, s32 *, s32), s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15114F04(s32 arg0, s32 arg1, s32 arg2) {
    func_1001001C(func_15114CC4, arg0, 0, arg1, arg2);
}
/* Call context: func_150AD770: unique active project prototype */
void func_150AD770(void);
extern s32 D_8003C8E0;
extern s32 D_800BE9F0;
extern void *D_800DBDD8;
extern s32 D_800DBE18;
extern s32 D_800DBE20;
extern s32 D_800DBF9C;
extern s32 D_800DBFA0;
extern s32 D_800DBFA4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15114F44 CURRENT (750) */
void func_15114F44(s32 arg0, s32 arg1, s32 arg2) {
    s32 *var_s4;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_s1;
    void **var_s7;
    u8 *var_s0;

    var_s7 = &D_800DBDD8;
    if ((D_800BE9F0 == 0x12) || (D_800BE9F0 == 0x36) || (D_800BE9F0 == 0x13)) {
        var_s4 = &D_800DBE18;
        do {
            var_s1 = 0;
            var_s0 = *var_s7;
            if (*var_s4 > 0) {
                do {
                    temp_v0 = *(s32 *)((u8 *)var_s0 + 0);
                    if (((temp_v0 & 0xF0000000) != 0x80000000) || (temp_v1 = *(s32 *)((u8 *)var_s0 + 4), ((temp_v1 & 0xF0000000) != 0x80000000)) || (temp_a0 = *(s32 *)((u8 *)var_s0 + 8), ((temp_a0 & 0xF0000000) != 0x80000000)) || (temp_v0 & 3) || (temp_v1 & 3) || (temp_a0 & 3)) {
                        D_8003C8E0 = 0x0C00005A;
                        func_150AD770();
                    }
                    var_s1 += 1;
                    var_s0 += 0xC;
                } while (var_s1 < *var_s4);
            }
            var_s4 += 4;
            var_s7 += 4;
        } while (var_s4 != &D_800DBE20);
        D_800DBF9C = arg0;
        D_800DBFA0 = arg1;
        D_800DBFA4 = arg2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15114F44 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114F44.s")
