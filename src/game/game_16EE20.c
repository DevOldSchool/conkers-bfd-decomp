#include "types.h"

/*
 * Reviewed source unit: src/game/game_16EE20.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151419D0
 * - func_15141A7C
 * - func_15141E38
 * - func_15141F78
 * - func_15142600
 * - func_1514306C
 * - func_15143134
 * - func_151432BC
 * - func_151438D8
 * - func_15143D18
 * - func_15143E94
 * - func_1514401C
 * - func_1514470C
 * - func_15144CEC
 * - func_15144E80
 * - func_151452C4
 * - func_1514563C
 * - func_15145740
 * - func_15145AD8
 * - func_15145CD0
 * - func_15145DB4
 * - func_15145EA4
 * - func_15146078
 * - func_151462C8
 * - func_1514654C
 * - func_151467A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Reviewed bank-01 model records; descriptive labels, not original symbols.
 * See config/model-semantic-names.json.
 */
enum {
    MODEL_CONKER = 0,
    MODEL_CONKER_VARIANT_1 = 1,
    MODEL_CONKER_VARIANT_2 = 2,
    MODEL_CONKER_VARIANT_3 = 3,
    MODEL_CONKER_VARIANT_4 = 4,
    MODEL_ROCKMAN = 16,
    MODEL_BUGGER_LUGS = 33,
    MODEL_BIG_BIG_GUY = 43,
    MODEL_DINO_BABY = 54,
    MODEL_HAYBOT_HAY_COVERED = 69,
    MODEL_HAYBOT = 75,
    MODEL_FANGY = 83,
    MODEL_BUGA_THE_KNUT = 84,
    MODEL_SHC_SOLDIER = 88,
    MODEL_COW = 121,
    MODEL_THE_EXPERIMENT = 123,
    MODEL_ROCKWOMAN = 145,
    MODEL_CONKER_BLACK_OUTFIT = 150,
    MODEL_RED_DINOSAUR = 165
};

void func_1514EDF0(s32 arg0, s32 arg1);

void func_15141970(s32 *arg0) {
    func_1514EDF0((s32)arg0, arg0[0xB]);
}
void func_15141990(s32 *arg0) {
    func_15141970(arg0);
}
void func_151419B0(s32 *arg0) {
    func_15141970(arg0);
}
void func_1516972C(void *);

