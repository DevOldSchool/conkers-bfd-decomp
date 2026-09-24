#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A5C00.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151787AC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_15168118(s32, void *, s16);

s32 func_15178750(s32 arg0, void *arg1, s16 arg2) {
    s32 temp_t0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg1 + 0x14);
    temp_t0 = 1 << arg2;
    if (*(u8 *)((u8 *)temp_v0 + 0x36) & temp_t0) {
        return func_15168118(arg0, arg1, arg2);
    }
    return arg0;
}
void func_151787A4(void) {

}
void func_1000F91C(u16, s32, s16, s32, s32, s32, s32, s32, s32, s32);
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_150A6360(void *, void *, f32, f32, f32, f32, f32, f32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern s32 D_80082FA0;
extern f32 D_800A71E4;
extern u8 *D_800BE628;
extern s32 D_800BE9E4;
extern u8 D_800D9C10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151787AC CURRENT (4852) */
void func_151787AC(void *arg0) {
    volatile f32 sp68;
    volatile f32 sp64;
    volatile f32 sp60;
    u8 *var_s1;
    f32 temp_fa0;
    f32 temp_fa1;
    register f32 temp_fs1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    register f32 var_fs0;
    register f32 var_fs1;
    f32 var_ft5;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s32 var_t0;
    s16 var_v1;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a3;
    s32 var_s0;
    s32 var_s2;
    s32 var_s4;
    u16 temp_a0;
    f32 *temp_v0_2;
    f32 *temp_v0_4;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x14);
    temp_a1 = *(s32 *)((u8 *)arg0 + 0x18);
    temp_a2 = *(s32 *)((u8 *)arg0 + 0x1C);
    temp_a3 = *(s32 *)((u8 *)arg0 + 0x20);
    *(s16 *)((u8 *)arg0 + 0x28) = temp_a1;
    *(s16 *)((u8 *)arg0 + 0x2A) = temp_a2;
    *(s16 *)((u8 *)arg0 + 0x2C) = temp_a3;
    if (temp_v0 == -0x8000) {
        temp_v0_2 = *(f32 **)((u8 *)arg0 + 0x10);
        var_ft5 = temp_v0_2[0];
        var_fs0 = temp_v0_2[1];
        var_fs1 = temp_v0_2[2];
    } else {
        var_fs1 = (f32) temp_v0;
        var_ft5 = (f32) *(s16 *)((u8 *)arg0 + 0x10);
        var_fs0 = (f32) *(s16 *)((u8 *)arg0 + 0x12);
    }
    var_s1 = D_800D9C10;
    sp68 = (f32) temp_a1;
    var_s0 = 0;
    temp_fa0 = var_ft5 - sp68;
    sp64 = (f32) temp_a2;
    temp_fa1 = var_fs0 - sp64;
    sp60 = (f32) temp_a3;
    temp_ft4 = var_fs1 - sp60;
    temp_fv0 = sqrtf((temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1) + (temp_ft4 * temp_ft4));
    if (temp_fv0 > 1.0f) {
        temp_fv1 = 16.0f / temp_fv0;
        *(s32 *)((u8 *)arg0 + 0x18) = (s32) (sp68 + temp_fa0 * temp_fv1);
        *(s32 *)((u8 *)arg0 + 0x1C) = (s32) (sp64 + temp_fa1 * temp_fv1);
        *(s32 *)((u8 *)arg0 + 0x20) = (s32) (sp60 + temp_ft4 * temp_fv1);
    }
    var_s4 = 0;
    var_s2 = 0;
    if (D_80082FA0 >= 0) {
        temp_fs1 = D_800A71E4;
        do {
            if (func_150A6360(var_s0 + D_800BE628, var_s1,
                (f32)*(s32 *)((u8 *)arg0 + 0x18), (f32)*(s32 *)((u8 *)arg0 + 0x1C),
                (f32)*(s32 *)((u8 *)arg0 + 0x20), 100.0f, 100.0f, temp_fs1)) {
                var_s4 |= 1 << var_s2;
            }
            var_s2++;
            var_s0 += 0x180;
            var_s1 += 0x40;
        } while (D_80082FA0 >= var_s2);
    }
    *(s8 *)((u8 *)arg0 + 0x36) = var_s4;
    if (*(u8 *)((u8 *)arg0 + 0x37) != 0) {
        temp_a0 = *(u16 *)((u8 *)arg0 + 0x2E);
        if (temp_a0 == 0) {
            *(u16 *)((u8 *)arg0 + 0x2E) = func_10010F88(0x4A2, 0x2710, 0, 0, 0,
                *(s32 *)((u8 *)arg0 + 0x18), *(s32 *)((u8 *)arg0 + 0x1C), *(s32 *)((u8 *)arg0 + 0x20), 0x64, 0x320);
        } else {
            func_1000F91C(temp_a0, 0x2710, 0, 0, 0,
                *(s32 *)((u8 *)arg0 + 0x18), *(s32 *)((u8 *)arg0 + 0x1C), *(s32 *)((u8 *)arg0 + 0x20), 0x64, 0x320);
        }
    }
    temp_v0_3 = *(s16 *)((u8 *)arg0 + 0x14);
    var_t0 = temp_v0_3;
    if (temp_v0_3 == -0x8000) {
        temp_v0_4 = *(f32 **)((u8 *)arg0 + 0x10);
        var_a3 = (s32)temp_v0_4[0];
        var_a1 = (s32)temp_v0_4[1];
        var_t0 = (s32)temp_v0_4[2];
    } else {
        var_a3 = *(s16 *)((u8 *)arg0 + 0x10);
        var_a1 = *(s16 *)((u8 *)arg0 + 0x12);
    }
    temp_v0_5 = var_a3 - *(s32 *)((u8 *)arg0 + 0x18);
    temp_v1 = (var_a1 + *(s16 *)((u8 *)arg0 + 0x30)) - *(s32 *)((u8 *)arg0 + 0x1C);
    temp_a0_2 = var_t0 - *(s32 *)((u8 *)arg0 + 0x20);
    if ((temp_v0_5 * temp_v0_5 + temp_v1 * temp_v1 + temp_a0_2 * temp_a0_2) >= 0x2711) {
        temp_v0_6 = *(s16 *)((u8 *)arg0 + 0x32);
        var_v1 = 0x640;
        if (temp_v0_6 != 0x640) {
            *(s16 *)((u8 *)arg0 + 0x32) = temp_v0_6 + D_800BE9E4 + 0x28;
            if (*(s16 *)((u8 *)arg0 + 0x32) >= 0x641) {
                goto block_23;
            }
        }
    } else {
        temp_v0_7 = *(s16 *)((u8 *)arg0 + 0x32);
        var_v1 = 0x320;
        if (temp_v0_7 != 0x320) {
            *(s16 *)((u8 *)arg0 + 0x32) = temp_v0_7 - D_800BE9E4 - 0x28;
            if (*(s16 *)((u8 *)arg0 + 0x32) < 0x320) {
block_23:
                *(s16 *)((u8 *)arg0 + 0x32) = var_v1;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151787AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5C00/func_151787AC.s")

extern void *D_800DCF38;

void *func_15178B98(u8 arg0) {
    void *var_v1;
    u8 target;

    var_v1 = D_800DCF38;
    target = arg0;
    while (var_v1 != 0) {
        if (target == *(u8 *)((u8 *)var_v1 + 0x34)) {
            return var_v1;
        }
        var_v1 = *(void **)((u8 *)var_v1 + 8);
    }
    return 0;
}
/* Call context: func_15178B98: unique active project prototype */
void * func_15178B98(u8);

void func_15178BE4(u8 arg0, void *arg1, s16 arg2) {
    void *temp_v0;

    temp_v0 = func_15178B98(arg0);
    if (temp_v0 != 0) {
        *(void **)((u8 *)temp_v0 + 0x10) = arg1;
        *(s32 *)((u8 *)temp_v0 + 0x14) = 0x80000000;
        *(s16 *)((u8 *)temp_v0 + 0x30) = arg2;
    }
}
/* Call context: func_15178B98: unique active project prototype */

void func_15178C34(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4) {
    void *temp_v0;

    temp_v0 = func_15178B98(arg0);
    if (temp_v0 != 0) {
        *(s32 *)((u8 *)temp_v0 + 0x10) = (s32) ((arg1 << 0x10) | (arg2 & 0xFFFF));
        *(s32 *)((u8 *)temp_v0 + 0x14) = (s32) (arg3 << 0x10);
        *(s16 *)((u8 *)temp_v0 + 0x30) = arg4;
    }
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern s32 D_800CC2D0;

s32 func_15178C9C(u8 arg0, s32 arg1) {
    s32 temp_ft2;
    s32 temp_ft3;
    s32 temp_ft4;
    u8 *temp_a2;
    u8 *temp_v0;

    temp_v0 = func_15178B98(arg0);
    if (temp_v0 != 0) {
        temp_a2 = (arg1 * 0x32C) + (u8 *)&D_800CC2D0;
        temp_ft4 = (s32)(*(f32 *)(temp_a2 + 0x14) -
                             (f32)*(s32 *)(temp_v0 + 0x18));
        temp_ft3 = (s32)(*(f32 *)(temp_a2 + 0x18) -
                             (f32)*(s32 *)(temp_v0 + 0x1C));
        temp_ft2 = (s32)(*(f32 *)(temp_a2 + 0x1C) -
                             (f32)*(s32 *)(temp_v0 + 0x20));
        temp_ft4 *= temp_ft4;
        temp_ft3 *= temp_ft3;
        temp_ft2 *= temp_ft2;
        return (s32)sqrtf((f32)(temp_ft4 + temp_ft3 + temp_ft2));
    }
    return 1;
}
typedef struct Game1A5C00Owner {
    u8 pad0[0x2E];
    u16 field_2E;
} Game1A5C00Owner;

typedef struct Game1A5C00Node {
    u8 pad0[8];
    struct Game1A5C00Node *next_8;
    u8 padC[8];
    Game1A5C00Owner *owner_14;
} Game1A5C00Node;

void func_100111C8(s32, Game1A5C00Node *);
void func_1516972C(u8 *);
void func_15169824(s32);
extern Game1A5C00Node *D_800DCF3C;

void func_15178DA4(Game1A5C00Owner *arg0) {
    struct {
        Game1A5C00Node * volatile saved;
        u32 pad;
    } home;
    Game1A5C00Node *next;
    Game1A5C00Node *node;
    u16 key;

    node = D_800DCF3C;
    key = arg0->field_2E;
    home.saved = node;
    func_100111C8(key, node);
    node = home.saved;
    while (node != 0) {
        next = node->next_8;
        if (arg0 == node->owner_14) {
            func_1516972C((u8 *)node);
        }
        node = next;
    }
    func_15169824((s32)arg0);
}
void *func_15178B98(u8);
void func_15178DA4(Game1A5C00Owner *);

void func_15178E14(u8 arg0) {
    func_15178DA4(func_15178B98(arg0));
}
