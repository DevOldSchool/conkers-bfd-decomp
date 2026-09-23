#include "types.h"

/*
 * Reviewed source unit: src/game/game_105FC0.c
 * Boundary evidence: docs/evidence/game_raw_particle_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D8B3C
 * - func_150D8B88
 * - func_150D8E1C
 * - func_150D8E4C
 * - func_150D8FAC
 * - func_150D942C
 * - func_150D9C7C
 * - func_150DA50C
 * - func_150DA5EC
 * - func_150DA67C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150DA484(void *arg0);
void func_100111C8(s32 arg0, u16 arg1);
void func_15147928(s32 arg0);
void func_15145740(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4);
extern f32 D_800A0B40;
extern f32 D_800A0B44;
extern u8 D_800BE616;

void func_150D8B10(void *arg0, void *arg1) {
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + 20.0f);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D8B3C CURRENT (270) */
void func_150D8B3C(void *arg0, void *arg1) {
    u8 sp28[0x1C];
    f32 var_fv0;

    if (D_800BE616 != 0) {
        var_fv0 = D_800A0B40;
    } else {
        var_fv0 = D_800A0B44;
    }
    func_15145740(arg0, sp28 + 0xC, sp28, arg1, var_fv0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D8B3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8B3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8B88.s")
extern f32 D_800A0B4C;
extern f32 D_800A0B50;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game105FC0Vec3;

void func_150D8D84(Game105FC0Vec3 *arg0, Game105FC0Vec3 *arg1, f32 arg2) {
    Game105FC0Vec3 sp4;

    sp4 = *arg1;
    arg1->y += D_800A0B4C * arg2;
    arg0->x += sp4.x * arg2;
    arg0->y += (sp4.y * arg2) + (D_800A0B50 * arg2 * arg2);
    arg0->z += sp4.z * arg2;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D8E1C CURRENT (60) */
void func_150D8E1C(void *arg0) {
    u16 temp_t0;
    u16 temp_t8;

    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    temp_t8 = *(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD;
    temp_t0 = temp_t8 | 8;
    *(volatile u16 *)((u8 *)arg0 + 0x1E) = temp_t8;
    *(volatile u16 *)((u8 *)arg0 + 0x1E) = temp_t0;
    *(volatile u16 *)((u8 *)arg0 + 0x1E) = (u16) (temp_t0 | 1);
    *(s16 *)((u8 *)arg0 + 0x1C) = 0x28;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D8E1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8E1C.s")
typedef struct Game105FC0Sub {
    u8 pad0[0x1AA];
    s16 count;
} Game105FC0Sub;

typedef struct Game105FC0Owner {
    u8 pad0[0x31C];
    Game105FC0Sub *sub;
} Game105FC0Owner;

typedef struct Game105FC0Timer {
    Game105FC0Owner *owner;
    u8 pad4[0x49];
    s8 count;
} Game105FC0Timer;

typedef struct Game105FC0State {
    u8 pad0[0x1E];
    u16 flags;
    u8 pad20[5];
    u8 capacity;
    u8 pad26[6];
    s8 mode;
    s8 stop;
    s8 current;
    u8 pad2F[0x25];
    Game105FC0Vec3 position;
    u8 pad60[0x34];
    u8 *samples;
    Game105FC0Timer *timer;
} Game105FC0State;

extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D8E4C CURRENT (565) */
s32 func_150D8E4C(Game105FC0State *arg0) {
    s32 temp_s4;
    s32 var_s0;
    Game105FC0Timer *temp_s5;
    Game105FC0Vec3 *temp_a0;
    Game105FC0Vec3 *temp_t0;
    Game105FC0Owner *temp_v1;
    Game105FC0Sub *temp_v0;
    s32 stride;

    temp_s5 = arg0->timer;
    temp_s4 = (s32)arg0->samples;
    if (arg0->mode < 2 && (arg0->flags & 8)) {
        return 0;
    }
    var_s0 = arg0->current;
    if (var_s0 != arg0->stop) {
        do {
            var_s0 -= 1;
            if (var_s0 < 0) {
                var_s0 = arg0->capacity - 1;
            }
            temp_a0 = (Game105FC0Vec3 *)(temp_s4 + var_s0 * 0x24);
            func_150D8D84(temp_a0, temp_a0 + 1, D_800BE9A4);
        } while (var_s0 != arg0->stop);
    }
    stride = 0x24;
    if (arg0->mode > 0) {
        temp_t0 = (Game105FC0Vec3 *)(temp_s4 + arg0->stop * stride);
        arg0->position = *temp_t0;
    } else {
        arg0->position.x = 0.0f;
        arg0->position.y = 0.0f;
        arg0->position.z = 0.0f;
    }
    temp_s5->count += D_800BE9E4;
    if (temp_s5->count >= 0x3D) {
        temp_v1 = temp_s5->owner;
        if (temp_v1 != 0) {
            temp_v0 = temp_v1->sub;
            if (temp_v0 != 0) {
                temp_v0->count += 1;
            }
        }
        temp_s5->count = 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D8E4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8E4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8FAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D942C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D9C7C.s")
void func_150DA484(void *arg0) {
    u8 *temp_v0;
    u16 temp_a1;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x98);
    temp_a1 = *(u16 *)(temp_v0 + 0x30);
    if (temp_a1 != 0) {
        func_100111C8(temp_a1 & 0xFFFF, temp_a1);
    }
}
void func_150DA4B4(s32 arg0) {
    func_150DA484((void *)arg0);
    func_151478F4(arg0);
}
void func_150DA4E0(s32 arg0) {
    func_150DA484((void *)arg0);
    func_15147928(arg0);
}
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DA50C CURRENT (280) */
void func_150DA50C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = arg2;
    if (temp_v1 == 0x44) {
        if ((*(s32 *)temp_v0 == *(s32 *)arg1) || (temp_v0[4] == arg1[4])) {
            *(f32 *)(temp_v0 + 0x3C) = *(f32 *)(arg1 + 8);
        }
    } else if (temp_v1 == 0) {
        temp_v1 = *(s32 *)arg1;
        if ((temp_v1 == *(s32 *)temp_v0) || (arg1[4] == temp_v0[4])) {
            func_1516972C(arg0);
        }
    } else if (temp_v1 == 0x2D) {
        temp_a0 = *(s32 *)arg1;
        temp_v1 = *(s32 *)temp_v0;
        if (temp_a0 == temp_v1) {
            *(s32 *)temp_v0 = *(s32 *)(arg1 + 4);
            temp_v0[4] = arg1[9];
            return;
        }
        if (*(s32 *)(arg1 + 4) == temp_v1) {
            *(s32 *)temp_v0 = temp_a0;
            temp_v0[4] = arg1[8];
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DA50C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA50C.s")
void func_15147D64(void *, s32, void *, void *, u8, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DA5EC CURRENT (510) */
void func_150DA5EC(void *arg0, f32 arg1, s32 arg2, void *arg3) {
    void *sp1C;
    u8 sp20;

    sp1C = arg0;
    sp20 = *(u8 *)((u8 *)arg0 + 0x3B);
    func_15147D64(&sp1C, 0x44, arg0, arg3, sp20, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DA5EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA5EC.s")
void func_15131828(s32, s32, s32, s32);
void func_15131958(void *, f32, s32);

s32 func_150DA628(s32 arg0, s32 arg1) {
    struct {
        s32 state;
        s32 pad;
    } locals;

    locals.state = arg0 + 0xA8;
    func_15131828(arg0, arg0 + 0xAC, locals.state, arg0 + 0xAA);
    func_15131958((void *)(arg0 + 0x58), *(f32 *)(locals.state + 0xC), locals.state);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA67C.s")