extern f32 D_800A56A4;
extern s32  D_80082FA0;
extern f32 D_800A56C4;
extern f32 D_800A56C8;
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151419D0 CURRENT (430) */
void func_151419D0(s32 arg0, void *arg1, u8 arg2) {
    void *temp_a3;
    s32 temp_v1;
    void *temp_v0;
    void *temp_v0_2;

    temp_a3 = (void *)arg0;
    if (arg2 == 0) {
        temp_v0 = (u8 *)temp_a3 + 0x28;
        temp_v1 = *(s32 *)arg1;
        if ((temp_v1 == *(s32 *)((u8 *)temp_v0 + 4)) ||
            (*(u8 *)((u8 *)temp_v0 + 8) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(temp_a3);
        }
    } else {
        temp_v0_2 = (u8 *)temp_a3 + 0x28;
        if (arg2 == 0x2D) {
            arg0 = *(s32 *)((u8 *)temp_v0_2 + 4);
            temp_v1 = *(s32 *)arg1;
            if (temp_v1 == arg0) {
                *(s32 *)((u8 *)temp_v0_2 + 4) = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)((u8 *)temp_v0_2 + 8) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == arg0) {
                *(s32 *)((u8 *)temp_v0_2 + 4) = temp_v1;
                *(u8 *)((u8 *)temp_v0_2 + 8) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151419D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151419D0.s")
s32 func_1510F8CC(s32);
s32 func_15141C0C(void *);
s32 func_15141CC0(u32);
void func_15141E38(void *, s32);
s32 func_1514ECE0(void *, s32, void **);
extern u8 D_800BE616;
extern s32 D_8008A084[];
extern s32 D_8008A0B4[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141A7C CURRENT (3828) */
void func_15141A7C(void *arg0, s32 arg1) {
    void *current;
    u8 *actor = arg0;
    s32 index;
    s32 result;
    s32 *entry;
    u8 *object;
    void *next;

    if (D_800BE616 != 0) {
        return;
    }
    index = func_15141C0C(arg0);
    if (D_8008A084[index] != 0) {
        result = ((s32 (*)(s32, void *))D_8008A084[index])(
            func_15141CC0(func_1510F8CC(*(s32 *)(actor + 0x184))), arg0);
        if (result != -1) {
            entry = &D_8008A0B4[result * 2];
            if (entry[0] != 0) {
                if (entry[1] > 0) {
                    func_15141E38(arg0, result);
                } else {
                    ((void (*)(void *, s32, s32, s32))entry[0])(
                        arg0, arg1, 0, result);
                }
            }
        }
    }
    current = *(void **)(actor + 0x2F4);
    if (func_1514ECE0(current, 0x1A, &current) != 0) {
        do {
            object = *(u8 **)((u8 *)current + 0x10);
            entry = &D_8008A0B4[*(s32 *)(object + 0x28) * 2];
            if (entry[0] != 0) {
                ((void (*)(void *, s32, s16))entry[0])(
                    arg0, arg1, *(s16 *)(object + 0xE));
            }
            next = *(void **)((u8 *)current + 0x14);
            current = next;
        } while (func_1514ECE0(next, 0x1A, &current) != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141A7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141A7C.s")
/*
 * Descriptive role: actor_get_effect_selector_callback_index.
 * Actor model byte +0x04 selects one of 12 callbacks in D_8008A084;
 * default 11 is the null slot. A selected callback returns a separate
 * D_8008A0B4 effect-handler index, or -1 when no handler is selected.
 */
s32 func_15141C0C(void *actor) {
    switch (*(u8 *)((u8 *)actor + 4)) {
    case MODEL_COW:
        return 0xA;
    case MODEL_BUGGER_LUGS:
        return 9;
    case MODEL_THE_EXPERIMENT:
        return 8;
    case MODEL_CONKER:
    case MODEL_CONKER_VARIANT_1:
    case MODEL_CONKER_VARIANT_2:
    case MODEL_CONKER_VARIANT_3:
    case MODEL_CONKER_VARIANT_4:
    case MODEL_CONKER_BLACK_OUTFIT:
        return 0;
    case MODEL_ROCKMAN:
    case MODEL_ROCKWOMAN:
        return 1;
    case MODEL_BIG_BIG_GUY:
        return 2;
    case MODEL_BUGA_THE_KNUT:
        return 5;
    case MODEL_DINO_BABY:
    case MODEL_FANGY:
    case MODEL_RED_DINOSAUR:
        return 6;
    case MODEL_SHC_SOLDIER:
        return 7;
    case MODEL_HAYBOT_HAY_COVERED:
        return 3;
    case MODEL_HAYBOT:
        return 4;
    default:
        return 0xB;
    }
}
extern s32 D_800BE9F0;

s32 func_15141CC0(u32 arg0) {
    if (D_800BE9F0 == 0x2F) {
        return 6;
    }
    if (D_800BE9F0 == 0x42) {
        return 7;
    }
    if (D_800BE9F0 == 0x27) {
        return 8;
    }
    if (D_800BE9F0 == 0x19) {
        return 5;
    }
    switch (arg0) {
    case 10:
        return 0;
    case 7:
        return 2;
    case 11:
        return 1;
    case 15:
        return 3;
    case 2:
    case 8:
    case 12:
        if (D_800BE9F0 == 2) {
            return 7;
        }
        return 4;
    case 5:
        if (D_800BE9F0 == 0x14) {
            return 5;
        }
        return 9;
    case 0:
        return 9;
    default:
        return 9;
    }
}
void func_15141E38(void *, s32);
extern s32 D_8008A084[];
extern s32 D_8008A0B4[];
extern u8 D_800BE616;

/*
 * Descriptive role: actor_request_timed_effect_handler.
 * Checks the separate 12-callback and 20-handler index domains, their null
 * slots and the global gate; requests a handler only for a positive duration.
 * actorAddress retains the existing integer ABI.
 */
void func_15141DA4(s32 actorAddress, s32 selectorCallbackIndex, s32 effectHandlerIndex) {
    s32 *handlerRecord;

    if ((selectorCallbackIndex < 0xC) && (selectorCallbackIndex >= 0) && (effectHandlerIndex < 0x14) && (effectHandlerIndex >= 0) &&
        (D_800BE616 == 0) && (D_8008A084[selectorCallbackIndex] != 0) && (effectHandlerIndex != -1)) {
        handlerRecord = (s32 *)((u8 *)D_8008A0B4 + effectHandlerIndex * 8);
        if ((handlerRecord[0] != 0) && (handlerRecord[1] > 0)) {
            func_15141E38((void *)actorAddress, effectHandlerIndex);
        }
    }
}
s32 func_1514ECE0(void *, s32, void **);
void func_1514EC1C(void *, void *, s32);
u8 *func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141E38 CURRENT (1418) */
void func_15141E38(void *arg0, s32 arg1) {
    struct {
        s32 id;
        void *owner;
        u8 flag;
    } packet;
    void *current;
    void *next;
    void *found;
    u8 *created;
    s32 *entry;

    current = *(void **)((u8 *)arg0 + 0x2F4);
    found = 0;
    if (func_1514ECE0(current, 0x1A, &current) != 0) {
        do {
            entry = &D_8008A0B4[arg1 * 2];
            if (arg1 == *(s32 *)(*(u8 **)((u8 *)current + 0x10) + 0x28)) {
                found = current;
                *(s16 *)(*(u8 **)((u8 *)current + 0x10) + 0xE) = (s16)entry[1];
            }
            next = *(void **)((u8 *)current + 0x14);
            current = next;
        } while (func_1514ECE0(next, 0x1A, &current) != 0);
    }
    if (found == 0) {
        packet.id = arg1;
        packet.owner = arg0;
        packet.flag = *(u8 *)((u8 *)arg0 + 0x3B);
        created = func_15149130((s16)D_8008A0B4[arg1 * 2 + 1], -1, -1, -1,
                               1, 0x32, 0xC, 0xFF, 1);
        if (created != 0) {
            func_10022EC0(created + 0x28, &packet, 0xC);
            func_1514EC1C(created, arg0, 0x1A);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141E38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141E38.s")
typedef struct Game141F78Packet {
    s32 code;
    s16 value;
    u8 kind;
    u8 zero7;
    s32 zero8;
    s32 zeroC;
    u8 color[6];
    u8 zero16;
    u8 seven;
    s32 type;
    s32 owner;
    u8 ff;
    u8 pad21;
    s16 size;
    s16 count;
} Game141F78Packet;

void *func_1513C650(s32, u8, u8, s32, f32, f32, f32, f32, f32,
                     u8, u8, s32, s32, s32, u8, s32);
s32 func_150ADA20();
f32 func_150ADA68();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141F78 CURRENT (1678) */
void func_15141F78(s32 arg0, void *arg1, f32 arg2, u8 arg3,
                   void *arg4, u8 arg5) {
    Game141F78Packet packet;
    f32 scale;

    arg0 = (u8)arg0;
    packet.kind = arg0;
    packet.zero7 = 0;
    packet.code = 0x6F701;
    packet.value = (func_150ADA20(arg0) % 61U) + 0x64;
    packet.zero8 = 0;
    packet.zeroC = 0;
    packet.color[0] = (func_150ADA20() & 0x7F) + 0x80;
    packet.color[1] = 0xFF;
    packet.color[2] = 0xFF;
    packet.color[3] = 0xFF;
    packet.color[4] = 0xFF;
    packet.color[5] = 0xFF;
    packet.type = 0x3B0002;
    packet.zero16 = 0;
    packet.seven = 7;
    packet.ff = 0xFF;
    packet.size = 0x28;
    packet.count = 6;
    packet.owner = *(s32 *)((u8 *)arg1 + 0x18);
    scale = ((func_150ADA68() * 5.0f) + 10.0f) * arg2;
    func_1513C650((s32)&packet, 0, 0, (s32)((u8 *)arg1 + 4),
                   *(f32 *)arg4, *(f32 *)arg1, *(f32 *)((u8 *)arg4 + 8),
                   scale, scale, arg3, arg5 == 2 ? 1 : 0, 3, 1, 0, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141F78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141F78.s")
extern s32 D_800A5200[];
extern u8 D_800CC2D0[];
s32 func_150A2AEC(s32, s32, s32 *, s32);

s32 func_151420F8(s32 arg0) {
    typedef struct { s32 words[6]; } Copy6;
    Copy6 sp18;

    sp18 = *(Copy6 *)D_800A5200;
    if (func_150A2AEC((arg0 - (s32)D_800CC2D0) / 0x32C, 6, sp18.words, arg0) == -1) {
        return 0;
    }
    return 1;
}
void func_15153F18(s16 *, void *, s32, s32, s32);
extern f32 D_800A5470;
extern f32 D_800A5474;

typedef struct Game16EE20Position {
    s32 x;
    s32 y;
    s32 z;
} Game16EE20Position;

typedef struct Game16EE20EffectPacket {
    s16 field00;
    s16 field02;
    s16 field04;
    s16 field06;
    Game16EE20Position position;
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
    s16 field34;
    s16 field36;
    s16 field38;
    s16 field3A;
    u8 field3C;
    u8 pad3D[3];
    f32 field40;
    s16 field44;
    s16 field46;
    s32 field48;
} Game16EE20EffectPacket;

void func_15142180(u8 arg0, s32 *arg1, s32 arg2, f32 arg3, f32 arg4) {
    Game16EE20EffectPacket packet;

    packet.position = *(Game16EE20Position *)arg1;
    packet.field14 = 2.5f * arg3;
    packet.field18 = 2 * arg3;
    packet.field1C = D_800A5470;
    packet.field20 = D_800A5474;
    packet.field2C = 3;
    packet.field2E = 3;
    packet.field02 = 0xFF;
    packet.field04 = -0x19;
    packet.field06 = 0xA;
    packet.field30 = 3;
    packet.field24 = 3.0f * arg4;
    packet.field28 = 3.5f * arg4;
    packet.field00 = 0;
    packet.field32 = 1;
    packet.field34 = 9;
    packet.field36 = 0xF;
    packet.field38 = 0xB4;
    packet.field3A = 0x4B;
    packet.field44 = 0xC;
    packet.field46 = 0x15;
    packet.field40 = 0.0f;
    packet.field48 = arg2;
    packet.field3C = arg0;
    func_15153F18(&packet.field00, &packet.position, 0, 0xFF, 1);
}
s32 func_151422C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return (arg3 + arg2) >> 1;
}
s32 func_151422DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return arg4;
}
s32 func_151422F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return arg4;
}
extern u8 D_800C3E90;

void func_15142314(s32 arg0, s32 arg1, f32 *arg2) {
    u8 *p;

    p = ((u8 *)arg0) + (arg1 << 6);
    if (D_800C3E90 != 0) {
        p = ((u8 *)arg0) + (arg1 << 6);
        do {
            f32 scale = 0.000015258789f;
            arg2[0] = (((f32)((*((s16 *)(p + 0x18))) << 0x10)) + ((f32)(*((s16 *)(p + 0x38))))) * scale;
            arg2[1] = (((f32)((*((s16 *)(p + 0x1A))) << 0x10)) + ((f32)(*((s16 *)(p + 0x3A))))) * scale;
            arg2[2] = (((f32)((*((s16 *)(p + 0x1C))) << 0x10)) + ((f32)(*((s16 *)(p + 0x3C))))) * scale;
        } while (0);
        return;
    }
    arg2[0] = *((f32 *)(p + 0x30));
    arg2[1] = *((f32 *)(p + 0x34));
    arg2[2] = *((f32 *)(p + 0x38));
}
extern f32 D_8009A220[];

f32 func_151423D8(u8 arg0) {
    u8 temp_t0;
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = arg0;
    if (temp_v0 & 0x40) {
        var_v1 = 0x40 - (temp_v0 & 0x3F);
    } else {
        var_v1 = temp_v0 & 0x3F;
    }
    temp_t0 = temp_v0 & 0xC0;
    if ((temp_t0 == 0) || (temp_t0 == 0xC0)) {
        return D_8009A220[var_v1];
    }
    return -D_8009A220[var_v1];
}
/* Call context: func_15083E90: unique active project prototype */
void * func_15083E90(u8);

void *func_15142444(u8 arg0, void *arg1) {
    void *temp_v0;

    if (arg0 == 0xFF) {
        if (*(s32 *)((u8 *)arg1 + 0x1D4) != 0) {
            return arg1;
        }
        return 0;
    }
    if ((arg1 != 0) && (*(s32 *)((u8 *)arg1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)arg1 + 0x3B))) {
        if (*(s32 *)((u8 *)arg1 + 0x1D4) != 0) {
            return arg1;
        }
        return 0;
    }
    temp_v0 = func_15083E90(arg0);
    if ((temp_v0 != 0) && (*(s32 *)((u8 *)temp_v0 + 0x1D4) != 0)) {
        return temp_v0;
    }
    return 0;
}
/* Call context: func_150A7790: unique active project prototype */
void func_150A7790(void *, s32);
void func_150A8050(void *, f32, f32, f32);

void func_151424F4(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11) {
    f32 mtx[4][4];

    func_150A8050(mtx, arg3, arg4, arg5);
    mtx[3][0] = arg9;
    mtx[3][1] = arg10;
    mtx[3][2] = arg11;
    mtx[0][0] *= arg6 * arg1;
    mtx[0][1] *= arg7 * arg1;
    mtx[0][2] *= arg8 * arg1;
    mtx[1][0] *= arg6 * arg2;
    mtx[1][1] *= arg7 * arg2;
    mtx[1][2] *= arg8 * arg2;
    mtx[2][0] *= arg6 * arg1;
    mtx[2][1] *= arg7 * arg1;
    mtx[2][2] *= arg8 * arg1;
    func_150A7790(mtx, arg0);
}
/* Call context: func_150A7790: unique active declaration in the allowed source */
f32 sqrtf(f32);

#pragma intrinsic(sqrtf)
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142600 CURRENT (10388) */
void func_15142600(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11) {
    f32 transform[4][4];
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp3C;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_ft0;
    f32 temp_ft0_2;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv1;

    temp_ft4 = arg9 - arg6;
    sp28 = arg6;
    temp_ft5 = arg10 - arg7;
    sp2C = arg7;
    temp_ft3 = arg11 - arg8;
    sp30 = arg8;
    sp3C = temp_ft3;
    temp_fa0 = 1.0f / sqrtf((temp_ft4 * temp_ft4) + (temp_ft5 * temp_ft5) + (temp_ft3 * temp_ft3));
    temp_fa1 = temp_ft3 * temp_fa0;
    sp44 = temp_ft4 * temp_fa0;
    sp6C = temp_ft5 * temp_fa0;
    sp70 = sp44;
    temp_ft0 = -sp44;
    sp44 = temp_ft0;
    sp68 = temp_fa1;
    temp_fa0_2 = 1.0f / sqrtf((temp_fa1 * temp_fa1) + (temp_ft0 * temp_ft0));
    temp_fv1 = temp_fa1 * temp_fa0_2;
    temp_fs0 = temp_ft0 * temp_fa0_2;
    transform[0][1] = 0.0f;
    transform[0][3] = 0.0f;
    transform[1][3] = 0.0f;
    transform[2][3] = 0.0f;
    temp_ft3_2 = sp6C * temp_fs0;
    sp50 = temp_ft3_2;
    temp_ft0_2 = (sp68 * temp_fv1) - (sp70 * temp_fs0);
    sp4C = temp_ft0_2;
    sp48 = -sp6C * temp_fv1;
    temp_fa0_3 = 1.0f / sqrtf((temp_ft3_2 * temp_ft3_2) + (sp4C * temp_ft0_2) + (sp48 * sp48));
    transform[0][0] = temp_fv1 * arg3 * arg1;
    transform[1][0] = temp_ft3_2 * temp_fa0_3 * arg3 * arg2;
    transform[3][0] = sp28;
    transform[2][0] = sp70 * arg3 * arg1;
    transform[1][1] = sp4C * temp_fa0_3 * arg4 * arg2;
    transform[3][1] = arg7;
    transform[2][1] = sp6C * arg4 * arg1;
    transform[0][2] = temp_fs0 * arg5 * arg1;
    transform[1][2] = sp48 * temp_fa0_3 * arg5 * arg2;
    transform[3][3] = 1.0f;
    transform[3][2] = arg8;
    transform[2][2] = sp68 * arg5 * arg1;
    func_150A7790(transform, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142600 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142600.s")
/* Call context: func_150A7790: unique active project prototype */
void func_150A7790(void *, s32);
void func_150A8050(void *, f32, f32, f32);

void func_15142838(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    f32 transform[4][4];

    func_150A8050(transform, arg3, arg4, arg5);
    transform[3][0] = arg6;
    transform[3][1] = arg7;
    transform[3][2] = arg8;
    transform[0][0] *= arg1;
    transform[0][1] *= arg1;
    transform[0][2] *= arg1;
    transform[1][0] *= arg2;
    transform[1][1] *= arg2;
    transform[1][2] *= arg2;
    transform[2][0] *= arg1;
    transform[2][1] *= arg1;
    transform[2][2] *= arg1;
    func_150A7790(transform, arg0);
}
/* Call context: func_150A8050: unique active project prototype */
void func_150A8050(void *, f32, f32, f32);

void func_15142914(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    func_150A8050(arg0, arg3, arg4, arg5);
    *(f32 *)((u8 *)arg0 + 0x30) = arg6;
    *(f32 *)((u8 *)arg0 + 0x34) = arg7;
    *(f32 *)((u8 *)arg0 + 0x38) = arg8;
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) * arg2);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) * arg2);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) * arg2);
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) * arg1);
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) * arg1);
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) * arg1);
}
s32 func_150ADA20(); /* extern */
extern u8 D_8008A160[];

