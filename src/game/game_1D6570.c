#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D6570.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A90C0
 * - func_151A91AC
 * - func_151A931C
 * - func_151A9390
 * - func_151A9834
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s8 field_0;
    u8 pad_1[3];
    s32 field_4;
    f32 field_8;
    f32 field_C;
    f32 field_10;
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    f32 field_20;
    s8 field_24;
    s8 field_25;
    s8 field_26;
} Game1D6570Descriptor;

void *func_10022EC0(void *, const void *, u32);
s32 func_151A8B20(Game1D6570Descriptor *, s32, s32, s32, s32);
extern f32 D_800A8F58;
extern f32 D_800A8F5C;
extern f32 D_800A8F60;
extern f32 D_800A8F64;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A90C0 CURRENT (302) */
void func_151A90C0(s32 arg0, s32 arg1) {
    Game1D6570Descriptor descriptor;
    s8 payload;
    f32 parity;
    s32 result;

    descriptor.field_4 = arg0;
    descriptor.field_0 = 2;
    parity = (f32)(arg1 & 1);
    if (parity != 0.0f) {
        descriptor.field_8 = D_800A8F58;
    } else {
        descriptor.field_8 = D_800A8F5C;
    }
    if (parity != 0.0f) {
        descriptor.field_C = D_800A8F60;
    } else {
        descriptor.field_C = D_800A8F64;
    }
    descriptor.field_10 = 0.0f;
    descriptor.field_14 = 0.0f;
    descriptor.field_18 = 0.0f;
    descriptor.field_1C = 0.0f;
    descriptor.field_20 = 0.0f;
    descriptor.field_24 = 1;
    descriptor.field_25 = -1;
    descriptor.field_26 = 0;
    payload = arg1;
    result = func_151A8B20(&descriptor, -1, 1, 0xFF, 0);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x80, &payload, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A90C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A90C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A91AC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A931C CURRENT (1055) */
void func_151A931C(void *arg0, u8 *arg1, s32 arg2) {
    s32 temp_t6;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x17) {
        if (*arg1 == *(u8 *)((u8 *)arg0 + 0x80)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) (*(u8 *)((u8 *)arg0 + 0x28) | 1);
        }
    } else if ((temp_t6 == 0x18) && (*arg1 == *(u8 *)((u8 *)arg0 + 0x80))) {
        *(u8 *)((u8 *)arg0 + 0x28) = (u8) (*(u8 *)((u8 *)arg0 + 0x28) & 0xFFFE);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A931C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A931C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A9390.s")
typedef struct Game1D6570Emitter {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    s16 field10;
    s16 field12;
    s16 field14;
    s16 field16;
    s16 field18;
    s16 field1A;
    s16 field1C;
    s16 field1E;
    f32 field20;
    f32 field24;
    u8 flags28;
} Game1D6570Emitter;

typedef struct Game1D6570Actor {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD[0x73];
    Game1D6570Emitter emitter;
} Game1D6570Actor;

typedef struct Game1D6570Payload {
    f32 field0;
    s16 field4;
} Game1D6570Payload;

void *func_10022EC0(void *, const void *, u32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_1514B8E4(s32, f32 *, s16, s32, s32, f32, f32, f32,
    s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151A9634(Game1D6570Actor *arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 position[2];
    s32 choice;
    Game1D6570Payload payload;
    s32 kind;
    s32 flags;
    s32 result;
    Game1D6570Emitter *emitter;
    u32 random2;
    u32 random1;

    emitter = &arg0->emitter;
    position[0] = func_150ADA68() * emitter->field8 + emitter->field0;
    position[1] = func_150ADA68() * emitter->fieldC + emitter->field4;
    payload.field0 = func_150ADA68() * emitter->field24 + emitter->field20;
    payload.field4 = func_150ADA20() % (u32)(emitter->field16 + 1) + emitter->field14;
    random1 = func_150ADA20();
    random2 = func_150ADA20();
    if (emitter->flags28 & 1) {
        kind = 0x71;
    } else {
        if (func_150ADA20() & 1) {
            choice = 0x13;
        } else {
            choice = 0x14;
        }
        kind = choice;
    }
    flags = (emitter->flags28 & 2) ? 0 : 2;
    result = func_1514B8E4(arg1, position,
        (s16)(random1 % (u32)(emitter->field12 + 1) + emitter->field10),
        (random2 % (u32)(emitter->field1A + 1) + emitter->field18) & 0xFF,
        0, 0.0f, 1.0f, 1.0f, 0x21, 0x23, 2, kind, flags,
        emitter->field1C, emitter->field1E, 8, arg0->fieldC, arg0->field1);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x160, &payload, 8);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A9834.s")
