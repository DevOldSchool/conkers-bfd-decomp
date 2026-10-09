#include "types.h"

/*
 * Reviewed source unit: src/game/game_174BF0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_effect_dispatch_engine.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514795C
 * - func_15147A80
 * - func_15147C4C
 * - func_15147D64
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE9E4;
extern s32 (*D_8008A200[])(u8 *, s32);
extern s32 (*D_8008A23C[])(u8 *, s32);
extern s32 (*D_8008A284[])(u8 *, s32);
void func_1516972C(u8 *);

void func_15147740(u8 *arg0) {
    s8 temp_v0_3;
    u8 temp_v0;
    u8 temp_v0_2;

    {
        s8 spill_pad;
        s8 var_a1 = 0;
        if (*(u16 *)(arg0 + 0x1E) & 1) {
            *(s16 *)(arg0 + 0x1C) -= D_800BE9E4;
            if (*(s16 *)(arg0 + 0x1C) < 0) {
                var_a1 = 1;
            }
        }
        temp_v0 = arg0[0x2F];
        if (temp_v0 >= 0xF) {
            func_1516972C(arg0);
            return;
        }
        if (temp_v0 != 0 && var_a1 == 0) {
            if (D_8008A200[temp_v0](arg0, var_a1) == 0) {
                var_a1 = 1;
            }
        }
        temp_v0_2 = arg0[0x30];
        if (temp_v0_2 >= 0x12) {
            func_1516972C(arg0);
            return;
        }
        if (temp_v0_2 != 0 && var_a1 == 0) {
            if (D_8008A23C[temp_v0_2](arg0, var_a1) == 0) {
                var_a1 = 1;
            }
        }
        if (*(u16 *)(arg0 + 0x1E) & 0x10) {
            temp_v0_3 = *(s8 *)(arg0 + 0x24);
            if (temp_v0_3 < -1 || temp_v0_3 >= 8) {
                func_1516972C(arg0);
                return;
            }
            if (temp_v0_3 != -1 && var_a1 == 0) {
                if (D_8008A284[temp_v0_3](arg0, var_a1) == 0) {
                    var_a1 = 1;
                }
            }
        }
        if (var_a1 != 0) {
            func_1516972C(arg0);
        }
    }
}
void func_151478D0(s32 arg0) {
    func_151D5E30(arg0 + 0x84, arg0);
}
void func_1514795C(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_151478F4(s32 arg0) {
    func_151478D0(arg0);
    func_1514795C(arg0);
    func_15169804(arg0);
}
void func_15147928(s32 arg0) {
    func_151478D0(arg0);
    func_1514795C(arg0);
    func_15169824(arg0);
}
void func_100043B4(void *, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514795C CURRENT (890) */
void func_1514795C(s32 arg0) {
    void *temp_v0;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = arg0;
    if (D_80082FA0 >= 0) {
        do {
            temp_v0 = *(void **)((u8 *)var_s0 + 0x3C);
            if (temp_v0 != 0) {
                func_100043B4(temp_v0, 4);
            }
            var_s1 += 1;
            var_s0 += 4;
        } while (D_80082FA0 >= var_s1);
    }
    temp_v0 = *(void **)((u8 *)arg0 + 0x4C);
    if (temp_v0 != 0) {
        func_100043B4(temp_v0, 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514795C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_1514795C.s")
typedef struct {
    u8 pad_0[0x20];
    s32 field_20;
} Game174BF0State;

extern void (*D_8008A2F0[])(void);

void func_151479E0(Game174BF0State *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field_20;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    } else if (temp_v0 >= 0x14) {
        temp_v0 = 0;
    }
    D_8008A2F0[temp_v0]();
}
extern void (*D_8008A340[])(void);

void func_15147A30(Game174BF0State *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field_20;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    } else if (temp_v0 >= 0x14) {
        temp_v0 = 0;
    }
    D_8008A340[temp_v0]();
}
void *func_10022EC0(void *, const void *, u32);
void *func_1515D440(void);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_100226F0(void *, s32);
void *func_1515D480(s32);

typedef struct Game174BF0Packet {
    u32 words[9];
} Game174BF0Packet;

typedef struct Game174BF0Allocation {
    u8 pad0[0x10];
    u8 header[0x1C];
    u8 state2C;
    u8 state2D;
    u8 state2E;
    u8 selector2F;
    u8 selector30;
    u8 selector31;
    u8 pad32[2];
    s32 parameter34;
    u8 state38;
    u8 pad39[3];
    void *slots[4];
    void *list;
    s32 parameter50;
    f32 position[3];
    Game174BF0Packet packet;
    u8 storage[0x10];
    void *end;
    void *start;
    u8 pad9C[4];
} Game174BF0Allocation;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15147A80 CURRENT (922) */
void *func_15147A80(u8 *arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   Game174BF0Packet *arg8, u8 arg9, s32 arg10) {
    s32 index;
    s32 type;
    s32 size;
    Game174BF0Allocation *allocation;
    u8 *start;
    u8 *cursor;

    size = arg0[0x15] * arg2;
    type = 0x22;
    if (*(u16 *)(arg0 + 0xE) & 0x40) {
        type = 0x4D;
    }
    allocation = func_15167A68(type, arg10,
        arg1 + size + 0xA0, 1, arg9, 1);
    if (allocation == 0) {
        return 0;
    }
    start = (u8 *)allocation + 0xA0;
    allocation->start = start;
    allocation->end = (u8 *)allocation->start + arg1;
    func_10022EC0(allocation->header, arg0, 0x1C);
    allocation->state2C = 0;
    allocation->state2D = 0;
    allocation->state2E = 0;
    allocation->selector2F = arg3;
    allocation->selector30 = arg4;
    allocation->selector31 = arg5;
    if (arg8 != 0) {
        allocation->packet = *arg8;
    } else {
        *((u8 *)&allocation->packet + 0x1C) = 0;
    }
    index = 0;
    cursor = (u8 *)allocation;
    allocation->parameter34 = arg6;
    allocation->state38 = 0;
    allocation->parameter50 = arg7;
    do {
        index++;
        cursor += 4;
        *(s32 *)(cursor + 0x38) = 0;
    } while (index < 4);
    allocation->list = 0;
    if (arg6 != 0) {
        index = 0;
        cursor = (u8 *)allocation;
        if (D_80082FA0 >= 0) {
            do {
                *(void **)(cursor + 0x3C) = func_1515D480(arg6);
                index++;
                cursor += 4;
            } while (D_80082FA0 >= index);
        }
        allocation->list = func_1515D440();
    }
    allocation->position[0] = 0.0f;
    allocation->position[1] = 0.0f;
    allocation->position[2] = 0.0f;
    func_100226F0(allocation->storage, 0x10);
    return allocation;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15147A80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147A80.s")
extern s32 func_151462C8(s32, void *, s32, s32, s32, s32, void *, s32, s32);
extern void func_1516972C(u8 *);
extern s32 (*D_8008A2A4[])(u8 *, s32, s16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15147C4C CURRENT (1679) */
s32 func_15147C4C(s32 arg0, u8 *arg1, s16 arg2) {
    s32 arg8;
    u8 index;

    if (*(u16 *)(arg1 + 0x1E) & 0x20) {
        arg8 = *(s32 *)(arg1 + 0x28);
    } else {
        arg8 = 0;
    }

    arg0 = func_151462C8(arg0, arg1 + 0x34, 0, 0, 0, arg2, arg1 + 0x54, 2, arg8);
    index = arg1[0x31];
    if (index >= 0x13) {
        func_1516972C(arg1);
    } else if (index != 0) {
        return D_8008A2A4[index](arg1, arg0, arg2);
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15147C4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147C4C.s")
extern void (*D_8008A390[])(void *, s32, u8);

void func_15147D1C(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008A390[*(s32 *)((u8 *)arg0 + 0x20)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
void func_15169260(void *, s32, s32, u8);
extern u8 D_800A5760;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15147D64 CURRENT (200) */
void func_15147D64(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5760, 2, arg0, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15147D64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147D64.s")
