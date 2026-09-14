#include "types.h"

/*
 * Reviewed source unit: src/game/effects/colourframebuffer.c
 * Boundary evidence: docs/evidence/effects_colourframebuffer.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515FDA0
 * - func_1515FFEC
 * - func_151600D8
 * - func_15160274
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_1515FDA0.s")
typedef struct {
    u8 pad0[0xE];
    u8 payload[8];
    u8 pad16[2];
} ColourFramebufferEffect;

void func_10022EC0(void *, void *, s32);
ColourFramebufferEffect *func_15167A68(s32, s32, s32, s32, u8, u8);

ColourFramebufferEffect *func_1515FF74(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    ColourFramebufferEffect *effect;

    effect = func_15167A68(0x34, arg3, arg1 + sizeof(ColourFramebufferEffect), 1, arg2, 1);
    if (effect == 0) {
        return 0;
    }
    func_10022EC0(effect->payload, arg0, sizeof(effect->payload));
    return effect;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_1515FFEC.s")
extern void (*D_8008B0E4[])(void *, s32, u8);

void func_15160090(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008B0E4[*(u8 *)((u8 *)arg0 + 0x14)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_151600D8.s")
void func_15169260(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_800A6670;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15160274 CURRENT (650) */
void func_15160274(s32 arg0, u8 arg1) {
    s32 sp1C;

    sp1C = D_800A6670;
    func_15169260(&sp1C, 1, arg0, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15160274 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_15160274.s")
