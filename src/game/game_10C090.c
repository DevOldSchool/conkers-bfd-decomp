#include "types.h"

/*
 * Reviewed source unit: src/game/game_10C090.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DEBE0
 * - func_150DEC28
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_150DEC28(s32 arg0, s32 arg1);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DEBE0 CURRENT (415) */
void func_150DEBE0(s32 arg0) {
    s32 temp_t6;
    s32 var_s0;

    var_s0 = 0;
loop_1:
        func_150DEC28(var_s0 & 0xFF, 1);
        var_s0 += 1;
        temp_t6 = var_s0 & 0xFF;
        if (temp_t6 < 4) {
            var_s0 = temp_t6;
            goto loop_1;
        }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DEBE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10C090/func_150DEBE0.s")
typedef struct Game10C090LookupRecord {
    u8 value;
    u8 pad1[3];
} Game10C090LookupRecord;

extern Game10C090LookupRecord D_800A0D0B[];
extern Game10C090LookupRecord D_800A0D2B[];
void func_151616D0();
void func_151417C4(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DEC28 CURRENT (569) */
void func_150DEC28(s32 arg0, s32 arg1) {
    s32 temp_a3;
    s32 temp_v0;

    temp_a3 = arg0 & 0xFF;
    temp_v0 = temp_a3 * sizeof(Game10C090LookupRecord);
    func_151616D0(((u8 *)D_800A0D0B)[temp_v0], 0x22, 0, temp_a3);
    func_151417C4(((u8 *)D_800A0D2B)[temp_v0], 0x22);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DEC28 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10C090/func_150DEC28.s")