void func_151429E0(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 *entry;

    entry = ((func_150ADA20() & 3) * 3) + (arg0 * 0xC) + D_8008A160;
    *arg1 = entry[0];
    *arg2 = entry[1];
    *arg3 = entry[2];
}
s32 func_15142A5C(void *arg0) {
    s16 *state = *(s16 **)((u8 *)arg0 + 0x2D0);

    if (state[0x1E] > 0) {
        return 1;
    }
    return 0;
}
extern f32 D_800A5624;

f32 func_15142A80(f32 arg0) {
    return (1.0f - arg0) * (arg0 - 2.0f) * arg0 * D_800A5624;
}
f32 func_15142AC0(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * (arg0 - 2.0f) * 0.5f;
}
f32 func_15142B04(f32 arg0) {
    return (2.0f - arg0) * (arg0 + 1.0f) * arg0 * 0.5f;
}
extern f32 D_800A5628;

f32 func_15142B44(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * arg0 * D_800A5628;
}
extern s32 D_800DD1FC;
extern s32 D_800DD200;

typedef struct {
    u32 w0;
    u32 w1;
} Game16EE20Gwords;

typedef union {
    Game16EE20Gwords words;
} Gfx;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define G_GEOMETRYMODE 0xd9
#define G_SETENVCOLOR 0xfb
#define G_SETPRIMCOLOR 0xfa
#define G_RDPSETOTHERMODE 0xef
#define G_RDPPIPESYNC 0xe7
#define gSPGeometryMode(pkt, c, s) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
    _g->words.w0 = _SHIFTL(G_GEOMETRYMODE, 24, 8) | _SHIFTL(~(u32)(c), 0, 24); \
    _g->words.w1 = (u32)(s); \
}
#define gSPSetGeometryMode(pkt, word) gSPGeometryMode((pkt), 0, (word))
#define gSPClearGeometryMode(pkt, word) gSPGeometryMode((pkt), (word), 0)
#define gDPNoParam(pkt, cmd) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
 \
    _g->words.w0 = _SHIFTL(cmd, 24, 8); \
    _g->words.w1 = 0; \
}
#define gDPPipeSync(pkt) gDPNoParam(pkt, G_RDPPIPESYNC)
#define gDPSetColor(pkt, c, d) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
 \
    _g->words.w0 = _SHIFTL(c, 24, 8); \
    _g->words.w1 = (u32)(d); \
}
#define DPRGBColor(pkt, cmd, r, g, b, a) \
    gDPSetColor(pkt, cmd, \
                (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | \
                 _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8)))
#define gDPSetEnvColor(pkt, r, g, b, a) \
    DPRGBColor(pkt, G_SETENVCOLOR, r, g, b, a)
#define gDPSetPrimColor(pkt, m, l, r, g, b, a) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
 \
    _g->words.w0 = (_SHIFTL(G_SETPRIMCOLOR, 24, 8) | \
                    _SHIFTL(m, 8, 8) | _SHIFTL(l, 0, 8)); \
    _g->words.w1 = (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | \
                    _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8)); \
}
#define gDPSetOtherMode(pkt, mode0, mode1) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
 \
    _g->words.w0 = _SHIFTL(G_RDPSETOTHERMODE, 24, 8) | _SHIFTL(mode0, 0, 24); \
    _g->words.w1 = (u32)(mode1); \
}

Gfx *func_15142B7C(Gfx *gdl, s32 arg1, s32 arg2) {
    extern s32 D_800DD200;
    extern s32 D_800DD1FC;

    if ((~D_800DD200) & arg2) {
        gSPClearGeometryMode(gdl++, arg2);
        D_800DD200 |= arg2;
    }
    if ((~D_800DD1FC) & arg1) {
        gSPSetGeometryMode(gdl++, arg1);
        D_800DD1FC |= arg1;
    }
    return gdl;
}
extern s16 D_800DD1C8;
extern s16 D_800DD1CA;
extern s16 D_800DD1CC;
extern s16 D_800DD1CE;

Gfx *func_15142C10(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5) {
    extern s16 D_800DD1C8;
    extern s16 D_800DD1CA;
    extern s16 D_800DD1CC;
    extern s16 D_800DD1CE;

    if ((arg1 != D_800DD1C8) || (arg2 != D_800DD1CA) || (arg3 != D_800DD1CC) || (arg4 != D_800DD1CE)) {
        if (*arg5 == 1) {
            gDPPipeSync(gdl++);
            *arg5 = 0;
        }
        gDPSetEnvColor(gdl++, arg1, arg2, arg3, arg4);
        D_800DD1C8 = arg1;
        D_800DD1CA = arg2;
        D_800DD1CC = arg3;
        D_800DD1CE = arg4;
    }
    return gdl;
}
extern s16 D_800DD1C0;
extern s16 D_800DD1C2;
extern s16 D_800DD1C4;
extern s16 D_800DD1C6;
extern s16 D_800DD204;
extern s16 D_800DD206;

Gfx *func_15142CF0(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 *arg7) {
    extern s16 D_800DD204;
    extern s16 D_800DD206;
    extern s16 D_800DD1C0;
    extern s16 D_800DD1C2;
    extern s16 D_800DD1C4;
    extern s16 D_800DD1C6;

    if ((arg1 != D_800DD204) || (arg2 != D_800DD206) || (arg3 != D_800DD1C0) || (arg4 != D_800DD1C2) || (arg5 != D_800DD1C4) || (arg6 != D_800DD1C6)) {
        if (*arg7 == 1) {
            gDPPipeSync(gdl++);
            *arg7 = 0;
        }
        gDPSetPrimColor(gdl++, arg1, arg2, arg3, arg4, arg5, arg6);
        D_800DD204 = arg1;
        D_800DD206 = arg2;
        D_800DD1C0 = arg3;
        D_800DD1C2 = arg4;
        D_800DD1C4 = arg5;
        D_800DD1C6 = arg6;
    }
    return gdl;
}
s32 func_15094FE8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 func_1514306C(s32, s32, s32, u8);               /* extern */
extern s32 D_800BE9F0;
extern s32 D_800DD1B0;
extern s32 D_800DD208;
extern s32 D_800DD20C;
extern s32 D_800DD210;
extern s32 D_800DD214;

s32 func_15142E24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *arg9, s32 arg10) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_1514306C(arg1, arg6, arg2 >> 0x10, arg7);
    if ((temp_v0 != D_800DD1B0) || (arg3 != D_800DD208) || (arg4 != D_800DD20C) || (arg5 != D_800DD210) || (arg8 != D_800DD214)) {
        if (*arg9 == 1) {
            *arg9 = 0;
        }
        if ((D_800BE9F0 == 0x18) || (D_800BE9F0 == 0x13) || (D_800BE9F0 == 6) || (D_800BE9F0 == 0x3B) || (D_800BE9F0 == 2) || (D_800BE616 != 0)) {
            arg10 = 3;
        }
        temp_v0_2 = func_15094FE8(arg0, arg1, arg2 >> 8, arg8, 0, 0, 0, arg3, arg4, arg5, arg10);
        D_800DD1B0 = temp_v0;
        D_800DD208 = arg3;
        D_800DD20C = arg4;
        D_800DD210 = arg5;
        arg0 = temp_v0_2;
        D_800DD214 = D_800DD214;
    }
    return arg0;
}
extern s32 D_800DD218;
extern s32 D_800DD21C;

