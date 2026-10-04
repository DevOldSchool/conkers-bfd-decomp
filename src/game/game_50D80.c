#include "types.h"

/*
 * Reviewed source unit: src/game/game_50D80.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150238D8
 * - func_15023BB0
 * - func_15023DE0
 * - func_15024130
 * - func_150241B4
 * - func_150242F8
 * - func_1502460C
 * - func_150265CC
 * - func_15029BB8
 * - func_1502A8A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150238D0(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150238D8.s")
typedef struct {
    s8 kind;
    u8 step;
    s16 value;
    s8 field4;
    s8 field5;
    u8 pad6[2];
} Game50D80Record;

extern u16 *D_800C35D8[];
extern s32 D_800C3640[];
extern u8 D_800C3688[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15023BB0 CURRENT (3604) */
s32 func_15023BB0(u32 arg0, s32 arg1, s32 arg2, void **arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    s32 var_v1;
    s32 var_a1;
    u16 temp_a3;
    u8 var_v0;
    Game50D80Record *temp_v0;
    Game50D80Record *var_a0;

    temp_v0 = *(Game50D80Record **)(D_800C3688 + arg10 * 0x78 + arg2 * 4);
    if (temp_v0 != 0) {
        var_a0 = temp_v0 + 4;
        temp_a3 = D_800C35D8[arg10][arg2];
        var_a1 = (u8 *)var_a0 - (u8 *)temp_v0;
        var_v1 = temp_v0->value;
        if ((u32) (var_a1 >> 3) < temp_a3) {
loop_3:
            var_v0 = var_a0->step;
            if ((var_v0 == 0) && (var_a0->kind == 0)) {
                var_v1 = var_a0->value;
                goto block_37;
            }
            if ((arg0 < (u32) var_a0) && (arg1 == var_a0->kind) && ((arg4 == 0) || ((arg4 == 1) && (arg5 == var_a0->value))) && ((arg6 == 0) || ((arg6 == 1) && (arg7 == var_a0->field4))) && ((arg8 == 0) || ((arg8 == 1) && (arg9 == var_a0->field5)))) {
                *arg3 = var_a0;
                return (s32) var_v1;
            }
            if (var_v0 == 0) {
loop_19:
                if (var_a0->kind == 0) {
                    var_v1 = var_a0->value;
                    goto block_36;
                }
                var_a1 += 8;
                var_a0++;
                if ((u32) (var_a1 >> 3) >= temp_a3) {
                    var_v0 = var_a0->step;
                    goto block_36;
                }
                if ((arg0 < (u32) var_a0) && (arg1 == var_a0->kind) && ((arg4 == 0) || ((arg4 == 1) && (arg5 == var_a0->value))) && ((arg6 == 0) || ((arg6 == 1) && (arg7 == var_a0->field4))) && ((arg8 == 0) || ((arg8 == 1) && (arg9 == var_a0->field5)))) {
                    *arg3 = var_a0;
                    return (s32) var_v1;
                }
                var_v0 = var_a0->step;
                if (var_v0 != 0) {
                    goto block_36;
                }
                goto loop_19;
            }
block_36:
            var_v1 += var_v0;
block_37:
            var_a1 += 8;
            var_a0++;
            if ((u32) (var_a1 >> 3) >= temp_a3) {
                goto block_38;
            }
            goto loop_3;
        }
    }
block_38:
    *arg3 = 0;
    return D_800C3640[arg10];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15023BB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15023BB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15023DE0.s")
void func_1502A8A0(void *, s32, s32, s32, s32);
extern s32 D_800C3D50;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15024130 CURRENT (514) */
void func_15024130(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s1;
    s32 *var_s4;
    void *temp_v0;

    var_s0 = 0;
    if (arg0 > 0) {
        var_s4 = &D_800C3D50;
        var_s1 = 0;
        do {
            temp_v0 = (void *)((u8 *)(*var_s4) + var_s1);
            func_1502A8A0(*(s32 *)((u8 *)temp_v0 + 0), *(u8 *)((u8 *)temp_v0 + 8), *(u16 *)((u8 *)temp_v0 + 0xA), *(s32 *)((u8 *)temp_v0 + 4), arg1);
            var_s0 += 1;
            var_s1 += 0xC;
        } while (var_s0 != arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15024130 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15024130.s")
extern u16 D_800C3C9A;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150241B4 CURRENT (865) */
void func_150241B4(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    typedef struct { s32 words[3]; } Copy3;
    s32 temp_s0;
    s32 var_a0;
    s32 var_a2;
    u8 *var_v0;
    u8 *var_v1;

    temp_s0 = *arg1;
    var_a2 = temp_s0;
    if (temp_s0 >= (s32) D_800C3C9A) {
        func_15024130(temp_s0, arg6);
        *arg1 = 0;
        return;
    }
    var_a0 = 0;
    if (temp_s0 > 0) {
        var_v0 = arg0;
loop_4:
        if (*(s32 *)((u8 *)var_v0 + 4) >= arg5) {
            var_a2 = var_a0;
        } else {
            var_a0 += 1;
            var_v0 += 0xC;
            if (var_a0 < temp_s0) {
                goto loop_4;
            }
        }
    }
    var_a0 = temp_s0 - 1;
    if (var_a0 >= var_a2) {
        var_v0 = (void *)(arg0 + (var_a0 * 0xC));
        var_v1 = (void *)(var_v0 + 0xC);
        do {
            *(Copy3 *)var_v1 = *(Copy3 *)var_v0;
            var_v1 -= 0xC;
            var_v0 -= 0xC;
        } while ((u32) var_v1 >= (u32) ((var_a2 * 0xC) + arg0 + 0xC));
    }
    var_v0 = (void *)(arg0 + (var_a2 * 0xC));
    *(s32 *)((u8 *)var_v0 + 0) = arg2;
    *(s8 *)((u8 *)var_v0 + 8) = (s8) arg3;
    *(s32 *)((u8 *)var_v0 + 4) = arg5;
    *(s16 *)((u8 *)var_v0 + 0xA) = (s16) arg4;
    *arg1 += 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150241B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150241B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150242F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_1502460C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150265CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15029BB8.s")
typedef struct {
    u16 kind;
    u8 index;
    u8 pad3[5];
} Game50D80DispatchEntry;

typedef struct {
    u8 bytes[0x44];
} Game50D80DispatchState;

extern u8 D_800C35E8[];
extern Game50D80DispatchEntry *D_800C35F0[];
extern Game50D80DispatchState *D_800C3958[];
extern u8 D_800C3C88;
s32 func_151149AC(u8);
void *func_15083E90(u8);
s32 func_1502460C(void *, s32, s32, s32, s32, void *, void *, void *, s32);
s32 func_150265CC(void *, s32, s32, s32, s32, void *, void *, void *, s32);
s32 func_15029BB8(void *, s32, s32, s32, s32, void *, void *, void *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502A8A0 CURRENT (5458) */
void func_1502A8A0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *actor;
    void *object;
    void *state;
    s32 flag;
    Game50D80DispatchEntry *entry;

    actor = 0;
    object = 0;
    flag = D_800C35E8[arg4];
    entry = &D_800C35F0[arg4][arg1];
    state = 0;
    if (entry->kind == 2) {
        actor = func_15083E90(entry->index);
        if (actor != 0) {
            state = (u8 *)actor + 0x14;
            goto dispatch;
        }
    } else if (entry->kind != 3 || (object = (void *)func_151149AC(entry->index)) != 0) {
        dispatch:
        if (state == 0) {
            state = &D_800C3958[arg4][arg1];
        }
        if (D_800C3C88 != 2) {
            if (func_1502460C(arg0, arg1, arg2, arg3, arg4, actor, object, state, flag) == 0) {
                if (func_150265CC(arg0, arg1, arg2, arg3, arg4, actor, object, state, flag) == 0 &&
                    func_15029BB8(arg0, arg1, arg2, arg3, arg4, actor, object, state, flag, 0) != 0) {
                    return;
                }
            }
        } else {
            if (func_1502460C(arg0, arg1, arg2, arg3, arg4, actor, object, state, flag) == 0) {
                func_15029BB8(arg0, arg1, arg2, arg3, arg4, actor, object, state, flag, 1);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502A8A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_1502A8A0.s")
