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

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B8F40/func_1518BA90.s")
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
typedef struct Game1B8F40Effect {
    u8 pad0[0x2C];
    s32 field2C;
    s32 field30;
} Game1B8F40Effect;

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
