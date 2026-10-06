#include "types.h"

/*
 * Reviewed source unit: src/game/game_12D7F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15100464
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct { u8 bytes[5]; } Game12D7F0Copy5;
extern Game12D7F0Copy5 D_80088BC0;
extern u8 D_800BE500[];
extern u8 D_800DD405;

u32 func_150ADA20(void);
void func_151616D0(u8, s32, s32);

void func_15100340(s32 arg0) {
    s32 var_s2;
    Game12D7F0Copy5 sp44;
    u32 var_s0;
    u8 *temp_s0;
    u8 *var_s1;

    sp44 = D_80088BC0;
    if (arg0 == 0) {
        var_s1 = D_800BE500;
        D_800DD405 += 1;
        var_s2 = 0;
        do {
            var_s0 = *var_s1 != 0 ? 0x46 : 0x23;
            if ((func_150ADA20() % 1000U) < var_s0) {
                temp_s0 = &sp44.bytes[var_s2];
                if ((*var_s1 ^= 1) != 0) {
                    func_151616D0(*temp_s0, 0x18, 0);
                } else {
                    func_151616D0(*temp_s0, 0x1C, 0);
                    func_151616D0(*temp_s0, 0x17, 0);
                }
            }
            var_s2++;
            var_s1++;
        } while (var_s2 != 5);
    }
}
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern s32 D_80090324[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15100464 CURRENT (335) */
void *func_15100464(void *arg0) {
    typedef struct { u32 words[2]; } Packet;
    s32 workspace[4];
    s32 phase;
    s32 value;
    u8 *selector;
    s32 command;

    phase = D_800DD405 >> 2;
    value = func_1510D0EC(D_80090324[phase % 3], workspace, 3, 0);
    {
        Packet *slot = arg0;
        arg0 = (u8 *)arg0 + sizeof(Packet);
        slot->words[0] = 0xDB060008;
        slot->words[1] = value;
    }
    value = func_1510D0EC(D_80090324[(phase + 1) % 3], workspace, 3, 0);
    {
        Packet *slot = arg0;
        arg0 = (u8 *)arg0 + sizeof(Packet);
        slot->words[0] = 0xDB06000C;
        slot->words[1] = value;
    }
    selector = D_800BE500;
    command = 0x10;
    do {
        value = func_1510D0EC(D_80090324[selector[0] + 3], workspace, 3, 0);
        {
            Packet *slot = arg0;
            arg0 = (u8 *)arg0 + sizeof(Packet);
            slot->words[0] = 0xDB060000 | (command & 0xFFFF);
            slot->words[1] = value;
        }
        command += 4;
        selector++;
    } while (command != 0x24);
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15100464 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12D7F0/func_15100464.s")
