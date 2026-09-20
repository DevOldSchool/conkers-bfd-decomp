#include "types.h"

/*
 * Reviewed source unit: src/game/game_1368C0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15109410
 * - func_151094FC
 * - func_15109848
 * - func_15109C20
 * - func_15109ED4
 * - func_15109FB8
 * - func_1510A344
 * - func_1510A40C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game1368C0Spawn9410 {
    void *source;
    u8 type;
    u8 pad5[3];
    f32 zero;
    f32 value;
    s8 field_10;
    s8 field_11;
    u8 pad12[2];
} Game1368C0Spawn9410;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15109410 CURRENT (85) */
s32 func_15109410(void *arg0, s16 arg1, s8 arg2, s8 arg3,
                   f32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    Game1368C0Spawn9410 spawn;
    s16 type;
    s32 enabled;
    s32 result;

    if (arg0 == 0) {
        return 0;
    }
    enabled = 0;
    if (arg1 < 0) {
        type = 0x12C;
    } else {
        enabled = 1;
        type = arg1;
    }
    spawn.zero = 0.0f;
    spawn.value = arg4;
    spawn.field_10 = arg2;
    spawn.field_11 = arg3;
    spawn.source = arg0;
    spawn.type = *(u8 *)((u8 *)arg0 + 0x3B);
    result = func_15149130(type, -1, 0x1A, -1, enabled, 0x1A,
                          arg5 + 0x14, arg6, arg7);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x28, &spawn, 0x14U);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15109410 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109410.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_151094FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109848.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109C20.s")
void *func_10022EC0(void *, const void *, u32);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game1368C0Spawn {
    void *source;
    f32 zero;
    f32 value;
    s8 field_C;
    s8 field_D;
    u8 padE[2];
} Game1368C0Spawn;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15109ED4 CURRENT (318) */
s32 func_15109ED4(s32 arg0, s16 arg1, s8 arg2, s8 arg3,
                   f32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    s32 sp44;
    Game1368C0Spawn spawn;
    s16 var_a0;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    if (arg0 == 0) {
        return 0;
    }
    var_v0 = 0;
    if (arg1 < 0) {
        var_a0 = 0x12C;
    } else {
        var_v0 = 1;
        var_a0 = arg1;
    }
    spawn.zero = 0.0f;
    spawn.value = arg4;
    spawn.field_C = arg2;
    spawn.field_D = arg3;
    spawn.source = (void *)arg0;
    temp_v0 = func_15149130(var_a0, -1, 0x1B, -1, var_v0,
                             0x1B, arg5 + 0x10, arg6, arg7);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp44 = temp_v0;
        func_10022EC0((u8 *)temp_v0 + 0x28, &spawn, 0x10);
        var_v1 = sp44;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15109ED4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109ED4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109FB8.s")
extern f32 D_800A2684;
extern f32 D_800A2688;

typedef struct Game1368C0Locals {
    void *source;
    u8 type;
    u8 pad5[3];
    f32 zero;
    f32 value_1;
    f32 value_2;
    s32 saved;
} Game1368C0Locals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510A344 CURRENT (415) */
s32 func_1510A344(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    Game1368C0Locals locals;
    register s32 value;

    if (arg0 == 0) {
        return 0;
    }
    locals.source = arg0;
    locals.type = *(u8 *) ((u8 *) arg0 + 0x3B);
    locals.value_1 = D_800A2684;
    locals.zero = 0.0f;
    locals.value_2 = D_800A2688;
    value = func_15149130(arg1, -1, 0x1C, -1, 1, 0x1C, 0x14, arg2, arg3);
    if (value != 0) {
        locals.saved = value;
        func_10022EC0((u8 *) value + 0x28, &locals.source, 0x14);
        value = locals.saved;
    }
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510A344 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_1510A344.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_1510A40C.s")
