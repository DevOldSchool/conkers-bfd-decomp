#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/effects/colourframebuffer.c
 * Boundary evidence: docs/evidence/boundaries/effects/effects_colourframebuffer.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515FDA0
 * - func_151600D8
 * - func_15160274
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct ColourFramebufferEffect {
    u8 pad0[8];
    struct ColourFramebufferEffect *next;
    u8 padC[2];
    u8 payload[8];
    u8 pad16[2];
} ColourFramebufferEffect;

typedef struct ColourFramebufferGroup {
    ColourFramebufferEffect *head;
    u8 pad4[0x19C];
} ColourFramebufferGroup;

extern ColourFramebufferGroup D_800DCF20[];
extern ColourFramebufferEffect *D_800DD198[];
extern s8 D_800DD190;
extern u8 D_800C35EA;
extern void (*D_8008B0D8[])(ColourFramebufferEffect *, s32);
s32 func_1517EF00(s32);
s32 func_15181CC8(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515FDA0 CURRENT (5566) */
void func_1515FDA0(s32 arg0) {
    s32 group;
    s32 enabled;
    s32 slot_offset;
    s8 depth;
    u8 flags;
    ColourFramebufferEffect **slot;
    ColourFramebufferEffect *effect;

    group = 0;
    do {
        effect = D_800DCF20[group].head;
        depth = D_800DD190 + 1;
        D_800DD190 = depth;
        if (effect != 0) {
            slot = &D_800DD198[depth];
            do {
                *slot = effect->next;
                flags = effect->payload[0];
                if (flags & 4) {
                    effect->payload[0] = flags & ~4;
                    slot_offset = D_800DD190 * 4;
                    goto reload_slot;
                }
                if ((s8)effect->payload[2] != -1) {
                    enabled = 1;
                    if ((flags & 2) && D_800C35EA == 1) {
                        enabled = 0;
                    }
                    if ((flags & 8) && (func_15181CC8(0) == 0 || func_1517EF00(0) != 0)) {
                        enabled = 0;
                    }
                    if (enabled != 0) {
                        D_8008B0D8[(s8)effect->payload[2]](effect, arg0);
                    }
                    slot_offset = D_800DD190 * 4;
reload_slot:
                    slot = (ColourFramebufferEffect **)((u8 *)D_800DD198 + slot_offset);
                }
                effect = *slot;
            } while (effect != 0);
        }
        D_800DD190--;
        group = (group + 1) & 0xFF;
    } while (group < 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515FDA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/colourframebuffer/func_1515FDA0.s")

void *func_10022EC0(void *, const void *, u32);

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

void func_1515FFEC(void *arg0) {
    u8 *p = (u8 *)arg0;
    u8 finished = 0;

    if (p[0xE] & 1) {
        *(s16 *)(p + 0x12) -= D_800BE9E4;
        if (*(s16 *)(p + 0x12) < 0) {
            finished = 1;
        }
    }
    if (finished == 0) {
        s8 callback = *(s8 *)(p + 0xF);
        if (callback != -1) {
            if (D_8008B0D0[callback](arg0) == 0) {
                finished = 1;
            }
        }
    }
    if (finished) {
        func_1516972C(arg0);
    }
}
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
