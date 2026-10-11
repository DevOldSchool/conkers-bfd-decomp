#include "types.h"

/*
 * Reviewed source unit: src/game/game_63A20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15036570
 * - func_150368C4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
extern f32 D_80097D80;
extern u8 D_800C3FC0[];
extern u8 D_800C3FC4[];
extern u8 D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15036570 CURRENT (7700) */
void func_15036570(s32 index, void *firstTransform, void *secondTransform) {
    f32 x;
    f32 y;
    f32 z;
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    u8 *model;
    f32 oldX;
    f32 oldY;
    f32 oldZ;
    u8 *position;
    f32 blend;

    position = D_800CC2D0 + index * 0x32C;
    blend = *(f32 *)(*(u8 **)(position + 0x2D0) + 8);
    model = *(u8 **)(D_800C3FC0 + index * 4);
    if (*(u16 *)(position + 0x84) == 0x3E || *(u16 *)(position + 0x84) == 0x41 ||
        (*(u16 *)(position + 0x84) == 0x138 && blend >= 36.0f) ||
        ((*(u16 *)(position + 0x84) == 0x3D || *(u16 *)(position + 0x84) == 0xD9) && blend > 21.0f)) {
        func_150A7960(firstTransform, -7.0f, -17.0f, -7.0f, &x, &y, &z);
        position = D_800C3FC4 + index * 6;
        *(s16 *)(position + 0x0) = (s32)x;
        *(s16 *)(position + 0x2) = (s32)y;
        *(s16 *)(position + 0x4) = (s32)z;
    } else {
        if (((*(u16 *)(position + 0x84) == 0x3D || *(u16 *)(position + 0x84) == 0xD9) && blend > 7.0f) ||
            *(u16 *)(position + 0x84) == 0x138 || *(u16 *)(position + 0x84) == 0x139) {
            blend = 1.0f;
        } else {
            blend = D_80097D80;
        }
        x = (*(s16 *)(model + 0x30) + *(s16 *)(model + 0x20)) * 0.5f;
        y = (*(s16 *)(model + 0x32) + *(s16 *)(model + 0x22)) * 0.5f;
        z = (*(s16 *)(model + 0x34) + *(s16 *)(model + 0x24)) * 0.5f;
        func_150A7960(secondTransform, x, y, z, &targetX, &targetY, &targetZ);
        position = D_800C3FC4 + index * 6;
        oldX = *(s16 *)(position + 0x0);
        oldY = *(s16 *)(position + 0x2);
        oldZ = *(s16 *)(position + 0x4);
        *(s16 *)(position + 0x0) = (s32)(oldX + (targetX - oldX) * blend);
        *(s16 *)(position + 0x2) = (s32)(oldY + (targetY - oldY) * blend);
        *(s16 *)(position + 0x4) = (s32)(oldZ + (targetZ - oldZ) * blend);
        x = *(s16 *)(position + 0x0);
        y = *(s16 *)(position + 0x2);
        z = *(s16 *)(position + 0x4);
    }
    *(s16 *)(model + 0x0) = (s32)x;
    *(s16 *)(model + 0x2) = (s32)y;
    *(s16 *)(model + 0x4) = (s32)z;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15036570 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_63A20/func_15036570.s")
typedef struct Game368C4State {
    u8 pad0[0x66];
    u8 mode;
    u8 pad67[0x16D];
    u8 *transforms;
    u8 pad1D8[0x129];
    u8 lighting0, lighting1;
    u8 pad303;
    s32 lights[4];
    u8 *lightData;
    u8 pad318[4];
    u8 *model;
} Game368C4State;

void *func_1503195C(void *, s32, s32);
void func_15036570(s32, void *, void *);
s32 func_1515E544(s32, s32, s32, s32, void *);
struct GameC2350Input;
struct GameC2350Owner;
s32 func_15094F70(s32, struct GameC2350Input *, s32, struct GameC2350Owner *, s32, s32, s32, s32, s32);
extern u8 D_80084350[], D_80089470[], D_800903BC[];
extern u8 D_800BE9C0;
extern s32 D_800DCD7C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150368C4 CURRENT (1356) */
u32 *func_150368C4(u32 *arg0, s32 arg1, s32 arg2) {
    u8 *effect;
    Game368C4State *state;
    u8 *colors;
    s32 index;
    s32 mode;
    u8 **vertices;
    u8 *transform;

    state = (Game368C4State *)(D_800CC2D0 + arg1 * 0x32C);
    if (state->model[0x75] != 2 && state->model[0x75] != 0x13) {
        return arg0;
    }
    effect = func_1503195C(state, 8, 0);
    if (effect == NULL) {
        return arg0;
    }
    if (arg1 > 0) {
        return arg0;
    }
    colors = *(u8 **)(effect + 0x28 + D_800BE9C0 * 4) + 0x300;
    vertices = (u8 **)(D_800C3FC0 + arg1 * 4);
    for (index = 0; index < 5; index++) {
        (*vertices)[index * 0x10 + 0xC] = colors[0xC];
        (*vertices)[index * 0x10 + 0xD] = colors[0xD];
        (*vertices)[index * 0x10 + 0xE] = colors[0xE];
    }
    if (state->transforms == NULL) {
        return arg0;
    }
    transform = state->transforms + 0x100;
    func_15036570(arg1, state->transforms + 0x240, transform);
    {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0xDE000000;
        packet[1] = (u32)D_80084350;
    }
    arg0 = (u32 *)func_1515E544((s32)arg0, state->lights[arg2], state->lighting0,
                              state->lighting1, state->lightData + D_800BE9C0 * 8);
    mode = state->mode & 0xC;
    if (mode == 0xC) {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0xD9FDFFFF;
        packet[1] = 0;
    } else if (mode != 8 && !(effect[4] & 1)) {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0xD9FDFFFF;
        packet[1] = 0;
    } else if (D_800DCD7C != 0) {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0xD9FFFFFF;
        packet[1] = 0x20000;
    } else {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0xD9FDFFFF;
        packet[1] = 0;
    }
    arg0 = (u32 *)func_15094F70((s32)arg0, (struct GameC2350Input *)D_800903BC, 0, NULL, 0, 0, 0, 2, 3);
    {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0xDA380003;
        packet[1] = (u32)D_80089470;
    }
    {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0x01001002;
        packet[1] = (u32)*vertices;
    }
    {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0xDA380003;
        packet[1] = (u32)transform;
    }
    {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0x0100400A;
        packet[1] = (u32)(*vertices + 0x10);
    }
    {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0x05000204;
        packet[1] = 0;
    }
    {
        u32 *packet = arg0;
        arg0 += 2;
        packet[0] = 0x05000608;
        packet[1] = 0;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150368C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_63A20/func_150368C4.s")
