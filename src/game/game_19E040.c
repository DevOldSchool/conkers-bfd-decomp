#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_19E040.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15170B90
 * - func_15170F4C
 * - func_15171200
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game70F4CPacket {
    f32 position[3];
    f32 rotation[3];
    f32 velocity[3];
    f32 random[3];
    f32 scale[3];
    s32 life;
    s32 texture;
    u32 pad44;
    f32 color[3];
    u8 flags[10];
    u8 pad5E[2];
} Game70F4CPacket;

typedef struct {
    u16 values[3];
} Game70B90Kinds;
s32 func_1518C900(s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)
void func_151718F0(f32, f32, f32, f32, s32, f32, s32, s32, u8, s32);
extern f32 D_800A6E90[][3];
extern Game70B90Kinds D_800A6F80;
extern f32 D_800A6F88, D_800A6F8C, D_800A6F90, D_800A6F94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15170B90 CURRENT (9193) */
void func_15170B90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    f32 speed;
    Game70F4CPacket packet;
    f32 originX, originY, originZ;
    f32 x, y, z;
    Game70B90Kinds kinds;
    s32 index;
    s32 texture;
    f32 *entry;
    s32 kind;

    originX = *(s16 *)(arg0 + 0x10);
    originY = *(s16 *)(arg0 + 0x12);
    originZ = *(s16 *)(arg0 + 0x14);
    packet.rotation[0] = 0.0f;
    packet.rotation[1] = 0.0f;
    packet.rotation[2] = 0.0f;
    packet.scale[0] = 1.0f;
    packet.scale[1] = 1.0f;
    packet.scale[2] = 1.0f;
    packet.life = 60;
    packet.color[0] = D_800A6F88;
    packet.color[1] = D_800A6F8C;
    packet.flags[0] = 2;
    packet.color[2] = D_800A6F90;
    packet.flags[1] = 255;
    packet.flags[2] = 0;
    packet.flags[3] = 0;
    packet.flags[4] = 0;
    packet.flags[5] = 60;
    packet.flags[7] = arg2;
    packet.flags[8] = 0;
    packet.flags[9] = 0;
    speed = D_800A6F94;
    index = 0;
    entry = D_800A6E90[0];
    do {
        if (arg3 & 2) {
            kinds = D_800A6F80;
            kind = ((u8 *)&kinds)[index];
        } else {
            kind = arg1;
            if (arg3 & 1) kind = arg1 + index;
        }
        texture = func_1518C900(kind);
        x = entry[0];
        y = entry[1];
        z = entry[2];
        packet.position[1] = y + originY;
        packet.position[0] = x + originX;
        packet.flags[6] = kind;
        packet.velocity[0] = x * speed;
        packet.velocity[2] = z * speed;
        packet.position[2] = z + originZ;
        packet.velocity[1] = fabsf(y) * speed + 7;
        packet.velocity[0] += (f32)((s32)func_150ADA20() >> 16) * 0.00006103515625f;
        packet.velocity[1] += (f32)((s32)func_150ADA20() >> 16) * 0.00006103515625f;
        packet.velocity[2] += (f32)((s32)func_150ADA20() >> 16) * 0.00006103515625f;
        packet.random[0] = (f32)((s32)func_150ADA20() >> 16) * 0.0000762939453125f;
        packet.random[1] = (f32)((s32)func_150ADA20() >> 16) * 0.0000762939453125f;
        packet.random[2] = (f32)((s32)func_150ADA20() >> 16) * 0.0000762939453125f;
        packet.texture = texture;
        func_15168BE4((struct Game1944C0State *)&packet, (u8)arg4, arg5);
        index++;
        entry += 3;
    } while (index != 6);
    func_151718F0(originX, originY - 80.0f, originZ, 70.0f, 500,
                  0.00457763671875f, 0, 10, (u8)arg4, arg5);
    *(s8 *)(arg0 + 0x6E) = 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15170B90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19E040/func_15170B90.s")

void func_15170B90(s32, s32, s32, s32, s32, s32);
extern s32 D_800BE9F0;

void func_15170EC4(s32 arg0, u8 arg1, s32 arg2) {
    switch (D_800BE9F0) {
    case 2:
        func_15170B90(arg0, 1, 1, 1, (s32)arg1, arg2);
        return;
    case 16:
        func_15170B90(arg0, 0xA9, 8, 0, (s32)arg1, arg2);
        return;
    }
}
typedef struct Game70F4CEntry {
    u16 kind;
    u16 pad2;
    f32 position[3];
    f32 rotation[3];
} Game70F4CEntry;

s32 func_1518C900(s32);
f32 func_150ADA68(void);
f32 fabsf(f32);
extern Game70F4CEntry D_800A6ED8[];
extern f32 D_800A6F98, D_800A6F9C, D_800A6FA0;
extern f32 D_800A6FA4, D_800A6FA8, D_800A6FAC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15170F4C CURRENT (6028) */
void func_15170F4C(u8 *arg0, s32 arg1, s32 arg2) {
    Game70F4CPacket packet;
    volatile f32 originX;
    volatile f32 originY;
    volatile f32 originZ;
    Game70F4CEntry *entry;
    s32 index;
    s32 texture;
    f32 rate;
    f32 height;
    f32 speed;

    packet.flags[8] = 2;
    packet.flags[9] = 1;
    packet.flags[7] = 6;
    packet.flags[5] = 0;
    entry = D_800A6ED8;
    originX = *(s16 *)(arg0 + 0x10);
    index = 0;
    originY = *(s16 *)(arg0 + 0x12);
    rate = D_800A6FA4;
    height = D_800A6FA8;
    packet.rotation[0] = 0.0f;
    packet.rotation[1] = 0.0f;
    originZ = *(s16 *)(arg0 + 0x14);
    packet.rotation[2] = 0.0f;
    packet.scale[0] = 2.0f;
    packet.scale[1] = 2.0f;
    packet.scale[2] = 2.0f;
    packet.life = 60;
    packet.flags[0] = 2;
    packet.flags[1] = 255;
    packet.flags[2] = 0;
    packet.flags[3] = 0;
    packet.flags[4] = 0;
    speed = D_800A6FAC;
    packet.color[0] = D_800A6F98;
    packet.color[1] = D_800A6F9C;
    packet.color[2] = D_800A6FA0;
    do {
        texture = func_1518C900(entry->kind);
        packet.flags[6] = entry->kind;
        packet.position[0] = entry->position[0] + originX;
        packet.position[1] = entry->position[1] + originY;
        packet.position[2] = entry->position[2] + originZ;
        packet.velocity[0] = entry->position[0] * speed;
        packet.velocity[1] = fabsf(entry->position[1]) * height;
        packet.velocity[2] = entry->position[2] * speed;
        packet.rotation[0] = entry->rotation[0];
        packet.rotation[1] = entry->rotation[1];
        packet.rotation[2] = entry->rotation[2];
        packet.random[0] = packet.rotation[0] * rate;
        packet.random[1] = func_150ADA68() * 4.0f - 2.0f;
        packet.random[2] = func_150ADA68() * 10.0f - 5.0f;
        packet.texture = texture;
        func_15168BE4(&packet, (u8)arg1, arg2);
        index++;
        entry++;
    } while (index < 6);
    arg0[0x6E] = 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15170F4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19E040/func_15170F4C.s")


void func_150C3D5C(void);
void func_15060F28(u8 *, s32);

void func_151711C4(u8 *arg0) {
    if (arg0[4] == 0x33) {
        func_150C3D5C();
    }
    func_15060F28(arg0, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_19E040/func_15171200.s")
