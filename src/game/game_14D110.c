#include "types.h"

/*
 * Reviewed source unit: src/game/game_14D110.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511FC60
 * - func_15120158
 * - func_15121490
 * - func_151218C4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_1511FC60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_15120158.s")
typedef struct {
    f32 x, y, z;
} Game14D110Vector;

typedef struct {
    u8 pad0[0x78];
    u8 kind;
    u8 pad79[0x9B];
    s16 height;
    u8 pad116[0x1A];
    Game14D110Vector direction, origin, destination;
    u8 pad154[0x18];
    f32 pitch, yaw;
    u8 pad174[0x24];
    u8 active;
} Game14D110Aim;

typedef struct {
    u8 pad0[0x14];
    Game14D110Vector position;
    u8 pad20[0x10];
    f32 groundY;
    u8 pad34[0xC];
    f32 angle;
    u8 pad44[0x2D8];
    Game14D110Aim *aim;
} Game14D110Actor;

f32 func_15047D60(f32);
f32 func_15047C00(f32);
extern f32 D_800A3408, D_800A340C, D_800A3410, D_800A3414, D_800A3418;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15121490 CURRENT (1407) */
void func_15121490(Game14D110Actor *arg0, u16 *arg1) {
    Game14D110Vector destination;
    Game14D110Vector origin;
    Game14D110Vector direction;
    f32 intermediate;
    f32 angle;
    f32 value;
    Game14D110Aim *aim;
    u8 kind;

    arg0->aim->active = 0;
    if ((*arg1 & 0x10) &&
        ((aim = arg0->aim, kind = aim->kind, kind == 9) ||
         kind == 0x38 || kind == 0x39 || kind == 0x37 ||
         kind == 0x3B || kind == 0x15 || kind == 0x26 || kind == 0x3A)) {
        destination.x = arg0->position.x;
        angle = (arg0->angle - 90.0f) * D_800A3408;
        destination.y = arg0->position.y + (f32)aim->height * 0.75f;
        destination.z = arg0->position.z;
        origin = destination;
        value = func_15047D60(angle) * 100.0f;
        destination.y = origin.y;
        destination.x = value + origin.x;
        destination.z = func_15047C00(angle) * 100.0f + origin.z;
        origin.y += arg0->position.y - arg0->groundY;
        aim->origin = origin;
        aim->destination = destination;
        aim->active = 1;
        direction.x = 1.0f;
        intermediate = func_15047C00(aim->yaw * D_800A340C) * direction.x;
        value = func_15047D60(aim->yaw * D_800A3410) * direction.x;
        direction.x = intermediate;
        direction.y = value;
        intermediate = func_15047C00(aim->pitch * D_800A3414) * direction.x;
        value = func_15047D60(aim->pitch * D_800A3418) * direction.x;
        direction.x = intermediate;
        direction.z = value;
        aim->direction = direction;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15121490 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_15121490.s")
extern s32 D_800BE9F0;

void func_151216F8(void *arg0) {
    s32 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0x23E);
    if (temp_v0 != 0) {
        if (temp_v0 == 0x34) {
            *(f32 *)((u8 *)arg0 + 0x190) = 80.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 350.0f;
            return;
        }
        if ((temp_v0 == 0x3B) && ((D_800BE9F0 == 0x41) || (D_800BE9F0 == 0x3C))) {
            *(f32 *)((u8 *)arg0 + 0x190) = -12.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = -28.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 106.0f;
            return;
        }
        if ((temp_v0 == 2) || (temp_v0 == 0xA) || (temp_v0 == 0x13)) {
            *(f32 *)((u8 *)arg0 + 0x190) = 10.0f;
            *(s32 *)((u8 *)arg0 + 0x84) = (s32) (*(s32 *)((u8 *)arg0 + 0x84) | 0x80);
            *(f32 *)((u8 *)arg0 + 0x784) = 135.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if ((temp_v0 == 0x12) && (D_800BE9F0 == 0x3C)) {
            *(f32 *)((u8 *)arg0 + 0x190) = 10.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 180.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if (temp_v0 == 0xF) {
            *(f32 *)((u8 *)arg0 + 0x190) = 10.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 480.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if (temp_v0 == 0x38) {
            *(f32 *)((u8 *)arg0 + 0x784) = 110.0f;
            *(f32 *)((u8 *)arg0 + 0x190) = 5.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if (temp_v0 == 0x15) {
            *(f32 *)((u8 *)arg0 + 0x784) = 110.0f;
            *(f32 *)((u8 *)arg0 + 0x190) = 25.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        *(f32 *)((u8 *)arg0 + 0x190) = 5.0f;
        *(f32 *)((u8 *)arg0 + 0x784) = 75.0f;
        *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
        return;
    }
    *(f32 *)((u8 *)arg0 + 0x784) = 90.0f;
    *(f32 *)((u8 *)arg0 + 0x190) = 25.0f;
    *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
}
void func_1506160C(u8 *, s32, s32, s32, u8);
void func_151C9ED4(void *);

typedef struct {
    u8 pad0[0x2C];
    f32 field2C;
    u8 pad30[0x1C];
    s8 field4C;
} Game14D110State;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151218C4 CURRENT (1215) */
void func_151218C4(void *arg0) {
    Game14D110State *temp_v0;

    if (!(**(u16 **)((u8 *)arg0 + 0x36C) & 0x10)) {
        if (*(s32 *)((u8 *)arg0 + 0x34) == 0x40) {
            if (*(s32 *)((u8 *)arg0 + 0x6FC) == 0xF) {
                *(f32 *)((u8 *)arg0 + 0x898) = 0.0f;
                *(f32 *)((u8 *)arg0 + 0x89C) = 0.0f;
            }
            *(s8 *)(*(u8 **)((u8 *)arg0 + 0x3D4) + 0x198) = 0;
            *(s16 *)((u8 *)arg0 + 0x73C) = 0;
            *(s16 *)((u8 *)arg0 + 0x84A) = 0x3C;
        } else {
            *(s16 *)((u8 *)arg0 + 0x84A) = 0x3C;
            *(s16 *)((u8 *)arg0 + 0x73C) = 3;
        }
        temp_v0 = (Game14D110State *)((u8 *)arg0 + 0x740);
        *(f32 *)((u8 *)arg0 + 0x374) = 200.0f;
        *(f32 *)((u8 *)arg0 + 0x348) = 100.0f;
        *(s32 *)((u8 *)arg0 + 0x134) = (s32)temp_v0->field2C;
        temp_v0->field4C = 0;
        *(f32 *)((u8 *)arg0 + 0x190) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x198) = 0.0f;
        func_1506160C(*(u8 **)((u8 *)arg0 + 0x3D0), 2, 0xFF, 0x20,
                      *(u8 *)((u8 *)arg0 + 0x23D));
        if (*(u8 *)((u8 *)arg0 + 0x84C) != 0) {
            func_151C9ED4(arg0);
            *(u8 *)((u8 *)arg0 + 0x84C) = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151218C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_151218C4.s")
