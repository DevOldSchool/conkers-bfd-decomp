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
    /* Reviewed automation tables: docs/evidence/automation_jump_tables.md. */
    .game_rodata_433f0 0x800966C0 (INFO) : SUBALIGN(4) { *game_433F0.o(.rodata) }
    .game_rodata_58f80 0x80096DF8 (INFO) : SUBALIGN(4) { *game_58F80.o(.rodata) }
    .game_rodata_aeb40 0x8009CC40 (INFO) : SUBALIGN(4) { *game_AEB40.o(.rodata) }
    .game_rodata_b4080 0x8009DA94 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata) }
    .game_rodata_16ee20_0 0x800A5430 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_0) }
    .game_rodata_16ee20_40 0x800A565C (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_40) }
    .game_rodata_1c1150_0 0x800A8258 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_0) }
    .game_rodata_1c1150_14 0x800A826C (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_14) }
    .game_rodata_1c1150_28 0x800A82BC (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_28) }
    /* Reviewed manual switch tables: docs/evidence/manual_batch_jump_tables.md. */
    .game_rodata_49be0 0x800969A0 (INFO) : SUBALIGN(4) { *game_49BE0.o(.rodata) }
    .game_rodata_cd860 0x8009F550 (INFO) : SUBALIGN(4) { *game_CD860.o(.rodata) }
    .game_rodata_179f30 0x800A5E20 (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata) }
    /* Recovered blocked switches: docs/evidence/blocked_switch_jump_tables.md. */
    .game_rodata_5d2c0 0x80096F40 (INFO) : SUBALIGN(4) { *game_5D2C0.o(.rodata) }
    .game_rodata_1bf090 0x800A811C (INFO) : SUBALIGN(4) { *game_1BF090.o(.rodata) }
}
__game_rodata_16ee20_0_base = ADDR(.game_rodata_16ee20_0);
__game_rodata_16ee20_40_base = ADDR(.game_rodata_16ee20_40) - 0x40;
__game_rodata_1c1150_0_base = ADDR(.game_rodata_1c1150_0);
__game_rodata_1c1150_14_base = ADDR(.game_rodata_1c1150_14) - 0x14;
__game_rodata_1c1150_28_base = ADDR(.game_rodata_1c1150_28) - 0x28;
ASSERT(SIZEOF(.game_rodata_433f0) == 0xA0, "game_433F0 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_58f80) == 0x100, "game_58F80 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_aeb40) == 0x120, "game_AEB40 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_b4080) == 0x1E0, "game_B4080 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_0) == 0x40, "game_16EE20 first table extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_40) == 0x38, "game_16EE20 second table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_0) == 0x14, "game_1C1150 first table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_14) == 0x14, "game_1C1150 second table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_28) == 0x14, "game_1C1150 third table extent changed")
ASSERT(SIZEOF(.game_rodata_49be0) == 0x20, "game_49BE0 table extent changed")
ASSERT(SIZEOF(.game_rodata_cd860) == 0x20, "game_CD860 table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30) == 0x30, "game_179F30 table extent changed")
__game_rodata_49be0_payload_size = 0x1C;
__game_rodata_cd860_payload_size = 0x18;
__game_rodata_179f30_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_5d2c0) == 0xE0, "game_5D2C0 table extent changed")
ASSERT(SIZEOF(.game_rodata_1bf090) == 0x50, "game_1BF090 table extent changed")
__game_rodata_5d2c0_payload_size = 0xDC;
__game_rodata_1bf090_payload_size = 0x44;
__game_rodata_aeb40_payload_size = 0x114;
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
