#include "types.h"

/*
 * Reviewed source unit: src/game/game_179F30.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514CA80
 * - func_1514D15C
 * - func_1514D3B0
 * - func_1514D64C
 * - func_1514E920
 * - func_1514EECC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514CA80.s")
void *func_15155FD4(s32);
void func_1516972C(void *);
void *func_15155780(s32, s32);
s32 func_1514CA80(void *, s32 *, s32 *, s32 *);
extern void (*D_8008AACC)(void *);
extern void (*D_8008AA70[])(void *);
extern u8 *D_8008AB90[];
extern u8 D_800A5EC0[];
extern u8 D_800A5ED8[];
extern u8 D_800CC2D0[];
extern u8 D_800BE616;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514D15C CURRENT (150) */
s32 func_1514D15C(u8 *arg0) {
    struct {
        s32 third;
        s32 second;
        s32 first;
    } locals;
    u8 mask;
    void *node;
    s32 result;
    s32 actorIndex;

    locals.first = -1;
    locals.second = -1;
    locals.third = -1;
    if (*(s32 *)(arg0 + 0x2F4) != 0) {
        return 0;
    }
    actorIndex = ((s32)arg0 - (s32)D_800CC2D0) / 0x32C;
    do {
        node = func_15155FD4(actorIndex);
        if (node != 0) {
            func_1516972C(node);
        }
    } while (node != 0);
    if (actorIndex == 0 && D_800BE616 == 0) {
        func_15155780(actorIndex, 0xFF);
    }
    D_8008AACC(arg0);
    result = func_1514CA80(arg0, &locals.first, &locals.second, &locals.third);
    mask = result;
    if (result == 0) {
        return 0;
    }
    if (result & 4) {
        if (D_800A5ED8[locals.third] != 0) {
            D_8008AA70[D_800A5ED8[locals.third]](arg0);
        }
    }
    if (mask & 2) {
        if (D_800A5EC0[locals.second] != 0) {
            D_8008AA70[D_800A5EC0[locals.second]](arg0);
        }
    }
    if ((mask & 2) && (mask & 1)) {
        if (D_8008AA70[D_8008AB90[locals.second][locals.first]] != 0) {
            D_8008AA70[D_8008AB90[locals.second][locals.first]](arg0);
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514D15C */
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

s32 func_1514D310(void *arg0) {
    Game179F30Node *node;
    Game179F30Node *next;
    s16 sentinel;
    Game179F30DispatchEntry **entries;

    sentinel = -1;
    node = *(Game179F30Node **)((u8 *)arg0 + 0x2F4);
    if (node != 0) {
        entries = D_8008ABE8;
        do {
            next = (Game179F30Node *)node->next;

            if (sentinel != entries[node->dispatch_index]->dispatch_id) {
                D_8008AB58[entries[node->dispatch_index]->dispatch_id](node->field_10);
            }
            func_1516972C(node);
            node = next;
        } while (node != 0);
    }
    return 1;
}
s32 func_1514D4B8(s16, s16);
extern s32 (*D_8008AB64[])(s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514D3B0 CURRENT (703) */
s32 func_1514D3B0(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    s32 callback_result;
    s32 var_s1;
    Game179F30Node *var_s0;
    Game179F30DispatchEntry **entries;

    var_s1 = 0;
    var_s0 = *(Game179F30Node **)((u8 *)arg0 + 0x2F4);
    if (var_s0 != 0) {
        entries = D_8008ABE8;
        do {
            if (arg1 != var_s0->dispatch_index) {
                if (func_1514D4B8(
                        *(s16 *)((u8 *)entries[arg1] + 4),
                        var_s0->dispatch_index) != 0) {
                    goto dispatch;
                }
            } else {
dispatch:
                if (*(s16 *)entries[var_s0->dispatch_index] != -1) {
                    callback_result = D_8008AB64[
                        *(s16 *)entries[var_s0->dispatch_index]](
                            var_s0->field_10, arg2, arg3);
                    var_s1 = 0;
                    if (callback_result != 0) {
                        var_s1 = 1;
                    }
                }
            }
            var_s0 = (Game179F30Node *)var_s0->next;
        } while (var_s0 != 0);
    }
    return var_s1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514D3B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D3B0.s")
s32 func_1514D4B8(s16 arg0, s16 arg1) {
    if (arg0 == -1) {
        return 0;
    }
    if (arg0 == arg1) {
        return 1;
    }
    if (func_1514D4B8(*(s16 *)((u8 *)D_8008ABE8[arg0] + 6), arg1) != 0) {
        return 1;
    }
    if (func_1514D4B8(*(s16 *)((u8 *)D_8008ABE8[arg0] + 4), arg1) != 0) {
        return 1;
    }
    return 0;
}
void func_10022EC0(void *, void *, s32);
s32 func_1514EC1C(s32, s32, s16);
s32 func_150C5370(f32 *, s32);
extern f32 D_800A5DE4;
extern f32 D_800A5DE8;
extern f32 D_800A5DEC;
extern f32 D_800A5DF0;

typedef struct {
    void * volatile sp1C;
    u8 sp20;
    s8 sp21;
    u8 pad22[2];
    f32 sp24;
    f32 sp28;
    f32 sp2C;
} Game179F30SetupHead;

typedef struct {
    f32 sp34;
    f32 sp38;
    f32 sp3C;
    f32 sp40;
    f32 sp44;
    f32 sp48;
    s8 sp4C;
    u8 pad4D[3];
    f32 sp50;
    s8 sp54;
    u8 pad55[3];
} Game179F30SetupTail;

void func_1514D564(u8 *arg0) {
    Game179F30SetupTail tail;
    s32 temp_v0;
    Game179F30SetupHead head;

    head.sp1C = arg0;
    head.sp20 = arg0[0x3B];
    head.sp21 = 6;
    tail.sp4C = 1;
    head.sp24 = 0.0f;
    head.sp28 = -180.0f;
    head.sp2C = 77.0f;
    tail.sp34 = D_800A5DE4;
    tail.sp38 = D_800A5DE8;
    tail.sp3C = D_800A5DEC;
    tail.sp40 = *(f32 *)(arg0 + 0x14);
    tail.sp44 = *(f32 *)(arg0 + 0x18);
    tail.sp48 = *(f32 *)(arg0 + 0x1C);
    tail.sp54 = 1;
    tail.sp50 = D_800A5DF0;
    temp_v0 = func_150C5370(&tail.sp34, 0x14);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0xC8), (void *)&head.sp1C, 0x14);
        func_1514EC1C(temp_v0, (s32)arg0, 0x15);
    }
}
/* Raw US callees establish pointer arguments and the stack byte parameters. */
s32 func_15189FF0(s32, void *, void *, s32, u8, u8, u8);
void *func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);
extern u8 D_800A58D0[];
extern u8 D_800A58E4[];
extern u8 D_800A58F8[];
extern u8 D_800A590C[];

s32 func_1514EC1C(s32, s32, s16);
void *func_15160A58(void *, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A5DF4;
extern f32 D_800A5DF8;
extern f32 D_800A5DFC;
extern f32 D_800A5E00;

typedef struct {
        f32 sp54;
        f32 sp58;
        f32 sp5C;
        f32 sp60;
        f32 sp64;
        f32 sp68;
        void * sp6C;
        s8 sp70;
        u8 sp71;
        s8 sp72;
        u8 pad_73[0x1];
        s8 sp74;
        u8 pad_75[0x1];
        s16 sp76;
        s16 sp78;
        u8 pad_7A[0x2];
        s32 sp7C;
        s32 sp80;
        u8 sp84;
        s8 sp85;
        s8 sp86;
        u8 sp87;
        u8 pad_88[0x8];
        f32 sp90;
        f32 sp94;
        f32 sp98;
        f32 sp9C;
        f32 spA0;
        f32 spA4;
        u8 pad_A8[0xC];
        s32 spB4;
        u8 pad_B8[0x1];
        u8 spB9;
        u8 pad_BA[0x12];
        f32 spCC;
        f32 spD0;
        f32 spD4;
        f32 spD8;
        f32 spDC;
        f32 spE0;
        f32 spE4;
        f32 spE8;
        f32 spEC;
        u8 pad_F0[0x24];
        f32 sp114;
        u8 pad_118[0x8];
        s8 sp120;
        s8 sp121;
        s8 sp122;
        s8 sp123;
} Game179F30D64CSetup;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514D64C CURRENT (7859) */
void func_1514D64C(void *arg0) {
    void *second_setup;
    Game179F30D64CSetup setup;

    setup.sp74 = 3;
    setup.sp7C = 0;
    setup.sp80 = 0;
    setup.spB4 = 0x12012;
    setup.sp78 = 0;
    setup.spB9 = 0xFF;
    setup.sp84 = 0xFF;
    setup.sp85 = 0;
    setup.sp86 = 0;
    setup.sp87 = 0xFF;
    setup.sp76 = 0x401;
    setup.sp90 = 0.0f;
    setup.sp94 = 0.0f;
    setup.sp98 = 0.0f;
    setup.sp9C = 0.0f;
    setup.spA0 = 0.0f;
    setup.spA4 = 0.0f;
    setup.spCC = 28.0f;
    setup.spD0 = 28.0f;
    setup.spDC = 0.5f;
    setup.spE0 = 0.5f;
    setup.spD4 = 4.0f;
    setup.spD8 = 17.0f;
    setup.spE4 = 0.75f;
    setup.spE8 = 0.25f;
    setup.spEC = D_800A5DF4;
    setup.sp6C = arg0;
    setup.sp54 = 0.0f;
    setup.sp58 = 0.0f;
    setup.sp60 = 0.0f;
    setup.sp64 = 0.0f;
    setup.sp70 = 0x2B;
    setup.sp120 = 0;
    setup.sp121 = 0;
    setup.sp122 = 0;
    setup.sp123 = 0;
    setup.sp72 = 1;
    setup.sp71 = *(u8 *)((u8 *)arg0 + 0x3B);
    setup.sp5C = 25.0f;
    setup.sp68 = 75.0f;
    setup.sp114 = 1.0f;
    func_1514EC1C(func_15189FF0((s32)((u8 *)&setup.sp76 - 2), &setup.spCC, &setup.sp54, 2, 0U, 0U, 0U), (s32) arg0, 9);
    second_setup = &setup.sp74;
    setup.sp74 = 3;
    setup.sp7C = 0;
    setup.sp80 = 0;
    setup.spB4 = 0x12012;
    setup.sp78 = 0;
    setup.spB9 = 0xFF;
    setup.sp84 = 0xFF;
    setup.sp85 = 0;
    setup.sp86 = 0;
    setup.sp87 = 0xFF;
    setup.sp76 = 0x401;
    setup.spCC = 30.0f;
    setup.spD0 = 30.0f;
    setup.spD4 = 10.0f;
    setup.spDC = D_800A5DF8;
    setup.spE0 = D_800A5DF8;
    setup.sp90 = 0.0f;
    setup.sp94 = 0.0f;
    setup.sp98 = 0.0f;
    setup.sp9C = 0.0f;
    setup.spA0 = 0.0f;
    setup.spA4 = 0.0f;
    setup.spE4 = D_800A5DFC;
    setup.spE8 = D_800A5DFC;
    setup.spD8 = 16.0f;
    setup.spEC = D_800A5E00;
    setup.sp6C = arg0;
    setup.sp70 = 5;
    setup.sp120 = 0;
    setup.sp121 = 0;
    setup.sp122 = 0;
    setup.sp123 = 0;
    setup.sp72 = 0;
    setup.sp58 = 10.0f;
    setup.sp54 = 0.0f;
    setup.sp60 = 0.0f;
    setup.sp71 = *(u8 *)((u8 *)arg0 + 0x3B);
    setup.sp5C = -70.0f;
    setup.sp64 = 20.0f;
    setup.sp68 = -140.0f;
    setup.sp114 = 1.0f;
    func_1514EC1C(func_15189FF0((s32)second_setup, &setup.spCC, &setup.sp54, 2, 0U, 0U, 0U), (s32) arg0, 0xA);
    func_15160A58(arg0, 5, &setup.sp54, 2, 0x12C, 0x28, 0xFF, 0, 0, 0xFF, 0, 1, 0, 0, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514D64C */
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
extern s32 func_1514EC1C(s32 arg0, s32 arg1, s16 arg2);

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

void func_1514DAA4(s32 arg0) {
    s32 object;

    ((Game179F30State *)arg0)->flags |= 2;
    {
        Game179F30SmallPacket packet;
        packet.field_0 = 0;
        packet.field_4 = 0;
        object = func_15158BD0(arg0, 1, sizeof(packet));
        if (object != 0) {
            func_10022EC0((void *)(object + 0x58), &packet, sizeof(packet));
            func_1514EC1C(object, arg0, 0x13);
        }
    }
}
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
void func_1514F194();
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
void *func_15160A58(void *, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_1514DBB8(void *arg0) {
    func_15160A58(arg0, 2, D_800A58A0, 2, 0x12C, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}
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
void func_1514DCAC(void *arg0);

void *func_15083568(void *, s32, s32, s32);

void func_1514DCAC(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0x9C) = 0x6000;
    func_15083568(arg0, 0x23, 0x3F800000, 0);
    func_15083568(arg0, 0x44, 0x3F800000, 0);
}
void *func_15083568(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1514DCF4(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x94) = 1;
    }
    func_15083568(arg0, 0x17, 0x3F800000, 0);
}
void func_1514DD2C(void *arg0) {
    func_1514DCAC(arg0);
}
void func_1514DD4C(void *arg0) {
    func_1514DCAC(arg0);
}
void func_1514DD6C(void *arg0) {
    func_1514DCAC(arg0);
}
void func_1514DD8C(void *arg0) {
    func_1514DCAC(arg0);
}
void func_1514DDAC(void *arg0) {
    func_1514DCAC(arg0);
}
void func_1514DDCC(void *arg0) {
    func_1514DCAC(arg0);
}
void func_1514DDEC(void *arg0) {
    func_1514DCAC(arg0);
}
void func_1514DE0C(void *arg0) {
    func_1514DCAC(arg0);
}
void func_1514DE2C(s32 arg0) {

}
void func_1514DE38(s32 arg0) {

}
void func_1514DE44(s32 arg0) {

}
extern void *D_800D2E4C;

void func_1514DE50(void *arg0) {
    if (*(u8 *)((u8 *)D_800D2E4C + 0x11) & 8) {
        func_1514DCAC(arg0);
    }
}
void func_1514DE88(s32 arg0) {

}
void func_15160CDC(s32, s32, void *, void *, f32, s32, s32, s32, s32,
                   s32, s32, s32, s32, s32, s32, s32);
extern u8 D_800A58AC[];
extern u8 D_800A58B8[];
extern u8 D_800A58C4[];
extern f32 D_800A5E04;
extern u8 D_800BE9B4;

void func_1514DE94(s32 arg0) {
    void *effect;

    func_15160CDC(arg0, 0xC, D_800A58AC, D_800A58B8, D_800A5E04,
                  2, 0x12C, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 1, 0xFF, 1);
    effect = func_15083568((void *)arg0, 0x3C, 0x3F800000, 0);
    if (D_800BE9B4 == 0) {
        *(s32 *)((u8 *)effect + 0x38) = 0x960;
    }
    effect = func_15160A58((void *)arg0, 0, D_800A58C4, 2, 0x12C,
                           0xB, 0xFF, 0xFF, 0xFF, 2, 0, -1, 0, 0,
                           0xFF, 1);
    func_1514EC1C((s32)effect, arg0, 0x19);
}
/* Call context: func_15083FB0: unique active project prototype */
u8 func_15083FB0(u8);

void func_1514DFD0(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x65) = (s8) (func_15083FB0(9U) + 1);
    *(u8 *)((u8 *)arg0 + 0x101) = (u8) (*(u8 *)((u8 *)arg0 + 0x101) | 0x34);
}
void func_151D74B0(s32, s32, s32, s32, s32);
extern f32 D_800A5E08;
extern f32 D_800A5E0C;

void func_1514E00C(void *arg0) {
    struct {
        f32 sp2C;
        f32 sp30;
        f32 sp34;
        f32 sp38;
        f32 sp3C;
        f32 sp40;
        void * sp44;
        s8 sp48;
        u8 sp49;
        s8 sp4A;
        u8 pad_4B[0x1];
        s8 sp4C;
        u8 pad_4D[0x1];
        s16 sp4E;
        s16 sp50;
        u8 pad_52[0x2];
        s32 sp54;
        s32 sp58;
        u8 sp5C;
        u8 sp5D;
        s8 sp5E;
        u8 sp5F;
        u8 pad_60[0x8];
        f32 sp68;
        f32 sp6C;
        f32 sp70;
        f32 sp74;
        f32 sp78;
        f32 sp7C;
        u8 pad_80[0xC];
        s32 sp8C;
        u8 pad_90[0x1];
        u8 sp91;
        u8 pad_92[0x12];
        f32 spA4;
        f32 spA8;
        f32 spAC;
        f32 spB0;
        f32 spB4;
        f32 spB8;
        f32 spBC;
        f32 spC0;
        f32 spC4;
        u8 pad_C8[0x24];
        f32 spEC;
        u8 pad_F0[0x8];
        s8 spF8;
        s8 spF9;
        s8 spFA;
        s8 spFB;
        u8 pad_FC[4];
    } setup;

    setup.sp4C = 3;
    setup.sp54 = 0;
    setup.sp58 = 0;
    setup.sp8C = 0x12002;
    setup.sp50 = 0;
    setup.sp91 = 0xFF;
    setup.sp5C = 0xFF;
    setup.sp5D = 0x8E;
    setup.sp5E = 0x19;
    setup.sp5F = 0xFF;
    setup.sp4E = 0x401;
    setup.sp68 = 0.0f;
    setup.sp6C = 0.0f;
    setup.sp70 = 0.0f;
    setup.sp74 = 0.0f;
    setup.sp78 = 0.0f;
    setup.sp7C = 0.0f;
    setup.spA4 = 20.0f;
    setup.spA8 = 20.0f;
    setup.spAC = 20.0f;
    setup.spB0 = 20.0f;
    setup.spB4 = 0.0f;
    setup.spB8 = 0.0f;
    setup.spBC = 0.5f;
    setup.spC0 = 0.5f;
    setup.spC4 = D_800A5E08;
    setup.sp49 = *(u8 *)((u8 *)arg0 + 0x3B);
    setup.sp2C = 35.0f;
    setup.sp30 = 27.0f;
    setup.sp38 = 35.0f;
    setup.sp3C = 27.0f;
    setup.sp44 = arg0;
    setup.sp48 = 6;
    setup.spF8 = 0;
    setup.spF9 = 0;
    setup.spFA = 0;
    setup.spFB = 0;
    setup.sp4A = -1;
    setup.sp34 = 59.0f;
    setup.sp40 = D_800A5E0C;
    setup.spEC = 1.0f;
    func_1514EC1C(func_15189FF0((s32) &setup.sp4C, &setup.spA4, &setup.sp2C, 2, 0U, 0U, 0U), (s32) arg0, 6);
    func_151D74B0((s32) arg0, 5, -1, 0xFF, 1);
}

void func_151D74B0(s32, s32, s32, s32, s32);
extern f32 D_800A5E10;
extern f32 D_800A5E14;

void func_1514E194(void *arg0) {
    struct {
        f32 sp2C;
        f32 sp30;
        f32 sp34;
        f32 sp38;
        f32 sp3C;
        f32 sp40;
        void * sp44;
        s8 sp48;
        u8 sp49;
        s8 sp4A;
        u8 pad_4B[0x1];
        s8 sp4C;
        u8 pad_4D[0x1];
        s16 sp4E;
        s16 sp50;
        u8 pad_52[0x2];
        s32 sp54;
        s32 sp58;
        u8 sp5C;
        u8 sp5D;
        s8 sp5E;
        u8 sp5F;
        u8 pad_60[0x8];
        f32 sp68;
        f32 sp6C;
        f32 sp70;
        f32 sp74;
        f32 sp78;
        f32 sp7C;
        u8 pad_80[0xC];
        s32 sp8C;
        u8 pad_90[0x1];
        u8 sp91;
        u8 pad_92[0x12];
        f32 spA4;
        f32 spA8;
        f32 spAC;
        f32 spB0;
        f32 spB4;
        f32 spB8;
        f32 spBC;
        f32 spC0;
        f32 spC4;
        u8 pad_C8[0x24];
        f32 spEC;
        u8 pad_F0[0x8];
        s8 spF8;
        s8 spF9;
        s8 spFA;
        s8 spFB;
        u8 pad_FC[4];
    } setup;

    setup.sp4C = 3;
    setup.sp54 = 0;
    setup.sp58 = 0;
    setup.sp8C = 0x12002;
    setup.sp50 = 0;
    setup.sp91 = 0xFF;
    setup.sp5C = 0xFF;
    setup.sp5D = 0x8E;
    setup.sp5E = 0x19;
    setup.sp5F = 0xFF;
    setup.sp4E = 0x401;
    setup.sp68 = 0.0f;
    setup.sp6C = 0.0f;
    setup.sp70 = 0.0f;
    setup.sp74 = 0.0f;
    setup.sp78 = 0.0f;
    setup.sp7C = 0.0f;
    setup.spA4 = 16.0f;
    setup.spA8 = 16.0f;
    setup.spAC = 16.0f;
    setup.spB0 = 16.0f;
    setup.spB4 = 0.0f;
    setup.spB8 = 0.0f;
    setup.spBC = 0.5f;
    setup.spC0 = 0.5f;
    setup.spC4 = D_800A5E10;
    setup.sp49 = *(u8 *)((u8 *)arg0 + 0x3B);
    setup.sp2C = 35.0f;
    setup.sp30 = 27.0f;
    setup.sp38 = 35.0f;
    setup.sp3C = 27.0f;
    setup.sp44 = arg0;
    setup.sp48 = 6;
    setup.spF8 = 0;
    setup.spF9 = 0;
    setup.spFA = 0;
    setup.spFB = 0;
    setup.sp4A = -1;
    setup.sp34 = 59.0f;
    setup.sp40 = D_800A5E14;
    setup.spEC = 1.0f;
    func_1514EC1C(func_15189FF0((s32) &setup.sp4C, &setup.spA4, &setup.sp2C, 2, 0U, 0U, 0U), (s32) arg0, 6);
    func_151D74B0((s32) arg0, 5, -1, 0xFF, 1);
}

extern f32 D_800A5E18;
extern f32 D_800A5E1C;

void func_1514E31C(void *arg0) {
    struct {
        f32 sp5C;
        f32 sp60;
        f32 sp64;
        f32 sp68;
        f32 sp6C;
        f32 sp70;
        void * sp74;
        s8 sp78;
        u8 sp79;
        s8 sp7A;
        u8 pad_7B[0x1];
        s8 sp7C;
        u8 pad_7D[0x1];
        s16 sp7E;
        s16 sp80;
        u8 pad_82[0x2];
        s32 sp84;
        s32 sp88;
        u8 sp8C;
        u8 sp8D;
        s8 sp8E;
        u8 sp8F;
        u8 pad_90[0x8];
        f32 sp98;
        f32 sp9C;
        f32 spA0;
        f32 spA4;
        f32 spA8;
        f32 spAC;
        u8 pad_B0[0xC];
        s32 spBC;
        u8 pad_C0[0x1];
        u8 spC1;
        u8 pad_C2[0x12];
        f32 spD4;
        f32 spD8;
        f32 spDC;
        f32 spE0;
        f32 spE4;
        f32 spE8;
        f32 spEC;
        f32 spF0;
        f32 spF4;
        u8 pad_F8[0x24];
        f32 sp11C;
        u8 pad_120[0x8];
        s8 sp128;
        s8 sp129;
        s8 sp12A;
        s8 sp12B;
        u8 pad_12C[4];
    } setup;

    setup.sp7C = 3;
    setup.sp84 = 0;
    setup.sp88 = 0;
    setup.spBC = 0x2012;
    setup.sp80 = 0;
    setup.spC1 = 0xFF;
    setup.sp8C = 0xFF;
    setup.sp8D = 0xE6;
    setup.sp8E = 0;
    setup.sp8F = 0xFF;
    setup.sp7E = 0x401;
    setup.sp98 = 0.0f;
    setup.sp9C = 0.0f;
    setup.spA0 = 0.0f;
    setup.spA4 = 0.0f;
    setup.spA8 = 0.0f;
    setup.spAC = 0.0f;
    setup.spD4 = 45.0f;
    setup.spE0 = 45.0f;
    setup.spE4 = 0.5f;
    setup.spE8 = 0.5f;
    setup.spF0 = 0.0f;
    setup.spD8 = 55.0f;
    setup.spDC = 25.0f;
    setup.spEC = D_800A5E18;
    setup.spF4 = D_800A5E1C;
    setup.sp79 = *(u8 *)((u8 *)arg0 + 0x3B);
    setup.sp5C = 0.0f;
    setup.sp60 = 0.0f;
    setup.sp68 = 0.0f;
    setup.sp6C = 0.0f;
    setup.sp74 = arg0;
    setup.sp78 = 0xC;
    setup.sp128 = 0;
    setup.sp129 = 0;
    setup.sp12A = 0;
    setup.sp12B = 0;
    setup.sp7A = 2;
    setup.sp64 = 100.0f;
    setup.sp70 = 600.0f;
    setup.sp11C = 1.0f;
    func_1514EC1C(func_15189FF0((s32) &setup.sp7C, &setup.spD4, &setup.sp5C, 2, 3U, 0U, 0U), (s32) arg0, 7);
    {
        f32 effect_position[3];

        effect_position[0] = 0.0f;
        effect_position[1] = 0.0f;
        effect_position[2] = 150.0f;
        func_15160A58(arg0, 0xC, effect_position, 2, 0x12C, 0x28, 0xFF, 0xB5, 0, 0xFF, 0, 2, 0, 0, 0xFF, 1);
    }
}

void * func_1518D1C0(s32, s32, s32, s32, s32, s32, void *);

void func_1514E508(s32 arg0) {
    s32 temp_v1;

    func_1514EC1C((s32) func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A58D0), arg0, 0xD);
    temp_v1 = arg0 + 0x14;
    func_1514EC1C((s32) func_1515D5F8(-0x8000, temp_v1 >> 0x10, temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0U), arg0, 0x18);
}


void * func_1518D1C0(s32, s32, s32, s32, s32, s32, void *);

void func_1514E5B8(s32 arg0) {
    s32 temp_v1;

    func_1514EC1C((s32) func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A58E4), arg0, 0xD);
    temp_v1 = arg0 + 0x14;
    func_1514EC1C((s32) func_1515D5F8(-0x8000, temp_v1 >> 0x10, temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0U), arg0, 0x18);
}


void * func_1518D1C0(s32, s32, s32, s32, s32, s32, void *);

void func_1514E668(s32 arg0) {
    s32 temp_v1;

    func_1514EC1C((s32) func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A58F8), arg0, 0xD);
    temp_v1 = arg0 + 0x14;
    func_1514EC1C((s32) func_1515D5F8(-0x8000, temp_v1 >> 0x10, temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0U), arg0, 0x18);
}


