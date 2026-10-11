#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_121A20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_secondary_stream_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F4570
 * - func_150F48D0
 * - func_150F4A38
 * - func_150F4CFC
 * - func_150F4DEC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game121A20NestedState {
    u8 pad0[0x24];
    u8 flags;
} Game121A20NestedState;

typedef struct Game121A20State {
    u8 pad0[0x71];
    u8 field71;
    u8 pad72[0xFE];
    Game121A20NestedState nested170;
} Game121A20State;

void *func_10022EC0(void *, const void *, u32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4570.s")
/* Call context: func_1514373C: unique active project prototype */
void func_1514373C(f32, f32, f32 *, f32 *);
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F48D0 CURRENT (590) */
void *func_150F48D0(u8 *arg0) {
    u8 *temp_v0;
    f32 sp20;
    f32 sp1C;

    temp_v0 = (void *)(arg0 + 0x170);
    *(f32 *)((u8 *)arg0 + 0x170) = (f32) (*(f32 *)((u8 *)arg0 + 0x170) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x170) <= 0.0f) {
        return 0;
    }
    func_1514373C(*(f32 *)((u8 *)temp_v0 + 0x10), *(f32 *)((u8 *)temp_v0 + 0x20), &sp1C, &sp20);
    *(f32 *)((u8 *)temp_v0 + 0x10) += *(f32 *)((u8 *)temp_v0 + 0x14) * D_800BE9A4;
    *(f32 *)((u8 *)temp_v0 + 4) += *(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4;
    *(f32 *)((u8 *)temp_v0 + 8) += *(f32 *)((u8 *)arg0 + 0x48) * D_800BE9A4;
    *(f32 *)((u8 *)temp_v0 + 0xC) += *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x18) * sp1C) + *(f32 *)((u8 *)temp_v0 + 4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)temp_v0 + 8) + sp20);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)temp_v0 + 0xC) - (*(f32 *)((u8 *)temp_v0 + 0x1C) * sp1C));
    *(f32 *)((u8 *)arg0 + 0x20) += *(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x24) += *(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x28) += *(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4;
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F48D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F48D0.s")
typedef struct GameF4A38Vector {
    f32 x, y, z;
} GameF4A38Vector;

typedef struct GameF4A38Actor {
    u8 pad0[0x38];
    GameF4A38Vector position;
    u8 pad44[0x2C];
    u8 opacity;
    u8 pad71[0x17];
    u32 sound;
    u8 pad8C[0xE4];
    Game121A20NestedState nested;
} GameF4A38Actor;

s32 func_15144B34(s32);
void func_1000F9D4(s32, s32, s32, s32);
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_150ADA20(void);
extern f64 D_800A1A88, D_800A1A90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F4A38 CURRENT (1667) */
s32 func_150F4A38(GameF4A38Actor *arg0) {
    f32 distance;
    GameF4A38Vector delta;
    u8 *saved;
    u8 *nested;
    GameF4A38Vector *camera;
    u32 handle;
    s32 flags;

    nested = (u8 *) &arg0->nested;
    if ((arg0->nested.flags & 1) || ((flags = nested[0x24]) & 2)) {
        saved = (u8 *) &arg0->nested;
        camera = (GameF4A38Vector *) func_15144B34(0);
        delta.x = arg0->position.x - camera->x;
        delta.y = arg0->position.y - camera->y;
        delta.z = arg0->position.z - camera->z;
        distance = func_15143E64(&delta);
        nested = saved;
        flags = nested[0x24];
    }
    if (flags & 1) {
        if (distance < 500.0f) {
            arg0->opacity = 0;
        } else if (distance < 1200.0f) {
            arg0->opacity = (u32) ((f64) (distance - 500.0f) * D_800A1A88 * D_800A1A90);
        } else {
            arg0->opacity = 255;
        }
        flags = nested[0x24];
    }
    if ((flags & 2) && !(flags & 4)) {
        handle = arg0->sound >> 16;
        if (handle != 0) {
            func_1000F9D4(handle & 0xFFFF, (s16) (s32) arg0->position.x,
                         (s16) (s32) arg0->position.y, (s16) (s32) arg0->position.z);
        } else if (distance < 200.0f) {
            handle = func_10010F88(arg0->sound & 0xFFFF,
                (u16) ((func_150ADA20() & 0x3FFF) + 0x4000), 0, 0, -1,
                (s32) arg0->position.x, (s32) arg0->position.y, (s32) arg0->position.z,
                10000, 20000);
            arg0->sound |= handle << 16;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F4A38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4A38.s")


#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F4CFC CURRENT (410) */
void func_150F4CFC(Game121A20State *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4E) {
        arg0->field71 = 0;
        arg0->nested170.flags |= 5;
        return;
    }
    if (arg2 == 0x4F) {
        func_1516972C((u8 *)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F4CFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4CFC.s")

void func_150F4D5C(s32 arg0, s8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct {
        s32 field_0;
        f32 field_4;
        s8 field_8;
        u8 field_9;
        u8 padA[2];
    } packet;
    u8 *temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = 0.0f;
    packet.field_8 = arg1;
    packet.field_9 = arg2;
    temp_v0 = func_15149130(0x12C, -1, 0x56, -1, 0, 0, 0xC, (s32) arg3, arg4);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 0xC);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4DEC.s")
