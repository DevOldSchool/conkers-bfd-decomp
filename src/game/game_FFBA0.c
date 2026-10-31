#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FFBA0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_child_chain_render_lists.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D26F0
 * - func_150D278C
 * - func_150D2924
 * - func_150D2D6C
 * - func_150D32FC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_150D278C: unique active declaration in the allowed source */
void func_150D278C(s32, void *, u8, s32);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D26F0 CURRENT (42) */
void func_150D26F0(u8 *arg0) {
    u8 *state;

    state = arg0 + 0x28;
    if (arg0[0x78] & 1) {
        if ((*(s32 *)(state + 0xC) -= D_800BE9E4) < 0) {
            func_150D278C(*(s32 *)state, state + 0x10, arg0[0xC], arg0[1]);
            *(s32 *)(state + 0xC) = *(s32 *)(state + 4) + (func_150ADA20() % (u32)(*(s32 *)(state + 8) + 1));
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D26F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D26F0.s")
void *func_10022EC0(void *, const void *, u32);
f32 func_150ADA68(void);
extern u8 D_800A0990[];
extern f32 D_800A099C;
extern f32 D_800A09A0;
extern f32 D_800A09A4;
extern f32 D_800A09A8;
extern f32 D_800A09AC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D278C CURRENT (941) */
void func_150D278C(s32 arg0, void *arg1, u8 arg2, s32 arg3) {
    u8 packet[0x60];
    u8 choices[9];
    u8 *color;
    u8 *object;
    f32 temp;

    *(s32 *)(packet + 0) = arg0;
    *(f32 *)(packet + 4) = (2.0f * func_150ADA68()) * D_800A099C;
    temp = (func_150ADA68() * D_800A09A0) + D_800A09A4;
    *(f32 *)(packet + 8) = temp;
    *(f32 *)(packet + 0xC) = 1.0f / temp;
    *(f32 *)(packet + 0x10) = (func_150ADA68() * D_800A09A8) + D_800A09AC;
    if (func_150ADA20() & 1) {
        *(f32 *)(packet + 0x10) = -*(f32 *)(packet + 0x10);
    }
    *(f32 *)(packet + 0x14) = 0.0f;
    *(f32 *)(packet + 0x18) = 0.0f;
    func_10022EC0(packet + 0x1C, arg1, 0x40);
    *(u32 *)choices = *(u32 *)D_800A0990;
    *(u32 *)(choices + 4) = *(u32 *)(D_800A0990 + 4);
    choices[8] = D_800A0990[8];
    color = choices + (((func_150ADA20() % 3U) & 0xFF) * 3);
    packet[0x5C] = color[0];
    packet[0x5D] = color[1];
    packet[0x5E] = color[2];
    object = func_15149130((s16)((func_150ADA20() % 101U) + 0x64), -1,
                           0x32, -1, 1, 0, 0x60, arg2, arg3);
    if (object != 0) {
        func_10022EC0(object + 0x28, packet, 0x60);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D278C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D278C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D2924.s")
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
typedef struct GameFFBA0BeamVertex {
    s16 x;
    s16 y;
    s16 z;
    s16 flag;
    s16 s;
    s16 t;
    u8 color[4];
} GameFFBA0BeamVertex;

void func_150AD8B0(f32 *, f32 *, f32 *);
s32 func_15144B34(s32);
void func_151D5D60(void *, s16, s32, void **, u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D2D6C CURRENT (6389) */
void *func_150D2D6C(u8 *arg0, s32 arg1) {
    GameFFBA0BeamVertex *vertices;
    void *result;
    f32 *camera;
    f32 delta[3];
    f32 end[3];
    f32 middle[3];
    f32 view[3];
    f32 side[3];
    f32 lengthSquared;
    f32 length;
    u8 fresh;
    f32 scale;
    u8 *slot;
    u8 *source;
    f32 x;
    f32 y;
    f32 z;

    func_151D5D60(arg0 + 0x100, ((s16 *)&arg1)[1], 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != NULL) {
        if (fresh != 0) {
            slot = arg0 + ((s16 *)&arg1)[1] * 4;
            source = arg0 + 0xC0;
            func_10022EC0(*(void **)(slot + 0x100), source, 0x40U);
            func_10022EC0(*(u8 **)(slot + 0x100) + 0x40, source, 0x40U);
        }
    } else {
        return NULL;
    }
    camera = (f32 *)func_15144B34(((s16 *)&arg1)[1]);
    delta[0] = *(f32 *)(arg0 + 0x40) - *(f32 *)(arg0 + 0x34);
    delta[1] = *(f32 *)(arg0 + 0x44) - *(f32 *)(arg0 + 0x38);
    delta[2] = *(f32 *)(arg0 + 0x48) - *(f32 *)(arg0 + 0x3C);
    end[0] = *(f32 *)(arg0 + 0x34) + delta[0];
    end[1] = *(f32 *)(arg0 + 0x38) + delta[1];
    end[2] = *(f32 *)(arg0 + 0x3C) + delta[2];
    middle[0] = *(f32 *)(arg0 + 0x34) + delta[0] * 0.5f;
    middle[1] = *(f32 *)(arg0 + 0x38) + delta[1] * 0.5f;
    middle[2] = *(f32 *)(arg0 + 0x3C) + delta[2] * 0.5f;
    view[0] = middle[0] - camera[0];
    view[1] = middle[1] - camera[1];
    view[2] = middle[2] - camera[2];
    func_150AD8B0(delta, view, side);
    x = side[0];
    y = side[1];
    z = side[2];
    lengthSquared = x * x + y * y + z * z;
    if (lengthSquared == 0.0f) {
        scale = 0.0f;
        side[0] = scale;
        side[1] = scale;
        side[2] = scale;
    } else {
        length = sqrtf(lengthSquared);
        scale = *(f32 *)(arg0 + 0x2C) / length;
        side[0] = x * scale;
        side[1] = y * scale;
        side[2] = z * scale;
    }
    vertices->x = *(f32 *)(arg0 + 0x34) - side[0];
    vertices->y = *(f32 *)(arg0 + 0x38) - side[1];
    vertices->z = *(f32 *)(arg0 + 0x3C) - side[2];
    vertices->s = *(f32 *)(arg0 + 0x114);
    vertices->flag = 0;
    vertices++;
    vertices->x = end[0] - side[0];
    vertices->y = end[1] - side[1];
    vertices->z = end[2] - side[2];
    vertices->s = *(f32 *)(arg0 + 0x110);
    vertices->flag = 0;
    vertices++;
    vertices->x = end[0] + side[0];
    vertices->y = end[1] + side[1];
    vertices->z = end[2] + side[2];
    vertices->s = *(f32 *)(arg0 + 0x110);
    vertices->flag = 0;
    vertices++;
    vertices->x = *(f32 *)(arg0 + 0x34) + side[0];
    vertices->y = *(f32 *)(arg0 + 0x38) + side[1];
    vertices->z = *(f32 *)(arg0 + 0x3C) + side[2];
    vertices->s = *(f32 *)(arg0 + 0x114);
    vertices->flag = 0;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D2D6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D2D6C.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

s32 func_150D317C(u8 *arg0) {
    u8 *temp_s0;

    *(f32 *)(arg0 + 0x128) += *(f32 *)(arg0 + 0x130) * D_800BE9A4;
    *(f32 *)(arg0 + 0x12C) += *(f32 *)(arg0 + 0x134) * D_800BE9A4;
    temp_s0 = (void *)(arg0 + 0x110);
    *(f32 *)((u8 *)temp_s0 + 0x18) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x128));
    *(f32 *)((u8 *)temp_s0 + 0x1C) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x1C));
    *(f32 *)temp_s0 = *(f32 *)(temp_s0 + 8) + *(f32 *)(temp_s0 + 0x10) * func_15047D60(*(f32 *)(temp_s0 + 0x18));
    *(f32 *)((u8 *)temp_s0 + 4) = *(f32 *)(temp_s0 + 0xC) + *(f32 *)(temp_s0 + 0x14) * func_15047D60(*(f32 *)(temp_s0 + 0x1C));
    *(f32 *)((u8 *)temp_s0 + 0x28) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x28) - D_800BE9A4);
    *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (u32) (*(f32 *)((u8 *)temp_s0 + 0x28) * *(f32 *)((u8 *)temp_s0 + 0x2C));
    if (*(f32 *)((u8 *)temp_s0 + 0x28) > 0.0f) {
        return 1;
    }
    return 0;
}
typedef struct {
    s32 field_0;
    u8 pad_4[0xC];
    u8 field_10[0x41];
    u8 field_51;
} GameFFBA0Child;

typedef struct {
    u8 pad_0;
    u8 field_1;
    u8 pad_2[0xA];
    u8 field_C;
    u8 pad_D[0x1B];
    GameFFBA0Child child;
} GameFFBA0State;

void func_150D278C(s32, void *, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D32FC CURRENT (110) */
void func_150D32FC(GameFFBA0State *arg0, u8 *arg1, u8 arg2) {
    GameFFBA0Child *child = &arg0->child;

    if (arg2 == 0x34 && *arg1 == child->field_51) {
        func_150D278C(child->field_0, child->field_10, arg0->field_C, arg0->field_1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D32FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D32FC.s")
