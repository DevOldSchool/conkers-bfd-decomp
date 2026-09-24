#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D0840.c
 * Boundary evidence: docs/evidence/game_raw_composite_emitter_timed_groups.md
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
 * - func_151A4CE0
 * - func_151A4D88
 * - func_151A4E9C
 * - func_151A4ECC
 * - func_151A4F7C
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

void func_151A3390(u8 *arg0, volatile u8 arg1) {
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
    u8 pad15[3];
} Game1D0840TimedEntry;

typedef struct Game1D0840TimedState {
    u8 pad0[0x1C];
    s16 field1C;
    u8 pad1E[6];
    f32 field24;
    u8 pad28[2];
    s8 field2A;
    u8 pad2B[5];
    u8 flags30;
    u8 pad31[0x1B];
    u8 field4C;
} Game1D0840TimedState;

typedef struct Game1D0840TimedObject {
    u8 pad0[0x25];
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A361C CURRENT (190) */
s32 func_151A361C(Game1D0840TimedObject *arg0) {
    Game1D0840TimedState *state = arg0->state98;
    Game1D0840TimedEntry *entries = arg0->entries94;
    Game1D0840TimedEntry *entry;
    s32 index;
    s32 current;

    if (arg0->field2C < 2 && (state->flags30 & 1)) {
        return 0;
    }
    state->field4C += state->field2A * D_800BE9E4;
    index = arg0->field2E;
    if (index != arg0->field2D) {
        do {
            index--;
            if (index < 0) {
                index = arg0->field25 - 1;
            }
            entry = &entries[index];
            if (entry->field12 > 0) {
                entry->field12 -= D_800BE9E4;
            } else {
                entry->field10 -= D_800BE9E4 * state->field1C;
            }
            entry->field14 = 0xFF;
            entry->fieldC += D_800BE9A4 * state->field24;
            if (entry->field10 < 0) {
                state->flags30 &= ~2;
                if (index != arg0->field2D) {
                    do {
                        current = arg0->field2D + 1;
                        arg0->field2D = current;
                        if (arg0->field25 == arg0->field2D) {
                            arg0->field2D = 0;
                        }
                        arg0->field2C--;
                    } while (index != arg0->field2D);
                }
                entries[arg0->field2D].field10 = 0;
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4A38.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4CE0 CURRENT (10) */
void func_151A4CE0(void *arg0, void *arg1, u8 arg2) {
    void *temp_v0;
    s32 temp_v1;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    if (arg2 == 0) {
        if ((*(s32 *)((u8 *)temp_v0 + 0) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_151A4E9C(arg0);
        }
    } else if (arg2 == 0x2D) {
        arg0 = *(void **)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)temp_v0 + 0);
        if ((s32)arg0 == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32)arg0;
            *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4CE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4CE0.s")
extern void func_1516972C(void *arg0, u8 *arg1);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4D88 CURRENT (30) */
void func_151A4D88(void *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    void *temp_a0;
    void *temp_v1;

    temp_v0 = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
        if ((*(s32 *)temp_v0 == *(s32 *)arg1) || (temp_v0[4] == arg1[4])) {
            func_1516972C(arg0, arg1);
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4E9C CURRENT (35) */
void func_151A4E9C(void *arg0) {
    u8 temp_t0;
    volatile u8 *temp_v0;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    temp_t0 = temp_v0[0x30] | 1;
    temp_v0[0x30] = temp_t0;
    temp_v0[0x30] = (u8) (temp_t0 | 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4E9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4E9C.s")
extern void *func_151A3504(void *arg0, u8 arg1);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4ECC CURRENT (931) */
void func_151A4ECC(void *arg0) {
    u8 *temp_a0;
    void *temp_v0;
    s32 var_v1;

    var_v1 = 0;
    temp_a0 = (u8 *)arg0 + 0x28;
    temp_v0 = *(void **)((u8 *)arg0 + 0x28);
    if (*(s32 *)temp_v0 == 0) {
        var_v1 = 1;
    }
    if (temp_a0[4] != *(u8 *)((u8 *)temp_v0 + 0x3B)) {
        var_v1 = 1;
    }
    if ((var_v1 == 0) && (*(s32 *)((u8 *)temp_v0 + 0x1D4) != 0) &&
        ((*(u8 *)((u8 *)temp_v0 + 0x74) & 0xF) != 0xF)) {
        func_151A3504(temp_a0, *(u8 *)((u8 *)arg0 + 0xC), arg0);
        var_v1 = 1;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4F7C CURRENT (647) */
void func_151A4F7C(Game1D0840State *arg0, Game1D0840Data *arg1, s32 arg2) {
    s32 temp_t6;

    temp_t6 = arg2 & 0xFF;
    if ((temp_t6 == 0) && ((arg0->field_28.field_0 == arg1->field_0) ||
        (arg0->field_28.field_4 == arg1->field_4))) {
        func_1516972C(arg0, arg1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4F7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4F7C.s")
