#include "types.h"

/*
 * Reviewed source unit: src/game/game_12CCF0.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FF840
 * - func_150FFB6C
 * - func_150FFBDC
 * - func_150FFC3C
 * - func_150FFD84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game12CCF0State {
    u8 pad0[0x1D4];
    s32 field1D4;
} Game12CCF0State;

void func_15145EA4(s32 *, s32 *, s32, s32);

extern u8 D_80088BB0;
extern s32 D_800A2130;

#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FF840.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FFB6C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FFBDC CURRENT (100) */
void func_150FFBDC(Game12CCF0State *arg0, s32 arg1, s32 arg2) {
    s32 *sp1C;
    s32 sp18;

    sp1C = &D_800A2130;
    sp18 = arg2;
    func_15145EA4((s32 *) &sp1C, &sp18,
                  arg0->field1D4 + (D_80088BB0 << 6), 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FFBDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FFBDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FFC3C.s")
void func_151D3E6C(void *, void *, void *, s32);
void func_151D5A18(void *, void *, void *, void *, void *, s32, s32);
extern s32 D_8008FC8C;
extern u8 *D_8008FC94;

void func_150FFCC8(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    func_151D5A18(arg0, arg1, arg2, arg3, arg4, D_8008FC8C, *D_8008FC94);
    func_151D3E6C(arg0, arg1, arg1, 0x8003A);
}
void func_15081E0C(void *, s32, s32);

void func_150FFD2C(s32 arg0, void *arg1, s32 arg2) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg1 + 4);
    if (((temp_v0 == 0x9F) || (temp_v0 == 0xA0)) && !(*(s32 *)((u8 *)arg1 + 0x94) & 0x80)) {
        func_15081E0C(arg1, 4, 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FFD84.s")
