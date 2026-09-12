#include "types.h"

/*
 * Reviewed source unit: src/game/game_F4D20.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C7870
 * - func_150C78E0
 * - func_150C7930
 * - func_150C7968
 * - func_150C79BC
 * - func_150C7C90
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F4D20/func_150C7870.s")
/* Call context: func_151150BC: unique active project prototype */
void func_151150BC(void);
extern void * D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C78E0 CURRENT (175) */
void func_150C78E0(void *arg0) {
    if (!(*(u8 *)((u8 *)arg0 + 0x73) & 4)) {
        *(s32 *)((u8 *)arg0 + 0x3C) = (s32) (-(*(s32 *)((u8 *)D_800DBEF4 + 0x21C) & 0xFFFF0000) & 0xFFFF0000);
        func_151150BC();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C78E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F4D20/func_150C78E0.s")
void func_151150BC(void);
extern void *D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C7930 CURRENT (120) */
void func_150C7930(void *arg0) {
    void *temp_v0;
    s32 temp_t6;
    s32 temp_t7;

    temp_v0 = D_800DBEF4;
    temp_t6 = *(s32 *)((u8 *)temp_v0 + 0x21C);
    temp_t7 = temp_t6 & 0xFFFF0000;
    *(s32 *)((u8 *)arg0 + 0x3C) = temp_t7;
    func_151150BC();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C7930 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F4D20/func_150C7930.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F4D20/func_150C7968.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F4D20/func_150C79BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F4D20/func_150C7C90.s")
/* Call context: func_15083E90: unique active project prototype */
void * func_15083E90(u8);

void func_150C7D7C(void *arg0) {
    void *temp_v0;

    temp_v0 = func_15083E90(0xCU);
    *(s16 *)((u8 *)arg0 + 0x10) = (s16) (s32) (*(f32 *)((u8 *)temp_v0 + 0x14) - 30.0f);
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) (*(f32 *)((u8 *)temp_v0 + 0x18) + 50.0f);
    *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) (*(f32 *)((u8 *)temp_v0 + 0x1C) + 30.0f);
}
