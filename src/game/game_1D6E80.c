#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D6E80.c
 * Boundary evidence: docs/evidence/game_raw_callback_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A99D0
 * - func_151A9AA4
 * - func_151A9BA0
 * - func_151A9CA0
 * - func_151A9DC0
 * - func_151A9EC0
 * - func_151A9FC8
 * - func_151AA09C
 * - func_151AA17C
 * - func_151AA210
 * - func_151AA264
 * - func_151AA30C
 * - func_151AA48C
 * - func_151AA5A4
 * - func_151AA6D8
 * - func_151AAA4C
 * - func_151AAABC
 * - func_151AAB50
 * - func_151AAB78
 * - func_151AABC4
 * - func_151AADBC
 * - func_151AADF8
 * - func_151AB090
 * - func_151AB180
 * - func_151AB1C4
 * - func_151AB2C4
 * - func_151AB3A4
 * - func_151AB6B8
 * - func_151AB788
 * - func_151AB7D8
 * - func_151AB828
 * - func_151AB854
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A99D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9AA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9BA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9CA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9DC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9EC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9FC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA09C.s")
void func_151AA170(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA17C.s")
void func_151AA1D0(void) {
    func_1519F400();
}
void func_151AA1F0(void) {
    func_1519F400();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA210.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA30C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA48C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA5A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA6D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AAA4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AAABC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AAB50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AAB78.s")
s32 func_151AABA0(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (*(u8 *)((u8 *)arg0 + 0x84) == 0) {
        var_v1 = 0;
    }
    *(u8 *)((u8 *)arg0 + 0x84) = 0U;
    return var_v1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AABC4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AADBC CURRENT (130) */
s32 func_151AADBC(void *arg0) {
    s32 temp_t6;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 0x10;
    {
        s32 var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
        *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) var_v1;
    }
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AADBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AADBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AADF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB090.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB180.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB1C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB2C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB3A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB6B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB788.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB7D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB828.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB854.s")
void func_151AB920(s32 arg0, s32 arg1) {
}
