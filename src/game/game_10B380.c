#include "types.h"

/*
 * Reviewed source unit: src/game/game_10B380.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DDED0
 * - func_150DDFAC
 * - func_150DE12C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_151491F4(s32, s32, s32, s32, s32, s32, s32, s32);
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DDED0 CURRENT (230) */
void func_150DDED0(void *arg0) {
    void *object;
    u8 tag;

    object = func_151491F4(0x64, 2, -1, 1, 0, 1, 0xFF, 0);
    if (object == 0) {
        return;
    }
    tag = *(u8 *)((u8 *)arg0 + 0x72);
    switch (tag) {
    case 0xFB:
        *(s8 *)((u8 *)object + 0x28) = 1;
        break;
    case 0xFC:
        *(s8 *)((u8 *)object + 0x28) = 2;
        break;
    case 0xFD:
        *(s8 *)((u8 *)object + 0x28) = 4;
        break;
    case 0xFE:
        *(s8 *)((u8 *)object + 0x28) = 3;
        break;
    default:
        func_1516972C(object);
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DDED0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B380/func_150DDED0.s")
extern void func_150DBD70(u8, void *);

void func_150DDF88(void *arg0) {
    func_150DBD70(*(u8 *)((u8 *)arg0 + 0x28), arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B380/func_150DDFAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B380/func_150DE12C.s")
typedef struct Game10B380Object {
    u8 pad0[0x1C];
    s16 field_1C;
    u8 pad1E[0xA];
    s8 field_28;
} Game10B380Object;

s32 func_150DE2A4(Game10B380Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x20) {
        arg0->field_28 = value * 8;
    }

    return 1;
}
void func_150DE2C4(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) - 0x1A);
    *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) - 0x1A);
    if ((*(s16 *)((u8 *)arg0 + 0x34) < 0xA) || (*(s16 *)((u8 *)arg0 + 0x36) < 0xA)) {
        *(s16 *)((u8 *)arg0 + 0x38) = 0;
    }
}
