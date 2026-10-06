#include "types.h"

/*
 * Reviewed source unit: src/game/game_130CB0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15103828
 * - func_15103910
 * - func_15103AA0
 * - func_15103C14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *arg0, s32 arg1);
extern u16 D_800D9AB0[];
extern u16 D_800D9AB4[];
extern s32 D_800BE9E4;

void func_15103800(void) {
    func_100226F0(D_800D9AB0, 8);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15103828 CURRENT (2160) */
void func_15103828(void) {
    u16 temp_v1;

    temp_v1 = D_800D9AB0[0];
    if (temp_v1 != 0) {
        if (D_800BE9E4 < temp_v1) {
            D_800D9AB0[0] = temp_v1 - D_800BE9E4;
        } else {
            D_800D9AB0[0] = 0;
        }
    }
    temp_v1 = D_800D9AB0[1];
    if (temp_v1 != 0) {
        if (D_800BE9E4 < temp_v1) {
            D_800D9AB0[1] = temp_v1 - D_800BE9E4;
        } else {
            D_800D9AB0[1] = 0;
        }
    }
    temp_v1 = D_800D9AB4[0];
    if (temp_v1 != 0) {
        if (D_800BE9E4 < temp_v1) {
            D_800D9AB4[0] = temp_v1 - D_800BE9E4;
        } else {
            D_800D9AB4[0] = 0;
        }
    }
    temp_v1 = D_800D9AB4[1];
    if (temp_v1 != 0) {
        if (D_800BE9E4 < temp_v1) {
            D_800D9AB4[1] = temp_v1 - D_800BE9E4;
            return;
        }
        D_800D9AB4[1] = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15103828 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103828.s")
/* Call context: func_10010344: unique active project prototype */
/* Call context: func_100111C8: unique active project prototype */
s32 func_10010344(s32, s32, u32, s16, s32);
void func_100111C8(s32, u16);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15103910 CURRENT (1725) */
s32 func_15103910(void *arg0, s32 *arg1, u32 *arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    s16 var_a3;
    s32 temp_t3;
    s32 temp_v1;
    u16 temp_a0;
    u16 temp_v0;
    u16 temp_v0_2;
    void *temp_s1;

    temp_s1 = *(void **)((u8 *)arg0 + 0x1C);
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x18);
    var_a3 = (s16) temp_v1;
    *(s16 *)((u8 *)arg0 + 2) = (s16) (s32) *(f32 *)((u8 *)temp_s1 + 0x14);
    *(s16 *)((u8 *)arg0 + 4) = (s16) (s32) *(f32 *)((u8 *)temp_s1 + 0x18);
    *(s16 *)((u8 *)arg0 + 6) = (s16) (s32) *(f32 *)((u8 *)temp_s1 + 0x1C);
    if (var_a3 != 0) {
        temp_v0 = *arg6;
        if (temp_v0 != 0) {
            *(s32 *)((u8 *)arg0 + 0x18) = (s32) ((temp_v0 << 0x10) | (temp_v1 & 0xFFFF));
            *(s16 *)((u8 *)arg0 + 0) = 0;
            *arg6 = 0;
            func_10010344(0x5B0, (s32) temp_s1, 0x61A8U, 0x64, 0x78);
            goto block_11;
        }
        temp_t3 = temp_v1 >> 0x10;
        var_a3 -= D_800BE9E4;
        if (var_a3 <= 0) {
            *arg6 = (u16) temp_t3;
            *(s16 *)((u8 *)arg0 + 0) = (s16) temp_t3;
            *arg2 = *(u32 *)((u8 *)arg0 + 0xC);
            *arg1 = 1;
            *(s32 *)((u8 *)arg0 + 0x18) = 0;
            return 0;
        }
        goto block_10;
    }
    *arg2 = *(u32 *)((u8 *)arg0 + 0xC);
    *arg1 = 1;
    temp_v0_2 = *(u16 *)((u8 *)arg0 + 0x24);
    if (temp_v0_2 == 0) {
        func_10010344(0x5B1, (s32) temp_s1, *(u32 *)((u8 *)arg0 + 0xC), *(s16 *)((u8 *)arg0 + 0xA), (s32) *(u16 *)((u8 *)arg0 + 8));
        return 1;
    }
    temp_a0 = *(u16 *)((u8 *)temp_s1 + 0x8C);
    if (temp_v0_2 != temp_a0) {
        func_100111C8((s32) temp_a0, (u16) temp_s1);
        *(u16 *)((u8 *)temp_s1 + 0x8C) = (u16) *(u16 *)((u8 *)arg0 + 0x24);
    }
    *(s32 *)((u8 *)arg0 + 0x10) = (s32) (*(s32 *)((u8 *)arg0 + 0x10) & ~0x80);
block_10:
    *(s32 *)((u8 *)arg0 + 0x18) = (s32) ((*(s32 *)((u8 *)arg0 + 0x18) & 0xFFFF0000) | var_a3);
block_11:
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15103910 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103910.s")
typedef struct Game130CB0Source {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
} Game130CB0Source;

typedef struct Game130CB0Record {
    s16 field0;
    s16 x;
    s16 y;
    s16 z;
    u16 field8;
    s16 fieldA;
    u8 padC[4];
    s32 flags;
    u8 pad14[4];
    s32 remaining;
    Game130CB0Source *source;
    u8 pad20[4];
    u16 field24;
} Game130CB0Record;

void func_1000F85C(u16, s32, s32, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15103AA0 CURRENT (785) */
s32 func_15103AA0(void *arg0, s32 *arg1, u32 *arg2, s32 *arg3,
                  s32 *arg4, s32 *arg5, u16 *arg6) {
    Game130CB0Record *record;
    Game130CB0Source *source;
    s32 packed;
    u32 remaining;
    u16 trigger;

    record = arg0;
    source = record->source;
    packed = record->remaining;
    remaining = packed & 0x7FFF;
    record->x = (s16)(s32)source->x;
    record->y = (s16)(s32)source->y;
    record->z = (s16)(s32)source->z;
    if (remaining != 0) {
        trigger = *arg6;
        if (trigger != 0) {
            record->remaining = ((u32)trigger << 16) | (packed & 0xFFFF);
            record->field0 = 0;
            *arg6 = 0;
            func_10010344(0x5B0, (s32)source, (u32)-0x61A8, record->fieldA, record->field8);
            return 0;
        }
        if ((u32)D_800BE9E4 >= remaining) {
            *arg6 = packed >> 16;
            record->field0 = packed >> 16;
            record->remaining &= ~0x7FFF;
            return 0;
        }
        remaining -= D_800BE9E4;
    } else {
        if (record->field24 == 0) {
            func_10010344(0x5B1, (s32)source, (u32)-0x61A8, record->fieldA, record->field8);
            return 1;
        }
        if (packed != 0) {
            if ((packed & 0x8000) == 0) {
                func_1000F85C(record->field24, -0x8000, 2, remaining);
            }
            record->remaining = 0;
        }
        record->flags &= ~0x80;
    }
    record->remaining = (record->remaining & ~0x7FFF) | remaining;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15103AA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103AA0.s")
typedef s32 (*Game130CB0SoundCallback)(void *, s32 *, u32 *, s32 *, s32 *, s32 *, u16 *);

u16 func_1000FA64(s32, s32, s32, s32, s32, s32, s32,
                   Game130CB0SoundCallback, s32, void *, s32, s32);
s32 func_10010894(void *);
void *func_1505EEF4(s32);
u32 func_150ADA20(void);
s32 func_15103910(void *, s32 *, u32 *, s32 *, s32 *, s32 *, u16 *);
s32 func_15103AA0(void *, s32 *, u32 *, s32 *, s32 *, s32 *, u16 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15103C14 CURRENT (166) */
void func_15103C14(s32 arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4) {
    u16 *saved;
    Game130CB0Source *actor;
    u16 *timer;
    s32 special;

    timer = &D_800D9AB0[arg3];
    special = 0;
    if (*timer == 0 || arg0 == 0x58D) {
        saved = timer;
        actor = func_1505EEF4(arg1);
        if (actor != 0 && func_10010894(actor) == 0) {
            if (arg2 != 0) {
                if (arg4 != 0) {
                    arg0 += (func_150ADA20() % arg2) * 2;
                } else {
                    arg0 += func_150ADA20() % arg2;
                }
            }
            if (*(s32 *)((u8 *)actor + 0x318) != 0) {
                special = 1;
            } else if (arg4 != 0) {
                arg0 += 1;
            }
            if (special != 0) {
                func_1000FA64(arg0 & 0xFFFF, (s16)(s32)actor->x,
                    (s16)(s32)actor->y, (s16)(s32)actor->z,
                    0x7530, 0x7FFF, 0x7FFE, func_15103910,
                    0x14, actor, 0x100, 0);
            } else {
                func_1000FA64(arg0 & 0xFFFF, (s16)(s32)actor->x,
                    (s16)(s32)actor->y, (s16)(s32)actor->z,
                    0x7FBC, 0x7FFF, 0x7FFE, func_15103AA0,
                    (arg4 << 15) | 0x14, actor, 0x100, 0);
            }
            *saved = 0x258;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15103C14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103C14.s")
