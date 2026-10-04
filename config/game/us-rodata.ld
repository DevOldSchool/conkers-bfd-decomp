/* Reviewed external game data; see docs/evidence/game_61950_jump_table.md.
 * INFO retains linked bytes for verification without appending them to the
 * code-only payload. The original game-data archive supplies these bytes.
 * Read before the generated code linker script so this input is consumed here.
 */
SECTIONS
{
    /* Entrypoint dispatch: docs/evidence/entrypoint_jump_table.md. */
    .game_rodata_entrypoint 0x80095A30 (INFO) : SUBALIGN(4)
    {
        *entrypoint.o(.rodata)
    }
    /* Constructor literals: docs/evidence/game_981e0_constructor_literal_pool.md. */
    .game_rodata_981e0 0x80099DAC (INFO) : SUBALIGN(4)
    {
        *game_981E0.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/game_11d830_float_constant.md. */
    .game_rodata_11d830 0x800A1854 (INFO) : SUBALIGN(4)
    {
        *game_11D830.o(.rodata)
    }
    /* Reviewed tables: docs/evidence/game_1bc650_jump_tables.md. */
    .game_rodata_1bc650 0x800A7B7C (INFO) : SUBALIGN(4)
    {
        *game_1BC650.o(.rodata)
    }
    .game_rodata_61950 0x80097D1C (INFO) : SUBALIGN(4)
    {
        *game_61950.o(.rodata)
    }
    /* Glyph switch and constants: docs/evidence/game_6ea90_glyph_rodata.md. */
    .game_rodata_6ea90 0x80098AB0 (INFO) : SUBALIGN(4)
    {
        *game_6EA90.o(.rodata)
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
    .game_rodata_16ee20_0 0x800A5218 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_0) }
    .game_rodata_16ee20_b4 0x800A52CC (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_b4) }
    .game_rodata_16ee20_218 0x800A5430 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_218) }
    .game_rodata_16ee20_258 0x800A5648 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_258) }
    .game_rodata_16ee20_26c 0x800A565C (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_26c) }
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
    /* Six switch targets: docs/evidence/game_a9d90_jump_table.md. */
    .game_rodata_a9d90 0x8009B884 (INFO) : SUBALIGN(4) { *game_A9D90.o(.rodata) }
    /* Six switch targets: docs/evidence/game_11f780_jump_table.md. */
    .game_rodata_11f780 0x800A192C (INFO) : SUBALIGN(4) { *game_11F780.o(.rodata) }
    /* Two adjacent switches: docs/evidence/game_15d730_jump_tables.md. */
    .game_rodata_15d730 0x800A3800 (INFO) : SUBALIGN(4) { *game_15D730.o(.rodata) }
    /* Actor command dispatcher: docs/evidence/game_61490_jump_table.md. */
    .game_rodata_61490 0x80097C80 (INFO) : SUBALIGN(4) { *game_61490.o(.rodata) }
    /* Sound-event switch: docs/evidence/game_1483e0_jump_table.md. */
    .game_rodata_1483e0 0x800A3218 (INFO) : SUBALIGN(4) { *game_1483E0.o(.rodata) }
    /* Six ROM-proven targets: docs/evidence/game_c98f0_jump_table.md. */
    .game_rodata_c98f0 0x8009E458 (INFO) : SUBALIGN(4) { *game_C98F0.o(.rodata) }
}
__game_rodata_16ee20_0_base = ADDR(.game_rodata_16ee20_0);
__game_rodata_16ee20_b4_base = ADDR(.game_rodata_16ee20_b4) - 0xB4;
__game_rodata_16ee20_218_base = ADDR(.game_rodata_16ee20_218) - 0x218;
__game_rodata_16ee20_258_base = ADDR(.game_rodata_16ee20_258) - 0x258;
__game_rodata_16ee20_26c_base = ADDR(.game_rodata_16ee20_26c) - 0x26C;
__game_rodata_1c1150_0_base = ADDR(.game_rodata_1c1150_0);
__game_rodata_1c1150_14_base = ADDR(.game_rodata_1c1150_14) - 0x14;
__game_rodata_1c1150_28_base = ADDR(.game_rodata_1c1150_28) - 0x28;
ASSERT(SIZEOF(.game_rodata_433f0) == 0xA0, "game_433F0 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_58f80) == 0x100, "game_58F80 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_aeb40) == 0x120, "game_AEB40 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_b4080) == 0x1E0, "game_B4080 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_0) == 0xB4, "game_16EE20 table at 800A5218 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_b4) == 0x164, "game_16EE20 table at 800A52CC extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_218) == 0x40, "game_16EE20 table at 800A5430 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_258) == 0x14, "game_16EE20 table at 800A5648 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_26c) == 0x38, "game_16EE20 table at 800A565C extent changed")
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
ASSERT(SIZEOF(.game_rodata_6ea90) == 0x60,
       "game_6EA90 glyph rodata extent changed")
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
ASSERT(SIZEOF(.game_rodata_11f780) == 0x20, "game_11F780 table extent changed")
__game_rodata_11f780_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_15d730) == 0x50, "game_15D730 table extent changed")
__game_rodata_15d730_payload_size = 0x44;

ASSERT(SIZEOF(.game_rodata_a9d90) == 0x20, "game_A9D90 table extent changed")
__game_rodata_a9d90_payload_size = 0x18;

ASSERT(SIZEOF(.game_rodata_11d830) == 0x10,
       "game_11D830 constant pool extent changed")
__game_rodata_11d830_payload_size = 0x4;

ASSERT(SIZEOF(.game_rodata_1bc650) == 0x490,
       "game_1BC650 table extent changed")
__game_rodata_1bc650_payload_size = 0x488;

ASSERT(SIZEOF(.game_rodata_1483e0) == 0xE0, "game_1483E0 table extent changed")
__game_rodata_1483e0_payload_size = 0xD8;

ASSERT(SIZEOF(.game_rodata_61490) == 0xA0, "game_61490 table extent changed")
__game_rodata_61490_payload_size = 0x94;

ASSERT(SIZEOF(.game_rodata_981e0) == 0xF0,
       "game_981E0 constructor literal pool extent changed")
__game_rodata_981e0_payload_size = 0xEC;
ASSERT(__game_rodata_981e0_payload_size == 0xEC,
       "game_981E0 constructor literal payload extent changed")

ASSERT(SIZEOF(.game_rodata_entrypoint) == 0x20, "entrypoint table extent changed")
__game_rodata_entrypoint_payload_size = 0x14;

ASSERT(SIZEOF(.game_rodata_c98f0) == 0x20, "game_C98F0 table extent changed")
__game_rodata_c98f0_payload_size = 0x18;
