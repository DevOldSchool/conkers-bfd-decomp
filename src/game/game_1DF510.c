#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DF510.c
 * Boundary evidence: docs/evidence/game_raw_render_effect_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B2060
 * - func_151B2100
 * - func_151B229C
 * - func_151B22F4
 * - func_151B2348
 * - func_151B2690
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1DF510EffectSlots {
    u8 pad0[0x10];
    void *effects[3];
    void *field_1C;
} Game1DF510EffectSlots;

typedef struct Game1DF510EffectOwner {
    u8 pad0[0x28];
    Game1DF510EffectSlots slots;
} Game1DF510EffectOwner;

void func_1516972C(void *);
void func_151B222C();

typedef struct {
    void *field_0;
    u8 field_4;
    u8 pad_5[3];
    s32 field_8;
    u8 field_C;
    s8 field_D;
    u8 pad_E[2];
    u8 field_10[0xC];
    s32 field_1C;
} Game1DF510Packet;

void func_100226F0(void *, s32);
void func_10022EC0(s32, void *, s32);
s32 func_15083E90(s32, void *);
s32 func_151491F4(s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B2060 CURRENT (134) */
void func_151B2060(void *arg0) {
    Game1DF510Packet packet;
    s32 object;

    if (arg0 != 0) {
        packet.field_0 = arg0;
        packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
        packet.field_8 = func_15083E90(1, arg0);
        packet.field_C = 1;
        packet.field_D = 0;
        func_100226F0(packet.field_10, 0xC);
        packet.field_1C = 0;
        object = func_151491F4(0x12C, -1, 0x16, 0, 0x12, 0x20, 0xFF, 1);
        if (object != 0) {
            func_10022EC0(object + 0x28, &packet, 0x20);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B2060 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2060.s")
s32 func_151B22F4();
void func_151B2348();
void func_151B2690();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B2100 CURRENT (148) */
void func_151B2100(void *arg0) {
    u8 sp2B;
    u8 *temp_v1;
    u8 *temp_a1;
    u8 *temp_v0;
    u8 temp_v0_2;
    u8 var_v0;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x28);
    temp_a1 = *(u8 **)((u8 *)arg0 + 0x30);
    temp_v1 = (u8 *)arg0 + 0x28;
    if ((*(s32 *)temp_v0 == 0) || (temp_v0[4] == 0xFF) ||
        (temp_v1[4] != temp_v0[0x3B]) || (*(s32 *)temp_a1 == 0) ||
        (temp_a1[4] == 0xFF) || (temp_v1[0xC] != temp_a1[0x3B])) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        return;
    }
    sp2B = temp_v1[0xD];
    temp_v0_2 = func_151B22F4(arg0);
    temp_v1[0xD] = temp_v0_2;
    if (sp2B != temp_v0_2) {
        func_151B222C(arg0);
        var_v0 = temp_v1[0xD];
        if (var_v0 == 1) {
            func_151B2348(arg0);
            var_v0 = temp_v1[0xD];
        }
        if ((var_v0 == 2) || (var_v0 == 0)) {
            func_151B2690(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B2100 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2100.s")
void func_151B220C() {
    func_151B222C();
}
void func_151B222C(Game1DF510EffectOwner *arg0) {
    u8 i = 0;
    Game1DF510EffectSlots *slots = &arg0->slots;
    void *effect;

    do {
        effect = slots->effects[i];
        if (effect != 0) {
            func_1516972C(effect);
        }
        i++;
    } while (i < 3);

    effect = slots->field_1C;
    if (effect != 0) {
        func_1516972C(effect);
    }
}
void func_1514933C(s32);
void func_15149368(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B229C CURRENT (200) */
void func_151B229C(s32 arg0) {
    func_151B220C();
    func_1514933C(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B229C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B229C.s")
void func_151B22C8(s32 arg0) {
    func_151B220C(arg0);
    func_15149368(arg0);
}
typedef struct {
    u8 pad_0[0x5C];
    s32 field_5C;
    u8 pad_60[5];
    u8 field_65;
} Game1DF510Entry;

typedef struct {
    u8 pad_0[0x28];
    u8 *field_28;
    u8 pad_2C[4];
    Game1DF510Entry *field_30;
} Game1DF510State;

extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B22F4 CURRENT (780) */
s32 func_151B22F4(Game1DF510State *arg0) {
    Game1DF510Entry *temp_v1;

    temp_v1 = arg0->field_30;
    if (((((arg0->field_28 - &D_800CC2D0) / 0x32C) + 1) == temp_v1->field_65) && (temp_v1->field_5C == 1)) {
        return 1;
    }
    return 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B22F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B22F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2348.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2690.s")
