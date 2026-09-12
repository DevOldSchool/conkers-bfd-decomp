#include "types.h"

/*
 * Reviewed source unit: src/game/game_11D830.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F03F8
 * - func_150F07E4
 * - func_150F088C
 * - func_150F0938
 * - func_150F0A24
 * - func_150F0BEC
 * - func_150F0E48
 * - func_150F1020
 * - func_150F10D4
 * - func_150F1170
 * - func_150F15F8
 * - func_150F1684
 * - func_150F16DC
 * - func_150F1A00
 * - func_150F1B48
 * - func_150F1CB0
 * - func_150F1D10
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game11D830Inner {
    u8 pad0[0x138];
    s32 field_138;
} Game11D830Inner;

typedef struct Game11D830Object {
    u8 pad0[0x178];
    Game11D830Inner *inner;
} Game11D830Object;

typedef struct Game11D830AltInner {
    u8 pad0[0x13C];
    s32 field_13C;
} Game11D830AltInner;

typedef struct Game11D830AltObject {
    u8 pad0[0x18];
    Game11D830AltInner *inner;
} Game11D830AltObject;

Game11D830Inner *func_150F0380(Game11D830Object *arg0) {
    Game11D830Inner *inner = arg0->inner;

    inner->field_138 = 0;
    return inner;
}
Game11D830AltInner *func_150F03E8(Game11D830AltObject *arg0);
void func_151617C4(Game11D830AltObject *arg0);
void func_151617E4(Game11D830AltObject *arg0);

void func_150F0390(Game11D830AltObject *arg0) {
    func_150F03E8(arg0);
    func_151617C4(arg0);
}
void func_150F03BC(Game11D830AltObject *arg0) {
    func_150F03E8(arg0);
    func_151617E4(arg0);
}
Game11D830AltInner *func_150F03E8(Game11D830AltObject *arg0) {
    Game11D830AltInner *inner = arg0->inner;

    inner->field_13C = 0;
    return inner;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F03F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F07E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F088C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0938.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0A24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0BEC.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800A1870;
extern f32 D_800A1874;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F0E48 CURRENT (533) */
s32 func_150F0E48(u8 *arg0, s32 arg1) {
    u8 *temp_s0;
    u8 *temp_v0;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0xA8));
    if (*(u8 *)((u8 *)arg0 + 0xAC) != *(u8 *)((u8 *)temp_v0 + 0x3B)) {
        return 0;
    }
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) *(f32 *)((u8 *)temp_v0 + 0x14);
    temp_s0 = (void *)(arg0 + 0xA8);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) *(f32 *)((u8 *)temp_v0 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) *(f32 *)((u8 *)temp_v0 + 0x1C);
    *(f32 *)((u8 *)temp_s0 + 8) = (f32) (*(f32 *)((u8 *)temp_s0 + 8) + (D_800A1870 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0xC) = (f32) (*(f32 *)((u8 *)temp_s0 + 0xC) + (D_800A1874 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0x10) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x10) + (0.25f * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 8) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 8));
    *(f32 *)((u8 *)temp_s0 + 0xC) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0xC));
    *(f32 *)((u8 *)temp_s0 + 0x10) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x10));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) ((func_15047D60(*(f32 *)((u8 *)temp_s0 + 8)) * 243.0f) + 780.0f);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((func_15047D60(*(f32 *)((u8 *)temp_s0 + 0xC)) * 243.0f) + 780.0f);
    *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) ((func_15047D60(*(f32 *)((u8 *)temp_s0 + 0x10)) * 50.0f) + 200.0f);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F0E48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0E48.s")
void *func_1516972C(void *, s32, void *);           /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F1020 CURRENT (2723) */
void *func_150F1020(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *var_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2D) {
        var_v0 = (void *)(arg0 + 0xA8);
        temp_a0 = *(s32 *)((u8 *)arg0 + 0xA8);
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a0) {
            *(s32 *)((u8 *)arg0 + 0xA8) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)var_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return var_v0;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
            *(s32 *)((u8 *)arg0 + 0xA8) = temp_v1;
            *(u8 *)((u8 *)var_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
            return var_v0;
        }
        /* Duplicate return node #10. Try simplifying control flow for better match */
        return var_v0;
    }
    if (((temp_t6 == 0) || (var_v0 = arg0 + 0xA8, (temp_t6 == 0x43))) && ((var_v0 = arg0 + 0xA8, (*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0xA8))) || (*(u8 *)((u8 *)var_v0 + 4) == (u8) *(s32 *)((u8 *)arg1 + 4)))) {
        var_v0 = func_1516972C(arg0, temp_t6, arg0);
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F1020 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1020.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F10D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1170.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F15F8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F1684 CURRENT (852) */
void func_150F1684(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_t6;

    temp_t6 = arg2 & 0xFF;
    if ((temp_t6 == 0x43) && ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x18)) || (*(u8 *)((u8 *)(arg0 + 0x18) + 4) == *(u8 *)((u8 *)arg1 + 4)))) {
        func_1516972C(arg0, (s32) arg1, (void *) temp_t6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F1684 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1684.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F16DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1A00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1B48.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F1CB0 CURRENT (460) */
void func_150F1CB0(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0x84) == 0x14) {
        *(s8 *)((u8 *)arg0 + 0x68) = 0x1B;
    } else {
        *(s8 *)((u8 *)arg0 + 0x68) = 0xC;
    }
    *(s8 *)((u8 *)arg0 + 0x69) = 0x13;
    if ((*(s32 *)((u8 *)arg0 + 0x2E4) & 3) == 3) {
        *(s8 *)((u8 *)arg0 + 0x69) = 0x14;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x2E4) & 0xC) == 0xC) {
        *(s8 *)((u8 *)arg0 + 0x69) = 0x17;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F1CB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1CB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1D10.s")
