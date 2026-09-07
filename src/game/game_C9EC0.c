#include "types.h"

/*
 * Reviewed source unit: src/game/game_C9EC0.c
 * Boundary evidence: docs/evidence/game_raw_resource_dependency_core.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509CA50
 * - func_1509CA98
 * - func_1509CB68
 * - func_1509CBD4
 * - func_1509CCB4
 * - func_1509CCF4
 * - func_1509CDDC
 * - func_1509CE64
 * - func_1509CF28
 * - func_1509D054
 * - func_1509D08C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameC9EC0Entry {
    s32 field_0;
    u8 pad4[4];
    u16 field_8;
    u8 padA[0xA];
} GameC9EC0Entry;

extern GameC9EC0Entry D_80087430[];
extern GameC9EC0Entry D_80087434[];

typedef struct GameC9EC0HalfwordEntry {
    u16 field_0;
    u8 pad2[0x12];
} GameC9EC0HalfwordEntry;

extern GameC9EC0HalfwordEntry D_80087438[];

s32 func_1509CA10(s32 arg0) {
    return D_80087430[arg0].field_0;
}
u16 func_1509CA30(s32 arg0) {
    return D_80087438[arg0].field_0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CA50.s")
s32 func_1509CA78(s32 arg0) {
    return D_80087434[arg0].field_0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509CA98 CURRENT (60) */
s32 func_1509CA98(s32 arg0) {
    GameC9EC0Entry *var_v0;
    s32 var_v1;

    var_v1 = 0;
    var_v0 = D_80087430;
loop_1:
    if ((var_v0->field_0 != 0) && (arg0 == ((*(s32 *)((u8 *)var_v0 + 4) & 0x1FFFFFFF) + 1))) {
        return var_v1;
    }
    if ((*(s32 *)((u8 *)var_v0 + 0x14) != 0) && (arg0 == ((*(s32 *)((u8 *)var_v0 + 0x18) & 0x1FFFFFFF) + 1))) {
        return var_v1 + 1;
    }
    if ((*(s32 *)((u8 *)var_v0 + 0x28) != 0) && (arg0 == ((*(s32 *)((u8 *)var_v0 + 0x2C) & 0x1FFFFFFF) + 1))) {
        return var_v1 + 2;
    }
    if ((*(s32 *)((u8 *)var_v0 + 0x3C) != 0) && (arg0 == ((*(s32 *)((u8 *)var_v0 + 0x40) & 0x1FFFFFFF) + 1))) {
        return var_v1 + 3;
    }
    var_v1 += 4;
    var_v0 += 0x50;
    if (var_v1 == 0xCC) {
        return 0xCC;
    }
    goto loop_1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509CA98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CA98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CB68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CBD4.s")
void func_1509CC94(void) {
    func_1509CCB4();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CCB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CCF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CDDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CE64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CF28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509D054.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509D08C.s")
