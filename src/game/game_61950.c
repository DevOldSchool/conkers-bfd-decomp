#include "types.h"

/*
 * Reviewed source unit: src/game/game_61950.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150344A0
 * - func_1503453C
 * - func_150345E4
 * - func_15034728
 * - func_150347E8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_61950/func_150344A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_61950/func_1503453C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_61950/func_150345E4.s")
s32 func_1502DB20(u8);                              /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15034728 CURRENT (1384) */
void func_15034728(void *arg0) {
    f32 *temp_t7;
    s32 temp_v1;
    s32 var_a1;
    s32 var_t1;
    s32 var_v0;

    if ((*(s32 *)((u8 *)arg0 + 0x1D4) != 0) && (*(s32 *)((u8 *)arg0 + 0x9C) != 0)) {
        temp_v1 = func_1502DB20(*(u8 *)((u8 *)arg0 + 4)) - 1;
        var_t1 = 0x1F;
        if (temp_v1 < 0x1F) {
            var_t1 = temp_v1;
        }
        if (var_t1 >= 0) {
            do {
                var_a1 = 0;
                if (*(s32 *)((u8 *)arg0 + 0x9C) & (1 << var_t1)) {
                    do {
                        var_v0 = 0;
loop_9:
                        temp_t7 = (var_t1 << 6) + *(s32 *)((u8 *)arg0 + 0x1D4) + (var_a1 * 0x10) + var_v0;
                        var_v0 += 4;
                        *temp_t7 = 0.0f;
                        if (var_v0 != 0xC) {
                            goto loop_9;
                        }
                        var_a1 += 1;
                    } while (var_a1 != 3);
                }
                var_t1 -= 1;
            } while (var_t1 >= 0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15034728 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_61950/func_15034728.s")
typedef struct Game61950Actor {
    s32 field_0;
    u8 pad4[0x98];
    s32 field_9C;
    u8 padA0[0x28C];
} Game61950Actor;

extern u8 D_800BEAC0;
extern Game61950Actor D_800CC2D0[];
extern Game61950Actor D_800D121C;
void func_15034728(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150347E8 CURRENT (400) */
void func_150347E8(void) {
    Game61950Actor *actor;
    Game61950Actor *end;

    actor = D_800CC2D0;
    if (D_800BEAC0 == 0) {
        end = &D_800D121C;
        do {
            if ((actor->field_0 != 0) && (actor->field_9C != 0)) {
                func_15034728(actor);
            }
            actor++;
        } while (actor != end);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150347E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_61950/func_150347E8.s")
