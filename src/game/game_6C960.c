#include "types.h"

/*
 * Reviewed source unit: src/game/game_6C960.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503F4B0
 * - func_1503F62C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game6C960Actor {
    u8 pad0[0x3F5];
    u8 field_3F5;
} Game6C960Actor;

void func_1505E0C4(s32, s32, Game6C960Actor *, s32, s32, s32, s32,
                   f32, f32, f32, f32, s32);

void *func_10003C40(s32, s32, s32, s32);
void func_10004074(s32);
void func_1502D824(void *, s32, s32);
void func_150A81D0(s32 *, s32, void *, s32, s32, s16 *, s32, s32);
void func_150A9984(void *, u16);
void func_1507BDB0(s32, s32, void *, s32);
extern s32 D_800BE9A4;
extern u8 D_800BE9C0;

typedef struct {
    s32 handle;
    u8 pad4[4];
    s16 value;
    u8 padA[2];
    s32 allocation;
} Game6C960F4B0Locals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503F4B0 CURRENT (270) */
void func_1503F4B0(void *arg0) {
    Game6C960F4B0Locals locals;
    s32 temp_v0;
    void *temp_v0_2;

    locals.allocation = 0;
    if (*(s32 *)((u8 *)arg0 + (D_800BE9C0 * 4) + 0x3E0) != 0) {
        temp_v0 = (s32)func_10003C40(0x320, 1, 2, 2);
        locals.allocation = temp_v0;
        func_1502D824(arg0, 0, temp_v0);
        locals.value = 0x1000;
        temp_v0_2 = (u8 *)arg0 + (D_800BE9C0 * 4);
        locals.handle = *(s32 *)((u8 *)temp_v0_2 + 0x3E8);
        func_150A81D0(&locals.handle, *(s32 *)((u8 *)temp_v0_2 + 0x3E0), arg0,
                       *(s32 *)((u8 *)arg0 + 0x3F0),
                       *(u8 *)((u8 *)arg0 + 0x3F4), &locals.value, 0, 0);
        func_150A9984(*(void **)((u8 *)arg0 + (D_800BE9C0 * 4) + 0x3E8),
                      *(u8 *)((u8 *)arg0 + 0x3F4));
        *(s8 *)((u8 *)arg0 + 0x3F6) = 1;
    }
    func_1507BDB0((s32)arg0, D_800BE9A4, 0, 0);
    if (locals.allocation != 0) {
        func_10004074(locals.allocation);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503F4B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6C960/func_1503F4B0.s")

void func_1503F5B8(Game6C960Actor *arg0, s32 arg1, s32 arg2, f32 arg3,
                   f32 arg4, s32 arg5) {
    func_1505E0C4(0, 0, arg0, 0, arg1, arg2, arg0->field_3F5, arg3,
                  arg4, 0.0f, 0.0f, arg5);
}
void func_100226F0(void *, s32);
s32 func_1502FE10(u8, void *, void *, void **, void *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503F62C CURRENT (1095) */
s32 func_1503F62C(u8 arg0, s32 arg1, void *arg2, void *arg3,
                   void **arg4, void *arg5, Game6C960Actor **arg6) {
    s32 count;
    Game6C960Actor *actor;
    void *allocation;

    actor = func_10003C40(0x3F8, 1, 2, 2);
    *arg6 = actor;
    if (actor == 0) {
        return 1;
    }
    func_100226F0(*arg6, 0x40);
    ((u8 *)*arg6)[0x215] = 1;
    ((u8 *)*arg6)[0x45] = 1;
    func_1502FE10(arg0, arg2, arg3, arg4, arg5,
                   (s32)((u8 *)*arg6 + 0x3F0), (s32)&count);
    ((u8 *)*arg6)[0x3F4] = (u8)count;
    ((u8 *)*arg6)[0x3F5] = (u8)arg1;
    ((u8 *)*arg6)[0x3F6] = 0;
    *(void **)((u8 *)*arg6 + 0x3E8) = func_10003C40(count << 6, 1, 2, 2);
    *(void **)((u8 *)*arg6 + 0x3EC) = func_10003C40(count << 6, 1, 2, 2);
    actor = *arg6;
    allocation = *(void **)((u8 *)actor + 0x3E8);
    if (allocation == 0 || *(void **)((u8 *)actor + 0x3EC) == 0) {
        if (allocation == 0) {
            func_10004074((s32)allocation);
        }
        allocation = *(void **)((u8 *)*arg6 + 0x3EC);
        if (allocation == 0) {
            func_10004074((s32)allocation);
        }
        func_10004074((s32)*arg6);
        return 1;
    }
    func_1503F5B8(actor, 1, 0, 1.0f, 0.0f, 0);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503F62C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6C960/func_1503F62C.s")
extern void func_10004074(s32 arg0);
extern void func_100043B4();

void func_1503F7B8(void *arg0) {
    func_100043B4(*(s32 *)((u8 *)arg0 + 0x3E8), 4);
    func_100043B4(*(s32 *)((u8 *)arg0 + 0x3EC), 4);
    func_10004074((s32) arg0);
}
