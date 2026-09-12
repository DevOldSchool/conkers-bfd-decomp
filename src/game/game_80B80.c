#include "types.h"

/*
 * Reviewed source unit: src/game/game_80B80.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15053750
 * - func_15053894
 * - func_150538CC
 * - func_150548E4
 * - func_15054A94
 * - func_15054F74
 * - func_1505528C
 * - func_15055A2C
 * - func_15055B0C
 * - func_15055B64
 * - func_15055BF8
 * - func_15055C88
 * - func_15055D48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game80B80Object {
    s32 field_0;
    u8 pad4[0xE0];
    s16 field_E4;
    s16 field_E6;
} Game80B80Object;

void func_150536D0(Game80B80Object *arg0) {
    arg0->field_0 = 0xD;
    arg0->field_E4 = 0;
    arg0->field_E6 = 0;
}
void func_150536E8(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
}
void func_1505371C(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15053750.s")
/* Call context: func_15060F28: unique active project prototype */
void func_15060F28(u8 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15053894 CURRENT (10) */
void func_15053894(u8 *arg0) {
    u8 temp_t6;
    u8 temp_t7;
    u8 temp_t8;

    temp_t6 = arg0[0x7F];
    temp_t7 = temp_t6 + 1;
    temp_t8 = temp_t7 & 0xFF;
    arg0[0x7F] = temp_t7;
    if (temp_t8 >= 0x1F) {
        func_15060F28(arg0, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15053894 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15053894.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_150538CC.s")
void func_150548D8(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_150548E4.s")
void func_15054A0C(u8 *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x2D0);
    if ((temp_v0 != 0) && ((*(f32 *)((u8 *)temp_v0 + 0x18) - 1.0f) <= *(f32 *)((u8 *)temp_v0 + 8))) {
        func_15060F28(arg0, 0);
    }
}
void func_15054A5C(u8 *arg0, void *arg1) {
    *(s8 *)((u8 *)*(void **)((u8 *)arg1 + 0x31C) + 0x11A) = 0;
    func_151027E8(arg1);
    func_15060F28(arg0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15054A94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15054F74.s")
void func_150335C8(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_15055260(void *arg0, void *arg1, s32 arg2) {
    func_150335C8(arg0, arg1, 0x4D, arg2, 0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_1505528C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15055A2C.s")
/* Call context: func_1505E650: unique active project prototype */
void func_1505E650(u8 *, s32, s32, s32, f32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15055B0C CURRENT (400) */
void func_15055B0C(u8 *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0) = 0x27;
    func_1505E650(arg0, (s32) *(u16 *)((u8 *)arg0 + 0x84), 0, 0, 0.0f, 0.0f, 0);
    *(s16 *)((u8 *)arg0 + 0xE4) = 0;
    *(s16 *)((u8 *)arg0 + 0xE6) = 0;
    *(s16 *)((u8 *)arg0 + 0x21C) = (s16) arg1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15055B0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15055B0C.s")
/* Call context: func_15060F28: unique active project prototype */
extern u8 D_800BE9A0;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15055B64 CURRENT (515) */
void func_15055B64(u8 *arg0) {
    u16 temp_v0;

    *(s32 *)((u8 *)arg0 + 0xF8) = (s32) (*(s32 *)((u8 *)arg0 + 0xF8) | 0x01000000);
    temp_v0 = *(u16 *)((u8 *)arg0 + 0x21C);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
    if ((s32) D_800BE9A0 < (s32) temp_v0) {
        *(u16 *)((u8 *)arg0 + 0x21C) = (u16) (temp_v0 - D_800BE9E4);
        return;
    }
    *(u16 *)((u8 *)arg0 + 0x21C) = 0U;
    if (*(s32 *)((u8 *)arg0 + 0x1D4) == 0) {
        func_15060F28(arg0, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15055B64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15055B64.s")
/* Call context: func_15060F28: unique active project prototype */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15055BF8 CURRENT (515) */
void func_15055BF8(u8 *arg0) {
    *(s32 *)((u8 *)arg0 + 0xF8) = (s32) (*(s32 *)((u8 *)arg0 + 0xF8) | 0x01000000);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x18) < (*(f32 *)((u8 *)arg0 + 0x180) - 100.0f)) {
        func_15060F28(arg0, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15055BF8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15055BF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15055C88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_80B80/func_15055D48.s")
