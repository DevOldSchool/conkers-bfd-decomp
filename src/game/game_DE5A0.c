#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_DE5A0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_table_selected_collections.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B10F0
 * - func_150B12FC
 * - func_150B1484
 * - func_150B17DC
 * - func_150B19E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_1505A184: unique active project prototype */
/* Call context: func_1505A630: unique active project prototype */
/* Call context: func_1505E650: unique active project prototype */
void func_1505A184(u16, f32, f32, f32 *, f32 *, f32 *);
s32 func_1505A630(f32, f32, s32);
void func_1505E650(u8 *, s32, s32, s32, f32, f32, s32);
extern f32 D_8009F8A0;
extern f32 D_8009F8A4;
extern f32 D_8009F8A8;
extern f32 D_8009F8AC;
extern f32 D_8009F8B0;
extern f32 D_8009F8B4;
extern f32 D_8009F8B8;
extern u8 D_800CC2D0;
extern f32 D_800CC2E8;
extern f32 D_800D1550;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B10F0 CURRENT (1862) */
void func_150B10F0(u8 *arg0) {
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp40;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fv1;
    s32 temp_v1;

    *(f32 *)((u8 *)arg0 + 0x174) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x178) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
    *(s8 *)((u8 *)arg0 + 0x125) = 0x64;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
    if (func_1505A6F8(&D_800CC2D0, arg0) < D_8009F8A0) {
        temp_fv0 = func_1505A6F8(arg0, &D_800CC2D0);
        temp_ft4 = temp_fv0;
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)&D_800CC2D0 + 0x18);
        if (temp_fv1 < 0.0f) {
            var_fv1 = 1000.0f;
        } else {
            var_fv1 = D_8009F8A4 - (temp_fv1 * D_8009F8A8);
        }
        if ((temp_fv0 < var_fv1) && (*(u8 *)((u8 *)&D_800CC2D0 + 0xAD) == 1)) {
            sp40 = temp_ft4;
            temp_fv0_2 = D_8009F8AC - temp_ft4;
            temp_v1 = func_1505A630(*(f32 *)((u8 *)arg0 + 0x174) - *(f32 *)((u8 *)&D_800CC2D0 + 0x14), *(f32 *)((u8 *)&D_800CC2D0 + 0x1C) - *(f32 *)((u8 *)arg0 + 0x178), 0) & 0xFFFF;
            if (D_8009F8B0 < temp_fv0_2) {
                D_800CC2E8 = *(f32 *)((u8 *)&D_800CC2D0 + 0x18) - ((temp_fv0_2 - 820.0f) * D_8009F8B4 * D_800D1550);
            }
            func_1505A184((temp_v1 - 0x3000) & 0xFFFF, (temp_fv0_2 * D_8009F8B8) + 5.0f, 0.0f, &sp50, &sp4C, &sp48);
            *(f32 *)((u8 *)&D_800CC2D0 + 0x164) = sp50;
            *(f32 *)((u8 *)&D_800CC2D0 + 0x168) = sp4C;
        }
    }
    func_1505E650(arg0, 0, 0x3F800000, 0, 0.0f, 0.0f, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B10F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B10F0.s")
void func_1502178C(void *, s32, s32);
s32 func_150535F4(u8 *);
void func_15058EA4(void *, f32, f32, f32, f32, f32, f32);
void func_15056B08(u8 *);
void func_15059140(u8 *);
extern f32 D_8009F8BC;
extern f32 D_8009F8C0;
extern u8 **D_800D2104;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B12FC CURRENT (1805) */
void func_150B12FC(u8 *arg0) {
    s16 original[2];
    f32 height;
    f32 prior;
    f32 target;
    f32 current;

    original[0] = *(s16 *)(arg0 + 0x76);
    arg0[0x80] = 0xA;
    height = (f32)*(s16 *)(D_800D2104[arg0[0x13F]] + 2);
    func_15058EA4(arg0, height, 1.0f, height, D_8009F8BC, 12.0f, -16.0f);
    func_15056B08(arg0);
    prior = *(f32 *)(arg0 + 0xC4);
    target = ((f32)(s16)((original[0] - *(u16 *)(arg0 + 0x76)) * 6) * 0.00390625f) - prior;
    if (target > 6.0f) {
        target = 6.0f;
    } else if (target < -6.0f) {
        target = -6.0f;
    }
    current = *(f32 *)(arg0 + 0x148);
    *(volatile f32 *)(arg0 + 0x148) = current + ((target - current) * D_8009F8C0);
    *(volatile f32 *)(arg0 + 0xC4) = prior + *(volatile f32 *)(arg0 + 0x148);
    *(volatile f32 *)(arg0 + 0x40) = (f32)(s16)(*(u16 *)(arg0 + 0x7A) + 0x4000) * 0.005493164f;
    func_15059140(arg0);
    if (func_150535F4(arg0) == 0) {
        func_1502178C(arg0, 0, -1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B12FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B12FC.s")
void func_15052760(void *, s16);
void func_150585F0(u8 *, f32);
extern u8 *D_800D20FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B1484 CURRENT (1000) */
void func_150B1484(u8 *arg0) {
    u16 original;
    f32 height;
    f32 travelTime;
    f32 positive;
    f32 range;
    s32 kind;
    s32 offset;

    original = *(u16 *)(arg0 + 0x76);
    arg0[0x80] = 10;
    if (arg0[0x104] == 0) {
        height = (f32)*(s16 *)(D_800D20FC + arg0[0x13F] * 0x30 + 8) + 210.0f;
        if (!(*(u16 *)(arg0 + 0x22C) & 8)) {
            if (arg0[0x223] != 3) {
                *(f32 *)(arg0 + 0xB8) = *(f32 *)(arg0 + 0x20) * -0.5f;
            } else {
                *(f32 *)(arg0 + 0xB8) = 0.0f;
            }
        }
        kind = arg0[0x223];
        if (kind == 14) {
            travelTime = func_1505A6F8(&D_800CC2D0 + arg0[0x222] * 0x32C, arg0) / *(f32 *)(arg0 + 0x3C);
            *(f32 *)(arg0 + 0x20) = (*(f32 *)((u8 *)&D_800CC2E8 + arg0[0x222] * 0x32C) + (f32)*(s16 *)(arg0 + 0x224) - *(f32 *)(arg0 + 0x18)) / travelTime;
            *(f32 *)(arg0 + 0x24) = 0.0f;
        } else {
            if (kind == 1) {
                height = D_800CC2E8 + 210.0f;
            }
            offset = *(s16 *)(arg0 + 0x224);
            if (offset != 0) {
                if (offset == 10000) {
                    height = (f32)*(s16 *)(D_800D2104[arg0[0x13F]] + arg0[0x21E] * 8 + 10);
                } else {
                    kind = arg0[4];
                    if (kind == 0x50 || kind == 5 || kind == 0xAD || kind == 0xAE || kind == 0xAF) {
                        height = (f32)(offset * 8);
                    } else {
                        height = (f32)(offset * 8);
                        height += *(f32 *)(arg0 + 0x180);
                    }
                }
            }
            if (!(arg0[0x100] & 0x40)) {
                if (arg0[4] == 0x44) {
                    positive = 3.0f;
                    range = 12.0f;
                    height = (f32)*(s16 *)(D_800D2104[arg0[0x13F]] + arg0[0x21E] * 8 + 10);
                } else {
                    positive = 5.0f;
                    range = 35.0f;
                }
                func_15058EA4(arg0, height, positive, height, -positive, range, -range);
            }
        }
        func_15056B08(arg0);
    } else {
        func_150585F0(arg0, 0.05f);
    }
    *(f32 *)(arg0 + 0x40) = (f32)(s16)(*(u16 *)(arg0 + 0x7A) + 0x4000) * 0.005493164f;
    func_15059140(arg0);
    kind = arg0[4];
    if (kind == 5 || kind == 0xAD || kind == 0xAE || kind == 0xAF || kind == 0x44) {
        func_15052760(arg0, (s16)original);
    }
    if (func_150535F4(arg0) == 0) {
        func_1502178C(arg0, 0, -1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B1484 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B1484.s")
/* Call context: func_15056B08: unique active declaration in the allowed source */
/* Call context: func_1505A184: unique active declaration in the allowed source */
/* Call context: func_1505A630: unique active declaration in the allowed source */
/* Call context: func_150AD78C: unique active project prototype */
void func_15056B08(u8 *);
void func_1505A184(u16, f32, f32, f32 *, f32 *, f32 *);
s32 func_1505A630(f32, f32, s32);
f32 func_150AD78C(f32);

void func_1505A770(void *);
extern f32 D_8009F8C4;
extern f32 D_8009F8C8;
extern u8 D_800BE9A0;
extern u8 D_800C3E78;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B17DC CURRENT (230) */
void func_150B17DC(u8 *arg0) {
    s32 sp3C;
    void *temp_s0;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s16 temp_v0;

    temp_s0 = func_1505EEB0(0xA, &sp3C);
    func_15056B08(arg0);
    if (*(u8 *)((u8 *)arg0 + 0x1E5) == 2) {
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) *(f32 *)((u8 *)temp_s0 + 0x14);
        *(f32 *)((u8 *)arg0 + 0x1C) = (f32) *(f32 *)((u8 *)temp_s0 + 0x1C);
        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x18) + ((f32) ((s32) *(u16 *)((u8 *)arg0 + 0x21C) / 5) + 160.0f));
        *(f32 *)((u8 *)arg0 + 0x20) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x24) = (f32) D_8009F8C4;
        *(u8 *)((u8 *)arg0 + 0x7E) = 0U;
    } else {
        *(f32 *)((u8 *)temp_s0 + 0xB8) = (f32) (func_150AD78C((f32)(u32)*(u8 *)(arg0 + 0x7E) * D_8009F8C8) * 6.0f);
        func_1505A770(arg0);
        *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) - 170.0f);
        *(s8 *)((u8 *)temp_s0 + 0x13C) = (s8) (D_800C3E78 + 0x64);
        func_1505A184(*(u16 *)((u8 *)temp_s0 + 0x7A), *(f32 *)((u8 *)temp_s0 + 0xB8) * -7.0f, 0.0f, &sp34, &sp30, &sp2C);
        *(f32 *)((u8 *)temp_s0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + sp34);
        *(f32 *)((u8 *)temp_s0 + 0x1C) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C) + sp30);
        *(u16 *)((u8 *)temp_s0 + 0x7A) = (u16) (*(u16 *)((u8 *)temp_s0 + 0x7A) + (D_800BE9A0 << 8));
        *(u8 *)((u8 *)arg0 + 0x7E) = (u8) (*(u8 *)((u8 *)arg0 + 0x7E) + D_800BE9A0);
        *(s8 *)((u8 *)temp_s0 + 0xAD) = 0;
        *(f32 *)((u8 *)temp_s0 + 0x3C) = 0.0f;
        *(f32 *)((u8 *)temp_s0 + 0x16C) = 0.0f;
        *(f32 *)((u8 *)temp_s0 + 0x170) = 0.0f;
    }
    temp_v0 = func_1505A630(*(f32 *)((u8 *)&D_800CC2D0 + 0x14) - *(f32 *)((u8 *)arg0 + 0x14), *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)&D_800CC2D0 + 0x1C), 0);
    *(s16 *)((u8 *)arg0 + 0x7A) = temp_v0;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (temp_v0 + 0x4000) * 0.005493164f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B17DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B17DC.s")
