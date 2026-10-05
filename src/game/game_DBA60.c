#include "types.h"

/*
 * Reviewed source unit: src/game/game_DBA60.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AE790
 * - func_150AEB9C
 * - func_150AEDF8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameDBA60Camera {
    u8 pad00[0x2C];
    s32 flags2C;
    u8 pad30[0x54];
    u32 flags84;
    u8 pad88[0xAC];
    s32 field134;
    u8 pad138[0x7C];
    s16 mode1B4;
} GameDBA60Camera;
s32 func_1509BE40(s32, ...);
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);
void func_151254F4(void *, s32);
void func_15124B18(u8 *);
extern u8 D_800CC335;
extern u8 *D_800D2E4C;

void func_150AE5B0(GameDBA60Camera *arg0) {
    s32 flags;

    if (!(D_800D2E4C[4] & 0x80)) {
        if (func_1509BE40(0, 0x2000, 0xBB) != -1) {
            if (func_15123934(arg0, arg0->flags2C, 0, arg0->field134, 8) != 0) {
                arg0->flags84 |= 0x01000000;
                func_151254F4(arg0, D_800CC335 - 1);
            }
        } else if (func_151239CC(arg0, 8) != 0) {
            func_151254F4(arg0, 0);
        }
    }
    arg0->flags84 &= ~0x4000;
    if (!(D_800D2E4C[1] & 4)) {
        if (func_1509BE40(1, 0x2000, 0x95, func_1509BE40(0, 0x2014, 0xB7) | 0x2000) != 0) {
            arg0->flags84 |= 0x01000000;
            flags = arg0->flags2C;
            if ((flags & 1) && (func_15123934(arg0, flags, 0, arg0->field134, 0) != 0)) {
                arg0->mode1B4 = 3;
                arg0->flags84 &= ~4;
                func_15124B18((u8 *)arg0);
            }
        } else if (func_151239CC(arg0, 0) != 0) {
            func_15124B18((u8 *)arg0);
            arg0->flags84 &= 0xFEFFFFFF;
        }
    }
    if (func_1509BE40(1, 0x4082, 6, 0x9000) != 0) {
        arg0->flags84 |= 0x10000;
        return;
    }
    arg0->flags84 &= 0xFFFEFFFF;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AE790.s")
typedef struct {
    u8 field_0;
    u8 pad_1;
    s16 field_2;
} GameDBA60Entry;

void *func_151491F4(s16, s8, s8, u8, u8, s32, u8, s32);
void func_15001A08(void);
extern u32 D_15001B08;
extern s32 D_800886E0;
extern GameDBA60Entry *D_800886E4;
extern u8 D_800DCE50[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AEB9C CURRENT (2269) */
void func_150AEB9C(void *arg0) {
    u32 *cursor;
    u32 checksum;
    s32 index;
    s32 offset;
    u8 *effect;

    if (arg0 != 0) {
        cursor = (u32 *)(void *)func_15001A08;
        checksum = 0;
        while ((u32)cursor < (u32)&D_15001B08) {
            checksum = (checksum ^ *cursor++) * 2;
        }
        if (checksum != 0xB4E42D60) {
            *(s32 *)(D_800DCE50 + 0x8C) = 0;
            *(s32 *)(D_800DCE50 + 0x22C) = 0;
        }
        index = 0;
        offset = 0;
        if (D_800886E0 > 0) {
            do {
                effect = func_151491F4(*(s16 *)((u8 *)D_800886E4 + offset + 2),
                                       0, -1, 1, 0x27, 8, 0xFF, 0);
                if (effect == 0) {
                    return;
                }
                *(void **)(effect + 0x28) = arg0;
                effect[0x2C] = *(u8 *)((u8 *)arg0 + 0x3B);
                effect[0x2D] = *(u8 *)((u8 *)D_800886E4 + offset);
                index++;
                offset += 4;
            } while (index < D_800886E0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AEB9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AEB9C.s")
void func_1516972C(void *arg0);
extern s32 D_800BE9E4;

void func_150AECCC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x96) = (s16) ((*(s16 *)((u8 *)arg0 + 0x94) * D_800BE9E4) + *(s16 *)((u8 *)arg0 + 0x96));
    if (*(s16 *)((u8 *)arg0 + 0x96) >= 0x1401) {
        *(s16 *)((u8 *)arg0 + 0x96) = 0x1400;
    }
    *(s16 *)((u8 *)arg0 + 0x9E) = (s16) (*(s16 *)((u8 *)arg0 + 0x9E) - (*(s16 *)((u8 *)arg0 + 0x96) >> 8));
    *(s16 *)((u8 *)arg0 + 0xA4) = (s16) (*(s16 *)((u8 *)arg0 + 0xA4) + D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0xA4) >= 0x1A) {
        *(s16 *)((u8 *)arg0 + 0xA4) = 0x19;
    }
}
extern s32 D_800BE9E4;

void func_150AED4C(void *arg0) {
    s32 value;
    s32 limit;

    *(s16 *)((u8 *)arg0 + 0x34) += *(s32 *)((u8 *)arg0 + 0x14) * (u32)D_800BE9E4;
    value = *(s16 *)((u8 *)arg0 + 0x34);
    limit = *(s16 *)((u8 *)arg0 + 0x2A);
    if (limit < value) {
        *(s16 *)((u8 *)arg0 + 0x34) = limit;
        *(volatile s8 *)((u8 *)arg0 + 0x3A) = 0x46;
        value = *(volatile s16 *)((u8 *)arg0 + 0x34);
    }
    *(s16 *)((u8 *)arg0 + 0x36) = value;
}
s32 func_150AED9C(void *arg0) {
    s32 value;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    value = *(s16 *)((u8 *)arg0 + 0x1C);
    value *= 8;
    if (value >= 0x100) {
        value = 0xFF;
    }
    *(s8 *)((u8 *)temp_v0 + 0x1B) = value;
    if ((value & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
typedef struct GameDBA60Object {
    u8 pad0[0x1C];
    s16 field_1C;
    u8 pad1E[0xA];
    s8 field_28;
} GameDBA60Object;

s32 func_150AEDD8(GameDBA60Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x20) {
        arg0->field_28 = value * 8;
    }

    return 1;
}
/* Call context: func_1516972C: unique active declaration in the allowed source */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AEDF8 CURRENT (175) */
void func_150AEDF8(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = arg0 + 0x28;
    if (arg2 == 0x2D) {
        temp_a0 = *(s32 *)temp_v0;
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a0) {
            *(s32 *)temp_v0 = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
            *(s32 *)temp_v0 = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    } else if (arg2 == 0) {
        temp_v1 = *(s32 *)arg1;
        if ((temp_v1 == *(s32 *)temp_v0) ||
            (temp_v0[4] == arg1[4])) {
            func_1516972C(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AEDF8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AEDF8.s")
