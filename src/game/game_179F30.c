#include "types.h"

/*
 * Reviewed source unit: src/game/game_179F30.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514CA80
 * - func_1514D15C
 * - func_1514D310
 * - func_1514D3B0
 * - func_1514D4B8
 * - func_1514D564
 * - func_1514D64C
 * - func_1514DAA4
 * - func_1514DBB8
 * - func_1514DE94
 * - func_1514E00C
 * - func_1514E194
 * - func_1514E31C
 * - func_1514E508
 * - func_1514E5B8
 * - func_1514E668
 * - func_1514E718
 * - func_1514E89C
 * - func_1514E920
 * - func_1514EA1C
 * - func_1514EC1C
 * - func_1514ECE0
 * - func_1514ED3C
 * - func_1514EDF0
 * - func_1514EE70
 * - func_1514EECC
 * - func_1514F194
 * - func_1514F308
 * - func_1514F3CC
 * - func_1514F5CC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514CA80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D15C.s")
typedef struct {
    u8 pad_0[0x10];
    s32 field_10;
    void *next;
    u8 pad_18[4];
    s16 dispatch_index;
} Game179F30Node;

typedef struct {
    u8 pad_0[2];
    s16 dispatch_id;
} Game179F30DispatchEntry;

extern void (*D_8008AB58[])(s32);
extern Game179F30DispatchEntry *D_8008ABE8[];
void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514D310 CURRENT (500) */
s32 func_1514D310(void *arg0) {
    Game179F30Node *node;
    Game179F30Node *next;
    s32 last_dispatch;
    s16 dispatch_index;
    s16 dispatch_id;

    node = *(Game179F30Node **)((u8 *)arg0 + 0x2F4);
    if (node != 0) {
        last_dispatch = -1;
        do {
            dispatch_index = node->dispatch_index;
            next = (Game179F30Node *)node->next;
            dispatch_id = D_8008ABE8[dispatch_index]->dispatch_id;

            if (dispatch_id != last_dispatch) {
                last_dispatch = dispatch_id;
                D_8008AB58[dispatch_id](node->field_10);
            }
            func_1516972C(node);
            node = next;
        } while (node != 0);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514D310 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D310.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D3B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D4B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D564.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D64C.s")
void func_1514D96C(s32 arg0) {

}
typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    f32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
} Game179F30LargePacket;

void func_10022EC0(void *, void *, s32);
extern s32 func_15158BD0(s32, s32, s32);
extern void func_1514EC1C(s32 arg0, s32 arg1, s32 arg2);

void func_1514D978(s32 arg0) {
    Game179F30LargePacket packet;
    s32 object;

    packet.field_0 = 0;
    packet.field_4 = 0;
    packet.field_8 = 0;
    packet.field_C = 0;
    packet.field_10 = 12.0f;
    packet.field_14 = 0;
    packet.field_18 = 0;
    packet.field_1C = 0;
    object = func_15158BD0(arg0, 1, sizeof(packet));
    if (object != 0) {
        func_10022EC0((void *)(object + 0x58), &packet, sizeof(packet));
        func_1514EC1C(object, arg0, 0x13);
    }
}
extern s32 func_151ACA60(s32 arg0, s32 arg1, s32 arg2);

void func_1514D9F4(s32 arg0) {
    func_1514D978(arg0);
    func_1514EC1C(func_151ACA60(arg0, 0x41A00000, 0), arg0, 0x14);
}

typedef struct Game179F30Packet {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    u8 pad10[4];
    s32 field_14;
    s32 field_18;
} Game179F30Packet;

void func_1514DA38(s32 arg0) {
    s32 object;
    Game179F30Packet packet;

    packet.field_14 = 0;
    packet.field_18 = 0;
    packet.field_0 = 0;
    packet.field_4 = 0;
    packet.field_8 = 0;
    packet.field_C = 0;
    object = func_15158BD0(arg0, 1, sizeof(packet));
    if (object != 0) {
        func_10022EC0((void *)(object + 0x58), &packet, sizeof(packet));
        func_1514EC1C(object, arg0, 0x13);
    }
}

typedef struct Game179F30State {
    u8 pad0[0x94];
    u32 flags;
} Game179F30State;

typedef struct Game179F30SmallPacket {
    s32 field_0;
    s32 field_4;
} Game179F30SmallPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514DAA4 CURRENT (120) */
void func_1514DAA4(s32 arg0) {
    s32 object;
    Game179F30SmallPacket packet;

    ((Game179F30State *)arg0)->flags |= 2;
    packet.field_0 = 0;
    packet.field_4 = 0;
    object = func_15158BD0(arg0, 1, sizeof(packet));
    if (object != 0) {
        func_10022EC0((void *)(object + 0x58), &packet, sizeof(packet));
        func_1514EC1C(object, arg0, 0x13);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514DAA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DAA4.s")
extern s32 func_15158BD0(s32 arg0, s32 arg1, s32 arg2);

void func_1514DB18(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_15158BD0(arg0, 1, 0);
    if (temp_v0 != 0) {
        func_1514EC1C(temp_v0, arg0, 0x13);
    }
}
void func_1514DB58(s32 arg0) {

}
void func_151B2060(void);
extern s32 D_800BE9F0;

void func_1514DB64(void) {
    if (D_800BE9F0 == 0x14) {
        func_151B2060();
    }
}
void func_1514DB98(void) {
    func_1514F194();
}
extern u8 D_800A58A0[];
void func_15160A58(void *, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514DBB8 CURRENT (100) */
void func_1514DBB8(void *arg0) {
    func_15160A58(arg0, 2, D_800A58A0, 2, 0x12C, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514DBB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DBB8.s")
/* Call context: func_1500EE18: raw o32 argument homes in asm/nonmatchings/game_3C230/func_1500EE18.s; pointer uses in entry block; caller discards result */
void func_1500EE18(void *, s32, s32); /* CONKER_ABI_DISCARDED_RETURN */

void func_1514DC38(void *arg0) {
    func_1500EE18(arg0, 0xFF, 1);
}
void func_151D0F60(void *, s32, s32, s32); /* CONKER_ABI_DISCARDED_RETURN */

void func_1514DC5C(void *arg0) {
    func_151D0F60(arg0, 0, 0xFF, 1);
}
void func_1514DC84(u8 *arg0) {
    *(u32 *)(arg0 + 0x94) |= 2;
}
void func_1514DC98(u8 *arg0) {
    *(u32 *)(arg0 + 0x94) |= 0x710;
}
void func_1514DCAC();

void func_15083568(void *, s32, s32, s32);

void func_1514DCAC(arg0)
void *arg0;
{
    *(s32 *)((u8 *)arg0 + 0x9C) = 0x6000;
    func_15083568(arg0, 0x23, 0x3F800000, 0);
    func_15083568(arg0, 0x44, 0x3F800000, 0);
}
void func_15083568(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1514DCF4(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x94) = 1;
    }
    func_15083568(arg0, 0x17, 0x3F800000, 0);
}
void func_1514DD2C(void) {
    func_1514DCAC();
}
void func_1514DD4C(void) {
    func_1514DCAC();
}
void func_1514DD6C(void) {
    func_1514DCAC();
}
void func_1514DD8C(void) {
    func_1514DCAC();
}
void func_1514DDAC(void) {
    func_1514DCAC();
}
void func_1514DDCC(void) {
    func_1514DCAC();
}
void func_1514DDEC(void) {
    func_1514DCAC();
}
void func_1514DE0C(void) {
    func_1514DCAC();
}
void func_1514DE2C(s32 arg0) {

}
void func_1514DE38(s32 arg0) {

}
void func_1514DE44(s32 arg0) {

}
extern void *D_800D2E4C;

void func_1514DE50(void) {
    if (*(u8 *)((u8 *)D_800D2E4C + 0x11) & 8) {
        func_1514DCAC();
    }
}
void func_1514DE88(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DE94.s")
/* Call context: func_15083FB0: unique active project prototype */
u8 func_15083FB0(u8);

void func_1514DFD0(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x65) = (s8) (func_15083FB0(9U) + 1);
    *(u8 *)((u8 *)arg0 + 0x101) = (u8) (*(u8 *)((u8 *)arg0 + 0x101) | 0x34);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E00C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E194.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E31C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E508.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E5B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E668.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E718.s")
void *func_1518D1C0(s32, s32, s32, s32, s32, s32, void *);
extern u8 D_800A5920;

void func_1514E7C8(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_1518D1C0(arg0, 7, 0, 1, 0xFF, 1, &D_800A5920);
    func_1514EC1C((s32)temp_v0, arg0, 0xF);
}
void func_1514E824(s32 arg0) {

}
void func_1516972C(void *arg0);

void func_1514E830(void *arg0) {
    func_1516972C(arg0);
}
void func_1518E308(void *arg0);

void func_1514E850(void *arg0) {
    func_1518E308(arg0);
    func_1516972C(arg0);
}
void func_1515F10C(void);

void func_1514E87C(void) {
    func_1515F10C();
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514E89C CURRENT (2325) */
s32 func_1514E89C(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    switch (arg1) {
    case 0:
        temp_v0 = *(s32 *)((u8 *)arg0 + 0x10);
        if (temp_v0 & 1) {
            *(s32 *)((u8 *)arg0 + 0x10) = temp_v0 & ~1;
        } else {
            *(s32 *)((u8 *)arg0 + 0x10) = temp_v0 | 1;
        }
        return 1;
    case 1:
        *(s32 *)((u8 *)arg0 + 0x10) |= 1;
        return 1;
    case 2:
        *(s32 *)((u8 *)arg0 + 0x10) &= ~1;
        return 1;
    default:
        return 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514E89C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E89C.s")
s32 func_1514E89C();
void func_1514E920(void);

#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E920.s")
void func_1514E9DC(void) {
    func_1514E920();
}
void func_1514E9FC(void) {
    func_1514E89C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EA1C.s")
void func_1514EB6C(void) {
    func_1514E89C();
}
s32 func_1514EB8C(s32 arg0, s32 arg1, s32 arg2) {
    return 1;
}
typedef struct {
    u8 pad0[0x10];
    void *owner;
    void *field_14;
    void *field_18;
    s16 id;
    u8 pad1E[2];
} Game179F30Effect;

Game179F30Effect *func_15167A68(s32, s32, s32, s32, u8, u8);

Game179F30Effect *func_1514EBA4(void *arg0, s16 arg1, s32 arg2) {
    Game179F30Effect *effect;

    effect = func_15167A68(0x24, 1, arg2 + sizeof(Game179F30Effect), 1, 0xFF, 1);
    if (effect == 0) {
        return 0;
    }
    effect->owner = arg0;
    effect->field_14 = 0;
    effect->field_18 = 0;
    effect->id = arg1;
    return effect;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EC1C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514ECE0 CURRENT (920) */
s32 func_1514ECE0(void *arg0, s16 arg1, void **arg2) {
    s32 var_v1;
    void *var_v0;

    var_v1 = 0;
    var_v0 = arg0;
    if (arg0 != 0) {
loop_1:
        if (arg1 == *(s16 *)((u8 *)var_v0 + 0x1C)) {
            var_v1 = 1;
        } else {
            var_v0 = *(void **)((u8 *)var_v0 + 0x14);
        }
        if ((var_v0 != 0) && (var_v1 == 0)) {
            goto loop_1;
        }
    }
    if (arg2 != 0) {
        *arg2 = var_v0;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514ECE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514ECE0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514ED3C CURRENT (920) */
s32 func_1514ED3C(void *arg0, s32 arg1, void **arg2) {
    s32 var_v1;
    void *var_v0;

    var_v1 = 0;
    var_v0 = arg0;
    if (arg0 != 0) {
loop_1:
        if (arg1 == *(s32 *)((u8 *)var_v0 + 0x10)) {
            var_v1 = 1;
        } else {
            var_v0 = *(void **)((u8 *)var_v0 + 0x14);
        }
        if ((var_v0 != 0) && (var_v1 == 0)) {
            goto loop_1;
        }
    }
    if (arg2 != 0) {
        *arg2 = var_v0;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514ED3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514ED3C.s")
s32 func_1514ED8C(void *arg0, void *arg1) {
    s32 sp1C;
    void *temp_v0;
    void *temp_v0_2;

    if (arg0 == *(void **)((u8 *)arg1 + 0x2F4)) {
        *(void **)((u8 *)arg1 + 0x2F4) = (void *) *(void **)((u8 *)arg0 + 0x14);
    }
    temp_v0 = *(void **)((u8 *)arg0 + 0x14);
    if (temp_v0 != 0) {
        *(void **)((u8 *)temp_v0 + 0x18) = (void *) *(void **)((u8 *)arg0 + 0x18);
    }
    temp_v0_2 = *(void **)((u8 *)arg0 + 0x18);
    if (temp_v0_2 != 0) {
        *(void **)((u8 *)temp_v0_2 + 0x14) = (void *) *(void **)((u8 *)arg0 + 0x14);
    }
    sp1C = *(s32 *)((u8 *)arg0 + 0x10);
    func_1516972C(arg0);
    return sp1C;
}
/* Call context: func_1514ED8C: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514EDF0 CURRENT (310) */
void func_1514EDF0(s32 arg0, void *arg1) {
    s32 temp_v0;
    void *var_s1;

    var_s1 = *(void **)((u8 *)arg1 + 0x2F4);
    {
        void * sp34 = 0;
    do {
        temp_v0 = func_1514ED3C(var_s1, arg0, &sp34);
        if (temp_v0 != 0) {
            var_s1 = *(void **)((u8 *)sp34 + 0x14);
            func_1514ED8C(sp34, arg1);
        }
    } while (temp_v0 & 0xFF);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514EDF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EDF0.s")
void *func_1515BE50(void *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514EE70 CURRENT (185) */
void func_1514EE70(s32 arg0) {
    struct {
        void *field_0;
        u8 field_4;
        u8 field_5;
        s16 field_6;
    } sp20;
    void *temp_v0;

    sp20.field_0 = (void *)arg0;
    sp20.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    sp20.field_5 = 0;
    sp20.field_6 = 0x12C;
    temp_v0 = func_1515BE50(&sp20, 0, 0xFF, 1);
    func_1514EC1C((s32)temp_v0, arg0, 0x16);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514EE70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EE70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EECC.s")
void func_1514F110(void) {
    func_1514F194();
}
typedef struct {
    u8 pad_0[9];
    u8 field_9;
} Game179F30Mode;

typedef struct {
    u8 pad_0[0x14];
    Game179F30Mode *field_14;
} Game179F30ModeState;

s32 func_1514E89C(void *, s32, s32);

s32 func_1514F130(Game179F30ModeState *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
        case 0xD:
            arg0->field_14->field_9 = 0;
            break;
        case 0xE:
            arg0->field_14->field_9 = 1;
            break;
        default:
            return func_1514E89C(arg0, arg1, arg2);
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F194.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F308.s")
typedef struct Game179F30F3CCPacket {
    void *actor;
    u8 type;
    u8 pad5[3];
    f32 value;
} Game179F30F3CCPacket;

void *func_15149130(s16, s8, s8, s8, u8, u8, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514F3CC CURRENT (100) */
void func_1514F3CC(void *arg0) {
    Game179F30F3CCPacket packet;
    void *temp_v0;

    packet.actor = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.value = 0.0f;
    temp_v0 = func_15149130(0x12C, -1, 0x3A, -1, 0, 0x2B, 0xC, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0xC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514F3CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F3CC.s")
extern u8 D_800A5988;

void func_1514F44C(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, &D_800A5988);
    func_1514EC1C((s32)temp_v0, arg0, 0xD);
}
void func_151D74B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_1514F4A8(s32 arg0) {
    func_151D74B0(arg0, 1, -1, 0xFF, 1);
}
void func_1514F4D8(s32 arg0) {
    func_151D74B0(arg0, 2, 1, 0xFF, 1);
}
void func_1514F508(s32 arg0) {
    func_151D74B0(arg0, 3, 0, 0xFF, 1);
}
void func_1514F538(s32 arg0) {
    func_151D74B0(arg0, 4, -1, 0xFF, 1);
}
void func_150C4120(void *, s32, s32, s32); /* CONKER_ABI_DISCARDED_RETURN */

void func_1514F568(void *arg0) {
    func_150C4120(arg0, -1, 0xFF, 1);
}
void func_1501175C(s32, s32, s32);
void func_15011A78(s32, s32, s32);

void func_1514F590(s32 arg0) {
    func_1501175C(arg0, 0xFF, 1);
    func_15011A78(arg0, 0xFF, 1);
}
typedef struct Game179F30Actor {
    u8 pad0[0x3B];
    u8 type;
} Game179F30Actor;

typedef struct Game179F30EffectPacket {
    s32 field_0;
    f32 field_4;
    Game179F30Actor *actor;
    u8 type;
    u8 padD[3];
    f32 field_10;
    s16 field_14;
    s16 field_16;
    u8 field_18;
} Game179F30EffectPacket;

extern f32 D_800A5E5C;
void func_150C0AC0(Game179F30EffectPacket *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514F5CC CURRENT (400) */
void func_1514F5CC(Game179F30Actor *arg0) {
    Game179F30EffectPacket packet;

    packet.field_0 = 0;
    packet.actor = arg0;
    packet.field_4 = 0.0f;
    packet.type = arg0->type;
    packet.field_10 = D_800A5E5C;
    packet.field_14 = 0x14;
    packet.field_16 = 0x12C;
    packet.field_18 = 4;
    func_150C0AC0(&packet, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514F5CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F5CC.s")