void func_150562FC(u8 *);
void func_150597FC(u8 *);
void func_1510F800(s32);
s32 func_1510F8D8(s32, s32, s32, s32 *);
extern s32 D_8008CAE0;
extern f32 D_8009F8CC;
extern u8 D_800B86A4[];
extern s32 D_800CC250;
extern f32 D_800CC2E4;
extern f32 D_800CC2EC;

/* func_15167D84 copies the full 0x38-byte descriptor. */
typedef struct {
    s32 resource;
    s32 surface;
    u8 unknown08[4];
    s16 field0C, field0E;
    s16 x, y, z;
    s16 velocityX, velocityZ, velocityY;
    u8 unknown1C[3];
    s8 mode;
    s16 field20, field22, size, step, lifetime;
    s8 field2A;
    u8 alpha;
    u8 red, green, blue, opacity;
    u8 unknown30[4];
    s16 field34;
    u8 unknown36[2];
} GameDE5A0Particle;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B19E0 CURRENT (1365) */
void func_150B19E0(u8 *arg0) {
    f32 target;
    f32 radius;
    f32 speed;
    f32 sine;
    f32 cosine;
    GameDE5A0Particle particle;
    s32 random;
    u8 angle;

    random = *(s32 *)(arg0 + 0xF8) & ~4;
    target = 0.0f;
    *(s32 *)(arg0 + 0xF8) = random;
    arg0[0xB0] = 0x19;
    arg0[0x13C] = 0;
    *(s32 *)(arg0 + 0xF8) = random | 0x80;
    if (*(f32 *)(arg0 + 0x3C) > 1.0f) {
        *(s32 *)(arg0 + 0xF8) |= 4;
    }
    random = *(s32 *)(arg0 + 0x25C);
    arg0[0x104] = 10;
    arg0[0x239] = 3;
    *(s32 *)(arg0 + 0xFC) = 0xA7;
    arg0[0x80] = 1;
    if (random & 0x40) {
        *(s32 *)(arg0 + 0x25C) = random & ~0x40;
        *(f32 *)(arg0 + 0x2C) = D_800CC2E4;
        *(f32 *)(arg0 + 0x34) = D_800CC2EC;
    }
    if (arg0[0x13D] != 0) {
        func_150562FC(arg0);
        if ((D_800B86A4[arg0[0x13D] * 0x32C] == 0 || (D_800CC250 & 4)) && *(u16 *)(arg0 + 0x21C) >= 9) {
            target = -20.0f;
        }
    }
    cosine = *(f32 *)(arg0 + 0xB8);
    *(f32 *)(arg0 + 0xB8) = cosine + (target - cosine) * D_8009F8CC;
    *(f32 *)(arg0 + 0x40) = (f32)(s16)(*(u16 *)(arg0 + 0x7A) + 0x4000) * 0.005493164f;
    func_15059140(arg0);
    func_150597FC(arg0);
    target = 0.0f;
    func_1505E650(arg0, 0, 0x3F800000, 0, target, target, 0);
    func_1502178C(arg0, 0, -1);
    if (arg0[0x13D] != 0 && (func_150ADA20() & 0xFF) < 40U) {
        cosine = (f32)(func_150ADA20() % 40U);
        radius = *(f32 *)(arg0 + 0x14C) * cosine;
        angle = func_150ADA20();
        sine = func_150489B0(angle);
        cosine = func_15048A40(angle);
        particle.field0C = 0;
        particle.field0E = 0;
        particle.resource = D_8008CAE0;
        particle.x = *(f32 *)(arg0 + 0x14) + sine * radius;
        particle.y = *(f32 *)(arg0 + 0x18);
        particle.z = *(f32 *)(arg0 + 0x1C) + cosine * radius;
        func_1510F800(0);
        particle.surface = func_1510F8D8(particle.x, particle.y, particle.z, 0);
        angle = *(u16 *)((u8 *)&D_800CC2D0 + 0x76) >> 8;
        speed = *(f32 *)((u8 *)&D_800CC2D0 + 0x3C) * 64.0f;
        particle.velocityX = func_150489B0(angle) * speed;
        cosine = func_15048A40(angle) * -speed;
        particle.velocityY = -30;
        particle.mode = 7;
        particle.field20 = 0;
        particle.field22 = -80;
        particle.velocityZ = cosine;
        random = func_150ADA20() & 0xFF;
        particle.alpha = random;
        particle.size = (random << 12) / 5100 + 0xCC;
        particle.step = (random << 12) / 12750 + 0x51;
        particle.lifetime = 400;
        particle.field2A = 0;
        particle.red = 0xFF;
        particle.green = 0xFF;
        particle.blue = 0;
        particle.opacity = 0xFF;
        particle.field34 = 0;
        func_15167D84(&particle, 0, 0, -1, 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B19E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B19E0.s")
