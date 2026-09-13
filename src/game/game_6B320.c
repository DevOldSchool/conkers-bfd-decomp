#include "types.h"

/*
 * Reviewed source unit: src/game/game_6B320.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503DE70
 * - func_1503DF0C
 * - func_1503DF48
 * - func_1503E1F4
 * - func_1503E260
 * - func_1503E3C4
 * - func_1503E5F8
 * - func_1503E82C
 * - func_1503EA54
 * - func_1503EB78
 * - func_1503ECA0
 * - func_1503EEC0
 * - func_1503EF4C
 * - func_1503EFC4
 * - func_1503F16C
 * - func_1503F2B0
 * - func_1503F404
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503DE70.s")
typedef struct {
    u8 pad_0[0x1EC];
    f32 field_1EC;
} Game6B320Entity;

typedef struct {
    Game6B320Entity *entity;
    u8 pad_4[8];
    s16 field_C;
    u8 pad_E[2];
} Game6B320Slot;

extern Game6B320Slot D_800C6660[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DF0C CURRENT (380) */
void func_1503DF0C(s32 arg0, s8 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = (void *)((u8 *)&D_800C6660 + (arg0 * 0x10));
    *(s32 *)((u8 *)temp_v0 + 4) |= arg2;
    *(s32 *)((u8 *)temp_v0 + 8) |= arg3;
    *(s8 *)((u8 *)temp_v0 + 0xE) = arg1;
    *(s8 *)((u8 *)temp_v0 + 0xF) = 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DF0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503DF0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503DF48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E1F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E3C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E5F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E82C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503EA54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503EB78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503ECA0.s")
void func_1503EEB8(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503EEC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503EF4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503EFC4.s")
/* Call context: func_1503EB78: unique active project prototype */
void func_1503EB78(void *, f32, f32, s32);

void func_1503F078(void *arg0, s32 arg1) {
    func_1503EB78(arg0, 2.0f, 2.0f, 0);
}
void func_1503EB78(void *arg0, f32 arg1, f32 arg2, s32 arg3);

void func_1503F0AC(void *arg0, u8 arg1) {
    func_1503EB78(arg0, 1.0f, 2.0f, 1);
}
/* Call context: func_1503EB78: unique active project prototype */

void func_1503F0D8(void *arg0, s32 arg1) {
    func_1503EB78(arg0, 2.06f, 3.0f, 1);
}
typedef struct {
    s32 field_0;
    u8 pad_4[0x328];
} Game6B320EntityRecordField94;

extern Game6B320EntityRecordField94 D_800CC364[];

void func_1503F108(s32 arg0) {
    D_800C6660[arg0].field_C = 0x8C;
    D_800CC364[arg0].field_0 = 6;
    D_800C6660[arg0].entity->field_1EC = 10.0f;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503F16C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503F2B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503F404.s")
