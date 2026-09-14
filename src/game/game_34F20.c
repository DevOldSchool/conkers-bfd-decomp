#include "types.h"

/*
 * Reviewed source unit: src/game/game_34F20.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15007A70
 * - func_15007B3C
 * - func_150081E4
 * - func_15008248
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_34F20/func_15007A70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_34F20/func_15007B3C.s")
extern s32 D_800CBE00;
extern s32 D_800D245C;
extern s32 D_800D2548;
extern s32 D_800D3668;
extern s32 D_800DDD64;
extern s32 D_800DF7C8;
extern s32 D_800DF7D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150081E4 CURRENT (1690) */
void func_150081E4(void) {
    u8 *var_v1;

    D_800D3668 = 0;
    D_800CBE00 = 0;
    D_800DDD64 = 0;
    var_v1 = (u8 *)&D_800DF7C8;
    do {
        var_v1 += 4;
        *(s32 *)(var_v1 - 4) = 0;
    } while (var_v1 != (u8 *)&D_800DF7D0);
    D_800D245C = 0;
    D_800D2548 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150081E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_34F20/func_150081E4.s")
extern u8 D_800C35C4;
extern s8 D_800C3C88;

void func_15008230(void) {
    D_800C35C4 = 0;
    D_800C3C88 = 0;
}
extern s8 D_800C3638;
extern s8 D_800C3663;
extern s8 D_800C3670;
extern s8 D_800C3671;
extern s8 D_800C3681;
extern s8 D_800C3682;
extern s8 D_800C3683;
typedef struct Game34F20Slot {
    s16 field_0;
    u8 pad2[0xA];
    s8 field_C;
    u8 padD[0x2B];
} Game34F20Slot;

extern Game34F20Slot D_800C3CA0[];
extern Game34F20Slot D_800C3D48[];
void func_1501D044(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15008248 CURRENT (2180) */
void func_15008248(s32 arg0) {
    Game34F20Slot *var_v0;

    D_800C3638 = 0;
    D_800C3671 = 0;
    D_800C3670 = 0;
    func_1501D044(0);
    func_1501D044(1);
    D_800C3663 = 0;
    var_v0 = D_800C3CA0;
    do {
        var_v0->field_0 = 0;
        var_v0->field_C = 0;
        var_v0 += 1;
    } while (var_v0 != D_800C3D48);
    D_800C3681 = 0;
    D_800C3682 = 0;
    D_800C3683 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15008248 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_34F20/func_15008248.s")

void func_1501D348(s32, s32, s32, u8, s32);
extern u8 D_800C35C5;
extern u8 D_800C35EA;
extern u8 D_800C3C90;
extern s32 D_800C3C94;
extern s32 D_800BE9F0;

void func_150082CC(void) {
    s32 index = D_800C35C4 - 1;

    if (D_800C35C4 != 0) {
        if (D_800C35C5 == 0) {
            D_800C35EA = 2;
        }
        D_800C35C4 = 0;
        func_1501D348(D_800BE9F0, index, 0, D_800C3C90, D_800C3C94);
    }
}
