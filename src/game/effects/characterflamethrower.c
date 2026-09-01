#include "types.h"

/*
 * Reviewed source unit: src/game/effects/characterflamethrower.c
 * Boundary evidence: docs/evidence/effects_characterflamethrower.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151957B0
 * - func_1519582C
 * - func_15195868
 * - func_15195984
 * - func_15195AA8
 * - func_15195D00
 * - func_15195DD4
 * - func_15195FF0
 * - func_15196318
 * - func_15196330
 * - func_151963B4
 * - func_15196438
 * - func_15196748
 * - func_15196B4C
 * - func_15197148
 * - func_15197A0C
 * - func_15197AB4
 * - func_15197BBC
 * - func_15197C10
 * - func_15198054
 * - func_15198110
 * - func_15198570
 * - func_151987CC
 * - func_1519897C
 * - func_15198C90
 * - func_15198D40
 * - func_15198D88
 * - func_151990AC
 * - func_151993E4
 * - func_1519944C
 * - func_151994B8
 * - func_1519986C
 * - func_15199980
 * - func_15199A10
 * - func_15199C34
 * - func_1519A9A4
 * - func_1519B4B8
 * - func_1519BE1C
 * - func_1519BEB8
 * - func_1519BF20
 * - func_1519BFBC
 * - func_1519C09C
 * - func_1519C258
 * - func_1519C26C
 * - func_1519C4E4
 * - func_1519C56C
 * - func_1519C9C4
 * - func_1519CD64
 * - func_1519CDB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_800A8AA4;
extern s32 D_800E08E0;
extern s32 D_800E08E4;
extern s32 D_800E08E8;
extern s32 D_800E08EC;
extern s32 D_800E08F0;

void func_1519CDB0(s32 arg0, f32 arg1, s32 arg2);
void func_10010F30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_151478F4(s32 arg0);
void func_15147928(s32 arg0);
void func_15199980(s32 arg0);
void func_100111C8(s32 arg0, u16 arg1);
void func_15195DD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

typedef struct CharacterFlamethrowerDispatch {
    char pad0[0x1C];
    s32 unk1C;
} CharacterFlamethrowerDispatch;

typedef struct CharacterFlamethrowerIdentity {
    char pad0[0x84];
    u16 unk84;
} CharacterFlamethrowerIdentity;

typedef struct CharacterFlamethrowerState {
    CharacterFlamethrowerIdentity *identity;
    char pad4[0x2];
    u8 flags6;
    char pad7[0x5F];
    u16 unk66;
    char pad68[0xC8];
    u16 unk130;
    char pad132[0x16];
    s32 unk148;
    char pad14C[0xC];
    s32 unk158;
    s32 unk15C;
} CharacterFlamethrowerState;

typedef struct CharacterFlamethrowerActor {
    char pad0[0x1E];
    u16 flags1E;
    char pad20[0xC];
    s8 unk2C;
    char pad2D[0x3];
    s8 unk30;
    char pad31[0xA];
    u8 unk3B;
    char pad3C[0x5C];
    CharacterFlamethrowerState *state;
} CharacterFlamethrowerActor;

typedef struct CharacterFlamethrowerContext {
    char pad0[0x38];
    CharacterFlamethrowerActor *actor;
} CharacterFlamethrowerContext;

typedef struct CharacterFlamethrowerControl {
    char pad0[0x12];
    char unk12;
    char unk13;
} CharacterFlamethrowerControl;

typedef struct CharacterFlamethrowerLocal {
    CharacterFlamethrowerActor *actor;
    u8 unk4;
} CharacterFlamethrowerLocal;

void func_15147D64(void *arg0, s32 arg1, CharacterFlamethrowerActor *arg2);

void func_151617C4();
void func_151617E4();
void func_1519C258(CharacterFlamethrowerContext *arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151957B0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519582C CURRENT (450) */
void func_1519582C(void) {
    D_800E08E4 = 0;
    D_800E08E0 = 0;
    D_800E08EC = 0;
    D_800E08E8 = 0;
    D_800E08F0 = -2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519582C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519582C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195868.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195984.s")
s16 func_15195A84(s16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195AA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195D00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195DD4.s")

void func_15195FB0(
    CharacterFlamethrowerDispatch *arg0,
    s32 arg1,
    s32 arg2,
    s32 arg3,
    s32 arg4,
    s32 arg5,
    s32 arg6
) {
    func_15195DD4(arg0->unk1C, arg1, arg2, arg3, arg4, arg5, arg6);
}

#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195FF0.s")
void func_15196318(CharacterFlamethrowerControl *arg0, s32 arg1, s32 arg2) {
    if (arg0 != 0) {
        arg0->unk12 = arg1;
        arg0->unk13 = arg2;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15196330.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151963B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15196438.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15196748.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15196B4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197148.s")
f32 func_151979F8(s32 arg0) {
    return D_800A8AA4;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197A0C.s")

extern f32 D_800A8AAC;

f32 func_15197A68(s32 arg0) {
    return D_800A8AAC;
}

void func_15197A7C(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerLocal sp18;

    if (arg0 != 0) {
        sp18.actor = arg0;
        sp18.unk4 = arg0->unk3B;
        func_15147D64(&sp18, 8, arg0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197AB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197BBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197C10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198054.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198110.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198570.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151987CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519897C.s")
void func_15198C60(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198C90.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15198D40 */
void func_15198D40(CharacterFlamethrowerActor *arg0, s32 arg1) {
    CharacterFlamethrowerState *temp_v0 = arg0->state;
    u16 temp_a0;

    if (arg0->unk2C != 0) {
        temp_a0 = temp_v0->unk66;
        if (temp_a0 != 0) {
            func_100111C8(temp_a0, arg1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15198D40 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198D40.s")

void func_15198D7C(s32 arg0) {

}

#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198D88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151990AC.s")
void func_151993B4(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerState *state = arg0->state;

    arg0->unk30 = 0;
    arg0->flags1E &= 0xFFFD;
    state->flags6 |= 1;
    state->flags6 |= 4;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151993E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519944C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151994B8.s")
void func_15199834(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerLocal sp18;

    if (arg0 != 0) {
        sp18.actor = arg0;
        sp18.unk4 = arg0->unk3B;
        func_15147D64(&sp18, 0x26, arg0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519986C.s")
void func_15199928(s32 arg0) {
    func_15199980(arg0);
    func_151478F4(arg0);
}
void func_15199954(s32 arg0) {
    func_15199980(arg0);
    func_15147928(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199980.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199A10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199C34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519A9A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519B4B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519BE1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519BEB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519BF20.s")
void func_1519BF8C(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519BFBC.s")
void func_1519C06C(CharacterFlamethrowerActor *arg0) {
    register CharacterFlamethrowerState *temp_v0 = arg0->state;
    u16 temp_a1 = temp_v0->unk130;

    if (temp_a1 != 0) {
        func_100111C8(temp_a1 & 0xFFFF, temp_a1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C09C.s")
void func_1519C200(CharacterFlamethrowerContext *arg0) {
    func_1519C258(arg0);
    func_151617C4(arg0);
}
void func_1519C22C(CharacterFlamethrowerContext *arg0) {
    func_1519C258(arg0);
    func_151617E4(arg0);
}
void func_1519C258(CharacterFlamethrowerContext *arg0) {
    void *state = arg0->actor->state;

    ((CharacterFlamethrowerState *)state)->unk148 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C26C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C4E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C56C.s")
s32 func_1519C910(CharacterFlamethrowerActor *arg0) {
    register CharacterFlamethrowerState *temp_v0 = arg0->state;
    register CharacterFlamethrowerIdentity *temp_v1 = temp_v0->identity;
    u16 temp_a1 = temp_v1->unk84;

    if ((temp_a1 != temp_v0->unk158) && (temp_a1 != temp_v0->unk15C)) {
        return 0;
    }
    return 1;
}
s32 func_1519C948(s32 arg0) {
    func_1519CDB0(arg0, 0.25f, 0x1C);
    return 0;
}
s32 func_1519C970(s32 arg0) {
    func_1519CDB0(arg0, 0.5f, 0x1D);
    return 0;
}
s32 func_1519C998(s32 arg0) {
    func_1519CDB0(arg0, 0.2f, 0x1D);
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C9C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519CD64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519CDB0.s")
