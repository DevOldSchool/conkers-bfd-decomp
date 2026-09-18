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
u32 func_1513418C(void *, s32, u8, s32);
extern f32 D_800A8D5C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4590 CURRENT (3228) */
void func_151A4590(void *arg0, s32 arg1) {
    s8 sp45;
    s8 sp44;
    s8 sp43;
    s8 sp42;
    s16 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s8 sp28;
    void *sp24;
    u8 sp20;
    s32 sp1C;
    s32 sp18;

    if (arg0 != 0) {
        sp18 = 0;
        sp1C = 0;
        sp28 = 1;
        sp40 = 0x64;
        sp42 = 0xA;
        sp43 = 1;
        sp44 = -1;
        sp45 = 0;
        sp24 = arg0;
        sp20 = *(u8 *)((u8 *)arg0 + 0x3B);
        sp2C = 0.0f;
        sp30 = 0.0f;
        sp34 = 0.0f;
        sp38 = D_800A8D5C;
        sp3C = 3.0f;
        func_1513418C(&sp18, 0, arg1 & 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4590 */
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
void func_10022EC0(void *, void *, s32);
s32 func_151491F4(s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A8D64;

typedef struct Game1D0840EffectPacket {
    void *field_0;
    u8 field_4;
    u8 pad5[3];
    f32 field_8;
    f32 field_C;
    u8 field_10;
    u8 pad11[3];
    f32 field_14;
    f32 field_18;
    f32 field_1C;
} Game1D0840EffectPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A499C CURRENT (37) */
void func_151A499C(void *arg0, u8 arg1) {
    Game1D0840EffectPacket packet;
    s32 temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_8 = D_800A8D64;
    packet.field_C = 0.0f;
    packet.field_10 = 1;
    packet.field_14 = 0.0f;
    packet.field_18 = 0.0f;
    packet.field_1C = 0.0f;
    temp_v0 = func_151491F4(0x12C, -1, 5, 0, 1, 0x20, (s32) arg1, 0);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0x20);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A499C */
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
typedef struct Game1D0840TransformSource {
    u8 pad0[0x74];
    u8 flags;
    u8 pad75[0x15F];
    u8 *transformBase;
} Game1D0840TransformSource;

typedef struct Game1D0840TransformRequest {
    Game1D0840TransformSource *source;
    u8 pad4;
    u8 transformIndex;
    u8 pad6[2];
    f32 input[3];
} Game1D0840TransformRequest;

void func_15143134(f32 *, f32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4E34 CURRENT (10) */
s32 func_151A4E34(Game1D0840TransformRequest *arg0, f32 *arg1) {
    u8 *temp_v1;
    Game1D0840TransformSource *temp_v0;

    temp_v0 = arg0->source;
    temp_v1 = temp_v0->transformBase;
    if (temp_v1 == 0) {
        return 0;
    }
    if ((temp_v0->flags & 0xF) == 0xF) {
        return 0;
    }
    func_15143134(arg0->input, arg1, (s32)(temp_v1 + (arg0->transformIndex << 6)));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4E34 */
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
