#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BA1D0.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518CD20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1BA1D0Vector { f32 x, y, z; } Game1BA1D0Vector;
typedef struct Game1BA1D0Spawn {
    s32 flags, word04;
    s16 type, life;
    s32 word0C, word10;
    u8 color[4], color2[4];
    u8 byte1C, byte1D;
    s16 short1E, short20, short22;
    f32 value24, scaleX, scaleY;
    Game1BA1D0Vector position, offset, velocity;
    f32 acceleration;
    s32 motionFlags;
    u8 unused5C[4];
    s8 byte60, byte61, byte62, byte63, byte64, byte65;
    u8 unused66[0xA];
} Game1BA1D0Spawn;

void *func_10003C6C(s32, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void *func_15130280(void *, u8, void *, s32, u8, s32);
void func_1514373C(f32, f32, f32 *, f32 *);
void func_15145DB4(void *, Game1BA1D0Vector *, Game1BA1D0Vector *, s32);
extern f32 D_800A7450, D_800A7454, D_800A7458, D_800A745C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518CD20 CURRENT (4353) */
void func_1518CD20(void *arg0, u8 arg1, s32 arg2) {
    Game1BA1D0Spawn spawn;
    Game1BA1D0Vector *points;
    Game1BA1D0Vector *transformed;
    Game1BA1D0Vector *center;
    Game1BA1D0Vector *point;
    u8 *result;
    f32 extra;
    f32 factor;
    f32 speed;
    s16 count;
    s16 remaining;
    s16 i;
    s32 bytes;
    s32 flag;
    s32 flag2;

    count = func_150ADA20() % 11U + 25;
    remaining = count;
    if (count > 0) {
        bytes = (count + 1) * sizeof(Game1BA1D0Vector);
        points = func_10003C6C(bytes, 3, 1, 0, 1);
        transformed = func_10003C6C(bytes, 3, 1, 0, 1);
        if (points != 0 && transformed != 0) {
            i = 0;
            if (count > 0) {
                factor = D_800A7450;
                do {
                    func_1514373C(func_150ADA68() * factor + factor, 114.0f, &points[i].x, &points[i].z);
                    points[i].y = -90.0f;
                    points[i].x += 111.0f;
                    i++;
                } while (i < count);
                i = 0;
            }
            points[count].x = 111.0f;
            points[count].y = -90.0f;
            points[count].z = 0.0f;
            func_15145DB4(arg0, points, transformed, count + 1);
            spawn.color2[2] = 0x62;
            spawn.byte1D = 0x6C;
            spawn.type = 0x5103;
            spawn.flags = 0x200005;
            spawn.color[0] = 0xE7;
            spawn.color[1] = 0xE7;
            spawn.color[2] = 0xB6;
            spawn.color2[0] = 0x9E;
            spawn.color2[1] = 0x9E;
            spawn.word04 = 0;
            spawn.word0C = 0;
            spawn.word10 = 0;
            spawn.color[3] = 0xFF;
            spawn.byte1C = 0xFF;
            spawn.offset.x = 0.0f;
            spawn.offset.y = 0.0f;
            spawn.offset.z = 0.0f;
            spawn.short1E = 25;
            spawn.short20 = 10;
            spawn.byte60 = 8;
            spawn.byte61 = 6;
            spawn.byte62 = 16;
            spawn.byte63 = -1;
            spawn.byte64 = -1;
            spawn.byte65 = 0;
            factor = D_800A745C;
            spawn.motionFlags = 0x80CE07;
            spawn.value24 = D_800A7454;
            extra = D_800A7458;
            center = &transformed[count];
            do {
                spawn.motionFlags &= ~0xC0;
                flag = 0;
                if (func_150ADA20() & 1) {
                    flag = 0x80;
                }
                if (func_150ADA20() & 1) {
                    flag2 = 0x40;
                } else {
                    flag2 = 0;
                }
                spawn.motionFlags |= flag2 | flag;
                speed = (func_150ADA68() * 202.0f + 250.0f) * factor;
                spawn.short22 = func_150ADA20() % 26U + 25;
                spawn.life = spawn.short22;
                spawn.scaleY = func_150ADA68() * 105.0f + 150.0f;
                spawn.scaleX = spawn.scaleY;
                point = &transformed[i];
                spawn.position = *point;
                spawn.velocity.x = (point->x - center->x) * speed;
                spawn.velocity.y = (point->y - center->y) * speed;
                spawn.velocity.z = (point->z - center->z) * speed;
                spawn.acceleration = (func_150ADA68() * 880.0f + 13.0f) * factor;
                spawn.color2[3] = func_150ADA20() % 176U + 80;
                result = func_15130280(&spawn, 1, 0, 4, arg1, arg2);
                if (result != 0) {
                    func_10022EC0(result + 0xA8, &extra, 4);
                }
                remaining--;
                i++;
            } while (remaining > 0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518CD20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BA1D0/func_1518CD20.s")
