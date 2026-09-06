#include "types.h"

/*
 * Reviewed source unit: src/game/game_11D830.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F0390
 * - func_150F03BC
 * - func_150F03F8
 * - func_150F07E4
 * - func_150F088C
 * - func_150F0938
 * - func_150F0A24
 * - func_150F0BEC
 * - func_150F0E48
 * - func_150F1020
 * - func_150F10D4
 * - func_150F1170
 * - func_150F15F8
 * - func_150F1684
 * - func_150F16DC
 * - func_150F1A00
 * - func_150F1B48
 * - func_150F1CB0
 * - func_150F1D10
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game11D830Inner {
    u8 pad0[0x138];
    s32 field_138;
} Game11D830Inner;

typedef struct Game11D830Object {
    u8 pad0[0x178];
    Game11D830Inner *inner;
} Game11D830Object;

typedef struct Game11D830AltInner {
    u8 pad0[0x13C];
    s32 field_13C;
} Game11D830AltInner;

typedef struct Game11D830AltObject {
    u8 pad0[0x18];
    Game11D830AltInner *inner;
} Game11D830AltObject;

Game11D830Inner *func_150F0380(Game11D830Object *arg0) {
    Game11D830Inner *inner = arg0->inner;

    inner->field_138 = 0;
    return inner;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0390.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F03BC.s")
Game11D830AltInner *func_150F03E8(Game11D830AltObject *arg0) {
    Game11D830AltInner *inner = arg0->inner;

    inner->field_13C = 0;
    return inner;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F03F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F07E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F088C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0938.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0A24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0BEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F0E48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1020.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F10D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1170.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F15F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1684.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F16DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1A00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1B48.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F1CB0 CURRENT (460) */
void func_150F1CB0(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0x84) == 0x14) {
        *(s8 *)((u8 *)arg0 + 0x68) = 0x1B;
    } else {
        *(s8 *)((u8 *)arg0 + 0x68) = 0xC;
    }
    *(s8 *)((u8 *)arg0 + 0x69) = 0x13;
    if ((*(s32 *)((u8 *)arg0 + 0x2E4) & 3) == 3) {
        *(s8 *)((u8 *)arg0 + 0x69) = 0x14;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x2E4) & 0xC) == 0xC) {
        *(s8 *)((u8 *)arg0 + 0x69) = 0x17;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F1CB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1CB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D830/func_150F1D10.s")
