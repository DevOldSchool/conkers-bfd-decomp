#include "types.h"

/*
 * Reviewed source unit: src/game/game_F5800.c
 * Boundary evidence: docs/evidence/game_raw_narrow_effect_record_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C8350
 * - func_150C851C
 * - func_150C8600
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE4E0;
extern u8 D_800BE9A0;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C8350 CURRENT (1840) */
void func_150C8350(void) {
    s16 temp_a1;
    s16 temp_a1_3;
    s16 var_a0;
    s16 var_a2;
    s32 temp_a1_2;
    s32 temp_t7;
    s32 var_a1;
    s32 var_t0;
    s32 var_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *var_v0;

    var_v1 = 0;
    do {
        var_v0 = D_800BE4E0 + var_v1;
        var_a0 = *(s16 *)((u8 *)var_v0 + 6);
        temp_a1 = *(s16 *)((u8 *)var_v0 + 8);
        if (var_a0 != temp_a1) {
            var_a2 = temp_a1;
            if (var_a0 < 0) {
                var_a2 = -temp_a1;
            }
            temp_a1_2 = var_a2 - var_a0;
            var_t0 = temp_a1_2;
            temp_t7 = D_800BE9E4 * 0x10;
            if (temp_a1_2 < 0) {
                var_t0 = -temp_a1_2;
            }
            if (var_t0 < temp_t7) {
                *(s16 *)((u8 *)var_v0 + 6) = var_a2;
                var_v0 = D_800BE4E0 + var_v1;
            } else {
                if (temp_a1_2 < 0) {
                    var_a1 = -1;
                } else {
                    var_a1 = 1;
                }
                *(s16 *)((u8 *)var_v0 + 6) = (s16) (var_a0 + (temp_t7 * var_a1));
                var_v0 = D_800BE4E0 + var_v1;
            }
            var_a0 = *(s16 *)((u8 *)var_v0 + 6);
        }
        *(s16 *)((u8 *)var_v0 + 4) = (s16) (*(s16 *)((u8 *)var_v0 + 4) + (var_a0 * *(s8 *)((u8 *)var_v0 + 2) * D_800BE9A0));
        temp_v0 = D_800BE4E0 + var_v1;
        temp_a1_3 = *(s16 *)((u8 *)temp_v0 + 4);
        if (temp_a1_3 >= 0x500) {
            *(s16 *)((u8 *)temp_v0 + 4) = (s16) (temp_a1_3 - 0x500);
            temp_v0_2 = D_800BE4E0 + var_v1;
            *(s16 *)((u8 *)temp_v0_2 + 4) = (s16) (0x500 - *(s16 *)((u8 *)temp_v0_2 + 4));
            temp_v0_3 = D_800BE4E0 + var_v1;
            *(s8 *)((u8 *)temp_v0_3 + 2) = (s8) -*(s8 *)((u8 *)temp_v0_3 + 2);
            temp_v0_4 = D_800BE4E0 + var_v1;
            if (*(s16 *)((u8 *)temp_v0_4 + 4) >= 0x500) {
                *(s16 *)((u8 *)temp_v0_4 + 4) = 0x4FF;
            }
        } else if (temp_a1_3 < 0) {
            *(s16 *)((u8 *)temp_v0 + 4) = (s16) -temp_a1_3;
            temp_v0_5 = D_800BE4E0 + var_v1;
            *(s8 *)((u8 *)temp_v0_5 + 2) = (s8) -*(s8 *)((u8 *)temp_v0_5 + 2);
            temp_v0_6 = D_800BE4E0 + var_v1;
            if (*(s16 *)((u8 *)temp_v0_6 + 4) < 0) {
                *(s16 *)((u8 *)temp_v0_6 + 4) = 0;
            }
        }
        var_v1 += 0xA;
    } while (var_v1 != 0x64);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C8350 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C8350.s")
void func_150C84F4(s32 arg0) {
    if (arg0 == 0) {
        func_150C8350();
    }
}
u32 func_150ADA20(void);
void func_150CDB6C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C851C CURRENT (255) */
void func_150C851C(s32 arg0) {
    s32 base;
    s32 range;
    s32 value;
    s32 var_s0;
    u32 random_value;
    u8 *temp_t1;

    if (D_800BE4E0 != 0) {
        func_150CDB6C(arg0);
        base = (s32)(arg0 * 0x12C) >> 8;
        range = ((s32)(arg0 * 0x32) >> 8) + 0x32;
        var_s0 = 0;
        do {
            value = base;
            random_value = func_150ADA20();
            temp_t1 = (u8 *)D_800BE4E0 + var_s0;
            var_s0 += 0xA;
            value += random_value % (u32)range;
            *(s16 *)(temp_t1 + 8) = value;
        } while (var_s0 != 0x64);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C851C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C851C.s")
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern s32 *D_80088810[2];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C8600 CURRENT (1931) */
void *func_150C8600(void *arg0) {
    s32 sp58[2];
    s32 *sp4C[2];
    s32 **table;
    s32 record_offset;
    s32 command_offset;
    s32 variant;
    s32 result;
    u8 state;
    u8 *record;
    s32 *output;

    output = arg0;
    table = sp4C;
    sp4C[0] = D_80088810[0];
    sp4C[1] = D_80088810[1];
    record_offset = 0;
    command_offset = 4;
    do {
        record = (u8 *)D_800BE4E0 + record_offset;
        variant = *(s16 *)(record + 4) >> 8;
        if (variant < 0) {
            variant = 0;
        } else if (variant >= 5) {
            variant = 4;
        }
        state = record[0];
        if (state >= 2) {
            record[0] = 0;
            state = *((u8 *)D_800BE4E0 + record_offset);
        }
        result = func_1510D0EC(table[state][variant], sp58, 3, 0);
        output[0] = (command_offset & 0xFFFF) | 0xDB060000;
        output[1] = result;
        output += 2;
        command_offset += 4;
        record_offset += 0xA;
    } while (command_offset != 0x2C);
    return output;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C8600 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C8600.s")
