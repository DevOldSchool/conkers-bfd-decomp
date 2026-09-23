#include "types.h"

/*
 * Reviewed source unit: src/game/game_193E50.c
 * Boundary evidence: docs/evidence/game_raw_display_transition_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151669A0
 * - func_15166B50
 * - func_15166D68
 * - func_15166F6C
 * - func_15166FD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_1517E05C(s32, s32, s32);
void func_15043D90(s32, f32, f32, volatile s32, f32, f32, f32, f32, f32, f32);
void func_15043E68(s32, f32, f32, volatile s32, f32, f32, f32);
u32 func_150ADA20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151669A0 CURRENT (781) */
void func_151669A0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, u8 arg4, s32 arg5) {
    u8 *object;
    u8 *cursor;
    s32 random_offset;
    s32 byte_offset;
    f32 x;
    f32 y;
    f32 z;

    object = func_15167A68(0xD, arg5, 0xE0, 1, arg4, 1);
    if (object != 0) {
        object[0xD0] = 0xA;
        *(s16 *)(object + 0xD2) = arg0;
        *(s16 *)(object + 0xD4) = arg1;
        *(f32 *)(object + 0xD8) = arg3;
        *(s16 *)(object + 0xD6) = arg2;
        random_offset = func_150ADA20() & 0x7F;
        byte_offset = 0;
        cursor = object + 0x10;
        x = (f32)arg0;
        y = (f32)arg1;
        z = (f32)arg2;
        do {
            if (arg3 != 1.0f) {
                func_15043D90((s32)cursor, 0.0f, (f32)random_offset, 0,
                               arg3, arg3, arg3, x, y, z);
            } else {
                func_15043E68((s32)cursor, 0.0f, (f32)random_offset, 0,
                               x, y, z);
            }
            random_offset += func_150ADA20() & 0x3F;
            byte_offset += 0x40;
            cursor += 0x40;
            random_offset += 0x5A;
        } while (byte_offset != 0xC0);
        func_1517E05C(arg0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151669A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_151669A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166B50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166D68.s")

void func_15094F70(s32, void *, s32, void *, s32, s32, s32, s32, s32);
extern u8 D_8009054C;
extern s32 D_800DD220;
extern s32 D_800DD224;
extern u8 *D_800DD228;
extern u8 D_800DD230;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15166F6C CURRENT (883) */
void func_15166F6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800DD228 = &D_8009054C;
    func_15094F70(arg0, &D_8009054C, D_800DD220, &D_800DD230, 0, 0, 0,
                   D_800DD224, 3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15166F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166F6C.s")
extern u8 D_80089470;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15166FD8 CURRENT (485) */
void *func_15166FD8(void *arg0, s32 arg1, s32 arg2) {
    u32 *temp_v1;

    temp_v1 = arg0;
    temp_v1[0] = 0xDA380003;
    temp_v1[1] = (u32)&D_80089470;
    return temp_v1 + 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15166FD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166FD8.s")
