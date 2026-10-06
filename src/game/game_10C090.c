#include "types.h"

/*
 * Reviewed source unit: src/game/game_10C090.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DEC28
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_150DEC28(u8 arg0, s32 arg1);

void func_150DEBE0(s32 arg0) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
        func_150DEC28((u8)var_s0, 1);
        var_s0 += 1;
        var_s0 &= 0xFF;
        if (var_s0 < 4) {
            goto loop_1;
        }
}
typedef struct Game10C090LookupRecord {
    u8 value;
    u8 pad1[3];
} Game10C090LookupRecord;

extern Game10C090LookupRecord D_800A0D0B[];
extern Game10C090LookupRecord D_800A0D2B[];
void func_151616D0(s32, u8, s32);
void func_151417C4(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DEC28 CURRENT (200) */
void func_150DEC28(u8 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg0 * sizeof(Game10C090LookupRecord);
    func_151616D0(((u8 *)D_800A0D0B)[temp_v0], 0x22, 0);
    func_151417C4(((u8 *)D_800A0D2B)[temp_v0], 0x22);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DEC28 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10C090/func_150DEC28.s")
