#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BFC70.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_units_up_to_64_bytes.md
 */

typedef struct Game1BFC70State {
    u8 pad0[0x14];
    s32 unk14;
    u8 pad18[0x20];
    s16 unk38;
    s8 unk3A;
    s8 unk3B;
} Game1BFC70State;

void func_151927C0(s8 *arg0)
{
  s16 new_var;

  new_var = (s16) (((s32) ((*((s32 *) (((s8 *) arg0) + 0x14))) & 0xFF)) >> 1);
  *((s16 *) (((s8 *) arg0) + 0x38)) = 0x12C;
  *((s8 *) (((s8 *) arg0) + 0x3A)) = 0xA;
  *((s32 *) (((s8 *) arg0) + 0x14)) = (s32) ((new_var << 16) + new_var);
  *((s8 *) (((s8 *) arg0) + 0x3B)) = 0;
}
