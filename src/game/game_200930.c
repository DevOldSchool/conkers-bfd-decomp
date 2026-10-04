#include "types.h"

/*
 * Reviewed source unit: src/game/game_200930.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D3480
 * - func_151D3E6C
 * - func_151D40D4
 * - func_151D42E8
 * - func_151D4408
 * - func_151D4794
 * - func_151D4C38
 * - func_151D4DAC
 * - func_151D5174
 * - func_151D5334
 * - func_151D5514
 * - func_151D5714
 * - func_151D57F8
 * - func_151D5A18
 * - func_151D5B6C
 * - func_151D5D60
 * - func_151D5E30
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game200930ResourceSlots {
    s32 entries[4];
} Game200930ResourceSlots;

void func_100043B4(s32, s32);

u16 func_10010E78(s32, s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
void * func_10022EC0(void *, const void *, u32);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_15102920(f32, s32, void *, void *, s32, s32, s32, s32, s32, s32);
void * func_15132A4C(void *, s32, s32, s32, u8, s32);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
void func_15145974(void *, f32 *, f32 *);
s32 func_15145C90(s32);

s32 func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
void func_15152B38(void *, s32, s32);
extern u8 D_1000EC24[];
extern s32 D_80082FA0;
extern f32 D_800AB188;
extern f32 D_800AB18C;
extern f32 D_800AB190;
extern f32 D_800AB194;
extern f32 D_800AB198;
extern f32 D_800AB19C;
extern f32 D_800AB1A0;
extern f32 D_800AB1A4;
extern f32 D_800AB1A8;
extern f32 D_800AB1AC;
extern f32 D_800AB1B0;
extern f32 D_800AB1B4;
extern f32 D_800AB1B8;
extern f32 D_800AB1BC;
extern f32 D_800AB1C0;
extern f32 D_800AB1C4;
extern f32 D_800AB1C8;
extern u8 D_800DCA20;
extern f32 D_800DCA24;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3480 CURRENT (17614) */
void func_151D3480(void *arg0, f32 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5) {
    typedef struct { f32 x, y, z; } Vec3;
    typedef struct { s16 words[9]; } Surface;
    typedef struct {
        s32 field00;
        s32 field04;
        Vec3 position;
        f32 field14;
        f32 field18;
        f32 field1C;
        f32 field20;
        f32 field24;
        f32 field28;
        s16 field2C;
        s16 field2E;
        s16 field30;
        s16 field32;
        s32 field34;
        s32 field38;
        s16 field3C;
        s16 field3E;
        s16 field40;
        s8 field42;
        s8 field43;
        s8 field44;
        s8 field45;
        s8 field46;
        s8 field47;
        s8 field48;
        s8 field49;
        s8 field4A;
        s8 field4B;
        s8 field4C;
        s8 field4D;
        s8 field4E;
        s8 field4F;
        s8 field50;
        s8 field51;
        s8 field52;
        s8 field53;
        s8 field54;
        s8 field55;
        s8 field56;
        s8 field57;
        s8 field58;
        u8 pad59[0x3];
        s32 field5C;
        s32 field60;
        s16 field64;
        s16 field66;
        s16 field68;
        s8 field6A;
        u8 pad6B[0x1];
        f32 field6C;
        s8 field70;
        s8 field71;
        s8 field72;
        s8 field73;
    } Emitter;
    typedef struct {
        f32 field00;
        f32 field04;
        f32 field08;
        f32 field0C;
        Vec3 transform;
        f32 field1C;
        f32 field20;
        f32 field24;
        Vec3 position;
        f32 field34;
        f32 field38;
        f32 field3C;
        Vec3 rotation;
        f32 field4C;
        s32 field50;
        s16 field54;
        s16 field56;
        s8 field58;
        u8 pad59[0x3];
        s32 field5C;
        s8 field60;
        s8 field61;
        s8 field62;
        s8 field63;
        s8 field64;
        s8 field65;
        s8 field66;
        s8 field67;
        s8 field68;
        u8 pad69[0x1];
        s8 field6A;
        u8 pad6B[0x1];
        s32 field6C;
        s8 field70;
        u8 pad71[0x1];
        s16 field72;
        s16 field74;
        u8 pad76[0x2];
    } ImpactPacket;
    typedef struct { s16 timer; u8 pad2[2]; f32 angle, rate, amplitude; } Motion;
    Vec3 position;
    Surface surface;
    u8 sp19F;
    s32 sp198;
    u8 sp197;
    s32 sp190;
    s32 sp18C;
    void *sp188;
    f32 sp184;
    s32 sp180;
    Emitter emitter;
    ImpactPacket packet;
    Vec3 normal;
    f32 sp80;
    f32 sp7C;
    Motion aux;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    s32 var_v1;
    void *temp_v0;

    arg3 &= 0xFF;
    if (arg3 >= 6) {
        return;
    }
    var_v1 = arg3;
    switch (arg3) {                              /* irregular */
    case 4:
        sp190 = 0xC;
block_9:
        if (arg2 == 0) {
            temp_fv0 = *(f32 *)((u8 *)arg1 + 0);
            temp_fv1 = *(f32 *)((u8 *)arg1 + 4);
            temp_ft4 = *(f32 *)((u8 *)arg1 + 8);
            if (func_150AC9C0(*(f32 *)((u8 *)arg0 + 0) - temp_fv0, *(f32 *)((u8 *)arg0 + 4) - temp_fv1, *(f32 *)((u8 *)arg0 + 8) - temp_ft4, temp_fv0, temp_fv1, temp_ft4, &sp188, &surface.words[0], &position.x, &position.y, &position.z, &sp184, &sp198, 0, 0.0f) != 0) {
                sp19F = 1;
            } else {
                sp19F = 0;
                sp198 = -1;
            }
        } else {
            sp198 = -1;
            position = *(Vec3 *)arg0;
            surface = *(Surface *)arg2;
            sp19F = 1;
        }
        sp197 = func_15145C90(sp198);
        if ((func_150ADA20() & 1) || (sp197 == 0)) {
            sp18C = 1;
        } else {
            sp18C = 0;
        }
        if (var_v1 == 1) {
            if (sp18C != 0) {
                sp180 = (func_150ADA20() % 3U) + 0x459;
                if (D_80082FA0 == 0) {
                    func_1000FA64((u16)sp180, (s16) (s32) *(f32 *)((u8 *)arg0 + 0), (s16) (s32) *(f32 *)((u8 *)arg0 + 4), (s16) (s32) *(f32 *)((u8 *)arg0 + 8), 0x4000, 0x4B0, 0x320, D_1000EC24, 0x28, 0, 0, 0);
                    sp180 = 0x106;
                }
            } else {
                sp180 = 0xB0;
            }
            func_10010E78(0, sp180, 0x6590U, (s32) (s16) ((func_150ADA20() % 500U) - 0xFA), 0, 0, (s32) *(f32 *)((u8 *)arg0 + 0), (s32) *(f32 *)((u8 *)arg0 + 4), (s32) *(f32 *)((u8 *)arg0 + 8), 0x1F4, 0x320);
        }
        if (func_150ADA68() < D_800DCA24) {
            emitter.field00 = 5 >> D_800DCA20;
            emitter.field04 = 4 >> D_800DCA20;
            emitter.position = *(Vec3 *)arg0;
            emitter.field32 = 0x50;
            emitter.field34 = 3;
            emitter.field2E = 0xFF;
            emitter.field30 = -0x3D;
            emitter.field38 = 1;
            emitter.field3C = 0xC;
            emitter.field3E = 0xA;
            emitter.field40 = 1;
            emitter.field42 = 4;
            emitter.field43 = 2;
            emitter.field46 = 0xFF;
            emitter.field47 = 0xFF;
            emitter.field44 = 3;
            emitter.field45 = 0xFF;
            emitter.field48 = 0xFF;
            emitter.field4D = 0xFF;
            emitter.field4E = 0xFF;
            emitter.field4F = 0xFF;
            emitter.field50 = 0xFF;
            emitter.field55 = 0xFF;
            emitter.field1C = 0.0f;
            emitter.field20 = 0.0f;
            emitter.field2C = 0;
            emitter.field49 = 0;
            emitter.field4A = 0;
            emitter.field4B = 0;
            emitter.field4C = 0;
            emitter.field51 = 0;
            emitter.field52 = 0;
            emitter.field53 = 0;
            emitter.field54 = 0;
            emitter.field56 = 0;
            emitter.field57 = 1;
            emitter.field58 = 0x24;
            emitter.field5C = 0x200005;
            emitter.field60 = 0x60600;
            emitter.field64 = 0xA;
            emitter.field66 = 0x19;
            emitter.field68 = 1;
            emitter.field6A = 0;
            emitter.field6C = 1.0f;
            emitter.field70 = -1;
            emitter.field71 = 0;
            emitter.field72 = -1;
            emitter.field73 = -1;
            emitter.field14 = 8.25f;
            emitter.field18 = D_800AB188;
            emitter.field24 = 7.0f;
            emitter.field28 = 16.0f;
            func_15152B38(&emitter.field00, (u8)arg4, arg5);
        }
        if ((sp190 != 0) && (D_80082FA0 < 2)) {
            packet.position = *(Vec3 *)arg0;
            func_15145974(arg1, &packet.transform.y, &packet.transform.x);
            packet.field58 = 0;
            packet.field5C = 0;
            packet.field60 = 0xFF;
            packet.field62 = 0;
            packet.field63 = 0;
            packet.field64 = 0;
            packet.field65 = 0;
            packet.field66 = 0;
            packet.field67 = 0;
            packet.field68 = 2;
            packet.field6A = 0;
            packet.field6C = 0;
            packet.field70 = 0;
            packet.field72 = 0xC;
            packet.field74 = 0x15;
            packet.field00 = 1.0f;
            packet.field04 = 1.0f;
            packet.field1C = 1.0f;
            packet.field20 = 1.0f;
            packet.field24 = 1.0f;
            packet.field0C = D_800AB18C;
            packet.field08 = D_800AB18C;
            packet.transform.z = 0.0f;
            packet.field56 = (s16) sp190;
            if (sp18C != 0) {
                if (func_15145128(arg1, &normal.x, &sp80, &sp7C) != 0) {
                    temp_fv1_2 = (func_150ADA68() * 12.0f) + 3.0f;
                    packet.field54 = (func_150ADA20() % 11U) + 0x1E;
                    packet.field34 = -normal.x * temp_fv1_2;
                    packet.field38 = -normal.y * temp_fv1_2;
                    packet.field3C = -normal.z * temp_fv1_2;
                    packet.rotation.x = ((func_150ADA68() * D_800AB190) + D_800AB194) * D_800AB198;
                    packet.rotation.y = ((func_150ADA68() * D_800AB19C) + D_800AB1A0) * D_800AB1A4;
                    packet.rotation.z = ((func_150ADA68() * D_800AB1A8) + D_800AB1AC) * D_800AB1B0;
                    temp_ft1 = (func_150ADA68() * D_800AB1B4) + -744.0f;
                    packet.field50 = 0x39E8;
                    packet.field61 = 8;
                    packet.field4C = temp_ft1 * D_800AB1B8;
                    func_15132A4C(&packet.field00, 3, 0xFF, 0, (u8) (s32) arg4, arg5);
                }
            } else {
                aux.timer = (func_150ADA20() & 0xF) + 0x14;
                aux.angle = 0.0f;
                aux.rate = ((func_150ADA68() * D_800AB1BC) + D_800AB1BC) * D_800AB1C0;
                temp_ft0 = func_150ADA68() * D_800AB1C4;
                packet.field54 = 0x12C;
                packet.field34 = 0.0f;
                packet.field38 = 0.0f;
                packet.field3C = 0.0f;
                aux.amplitude = (temp_ft0 + 4000.0f) * D_800AB1C8;
                packet.rotation = packet.transform;
                packet.field50 = 0x3980;
                packet.field61 = 0xC;
                packet.field4C = 0.0f;
                temp_v0 = func_15132A4C(&packet.field00, 3, 0xFF, 0x10, (u8) (s32) arg4, arg5);
                if (temp_v0 != 0) {
                    func_10022EC0((u8 *)temp_v0 + 0x170, &aux.timer, 0x10U);
                }
            }
        }
        if ((sp19F != 0) && (sp197 != 0)) {
            func_15102920((func_150ADA68() * 20.0f) + 15.0f, 0xFF, &surface.words[0], &position.x, 0x12C, 1, 1, 0, (s32)(u8)arg4, arg5);
        }
        break;
    case 2:
        sp190 = 0x57;
        goto block_9;
    case 3:
        sp190 = 0x58;
        goto block_9;
    case 0:
        sp190 = 0x34;
        goto block_9;
    case 1:
        sp190 = 0x4D;
        goto block_9;
    default:
        sp190 = 0;
        goto block_9;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3480 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3480.s")

/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

s32 func_151D3D50(u8 *arg0) {
    typedef struct { s32 words[3]; } Copy3;
    typedef struct {
        s16 timer;
        u8 pad2[2];
        f32 angle;
        f32 rate;
        f32 amplitude;
    } State;
    State *temp_v0;

    temp_v0 = (State *)(arg0 + 0x170);
    if (temp_v0->timer > 0) {
        temp_v0->angle += temp_v0->rate * D_800BE9A4;
        temp_v0->angle = func_15144B68(temp_v0->angle);
        *(f32 *)((u8 *)arg0 + 0x24) = *(f32 *)((u8 *)arg0 + 0x54) + (func_15047D60(temp_v0->angle) * temp_v0->amplitude);
        temp_v0->timer = (s16) (temp_v0->timer - D_800BE9E4);
    } else {
        *(Copy3 *)((u8 *)arg0 + 0x20) = *(Copy3 *)((u8 *)arg0 + 0x50);
    }
    return 1;
}
/* Call context: func_15143134: unique active project prototype */
void func_15143134(f32 *, f32 *, s32);

void func_151D3E04(void *arg0, f32 *arg1, f32 *arg2, u8 arg3, f32 arg4) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x1D4);
    if (temp_v0 != 0) {
        func_15143134(arg2, arg1, (s32)((u8 (*)[0x40])temp_v0)[arg3]);
        return;
    }
    *(f32 *)((u8 *)arg1 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + arg4);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
extern u8 D_800CC2D0[];
s32 func_1505D1C4(f32, f32, f32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3E6C CURRENT (740) */
void func_151D3E6C(void *arg0, void *arg1, void *arg2, s32 arg3) {
    f32 x;
    f32 y;
    f32 z;
    s32 offset;
    u16 var_v1;
    void *temp_v0;

    x = (*(f32 *)arg1 + *(f32 *)arg2) * 0.5f;
    y = (*(f32 *)((u8 *)arg1 + 4) + *(f32 *)((u8 *)arg2 + 4)) * 0.5f;
    z = (*(f32 *)((u8 *)arg1 + 8) + *(f32 *)((u8 *)arg2 + 8)) * 0.5f;
    offset = (s32)arg0 - (s32)D_800CC2D0;
    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    if (temp_v0 != 0) {
        var_v1 = (u16)(*(u16 *)((u8 *)arg0 + 0x76) - *(s16 *)((u8 *)temp_v0 + 0x12));
    } else {
        var_v1 = *(u16 *)((u8 *)arg0 + 0x76);
    }
    func_1505D1C4(x, y, z, arg3, offset / 0x32C, var_v1, 0, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3E6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3E6C.s")
u32 func_150ADA20(void);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game200930Position {
    s32 x;
    s32 y;
    s32 z;
} Game200930Position;

typedef struct Game200930Particle {
    u8 type;
    s8 subtype;
    s16 duration;
    s8 flags;
} Game200930Particle;

void func_151D3F14(void *arg0, u8 arg1, s32 arg2) {
    Game200930Particle particle;
    Game200930Position position;

    particle.type = 3;
    particle.subtype = -1;
    particle.duration = (func_150ADA20() % 3U) + 4;
    particle.flags = 0;
    position.x = (s32)*(f32 *)((u8 *)arg0 + 0);
    position.y = (s32)*(f32 *)((u8 *)arg0 + 4);
    position.z = (s32)*(f32 *)((u8 *)arg0 + 8);
    func_151602C0((u8 *)&particle, &position.x,
                   (func_150ADA20() % 13U) + 0x14,
                   0xFF, 0xE8, 0xAB, 0xFF, 0, 0, arg1, arg2);
}
void func_151D3FF4(s32 arg0, u8 arg1, s32 arg2) {
    Game200930Particle particle;
    Game200930Position position;

    particle.type = 3;
    particle.subtype = -1;
    particle.duration = (func_150ADA20() % 11U) + 0x14;
    particle.flags = 0;
    position.x = (s32)*(f32 *)(arg0 + 0);
    position.y = (s32)*(f32 *)(arg0 + 4);
    position.z = (s32)*(f32 *)(arg0 + 8);
    func_151602C0((u8 *)&particle, &position.x,
                   (func_150ADA20() % 24U) + 0x22,
                   0xFF, 0xA1, 0xA2, 0xFF, 0, 0, arg1, arg2);
}
f32 func_150484A0(f32, f32);
void func_1507C3E0(void *, s16 *, s16 *, s16 *);
extern f32 D_800AB1CC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D40D4 CURRENT (1532) */
void func_151D40D4(void *arg0, void *arg1, s32 arg2, void *arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    typedef struct { f32 x, y, z; } Vec3;
    u16 direction;
    Vec3 position;
    s16 height;
    s32 index;

    if (arg1 != 0) {
        direction = ((u32)(func_150484A0(*(f32 *)((u8 *)arg1 + 0), *(f32 *)((u8 *)arg1 + 8)) * D_800AB1CC) - 0x4000) | 1;
        position.x = *(f32 *)((u8 *)arg0 + 0) + (*(f32 *)((u8 *)arg1 + 0) * -90.0f);
        position.y = *(f32 *)((u8 *)arg0 + 4) + (*(f32 *)((u8 *)arg1 + 4) * -90.0f);
        position.z = *(f32 *)((u8 *)arg0 + 8) + (*(f32 *)((u8 *)arg1 + 8) * -90.0f);
    } else {
        position = *(Vec3 *)arg0;
        if (arg3 != 0) {
            func_1507C3E0(arg3, &height, 0, 0);
            position.y += (f32)(height >> 1);
        }
        direction = 0;
    }
    index = (arg2 - (s32)D_800CC2D0) / 0x32C;
    func_1505D1C4(*(f32 *)((u8 *)arg0 + 0), *(f32 *)((u8 *)arg0 + 4), *(f32 *)((u8 *)arg0 + 8), arg5, index, direction,
                  arg7, (s32)&position);
    func_1505D1C4(*(f32 *)((u8 *)arg0 + 0), *(f32 *)((u8 *)arg0 + 4), *(f32 *)((u8 *)arg0 + 8), arg6, index, direction,
                  arg7, (s32)&position);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D40D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D40D4.s")

f32 func_150484A0(f32, f32);
extern f32 D_800AB1D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D42E8 CURRENT (740) */
void func_151D42E8(void *arg0, void *arg1, s32 arg2, s32 arg3,
                   s32 arg4) {
    f32 temp_ft1;
    u32 var_v0;
    s32 var_v0_2;

    var_v0 = 0;
    if (arg1 != 0) {
        temp_ft1 = func_150484A0(*(f32 *)arg1,
                                 *(f32 *)((u8 *)arg1 + 8)) *
                   D_800AB1D0;
        var_v0_2 = (u32)temp_ft1;
        var_v0 = var_v0_2 - 0x4000;
        var_v0 |= 1;
        var_v0 &= 0xFFFF;
    }
    func_1505D1C4(*(f32 *)arg0, *(f32 *)((u8 *)arg0 + 4),
                  *(f32 *)((u8 *)arg0 + 8), arg4,
                  (arg2 - (s32)D_800CC2D0) / 0x32C, var_v0, 0, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D42E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D42E8.s")
void func_1503F404(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_150ADA68(void);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_800AB1D4;
extern f32 D_800AB1D8;
extern f32 D_800AB1DC;
extern f32 D_800AB1E0;
extern f32 D_800AB1E4;
extern f32 D_800AB1E8;
extern f32 D_800AB1EC;
extern f32 D_800AB1F0;
extern f32 D_800AB1F4;
extern f32 D_800AB1F8;

typedef struct Game200930TransformPacket {
    f32 field00;
    f32 field04;
    f32 field08;
    f32 field0C;
    f32 rotation[3];
    f32 scale[3];
    Game200930Position position;
    f32 velocity[3];
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    s32 field50;
    s16 field54;
    s16 field56;
    u8 field58;
    u8 pad59[3];
    s32 field5C;
    u8 field60;
    u8 field61;
    u8 field62;
    u8 field63;
    u8 field64;
    u8 field65;
    u8 field66;
    u8 field67;
    u8 field68;
    u8 pad69;
    u8 field6A;
    u8 pad6B;
    void *owner;
    u8 owner_type;
    u8 pad71;
    s16 field72;
    s16 field74;
} Game200930TransformPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D4408 CURRENT (2268) */
void func_151D4408(void *arg0, void *arg1, s32 arg2, void *arg3,
                   f32 arg4, s32 arg5, s32 arg6) {
    Game200930TransformPacket packet;
    f32 first[3];
    f32 second[3];
    f32 random;
    f32 speed;

    func_1503F404(arg2, (s32)&first[0], (s32)&first[1], (s32)&first[2],
                  (s32)&packet.rotation[0], (s32)&packet.rotation[1],
                  (s32)&packet.rotation[2], (s32)&second[0],
                  (s32)&second[1], (s32)&second[2]);
    packet.rotation[0] += 180.0f;
    random = func_150ADA68();
    packet.field00 = 1.0f;
    packet.field04 = 1.0f;
    packet.field0C = D_800AB1D4 * arg4;
    packet.field08 = packet.field0C;
    packet.scale[0] = 1.0f;
    packet.scale[1] = 1.0f;
    packet.scale[2] = 1.0f;
    packet.position = *(Game200930Position *)arg0;
    speed = ((random * 105.0f) + 199.0f) * D_800AB1D8;
    packet.velocity[0] = *(f32 *)arg1 * speed;
    packet.velocity[1] = *(f32 *)((u8 *)arg1 + 4) * speed;
    packet.velocity[2] = *(f32 *)((u8 *)arg1 + 8) * speed;
    packet.field40 = ((func_150ADA68() * D_800AB1DC) + D_800AB1E0) * D_800AB1E4;
    packet.field44 = 0.0f;
    packet.field48 = ((func_150ADA68() * D_800AB1E8) + D_800AB1EC) * D_800AB1F0;
    packet.field4C = ((func_150ADA68() * 320.0f) + D_800AB1F4) * D_800AB1F8;
    packet.field50 = 0x29E8;
    packet.field54 = (func_150ADA20() & 7) + 0x1C;
    packet.field56 = 0x25;
    packet.field58 = 0;
    packet.field5C = 0;
    packet.field60 = 0xFF;
    packet.field61 = 8;
    packet.field62 = 0;
    packet.field63 = 0;
    packet.field64 = 0;
    packet.field65 = 0;
    packet.field66 = 0;
    packet.field67 = 0;
    packet.field68 = 2;
    packet.field6A = 1;
    packet.owner = arg3;
    packet.field72 = 6;
    packet.field74 = 0x2A;
    packet.owner_type = *(u8 *)((u8 *)arg3 + 0x3B);
    func_15132A4C(&packet, 3, 0xFF, 0, (u8)arg5, arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D4408 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4408.s")

void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_151D4668(void *arg0) {
    struct {
        void *sp18;
        volatile u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32 *)&sp, 0x3C, (s32)arg0);
}
void *func_10022EC0(void *, const void *, u32);
u8 *func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
extern void (*D_8008FC70[])(u8 *, s16, void *);

typedef struct Game200930SpawnPacket {
    u8 *owner;
    u8 type;
    u8 pad5;
    s16 variant;
    u8 subtype;
    u8 pad9[3];
    f32 value;
    u8 flags;
    u8 pad11[3];
    s32 callback_data[3];
} Game200930SpawnPacket;

void func_151D469C(u8 *arg0, u8 arg1, s16 arg2, u8 arg3, s32 arg4) {
    Game200930SpawnPacket packet;
    u8 *result;

    packet.owner = arg0;
    packet.type = arg0[0x3B];
    packet.subtype = arg1;
    packet.value = 0.0f;
    packet.variant = -1;
    packet.flags = 0;
    if (arg1 == 6) {
        packet.variant = 0x82;
    }
    if ((*(s32 *)(arg0 + 0x1D4) != 0) &&
        ((arg0[0x74] & 0xF) != 0xF)) {
        D_8008FC70[arg1](arg0, packet.variant, packet.callback_data);
        packet.flags |= 1;
    }
    result = func_15149130(arg2, -1, 0x41, -1, 1, 0x35, 0x20, arg3, arg4);
    if (result != 0) {
        func_10022EC0(result + 0x28, &packet, 0x20U);
    }
}
f32 func_15143E64(void *);
void *func_15130280(void *, u8, void *, s32, u8, s32);
extern f32 D_800AB1FC;
extern f32 D_800AB200;
extern f32 D_800AB204;
extern f32 D_800AB208;
extern f32 D_800AB20C;
extern f32 D_800AB210;
extern f32 D_800AB214;
extern f32 D_800BE9A8;

typedef struct Game200930TrailDescriptor {
    s32 field00;
    s32 field04;
    s16 field08;
    s16 field0A;
    s32 field0C;
    s32 field10;
    s8 field14;
    s8 field15;
    s8 field16;
    s8 field17;
    s8 field18;
    s8 field19;
    s8 field1A;
    s8 field1B;
    s8 field1C;
    s8 field1D;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    f32 field50;
    f32 field54;
    s32 field58;
    u8 pad5C[0x4];
    s8 field60;
    s8 field61;
    s8 field62;
    s8 field63;
    s8 field64;
    s8 field65;
    u8 pad66[0xA];
} Game200930TrailDescriptor;

typedef struct Game200930TrailAux {
    s8 field0, field1, field2, field3;
    f32 field4, field8, fieldC;
} Game200930TrailAux;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D4794 CURRENT (11658) */
void func_151D4794(void *arg0) {
    typedef struct { f32 x, y, z; } Vec3;
    Vec3 position;
    Vec3 delta;
    Game200930TrailDescriptor descriptor;
    Game200930TrailAux aux;
    f32 temp_fs0;
    f32 temp_ft3;
    f32 temp_ft5;
    f32 temp_fv0;
    s32 temp_s1;
    void *temp_v0;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a3;
    Game200930SpawnPacket *temp_s0;

    temp_a3 = *(u8 **)((u8 *)arg0 + 0x28);
    position = *(Vec3 *)((u8 *)arg0 + 0x3C);
    temp_s0 = (Game200930SpawnPacket *)((u8 *)arg0 + 0x28);
    temp_s1 = *(u8 *)((u8 *)arg0 + 0x38) & 1;
    if ((*(s32 *)((u8 *)temp_a3 + 0) == 0) || (temp_s0->type != *(u8 *)((u8 *)temp_a3 + 0x3B))) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        return;
    }
    if ((*(s32 *)((u8 *)temp_a3 + 0x1D4) != 0) && ((*(u8 *)((u8 *)temp_a3 + 0x74) & 0xF) != 0xF)) {
        D_8008FC70[temp_s0->subtype](temp_a3, temp_s0->variant, (u8 *)temp_s0 + 0x14);
        temp_s0->flags = (u8) (temp_s0->flags | 1);
    }
    if (temp_s1 != 0) {
        delta.x = *(f32 *)((u8 *)(u8 *)temp_s0 + 0x14) - position.x;
        delta.y = *(f32 *)((u8 *)temp_s0 + 0x18) - position.y;
        delta.z = *(f32 *)((u8 *)temp_s0 + 0x1C) - position.z;
        if (!(func_15143E64(&delta.x) > 5.0f)) {
            temp_s0->value = (f32) (temp_s0->value + ((D_800AB1FC + (func_150ADA68() * D_800AB200)) * D_800BE9A4));
            if (temp_s0->value > 1.0f) {
                descriptor.field1D = 0x6C;
                descriptor.field08 = 0x5103;
                descriptor.field00 = 0x200005;
                descriptor.field1E = 0x46;
                descriptor.field20 = 3;
                descriptor.field58 = 0x90DE07;
                descriptor.field60 = 8;
                descriptor.field61 = 6;
                descriptor.field62 = 0x20;
                descriptor.field63 = -1;
                descriptor.field04 = 0;
                descriptor.field0C = 0;
                descriptor.field10 = 0;
                descriptor.field64 = -1;
                descriptor.field65 = 0;
                descriptor.field22 = 0x46;
                descriptor.field14 = 0xDD;
                descriptor.field15 = 0xD3;
                descriptor.field16 = 0xCD;
                descriptor.field17 = 0xFF;
                descriptor.field18 = 0x57;
                descriptor.field19 = 0x55;
                descriptor.field1A = 0x5A;
                descriptor.field1C = 0xFF;
                descriptor.field3C = 0.0f;
                descriptor.field40 = 0.0f;
                descriptor.field44 = 0.0f;
                temp_fs0 = D_800AB20C;
                aux.fieldC = D_800AB204;
                descriptor.field24 = D_800AB208;
                do {
                    temp_fv0 = func_150ADA68();
                    descriptor.field30 = (delta.x * temp_fv0) + position.x;
                    descriptor.field34 = (delta.y * temp_fv0) + position.y;
                    descriptor.field38 = (delta.z * temp_fv0) + position.z;
                    descriptor.field48 = delta.x * D_800BE9A8 * temp_fs0;
                    descriptor.field4C = delta.y * D_800BE9A8 * temp_fs0;
                    descriptor.field50 = delta.z * D_800BE9A8 * temp_fs0;
                    aux.field0 = func_150ADA20();
                    aux.field1 = func_150ADA20();
                    aux.field2 = (func_150ADA20() % 5U) + 4;
                    aux.field3 = (func_150ADA20() % 5U) + 4;
                    aux.field4 = func_150ADA68() * 6.0f;
                    aux.field8 = func_150ADA68() * 6.0f;
                    temp_ft5 = func_150ADA68() * D_800AB210;
                    descriptor.field58 &= ~0xC0;
                    descriptor.field54 = temp_ft5 + D_800AB214;
                    var_v1 = 0;
                    if (func_150ADA20() & 1) {
                        var_v1 = 0x80;
                    }
                                    if (func_150ADA20() & 1) {
                        var_v0 = 0x40;
                    } else {
                        var_v0 = 0;
                    }
                    descriptor.field58 |= var_v0 | var_v1;
                    descriptor.field1B = (func_150ADA20() % 61U) + 0x3C;
                    descriptor.field0A = (func_150ADA20() % 11U) + 0x46;
                    temp_ft3 = (func_150ADA68() * 40.0f) + 40.0f;
                    descriptor.field2C = temp_ft3;
                    descriptor.field28 = temp_ft3;
                    temp_v0 = func_15130280(&descriptor.field00, 1, 0, 0x10, (s32) *(u8 *)((u8 *)arg0 + 0xC), (s32) *(u8 *)((u8 *)arg0 + 1));
                    if (temp_v0 != 0) {
                        func_10022EC0((u8 *)temp_v0 + 0xA8, &aux.field0, 0x10U);
                    }
                    temp_s0->value = (f32) (temp_s0->value - 1.0f);
                } while (temp_s0->value > 1.0f);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D4794 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4794.s")

void func_15149514(s32, u8, s32, s32, s32);
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D4C38 CURRENT (1130) */
void func_151D4C38(u8 *arg0, void *arg1, u8 arg2) {
    u8 *temp_a2;
    u8 *temp_a2_2;

    if (arg2 == 0x3C) {
        if ((*(s32 *)((u8 *)arg0 + 0x28) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)(arg0 + 0x28) + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 4) {
        temp_a2 = arg0 + 0x28;
        if ((*(s32 *)((u8 *)arg0 + 0x28) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_a2 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            *(u8 *)((u8 *)temp_a2 + 0x10) = (u8) (*(u8 *)((u8 *)temp_a2 + 0x10) & 0xFFFE);
        }
    } else {
        temp_a2_2 = arg0 + 0x28;
        func_15149514((s32) arg1, arg2, (s32) temp_a2_2, (s32) (temp_a2_2 + 4), (s32) arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D4C38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4C38.s")
void func_15131828(s32, s32, s32, s32);
void func_15131958(void *, f32, s32);

s32 func_151D4D04(s32 arg0, s32 arg1) {
    u8 *sp20;
    u8 *temp_a2;

    temp_a2 = (u8 *)arg0 + 0xA8;
    sp20 = temp_a2;
    func_15131828(arg0, arg0 + 0xAC, (s32)temp_a2, arg0 + 0xAA);
    func_15131958((void *)(arg0 + 0x58), *(f32 *)(temp_a2 + 0xC),
                  (s32)temp_a2);
    return 1;
}
/* Call context: func_151D469C: unique active project prototype */
void func_151D469C(u8 *, u8, s16, u8, s32);

void func_151D4D58(u8 *arg0) {
    func_151D469C(arg0, 0, 0x50, 0xFF, 1);
    func_151D469C(arg0, 1, 0x50, 0xFF, 1);
}
void func_1507DE4C(s32);
void func_15137610(void *, void *, void *, s32, s32, s32);
s32 func_1505D024(void *, s32, s32, s32);
void func_15138C80(void *, s32, s32);
void func_151C2050(s32, void *, s32, s32, f32);
extern f32 D_800AB218;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D4DAC CURRENT (650) */
void func_151D4DAC(void *arg0, s32 arg1, void *arg2, void *arg3, void *arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 sp24;
    s32 temp_v0_3;

    if ((*(u8 *)((u8 *)arg0 + 4) == 9) || (*(u8 *)((u8 *)arg0 + 4) == 0xF) || (*(u8 *)((u8 *)arg0 + 4) == 0x10) || (*(u8 *)((u8 *)arg0 + 4) == 0x12) || (*(u8 *)((u8 *)arg0 + 4) == 0x17) || (*(u8 *)((u8 *)arg0 + 4) == 0x1B) || (*(u8 *)((u8 *)arg0 + 4) == 0x1E) || (*(u8 *)((u8 *)arg0 + 4) == 0x28) || (*(u8 *)((u8 *)arg0 + 4) == 0x29) || (*(u8 *)((u8 *)arg0 + 4) == 0x2A) || (*(u8 *)((u8 *)arg0 + 4) == 0x2B) || (*(u8 *)((u8 *)arg0 + 4) == 0x2C) || (*(u8 *)((u8 *)arg0 + 4) == 0x2E) || (*(u8 *)((u8 *)arg0 + 4) == 0x38) || (*(u8 *)((u8 *)arg0 + 4) == 0x41) || (*(u8 *)((u8 *)arg0 + 4) == 0x42) || (*(u8 *)((u8 *)arg0 + 4) == 0x4B) || (*(u8 *)((u8 *)arg0 + 4) == 0x46) || (*(u8 *)((u8 *)arg0 + 4) == 0x47) || (*(u8 *)((u8 *)arg0 + 4) == 0x49) || (*(u8 *)((u8 *)arg0 + 4) == 0x4A) || (*(u8 *)((u8 *)arg0 + 4) == 0x4C) || (*(u8 *)((u8 *)arg0 + 4) == 0x4D) || (*(u8 *)((u8 *)arg0 + 4) == 0x4E) || (*(u8 *)((u8 *)arg0 + 4) == 0x4F) || (*(u8 *)((u8 *)arg0 + 4) == 0x52) || (*(u8 *)((u8 *)arg0 + 4) == 0x5D) || (*(u8 *)((u8 *)arg0 + 4) == 0x60) || (*(u8 *)((u8 *)arg0 + 4) == 0x61) || (*(u8 *)((u8 *)arg0 + 4) == 0x66) || (*(u8 *)((u8 *)arg0 + 4) == 0x67) || (*(u8 *)((u8 *)arg0 + 4) == 0x70) || (*(u8 *)((u8 *)arg0 + 4) == 0x73) || (*(u8 *)((u8 *)arg0 + 4) == 0x77) || (*(u8 *)((u8 *)arg0 + 4) == 0x7B) || (*(u8 *)((u8 *)arg0 + 4) == 0x89) || (*(u8 *)((u8 *)arg0 + 4) == 0x8C) || (*(u8 *)((u8 *)arg0 + 4) == 0x8E) || (*(u8 *)((u8 *)arg0 + 4) == 0x8F) || (*(u8 *)((u8 *)arg0 + 4) == 0x91) || (*(u8 *)((u8 *)arg0 + 4) == 0x9E) || (*(u8 *)((u8 *)arg0 + 4) == 0xA6) || (*(u8 *)((u8 *)arg0 + 4) == 0xAB) || (*(u8 *)((u8 *)arg0 + 4) == 0xAC) || (*(u8 *)((u8 *)arg0 + 4) == 0xB2) || (*(u8 *)((u8 *)arg0 + 4) == 0xB4) || (*(u8 *)((u8 *)arg0 + 4) == 0x5B)) {
        func_151C2050(arg1, arg2, arg6, 9,
                      arg4 != 0 ? *(f32 *)((u8 *)arg4 + 4) : 0.0f);
    }
    if (*(u8 *)((u8 *)arg0 + 0x1CA) == 0) {
        sp24 = 1;
    } else {
        sp24 = 0;
    }
    arg5 = arg5 | 0x60000;
    if ((arg4 != 0) && (*(u8 *)((u8 *)arg4 + 0x59) == 3) && (*(u8 *)((u8 *)arg4 + 0x58) == 0xA)) {
        if ((s32) *(u8 *)((u8 *)arg0 + 0x1CA) >= 3) {
            *(u8 *)((u8 *)arg0 + 0x1CA) = (u8) (*(u8 *)((u8 *)arg0 + 0x1CA) - 1);
        } else {
            *(u8 *)((u8 *)arg0 + 0x1CA) = 0U;
            func_1507DE4C((s32) arg0);
            func_15138C80(arg0, 0xFF, 1);
            arg5 = 0x100020;
        }
    }
    func_15137610(arg0, arg2, arg3, arg6, (s32)(u8)arg7, arg8);
    if (sp24 == 0) {
        temp_v0_3 = (u32) (func_150484A0(*(f32 *)((u8 *)arg6 + 0), *(f32 *)((u8 *)arg6 + 8)) * D_800AB218) & 0xFFFF;
        func_1505D024(arg0, arg5 | 0x80000, ((temp_v0_3 - 0x4000) | 1) & 0xFFFF, arg1 != 0 ? (arg1 - (s32)D_800CC2D0) / 812 : -1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D4DAC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4DAC.s")

void func_151D5148(void *arg0) {
    void *temp_v0;
    s16 temp_v1;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    temp_v1 = *(s16 *)((u8 *)temp_v0 + 0x24);
    if (temp_v1 > 0) {
        *(s16 *)((u8 *)temp_v0 + 0x24) = (s16) (temp_v1 - 1);
        temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    }
    *(s16 *)((u8 *)temp_v0 + 0x1AA) = (s16) (*(s16 *)((u8 *)temp_v0 + 0x1AA) + 1);
}
void func_151450B4(void *, void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5174 CURRENT (1549) */
void func_151D5174(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4,
                   void *arg5, void *arg6, void **arg7, void **arg8, void *arg9) {
    typedef struct {
        f32 x;
        f32 y;
        f32 z;
    } Vec3;
    typedef struct {
        u8 pad00[0x84];
        u8 flag;
        u8 pad85[0xAB];
        Vec3 direction;
        Vec3 position;
        u8 pad148[0x50];
        u8 mode;
    } Node;
    typedef struct {
        u8 pad00[0x1D4];
        void *active;
        u8 pad1D8[0x144];
        Node *node;
    } Actor;
    Vec3 *base;
    Vec3 first;
    Vec3 second;
    Node *node;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 scale;
    f32 baseX;

    if (((Actor *)arg0)->active != 0) {
        node = ((Actor *)arg0)->node;
        if (node != 0 && (node->mode == 2 || node->flag != 0)) {
            base = &node->position;
            func_151450B4(arg2, arg3, &first);
            func_151450B4(&first, arg4, &second);
            if (arg9 != 0) {
                baseX = base->x;
                dx = ((Vec3 *)arg9)->x - baseX;
                dy = ((Vec3 *)arg9)->y - base->y;
                dz = ((Vec3 *)arg9)->z - base->z;
            } else {
                baseX = base->x;
                dx = ((Vec3 *)arg1)->x - baseX;
                dy = ((Vec3 *)arg1)->y - base->y;
                dz = ((Vec3 *)arg1)->z - base->z;
            }
            node = ((Actor *)arg0)->node;
            scale = (second.x * dx + second.y * dy + second.z * dz) /
                    (second.x * node->direction.x + second.y * node->direction.y + second.z * node->direction.z);
            ((Vec3 *)arg5)->x = baseX + scale * node->direction.x;
            ((Vec3 *)arg5)->y = base->y + scale * ((Actor *)arg0)->node->direction.y;
            ((Vec3 *)arg5)->z = base->z + scale * ((Actor *)arg0)->node->direction.z;
            ((Vec3 *)arg6)->x = ((Actor *)arg0)->node->direction.x;
            ((Vec3 *)arg6)->y = ((Actor *)arg0)->node->direction.y;
            ((Vec3 *)arg6)->z = ((Actor *)arg0)->node->direction.z;
            *arg7 = arg5;
            *arg8 = arg6;
            return;
        }
    }
    *arg7 = 0;
    *arg8 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5174 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5174.s")
void func_15164F0C(u8, u8, void *, u8, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5334 CURRENT (928) */
void func_151D5334(void *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4,
                   u8 arg5, s32 arg6) {
    typedef struct {
        s32 x;
        s32 y;
        s32 z;
    } Position;
    struct {
        Position position;
        f32 value1;
        f32 value2;
        f32 value3;
        u32 pad_18;
    } data;
    s32 i;

    i = 0;
    data.position = *(Position *)arg0;
    data.value1 = arg1;
    data.value2 = arg2;
    data.value3 = arg3;
    if ((D_80082FA0 + 1) > 0) {
        do {
            func_15164F0C(arg4, i, &data, arg5, arg6);
            i++;
        } while (D_80082FA0 >= i);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5334 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5334.s")
u8 *func_151D8868(s8 *, s32, s32, s32);

typedef struct {
    s8 field0;
    u8 pad1;
    s16 field2;
    s8 field4;
    s8 field5;
    s8 field6;
    u8 pad7;
} Game200930EventDescriptor;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Game200930EventPosition;

typedef struct {
    Game200930EventPosition position;
    f32 value1;
    f32 value2;
    f32 value3;
    s8 index;
    u8 pad19[3];
} Game200930EventPayload;

void func_151D5404(void *arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4,
                   s16 arg5) {
    struct {
        Game200930EventDescriptor descriptor;
        Game200930EventPayload payload;
        u32 pad54;
    } locals;
    u8 *temp_v0;
    s32 var_s0;

    locals.payload.position = *(Game200930EventPosition *)arg0;
    locals.payload.value1 = arg1;
    locals.payload.value2 = arg2;
    locals.descriptor.field0 = 1;
    locals.payload.value3 = arg3;
    locals.descriptor.field2 =
        (s16)((func_150ADA20() % (u32)(arg5 + 1)) + arg4);
    locals.descriptor.field4 = 0;
    locals.descriptor.field6 = 0;
    var_s0 = 0;
    if ((D_80082FA0 + 1) > 0) {
        do {
            locals.descriptor.field5 = 1 << var_s0;
            locals.payload.index = var_s0;
            temp_v0 = func_151D8868((s8 *)&locals.descriptor, 0x1C, 0xFF, 0);
            if (temp_v0 != 0) {
                func_10022EC0(temp_v0 + 0x18, &locals.payload, 0x1CU);
            }
            var_s0 += 1;
        } while (D_80082FA0 >= var_s0);
    }
}
typedef struct {
    s16 field00;
    s16 field02;
    s16 field04;
    s16 field06;
    s32 field08;
    s32 field0C;
    Game200930EventPosition position;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    s32 field34;
    s32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    s16 field4C;
    s16 field4E;
    s16 field50;
    s16 field52;
    s16 field54;
    s16 field56;
    s8 field58;
    u8 pad59[3];
} Game200930Effect;

void func_1514FCE8(s16 *, s32, s32);
extern f32 D_800AB21C;
extern f32 D_800AB220;
extern f32 D_800AB224;
extern f32 D_800AB228;
extern f32 D_800AB22C;
extern f32 D_800AB230;
extern f32 D_800AB234;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5514 CURRENT (778) */
void func_151D5514(s32 arg0, u8 arg1, s32 arg2) {
    Game200930Effect effect;

    effect.field00 = 0;
    effect.field02 = 0xFF;
    effect.field04 = -0x40;
    effect.field06 = 0x4A;
    effect.field08 = 9;
    effect.field0C = 3;
    effect.position = *(Game200930EventPosition *)arg0;
    effect.field1C = D_800AB21C;
    effect.field20 = 214.0f;
    effect.field24 = 203.0f;
    effect.field28 = D_800AB220;
    effect.field34 = 7;
    effect.field38 = 3;
    effect.field4C = 0xF;
    effect.field4E = 0xF;
    effect.field50 = 0x64;
    effect.field52 = 0x64;
    effect.field54 = 0xC;
    effect.field56 = 0x14;
    effect.field58 = 0;
    effect.field2C = D_800AB224;
    effect.field30 = D_800AB228;
    effect.field3C = 45.0f;
    effect.field40 = D_800AB22C;
    effect.field44 = D_800AB230;
    effect.field48 = D_800AB234;
    func_1514FCE8(&effect.field00, arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5514 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5514.s")
void func_151541B8(s32, f32, s32, f32, f32, u8, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_151D3FF4(s32, u8, s32);
void func_151D5514(s32, u8, s32);

void func_151D5648(s32 arg0, u8 arg1, s32 arg2) {
    volatile s32 spacer;
    f32 random_float;
    u32 random_value;

    func_151D5514(arg0, arg1, arg2);
    func_151D3FF4(arg0, arg1, arg2);
    random_float = func_150ADA68();
    random_value = (func_150ADA20() % 56U) + 0xC8;
    func_151541B8(arg0, (random_float * 4.0f) + 12.0f, 0x3FD20C49,
                  (f32)random_value, 0.0f, arg1, arg2);
}
void func_15145EA4(s32 *, s32 *, s32, s32);
void func_151D4408(void *, void *, s32, void *, f32, s32, s32);

typedef struct Game200930Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game200930Vec3;

typedef struct Game200930RayLocals {
    Game200930Vec3 *second_ptr;
    Game200930Vec3 *first_ptr;
    s32 input[2];
    s32 transform;
    Game200930Vec3 first;
    Game200930Vec3 second;
} Game200930RayLocals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5714 CURRENT (2337) */
void func_151D5714(void *arg0, s32 arg1, s32 arg2, u8 arg3,
                   f32 arg4, u8 arg5, s32 arg6) {
    Game200930RayLocals locals;
    s32 temp_a2;
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x1D4);
    if ((temp_v0 != 0) && ((*(u8 *)((u8 *)arg0 + 0x74) & 0xF) != 0xF)) {
        temp_a2 = temp_v0 + (arg3 << 6);
        locals.second_ptr = &locals.second;
        locals.first_ptr = &locals.first;
        locals.transform = temp_a2;
        locals.input[0] = arg1;
        locals.input[1] = arg2;
        func_15145EA4(locals.input, (s32 *)&locals.second_ptr, temp_a2, 2);
        locals.first.x -= locals.second.x;
        locals.first.y -= locals.second.y;
        locals.first.z -= locals.second.z;
        func_151D4408(&locals.second, &locals.first, locals.transform, arg0,
                       arg4, arg5, arg6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5714 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5714.s")
void func_151D5174(void *, void *, void *, void *, void *, void *, void *, void **, void **, void *);
void func_151D5A18(void *, s32, void *, void *, void *, s32, u8);
void func_150636A4(void *);
void func_15081690(void *, f32, f32, f32, f32, f32, f32, void *, f32, s32, s32, s32, s32, s32, s32);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
extern s32 D_8008FC8C[];
extern u8 *D_8008FC94[];
extern f32 D_800AB238;
extern f32 D_800AB23C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D57F8 CURRENT (180) */
void func_151D57F8(void *arg0, s32 arg1) {
    Game200930Vec3 position;
    Game200930Vec3 direction;
    Game200930Vec3 first;
    Game200930Vec3 second;
    Game200930Vec3 result_position;
    Game200930Vec3 result_direction;
    Game200930Vec3 *position_ptr;
    Game200930Vec3 *direction_ptr;
    Game200930Vec3 delta;
    f32 length;
    f32 scale;

    func_151D5A18(arg0, (s32)&position, &direction, &first, &second,
                  D_8008FC8C[(u8)arg1], *D_8008FC94[(u8)arg1]);
    func_151D5174(arg0, &position, &direction, &first, &second,
                  &result_position, &result_direction, (void **)&position_ptr,
                  (void **)&direction_ptr, 0);
    *(u8 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x109) = 1;
    if (position_ptr == 0) {
        position_ptr = &position;
    }
    if (direction_ptr == 0) {
        direction_ptr = &direction;
    }
    scale = D_800AB238;
    *(f32 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xB8) = position_ptr->x + direction_ptr->x * scale;
    *(f32 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xBC) = position_ptr->y + direction_ptr->y * scale;
    *(f32 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xC0) = position_ptr->z + direction_ptr->z * scale;
    if (*(u8 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x109) != 0) {
        delta.x = *(f32 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xB8) - position.x;
        delta.y = *(f32 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xBC) - position.y;
        delta.z = *(f32 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xC0) - position.z;
        if (func_15145128(&delta.x, &delta.x, &length, 0) != 0) {
            func_15081690(arg0, position.x, position.y, position.z,
                          delta.x, delta.y, delta.z,
                          *(u8 **)((u8 *)arg0 + 0x31C) + 0xB0,
                          length * D_800AB23C, 0, 0, 0, -1, 0, 0);
        }
    }
    func_150636A4(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D57F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D57F8.s")

/* Call context: func_15145740: unique active project prototype */
/* Call context: func_15145EA4: unique active project prototype */
void func_15145740(void *, void *, void *, void *, f32);
void func_15145EA4(s32 *, s32 *, s32, s32);
extern f32 D_800AB240;
extern f32 D_800AB244;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

f32 fabsf(f32);
#pragma intrinsic(fabsf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5A18 CURRENT (565) */
void func_151D5A18(void *arg0, s32 arg1, void *arg2, void *arg3, void *arg4, s32 arg5, u8 arg6) {
    s32 sp44;
    s32 sp40;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    f32 var_ft4;
    f32 var_ft5;

    func_15145740(arg0, arg2, arg3, arg4, D_800AB240);
    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        sp40 = arg1;
        sp44 = arg5;
        func_15145EA4(&sp44, &sp40, *(s32 *)((u8 *)arg0 + 0x1D4) + (arg6 << 6), 1);
        return;
    }
    temp_fa1 = *(f32 *)((u8 *)arg2 + 0);
    if ((D_800AB244 < fabsf(temp_fa1)) || (D_800AB244 < fabsf(*(f32 *)((u8 *)arg2 + 8)))) {
        temp_fv1 = *(f32 *)((u8 *)arg2 + 8);
        temp_fa0 = 1.0f / sqrtf((temp_fa1 * temp_fa1) + (temp_fv1 * temp_fv1));
        var_ft4 = temp_fv1 * temp_fa0;
        var_ft5 = -temp_fa1 * temp_fa0;
    } else {
        var_ft4 = 1.0f;
        var_ft5 = 0.0f;
    }
    *(f32 *)((u8 *)arg1 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + (34.0f * var_ft5));
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + 49.0f);
    *(f32 *)((u8 *)arg1 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C) + (34.0f * var_ft4));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5A18 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5A18.s")
s32 func_151452C4(void *, void *, s32, f32, s32, s32, f32 *, f32 *);
extern s32 (*D_80086C90[])(void *, s32, s32);
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5B6C CURRENT (4088) */
s32 func_151D5B6C(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    Game200930Vec3 position;
    Game200930Vec3 first;
    Game200930Vec3 second;
    f32 near_distance;
    f32 far_distance;
    f32 radius;
    s16 width;
    s16 depth;
    s32 index;
    s32 result;
    u8 *actor;
    s32 selector;

    selector = (s8)arg3;
    result = -1;
    index = 0;
    do {
        actor = D_800CC2D0 + (index * 0x32C);
        if (*(s32 *)actor != 0 && actor[5] != 3 &&
            (D_800BE9F0 == 0x23 || actor[4] != 0xFF) &&
            actor != (u8 *)arg2 && (*(s32 *)(actor + 0xF8) & 0x40) &&
            (selector == -1 || D_80086C90[selector](actor, arg2, arg4) != 0)) {
            width = *(s16 *)(actor + 0xD2);
            depth = *(s16 *)(actor + 0xD4);
            if (width < depth) {
                radius = (f32)depth;
            } else {
                radius = (f32)width;
            }
            position.x = *(f32 *)(actor + 0x14);
            position.y = *(f32 *)(actor + 0x18) + (f32)*(s16 *)(actor + 0xD6);
            position.z = *(f32 *)(actor + 0x1C);
            if (func_151452C4(arg0, arg1, (s32)&position, 2.0f * radius,
                (s32)&first, (s32)&second, &near_distance, &far_distance) != 0) {
                result &= ~(1 << index);
            }
        }
        index = (index + 1) & 0xFF;
    } while (index < 0x19);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5B6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5B6C.s")
s32 func_10003C40(s32, s32, s32, s32);
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5D60 CURRENT (1085) */
void func_151D5D60(volatile s32 arg0, s16 arg1, s32 arg2, s32 *arg3, u8 *arg4) {
    u8 fallback;
    s32 *entry;
    s32 value;
    s32 allocated;
    s32 offset;

    if (arg4 == 0) {
        arg4 = &fallback;
    }
    *arg4 = 0;
    entry = (s32 *)(arg0 + (arg1 * 4));
    value = *entry;
    if (value == 0) {
        allocated = func_10003C40(arg2 * 2, 1, 2, 1);
        *entry = allocated;
        if (allocated == 0) {
            *arg3 = 0;
            return;
        }
        *arg4 = 1;
        value = *entry;
    }
    offset = arg2;
    if (D_800BE9C0 != 0) {
        offset = 0;
    }
    *arg3 = offset + value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5D60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5D60.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5E30 CURRENT (405) */
void func_151D5E30(Game200930ResourceSlots *arg0) {
    register s32 resource;
    s32 index;

    index = 0;
    do {
        resource = arg0->entries[index];
        if (resource != 0) {
            func_100043B4(resource, 3);
        }
        index = (index + 1) & 0xFF;
    } while (index < 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5E30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5E30.s")
