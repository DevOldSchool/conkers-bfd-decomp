#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D4E00.c
 * Boundary evidence: docs/evidence/game_raw_model_owner_mode_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A7950
 * - func_151A7A90
 * - func_151A7D6C
 * - func_151A8340
 * - func_151A8584
 * - func_151A85D4
 * - func_151A8624
 * - func_151A87F8
 * - func_151A8A20
 * - func_151A8A78
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A7950.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A7A90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A7D6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8340.s")
void func_151A8560(s32 arg0) {
    func_151D5E30(arg0 + 0x6C, arg0);
}
typedef struct {
    u8 pad_0[0x5C];
    u8 field_5C;
} Game1D4E00State;

void func_15169804(s32);
void func_151A8560(s32);
extern void (*D_8008F94C[])(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8584 CURRENT (575) */
void func_151A8584(s32 arg0) {
    void (*temp_v0)(s32);

    temp_v0 = D_8008F94C[((Game1D4E00State *)arg0)->field_5C];
    if (temp_v0 != 0) {
        temp_v0(arg0);
    }
    func_151A8560(arg0);
    func_15169804(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8584 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8584.s")
void func_15169824(s32);
extern void (*D_8008F958[])(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A85D4 CURRENT (575) */
void func_151A85D4(s32 arg0) {
    void (*temp_v0)(s32);

    temp_v0 = D_8008F958[((Game1D4E00State *)arg0)->field_5C];
    if (temp_v0 != 0) {
        temp_v0(arg0);
    }
    func_151A8560(arg0);
    func_15169824(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A85D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A85D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8624.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A87F8.s")
typedef void (*Game1D4E00Callback)(void *, s32, s32);

extern Game1D4E00Callback D_8008F964[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8A20 CURRENT (442) */
void func_151A8A20(void *arg0, s32 arg1, s32 arg2) {
    Game1D4E00Callback temp_v1;
    u8 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x5C);
    if (var_v0 >= 3) {
        var_v0 = 0;
    }
    temp_v1 = D_8008F964[var_v0];
    if (temp_v1 != 0) {
        temp_v1(arg0, arg1, arg2 & 0xFF);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8A20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8A20.s")
void func_1516972C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8A78 CURRENT (772) */
void func_151A8A78(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_v0 = *(void **)((u8 *)arg0 + 0x60);
    if (temp_t6 == 0) {
        if ((*(s32 *)arg1 == *(s32 *)temp_v0) || (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)temp_v0 + 4))) {
            func_1516972C(temp_t6);
        }
    } else if (temp_t6 == 0x2D) {
        temp_a0 = *(s32 *)arg1;
        temp_v1 = *(s32 *)temp_v0;
        if (temp_a0 == temp_v1) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)temp_v0 = temp_a0;
            *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8A78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8A78.s")
