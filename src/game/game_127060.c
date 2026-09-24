#include "types.h"

/*
 * Reviewed source unit: src/game/game_127060.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F9BB0
 * - func_150FA1B8
 * - func_150FA468
 * - func_150FA520
 * - func_150FAA40
 * - func_150FAAEC
 * - func_150FAE18
 * - func_150FB188
 * - func_150FB1E8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game127060State {
    u8 pad0[0x54];
    f32 field54;
    f32 field58;
    f32 field5C;
} Game127060State;

typedef struct Game127060Transform {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
} Game127060Transform;

#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150F9BB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA1B8.s")
void func_1515D4D4(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FA468 CURRENT (2894) */
void func_150FA468(void *arg0, s32 arg1, s32 arg2) {
    switch ((u8)arg2) {
    case 0x4C:
        *(s8 *)((u8 *)arg0 + 0x11) = -1;
        func_1515D4D4(0, 0, 0, 0xFF);
        break;
    case 0x4D:
        *(s8 *)((u8 *)arg0 + 0x11) = 0x1E;
        break;
    case 0x4E:
        *(s8 *)((u8 *)arg0 + 0x11) = -1;
        break;
    case 0x4F:
        *(s8 *)((u8 *)arg0 + 0x11) = -1;
        func_1515D4D4(0xFF, 0xFF, 0xFF, 0xFF);
        break;
    default:
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FA468 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FA520.s")
void *func_10022EC0(void *, const void *, u32);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_80088B60;
extern s32 D_800D3098;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FAA40 CURRENT (939) */
void func_150FAA40(u8 arg0, s32 arg1) {
    f32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 temp_v0;

    if (D_80088B60 == 0) {
        sp3C = D_800D3098 + 0x71C;
        sp40 = D_800D3098 + 0x6E8;
        sp44 = 0.0f;
        temp_v0 = func_15149130(0x12C, -1, 0x57, -1, 0, 0x46, 0xC, (s32)arg0, arg1);
        if (temp_v0 != 0) {
            D_80088B60 = 1;
        }
        if (temp_v0 != 0) {
            func_10022EC0((u8 *)temp_v0 + 0x28, &sp3C, 0xCU);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FAA40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FAA40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FAAEC.s")
extern void func_1516972C(s32 arg0);

void func_150FACE4(s32 arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0x4E) || (arg2 == 0x4F)) {
        func_1516972C(arg0);
    }
}
void func_1515F170(s32, s32);
void func_151494E0(s32, s32);
extern s32 D_800D3098;

void func_150FAD28(void) {
    func_1515F170(8, 0);
    func_1515F170(0xB, 1);
    func_151494E0(D_800D3098 + 0x514, 0x30);
    func_151494E0(0, 0x4D);
}
void func_150FAD78(void) {
    func_1515F170(8, 1);
    func_1515F170(7, 0);
    func_151494E0(D_800D3098 + 0x514, 0x31);
    func_151494E0(0, 0x4C);
}
void func_150FADC8(void *arg0, s32 arg1, u8 arg2) {

    if (arg2 == 0x53) {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 2);
        return;
    }
    if (arg2 == 0x54) {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) & ~2);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FAE18.s")
void func_15157DEC(Game127060State *, Game127060Transform *);
extern f32 D_800A1DC0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FB188 CURRENT (654) */
s32 func_150FB188(Game127060State *arg0) {
    Game127060Transform transform;

    arg0->field5C = 0.0f;
    arg0->field54 = -95.0f;
    arg0->field58 = -80.0f;
    transform.field0 = 0.0f;
    transform.field4 = 0.0f;
    transform.field8 = 0.0f;
    transform.fieldC = D_800A1DC0;
    transform.field10 = D_800A1DC0;
    func_15157DEC(arg0, &transform);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FB188 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FB188.s")

void func_15157F80(s32, s32, s32, s32, s32);
s32 func_151D710C(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FB1E8 CURRENT (452) */
void func_150FB1E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_15157F80(func_151D710C(arg1, arg2, arg3, arg4), arg1, arg2, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FB1E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_127060/func_150FB1E8.s")
