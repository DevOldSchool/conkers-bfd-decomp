#include "types.h"

extern f32 D_800A8AA4;

void func_1519CDB0(s32 arg0, f32 arg1, s32 arg2);

typedef struct CharacterFlamethrowerState {
    char pad0[0x148];
    s32 unk148;
} CharacterFlamethrowerState;

typedef struct CharacterFlamethrowerActor {
    char pad0[0x98];
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

/*
 * Reviewed source unit: src/game/effects/characterflamethrower.c
 * Boundary evidence: docs/evidence/effects_characterflamethrower.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151957B0
 * - func_1519582C
 * - func_15195868
 * - func_15195984
 * - func_15195A84
 * - func_15195AA8
 * - func_15195D00
 * - func_15195DD4
 * - func_15195FB0
 * - func_15195FF0
 * - func_15196318
 * - func_15196330
 * - func_151963B4
 * - func_15196438
 * - func_15196748
 * - func_15196B4C
 * - func_15197148
 * - func_15197A0C
 * - func_15197A7C
 * - func_15197AB4
 * - func_15197BBC
 * - func_15197C10
 * - func_15198054
 * - func_15198110
 * - func_15198570
 * - func_151987CC
 * - func_1519897C
 * - func_15198C60
 * - func_15198C90
 * - func_15198D40
 * - func_15198D88
 * - func_151990AC
 * - func_151993B4
 * - func_151993E4
 * - func_1519944C
 * - func_151994B8
 * - func_15199834
 * - func_1519986C
 * - func_15199928
 * - func_15199954
 * - func_15199980
 * - func_15199A10
 * - func_15199C34
 * - func_1519A9A4
 * - func_1519B4B8
 * - func_1519BE1C
 * - func_1519BEB8
 * - func_1519BF20
 * - func_1519BF8C
 * - func_1519BFBC
 * - func_1519C06C
 * - func_1519C09C
 * - func_1519C200
 * - func_1519C22C
 * - func_1519C258
 * - func_1519C26C
 * - func_1519C4E4
 * - func_1519C56C
 * - func_1519C910
 * - func_1519C970
 * - func_1519C998
 * - func_1519C9C4
 * - func_1519CD64
 * - func_1519CDB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151957B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519582C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195868.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195984.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195A84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195AA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195D00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195DD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195FB0.s")
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

#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197A7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197AB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197BBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197C10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198054.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198110.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198570.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151987CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519897C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198C60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198C90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198D40.s")

void func_15198D7C(s32 arg0) {

}

#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198D88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151990AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151993B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151993E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519944C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151994B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199834.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519986C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199928.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199954.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199980.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199A10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199C34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519A9A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519B4B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519BE1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519BEB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519BF20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519BF8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519BFBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C06C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C09C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C200.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C22C.s")
void func_1519C258(CharacterFlamethrowerContext *arg0) {
    void *state = arg0->actor->state;

    ((CharacterFlamethrowerState *)state)->unk148 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C26C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C4E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C56C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C910.s")
s32 func_1519C948(s32 arg0) {
    func_1519CDB0(arg0, 0.25f, 0x1C);
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C998.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C9C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519CD64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519CDB0.s")
