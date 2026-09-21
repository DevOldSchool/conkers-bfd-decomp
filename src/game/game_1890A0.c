#include "types.h"

/*
 * Reviewed source unit: src/game/game_1890A0.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515BBF0
 * - func_1515BE50
 * - func_1515BFA8
 * - func_1515C158
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1890A0State {
    u8 pad0[0x2F4];
    s32 field2F4;
} Game1890A0State;

typedef struct Game1890A0Node {
    u8 pad0[0x10];
    u8 *field10;
} Game1890A0Node;

s32 func_1514ECE0(s32, s32, void **, void *);

#pragma GLOBAL_ASM("asm/nonmatchings/game_1890A0/func_1515BBF0.s")
void func_1515BE48(void) {

}
void *func_10022EC0(void *, const void *, u32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);

typedef struct {
    u8 pad0[0x10];
    s32 field10;
    s32 field14;
    u8 payload18[8];
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    s32 field44;
    s32 field48;
} Game1890A0Effect;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515BE50 CURRENT (88) */
void *func_1515BE50(void **arg0, s32 arg1, u8 arg2, s32 arg3) {
    f32 final_value;
    Game1890A0Effect *result;
    Game1890A0Effect *allocated;

    if (*arg0 == 0) {
        return 0;
    }
    allocated = func_15167A68(0x32, arg3, arg1 + 0x50, 1, arg2, 1);
    if (allocated == 0) {
        return 0;
    }
    result = allocated;
    func_10022EC0(result->payload18, arg0, 8);
    result->field20 = *(f32 *)((u8 *)*arg0 + 0x14);
    result->field24 = *(f32 *)((u8 *)*arg0 + 0x18);
    result->field28 = *(f32 *)((u8 *)*arg0 + 0x1C);
    result->field2C = *(f32 *)((u8 *)*arg0 + 0x14);
    result->field30 = *(f32 *)((u8 *)*arg0 + 0x18);
    final_value = *(f32 *)((u8 *)*arg0 + 0x1C);
    result->field44 = 0;
    result->field48 = -1;
    result->field10 = 1;
    result->field14 = 0;
    result->field38 = 0.0f;
    result->field3C = 0.0f;
    result->field40 = 0.0f;
    result->field34 = final_value;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515BE50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1890A0/func_1515BE50.s")
/* Call context: func_1514EDF0: unique active project prototype */
/* Call context: func_15169804: unique active project prototype */
void func_1514EDF0(s32, s32);
void func_15169804(s32);
void func_15169824(s32);

void func_1515BF50(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_15169804((s32) arg0);
}
void func_1515BF7C(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_15169824((s32) arg0);
}
extern f32 D_800BE9A8;
extern s32 D_800BE9E4;
void func_1516972C(u8 *);

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Game1890A0Vector;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515BFA8 CURRENT (60) */
void func_1515BFA8(u8 *arg0) {
    s32 var_a1;
    f32 *temp_v1;
    u8 *temp_v0;

    var_a1 = 0;
    if (arg0[0x1D] & 1) {
        *(s16 *)(arg0 + 0x1E) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x1E) < 0) {
            var_a1 = 1;
        }
    }
    temp_v0 = *(u8 **)(arg0 + 0x18);
    if ((*(s32 *)temp_v0 == 0) || (arg0[0x1C] != temp_v0[0x3B])) {
        var_a1 = 1;
    }
    if (var_a1 == 0) {
        *(Game1890A0Vector *)(arg0 + 0x2C) = *(Game1890A0Vector *)(arg0 + 0x20);
        temp_v0 = *(u8 **)(arg0 + 0x18);
        temp_v1 = &D_800BE9A8;
        *(f32 *)(arg0 + 0x20) = *(f32 *)(temp_v0 + 0x14);
        *(f32 *)(arg0 + 0x24) = *(f32 *)(temp_v0 + 0x18);
        *(f32 *)(arg0 + 0x28) = *(f32 *)(temp_v0 + 0x1C);
        *(f32 *)(arg0 + 0x38) = (*(f32 *)(arg0 + 0x2C) - *(f32 *)(arg0 + 0x20)) * *temp_v1;
        *(f32 *)(arg0 + 0x3C) = (*(f32 *)(arg0 + 0x30) - *(f32 *)(arg0 + 0x24)) * *temp_v1;
        *(f32 *)(arg0 + 0x40) = (*(f32 *)(arg0 + 0x34) - *(f32 *)(arg0 + 0x28)) * *temp_v1;
    }
    if (var_a1 != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515BFA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1890A0/func_1515BFA8.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_1515C0B8(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x18, arg0 + 0x1C, arg0);
}
s32 func_1515C0F8(Game1890A0State *arg0, u8 **arg1) {
    Game1890A0Node *sp1C;
    u8 *data;

    if (arg0 == 0) {
        return 0;
    }
    if (func_1514ECE0(arg0->field2F4, 0x16, (void **) &sp1C, arg0) != 0) {
        data = sp1C->field10;
        *arg1 = data + 0x38;
        return 1;
    }
    return 0;
}
extern u8 D_800DCE50[];
extern u8 D_800DD190[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515C158 CURRENT (105) */
void func_1515C158(void) {
    u8 *var_v1;
    void *var_v0;

    var_v1 = D_800DCE50;
    do {
        var_v0 = *(void **)(var_v1 + 0xC8);
        var_v1 += 0x1A0;
        if (var_v0 != 0) {
            do {
                *(s32 *)((u8 *)var_v0 + 0x44) = 0;
                *(s32 *)((u8 *)var_v0 + 0x48) = -1;
                var_v0 = *(void **)((u8 *)var_v0 + 8);
            } while (var_v0 != 0);
        }
    } while (var_v1 != D_800DD190);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515C158 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1890A0/func_1515C158.s")
void func_1515C1A0(void *arg0, void *arg1, f32 *arg2, f32 *arg3) {
    u8 temp_v0;
    f32 fallback;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if (((s32) temp_v0 < 0xBB) && (temp_v0 != 0xFF)) {
        *arg2 = (f32) *(s16 *)((u8 *)arg0 + 0xD2);
        *arg3 = (f32) *(s16 *)((u8 *)arg0 + 0xD4);
        *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg1 + 4) = (f32) ((f32) *(s16 *)((u8 *)arg0 + 0xD6) + *(f32 *)((u8 *)arg0 + 0x18));
        *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
        return;
    }
    fallback = 1.0f;
    *arg2 = fallback;
    *arg3 = fallback;
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) *(f32 *)((u8 *)arg0 + 0x18);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
void func_1515C244(void *arg0, void *arg1, f32 *arg2, f32 *arg3) {
    u8 temp_v0;
    f32 fallback;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if (((s32) temp_v0 < 0xBB) && (temp_v0 != 0xFF)) {
        *arg2 = (f32) *(s16 *)((u8 *)arg0 + 0xE4);
        *arg3 = (f32) *(s16 *)((u8 *)arg0 + 0xE6);
        *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg1 + 4) = (f32) ((f32) *(s16 *)((u8 *)arg0 + 0xE8) + *(f32 *)((u8 *)arg0 + 0x18));
        *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
        return;
    }
    fallback = 1.0f;
    *arg2 = fallback;
    *arg3 = fallback;
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) *(f32 *)((u8 *)arg0 + 0x18);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
