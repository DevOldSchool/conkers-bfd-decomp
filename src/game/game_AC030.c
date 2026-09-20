#include "types.h"

/*
 * Reviewed source unit: src/game/game_AC030.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507EBB8
 * - func_1507EC38
 * - func_1507EE58
 * - func_1507EEB8
 * - func_1507EEF4
 * - func_1507EFD0
 * - func_1507F454
 * - func_1507F54C
 * - func_1507F640
 * - func_1507FC2C
 * - func_1507FEA0
 * - func_1507FF94
 * - func_1507FFD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u32 func_150ADA20(u32);
extern s32 D_800BE9F0;

void func_1507EB80(u8 *arg0, s32 *arg1, u8 arg2) {
    s32 temp_v0;
    u8 *temp_v1;

    temp_v0 = *arg1;
    if ((temp_v0 + 1) < 0x28) {
        temp_v1 = arg0 + temp_v0;
        *temp_v1 = arg2;
        *arg1 += 1;
    }
}
void func_10023A10(void *, void *, s32);
extern void *D_80086C24[];
extern u8 D_8009BBF0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507EBB8 CURRENT (252) */
void func_1507EBB8(s32 arg0, s32 *arg1, s32 arg2) {
    s32 sp18;
    s32 temp_v0;
    u8 temp_a3;
    void *temp_t7;

    temp_t7 = D_80086C24[arg2];
    temp_a3 = D_8009BBF0[arg2];
    temp_v0 = *arg1;
    if ((temp_v0 + temp_a3) < 0x28) {
        sp18 = (s32) temp_a3;
        func_10023A10(temp_t7, (void *)(temp_v0 + arg0), (s32) temp_a3);
        *arg1 += temp_a3;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507EBB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EBB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EC38.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507EE58 CURRENT (644) */
void func_1507EE58(u8 arg0, u8 *arg1) {
    func_1507EEB8((s32) arg0, arg1);
    if (arg0 == 0x11) {
        func_1507EEB8(0x12, arg1);
        return;
    }
    if (arg0 == 0x12) {
        func_1507EEB8(0x11, arg1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507EE58 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EE58.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507EEB8 CURRENT (525) */
void func_1507EEB8(s32 arg0, u8 *arg1) {
    u8 temp_t7;
    u8 *temp_v0;

    temp_v0 = (void *)(arg1 + 4);
    temp_t7 = *(u8 *)((u8 *)temp_v0 + -1);
    *(u8 *)((u8 *)temp_v0 + -1) = (u8) *(u8 *)((u8 *)temp_v0 + -2);
    *(u8 *)((u8 *)temp_v0 + -2) = (u8) *(u8 *)((u8 *)temp_v0 + -3);
    *(u8 *)((u8 *)temp_v0 + -3) = (u8) *(u8 *)((u8 *)temp_v0 + -4);
    *(u8 *)((u8 *)arg1 + 4) = temp_t7;
    *(s8 *)((u8 *)arg1 + 0) = (s8) (arg0 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507EEB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EEB8.s")
extern void *D_800D154C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507EEF4 CURRENT (875) */
void func_1507EEF4(u32 arg0) {
    u8 *temp_v1;
    void *sp1C;
    u8 temp_v0;
    u8 *temp_v1_2;

    temp_v1 = (void *)(*(void **)((u8 *)D_800D154C + 0x31C));
    temp_v0 = *(u8 *)((u8 *)temp_v1 + 0x64);
    temp_v1_2 = (void *)(temp_v1 + 0x58);
    if (temp_v0 == 0) {
        *(s8 *)((u8 *)temp_v1_2 + 0xC) = 1;
        goto block_7;
    }
    if (temp_v0 == 1) {
        sp1C = temp_v1_2;
        func_150ADA20(arg0);
        if ((s32) *(u8 *)((u8 *)temp_v1_2 + 0xD) >= 3) {
            *(s8 *)((u8 *)temp_v1_2 + 0xC) = 2;
            goto block_7;
        }
    } else {
        sp1C = temp_v1_2;
        if ((s32) *(u8 *)((u8 *)temp_v1_2 + 0xD) >= ((func_150ADA20(arg0) & 3) + 8)) {
            *(s8 *)((u8 *)temp_v1_2 + 0xC) = 1;
block_7:
            *(u8 *)((u8 *)temp_v1_2 + 0xD) = 0U;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507EEF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EEF4.s")
void func_1507EFA0(s32 arg0, u8 *arg1) {
    s32 var_v0;
    u8 *var_v1;

    var_v0 = 4;
    var_v1 = arg1 + 4;
loop_1:
    var_v0 -= 1;
    if (arg0 == *var_v1) {
        *var_v1 = 0;
        return;
    }
    var_v1 -= 1;
    if (var_v0 < 0) {
        return;
    }
    goto loop_1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EFD0.s")
typedef struct GameAC030AnimationState {
    u8 pad0[4];
    u8 sequence;
    u8 frame;
} GameAC030AnimationState;

typedef struct GameAC030NestedState {
    u8 pad0[0x58];
    GameAC030AnimationState animation;
} GameAC030NestedState;

typedef struct GameAC030RootState {
    u8 pad0[0x31C];
    GameAC030NestedState *nested;
} GameAC030RootState;

extern u8 *D_80086BA0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507F454 CURRENT (95) */
s32 func_1507F454(void) {
    GameAC030AnimationState *animation;
    u8 sequence;
    s32 frame;

    animation = &((GameAC030RootState *)D_800D154C)->nested->animation;
    sequence = animation->sequence;
    if (sequence == 0) {
        return 1;
    }
    frame = animation->frame + 1;
    animation->frame = (u8)frame;
    if (D_80086BA0[sequence][frame & 0xFF] == 0) {
        animation->sequence = 0;
        animation->frame = 0;
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507F454 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507F454.s")
s32 func_1507F4C0(s32 arg0) {
    s32 sp20;
    s32 var_v1;
    u32 var_a0;
    u32 sp1C;

    if (arg0 == 0) {
        var_v1 = 0xB4;
        var_a0 = 0x3C;
        goto block_7;
    }
    if (D_800BE9F0 == 0x31) {
        return 0;
    }
    var_v1 = 0;
    if (arg0 == 1) {
        var_v1 = 0x3C;
        var_a0 = 0x3C;
    } else {
        var_a0 = 0x1E;
    }
block_7:
    sp20 = var_v1;
    sp1C = var_a0;
    return (func_150ADA20(var_a0) % var_a0) + var_v1;
}
void func_1505E650(u8 *, s32, s32, s32, f32, f32, s32);
extern u8 D_800B85A4[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507F54C CURRENT (705) */
void func_1507F54C(u8 *arg0) {
    s32 var_v0;
    u8 temp_v0;
    u8 temp_v1;

    temp_v1 = arg0[0x13C];
    if ((s32)temp_v1 >= 0x64) {
        temp_v0 = D_800B85A4[temp_v1 * 0x32C];
        switch (temp_v0) {
        default:
            var_v0 = 0xD8;
            break;
        case 0x57:
            var_v0 = 0x115;
            break;
        case 0x8C:
            var_v0 = 0x1A5;
            break;
        case 0xA8:
        case 0xA9:
            var_v0 = 0x1AF;
            break;
        case 0x89:
        case 0xBA:
            var_v0 = 0x1FA;
            break;
        }
        func_1505E650(arg0, var_v0 & 0xFFFF, 0x3F800000, 0x40800000,
                      0.0f, 0.0f, 0);
        return;
    }
    func_1505E650(arg0, 0xF, 0x3F800000, 0x40400000, 0.0f, 0.0f, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507F54C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507F54C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507F640.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FC2C.s")
void func_1507FC2C(void *);
void func_1507FF94(void *);
extern s32 D_800BE9E4;
extern u8 D_800C35EA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507FEA0 CURRENT (1655) */
void func_1507FEA0(void *arg0) {
    s16 temp_v0_2;
    u16 temp_a1_2;
    u8 temp_v1;
    void *temp_a1;
    void *temp_a1_3;
    void *temp_v0;

    temp_a1 = *(void **)((u8 *)arg0 + 0x31C);
    if ((temp_a1 != 0) && (*(u8 *)((u8 *)arg0 + 0x127) != 0xFF)) {
        temp_v1 = *(u8 *)((u8 *)arg0 + 0x13A);
        temp_v0 = (u8 *)temp_a1 + 0x58;
        if (temp_v1 != 0) {
            *(u8 *)((u8 *)arg0 + 0x13A) = temp_v1 - 1;
        }
        if ((*(u8 *)((u8 *)temp_a1 + 0x58) == 1) && (D_800C35EA != 1)) {
            temp_a1_2 = *(u16 *)((u8 *)temp_v0 + 2);
            if ((s32)temp_a1_2 < (0xFFFF - D_800BE9E4)) {
                *(u16 *)((u8 *)temp_v0 + 2) = temp_a1_2 + D_800BE9E4;
            }
        } else {
            *(u16 *)((u8 *)temp_v0 + 2) = 0;
            *(u8 *)((u8 *)temp_v0 + 4) = 0;
            *(u8 *)((u8 *)temp_v0 + 5) = 0;
            *(u8 *)((u8 *)temp_v0 + 0xC) = 0;
            *(u8 *)((u8 *)temp_v0 + 0xD) = 0;
        }
        temp_a1_3 = *(void **)((u8 *)arg0 + 0x31C);
        temp_v0_2 = *(s16 *)((u8 *)temp_a1_3 + 0x66);
        if (temp_v0_2 != 0) {
            if (D_800BE9E4 < temp_v0_2) {
                *(s16 *)((u8 *)temp_a1_3 + 0x66) = temp_v0_2 - D_800BE9E4;
            } else {
                func_1507FF94(arg0);
                *(s16 *)((u8 *)*(void **)((u8 *)arg0 + 0x31C) + 0x66) = 0;
            }
        }
        func_1507FC2C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507FEA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FEA0.s")
extern void func_15191B8C(u8 *arg0, s32 arg1, void *arg2);
extern void func_151494E0(s32 *arg0, s32 arg1);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507FF94 CURRENT (560) */
void func_1507FF94(void *arg0) {
    u8 sp24;
    void *sp20;
    void **sp1C;

    sp20 = arg0;
    sp1C = &sp20;
    sp24 = *(u8 *)((u8 *)arg0 + 0x3B);
    func_15191B8C((u8 *) &sp20, 0xD, arg0);
    func_151494E0((s32 *) sp1C, 0xD);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507FF94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FF94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FFD8.s")
