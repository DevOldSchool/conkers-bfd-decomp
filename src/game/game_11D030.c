#include "types.h"

/*
 * Reviewed source unit: src/game/game_11D030.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EFB80
 * - func_150EFEC8
 * - func_150F00EC
 * - func_150F0198
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150EFB80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150EFEC8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F00EC CURRENT (1860) */
s32 func_150F00EC(u8 *arg0) {
    s32 temp_t4;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x178));
    if (*(u8 *)((u8 *)temp_v0 + 0x128) & 1) {
        temp_v1 = (void *)(temp_v0 + 0x110);
        *(f32 *)((u8 *)arg0 + 0x34) = (f32) *(f32 *)((u8 *)temp_v0 + 0x34);
        *(f32 *)((u8 *)arg0 + 0x38) = (f32) *(f32 *)((u8 *)temp_v0 + 0x38);
        *(f32 *)((u8 *)arg0 + 0x3C) = (f32) *(f32 *)((u8 *)temp_v0 + 0x3C);
        *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x34) + (*(f32 *)((u8 *)temp_v1 + 0x30) * 500.0f));
        *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x38) + (*(f32 *)((u8 *)temp_v1 + 0x34) * 500.0f));
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 6);
        *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x3C) + (*(f32 *)((u8 *)temp_v1 + 0x38) * 500.0f));
    } else {
        temp_t4 = *(s32 *)((u8 *)arg0 + 0x58) & ~4;
        *(s32 *)((u8 *)arg0 + 0x58) = temp_t4;
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (temp_t4 & ~2);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F00EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150F00EC.s")
void *func_10022EC0(void *, const void *, u32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game11D030Locals {
    s32 payload;
    s32 position[3];
    u8 descriptor_0;
    s8 descriptor_1;
    s16 descriptor_2;
    s8 descriptor_4;
    u8 pad15[3];
    s32 saved;
} Game11D030Locals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F0198 CURRENT (120) */
s32 func_150F0198(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    Game11D030Locals locals;
    register s32 value;

    locals.payload = arg4;
    locals.descriptor_0 = 2;
    locals.descriptor_1 = -1;
    locals.descriptor_2 = 0x12C;
    locals.descriptor_4 = 0x21;
    locals.position[0] = 0;
    locals.position[1] = 0;
    locals.position[2] = 0;
    value = func_151602C0(&locals.descriptor_0, &locals.position[0], arg0, arg1, arg2,
                          arg3, 0xFF, 0, 4, arg5, arg6);
    if (value != 0) {
        locals.saved = value;
        func_10022EC0((u8 *) value + 0x18, &locals.payload, 4);
        value = locals.saved;
    }
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F0198 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150F0198.s")
