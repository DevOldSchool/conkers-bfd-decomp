#include "types.h"

/*
 * Reviewed source unit: src/game/game_15BAA0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512E5F0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game12E5F0Command { u32 first, second; } Game12E5F0Command;
void *func_1501A490(void *, s16, s32, s32, s32, s32);
void *func_1501A680(void *);
extern s16 D_80082FA6;
extern s32 D_800BE620;
extern s32 D_800BE9C4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512E5F0 CURRENT (3515) */
void *func_1512E5F0(register Game12E5F0Command *arg0, u8 *arg1) {
    register s32 *width = &D_800BE620;
    register u32 tileId = 0x07000000;
    s32 capped, words, numerator, denominator, widthValue, limit;
    {
        Game12E5F0Command *command = arg0++;
        command->first = 0xE7000000;
        command->second = 0;
    }
    {
        Game12E5F0Command *command = arg0++;
        command->first = 0xEF202CFF;
        command->second = 0;
    }
    {
        Game12E5F0Command *image = arg0++;
        Game12E5F0Command *tile;
        Game12E5F0Command *sync;
        Game12E5F0Command *load;
        image->first = 0xFD100000;
        tile = arg0++;
        sync = arg0++;
        load = arg0++;
        image->second = (u32)*(u16 *)(arg1 + 0x8BA) * (u32)*width * 2 + (u32)D_800BE9C4;
        tile->first = 0xF5100000;
        tile->second = tileId;
        sync->first = 0xE6000000;
        sync->second = 0;
        load->first = 0xF3000000;
        widthValue = *width;
        limit = widthValue - 1;
        if (limit < 0x7FF) capped = limit; else capped = 0x7FF;
        words = (s32)((u32)widthValue * 2) / 8;
        if (words <= 0) numerator = 1; else numerator = words;
        if (words <= 0) denominator = 1; else denominator = words;
        load->second = (((numerator + 0x7FF) / denominator) & 0xFFF) | tileId | ((capped & 0xFFF) << 12);
    }
    {
        Game12E5F0Command *command = arg0++;
        command->first = 0xE7000000;
        command->second = 0;
    }
    {
        Game12E5F0Command *command = arg0++;
        command->second = 0;
        command->first = (((s32)((u32)*width * 2 + 7) >> 3) & 0x1FF) << 9 | 0xF5100000;
    }
    {
        Game12E5F0Command *command = arg0++;
        command->first = 0xF2000000;
        limit = *width - 1;
        command->second = (((u32)limit * 4) & 0xFFF) << 12;
    }
    {
        Game12E5F0Command *command = arg0++;
        command->first = ((*width - 1) & 0xFFF) | 0xFF100000;
        command->second = *(u32 *)(arg1 + 0x8BC);
    }
    {
        Game12E5F0Command *scissor = arg0++;
        Game12E5F0Command *rectangle;
        Game12E5F0Command *half1;
        Game12E5F0Command *half2;
        Game12E5F0Command *sync;
        scissor->first = 0xED000000;
        rectangle = arg0++;
        half1 = arg0++;
        half2 = arg0++;
        sync = arg0++;
        scissor->second = (((s32)((f32)*width * 4.0f) & 0xFFF) << 12) | 4;
        rectangle->second = 0;
        rectangle->first = (((u32)*width * 4 & 0xFFF) << 12) | 0xE4000000 | 4;
        half1->first = 0xE1000000;
        half1->second = 0;
        half2->first = 0xF1000000;
        half2->second = 0x10000400;
        sync->first = 0xE7000000;
        sync->second = 0;
    }
    arg0 = func_1501A490(func_1501A680(arg0), D_80082FA6, 0, 0, 0, 0);
    arg0->first = 0xEF082C3F;
    arg0->second = 0x552230;
    return arg0 + 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512E5F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15BAA0/func_1512E5F0.s")
