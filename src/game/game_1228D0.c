#include "types.h"

/*
 * Reviewed source unit: src/game/game_1228D0.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 */

typedef struct Game1228D0Spawn {
    void *asset;
    s32 pad4;
    s32 packed0;
    s32 packed1;
    s32 lifetime;
    s16 total;
    s16 zero3A;
    s16 zero3C;
    s16 pad3E;
    f32 value0;
    f32 value1;
    s16 zero48;
    s16 zero4A;
    s16 scale0;
    s16 scale1;
    s16 size0;
    s16 size1;
    u8 byte54;
    u8 byte55;
    u8 byte56;
    u8 byte57;
    u8 byte58;
    u8 byte59;
    u8 byte5A;
    u8 byte5B;
    u8 byte5C;
    u8 byte5D;
} Game1228D0Spawn;

void func_15169968(void *);
extern u8 D_800917F8;
extern u8 D_80091930;
extern u8 D_8009193C;
extern u8 D_80091948;

void func_150F5420(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Game1228D0Spawn spawn;
    s32 total;

    if (arg3 != 0) {
        if (arg3 == 2) {
            spawn.size0 = 0xF0;
            spawn.size1 = 0xBA;
            spawn.asset = &D_80091948;
        } else {
            spawn.size0 = 0x10E;
            spawn.size1 = 0x7C;
            if (arg3 == 1) {
                spawn.asset = &D_80091930;
            } else {
                spawn.asset = &D_8009193C;
            }
        }
        spawn.byte54 = 9;
        spawn.byte5D = 0x10;
        spawn.scale0 = 0;
        spawn.scale1 = 0;
        spawn.byte5A = 8;
    } else {
        spawn.asset = &D_800917F8;
        spawn.byte54 = 0xA;
        spawn.size0 = 0xA0;
        spawn.size1 = 0xC0;
        spawn.byte5D = 0x20;
        spawn.scale0 = 0x1000;
        spawn.scale1 = 0x1000;
        spawn.byte5A = 0x18;
    }
    spawn.packed0 = (arg0 << 16) | arg1;
    total = arg0 + arg1 + arg2;
    spawn.packed1 = (arg2 << 16) | total;
    spawn.lifetime = 0x2710;
    spawn.total = total;
    spawn.zero3C = 0;
    spawn.zero48 = 0;
    spawn.zero4A = 0;
    spawn.byte55 = 1;
    spawn.byte56 = 0xFF;
    spawn.byte57 = 0xFF;
    spawn.byte58 = 0xFF;
    spawn.byte5B = 0x11;
    spawn.byte59 = 0;
    spawn.zero3A = 0;
    spawn.value0 = 146.0f;
    spawn.value1 = 100.0f;
    func_15169968(&spawn);
}
