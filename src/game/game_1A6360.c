#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1A6360.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_animated_emission_controllers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15178EFC
 * - func_15179008
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800DD432;
extern s8 D_800DD433;
extern s8 D_800DD434;
extern s16 D_800DD436;
extern s32 D_800DD440;
extern s16 D_800DD444;
extern s8 D_800DD446;

void func_15178EB0(void) {
    D_800DD434 = 0;
    D_800DD446 = 0;
    D_800DD444 = 0x258;
    D_800DD432 = 0xF0;
    D_800DD433 = 0x14;
    D_800DD436 = 0;
    D_800DD440 = 0;
}
void func_10004074(s32);
void func_100111C8(u16);
extern u16 D_800DD430;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15178EFC CURRENT (30) */
void func_15178EFC(s32 arg0) {
    s32 temp_v0;
    s32 var_s0;
    u8 *temp_a0;

    if (arg0 == 2) {
        D_800DD434 = 0;
        temp_v0 = D_800DD440;
        D_800DD446 = 0;
        if (temp_v0 != 0) {
            var_s0 = 0;
            do {
                temp_a0 = *(u8 **)((u8 *)temp_v0 + var_s0);
                if (temp_a0 != 0) {
                    func_1516972C(temp_a0);
                    *(u8 **)((u8 *)(s32)D_800DD440 + var_s0) = 0;
                }
                temp_v0 = D_800DD440;
                var_s0 += 4;
            } while (var_s0 != 0x4B0);
            func_10004074(temp_v0);
            D_800DD440 = 0;
        }
        func_100111C8(D_800DD430);
        D_800DD444 = 0;
        D_800DD436 = 0;
        return;
    }
    if (arg0 == 3) {
        if (D_800DD446 == 0) {
            D_800DD444 = 0x258;
        } else if (D_800DD446 == 3) {
            D_800DD446 = 1;
        }
        D_800DD434 = arg0;
        return;
    }
    D_800DD434 = arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15178EFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A6360/func_15178EFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A6360/func_15179008.s")
f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern void *D_800DBFF0;
extern s16 D_800DD438[3];

void func_151794C8(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 zero = 0.0f;
    f32 horizontal;
    f32 depth;
    f32 trig;
    f32 cosine;
    f32 angle;

    x = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
    y = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x2FC);
    z = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x300);
    angle = *(f32 *)((u8 *)D_800DBFF0 + 0x398);
    trig = func_150AD78C(angle);
    cosine = func_150AD780(angle);
    horizontal = 500.0f * trig;
    depth = -500.0f * cosine;
    angle = *(f32 *)((u8 *)D_800DBFF0 + 0x3A0);
    trig = func_150AD78C(angle);
    cosine = func_150AD780(angle);
    x = (s32)((f32)x + (zero + (depth * trig)));
    z = (s32)((f32)z + ((depth * cosine) - zero));
    y = (s32)((f32)y + horizontal);
    D_800DD438[0] = x;
    D_800DD438[2] = z;
    D_800DD438[1] = y;
}
void func_1516865C(void *, s32, s32, s32, s32);

