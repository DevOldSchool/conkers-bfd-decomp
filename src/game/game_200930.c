#include "types.h"

/*
 * Reviewed source unit: src/game/game_200930.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D3480
 * - func_151D3D50
 * - func_151D3E04
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3480.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3D50 CURRENT (739) */
s32 func_151D3D50(u8 *arg0) {
    void *sp18;
    f32 temp_fv0;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x170);
    if (*(s16 *)((u8 *)arg0 + 0x170) > 0) {
        *(f32 *)((u8 *)temp_v0 + 4) = (f32) (*(f32 *)((u8 *)temp_v0 + 4) + (*(f32 *)((u8 *)temp_v0 + 8) * D_800BE9A4));
        sp18 = temp_v0;
        temp_fv0 = func_15144B68(*(f32 *)((u8 *)temp_v0 + 4));
        *(f32 *)((u8 *)temp_v0 + 4) = temp_fv0;
        *(f32 *)((u8 *)arg0 + 0x24) = (f32) ((func_15047D60(temp_fv0) * *(f32 *)((u8 *)temp_v0 + 0xC)) + *(f32 *)((u8 *)arg0 + 0x54));
        *(s16 *)((u8 *)arg0 + 0x170) = (s16) (*(s16 *)((u8 *)arg0 + 0x170) - D_800BE9E4);
    } else {
        *(s32 *)((u8 *)arg0 + 0x20) = (s32) *(s32 *)((u8 *)arg0 + 0x50);
        *(f32 *)((u8 *)arg0 + 0x24) = (f32) *(f32 *)((u8 *)arg0 + 0x54);
        *(s32 *)((u8 *)arg0 + 0x28) = (s32) *(s32 *)((u8 *)arg0 + 0x58);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3D50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3D50.s")
/* Call context: func_15143134: unique active project prototype */
void func_15143134(f32 *, f32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3E04 CURRENT (373) */
void func_151D3E04(void *arg0, f32 *arg1, f32 *arg2, s32 arg3, f32 arg4) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x1D4);
    if (temp_v0 != 0) {
        func_15143134(arg2, arg1, temp_v0 + ((arg3 & 0xFF) << 6));
        return;
    }
    *(f32 *)((u8 *)arg1 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + arg4);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D3E04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3E04.s")
extern u8 D_800CC2D0[];
s32 func_1505D1C4(f32, f32, f32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D3E6C CURRENT (2377) */
void func_151D3E6C(void *arg0, void *arg1, void *arg2) {
    u16 var_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    if (temp_v0 != 0) {
        var_v1 = (u16)(*(u16 *)((u8 *)arg0 + 0x76) - *(s16 *)((u8 *)temp_v0 + 0x12));
    } else {
        var_v1 = *(u16 *)((u8 *)arg0 + 0x76);
    }
    func_1505D1C4(((*(f32 *)arg1) + (*(f32 *)arg2)) * 0.5f,
                  ((*(f32 *)((u8 *)arg1 + 4)) + (*(f32 *)((u8 *)arg2 + 4))) * 0.5f,
                  ((*(f32 *)((u8 *)arg1 + 8)) + (*(f32 *)((u8 *)arg2 + 8))) * 0.5f,
                  ((s32)arg0 - (s32)D_800CC2D0) / 0x32C, var_v1, 0, 0);
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5174 CURRENT (2906) */
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
    Actor *actor = arg0;
    Node *node;
    Vec3 first;
    Vec3 second;
    void *base;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 scale;

    if (actor->active != 0) {
        node = actor->node;
        if (node != 0 && (node->mode == 2 || node->flag != 0)) {
            base = &node->position;
            func_151450B4(arg2, arg3, &first);
            func_151450B4(&first, arg4, &second);
            if (arg9 != 0) {
                dx = ((Vec3 *)arg9)->x - ((Vec3 *)base)->x;
                dy = ((Vec3 *)arg9)->y - ((Vec3 *)base)->y;
                dz = ((Vec3 *)arg9)->z - ((Vec3 *)base)->z;
            } else {
                dx = ((Vec3 *)arg1)->x - ((Vec3 *)base)->x;
                dy = ((Vec3 *)arg1)->y - ((Vec3 *)base)->y;
                dz = ((Vec3 *)arg1)->z - ((Vec3 *)base)->z;
            }
            node = actor->node;
            scale = (second.x * dx + second.y * dy + second.z * dz) /
                    (second.x * node->direction.x + second.y * node->direction.y + second.z * node->direction.z);
            ((Vec3 *)arg5)->x = ((Vec3 *)base)->x + scale * node->direction.x;
            ((Vec3 *)arg5)->y = ((Vec3 *)base)->y + scale * actor->node->direction.y;
            ((Vec3 *)arg5)->z = ((Vec3 *)base)->z + scale * actor->node->direction.z;
            ((Vec3 *)arg6)->x = actor->node->direction.x;
            ((Vec3 *)arg6)->y = actor->node->direction.y;
            ((Vec3 *)arg6)->z = actor->node->direction.z;
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D57F8.s")
/* Call context: func_15145740: unique active project prototype */
/* Call context: func_15145EA4: unique active project prototype */
void func_15145740(void *, void *, void *, void *, f32);
void func_15145EA4(s32 *, s32 *, s32, s32);
extern f32 D_800AB240;
extern f32 D_800AB244;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5A18 CURRENT (4979) */
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
