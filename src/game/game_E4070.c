#include "types.h"

/*
 * Reviewed source unit: src/game/game_E4070.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B6BC0
 * - func_150B6C90
 * - func_150B6D34
 * - func_150B6E3C
 * - func_150B71A8
 * - func_150B7220
 * - func_150B73F0
 * - func_150B76BC
 * - func_150B77A8
 * - func_150B791C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150B6C90(void);
void func_150B6D34(void);
void func_150B6D78(void);
void func_150B7484(void);
void func_150B7560(void);
void func_150B765C(void);
void func_150B768C(void);
void func_150B77A8(void);
void func_150B791C(void);
extern s8 D_800D9890;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6BC0 */
void func_150B6BC0(s32 arg0) {
    switch ((u8)D_800D9890) {
    case 1:
        func_150B6C90();
        return;
    case 2:
        func_150B6D34();
        return;
    case 4:
        func_150B6D78();
        return;
    case 5:
        func_150B7484();
        return;
    case 6:
        func_150B7560();
        return;
    case 7:
        func_150B765C();
        return;
    case 8:
        func_150B77A8();
        return;
    case 9:
        func_150B768C();
        return;
    case 10:
        func_150B791C();
    default:
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6BC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6BC0.s")
extern s32 D_800BE9E8;
extern s32 D_800D9894;
extern s32 D_800D9898;
extern s32 D_800D989C;
extern s32 D_800D98A0;
extern s32 D_800D98C0;
extern s8 D_800D9890;
void func_1516972C(s32);
s32 func_151A4FD0(s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6C90 CURRENT (2125) */
void func_150B6C90(void) {
    s32 *var_v0;
    s32 *var_v1;

    if (D_800D9894 != 0) {
        func_1516972C(D_800D9894);
    }
    D_800D9894 = func_151A4FD0(0, 0, 0xFF, 0, 0, D_800BE9E8, 0, 0);
    D_800D9890 = 3;
    var_v0 = &D_800D98A0;
    var_v1 = &D_800D98C0;
    D_800D9898 = 0;
    D_800D989C = 0;
    do {
        var_v0 += 4;
        var_v0[-3] = 0;
        var_v0[-2] = 0;
        var_v0[-1] = 0;
        var_v0[-4] = 0;
    } while (var_v0 != var_v1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6C90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6C90.s")
extern s32 D_800D9898;
extern s32 D_800D98A4;
extern s8 D_800D9890;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6D34 CURRENT (70) */
void func_150B6D34(void) {
    u32 var_v1;
    void *temp_v0;
    u32 end = (u32)&D_800D98A4;

    var_v1 = (u32)&D_800D9898;
loop:
        temp_v0 = *(void **)(var_v1 + 0x14);
        var_v1 += 4;
        if (temp_v0 != 0) {
            *(s32 *)((u8 *)temp_v0 + 0x20) = 1;
        }
    if ((u32)var_v1 != end) {
        goto loop;
    }
    D_800D9890 = 3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6D34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6D34.s")
extern s32 D_800D9894;
extern s32 D_800D98C0;
extern s8 D_800D9890;
void func_1516972C(s32);

void func_150B6D78(void) {
    s32 *var_s0;
    s32 *var_s1;
    s32 temp_a0;

    if (D_800D9894 != 0) {
        func_1516972C(D_800D9894);
        D_800D9894 = 0;
    }
    var_s1 = (var_s0 = &D_800D9898, &D_800D98C0);
    do {
        temp_a0 = *var_s0;
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
            *var_s0 = 0;
        }
        var_s0 += 1;
    } while (var_s0 != var_s1);
    D_800D9890 = 3;
}
extern s32 D_800BE9E4;

void func_150B6DFC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + (D_800BE9E4 * 0x30));
    if (*(s16 *)((u8 *)arg0 + 0x34) >= 0x801) {
        *(s16 *)((u8 *)arg0 + 0x34) = -0xC00;
    }
}
/* The effect allocator reserves 0x4C bytes and copies its 0x3C-byte payload at +0x10. */
typedef struct {
    u8 unknown00[0x10];
    void *resource;
    u8 unknown14[4];
    s32 target_phase;
    s32 target_y;
    s32 cycles;
    s16 lifetime;
    s16 phase;
    u8 unknown28[4];
    f32 x;
    f32 y;
    u8 unknown34[8];
    s16 width;
    s16 height;
    s8 callback;
    u8 frame_count;
    u8 unknown42[3];
    u8 opacity;
    u8 unknown46[6];
} GameE4070Effect;

extern u8 D_80091918;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6E3C CURRENT (625) */
void func_150B6E3C(GameE4070Effect *effect) {
    s32 distance;
    s32 opacity;

    if (effect->cycles == 0 || effect->target_phase != effect->phase ||
        (effect->y < (f32)effect->target_y ?
            -(effect->y - (f32)effect->target_y) :
            effect->y - (f32)effect->target_y) > (f32)(D_800BE9E4 * 3)) {
        effect->y -= (f32)(D_800BE9E4 * 3);
        if (effect->y <= 140.0f) {
            effect->phase += 0x100;
            if (effect->phase >= (effect->frame_count << 8)) {
                effect->phase = 0;
            }
            effect->y = 200.0f - (140.0f - effect->y);
        }
        if (effect->y < 170.0f) {
            distance = (s32)-(effect->y - 170.0f);
        } else {
            distance = (s32)(effect->y - 170.0f);
        }
        opacity = 0xFF - distance * 8;
        if (opacity < 0) {
            opacity = 0;
        }
        effect->opacity = opacity;
    } else {
        effect->y = (f32)effect->target_y;
        if (effect->target_y == 170) {
            opacity = effect->opacity + D_800BE9E4 * 8;
            if (opacity >= 0x100) {
                opacity = 0;
                effect->cycles++;
                if (effect->cycles == 3) {
                    effect->resource = &D_80091918;
                    effect->callback = 8;
                    effect->opacity = 0xFF;
                    effect->width = 0x80;
                    effect->height = 0x10;
                    effect->phase = 0;
                    effect->target_phase = 0;
                    return;
                }
            }
            effect->opacity = opacity;
        } else {
            if (effect->y < 170.0f) {
                distance = (s32)-(effect->y - 170.0f);
            } else {
                distance = (s32)(effect->y - 170.0f);
            }
            opacity = 0xFF - distance * 9;
            if (opacity < 0) {
                opacity = 0;
            }
            effect->opacity = opacity;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6E3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6E3C.s")
void func_150B709C(void *arg0) {
    s32 var_v0;
    s32 var_v1;

    var_v0 = *(s32 *)((u8 *)arg0 + 0x18);
    if (var_v0 == 0x1E) {
        var_v1 = *(u8 *)((u8 *)arg0 + 0x45);
        var_v1 += D_800BE9E4 * 8;
        if (var_v1 >= 0x100) {
            var_v1 = 0;
        }
        *(u8 *)((u8 *)arg0 + 0x45) = (u8) var_v1;
    }
    var_v0 += D_800BE9E4 * 2;
    if (var_v0 >= 0x1F) {
        var_v0 = 0x1E;
    }
    *(s32 *)((u8 *)arg0 + 0x18) = var_v0;
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (((s32) (var_v0 * -0x54) / 30) + 0xE6);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (((s32) (var_v0 * -0x32) / 30) + 0xAA);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B71A8 CURRENT (10) */
void func_150B71A8(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 limit;

    limit = 0x1000;
    temp_v0 = *(s16 *)((u8 *)arg0 + 0x38);
    if (limit != temp_v0) {
        *(s16 *)((u8 *)arg0 + 0x38) = (s16) (temp_v0 + ((u32)D_800BE9E4 << 8));
        if (*(s16 *)((u8 *)arg0 + 0x38) >= 0x1001) {
            *(s16 *)((u8 *)arg0 + 0x38) = limit;
        }
    } else {
        temp_v0_2 = *(s16 *)((u8 *)arg0 + 0x3A);
        if (limit != temp_v0_2) {
            *(s16 *)((u8 *)arg0 + 0x3A) = (s16) (temp_v0_2 + ((u32)D_800BE9E4 << 8));
            if (*(s16 *)((u8 *)arg0 + 0x3A) >= 0x1001) {
                *(s16 *)((u8 *)arg0 + 0x3A) = limit;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B71A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B71A8.s")
typedef struct {
    void *resource;
    void *resource2;
    s32 field08;
    s32 field0C;
    s32 field10;
    s16 position[3];
    u8 pad1A[2];
    f32 scale_x;
    f32 scale_y;
    s16 field24;
    s16 field26;
    s16 field28;
    s16 field2A;
    s16 field2C;
    s16 field2E;
    u8 field30;
    u8 field31;
    u8 field32;
    u8 field33;
    u8 field34;
    u8 field35;
    u8 field36;
    u8 field37;
    u8 field38;
    u8 field39;
} GameE4070Descriptor;

void *func_15169900(void *, s32);
extern u8 D_80091924;
extern s32 D_800BE638;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B7220 CURRENT (4246) */
void func_150B7220(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    GameE4070Descriptor descriptor;
    s32 packed_x;
    s32 packed_y;
    s32 extent;
    s32 top, bottom, left, right;

    packed_x = (u32)arg0 << 16;
    packed_y = arg1 & 0xFFFF;
    descriptor.field2A = 0x1000;
    descriptor.resource = &D_80091924;
    descriptor.field08 = packed_x | packed_y;
    descriptor.field28 = 0x1000;
    descriptor.field0C = arg2;
    descriptor.position[0] = arg2;
    descriptor.position[2] = 0;
    descriptor.field24 = 0;
    descriptor.field26 = 0;
    descriptor.field2C = 0x10;
    descriptor.field2E = 0x10;
    descriptor.field30 = 7;
    descriptor.field31 = 2;
    descriptor.field32 = 0xFF;
    descriptor.field33 = 0;
    descriptor.field34 = 0;
    descriptor.field35 = 0xFF;
    descriptor.field36 = 7;
    descriptor.field37 = 0x11;
    if (arg0 < (D_800BE638 >> 1)) {
        extent = D_800BE638 - arg0;
    } else {
        extent = arg0;
    }
    top = arg1 - extent;
    descriptor.field10 = packed_x | (top & 0xFFFF);
    descriptor.field39 = 0;
    descriptor.position[1] = 0;
    descriptor.scale_x = arg0;
    descriptor.scale_y = top;
    func_15169900(&descriptor, arg3);
    bottom = arg1 + extent;
    descriptor.field10 = packed_x | (bottom & 0xFFFF);
    descriptor.field39 = 8;
    descriptor.scale_y = bottom;
    func_15169900(&descriptor, arg3);
    left = arg0 - extent;
    descriptor.scale_x = left;
    descriptor.field10 = ((u32)left << 16) | packed_y;
    descriptor.field39 = 4;
    descriptor.position[1] = 0x100;
    descriptor.scale_y = arg1;
    func_15169900(&descriptor, arg3);
    right = arg0 + extent;
    descriptor.field10 = ((u32)right << 16) | packed_y;
    descriptor.field39 = 0;
    descriptor.scale_x = right;
    func_15169900(&descriptor, arg3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B7220 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B7220.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B73F0 CURRENT (80) */
void func_150B73F0(void *arg0) {
    s16 target_x;
    s16 target_y;
    s16 scale;
    s32 divisor;
    s16 temp_v0;
    s16 temp_v1;
    s32 temp_lo;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x18);
    scale = *(s16 *)((u8 *)arg0 + 0x24);
    divisor = *(s32 *)((u8 *)arg0 + 0x1C);
    temp_lo = (s32) (scale << 0x10) / divisor;
    target_x = *(s16 *)((u8 *)arg0 + 0x20);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1A);
    target_y = *(s16 *)((u8 *)arg0 + 0x22);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (((s32) ((target_x - temp_v0) * temp_lo) >> 0x10) + temp_v0);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (((s32) ((target_y - temp_v1) * temp_lo) >> 0x10) + temp_v1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B73F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B73F0.s")


extern u8 D_800918DC;
s32 func_15169968(void *);

void func_150B7484(void) {
    GameE4070Descriptor descriptor;

    descriptor.field31 = 1;
    descriptor.field2C = 0x58;
    descriptor.scale_x = 60.0f;
    descriptor.scale_y = 60.0f;
    descriptor.position[0] = 0;
    descriptor.position[1] = 0;
    descriptor.position[2] = 0;
    descriptor.field2E = 0x58;
    descriptor.field30 = 6;
    descriptor.resource = &D_800918DC;
    descriptor.field32 = 0xFF;
    descriptor.field33 = 0;
    descriptor.field34 = 0;
    descriptor.field35 = 0xFF;
    descriptor.field24 = 0;
    descriptor.field26 = 0;
    descriptor.field39 = 0;
    descriptor.field36 = 7;
    descriptor.field37 = 0x15;
    descriptor.field38 = 1;
    descriptor.field28 = 0x51;
    descriptor.field2A = 0x51;
    if (D_800D9898 != 0) {
        func_1516972C(D_800D9898);
    }
    D_800D9898 = func_15169968(&descriptor);
    D_800D9890 = 3;
}
void func_150B7560(void) {
    GameE4070Descriptor descriptor;

    if (D_800D9898 != 0) {
        func_1516972C(D_800D9898);
        D_800D9898 = 0;
    }
    descriptor.position[2] = 0x4D;
    descriptor.field31 = 0xF;
    descriptor.position[0] = 0;
    descriptor.position[1] = 0;
    descriptor.field2C = 0x58;
    descriptor.field2E = 0x58;
    descriptor.field30 = 0;
    descriptor.resource = &D_800918DC;
    descriptor.field24 = 0;
    descriptor.field26 = 0;
    descriptor.field32 = 0xFF;
    descriptor.field33 = 0;
    descriptor.field34 = 0;
    descriptor.field35 = 0xFF;
    descriptor.field36 = 7;
    descriptor.field37 = 0x11;
    descriptor.field38 = 1;
    descriptor.field39 = 0;
    descriptor.field28 = 0x1000;
    descriptor.field2A = 0x1000;
    descriptor.scale_x = 60.0f;
    descriptor.scale_y = 60.0f;
    if (D_800D98A4 != 0) {
        func_1516972C(D_800D98A4);
    }
    D_800D98A4 = func_15169968(&descriptor);
    D_800D9890 = 3;
}
void func_150B76BC(s32 arg0, s32 arg1);
extern s8 D_800D9890;

void func_150B765C(void) {
    func_150B76BC(0x3C, 1);
    D_800D9890 = 3;
}
void func_150B768C(void) {
    func_150B76BC(0xE6, 2);
    D_800D9890 = 3;
}
extern u8 D_800918E8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B76BC CURRENT (1315) */
void func_150B76BC(s32 arg0, s32 arg1) {
    GameE4070Descriptor descriptor;
    s32 *entry;
    s32 resource;

    descriptor.field30 = 6;
    descriptor.field2E = 0x40;
    entry = &(&D_800D9898)[arg1];
    resource = *entry;
    descriptor.field31 = 1;
    descriptor.field2C = 0x58;
    descriptor.scale_x = (f32)arg0;
    descriptor.position[0] = 0;
    descriptor.position[1] = 0;
    descriptor.position[2] = 0;
    descriptor.resource = &D_800918E8;
    descriptor.field32 = 0xFF;
    descriptor.field33 = 0;
    descriptor.field34 = 0;
    descriptor.field35 = 0xFF;
    descriptor.field24 = 0;
    descriptor.field26 = 0;
    descriptor.field39 = 0;
    descriptor.field36 = 7;
    descriptor.field37 = 0x15;
    descriptor.field38 = 1;
    descriptor.field28 = 0x51;
    descriptor.field2A = 0x51;
    descriptor.scale_y = 170.0f;
    if (resource != 0) {
        func_1516972C(resource);
    }
    *entry = func_15169968(&descriptor);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B76BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B76BC.s")
extern u8 D_800918F4;
extern u8 D_80091900;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B77A8 CURRENT (2002) */
void func_150B77A8(void) {
    GameE4070Descriptor descriptor;
    s32 *slots = &D_800D9898;
    s32 current;

    current = slots[1];
    if (current != 0) {
        func_1516972C(current);
        slots[1] = 0;
    }
    descriptor.field2C = 0x40;
    descriptor.field2E = 0x40;
    descriptor.field30 = 4;
    descriptor.resource = &D_800918F4;
    descriptor.resource2 = &D_80091900;
    descriptor.position[0] = 0;
    descriptor.position[1] = 0;
    descriptor.position[2] = 0;
    descriptor.field31 = 0;
    descriptor.field24 = -0x800;
    descriptor.field26 = 9;
    descriptor.field32 = 0xFF;
    descriptor.field33 = 0;
    descriptor.field34 = 0;
    descriptor.field35 = 0xFF;
    descriptor.field36 = 0xD;
    descriptor.field37 = 0x12;
    descriptor.field38 = 2;
    descriptor.field39 = 3;
    descriptor.field28 = 0x1000;
    descriptor.field2A = 0x1000;
    descriptor.scale_x = 60.0f;
    descriptor.scale_y = 170.0f;
    current = slots[4];
    if (current != 0) {
        func_1516972C(current);
    }
    slots[4] = func_15169968(&descriptor);
    descriptor.field24 = 0;
    descriptor.field26 = 0;
    descriptor.field2C = 0x58;
    descriptor.field2E = 0x40;
    descriptor.field30 = 0;
    descriptor.field36 = 7;
    descriptor.field37 = 0x11;
    descriptor.field38 = 1;
    descriptor.resource = &D_800918E8;
    current = slots[8];
    if (current != 0) {
        func_1516972C(current);
    }
    slots[8] = func_15169968(&descriptor);
    D_800D9890 = 3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B77A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B77A8.s")
extern u8 D_8009190C;

typedef struct {
    u8 pad0[8];
    s32 oldEffect;
    u8 padC[8];
    s32 first;
    s32 second;
    s32 third;
    u8 pad20[4];
    s32 label;
} GameE4070EffectSlots;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B791C CURRENT (6118) */
void func_150B791C(void) {
    GameE4070Descriptor descriptor;
    GameE4070EffectSlots *slots = (GameE4070EffectSlots *)&D_800D9898;
    s32 current;

    if (slots->oldEffect != 0) {
        func_1516972C(slots->oldEffect);
        slots->oldEffect = 0;
    }
    descriptor.field31 = 3;
    descriptor.field2C = 0x40;
    descriptor.field2E = 0x10;
    descriptor.field30 = 5;
    descriptor.field24 = 0;
    descriptor.field26 = 0;
    descriptor.position[0] = 0;
    descriptor.position[1] = 0;
    descriptor.position[2] = 0;
    descriptor.resource = &D_8009190C;
    descriptor.resource2 = 0;
    descriptor.field08 = 0;
    descriptor.field10 = 0;
    descriptor.field32 = 0xFF;
    descriptor.field33 = 0;
    descriptor.field34 = 0;
    descriptor.field35 = 0x80;
    descriptor.field36 = 7;
    descriptor.field37 = 0x11;
    descriptor.field38 = 1;
    descriptor.field39 = 0;
    descriptor.field28 = 0x1000;
    descriptor.field2A = 0x1000;
    descriptor.scale_y = 150.0f;
    descriptor.scale_x = 230.0f;
    descriptor.field0C = (s32)descriptor.scale_y;
    if (slots->first != 0) {
        func_1516972C(slots->first);
    }
    current = func_15169968(&descriptor);
    slots->first = current;
    descriptor.position[1] = 0x100;
    descriptor.field08 = 0x100;
    descriptor.field35 = 0xFF;
    descriptor.scale_y = 170.0f;
    descriptor.field0C = (s32)descriptor.scale_y;
    if (slots->second != 0) {
        func_1516972C(current);
    }
    slots->second = func_15169968(&descriptor);
    descriptor.position[1] = 0x200;
    descriptor.field08 = 0x200;
    descriptor.field35 = 0x80;
    descriptor.scale_y = 190.0f;
    descriptor.field0C = (s32)descriptor.scale_y;
    if (slots->third != 0) {
        func_1516972C(slots->first);
    }
    slots->third = func_15169968(&descriptor);
    descriptor.position[0] = 0;
    descriptor.position[1] = 0;
    descriptor.position[2] = 0;
    descriptor.field31 = 0;
    descriptor.field2C = 0x58;
    descriptor.field2E = 0x40;
    descriptor.field35 = 0xFF;
    descriptor.field30 = 0;
    descriptor.resource = &D_800918E8;
    descriptor.scale_x = 230.0f;
    descriptor.scale_y = 170.0f;
    if (slots->label != 0) {
        func_1516972C(slots->label);
    }
    slots->label = func_15169968(&descriptor);
    D_800D9890 = 3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B791C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B791C.s")