Gfx *func_15142FBC(Gfx *gdl, s32 arg1, s32 arg2, u8 *arg3) {
    extern s32 D_800DD218;
    extern s32 D_800DD21C;

    if ((arg1 != D_800DD218) || (arg2 != D_800DD21C)) {
        if (*arg3 == 1) {
            gDPPipeSync(gdl++);
            *arg3 = 0;
        }
        gDPSetOtherMode(gdl++, arg1 | 0xF, arg2);
        D_800DD218 = arg1;
        D_800DD21C = arg2;
    }
    return gdl;
}
s16 func_15143044(u8 arg0, s32 arg1) {
    return (s16) (0x7FFF - arg0);
}
extern s32 D_800915B0;
extern s32 D_80091514;
extern s32 D_80091564[];
typedef struct {
    s32 *field0;
    s32 *field4;
    s32 *field8;
} Game16EE20PointerGroup;
extern Game16EE20PointerGroup D_80090B60[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514306C CURRENT (205) */
s32 func_1514306C(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 value;
    u32 address;

    switch (arg3) {
    case 1:
        value = D_800915B0;
        break;
    case 2:
        value = D_80091514;
        break;
    case 3:
        value = 0;
        break;
    case 4:
        value = D_80091564[arg1];
        break;
    case 5:
        value = arg1;
        break;
    case 6:
        address = *(u32 *)arg0;
        if (address >= 0x10000000U) {
            value = ((s32 *)address)[arg2];
        } else {
            value = address;
        }
        break;
    default:
        value = D_80090B60[arg1].field0[arg2];
        break;
    }
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514306C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514306C.s")
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_15142314(s32, s32, f32 *);
void func_151EFEB8(void *, s32);
extern s32 D_800DCA00;
extern s32 D_800DCA04;
extern f32 D_800DCA08;
extern f32 D_800DCA0C;
extern f32 D_800DCA10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143134 CURRENT (215) */
void func_15143134(f32 *arg0, f32 *arg1, s32 arg2) {
    u8 transform[0x40];

    D_800DCA00 = 1;
    if (arg0 != 0 && (arg0[0] != 0.0f || arg0[1] != 0.0f || arg0[2] != 0.0f)) {
        D_800DCA00 = 2;
        D_800DCA08 = arg0[0];
        D_800DCA0C = arg0[1];
        D_800DCA10 = arg0[2];
        if (D_800C3E90 != 0) {
            D_800DCA00 = 3;
            D_800DCA04 = arg2;
            func_151EFEB8(transform, arg2);
            func_150A7960(transform, arg0[0], arg0[1], arg0[2],
                          &arg1[0], &arg1[1], &arg1[2]);
            D_800DCA00 = 4;
        } else {
            D_800DCA00 = 5;
            D_800DCA04 = arg2;
            func_150A7960((void *)arg2, arg0[0], arg0[1], arg0[2],
                          &arg1[0], &arg1[1], &arg1[2]);
            D_800DCA00 = 6;
        }
    } else {
        D_800DCA00 = 7;
        func_15142314(arg2, 0, arg1);
        D_800DCA00 = 8;
    }
    D_800DCA00 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143134 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143134.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151432BC.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15047C00(f32);                             /* extern */

void func_151436B4(f32 arg0, f32 arg1, f32 arg2, f32 *arg3) {
    f32 c0 = func_15047C00(arg0);
    f32 s0 = func_15047D60(arg0);
    f32 c1 = func_15047C00(arg1);
    f32 s1 = func_15047D60(arg1);
    f32 t = arg2 * c1;

    arg3[0] = t * s0;
    arg3[1] = -arg2 * s1;
    arg3[2] = t * c0;
}
f32 func_15047C00(f32);                             /* extern */
f32 func_15047D60(f32);                             /* extern */

void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 sp1C;
    f32 temp_fv0;

    sp1C = func_15047C00(arg0);
    temp_fv0 = func_15047D60(arg0);
    *arg2 = arg1 * temp_fv0;
    *arg3 = arg1 * sp1C;
}
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);

void func_15143794(s16 arg0, s16 arg1, f32 arg2, void *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_fv1;
    f32 temp_ft4;
    f32 fourth;
    s32 angle0;
    s32 angle1;

    sp24 = func_151423D8(arg0);
    angle0 = arg0;
    angle0 -= 0x40;
    sp20 = func_151423D8(angle0);
    sp1C = func_151423D8(arg1);
    angle1 = arg1;
    angle1 -= 0x40;
    fourth = func_151423D8(angle1);
    temp_ft4 = -arg2 * fourth;
    temp_fv1 = arg2 * sp1C;
    *(f32 *)((u8 *)arg3 + 0) = (f32) (temp_fv1 * sp20);
    *(f32 *)((u8 *)arg3 + 4) = temp_ft4;
    *(f32 *)((u8 *)arg3 + 8) = (f32) (temp_fv1 * sp24);
}
extern void func_15143794(s16 arg0, s16 arg1, f32 arg2, void *arg3);

void func_15143834(s16 arg0, s16 arg1, f32 arg2, void *arg3) {
    func_15143794(arg0, arg1, arg2, arg3);
}
f32 func_151423D8(u8);                              /* extern */

void func_15143874(s16 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 sp1C;
    f32 cosine;
    s32 angle;

    sp1C = func_151423D8(arg0);
    angle = arg0;
    angle -= 0x40;
    cosine = func_151423D8(angle);
    *arg2 = arg1 * cosine;
    *arg3 = arg1 * sp1C;
}
extern s32 D_800D3094;
extern s32 D_800D3098;

void func_15143D18(s32 *, s32 *, s32, s32);
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151438D8 CURRENT (2428) */
s32 func_151438D8(s32 arg0, s32 arg1, u16 arg2, u8 *arg3) {
    volatile s32 sp58;
    volatile s32 sp34;
    volatile s32 sp30;
    volatile s32 sp2C;
    volatile s32 sp28;
    volatile s32 sp24;
    volatile s32 sp20;
    s32 var_a0;
    s32 var_a1;
    s32 var_t0;
    s32 var_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    var_t0 = 0;
    if (arg3 == 0) {
        return 0;
    }
    sp58 = var_t0;
    func_15143D18(&arg0, &arg1, 0, D_800D3094);
    var_a1 = arg0;
    var_t0 = sp58;
    if (var_a1 < arg1) {
        sp30 = arg2 & 0x80;
        sp34 = arg2 & 0x40;
        sp28 = arg2 & 0x200;
        sp2C = arg2 & 0x100;
        sp20 = arg2 & 0x1000;
        sp24 = arg2 & 0x400;
        do {
            var_v0 = 0;
            var_a0 = 0;
            if (arg2 & 1) {
                temp_v1 = (void *)(D_800D3098 + (var_a1 * 0x34));
                if ((*(s16 *)((u8 *)arg3 + 0) == *(s16 *)((u8 *)temp_v1 + 0)) && (*(s16 *)((u8 *)arg3 + 2) == *(s16 *)((u8 *)temp_v1 + 2)) && (*(s16 *)((u8 *)arg3 + 4) == *(s16 *)((u8 *)temp_v1 + 4))) {
                    var_v0 = 1;
                    var_a0 = 1;
                }
            } else {
                var_v0 = 1;
            }
            if (arg2 & 2) {
                temp_v1_2 = (void *)(D_800D3098 + (var_a1 * 0x34));
                if ((*(s16 *)((u8 *)arg3 + 6) == *(s16 *)((u8 *)temp_v1_2 + 6)) && (*(s16 *)((u8 *)arg3 + 8) == *(s16 *)((u8 *)temp_v1_2 + 8)) && (*(s16 *)((u8 *)arg3 + 0xA) == *(s16 *)((u8 *)temp_v1_2 + 0xA))) {
                    var_v0 = (var_v0 | 2) & 0xFFFF;
                    var_a0 = (var_a0 | 2) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 2) & 0xFFFF;
            }
            if (arg2 & 4) {
                if (*(f32 *)((u8 *)arg3 + 0xC) == *(f32 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0xC)) {
                    var_v0 = (var_v0 | 4) & 0xFFFF;
                    var_a0 = (var_a0 | 4) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 4) & 0xFFFF;
            }
            if (arg2 & 8) {
                if (*(f32 *)((u8 *)arg3 + 0x10) == *(f32 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x10)) {
                    var_v0 = (var_v0 | 8) & 0xFFFF;
                    var_a0 = (var_a0 | 8) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 8) & 0xFFFF;
            }
            if (arg2 & 0x10) {
                if (*(u8 *)((u8 *)arg3 + 0x14) == *(u8 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x14)) {
                    var_v0 = (var_v0 | 0x10) & 0xFFFF;
                    var_a0 = (var_a0 | 0x10) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x10) & 0xFFFF;
            }
            if (arg2 & 0x20) {
                if (*(u8 *)((u8 *)arg3 + 0x15) == ((s32) *(u8 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x15) >> 2)) {
                    var_v0 = (var_v0 | 0x20) & 0xFFFF;
                    var_a0 = (var_a0 | 0x20) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x20) & 0xFFFF;
            }
            if (sp34 != 0) {
                if (*(u8 *)((u8 *)arg3 + 0x16) == *(u8 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x16)) {
                    var_v0 = (var_v0 | 0x40) & 0xFFFF;
                    var_a0 = (var_a0 | 0x40) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x40) & 0xFFFF;
            }
            if (sp30 != 0) {
                if (*(u8 *)((u8 *)arg3 + 0x17) == *(u8 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x17)) {
                    var_v0 = (var_v0 | 0x80) & 0xFFFF;
                    var_a0 = (var_a0 | 0x80) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x80) & 0xFFFF;
            }
            if (sp2C != 0) {
                if (*(s32 *)((u8 *)arg3 + 0x18) == *(s32 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x18)) {
                    var_v0 = (var_v0 | 0x100) & 0xFFFF;
                    var_a0 = (var_a0 | 0x100) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x100) & 0xFFFF;
            }
            if (sp28 != 0) {
                if (*(s32 *)((u8 *)arg3 + 0x1C) == *(s32 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x1C)) {
                    var_v0 = (var_v0 | 0x200) & 0xFFFF;
                    var_a0 = (var_a0 | 0x200) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x200) & 0xFFFF;
            }
            if (sp24 != 0) {
                if (*(s32 *)((u8 *)arg3 + 0x20) == *(s32 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x20)) {
                    var_v0 = (var_v0 | 0x400) & 0xFFFF;
                    var_a0 = (var_a0 | 0x400) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x400) & 0xFFFF;
            }
            if (sp20 != 0) {
                if (var_v0 == 0x7FF) {
                    var_t0 = (var_a1 * 0x34) + D_800D3098;
                }
            } else if (var_a0 != 0) {
                var_t0 = (var_a1 * 0x34) + D_800D3098;
            }
            var_a1 += 1;
        } while (var_a1 != arg1);
    }
    return var_t0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151438D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151438D8.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143D18 CURRENT (300) */
void func_15143D18(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a2;

    var_a2 = arg2;
    temp_v1 = var_a2 ^ arg3;
    if (arg3 < var_a2) {
        temp_a1 = arg3 ^ temp_v1;
        arg3 = temp_a1;
        var_a2 = temp_a1 ^ temp_v1;
    }
    temp_v1_2 = *arg1;
    var_a1 = *arg0;
    temp_v0 = var_a1 ^ temp_v1_2;
    if (temp_v1_2 < var_a1) {
        *arg0 = temp_v0;
        temp_a0 = *arg1 ^ temp_v0;
        *arg1 = temp_a0;
        var_a1 = *arg0 ^ temp_a0;
        *arg0 = var_a1;
    }
    if (var_a1 < var_a2) {
        *arg0 = var_a2;
    }
    if (arg3 < *arg1) {
        *arg1 = arg3;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143D18 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143D18.s")
s32 func_15143DA8(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_v0;

    if (arg2 < arg1) {
        s32 temp_v1 = arg1 ^ arg2;
        temp_a3 = arg2 ^ temp_v1;
        arg2 = temp_a3;
        arg1 = temp_v1 ^ temp_a3;
    }
    temp_v0 = *arg0;
    if (temp_v0 < arg1) {
        *arg0 = arg1;
        return 1;
    }
    if (arg2 < temp_v0) {
        *arg0 = arg2;
        return 2;
    }
    return 0;
}
s32 func_15143E08(u16 *arg0) {
    return (((s32)arg0[0x3D] >> 8) + 0x40) & 0xFF;
}
s16 func_15143E24(void *arg0) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x31C);
    if (temp_v1 != 0) {
        return (s16) ((s32) (*(u16 *)((u8 *)arg0 + 0x7A) - *(s16 *)((u8 *)temp_v1 + 0x12)) >> 8);
    }
    return (s16) ((s32) *(u16 *)((u8 *)arg0 + 0x7A) >> 8);
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_15143E64(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 4);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 8);
    return sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
}
typedef struct Game143E94Packet {
    s8 type;
    u8 pad1;
    s16 lifetime;
    s8 size;
    s8 one;
    s8 negative;
} Game143E94Packet;

typedef struct Game143E94Locals {
    Game143E94Packet packet;
    u8 pad7[7];
    volatile u8 success;
} Game143E94Locals;

s32 func_150A29C8(s32, s32);
void func_1512D748(void *, s32, s32);
void func_151D8868(Game143E94Packet *, s32, s32, s32);

extern s32 D_800BE9E8;
extern s32 D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143E94 CURRENT (933) */
u8 func_15143E94(s32 arg0, s32 arg1) {
    Game143E94Locals locals;
    s8 limit = D_80082FA0 + 1;
    s8 index = 0;
    s32 found = 0;
    s32 effect_found;

    locals.success = 0;
    if (limit > 0) {
        do {
            if (D_800CC2D0[index * 0x32C + 0x1CA] != 0) {
                found = 1;
            } else {
                index++;
            }
            if (found != 0) {
                break;
            }
        } while (index < limit);
    }
    if (found != 0) {
        index = 0;
        effect_found = 0;
        if (limit > 0) {
            do {
                if (func_150A29C8(index, arg1) == 0) {
                    effect_found = 1;
                } else {
                    index++;
                }
                if (effect_found != 0) {
                    break;
                }
            } while (index < limit);
        }
        if (effect_found != 0) {
            func_1512D748((u8 *)D_800DBFF0 + D_800BE9E8 * 0x9A0, arg0, 1);
            locals.packet.type = 1;
            locals.packet.lifetime = (func_150ADA20() & 0xF) + 0x14;
            locals.packet.size = (func_150ADA20() & 3) + 4;
            locals.packet.negative = -1;
            locals.packet.one = 1;
            func_151D8868(&locals.packet, 0, 0xFF, 0);
            locals.success = 1;
        }
    }
    return locals.success;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143E94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143E94.s")
extern u8 D_80090B64[];
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514401C CURRENT (320) */
s32 func_1514401C(u8 arg0, s32 *arg1, s32 *arg2, u8 arg3) {
    s32 boundary;
    s32 value;
    s32 overflow_value;
    s32 underflow_value;
    s32 current;
    s32 result = 0;

    boundary = (D_80090B64[arg0 * 0xC] << 16) - 1;
    value = *arg2 + (D_800BE9E4 * *arg1);
    *arg2 = value;
    current = value;
    if (boundary < value) {
        if (arg3 & 1) {
            result = 1;
        } else if (arg3 & 2) {
            *arg1 = 0;
            *arg2 = boundary;
        } else if (arg3 & 4) {
            *arg2 = boundary - (current % boundary);
            *arg1 = -*arg1;
        } else {
            do {
                overflow_value = current - boundary;
                *arg2 = overflow_value;
                current = overflow_value;
            } while (boundary < overflow_value);
        }
    } else if (current < 0 && !(arg3 & 8)) {
        if (arg3 & 0x10) {
            *arg1 = 0;
            *arg2 = 0;
        } else if (arg3 & 4) {
            *arg2 = -current % boundary;
            *arg1 = -*arg1;
        } else {
            do {
                underflow_value = current + boundary;
                *arg2 = underflow_value;
                current = underflow_value;
            } while (underflow_value < 0);
        }
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514401C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514401C.s")
void func_151441A4(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12, u8 arg13) {
    s16 temp_v0;
    s16 temp_v0_2;

    switch (arg13) {
    case 2:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) arg10;
        *arg3 = (s16) arg11;
        return;
    case 0:
        *arg3 = 0;
        temp_v0 = *arg3;
        *arg2 = temp_v0;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        return;
    case 1:
        *arg2 = 0;
        temp_v0_2 = *arg2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        *arg3 = (s16) arg11;
        return;
    case 3:
        *arg0 = (s16) ((s32) (arg4 * arg12) >> 8);
        *arg1 = (s16) ((s32) (arg5 * arg12) >> 8);
        *arg2 = (s16) ((s32) (arg6 * arg12) >> 8);
        *arg3 = 0;
        return;
    case 4:
        *arg0 = (s16) ((s32) (arg4 * arg12) >> 8);
        *arg1 = (s16) ((s32) (arg5 * arg12) >> 8);
        *arg2 = (s16) ((s32) (arg6 * arg12) >> 8);
        *arg3 = 0;
        return;
    default:
        *arg0 = (s16) ((s32) (arg4 * arg12) >> 8);
        *arg1 = (s16) ((s32) (arg5 * arg12) >> 8);
        *arg2 = (s16) ((s32) (arg6 * arg12) >> 8);
        *arg3 = 0;
        return;
    }
}
void func_151442FC(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12, u8 arg13) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;

    switch (arg13) {
    case 2:
    case 3:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = (s16) arg7;
        return;
    case 13:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = 0;
        return;
    case 0:
        *arg3 = 0;
        temp_v0 = *arg3;
        *arg2 = temp_v0;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        return;
    case 1:
        *arg2 = (s16) arg12;
        *arg1 = (s16) arg12;
        *arg0 = (s16) arg12;
        *arg3 = 0;
        return;
    case 7:
    case 12:
        *arg2 = 0;
        temp_v0_2 = *arg2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        *arg3 = (s16) arg11;
        return;
    case 8:
        *arg2 = 0;
        temp_v0_3 = *arg2;
        *arg1 = temp_v0_3;
        *arg0 = temp_v0_3;
        *arg3 = (s16) arg7;
        return;
    case 4:
        *arg2 = (s16) arg12;
        *arg1 = (s16) arg12;
        *arg0 = (s16) arg12;
        *arg3 = (s16) ((s32) (arg7 * arg11) >> 8);
        return;
    case 5:
        *arg2 = (s16) arg12;
        *arg1 = (s16) arg12;
        *arg0 = (s16) arg12;
        *arg3 = (s16) ((s32) (arg7 * arg11) >> 8);
        return;
    case 6:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = (s16) arg11;
        return;
    case 10:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) arg10;
        *arg3 = (s16) arg11;
        return;
    case 11:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) arg10;
        *arg3 = (s16) arg7;
        return;
    case 9:
        *arg2 = (s16) arg12;
        *arg1 = (s16) arg12;
        *arg0 = (s16) arg12;
        *arg3 = (s16) arg11;
        return;
    default:
        *arg2 = (s16) arg12;
        *arg1 = (s16) arg12;
        *arg0 = (s16) arg12;
        *arg3 = (s16) ((s32) (arg7 * arg11) >> 8);
        return;
    }
}
s32 func_151444DC(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 < arg0) {
        s32 delta = (arg1 - arg2) + 1;
        do {
            arg0 -= delta;
        } while (arg1 < arg0);
    }
    if (arg0 < arg2) {
        s32 delta = (arg1 - arg2) + 1;
        do {
            arg0 += delta;
        } while (arg0 < arg2);
    }
    return arg0;
}
f32 func_15144528(f32 arg0, f32 arg1, f32 arg2) {
    if (arg1 < arg0) {
        do {
            arg0 -= arg1 - arg2;
        } while (arg1 < arg0);
    }
    if (arg0 < arg2) {
        do {
            arg0 += arg1 - arg2;
        } while (arg0 < arg2);
    }
    return arg0;
}
extern f32 D_800A5694;

