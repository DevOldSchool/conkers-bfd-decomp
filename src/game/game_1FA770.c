#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FA770.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CD2C0
 * - func_151CD3CC
 * - func_151CD4C0
 * - func_151CD674
 * - func_151CD7BC
 * - func_151CDB94
 * - func_151CDE20
 * - func_151CE47C
 * - func_151CE49C
 * - func_151CE4DC
 * - func_151CE51C
 * - func_151CE634
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_10022EC0(void *, void *, s32);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game1FA770Packet {
    void *field_0;
    s32 field_4;
    s32 field_8;
    s8 field_C;
    u8 padD[3];
} Game1FA770Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CD2C0 CURRENT (324) */
s32 func_151CD2C0(void *arg0, u8 arg1, s32 arg2) {
    Game1FA770Packet packet;
    s32 temp_v0;
    s32 var_v1;

    packet.field_0 = arg0;
    packet.field_8 = 0;
    packet.field_4 = *(s32 *)((u8 *)arg0 + 0x18);
    packet.field_C = (s8) *(s32 *)((u8 *)arg0 + 0x1C);
    temp_v0 = func_15149130(0x12C, -1, -1, -1, 0, 0x1E, 0x10, (s32) arg1, arg2);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0x10);
        var_v1 = temp_v0;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CD2C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD2C0.s")
void func_151CD35C(s32 arg0) {
    s32 sp1C;

    if ((arg0 >= 0) && (arg0 < 4)) {
        sp1C = arg0;
        func_151494E0(&sp1C, 0x17, arg0);
    }
}
void func_151CD394(s32 arg0) {
    s32 sp1C;

    if ((arg0 >= 0) && (arg0 < 4)) {
        sp1C = arg0;
        func_151494E0(&sp1C, 0x18, arg0);
    }
}
typedef struct Game1FA770DispatchState {
    void *object;
    s32 id;
    void *handle;
    u8 field_C;
} Game1FA770DispatchState;

typedef struct Game1FA770DispatchOwner {
    u8 pad0;
    u8 field_1;
    u8 pad2[0xA];
    u8 field_C;
    u8 padD[0x1B];
    Game1FA770DispatchState state;
} Game1FA770DispatchOwner;

