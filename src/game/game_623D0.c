#include "types.h"

/*
 * Reviewed source unit: src/game/game_623D0.c
 * Boundary evidence: docs/evidence/game_raw_record_glyph_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15034F30
 * - func_150356C8
 * - func_15035714
 * - func_15035808
 * - func_15035D6C
 * - func_15035FE8
 * - func_15036148
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s8 D_800C3F00;

void func_15034F20(void) {
    D_800C3F00 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15034F30.s")
extern u8 D_800C3F08[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150356C8 CURRENT (115) */
void *func_150356C8(void) {
    s32 temp_t6;
    u8 temp_v1;

    temp_v1 = D_800C3F00;
    if (temp_v1 == 0xF) {
        return 0;
    }
    temp_t6 = temp_v1 + 1;
    D_800C3F00 = temp_t6;
    return ((temp_t6 & 0xFF) * 0xC) - 0xC + D_800C3F08;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150356C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_150356C8.s")
s32 func_150A6360(void *, void *, f32, f32, f32, f32, f32, f32);
extern f32 D_80097D70;
extern s32 D_800BE628;
extern void *D_800D1C90[];
extern u8 D_800D9C10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15035714 CURRENT (1106) */
s32 func_15035714(s32 arg0, u8 *arg1, u8 *arg2, register f32 arg3) {
    s32 sp28;
    f32 temp_fa0;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv1;
    f32 var_fv0;
    f32 var_fv1;
    u16 temp_t8;
    u8 *temp_v0;

    sp28 = D_800BE628;
    temp_v0 = D_800D1C90[arg1[4]];
    temp_t8 = *(u16 *)(temp_v0 + 0xE);
    var_fv0 = (f32)temp_t8;
    temp_fv1 = *(f32 *)(arg1 + 0x150);
    temp_ft4 = var_fv0 * *(f32 *)(arg1 + 0x14C);
    temp_ft5 = var_fv0 * temp_fv1;
    temp_fa0 = (f32)*(s16 *)(temp_v0 + 0x10) * temp_fv1;
    if ((arg0 == 1) || (arg0 == 0)) {
        var_fv1 = arg3 - ((*(f32 *)(arg1 + 0x18) + temp_fa0) - arg3);
    } else {
        var_fv1 = *(f32 *)(arg1 + 0x18) + temp_fa0;
    }
    if (func_150A6360((void *)sp28, &D_800D9C10,
                      *(f32 *)(arg2 + 0x30), var_fv1,
                      *(f32 *)(arg2 + 0x38), temp_ft4, temp_ft5,
                      D_80097D70) == 0) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15035714 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15035714.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15035808.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15035D6C.s")
typedef struct Game623D0Entry {
    s32 word;
    u8 field4;
    u8 field5;
    u8 field6;
    u8 field7;
    u8 field8;
    u8 pad9[2];
    u8 fieldB;
} Game623D0Entry;

void *func_1502CCFC(void *, u8, void *, s32, s32, s32 *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15035FE8 CURRENT (7949) */
void *func_15035FE8(void *arg0, void *arg1) {
    u8 *cursor;
    Game623D0Entry *entry;
    Game623D0Entry *end;
    s32 colors[4];
    u8 count;

    cursor = arg0;
    if ((u8)D_800C3F00 != 0) {
        *(u32 *)(cursor + 4) = 0x200004;
        *(u32 *)cursor = 0xD9FFFFFF;
        cursor += 8;
        *(u32 *)cursor = 0xD9EEFFFF;
        *(u32 *)(cursor + 4) = 0;
        cursor += 8;
        *(u32 *)cursor = 0xE2001E01;
        *(u32 *)(cursor + 4) = 0;
        cursor += 8;
        count = (u8)D_800C3F00;
        entry = (Game623D0Entry *)D_800C3F08;
        if (count > 0) {
            do {
                if (entry->fieldB != 0) {
                    end = (Game623D0Entry *)(D_800C3F08 + count * 0xC);
                } else {
                    colors[3] = 0xFF;
                    colors[0] = entry->field5;
                    colors[1] = entry->field6;
                    colors[2] = entry->field7;
                    cursor = func_1502CCFC(cursor, entry->field8, arg1,
                                           entry->word, entry->field4,
                                           colors, 0, 1);
                    count = (u8)D_800C3F00;
                    end = (Game623D0Entry *)(D_800C3F08 + count * 0xC);
                }
                entry++;
            } while (entry < end);
        }
    }
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15035FE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15035FE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15036148.s")
