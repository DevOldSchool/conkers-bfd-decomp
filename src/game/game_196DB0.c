#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_196DB0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15169A48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game196DB0Effect {
    u8 pad0[0x10];
    u8 payload[0x3C];
} Game196DB0Effect;

void func_10023A10(void *, void *, s32);

Game196DB0Effect *func_15169900(void *arg0, s32 arg1) {
    Game196DB0Effect *effect;

    effect = func_15167A68(0x5E, 0, 0x4C, 0, arg1, 1);
    if (effect != 0) {
        func_10023A10(arg0, effect->payload, sizeof(effect->payload));
    }
    return effect;
}

void *func_15169968(void *arg0) {
    return func_15169900(arg0, 0xFF);
}
extern void (*D_8008CA20[])(void);
extern s32 D_800BE9E4;

void func_15169988(void *arg0) {
    s32 temp_v1;
    s32 var_v0;
    s32 temp_t1;
    s8 temp_v0;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x40);
    if (temp_v0 != 0) {
        D_8008CA20[(s32)temp_v0]();
    }
    var_v0 = *(s16 *)((u8 *)arg0 + 0x26);
    var_v0 += *(s16 *)((u8 *)arg0 + 0x28) * (u32)D_800BE9E4;
    temp_t1 = *(u8 *)((u8 *)arg0 + 0x41) << 8;
    if (var_v0 >= temp_t1) {
        var_v0 -= temp_t1;
    } else if (var_v0 < 0) {
        var_v0 += temp_t1;
    }
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x24);
    *(s16 *)((u8 *)arg0 + 0x26) = var_v0;
    if (temp_v1 != 0) {
        temp_v1 -= D_800BE9E4;
        if (temp_v1 <= 0) {
            func_1516972C(arg0);
            return;
        }
        *(s16 *)((u8 *)arg0 + 0x24) = temp_v1;
    }
}
typedef struct Game196DB0RenderEffect {
    u8 pad0[0x10];
    void *image;
    void *palette;
    u8 pad18[0xE];
    s16 frame;
    u8 pad28[4];
    f32 x;
    f32 y;
    s16 scale_s;
    s16 scale_t;
    s16 width;
    s16 height;
    u16 start_s;
    u16 start_t;
    u8 pad40[2];
    u8 red, green, blue, alpha;
    u8 mode, material, blend, flags;
} Game196DB0RenderEffect;

s32 *func_1513F4E4(s32 *, u8, u8 *);
void *func_15142FBC(void *, s32, s32, u8 *);
s32 func_15094F70(s32, void *, s32, void *, s32, s32, s32, s32, s32);
s32 *func_1509629C(void *, void *, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32);
extern s32 D_800A4AC8[][2];
extern s32 D_800D2C9C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15169A48 CURRENT (2636) */
s32 *func_15169A48(s32 *arg0, Game196DB0RenderEffect *arg1, s32 arg2) {
    s32 flags;
    u8 state;
    s32 offset;
    s32 blend;
    s32 *mode;
    s32 *packet;
    s32 *depth_packet;

    if ((arg1->width == 0) || (arg1->height == 0)) {
        return arg0;
    }
    state = 1;
    packet = func_1513F4E4(arg0, arg1->material, &state);
    packet[0] = 0xFA000100;
    packet[1] = ((u32)arg1->red << 24) | ((u32)arg1->green << 16) | ((u32)arg1->blue << 8) | (u32)arg1->alpha;
    arg0 = packet + 2;
    if (arg1->flags & 1) {
        if (arg1->flags & 2) {
            offset = (arg1->scale_s * 4) >> 5;
        } else {
            offset = 0;
        }
        arg0 = (s32 *)func_15094F70((s32)arg0, arg1->palette, 0, 0, 0x100, 1, offset, 2, 3);
    }
    if (arg1->flags & 0x10) {
        flags = 1;
    } else {
        flags = 0;
    }
    if (arg1->flags & 4) {
        flags |= 2;
    }
    if (arg1->flags & 8) {
        flags |= 4;
    }
    if (arg1->flags & 0x20) {
        depth_packet = arg0;
        arg0 += 2;
        depth_packet[0] = 0xEE000000;
        depth_packet[1] = 0x795A0000;
    }
    if (arg1->blend == 2) {
        blend = 0x100000;
    } else {
        blend = 0;
    }
    mode = D_800A4AC8[arg1->mode];
    arg0 = func_15142FBC(arg0, blend | D_800D2C9C | 0x2CA0,
                          mode[1] | mode[0] | 4, &state);
    return func_1509629C(arg0,
                         arg1->image, (f32)arg1->width, (f32)arg1->height,
                         arg1->x, arg1->y, arg1->start_s, arg1->start_t,
                         flags, arg1->scale_s, arg1->scale_t, arg1->frame >> 8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15169A48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_196DB0/func_15169A48.s")
