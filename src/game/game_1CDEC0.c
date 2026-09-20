#include "types.h"

/*
 * Reviewed source unit: src/game/game_1CDEC0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A0AF8
 * - func_151A0C0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_1510F8CC(s32);
void *func_151491F4(s16, s8, s8, u8, u8, s32, u8, s32);
extern u8 D_800C35EA;

typedef struct {
    f32 field_0;
    f32 field_4;
    f32 field_8;
    s8 field_C;
    u8 pad_D[3];
    f32 field_10;
} Game1CDEC0Packet;

void func_151A0A10(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    void *temp_v0_2;
    Game1CDEC0Packet packet;
    s32 temp_v0;

    if (arg0 != 0) {
        packet.field_0 = *(f32 *)(arg0 + 0x14);
        packet.field_8 = *(f32 *)(arg0 + 0x1C);
        if (D_800C35EA != 1) {
            packet.field_4 = *(f32 *)(arg0 + 0x180);
            packet.field_10 = 0.0f;
            temp_v0 = func_1510F8CC(*(s32 *)(arg0 + 0x184));
            switch (temp_v0) {
                default:
                    packet.field_C = 0;
                    break;
                case 10:
                    packet.field_C = 0;
                    break;
                case 15:
                case 17:
                    packet.field_C = 1;
                    break;
            }
            temp_v0_2 = func_151491F4(arg1, -1, 1, 1, 0, 0x14, arg2, arg3);
            if (temp_v0_2 != 0) {
                func_10022EC0((u8 *)temp_v0_2 + 0x28, &packet, 0x14);
            }
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CDEC0/func_151A0AF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CDEC0/func_151A0C0C.s")
