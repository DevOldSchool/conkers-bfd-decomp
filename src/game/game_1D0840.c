#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D0840.c
 * Boundary evidence: docs/evidence/game_raw_composite_emitter_timed_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A3390
 * - func_151A3504
 * - func_151A361C
 * - func_151A37C0
 * - func_151A3BE4
 * - func_151A4590
 * - func_151A4638
 * - func_151A483C
 * - func_151A4900
 * - func_151A499C
 * - func_151A4A38
 * - func_151A4CE0
 * - func_151A4D88
 * - func_151A4E34
 * - func_151A4E9C
 * - func_151A4ECC
 * - func_151A4F7C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A3390.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A3504.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A361C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A37C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A3BE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4590.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4638.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A483C CURRENT (510) */
s32 func_151A483C(u8 *arg0, s32 arg1) {
    f32 temp_fv0;
    s16 temp_v1;
    u8 *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1A);
    temp_v0 = (void *)(arg0 + 0xA8);
    if (temp_v1 < *(s16 *)((u8 *)arg0 + 0xAC)) {
        *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (temp_v1 * *(s16 *)((u8 *)arg0 + 0xAE));
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 8)) {
        temp_fv0 = (f32) (*(s16 *)((u8 *)temp_v0 + 0xA) * D_800BE9E4);
        *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + temp_fv0);
        *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + temp_fv0);
    }
    if (*(s16 *)((u8 *)arg0 + 0x1A) < *(s16 *)((u8 *)arg0 + 0xA8)) {
        *(s8 *)((u8 *)arg0 + 0x72) = 1;
        *(s8 *)((u8 *)arg0 + 0x70) = 2;
        *(s8 *)((u8 *)arg0 + 0x71) = 2;
        *(s16 *)((u8 *)arg0 + 0x18) = 0x5203;
        *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s16 *)((u8 *)arg0 + 0x1A) * *(s16 *)((u8 *)temp_v0 + 2));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A483C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A483C.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4900 CURRENT (80) */
s32 func_151A4900(u8 *arg0, s32 arg1) {
    f32 temp_fv0;
    s16 temp_a1;
    u8 *temp_v1;

    temp_a1 = *(s16 *)((u8 *)arg0 + 0x1A);
    temp_v1 = (void *)(arg0 + 0xA8);
    if (temp_a1 < *(s16 *)((u8 *)arg0 + 0xAC)) {
        *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (temp_a1 * *(s16 *)((u8 *)arg0 + 0xAE));
    }
    if (temp_a1 < *(s16 *)((u8 *)temp_v1 + 8)) {
        temp_fv0 = (f32) (*(s16 *)((u8 *)temp_v1 + 0xA) * D_800BE9E4);
        *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + temp_fv0);
        *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + temp_fv0);
    }
    *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s16 *)((u8 *)arg0 + 0x1A) * *(s16 *)((u8 *)temp_v1 + 2));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4900 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4900.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A499C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4A38.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4CE0 CURRENT (1222) */
void func_151A4CE0(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    if (temp_t6 == 0) {
        if ((*(s32 *)((u8 *)temp_v0 + 0) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_151A4E9C(arg0);
        }
    } else if (temp_t6 == 0x2D) {
        temp_a0 = *(s32 *)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)temp_v0 + 0);
        if (temp_a0 == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32) *(u8 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if ((s32) *(u8 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = temp_a0;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4CE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4CE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4D88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4E34.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4E9C CURRENT (220) */
void func_151A4E9C(void *arg0) {
    u8 temp_t0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    temp_t0 = *(u8 *)((u8 *)temp_v0 + 0x30) | 1;
    *(u8 *)((u8 *)temp_v0 + 0x30) = temp_t0;
    *(u8 *)((u8 *)temp_v0 + 0x30) = (u8) (temp_t0 | 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4E9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4E9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4ECC.s")
typedef struct {
    s32 field_0;
    u8 field_4;
} Game1D0840Data;

typedef struct {
    u8 pad_0[0x28];
    Game1D0840Data field_28;
} Game1D0840State;

void func_1516972C(Game1D0840State *, Game1D0840Data *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4F7C CURRENT (647) */
void func_151A4F7C(Game1D0840State *arg0, Game1D0840Data *arg1, s32 arg2) {
    s32 temp_t6;

    temp_t6 = arg2 & 0xFF;
    if ((temp_t6 == 0) && ((arg0->field_28.field_0 == arg1->field_0) ||
        (arg0->field_28.field_4 == arg1->field_4))) {
        func_1516972C(arg0, arg1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4F7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4F7C.s")