void * func_1518D1C0(s32, s32, s32, s32, s32, s32, void *);

void func_1514E718(s32 arg0) {
    s32 temp_v1;

    func_1514EC1C((s32) func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A590C), arg0, 0xE);
    temp_v1 = arg0 + 0x14;
    func_1514EC1C((s32) func_1515D5F8(-0x8000, temp_v1 >> 0x10, temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0U), arg0, 0x18);
}


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
        break;
    case 2:
        *(s32 *)((u8 *)arg0 + 0x10) &= ~1;
        break;
    case 1:
        *(s32 *)((u8 *)arg0 + 0x10) |= 1;
        break;
    default:
        return 0;
    }
    return 1;
}
s32 func_1514E89C(void *, s32, s32);
s32 func_1514E920();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514E920 CURRENT (2340) */
s32 func_1514E920(void *arg0, s32 arg1, s32 arg2) {
    s32 flags;
    void *state;
    void *object;

    state = (u8 *)arg0 + 0x110;
    switch (arg1) {
        case 0:
            flags = *(s32 *)((u8 *)arg0 + 0x10);
            if (flags & 1) {
                *(s32 *)((u8 *)arg0 + 0x10) = flags & ~1;
                object = *(void **)((u8 *)state + 0x44);
                if (object != 0) {
                    *(s8 *)((u8 *)object + 0x30) = 0;
                }
            } else {
                *(s32 *)((u8 *)arg0 + 0x10) = flags | 1;
            }
            break;
        case 1:
            *(s32 *)((u8 *)arg0 + 0x10) |= 1;
            break;
        case 2:
            *(s32 *)((u8 *)arg0 + 0x10) &= ~1;
            object = *(void **)((u8 *)state + 0x44);
            if (object != 0) {
                *(s8 *)((u8 *)object + 0x30) = 0;
            }
            break;
        default:
            return func_1514E89C(arg0, arg1, arg2);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514E920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E920.s")
void func_1514E9DC(void) {
    func_1514E920();
}
void func_1514E9FC(void *arg0, s32 arg1, s32 arg2) {
    func_1514E89C(arg0, arg1, arg2);
}
void func_1518E37C(void *, u8);

s32 func_1514EA1C(void *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
        case 3:
            if (*(u8 *)((u8 *)arg0 + 0x22) == 2) {
                func_1518E37C(arg0, 3);
            } else {
                func_1518E37C(arg0, 2);
            }
            break;
        case 4:
            func_1518E37C(arg0, 3);
            break;
        case 5:
            func_1518E37C(arg0, 2);
            break;
        case 6:
            if (*(u8 *)((u8 *)arg0 + 0x22) == 2) {
                func_1518E37C(arg0, 5);
            } else {
                func_1518E37C(arg0, 2);
            }
            break;
        case 7:
            func_1518E37C(arg0, 5);
            break;
        case 8:
            func_1518E37C(arg0, 2);
            break;
        case 9:
            if (*(u8 *)((u8 *)arg0 + 0x22) == 2) {
                func_1518E37C(arg0, 6);
            } else {
                func_1518E37C(arg0, 2);
            }
            break;
        case 10:
            func_1518E37C(arg0, 6);
            break;
        case 11:
            func_1518E37C(arg0, 2);
            break;
        case 12:
            func_1518E37C(arg0, 2);
            break;
        default:
            return func_1514E89C(arg0, arg1, arg2);
    }
    return 1;
}
void func_1514EB6C(void *arg0, s32 arg1, s32 arg2) {
    func_1514E89C(arg0, arg1, arg2);
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
s32 func_1514EC1C(s32 arg0, s32 arg1, s16 arg2) {
    Game179F30Effect *var_t0;
    s16 temp_v0_2;

    var_t0 = 0;
    if (arg0 != 0) {
        var_t0 = func_1514EBA4((void *)arg0, arg2, 0);
        if (var_t0 != 0) {
            var_t0->field_14 = *(Game179F30Effect **)((u8 *)arg1 + 0x2F4);
            *(Game179F30Effect **)((u8 *)arg1 + 0x2F4) = var_t0;
            var_t0->field_18 = 0;
            if (var_t0->field_14 != 0) {
                *(void **)((u8 *)var_t0->field_14 + 0x18) = var_t0;
            }
        } else {
            temp_v0_2 = D_8008ABE8[arg2]->dispatch_id;
            if (temp_v0_2 != -1) {
                D_8008AB58[temp_v0_2](arg0);
            } else {
                func_1516972C((void *)arg0);
            }
        }
    }
    return (s32)var_t0;
}
s32 func_1514ECE0(void *arg0, s16 arg1, void **arg2) {
    s32 var_v1;
    void *var_v0;
    void *next;

    var_v1 = 0;
    var_v0 = arg0;
    while ((var_v0 != 0) && (var_v1 == 0)) {
        next = *(void **)((u8 *)var_v0 + 0x14);
        if (arg1 == *(s16 *)((u8 *)var_v0 + 0x1C)) {
            var_v1 = 1;
        } else {
            var_v0 = next;
        }
    }
    if (arg2 != 0) {
        *arg2 = var_v0;
    }
    return var_v1;
}
s32 func_1514ED3C(void *arg0, s32 arg1, void **arg2) {
    s32 var_v1;
    void *var_v0;
    void *next;

    var_v1 = 0;
    var_v0 = arg0;
    while ((var_v0 != 0) && (var_v1 == 0)) {
        next = *(void **)((u8 *)var_v0 + 0x14);
        if (arg1 == *(s32 *)((u8 *)var_v0 + 0x10)) {
            var_v1 = 1;
        } else {
            var_v0 = next;
        }
    }
    if (arg2 != 0) {
        *arg2 = var_v0;
    }
    return var_v1;
}
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

void func_1514EDF0(s32 arg0, void *arg1) {
    s32 temp_v0;
    void *var_s1;

    var_s1 = *(void **)((u8 *)arg1 + 0x2F4);
    {
        void *sp34 = 0;
        u8 loop_flag;
        do {
            temp_v0 = func_1514ED3C(var_s1, arg0, &sp34);
            loop_flag = temp_v0;
            if (temp_v0 != 0) {
                var_s1 = *(void **)((u8 *)sp34 + 0x14);
                func_1514ED8C(sp34, arg1);
            }
        } while (loop_flag != 0);
    }
}
void *func_1515BE50(void *, s32, s32, s32);

void func_1514EE70(u8 *arg0) {
    struct {
        void *field_0;
        u8 field_4;
        u8 field_5;
        s16 field_6;
    } sp20;
    void *temp_v0;

    sp20.field_0 = arg0;
    sp20.field_4 = arg0[0x3B];
    sp20.field_5 = 0;
    sp20.field_6 = 0x12C;
    temp_v0 = func_1515BE50(&sp20, 0, 0xFF, 1);
    func_1514EC1C((s32)temp_v0, (s32)arg0, 0x16);
}
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
void func_151BB044(void *);
void func_151BC074(s32);
void func_151BD2F8(void *, s32, s32);
void func_151B9F00(void *, s32, s32);
extern u8 D_800A5958;
extern u8 D_800A5964;
extern u8 D_800BE616;

void func_1514F194(void *arg0) {
    void *effect;

    func_151D0F60(arg0, 1, 0xFF, 1);
    func_151D0F60(arg0, 2, 0xFF, 1);
    func_151BB044(arg0);
    if (D_800BE616 == 0) {
        func_151BC074((s32)arg0);
    }
    func_151BD2F8(arg0, 0xFF, 1);
    func_151B9F00(arg0, 0xFF, 1);
    func_15160A58(arg0, 1, &D_800A5958, 2,
                   0x12C, 0xC, 0xFF, 0xFF, 0xFF, 2, 0, -1, 0, 0, 0xFF, 1);
    effect = func_15160A58(arg0, 1, &D_800A5964, 2,
                            0x12C, 0xF, 0xFF, 0, 0, 0xFF, 1, -1, 0, 0, 0xFF, 1);
    if (effect != 0) {
        func_1514EC1C((s32)effect, (s32)arg0, 0x19);
    }
}
void func_15160CDC(s32, s32, void *, void *, f32, s32, s32, s32, s32, s32,
    s32, s32, s32, s32, s32, s32);
extern s32 D_800A5970[];
extern s32 D_800A597C[];
extern f32 D_800A5E58;

typedef struct {
    s32 first;
    s32 second;
    s32 third;
} Game179F30Vec3;

void func_1514F308(s32 arg0) {
    Game179F30Vec3 sp54;
    Game179F30Vec3 sp48;

    sp54 = *(Game179F30Vec3 *)D_800A5970;
    sp48 = *(Game179F30Vec3 *)D_800A597C;
    func_15160CDC(arg0, 5, &sp54, &sp48, D_800A5E58, 2, 0x12C, 0xFF,
        0xFF, 0xFF, 0xFF, 1, 0, 0, 0xFF, 1);
}
typedef struct Game179F30F3CCPacket {
    void *actor;
    u8 type;
    u8 pad5[3];
    f32 value;
} Game179F30F3CCPacket;

void *func_15149130(s16, s8, s8, s8, u8, u8, s32, u8, s32);

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
