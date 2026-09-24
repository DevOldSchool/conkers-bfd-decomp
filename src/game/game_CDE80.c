#include "types.h"

/*
 * Reviewed source unit: src/game/game_CDE80.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A09D0
 * - func_150A0D8C
 * - func_150A104C
 * - func_150A11C4
 * - func_150A1DA0
 * - func_150A23E4
 * - func_150A24C0
 * - func_150A25D4
 * - func_150A2864
 * - func_150A29C8
 * - func_150A2AEC
 * - func_150A2CA4
 * - func_150A2D84
 * - func_150A2E4C
 * - func_150A2EE4
 * - func_150A2FA4
 * - func_150A3058
 * - func_150A3194
 * - func_150A32B4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A09D0.s")
f32 func_150AD780(f32);                             /* extern */
f32 func_150AD78C(f32);                             /* extern */
extern f32 D_8009F5A0;
extern f32 D_8009F5A4;

void func_150A0D14(void *arg0) {
    f32 temp_fs0;

    temp_fs0 = *(f32 *)((u8 *)arg0 + 0xC) * D_8009F5A0;
    *(f32 *)((u8 *)arg0 + 0x24) = func_150AD78C(temp_fs0);
    *(f32 *)((u8 *)arg0 + 0x28) = func_150AD780(temp_fs0);
    temp_fs0 = *(f32 *)((u8 *)arg0 + 0x10) * D_8009F5A4;
    *(f32 *)((u8 *)arg0 + 0x2C) = func_150AD78C(temp_fs0);
    *(f32 *)((u8 *)arg0 + 0x30) = func_150AD780(temp_fs0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A0D8C.s")
s32 func_150A1040(s32 arg0) {
    return arg0 + 0x400;
}
typedef struct {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0xC];
    f32 field2C;
    f32 field30;
    f32 field34;
    u8 pad38[0x148];
    f32 field180;
    u8 pad184[0x1A8];
} GameCDE80Actor;

s32 func_150A1DA0(GameCDE80Actor *, s32, s32);
extern f32 D_8009F5AC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A104C CURRENT (354) */
void func_150A104C(u8 *arg0, s32 *arg1, s32 arg2) {
    GameCDE80Actor actor;
    u8 *entry;
    s16 height;

    actor.x = *(f32 *)(arg0 + 0x2F8);
    actor.y = *(f32 *)(arg0 + 0x2FC);
    actor.z = *(f32 *)(arg0 + 0x300);
    actor.field180 = actor.y;
    actor.field2C = *(f32 *)(arg0 + 0x304);
    actor.field30 = *(f32 *)(arg0 + 0x308);
    actor.field34 = *(f32 *)(arg0 + 0x30C);
    *(f32 *)(arg0 + 0x364) = D_8009F5AC;
    *(s32 *)(arg0 + 0x84) &= ~0x40000;
    while (arg2 != 0) {
        if (*arg1 != 0 && func_150A1DA0(&actor, *arg1, 0) == 0) {
            entry = (u8 *)*arg1;
            if ((entry[0x15] >> 2) == 1) {
                switch (entry[0x17]) {
                case 2:
                    height = *(s16 *)(entry + 8);
                    *(f32 *)(arg0 + 0x364) = (f32)(height + *(s16 *)(entry + 2));
                    break;
                case 0:
                    *(s32 *)(arg0 + 0x84) |= 0x40000;
                    break;
                case 6:
                    *(s32 *)(arg0 + 0x84) &= ~0x40000;
                    break;
                }
            }
        }
        arg2--;
        arg1++;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A104C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A104C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A11C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A1DA0.s")
/* Call context: func_1000FA64: unique active project prototype */
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A23E4 CURRENT (265) */
void func_150A23E4(void *arg0) {
    s32 var_t0;
    s32 var_v1;
    u32 temp_v0;
    u8 temp_t1;

    if (*(s32 *)((u8 *)arg0 + 0x20) == 0) {
        var_v1 = 0;
        var_t0 = 8;
        if (!(*(u8 *)((u8 *)arg0 + 0x15) & 3)) {
            var_v1 = 0x8000;
        }
        temp_t1 = *(u8 *)((u8 *)arg0 + 0x17);
        if (((s32) temp_t1 >> 7) != 0) {
            var_t0 = 0x108;
        }
        temp_v0 = *(u32 *)((u8 *)arg0 + 0x1C);
        func_1000FA64((temp_v0 >> 0x10) & 0xFFFF, (s32) *(s16 *)((u8 *)arg0 + 0), (s32) *(s16 *)((u8 *)arg0 + 2), (s32) *(s16 *)((u8 *)arg0 + 4), (temp_t1 & 0x7F) * 0x147, *(s32 *)((u8 *)arg0 + 0x18) | var_v1, temp_v0 & 0xFFFF, 0, 0, 0, var_t0, 0);
        *(s32 *)((u8 *)arg0 + 0x20) = 1;
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x20) = 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A23E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A23E4.s")
s32 func_15183290(s16, s32, s16, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A24C0 CURRENT (1541) */
void func_150A24C0(void *arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;

    if (arg1 != 0xFF) {
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x1C);
        {
            s32 temp_a0 = temp_v1 & 0xFF;
        if ((temp_a0 == 0) || (*(u8 *)((u8 *)arg0 + 0x17) == 9)) {
            temp_v0 = func_15183290(*(s16 *)((u8 *)arg0 + 0), *(s16 *)((u8 *)arg0 + 2) + (*(u8 *)((u8 *)arg0 + 0x1D) * 0x10), *(s16 *)((u8 *)arg0 + 4), *(s32 *)((u8 *)arg0 + 0x18) & 0xFF, (s32) *(u8 *)((u8 *)arg0 + 0x17), (s32) *(s16 *)((u8 *)arg0 + 6), arg1, (s32) (s16) *(s32 *)((u8 *)arg0 + 0x18), (s32) *(u8 *)((u8 *)arg0 + 0x1A), (s32) (u8) *(s32 *)((u8 *)arg0 + 0x1C), *(s32 *)((u8 *)arg0 + 0x20));
            if ((temp_v0 != -1) && (*(u8 *)((u8 *)arg0 + 0x17) != 9)) {
                *(s32 *)((u8 *)arg0 + 0x1C) = (s32) ((temp_v0 << 8) | 0xF0 | (*(s32 *)((u8 *)arg0 + 0x1C) & 0xFFFF0000));
            }
        } else {
            var_v0 = temp_a0;
            if (temp_a0 < 2) {
                var_v0 = 2;
            }
            *(s32 *)((u8 *)arg0 + 0x1C) = (s32) ((temp_v1 & ~0xFF) | var_v0);
        }
    }
        }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A24C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A24C0.s")
typedef struct GameA25D4Event {
    u8 pad0[0x17];
    u8 type;
    s32 value18;
    s32 value1C;
    s32 value20;
} GameA25D4Event;

typedef struct GameA25D4Color {
    u8 r;
    u8 g;
    u8 b;
} GameA25D4Color;

void func_150E7290(s32, s32, s32);
void func_150E68B0(void *, s32, void *, u8);
void func_10010344(s32, void *, s32, s32, s32);
void func_151C8674(void *, s32);
void func_1515F270(void *, void *);
void func_151CE51C(void *, void *);
extern GameA25D4Color D_800D9EB8[];
extern u8 D_800D3090;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A25D4 CURRENT (1950) */
void func_150A25D4(GameA25D4Event *arg0, void *arg1, s32 arg2,
                    s32 arg3, s32 arg4, s32 arg5) {
    u16 value;
    u8 timer;
    GameA25D4Color *color;

    switch (arg0->type) {
    case 0:
        break;
    case 1:
        if (arg2 != 0xFF) {
            func_150E7290(arg2, 0xFF, 0);
        }
        break;
    case 2:
        if (arg2 != 0xFF) {
            color = &D_800D9EB8[arg2];
            color->r = arg0->value18;
            color->g = arg0->value1C;
            color->b = arg0->value20;
        }
        break;
    case 3:
        if (arg2 != 0xFF) {
            func_150E68B0(arg1, arg2, arg0, ((u8 *)&arg0->value18)[3]);
        }
        break;
    case 6:
        if (!(arg5 & 1)) {
            D_800D3090 = 0x1E;
            func_10010344(0x66F, arg1, 0x5DC0, 0x190, 0x1F4);
        }
        timer = (D_800D3090 + D_800BE9E4) & 0xFF;
        D_800D3090 = timer;
        if (timer < 0x1F) {
            return;
        }
        value = *(u16 *)((u8 *)arg1 + 0xB2);
        if (value >= 0x5A1) {
            *(u16 *)((u8 *)arg1 + 0xB2) = 0x4B0;
        } else if (value < 0xF1) {
            *(u16 *)((u8 *)arg1 + 0xB2) = 0x5A;
        } else {
            *(u16 *)((u8 *)arg1 + 0xB2) = value - 0xF0;
        }
        D_800D3090 = 0;
        break;
    case 8:
        func_151C8674(arg1, (s32)arg0);
        break;
    case 9:
        func_1515F270(arg1, arg0);
        break;
    case 10:
        func_151CE51C(arg1, arg0);
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A25D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A25D4.s")
s32 func_150A1DA0();
void func_15172E7C(void *, u8, s32);
extern u32 D_800D3094;
extern s32 D_800D3098;

void func_150A278C(void *arg0) {
    s32 offset;
    u32 index;
    u8 *entry;

    if (*(u8 *)((u8 *)arg0 + 0x65) == 0) {
        index = 0;
        offset = 0;
        if (D_800D3094 != 0) {
            do {
                if (((*(u8 *)((u8 *)D_800D3098 + offset + 0x15) >> 2) == 8) &&
                    (func_150A1DA0(arg0, offset + D_800D3098, 0) == 0)) {
                    entry = (u8 *)D_800D3098 + offset;
                    func_15172E7C(arg0, entry[0x17], *(s32 *)(entry + 0x18));
                }
                index++;
                offset += 0x34;
            } while (index < D_800D3094);
        }
    }
}
u64 func_100268A4(s32, s32, s32, s32);
extern u8 D_800D30F0[];
extern u8 D_800D3270[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A2864 CURRENT (2892) */
void func_150A2864(s32 arg0, s32 arg1) {
    u32 index;

    index = arg0 & 0xFFF;
    if (index < D_800D3094) {
        *(s8 *)((u8 *)D_800D3098 + index * 0x34 + 0x14) = arg1;
    }
    if (arg1 == 1) {
        u8 *row;
        s32 group_offset;
        volatile s32 word_index;
        volatile s32 within_group;

        row = D_800D30F0;
        word_index = 0;
        within_group = index & 0x3F;
        group_offset = (index >> 6) * 8;
        do {
            u64 mask;
            u32 *words;
            s32 first;
            s32 second;

            mask = func_100268A4(0, 1, word_index, within_group);
            words = (u32 *)(row + group_offset);
            first = words[0];
            second = words[1];
            row += 0x18;
            words[1] = second & ~(u32)mask;
            words[0] = first & ~mask;
        } while (row != D_800D3270);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A2864 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2864.s")

void func_150A2940(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    u32 temp_t6;

    arg0 &= 0xFFF;
    temp_t6 = arg0;
    if (temp_t6 < (u32) D_800D3094) {
        if (arg1 != -1) {
            *(s32 *)((u8 *)(D_800D3098 + (temp_t6 * 0x34)) + 0x18) = arg1;
        }
        temp_v0 = temp_t6 * 0x34;
        if (arg2 != -1) {
            *(s8 *)((u8 *)(D_800D3098 + temp_v0) + 0x17) = arg2;
        }
        *(s32 *)((u8 *)(D_800D3098 + temp_v0) + 0x1C) = 0;
    }
}
u64 func_10026800(s32, s32, s32, s32);
extern u16 D_800D2340;
extern u8 D_800D30F4[];
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A29C8 CURRENT (485) */
s32 func_150A29C8(u32 arg0, s32 arg1) {
    s32 temp_t7;

    arg1 &= 0xFFF;
    if (D_800D3094 < (u32)arg1) {
        return 1;
    }
    if ((arg0 < 0x10U) && (D_800D2340 & (1 << arg0))) {
        temp_t7 = (arg0 * 0x18) + (((u32)arg1 >> 6) * 8);
        if ((u32)func_10026800(*(s32 *)(D_800D30F0 + temp_t7),
                                *(s32 *)(D_800D30F4 + temp_t7), 0,
                                arg1 & 0x3F) & 1) {
            return 0;
        }
        return 1;
    }
    return func_150A1DA0((arg0 * 0x32C) + &D_800CC2D0,
                          (arg1 * 0x34) + D_800D3098, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A29C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A29C8.s")
u64 func_10026800(s32, s32, s32, s32);

typedef struct GameA2AECRow {
    s32 words[6];
} GameA2AECRow;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A2AEC CURRENT (2690) */
u32 func_150A2AEC(u32 arg0, s32 arg1, s32 *arg2) {
    s32 *entry;
    s32 current;
    u32 index;
    s32 count;
    u8 *row;

    if (arg0 < 0x10U && (D_800D2340 & (1 << arg0))) {
        count = 0;
        if (arg1 > 0) {
            entry = arg2;
            do {
                current = *entry;
                index = current & 0xFFF;
                if (index < D_800D3094) {
                    row = (u8 *)&((GameA2AECRow *)D_800D30F0)[arg0]
                          + (index >> 6) * 8;
                    if ((u32)func_10026800(*(s32 *)row, *(s32 *)(row + 4),
                                             0, index & 0x3F) & 1) {
                        return index;
                    }
                }
                count++;
                entry++;
            } while (count != arg1);
        }
    } else {
        count = 0;
        entry = arg2;
        if (arg1 > 0) {
            do {
                current = *entry;
                index = current & 0xFFF;
                if (index < D_800D3094 &&
                    func_150A1DA0((GameCDE80Actor *)((u8 *)&D_800CC2D0 + arg0 * 0x32C),
                                   D_800D3098 + index * 0x34, 1) == 0) {
                    return index;
                }
                count++;
                entry++;
            } while (count != arg1);
        }
    }
    return -1U;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A2AEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2AEC.s")
u64 func_10026800(s32, s32, s32, s32);
extern u8 D_800D2138[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A2CA4 CURRENT (1849) */
s32 func_150A2CA4(s32 arg0) {
    s32 temp_t2;
    register s32 limit;
    s32 var_s0;
    u32 temp_t6;
    u8 *temp_t6_2;
    register u8 *temp_s2;
    register u8 *temp_s3;

    arg0 &= 0xFFF;
    temp_t6 = arg0;
    var_s0 = 0;
    if (D_800D3094 < temp_t6) {
        return -1;
    }
    temp_s2 = D_800D2138;
    temp_s3 = D_800D30F0;
    limit = 0x10;
    do {
        if (*(u16 *)(temp_s2 + 0x208) & (1 << var_s0)) {
            temp_t2 = ((var_s0 * 4) - var_s0) << 3;
            temp_t6_2 = temp_s3 + temp_t2 + ((temp_t6 >> 6) * 8);
            if ((u32)func_10026800(*(s32 *)temp_t6_2, *(s32 *)(temp_t6_2 + 4),
                                  0, temp_t6 & 0x3F) & 1) {
                return var_s0;
            }
        }
        var_s0 += 1;
    } while (var_s0 != limit);
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A2CA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2CA4.s")
typedef struct GameCDE80ActorSnapshot {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0xC];
    f32 field_2C;
    f32 field_30;
    f32 field_34;
    u8 pad38[0x148];
    f32 field_180;
    u8 pad184[0x1AC];
} GameCDE80ActorSnapshot;

extern s32 D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A2D84 CURRENT (618) */
s32 func_150A2D84(s32 arg0, s32 arg1) {
    GameCDE80ActorSnapshot actor;
    u32 index;
    u8 *source;

    index = arg1 & 0xFFF;
    source = (u8 *) (D_800DBFF0 + (arg0 * 0x9A0));
    if ((u32) D_800D3094 < index) {
        return 1;
    }
    actor.x = *(f32 *) (source + 0x2F8);
    actor.y = *(f32 *) (source + 0x2FC);
    actor.z = *(f32 *) (source + 0x300);
    actor.field_180 = actor.y;
    actor.field_2C = *(f32 *) (source + 0x304);
    actor.field_30 = *(f32 *) (source + 0x308);
    actor.field_34 = *(f32 *) (source + 0x30C);
    return func_150A1DA0(&actor, D_800D3098 + (index * 0x34), 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A2D84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2D84.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A2E4C CURRENT (2248) */
s32 func_150A2E4C(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fa1;

    temp_fa1 = arg2 - (f32) *(s16 *)((u8 *)arg0 + 2);
    arg3 = temp_fa1 - (f32) *(s16 *)((u8 *)arg0 + 4);
    if (((((arg3 * *(f32 *)((u8 *)arg0 + 0x30)) + ((arg1 - (f32) *(s16 *)((u8 *)arg0 + 0)) * *(f32 *)((u8 *)arg0 + 0x2C))) * *(f32 *)((u8 *)arg0 + 0x28)) - (temp_fa1 * *(f32 *)((u8 *)arg0 + 0x24))) <= 0.0f) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A2E4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2E4C.s")
s32 func_150A2E4C(s32, f32, f32, f32);
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A2EE4 CURRENT (2525) */
s32 func_150A2EE4(s32 arg0, s32 arg1) {
    u32 index;
    s32 offset;
    u8 *descriptor;
    u8 *actor;

    index = (u32)arg1 & 0xFFF;
    if ((u32)D_800D3094 < index) {
        return 1;
    }
    offset = index * 0x34;
    if ((*(u8 *)((u8 *)D_800D3098 + offset + 0x15) & 3) != 3) {
        return 0;
    }
    descriptor = (u8 *)D_800D3098 + offset;
    actor = (u8 *)&D_800CC2D0 + arg0 * 0x32C;
    return func_150A2E4C(offset, *(f32 *)(actor + 0x14),
                         *(f32 *)(actor + 0x18), *(f32 *)(actor + 0x1C));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A2EE4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2EE4.s")
extern s32 D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A2FA4 CURRENT (495) */
s32 func_150A2FA4(s32 arg0, s32 arg1) {
    s32 temp_t0;
    u32 temp_t8;
    u8 *temp_v0;

    temp_t8 = arg1 & 0xFFF;
    temp_v0 = (void *)((arg0 * 0x9A0) + D_800DBFF0);
    if ((u32) D_800D3094 < temp_t8) {
        return 1;
    }
    temp_t0 = temp_t8 * 0x34;
    if ((*(u8 *)((u8 *)(D_800D3098 + temp_t0) + 0x15) & 3) == 3) {
        return func_150A2E4C(temp_t0 + D_800D3098, *(f32 *)((u8 *)temp_v0 + 0x2F8), *(f32 *)((u8 *)temp_v0 + 0x2FC), *(f32 *)((u8 *)temp_v0 + 0x300));
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A2FA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2FA4.s")
typedef struct {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0xC];
    f32 field2C;
    f32 field30;
    f32 field34;
    u8 pad38[0x148];
    f32 field180;
    u8 pad184[0x1A8];
} GameCDE80Actor3058;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A3058 CURRENT (2087) */
s32 func_150A3058(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    GameCDE80Actor3058 actor;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_s0;
    u32 var_s1;
    u8 *temp_v0;
    register GameCDE80Actor3058 *actor_ptr;

    temp_fv0 = (f32)arg2;
    var_s1 = 0;
    temp_fv1 = (f32)arg1;
    actor.y = temp_fv0;
    actor.field180 = temp_fv0;
    actor.field30 = temp_fv0;
    var_s0 = 0;
    temp_fa0 = (f32)arg3;
    actor.x = temp_fv1;
    actor.field2C = temp_fv1;
    actor.z = temp_fa0;
    actor.field34 = temp_fa0;
    actor_ptr = &actor;
    if (D_800D3094 != 0) {
loop_1:
        temp_v0 = (u8 *)D_800D3098 + var_s0;
        if ((temp_v0[0x14] == 0) &&
            (((s32)temp_v0[0x15] >> 2) == 3) &&
            (arg0 == temp_v0[0x17]) &&
            (func_150A1DA0(actor_ptr, var_s0 + D_800D3098, 0) == 0)) {
            return 1;
        }
        var_s1++;
        var_s0 += 0x34;
        if (var_s1 >= D_800D3094) {
            goto block_7;
        }
        goto loop_1;
    }
block_7:
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A3058 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A3058.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A3194 CURRENT (2346) */
s32 func_150A3194(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    GameCDE80Actor actor;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_s0;
    u32 var_s1;
    u8 *temp_v0;

    temp_fv0 = (f32)arg3;
    var_s1 = 0;
    temp_fv1 = (f32)arg2;
    actor.y = temp_fv0;
    actor.field180 = temp_fv0;
    actor.field30 = temp_fv0;
    var_s0 = 0;
    temp_fa0 = (f32)arg4;
    actor.x = temp_fv1;
    actor.field2C = temp_fv1;
    actor.z = temp_fa0;
    actor.field34 = temp_fa0;
    if (D_800D3094 != 0) {
loop_1:
        temp_v0 = (u8 *)D_800D3098 + var_s0;
        if ((temp_v0[0x14] == 0) &&
            (arg0 == ((s32)temp_v0[0x15] >> 2)) &&
            (arg1 == temp_v0[0x17]) &&
            (func_150A1DA0(&actor, var_s0 + D_800D3098, 0) == 0)) {
            return var_s0 + D_800D3098;
        }
        var_s1++;
        var_s0 += 0x34;
        if (var_s1 >= D_800D3094) {
            goto block_7;
        }
        goto loop_1;
    }
block_7:
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A3194 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A3194.s")

s32 func_150A1DA0(GameCDE80Actor *, s32, s32); /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A32B4 CURRENT (70) */
s32 func_150A32B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    GameCDE80Actor actor;
    f32 temp;

    temp = (f32) arg3;
    actor.z = temp;
    actor.field34 = temp;
    temp = (f32) arg2;
    actor.y = temp;
    actor.field180 = temp;
    actor.field30 = temp;
    temp = (f32) arg1;
    actor.x = temp;
    actor.field2C = temp;
    if (func_150A1DA0(&actor, arg0, 0) == 0) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A32B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A32B4.s")
extern s32 D_800D3098;

void func_150A3330(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x34;
    *arg1 = (s32) *(u8 *)((u8 *)(D_800D3098 + temp_v0) + 0x17);
    *arg2 = *(s32 *)((u8 *)(D_800D3098 + temp_v0) + 0x18);
    *arg3 = *(s32 *)((u8 *)(D_800D3098 + temp_v0) + 0x1C);
    *arg4 = *(s32 *)((u8 *)(D_800D3098 + temp_v0) + 0x20);
}
void func_150A3398(s32 arg0, u16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg1 & 1) {
        *(s8 *)((u8 *)(D_800D3098 + (arg0 * 0x34)) + 0x17) = arg2;
    }
    if (arg1 & 2) {
        *(s32 *)((u8 *)(D_800D3098 + (arg0 * 0x34)) + 0x18) = arg3;
    }
    if (arg1 & 4) {
        *(s32 *)((u8 *)(D_800D3098 + (arg0 * 0x34)) + 0x1C) = arg4;
    }
    if (arg1 & 8) {
        *(s32 *)((u8 *)(D_800D3098 + (arg0 * 0x34)) + 0x20) = arg5;
    }
}
void func_150A3444(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 offset;

    offset = arg0 * 0x34;
    *(s16 *)(D_800D3098 + offset) = arg1;
    *(s16 *)(D_800D3098 + offset + 2) = arg2;
    *(s16 *)(D_800D3098 + offset + 4) = arg3;
}
