#include "types.h"

/*
 * Reviewed source unit: src/game/game_6E770.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150412C0
 * - func_150413FC
 * - func_15041508
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_80084930[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150412C0 CURRENT (6065) */
void *func_150412C0(u8 *arg0) {
    volatile s32 *p;

    p = (volatile s32 *)arg0;
    p[1] = -1;
    p[0] = 0xD7000002;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[0] = 0xE7000000;
    p[1] = 0;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[0] = 0xFCFFFFFF;
    p[1] = 0xFFFCF279;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[0] = 0xEF002C0F;
    p[1] = 0x0055204C;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[0] = 0xFD90003F;
    p[1] = (s32)D_80084930;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[0] = 0xFD900000;
    p[1] = (s32)D_80084930;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[1] = 0x07000000;
    p[0] = 0xF5900000;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[0] = 0xE6000000;
    p[1] = 0;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[0] = 0xF3000000;
    p[1] = 0x077FF200;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[0] = 0xE7000000;
    p[1] = 0;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[0] = 0xF5800800;
    p[1] = 0;
    arg0 += 8;
    p = (volatile s32 *)arg0;
    p[0] = 0xF2000000;
    p[1] = 0x000FC1FC;
    return arg0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150412C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150412C0.s")
u8 *func_15041508(u8 *, s32, s32, s32);
s32 func_15041480(u8);
extern u8 D_800848D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150413FC CURRENT (878) */
u8 *func_150413FC(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    s32 var_s1;
    u8 *temp_v0;
    u8 *var_s0;
    u8 *var_s2;
    u8 temp_t6;

    var_s2 = arg0;
    temp_t6 = *arg3;
    var_s0 = arg3;
    var_s1 = arg1;
    if (temp_t6 != 0) {
        do {
            temp_v0 = func_15041508(var_s2, var_s1, arg2, func_15041480(temp_t6 & 0xFF));
            temp_t6 = *(u8 *)(var_s0 + 1);
            var_s2 = temp_v0;
            var_s0 += 1;
            var_s1 += 8;
        } while (temp_t6 != 0);
    }
    return var_s2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150413FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150413FC.s")
s32 func_15041480(u8 arg0) {
    s32 i;

    for (i = 0; i < 0x50; i++) {
        if (arg0 == D_800848D0[i]) {
            return i;
        }
    }
    return i;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15041508 CURRENT (2575) */
u8 *func_15041508(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    union Packet {
        u64 command;
        struct { u32 first; u32 second; } words;
    };
    union Packet *cursor;
    union Packet *packet;
    s32 remainder;

    cursor = (union Packet *)arg0;
    packet = cursor++;
    packet->words.first = (((((arg1 + 8) * 4) & 0xFFF) << 12) | 0xE4000000 | (((arg2 + 12) * 4) & 0xFFF));
    packet->words.second = ((((arg1 * 4) & 0xFFF) << 12) | ((arg2 * 4) & 0xFFF));
    packet = cursor++;
    packet->words.first = 0xE1000000;
    remainder = arg3 % 8;
    packet->words.second = (((u32)(remainder * 8) << 5) << 16) | ((((arg3 - remainder) / 8) * 0x180) & 0xFFFF);
    packet = cursor++;
    packet->words.first = 0xF1000000;
    packet->words.second = 0x04000400;
    return (u8 *)cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15041508 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_15041508.s")