void func_15179600(s32 arg0, s32 arg1) {
    s32 x;
    s32 y;
    s32 z;
    s32 base_x;
    s32 base_y;
    s32 base_z;
    u8 *camera;
    void *effect;
    s32 random;
    s32 spD0;
    u8 packet[0xA8];

    packet[0xA0] = 0x11;
    *(s16 *)(packet + 0x8A) = 0x33;
    packet[0xA2] = 1;
    *(s16 *)(packet + 0x98) = 0;
    func_1516865C(packet, 0xFF, 0xFF, 0xFF, 0x50);
    camera = D_800DBFF0;
    base_x = (s32)*(f32 *)(camera + 0x2F8);
    base_y = (s32)*(f32 *)(camera + 0x2FC);
    base_z = (s32)*(f32 *)(camera + 0x300);
    x = ((s32)func_150ADA20() % 500) + base_x;
    z = ((s32)func_150ADA20() % 500) + base_z;
    if (arg0 == 0) {
        y = base_y + 500;
    } else {
        y = ((s32)func_150ADA20() % 500) + base_y;
    }
    random = (u32)func_150ADA20() % 10U;
    *(s16 *)(packet + 0x8C) = x;
    *(s16 *)(packet + 0x90) = z;
    *(s16 *)(packet + 0x8E) = y;
    *(s16 *)(packet + 0x9C) = 0;
    *(s16 *)(packet + 0x9E) = 0;
    *(s16 *)(packet + 0x92) = 4;
    *(s16 *)(packet + 0x94) = random + 0x23;
    *(u16 *)(packet + 0x98) = 0x8C00;
    packet[0xA1] = random + 0xA;
    *(s32 *)(packet + 0x80) = arg1;
    *(s16 *)(packet + 0x84) = D_800DD436;
    effect = func_15168800(packet, 0xFF, 0);
    if (effect != 0) {
        *(void **)((u8 *)(s32)D_800DD440 + (D_800DD436 * 4)) = effect;
        D_800DD436 += 1;
    }
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern f32 D_800A7204;
extern s32 D_800BE9E4;

void func_151797B0(u8 *arg0) {
    s32 value;
    s32 centerX;
    s32 centerY;
    s32 centerZ;
    f32 step;
    s32 wrapped;
    s32 temp;
    f32 trig;

    trig = sqrtf(((f32)*(s16 *)(arg0 + 0x9C) - *(f32 *)((u8 *)D_800DBFF0 + 0x2F8)) *
                     ((f32)*(s16 *)(arg0 + 0x9C) - *(f32 *)((u8 *)D_800DBFF0 + 0x2F8)) +
                 ((f32)*(s16 *)(arg0 + 0xA0) - *(f32 *)((u8 *)D_800DBFF0 + 0x300)) *
                     ((f32)*(s16 *)(arg0 + 0xA0) - *(f32 *)((u8 *)D_800DBFF0 + 0x300)));
    value = 80.0f - (80.0f * trig) / 1000.0f;
    if (value < 0) {
        value = 0;
    }
    temp = *(u16 *)(arg0 + 0xAE);
    arg0[0xB4] = value;
    temp += ((u32)((u8)D_800DD433 * 0x10 * ((func_150ADA20() & 0xFF) + 0x80))) >> 9;
    temp = (f32)temp * D_800A7204;
    if (temp > 0x3200) {
        temp = 0x3200;
    }
    *(u16 *)(arg0 + 0xAE) = temp;
    step = (s32)(arg0[0xB1] * D_800BE9E4);
    trig = func_15048A40(*(u16 *)(arg0 + 0xAE) >> 8);
    *(s16 *)(arg0 + 0x9C) = *(s16 *)(arg0 + 0x9C) + step * trig;
    trig = func_150489B0(*(u16 *)(arg0 + 0xAE) >> 8);
    temp = *(s16 *)(arg0 + 0x9C);
    *(s16 *)(arg0 + 0x9E) = *(s16 *)(arg0 + 0x9E) - step * trig;
    centerX = D_800DD438[0];
    centerY = D_800DD438[1];
    centerZ = D_800DD438[2];
    wrapped = 0;
    if (temp < centerX - 500) {
        *(s16 *)(arg0 + 0x9C) = (centerX - 500) - ((centerX - 500) - temp) + 1000;
        wrapped = 1;
    } else if (centerX + 500 < temp) {
        *(s16 *)(arg0 + 0x9C) = (centerX + 500) + (temp - (centerX + 500) - 1000);
        wrapped = 1;
    }
    {
        s32 pos;

        pos = *(s16 *)(arg0 + 0x9E);
        if (pos < centerY - 500) {
            *(s16 *)(arg0 + 0x9E) = (centerY - 500) - ((centerY - 500) - pos) + 1000;
            wrapped = 1;
        } else if (centerY + 500 < pos) {
            *(s16 *)(arg0 + 0x9E) = (centerY + 500) + (pos - (centerY + 500) - 1000);
            wrapped = 1;
        }
        pos = *(s16 *)(arg0 + 0xA0);
        if (pos < centerZ - 500) {
            *(s16 *)(arg0 + 0xA0) = (centerZ - 500) - ((centerZ - 500) - pos) + 1000;
            wrapped = 1;
        } else if (centerZ + 500 < pos) {
            *(s16 *)(arg0 + 0xA0) = (centerZ + 500) + (pos - (centerZ + 500) - 1000);
            wrapped = 1;
        }
    }
    if ((*(s32 *)(arg0 + 0x90) & 2) && wrapped) {
        D_800DD436 -= 1;
        *(s32 *)((u8 *)D_800DD440 + *(s16 *)(arg0 + 0x94) * 4) = 0;
        func_1516972C(arg0);
    } else if (*(s32 *)(arg0 + 0x90) & 1) {
        if (wrapped) {
            *(s32 *)(arg0 + 0x90) ^= 1;
        } else {
            arg0[0xB4] = 0;
        }
    }
}
void func_15179AB8(void) {
    void **ptr;
    void *temp_v0_2;
    s32 var_v1;
    int tmp1;
    s32 temp_v0;
    s32 temp_a1;

    tmp1 = D_800DD436 - 1;
    temp_v0 = tmp1;
    if (temp_v0 >= 0) {
        var_v1 = temp_v0 * 4;
        ptr = (void **)((u8 *)(s32)D_800DD440 + var_v1);
        do {
            temp_v0_2 = *ptr;
            var_v1 -= 4;
            if (temp_v0_2 != 0) {
                temp_a1 = *(s32 *)((u8 *)temp_v0_2 + 0x90);
                if (!(temp_a1 & 2)) {
                    *(s32 *)((u8 *)temp_v0_2 + 0x90) = temp_a1 | 2;
                    return;
                }
            }
            ptr--;
        } while (var_v1 >= 0);
    }
}
s32 func_1510F8D8(s32, s32, s32, s32);
void func_1516865C(void *, s32, s32, s32, s32);
extern f32 D_800A7208;

void func_15179B14(s32 arg0) {
    s16 baseX;
    s16 baseZ;
    s32 x;
    s32 z;
    s32 value;
    s32 count;
    f32 sentinel;

    baseX = D_800DD438[0];
    baseZ = D_800DD438[2];
    count = 0;
    if (arg0 > 0) {
        sentinel = D_800A7208;
        do {
            x = baseX + (s32)func_150ADA20() % 500;
            z = baseZ + (s32)func_150ADA20() % 500;
            value = func_1510F8D8(x, 0x2710, z, 0);
            if (sentinel != (f32)value) {
                u8 packet[0xB0];

                *(s32 *)(packet + 0x80) = 0;
                *(s16 *)(packet + 0x8A) = 0x80;
                *(s16 *)(packet + 0x8C) = x;
                *(s16 *)(packet + 0x8E) = value;
                *(s16 *)(packet + 0x90) = z;
                *(s16 *)(packet + 0x94) = 0x19;
                *(s16 *)(packet + 0x92) = 0x19;
                *(s16 *)(packet + 0x96) = 0;
                packet[0xA2] = 0xE;
                packet[0xA0] = 0x12;
                *(u16 *)(packet + 0x98) = 0x9804;
                packet[0xA1] = 0;
                func_1516865C(packet, 0xFF, 0xFF, 0xFF, 0xFF);
                func_15168800(packet, 0xFF, 0);
            }
            count++;
        } while (count != arg0);
    }
}
extern void *D_800DBFF0;

void func_15179CB0(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;
    f32 scale;

    temp_fv1 = (f32) *(s16 *)((u8 *)arg0 + 0xA0) - *(f32 *)((u8 *)D_800DBFF0 + 0x300);
    temp_fa0 = (f32) *(s16 *)((u8 *)arg0 + 0x9C) - *(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
    scale = 160.0f;
    scale *= sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
    *(s8 *)((u8 *)arg0 + 0xB4) = (s8) (u32) (255.0f - (scale / 1000.0f));
}
