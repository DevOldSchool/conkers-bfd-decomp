#include "types.h"

/*
 * Reviewed source unit: src/game/game_117490.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E9FE0
 * - func_150EA11C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_15134DAC(u8 *, s32, void *, s16);
extern f32 D_800A1410;
extern f32 D_800A1414;

typedef struct {
    u8 type;
    u8 pad01[3];
    void *object;
    s8 count;
    u8 pad09[3];
    f32 value0C;
    f32 value10;
    f32 value14;
    f32 value18;
    f32 value1C;
    f32 value20;
    s8 mode;
    u8 pad25;
    s16 size0;
    s16 size1;
    s16 argument;
    u8 pad2C[2];
    s8 flag0;
    s8 flag1;
    s8 flag2;
    u8 pad31[3];
    f32 scale;
    s8 kind;
    s8 end;
} Game117490Descriptor;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E9FE0 CURRENT (283) */
s32 func_150E9FE0(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    Game117490Descriptor descriptor;
    s32 saved;
    u8 copy[0x10];
    s32 temp_v0;
    s32 var_v1;

    descriptor.type = *((u8 *) arg0 + 0x3B);
    descriptor.value0C = -9.0f;
    descriptor.object = arg0;
    descriptor.count = 8;
    descriptor.value10 = -14.0f;
    descriptor.value1C = -14.0f;
    descriptor.mode = 2;
    descriptor.size0 = 0x3C;
    descriptor.size1 = 0x3C;
    descriptor.argument = arg1;
    descriptor.flag0 = 2;
    descriptor.flag1 = 2;
    descriptor.flag2 = 2;
    descriptor.kind = 3;
    descriptor.end = -1;
    *(s32 *) (copy + 0x0) = 0;
    *(s32 *) (copy + 0x4) = 0x11111;
    descriptor.value14 = 27.0f;
    descriptor.value18 = -21.0f;
    descriptor.value20 = 41.0f;
    descriptor.scale = 0.5f;
    *(f32 *) (copy + 0x8) = D_800A1410;
    *(f32 *) (copy + 0xC) = D_800A1414;
    temp_v0 = func_15134DAC((u8 *) &descriptor, 0x10, arg0, arg1);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        saved = temp_v0;
        func_10022EC0((void *) (temp_v0 + 0x80), copy, 0x10U);
        var_v1 = saved;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E9FE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_117490/func_150E9FE0.s")
s32 func_150EA10C(u8 *arg0) {
    *(s32 *)(arg0 + 0x80) = 0;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_117490/func_150EA11C.s")
