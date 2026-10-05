#include "types.h"

/*
 * Reviewed source unit: src/game/game_AC030.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507EEB8
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

void func_1507EBB8(s32 arg0, s32 *arg1, s32 arg2) {
    struct { s32 count; void *source; } copy;

    copy.source = D_80086C24[arg2];
    copy.count = D_8009BBF0[arg2];
    if ((*arg1 + copy.count) < 0x28) {
        func_10023A10(copy.source, (void *)(*arg1 + arg0), (s32) copy.count);
        *arg1 += copy.count;
    }
}
s32 func_1507EC38(u8 *candidates, s32 candidate_count, u8 *output,
                   s32 *output_count, u8 *history) {
    s32 result;
    s32 i;
    s32 j;
    s32 duplicate;
    s32 scratch_count;
    u8 scratch[5];
    s32 take;

    result = 0;
    *output_count = 0;
    i = 0;
    if (candidate_count > 0) {
        do {
            duplicate = 0;
            for (j = 0; j < *output_count; j++) {
                if (output[j] == candidates[i]) {
                    duplicate = 1;
                    break;
                }
            }
            if (duplicate == 0) {
                for (j = 0; j != 5; j++) {
                    if (history[j] == candidates[i]) {
                        duplicate = 1;
                        break;
                    }
                }
                if (duplicate == 0) {
                    output[*output_count] = candidates[i];
                    *output_count += 1;
                }
            }
            i++;
        } while (i != candidate_count);
    }
    scratch_count = 0;
    if (*output_count == 0) {
        for (i = 0; i < 5; i++) {
            if (history[i] != 0) {
                j = 0;
                if (candidate_count > 0) {
                    do {
                        if (history[i] == candidates[j]) {
                            scratch[scratch_count] = history[i];
                            scratch_count++;
                            break;
                        }
                        j++;
                    } while (j != candidate_count);
                }
            }
        }
        if (scratch_count == 0) {
            output[0] = 0;
            *output_count = 1;
        } else {
            take = scratch_count >> 1;
            if (take == 0) {
                take = 1;
            }
            while (take != 0) {
                scratch_count--;
                output[*output_count] = scratch[scratch_count];
                *output_count += 1;
                take--;
            }
            result = 1;
        }
    }
    return result;
}
void func_1507EE58(volatile u8 arg0, u8 *arg1) {
    s32 value;

    func_1507EEB8(arg0, arg1);
    value = arg0;
    if (value == 0x11) {
        func_1507EEB8(0x12, arg1);
        return;
    }
    if (value == 0x12) {
        func_1507EEB8(0x11, arg1);
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507EEB8 CURRENT (330) */
void func_1507EEB8(u8 arg0, u8 *arg1) {
    u8 temp_t7;
    u8 temp_t8;
    u8 temp_t9;
    u8 temp_t0;
    u8 *temp_v0;

    temp_v0 = (void *)(arg1 + 4);
    temp_t8 = *(u8 *)((u8 *)temp_v0 + -2);
    temp_t9 = *(u8 *)((u8 *)temp_v0 + -3);
    temp_t0 = *(u8 *)((u8 *)temp_v0 + -4);
    temp_t7 = *(u8 *)((u8 *)temp_v0 + -1);
    *(u8 *)((u8 *)temp_v0 + -1) = temp_t8;
    *(u8 *)((u8 *)temp_v0 + -2) = temp_t9;
    *(u8 *)((u8 *)temp_v0 + -3) = temp_t0;
    *(u8 *)((u8 *)arg1 + 4) = temp_t7;
    *(s8 *)((u8 *)arg1 + 0) = (s8) arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507EEB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EEB8.s")
extern void *D_800D154C;

void func_1507EEF4(u32 arg0) {
    u8 *temp_v1;
    void *sp1C;
    s32 temp_v0;

    temp_v1 = (void *)(*(void **)((u8 *)D_800D154C + 0x31C));
    temp_v0 = *(u8 *)((u8 *)temp_v1 + 0x64);
    temp_v1 += 0x58;
    if (temp_v0 == 0) {
        *(s8 *)((u8 *)temp_v1 + 0xC) = 1;
        *(u8 *)((u8 *)temp_v1 + 0xD) = 0;
        return;
    }
    if (temp_v0 == 1) {
        sp1C = temp_v1;
        func_150ADA20(arg0);
        if ((s32) *(u8 *)((u8 *)temp_v1 + 0xD) >= 3) {
            *(s8 *)((u8 *)temp_v1 + 0xC) = 2;
            *(u8 *)((u8 *)temp_v1 + 0xD) = 0;
            return;
        }
    } else {
        sp1C = temp_v1;
        if ((s32) *(u8 *)((u8 *)temp_v1 + 0xD) >= ((s32)(func_150ADA20(arg0) & 3) + 8)) {
            *(s8 *)((u8 *)temp_v1 + 0xC) = 1;
            *(u8 *)((u8 *)temp_v1 + 0xD) = 0U;
        }
    }
}
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
typedef struct GameFC2CFrame { u8 pad0[6]; u8 flags; u8 pad7; } GameFC2CFrame;
typedef struct GameFC2CSequence { u8 pad0[4]; u8 id; u8 frame; u8 flags; u8 pad7; } GameFC2CSequence;
extern GameFC2CFrame D_8009B8B0[];
extern s32 D_800418B0[][16];
extern u8 D_800419A0;
extern s32 D_800D18C4;
void func_1000E7A0(u32, s32);
void func_1000E8C4(s32, s32);
void func_1000D96C(s32, s32, s32);
void func_1000DE1C(s32, s32);
void func_100109D0(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507FC2C CURRENT (2919) */
void func_1507FC2C(void *volatile arg0) {
    GameFC2CSequence *sequence;
    GameFC2CFrame *frame;
    s32 flags;
    s32 old;
    s32 changed;
    s32 enabled;
    s32 id;
    s32 previous_sound;
    f32 fade;
    u8 *intensity;

    flags = 0;
    sequence = (GameFC2CSequence *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x58);
    id = sequence->id;
    if (id != 0) {
        frame = &D_8009B8B0[D_80086BA0[id & 0xFF][sequence->frame]];
        flags = frame->flags;
    }
    if (flags & 0x10) {
        fade = (f32)D_800418B0[D_800419A0][0];
        intensity = arg0;
        if (fade >= 0.0f) {
            intensity = *(u8 **)(intensity + 0x2D0);
            *(f32 *)(intensity + 8) = *(f32 *)(intensity + 0x18) * (32768.0f - fade) / 32768.0f;
        }
    }
    old = sequence->flags;
    changed = flags ^ old;
    if (flags != old) {
        enabled = changed & flags;
        if ((enabled & 1) == 1) *(u16 *)((u8 *)arg0 + 0x2F8) |= 1;
        else if ((changed & old & 1) == 1) *(u16 *)((u8 *)arg0 + 0x2F8) &= 0xFFFE;
        if ((enabled & 2) == 2) func_1000E7A0(1, 0);
        else if ((changed & old & 2) == 2) func_1000E8C4(1, id);
        if ((enabled & 4) == 4) {
            previous_sound = D_800D18C4;
            if (previous_sound == 0) D_800D18C4 = 0x15;
            else {
                D_800D18C4 = (u32)previous_sound + 1;
                if ((previous_sound ^ 0x17) == 0) D_800D18C4 = 0x15;
            }
            func_1000D96C(D_800D18C4, 0, 0);
        } else if ((changed & old & 4) == 4) func_1000DE1C(D_800D18C4, 0);
        if ((enabled & 8) != 8 && (changed & old & 8) == 8) func_100109D0((s32)arg0);
        sequence->flags = flags;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507FC2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FC2C.s")

void func_1507FC2C(void *volatile);
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507FF94 CURRENT (300) */
void func_1507FF94(void *arg0) {
    struct {
        void *object;
        u8 kind;
    } descriptor;
    void *sp1C;

    descriptor.object = arg0;
    descriptor.kind = *(u8 *)((u8 *)arg0 + 0x3B);
    sp1C = &descriptor;
    func_15191B8C((u8 *)sp1C, 0xD, arg0);
    func_151494E0((s32 *) sp1C, 0xD);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507FF94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FF94.s")
typedef struct GameAC030Position {
    u8 pad0[0x14];
    f32 position[3];
} GameAC030Position;

typedef struct GameAC030Target {
    u8 pad0[8];
    struct GameAC030Target *next;
    u8 padC[0x8C];
    f32 position[3];
} GameAC030Target;

typedef struct GameAC030TargetGroups {
    s32 entries[3];
} GameAC030TargetGroups;

s32 func_150A3194(s32, s32, s32, s32, s32);
s32 func_15037698(s32, s32, s32, f32, f32, f32, f32 *, f32, s32, s32);
extern GameAC030TargetGroups D_80086C50;
extern f32 D_8009BD04;
extern u8 D_800CC2D0[];
extern GameAC030Target *D_800DCE50[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507FFD8 CURRENT (1911) */
s32 func_1507FFD8(void *arg0) {
    f32 dz;
    f32 z;
    f32 limit;
    GameAC030TargetGroups groups;
    f32 x;
    f32 y;
    f32 dx;
    f32 dy;
    f32 output[3];
    register f32 squared;
    s32 *group;
    GameAC030Target *target;
    s32 *end;

    if (func_150A3194(4, 5, (s32)((GameAC030Position *)arg0)->position[0],
                           (s32)((GameAC030Position *)arg0)->position[1],
                           (s32)((GameAC030Position *)arg0)->position[2]) ||
        func_150A3194(4, 11, (s32)((GameAC030Position *)arg0)->position[0],
                               (s32)((GameAC030Position *)arg0)->position[1],
                               (s32)((GameAC030Position *)arg0)->position[2])) {
        groups = D_80086C50;
        limit = D_8009BD04;
        group = groups.entries;
        end = groups.entries + 3;
        do {
            target = D_800DCE50[*group];
            if (target != 0) {
                do {
                    x = target->position[0];
                    y = target->position[1];
                    dx = x - ((GameAC030Position *)arg0)->position[0];
                    z = target->position[2];
                    dy = y - ((GameAC030Position *)arg0)->position[1];
                    dz = z - ((GameAC030Position *)arg0)->position[2];
                    squared = dx * dx + dy * dy + dz * dz;
                    if ((squared < limit) &&
                        func_15037698(((u8 *)arg0 - D_800CC2D0) / 812,
                                      0, 0, x, y, z, output, 90.0f, 0, 0) != 0) {
                        return 1;
                    }
                    target = target->next;
                } while (target != 0);
            }
            group++;
        } while (group != end);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507FFD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FFD8.s")
