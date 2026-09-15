#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A11B0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15173D00
 * - func_151742EC
 * - func_151745F0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A11B0/func_15173D00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A11B0/func_151742EC.s")
typedef struct {
    f32 field_0;
    f32 field_4;
    f32 field_8;
    u8 state;
    u8 pad_D[0x27];
    s8 field_34;
    u8 pad_35[3];
    s32 field_38;
} Game1A11B0Entry;

extern Game1A11B0Entry D_800DD348[];
extern Game1A11B0Entry D_800DD3FC[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151745F0 CURRENT (2015) */
s32 func_151745F0(f32 arg0, f32 arg1, f32 arg2, void *arg3, s8 arg4,
                  s32 arg5) {
    Game1A11B0Entry *entry;
    Game1A11B0Entry *end;
    u32 *source;
    u32 *destination;

    entry = D_800DD348;
    end = D_800DD3FC;
loop:
    if (entry->state != 0) {
        entry++;
        if (entry != end) {
            goto loop;
        }
        return 1;
    }
    entry->field_0 = arg0;
    entry->field_4 = arg1;
    entry->state = 3;
    entry->field_8 = arg2;
    entry->field_34 = arg4;
    entry->field_38 = arg5;
    if (arg3 != 0) {
        source = (u32 *)arg3;
        destination = (u32 *)entry;
        do {
            source += 3;
            destination += 3;
            destination[1] = source[-3];
            destination[2] = source[-2];
            destination[3] = source[-1];
        } while (source != (u32 *)((u8 *)arg3 + 0x24));
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151745F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A11B0/func_151745F0.s")