s32 func_151CD4C0(void *, u8, s32, u8, s32);
typedef struct Game1FA770Object Game1FA770Object;
void func_151CE47C(Game1FA770Object *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CD3CC CURRENT (458) */
void func_151CD3CC(Game1FA770DispatchOwner *arg0, s32 *arg1, u8 arg2) {
    Game1FA770DispatchState *state;
    s32 temp_a2;

    if (arg2 == 0x17) {
        state = &arg0->state;
        temp_a2 = state->id;
        if ((temp_a2 == *arg1) && (state->handle == 0)) {
            state->handle = (void *)func_151CD4C0(
                state->object, state->field_C, temp_a2, arg0->field_C,
                arg0->field_1);
            *(s8 *)((u8 *)state->object + 0x14) = 0;
        }
    } else {
        state = &arg0->state;
        if (arg2 == 0x18) {
            if ((state->id == *arg1) && (state->handle != 0)) {
                func_151CE47C(state->handle);
            }
        } else if ((arg2 == 0x23) && (state->id == *arg1)) {
            state->handle = 0;
            *(s8 *)((u8 *)state->object + 0x14) = 1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CD3CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD3CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD4C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD674.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_150ADA68();                                /* extern */
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800AAFC8;
extern f32 D_800AAFCC;
extern f32 D_800AAFD0;
extern f32 D_800AAFD4;
extern f32 D_800AAFD8;
extern f32 D_800AAFDC;
extern f32 D_800AAFE0;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CD7BC CURRENT (8548) */
s32 func_151CD7BC(u8 *arg0) {
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA0;
    f32 sp9C;
    f32 sp90;
    f32 sp84;
    u8 *sp6C;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_ft2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    s32 temp_s3;
    s8 temp_v1;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_s1 = (void *)(*(void **)((u8 *)arg0 + 0x98));
    temp_s3 = *(s32 *)((u8 *)arg0 + 0x94);
    *(f32 *)((u8 *)temp_s1 + 8) = (f32) (*(f32 *)((u8 *)temp_s1 + 8) + (*(f32 *)((u8 *)temp_s1 + 0x10) * D_800BE9A4));
    *(f32 *)((u8 *)temp_s1 + 0xC) = (f32) (*(f32 *)((u8 *)temp_s1 + 0xC) + (*(f32 *)((u8 *)temp_s1 + 0x14) * D_800BE9A4));
    *(f32 *)((u8 *)temp_s1 + 8) = func_15144B68(*(f32 *)((u8 *)temp_s1 + 8));
    *(f32 *)((u8 *)temp_s1 + 0xC) = func_15144B68(*(f32 *)((u8 *)temp_s1 + 0xC));
    *(f32 *)((u8 *)temp_s1 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_s1 + 0x2C) + (*(f32 *)((u8 *)temp_s1 + 0x30) * D_800BE9A4));
    *(f32 *)((u8 *)temp_s1 + 0x2C) = func_15144B68(*(f32 *)((u8 *)temp_s1 + 0x2C));
    *(f32 *)((u8 *)temp_s1 + 0x40) = (f32) (*(f32 *)((u8 *)temp_s1 + 0x40) + (D_800AAFC8 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s1 + 0x3C) = (f32) (*(f32 *)((u8 *)temp_s1 + 0x3C) + ((D_800AAFCC + (func_150ADA68() * D_800AAFD0)) * D_800AAFD4 * D_800BE9A4));
    if (*(f32 *)((u8 *)temp_s1 + 0x3C) >= 16384.0f) {
        do {
            *(f32 *)((u8 *)temp_s1 + 0x3C) = (f32) (*(f32 *)((u8 *)temp_s1 + 0x3C) - 16384.0f);
        } while (*(f32 *)((u8 *)temp_s1 + 0x3C) >= 16384.0f);
    }
    temp_fv0 = *(f32 *)((u8 *)temp_s1 + 0x40);
    if (temp_fv0 > 1.0f) {
        temp_fs4 = 1.0f / temp_fv0;
        temp_v0 = (void *)(temp_s1 + 0x18);
        temp_ft4 = *(f32 *)((u8 *)temp_s1 + 0x20) + D_800BE9A4;
        spAC = -(temp_ft4 * temp_fs4);
        *(f32 *)((u8 *)&sp9C + 0) = *(f32 *)((u8 *)temp_s1 + 0x18);
        *(s32 *)((u8 *)&sp9C + 4) = (s32) *(s32 *)((u8 *)temp_v0 + 4);
        spB0 = temp_ft4;
        sp6C = temp_v0;
        temp_fs5 = ((func_15047D60(*(f32 *)((u8 *)temp_s1 + 8)) * *(f32 *)((u8 *)temp_s1 + 0)) + *(f32 *)((u8 *)arg0 + 0x10)) - *(f32 *)((u8 *)temp_s1 + 0x18);
        spA8 = ((func_15047D60(*(f32 *)((u8 *)temp_s1 + 0xC)) * *(f32 *)((u8 *)temp_s1 + 4)) + *(f32 *)((u8 *)arg0 + 0x18)) - *(f32 *)((u8 *)temp_s1 + 0x1C);
        var_fa0 = *(f32 *)((u8 *)temp_s1 + 0x34);
        var_ft4 = temp_ft4;
        temp_ft2 = ((func_15047D60(*(f32 *)((u8 *)temp_s1 + 0x2C)) * *(f32 *)((u8 *)temp_s1 + 0x28)) + *(f32 *)((u8 *)temp_s1 + 0x24)) - var_fa0;
        sp90 = temp_ft2;
        var_fa1 = *(f32 *)((u8 *)temp_s1 + 0x3C);
        sp84 = var_fa1 - *(f32 *)((u8 *)temp_s1 + 0x38);
        if (*(f32 *)((u8 *)temp_s1 + 0x40) > 1.0f) {
            do {
                temp_v0_2 = (void *)((*(s8 *)((u8 *)arg0 + 0x2E) * 0x1C) + temp_s3);
                *(f32 *)((u8 *)temp_v0_2 + 0) = sp9C;
                *(f32 *)((u8 *)temp_v0_2 + 4) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
                *(f32 *)((u8 *)temp_v0_2 + 0xC) = (f32) D_800AAFE0;
                *(f32 *)((u8 *)temp_v0_2 + 0x10) = var_fa0;
                *(s16 *)((u8 *)temp_v0_2 + 0x14) = 0xFF;
                *(f32 *)((u8 *)temp_v0_2 + 0x18) = var_fa1;
                *(f32 *)((u8 *)temp_v0_2 + 8) = spA0;
                var_fa0 += temp_ft2 * temp_fs4;
                var_fa1 += sp84 * temp_fs4;
                *(f32 *)((u8 *)temp_v0_2 + 4) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 4) + ((D_800AAFE0 * D_800BE9A4) + (D_800AAFDC * (D_800BE9A4 * D_800BE9A4))));
                *(f32 *)((u8 *)temp_v0_2 + 0xC) = (f32) (D_800AAFE0 + (D_800AAFD8 * D_800BE9A4));
                *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(s8 *)((u8 *)arg0 + 0x2E) + 1);
                if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2E)) {
                    *(s8 *)((u8 *)arg0 + 0x2E) = 0;
                }
                temp_v1 = *(s8 *)((u8 *)arg0 + 0x2D);
                *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) + 1);
                if (temp_v1 == *(s8 *)((u8 *)arg0 + 0x2E)) {
                    *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (temp_v1 + 1);
                    if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2D)) {
                        *(s8 *)((u8 *)arg0 + 0x2D) = 0;
                    }
                    *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) - 1);
                }
                sp9C += temp_fs5 * temp_fs4;
                var_ft4 += spAC;
                spA0 += spA8 * temp_fs4;
                *(f32 *)((u8 *)temp_s1 + 0x40) = (f32) (*(f32 *)((u8 *)temp_s1 + 0x40) - 1.0f);
            } while (*(f32 *)((u8 *)temp_s1 + 0x40) > 1.0f);
        }
        *(f32 *)((u8 *)sp6C + 0) = (f32) *(f32 *)((u8 *)&sp9C + 0);
        *(s32 *)((u8 *)sp6C + 4) = (s32) *(s32 *)((u8 *)&sp9C + 4);
        *(f32 *)((u8 *)temp_s1 + 0x34) = var_fa0;
        *(f32 *)((u8 *)temp_s1 + 0x38) = var_fa1;
        *(f32 *)((u8 *)temp_s1 + 0x20) = var_ft4;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CD7BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD7BC.s")
