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
typedef s32 (*ColourFramebufferCallback)(void *);

extern ColourFramebufferCallback D_8008B0D0[];
extern s32 D_800BE9E4;
void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515FFEC CURRENT (889) */
void func_1515FFEC(void *arg0) {
    u8 sp1B;
    s8 callback_index;
    u8 callback_pending;

    callback_pending = 0;
    if (*(u8 *)((u8 *)arg0 + 0xE) & 1) {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (*(s16 *)((u8 *)arg0 + 0x12) - D_800BE9E4);
        if (*(s16 *)((u8 *)arg0 + 0x12) < 0) {
            callback_pending = 1;
        }
    }
    if (callback_pending == 0) {
        callback_index = *(s8 *)((u8 *)arg0 + 0xF);
        if (callback_index != -1) {
            sp1B = callback_pending;
            if (D_8008B0D0[(s32) callback_index](arg0) != 0) {
                callback_pending = sp1B;
            } else {
                callback_pending = 1;
            }
        }
    }
    if (callback_pending != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515FFEC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_1515FFEC.s")
extern void (*D_8008B0E4[])(void *, s32, u8);

void func_15160090(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008B0E4[*(u8 *)((u8 *)arg0 + 0x14)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
s32 func_151422DC(s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800A6540;
extern s32 D_800A6548;
extern s32 D_800A657C;
extern s32 D_800A6584;
extern s32 D_800A65B8;
extern s32 D_800A65C0;
extern s32 D_800A65F4;
extern s32 D_800A65FC;
extern s32 D_800A6630;
extern s32 D_800A663C;
extern f32 D_800A6674;
extern f32 D_800A6678;
extern f32 D_800A667C;
extern f32 D_800A6680;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151600D8 CURRENT (1135) */
s32 func_151600D8(u8 *arg0) {
    f32 *values;
    s32 index;
    s32 selector;

    selector = 2;
    values = (f32 *)(arg0 + 0x18);
    index = func_151422DC(0, (s32)&D_800A6540, -0x7D0, 0x7D0,
                          0, (s32)&D_800A6548, 0x1C4);
    values[0] = (f32)index * D_800A6674;
    index = func_151422DC(1, (s32)&D_800A657C, -0x7D0, 0x7D0,
                          0, (s32)&D_800A6584, 0x1C9);
    values[1] = (f32)index * D_800A6678;
    index = func_151422DC(selector, (s32)&D_800A65B8, 0, 0x7D0,
                          0x1F4, (s32)&D_800A65C0, 0x1CE);
    values[2] = (f32)index * D_800A667C;
    selector++;
    index = func_151422DC(selector, (s32)&D_800A65F4, 0, 0x7D0,
                          0x1F4, (s32)&D_800A65FC, 0x1D3);
    values[3] = (f32)index * D_800A6680;
    selector++;
    *(s32 *)(values + 4) = func_151422DC(selector, (s32)&D_800A6630,
                                          0, 0x10000, 0x10000,
                                          (s32)&D_800A663C, 0x1D9);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151600D8 */
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
