#include "types.h"

/*
 * Reviewed source unit: src/game/game_130240.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15102D90
 * - func_15102EB8
 * - func_15103254
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15145EA4(s32 *, s32 *, s32, s32);
void *func_1503195C(void *, s32, s32);
s32 func_1514654C(void *, s32, s32, void **, void **, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15102D90 CURRENT (2238) */
s32 func_15102D90(void *arg0) {
    void *sp40[2];
    void *sp38[2];
    s16 temp_a1;
    void *temp_v0;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s1 = *(u8 **)((u8 *)arg0 + 0x110);
    *(u8 *)((u8 *)arg0 + 0x124) &= 0xFFFE;
    if ((*(u8 *)((u8 *)arg0 + 0x114) != temp_s1[0x3B]) ||
        (*(s32 *)temp_s1 == 0)) {
        return 0;
    }
    if ((*(s32 *)(temp_s1 + 0x1D4) == 0) ||
        ((temp_s1[0x74] & 0xF) == 0xF)) {
        return 1;
    }
    temp_s0 = (u8 *)arg0 + 0x110;
    sp40[0] = (u8 *)arg0 + 0x34;
    sp40[1] = (u8 *)arg0 + 0x40;
    sp38[0] = temp_s0 + 0x18;
    sp38[1] = temp_s0 + 0x24;
    temp_a1 = *(s16 *)(temp_s0 + 0xC);
    if (temp_a1 != -1) {
        temp_v0 = func_1503195C(temp_s1, temp_a1, 0);
        if (temp_v0 == 0) {
            return 0;
        }
        if (func_1514654C(temp_s1, (s32)temp_v0,
                          *(s32 *)(temp_s0 + 0x10), sp40, sp38, 2) == 0) {
            return 0;
        }
        goto block_12;
    }
    func_15145EA4((s32 *)sp40, (s32 *)sp38,
                  *(s32 *)(temp_s1 + 0x1D4) + *(s32 *)(temp_s0 + 8), 2);
block_12:
    temp_s0[0x14] |= 1;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15102D90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_130240/func_15102D90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_130240/func_15102EB8.s")
typedef struct Game130240Vector {
    f32 x, y, z;
} Game130240Vector;

typedef struct Game130240Descriptor {
    s32 flags;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s32 fieldC;
    s32 field10;
    u8 color14[4];
    u8 color18[4];
    u8 alpha;
    u8 kind;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    Game130240Vector position;
    Game130240Vector velocity;
    Game130240Vector acceleration;
    f32 field54;
    s32 field58;
    s32 field5C;
    u8 field60;
    u8 field61;
    s8 field62;
    s8 field63;
    s8 field64;
    s8 field65;
    u8 field66;
    u8 pad67[9];
} Game130240Descriptor;

u32 func_150ADA20(void);
void func_15130374(s32, u8, s32, u8, s32);
extern s32 D_80088BD0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15103254 CURRENT (828) */
void func_15103254(s32 arg0, s32 arg1, f32 arg2, Game130240Vector *arg3,
                   s32 arg4, s32 arg5, s32 arg6) {
    s32 second;
    Game130240Descriptor descriptor;
    s32 first;

    descriptor.kind = D_80088BD0[func_150ADA20() & 3];
    descriptor.field8 = 0x2203;
    descriptor.flags = 0x200005;
    descriptor.field4 = 0x20000;
    descriptor.fieldA = (s16)arg0 + 1;
    descriptor.fieldC = 0;
    descriptor.field10 = 0;
    descriptor.color14[0] = 0xFF;
    descriptor.color14[1] = 0xFF;
    descriptor.color14[2] = 0xFF;
    descriptor.color14[3] = 0xFF;
    descriptor.color18[0] = 0xFF;
    descriptor.color18[1] = 0xFF;
    descriptor.color18[2] = 0xFF;
    descriptor.alpha = 0xFF;
    descriptor.field2C = arg2;
    descriptor.field28 = arg2;
    descriptor.color18[3] = (u8)arg1;
    descriptor.position = *arg3;
    descriptor.field1E = 3;
    descriptor.field20 = 0x55;
    descriptor.field22 = 1;
    descriptor.velocity.x = 0.0f;
    descriptor.velocity.y = 0.0f;
    descriptor.velocity.z = 0.0f;
    descriptor.acceleration.x = 0.0f;
    descriptor.acceleration.y = 0.0f;
    descriptor.acceleration.z = 0.0f;
    descriptor.field54 = 0.0f;
    descriptor.field24 = 1.0f;
    first = (func_150ADA20() & 1) ? 0x40 : 0;
    if (func_150ADA20() & 1) {
        second = 0x80;
    } else {
        second = 0;
    }
    descriptor.field58 = second | 1 | first | 0xC200 | 0x40000 | 0x800000;
    descriptor.field60 = 6;
    descriptor.field61 = 8;
    descriptor.field62 = -1;
    descriptor.field63 = -1;
    descriptor.field64 = -1;
    descriptor.field65 = 0;
    descriptor.field66 = (u8)arg4;
    func_15130374((s32)&descriptor, 1, 0, (u8)arg5, arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15103254 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_130240/func_15103254.s")