extern f32 D_800AAFE4;
extern f32 D_800AAFE8;
extern f32 D_800AAFEC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CDB94 CURRENT (7501) */
s32 func_151CDB94(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    s32 temp_v0;
    s32 var_v1;
    s8 temp_a2;
    s8 var_v1_2;
    void *temp_a1;
    void *temp_a2_2;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x94);
    if (*(s8 *)((u8 *)arg0 + 0x2C) <= 0) {

    } else {
        var_v1 = *(s8 *)((u8 *)arg0 + 0x2E) - 1;
        if (var_v1 < 0) {
            var_v1 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
        }
        temp_a2 = *(s8 *)((u8 *)arg0 + 0x2D);
        temp_a1 = (temp_a2 * 0x1C) + temp_v0;
        temp_fv0 = fabsf(*(f32 *)((u8 *)((var_v1 * 0x1C) + temp_v0) + 4) - *(f32 *)((u8 *)temp_a1 + 4));
        if (temp_fv0 == 0.0f) {

        } else {
            temp_fa1 = 1.0f / temp_fv0;
            var_v1_2 = temp_a2;
            do {
                temp_a2_2 = (var_v1_2 * 0x1C) + temp_v0;
                *(s16 *)((u8 *)temp_a2_2 + 0x14) = 0xFF;
                temp_fa0 = *(f32 *)((u8 *)temp_a2_2 + 4) - *(f32 *)((u8 *)temp_a1 + 4);
                if (temp_fa0 < (temp_fv0 * D_800AAFE4)) {
                    *(s16 *)((u8 *)temp_a2_2 + 0x14) = (s16) ((u32) (temp_fa0 * (temp_fa1 * D_800AAFEC) * 255.0f) & 0xFF);
                } else if ((temp_fv0 - (temp_fv0 * D_800AAFE8)) < temp_fa0) {
                    *(s16 *)((u8 *)temp_a2_2 + 0x14) = (s16) ((u32) ((temp_fv0 - temp_fa0) * (temp_fa1 * 10.0f) * 255.0f) & 0xFF);
                }
                var_v1_2 += 1;
                if (var_v1_2 >= (s32) *(u8 *)((u8 *)arg0 + 0x25)) {
                    var_v1_2 = 0;
                }
            } while (var_v1_2 != *(s8 *)((u8 *)arg0 + 0x2E));
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CDB94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CDB94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CDE20.s")
struct Game1FA770Object {
    u8 pad0[0x1E];
    volatile u16 flags;
    u8 pad20[0x10];
    s8 field_30;
};

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CE47C CURRENT (35) */
void func_151CE47C(Game1FA770Object *arg0) {
    u16 flags;

    arg0->field_30 = 0;
    flags = arg0->flags & 0xFFFD;
    arg0->flags = flags;
    arg0->flags = flags | 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CE47C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE47C.s")
extern void func_151478F4(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CE49C CURRENT (120) */
void func_151CE49C(void *arg0, s32 arg1, s32 arg2) {
    s32 sp1C;

    sp1C = *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x98) + 0x48);
    func_151494E0(&sp1C, 0x23, arg2);
    func_151478F4((s32) arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CE49C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE49C.s")
extern void func_15147928(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CE4DC CURRENT (120) */
void func_151CE4DC(void *arg0, s32 arg1, s32 arg2) {
    s32 sp1C;

    sp1C = *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x98) + 0x48);
    func_151494E0(&sp1C, 0x23, arg2);
    func_15147928((s32) arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CE4DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE4DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE51C.s")
extern s32 D_800A5760[];
extern u8 D_800DCE50[];
extern u8 D_800DD190[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CE634 CURRENT (1255) */
void *func_151CE634(s32 arg0) {
    u8 *var_a0;
    void **var_a1;
    s32 temp_t0;
    u8 *temp_t1;
    s32 temp_t4;
    s32 temp_t7;
    s32 temp_t8;
    s32 var_a3;
    s32 var_v0;
    void *var_v1;

    var_a3 = arg0;
    temp_t1 = D_800DD190;
    temp_t0 = 0xB;
    var_v0 = 0;
loop_1:
    temp_t7 = var_v0 << 2;
    temp_t8 = D_800A5760[var_v0];
    var_a0 = D_800DCE50;
    var_a1 = (void **)(var_a0 + (temp_t8 << 2));
loop_2:
    var_v1 = *var_a1;
    if (var_v1 != 0) {
loop_3:
        if ((*(s32 *)((u8 *)var_v1 + 0x20) == temp_t0) &&
            (var_a3 == *(s32 *)(*(u8 **)((u8 *)var_v1 + 0x98) + 0x48))) {
            return var_v1;
        }
        var_v1 = *(void **)((u8 *)var_v1 + 8);
        if (var_v1 != 0) {
            goto loop_3;
        }
    }
    var_a0 += 0x1A0;
    var_a1 += 0x1A0 / sizeof(void *);
    if (var_a0 == temp_t1) {
        temp_t4 = (var_v0 + 1) & 0xFF;
        var_v0 = temp_t4;
        if (var_v0 < 2) {
            goto loop_1;
        }
        return 0;
    }
    goto loop_2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CE634 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE634.s")
