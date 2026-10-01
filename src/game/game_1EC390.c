#include "types.h"

/*
 * Reviewed source unit: src/game/game_1EC390.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BEEE0
 * - func_151BF0C8
 * - func_151BF340
 * - func_151BF81C
 * - func_151BFB2C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1EC390Selector {
    u8 values[3];
} Game1EC390Selector;

typedef struct Game1EC390Position {
    s32 values[3];
} Game1EC390Position;

typedef struct Game1EC390Spawn {
    f32 scale0;
    f32 scale4;
    f32 scale8;
    f32 scaleC;
    f32 zero10;
    f32 amount;
    f32 zero18;
    f32 scale1C;
    f32 scale20;
    f32 scale24;
    Game1EC390Position position;
    f32 zeros[7];
    s32 flags;
    s16 lifetime;
    s16 kind;
    u8 selector;
    u8 pad59[3];
    s32 owner;
    u8 alpha;
    u8 state;
    u8 zero62;
    u8 zero63;
    u8 zero64;
    u8 zero65;
    u8 zero66;
    u8 zero67;
    u8 mode;
    u8 pad69;
    u8 zero6A;
    u8 pad6B;
    s32 zero6C;
    u8 zero70;
    u8 pad71;
    s16 one72;
    s16 maximum;
} Game1EC390Spawn;

void *func_15132A4C(void *, s32, s32, s32, u8, s32);
s32 func_15133760(s32, void *);
extern Game1EC390Selector D_8008FBC0;
extern f32 D_800AA8E4;
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BEEE0 CURRENT (1392) */
void *func_151BEEE0(f32 arg0, Game1EC390Position *arg1, s32 arg2,
                   u8 arg3, s32 arg4, s32 arg5, s32 arg6,
                   s32 arg7, s32 arg8) {
    s32 offset;
    Game1EC390Selector selectors;
    s32 flags;
    Game1EC390Spawn spawn;
    u8 *object;
    u8 *transform;

    offset = (u8)arg4;
    selectors = D_8008FBC0;
    if (offset >= 3) {
        return 0;
    }
    spawn.scale0 = 1.0f;
    spawn.scale4 = 1.0f;
    spawn.scaleC = D_800AA8E4;
    spawn.scale8 = D_800AA8E4;
    spawn.zero10 = 0.0f;
    spawn.amount = arg0;
    spawn.zero18 = 0.0f;
    spawn.scale1C = 1.0f;
    spawn.scale20 = 1.0f;
    spawn.scale24 = 1.0f;
    spawn.position = *arg1;
    spawn.zeros[0] = 0.0f;
    spawn.zeros[1] = 0.0f;
    spawn.zeros[2] = 0.0f;
    spawn.zeros[3] = 0.0f;
    spawn.zeros[4] = 0.0f;
    spawn.zeros[5] = 0.0f;
    spawn.zeros[6] = 0.0f;
    if ((u8)arg5 != 0) {
        flags = 0x4000;
    } else {
        flags = 0;
    }
    spawn.flags = flags | 0x1D00 | 0x80000 | 0x40000;
    spawn.lifetime = 0x12C;
    spawn.kind = 0x26;
    spawn.alpha = 0xFF;
    spawn.selector = selectors.values[offset];
    spawn.owner = arg6;
    if (D_800BE9F0 == 7) {
        spawn.state = 0x18;
    } else {
        spawn.state = 0;
    }
    spawn.zero62 = 0;
    spawn.zero63 = 0;
    spawn.zero64 = 0;
    spawn.zero65 = 0;
    spawn.zero66 = 0;
    spawn.zero67 = 0;
    spawn.mode = 2;
    spawn.zero6A = 0;
    spawn.zero6C = 0;
    spawn.zero70 = 0;
    spawn.one72 = 1;
    spawn.maximum = 0xFF;
    object = func_15132A4C(&spawn, arg2, arg3, 0, (u8)arg7, arg8);
    if (object != 0) {
        offset = 0;
        transform = object + 0x90;
        do {
            func_15133760((s32)transform, object);
            offset += 0x40;
            transform += 0x40;
        } while (offset != 0x80);
    }
    return object;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BEEE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EC390/func_151BEEE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EC390/func_151BF0C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EC390/func_151BF340.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EC390/func_151BF81C.s")

typedef struct {
    u8 pad0[0x28];
    void *primary;
    void *secondary[2];
} Game1EC390ResourceOwner;

void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BFB2C CURRENT (50) */
void func_151BFB2C(Game1EC390ResourceOwner *arg0) {
    u8 i;
    struct { void *primary; void *secondary[2]; } *resources;

    if (*(s32 *)&arg0->primary != 0) {
        func_1516972C((void *)*(s32 *)&arg0->primary);
    }

    resources = (void *)((u8 (*)[1])arg0)[0x28];
    for (i = 0; i < 2; i++) {
        if (resources->secondary[i] != 0) {
            func_1516972C(resources->secondary[i]);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BFB2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EC390/func_151BFB2C.s")

void func_1514933C(s32 arg0);

void func_151BFBA4(s32 arg0) {
    func_151BFB2C(arg0);
    func_1514933C(arg0);
}
