#include "types.h"

/*
 * Reviewed source unit: src/game/game_7F710.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15052260
 * - func_15052490
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game7F710MotionController {
    u8 pad0[0x6B];
    u8 mode;
    s16 targetX;
    s16 targetY;
    s16 targetZ;
} Game7F710MotionController;

typedef struct Game7F710MotionObject {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    f32 speed;
    f32 field24;
    f32 timer;
    u8 pad2C[0x57];
    s8 field83;
    u8 pad84[0x29];
    s8 fieldAD;
    u8 padAE[0x6A];
    f32 threshold;
    u8 pad11C[0xB0];
    f32 cachedY;
    u8 pad1D0[0x14C];
    Game7F710MotionController *controller;
} Game7F710MotionObject;

void func_1505E650(Game7F710MotionObject *, s32, f32, f32, f32, f32, s32);
void func_1505A770(Game7F710MotionObject *);
extern f32 D_8009933C;
extern f32 D_80099340;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15052260 CURRENT (30) */
void func_15052260(Game7F710MotionObject *arg0) {
    Game7F710MotionController *controller;
    f32 factor;
    f32 oldY;
    f32 oldX;
    f32 oldZ;

    controller = arg0->controller;
    if (controller->mode == 1 || controller->mode == 3) {
        factor = D_8009933C;
    } else {
        factor = 1.0f;
    }
    oldY = arg0->y;
    arg0->cachedY = oldY;
    if (controller->mode < 4) {
        oldX = arg0->x;
        oldZ = arg0->z;
        arg0->x = oldX + ((f32)controller->targetX - oldX) * factor;
        arg0->y = oldY + ((f32)(controller->targetY - 0x50) - oldY) * factor;
        arg0->z = oldZ + ((f32)controller->targetZ - oldZ) * factor;
        func_1505E650(arg0, 0x14, 1.0f, 6.0f, 0.0f, 0.0f, 0);
        arg0->speed = -10.0f;
    } else {
        if ((s32)arg0->timer == 0) {
            controller->mode = 0;
        } else {
            func_1505E650(arg0, 0x38, 1.0f, 6.0f, 0.0f, 0.0f, 0);
        }
        func_1505A770(arg0);
    }
    arg0->field24 = D_80099340;
    if (arg0->y < arg0->threshold) {
        arg0->field24 = 0.0f;
        arg0->speed = 0.0f;
        arg0->controller->mode = 0;
        arg0->field83 = 0;
        arg0->fieldAD = 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15052260 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_7F710/func_15052260.s")
typedef struct {
    u8 pad_0[0x95];
    s8 field_95;
} Game7F710Nested;

typedef struct {
    u8 pad_0[0x24];
    f32 field_24;
    u8 pad_28[0x14];
    f32 field_3C;
    u8 pad_40[0x41];
    s8 field_81;
    u8 pad_82[1];
    s8 field_83;
    u8 pad_84[5];
    s8 field_89;
    u8 pad_8A[0x23];
    s8 field_AD;
    u8 pad_AE[4];
    s16 field_B2;
    u8 pad_B4[4];
    f32 field_B8;
    u8 pad_BC[0x10E];
    u8 field_1CA;
    u8 pad_1CB[0x151];
    Game7F710Nested *field_31C;
} Game7F710State;

void func_15052408(Game7F710State *arg0) {
    arg0->field_B2 = 0;
    arg0->field_31C->field_95 = 0;
    if (arg0->field_1CA != 0) {
        arg0->field_81 = 0;
        arg0->field_83 = 0;
        arg0->field_89 = 6;
    }
    arg0->field_AD = 0;
    arg0->field_24 = 4.0f;
    arg0->field_B8 = 0.0f;
    arg0->field_3C = 15.0f;
}
void func_15052458(s32 arg0) {

}
void func_15060F28(u8 *arg0, s32 arg1);

void func_15052464(u8 *arg0) {
    if (arg0[0x1CA] == 0) {
        func_15060F28(arg0, 1);
    }
}
extern f32 D_800D1550;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15052490 CURRENT (420) */
void func_15052490(void *arg0, s32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fa0;
    u16 temp_v0;

    temp_v0 = *(u16 *)((u8 *)arg0 + 0x7A);
    temp_fa0 = arg3 * D_800D1550;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (temp_v0 + 0x4000) * 0.005493164f);
    if ((((arg1 & 0xFFFF) - temp_v0) + 0x4000) & 0x8000) {
        *(f32 *)((u8 *)arg0 + 0xB8) = (f32) (*(f32 *)((u8 *)arg0 + 0xB8) - (arg2 * temp_fa0));
        return;
    }
    *(f32 *)((u8 *)arg0 + 0xB8) = (f32) (*(f32 *)((u8 *)arg0 + 0xB8) + (arg2 * temp_fa0));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15052490 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_7F710/func_15052490.s")
void func_1505250C(void *arg0, s32 arg1) {
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0xCE);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0xCC);
    if (temp_v0 != temp_v1) {
        if (temp_v1 < temp_v0) {
            *(s16 *)((u8 *)arg0 + 0xCC) = (s16) (temp_v1 + ((s32) (temp_v0 - temp_v1) / 12) + 1);
            if (temp_v0 < *(s16 *)((u8 *)arg0 + 0xCC)) {
                *(s16 *)((u8 *)arg0 + 0xCC) = temp_v0;
            }
        } else {
            *(s16 *)((u8 *)arg0 + 0xCC) = (s16) ((temp_v1 + ((s32) (temp_v0 - temp_v1) / 12)) - 1);
            if (*(s16 *)((u8 *)arg0 + 0xCC) < temp_v0) {
                *(s16 *)((u8 *)arg0 + 0xCC) = temp_v0;
            }
        }
    }
}
