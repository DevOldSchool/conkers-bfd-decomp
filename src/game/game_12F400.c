#include "types.h"

/*
 * Reviewed source unit: src/game/game_12F400.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15101F50
 * - func_151022AC
 * - func_151025F4
 * - func_151026BC
 * - func_1510281C
 * - func_151028AC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_15101F50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151022AC.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151025F4 CURRENT (2343) */
s32 func_151025F4(u8 *arg0, s32 arg1) {
    f32 sp24;
    f32 temp_ft3;
    u8 *temp_s0;

    sp24 = func_15047D60(*(f32 *)((u8 *)arg0 + 0xC0));
    temp_s0 = (void *)(arg0 + 0xA8);
    temp_ft3 = *(f32 *)((u8 *)temp_s0 + 0xC) + (*(f32 *)((u8 *)temp_s0 + 0x14) * func_15047D60(*(f32 *)((u8 *)arg0 + 0xC4)));
    *(f32 *)((u8 *)arg0 + 0xA8) = (f32) (*(f32 *)((u8 *)temp_s0 + 8) + (*(f32 *)((u8 *)temp_s0 + 0x10) * sp24));
    *(f32 *)((u8 *)temp_s0 + 4) = temp_ft3;
    *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x18) + (*(f32 *)((u8 *)temp_s0 + 0x20) * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0x1C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x1C) + (*(f32 *)((u8 *)temp_s0 + 0x24) * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0x18) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x18));
    *(f32 *)((u8 *)temp_s0 + 0x1C) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x1C));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151025F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151025F4.s")
typedef struct {
    u8 pad0[0x78];
    u8 field78;
} Game12F400Inner;

typedef struct {
    u8 pad0[4];
    u8 type;
    u8 pad5[0x317];
    Game12F400Inner *inner;
} Game12F400Object;

s32 func_15100600(void *, void *, void *, u8, s32, s32, s32, s32, f32, f32, f32, f32, s32, s32, s32);
extern u8 D_800A21A0[];
extern u8 D_800A21F4[];
extern u8 D_800A2248[];
extern f32 D_800A233C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151026BC CURRENT (600) */
s32 func_151026BC(Game12F400Object *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    s32 offset;
    s32 var_t0;
    s32 var_v1;

    if (arg0 == 0) {
        return 0;
    }
    switch (arg0->type) {
    case 0x58:
    case 0x5B:
    case 0x80:
        var_v1 = 0x32;
        var_t0 = 0xFF;
        break;
    case 0x5A:
    case 0x5F:
    case 0x74:
    case 0x75:
    case 0x7A:
        var_v1 = 0xFF;
        var_t0 = 0;
        break;
    default:
        var_v1 = 0x32;
        var_t0 = 0xFF;
        if (arg0->inner->field78 != 0x3B) {
            break;
        }
        var_v1 = 0xFF;
        var_t0 = 0;
        break;
    }
    offset = arg2 * 0xC;
    return func_15100600(arg0, D_800A21A0 + offset, D_800A21F4 + offset, D_800A2248[arg2],
                         arg1, var_v1, var_t0, 0, 20.0f, (f32) 20, 4.0f, D_800A233C,
                         arg3, arg4, arg5);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151026BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151026BC.s")
void func_151403A8(void **arg0, s32 arg1, void *arg2);

void func_151027E8(void *arg0) {
    struct {
        void *sp18;
        volatile u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151403A8(&sp.sp18, 0x1A, arg0);
}
typedef struct Game12F400DeepState {
    u8 pad0[0x197];
    u8 active;
} Game12F400DeepState;

typedef struct Game12F400LinkedState {
    u8 pad0[0x31C];
    Game12F400DeepState *deep;
} Game12F400LinkedState;

typedef struct Game12F400ControlState {
    u8 pad0[0x110];
    Game12F400LinkedState *linked;
    u8 pad114[0x1E];
    u8 selector;
} Game12F400ControlState;

typedef struct Game12F400State {
    u8 pad0[0xD0];
    Game12F400ControlState *control;
    u8 flags;
} Game12F400State;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510281C CURRENT (65) */
s32 func_1510281C(Game12F400State *arg0, s16 arg1) {
    Game12F400ControlState *temp_v0;
    Game12F400LinkedState *temp_v1;

    temp_v0 = arg0->control;
    if (arg1 == temp_v0->selector) {
        temp_v0 = (Game12F400ControlState *)((u8 *)temp_v0 + 0x110);
        temp_v1 = *(Game12F400LinkedState **)temp_v0;
        if ((temp_v1 == 0) || (temp_v1->deep->active != 0)) {
            return 0;
        }
    }
    if (!(arg0->flags & 1)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510281C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_1510281C.s")
s32 func_15102884(void *arg0, s32 arg1) {
    if (!(*(u8 *)((u8 *)arg0 + 0xAC) & 1)) {
        return 0;
    }
    return 1;
}

typedef struct Game12F400WideState {
    u8 pad0[0x170];
    Game12F400ControlState *control;
    u8 flags;
} Game12F400WideState;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151028AC CURRENT (460) */
s32 func_151028AC(Game12F400WideState *arg0, s16 arg1) {
    Game12F400ControlState *control = arg0->control;
    Game12F400LinkedState *linked;
    u8 selector = control->selector;

    control = (Game12F400ControlState *)((u8 *)control + 0x110);
    if (arg1 == selector) {
        linked = *(Game12F400LinkedState **)control;
        if ((linked == 0) || (linked->deep->active != 0)) {
            return 0;
        }
    }
    if (!(arg0->flags & 1)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151028AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151028AC.s")
