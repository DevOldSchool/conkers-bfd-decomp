#include "types.h"

/*
 * Reviewed source unit: src/game/game_19E040.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15170B90
 * - func_15170F4C
 * - func_15171200
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

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
s32 func_1518C900(s32);
f32 func_150ADA68(void);
void func_15168BE4(void *, s32, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)
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
