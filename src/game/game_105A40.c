#include "types.h"

/*
 * Reviewed source unit: src/game/game_105A40.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D85AC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game105A40Header {
    s16 field_0;
    s16 field_2;
} Game105A40Header;

Game105A40Header *func_150D8590(Game105A40Header *arg0, s32 arg1) {
    arg0->field_0 = 0x42;
    arg0->field_2 = 0;
    return arg0 + 1;
}
typedef struct Game71820XZ {
    f32 x, y, z;
} Game71820XZ;

typedef struct Game71820Hit {
    f32 height;
    s16 points[9];
    s32 object;
    u8 flags, active;
    u8 pad1E[2];
    s32 field20;
} Game71820Hit;

typedef struct GameDC6B0Burst {
    s16 count, countRange;
    u8 kind, pad5;
    u16 field6;
    s32 flags, fieldC;
    s16 timer, timerRange;
    s32 field14, field18;
    u8 field1C, field1D, field1E, field1F, field20;
    u8 field21, field22, field23, field24, field25;
    s16 field26, field28, field2A;
    f32 field2C, field30, field34;
    Game71820XZ position;
    s16 yaw, pitch, yawRange, pitchRange;
    f32 speed, speedRange, field54, field58;
    u32 field5C;
    s8 field60, field61;
    u8 field62, field63, field64;
    u8 pad65[3];
    f32 field68;
} GameDC6B0Burst;

void func_1504715C(Game71820Hit *, void *);
s32 func_15046C80(Game71820XZ *, u16, f32, Game71820Hit *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_150E7FEC(f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150E83AC(void *, s16, u8, s32);
void func_15153634(GameDC6B0Burst *, s32, s32, s32);
extern f32 D_800A0B18, D_800A0B1C, D_800A0B20, D_800A0B24;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D85AC CURRENT (1772) */
void func_150D85AC(void *arg0) {
    f32 position[3];
    f32 probe[3];
    Game71820Hit hit;
    GameDC6B0Burst packet;

    position[0] = *(f32 *)((u8 *)arg0 + 0x14);
    position[1] = *(f32 *)((u8 *)arg0 + 0x180);
    position[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    probe[0] = position[0];
    probe[2] = position[2];
    probe[1] = position[1] + 100.0f;
    func_1504715C(&hit, arg0);
    if (func_15046C80((Game71820XZ *)probe, 0, position[1] - 200.0f, &hit) != 0 && (hit.flags & 1)) {
        u32 random;
        f32 size;

        position[0] = probe[0];
        position[1] = hit.height;
        position[2] = probe[2];
        size = func_150ADA68();
        random = func_150ADA20();
        func_150E7FEC(size * 109.0f + 140.0f, (u8)((random % 86U) + 170),
            (s32)hit.points, (s32)position, (func_150ADA20() % 251U) + 500,
            0, 1, 0, 0, 0, 255, 0);
    }
    func_150E83AC(position, (s16)((func_150ADA20() % 62U) + 120), 255, 1);
    packet.count = 26;
    packet.field2C = D_800A0B18;
    packet.field30 = 150.0f;
    packet.field34 = 298.0f;
    packet.field6 = 0x5103;
    packet.position.x = position[0];
    packet.countRange = 7;
    packet.kind = 0x6C;
    packet.flags = 0x200005;
    packet.timer = 30;
    packet.timerRange = 10;
    packet.field1F = 255;
    packet.field1C = 0xB9;
    packet.field1D = 0xC7;
    packet.field1E = 0xC4;
    packet.field20 = 0x95;
    packet.field21 = 0x91;
    packet.field22 = 0x7E;
    packet.field23 = 100;
    packet.field24 = 0x9B;
    packet.field25 = 255;
    packet.field26 = 30;
    packet.field28 = 8;
    packet.fieldC = 0;
    packet.field14 = 0;
    packet.field18 = 0;
    packet.field2A = 30;
    packet.position.y = position[1] + 35.0f;
    packet.yaw = 0;
    packet.pitch = -16;
    packet.yawRange = 255;
    packet.pitchRange = 20;
    packet.speed = 18.0f;
    packet.speedRange = 18.0f;
    packet.field5C = 0x840E07;
    packet.field60 = 16;
    packet.field61 = -1;
    packet.field62 = 8;
    packet.field63 = 6;
    packet.field64 = 1;
    packet.field54 = D_800A0B1C;
    packet.field58 = D_800A0B20;
    packet.position.z = position[2];
    packet.field68 = D_800A0B24;
    func_15153634(&packet, 255, 255, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D85AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105A40/func_150D85AC.s")
s32 func_150D88AC(void *arg0) {
    u8 var_v0;

    var_v0 = 1;
    if (*(u8 *)(*(u8 **)((u8 *)arg0 + 0x18) + 0x6F) != 0) {
        *(u8 *)(*(u8 **)((u8 *)arg0 + 0x14) + 9) = 0;
    } else {
        *(u8 *)(*(u8 **)((u8 *)arg0 + 0x14) + 9) = 1;
    }
    return (s32) var_v0;
}
