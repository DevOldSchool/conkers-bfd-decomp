#include "types.h"

/*
 * Reviewed source unit: src/game/game_11D030.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EFB80
 * - func_150EFEC8
 * - func_150F00EC
 * - func_150F0198
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150EFB80.s")
typedef struct Game11D030SpawnDescriptor {
    u8 kind, mode;
    u16 flags;
    s16 lifetime;
    u8 pad6[2];
    s32 callback0, callback1;
    u8 colors[4];
    f32 field14, field18;
    f32 position[3], direction[3], scales[3];
    u32 options;
    u8 channels[4];
    s32 parameter;
    u8 pad4C[0xC];
} Game11D030SpawnDescriptor;

typedef struct Game11D030SpawnParameters {
    f32 values[9];
    s32 handles[8];
    s32 count;
    f32 multiplier;
    s16 angles[4];
    u8 colors[4];
    u8 state;
    s8 mode;
    u8 pad5A[0x12];
} Game11D030SpawnParameters;

typedef struct Game11D030SpawnOwner {
    u8 *actor;
    u8 kind, mode;
    u8 pad6[2];
    s32 data;
} Game11D030SpawnOwner;

void *func_10022EC0(void *, const void *, u32);
s32 func_151407D0(void *, u32, Game11D030SpawnDescriptor *,
                  u8, u8, u8, u8, s8, u8, s32);
extern s32 (*D_8008FD00)(void *, u8);
extern f32 D_800A1830, D_800A1834;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EFEC8 CURRENT (3643) */
s32 func_150EFEC8(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4,
                   s32 arg5, u8 arg6, s32 arg7) {
    s32 saved;
    Game11D030SpawnParameters parameters;
    Game11D030SpawnDescriptor descriptor;
    Game11D030SpawnOwner owner;
    register s32 value;

    owner.actor = arg0;
    owner.mode = arg1;
    owner.kind = arg0[0x3B];
    owner.data = arg5;
    descriptor.kind = D_8008FD00(arg0, arg1);
    descriptor.colors[3] = 0xFF;
    descriptor.options = 0xCD2002;
    descriptor.mode = 3;
    descriptor.flags = 0x2203;
    descriptor.lifetime = 0x12C;
    descriptor.colors[0] = arg2;
    parameters.handles[6] = -1;
    parameters.handles[3] = -1;
    descriptor.channels[0] = 0xFF;
    descriptor.channels[3] = 6;
    parameters.handles[0] = -1;
    parameters.handles[4] = -1;
    parameters.handles[1] = -1;
    descriptor.colors[1] = arg3;
    descriptor.colors[2] = arg4;
    descriptor.callback0 = 0;
    descriptor.callback1 = 0;
    descriptor.channels[1] = 0xFF;
    descriptor.channels[2] = 0;
    descriptor.parameter = 0;
    parameters.handles[5] = -1;
    parameters.handles[2] = -1;
    parameters.handles[7] = -1;
    parameters.count = 0;
    parameters.angles[0] = 0;
    parameters.angles[1] = 0;
    parameters.angles[2] = 0;
    parameters.angles[3] = 0;
    parameters.colors[0] = 0xFF;
    parameters.colors[1] = 0xFF;
    parameters.colors[2] = 0xFF;
    parameters.colors[3] = 0xFF;
    parameters.state = 0xA;
    parameters.mode = -1;
    descriptor.scales[0] = 1.0f;
    descriptor.scales[1] = 1.0f;
    descriptor.scales[2] = 1.0f;
    parameters.values[6] = 1.0f;
    parameters.multiplier = 1.0f;
    descriptor.field18 = 100.0f;
    descriptor.field14 = 100.0f;
    parameters.values[1] = 160.0f;
    parameters.values[0] = 160.0f;
    parameters.values[3] = 80.0f;
    parameters.values[2] = 80.0f;
    descriptor.position[0] = 0.0f;
    descriptor.position[1] = 0.0f;
    descriptor.position[2] = 0.0f;
    descriptor.direction[0] = 0.0f;
    descriptor.direction[1] = 0.0f;
    descriptor.direction[2] = 0.0f;
    parameters.values[4] = 0.5f;
    parameters.values[5] = 0.5f;
    parameters.values[7] = D_800A1830;
    parameters.values[8] = D_800A1834;
    value = func_151407D0(&parameters, 0x6C, &descriptor, 0x1E,
                         0, 0, 0, -1, arg6, arg7);
    if (value != 0) {
        saved = value;
        func_10022EC0((void *)(value + 0x170), &owner, 0xCU);
        value = saved;
    }
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EFEC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150EFEC8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F00EC CURRENT (290) */
s32 func_150F00EC(u8 *arg0) {
    typedef struct { f32 words[3]; } Copy3;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x178));
    if (*(u8 *)((u8 *)temp_v0 + 0x128) & 1) {
        temp_v1 = (void *)(temp_v0 + 0x110);
        *(Copy3 *)((u8 *)arg0 + 0x34) = *(Copy3 *)((u8 *)temp_v0 + 0x34);
        *(f32 *)((u8 *)arg0 + 0x40) = (*(f32 *)((u8 *)temp_v1 + 0x30) * 500.0f) + *(f32 *)((u8 *)temp_v0 + 0x34);
        *(f32 *)((u8 *)arg0 + 0x44) = (*(f32 *)((u8 *)temp_v1 + 0x34) * 500.0f) + *(f32 *)((u8 *)temp_v0 + 0x38);
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 6);
        *(f32 *)((u8 *)arg0 + 0x48) = (*(f32 *)((u8 *)temp_v1 + 0x38) * 500.0f) + *(f32 *)((u8 *)temp_v0 + 0x3C);
    } else {
        *(s32 *)((u8 *)arg0 + 0x58) &= ~4;
        *(volatile s32 *)((u8 *)arg0 + 0x58) = *(s32 *)((u8 *)arg0 + 0x58) & ~2;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F00EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150F00EC.s")
void *func_10022EC0(void *, const void *, u32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game11D030Locals {
    s32 payload;
    s32 position[3];
    u8 descriptor_0;
    s8 descriptor_1;
    s16 descriptor_2;
    s8 descriptor_4;
    u8 pad15[3];
    s32 saved;
} Game11D030Locals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F0198 CURRENT (120) */
s32 func_150F0198(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    Game11D030Locals locals;
    register s32 value;

    locals.payload = arg4;
    locals.descriptor_0 = 2;
    locals.descriptor_1 = -1;
    locals.descriptor_2 = 0x12C;
    locals.descriptor_4 = 0x21;
    locals.position[0] = 0;
    locals.position[1] = 0;
    locals.position[2] = 0;
    value = func_151602C0(&locals.descriptor_0, &locals.position[0], arg0, arg1, arg2,
                          arg3, 0xFF, 0, 4, arg5, arg6);
    if (value != 0) {
        locals.saved = value;
        func_10022EC0((u8 *) value + 0x18, &locals.payload, 4);
        value = locals.saved;
    }
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F0198 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150F0198.s")
