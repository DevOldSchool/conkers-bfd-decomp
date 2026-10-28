#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_15BD90.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512E8E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_15BD90/func_1512E8E0.s")
typedef struct Game15BD90Actor {
    u8 pad0[0x2C];
    s32 mode;
    u8 pad30[0x54];
    s32 flags;
    u8 pad88[0xAC];
    s32 field134;
    u8 pad138[0x58];
    f32 field190;
    u8 pad194[0x23C];
    struct CameraCameraTarget *target;
} Game15BD90Actor;

void func_1512FE00(Game15BD90Actor *arg0, s32 arg1) {
    switch (arg1) {
    case 1:
        func_15123934(arg0, arg0->mode, 0, 0, 7);
        break;
    case 2:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags &= ~8;
        break;
    case 3:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x10000000;
        break;
    case 8:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x80;
        break;
    case 9:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags &= ~8;
        arg0->flags |= 0x80;
        break;
    case 11:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x4000;
        break;
    case 12:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x8000;
        break;
    case 13:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x20000;
        break;
    case 16:
        func_15123934(arg0, 8, 0, arg0->field134, 7);
        break;
    case 14:
        func_15123934(arg0, 2, 0, arg0->field134, 7);
        break;
    case 18:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x100000;
        break;
    case 19:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x400000;
        break;
    case 21:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->field190 = 0.0f;
        break;
    case 22:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x800;
        arg0->field190 = -30.0f;
        break;
    case 25:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x40;
        break;
    case 23:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x01000000;
        break;
    case 24:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x80000000;
        break;
    case 26:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x10;
        break;
    case 27:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x20;
        break;
    case 28:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x10;
        arg0->flags &= ~8;
        break;
    case 29:
        func_15123934(arg0, arg0->mode, 0, arg0->field134, 7);
        arg0->flags |= 0x01000010;
        arg0->flags &= ~8;
        break;
    case 30:
        func_15128774((struct CameraCameraTargetState *)arg0, arg0->target);
        break;
    }
}
