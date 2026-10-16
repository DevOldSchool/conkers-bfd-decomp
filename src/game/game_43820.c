#include "types.h"

/*
 * Reviewed source unit: src/game/game_43820.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_single_function_units_up_to_256_bytes.md
 */

extern s8 D_8008FD8C;
extern s32 D_800CC2D0;

void func_15016370(void) {
    s32 i;

    for (i = 0; i < D_8008FD8C; i++) {
        *(s16 *)(*(u8 **)((u8 *)&D_800CC2D0 + i * 0x32C + 0x31C) + 0x114) = 0xB4;
        *(s16 *)(*(u8 **)((u8 *)&D_800CC2D0 + i * 0x32C + 0x31C) + 0x116) = 0x3C;
        *(s16 *)(*(u8 **)((u8 *)&D_800CC2D0 + i * 0x32C + 0x31C) + 0x118) = 0x3C;
    }
}
