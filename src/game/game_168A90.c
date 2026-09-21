#include "types.h"

/*
 * Reviewed source unit: src/game/game_168A90.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1513B5E0
 * - func_1513B798
 * - func_1513B83C
 * - func_1513B968
 * - func_1513B9A8
 * - func_1513B9DC
 * - func_1513BAE8
 * - func_1513BBFC
 * - func_1513BEB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B5E0.s")
typedef s32 (*Game168A90Callback)(void *);

extern Game168A90Callback D_80089C18[];
extern s32 D_800BE9E4;
void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513B798 CURRENT (889) */
void func_1513B798(void *arg0) {
    u8 sp1B;
    s8 callback_index;
    u8 callback_pending;

    callback_pending = 0;
    if (*(u8 *)((u8 *)arg0 + 0x10) & 1) {
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) (*(s16 *)((u8 *)arg0 + 0x14) - D_800BE9E4);
        if (*(s16 *)((u8 *)arg0 + 0x14) < 0) {
            callback_pending = 1;
        }
    }
    if (callback_pending == 0) {
        callback_index = *(s8 *)((u8 *)arg0 + 0x11);
        if (callback_index != -1) {
            sp1B = callback_pending;
            if (D_80089C18[(s32) callback_index](arg0) != 0) {
                callback_pending = sp1B;
            } else {
                callback_pending = 1;
            }
        }
    }
    if (callback_pending != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513B798 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B798.s")
typedef struct {
    u8 pad0[0x10];
    u8 flags;
    u8 pad11;
    s8 callback;
    u8 pad13[0x41];
    s32 displayList;
} Game168A90RenderState;

typedef s32 (*Game168A90RenderCallback)(void *, s16, s32, void *);

typedef struct {
    u32 word0;
    u32 word1;
} Game168A90Command;

extern Game168A90RenderCallback D_80089C28[];
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513B83C CURRENT (4000) */
void *func_1513B83C(void *arg0, Game168A90RenderState *arg1, s32 arg2) {
    s32 result;
    Game168A90Command *cursor;
    Game168A90Command *command;

    arg2 = (s16) arg2;
    if ((arg1->flags & 2) && !(*((u8 *) arg1 + 0x49) & (1 << arg2))) {
        return arg0;
    }
    if (arg1->callback != -1) {
        result = D_80089C28[arg1->callback](arg1, arg2, arg2, arg0);
        if (result == 0) {
            return arg0;
        }
    }

    cursor = arg0;
    command = cursor++;
    command->word0 = 0xDA380003;
    command->word1 = (s32) ((u8 *) arg1 + (D_800BE9C0 << 6) + 0x78);
    command = cursor++;
    command->word0 = 0xDB060004;
    command->word1 =
        *(s32 *) ((u8 *) arg1 + (D_800BE9C0 << 4) + (arg2 * 4) + 0x58);
    command = cursor++;
    command->word0 = 0xDE000000;
    command->word1 = arg1->displayList;
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513B83C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B83C.s")
extern void func_150A7B80(s32 arg0, s32 arg1);
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513B968 CURRENT (110) */
s32 func_1513B968(s32 arg0, s32 arg1) {
    s32 temp_a0;

    temp_a0 = arg0;
    temp_a0 += D_800BE9C0 << 6;
    func_150A7B80(temp_a0 + 0x78, arg0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513B968 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B968.s")
void func_100043B4(s32 arg0, s32 arg1, void *arg2);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513B9A8 CURRENT (100) */
void func_1513B9A8(void *arg0, s32 arg1, void *arg2) {
    func_100043B4(*(s32 *)((u8 *)arg0 + 0x4C), 4, arg2);
    func_15169804((s32)arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513B9A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B9A8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513B9DC CURRENT (100) */
void func_1513B9DC(void *arg0, s32 arg1, void *arg2) {
    func_100043B4(*(s32 *)((u8 *)arg0 + 0x4C), 4, arg2);
    func_15169824((s32)arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513B9DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B9DC.s")
typedef void (*Func_1513BA10)(void);
extern Func_1513BA10 D_80089C44[];

void func_1513BA10(void *arg0) {
    D_80089C44[*(u8 *)((u8 *)arg0 + 0x48)]();
}
extern Func_1513BA10 D_80089C54[];

void func_1513BA44(void *arg0) {
    D_80089C54[*(u8 *)((u8 *)arg0 + 0x48)]();
}
void func_15109064(void *, void *, u8);
void func_151BA468(void *, void *, u8);

void func_1513BA78(void *arg0, void *arg1, u8 arg2) {
    switch (*(u8 *)((u8 *)arg0 + 0x48)) {
    case 1:
        func_15109064(arg0, arg1, arg2);
        return;
    case 2:
        func_151BA468(arg0, arg1, arg2);
        return;
    }
}
s32 func_1513BAD4(s32 arg0, s32 arg1) {
    return 0;
}
void *func_10022EC0(void *, const void *, u32);
void *func_1513B5E0(s8 *, s32, s32, s32, s32);

typedef struct Game168A90SpawnParams {
    s8 field_00;
    s8 field_01;
    s8 field_02;
    u8 pad03;
    s16 field_04;
    u8 pad06[2];
    s32 field_08;
    s32 field_0C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s8 field_24;
    s8 field_25;
    u8 pad26[10];
    s32 field_30;
    s32 field_34;
    s8 field_38;
    u8 pad39[3];
} Game168A90SpawnParams;

typedef struct Game168A90Vector5 {
    f32 field_00;
    f32 field_04;
    f32 field_08;
    f32 field_0C;
    f32 field_10;
} Game168A90Vector5;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513BAE8 CURRENT (1102) */
void *func_1513BAE8(void) {
    void *sp74;
    Game168A90SpawnParams sp38;
    Game168A90Vector5 sp24;
    register void *temp_v0;
    register void *var_a3;

    sp38.field_01 = 2;
    sp38.field_02 = 5;
    sp38.field_04 = 0x12C;
    sp38.field_30 = 9;
    sp24.field_00 = 0.0f;
    sp24.field_04 = 0.0f;
    sp24.field_0C = 0.0f;
    sp24.field_10 = 0.0f;
    sp24.field_08 = 0.0f;
    sp38.field_00 = 0;
    sp38.field_34 = 0x1AE;
    sp38.field_08 = 1;
    sp38.field_0C = 0x220205;
    sp38.field_10 = 0x40600;
    sp38.field_24 = 0;
    sp38.field_25 = 0;
    sp38.field_14 = 1;
    sp38.field_18 = 0x36;
    sp38.field_1C = 0x80;
    sp38.field_20 = 0x20;
    sp38.field_38 = 3;
    temp_v0 = func_1513B5E0((s8 *)&sp38, 1, 0x14, 0xFF, 1);
    var_a3 = temp_v0;
    if (temp_v0 != 0) {
        if (*(s32 *)((u8 *)temp_v0 + 0x50) != 0x1180) {
            sp74 = temp_v0;
            func_1516972C(temp_v0);
        } else {
            sp74 = var_a3;
            func_10022EC0((u8 *)var_a3 + *(s32 *)((u8 *)var_a3 + 0x50) + 0xF8,
                          &sp24, 0x14U);
        }
        var_a3 = sp74;
    }
    return var_a3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513BAE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BAE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BBFC.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800A4A84;
extern f32 D_800A4A88;
extern f32 D_800A4A8C;
extern f32 D_800A4A90;
extern f32 D_800A4A94;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513BEB0 CURRENT (919) */
s32 func_1513BEB0(u8 *arg0) {
    f32 temp_fv0;
    u8 *temp_s0;
    u8 *temp_s0_2;

    temp_s0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    temp_s0_2 = (void *)(temp_s0 + 0xF8);
    *(f32 *)((u8 *)temp_s0_2 + 8) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x100) + (D_800A4A84 * D_800BE9A4));
    temp_fv0 = func_15144B68(*(f32 *)((u8 *)temp_s0_2 + 8));
    *(f32 *)((u8 *)temp_s0_2 + 8) = temp_fv0;
    *(f32 *)((u8 *)temp_s0 + 0xF8) = (f32) (*(f32 *)((u8 *)temp_s0 + 0xF8) + (D_800A4A88 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0_2 + 4) = (f32) (func_15047D60(temp_fv0) * D_800A4A8C);
    *(f32 *)((u8 *)temp_s0_2 + 0xC) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 0xC) + (D_800A4A90 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0_2 + 0x10) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 0x10) + (D_800A4A94 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0_2 + 0xC) = func_15144B68(*(f32 *)((u8 *)temp_s0_2 + 0xC));
    *(f32 *)((u8 *)temp_s0_2 + 0x10) = func_15144B68(*(f32 *)((u8 *)temp_s0_2 + 0x10));
    if (*(f32 *)((u8 *)temp_s0 + 0xF8) > 4096.0f) {
        do {
            *(f32 *)((u8 *)temp_s0 + 0xF8) = (f32) (*(f32 *)((u8 *)temp_s0 + 0xF8) - 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0 + 0xF8) > 4096.0f);
    }
    if (*(f32 *)((u8 *)temp_s0 + 0xF8) < 0.0f) {
        do {
            *(f32 *)((u8 *)temp_s0 + 0xF8) = (f32) (*(f32 *)((u8 *)temp_s0 + 0xF8) + 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0 + 0xF8) < 0.0f);
    }
    if (*(f32 *)((u8 *)temp_s0_2 + 4) > 4096.0f) {
        do {
            *(f32 *)((u8 *)temp_s0_2 + 4) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 4) - 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0_2 + 4) > 4096.0f);
    }
    if (*(f32 *)((u8 *)temp_s0_2 + 4) < 0.0f) {
        do {
            *(f32 *)((u8 *)temp_s0_2 + 4) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 4) + 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0_2 + 4) < 0.0f);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513BEB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BEB0.s")
