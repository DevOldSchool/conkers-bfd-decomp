#include "types.h"

/*
 * Reviewed source unit: src/game/game_123D40.c
 * Boundary evidence: docs/evidence/game_raw_record_glyph_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F695C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 field0;
    u8 pad1[3];
    void *field4;
    s8 field8;
    u8 pad9[3];
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    s8 field24;
    u8 pad25;
    s16 field26;
    s16 field28;
    s16 field2A;
    s16 field2C;
    s8 field2E;
    s8 field2F;
    s8 field30;
    u8 pad31[3];
    f32 field34;
    s8 field38;
    s8 field39;
} Game123D40Packet;

void func_15134DAC(u8 *, s32, void *, s16);
extern f32 D_800A1B70;

void func_150F6890(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    Game123D40Packet packet;

    packet.field0 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field1C = D_800A1B70;
    packet.field20 = 8.5f;
    packet.field34 = 1.0f;
    packet.field4 = arg0;
    packet.field8 = 3;
    packet.fieldC = 0.0f;
    packet.field10 = 0.0f;
    packet.field14 = 0.0f;
    packet.field18 = 0.0f;
    packet.field24 = 2;
    packet.field26 = 0x28;
    packet.field28 = 0x10;
    packet.field2A = arg1;
    packet.field2E = 5;
    packet.field2F = 8;
    packet.field30 = -1;
    packet.field38 = 0;
    packet.field39 = -1;
    packet.field2C = 0;
    func_15134DAC(&packet.field0, 0, arg0, arg1);
}
void func_15137F30(void *, void *, void *, void *, f32, void *, void *, void *,
                   void *, f32 *, s16 *, s8 *, f32 *);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32, f32,
                   s32, s32, s32, s32, s32, s32);
void func_1504715C(f32 *, s32);
f32 func_150ADA68(void);
extern f32 D_800A1B74;
extern f32 D_800A1B78;
extern f32 D_800A1B7C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F695C CURRENT (1460) */
void func_150F695C(void *arg0, void *arg1, void *arg2, void *arg3,
                    f32 arg4, u8 *arg5) {
    struct {
        f32 value;
        u8 pad60[0x14];
        s32 field74;
        s8 field78;
        s8 field79;
        u8 pad7A[2];
        s32 field7C;
        f32 scale;
        u8 pad84;
        s8 field85;
        s16 field86;
        f32 field88;
        f32 vector8C[3];
        u8 field98[0xC];
        f32 vectorA4[3];
    } local;
    u8 selected;
    s32 variant;
    f32 random;

    func_15137F30(arg0, arg1, arg2, arg3, arg4, arg5,
                   local.vectorA4, local.field98, local.vector8C,
                   &local.field88, &local.field86, &local.field85,
                   &local.scale);
    random = func_150ADA68();
    local.scale *= 1.0f + (random + random);
    selected = func_150ADA68() < D_800A1B74;
    if (selected != 0) {
        func_1504715C(&local.value, *(s32 *)(arg5 + 0x1C));
    } else {
        local.field74 = 0;
        local.field78 = 0;
        local.field79 = 0;
        local.field7C = 0;
        local.value = D_800A1B78;
    }
    variant = 0;
    if (selected != 0 && func_150ADA68() < 0.5f) {
        variant = 1;
    }
    func_151D9014(local.vectorA4, local.vector8C, 1, local.field88,
                   local.field86, (u8)local.field85, local.scale, selected,
                   D_800A1B7C, D_800A1B7C, 1, (s32)&local.value, 1,
                   variant, arg5[0xC], arg5[1]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F695C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_123D40/func_150F695C.s")
