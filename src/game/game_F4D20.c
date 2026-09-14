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

typedef struct GameF4D20GlobalState {
    u8 pad0[0xA];
    u8 field_A;
} GameF4D20GlobalState;

typedef struct GameF4D20Flags {
    u8 pad0[0x73];
    u8 field_73;
} GameF4D20Flags;

void func_1511650C(void *, s32, s32, f32);
extern GameF4D20GlobalState *D_800D2E4C;
extern void *D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C7870 CURRENT (100) */
void func_150C7870(void *arg0) {
    if (!(D_800D2E4C->field_A & 8)) {
        if (!(((GameF4D20Flags *)D_800DBEF4)->field_73 & 4)) {
            func_1511650C(arg0, 1, 0x353, 1000.0f);
            return;
        }
        func_1511650C(arg0, 1, 0x43, 400.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C7870 */
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
typedef struct {
    u8 pad_0[0x73];
    u8 field_73;
    u8 pad_74[8];
    void *field_7C;
} GameF4D20State;

extern void *D_800DBEF4;
void func_15116110(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C7968 CURRENT (1135) */
void **func_150C7968(GameF4D20State *arg0) {
    void **var_v0;
    void *temp_v1;

    func_15116110();
    var_v0 = (void **)&D_800DBEF4;
    if (!(arg0->field_73 & 4)) {
        temp_v1 = arg0->field_7C;
        var_v0 = (void **)((u8 *)D_800DBEF4 + 0x1E0);
        if (temp_v1 != 0) {
            *(s8 *)((u8 *)temp_v1 + 0x13) = *(s16 *)((u8 *)D_800DBEF4 + 0x21C) >> 4;
        }
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C7968 */
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
