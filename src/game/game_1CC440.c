#include "types.h"

/*
 * Reviewed source unit: src/game/game_1CC440.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_attachment_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1519EF90
 * - func_1519F108
 * - func_1519F168
 * - func_1519F1C8
 * - func_1519F400
 * - func_1519F48C
 * - func_1519F4F0
 * - func_1519F7F0
 * - func_1519FE6C
 * - func_151A084C
 * - func_151A0950
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1CC440NodeData {
    s32 field0;
    u8 pad4[4];
    s32 field8;
} Game1CC440NodeData;

typedef struct Game1CC440Node {
    u8 pad0[0x18];
    void *field18;
    u8 field1C;
    u8 pad1D[0x3B];
    Game1CC440NodeData data58;
} Game1CC440Node;

typedef struct Game1CC440State {
    u8 pad0[0x20];
    s32 mode;
    u8 pad24[0x74];
    Game1CC440Node **link98;
} Game1CC440State;

typedef struct Game1CC440Attachments {
    Game1CC440State *field0;
    Game1CC440State *field4;
    Game1CC440State *field8;
    Game1CC440State *fieldC;
} Game1CC440Attachments;

typedef struct Game1CC440AttachmentOwner {
    u8 pad0[0x58];
    Game1CC440Attachments attachments;
} Game1CC440AttachmentOwner;

void func_151478F4(s32);
void func_15147928(s32);

/* Call context: func_151423D8: unique active project prototype */
/* Call context: func_15143E08: unique active project prototype */
f32 func_151423D8(u8);
s32 func_15143E08(u16 *);
extern f32 D_800A8CE0;
extern f32 D_800A8CE4;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519EF90 CURRENT (6001) */
s32 func_1519EF90(u8 *arg0, u8 arg1, u8 *arg2) {
    u16 *sp3C;
    u8 *sp38;
    f32 sp2C;
    f32 sp28;
    u8 sp1F;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_ft4;
    f32 var_ft5;
    u8 *temp_v0;
    f32 var_fv0;
    u16 *temp_a3;
    u8 temp_v0_2;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0));
    sp38 = (void *)(temp_v0 + 0x58);
    temp_a3 = (void *)(*(u16 **)((u8 *)temp_v0 + 0x18));
    if (*(s32 *)((u8 *)temp_a3 + 0x1D4) == 0) {
        return 0;
    }
    var_ft4 = *(f32 *)((u8 *)temp_a3 + 0x14);
    temp_fa0 = var_ft4 - *(f32 *)((u8 *)arg0 + 0x20);
    temp_fa1 = *(f32 *)((u8 *)temp_a3 + 0x1C) - *(f32 *)((u8 *)arg0 + 0x24);
    if ((D_800A8CE0 < fabsf(temp_fa0)) || (D_800A8CE0 < fabsf(temp_fa1))) {
        temp_fv1 = 1.0f / sqrtf((temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
        var_ft5 = temp_fa1 * temp_fv1;
        sp28 = temp_fa0 * temp_fv1;
    } else {
        sp3C = temp_a3;
        temp_v0_2 = func_15143E08(temp_a3);
        sp1F = temp_v0_2;
        sp2C = func_151423D8(temp_v0_2 & 0xFF);
        var_ft5 = sp2C;
        sp28 = func_151423D8((sp1F - 0x40) & 0xFF);
        var_ft4 = *(f32 *)((u8 *)temp_a3 + 0x14);
    }
    if (arg1 == 6) {
        var_fv0 = *(f32 *)((u8 *)sp38 + 0x10);
    } else {
        var_fv0 = -*(f32 *)((u8 *)sp38 + 0x10);
    }
    *(f32 *)((u8 *)arg2 + 0) = (f32) (var_ft4 + (var_fv0 * var_ft5));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)temp_a3 + 0x1C) - (var_fv0 * sp28));
    temp_fv1_2 = *(f32 *)((u8 *)temp_a3 + 0x118);
    if (temp_fv1_2 < D_800A8CE4) {
        *(f32 *)((u8 *)arg2 + 4) = (f32) *(f32 *)((u8 *)temp_a3 + 0x18);
        return 1;
    }
    *(f32 *)((u8 *)arg2 + 4) = temp_fv1_2;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519EF90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519EF90.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519F108 CURRENT (735) */
