#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A0420.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15172F70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1A0420Command {
    u32 word0;
    u32 word1;
} Game1A0420Command;

typedef struct Game1A0420ViewportPrefix {
    u8 unknown00[0x24];
    f32 top24;
    f32 bottom28;
    f32 left2C;
    f32 right30;
} Game1A0420ViewportPrefix;

extern s8 D_800DD2D0;
extern u8 *D_800BE628;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15172F70 CURRENT (1055) */
Game1A0420Command *func_15172F70(Game1A0420Command *cursor) {
    s32 alpha = (u8)D_800DD2D0;

    if (alpha != 0) {
        {
            Game1A0420Command *command = cursor++;
            command->word0 = 0xD9E0FFFE;
            command->word1 = 0;
        }
        {
            Game1A0420Command *command = cursor++;
            command->word0 = 0xD9FFFFFF;
            command->word1 = 0x00200004;
        }
        {
            Game1A0420Command *command = cursor++;
            command->word0 = 0xE7000000;
            command->word1 = 0;
        }
        {
            Game1A0420Command *command = cursor++;
            command->word0 = 0xE3000A01;
            command->word1 = 0;
        }
        {
            Game1A0420Command *command = cursor++;
            command->word0 = 0xFA000000;
            command->word1 = 0xFFFFFF00 | (alpha & 0xFF);
        }
        {
            Game1A0420Command *command = cursor++;
            command->word0 = 0xE200001C;
            command->word1 = 0x00504340;
        }
        {
            Game1A0420Command *command = cursor++;
            command->word0 = 0xE3000C00;
            command->word1 = 0;
        }
        {
            Game1A0420Command *command = cursor++;
            command->word0 = 0xE3000F00;
            command->word1 = 0;
        }
        {
            Game1A0420Command *command = cursor++;
            command->word0 = 0xFCFFFFFF;
            command->word1 = 0xFFFDF6FB;
        }
        {
            Game1A0420Command *command = cursor++;
            command->word0 = 0xF6000000 |
                (((u32)((Game1A0420ViewportPrefix *)D_800BE628)->bottom28 & 0x3FF) << 2) |
                (((u32)((Game1A0420ViewportPrefix *)D_800BE628)->right30 & 0x3FF) << 14);
            command->word1 =
                (((u32)((Game1A0420ViewportPrefix *)D_800BE628)->top24 & 0x3FF) << 2) |
                (((u32)((Game1A0420ViewportPrefix *)D_800BE628)->left2C & 0x3FF) << 14);
        }
    }
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15172F70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0420/func_15172F70.s")
