#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BA670.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518D1C0
 * - func_1518D6E0
 * - func_1518E308
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1BA670/func_1518D1C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BA670/func_1518D6E0.s")
s32 func_1518E298(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x1C);
    if ((temp_v1 != 0) && (*(s32 *)((u8 *)temp_v1 + 0) != 0)) {
        *(s16 *)((u8 *)arg0 + 2) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x14);
        *(s16 *)((u8 *)arg0 + 4) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x18);
        *(s16 *)((u8 *)arg0 + 6) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x1C);
        return 0;
    }
    return 1;
}
typedef struct Game1BA670Slot {
    void *effect;
    u8 pad4[0x14];
} Game1BA670Slot;

typedef struct Game1BA670State {
    u8 pad0[0x24];
    f32 field_24;
    s32 field_28;
    u8 pad2C[0x1C];
    Game1BA670Slot slots[100];
} Game1BA670State;

void func_1516972C(void *);
void func_100226F0(void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518E308 CURRENT (8) */
void func_1518E308(Game1BA670State *arg0) {
    Game1BA670Slot *first;
    Game1BA670Slot *slot;
    s32 i;

    slot = arg0->slots;
    first = slot;
    arg0->field_28 = 0;
    i = 0;
    arg0->field_24 = 0.0f;
    do {
        if (slot->effect != 0) {
            func_1516972C(slot->effect);
        }
        i++;
        slot++;
    } while (i != 100);
    func_100226F0(first, sizeof(arg0->slots));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518E308 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BA670/func_1518E308.s")
/* Call context: func_1518E308: unique active project prototype */
void func_1518E308(Game1BA670State *);

void func_1518E37C(void *arg0, u8 arg1) {
    if (arg1 != *(u8 *)((u8 *)arg0 + 0x22)) {
        func_1518E308(arg0);
        *(u8 *)((u8 *)arg0 + 0x22) = arg1;
    }
}
void *func_15167A68(s32, s32, s32, s32, u8, u8);
void *func_10022EC0(void *, const void *, u32);

void *func_1518E3C4(void **arg0, u8 arg1) {
    u8 *result;

    if (*(u8 *)((u8 *)*arg0 + 4) == 0x96) {
        return 0;
    }
    result = func_15167A68(0x21, 1, 0x9EC, 1, arg1, 1);
    if (result == 0) {
        return 0;
    }
    func_10022EC0(result + 0x18, arg0, 0xC);
    *(s32 *)(result + 0x28) = 0;
    *(s8 *)(result + 0x2C) = 8;
    *(s8 *)(result + 0x2D) = 4;
    *(s32 *)(result + 0x30) = 0;
    *(s32 *)(result + 0x10) = 1;
    *(s32 *)(result + 0x14) = 0;
    *(f32 *)(result + 0x24) = 0.0f;
    *(f32 *)(result + 0x38) = 0.0f;
    *(f32 *)(result + 0x3C) = 0.0f;
    *(f32 *)(result + 0x40) = 0.0f;
    *(f32 *)(result + 0x34) = 1.0f;
    func_100226F0(result + 0x48, 0x960);
    return result;
}
