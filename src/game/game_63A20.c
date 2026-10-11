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
#pragma GLOBAL_ASM("asm/nonmatchings/game_63A20/func_150368C4.s")