f32 func_15144598(void *arg0) {
    f32 var_fv1;
    s16 temp_v0;
    s32 temp_t6;

    temp_t6 = *(u8 *)((u8 *)arg0 + 0x15) & 3;
    switch (temp_t6) {                              /* irregular */
    default:
        var_fv1 = 1.0f;
        break;
    case 2:
        var_fv1 = (f32) (*(s16 *)((u8 *)arg0 + 0xA) * *(s16 *)((u8 *)arg0 + 6)) * 4.0f;
        break;
    case 0:
    case 1:
        temp_v0 = *(s16 *)((u8 *)arg0 + 6);
        var_fv1 = (f32) (temp_v0 * temp_v0) * D_800A5694;
        break;
    }
    return var_fv1;
}
extern f32 D_800A5698;
extern f32 D_800A569C;

f32 func_1514462C(s32 arg0) {
    typedef struct {
        u8 pad0[6];
        s16 unk6;
        s16 unk8;
        s16 unkA;
        u8 padC[9];
        u8 unk15;
    } Local;
    extern f32 D_800A5698;
    extern f32 D_800A569C;
    Local *a = (Local *)arg0;
    s16 v0;
    f32 f0;
    f32 f2;

    switch (a->unk15 & 3) {
    case 2:
        f2 = a->unk6 * a->unk8 * a->unkA;
        break;
    case 0:
        v0 = a->unk6;
        f2 = (v0 * v0) * D_800A5698 * a->unk8;
        break;
    case 1:
        f0 = a->unk6;
        f2 = ((f0 * D_800A569C) * f0) * f0;
        break;
    default:
        f2 = 1.0f;
        break;
    }
    return f2;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514470C.s")
f32 func_15144A74(void *arg0, void *arg1) {
    return *(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 8) + (*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 4) + *(f32 *)((u8 *)arg1 + 0) * *(f32 *)((u8 *)arg0 + 0));
}
extern s32 D_800DBFF0;

f32 func_15144AA8(s32 arg0) {
    f32 var_fv1;

    var_fv1 = *(f32 *)((u8 *)D_800DBFF0 + (arg0 * 0x9A0) + 0x380);
    if (var_fv1 > 360.0f) {
        do {
            var_fv1 -= 360.0f;
        } while (var_fv1 > 360.0f);
    }
    if (var_fv1 < 0.0f) {
        do {
            var_fv1 += 360.0f;
        } while (var_fv1 < 0.0f);
    }
    return var_fv1;
}

s32 func_15144B34(s32 arg0) {
    return (arg0 * 0x9A0) + D_800DBFF0 + 0x2F8;
}

f32 func_15144B68(f32 arg0) {
    f32 hi = D_800A56A4;
    {
        f32 x = arg0;
        if (hi < arg0) {
            do {
                x -= hi;
            } while (hi < x);
        }
        if (x < 0.0f) {
            do {
                x += hi;
            } while (x < 0.0f);
        }
        return x;
    }
}
f32 func_15144BC8(f32 arg0) {
    f32 var_fv1;

    var_fv1 = arg0;
    if (arg0 > 360.0f) {
        do {
            var_fv1 -= 360.0f;
        } while (var_fv1 > 360.0f);
    }
    if (var_fv1 < 0.0f) {
        do {
            var_fv1 += 360.0f;
        } while (var_fv1 < 0.0f);
    }
    return var_fv1;
}
s16 func_15144C2C(s16 arg0) {
    s16 var_v1;

    var_v1 = arg0;
    if (arg0 >= 0x100) {
        do {
            var_v1 -= 0xFF;
        } while (var_v1 >= 0x100);
    }
    if (var_v1 < 0) {
        do {
            var_v1 += 0xFF;
        } while (var_v1 < 0);
    }
    return var_v1;
}
extern f32 D_800A56A8;
extern f32 D_800A56AC;
f32 func_15144B68(f32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)

