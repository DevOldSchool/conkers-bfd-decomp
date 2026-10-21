#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1B9DB0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_selected_particle_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518C900
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 *func_1502B6BC(s32, s32, s32, s32, s32, s32);
void func_1510CE60(s32, s32, s32, s32, void *);
void func_15168E54(s32, s32 *);
extern u8 D_800DF7D0[];
extern s32 D_800DF9B8[];
extern s32 *D_800E0148[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518C900 CURRENT (24) */
s32 func_1518C900(s32 arg0) {
    s32 *object;
    u8 *count;

    count = &D_800DF7D0[arg0];
    if (*count == 0) {
        object = func_1502B6BC(0, 0, 0, 2, 9, arg0);
        if (object == 0) {
            return 0;
        }
        func_1510CE60(*object, 0, 1, 0x3E, &D_800DF9B8[arg0]);
        func_15168E54(*object, object);
        D_800E0148[arg0] = object;
    } else {
        object = D_800E0148[arg0];
    }
    if (*count != 0xFF) {
        (*count)++;
    }
    return *object;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518C900 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9DB0/func_1518C900.s")
void func_100043B4(s32, s32); /* extern */

void func_1518CA04(s32 arg0) {
    if (arg0 != 0x1E4) {
        if (D_800DF7D0[arg0] != 0) {
            D_800DF7D0[arg0] -= 1;
            if (D_800DF7D0[arg0] == 0) {
                func_1510D630(*(struct Game13AAE0ValueList **)((u8 *)&D_800DF9B8 + arg0 * 4));
                func_100043B4(*(s32 *)((u8 *)&D_800E0148 + arg0 * 4), 4);
            }
        }
    }
}
