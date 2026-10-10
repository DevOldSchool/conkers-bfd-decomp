#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D0840.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_composite_emitter_timed_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A361C
 * - func_151A37C0
 * - func_151A3BE4
 * - func_151A4590
 * - func_151A4638
 * - func_151A483C
 * - func_151A4900
 * - func_151A4A38
 * - func_151A4D88
 * - func_151A4ECC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1D0840LaunchPacket {
    void *owner;
    u8 mode;
    u8 enabled;
    u8 pad6[2];
    f32 zero0;
    f32 zero1;
    f32 zero2;
    f32 scale;
    s16 field18;
    s16 field1A;
    s16 field1C;
    u8 pad1E[2];
    f32 field20;
    f32 field24;
    u8 field28;
    u8 field29;
    u8 field2A;
    u8 field2B;
    u8 field2C;
    u8 field2D;
    u8 field2E;
    u8 pad2F;
} Game1D0840LaunchPacket;

void *func_151A3504(void *, u8);
void func_151A4590(void *, u8);
void func_151A499C(void *, u8);
void func_10010154(s32, void *, s32, s32, s32);
void *func_15160A58(void *, s32, void *, s32, s32, s32, s32, s32,
                    s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A8D50;
extern f32 D_800A8D54;

void func_151A3390(u8 *arg0, u8 arg1) {
    Game1D0840LaunchPacket packet;
    f32 origin[3];

    packet.owner = arg0;
    packet.mode = arg0[0x3B];
    packet.enabled = 1;
    packet.zero0 = 0.0f;
    packet.zero1 = 0.0f;
    packet.zero2 = 0.0f;
    packet.field2B = 1;
    packet.field2C = 0xFF;
    packet.field2D = 8;
    packet.field2E = 0x1F;
    packet.field18 = 0xAA;
    packet.field1A = 0x28;
    packet.field1C = 7;
    packet.field28 = 2;
    packet.field29 = 4;
    packet.field2A = 1;
    packet.scale = D_800A8D50;
    packet.field20 = 30.0f;
    packet.field24 = D_800A8D54;
    func_151A3504(&packet, arg1);
    func_151A4590(arg0, arg1);
    func_151A499C(arg0, arg1);
    func_10010154(0x1AA, arg0, 0x55F0, 0x3E8, 0xFA0);
    origin[0] = 0.0f;
    origin[1] = 0.0f;
    origin[2] = 0.0f;
    func_15160A58(arg0, 1, origin, 2, 0x12C, 0x50, 0xFF, 0xFF,
                   0x75, 0xFF, 0, -1, 0, 0, arg1, 1);
}
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game1D0840Vec3;

typedef struct {
    u8 request[0x30];
    s8 field30;
    u8 pad31[3];
    Game1D0840Vec3 vec34;
    f32 field40;
    s8 field44;
    u8 pad45[3];
    f32 field48;
    s8 field4C;
    u8 pad4D[3];
    Game1D0840Vec3 output50;
    s16 field5C;
    u16 flags5E;
    s32 field60;
    u8 pad64;
    s8 field65;
    u8 pad66[2];
    u8 tail68[4];
} Game1D0840SpawnLocals;

void func_10022EC0(void *, void *, s32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32,
                    s32, s32, s32);
s32 func_151A4E34();

void *func_151A3504(void *arg0, u8 arg1) {
    Game1D0840SpawnLocals locals;
    void *result;

    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    func_10022EC0(locals.request, arg0, 0x30);
    locals.field44 = 0;
    locals.field65 = 0x32;
    locals.flags5E = 2;
    locals.field5C = 0x3E8;
    locals.field30 = 6;
    locals.field4C = 0;
    locals.field40 = 0.0f;
    locals.field48 = 0.0f;
    if (func_151A4E34(locals.request, &locals.output50.x) != 0) {
        locals.vec34 = locals.output50;
        locals.flags5E |= 4;
    }
    locals.field60 = 8;
    result = func_15147A80(&locals.output50, (void *)0x50, 0x18, 6, 6, 6,
                           0, 0, 0, arg1, 0);
    if (result != 0) {
        func_10022EC0(*(void **)((u8 *)result + 0x98), locals.request, 0x50);
    }
    return result;
}
extern s32 D_800BE9E4;
extern f32 D_800BE9A4;

typedef struct Game1D0840TimedEntry {
    Game1D0840Vec3 value0;
    f32 fieldC;
    s16 field10;
    s16 field12;
    u8 field14;
    u8 field15;
    u8 pad16[2];
} Game1D0840TimedEntry;

typedef struct Game1D0840TimedState {
    u8 *owner;
    u8 identity;
    u8 transformIndex;
    u8 pad06[2];
    Game1D0840Vec3 input08;
    f32 field14;
    s16 field18;
    s16 field1A;
    s16 field1C;
    u8 pad1E[2];
    f32 field20;
    f32 field24;
    u8 field28;
    u8 field29;
    s8 field2A;
    u8 pad2B[5];
    u8 flags30;
    u8 pad31[3];
    Game1D0840Vec3 previous34;
    f32 field40;
    u8 field44;
    u8 pad45[3];
    f32 field48;
    u8 field4C;
} Game1D0840TimedState;

typedef struct Game1D0840TimedObject {
    u8 pad0[0xC];
    u8 fieldC;
    u8 pad0D[3];
    Game1D0840Vec3 position10;
    u8 pad1C[2];
    u16 flags1E;
    u8 pad20[5];
    u8 field25;
    u8 pad26[6];
    s8 field2C;
    s8 field2D;
    s8 field2E;
    u8 pad2F[0x25];
    Game1D0840Vec3 output54;
    u8 pad60[0x34];
    Game1D0840TimedEntry *entries94;
    Game1D0840TimedState *state98;
} Game1D0840TimedObject;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A361C CURRENT (115) */
s32 func_151A361C(Game1D0840TimedObject *arg0) {
    Game1D0840TimedState *state = arg0->state98;
    Game1D0840TimedEntry *entries = arg0->entries94;
    Game1D0840TimedEntry *entry;
    s32 index;
    s32 current;

    if (arg0->field2C < 2 && (state->flags30 & 1)) {
        return 0;
    }
    state->field4C = (u32)state->field4C + (u32)(s32)state->field2A * (u32)D_800BE9E4;
    index = arg0->field2E;
    if (index != arg0->field2D) {
        do {
            index--;
            if (index < 0) {
                index = arg0->field25 - 1;
            }
            entry = &entries[index];
            if (entry->field12 > 0) {
                entry->field12 = (u32)(s32)entry->field12 - (u32)D_800BE9E4;
            } else {
                entry->field10 = (u32)(s32)entry->field10 - (u32)D_800BE9E4 * (u32)(s32)state->field1C;
            }
            entry->field14 = 0xFF;
            entry->fieldC += D_800BE9A4 * state->field24;
            if (entry->field10 < 0) {
                state->flags30 &= ~2;
                current = arg0->field2D;
                if (index != current) {
                    do {
                        arg0->field2D = current + 1;
                        current = arg0->field2D;
                        if (arg0->field25 == current) {
                            arg0->field2D = 0;
                            current = arg0->field2D;
                        }
                        arg0->field2C--;
                    } while (index != current);
                }
                entries[current].field10 = 0;
            }
        } while (index != arg0->field2D);
    }
    if (arg0->field2C > 0) {
        entry = &entries[arg0->field2D];
        arg0->output54 = entry->value0;
    } else {
        arg0->output54.x = 0.0f;
        arg0->output54.y = 0.0f;
        arg0->output54.z = 0.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A361C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A361C.s")
u32 func_150ADA20(void);
s32 func_151491F4(s32, s32, s32, s32, s32, s32, s32, s32);
void func_151A4E9C(void *);
f32 sqrtf(f32);
f32 fabsf(f32);
extern f32 D_800A8D58;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A37C0 CURRENT (12270) */
s32 func_151A37C0(Game1D0840TimedObject *object) {
    Game1D0840LaunchPacket snapshot;
    Game1D0840Vec3 point;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 distance;
    f32 inverse;
    f32 age;
    f32 ageStep;
    f32 value;
    f32 valueStep;
    f32 zStep;
    Game1D0840TimedState *state;
    Game1D0840TimedEntry *entries;
    Game1D0840TimedEntry *entry;
    s32 initialized;
    s32 spawned;
    Game1D0840Vec3 *previous;

    state = object->state98;
    entries = object->entries94;
    if (*(s32 *) state->owner == 0) {
        return 0;
    }
    if (state->identity != state->owner[0x3B]) {
        return 0;
    }
    initialized = 0;
    if (!(object->flags1E & 4)) {
        if (func_151A4E34(state, &object->position10.x) != 0) {
            initialized = 1;
            state->previous34 = object->position10;
            object->flags1E |= 4;
        } else {
            return 1;
        }
    }
    if ((initialized == 0) &&
        (func_151A4E34(state, &object->position10.x) == 0)) {
        func_151A4E9C(object);
        func_10022EC0(&snapshot, state, 0x30);
        spawned = func_151491F4(0x12C, -1, 0xA, 0, 5, 0x30,
                               object->fieldC, 0);
        if (spawned != 0) {
            func_10022EC0((void *) (spawned + 0x28), &snapshot, 0x30);
        }
    } else {
        dx = object->position10.x - state->previous34.x;
        dy = object->position10.y - state->previous34.y;
        dz = object->position10.z - state->previous34.z;
        if ((D_800A8D58 < fabsf(dx)) || (D_800A8D58 < fabsf(dy)) ||
            (D_800A8D58 < fabsf(dz))) {
            state->field40 += sqrtf(dx * dx + dy * dy + dz * dz) * state->field14;
        }
        distance = state->field40;
        if (distance > 1.0f) {
            inverse = 1.0f / distance;
            previous = &state->previous34;
            point = *previous;
            age = state->field48 + D_800BE9A4;
            ageStep = age * inverse;
            value = state->field20 + state->field24 * age;
            zStep = dz * inverse;
            valueStep = (state->field20 - value) * inverse;
            do {
                entry = &entries[object->field2E];
                entry->value0 = point;
                entry->fieldC = value;
                entry->field10 = state->field18;
                entry->field12 = state->field1A;
                entry->field15 = state->field44;
                state->field44 += state->field28 +
                    func_150ADA20() % (u32) (state->field29 + 1);
                entry->field14 = 0xFF;
                object->field2E++;
                if (object->field25 == object->field2E) {
                    object->field2E = 0;
                }
                object->field2C++;
                if (object->field2D == object->field2E) {
                    object->field2D++;
                    if (object->field25 == object->field2D) {
                        object->field2D = 0;
                    }
                    object->field2C--;
                }
                value += valueStep;
                point.x += dx * inverse;
                point.y += dy * inverse;
                age -= ageStep;
                point.z += zStep;
                state->field40 -= 1.0f;
            } while (state->field40 > 1.0f);
            *previous = point;
            state->field48 = age;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A37C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A37C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A3BE4.s")
u32 func_1513418C(void *, s32, u8, s32);
extern f32 D_800A8D5C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4590 CURRENT (716) */
void func_151A4590(void *arg0, u8 arg1) {
    struct {
        s32 zero0;
        s32 zero4;
        u8 selector;
        u8 pad9[3];
        void *object;
        s8 kind;
        u8 pad11[3];
        f32 x;
        f32 y;
        f32 z;
        f32 scale;
        f32 size;
        s16 lifetime;
        s8 a;
        s8 b;
        s8 c;
        s8 d;
    } packet;
    s32 selector;
    f32 scale;

    if (arg0 != 0) {
        packet.zero0 = 0;
        packet.zero4 = 0;
        selector = *(u8 *)((u8 *)arg0 + 0x3B);
        scale = D_800A8D5C;
        packet.kind = 1;
        packet.lifetime = 0x64;
        packet.a = 0xA;
        packet.b = 1;
        packet.c = -1;
        packet.d = 0;
        packet.object = arg0;
        packet.selector = selector;
        packet.x = 0.0f;
        packet.y = 0.0f;
        packet.z = 0.0f;
        packet.scale = scale;
        packet.size = 3.0f;
        func_1513418C((void *)&packet, 0, arg1, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4590 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4590.s")
typedef struct Game1D0840EmitterPacket {
    u32 field00;
    s32 field04;
    u16 field08;
    s16 lifetime;
    s32 field0C;
    s32 field10;
    u8 field14;
    u8 field15;
    u8 field16;
    u8 field17;
    u8 field18;
    u8 field19;
    u8 field1A;
    u8 field1B;
    u8 field1C;
    u8 callback;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    Game1D0840Vec3 position;
    u8 pad3C[0xC];
    Game1D0840Vec3 velocity;
    f32 field54;
    u32 flags58;
    u8 pad5C[4];
    u8 field60;
    u8 field61;
    u8 field62;
    s8 field63;
    u8 pad64[0xC];
} Game1D0840EmitterPacket;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void *func_15130374(s32, u8, s32, u8, s32);
extern f32 D_800A8D60;
extern f32 D_800BE9A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4638 CURRENT (470) */
void func_151A4638(f32 x, f32 y, f32 z, f32 velocityX, f32 velocityY,
                   f32 velocityZ, u8 *owner) {
    Game1D0840EmitterPacket packet;
    f32 scale;
    s16 parameters[6];
    u8 *result;

    packet.callback = 0x27;
    packet.field08 = 0x1401;
    packet.field00 = 0x200005;
    packet.field04 = 0;
    packet.lifetime = (func_150ADA20() % 5U) + 0xF;
    packet.field0C = 0;
    packet.field10 = 0;
    packet.field14 = 0x8A;
    packet.field15 = 0;
    packet.field16 = 0;
    packet.field17 = 0xFF;
    packet.field18 = 0;
    packet.field19 = 0;
    packet.field1A = 0;
    packet.field1E = 1;
    packet.field20 = 0xFF;
    packet.field22 = 1;
    packet.field24 = 1.0f;
    packet.field28 = func_150ADA68() * 50.0f + 500.0f;
    packet.position.x = x;
    packet.position.y = y;
    packet.position.z = z;
    scale = D_800A8D60 * D_800BE9A8;
    packet.velocity.x = -velocityX * scale;
    packet.velocity.y = -velocityY * scale;
    packet.flags58 = 0xD;
    packet.field60 = 1;
    packet.field61 = 1;
    packet.field2C = packet.field28;
    packet.velocity.z = -velocityZ * scale;
    packet.field54 = 0.0f;
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x80;
    }
    packet.field1B = 0xFF;
    packet.field1C = 0xFF;
    packet.field62 = 0;
    packet.field63 = -1;
    parameters[0] = 0x10;
    parameters[1] = 0xF;
    parameters[2] = 0xD;
    parameters[3] = 0x13;
    parameters[4] = 0x11;
    parameters[5] = -0x18;
    result = func_15130374((s32) &packet, 0, 0xC, owner[0xC], 1);
    if (result != 0) {
        func_10022EC0(result + 0xA8, parameters, 0xC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4638 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4638.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A483C CURRENT (65) */
s32 func_151A483C(u8 *arg0, s32 arg1) {
    f32 temp_fv0;
    s16 temp_t5;
    u8 *temp_v0;
    s16 temp_v1;

    temp_v0 = (void *)(arg0 + 0xA8);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1A);
    arg1 = 2;
    if (temp_v1 < *(s16 *)((u8 *)arg0 + 0xAC)) {
        *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (temp_v1 * *(s16 *)((u8 *)arg0 + 0xAE));
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 8)) {
        temp_fv0 = (f32) (*(s16 *)((u8 *)temp_v0 + 0xA) * D_800BE9E4);
        *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + temp_fv0);
        *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + temp_fv0);
    }
    if (*(s16 *)temp_v0 > *(s16 *)((u8 *)arg0 + 0x1A)) {
        *(s8 *)((u8 *)arg0 + 0x72) = 1;
        *(s8 *)((u8 *)arg0 + 0x70) = arg1;
        *(s8 *)((u8 *)arg0 + 0x71) = arg1;
        temp_t5 = *(s16 *)((u8 *)temp_v0 + 2);
        *(s16 *)((u8 *)arg0 + 0x18) = 0x5203;
        *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s16 *)((u8 *)arg0 + 0x1A) * temp_t5);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A483C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A483C.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4900 CURRENT (80) */
s32 func_151A4900(u8 *arg0, s32 arg1) {
    f32 temp_fv0;
    s16 temp_a1;
    u8 *temp_v1;

    temp_a1 = *(s16 *)((u8 *)arg0 + 0x1A);
    temp_v1 = (void *)(arg0 + 0xA8);
    if (temp_a1 < *(s16 *)((u8 *)arg0 + 0xAC)) {
        *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (temp_a1 * *(s16 *)((u8 *)arg0 + 0xAE));
    }
    if (temp_a1 < *(s16 *)((u8 *)temp_v1 + 8)) {
        temp_fv0 = (f32) (*(s16 *)((u8 *)temp_v1 + 0xA) * D_800BE9E4);
        *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + temp_fv0);
        *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + temp_fv0);
    }
    *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s16 *)((u8 *)arg0 + 0x1A) * *(s16 *)((u8 *)temp_v1 + 2));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4900 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4900.s")
void func_10022EC0(void *, void *, s32);
s32 func_151491F4(s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A8D64;

typedef struct Game1D0840EffectPacket {
    void *field_0;
    u8 field_4;
    u8 pad5[3];
    f32 field_8;
    f32 field_C;
    u8 field_10;
    u8 pad11[3];
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    u8 stack_pad[4];
} Game1D0840EffectPacket;

void func_151A499C(void *arg0, u8 arg1) {
    Game1D0840EffectPacket packet;
    s32 temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_8 = D_800A8D64;
    packet.field_C = 0.0f;
    packet.field_10 = 1;
    packet.field_14 = 0.0f;
    packet.field_18 = 0.0f;
    packet.field_1C = 0.0f;
    temp_v0 = func_151491F4(0x12C, -1, 5, 0, 1, 0x20, (s32) arg1, 0);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0x20);
    }
}
typedef struct Game1D0840BurstPacket {
    s16 count;
    s16 countRange;
    u8 callback;
    u8 pad05;
    u16 field06;
    u32 field08;
    s32 field0C;
    s16 field10;
    s16 field12;
    s32 field14;
    s32 field18;
    u8 field1C;
    u8 field1D;
    u8 field1E;
    u8 field1F;
    u8 field20;
    u8 field21;
    u8 field22;
    u8 field23;
    u8 field24;
    u8 field25;
    s16 field26;
    s16 field28;
    s16 field2A;
    f32 field2C;
    f32 field30;
    f32 field34;
    Game1D0840Vec3 position;
    s16 field44;
    s16 field46;
    s16 field48;
    s16 field4A;
    f32 field4C;
    f32 field50;
    f32 field54;
    f32 field58;
    u32 flags5C;
    s8 field60;
    s8 field61;
    u8 field62;
    u8 field63;
    u8 field64;
    u8 pad65[3];
    f32 field68;
} Game1D0840BurstPacket;

void func_15143134(f32 *, f32 *, s32);
void func_15153634(Game1D0840BurstPacket *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4A38 CURRENT (463) */
void func_151A4A38(u8 *object) {
    u8 *owner;
    Game1D0840Vec3 position;
    Game1D0840BurstPacket packet;
    s16 angle;
    Game1D0840EffectPacket *state;

    state = (Game1D0840EffectPacket *) (object + 0x28);
    if ((*(s32 *) *(void **) (object + 0x28) == 0) ||
        (owner = state->field_0, *(s32 *) owner == 8) ||
        (state->field_4 != owner[0x3B])) {
        *(s16 *) (object + 0xE) = -1;
        object[0xD] |= 1;
        return;
    }
    if ((*(void **) (owner + 0x1D4) != 0) &&
        ((owner[0x74] & 0xF) != 0xF)) {
        state->field_C += state->field_8 * D_800BE9A4;
        if (state->field_C > 1.0f) {
            owner = state->field_0;
            angle = (*(u16 *) (owner + 0x76) >> 8) - 0x40;
            func_15143134(&state->field_14, &position.x,
                         (s32) *(u8 **) (owner + 0x1D4) +
                         (state->field_10 << 6));
            packet.countRange = 0;
            packet.count = (s32) state->field_C;
            state->field_C -= (f32) packet.count;
            packet.callback = 0x28;
            packet.field06 = 0xC01;
            packet.field08 = 0x200005;
            packet.field0C = 0;
            packet.field10 = 0x17;
            packet.field12 = 0xD;
            packet.field14 = 0;
            packet.field18 = 0;
            packet.field1C = 0;
            packet.field1D = 0;
            packet.field1E = 0;
            packet.field1F = 0xFF;
            packet.field20 = 0;
            packet.field21 = 0;
            packet.field22 = 0;
            packet.field30 = 300.0f;
            packet.field34 = 400.0f;
            packet.position = position;
            packet.field26 = 1;
            packet.field28 = 0;
            packet.field2A = 1;
            packet.field64 = 0;
            packet.field44 = angle - 0x19;
            packet.field46 = -0x2C;
            packet.field48 = 0x32;
            packet.field4A = 0x32;
            packet.flags5C = 7;
            packet.field62 = 1;
            packet.field63 = 0;
            packet.field54 = -0.5f;
            packet.field58 = -0.5f;
            packet.field4C = 0.0f;
            packet.field2C = 1.0f;
            packet.field50 = 15.0f;
            if (func_150ADA20() & 1) {
                packet.flags5C |= 0x40;
            }
            if (func_150ADA20() & 1) {
                packet.flags5C |= 0x80;
            }
            packet.field23 = 0xFF;
            packet.field24 = 0;
            packet.field25 = 0xFF;
            packet.field60 = -1;
            packet.field61 = -1;
            func_15153634(&packet, 0xFF, object[0xC], object[1]);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4A38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4A38.s")
void func_151A4CE0(void *arg0, void *arg1, u8 arg2) {
    void *temp_v0;
    s32 value;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    if (arg2 == 0) {
        if ((*(s32 *)((u8 *)temp_v0 + 0) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_151A4E9C(arg0);
        }
    } else if (arg2 == 0x2D) {
        value = *(s32 *)((u8 *)arg1 + 0);
        if (value == *(s32 *)((u8 *)temp_v0 + 0)) {
            *(s32 *)((u8 *)temp_v0 + 0) = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)((u8 *)temp_v0 + 0)) {
            *(s32 *)((u8 *)temp_v0 + 0) = value;
            *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
extern void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4D88 CURRENT (30) */
void func_151A4D88(void *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    void *temp_a0;
    void *temp_v1;

    temp_v0 = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
        if ((*(s32 *)temp_v0 == *(s32 *)arg1) || (temp_v0[4] == arg1[4])) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        temp_v1 = *(void **)arg1;
        temp_a0 = *(void **)temp_v0;
        if (temp_v1 == temp_a0) {
            *(void **)temp_v0 = *(void **)(arg1 + 4);
            temp_v0[4] = arg1[9];
            return;
        }
        if (*(void **)(arg1 + 4) == temp_a0) {
            *(void **)temp_v0 = temp_v1;
            temp_v0[4] = arg1[8];
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4D88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4D88.s")
typedef struct Game1D0840TransformSource {
    u8 pad0[0x74];
    u8 flags;
    u8 pad75[0x15F];
    u8 *transformBase;
} Game1D0840TransformSource;

typedef struct Game1D0840TransformRequest {
    Game1D0840TransformSource *source;
    u8 pad4;
    u8 transformIndex;
    u8 pad6[2];
    f32 input[3];
} Game1D0840TransformRequest;

void func_15143134(f32 *, f32 *, s32);

s32 func_151A4E34(Game1D0840TransformRequest *arg0, f32 *arg1) {
    u8 *temp_v1;
    Game1D0840TransformSource *temp_v0;

    temp_v0 = arg0->source;
    temp_v1 = temp_v0->transformBase;
    if (temp_v1 == 0) {
        return 0;
    }
    if ((temp_v0->flags & 0xF) == 0xF) {
        return 0;
    }
    func_15143134(arg0->input, arg1, (s32)temp_v1 + (arg0->transformIndex << 6));
    return 1;
}
void func_151A4E9C(void *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    temp_v0[0x30] |= 1;
    temp_v0[0x30] |= 4;
}
extern void *func_151A3504(void *arg0, u8 arg1);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4ECC CURRENT (426) */
void func_151A4ECC(void *arg0) {
    u8 *temp_a0;
    void *temp_v0;
    u8 saved;
    s32 var_v1;

    var_v1 = 0;
    temp_a0 = (u8 *)arg0 + 0x28;
    if (*(s32 *)*(void *volatile *)((u8 *)arg0 + 0x28) == 0) {
        var_v1 = 1;
    }
    temp_v0 = *(void **)temp_a0;
    if (temp_a0[4] != *(u8 *)((u8 *)temp_v0 + 0x3B)) {
        var_v1 = 1;
    }
    if ((var_v1 == 0) && (*(s32 *)((u8 *)temp_v0 + 0x1D4) != 0) &&
        ((*(u8 *)((u8 *)temp_v0 + 0x74) & 0xF) != 0xF)) {
        saved = 1;
        func_151A3504(temp_a0, *(u8 *)((u8 *)arg0 + 0xC));
        var_v1 = saved;
    }
    if (var_v1 != 0) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        *(u8 *)((u8 *)arg0 + 0xD) |= 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4ECC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4ECC.s")
typedef struct {
    s32 field_0;
    u8 field_4;
} Game1D0840Data;

typedef struct {
    u8 pad_0[0x28];
    Game1D0840Data field_28;
} Game1D0840State;

void func_151A4F7C(Game1D0840State *arg0, Game1D0840Data *arg1, u8 arg2) {
    Game1D0840Data *data = &arg0->field_28;

    if ((arg2 == 0) && ((arg1->field_0 == data->field_0) ||
        (arg1->field_4 == data->field_4))) {
        func_1516972C(arg0);
    }
}
