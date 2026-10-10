#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_F52B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C7E00
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad00[0x14];
    f32 x, y, z;
    u8 pad20[0x45];
    u8 active;
} GameF52B0Actor;
typedef struct {
    u8 pad00[0x2C]; s32 mode;
    u8 pad30[0x54]; s32 flags;
    u8 pad88[0xAC]; s32 player;
    u8 pad138[0x58]; f32 distance;
    u8 pad194[0x20]; s16 state;
    u8 pad1B6[0x192]; f32 rangeA, rangeB;
    u8 pad350[0x1C]; u16 *buttons;
    u8 pad370[4]; f32 height;
    u8 pad378[0x58]; GameF52B0Actor *actor;
    u8 *stateData;
    u8 pad3D8[0x218]; s32 flags5F0;
    u8 pad5F4[0x7C]; f32 current, target;
    u8 pad678[0x50]; s32 locked;
    u8 pad6CC[0x70]; s16 state73C;
} GameF52B0Camera;
void func_15123070(void *);
void func_151254F4(void *, s32);
void func_15124B18(void *);
GameF52B0Actor *func_15083E90(s32);
s32 func_1509BE40(s32, s32, s32, ...);
void func_1509BFB0(s32, s32, s32, ...);
extern s32 D_80088800;
extern f32 D_800A04E0, D_800A04E4;
extern u8 D_800CC335;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C7E00 CURRENT (640) */
void func_150C7E00(GameF52B0Camera *arg0) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 none = -1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fa0;
    f32 var_fv1;
    GameF52B0Actor *temp_v0;
    GameF52B0Actor *temp_v1;

    sp34 = func_1509BE40(0, func_1509BE40(0, 0x2010, 0xB7) | 0x2000, 0xBC);
    sp30 = func_1509BE40(0, 0x2000, 0xBB);
    sp2C = func_1509BE40(0, func_1509BE40(0, 0x2010, 0xB7) | 0x2000, 0xBB);
    if (func_1509BE40(0, 0x5071, 0x1A) == 0) {
        if ((sp30 != none) && (sp34 == 0)) {
            if (func_15123934(arg0, arg0->mode, 0, arg0->player, 3) != 0) {
                arg0->flags = (s32) (arg0->flags | 0x01000000);
                func_151254F4(arg0, D_800CC335 - 1);
                arg0->target = 0.0f;
            }
        } else {
            if ((sp30 != none) && (sp34 != 0)) {
                func_151239CC(arg0, 2);
                if (func_15123934(arg0, 8, 0, arg0->player, 3) != 0) {
                    func_151254F4(arg0, D_800CC335 - 1);
                    arg0->flags = (s32) (arg0->flags & ~4);
                    arg0->target = 0.0f;
                    func_15123070(arg0);
                }
                arg0->flags5F0 = (s32) (arg0->flags5F0 | 0x200);
                arg0->rangeA = 500.0f;
                arg0->rangeB = 500.0f;
                arg0->height = 800.0f;
                return;
            }
            if (func_151239CC(arg0, 3) != 0) {
                func_151254F4(arg0, 0);
                arg0->flags = (s32) (arg0->flags & 0xFEFFFFFF);
                arg0->stateData[0x198] = 0;
                arg0->state73C = 0;
                if (arg0->locked == 0) {
                    arg0->target = 0.0f;
                }
            }
            arg0->flags5F0 = (s32) (arg0->flags5F0 & ~0x200);
        }
    } else {
        if (func_1509BE40(0, 0x5072, 0x1A) == 0) {
            if (*arg0->buttons & 4) {
                arg0->distance = 20.0f;
            }
            if (func_1509BE40(0, 0x2000, 0x93) == 0) {
                arg0->distance = 0.0f;
                return;
            }
            func_1509BFB0(1, 0x9000, 0x17, func_1509BE40(1, func_1509BE40(0, 0x2011, 0xB7) | 0x2000, 0x9C, 0x2000));
            temp_fv0 = ((f32) func_1509BE40(1, func_1509BE40(0, 0x2011, 0xB7) | 0x2000, 0x9A, 0x2000) - 300.0f) / 900.0f;
            if (temp_fv0 < 0.0f) {
                var_fv1 = 0.0f;
            } else {
                if (temp_fv0 > 1.0f) {
                    var_fa0 = 1.0f;
                } else {
                    var_fa0 = temp_fv0;
                }
                var_fv1 = var_fa0;
            }
            if (sp34 == 0) {
                arg0->rangeB = 200.0f;
                arg0->rangeA = 200.0f;
                arg0->distance = 100.0f;
            } else {
                arg0->distance = (f32) ((103.0f * var_fv1) + D_800A04E0);
                temp_fv0_2 = 231.0f * var_fv1;
                arg0->height = (f32) ((224.0f * var_fv1) + D_800A04E4);
                arg0->rangeB = temp_fv0_2;
                arg0->rangeA = temp_fv0_2;
            }
            func_1509BFB0(2, 0x9000, 6, 1, 0x20000);
            func_1509BFB0(2, 0x9000, 6, 0, 4);
            if (sp2C != none) {
                arg0->current = 0.0f;
            }
            D_80088800 = 0;
            if (arg0->flags5F0 & 4) {
                temp_v0 = func_15083E90(0x10);
                if (temp_v0 != 0) {
                    temp_v1 = arg0->actor;
                    if (temp_v1->active != 0) {
                        temp_v1->x = (f32) temp_v0->x;
                        arg0->actor->y = (f32) temp_v0->y;
                        arg0->actor->z = (f32) temp_v0->z;
                    }
                }
            }
            if (func_151239CC(arg0, 3) != 0) {
                arg0->flags5F0 = (s32) (arg0->flags5F0 & ~0x200);
                func_151254F4(arg0, 0);
                arg0->flags = (s32) (arg0->flags & 0xFEFFFFFF);
                arg0->stateData[0x198] = 0;
                arg0->state73C = 0;
                if (arg0->locked == 0) {
                    arg0->target = 0.0f;
                }
            }
        } else if ((func_151239CC(arg0, 3) != 0) || (D_80088800 == 0)) {
            arg0->flags = (s32) (arg0->flags | 4);
            D_80088800 = 1;
            func_151254F4(arg0, 0);
            arg0->stateData[0x198] = 0;
            arg0->state73C = 0;
            arg0->state = 3;
            func_15124B18(arg0);
            arg0->distance = 0.0f;
            if (arg0->locked == 0) {
                arg0->target = 0.0f;
            }
        }
        if (*arg0->buttons & 4) {
            arg0->distance = 0.0f;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C7E00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F52B0/func_150C7E00.s")
