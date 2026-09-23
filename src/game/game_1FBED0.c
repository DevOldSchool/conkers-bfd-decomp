#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FBED0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CEA20
 * - func_151CEAAC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CEA20 CURRENT (575) */
s32 func_151CEA20(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x40);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x44);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (temp_fv1 + (temp_fa0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + ((temp_fv1 + (0.5f * temp_fa0 * D_800BE9A4)) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    if (*(f32 *)((u8 *)arg0 + 0x50) > 1.0f) {
        *(f32 *)((u8 *)arg0 + 0x50) = 1.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CEA20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FBED0/func_151CEA20.s")
typedef struct Game1FBED0Link {
    void *owner;
    u8 type;
    u8 pad5[3];
    s32 arg1;
    f32 zero0;
    f32 one0;
    f32 zero1;
    f32 one1;
    u8 mode;
    u8 pad1D[3];
    f32 random0;
    f32 random1;
} Game1FBED0Link;

typedef struct Game1FBED0Spawn {
    f32 position[3];
    s16 fieldC;
    s16 fieldE;
    s32 field10;
    u8 field14;
    u8 field15;
    u8 pad16[2];
} Game1FBED0Spawn;

f32 func_150ADA68(void);
s32 func_151CEC10(f32 *, void *, s32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32,
                    s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);
extern f32 D_800AB008;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CEAAC CURRENT (268) */
void *func_151CEAAC(void *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct {
        Game1FBED0Link link;
        Game1FBED0Spawn spawn;
        void *saved_result;
    } locals;
    void *result;
    f32 random;
    s8 mode;

    locals.spawn.field15 = 0x19;
    locals.spawn.fieldC = 0x12C;
    locals.spawn.fieldE = 0x10;
    locals.spawn.field10 = 0x11;
    locals.spawn.field14 = 3;
    locals.link.owner = arg0;
    if (arg0 != 0) {
        locals.link.type = *(u8 *)((u8 *)arg0 + 0x3B);
    } else {
        locals.link.type = 0;
    }
    locals.link.one0 = 1.0f;
    locals.link.one1 = 1.0f;
    locals.link.arg1 = arg1;
    locals.link.zero0 = 0.0f;
    locals.link.zero1 = 0.0f;
    if (arg2 != 0) {
        mode = 2;
    } else {
        mode = 0;
    }
    locals.link.mode = mode;
    locals.link.random0 = func_150ADA68() * 400.0f + 400.0f;
    random = func_150ADA68();
    locals.link.random1 = (random + random) * D_800AB008;
    if (func_151CEC10(locals.spawn.position, arg0, arg1) == 0) {
        locals.spawn.position[0] = 0.0f;
        locals.spawn.position[1] = 0.0f;
        locals.spawn.position[2] = 0.0f;
    }
    result = func_15147A80(locals.spawn.position, (void *)0x28, 0x28,
                           0, 0xF, 0xF, 0, 0, 0, arg3, arg4);
    if (result != 0) {
        locals.saved_result = result;
        func_10022EC0(*(void **)((u8 *)result + 0x98), &locals.link, 0x28);
        result = locals.saved_result;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CEAAC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FBED0/func_151CEAAC.s")
