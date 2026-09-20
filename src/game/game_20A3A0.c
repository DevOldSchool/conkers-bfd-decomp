#include "types.h"

/*
 * Reviewed source unit: src/game/game_20A3A0.c
 * Boundary evidence: docs/evidence/game_raw_loader_transfer_emission_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151DCEF0
 * - func_151DCFD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u64 func_10026968(s32, s32, s32, s32);
u64 func_10026868(u64, s32, s32);
void func_10024A40(void *, u64, s32, s32, void *, s32);
s32 func_151DCFD8(s32);
extern s32 D_8002BD10;
extern s32 D_8002BD14;
extern u8 D_80042A58;
extern u8 D_80042A78;
extern u8 D_80042A90;
extern s32 D_800E0A20;
extern u8 D_800E0A24;
extern s32 D_800E0A28;
extern s32 D_800E0A2C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DCEF0 CURRENT (1053) */
void func_151DCEF0(s32 arg0, u8 arg1, s32 arg2, s32 arg3) {
    u64 value;

    if (func_151DCFD8(1) != 0) {
        do {
        } while (func_151DCFD8(1) != 0);
    }
    D_800E0A20 = arg0;
    D_800E0A24 = arg1;
    D_800E0A28 = arg2;
    D_800E0A2C = arg3;
    value = func_10026968(0, 0x2EE0, D_8002BD10, D_8002BD14);
    value = func_10026868(value, 0, 0xF4240);
    func_10024A40(&D_80042A58, value, 0, 0, &D_80042A78, (s32)&D_80042A90);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DCEF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20A3A0/func_151DCEF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20A3A0/func_151DCFD8.s")
