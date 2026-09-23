#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E73B0.c
 * Boundary evidence: docs/evidence/game_raw_complete_code_selected_segments.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B9F00
 * - func_151BA084
 * - func_151BA468
 * - func_151BA518
 * - func_151BB0E0
 * - func_151BB61C
 * - func_151BBA9C
 * - func_151BC104
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15160CDC(
    s32 arg0,
    s32 arg1,
    void *arg2,
    void *arg3,
    f32 arg4,
    s32 arg5,
    s32 arg6,
    s32 arg7,
    s32 arg8,
    s32 arg9,
    s32 arg10,
    s32 arg11,
    s32 arg12,
    s32 arg13,
    s32 arg14,
    s32 arg15
);
extern u8 D_800AA760;
extern u8 D_800AA76C;
extern f32 D_800AA82C;

typedef struct Game1E73B0Request {
    void *source;
    u8 code;
    u8 pad05[3];
    s8 kind;
    s8 negative;
    s8 count;
    u8 pad0B;
    s16 duration;
    u8 pad0E[2];
    s32 one;
    s32 mask;
    s32 flags;
    s32 another_one;
    s32 value36;
    s32 value80;
    s32 value20;
    u8 zero1;
    u8 zero2;
    u8 pad2E[0xA];
    s32 value9;
    s32 value1AD;
    s8 extra;
    u8 variant;
    u8 pad42[2];
    u8 pad44[4];
} Game1E73B0Request;

extern s8 D_8008FD90;
extern s8 D_800E0BCE[];
extern u8 D_800CC2D0[];
extern void *func_1513B5E0(s8 *, s32, s32, s32, s32);
extern void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B9F00 CURRENT (1427) */
void *func_151B9F00(void *arg0, u8 arg1, s32 arg2) {
    Game1E73B0Request request;
    s32 actor_index;
    void *result;

    if (arg0 == 0) {
        return 0;
    }
    request.source = arg0;
    request.kind = 2;
    request.negative = -1;
    request.count = 3;
    request.duration = 0x12C;
    request.value9 = 9;
    request.value1AD = 0x1AD;
    request.variant = 0xFF;
    request.code = *(u8 *)((u8 *)arg0 + 0x3B);
    actor_index = ((u8 *)arg0 - D_800CC2D0) / 0x32C;
    if (actor_index < 2 && D_800E0BCE[actor_index] != 0) {
        if (D_8008FD90 == 2) {
            request.variant = 0xFD;
        } else if (D_8008FD90 == 4) {
            if (actor_index == 0) {
                request.variant = 0xFB;
            } else {
                request.variant = 0xF7;
            }
        }
    }
    request.one = 1;
    request.mask = 0x200205;
    request.flags = 0x60600;
    request.zero1 = 0;
    request.zero2 = 0;
    request.another_one = 1;
    request.value36 = 0x36;
    request.value80 = 0x80;
    request.value20 = 0x20;
    request.extra = 2;
    result = func_1513B5E0(&request.kind, 1, 8, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + *(s32 *)((u8 *)result + 0x50) + 0xF8,
                      &request.source, 8);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B9F00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151B9F00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA084.s")
extern void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BA468 CURRENT (1697) */
void func_151BA468(void *arg0, u8 *arg1, s32 arg2) {
    u8 *temp_v0;
    void *temp_v1;

    arg2 &= 0xFF;
    temp_v0 = (u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x50);
    temp_v1 = *(void **)(temp_v0 + 0xF8);
    if (arg2 == 0) {
        if ((temp_v1 == *(void **)arg1) ||
            (*(u8 *)((u8 *)temp_v1 + 0x3B) == arg1[4])) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        void *temp_a0 = *(void **)arg1;

        if (temp_a0 == temp_v1) {
            *(void **)(temp_v0 + 0xF8) = (void *)(s32)arg1[4];
            temp_v0[0xFC] = arg1[9];
            return;
        }
        if ((s32)arg1[4] == (s32)temp_v1) {
            *(void **)(temp_v0 + 0xF8) = temp_a0;
            temp_v0[0xFC] = arg1[8];
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BA468 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA518.s")
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
extern void func_151BB0E0(void);

void func_151BB044(void *arg0) {
    func_1000FA64(0x4A7,
                  (s32) (s16) (s32) *(f32 *)((u8 *)arg0 + 0x14),
                  (s32) (s16) (s32) *(f32 *)((u8 *)arg0 + 0x18),
                  (s32) (s16) (s32) *(f32 *)((u8 *)arg0 + 0x1C),
                  0x2000, 0x320, 0xC8, (void *)&func_151BB0E0,
                  (s32) arg0, 0, 8, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BB0E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BB61C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BBA9C.s")
u32 func_150ADA20(void);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    u8 type;
    s8 neg_one;
    s16 lifetime;
    s8 zero;
} Game1E73B0Descriptor;

void func_151BBEE4(void *arg0, u8 arg1, s32 arg2) {
    Game1E73B0Descriptor descriptor;
    s32 position[3];

    descriptor.type = 3;
    descriptor.neg_one = -1;
    descriptor.lifetime = (func_150ADA20() & 0xF) + 5;
    descriptor.zero = 0;
    position[0] = (s32)*(f32 *)arg0;
    position[1] = (s32)*(f32 *)((u8 *)arg0 + 4);
    position[2] = (s32)*(f32 *)((u8 *)arg0 + 8);
    func_151602C0((u8 *)&descriptor, position,
                  (func_150ADA20() % 21U) + 0x1E,
                  0xFF, 0x61, 0x36, 0xFF, 0, 0, arg1, arg2);
}

f32 func_150ADA68(void);
void func_150E7FEC(f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151BBFBC(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    struct {
        s32 pad0;
        f32 scale;
        u32 random_value;
        s32 pad1;
    } locals;

    locals.scale = func_150ADA68();
    locals.random_value = func_150ADA20();
    func_150E7FEC((locals.scale * 75.0f) + 75.0f,
                  ((locals.random_value % 56U) + 0xC8) & 0xFF,
                  arg0, arg1,
                  (func_150ADA20() % 205U) + 0x12B,
                  1, 1, 0, 0, 0, (s32)arg2, 0);
}
void func_151BC074(s32 arg0) {
    if (arg0 != 0) {
        func_15160CDC(arg0, 1, &D_800AA760, &D_800AA76C, D_800AA82C, 2, 0x12C, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 0, 0xFF, 1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BC104.s")
