#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B9F30.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518CCA8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1B9F30Input {
    f32 x, y, z;
    s16 integer_x, integer_y, integer_z;
    u8 fraction_x, fraction_z, fraction_y, pad15;
    s16 field16, field18, delta_high, delta_low;
    s16 field1E, field20, field22, field24, field26;
    u8 color0[3];
    u8 color1[3];
    u8 brightness, alpha;
    s8 callback;
    u8 callback_flags;
} Game1B9F30Input;

typedef struct Game1B9F30Packet {
    s32 resource;
    s32 packed_delta;
    s32 field8;
    s16 fieldC, fieldE;
    s16 x, y, z;
    s16 field16, field18, field1A;
    u8 fraction_x, fraction_z, fraction_y, kind;
    s16 field20, field22, field24, field26, field28;
    s8 callback;
    u8 callback_flags;
    u8 color0[3];
    u8 alpha;
    u8 color1[3];
    u8 pad33;
    s16 field34;
    u8 pad36[2];
} Game1B9F30Packet;

void func_15167D84(void *, s32, s32, s32, u8, s32);
extern u8 *D_8008CA4C[];

void func_1518CA80(Game1B9F30Input *arg0, u8 arg1) {
    Game1B9F30Packet packet;
    u8 brightness;

    brightness = arg0->brightness;
    packet.color0[0] = (arg0->color0[0] * brightness) >> 8;
    packet.color0[1] = (arg0->color0[1] * brightness) >> 8;
    packet.color0[2] = (arg0->color0[2] * brightness) >> 8;
    packet.color1[0] = (arg0->color1[0] * brightness) >> 8;
    packet.color1[1] = (arg0->color1[1] * brightness) >> 8;
    packet.color1[2] = (arg0->color1[2] * brightness) >> 8;
    packet.field28 = arg0->field26;
    packet.alpha = arg0->alpha;
    packet.callback = arg0->callback;
    packet.resource = (s32)D_8008CA4C[0];
    packet.fieldC = 0;
    packet.fieldE = 0x100;
    if (arg1 == 1) {
        packet.x = (s32)arg0->x;
        packet.y = (s32)arg0->y;
        packet.z = (s32)arg0->z;
        packet.fraction_x = (u16)(s32)(arg0->x * 256.0f);
        packet.fraction_y = (u16)(s32)(arg0->y * 256.0f);
        packet.fraction_z = (u16)(s32)(arg0->z * 256.0f);
    } else {
        packet.x = arg0->integer_x;
        packet.y = arg0->integer_y;
        packet.z = arg0->integer_z;
        packet.fraction_x = arg0->fraction_x;
        packet.fraction_y = arg0->fraction_y;
        packet.fraction_z = arg0->fraction_z;
    }
    packet.field16 = arg0->field1E;
    packet.field18 = arg0->field20;
    packet.field20 = arg0->field22;
    packet.field22 = arg0->field24;
    packet.kind = 9;
    packet.field34 = 1;
    packet.field24 = arg0->field16;
    packet.field26 = arg0->field18;
    packet.packed_delta = arg0->delta_high << 16;
    packet.packed_delta += arg0->delta_low;
    packet.callback_flags = arg0->callback_flags;
    packet.field1A = 0;
    packet.field8 = 0;
    func_15167D84(&packet, 0, 0, -1, 0xFF, 1);
}
typedef struct Game1B9F30State {
    u8 pad0[0x14];
    s32 packed_delta;
    u8 pad18[0x1C];
    s16 field_34;
    s16 field_36;
    s16 field_38;
    u8 pad3A;
    u8 callback_flags;
} Game1B9F30State;

extern void (*D_8008D5D0[])(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518CCA8 CURRENT (460) */
void func_1518CCA8(Game1B9F30State *arg0) {
    s32 packed_delta;
    s32 callback_index;

    packed_delta = arg0->packed_delta;
    arg0->field_34 += (u32)(packed_delta & 0xFFFF0000) >> 16;
    arg0->field_36 += packed_delta;
    if (arg0->field_38 == 0) {
        callback_index = arg0->callback_flags & 0xF;
        if (callback_index != 0) {
            D_8008D5D0[callback_index]();
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518CCA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9F30/func_1518CCA8.s")
