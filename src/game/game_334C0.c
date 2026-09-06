#include "types.h"

/*
 * Reviewed source unit: src/game/game_334C0.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15006010
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game334C0State {
    u8 pad0[0x84];
    volatile s32 flags;
    u8 pad1[0x104];
    f32 unk18C;
    f32 unk190;
    u8 pad2[0x20];
    s16 unk1B4;
    u8 pad3[0x2A];
    s16 unk1E0;
    u8 pad4[0x5C];
    u8 unk23E;
    u8 pad5[0x109];
    f32 unk348;
    f32 unk34C;
    u8 pad6[0x24];
    f32 unk374;
    u8 pad7[0x58];
    struct Game334C0Child *child3D0;
} Game334C0State;

typedef struct Game334C0Child {
    u8 pad0[0x102];
    u8 unk102;
} Game334C0Child;

s32 func_15123934(Game334C0State *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_151239CC(Game334C0State *arg0, s32 arg1);
void func_15124B18();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15006010 CURRENT (105) */
void func_15006010(Game334C0State *arg0) {
    s32 firstFlags;
    s32 secondFlags;

    if (arg0->child3D0->unk102 != 0) {
        if (func_15123934(arg0, 8, 0, 0, 0) != 0) {
            firstFlags = arg0->flags | 0x100000;
            arg0->flags = firstFlags;
            arg0->flags = firstFlags & ~4;
            arg0->unk1B4 = 1;
            arg0->unk1E0 = 3;
            func_15124B18(arg0);
        }
        arg0->unk348 = 143.0f;
        arg0->unk34C = 143.0f;
        arg0->unk374 = 150.0f;
        arg0->unk190 = -38.0f;
        return;
    }

    if (arg0->unk23E == 0x3B) {
        if (func_15123934(arg0, 8, 0, 0, 0) != 0) {
            secondFlags = arg0->flags | 0x100000;
            arg0->flags = secondFlags;
            arg0->flags = secondFlags & ~4;
            arg0->unk348 = 155.0f;
            arg0->unk34C = 155.0f;
            arg0->unk190 = 30.0f;
            arg0->unk18C = 30.0f;
            arg0->unk374 = 178.0f;
        }
    } else {
        func_151239CC(arg0, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15006010 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_334C0/func_15006010.s")

void func_15006140(Game334C0State *arg0) {
    arg0->unk1E0 = 5;
    arg0->unk1B4 = 2;
    func_15124B18();
}
