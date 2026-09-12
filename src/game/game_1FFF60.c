#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FFF60.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D2AB0
 * - func_151D2B4C
 * - func_151D2BA4
 * - func_151D2C40
 * - func_151D2DCC
 * - func_151D2E14
 * - func_151D2E5C
 * - func_151D2F00
 * - func_151D2F90
 * - func_151D3130
 * - func_151D324C
 * - func_151D3354
 * - func_151D343C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2AB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2B4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2BA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2C40.s")
void func_151D2DAC(void) {
    func_151D3354();
}
extern void func_1516972C();
void func_15169804(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2DCC CURRENT (410) */
void func_151D2DCC(void *arg0) {
    s32 temp_v0;

    func_151D2DAC();
    temp_v0 = *(s32 *)((u8 *)arg0 + 0x2C);
    if (temp_v0 != 0) {
        func_1516972C(temp_v0, arg0);
    }
    func_15169804((s32)arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2DCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2DCC.s")
void func_1516979C(s32, void *);
void func_15169824(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2E14 CURRENT (410) */
void func_151D2E14(void *arg0) {
    s32 temp_v0;

    func_151D2DAC();
    temp_v0 = *(s32 *)((u8 *)arg0 + 0x2C);
    if (temp_v0 != 0) {
        func_1516979C(temp_v0, arg0);
    }
    func_15169824((s32)arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2E14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2E14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2E5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2F00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2F90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D3130.s")
void func_151D3130(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_151D31F4(s32 arg0) {
    func_151D3130(arg0);
    func_15169804(arg0);
}
void func_151D3220(s32 arg0) {
    func_151D3130(arg0);
    func_15169824(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D324C.s")
void func_151D3308(void *arg0) {
    void *temp_v0;
    void *temp_v1;

    temp_v0 = *(void **)((u8 *)arg0 + 0x30);
    if (temp_v0 != 0) {
        *(void **)((u8 *)arg0 + 0x40) = (void *) *(void **)((u8 *)temp_v0 + 0x24);
        temp_v1 = *(void **)((u8 *)temp_v0 + 0x24);
        if (temp_v1 != 0) {
            *(void **)((u8 *)temp_v1 + 0x44) = arg0;
        } else {
            *(void **)((u8 *)temp_v0 + 0x28) = arg0;
        }
        *(s32 *)((u8 *)arg0 + 0x44) = 0;
        *(void **)((u8 *)temp_v0 + 0x24) = arg0;
        *(s16 *)((u8 *)temp_v0 + 0x20) = (s16) (*(s16 *)((u8 *)temp_v0 + 0x20) + 1);
        *(void **)((u8 *)arg0 + 0x30) = temp_v0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D3354.s")
extern void func_1516972C();

void func_151D33B8(void *arg0) {
    if (*(s16 *)((u8 *)arg0 + 0x20) > 0) {
        do {
            func_1516972C(*(void **)((u8 *)arg0 + 0x24));
        } while (*(s16 *)((u8 *)arg0 + 0x20) > 0);
    }
}
extern void func_1516972C(void *arg0, void *arg1);

void func_151D33FC(void *arg0, void *arg1) {
    s32 temp_v0;
    s32 temp_v1;
    u8 temp_a2;
    u8 temp_a3;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x10);
    temp_v1 = *(s32 *)((u8 *)arg1 + 0);
    temp_a2 = *(u8 *)((u8 *)arg0 + 0x14);
    temp_a3 = *(u8 *)((u8 *)arg1 + 4);
    if ((temp_v0 == temp_v1) || (temp_a2 == temp_a3)) {
        func_1516972C(arg0, arg1);
    }
}
extern void func_15169260(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_800AB168;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D343C CURRENT (720) */
void func_151D343C(s32 arg0, s32 arg1) {
    s32 sp1C;

    sp1C = D_800AB168;
    func_15169260(&sp1C, 1, arg0, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D343C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D343C.s")
