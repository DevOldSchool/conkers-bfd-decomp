#include "types.h"

/*
 * Reviewed source unit: src/game/game_CD5A0.c
 * Boundary evidence: docs/evidence/game_raw_record_transform_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A00F0
 * - func_150A019C
 * - func_150A0264
 * - func_150A02D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A00F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A019C.s")
typedef struct GameCD5A0Record {
    volatile u8 flags;
    u8 pad1[3];
    s32 field_4;
    u8 pad8[4];
} GameCD5A0Record;

extern GameCD5A0Record D_800D3010[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A0264 CURRENT (300) */
s32 func_150A0264(s32 arg0, void *arg1) {
    GameCD5A0Record *record;
    s32 value;
    u8 temp_t3;
    u8 temp_t9;

    record = &D_800D3010[arg0];
    if ((*(u32 *)&record->flags >> 31) != 0) {
        return 0;
    }
    temp_t3 = record->flags | 0x80;
    record->flags = temp_t3;
    temp_t9 = temp_t3 & 0xBF;
    record->flags = temp_t9;
    value = *(s32 *)((u8 *)arg1 + 4);
    record->field_4 = 0;
    record->flags = ((value << 2) & 0x3C) | (temp_t9 & 0xC3);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A0264 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A0264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A02D0.s")
extern s32 D_800D3014[];

s32 func_150A0374(s32 arg0, s32 arg1, volatile s32 arg2) {
    if (arg1 == 3) {
        return *(s32 *)((u8 *)D_800D3014 + (arg0 * 0xC));
    }
    return 0;
}