f32 func_15144C8C(f32 arg0, f32 arg1) {
    f32 var_fv1;

    arg0 = func_15144B68(arg0);
    {
        f32 temp_fv0 = fabsf(arg0 - func_15144B68(arg1));
    var_fv1 = temp_fv0;
    if (D_800A56A8 < temp_fv0) {
        var_fv1 = D_800A56AC - temp_fv0;
    }
    return var_fv1;
    }
}
void func_150A7A00(void *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
extern f32 D_800A56B0;
extern f32 D_800D9B20;
extern u8 *D_800BE628;
extern u8 D_800D9D10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144CEC CURRENT (3547) */
s32 func_15144CEC(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3,
                  f32 *arg4, u8 arg5) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 *var_t0;
    f32 temp_fv0;
    f32 vertical_product;
    s32 temp_t9;
    u8 *temp_v1;

    if (arg2 == 0) {
        arg2 = &sp44;
    }
    if (arg3 == 0) {
        arg3 = &sp40;
    }
    var_t0 = arg4;
    if (var_t0 == 0) {
        var_t0 = &sp3C;
    }
    func_150A7A00(&D_800D9D10[arg5 << 6], arg0[0], arg0[1], arg0[2],
                   arg1, arg1 + 1, arg2, arg3);
    temp_fv0 = *arg3;
    if ((D_800A56B0 <= temp_fv0) || (temp_fv0 <= D_800D9B20)) {
        return 0;
    }
    if (temp_fv0 != 0.0f) {
        *var_t0 = 1.0f / temp_fv0;
        temp_t9 = arg5 * 0x180;
        temp_v1 = D_800BE628 + temp_t9;
        vertical_product = arg1[1] * (*(f32 *)(temp_v1 + 0x10) + 5.0f);
        arg1[0] = (*var_t0 * (arg1[0] * (*(f32 *)(temp_v1 + 0xC) + 5.0f))) +
                  *(f32 *)(temp_v1 + 0x34);
        arg1[1] = *(f32 *)(D_800BE628 + temp_t9 + 0x38) -
                  (*var_t0 * vertical_product);
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144CEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144CEC.s")
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game16EE20Vector3;

void func_151450B4(void *, void *, void *);
void *memcpy(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144E80 CURRENT (1615) */
s32 func_15144E80(void *arg0, void *arg1, void *arg2, void *arg3) {
    typedef struct {
        f32 x;
        f32 y;
        f32 z;
    } TriangleVector;
    TriangleVector vertices[3];
    TriangleVector normal;
    TriangleVector first_edge;
    TriangleVector second_edge;

    if (arg3 == 0) {
        arg3 = &normal;
    }
    vertices[0].x = (f32)((s16 *)arg0)[0];
    vertices[0].y = (f32)((s16 *)arg0)[1];
    vertices[0].z = (f32)((s16 *)arg0)[2];
    vertices[1].x = (f32)((s16 *)arg0)[3];
    vertices[1].y = (f32)((s16 *)arg0)[4];
    vertices[1].z = (f32)((s16 *)arg0)[5];
    vertices[2].x = (f32)((s16 *)arg0)[6];
    vertices[2].y = (f32)((s16 *)arg0)[7];
    vertices[2].z = (f32)((s16 *)arg0)[8];
    if ((vertices[0].x == vertices[1].x) &&
        (vertices[0].y == vertices[1].y) &&
        (vertices[0].z == vertices[1].z)) {
        return 0;
    }
    if ((vertices[0].x == vertices[2].x) &&
        (vertices[0].y == vertices[2].y) &&
        (vertices[0].z == vertices[2].z)) {
        return 0;
    }
    if ((vertices[1].x == vertices[2].x) &&
        (vertices[1].y == vertices[2].y) &&
        (vertices[1].z == vertices[2].z)) {
        return 0;
    }
    first_edge.x = vertices[0].x - vertices[1].x;
    first_edge.y = vertices[0].y - vertices[1].y;
    first_edge.z = vertices[0].z - vertices[1].z;
    second_edge.x = vertices[2].x - vertices[1].x;
    second_edge.y = vertices[2].y - vertices[1].y;
    second_edge.z = vertices[2].z - vertices[1].z;
    func_151450B4(&first_edge, &second_edge, arg3);
    func_151450B4(&first_edge, arg3, arg1);
    memcpy(arg2, &first_edge, sizeof(first_edge));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144E80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144E80.s")
void func_151450B4(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) ((*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)arg1 + 4) * *(f32 *)((u8 *)arg0 + 8)));
    *(f32 *)((u8 *)arg2 + 4) = (f32) ((*(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)arg1 + 8) * *(f32 *)((u8 *)arg0 + 0)));
    *(f32 *)((u8 *)arg2 + 8) = (f32) ((*(f32 *)((u8 *)arg0 + 0) * *(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)arg1 + 0) * *(f32 *)((u8 *)arg0 + 4)));
}
s32 func_15145128(Game16EE20Vector3 *arg0, Game16EE20Vector3 *arg1,
    f32 *arg2, f32 *arg3) {
    f32 magnitude_squared;
    f32 inverse;

    if (arg3 == 0) {
        arg3 = &inverse;
    }
    magnitude_squared = (arg0->x * arg0->x) + (arg0->y * arg0->y) +
                        (arg0->z * arg0->z);
    if (magnitude_squared == 0.0f) {
        return 0;
    }
    if (arg2 != 0) {
        *arg2 = sqrtf(magnitude_squared);
        *arg3 = 1.0f / *arg2;
    } else {
        *arg3 = 1.0f / sqrtf(magnitude_squared);
    }
    arg1->x = *arg3 * arg0->x;
    arg1->y = *arg3 * arg0->y;
    arg1->z = *arg3 * arg0->z;
    return 1;
}
s32 func_151452C4(void *, void *, s32, f32, s32, s32, f32 *, f32 *);

