#include "types.h"

/*
 * Reviewed source unit: src/game/game_133190.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15105CE0
 * - func_1510608C
 * - func_15106214
 * - func_15106610
 * - func_151067B8
 * - func_15106F98
 * - func_151070F8
 * - func_151072BC
 * - func_15107604
 * - func_15107700
 * - func_15107AE0
 * - func_15107B78
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game133190Subobject {
    u8 pad0[8];
    s32 field_8;
} Game133190Subobject;

typedef struct Game133190Target {
    u8 pad0[0x28];
    Game133190Subobject subobject;
} Game133190Target;

typedef struct Game133190Holder {
    Game133190Target *target;
} Game133190Holder;

typedef struct Game133190Object {
    u8 pad0[0x60];
    Game133190Holder *holder;
} Game133190Object;

typedef s32 (*Game133190EventCallback)(void *, u8 *);
typedef struct Game133190Triple {
    s32 x;
    s32 y;
    s32 z;
} Game133190Triple;
extern Game133190EventCallback D_80088C10[];
extern s32 D_800BE9E4;
void func_1516972C(void *);
void func_15106214(s32);
void func_15106610(void *);
u32 func_150ADA20(void);

#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15105CE0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510608C CURRENT (91) */
void func_1510608C(void *arg0) {
    u8 sp2B[1];
    Game133190EventCallback temp_v1;
    s8 temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;

    sp2B[0] = 0;
    temp_v0 = *(s8 *)((u8 *)arg0 + 0x44);
    if (temp_v0 != -1) {
        temp_v1 = D_80088C10[temp_v0];
        if ((temp_v1 != 0) && (temp_v1(arg0, sp2B) == 0)) {
            func_1516972C(arg0);
        }
    }
    if (*(u8 *)((u8 *)arg0 + 0x12) & 1) {
        *(s16 *)((u8 *)arg0 + 0x10) = (s16)(*(s16 *)((u8 *)arg0 + 0x10) - D_800BE9E4);
        if (*(s16 *)((u8 *)arg0 + 0x10) < 0) {
            func_1516972C(arg0);
        }
    }
    if (sp2B[0] != 0) {
        func_15106214((s32)arg0);
    }
    *(s16 *)((u8 *)arg0 + 0x68) = (s16)(*(s16 *)((u8 *)arg0 + 0x68) - D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0x68) < 0) {
        func_15106610(arg0);
        *(s16 *)((u8 *)arg0 + 0x68) = (s16)((func_150ADA20() % (u32)(*(s16 *)((u8 *)arg0 + 0x56) + 1)) + *(s16 *)((u8 *)arg0 + 0x54));
    }
    temp_v0_2 = *(void **)((u8 *)arg0 + 0x6C);
    if (temp_v0_2 != 0) {
        *(Game133190Triple *)((u8 *)temp_v0_2 + 0x40) = *(Game133190Triple *)((u8 *)arg0 + 0x14);
    }
    temp_v0_3 = *(void **)((u8 *)arg0 + 0x70);
    if (temp_v0_3 != 0) {
        *(Game133190Triple *)((u8 *)temp_v0_3 + 0x40) = *(Game133190Triple *)((u8 *)arg0 + 0x38);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510608C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_1510608C.s")
s32 func_151061E0(s32 arg0) {
    return arg0 + 0x88;
}
void *func_151061EC(u8 *arg0) {
    s32 temp_v1;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x48);
    return (void *)((s32)arg0 + (temp_v1 * 0x34) + 0x88);
}
/* Call context: func_151061E0: unique active project prototype */
/* Call context: func_151064B4: unique active project prototype */
/* Call context: func_151064DC: unique active project prototype */
/* Call context: func_15106510: unique active project prototype */
/* Call context: func_15106540: unique active project prototype */
/* Call context: func_15106558: unique active project prototype */
/* Call context: func_15106584: unique active project prototype */
/* Call context: func_151065BC: unique active project prototype */
/* Call context: func_151065EC: unique active project prototype */
f32 func_151064B4(f32);
f32 func_151064DC(f32);
f32 func_15106510(f32);
f32 func_15106540(f32);
f32 func_15106558(f32);
f32 func_15106584(f32);
f32 func_151065BC(f32);
f32 func_151065EC(f32);
s32 func_15146078(void *, void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15106214 CURRENT (940) */
void func_15106214(s32 arg0) {
    f32 sp78;
    f32 sp64;
    f32 sp60;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fs0;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;

    temp_v0 = func_151061E0(arg0);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x64);
    var_s2 = 0;
    var_fs0 = temp_fv1;
    if (*(s32 *)((u8 *)arg0 + 0x48) > 0) {
        var_s1 = temp_v0;
        var_s3 = temp_v0 + 0x10;
        var_s4 = temp_v0 + 0x1C;
        var_s5 = temp_v0 + 0x28;
        sp78 = temp_fv1;
        do {
            *(f32 *)((u8 *)var_s1 + 0) = var_fs0;
            temp_fs5 = func_151064B4(var_fs0);
            sp64 = func_151064DC(var_fs0);
            sp60 = func_15106510(var_fs0);
            temp_fs1 = func_15106540(var_fs0);
            temp_fs2 = func_15106558(var_fs0);
            temp_fs3 = func_15106584(var_fs0);
            temp_fs4 = func_151065BC(var_fs0);
            temp_fv0 = func_151065EC(var_fs0);
            *(f32 *)((u8 *)var_s1 + 4) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38) * temp_fs1) + ((*(f32 *)((u8 *)arg0 + 0x14) * temp_fs5) + (*(f32 *)((u8 *)arg0 + 0x20) * sp64) + (*(f32 *)((u8 *)arg0 + 0x2C) * sp60)));
            *(f32 *)((u8 *)var_s1 + 8) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C) * temp_fs1) + ((*(f32 *)((u8 *)arg0 + 0x18) * temp_fs5) + (*(f32 *)((u8 *)arg0 + 0x24) * sp64) + (*(f32 *)((u8 *)arg0 + 0x30) * sp60)));
            *(f32 *)((u8 *)var_s1 + 0xC) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40) * temp_fs1) + ((*(f32 *)((u8 *)arg0 + 0x1C) * temp_fs5) + (*(f32 *)((u8 *)arg0 + 0x28) * sp64) + (*(f32 *)((u8 *)arg0 + 0x34) * sp60)));
            *(f32 *)((u8 *)var_s1 + 0x10) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38) * temp_fv0) + ((*(f32 *)((u8 *)arg0 + 0x14) * temp_fs2) + (*(f32 *)((u8 *)arg0 + 0x20) * temp_fs3) + (*(f32 *)((u8 *)arg0 + 0x2C) * temp_fs4)));
            *(f32 *)((u8 *)var_s1 + 0x14) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C) * temp_fv0) + ((*(f32 *)((u8 *)arg0 + 0x18) * temp_fs2) + (*(f32 *)((u8 *)arg0 + 0x24) * temp_fs3) + (*(f32 *)((u8 *)arg0 + 0x30) * temp_fs4)));
            *(f32 *)((u8 *)var_s1 + 0x18) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40) * temp_fv0) + ((*(f32 *)((u8 *)arg0 + 0x1C) * temp_fs2) + (*(f32 *)((u8 *)arg0 + 0x28) * temp_fs3) + (*(f32 *)((u8 *)arg0 + 0x34) * temp_fs4)));
            var_s2 += 1;
            if (func_15146078((void *)var_s3, (void *)var_s4, (void *)var_s5) == 0) {
                *(f32 *)((u8 *)var_s1 + 0x1C) = 0.0f;
                *(f32 *)((u8 *)var_s1 + 0x20) = 0.0f;
                *(f32 *)((u8 *)var_s1 + 0x24) = 0.0f;
                *(f32 *)((u8 *)var_s1 + 0x28) = 0.0f;
                *(f32 *)((u8 *)var_s1 + 0x2C) = 0.0f;
                *(f32 *)((u8 *)var_s1 + 0x30) = 0.0f;
            }
            var_s1 += 0x34;
            var_s3 += 0x34;
            var_s4 += 0x34;
            var_s5 += 0x34;
            var_fs0 += sp78;
        } while (var_s2 < *(s32 *)((u8 *)arg0 + 0x48));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15106214 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106214.s")
