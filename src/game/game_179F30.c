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
 * - func_1514DE94
 * - func_1514E00C
 * - func_1514E194
 * - func_1514E31C
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514D4B8 CURRENT (8) */
s32 func_1514D4B8(s16 arg0, s16 arg1) {
    register Game179F30DispatchEntry **temp_v1;

    if (arg0 == -1) {
        return 0;
    }
    if (arg0 == arg1) {
        return 1;
    }
    temp_v1 = &D_8008ABE8[arg0];
    if (func_1514D4B8(*(s16 *)((u8 *)*temp_v1 + 6), arg1) != 0) {
        return 1;
    }
    if (func_1514D4B8(*(s16 *)((u8 *)*temp_v1 + 4), arg1) != 0) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514D4B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D4B8.s")
void func_10022EC0(void *, void *, s32);
s32 func_1514EC1C(s32, s32, s32);
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
    s32 sp30;
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
} Game179F30Setup;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514D564 CURRENT (2281) */
void func_1514D564(u8 *arg0) {
    Game179F30Setup setup;
    s32 temp_v0;

    setup.sp1C = arg0;
    setup.sp21 = 6;
    setup.sp4C = 1;
    setup.sp28 = -180.0f;
    setup.sp20 = arg0[0x3B];
    setup.sp2C = 77.0f;
    setup.sp34 = D_800A5DE4;
    setup.sp38 = D_800A5DE8;
    setup.sp24 = 0.0f;
    setup.sp3C = D_800A5DEC;
    setup.sp40 = *(f32 *)(arg0 + 0x14);
    setup.sp44 = *(f32 *)(arg0 + 0x18);
    setup.sp54 = 1;
    setup.sp50 = D_800A5DF0;
    setup.sp48 = *(f32 *)(arg0 + 0x1C);
    temp_v0 = func_150C5370(&setup.sp34, 0x14);
    if (temp_v0 != 0) {
        setup.sp30 = temp_v0;
        func_10022EC0((void *)(temp_v0 + 0xC8), (void *)&setup.sp1C, 0x14);
        func_1514EC1C(setup.sp30, (s32)arg0, 0x15);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514D564 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D564.s")
/* Raw US callees establish pointer arguments and the stack byte parameters. */
s32 func_15189FF0(s32, void *, void *, s32, u8, u8, u8);
void *func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);
extern u8 D_800A58D0[];
extern u8 D_800A58E4[];
extern u8 D_800A58F8[];
extern u8 D_800A590C[];

s32 func_1514EC1C(s32, s32, s32);
void func_15160A58(void *, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A5DF4;
extern f32 D_800A5DF8;
extern f32 D_800A5DFC;
extern f32 D_800A5E00;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514D64C CURRENT (8069) */
void func_1514D64C(void *arg0) {
    struct {
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
        s8 sp84;
        s8 sp85;
        s8 sp86;
        s8 sp87;
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
        s8 spB9;
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
    } setup;

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
    func_1514EC1C(func_15189FF0((s32) &setup.sp74, &setup.spCC, &setup.sp54, 2, 0U, 0U, 0U), (s32) arg0, 9);
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
    func_1514EC1C(func_15189FF0((s32) &setup.sp74, &setup.spCC, &setup.sp54, 2, 0U, 0U, 0U), (s32) arg0, 0xA);
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
extern s32 func_1514EC1C(s32 arg0, s32 arg1, s32 arg2);

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

void func_15083568(void *, s32, s32, s32);

void func_1514DCAC(void *arg0) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DE94.s")
/* Call context: func_15083FB0: unique active project prototype */
u8 func_15083FB0(u8);

void func_1514DFD0(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x65) = (s8) (func_15083FB0(9U) + 1);
    *(u8 *)((u8 *)arg0 + 0x101) = (u8) (*(u8 *)((u8 *)arg0 + 0x101) | 0x34);
}
void func_151D74B0(s32, s32, s32, s32, s32);
extern f32 D_800A5E08;
extern f32 D_800A5E0C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514E00C CURRENT (3750) */
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
        s8 sp5C;
        s8 sp5D;
        s8 sp5E;
        s8 sp5F;
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
        s8 sp91;
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
    setup.sp2C = 35.0f;
    setup.sp30 = 27.0f;
    setup.sp38 = 35.0f;
    setup.sp3C = 27.0f;
    setup.sp48 = 6;
    setup.spF8 = 0;
    setup.spF9 = 0;
    setup.spFA = 0;
    setup.spFB = 0;
    setup.sp4A = -1;
    setup.sp49 = *(u8 *)((u8 *)arg0 + 0x3B);
    setup.sp34 = 59.0f;
    setup.sp40 = D_800A5E0C;
    setup.sp44 = arg0;
    setup.spEC = 1.0f;
    func_1514EC1C(func_15189FF0((s32) &setup.sp4C, &setup.spA4, &setup.sp2C, 2, 0U, 0U, 0U), (s32) arg0, 6);
    func_151D74B0((s32) arg0, 5, -1, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514E00C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E00C.s")

void func_151D74B0(s32, s32, s32, s32, s32);
extern f32 D_800A5E10;
extern f32 D_800A5E14;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514E194 CURRENT (3750) */
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
        s8 sp5C;
        s8 sp5D;
        s8 sp5E;
        s8 sp5F;
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
        s8 sp91;
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
    setup.sp2C = 35.0f;
    setup.sp30 = 27.0f;
    setup.sp38 = 35.0f;
    setup.sp3C = 27.0f;
    setup.sp48 = 6;
    setup.spF8 = 0;
    setup.spF9 = 0;
    setup.spFA = 0;
    setup.spFB = 0;
    setup.sp4A = -1;
    setup.sp49 = *(u8 *)((u8 *)arg0 + 0x3B);
    setup.sp34 = 59.0f;
    setup.sp40 = D_800A5E14;
    setup.sp44 = arg0;
    setup.spEC = 1.0f;
    func_1514EC1C(func_15189FF0((s32) &setup.sp4C, &setup.spA4, &setup.sp2C, 2, 0U, 0U, 0U), (s32) arg0, 6);
    func_151D74B0((s32) arg0, 5, -1, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514E194 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E194.s")

extern f32 D_800A5E18;
extern f32 D_800A5E1C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514E31C CURRENT (4194) */
void func_1514E31C(void *arg0) {
    struct {
        f32 sp50;
        f32 sp54;
        f32 sp58;
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
        s8 sp8C;
        s8 sp8D;
        s8 sp8E;
        s8 sp8F;
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
        s8 spC1;
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
    setup.sp5C = 0.0f;
    setup.sp60 = 0.0f;
    setup.sp68 = 0.0f;
    setup.sp6C = 0.0f;
    setup.sp78 = 0xC;
    setup.sp128 = 0;
    setup.sp129 = 0;
    setup.sp12A = 0;
    setup.sp12B = 0;
    setup.sp7A = 2;
    setup.sp79 = *(u8 *)((u8 *)arg0 + 0x3B);
    setup.sp64 = 100.0f;
    setup.sp70 = 600.0f;
    setup.sp74 = arg0;
    setup.sp11C = 1.0f;
    func_1514EC1C(func_15189FF0((s32) &setup.sp7C, &setup.spD4, &setup.sp5C, 2, 3U, 0U, 0U), (s32) arg0, 7);
    setup.sp50 = 0.0f;
    setup.sp54 = 0.0f;
    setup.sp58 = 150.0f;
    func_15160A58(arg0, 0xC, &setup.sp50, 2, 0x12C, 0x28, 0xFF, 0xB5, 0, 0xFF, 0, 2, 0, 0, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514E31C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E31C.s")

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
void func_1514E920();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514E920 CURRENT (4345) */
void func_1514E920(void *arg0, s32 arg1, s32 arg2) {
    s32 flags;
    void *state;
    void *object;

    state = (u8 *)arg0 + 0x110;
    if (arg1 == 0) {
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
        return;
    }
    if (arg1 == 1) {
        *(s32 *)((u8 *)arg0 + 0x10) |= 1;
        return;
    }
    if (arg1 == 2) {
        *(s32 *)((u8 *)arg0 + 0x10) &= ~1;
        object = *(void **)((u8 *)state + 0x44);
        if (object != 0) {
            *(s8 *)((u8 *)object + 0x30) = 0;
        }
        return;
    }
    func_1514E89C(arg0, arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514E920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E920.s")
void func_1514E9DC(void) {
    func_1514E920();
}
void func_1514E9FC(void *arg0, s32 arg1, s32 arg2) {
    func_1514E89C(arg0, arg1, arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EA1C.s")
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514EC1C CURRENT (1147) */
s32 func_1514EC1C(s32 arg0, s32 arg1, s32 arg2) {
    Game179F30Effect *sp1C;
    Game179F30Effect *temp_v0;
    Game179F30Effect *var_t0;
    s16 temp_v0_2;
    void *temp_v1;

    var_t0 = 0;
    if (arg0 != 0) {
        temp_v0 = func_1514EBA4((void *)arg0, (s16)arg2, 0);
        var_t0 = temp_v0;
        if (temp_v0 != 0) {
            temp_v0->field_14 = *(Game179F30Effect **)((u8 *)arg1 + 0x2F4);
            *(Game179F30Effect **)((u8 *)arg1 + 0x2F4) = temp_v0;
            temp_v1 = temp_v0->field_14;
            temp_v0->field_18 = 0;
            if (temp_v1 != 0) {
                *(void **)((u8 *)temp_v1 + 0x18) = temp_v0;
            }
        } else {
            temp_v0_2 = D_8008ABE8[(s16)arg2]->dispatch_id;
            if (temp_v0_2 != -1) {
                sp1C = var_t0;
                D_8008AB58[temp_v0_2](arg0);
            } else {
                sp1C = var_t0;
                func_1516972C((void *)arg0);
            }
            var_t0 = sp1C;
        }
    }
    return (s32)var_t0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514EC1C */
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
void func_15160CDC(s32, s32, void *, void *, f32, s32, s32, s32, s32, s32,
    s32, s32, s32, s32, s32, s32);
extern s32 D_800A5970[];
extern s32 D_800A597C[];
extern f32 D_800A5E58;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514F308 CURRENT (3856) */
void func_1514F308(s32 arg0) {
    struct {
        s32 first;
        s32 second;
        s32 third;
    } sp54;
    struct {
        s32 first;
        s32 second;
        s32 third;
    } sp48;

    sp54.first = D_800A5970[0];
    sp54.second = D_800A5970[1];
    sp54.third = D_800A5970[2];
    sp48.first = D_800A597C[0];
    sp48.second = D_800A597C[1];
    sp48.third = D_800A597C[2];
    func_15160CDC(arg0, 5, &sp54, &sp48, D_800A5E58, 2, 0x12C, 0xFF,
        0xFF, 0xFF, 0xFF, 1, 0, 0, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514F308 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F308.s")
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