void func_1519F108(Game1CC440State *arg0) {
    register Game1CC440Node **link = arg0->link98;
    register Game1CC440Node *node = *link;

    if (node != 0) {
        Game1CC440NodeData *data = &node->data58;

        if (arg0->mode == 6) {
            data->field0 = 0;
        }
        if (arg0->mode == 7) {
            data->field8 = 0;
        }
    }
    func_151478F4((s32) arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519F108 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F108.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519F168 CURRENT (735) */
void func_1519F168(Game1CC440State *arg0) {
    register Game1CC440Node **link = arg0->link98;
    register Game1CC440Node *node = *link;

    if (node != 0) {
        Game1CC440NodeData *data = &node->data58;

        if (arg0->mode == 6) {
            data->field0 = 0;
        }
        if (arg0->mode == 7) {
            data->field8 = 0;
        }
    }
    func_15147928((s32) arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519F168 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F168.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F1C8.s")
s32 func_1519F1C8(void *, u8, ...);

void func_1519F3B8(void *arg0) {
    void *temp_v1;

    temp_v1 = (u8 *)arg0 + 0x58;
    *(s32 *)temp_v1 = func_1519F1C8(arg0, 6);
    *(s32 *)((u8 *)temp_v1 + 4) = 0;
    *(s32 *)((u8 *)temp_v1 + 8) = func_1519F1C8(arg0, 7);
    *(s32 *)((u8 *)temp_v1 + 0xC) = 0;
}
void func_1519F48C(Game1CC440State *);
void func_151A0928(void *);
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519F400 CURRENT (40) */
void func_1519F400(void *arg0) {
    Game1CC440State *temp_a0;
    register Game1CC440State *temp_t6;
    register void *temp_s0;

    temp_s0 = (u8 *)arg0 + 0x58;
    temp_t6 = *(Game1CC440State **)temp_s0;
    if (temp_t6 != 0) {
        func_1519F48C(temp_t6);
    }
    temp_a0 = *(Game1CC440State **)((u8 *)temp_s0 + 8);
    if (temp_a0 != 0) {
        func_1519F48C(temp_a0);
    }
    temp_a0 = *(Game1CC440State **)((u8 *)temp_s0 + 4);
    if (temp_a0 != 0) {
        func_151A0928(temp_a0);
        func_1516972C(*(void **)((u8 *)temp_s0 + 4));
    }
    temp_a0 = *(Game1CC440State **)((u8 *)temp_s0 + 0xC);
    if (temp_a0 != 0) {
        func_151A0928(temp_a0);
        func_1516972C(*(void **)((u8 *)temp_s0 + 0xC));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519F400 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F400.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519F48C CURRENT (140) */
void func_1519F48C(u8 *arg0) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x98));
    temp_v1 = (void *)(*(void **)((u8 *)temp_v0 + 0));
    if (temp_v1 != 0) {
        if (*(s32 *)((u8 *)arg0 + 0x20) == 6) {
            *(s32 *)((u8 *)temp_v1 + 0x58) = 0;
        }
        if (*(s32 *)((u8 *)arg0 + 0x20) == 7) {
            *(s32 *)((u8 *)(temp_v1 + 0x58) + 8) = 0;
        }
        *(void **)((u8 *)temp_v0 + 0) = 0;
    }
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    *(u8 *)((u8 *)temp_v0 + 4) = (u8) (*(u8 *)((u8 *)temp_v0 + 4) | 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519F48C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F48C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F4F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F7F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519FE6C.s")
/* Call context: func_151A0928: unique active project prototype */
void func_151A0928(void *);
s32 func_1519F1C8(void *, u8, ...);                 /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A084C CURRENT (1389) */
void func_151A084C(u8 *arg0) {
    void *sp28;
    u8 sp23;
    void *sp18;
    s32 temp_v0_2;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_a1;
    u8 *temp_v0;
    u8 *temp_a2;
    u8 *temp_t0;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x28));
    var_v1 = 0;
    temp_a2 = (void *)(arg0 + 0x28);
    temp_a1 = (void *)(*(void **)((u8 *)temp_v0 + 0x18));
    temp_t0 = (void *)(temp_v0 + 0x58);
    if (*(s32 *)((u8 *)temp_a1 + 0) == 0) {
        var_v1 = 1;
    }
    temp_a0 = (void *)(*(void **)((u8 *)arg0 + 0x28));
    if (*(u8 *)((u8 *)temp_a0 + 0x1C) != *(u8 *)((u8 *)temp_a1 + 0x3B)) {
        var_v1 = 1;
    }
    if ((var_v1 == 0) && (*(s32 *)((u8 *)temp_a1 + 0x1D4) != 0)) {
        sp23 = 1;
        sp28 = temp_t0;
        sp18 = temp_a2;
        temp_v0_2 = func_1519F1C8(temp_a0, *(u8 *)((u8 *)temp_a2 + 4), temp_a2, arg0);
        var_v1 = 1;
        if (*(u8 *)((u8 *)temp_a2 + 4) == 6) {
            *(s32 *)((u8 *)temp_v0 + 0x58) = temp_v0_2;
        } else {
            *(s32 *)((u8 *)temp_t0 + 8) = temp_v0_2;
        }
    }
    if (var_v1 != 0) {
        func_151A0928(arg0);
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        *(u8 *)((u8 *)arg0 + 0xD) = (u8) (*(u8 *)((u8 *)arg0 + 0xD) | 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A084C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A084C.s")
void func_151A0928(void *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(*(s32 *)((u8 *)arg0 + 0x28) + 0x58);
    if (*(u8 *)((u8 *)arg0 + 0x2C) == 6) {
        *(s32 *)((u8 *)temp_v0 + 4) = 0;
        return;
    }
    *(s32 *)((u8 *)temp_v0 + 0xC) = 0;
}
typedef struct {
    void *field0;
    u8 field4;
} Game1CC440Lookup;

void func_1519F48C(Game1CC440State *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A0950 CURRENT (40) */
void func_151A0950(Game1CC440State *arg0, Game1CC440Lookup *arg1, u8 arg2) {
    Game1CC440Node **temp_v1;
    Game1CC440Node *temp_v0;

    temp_v1 = arg0->link98;
    if (arg2 == 0xA) {
        temp_v0 = *temp_v1;
        if ((temp_v0 != 0) &&
            ((arg1->field0 == temp_v0->field18) ||
             (arg1->field4 == temp_v0->field1C))) {
            func_1519F48C(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A0950 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A0950.s")
void func_1516972C(void *);

void func_151A09B4(void *arg0, void *arg1, u8 arg2) {
    void *temp_v0;

    temp_v0 = *(void **)(*(u8 **)((u8 *)arg0 + 0x28) + 0x18);
    if ((arg2 == 0) && ((temp_v0 == *(void **)arg1) ||
        (*(u8 *)((u8 *)temp_v0 + 0x3B) == *(u8 *)((u8 *)arg1 + 4)))) {
        func_151A0928(arg0);
        func_1516972C(arg0);
    }
}
