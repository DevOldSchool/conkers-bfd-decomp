#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BB950.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518E5D8
 * - func_1518E73C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1514EDF0(s32 arg0, s32 arg1);
void func_1518E308(void *arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_1518E4A0(void *arg0) {
    func_1518E308(arg0);
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x18));
}
void func_1518E4CC(void *arg0) {
    func_1518E4A0(arg0);
    func_15169804((s32) arg0);
}
void func_1518E4F8(void *arg0) {
    func_1518E4A0(arg0);
    func_15169824((s32) arg0);
}
s32 func_150ADA20();                                /* extern */

void func_1518E524(s8 *arg0, u8 *arg1, s8 *arg2, s8 *arg3, s8 *arg4, u8 *arg5, s16 *arg6) {
    s32 temp_v1;

    *arg1 = 2;
    if (func_150ADA20() & 1) {
        *arg1 |= 1;
    }
    temp_v1 = func_150ADA20() & 1;
    switch (temp_v1) {                              /* irregular */
    case 0:
        *arg0 = 0x13;
        break;
    case 1:
        *arg0 = 0x14;
        break;
    }
    *arg2 = 0;
    *arg3 = 0;
    *arg4 = 0;
    *arg5 = 0xFF;
    *arg6 = 0x301;
}
/* Call context: func_151429E0: unique active project prototype */
void func_151429E0(u8, u8 *, u8 *, u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518E5D8 CURRENT (460) */
void func_1518E5D8(s8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, s8 *arg5, s16 *arg6) {
    s32 var_v0;

    if (func_150ADA20() & 1) {
        *arg1 |= 1;
    }
    *arg0 = 0x16;
    if (func_150ADA20() & 1) {
        var_v0 = 3;
    } else {
        var_v0 = 4;
    }
    func_151429E0(var_v0 & 0xFF, arg2, arg3, arg4);
    *arg5 = 0xC8;
    *arg6 = 0x401;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518E5D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BB950/func_1518E5D8.s")
typedef struct Game1BB950State {
    u8 pad0;
    u8 variant;
    u8 pad2[0xA];
    u8 intensity;
    u8 padD[0xB];
    s32 owner;
    u8 pad1C[2];
    s16 timer;
    u8 pad20;
    s8 callback;
} Game1BB950State;

void *func_1518D1C0(s32, s32, s32, s32, s32, s32, void *);
extern u8 D_800A7460;
extern u8 D_800A749C;

s32 func_1518E66C(Game1BB950State *arg0) {
    func_1518D1C0(arg0->owner, 3, 0, 0, arg0->intensity, arg0->variant, &D_800A7460);
    arg0->timer = 0x80;
    arg0->callback = -1;
    return 0;
}
s32 func_1518E6D4(Game1BB950State *arg0) {
    func_1518D1C0(arg0->owner, 4, 0, 0, arg0->intensity, arg0->variant, &D_800A749C);
    arg0->timer = 0x80;
    arg0->callback = -1;
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BB950/func_1518E73C.s")
