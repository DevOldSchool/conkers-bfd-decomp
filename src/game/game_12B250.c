#include "types.h"

/*
 * Reviewed source unit: src/game/game_12B250.c
 * Boundary evidence: docs/evidence/game_raw_slot_motion_attachment_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FDDA0
 * - func_150FDF38
 * - func_150FE0B8
 * - func_150FE288
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_12B250/func_150FDDA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B250/func_150FDF38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B250/func_150FE0B8.s")
extern void func_151D3E04(s32 arg0, s32 arg1, s32 *arg2, u8 arg3, f32 arg4);
extern u8 D_80088B80;
extern s32 D_800A1F70;

void func_150FE248(s32 arg0, s32 arg1, s32 arg2) {
    func_151D3E04(arg0, arg2, &D_800A1F70, D_80088B80, 0.0f);
}
typedef struct {
    s8 field_0;
    s8 pad1;
    s16 field_2;
    s8 field_4;
    s8 field_5;
    s8 field_6;
} Game12B250EventPacket;

u32 func_150ADA20(void *);
void func_151D8868(s8 *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FE288 CURRENT (400) */
void func_150FE288(void *arg0) {
    Game12B250EventPacket packet;

    if (*(void **)((u8 *)arg0 + 0x318) != 0) {
        packet.field_0 = 1;
        packet.field_2 = (func_150ADA20(arg0) % 9U) + 0xF;
        packet.field_5 = 1 << *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x318) + 0x23D);
        packet.field_4 = (func_150ADA20(arg0) & 3) + 3;
        packet.field_6 = -1;
        func_151D8868(&packet.field_0, 0, 0xFF, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FE288 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B250/func_150FE288.s")
