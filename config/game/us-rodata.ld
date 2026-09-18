/* Reviewed external game data; see docs/evidence/game_61950_jump_table.md.
 * INFO retains linked bytes for verification without appending them to the
 * code-only payload. The original game-data archive supplies these bytes.
 * Read before the generated code linker script so this input is consumed here.
 */
SECTIONS
{
    .game_rodata_61950 0x80097D1C (INFO) : SUBALIGN(4)
    {
        *game_61950.o(.rodata)
    }
    /* ROM-verified floating constants used by the recovered effect helpers. */
    .game_rodata_1dc720 0x800A9DD4 (INFO) : SUBALIGN(4)
    {
        *game_1DC720.o(.rodata)
    }
    .game_rodata_1e2490 0x800AA3E8 (INFO) : SUBALIGN(4)
    {
        *game_1E2490.o(.rodata)
    }
    .game_rodata_1e2180 0x800AA3D0 (INFO) : SUBALIGN(4)
    {
        *game_1E2180.o(.rodata)
    }
    .game_rodata_75c90 0x80099000 (INFO) : SUBALIGN(4)
    {
        *game_75C90.o(.rodata)
    }

    /* 51-entry format switch table; the final word is object alignment. */
    .game_rodata_70200 0x80098B98 (INFO) : SUBALIGN(4)
    {
        *game_70200.o(.rodata)
    }
}
ASSERT(SIZEOF(.game_rodata_61950) == 0x20,
       "game_61950 external rodata extent changed")
ASSERT(SIZEOF(.game_rodata_1dc720) == 0x10,
       "game_1DC720 external rodata extent changed")
ASSERT(SIZEOF(.game_rodata_1e2490) == 0x10,
       "game_1E2490 external rodata extent changed")
ASSERT(SIZEOF(.game_rodata_1e2180) == 0x10,
       "game_1E2180 external rodata extent changed")
ASSERT(SIZEOF(.game_rodata_75c90) == 0x20,
       "game_75C90 external rodata extent changed")
ASSERT(SIZEOF(.game_rodata_70200) == 0xD0,
       "game_70200 external rodata extent changed")
__game_rodata_70200_payload_size = 0xCC;