s32 func_151451F0(void *arg0, void *arg1, s32 arg2, f32 arg3, f32 arg4,
                  s32 arg5, s32 arg6, f32 *arg7, f32 *arg8) {
    f32 value;

    if (func_151452C4(arg0, arg1, arg2, arg3, arg5, arg6, arg7, arg8) != 0) {
        value = *arg7;
        if ((value < 0.0f) && (*arg8 < 0.0f)) {
            return 0;
        }
        if ((value >= 0.0f) && (*arg8 < 0.0f)) {
            return 1;
        }
        if (value < arg4) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
f32 func_15144A74(void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151452C4 CURRENT (2576) */
s32 func_151452C4(void *arg0, void *arg1, s32 arg2, f32 arg3,
                  s32 arg4, s32 arg5, f32 *arg6, f32 *arg7) {
    Game16EE20Vector3 direction;
    Game16EE20Vector3 origin;
    Game16EE20Vector3 delta;
    f32 perpendicular;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 radiusSquared;
    f32 projection;
    f32 discriminant;
    f32 root;
    f32 nearDistance;
    f32 farDistance;
    s32 result;

    dx = ((Game16EE20Vector3 *)arg2)->x - ((Game16EE20Vector3 *)arg0)->x;
    dy = ((Game16EE20Vector3 *)arg2)->y - ((Game16EE20Vector3 *)arg0)->y;
    dz = ((Game16EE20Vector3 *)arg2)->z - ((Game16EE20Vector3 *)arg0)->z;
    direction = *(Game16EE20Vector3 *)arg1;
    origin = *(Game16EE20Vector3 *)arg0;
    radiusSquared = arg3 * arg3;
    projection = dx * direction.x + dy * direction.y + dz * direction.z;
    discriminant = dx * dx + dy * dy + dz * dz - projection * projection;
    perpendicular = discriminant;
    if (radiusSquared < discriminant) return 0;
    root = sqrtf(radiusSquared - perpendicular);
    if (projection < root) root = -root;
    nearDistance = projection - root;
    farDistance = projection + root;
    ((Game16EE20Vector3 *)arg4)->x = nearDistance * direction.x + origin.x;
    ((Game16EE20Vector3 *)arg4)->y = nearDistance * direction.y + origin.y;
    ((Game16EE20Vector3 *)arg4)->z = nearDistance * direction.z + origin.z;
    *arg6 = nearDistance;
    ((Game16EE20Vector3 *)arg5)->x = farDistance * direction.x + origin.x;
    ((Game16EE20Vector3 *)arg5)->y = farDistance * direction.y + origin.y;
    ((Game16EE20Vector3 *)arg5)->z = farDistance * direction.z + origin.z;
    *arg7 = farDistance;
    delta.x = ((Game16EE20Vector3 *)arg4)->x - ((Game16EE20Vector3 *)arg0)->x;
    delta.y = ((Game16EE20Vector3 *)arg4)->y - ((Game16EE20Vector3 *)arg0)->y;
    delta.z = ((Game16EE20Vector3 *)arg4)->z - ((Game16EE20Vector3 *)arg0)->z;
    discriminant = func_15144A74(&delta, arg1);
    result = 1;
    if (discriminant < 0.0f) result = 0;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151452C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151452C4.s")

s32 func_151454BC(u8 arg0, f32 arg1, void *arg2) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    void *temp_v0;

    temp_v0 = func_15144B34((s32) arg0);
    temp_fv0 = *(f32 *)((u8 *)arg2 + 0) - *(f32 *)((u8 *)temp_v0 + 0);
    temp_fv1 = *(f32 *)((u8 *)arg2 + 4) - *(f32 *)((u8 *)temp_v0 + 4);
    temp_fa0 = *(f32 *)((u8 *)arg2 + 8) - *(f32 *)((u8 *)temp_v0 + 8);
    if ((arg1 * arg1) < ((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0))) {
        return 0;
    }
    return 1;
}
s32 func_1514563C(f32 *, f32 *, f32 *, f32 *, f32 *);

void func_15145548(void *arg0, void *arg1, void *arg2, void *arg3, f32 *arg4) {
    typedef struct { f32 values[3]; } Copy3;
    f32 sp24;
    f32 temp_fv0;

    if (arg4 == 0) {
        arg4 = &sp24;
    }
    if (func_1514563C(arg0, arg1, arg2, arg3, arg4) != 0) {
        temp_fv0 = *arg4;
        if (temp_fv0 < 0.0f) {
            *(Copy3 *)arg3 = *(Copy3 *)arg0;
        } else if (temp_fv0 > 1.0f) {
            *(f32 *)((u8 *)arg3 + 0) = (f32) (*(f32 *)((u8 *)arg1 + 0) + *(f32 *)((u8 *)arg0 + 0));
            *(f32 *)((u8 *)arg3 + 4) = (f32) (*(f32 *)((u8 *)arg1 + 4) + *(f32 *)((u8 *)arg0 + 4));
            *(f32 *)((u8 *)arg3 + 8) = (f32) (*(f32 *)((u8 *)arg1 + 8) + *(f32 *)((u8 *)arg0 + 8));
        }
    } else {
        *(Copy3 *)arg3 = *(Copy3 *)arg0;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514563C CURRENT (1600) */
s32 func_1514563C(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3,
                  f32 *arg4) {
    f32 sp10;
    f32 sp0;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft1;
    f32 temp_fv0;
    f32 temp_fv1;

    if (arg4 == 0) {
        arg4 = &sp10;
    }
    temp_fv1 = arg1[0];
    temp_fa0 = arg1[1];
    temp_fa1 = arg1[2];
    temp_fv0 = (temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) +
               (temp_fa1 * temp_fa1);
    if (temp_fv0 == 0.0f) {
        return 0;
    }
    temp_ft1 = (((temp_fv1 * arg2[0]) + (temp_fa0 * arg2[1]) +
                 (temp_fa1 * arg2[2])) -
                ((temp_fv1 * arg0[0]) + (temp_fa0 * arg0[1]) +
                 (temp_fa1 * arg0[2]))) / temp_fv0;
    sp0 = temp_ft1;
    *arg4 = temp_ft1;
    arg3[0] = (temp_ft1 * arg1[0]) + arg0[0];
    arg3[1] = (*arg4 * arg1[1]) + arg0[1];
    arg3[2] = (*arg4 * arg1[2]) + arg0[2];
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514563C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514563C.s")
typedef struct {
    u8 pad0[0x12];
    s16 rotation;
    u8 pad14[0x69];
    u8 active;
    u8 pad7E[2];
    s16 yaw;
    s16 pitch;
} Game145740Node;

typedef struct {
    u8 pad0[4];
    u8 kind;
    u8 pad5[0x75];
    u16 yaw;
    u8 pad7C[0x155];
    s8 pitch;
    u8 pad1D2[0x14A];
    Game145740Node *node;
} Game145740Actor;

void func_1505A184(u16, f32, f32, f32 *, f32 *, f32 *);
extern f32 D_800A56B4;
extern f32 D_800A56B8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145740 CURRENT (1849) */
void func_15145740(Game145740Actor *arg0, Game16EE20Vector3 *arg1,
                   Game16EE20Vector3 *arg2, Game16EE20Vector3 *arg3, f32 arg4) {
    s16 yaw;
    f32 pitch;
    volatile f32 shiftedPitch;
    volatile f32 radius;
    f32 yawRadians;
    f32 pitchRadians;
    s16 pitchUnits;
    Game145740Node *node;

    pitchUnits = arg0->kind;
    if (pitchUnits == 0x96 && (node = arg0->node)->active != 0) {
        yaw = arg0->yaw + node->yaw;
    } else {
        node = arg0->node;
        if (node != 0) {
            yaw = arg0->yaw - node->rotation;
        } else {
            yaw = arg0->yaw;
        }
    }
    if (pitchUnits == 0x96 && node->active != 0) {
        pitchUnits = node->pitch + 0x400;
    } else {
        pitchUnits = arg0->pitch * 0xC8;
    }
    *(volatile f32 *)&pitch = (f32)pitchUnits * 0.0054931640625f;
    pitchRadians = pitch * D_800A56B4;
    func_1505A184((u16)yaw, 2000.0f, pitch, &arg1->x, &arg1->z, &arg1->y);
    if (arg2 != 0) {
        arg2->y = func_15047C00(pitchRadians) * 1000.0f;
        radius = func_15047D60(pitchRadians) * 1000.0f;
        yawRadians = (f32)yaw * D_800A56B8;
        arg2->x = func_15047C00(yawRadians) * radius;
        arg2->z = func_15047D60(yawRadians) * -radius;
        if (arg3 != 0) {
            shiftedPitch = pitchRadians + arg4;
            arg3->y = func_15047C00(shiftedPitch) * 1000.0f;
            radius = func_15047D60(shiftedPitch) * 1000.0f;
            arg3->x = func_15047C00(yawRadians) * radius;
            arg3->z = func_15047D60(yawRadians) * -radius;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145740 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145740.s")

/* Call context: func_150484A0: unique active project prototype */
f32 func_150484A0(f32, f32);
extern f32 D_800A56BC;
extern f32 D_800A56C0;

void func_15145974(void *arg0, f32 *arg1, f32 *arg2) {
    f32 temp_ft4;
    f32 temp_fv1;

    *arg1 = func_150484A0(*(f32 *)((u8 *)arg0 + 0), *(f32 *)((u8 *)arg0 + 8)) * D_800A56BC;
    if (arg2 != 0) {
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
        temp_ft4 = *(f32 *)((u8 *)arg0 + 8);
        *arg2 = (func_150484A0(sqrtf((temp_fv1 * temp_fv1) + (temp_ft4 * temp_ft4)), *(f32 *)((u8 *)arg0 + 4)) * D_800A56C0) - 90.0f;
    }
}
extern f32 D_800A548C[];

f32 func_15145A0C(f32 arg0, f32 arg1, f32 arg2) {
    return D_800A548C[(s32) (arg0 * arg2 * 100.0f)] * arg1;
}
/* Call context: func_15053694: unique active project prototype */
void func_15053694(u8 *);

void func_15145A50(u8 *arg0) {
    s32 temp_v0;
    void *temp_v0_2;

    *(s8 *)((u8 *)arg0 + 5) = 3;
    if (D_800BE9F0 != 0x33) {
        if ((D_800BE616 != 0) || (temp_v0 = *(s32 *)((u8 *)arg0 + 0), (temp_v0 == 5)) || (temp_v0 == 1) || (temp_v0 == 0x15)) {
            temp_v0_2 = *(void **)((u8 *)arg0 + 0x31C);
            *(s32 *)((u8 *)arg0 + 0) = 5;
            if (temp_v0_2 != 0) {
                *(s8 *)((u8 *)temp_v0_2 + 0x78) = 0;
            }
        } else {
            func_15053694(arg0);
        }
    }
}
typedef struct Game145AD8Locals {
    f32 sp38;
    f32 sp3C;
    f32 sp40;
    f32 sp44;
    f32 sp48;
    f32 sp4C;
    Game16EE20Vector3 third;
    Game16EE20Vector3 second;
    Game16EE20Vector3 first;
    f32 sp74;
    f32 sp78;
} Game145AD8Locals;

void func_1515C1A0(void *, void *, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145AD8 CURRENT (787) */
s32 func_15145AD8(Game16EE20Vector3 *arg0, Game16EE20Vector3 *arg1,
                   u8 *arg2, f32 *arg3, f32 *arg4, f32 *arg5,
                   f32 *arg6, Game16EE20Vector3 *arg7) {
    Game16EE20Vector3 sp7C;
    f32 sp78;
    f32 sp74;
    Game16EE20Vector3 first;
    Game16EE20Vector3 second;
    Game16EE20Vector3 thirdVector;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 scale;
    f32 sp3C;
    f32 sp38;

    if (arg5 != 0) {
        arg5 = &sp78;
    }
    if (arg6 != 0) {
        arg6 = &sp74;
    }
    if (arg7 != 0) {
        arg7 = &sp7C;
    }
    func_1515C1A0(arg2, arg7, arg5, arg6);
    if (*arg6 == 0.0f) {
        return 0;
    }
    if (*arg5 == 0.0f) {
        return 0;
    }
    scale = *(f32 *)(arg2 + 0xDC);
    sp3C = *(f32 *)(arg2 + 0xE0);
    first.x = arg0->x;
    first.y = arg0->y * scale;
    first.z = arg0->z;
    second.x = arg1->x;
    second.y = arg1->y * scale;
    second.z = arg1->z;
    if (func_15145128(&second, &second,
                      &sp4C, &sp38) == 0) {
        return 0;
    }
    thirdVector.x = arg7->x;
    thirdVector.y = arg7->y * scale;
    thirdVector.z = arg7->z;
    if (func_151451F0(&first, &second, (s32)&thirdVector,
                      *arg5, sp4C, (s32)arg3, (s32)arg4,
                      &sp48, &sp44) == 0) {
        return 0;
    }
    arg3[1] *= sp3C;
    arg4[1] *= sp3C;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145AD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145AD8.s")
extern s32 D_800DBEF4;

s32 func_15145C90(s32 arg0) {
    if (arg0 < 0) {
        return 1;
    }
    return ((((u8 (*)[0xA0])D_800DBEF4)[arg0][0x6F] & 0x80) == 0x80) & 0xFF;
}
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);

typedef struct Game16EE20Transform {
    f32 values[12];
} Game16EE20Transform;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145CD0 CURRENT (1026) */
void func_15145CD0(u8 *arg0, f32 **arg1, f32 **arg2, s32 arg3) {
    f32 transform[4][4];
    f32 **var_s2;
    f32 *temp_v1;
    f32 **var_s1;
    f32 *temp_v0;

    func_150A8050(transform, *(f32 *)(arg0 + 0), *(s32 *)(arg0 + 4),
                   *(f32 *)(arg0 + 8));
    var_s2 = arg2;
    transform[3][0] = (f32)*(s16 *)(arg0 + 0x10);
    transform[3][1] = (f32)*(s16 *)(arg0 + 0x12);
    transform[3][2] = (f32)*(s16 *)(arg0 + 0x14);
    var_s1 = arg1;
    if (arg3 > 0) {
        do {
            temp_v0 = *var_s1;
            temp_v1 = *var_s2;
            func_150A7960(transform, temp_v0[0], temp_v0[1], temp_v0[2],
                           temp_v1, temp_v1 + 1, temp_v1 + 2);
            arg3 -= 1;
            var_s1 += 1;
            var_s2 += 1;
        } while (arg3 > 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145CD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145CD0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145DB4 CURRENT (1259) */
void func_15145DB4(u8 *arg0, u8 *arg1, f32 *arg2, register s32 arg3) {
    struct {
        u32 pad;
        Game16EE20Transform transform;
        volatile f32 x;
        volatile f32 y;
        volatile f32 z;
    } locals;
    f32 *out_x;
    f32 *out_y;
    f32 *out_z;
    s32 count;
    u8 *input;

    count = arg3;
    func_150A8050(&locals.transform, *(f32 *)(arg0 + 0), *(s32 *)(arg0 + 4),
                   *(f32 *)(arg0 + 8));
    out_x = arg2;
    out_y = out_x + 1;
    out_z = out_x + 2;
    locals.x = (f32)*(s16 *)(arg0 + 0x10);
    locals.y = (f32)*(s16 *)(arg0 + 0x12);
    locals.z = (f32)*(s16 *)(arg0 + 0x14);
    if (count > 0) {
        input = arg1;
        do {
            func_150A7960(&locals.transform, *(f32 *)(input + 0),
                           *(f32 *)(input + 4), *(f32 *)(input + 8),
                           out_x, out_y, out_z);
            count--;
            input += 0xC;
            out_x += 3;
            out_y += 3;
            out_z += 3;
        } while (count > 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145DB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145DB4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145EA4 CURRENT (353) */
void func_15145EA4(f32 **arg0, f32 **arg1, s32 arg2, s32 arg3) {
    f32 x;
    f32 transform[4][4];
    f32 **outputs;
    f32 *output;
    register s32 count;
    f32 **inputs;
    f32 *input;

    count = arg3;
    if (D_800C3E90 != 0) {
        func_151EFEB8(transform, arg2);
        inputs = arg0;
        if (count > 0) {
            outputs = arg1;
            do {
                input = *inputs;
                if (input != 0 && ((0.0f != (x = input[0])) || input[1] != 0.0f || input[2] != 0.0f)) {
                    output = *outputs;
                    func_150A7960(transform, x, input[1], input[2], output, output + 1, output + 2);
                } else {
                    func_15142314(arg2, 0, *outputs);
                }
                count--;
                inputs++;
                outputs++;
            } while (count > 0);
        }
    } else {
        inputs = arg0;
        if (count > 0) {
            outputs = arg1;
            do {
                input = *inputs;
                if (input != 0 && ((0.0f != (x = input[0])) || input[1] != 0.0f || input[2] != 0.0f)) {
                    output = *outputs;
                    func_150A7960((void *)arg2, x, input[1], input[2], output, output + 1, output + 2);
                } else {
                    func_15142314(arg2, 0, *outputs);
                }
                count--;
                inputs++;
                outputs++;
            } while (count > 0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145EA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145EA4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15146078 CURRENT (1755) */
s32 func_15146078(f32 *direction, Game16EE20Vector3 *first,
                   Game16EE20Vector3 *second) {
    u8 zero_count;
    u8 nonzero_axis;
    u8 zero_axis;
    s32 second_axis;
    s32 first_axis;
    f32 first_component;
    f32 magnitude;
    f32 inverse;

    first_component = direction[0];
    if (0.0f == first_component && 0.0f == direction[1] && 0.0f == direction[2]) {
        return 0;
    }
    zero_count = 0;
    if (0.0f == first_component) {
        zero_count++;
        zero_axis = 0;
    } else {
        nonzero_axis = 0;
    }
    first_axis = 1;
    if (0.0f == direction[1]) {
        zero_count++;
        zero_axis = 1;
    } else {
        nonzero_axis = 1;
    }
    if (0.0f == direction[2]) {
        zero_count++;
        zero_axis = 2;
    } else {
        nonzero_axis = 2;
    }
    if (zero_count == 2) {
        switch (nonzero_axis) {
        case 0:
            first->x = 0.0f;
            first->z = 0.0f;
            first->y = 1.0f;
            second->x = 0.0f;
            second->y = 0.0f;
            second->z = 1.0f;
            return 1;
        case 1:
            first->y = 0.0f;
            first->z = 0.0f;
            first->x = 1.0f;
            second->x = 0.0f;
            second->y = 0.0f;
            second->z = 1.0f;
            return 1;
        case 2:
            first->y = 0.0f;
            first->z = 0.0f;
            first->x = 1.0f;
            second->x = 0.0f;
            second->z = 0.0f;
            second->y = 1.0f;
            return 1;
        }
    } else {
        second_axis = 2;
        if (zero_count == 1 && zero_axis == 2) {
            first_axis = 2;
            second_axis = 1;
        }
        first->x = 1.0f;
        ((f32 *)first)[first_axis] = 1.0f;
        ((f32 *)first)[second_axis] = -direction[0] - direction[first_axis] / direction[second_axis];
        func_151450B4(first, direction, second);
        func_151450B4(second, direction, first);
        func_15145128(first, first, &magnitude, &inverse);
        func_15145128(second, second, &magnitude, &inverse);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15146078 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15146078.s")
s32 func_1515D914(s32, s32, s32, s32, s32, s32, s32, s32,
                   s32, void *, s32, s32, s32, s32);
s32 func_1515E544(s32, s32, s32, s32, void *);
extern u8 D_800BE9C0;
extern u8 D_800D9BD0[];
extern s32 D_800D9E10[];
extern u8 D_800D9E20;
extern u8 D_800D9E21;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151462C8 CURRENT (3510) */
s32 func_151462C8(s32 arg0, u8 *arg1, s32 arg2, u8 *arg3,
                   s32 arg4, s32 arg5, f32 *arg6, s32 arg7, s32 arg8) {
    s32 model;
    s32 data;
    s32 mode;
    s32 index;
    s32 flags;
    s32 type;
    s32 result;
    s32 extra;

    mode = arg2 & 0xFF;
    index = (s16)arg5 * 4;
    model = *(s32 *)(arg1 + index + 8);
    if (model != 0) {
        data = *(s32 *)(arg1 + 0x18);
        if (data != 0) {
            type = mode;
            if (mode == 1) {
                if (arg3 != 0) {
                    if (*(s32 *)arg3 == 0 || (u8)arg4 != arg3[0x3B] ||
                        arg3[4] == 0xFF || arg3[0x302] == 0) {
                        type = 2;
                    }
                } else {
                    type = 0;
                }
            }
            switch (type) {
                case 1:
                    result = func_1515E544(arg0, *(s32 *)(arg3 + index + 0x304),
                        arg3[0x301], arg3[0x302], *(void **)(arg3 + 0x314));
                    break;
                case 2:
                    result = func_1515E544(arg0, *(s32 *)((u8 *)D_800D9E10 + index),
                        D_800D9E20, D_800D9E21,
                        D_800D9BD0 + ((s16)arg5 * 0x10) + (D_800BE9C0 * 8));
                    break;
                default:
                case 0:
                    flags = 0;
                    if ((u8)arg7 & 1) {
                        flags = 2;
                    }
                    if ((u8)arg7 & 2) {
                        extra = 0x10;
                    } else {
                        extra = 0;
                    }
                    result = func_1515D914(arg0, (s16)arg5, (s32)arg6[0],
                        (s32)arg6[1], (s32)arg6[2], arg8, model,
                        *(s32 *)arg1, data, arg1 + 4, *(s32 *)(arg1 + 0x1C),
                        0, extra | 8 | flags, 0);
                    break;
            }
            arg0 = result;
        }
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151462C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151462C8.s")

u8 func_151464B8(s16 *arg0) {
    s32 i = 0;
    s16 mask = 0;
    s32 bits;

    for (; i <= D_80082FA0; i++) {
        mask |= 1 << i;
    }
    bits = arg0[1] & mask;
    return (bits == 0) & 0xFF;
}
extern void func_15169040(s32 arg0, u8 arg1);

void func_15146508(void *arg0, void *arg1) {
    struct {
        void *field0;
        void *field4;
        u8 field8;
        u8 field9;
    } sp1C;

    sp1C.field0 = arg0;
    sp1C.field4 = arg1;
    sp1C.field8 = *(u8 *)((u8 *) arg0 + 0x3B);
    sp1C.field9 = *(u8 *)((u8 *) arg1 + 0x3B);
    func_15169040((s32) &sp1C, 0x2D);
}
typedef struct Game16EE20TransformNode {
    u8 pad0[2];
    u8 transformIndex;
    u8 pad3[0x1B];
    u16 child;
    u16 childTransform;
    u8 pad22[0x12];
    s32 transforms;
    u8 pad38[0x10];
    u8 *model;
} Game16EE20TransformNode;

s32 func_15031070(void *, void *, s32 *, s32 *);
void *func_1503195C(void *, s32, s32);
void func_15145EA4(s32 *, s32 *, s32, s32);
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514654C CURRENT (1533) */
s32 func_1514654C(u8 *arg0, Game16EE20TransformNode *arg1, s32 arg2,
                   f32 **arg3, f32 **arg4, s32 arg5) {
    s32 selected;
    s32 auxiliary;
    f32 transform[4][4];
    f32 **inputs;
    f32 **outputs;
    s32 base;
    s32 matrix;
    s32 index;
    u16 childId;
    u8 *model;
    f32 *input;
    f32 *output;

    if ((arg0 == 0) || (arg1 == 0) ||
        ((base = *(s32 *)(arg0 + 0x1D4)) == 0)) {
        return 0;
    }
    model = arg1->model;
    if (model != 0) {
        if (model[0x3F6] == 0) {
            return 0;
        }
        matrix = ((s32 *)(model + 0x3E8))[D_800BE9C0] + (arg2 << 6);
    } else {
        childId = arg1->child;
        if (childId != 0) {
            model = func_1503195C(arg0, childId, 0);
            if (model == 0) {
                return 0;
            }
            if (func_15031070(model, arg0, &selected, &auxiliary) == 0) {
                return 0;
            }
            matrix = selected;
            if (*(s32 *)(model + 0x48) != 0) {
                matrix = (arg1->childTransform << 6) + selected;
            }
        } else {
            matrix = arg1->transforms;
            if (matrix != 0) {
                matrix += D_800BE9C0 << 6;
            } else {
                func_15145EA4((s32 *)arg3, (s32 *)arg4,
                              base + (arg1->transformIndex << 6), arg5);
                return 1;
            }
        }
    }
    if (matrix != 0) {
            func_151EFEB8(transform, matrix);
            index = 0;
            inputs = arg3;
            outputs = arg4;
            if (arg5 > 0) {
                do {
                    input = *inputs;
                    output = *outputs;
                    func_150A7960(transform, input[0], input[1], input[2],
                                  output, output + 1, output + 2);
                    index++;
                    inputs++;
                    outputs++;
                } while (index != arg5);
            }
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514654C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514654C.s")



s32 func_1514672C(struct17 *arg0) {
    f32 hi = D_800A56C4;
    {
        f32 x = fabsf(arg0->unk0);
        if ((hi < x) || (hi < fabsf(arg0->unk8)) || (hi < arg0->unk4) || (arg0->unk4 < D_800A56C8)) {
            return 0;
        }
        return 1;
    }
}
s32 func_150ADA20(f32 *);                           /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151467A4 CURRENT (110) */
void func_151467A4(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 *arg7) {
    f32 temp_fv0;

    *arg0 -= D_800BE9A4;
    if (*arg0 < 0.0f) {
        *arg0 = func_150ADA68() * arg1;
        if (func_150ADA20(arg0) & 3) {
            *arg2 = (func_150ADA68() * (arg4 - arg3)) + arg3;
        } else {
            *arg2 = (func_150ADA68() * (arg5 - arg4)) + arg4;
        }
    }
    temp_fv0 = *arg7;
    *arg7 = temp_fv0 + ((*arg2 - temp_fv0) * arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151467A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151467A4.s")
