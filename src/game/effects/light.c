#include "types.h"

/*
 * Reviewed source unit: src/game/effects/light.c
 * Boundary evidence: docs/evidence/effects_light.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151602C0
 * - func_151603FC
 * - func_151604A0
 * - func_151606A8
 * - func_151607A4
 * - func_15160954
 * - func_15160A58
 * - func_15160B74
 * - func_15160CDC
 * - func_15160E30
 * - func_151616D0
 * - func_15161804
 * - func_15161860
 * - func_151619A0
 * - func_15161A68
 * - func_15161F4C
 * - func_15162034
 * - func_151621B8
 * - func_151623F4
 * - func_15162510
 * - func_15162740
 * - func_1516284C
 * - func_1516295C
 * - func_15162B28
 * - func_15162FAC
 * - func_151630F4
 * - func_15163414
 * - func_15163504
 * - func_151635A8
 * - func_15163604
 * - func_15163704
 * - func_151638E0
 * - func_151639D0
 * - func_15163A60
 * - func_15163B98
 * - func_15163BE8
 * - func_15163FEC
 * - func_151640C0
 * - func_15164134
 * - func_1516429C
 * - func_151643A8
 * - func_151645C4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameLightDescriptor {
    s8 field0;
    s8 field1;
    s16 field2;
    u8 field4;
} GameLightDescriptor;

void *func_1516037C(GameLightDescriptor *, s32, void *, u8, s32);
void *func_15167A68(s32, s32, void *, s32, s32, s32);
void func_10022EC0(void *, void *, s32);
extern f32 D_800A6AE4;
extern f32 D_800A6AE8;
extern f32 D_800A6AEC;
f32 func_150ADA68();
extern f32 D_800A6AD8;
extern f32 D_800A6ADC;
extern f32 D_800A6AE0;
s32 func_151149AC(u8);

void func_15163CF8(s32 arg0, s32 arg1);
void func_1514EDF0(s32 arg0, s32 arg1);
void func_151617C4();
void func_151617E4();
void func_1516944C(s32 arg0, s8 *arg1, u8 arg2, u8 arg3);

typedef struct LightEntry {
    s32 unk0;
    u8 unk4;
} LightEntry;

typedef struct LightCallData {
    u8 value;
    u8 pad1[3];
    s32 arg2;
} LightCallData;

void *func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);
void func_1515F10C(s32, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151602C0 CURRENT (15) */
s32 func_151602C0(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    void *result;
    void *allocated;

    result = 0;
    allocated = func_1515D5F8(arg1[0], arg1[1], arg1[2], arg2, arg3, arg4,
                              arg5, (u8)arg6, (u8)arg7, 0);
    if (allocated != 0) {
        result = func_1516037C((GameLightDescriptor *)arg0, (s32)allocated,
                               (void *)arg8, (u8)arg9, arg10);
        if (result != 0) {
            *(u8 *)((u8 *)result + 0xE) |= 2;
        } else {
            func_1515F10C((s32)allocated, allocated);
        }
    }
    return (s32)result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151602C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151602C0.s")
void *func_1516037C(GameLightDescriptor *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4) {
    void *temp_v0;
    volatile void *sp24;

    temp_v0 = func_15167A68(0x35, arg4, (u8 *)arg2 + 0x18, 1, (s32)arg3, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    sp24 = temp_v0;
    func_10022EC0((u8 *)temp_v0 + 0xE, arg0, 6);
    *(s32 *)((u8 *)sp24 + 0x14) = arg1;
    return (void *)sp24;
}
typedef s32 (*LightCallback)(void *);

extern LightCallback D_8008B0F0[];
extern s32 D_800BE9E4;
void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151603FC CURRENT (889) */
void func_151603FC(void *arg0) {
    u8 sp1B;
    s8 callback_index;
    u8 callback_pending;

    callback_pending = 0;
    if (*(u8 *)((u8 *)arg0 + 0xE) & 1) {
        *(s16 *)((u8 *)arg0 + 0x10) = (s16) (*(s16 *)((u8 *)arg0 + 0x10) - D_800BE9E4);
        if (*(s16 *)((u8 *)arg0 + 0x10) < 0) {
            callback_pending = 1;
        }
    }
    if (callback_pending == 0) {
        callback_index = *(s8 *)((u8 *)arg0 + 0xF);
        if (callback_index != -1) {
            sp1B = callback_pending;
            if (D_8008B0F0[(s32) callback_index](arg0) != 0) {
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
#endif /* CONKER_DEFERRED_CANDIDATE func_151603FC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151603FC.s")
extern void (*D_8008B150[])(void *);
void func_151618BC(u16, s16, u8, s32, void *, s16, s16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151604A0 CURRENT (17) */
void func_151604A0(void *arg0, u8 *arg1, u8 arg2) {
    u8 *object = arg0;
    struct { f32 x, y, z; } position;
    void (*callback)(void *);

    switch (arg2) {
    case 0x17:
    case 0x18:
    case 0x1C:
    case 0x1F:
    case 0x22:
        if (*arg1 != object[0x12]) {
            return;
        }
        switch (arg2) {
        case 0:
            break;
        case 0x17:
            (*(u8 **)(object + 0x14))[9] = 0;
            break;
        case 0x18:
            (*(u8 **)(object + 0x14))[9] = 1;
            break;
        case 0x1C:
            position.x = (f32)*(s16 *)((u8 *)*(void **)(object + 0x14) + 0xE);
            position.y = (f32)*(s16 *)((u8 *)*(void **)(object + 0x14) + 0x10);
            position.z = (f32)*(s16 *)((u8 *)*(void **)(object + 0x14) + 0x12);
            func_151618BC(0x3E80, 0, 0, 0, &position, 0x1F4, 0x3E8);
            return;
        case 0x1F:
            object[0xF] = 0xB;
            (*(u8 **)(object + 0x14))[9] = 0;
            break;
        case 0x22:
            func_1516972C(arg0);
            return;
        }
        break;
    default:
        callback = D_8008B150[object[0x12]];
        if (callback != 0) {
            callback(arg0);
        }
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151604A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151604A0.s")
s32 func_151422DC(s32, void *, s32, s32, s32, void *, s32);
extern u8 D_800A6690;
extern u8 D_800A6698;

s32 func_15160600(void *arg0) {
    *(s8 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 0x2F) =
        func_151422DC(0, &D_800A6690, 0, 0xFF, 0xFF, &D_800A6698, 0x23F);
    return 1;
}
s32 func_1516065C(s32 arg0) {
    func_15163CF8(arg0 + 0x18, arg0);
    return 1;
}
void func_15163DEC(s32, s32);
s32 func_15160684(s32 arg0) {
    func_15163DEC(arg0, arg0 + 0x18);
    return 1;
}
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A8050(void *, f32, f32, f32);
extern f32 D_800A66B4[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151606A8 CURRENT (73) */
s32 func_151606A8(void *arg0) {
    struct {
        f32 output[3];
        f32 matrix[16];
    } locals;
    void **source;
    void *temp_v0;

    source = (void **)((u8 *)arg0 + 0x18);
    temp_v0 = *source;
    func_150A8050(locals.matrix, *(f32 *)temp_v0,
                  *(f32 *)((u8 *)temp_v0 + 4),
                  *(f32 *)((u8 *)temp_v0 + 8));
    locals.matrix[12] = (f32)*(s16 *)((u8 *)*source + 0x10);
    locals.matrix[13] = (f32)*(s16 *)((u8 *)*source + 0x12);
    locals.matrix[14] = (f32)*(s16 *)((u8 *)*source + 0x14);
    func_150A7960(locals.matrix, D_800A66B4[0], D_800A66B4[1],
                  D_800A66B4[2], &locals.output[0], &locals.output[1],
                  &locals.output[2]);
    *(s16 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 0xE) =
        (s16)(s32)locals.output[0];
    *(s16 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 0x10) =
        (s16)(s32)locals.output[1];
    *(s16 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 0x12) =
        (s16)(s32)locals.output[2];
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151606A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151606A8.s")
void func_15160954(f32 *, f32 *, f32 *, f32 *, void *);
u32 func_150ADA20(void);
extern f32 D_800BE9A4;
extern f32 D_800A6AD4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151607A4 CURRENT (190) */
s32 func_151607A4(void *arg0) {
    u8 *actor = arg0;
    f32 *motion = (f32 *)(actor + 0x18);
    f32 limit;

    if (*(s16 *)(actor + 0x28) != 0) {
        limit = motion[3];
        if (limit < 0.0f) {
            motion[1] += motion[2] * D_800BE9A4;
            if (motion[0] < motion[1]) {
                s16 remaining = *(s16 *)((u8 *)motion + 0x10);
                motion[1] = motion[0];
                *(s16 *)((u8 *)motion + 0x10) = remaining - 1;
                if (*(s16 *)((u8 *)motion + 0x10) != 0) {
                    func_15160954(&motion[1], motion, &motion[2], &motion[3], arg0);
                }
            }
        } else {
            motion[3] = limit - D_800BE9A4;
        }
    } else if (func_150ADA68() < D_800A6AD4) {
        *(s16 *)((u8 *)motion + 0x10) = (func_150ADA20() % 5U) + 1;
        func_15160954(&motion[1], motion, &motion[2], &motion[3], arg0);
    }
    *(s8 *)(*(u8 **)(actor + 0x14) + 0x2F) = (s8)(u32)motion[1];
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151607A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151607A4.s")
typedef struct {
    u8 pad0[0xE];
    s16 x;
    s16 y;
    s16 z;
} Light60954Position;

typedef struct {
    u8 pad0[0x14];
    Light60954Position *position;
    u8 pad18[0x12];
    u8 active;
} Light60954State;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15160954 CURRENT (83) */
void func_15160954(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3,
                   Light60954State *arg4) {
    struct {
        s32 pad;
        f32 position[3];
    } locals;

    *arg0 = 0.0f;
    *arg2 = *arg1 / ((func_150ADA68() * 12.0f) + 8.0f);
    *arg3 = (func_150ADA68() * 28.0f) + 1.0f;
    locals.position[0] = (f32) arg4->position->x;
    locals.position[1] = (f32) arg4->position->y;
    locals.position[2] = (f32) arg4->position->z;
    if (arg4->active != 0) {
        func_151618BC(0x61A8U, 0, 0U, 0, locals.position, 0x1F4, 0x5DC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15160954 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160954.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15160A58 CURRENT (2787) */
s32 func_15160A58(void *arg0, u8 arg1, void *arg2, u8 arg3, s16 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s8 arg11, s32 arg12, u8 arg13, u8 arg14,
                   s32 arg15) {
    s32 sp64;
    struct {
        u8 field0;
        s8 field1;
        s16 field2;
        s8 field4;
    } sp5C;
    struct {
        void *object;
        u8 object_value;
        u8 arg1;
        u8 pad4A[2];
        s32 vector[3];
        s8 arg11;
        u8 arg13;
        u8 pad5A[2];
    } sp44;
    s32 sp38[3];
    s32 temp_v0;
    s32 var_v1;

    if (arg0 == 0) {
        return 0;
    }
    sp5C.field0 = arg3;
    sp5C.field1 = 5;
    sp5C.field4 = 0x10;
    sp5C.field2 = arg4;
    sp44.object = arg0;
    sp44.arg1 = arg1;
    sp44.object_value = *(u8 *)((u8 *)arg0 + 0x3B);
    sp44.vector[0] = *(s32 *)((u8 *)arg2 + 0);
    sp44.vector[1] = *(s32 *)((u8 *)arg2 + 4);
    sp44.vector[2] = *(s32 *)((u8 *)arg2 + 8);
    sp38[0] = 0;
    sp38[1] = 0;
    sp38[2] = 0;
    sp44.arg11 = arg11;
    sp44.arg13 = arg13;
    temp_v0 = func_151602C0((u8 *)&sp5C, sp38, arg5, arg6, arg7, arg8,
                            0xFF, 0, arg12 + 0x18, arg14, arg15);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp64 = temp_v0;
        func_10022EC0((u8 *)temp_v0 + 0x18, &sp44, 0x18);
        var_v1 = sp64;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15160A58 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160A58.s")
void func_15143134(f32 *, f32 *, s32);
extern u8 (*D_8008B1F8[])(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15160B74 CURRENT (669) */
u8 func_15160B74(void *arg0) {
    u8 *object = (u8 *)arg0;
    u8 *slot;
    u8 *entity;
    u8 result;
    f32 transformed[3];
    u8 saved_result;
    s8 selector;
    s32 transform;

    entity = *(u8 **)(object + 0x18);
    result = 1;
    slot = object + 0x18;
    if (*(s32 *)entity == 0) {
        return 0;
    }
    if (slot[4] != entity[0x3B]) {
        return 0;
    }
    transform = *(s32 *)(entity + 0x1D4);
    if (transform != 0 && (entity[0x74] & 0xF) != 0xF) {
        saved_result = 1;
        func_15143134((f32 *)(slot + 8), transformed,
                       transform + (slot[5] << 6));
        result = saved_result;
        *(s16 *)(*(u8 **)(object + 0x14) + 0xE) = (s16)(s32)transformed[0];
        *(s16 *)(*(u8 **)(object + 0x14) + 0x10) = (s16)(s32)transformed[1];
        *(s16 *)(*(u8 **)(object + 0x14) + 0x12) = (s16)(s32)transformed[2];
    } else {
        *(s16 *)(*(u8 **)(object + 0x14) + 0xE) =
            (s16)(s32)*(f32 *)(entity + 0x14);
        *(s16 *)(*(u8 **)(object + 0x14) + 0x10) =
            (s16)(s32)*(f32 *)(entity + 0x18);
        *(s16 *)(*(u8 **)(object + 0x14) + 0x12) =
            (s16)(s32)*(f32 *)(entity + 0x1C);
    }
    selector = *(s8 *)(slot + 0x14);
    if (selector != -1) {
        result = D_8008B1F8[selector](arg0);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15160B74 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160B74.s")
typedef struct LightVector3Words {
    s32 values[3];
} LightVector3Words;

typedef struct Light60CDCPayload {
    void *object;
    u8 object_value;
    u8 arg1;
    u8 pad6[2];
    LightVector3Words vector;
    LightVector3Words other_vector;
    f32 scale;
    u8 flags;
    u8 arg12;
    u8 pad26[2];
} Light60CDCPayload;

s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15160CDC CURRENT (2685) */
s32 func_15160CDC(void *arg0, s32 arg1, void *arg2, void *arg3, f32 arg4,
                  u8 arg5, s16 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14,
                  s32 arg15) {
    s32 sp7C;
    GameLightDescriptor sp74;
    Light60CDCPayload sp4C;
    s32 sp40[3];
    s32 temp_v0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v0;

    arg1 = (u8)arg1;
    if (arg0 == 0) {
        return 0;
    }
    sp74.field0 = arg5;
    sp74.field1 = 6;
    sp74.field4 = 0x11;
    sp4C.object = arg0;
    sp74.field2 = arg6;
    sp4C.arg1 = arg1;
    sp4C.object_value = *(u8 *)((u8 *)arg0 + 0x3B);
    var_v1_2 = 0;
    sp4C.vector = *(LightVector3Words *)arg2;
    var_v0 = 0;
    sp4C.other_vector = *(LightVector3Words *)arg3;
    sp4C.scale = arg4;
    if (arg11 != 0) {
        var_v1_2 = 1;
    }
    if (arg13 != 0) {
        var_v0 = 2;
    }
    sp4C.flags = var_v0 | var_v1_2;
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    sp4C.arg12 = arg12;
    temp_v0 = func_151602C0((u8 *)&sp74, sp40, arg7, arg8, arg9,
                            arg10, 0xFF, 0, 0x28, arg14, arg15);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp7C = temp_v0;
        func_10022EC0((u8 *)temp_v0 + 0x18, &sp4C, 0x28);
        var_v1 = sp7C;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15160CDC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160CDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160E30.s")

s32 func_15161238(LightEntry *arg0, LightEntry *arg1) {
    if (arg0->unk0 == 0) {
        return 0;
    }
    if (arg0->unk4 == 0xFF) {
        return 0;
    }
    if (arg0 == arg1) {
        return 0;
    }
    return 1;
}

void *func_1516127C(s32 arg0, u8 arg1, s32 arg2) {
    void *result;
    GameLightDescriptor descriptor;
    f32 values[4];

    values[0] = 50.0f;
    values[1] = 40.0f;
    values[2] = func_150ADA68() * D_800A6AD8;
    descriptor.field0 = 0;
    descriptor.field1 = 1;
    descriptor.field2 = 0x12C;
    descriptor.field4 = 5;
    values[3] = D_800A6ADC;
    result = func_1516037C(&descriptor, arg0, (void *)0x10, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, values, 0x10);
    }
    return result;
}
void *func_15161334(s32 arg0, u8 arg1, s32 arg2) {
    void *result;
    GameLightDescriptor descriptor;
    f32 values[8];

    values[1] = 1.0f;
    values[3] = 1.0f;
    descriptor.field0 = 0;
    descriptor.field1 = 2;
    descriptor.field2 = 0x12C;
    descriptor.field4 = 6;
    values[0] = 20.0f;
    values[2] = 50.0f;
    values[4] = 0.0f;
    values[5] = 10.0f;
    values[6] = D_800A6AE0;
    values[7] = 127.0f;
    result = func_1516037C(&descriptor, arg0, (void *)0x20, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, values, 0x20);
    }
    return result;
}
void *func_15161408(s32 arg0, u8 arg1, s32 arg2) {
    void *result;
    GameLightDescriptor descriptor;
    s32 sp20;

    sp20 = func_151149AC(0xF9U);
    descriptor.field0 = 0;
    descriptor.field1 = 3;
    descriptor.field2 = 0x12C;
    descriptor.field4 = 8;
    result = func_1516037C(&descriptor, arg0, (void *)4, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, &sp20, 4);
    }
    return result;
}
void *func_15161494(s32 arg0, u8 arg1, s32 arg2) {
    void *result;
    GameLightDescriptor descriptor;
    f32 values[4];

    descriptor.field0 = 0;
    descriptor.field1 = 1;
    descriptor.field2 = 0x12C;
    descriptor.field4 = 5;
    values[0] = 127.0f;
    values[1] = 100.0f;
    values[2] = 0.0f;
    values[3] = D_800A6AE4;
    result = func_1516037C(&descriptor, arg0, (void *)0x10, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, values, 0x10);
    }
    return result;
}
void *func_15161540(s32 arg0, u8 arg1, s32 arg2) {
    void *result;
    GameLightDescriptor descriptor;
    f32 values[4];

    values[0] = 28.0f;
    values[1] = 27.0f;
    values[2] = func_150ADA68() * D_800A6AE8;
    descriptor.field0 = 0;
    descriptor.field1 = 1;
    descriptor.field2 = 0x12C;
    descriptor.field4 = 5;
    values[3] = D_800A6AEC;
    result = func_1516037C(&descriptor, arg0, (void *)0x10, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, values, 0x10);
    }
    return result;
}
extern f32 D_800A66C0[];

void *func_151615F8(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4,
                    s32 arg5) {
    void *result;
    GameLightDescriptor descriptor;
    struct {
        f32 value0;
        f32 value1;
        f32 value2;
        f32 value3;
        s16 field10;
        u8 selector;
        u8 pad;
    } payload;
    f32 value;

    if ((s32)arg2 < 0) {
        return 0;
    }
    if ((s32)arg2 >= 9) {
        return 0;
    }
    value = D_800A66C0[arg2];
    payload.field10 = 0;
    descriptor.field0 = 0;
    payload.selector = arg1;
    descriptor.field1 = 4;
    descriptor.field2 = 0x12C;
    descriptor.field4 = arg3;
    payload.value1 = value;
    payload.value2 = 0.0f;
    payload.value3 = 0.0f;
    payload.value0 = value;
    result = func_1516037C(&descriptor, arg0, (void *)0x14, arg4, arg5);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, &payload, 0x14);
    }
    return result;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151616D0 CURRENT (510) */
void func_151616D0(s32 arg0, u8 arg1, s32 arg2) {
    LightCallData data;

    data.value = arg0;
    data.arg2 = arg2;
    func_1516944C(0x35, (s8 *)&data, arg1, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151616D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151616D0.s")

void func_15161714(void *arg0) {
    func_1514EDF0((s32)arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_151617C4(arg0);
}
void func_15161740(void *arg0) {
    func_1514EDF0((s32)arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_151617E4(arg0);
}
void func_1516176C(void *arg0) {
    func_1514EDF0((s32)arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_151617C4(arg0);
}
void func_15161798(void *arg0) {
    func_1514EDF0((s32)arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_151617E4(arg0);
}
void func_151617C4(void) {
    func_15169804();
}
void func_151617E4(void) {
    func_15169824();
}
void func_1515F10C(s32, void *);
extern void (*D_8008B208[])(void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15161804 CURRENT (240) */
void func_15161804(void *arg0) {
    void *temp_a1;

    temp_a1 = arg0;
    if (*(u8 *)((u8 *)temp_a1 + 0xE) & 2) {
        func_1515F10C(*(s32 *)((u8 *)temp_a1 + 0x14), temp_a1);
    }
    D_8008B208[*(u8 *)((u8 *)temp_a1 + 0x12)](temp_a1, temp_a1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15161804 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161804.s")
extern void (*D_8008B2B0[])(void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15161860 CURRENT (240) */
void func_15161860(void *arg0) {
    if (*(u8 *)((u8 *)arg0 + 0xE) & 2) {
        func_1515F10C(*(s32 *)((u8 *)arg0 + 0x14), arg0);
    }
    D_8008B2B0[*(u8 *)((u8 *)arg0 + 0x12)](arg0, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15161860 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161860.s")
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);

typedef struct GameLightSoundIds {
    s32 values[10];
} GameLightSoundIds;

extern GameLightSoundIds D_800A66E4;

void func_151618BC(u16 arg0, s16 arg1, u8 arg2, s32 arg3,
                   void *arg4, s16 arg5, s16 arg6) {
    GameLightSoundIds sp38;

    sp38 = D_800A66E4;
    func_10010F88(sp38.values[func_150ADA20() % 10U], arg0, arg1, arg2,
                   arg3, (s32)*(f32 *)((u8 *)arg4 + 0),
                   (s32)*(f32 *)((u8 *)arg4 + 4),
                   (s32)*(f32 *)((u8 *)arg4 + 8), arg5, arg6);
}
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151619A0 CURRENT (115) */
s32 func_151619A0(s32 arg0, s16 arg1, u8 arg2, s32 arg3) {
    GameLightDescriptor descriptor;
    s32 payload;
    s32 position[3];
    s32 result;

    payload = arg0;
    descriptor.field0 = 3;
    descriptor.field1 = 9;
    descriptor.field4 = 0x14;
    position[0] = 0;
    position[1] = 0;
    position[2] = 0;
    descriptor.field2 = arg1;
    result = func_151602C0((u8 *)&descriptor, position, 0xFF, 0xFF, 0xFF, 0xFF,
                           0xFF, 0, 4, arg2, arg3);
    if (result != 0) {
        func_10022EC0((void *)(result + 0x18), &payload, 4);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151619A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151619A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161A68.s")
typedef struct LightEffectActor {
    u8 pad0[0x14];
    f32 position[3];
    u8 pad20[0x1B];
    u8 field3B;
} LightEffectActor;

s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_15161E24(LightEffectActor *arg0, u8 arg1, u8 arg2, s16 arg3,
                 s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s32 result;
    GameLightDescriptor descriptor;
    struct {
        LightEffectActor *actor;
        u8 field4;
        u8 field5;
        u8 pad6[2];
    } payload;
    s32 position[3];

    if (arg0 == 0) {
        return 0;
    }
    descriptor.field0 = (u8)arg2;
    descriptor.field1 = 0xA;
    descriptor.field2 = (s16)arg3;
    descriptor.field4 = 0x15;
    payload.actor = arg0;
    payload.field4 = arg0->field3B;
    payload.field5 = (u8)arg1;
    position[0] = (s32)arg0->position[0];
    position[1] = (s32)arg0->position[1];
    position[2] = (s32)arg0->position[2];
    result = func_151602C0((u8 *)&descriptor, position, arg4, arg5, arg6, arg7,
                          0xFF, 0, 8, (u8)arg8, arg9);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, &payload, 8);
    }
    return result;
}
void func_15161F2C(s32 arg0) {
    func_15163F50(arg0, arg0 + 0x18);
}
extern LightCallback D_8008B358[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15161F4C CURRENT (2915) */
void func_15161F4C(u8 *arg0, u8 *arg1, u8 arg2) {
    LightCallback temp_v0_2;
    s32 temp_a0;
    s32 temp_v1;
    u8 var_a2;
    register s32 temp_v0;
    u8 *var_a3;

    var_a3 = arg0;
    var_a2 = arg2;
    if (var_a2 == 0) {
        temp_v0 = (s32)var_a3 + 0x18;
        if ((*(s32 *)temp_v0 == *(s32 *)arg1) || (*(u8 *)(temp_v0 + 4) == arg1[4])) {
            arg2 = var_a2;
            func_1516972C(var_a3);
            var_a2 = arg2;
        }
    } else {
        temp_v0 = (s32)var_a3 + 0x18;
        if (var_a2 == 0x2D) {
            temp_a0 = *(s32 *)(var_a3 + 0x18);
            temp_v1 = *(s32 *)arg1;
            if (temp_v1 == temp_a0) {
                *(s32 *)(var_a3 + 0x18) = *(s32 *)(arg1 + 4);
                *(u8 *)(temp_v0 + 4) = arg1[9];
            } else if (*(s32 *)(arg1 + 4) == temp_a0) {
                *(s32 *)(var_a3 + 0x18) = temp_v1;
                *(u8 *)(temp_v0 + 4) = arg1[8];
            }
        }
    }
    temp_v0_2 = D_8008B358[var_a3[0x1D]];
    if (temp_v0_2 != 0) {
        temp_v0_2(var_a3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15161F4C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161F4C.s")
extern f32 D_800A6AF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15162034 CURRENT (648) */
void *func_15162034(s32 arg0, s32 arg1, s32 arg2) {
    void *result;
    GameLightDescriptor descriptor;
    f32 values[8];

    values[1] = 15.0f;
    values[0] = 22.0f;
    descriptor.field0 = 0;
    descriptor.field1 = 2;
    descriptor.field2 = 0x12C;
    descriptor.field4 = 6;
    values[2] = 45.0f;
    values[3] = 1.0f;
    values[5] = 10.0f;
    values[6] = D_800A6AF0;
    values[4] = 0.0f;
    values[7] = 127.0f;
    result = func_1516037C(&descriptor, arg0, (void *)0x20,
                           arg1 & 0xFF, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, values, 0x20);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15162034 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162034.s")
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A6AF4;

void func_15162110(s32 arg0) {
    s32 temp_v0;
    struct {
        f32 values[8];
    } payload;

    payload.values[1] = 15.0f;
    payload.values[2] = 0.0f;
    payload.values[4] = 15.0f;
    payload.values[5] = 0.0f;
    payload.values[6] = 0.0f;
    payload.values[0] = 42.5f;
    payload.values[3] = 37.5f;
    payload.values[7] = D_800A6AF4;
    temp_v0 = func_15149130(0x12C, -1, 0x1E, -1, 0, 0, 0x20, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, payload.values, 0x20);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151621B8.s")
extern s32 D_800A670C[];
extern s32 D_800A6730[];
extern f32 D_800A6754[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151623F4 CURRENT (3971) */
void *func_151623F4(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s8 arg4,
                    s16 arg5, u8 arg6, s32 arg7) {
    s32 values[8];
    GameLightDescriptor descriptor;
    void *saved;
    void *result;
    s32 index;

    if (arg1 >= 3) {
        return 0;
    }
    index = arg1 * 3;
    values[0] = D_800A670C[index + 0];
    values[1] = D_800A670C[index + 1];
    values[2] = D_800A670C[index + 2];
    values[3] = D_800A6730[index + 0];
    values[4] = D_800A6730[index + 1];
    values[5] = D_800A6730[index + 2];
    *(f32 *)&values[6] = 0.0f;
    descriptor.field0 = arg3;
    *(f32 *)&values[7] = D_800A6754[arg1];
    descriptor.field1 = arg4;
    descriptor.field2 = arg5;
    descriptor.field4 = arg2;
    result = func_1516037C(&descriptor, arg0, (void *)0x20, arg6, arg7);
    if (result != 0) {
        saved = result;
        func_10022EC0((u8 *)result + 0x18, &values, 0x20);
        result = saved;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151623F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151623F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162510.s")
extern f32 D_800A6760[];
extern f32 D_800A67C0[];
extern f32 D_800A6820[];
extern f32 D_800A6AF8;

typedef struct {
    f32 values[8];
    GameLightDescriptor descriptor;
    void *saved;
} Light62740Locals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15162740 CURRENT (711) */
void *func_15162740(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4,
                    s8 arg5, u8 arg6, s32 arg7) {
    Light62740Locals locals;
    void *result;

    if (arg1 >= 0x18) {
        return 0;
    }
    locals.values[0] = D_800A67C0[arg1];
    locals.values[1] = D_800A6760[arg1];
    locals.values[2] = D_800A6820[arg1];
    locals.values[3] = 1.0f;
    locals.values[5] = 10.0f;
    locals.values[6] = D_800A6AF8;
    locals.values[4] = 0.0f;
    locals.values[7] = 127.0f;
    locals.descriptor.field0 = arg3;
    locals.descriptor.field1 = arg5;
    locals.descriptor.field2 = arg4;
    locals.descriptor.field4 = arg2;
    result = func_1516037C(&locals.descriptor, arg0, (void *)0x20, arg6,
                           arg7);
    if (result != 0) {
        locals.saved = result;
        func_10022EC0((u8 *)result + 0x18, locals.values, 0x20);
        result = locals.saved;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15162740 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162740.s")
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A6AFC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516284C CURRENT (496) */
s32 func_1516284C(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4,
                   u8 arg5, u8 arg6, s32 arg7, u8 arg8, u8 arg9,
                   s32 arg10) {
    f32 values[8];
    s32 temp_v0;
    s32 var_v1;

    if ((s32)arg8 >= 0x18) {
        return 0;
    }
    values[0] = D_800A67C0[arg8];
    values[1] = D_800A6760[arg8];
    values[2] = D_800A6820[arg8];
    values[3] = 1.0f;
    values[5] = 10.0f;
    values[6] = D_800A6AFC;
    values[4] = 0.0f;
    values[7] = 127.0f;
    temp_v0 = func_151602C0(arg0, arg1, 0, arg2, arg3, arg4,
                            (s32)arg5, (s32)arg6, arg7 + 0x20,
                            (s32)arg9, arg10);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x18, values, 0x20);
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516284C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516284C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516295C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162B28.s")
void func_151403A8(s8 *, s32);

void func_15162EF8(void *arg0) {
    s8 sp1C[12];
    s32 temp_v0;

    temp_v0 = func_151149AC(*(u8 *)((u8 *)arg0 + 0x48));
    if (temp_v0 != 0) {
        *(s32 *)((u8 *)temp_v0 + 0x7C) |= 1;
    }
    sp1C[0] = *(u8 *)((u8 *)arg0 + 0x12) - 0x15;
    func_151403A8(sp1C, 0x24);
}
void func_15162F50(void *arg0) {
    s8 sp1C[12];
    s32 temp_v0;

    temp_v0 = func_151149AC(*(u8 *)((u8 *)arg0 + 0x48));
    if (temp_v0 != 0) {
        *(s32 *)((u8 *)temp_v0 + 0x7C) &= ~1;
    }
    sp1C[0] = *(u8 *)((u8 *)arg0 + 0x12) - 0x15;
    func_151403A8(sp1C, 0x25);
}
extern f32 D_800A68F8[];
extern f32 D_800A6904[];
extern f32 D_800A6910[];
extern s32 D_800A691C[];
extern s32 D_800A6928[];
extern f32 D_800A6934[];
extern f32 D_800A6940[];
extern f32 D_800A694C[];
extern f32 D_800A6958[];

typedef struct Light62FACPayload {
    f32 field_0;
    f32 field_4;
    f32 field_8;
    f32 field_C;
    f32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    f32 field_2C;
    f32 field_30;
} Light62FACPayload;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15162FAC CURRENT (120) */
void *func_15162FAC(s32 arg0, u8 arg1, u8 arg2, u8 arg3,
                    s16 arg4, s8 arg5, u8 arg6, s32 arg7) {
    struct {
        Light62FACPayload payload;
        GameLightDescriptor descriptor;
        void *saved;
    } locals;
    void *result;

    if (arg1 >= 3) {
        return 0;
    }
    locals.payload.field_0 = 0.0f;
    locals.payload.field_4 = D_800A68F8[arg1];
    locals.payload.field_8 = 0.0f;
    locals.payload.field_C = D_800A6904[arg1];
    locals.payload.field_10 = D_800A6910[arg1];
    locals.payload.field_14 = 0;
    locals.payload.field_18 = D_800A691C[arg1];
    locals.payload.field_1C = D_800A6928[arg1];
    locals.payload.field_20 = 0.0f;
    locals.payload.field_24 = D_800A6934[arg1];
    locals.payload.field_28 = D_800A6940[arg1];
    locals.payload.field_2C = D_800A694C[arg1];
    locals.payload.field_30 = D_800A6958[arg1];
    locals.descriptor.field0 = arg3;
    locals.descriptor.field1 = arg5;
    locals.descriptor.field2 = arg4;
    locals.descriptor.field4 = arg2;
    result = func_1516037C(&locals.descriptor, arg0, (void *)0x34,
                           arg6, arg7);
    if (result != 0) {
        locals.saved = result;
        func_10022EC0((u8 *)result + 0x18, &locals.payload, 0x34);
        result = locals.saved;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15162FAC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162FAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151630F4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15163414 CURRENT (283) */
s32 func_15163414(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s8 arg4,
                  u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10,
                  u8 arg11, s32 arg12, u8 arg13, s32 arg14) {
    s32 sp54;
    struct {
        f32 *field_0;
        f32 *field_4;
        f32 *field_8;
        s8 field_C;
        u8 field_D;
    } payload;
    s32 position[3];
    s32 temp_v0;
    s32 var_v1;

    payload.field_0 = arg1;
    payload.field_4 = arg2;
    payload.field_8 = arg3;
    payload.field_C = arg4;
    payload.field_D = arg5;
    position[0] = (s32)*arg1;
    position[1] = (s32)*arg2;
    position[2] = (s32)*arg3;
    temp_v0 = func_151602C0(arg0, position, (s32)arg6, (s32)arg7,
                            (s32)arg8, (s32)arg9, (s32)arg10, (s32)arg11,
                            arg12 + 0x10, (s32)arg13, arg14);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp54 = temp_v0;
        func_10022EC0((u8 *)temp_v0 + 0x18, &payload, 0x10);
        var_v1 = sp54;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15163414 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163414.s")
typedef s32 (*LightUpdateCallback)(void *);

extern LightUpdateCallback D_8008B36C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15163504 CURRENT (895) */
s32 func_15163504(void *arg0) {
    s32 result;

    result = 1;
    *(s16 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 0xE) = (s16)(s32)**(f32 **)((u8 *)arg0 + 0x18);
    *(s16 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 0x10) = (s16)(s32)**(f32 **)((u8 *)arg0 + 0x1C);
    *(s16 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 0x12) = (s16)(s32)**(f32 **)((u8 *)arg0 + 0x20);
    if (*(s8 *)((u8 *)arg0 + 0x24) != -1) {
        result = D_8008B36C[(s32) *(s8 *)((u8 *)arg0 + 0x24)](arg0);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15163504 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163504.s")
extern void (*D_8008B370[])(void *, void *, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151635A8 CURRENT (605) */
void func_151635A8(void *arg0, void *arg1, u8 arg2) {
    if (D_8008B370[*(u8 *)((u8 *)arg0 + 0x25)] != 0) {
        D_8008B370[*(u8 *)((u8 *)arg0 + 0x25)](arg0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151635A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151635A8.s")
extern u8 D_800A6964[];
extern u8 D_800A699C[];
extern u8 D_800A69D4[];
extern f32 D_800A6B00;

typedef struct {
    s32 offset;
    f32 values[4];
    GameLightDescriptor descriptor;
    u8 pad3A[2];
    void *saved;
} Light63604Locals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15163604 CURRENT (984) */
void *func_15163604(s32 arg0, s32 arg1, u8 arg2, s16 arg3, u8 arg4,
                    s32 arg5, u8 arg6, s32 arg7) {
    void *result;
    Light63604Locals locals;

    arg1 &= 0xFF;
    if (arg1 < 0) {
        return 0;
    }
    if (arg1 >= 0xE) {
        return 0;
    }
    locals.offset = arg1 * 4;
    locals.values[0] = *(f32 *)(D_800A6964 + locals.offset);
    locals.values[1] = *(f32 *)(D_800A699C + locals.offset);
    locals.values[2] = func_150ADA68() * D_800A6B00;
    locals.values[3] = *(f32 *)(D_800A69D4 + locals.offset);
    locals.descriptor.field0 = arg4;
    locals.descriptor.field1 = 1;
    locals.descriptor.field2 = arg3;
    locals.descriptor.field4 = arg2;
    result = func_1516037C(&locals.descriptor, arg0, (void *)0x10, arg6, arg7);
    if (result != 0) {
        locals.saved = result;
        func_10022EC0((u8 *)result + 0x18, locals.values, 0x10);
        result = locals.saved;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15163604 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163604.s")
f32 func_15047D60(f32);
f32 func_15144B68(f32);
extern f32 D_800BE9A4;
extern f32 D_800A6B04;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15163704 CURRENT (823) */
s32 func_15163704(void *arg0) {
    f32 temp_fv0;
    u8 *temp_v0;

    temp_v0 = (u8 *)arg0 + 0x18;
    temp_fv0 = func_15047D60(*(f32 *)((u8 *)arg0 + 0x20));
    *(s8 *)(*(u8 **)((u8 *)arg0 + 0x14) + 0x2F) =
        (s8)(u32)(*(f32 *)(temp_v0 + 0) +
                  (*(f32 *)(temp_v0 + 4) * temp_fv0));
    *(f32 *)(temp_v0 + 8) += *(f32 *)(temp_v0 + 0xC) * D_800BE9A4;
    temp_fv0 = func_15144B68(*(f32 *)(temp_v0 + 8));
    *(f32 *)(temp_v0 + 8) = temp_fv0;
    return !(D_800A6B04 < temp_fv0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15163704 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163704.s")
void func_1516381C(s32 arg0, u8 arg1, u8 arg2, s32 arg3) {
    GameLightDescriptor sp20;

    sp20.field0 = 0;
    sp20.field1 = -1;
    sp20.field2 = 0x12C;
    sp20.field4 = arg1;
    func_1516037C(&sp20, arg0, 0, arg2, arg3);
}
void func_1516387C(s32 arg0, u8 arg1, s8 arg2, s16 arg3, u8 arg4,
                   void *arg5, u8 arg6, s32 arg7) {
    GameLightDescriptor sp20;

    sp20.field0 = arg1;
    sp20.field1 = arg2;
    sp20.field2 = arg3;
    sp20.field4 = arg4;
    func_1516037C(&sp20, arg0, arg5, arg6, arg7);
}
void func_15187FC0(s32, void *);
void func_15188010(s32, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151638E0 CURRENT (929) */
s32 func_151638E0(void *arg0) {
    s32 sp20;
    f32 sp1C;
    u8 *sp18;

    func_15187FC0(*(s32 *)((u8 *)arg0 + 0x18), &sp20);
    sp18 = (u8 *)arg0 + 0x18;
    func_15188010(*(s32 *)sp18, &sp1C);
    *(s8 *)(*(u8 **)((u8 *)arg0 + 0x14) + 0x2F) =
        (s8)(u32)(*(f32 *)(sp18 + 4) + (*(f32 *)(sp18 + 8) * sp1C));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151638E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151638E0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151639D0 CURRENT (224) */
void func_151639D0(void *arg0, s32 arg1, s32 arg2) {
    arg2 &= 0xFF;
    if (arg2 == 0x27) {
        *(s8 *)(*(u8 **)((u8 *)arg0 + 0x14) + 9) = 1;
        return;
    }
    if (arg2 == 0x28) {
        *(s8 *)(*(u8 **)((u8 *)arg0 + 0x14) + 9) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151639D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151639D0.s")
void func_15163A18(void *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x27) {
        *(s8 *)(*(u8 **)((u8 *)arg0 + 0x14) + 9) = 0;
        return;
    }
    if (arg2 == 0x28) {
        *(s8 *)(*(u8 **)((u8 *)arg0 + 0x14) + 9) = 1;
    }
}
extern f32 D_800A697C, D_800A69B4, D_800A69EC, D_800A6B08;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15163A60 CURRENT (1141) */
s32 func_15163A60(s32 arg0, u8 arg1, s32 arg2) {
    s32 sp64;
    struct { u8 kind; s8 flags; s16 time; s8 mode; } sp5C;
    f32 values[4];
    s32 sp48;
    s32 position[3];
    f32 temp_ft3;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_151149AC(arg0 & 0xFF);
    sp48 = temp_v0;
    if (temp_v0 == 0) {
        return 0;
    }
    values[0] = D_800A697C;
    values[1] = D_800A69B4;
    temp_ft3 = func_150ADA68() * D_800A6B08;
    values[3] = D_800A69EC;
    values[2] = temp_ft3;
    position[0] = (s32) *(s16 *)((u8 *)sp48 + 0x10);
    position[1] = (s32) *(s16 *)((u8 *)sp48 + 0x12);
    position[2] = (s32) *(s16 *)((u8 *)sp48 + 0x14);
    sp5C.kind = 2;
    sp5C.flags = 0x11;
    sp5C.time = 0x12C;
    sp5C.mode = 5;
    temp_v0_2 = func_151602C0((u8 *) &sp5C, &position[0], (s32) D_800A697C, 0, 0xFF, 0, 0xFF, 0, 0x14, (s32) arg1, arg2);
    sp64 = temp_v0_2;
    if (temp_v0_2 != 0) {
        func_10022EC0((void *)(temp_v0_2 + 0x18), &values[0], 0x10);
        func_10022EC0((void *) (sp64 + 0x28), &sp48, 4);
    }
    return sp64;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15163A60 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163A60.s")
typedef struct {
    u8 pad_0[0x6E];
    u8 field_6E;
} LightStateData;

typedef struct {
    u8 pad_0[0x28];
    LightStateData *field_28;
} LightState;

s32 func_1516065C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15163B98 CURRENT (80) */
s32 func_15163B98(s32 arg0) {
    if (func_1516065C(arg0) == 0) {
        return 0;
    }
    if (((LightState *)arg0)->field_28->field_6E == 1) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15163B98 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163B98.s")
s32 func_15160A58(void *, u8, void *, u8, s16, s32, s32, s32, s32, s32,
                   s32, s8, s32, u8, u8, s32);
extern u8 D_800A6A0C;
extern f32 D_800A6B0C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15163BE8 CURRENT (120) */
s32 func_15163BE8(void *arg0, u8 arg1, s32 arg2) {
    s32 sp5C;
    f32 values[4];
    s32 var_v1;

    values[0] = D_800A697C;
    values[1] = D_800A69B4;
    values[2] = func_150ADA68() * D_800A6B0C;
    values[3] = D_800A69EC;
    var_v1 = func_15160A58(arg0, 1, &D_800A6A0C, 2, 0x12C, 0x64, 0, 0xFF, 0, 0xFF, 0, 0, 0x10, 1, arg1, arg2);
    if (var_v1 != 0) {
        sp5C = var_v1;
        func_10022EC0((void *)(var_v1 + 0x30), values, 0x10);
        var_v1 = sp5C;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15163BE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163BE8.s")
s32 func_15163CD0(s32 arg0) {
    func_15163CF8(arg0 + 0x30, arg0);
    return 1;
}
typedef struct LightMotionState {
    f32 base;
    f32 scale;
    f32 value;
    f32 velocity;
} LightMotionState;

typedef struct LightMotionOwner {
    u8 pad0[0x14];
    u8 *data;
} LightMotionOwner;

f32 func_15047D60(f32);
f32 func_15144B68(f32);
extern f32 D_800BE9A4;

void func_15163CF8(s32 arg0, s32 arg1) {
    LightMotionState *state;
    LightMotionOwner *owner;
    f32 factor;

    state = (LightMotionState *)arg0;
    owner = (LightMotionOwner *)arg1;
    factor = func_15047D60(state->value);
    owner->data[0x2F] =
        (s8)(u32)(state->base + (state->scale * factor));
    state->value += state->velocity * D_800BE9A4;
    state->value = func_15144B68(state->value);
}
typedef struct Light63DECState {
    f32 endpoint0;
    f32 endpoint1;
    f32 endpoint2;
    f32 target;
    f32 timer;
    f32 duration;
    f32 weight;
    f32 value;
} Light63DECState;

void func_15163DEC(s32 arg0, s32 arg1) {
    Light63DECState *state = (Light63DECState *)arg1;
    f32 current;

    state->timer = state->timer - D_800BE9A4;
    if (state->timer < 0.0f) {
        state->timer = func_150ADA68() * state->duration;
        if (func_150ADA20() & 3) {
            state->target = func_150ADA68() *
                (state->endpoint0 - state->endpoint1) + state->endpoint1;
        } else {
            state->target = func_150ADA68() *
                (state->endpoint2 - state->endpoint0) + state->endpoint0;
        }
    }
    state->value += (state->target - state->value) * state->weight;
    *(s8 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 0x2F) =
        (s8)(u32)*(volatile f32 *)&state->value;
}
s32 func_15163F50(void *arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = *(void **)arg1;
    if (*(s32 *)temp_v1 == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)temp_v1 + 4) == 0xFF) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg1 + 4) != *(u8 *)((u8 *)temp_v1 + 0x3B)) {
        return 0;
    }
    *(s16 *)(*(u8 **)((u8 *)arg0 + 0x14) + 0xE) = (s16) *(f32 *)((u8 *)temp_v1 + 0x14);
    *(s16 *)(*(u8 **)((u8 *)arg0 + 0x14) + 0x10) = (s16) *(f32 *)((u8 *)temp_v1 + 0x18);
    *(s16 *)(*(u8 **)((u8 *)arg0 + 0x14) + 0x12) = (s16) *(f32 *)((u8 *)temp_v1 + 0x1C);
    return 1;
}
extern void (*D_8008B374[])(void *, void *, u8);

typedef struct {
    s32 owner;
    u8 type;
} LightOwnerLink;

typedef struct {
    u8 pad0[0x18];
    LightOwnerLink link;
} LightOwnerState;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15163FEC CURRENT (760) */
void func_15163FEC(void *arg0, void *arg1, u8 arg2) {
    void (*callback)(void *, void *, u8);
    s32 temp_a2;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;
    LightOwnerLink *link;

    temp_t6 = arg2;
    if (temp_t6 == 0) {
        link = &((LightOwnerState *)arg0)->link;
        if ((*(s32 *)arg1 == link->owner) ||
            (link->type == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else {
        link = &((LightOwnerState *)arg0)->link;
        temp_v0 = link;
        if (temp_t6 == 0x2D) {
            temp_a2 = link->owner;
            temp_v1 = *(s32 *)arg1;
            if (temp_v1 == temp_a2) {
                link->owner = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
                link->owner = temp_v1;
                *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
            }
        } else {
            callback = D_8008B374[*(u8 *)((u8 *)arg0 + 0x2D)];
            if (callback != 0) {
                callback(arg0, arg1, arg2);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15163FEC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163FEC.s")
typedef struct LightActor {
    u8 pad0[0x3B];
    u8 type;
} LightActor;

typedef struct LightOwnerRecord {
    LightActor *owner;
    u8 type;
} LightOwnerRecord;

typedef struct LightEffectState {
    u8 pad0[0x18];
    LightOwnerRecord owner_record;
} LightEffectState;

typedef struct LightEvent {
    u8 pad0[4];
    LightOwnerRecord *owner_record;
} LightEvent;

typedef struct LightOutput {
    u8 pad0[0xE];
    s16 field_E;
    s16 field_10;
    s16 field_12;
} LightOutput;

typedef struct LightObject {
    u8 pad0[0x14];
    LightOutput *output;
} LightObject;

typedef struct LightInput {
    u8 pad0[0xC];
    s32 field_C;
} LightInput;

void func_1516972C(void *);
void func_15145CD0(s32, void **, f32 **, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151640C0 CURRENT (978) */
void func_151640C0(void *volatile arg0, void *volatile arg1, u8 arg2) {
    u8 state_type;
    u8 record_type;
    LightActor *owner;
    LightOwnerRecord *record;

    if ((arg2 == 0x29) &&
        ((record = ((LightEvent *)arg1)->owner_record,
          owner = ((LightEffectState *)arg0)->owner_record.owner,
          record_type = record->type,
          state_type = ((LightEffectState *)arg0)->owner_record.type,
          (owner == record->owner)) ||
         (record_type == state_type) ||
         (record_type == owner->type))) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151640C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151640C0.s")
extern void (*D_8008B37C[])(void *, void *, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15164134 CURRENT (1270) */
void func_15164134(void *arg0, void *arg1, u8 arg2) {
    LightOwnerRecord *record;
    void (*callback)(void *, void *, u8);
    LightActor *owner;
    LightActor *incoming;

    if (arg2 == 0) {
        record = &((LightEffectState *)arg0)->owner_record;
        if ((((LightOwnerRecord *)arg1)->owner == record->owner) ||
            (record->type == ((LightOwnerRecord *)arg1)->type)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        record = &((LightEffectState *)arg0)->owner_record;
        owner = record->owner;
        incoming = ((LightOwnerRecord *)arg1)->owner;
        if (incoming == owner) {
            record->owner = *(LightActor **)((u8 *)arg1 + 4);
            record->type = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(LightActor **)((u8 *)arg1 + 4) == owner) {
            record->owner = incoming;
            record->type = *(u8 *)((u8 *)arg1 + 8);
        }
    } else {
        callback = D_8008B37C[*(u8 *)((u8 *)arg0 + 0x3D)];
        if (callback != 0) {
            callback(arg0, arg1, arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15164134 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15164134.s")
void *func_15164208(s32 arg0, u8 arg1, u8 arg2, s32 arg3) {
    void *result;
    GameLightDescriptor sp2C;
    struct {
        f32 value;
        u8 selector;
        u8 pad[3];
    } payload;

    payload.value = 0.0f;
    payload.selector = arg1;
    sp2C.field0 = 0;
    sp2C.field1 = 0x14;
    sp2C.field2 = 0x12C;
    sp2C.field4 = 0x27;
    result = func_1516037C(&sp2C, arg0, (void *)8, arg2, arg3);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, &payload, 8);
    }
    return result;
}
extern f32 D_800A6B10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516429C CURRENT (6405) */
s32 func_1516429C(void *arg0) {
    f32 value;
    s32 integer_value;

    value = *(f32 *)((u8 *)arg0 + 0x18);
    integer_value = (s32)value;
    *(s8 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 0x2F) = (s8)integer_value;
    *(f32 *)((u8 *)arg0 + 0x18) = value - (value * D_800A6B10);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516429C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516429C.s")
void func_1516434C(void *arg0, void *arg1, u8 arg2) {
    void *temp_v0;

    temp_v0 = (u8 *)arg0 + 0x18;
    if ((arg2 == 0x33) &&
        (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)temp_v0 + 4))) {
        *(f32 *)temp_v0 = *(f32 *)arg1;
        *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 5) = *(u8 *)((u8 *)arg1 + 5);
        *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 6) = *(u8 *)((u8 *)arg1 + 6);
        *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 7) = *(u8 *)((u8 *)arg1 + 7);
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151643A8 CURRENT (210) */
void func_151643A8(void *arg0, void *arg1, u8 arg2) {
    void *temp_v0_2;

    if (arg2 == 0x40) {
        arg0 = (u8 *)arg0 + 0x18;
        *(u8 *)((u8 *)arg0 + 0x24) = (u8) (*(u8 *)((u8 *)arg0 + 0x24) | 1);
        return;
    }
    temp_v0_2 = (u8 *)arg0 + 0x18;
    if (arg2 == 0x41) {
        *(u8 *)((u8 *)temp_v0_2 + 0x24) = (u8) (*(u8 *)((u8 *)temp_v0_2 + 0x24) & 0xFFFE);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151643A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151643A8.s")
void func_1516441C(void *, void *);
s32 func_151643F8(s32 arg0) {
    func_1516441C((void *) arg0, (void *) (arg0 + 0x18));
    return 1;
}
void func_1516441C(void *arg0, void *arg1) {
    void *sp2C;
    f32 *sp28;
    f32 sp1C[3];

    sp2C = arg1;
    sp28 = sp1C;
    func_15145CD0(((LightInput *)arg1)->field_C, &sp2C, &sp28, 1);
    ((LightObject *)arg0)->output->field_E = (s16)sp1C[0];
    ((LightObject *)arg0)->output->field_10 = (s16)sp1C[1];
    ((LightObject *)arg0)->output->field_12 = (s16)sp1C[2];
}
void func_151644F4(void *arg0, void *arg1, s32 arg2, f32 arg3, f32 arg4);

s32 func_151644A8(void *arg0) {
    f32 temp_fv0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x20);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x1C);
    func_151644F4(arg0, (u8 *)arg0 + 0x24, *(s32 *)((u8 *)arg0 + 0x18), *(f32 *)((u8 *)temp_v0 + 0) * temp_fv0, *(f32 *)((u8 *)temp_v0 + 8) * temp_fv0);
    return 1;
}
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A8050(void *, f32, f32, f32);

void func_151644F4(void *arg0, void *arg1, s32 arg2, f32 arg3, f32 arg4) {
    struct {
        s32 pad_28;
        f32 matrix[12];
        f32 input[3];
        s32 pad_68;
        f32 output[3];
    } locals;

    func_150A8050(locals.matrix, arg3, 0.0f, arg4);
    locals.input[0] = ((f32 *)arg1)[0];
    locals.input[1] = ((f32 *)arg1)[1];
    locals.input[2] = ((f32 *)arg1)[2];
    func_150A7960(locals.matrix, 0.0f, *(f32 *)&arg2, 0.0f,
                  &locals.output[0], &locals.output[1], &locals.output[2]);
    *(s16 *)(*(u8 **)((u8 *)arg0 + 0x14) + 0xE) = (s16)(s32)locals.output[0];
    *(s16 *)(*(u8 **)((u8 *)arg0 + 0x14) + 0x10) = (s16)(s32)locals.output[1];
    *(s16 *)(*(u8 **)((u8 *)arg0 + 0x14) + 0x12) = (s16)(s32)locals.output[2];
}
extern u8 D_800886F0[3];
extern u8 D_800886F4[3];
extern u8 D_800886F8[3];
extern u8 *D_800B0DF0;
extern s32 D_800BE9F0;
extern u8 D_800DCD20[3];
extern s8 D_800DCDD0;
void func_1511172C(s32);
void func_1515F170(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151645C4 CURRENT (100) */
void func_151645C4(u8 arg0) {
    D_800DCDD0 = arg0;
    if (arg0 != 0) {
        switch (D_800BE9F0) {
        case 0xB:
            func_1511172C(4);
            return;
        case 6:
            func_1515F170(0xA, 1);
            func_1511172C(4);
        case 0x39:
            D_800DCD20[0] = D_800886F0[0];
            D_800DCD20[1] = D_800886F0[1];
            D_800DCD20[2] = D_800886F0[2];
            D_800B0DF0[5] = D_800886F4[0];
            D_800B0DF0[6] = D_800886F4[1];
            D_800B0DF0[7] = D_800886F4[2];
            return;
        case 7:
        case 0xC:
        default:
            return;
        }
    }
    switch (D_800BE9F0) {
    case 6:
        func_1515F170(0xA, 0);
    case 7:
    case 0xC:
    case 0x39:
        func_1511172C(6);
        D_800DCD20[0] = D_800886F8[0];
        D_800DCD20[1] = D_800886F8[1];
        D_800DCD20[2] = D_800886F8[2];
        D_800B0DF0[5] = 0xFF;
        D_800B0DF0[6] = 0xFF;
        D_800B0DF0[7] = 0xFF;
        return;
    case 0xB:
        func_1511172C(6);
        return;
    case 0x29:
        func_1511172C(1);
        return;
    default:
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151645C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151645C4.s")
