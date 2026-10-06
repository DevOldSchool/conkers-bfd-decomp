#include "types.h"

/*
 * Reviewed source unit: src/game/game_803A0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15052F9C
 * - func_1505327C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_1505E650: unique active project prototype */
void func_1505E650(u8 *, s32, f32, f32, f32, f32, s32);

void func_15052EF0(u8 *arg0) {
    *(s8 *)((u8 *)arg0 + 0x125) = 0x64;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
    func_1505E650(arg0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}
extern u8 D_800CC2D0[];

void func_15052F58(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = D_800CC2D0 + (arg0 * 0x32C);
    temp_v0[0x13C] = 0;
    *(s32 *)(temp_v0 + 0x218) = 0;
    temp_v0[0x232] = arg1;
}
void *func_15033E84(void *);
void func_1506E5FC(void);
s32 func_15083568(s32, s32, f32, s32);
void func_15060F28(u8 *, s32);
void func_1506160C(u8 *, s32, s32, s32, u8);
extern s32 D_800BE9F0;
extern u8 D_800C3E78;
extern s32 D_800D1580;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15052F9C CURRENT (2443) */
void func_15052F9C(u8 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    register u8 *actor;
    s32 subtype;
    s32 removeOwner;
    register s32 mode;
    s32 actorIndex;
    u8 *child;
    void *info;

    removeOwner = 0;
    subtype = -1;
    if (arg0[4] == 0x48) {
        info = func_15033E84(arg0);
        if (info != 0) {
            subtype = *(u8 *)((u8 *)info + 6);
        }
    }
    actorIndex = arg0[0x124];
    actor = D_800CC2D0 + actorIndex * 0x32C;
    if (arg8 != 0 || (*(f32 *)(actor + 0x18) < *(f32 *)(arg0 + 0x18) + arg1 * *(f32 *)(arg0 + 0x150) && *(f32 *)(actor + 0x20) < 0.0f)) {
        arg0[0x13C] = actorIndex + 100;
        if (arg9 != 0) {
            D_800D1580 = arg9;
            func_1506E5FC();
        }
        child = *(u8 **)(actor + 0x31C);
        *(f32 *)(actor + 0x1CC) = *(f32 *)(actor + 0x18);
        *(u16 *)(actor + 0x76) = *(u16 *)(arg0 + 0x7A);
        child[0x30] = 0;
        if (*(s32 *)arg0 == 0x20) {
            *(f32 *)(actor + 0x20) = 0.0f;
            mode = 2;
            *(f32 *)(arg0 + 0x20) = 0.0f;
            if (arg0[4] == 0x48) {
                if (subtype == 0x7A) {
                    arg0[0x65] = arg0[0x124] + 1;
                    *(s32 *)(arg0 + 0x5C) = arg2;
                    arg0[0x101] |= arg3;
                    func_1505E650(actor, 5, 1.0f, 0.0f, 0.0f, 0.0f, 0);
                    func_15083568((s32)actor, 0x79, 1.0f, 0);
                    removeOwner = 1;
                }
            } else {
                *(f32 *)(arg0 + 0x150) = 0.75f;
                *(f32 *)(actor + 0x18) = *(f32 *)(arg0 + 0x18);
                mode = 1;
                if (D_800BE9F0 == 6) {
                    mode = 0x81;
                }
            }
            actorIndex = *(u16 *)(arg0 + 0x7A);
            child = *(u8 **)(actor + 0x31C);
            *(u16 *)(actor + 0x76) = actorIndex;
            *(u16 *)(actor + 0x78) = actorIndex;
            *(u16 *)(actor + 0x7A) = actorIndex;
            *(f32 *)(actor + 0x40) = (f32)(s16)(actorIndex + 0x4000) * 0.0054931640625f;
            child[0x4E] = mode;
            actor[0x83] = 0;
            actor[0x89] = 0;
        } else {
            actor[0x65] = D_800C3E78 + 1;
            *(s32 *)(actor + 0x5C) = arg2;
            actor[0x89] = 0;
            actor[0x101] |= arg3;
        }
        child = *(u8 **)(actor + 0x31C);
        actor[0x125] = arg6;
        actor[0x239] = arg7;
        child[0x27] = 0;
        *(s32 *)(arg0 + 0x218) = 0;
        arg0[0x232] = arg5;
        if (arg4 != 0) {
            func_1506160C(actor, 1, 0, 0, 0);
            actor[0x101] |= 0x40;
        }
    }
    if (removeOwner != 0) {
        func_15060F28(arg0, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15052F9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_803A0/func_15052F9C.s")
void func_15043FF0(f32 *, u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505327C CURRENT (1140) */
void func_1505327C(u8 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4) {
    u8 *actor;
    u8 *object;
    struct {
        u8 pad[8];
        f32 position[3];
    } local;

    actor = (arg0[0x124] * 0x32C) + D_800CC2D0;
    if (actor[0x89] != 0 || actor[0x104] != 0) {
        return;
    }
    object = *(u8 **)(actor + 0x31C);
    if (object == 0 || object[0x6B] == 0) {
    actor[0x125] = 0xFF;
    *(f32 *)(actor + 0x20) = arg1;
    *(f32 *)(actor + 0x24) = arg2;
    actor[0x83] = 0xFF;
    actor[0x89] = 0xFF;
    *(u16 *)(actor + 0x76) = *(u16 *)(arg0 + 0x7A);
    *(s32 *)(arg0 + 0x218) = 0;
    arg0[0x232] = arg3;
    func_1505E650(actor, 0x32, 0x3FA66666, 0x40800000, 0.0f, 0.0f, 0);
    (*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C))[0x30] = 0x46;
    *(f32 *)(*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C) + 0x28) = *(f32 *)(arg0 + 0x14);
    *(f32 *)(*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C) + 0x2C) = *(f32 *)(arg0 + 0x1C);
    if (*(s32 *)(arg0 + 0x1D4) != 0 && arg4 != -1) {
        func_15043FF0(local.position, *(u8 **)(arg0 + 0x1D4) + (arg4 << 6));
        *(f32 *)(*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C) + 0x28) = local.position[0];
        *(f32 *)(*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C) + 0x2C) = local.position[2];
    }
    (*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C))[0x27] = 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505327C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_803A0/func_1505327C.s")
