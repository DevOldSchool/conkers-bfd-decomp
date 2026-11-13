#include "types.h"

/*
 * Reviewed source unit: src/game/game_1F4350.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_model_anchor_owner_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C7038
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_1513264C(void *, s32, s32, s32, s32, u8, s32);
void *func_10022EC0(void *, const void *, u32);
extern s32 D_800A5480[3];

typedef struct Game1F4350Copy3 {
    s32 words[3];
} Game1F4350Copy3;

typedef struct {
    u8 flags;
    u8 pad1[3];
    f32 field04, field08, field0C, field10;
    Game1F4350Copy3 angles;
    f32 scale[3];
    Game1F4350Copy3 position, velocity, field44;
    f32 field50;
    s32 field54;
    s16 field58, field5A;
    u8 field5C;
    u8 pad5D[3];
    s32 field60;
    u8 field64, field65, field66, field67, field68, field69;
    u8 field6A, field6B, field6C;
    s8 field6D;
    u8 field6E, pad6F;
    void *field70;
    u8 field74, pad75;
    s16 field76, field78;
    u8 pad7A[2];
    s32 field7C;
} Game1F4350Packet;


void func_151C6EA0(u8 *arg0, u8 arg1, s32 arg2) {
    Game1F4350Packet packet;
    void *result;

    packet.flags = 0;
    packet.field04 = 1.0f;
    packet.field08 = 1.0f;
    packet.field10 = 1.0f;
    packet.field0C = 1.0f;
    packet.angles = *(Game1F4350Copy3 *)D_800A5480;
    packet.scale[0] = 1.0f;
    packet.scale[1] = 1.0f;
    packet.scale[2] = 1.0f;
    packet.position = *(Game1F4350Copy3 *)D_800A5480;
    packet.velocity = *(Game1F4350Copy3 *)D_800A5480;
    packet.field44 = *(Game1F4350Copy3 *)D_800A5480;
    packet.field54 = 0x11900;
    packet.field58 = 0x12C;
    packet.field5A = 0xF;
    packet.field5C = 0;
    packet.field60 = 0;
    packet.field64 = 0x64;
    packet.field65 = 0x17;
    packet.field66 = 0;
    packet.field67 = 0;
    packet.field68 = 0;
    packet.field69 = 0;
    packet.field6A = 0;
    packet.field6B = 0;
    packet.field6C = 5;
    packet.field6D = -1;
    packet.field6E = 1;
    packet.field50 = 0.0f;
    packet.field70 = arg0;
    packet.field74 = arg0[0x3B];
    packet.field76 = 1;
    packet.field78 = 0xFF;
    packet.field7C = 0;
    result = func_1513264C(&packet.field04, 3, 0xFF, 0, 1, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x170, &packet, 1);
    }
}
s32 func_15142A5C(void *);          /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C7038 CURRENT (863) */
s32 func_151C7038(void *arg0) {
    void *sp1C;
    void *temp_a2;

    temp_a2 = *(void **)((u8 *)arg0 + 0x7C);
    if (*(u16 *)((u8 *)temp_a2 + 0x84) != 0xE9) {
        return 0;
    }
    sp1C = temp_a2;
    if (func_15142A5C(temp_a2) != 0) {
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) | 0x20000);
    } else {
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) & 0xFFFDFFFF);
    }
    {
        f32 var_fv0 = *(f32 *)((u8 *)temp_a2 + 0x4C) * 35.0f;
    if (var_fv0 > 255.0f) {
        var_fv0 = 255.0f;
    } else if (var_fv0 < 0.0f) {
        var_fv0 = 0.0f;
    }
    *(s8 *)((u8 *)arg0 + 0x70) = (s8) (u32) var_fv0;
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C7038 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4350/func_151C7038.s")