f32 func_151064B4(f32 arg0) {
    f32 temp_fv1;

    temp_fv1 = 1.0f - arg0;
    return temp_fv1 * temp_fv1 * temp_fv1;
}
f32 func_151064DC(f32 arg0) {
    f32 temp_fv1;

    temp_fv1 = 1.0f - arg0;
    return 3.0f * arg0 * temp_fv1 * temp_fv1;
}
f32 func_15106510(f32 arg0) {
    return 3.0f * arg0 * arg0 * (1.0f - arg0);
}
f32 func_15106540(f32 arg0) {
    return arg0 * arg0 * arg0;
}
f32 func_15106558(f32 arg0) {
    f32 temp_fv1;

    temp_fv1 = 1.0f - arg0;
    return -3.0f * temp_fv1 * temp_fv1;
}
f32 func_15106584(f32 arg0) {
    return ((9.0f * arg0 * arg0) - (12.0f * arg0)) + 3.0f;
}
f32 func_151065BC(f32 arg0) {
    return (-9.0f * arg0 * arg0) + (6.0f * arg0);
}
f32 func_151065EC(f32 arg0) {
    return 3.0f * arg0 * arg0;
}
typedef struct Game133190CurveObject {
    u8 pad0[0x14];
    Game133190Triple first;
    u8 pad20[0x18];
    Game133190Triple last;
    u8 pad44[4];
    s32 count;
    f32 scale;
} Game133190CurveObject;

