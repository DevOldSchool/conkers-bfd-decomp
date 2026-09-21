#include "types.h"

/*
 * Reviewed source unit: src/game/game_1F2730.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C5280
 * - func_151C5588
 * - func_151C577C
 * - func_151C5F44
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F2730/func_151C5280.s")
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32,
                   s32, s32, s32, s32, s32);
u32 func_150ADA20();
f32 func_150ADA68(void);
extern s32 D_800AAA90;
extern s32 D_800AAA9C;
extern f32 D_800AAABC;
extern f32 D_800AAAC0;
extern f32 D_800AAAC4;
extern f32 D_800AAAC8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C5588 CURRENT (12) */
void func_151C5588(s32 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    struct {
        u32 sp44;
        u32 sp48;
        f32 sp50;
        f32 sp54;
    } locals;

    locals.sp54 = ((func_150ADA68() * D_800AAABC) + 604.0f) * D_800AAAC0;
    locals.sp50 = ((func_150ADA68() * 59.0f) + 141.0f) * D_800AAAC4;
    locals.sp44 = func_150ADA20();
    locals.sp48 = func_150ADA20();
    func_15102B38(arg0, 0, (s32)&D_800AAA90, (s32)&D_800AAA9C,
                  &locals.sp50, (locals.sp44 & 3) + 6, 0xFF,
                  (func_150ADA68() * 270.0f) + D_800AAAC8,
                  arg1, 0xFF, 0, arg2, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C5588 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F2730/func_151C5588.s")
typedef struct {
    u8 type;
    s8 neg_one;
    s16 lifetime;
    s8 zero;
} Game1F2730Descriptor;

s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20();

void func_151C56A4(void *arg0, u8 arg1, s32 arg2) {
    Game1F2730Descriptor descriptor;
    s32 position[3];

    descriptor.type = 3;
    descriptor.neg_one = -1;
    descriptor.lifetime = (func_150ADA20() % 3U) + 3;
    descriptor.zero = 0;
    position[0] = (s32)*(f32 *)arg0;
    position[1] = (s32)*(f32 *)((u8 *)arg0 + 4);
    position[2] = (s32)*(f32 *)((u8 *)arg0 + 8);
    func_151602C0((u8 *)&descriptor, position,
                  (func_150ADA20(arg0) & 1) + 6,
                  0xFF, 0xE8, 0xAB, 0xFF, 0, 0, arg1, arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F2730/func_151C577C.s")
void func_15137F30(void *, void *, void *, void *, f32, void *, void *, void *,
                   void *, f32 *, s16 *, s8 *, f32 *);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32,
                   f32, s32, s32, s32, s32, s32, s32);

void func_151C5E74(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4,
                   u8 *arg5) {
    f32 position[3];
    f32 direction[3];
    f32 vector[3];
    f32 value;
    s16 count;
    s8 alpha;
    f32 scale;

    func_15137F30(arg0, arg1, arg2, arg3, arg4, arg5, position, direction,
                  vector, &value, &count, &alpha, &scale);
    func_151D9014(position, vector, 1, value, count, (u8)alpha, scale, 0,
                  1.0f, 1.0f, 1, 0, 1, 0, arg5[0xC], arg5[1]);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F2730/func_151C5F44.s")
typedef struct {
    s16 field00;
    s16 field02;
    s32 field04;
    s16 field08;
    s16 field0A;
    s16 field0C;
    s16 field0E;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    u8 field24;
    s8 field25;
    s16 field26;
    s16 field28;
    u8 pad2A[2];
    f32 field2C;
    f32 field30;
    f32 field34;
    s32 field38;
} Game1F2730Packet;

void func_15154684(s16 *, u8, s32);
extern f32 D_800AAAF4;
extern f32 D_800AAAF8;
extern f32 D_800AAAFC;

void func_151C61A0(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    Game1F2730Packet packet;

    packet.field10 = 5.0f;
    packet.field00 = 0xA;
    packet.field14 = 7.0f;
    packet.field02 = 4;
    packet.field04 = arg0;
    packet.field08 = 0;
    packet.field0C = 0xFF;
    packet.field0A = -0x18;
    packet.field0E = 0x19;
    packet.field24 = 0xBE;
    packet.field25 = 0x41;
    packet.field26 = 0xC8;
    packet.field28 = 0x96;
    packet.field18 = D_800AAAF4;
    packet.field1C = D_800AAAF8;
    packet.field20 = D_800AAAFC;
    packet.field2C = 96.0f;
    packet.field30 = 109.0f;
    packet.field34 = 1.0f;
    packet.field38 = arg1;
    func_15154684(&packet.field00, arg2, arg3);
}
