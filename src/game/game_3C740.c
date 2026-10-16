#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3C740.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_scene_setup_emission_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500F40C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_1513C5B0(s32, s32, u8, u8, f32, f32, f32, f32, f32, u8, u8, s32, u8, s32);
s32 func_151EF610(void);

typedef struct {
    s32 flags;
    s16 duration;
    u8 type, mode;
    s32 field8, fieldC;
    u8 selector, alpha, red, green, blue, flag15, flag16, flag17;
    s32 field18, field1C;
    u8 field20;
    s16 field22, field24;
} Game3C740Packet;

void func_1500F290(f32 arg0, f32 arg1, f32 arg2) {
    Game3C740Packet packet;
    s32 rand;

    packet.type = 0x38;
    packet.field8 = 0;
    rand = func_151EF610();
    packet.fieldC = (rand % 4096) + 0x4000;
    packet.flags = 0x20014;
    packet.duration = 1;
    packet.selector = 0xFF;
    packet.alpha = 0xFF;
    packet.red = 0;
    packet.green = 0;
    packet.blue = 0;
    packet.flag15 = 0xFF;
    packet.field18 = 0x30001;
    func_1513C5B0((s32)&packet, 0, 0, 0, arg0, arg1, arg2, 110.0f, 110.0f, 0, 0, 0, 0xFF, 0);
}
typedef struct {
    u8 pad0[0x28];
    s16 field_28;
    s16 field_2A;
    s16 field_2C;
    s16 field_2E;
    s8 field_30;
} Game3C740Object;

s32 func_150ADA20(void);

void func_1500F378(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Game3C740Object *temp_v0;

    temp_v0 = func_151491F4((s16)((func_150ADA20() & 0x7F) + 0xA), 1, -1, 1, 0, 0xA, 0xFF, 0);
    if (temp_v0 != 0) {
        temp_v0->field_28 = (s16)arg0;
        temp_v0->field_2A = (s16)arg1;
        temp_v0->field_2C = (s16)arg2;
        temp_v0->field_2E = (s16)arg3;
        temp_v0->field_30 = 1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_3C740/func_1500F40C.s")
