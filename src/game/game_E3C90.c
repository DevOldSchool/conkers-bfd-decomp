#include "types.h"

/*
 * Reviewed source unit: src/game/game_E3C90.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B67E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[0x65];
    u8 camera;
} ScriptCameraOwner;

typedef struct {
    u8 pad0[0x2C];
    s32 mode;
    u8 pad30[0x54];
    s32 flags;
    u8 pad88[0xAC];
    s32 field134;
    u8 pad138[0x58];
    f32 angle;
    u8 pad194[0x20];
    s16 state;
    u8 pad1B6[0x86];
    s8 locked;
    u8 camera;
    u8 pad23E[0x10A];
    f32 heightA;
    f32 heightB;
    u8 pad350[0x1C];
    u16 *settings;
    u8 pad370[0x4];
    f32 scale;
    u8 pad378[0x58];
    ScriptCameraOwner *owner;
    u8 pad3D4[0x21C];
    s32 scriptFlags;
    u8 pad5F4[0x80];
    f32 field674;
} ScriptCameraActor;

s32 func_1509BE40(s32 count, ...);
void func_1509BFB0(s32 count, ...);
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);
void func_15124B18(void *);
void func_151254F4(void *, s32);
extern s32 D_80088710;
extern f32 D_8009FCF0;
extern f32 D_8009FCF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B67E0 CURRENT (290) */
void func_150B67E0(ScriptCameraActor *arg0) {
    s32 temp_s0;
    s32 temp_v0;
    s32 var_s0;

    if (func_1509BE40(0, 0x503C, 0x1A) == 0) {
        if (func_15123934(arg0, arg0->mode, 0, 0, 0) != 0) {
            arg0->flags |= 0x20000;
            arg0->flags &= ~4;
            arg0->state = 3;
            func_15124B18(arg0);
            arg0->locked = 1;
        }
        arg0->scale = (f32) D_8009FCF0;
        arg0->heightA = 450.0f;
        arg0->heightB = 450.0f;
    } else {
        func_1509BFB0(0, 0x4000, 0);
        if ((arg0->mode == 1) && (func_151239CC(arg0, 0) != 0)) {
            arg0->state = 2;
            func_15124B18(arg0);
        }
        if (func_1509BE40(1, 0x4024, 6, 0x2000) != 0) {
            D_80088710 = 0x9003;
        } else if (func_1509BE40(1, 0x4025, 6, 0x2000) != 0) {
            D_80088710 = 0x9009;
        } else if (func_1509BE40(1, 0x4026, 6, 0x2000) != 0) {
            D_80088710 = 0x900A;
        } else if (func_1509BE40(1, 0x4027, 6, 0x2000) != 0) {
            D_80088710 = 0x900B;
        }
        if (D_80088710 != 0x3E7) {
            func_1509BFB0(5, 0x4000, 4, 2, 0, D_80088710 & 0xFFF, 0, 0);
        }
        var_s0 = 0;
        do {
            if ((func_1509BE40(1, var_s0 + 0x400C, 6, 0x2000) != 0) || (func_1509BE40(1, 0x4014, 6, 0x2000) != 0)) {
                func_1509BFB0(1, 0x2000, 0x3B, 2);
            }
            var_s0 += 1;
        } while (var_s0 != 3);
        if (func_1509BE40(1, 0x4000, 6, 0x2000) != 0) {
            func_1509BFB0(2, 0x9000, 6, 1, 0x80000);
            func_1509BFB0(1, 0x9000, 0x10, 0x55);
        } else {
            func_1509BFB0(2, 0x9000, 6, 0, 0x80000);
            func_1509BFB0(1, 0x9000, 0x10, 0);
        }
    }
    temp_s0 = func_1509BE40(0, func_1509BE40(0, 0x200A, 0xB7) | 0x2000, 0xBC);
    temp_v0 = func_1509BE40(0, 0x2000, 0xBB);
    if ((temp_s0 != 0) && (temp_v0 != -1)) {
        arg0->scriptFlags = (s32) (arg0->scriptFlags | 0x100);
    } else {
        arg0->scriptFlags = (s32) (arg0->scriptFlags & ~0x100);
    }
    if ((temp_s0 != 0) && (temp_v0 != -1)) {
        if (func_15123934(arg0, arg0->mode, 0, 0, 3) != 0) {
            arg0->flags = (s32) (arg0->flags | 0x100002);
            arg0->field674 = 0.0f;
            func_151254F4(arg0, arg0->owner->camera - 1);
            arg0->field134 = 0;
        }
        arg0->heightB = 450.0f;
        arg0->heightA = 450.0f;
        arg0->scale = (f32) D_8009FCF4;
        if (*arg0->settings & 4) {
            arg0->angle = 0.0f;
            return;
        }
        arg0->angle = 135.0f;
        return;
    }
    if (func_151239CC(arg0, 3) != 0) {
        func_151254F4(arg0, (s32) arg0->camera);
        arg0->field674 = 0.0f;
        arg0->angle = 0.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B67E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E3C90/func_150B67E0.s")
