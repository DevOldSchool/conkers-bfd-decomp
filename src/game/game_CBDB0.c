#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_CBDB0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509E900
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_CBDB0/func_1509E900.s")
typedef struct GameCBDB0Object {
    u8 pad0[8];
    f32 x;
    u8 padC[4];
    s16 field10, field12, field14;
    u8 pad16[0x26];
    s32 field3C;
    u8 pad40[0xF];
    u8 flags4F;
    u8 pad50[0x1E];
    u8 field6E;
    u8 pad6F[4];
    u8 flags73;
    u8 pad74[8];
    s32 values[3];
} GameCBDB0Object;

typedef struct GameCBDB0Actor {
    s32 id;
    u8 pad4[0x328];
} GameCBDB0Actor;

typedef struct GameCBDB0Query {
    s32 args[3];
} GameCBDB0Query;

s32 func_15084000(s32);
s32 func_151140C4(GameCBDB0Object *);
s32 func_15114050(GameCBDB0Object *, s32);
extern GameCBDB0Actor D_800CC2D0[];

s32 func_1509ED74(s32 arg0, s32 arg1, GameCBDB0Query *arg2) {
    GameCBDB0Object *object;
    s32 i;
    s32 result;

    object = func_151149AC(arg0);
    if (object == NULL) {
        return 0;
    }
    switch (arg1) {
    case 19:
        return func_15114050(object, -1);
    case 20:
        return func_15114050(object, func_15084000(arg2->args[2] & 0xFFFF0FFF));
    case 21:
        for (i = 0; i < 25; i++) {
            if (D_800CC2D0[i].id == arg2->args[2] && func_15114050(object, i) != 0) {
                return 1;
            }
        }
        return 0;
    case 22:
        if ((object->flags4F & 4) == 4) {
            return 1;
        }
        return 0;
    case 23:
        result = func_151140C4(object);
        if (result < 0) {
            return 0;
        }
        return result | 0x2000;
    case 24:
        return object->flags4F;
    case 25:
        if (object->values[2] == object->values[0]) {
            return 1;
        }
        return 0;
    case 26:
        return object->field3C;
    case 27:
        return object->flags73 & 3;
    case 28:
        return object->field6E == 0;
    case 29:
        return object->field10;
    case 30:
        return object->field12;
    case 31:
        return object->field14;
    case 32:
        return object->x;
    case 33:
        if (arg2->args[2] == 0) {
            return object->values[0];
        }
        if (arg2->args[2] == 1) {
            return object->values[1];
        }
        if (arg2->args[2] == 2) {
            return object->values[2];
        }
        break;
    case 34:
        if (arg2->args[2] == 0) {
            return *(f32 *)&object->values[0];
        }
        if (arg2->args[2] == 1) {
            return *(f32 *)&object->values[1];
        }
        if (arg2->args[2] == 2) {
            return *(f32 *)&object->values[2];
        }
        break;
    case 35:
        return (object->flags73 & 4) != 0;
    }
    return 0;
}
