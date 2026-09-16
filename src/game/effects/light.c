#include "types.h"

/*
 * Reviewed source unit: src/game/effects/light.c
 * Boundary evidence: docs/evidence/effects_light.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151602C0
 * - func_1516037C
 * - func_151603FC
 * - func_151604A0
 * - func_151606A8
 * - func_151607A4
 * - func_15160954
 * - func_15160A58
 * - func_15160B74
 * - func_15160CDC
 * - func_15160E30
 * - func_15161540
 * - func_151615F8
 * - func_151616D0
 * - func_15161804
 * - func_15161860
 * - func_151618BC
 * - func_151619A0
 * - func_15161A68
 * - func_15161F4C
 * - func_15162034
 * - func_15162110
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
 * - func_1516381C
 * - func_151638E0
 * - func_151639D0
 * - func_15163A60
 * - func_15163B98
 * - func_15163BE8
 * - func_15163CF8
 * - func_15163DEC
 * - func_15163FEC
 * - func_151640C0
 * - func_15164134
 * - func_1516429C
 * - func_151643A8
 * - func_151644F4
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

#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151602C0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516037C CURRENT (108) */
void *func_1516037C(GameLightDescriptor *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4) {
    void *sp24;
    void *temp_v0;

    temp_v0 = func_15167A68(0x35, arg4, (u8 *)arg2 + 0x18, 1, (s32)arg3, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    sp24 = temp_v0;
    func_10022EC0((u8 *)temp_v0 + 0xE, arg0, 6);
    *(s32 *)((u8 *)sp24 + 0x14) = arg1;
    return sp24;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516037C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516037C.s")
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
s32 func_15160684(s32 arg0) {
    func_15163DEC(arg0, arg0 + 0x18);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151606A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151607A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160954.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160A58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15160B74.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161540.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151615F8.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151618BC.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15161F4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162034.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162110.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151621B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151623F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162510.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162740.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15162FAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151630F4.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163604.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163704.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516381C CURRENT (100) */
void func_1516381C(s32 arg0, u8 arg1, u8 arg2, s32 arg3) {
    GameLightDescriptor sp20;

    sp20.field0 = 0;
    sp20.field1 = -1;
    sp20.field2 = 0x12C;
    sp20.field4 = arg1;
    func_1516037C(&sp20, arg0, 0, arg2, arg3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516381C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_1516381C.s")
void func_1516387C(s32 arg0, u8 arg1, s8 arg2, s16 arg3, u8 arg4,
                   void *arg5, u8 arg6, s32 arg7) {
    GameLightDescriptor sp20;

    sp20.field0 = arg1;
    sp20.field1 = arg2;
    sp20.field2 = arg3;
    sp20.field4 = arg4;
    func_1516037C(&sp20, arg0, arg5, arg6, arg7);
}
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163BE8.s")
s32 func_15163CD0(s32 arg0) {
    func_15163CF8(arg0 + 0x30, arg0);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163CF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_15163DEC.s")
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151643A8 CURRENT (759) */
void func_151643A8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_t6;
    void *temp_v0;
    void *temp_v0_2;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x40) {
        temp_v0 = arg0 + 0x18;
        *(u8 *)((u8 *)temp_v0 + 0x24) = (u8) (*(u8 *)((u8 *)temp_v0 + 0x24) | 1);
        return;
    }
    temp_v0_2 = arg0 + 0x18;
    if (temp_t6 == 0x41) {
        *(u8 *)((u8 *)temp_v0_2 + 0x24) = (u8) (*(u8 *)((u8 *)temp_v0_2 + 0x24) & 0xFFFE);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151643A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151643A8.s")
void func_1516441C(void *, void *);
s32 func_151643F8(s32 arg0) {
    func_1516441C(arg0, arg0 + 0x18);
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151644F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/light/func_151645C4.s")