void *func_151061EC(u8 *);
f32 func_150ADA68(void);
void func_15143874(s16, f32, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15106610 CURRENT (2042) */
void func_15106610(void *arg0) {
    struct {
        f32 sp50;
        f32 sp54;
        u8 pad[0x10];
    } local;
    f32 *control;
    f32 *currentControl;
    f32 *output;
    f32 *currentOutput;
    s32 count;
    u32 random;
    Game133190CurveObject *obj = arg0;

    control = (f32 *)func_151061E0((s32)arg0);
    output = func_151061EC((u8 *)arg0);
    *(Game133190Triple *)output = obj->first;
    ((Game133190Triple *)output)[obj->count + 1] = obj->last;
    count = 1;
    currentOutput = output + 3;
    currentControl = control;
    if (obj->count + 1 >= 2) {
        do {
            random = func_150ADA20();
            func_15143874((s16)(random & 0xFF), func_150ADA68() * obj->scale,
                          &local.sp50, &local.sp54);
            currentOutput[0] = (currentControl[7] * local.sp50) + (currentControl[10] * local.sp54) + currentControl[1];
            currentOutput[1] = (currentControl[8] * local.sp50) + (currentControl[11] * local.sp54) + currentControl[2];
            currentOutput[2] = (currentControl[9] * local.sp50) + (currentControl[12] * local.sp54) + currentControl[3];
            count++;
            currentOutput += 3;
            currentControl += 13;
        } while (obj->count >= count);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15106610 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106610.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151067B8.s")
void func_15106E78(void *arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);
void func_1510761C(void *arg0);
void func_1514933C(s32 arg0);
void func_15149368(s32 arg0);

typedef void (*Game133190Callback)(void *);
extern Game133190Callback D_80088C18[];
void func_1516972C(void *);
void func_151D5E30(void *);

void func_15106E78(void *arg0) {
    void *var_a1;
    Game133190Callback temp_v0;
    void *temp_a0;
    void *temp_a0_2;

    var_a1 = arg0;
    temp_v0 = D_80088C18[*(u8 *)((u8 *)var_a1 + 0x5C)];
    if (temp_v0 != 0) {
        temp_v0(var_a1);
    }
    temp_a0 = *(void **)((u8 *)var_a1 + 0x6C);
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
    temp_a0_2 = *(void **)((u8 *)var_a1 + 0x70);
    if (temp_a0_2 != 0) {
        func_1516972C(temp_a0_2);
    }
    func_151D5E30((u8 *)var_a1 + 0x74);
}
void func_15106EF8(s32 arg0) {
    func_15106E78((void *) arg0);
    func_15169804(arg0);
}
void func_15106F24(s32 arg0) {
    func_15106E78((void *) arg0);
    func_15169824(arg0);
}
extern void (*D_80088C28[])(void *, s32, u8, s32);

void func_15106F50(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    void (*temp_v0)(void *, s32, u8, s32);

    temp_v0 = D_80088C28[*(u8 *)((u8 *)arg0 + 0x5C)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2, arg3);
    }
}
typedef struct Game133190FourTriples {
    Game133190Triple values[4];
} Game133190FourTriples;

typedef struct Game133190SpawnPacket {
    s32 count;
    s32 field44;
    s32 field48;
    s32 pad4C;
    Game133190FourTriples positions;
    u8 field80;
    u8 pad81[3];
} Game133190SpawnPacket;

s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);
void func_151070F8(s32, s32, s16, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15106F98 CURRENT (505) */
s32 func_15106F98(Game133190Triple *arg0, Game133190Triple *arg1,
                  s32 arg2, Game133190FourTriples *arg3, s32 arg4,
                  u8 arg5, u8 arg6, s32 arg7) {
    s32 result;
    Game133190SpawnPacket packet;
    u8 *object;
    Game133190Triple *positions;

    packet.count = (1 << arg2) + 1;
    packet.field48 = 0;
    packet.field44 = 0;
    packet.positions = *arg3;
    packet.field80 = arg5;
    result = func_15149130(0, -1, 0x3E, -1, 0, 0x30,
                           (packet.count * 0xC) + 0x48, arg6, arg7);
    if (result != 0) {
        object = (u8 *)result + 0x28;
        func_10022EC0(object, &packet, 0x44);
        positions = (Game133190Triple *)(object + 0x48);
        *(Game133190Triple **)(object + 0xC) = positions;
        positions[0] = *arg0;
        positions[packet.count - 1] = *arg1;
        func_151070F8(result, 0, (s16)(packet.count - 1), arg4);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15106F98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15106F98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151070F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_151072BC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15107604 CURRENT (20) */
Game133190Holder *func_15107604(Game133190Object *arg0) {
    Game133190Holder *holder = arg0->holder;
    Game133190Subobject *subobject = &holder->target->subobject;

    subobject->field_8 = 0;
    return holder;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15107604 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107604.s")
void func_1516972C(void *arg0);

void func_1510761C(void *arg0) {
    volatile void **field_30 = (volatile void **)((u8 *)arg0 + 0x30);

    if (*field_30 != 0) {
        func_1516972C((void *)*field_30);
    }
}
void func_1510764C(s32 arg0) {
    func_1510761C((void *)arg0);
    func_1514933C(arg0);
}
void func_15107678(s32 arg0) {
    func_1510761C((void *)arg0);
    func_15149368(arg0);
}
extern u8 D_80088C38;

void func_151076A4(void *arg0, s32 arg1, u8 arg2) {
    if (*(void **)(((u8 (*)[4])&D_80088C38)[*(volatile u8 *)((u8 *)arg0 + 0x68)]) != 0) {
        (*(void (**)(void *, s32, u8))(((u8 (*)[4])&D_80088C38)[*(volatile u8 *)((u8 *)arg0 + 0x68)]))(arg0, arg1, arg2);
    }
}
typedef struct Game133190Vector {
    f32 x;
    f32 y;
    f32 z;
} Game133190Vector;

typedef struct Game133190Color {
    u8 bytes[4];
} Game133190Color;

typedef struct Game133190Contact {
    u8 pad0[8];
    Game133190Vector point;
    u8 pad14[0x45];
    u8 hit;
    u8 pad5A[0xA];
} Game133190Contact;

typedef struct Game133190Beam {
    s16 life;
    s8 enabled;
    u8 pad3;
    Game133190Vector position;
    Game133190Vector axis0;
    Game133190Vector axis1;
    Game133190Vector contact;
    s8 flag;
    u8 pad35[3];
    s32 count;
    f32 width;
    f32 scale;
    s16 lower;
    s16 upper;
    Game133190Color color;
    s8 mode;
    u8 pad4D[3];
} Game133190Beam;

typedef struct Game133190Owner {
    void *owner;
    u8 kind;
    u8 pad5;
    s16 first;
    s16 second;
    u8 padA[2];
} Game133190Owner;

/* Pointer-leading ABI proved by raw actor dereference and independent caller. */
void func_15081690(void *, f32, f32, f32, f32, f32, f32,
                   void *, f32, s32, s32, s32, s32, s32, s32);
void func_15107A20(void *, s16, s16, void *, void *);
void func_15107AE0(void *, void *, void *, void *);
Game133190Object *func_15105CE0(Game133190Beam *, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15107700 CURRENT (3417) */
Game133190Object *func_15107700(void *arg0, s32 arg1, s32 arg2, s32 arg3,
                              s32 arg4, f32 arg5, f32 arg6, s32 arg7,
                              s32 arg8, Game133190Color *arg9, s32 arg10, s32 arg11) {
    Game133190Owner owner;
    Game133190Object *result;
    Game133190Beam beam;
    Game133190Contact contact;
    Game133190Vector origin;
    s8 enabled;

    arg1 = (s16)arg1;
    arg2 = (s16)arg2;
    arg3 = (s16)arg3;
    if (*(void **)((u8 *)arg0 + 0x1D4) == 0) return 0;
    owner.owner = arg0;
    owner.first = arg1;
    owner.second = arg2;
    owner.kind = *((u8 *)arg0 + 0x3B);
    if (arg3 == -1) beam.life = 300; else beam.life = arg3;
    if (arg3 == -1) enabled = 0; else enabled = 1;
    beam.enabled = enabled;
    beam.flag = 0;
    beam.count = arg4;
    beam.width = arg5;
    beam.scale = arg6;
    beam.lower = (s16)arg7;
    beam.upper = (s16)arg8;
    beam.color = *arg9;
    beam.mode = 2;
    func_15107A20(arg0, (s16)arg1, (s16)arg2, &beam.position, &origin);
    func_15081690(arg0, beam.position.x, beam.position.y, beam.position.z,
                  beam.position.x-origin.x, beam.position.y-origin.y,
                  beam.position.z-origin.z, &contact, 0.0f, 0, 1, 1, -1, 0, 0);
    if (contact.hit == 0) return 0;
    beam.contact = contact.point;
    func_15107AE0(&beam.position, &beam.contact, &beam.axis0, &beam.axis1);
    result = func_15105CE0(&beam, 12, (u8)arg10, arg11);
    if (result != 0) {
        func_10022EC0(result->holder, &owner, sizeof(owner));
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15107700 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107700.s")

extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_151078E4(void *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2;

    temp_a2 = *(s32 *)((u8 *)arg0 + 0x60);
    func_15169850(arg1, (s32) arg2, temp_a2, temp_a2 + 4, (s32) arg0);
}
void func_15107A20(void *, s16, s16, void *, void *);
void func_15107AE0(void *, void *, void *, void *);

typedef struct Game133190VectorWords {
    s32 x;
    s32 y;
    s32 z;
} Game133190VectorWords;

s32 func_15107924(void *arg0, s8 *arg1) {
    typedef struct { f32 x; f32 y; f32 z; } Vector;
    void *temp_v0;
    void *temp_t6;
    Vector sp2C;

    temp_v0 = *(void **)((u8 *)arg0 + 0x60);
    temp_t6 = *(void **)temp_v0;
    if ((*(s32 *)temp_t6 == 0) ||
        (*(u8 *)((u8 *)temp_v0 + 4) !=
         *(u8 *)((u8 *)temp_t6 + 0x3B))) {
        return 0;
    }
    *arg1 = 0;
    sp2C = *(Vector *)((u8 *)arg0 + 0x14);
    func_15107A20(temp_t6, *(s16 *)((u8 *)temp_v0 + 6),
                   *(s16 *)((u8 *)temp_v0 + 8), ((u8 *)arg0 + 0x14), 0);
    if ((sp2C.x != *(f32 *)((u8 *)arg0 + 0x14)) ||
        (sp2C.y != *(f32 *)((u8 *)arg0 + 0x18)) ||
        (sp2C.z != *(f32 *)((u8 *)arg0 + 0x1C))) {
        *arg1 = 1;
        func_15107AE0((u8 *)arg0 + 0x14, (u8 *)arg0 + 0x38,
                      (u8 *)arg0 + 0x20, (u8 *)arg0 + 0x2C);
    }
    return 1;
}
void func_15143794(s16, s16, f32, void *);
void func_1515C244(void *, f32 *, f32 *, f32 *);

void func_15107A20(void *arg0, s16 arg1, s16 arg2, void *arg3, void *arg4) {
    typedef struct { f32 values[3]; } Copy3;
    f32 sp2C[3];
    f32 sp28;
    f32 sp24;

    func_1515C244(arg0, sp2C, &sp28, &sp24);
    func_15143794(arg1, arg2, sp28, arg3);
    *(f32 *)((u8 *)arg3 + 4) *= *(f32 *)((u8 *)arg0 + 0xF0);
    *(f32 *)((u8 *)arg3 + 0) += sp2C[0];
    *(f32 *)((u8 *)arg3 + 4) += sp2C[1];
    *(f32 *)((u8 *)arg3 + 8) += sp2C[2];
    if (arg4 != 0) {
        *(Copy3 *)arg4 = *(Copy3 *)sp2C;
    }
}
extern f32 D_800A2420;
extern f32 D_800A2424;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15107AE0 CURRENT (1070) */
void func_15107AE0(void *arg0, void *arg1, void *arg2, void *arg3) {
    f32 weight_first = D_800A2420;
    f32 weight_second = D_800A2424;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv0 = *(f32 *)((u8 *)arg1 + 0) - temp_fv1;
    temp_fa0 = *(f32 *)((u8 *)arg1 + 4) - *(f32 *)((u8 *)arg0 + 4);
    {
        f32 temp_fa1 = *(f32 *)((u8 *)arg1 + 8) - *(f32 *)((u8 *)arg0 + 8);
    *(f32 *)((u8 *)arg2 + 0) = (f32) (temp_fv1 + (temp_fv0 * weight_first));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + (temp_fa0 * weight_first));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + (temp_fa1 * weight_first));
    *(f32 *)((u8 *)arg3 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + (temp_fv0 * weight_second));
    *(f32 *)((u8 *)arg3 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + (temp_fa0 * weight_second));
    *(f32 *)((u8 *)arg3 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + (temp_fa1 * weight_second));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15107AE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107AE0.s")
void func_1515C244(void *, f32 *, f32 *, f32 *);
void func_15143794(s16, s16, f32, void *);
void func_151C329C(f32 *, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15107B78 CURRENT (394) */
void func_15107B78(void *arg0, s16 arg1, s16 arg2, u8 arg3, s32 arg4) {
    f32 result[3];
    f32 offsets[3];
    f32 temp_1;
    f32 temp_2;

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        func_1515C244(arg0, offsets, &temp_1, &temp_2);
        func_15143794(arg1, arg2, temp_1, result);
        result[1] = result[1] * *(f32 *)((u8 *)arg0 + 0xF0);
        result[0] = result[0] + offsets[0];
        result[2] = result[2] + offsets[2];
        result[1] = result[1] + offsets[1];
        func_151C329C(result, arg3, arg4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15107B78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_133190/func_15107B78.s")
typedef struct Game133190Attachment {
    void *owner;
    u8 kind;
    u8 pad5[3];
    Game133190Vector offset;
    u8 transform;
    u8 pad15[3];
} Game133190Attachment;

void func_15107F54(void *, u8, f32 *, f32 *);

Game133190Object *func_15107C1C(void *arg0, u8 arg1, f32 *arg2,
                               s16 arg3, s16 arg4, s16 arg5, s32 arg6,
                               f32 arg7, f32 arg8, s16 arg9, s16 arg10,
                               Game133190Color *arg11, u8 arg12, s32 arg13) {
    Game133190Attachment attachment;
    Game133190Object *result;
    Game133190Beam beam;
    Game133190Contact contact;
    Game133190Vector direction;
    s8 enabled;

    if (*(s32 *)((u8 *)arg0 + 0x1D4) == 0) {
        return 0;
    }
    attachment.owner = arg0;
    attachment.kind = *(u8 *)((u8 *)arg0 + 0x3B);
    attachment.offset = *(Game133190Vector *)arg2;
    attachment.transform = arg1;
    if (arg5 == -1) {
        beam.life = 300;
    } else {
        beam.life = arg5;
    }
    if (arg5 == -1) {
        enabled = 0;
    } else {
        enabled = 1;
    }
    beam.enabled = enabled;
    beam.flag = 1;
    beam.count = arg6;
    beam.width = arg7;
    beam.scale = arg8;
    beam.lower = arg9;
    beam.upper = arg10;
    beam.color = *arg11;
    beam.mode = 3;
    func_15107F54(arg0, arg1, arg2, &beam.position.x);
    func_15143794(arg3, arg4, 1.0f, &direction);
    func_15081690(arg0, beam.position.x, beam.position.y, beam.position.z,
                  direction.x, direction.y, direction.z,
                  &contact, 300.0f, 0, 1, 1, -1, 0, 0);
    if (contact.hit == 0) {
        beam.contact.x = beam.position.x;
        beam.contact.x += direction.x * 300.0f;
        beam.contact.y = beam.position.y;
        beam.contact.y += direction.y * 300.0f;
        beam.contact.z = beam.position.z;
        beam.contact.z += direction.z * 300.0f;
    } else {
        beam.contact = contact.point;
    }
    func_15107AE0(&beam.position, &beam.contact, &beam.axis0, &beam.axis1);
    result = func_15105CE0(&beam, 0x18, arg12, arg13);
    if (result != 0) {
        func_10022EC0(result->holder, &attachment, sizeof(attachment));
    }
    return result;
}
void func_15107F54(void *, u8, f32 *, f32 *);
void func_15107AE0(void *, void *, void *, void *);

s32 func_15107E48(u8 *arg0, s8 *arg1) {
    typedef struct { f32 values[3]; } Copy3;
    u8 *temp_s1;
    u8 *temp_v0;
    f32 sp24[3];

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x60));
    temp_s1 = (void *)(*(void **)((u8 *)temp_v0 + 0));
    if ((*(s32 *)((u8 *)temp_s1 + 0) == 0) || (*(u8 *)((u8 *)temp_v0 + 4) != *(u8 *)((u8 *)temp_s1 + 0x3B))) {
        return 0;
    }
    if (*(s32 *)((u8 *)temp_s1 + 0x1D4) == 0) {
        return 0;
    }
    *arg1 = 0;
    *(Copy3 *)sp24 = *(Copy3 *)(arg0 + 0x14);
    func_15107F54(temp_s1, *(u8 *)((u8 *)temp_v0 + 0x14), (f32 *) (temp_v0 + 8), (f32 *)(arg0 + 0x14));
    if ((sp24[0] != *(f32 *)((u8 *)arg0 + 0x14)) || (sp24[1] != *(f32 *)((u8 *)arg0 + 0x18)) || (sp24[2] != *(f32 *)((u8 *)arg0 + 0x1C))) {
        *arg1 = 1;
        func_15107AE0((f32 *)(arg0 + 0x14), arg0 + 0x38, arg0 + 0x20, arg0 + 0x2C);
    }
    return 1;
}
/* Call context: func_15143134: unique active project prototype */
void func_15143134(f32 *, f32 *, s32);

void func_15107F54(void *arg0, u8 arg1, f32 *arg2, f32 *arg3) {
    func_15143134(arg2, arg3, *(s32 *)((u8 *)arg0 + 0x1D4) + (arg1 << 6));
}
void func_15107F98(void *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2;

    temp_a2 = *(s32 *)((u8 *)arg0 + 0x60);
    func_15169850(arg1, (s32) arg2, temp_a2, temp_a2 + 4, (s32) arg0);
}
