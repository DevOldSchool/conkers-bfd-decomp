#include "types.h"

/*
 * Reviewed source unit: src/game/game_AD9B0.c
 * Boundary evidence: docs/evidence/game_raw_periodic_actor_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15080500
 * - func_15080620
 * - func_15080784
 * - func_15080828
 * - func_15080BE8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080500.s")
extern void * D_800CC5EC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15080620 CURRENT (1819) */
void func_15080620(s32 arg0, s32 arg1, s8 arg2, s32 arg3) {
    s8 var_a2;

    var_a2 = arg2;
    if (var_a2 != 0) {
        var_a2 |= 0x80;
    }
    if (arg1 == 0) {
        *(s8 *)((u8 *)*(&D_800CC5EC + (arg0 * 0x32C)) + 0x74) = var_a2;
        return;
    }
    *(s8 *)((u8 *)*(&D_800CC5EC + (arg0 * 0x32C)) + 0x75) = var_a2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15080620 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080620.s")
typedef struct GameAD9B0Nested {
    u8 pad0[0x74];
    u8 field_74;
    u8 field_75;
} GameAD9B0Nested;

typedef struct GameAD9B0Actor {
    u8 pad0[0x31C];
    GameAD9B0Nested *nested;
    u8 pad320[0xC];
} GameAD9B0Actor;

extern GameAD9B0Actor D_800CC2D0[];

void func_150806A8(s32 arg0) {
    GameAD9B0Actor *actor;
    GameAD9B0Nested *nested;
    u8 value_74;
    u8 value_75;

    actor = &D_800CC2D0[arg0];
    nested = actor->nested;
    value_74 = nested->field_74;
    if ((value_74 != 0) && !(value_74 & 0x80)) {
        nested->field_74 = 0;
    }
    nested = actor->nested;
    value_75 = nested->field_75;
    if ((value_75 != 0) && !(value_75 & 0x80)) {
        nested->field_75 = 0;
    }
}
void func_15080718(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg2 = 1 << (arg0 & 7);
    *arg1 = arg0 >> 3;
}
extern u8 D_800BE580[];

s32 func_15080738(s32 arg0) {
    s32 sp1C;
    s32 sp18;

    func_15080718(arg0, &sp1C, &sp18);
    if (D_800BE580[sp1C] & sp18) {
        return 1;
    }
    return 0;
}
void func_1001263C(s32, s32, s32);
extern u8 D_800D1994;
extern u8 D_800D1995;
extern u16 *D_800D1998;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15080784 CURRENT (110) */
void func_15080784(void) {
    s32 value;

    if (D_800D1998 != 0) {
        if (D_800D1995 != D_800D1994) {
            value = D_800D1998[D_800D1994];
            if (value != 0) {
                func_1001263C(value, 0x7FFF, 0x40);
            }
            D_800D1994++;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15080784 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080784.s")

void func_150807F4(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 0x20) {
        func_15080784();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080828.s")
void func_10004074(s32);
void func_1516D2E0(void *);
void func_151F2D6C(s32, s32);
extern u8 D_800D1941;
extern s32 D_800D1944;
extern void *D_800D1948;
extern s32 D_800D194C;
extern void *D_800D1950;
extern void *D_800D199C;
extern u8 D_800D2E60[];
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15080BE8 CURRENT (220) */
void func_15080BE8(void) {
    void *resource;

    D_800D1941 = 0;
    func_1516D2E0((void *)D_800D1950);
    func_10004074(D_800D1944);
    resource = D_800D1948;
    if (resource != 0) {
        func_10004074((s32)resource);
        func_10004074(D_800D194C);
        func_10004074((s32)D_800D1998);
        D_800D1948 = 0;
    }
    func_151F2D6C(0, 0x5622);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15080BE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080BE8.s")
void func_15080BE8(void);

void func_15080C64(void) {
    if ((D_800D1941 != 0) && (*(u8 *)((u8 *)D_800D1950 + 0x15) == 0)) {
        func_15080BE8();
        if ((D_800BE9F0 != 0x29) && (D_800BE9F0 != 0x2E)) {
            D_800D2E60[8] = (u8)(D_800D2E60[8] | 0x10);
        }
        if (D_800D199C != 0) {
            *(u8 *)((u8 *)D_800D199C + 0x14) = 1;
            D_800D199C = 0;
        }
    }
}

s32 func_15080CF4(void) {
    if (D_800D1941 == 0) {
        return 1;
    }
    return 0;
}
