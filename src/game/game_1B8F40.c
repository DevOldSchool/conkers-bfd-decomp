#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B8F40.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518BA90
 * - func_1518BBF4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1B8F40Node {
    u8 pad0[8];
    struct Game1B8F40Node *next;
    u8 padC[0x18];
    void *owner;
    u8 type;
} Game1B8F40Node;

extern u8 D_800DCE50[];
extern s8 D_800DD190;
extern Game1B8F40Node *D_800DD198[];
void func_1516972C(u8 *);

typedef struct Game1B8F40Effect {
    u8 pad0[0x2C];
    s32 field2C;
    s32 field30;
} Game1B8F40Effect;

extern f32 D_800A7434;
extern f32 D_800A7438;
extern f32 D_800A743C;
Game1B8F40Effect *func_1518BCD0(void *, u8, s32);

typedef struct Game1B8F40Spawn {
    f32 x;
    f32 y;
    f32 z;
    f32 scale;
    s16 field10;
    s16 field12;
    void *owner;
    u8 type;
    s8 field19;
    s8 field1A;
} Game1B8F40Spawn;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518BA90 CURRENT (145) */
Game1B8F40Effect *func_1518BA90(void *arg0, u8 arg1, s32 arg2) {
    Game1B8F40Spawn spawn;
    Game1B8F40Node *node;
    u8 *block;

    if (arg0 == 0) {
        return 0;
    }
    block = D_800DCE50;
    do {
        node = *(Game1B8F40Node **)(block + 0x7C);
        block += 0x1A0;
        while (node != 0) {
            if (node->owner == arg0 ||
                node->type == *(u8 *)((u8 *)arg0 + 0x3B)) {
                return (Game1B8F40Effect *)node;
            }
            node = node->next;
        }
    } while (block != (u8 *)&D_800DD190);

    switch (*(u8 *)((u8 *)arg0 + 4) + 1) {
    case 0:
        return 0;
    case 8:
        spawn.field12 = 0x37;
        spawn.field10 = 4;
        spawn.field19 = 5;
        spawn.field1A = 0x13;
        spawn.x = D_800A7434;
        spawn.y = D_800A7438;
        spawn.z = D_800A743C;
        spawn.scale = 5.0f;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        spawn.field12 = 0;
        spawn.field10 = 5;
        spawn.field19 = 5;
        spawn.field1A = 0x13;
        spawn.x = 10.0f;
        spawn.y = 10.0f;
        spawn.z = 10.0f;
        spawn.scale = 10.0f;
        break;
    default:
        return 0;
    }
    spawn.owner = arg0;
    spawn.type = *(u8 *)((u8 *)arg0 + 0x3B);
    return func_1518BCD0(&spawn, arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518BA90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B8F40/func_1518BA90.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518BBF4 CURRENT (685) */
void func_1518BBF4(void *arg0) {
    u8 *block;
    u8 *end;

    if (arg0 != 0) {
        block = D_800DCE50;
        end = (u8 *)&D_800DD190;
        do {
            Game1B8F40Node *node;

            node = *(Game1B8F40Node **)(block + 0x7C);
            D_800DD190 += 1;
            if (node != 0) {
                Game1B8F40Node **link;

                link = &D_800DD198[D_800DD190];
                do {
                    *link = node->next;
                    node->owner = arg0;
                    if ((arg0 != 0) ||
                        (*(u8 *)((u8 *)arg0 + 0x3B) == node->type)) {
                        func_1516972C((u8 *)node);
                    }
                    link = &D_800DD198[D_800DD190];
                    node = *link;
                } while (node != 0);
            }
            block += 0x1A0;
            D_800DD190 -= 1;
        } while (block != end);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518BBF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B8F40/func_1518BBF4.s")
void func_10022EC0(void *, void *, s32);
s32 func_150ADA20(void);
Game1B8F40Effect *func_15167A68(s32, s32, s32, s32, s32, s32);

Game1B8F40Effect *func_1518BCD0(void *arg0, u8 arg1, s32 arg2) {
    Game1B8F40Effect *temp_v0;

    temp_v0 = func_15167A68(0x1F, arg2, 0x44, 1, (s32) arg1, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    func_10022EC0((u8 *)temp_v0 + 0x10, arg0, 0x1C);
    temp_v0->field2C = func_150ADA20() & 0x1F;
    temp_v0->field30 = func_150ADA20() & 0x1F;
    return temp_v0;
}
