#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1179B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EA5CC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s32 field0;
    s32 field4;
    u8 field8;
    u8 pad9[3];
    void *fieldC;
    s8 field10;
    u8 pad11[3];
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    s16 field28;
    s8 field2A;
    s8 field2B;
    s8 field2C;
    s8 field2D;
} Game1179B0Packet;

extern f32 D_800A1438;

void func_150EA500(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    Game1179B0Packet packet;
    s32 mode;

    packet.field0 = 0;
    packet.field4 = 0;
    packet.field8 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field20 = 25.0f;
    packet.field24 = D_800A1438;
    packet.fieldC = arg0;
    packet.field10 = 1;
    packet.field14 = 0.0f;
    packet.field18 = 0.0f;
    packet.field1C = 0.0f;
    if (arg1 == -1) {
        packet.field28 = 0x12C;
    } else {
        packet.field28 = arg1;
    }
    if (arg1 == -1) {
        mode = 0;
    } else {
        mode = 4;
    }
    packet.field2A = mode | 0xA;
    packet.field2B = 7;
    packet.field2C = -1;
    packet.field2D = 6;
    func_1513418C(&packet, 0, 0xFF, 0);
}
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void *func_10022EC0(void *, const void *, u32);

typedef struct Game1179B0Burst {
    s32 flags, zero4;
    s16 texture, lifetime;
    s32 zeroC, zero10;
    u8 zero14, zero15, zero16, zero17, zero18, zero19, zero1A;
    u8 alpha, maximum, kind;
    s16 duration, period, zero22;
    f32 zero24, width, height;
    f32 x, y, z;
    f32 zero3C, zero40, zero44;
    f32 vx, vy, vz, rotation;
    s32 mode, unused5C;
    s8 field60, field61, field62, field63;
    u8 pad64[0xC];
} Game1179B0Burst;

typedef struct Game1179B0BurstMotion {
    f32 size;
    u8 mode0, mode1, count0, count1;
    f32 amount0, amount1, speed, damping;
    u8 mode2, mode3, count2, count3;
    f32 amount2, amount3, sourceScale;
} Game1179B0BurstMotion;

void *func_151303BC(s32, u8, s32);
extern f32 D_800A143C, D_800A1440, D_800A1444, D_800A1448;
extern f32 D_800A144C, D_800A1450, D_800A1454, D_800A1458;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EA5CC CURRENT (596) */
void func_150EA5CC(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                  f32 arg4, f32 arg5) {
    Game1179B0Burst burst;
    void *spawned;
    Game1179B0BurstMotion motion;
    motion.sourceScale = 1000.0f;
    burst.z = arg2;
    motion.speed = 4.0f;
    motion.damping = 0.25f;
    burst.kind = 0x2F;
    burst.texture = 0xC01;
    burst.flags = 0x200005;
    burst.zero4 = 0;
    burst.zero1A = 0;
    burst.zero19 = 0;
    burst.zero18 = 0;
    burst.zero17 = 0;
    burst.zero16 = 0;
    burst.zero15 = 0;
    burst.zero14 = 0;
    burst.zero10 = 0;
    burst.zeroC = 0;
    burst.maximum = 0xFF;
    burst.zero22 = 0;
    burst.zero24 = 0.0f;
    burst.mode = 0x3207;
    burst.field60 = 5;
    burst.field61 = 5;
    burst.field62 = 4;
    burst.field63 = -1;
    burst.x = arg0;
    burst.y = arg1;
    burst.zero3C = 0.0f;
    burst.zero40 = 0.0f;
    burst.zero44 = 0.0f;
    burst.duration = 30;
    burst.period = 8;
    motion.mode0 = 0;
    motion.mode1 = 0;
    motion.mode2 = 0;
    motion.mode3 = 0;
    burst.vx = -arg3 * D_800A143C;
    burst.vy = 0.0f;
    burst.vz = -arg5 * D_800A143C;
    if (func_150ADA20() & 1) burst.mode |= 0x40;
    if (func_150ADA20() & 1) burst.mode |= 0x80;
    burst.lifetime = func_150ADA20() % 51U + 106;
    burst.alpha = func_150ADA20() % 101U + 100;
    motion.size = burst.width = burst.height = func_150ADA68() * 62.0f + 41.0f;
    motion.count0 = func_150ADA20() % 5U + 4;
    motion.count1 = func_150ADA20() % 5U + 4;
    motion.amount0 = (func_150ADA68() * 0.25f + D_800A1440) * motion.size;
    motion.amount1 = (func_150ADA68() * 0.25f + D_800A1444) * motion.size;
    motion.count2 = func_150ADA20() % 5U + 4;
    motion.count3 = func_150ADA20() % 5U + 4;
    motion.amount2 = (func_150ADA68() * D_800A1448 + D_800A144C) * motion.size;
    motion.amount3 = (func_150ADA68() * D_800A1450 + D_800A1454) * motion.size;
    burst.rotation = (func_150ADA68() * 60.0f + 21.0f) * D_800A1458;
    spawned = func_151303BC((s32)&burst, 2, 0x28);
    if (spawned != NULL) func_10022EC0((u8 *)spawned + 0xA8, &motion, 0x28);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EA5CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1179B0/func_150EA5CC.s")
