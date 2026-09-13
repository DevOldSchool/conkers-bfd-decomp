#include "types.h"

/*
 * Reviewed source unit: src/game/game_1890A0.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515BBF0
 * - func_1515BE50
 * - func_1515BFA8
 * - func_1515C0F8
 * - func_1515C158
 * - func_1515C1A0
 * - func_1515C244
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1890A0/func_1515BFA8.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_1515C0B8(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x18, arg0 + 0x1C, arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515C0F8 CURRENT (30) */
s32 func_1515C0F8(Game1890A0State *arg0, u8 **arg1) {
    Game1890A0Node *sp1C;

    if (arg0 == 0) {
        return 0;
    }
    if (func_1514ECE0(arg0->field2F4, 0x16, (void **) &sp1C, arg0) != 0) {
        *arg1 = sp1C->field10 + 0x38;
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515C0F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1890A0/func_1515C0F8.s")
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515C1A0 CURRENT (25) */
void func_1515C1A0(void *arg0, void *arg1, f32 *arg2, f32 *arg3) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if (((s32) temp_v0 < 0xBB) && (temp_v0 != 0xFF)) {
        *arg2 = (f32) *(s16 *)((u8 *)arg0 + 0xD2);
        *arg3 = (f32) *(s16 *)((u8 *)arg0 + 0xD4);
        *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (f32) *(s16 *)((u8 *)arg0 + 0xD6));
        *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
        return;
    }
    *arg2 = 1.0f;
    *arg3 = 1.0f;
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) *(f32 *)((u8 *)arg0 + 0x18);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515C1A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1890A0/func_1515C1A0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515C244 CURRENT (25) */
void func_1515C244(void *arg0, void *arg1, f32 *arg2, f32 *arg3) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if (((s32) temp_v0 < 0xBB) && (temp_v0 != 0xFF)) {
        *arg2 = (f32) *(s16 *)((u8 *)arg0 + 0xE4);
        *arg3 = (f32) *(s16 *)((u8 *)arg0 + 0xE6);
        *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (f32) *(s16 *)((u8 *)arg0 + 0xE8));
        *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
        return;
    }
    *arg2 = 1.0f;
    *arg3 = 1.0f;
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) *(f32 *)((u8 *)arg0 + 0x18);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515C244 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1890A0/func_1515C244.s")
