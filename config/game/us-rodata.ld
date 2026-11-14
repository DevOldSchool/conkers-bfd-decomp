/* Reviewed external game data; see docs/evidence/data-layout/game_61950_jump_table.md.
 * INFO retains linked bytes for verification without appending them to the
 * code-only payload. The original game-data archive supplies these bytes.
 * Read before the generated code linker script so this input is consumed here.
 */
SECTIONS
{
    /* ROM-backed scalar literals: docs/evidence/data-layout/game_second_batch_literals.md. */
    .game_rodata_camera_camera 0x800A352C (INFO) : SUBALIGN(4)
    {
        *camera_camera.o(.rodata)
    }
    .game_rodata_18a8f0 0x800A6520 (INFO) : SUBALIGN(4)
    {
        *game_18A8F0.o(.rodata)
    }
    /* Entrypoint dispatch: docs/evidence/data-layout/entrypoint_jump_table.md. */
    .game_rodata_entrypoint 0x80095A30 (INFO) : SUBALIGN(4)
    {
        *entrypoint.o(.rodata)
    }
    /* Dispatch table, leading and constructor literals:
       docs/evidence/data-layout/game_981e0_constructor_literal_pool.md. */
    .game_rodata_981e0_0 0x80099D54 (INFO) : SUBALIGN(4) { *game_981E0.o(.rodata.981e0_0) }
    .game_rodata_981e0_38 0x80099D8C (INFO) : SUBALIGN(4) { *game_981E0.o(.rodata.981e0_38) }
    .game_rodata_981e0_144 0x80099EAC (INFO) : SUBALIGN(4) { *game_981E0.o(.rodata.981e0_144) }
    /* ROM-verified constant: docs/evidence/data-layout/game_10bc70_float_constant.md. */
    .game_rodata_10bc70 0x800A0D5C (INFO) : SUBALIGN(4)
    {
        *game_10BC70.o(.rodata)
    }
    /* Point pan and particle speed scales: docs/evidence/data-layout/game_114b80_float_constant.md. */
    .game_rodata_114b80_0 0x800A1350 (INFO) : SUBALIGN(4) { *game_114B80.o(.rodata.114b80_0) }
    .game_rodata_114b80_4 0x800A1374 (INFO) : SUBALIGN(4) { *game_114B80.o(.rodata.114b80_4) }
    /* Effect spin literals: docs/evidence/data-layout/game_115f30_float_constants.md. */
    .game_rodata_115f30 0x800A1384 (INFO) : SUBALIGN(4)
    {
        *game_115F30.o(.rodata)
    }
    /* Burst and emitter constants: docs/evidence/data-layout/game_116d40_float_constant.md. */
    .game_rodata_116d40 0x800A13F0 (INFO) : SUBALIGN(4)
    {
        *game_116D40.o(.rodata)
    }
    /* Burst spread scale: docs/evidence/data-layout/game_1188e0_float_constant.md. */
    /* ROM-verified constants: docs/evidence/data-layout/game_10d7b0_float_constants.md. */
    .game_rodata_10d7b0 0x800A0FBC (INFO) : SUBALIGN(4)
    {
        *game_10D7B0.o(.rodata)
    }
    .game_rodata_1188e0 0x800A14FC (INFO) : SUBALIGN(4)
    {
        *game_1188E0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_133190_float_constants.md. */
    .game_rodata_133190 0x800A2420 (INFO) : SUBALIGN(4)
    {
        *game_133190.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_191c30_float_constants.md. */
    .game_rodata_191c30 0x800A6B20 (INFO) : SUBALIGN(4)
    {
        *game_191C30.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_197120_float_constant.md. */
    .game_rodata_197120 0x800A6CB0 (INFO) : SUBALIGN(4)
    {
        *game_197120.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1d4ac0_float_constants.md. */
    .game_rodata_1d4ac0 0x800A8DC8 (INFO) : SUBALIGN(4)
    {
        *game_1D4AC0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1e58b0_float_constants.md. */
    .game_rodata_1e58b0 0x800AA4CC (INFO) : SUBALIGN(4)
    {
        *game_1E58B0.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_1e37d0_float_constant.md. */
    .game_rodata_1e37d0 0x800AA470 (INFO) : SUBALIGN(4)
    {
        *game_1E37D0.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_1e6260_float_constant.md. */
    .game_rodata_1e6260 0x800AA564 (INFO) : SUBALIGN(4)
    {
        *game_1E6260.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1e9820_float_constants.md. */
    .game_rodata_1e9820 0x800AA834 (INFO) : SUBALIGN(4)
    {
        *game_1E9820.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_11d830_float_constant.md
       and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_11d830_0 0x800A1854 (INFO) : SUBALIGN(4) { *game_11D830.o(.rodata.11d830_0) }
    .game_rodata_11d830_4 0x800A1878 (INFO) : SUBALIGN(4) { *game_11D830.o(.rodata.11d830_4) }
    /* ROM-verified constants: docs/evidence/data-layout/game_122b60_float_constants.md. */
    .game_rodata_122b60 0x800A1B60 (INFO) : SUBALIGN(4)
    {
        *game_122B60.o(.rodata)
    }
    /* func_151BB61C templates and literal: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_1e73b0_0 0x800AA718 (INFO) : SUBALIGN(4) { *game_1E73B0.o(.rodata.1e73b0_0) }
    .game_rodata_1e73b0_48 0x800AA7F4 (INFO) : SUBALIGN(4) { *game_1E73B0.o(.rodata.1e73b0_48) }
    /* func_151DC97C colour tables and literals: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_209b50_0 0x800AB500 (INFO) : SUBALIGN(4) { *game_209B50.o(.rodata.209b50_0) }
    .game_rodata_209b50_18 0x800AB538 (INFO) : SUBALIGN(4) { *game_209B50.o(.rodata.209b50_18) }
    /* ROM-verified constants: docs/evidence/data-layout/game_eee70_float_constants.md. */
    .game_rodata_eee70 0x800A0210 (INFO) : SUBALIGN(4)
    {
        *game_EEE70.o(.rodata)
    }
    /* Burst velocity literals: docs/evidence/data-layout/game_burst_velocity_literals.md. */
    /* Split pools: docs/evidence/data-layout/game_burst_velocity_literals.md. */
    .game_rodata_f3270_0 0x800A041C (INFO) : SUBALIGN(4) { *game_F3270.o(.rodata.f3270_0) }
    .game_rodata_f3270_4 0x800A043C (INFO) : SUBALIGN(4) { *game_F3270.o(.rodata.f3270_4) }
    /* Split pools: docs/evidence/data-layout/game_burst_velocity_literals.md. */
    .game_rodata_f3ba0_0 0x800A045C (INFO) : SUBALIGN(4) { *game_F3BA0.o(.rodata.f3ba0_0) }
    .game_rodata_f3ba0_4 0x800A047C (INFO) : SUBALIGN(4) { *game_F3BA0.o(.rodata.f3ba0_4) }
    .game_rodata_1179b0 0x800A143C (INFO) : SUBALIGN(4)
    {
        *game_1179B0.o(.rodata)
    }
    /* Split pools: docs/evidence/data-layout/game_burst_velocity_literals.md. */
    .game_rodata_1d6e80_0 0x800A8FE0 (INFO) : SUBALIGN(4) { *game_1D6E80.o(.rodata.1d6e80_0) }
    .game_rodata_1d6e80_c 0x800A8FF4 (INFO) : SUBALIGN(4) { *game_1D6E80.o(.rodata.1d6e80_c) }
    /* Particle speed literals: docs/evidence/data-layout/game_1d8de0_float_constants.md. */
    .game_rodata_1d8de0 0x800A9018 (INFO) : SUBALIGN(4) { *game_1D8DE0.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_111670_float_constants.md. */
    .game_rodata_111670_0 0x800A1060 (INFO) : SUBALIGN(4) { *game_111670.o(.rodata.111670_0) }
    .game_rodata_111670_4 0x800A112C (INFO) : SUBALIGN(4) { *game_111670.o(.rodata.111670_4) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1fa770_float_constants.md. */
    .game_rodata_1fa770_0 0x800AAFC0 (INFO) : SUBALIGN(4) { *game_1FA770.o(.rodata.1fa770_0) }
    .game_rodata_1fa770_8 0x800AAFE4 (INFO) : SUBALIGN(4) { *game_1FA770.o(.rodata.1fa770_8) }
    /* Rain emitter literals: docs/evidence/data-layout/game_1fbb80_float_constants.md. */
    .game_rodata_1fbb80 0x800AAFF0 (INFO) : SUBALIGN(4) { *game_1FBB80.o(.rodata) }
    /* Gust literals: docs/evidence/data-layout/game_1fc5d0_float_constants.md. */
    .game_rodata_1fc5d0 0x800AB014 (INFO) : SUBALIGN(4) { *game_1FC5D0.o(.rodata) }
    /* Smoke emitter literals: docs/evidence/data-layout/game_188440_float_constants.md. */
    .game_rodata_188440 0x800A6438 (INFO) : SUBALIGN(4) { *game_188440.o(.rodata) }
    /* Particle literals: docs/evidence/data-layout/game_1b8b60_float_constants.md. */
    .game_rodata_1b8b60 0x800A7400 (INFO) : SUBALIGN(4) { *game_1B8B60.o(.rodata) }
    /* Debris burst literals: docs/evidence/data-layout/game_e4ff0_float_constants.md. */
    .game_rodata_e4ff0 0x8009FD68 (INFO) : SUBALIGN(4) { *game_E4FF0.o(.rodata) }
    /* ROM-verified constant: docs/evidence/data-layout/game_20a290_float_constant.md. */
    .game_rodata_20a290 0x800AB558 (INFO) : SUBALIGN(4)
    {
        *game_20A290.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    /* func_15146970 ids and switch table: docs/evidence/data-layout/game_173d40_switch_table.md. */
    .game_rodata_173d40_0 0x800A56D0 (INFO) : SUBALIGN(4) { *game_173D40.o(.rodata.173d40_0) }
    .game_rodata_173d40_14 0x800A56E4 (INFO) : SUBALIGN(4) { *game_173D40.o(.rodata.173d40_14) }
    .game_rodata_173d40_38 0x800A5708 (INFO) : SUBALIGN(4) { *game_173D40.o(.rodata.173d40_38) }
    .game_rodata_173d40_50 0x800A5728 (INFO) : SUBALIGN(4) { *game_173D40.o(.rodata.173d40_50) }
    .game_rodata_173d40_58 0x800A573C (INFO) : SUBALIGN(4) { *game_173D40.o(.rodata.173d40_58) }
    /* ROM-verified constants: docs/evidence/data-layout/game_64120_float_constant.md
     * and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_64120_0 0x80098648 (INFO) : SUBALIGN(4) { *game_64120.o(.rodata.64120_0) }
    .game_rodata_64120_4 0x800986EC (INFO) : SUBALIGN(4) { *game_64120.o(.rodata.64120_4) }
    /* ROM-verified constants: docs/evidence/data-layout/game_f9430_float_constants.md. */
    .game_rodata_f9430 0x800A06D0 (INFO) : SUBALIGN(4)
    {
        *game_F9430.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/holtenrope_float_constants.md. */
    .game_rodata_holtenrope_0 0x800AA3A0 (INFO) : SUBALIGN(4) { *holtenrope.o(.rodata.holtenrope_0) }
    .game_rodata_holtenrope_c 0x800AA3B8 (INFO) : SUBALIGN(4) { *holtenrope.o(.rodata.holtenrope_c) }
    .game_rodata_holtenrope_18 0x800AA3C4 (INFO) : SUBALIGN(4) { *holtenrope.o(.rodata.holtenrope_18) }
    /* ROM-verified constants: docs/evidence/data-layout/characterflamethrower_float_constants.md. */
    .game_rodata_characterflamethrower 0x800A8AFC (INFO) : SUBALIGN(4)
    {
        *characterflamethrower.o(.rodata)
    }
    /* func_151C9BA0 switch and interpolation constant:
     * docs/evidence/data-layout/effects_sight_float_constant.md. */
    .game_rodata_effects_sight_0 0x800AAC58 (INFO) : SUBALIGN(4) { *effects_sight.o(.rodata.effects_sight_0) }
    .game_rodata_effects_sight_18 0x800AADBC (INFO) : SUBALIGN(4) { *effects_sight.o(.rodata.effects_sight_18) }
    .game_rodata_effects_sight_e4 0x800AAEBC (INFO) : SUBALIGN(4) { *effects_sight.o(.rodata.effects_sight_e4) }
    /* ROM-verified constants: docs/evidence/data-layout/game_e7970_float_constants.md. */
    .game_rodata_e7970 0x8009FE30 (INFO) : SUBALIGN(4)
    {
        *game_E7970.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_1cbe20_float_constant.md. */
    .game_rodata_1cbe20 0x800A8CD4 (INFO) : SUBALIGN(4)
    {
        *game_1CBE20.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_f21d0_float_constants.md. */
    .game_rodata_f21d0 0x800A03F0 (INFO) : SUBALIGN(4)
    {
        *game_F21D0.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_12c1e0_float_constant.md. */
    .game_rodata_12c1e0 0x800A2120 (INFO) : SUBALIGN(4)
    {
        *game_12C1E0.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_1dd500_float_constant.md. */
    .game_rodata_1dd500 0x800AA2FC (INFO) : SUBALIGN(4)
    {
        *game_1DD500.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_71820_float_constants.md. */
    .game_rodata_71820 0x80098D60 (INFO) : SUBALIGN(4)
    {
        *game_71820.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_2062d0_float_constant.md. */
    .game_rodata_2062d0_0 0x800AB470 (INFO) : SUBALIGN(4) { *game_2062D0.o(.rodata.2062d0_0) }
    .game_rodata_2062d0_10 0x800AB480 (INFO) : SUBALIGN(4) { *game_2062D0.o(.rodata.2062d0_10) }
    .game_rodata_2062d0_28 0x800AB49C (INFO) : SUBALIGN(4) { *game_2062D0.o(.rodata.2062d0_28) }
    /* ROM-verified constants: docs/evidence/data-layout/game_360a0_float_constants.md. */
    .game_rodata_360a0 0x80095B40 (INFO) : SUBALIGN(4)
    {
        *game_360A0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_113d60_float_constants.md. */
    .game_rodata_113d60 0x800A1304 (INFO) : SUBALIGN(4)
    {
        *game_113D60.o(.rodata)
    }
    /* ROM-verified prompt string and constant: docs/evidence/data-layout/game_fd1d0_prompt_constants.md. */
    .game_rodata_fd1d0 0x800A0880 (INFO) : SUBALIGN(4)
    {
        *game_FD1D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1a20a0_float_constants.md. */
    .game_rodata_1a20a0_0 0x800A7174 (INFO) : SUBALIGN(4) { *game_1A20A0.o(.rodata.1a20a0_0) }
    .game_rodata_1a20a0_4 0x800A71AC (INFO) : SUBALIGN(4) { *game_1A20A0.o(.rodata.1a20a0_4) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1199d0_float_constants.md. */
    .game_rodata_1199d0 0x800A1578 (INFO) : SUBALIGN(4)
    {
        *game_1199D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_156160_float_constants.md. */
    .game_rodata_156160 0x800A3614 (INFO) : SUBALIGN(4)
    {
        *game_156160.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_1ed0f0_float_constant.md. */
    .game_rodata_1ed0f0 0x800AA9C4 (INFO) : SUBALIGN(4)
    {
        *game_1ED0F0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_135d00_float_constants.md. */
    .game_rodata_135d00 0x800A2498 (INFO) : SUBALIGN(4)
    {
        *game_135D00.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1368c0_float_constants.md. */
    .game_rodata_1368c0 0x800A268C (INFO) : SUBALIGN(4)
    {
        *game_1368C0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_eeb70_float_constants.md. */
    .game_rodata_eeb70 0x800A01F0 (INFO) : SUBALIGN(4)
    {
        *game_EEB70.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_476d0_float_constants.md. */
    .game_rodata_476d0 0x800968F4 (INFO) : SUBALIGN(4)
    {
        *game_476D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_ddf10_float_constants.md. */
    .game_rodata_ddf10 0x8009F874 (INFO) : SUBALIGN(4)
    {
        *game_DDF10.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_e35c0_float_constants.md. */
    .game_rodata_e35c0 0x8009FCBC (INFO) : SUBALIGN(4)
    {
        *game_E35C0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_fc5f0_float_constants.md. */
    .game_rodata_fc5f0 0x800A0840 (INFO) : SUBALIGN(4)
    {
        *game_FC5F0.o(.rodata)
    }
    /* ROM-verified table and constant: docs/evidence/data-layout/game_1a7260_literal_pool.md. */
    .game_rodata_1a7260 0x800A7210 (INFO) : SUBALIGN(4)
    {
        *game_1A7260.o(.rodata)
    }
    /* ROM-verified table and constants: docs/evidence/data-layout/game_ffba0_literal_pool.md. */
    .game_rodata_ffba0 0x800A0990 (INFO) : SUBALIGN(4)
    {
        *game_FFBA0.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_1cc440_float_constant.md. */
    .game_rodata_1cc440 0x800A8CF0 (INFO) : SUBALIGN(4)
    {
        *game_1CC440.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_177b50_float_constants.md
       and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_177b50_0 0x800A57B0 (INFO) : SUBALIGN(4) { *game_177B50.o(.rodata.177b50_0) }
    .game_rodata_177b50_1c 0x800A5808 (INFO) : SUBALIGN(4) { *game_177B50.o(.rodata.177b50_1c) }
    /* ROM-verified constants: docs/evidence/data-layout/game_12b7d0_float_constants.md. */
    .game_rodata_12b7d0 0x800A1FF0 (INFO) : SUBALIGN(4)
    {
        *game_12B7D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_c2350_float_constants.md. */
    .game_rodata_c2350 0x8009DEC0 (INFO) : SUBALIGN(4)
    {
        *game_C2350.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_dc6b0_float_constants.md. */
    .game_rodata_dc6b0_0 0x8009F7B8 (INFO) : SUBALIGN(4) { *game_DC6B0.o(.rodata.dc6b0_0) }
    .game_rodata_dc6b0_18 0x8009F7D8 (INFO) : SUBALIGN(4) { *game_DC6B0.o(.rodata.dc6b0_18) }
    /* ROM-verified constants: docs/evidence/data-layout/game_97aa0_float_constants.md. */
    .game_rodata_97aa0 0x80099A10 (INFO) : SUBALIGN(4)
    {
        *game_97AA0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_de5a0_float_constants.md. */
    .game_rodata_de5a0 0x8009F8A0 (INFO) : SUBALIGN(4)
    {
        *game_DE5A0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_a28b0_float_constants.md. */
    .game_rodata_a28b0 0x8009A144 (INFO) : SUBALIGN(4)
    {
        *game_A28B0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_40490_float_constants.md. */
    .game_rodata_40490 0x80096688 (INFO) : SUBALIGN(4)
    {
        *game_40490.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_1f2730_0 0x800AAACC (INFO) : SUBALIGN(4) { *game_1F2730.o(.rodata.1f2730_0) }
    .game_rodata_1f2730_c 0x800AAADC (INFO) : SUBALIGN(4) { *game_1F2730.o(.rodata.1f2730_c) }
    /* ROM-verified constants: docs/evidence/data-layout/game_49d30_float_constants.md
       and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_49d30_0 0x800969C0 (INFO) : SUBALIGN(4) { *game_49D30.o(.rodata.49d30_0) }
    .game_rodata_49d30_4 0x800969D0 (INFO) : SUBALIGN(4) { *game_49D30.o(.rodata.49d30_4) }
    /* Camera literals with an aligned double: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_197f20_0 0x800A6DBC (INFO) : SUBALIGN(4) { *game_197F20.o(.rodata.197f20_0) }
    .game_rodata_197f20_8 0x800A6DC8 (INFO) : SUBALIGN(4) { *game_197F20.o(.rodata.197f20_8) }
    /* ROM-verified constants: docs/evidence/data-layout/game_f44d0_float_constants.md. */
    .game_rodata_f44d0 0x800A0494 (INFO) : SUBALIGN(4)
    {
        *game_F44D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_127060_float_constants.md. */
    .game_rodata_127060 0x800A1DC0 (INFO) : SUBALIGN(4)
    {
        *game_127060.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_6b320_float_constants.md. */
    .game_rodata_6b320_0 0x80098918 (INFO) : SUBALIGN(4) { *game_6B320.o(.rodata.6b320_0) }
    .game_rodata_6b320_8 0x80098928 (INFO) : SUBALIGN(4) { *game_6B320.o(.rodata.6b320_8) }
    /* ROM-verified constants: docs/evidence/data-layout/game_124920_float_constants.md. */
    .game_rodata_124920 0x800A1BDC (INFO) : SUBALIGN(4)
    {
        *game_124920.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1ef500_float_constants.md. */
    .game_rodata_1ef500 0x800AAA7C (INFO) : SUBALIGN(4)
    {
        *game_1EF500.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_e8c10_float_constants.md. */
    .game_rodata_e8c10 0x8009FEBC (INFO) : SUBALIGN(4)
    {
        *game_E8C10.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_19e040_float_constants.md. */
    .game_rodata_19e040 0x800A6F80 (INFO) : SUBALIGN(4)
    {
        *game_19E040.o(.rodata)
    }
    /* Camera clamp literals: docs/evidence/data-layout/game_1ac2f0_float_constants.md. */
    .game_rodata_1ac2f0 0x800A7280 (INFO) : SUBALIGN(4)
    {
        *game_1AC2F0.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_1b5370_float_constant.md. */
    .game_rodata_1b5370 0x800A7398 (INFO) : SUBALIGN(4)
    {
        *game_1B5370.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1b81d0_float_constants.md. */
    .game_rodata_1b81d0 0x800A73E0 (INFO) : SUBALIGN(4)
    {
        *game_1B81D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_fa360_float_constants.md. */
    .game_rodata_fa360 0x800A074C (INFO) : SUBALIGN(4)
    {
        *game_FA360.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_123d40_float_constants.md. */
    .game_rodata_123d40 0x800A1B74 (INFO) : SUBALIGN(4)
    {
        *game_123D40.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1dbd40_float_constants.md. */
    .game_rodata_1dbd40 0x800A9D8C (INFO) : SUBALIGN(4)
    {
        *game_1DBD40.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_200930_float_constants.md. */
    .game_rodata_200930_0 0x800AB1D4 (INFO) : SUBALIGN(4) { *game_200930.o(.rodata.200930_0) }
    .game_rodata_200930_28 0x800AB21C (INFO) : SUBALIGN(4) { *game_200930.o(.rodata.200930_28) }
    /* ROM-verified constants: docs/evidence/data-layout/game_12ccf0_float_constants.md. */
    .game_rodata_12ccf0 0x800A2170 (INFO) : SUBALIGN(4)
    {
        *game_12CCF0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_11d030_float_constants.md. */
    .game_rodata_11d030 0x800A1824 (INFO) : SUBALIGN(4)
    {
        *game_11D030.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_131f30_float_constants.md. */
    .game_rodata_131f30_0 0x800A23B4 (INFO) : SUBALIGN(4) { *game_131F30.o(.rodata.131f30_0) }
    .game_rodata_131f30_c 0x800A23EC (INFO) : SUBALIGN(4) { *game_131F30.o(.rodata.131f30_c) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1865d0_float_constants.md. */
    .game_rodata_1865d0_0 0x800A63C4 (INFO) : SUBALIGN(4) { *game_1865D0.o(.rodata.1865d0_0) }
    .game_rodata_1865d0_20 0x800A6414 (INFO) : SUBALIGN(4) { *game_1865D0.o(.rodata.1865d0_20) }
    /* ROM-verified constants: docs/evidence/data-layout/game_17caf0_float_constants.md. */
    .game_rodata_17caf0 0x800A5FFC (INFO) : SUBALIGN(4)
    {
        *game_17CAF0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_83300_float_constants.md
     * and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_83300_0 0x800994DC (INFO) : SUBALIGN(4) { *game_83300.o(.rodata.83300_0) }
    .game_rodata_83300_c 0x8009962C (INFO) : SUBALIGN(4) { *game_83300.o(.rodata.83300_c) }
    .game_rodata_83300_14 0x80099694 (INFO) : SUBALIGN(4) { *game_83300.o(.rodata.83300_14) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1ce2f0_float_constants.md. */
    .game_rodata_1ce2f0 0x800A8D20 (INFO) : SUBALIGN(4)
    {
        *game_1CE2F0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1d3ab0_float_constants.md. */
    .game_rodata_1d3ab0 0x800A8DA0 (INFO) : SUBALIGN(4)
    {
        *game_1D3AB0.o(.rodata)
    }
    /* Reviewed tables: docs/evidence/data-layout/game_1bc650_jump_tables.md. */
    .game_rodata_1bc650 0x800A7B7C (INFO) : SUBALIGN(4)
    {
        *game_1BC650.o(.rodata)
    }
    .game_rodata_61950 0x80097D1C (INFO) : SUBALIGN(4)
    {
        *game_61950.o(.rodata)
    }
    /* Glyph switch and constants: docs/evidence/data-layout/game_6ea90_glyph_rodata.md. */
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
    /* Reviewed automation tables: docs/evidence/data-layout/automation_jump_tables.md. */
    .game_rodata_433f0 0x800966C0 (INFO) : SUBALIGN(4) { *game_433F0.o(.rodata) }
    .game_rodata_58f80_0 0x80096DF8 (INFO) : SUBALIGN(4) { *game_58F80.o(.rodata.58f80_0) }
    .game_rodata_58f80_100 0x80096F04 (INFO) : SUBALIGN(4) { *game_58F80.o(.rodata.58f80_100) }
    .game_rodata_aeb40 0x8009CC40 (INFO) : SUBALIGN(4) { *game_AEB40.o(.rodata) }
    .game_rodata_b4080_0 0x8009DA18 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_0) }
    .game_rodata_b4080_8 0x8009DA24 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_8) }
    .game_rodata_b4080_28 0x8009DA60 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_28) }
    .game_rodata_b4080_30 0x8009DA94 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_30) }
    .game_rodata_b4080_12c 0x8009DB90 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_12c) }
    .game_rodata_16ee20_0 0x800A5218 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_0) }
    .game_rodata_16ee20_b4 0x800A52CC (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_b4) }
    .game_rodata_16ee20_218 0x800A5430 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_218) }
    .game_rodata_16ee20_258 0x800A5648 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_258) }
    .game_rodata_16ee20_26c 0x800A565C (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_26c) }
    /* func_1514470C literal: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_16ee20_2a4 0x800A56A0 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_2a4) }
    .game_rodata_1c1150_0 0x800A8258 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_0) }
    .game_rodata_1c1150_14 0x800A826C (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_14) }
    /* func_15194408 table and literals: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_1c1150_28 0x800A8280 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_28) }
    .game_rodata_1c1150_3c 0x800A8294 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_3c) }
    .game_rodata_1c1150_48 0x800A82BC (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_48) }
    /* func_15194FF4 switch tables: docs/evidence/data-layout/game_1c1150_jump_tables.md. */
    .game_rodata_1c1150_5c 0x800A82D0 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_5c) }
    .game_rodata_1c1150_70 0x800A82F0 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_70) }
    .game_rodata_1c1150_1e4 0x800A8464 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_1e4) }
    .game_rodata_1c1150_240 0x800A84C0 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_240) }
    .game_rodata_1c1150_428 0x800A86A8 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_428) }
    /* Reviewed manual switch tables: docs/evidence/data-layout/manual_batch_jump_tables.md. */
    .game_rodata_49be0 0x800969A0 (INFO) : SUBALIGN(4) { *game_49BE0.o(.rodata) }
    .game_rodata_cd860 0x8009F550 (INFO) : SUBALIGN(4) { *game_CD860.o(.rodata) }
    /* game_179F30 switch tables, setup literals and switch table:
     * docs/evidence/data-layout/game_179f30_jump_tables.md and
     * docs/evidence/data-layout/game_179f30_float_constants.md. */
    .game_rodata_179f30_0 0x800A59AC (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_0) }
    .game_rodata_179f30_2ec 0x800A5C98 (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_2ec) }
    .game_rodata_179f30_3c4 0x800A5D70 (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_3c4) }
    .game_rodata_179f30_410 0x800A5DBC (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_410) }
    .game_rodata_179f30_438 0x800A5DF4 (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_438) }
    .game_rodata_179f30_448 0x800A5E20 (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_448) }
    /* Recovered blocked switches: docs/evidence/data-layout/blocked_switch_jump_tables.md. */
    .game_rodata_5d2c0 0x80096F40 (INFO) : SUBALIGN(4) { *game_5D2C0.o(.rodata) }
    /* Literal pool before the table: docs/evidence/data-layout/game_1bf090_literal_pool.md. */
    .game_rodata_1bf090 0x800A80FC (INFO) : SUBALIGN(4) { *game_1BF090.o(.rodata) }
    /* Five switch targets after the 1BF090 table: docs/evidence/data-layout/game_1bfcb0_jump_table.md. */
    .game_rodata_1bfcb0 0x800A8160 (INFO) : SUBALIGN(4) { *game_1BFCB0.o(.rodata) }
    /* Emitter literals: docs/evidence/data-layout/game_1bfdd0_float_constants.md. */
    .game_rodata_1bfdd0 0x800A8180 (INFO) : SUBALIGN(4) { *game_1BFDD0.o(.rodata) }
    /* Three adjacent switches: docs/evidence/data-layout/game_a9d90_jump_table.md. */
    .game_rodata_a9d90 0x8009B6DC (INFO) : SUBALIGN(4) { *game_A9D90.o(.rodata) }
    /* Six switch targets: docs/evidence/data-layout/game_11f780_jump_table.md. */
    .game_rodata_11f780 0x800A192C (INFO) : SUBALIGN(4) { *game_11F780.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_11ff10_float_constants.md. */
    .game_rodata_11ff10 0x800A1968 (INFO) : SUBALIGN(4) { *game_11FF10.o(.rodata) }
    /* Nested light switches: docs/evidence/data-layout/effects_light_jump_tables.md. */
    .game_rodata_light 0x800A6A18 (INFO) : SUBALIGN(4) { *light.o(.rodata) }
    /* Nine switch targets: docs/evidence/data-layout/game_1b8f40_jump_table.md. */
    .game_rodata_1b8f40 0x800A7410 (INFO) : SUBALIGN(4) { *game_1B8F40.o(.rodata) }
    /* Forty and forty-two switch targets: docs/evidence/data-layout/game_ca630_jump_table.md. */
    .game_rodata_ca630 0x8009F1AC (INFO) : SUBALIGN(4) { *game_CA630.o(.rodata) }
    /* Ten switch targets: docs/evidence/data-layout/game_e4070_jump_table.md. */
    .game_rodata_e4070 0x8009FD00 (INFO) : SUBALIGN(4) { *game_E4070.o(.rodata) }
    /* Forty-one switch targets: docs/evidence/data-layout/game_12f400_jump_table.md. */
    .game_rodata_12f400 0x800A2298 (INFO) : SUBALIGN(4) { *game_12F400.o(.rodata) }
    /* Thirty switch targets: docs/evidence/data-layout/game_15bd90_jump_table.md. */
    .game_rodata_15bd90 0x800A376C (INFO) : SUBALIGN(4) { *game_15BD90.o(.rodata) }
    /* Two adjacent switches: docs/evidence/data-layout/game_15d730_jump_tables.md. */
    .game_rodata_15d730 0x800A3800 (INFO) : SUBALIGN(4) { *game_15D730.o(.rodata) }
    /* Actor command dispatcher: docs/evidence/data-layout/game_61490_jump_table.md. */
    .game_rodata_61490 0x80097C80 (INFO) : SUBALIGN(4) { *game_61490.o(.rodata) }
    /* Seven selector targets: docs/evidence/data-layout/game_b21b0_jump_table.md. */
    .game_rodata_b21b0 0x8009D9A0 (INFO) : SUBALIGN(4) { *game_B21B0.o(.rodata) }
    /* Particle scale literals: docs/evidence/data-layout/game_10c170_float_constants.md. */
    .game_rodata_10c170 0x800A0F28 (INFO) : SUBALIGN(4) { *game_10C170.o(.rodata) }
    /* Range limits: docs/evidence/data-layout/game_b3020_float_constants.md. */
    .game_rodata_b3020 0x8009D9C0 (INFO) : SUBALIGN(4) { *game_B3020.o(.rodata) }
    /* Seven mode targets: docs/evidence/data-layout/game_cbbe0_jump_table.md. */
    .game_rodata_cbbe0 0x8009F3D0 (INFO) : SUBALIGN(4) { *game_CBBE0.o(.rodata) }
    /* Seventeen query targets: docs/evidence/data-layout/game_cbdb0_jump_table.md. */
    .game_rodata_cbdb0 0x8009F43C (INFO) : SUBALIGN(4) { *game_CBDB0.o(.rodata) }
    /* Pending actor actions: docs/evidence/data-layout/game_90840_jump_table.md. */
    .game_rodata_90840_0 0x800996D8 (INFO) : SUBALIGN(4) { *game_90840.o(.rodata.90840_0) }
    /* ROM-verified constants: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_90840_b8 0x800997E8 (INFO) : SUBALIGN(4) { *game_90840.o(.rodata.90840_b8) }
    /* Sound-event switch: docs/evidence/data-layout/game_1483e0_jump_table.md. */
    .game_rodata_1483e0 0x800A3218 (INFO) : SUBALIGN(4) { *game_1483E0.o(.rodata) }
    /* Actor callback dispatcher: docs/evidence/data-layout/game_169510_jump_table.md. */
    .game_rodata_169510 0x800A5188 (INFO) : SUBALIGN(4) { *game_169510.o(.rodata) }
    /* Slot-type switch and scale constants: docs/evidence/data-layout/game_1b0740_jump_table_constants.md. */
    .game_rodata_1b0740 0x800A72F0 (INFO) : SUBALIGN(4) { *game_1B0740.o(.rodata) }
    /* Character blood-profile switch: docs/evidence/data-layout/game_blood_jump_tables.md;
     * spray literals: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_blood_0 0x800A4350 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_0) }
    .game_rodata_blood_204 0x800A4554 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_204) }
    .game_rodata_blood_260 0x800A45B8 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_260) }
    .game_rodata_blood_2b4 0x800A4650 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_2b4) }
    .game_rodata_blood_480 0x800A4874 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_480) }
    .game_rodata_blood_4d0 0x800A48C4 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_4d0) }
    .game_rodata_blood_504 0x800A4900 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_504) }
    .game_rodata_blood_53c 0x800A4950 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_53c) }
    /* Six ROM-proven targets: docs/evidence/data-layout/game_c98f0_jump_table.md. */
    .game_rodata_c98f0 0x8009E458 (INFO) : SUBALIGN(4) { *game_C98F0.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_39750_float_constants.md. */
    .game_rodata_39750_0 0x80096104 (INFO) : SUBALIGN(4) { *game_39750.o(.rodata.39750_0) }
    .game_rodata_39750_1c 0x80096158 (INFO) : SUBALIGN(4) { *game_39750.o(.rodata.39750_1c) }
    /* Sixteen ROM-proven entries: docs/evidence/data-layout/game_3ba70_jump_table.md. */
    .game_rodata_3ba70 0x800961D0 (INFO) : SUBALIGN(4) { *game_3BA70.o(.rodata) }
    /* Ten ROM-proven entries: docs/evidence/data-layout/game_20bda0_jump_table.md. */
    .game_rodata_20bda0 0x800AB9BC (INFO) : SUBALIGN(4) { *game_20BDA0.o(.rodata) }
    /* Thirty-five ROM-proven entries: docs/evidence/data-layout/game_138b40_jump_table.md. */
    .game_rodata_138b40 0x800A2C2C (INFO) : SUBALIGN(4) { *game_138B40.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_10e510_float_constants.md. */
    .game_rodata_10e510 0x800A1014 (INFO) : SUBALIGN(4) { *game_10E510.o(.rodata) }
    /* Switch table and constants: docs/evidence/data-layout/game_109220_rodata.md. */
    .game_rodata_109220 0x800A0C40 (INFO) : SUBALIGN(4) { *game_109220.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_ec420_float_constants.md. */
    .game_rodata_ec420 0x800A0110 (INFO) : SUBALIGN(4) { *game_EC420.o(.rodata) }
}
__game_rodata_b4080_0_base = ADDR(.game_rodata_b4080_0);
__game_rodata_b4080_8_base = ADDR(.game_rodata_b4080_8) - 0x8;
__game_rodata_b4080_28_base = ADDR(.game_rodata_b4080_28) - 0x28;
__game_rodata_b4080_30_base = ADDR(.game_rodata_b4080_30) - 0x30;
__game_rodata_b4080_12c_base = ADDR(.game_rodata_b4080_12c) - 0x12C;
__game_rodata_58f80_0_base = ADDR(.game_rodata_58f80_0);
__game_rodata_58f80_100_base = ADDR(.game_rodata_58f80_100) - 0x100;
__game_rodata_16ee20_0_base = ADDR(.game_rodata_16ee20_0);
__game_rodata_16ee20_b4_base = ADDR(.game_rodata_16ee20_b4) - 0xB4;
__game_rodata_16ee20_218_base = ADDR(.game_rodata_16ee20_218) - 0x218;
__game_rodata_16ee20_258_base = ADDR(.game_rodata_16ee20_258) - 0x258;
__game_rodata_16ee20_26c_base = ADDR(.game_rodata_16ee20_26c) - 0x26C;
__game_rodata_16ee20_2a4_base = ADDR(.game_rodata_16ee20_2a4) - 0x2A4;
__game_rodata_1c1150_0_base = ADDR(.game_rodata_1c1150_0);
__game_rodata_1c1150_14_base = ADDR(.game_rodata_1c1150_14) - 0x14;
__game_rodata_1c1150_28_base = ADDR(.game_rodata_1c1150_28) - 0x28;
__game_rodata_1c1150_3c_base = ADDR(.game_rodata_1c1150_3c) - 0x3C;
__game_rodata_1c1150_48_base = ADDR(.game_rodata_1c1150_48) - 0x48;
__game_rodata_1c1150_5c_base = ADDR(.game_rodata_1c1150_5c) - 0x5C;
__game_rodata_1c1150_70_base = ADDR(.game_rodata_1c1150_70) - 0x70;
__game_rodata_1c1150_1e4_base = ADDR(.game_rodata_1c1150_1e4) - 0x1E4;
__game_rodata_1c1150_240_base = ADDR(.game_rodata_1c1150_240) - 0x240;
__game_rodata_1c1150_428_base = ADDR(.game_rodata_1c1150_428) - 0x428;
__game_rodata_209b50_0_base = ADDR(.game_rodata_209b50_0);
__game_rodata_209b50_18_base = ADDR(.game_rodata_209b50_18) - 0x18;
__game_rodata_1e73b0_0_base = ADDR(.game_rodata_1e73b0_0);
__game_rodata_1e73b0_48_base = ADDR(.game_rodata_1e73b0_48) - 0x48;
__game_rodata_11d830_0_base = ADDR(.game_rodata_11d830_0);
__game_rodata_11d830_4_base = ADDR(.game_rodata_11d830_4) - 0x4;
__game_rodata_83300_0_base = ADDR(.game_rodata_83300_0);
__game_rodata_83300_c_base = ADDR(.game_rodata_83300_c) - 0xC;
__game_rodata_83300_14_base = ADDR(.game_rodata_83300_14) - 0x14;
__game_rodata_1f2730_0_base = ADDR(.game_rodata_1f2730_0);
__game_rodata_1f2730_c_base = ADDR(.game_rodata_1f2730_c) - 0xC;
__game_rodata_49d30_0_base = ADDR(.game_rodata_49d30_0);
__game_rodata_49d30_4_base = ADDR(.game_rodata_49d30_4) - 0x4;
__game_rodata_197f20_0_base = ADDR(.game_rodata_197f20_0);
__game_rodata_197f20_8_base = ADDR(.game_rodata_197f20_8) - 0x8;
__game_rodata_1865d0_0_base = ADDR(.game_rodata_1865d0_0);
__game_rodata_1865d0_20_base = ADDR(.game_rodata_1865d0_20) - 0x20;
__game_rodata_39750_0_base = ADDR(.game_rodata_39750_0);
__game_rodata_39750_1c_base = ADDR(.game_rodata_39750_1c) - 0x1C;
__game_rodata_64120_0_base = ADDR(.game_rodata_64120_0);
__game_rodata_64120_4_base = ADDR(.game_rodata_64120_4) - 0x4;
__game_rodata_90840_0_base = ADDR(.game_rodata_90840_0);
__game_rodata_90840_b8_base = ADDR(.game_rodata_90840_b8) - 0xB8;
__game_rodata_111670_0_base = ADDR(.game_rodata_111670_0);
__game_rodata_111670_4_base = ADDR(.game_rodata_111670_4) - 0x4;
__game_rodata_114b80_0_base = ADDR(.game_rodata_114b80_0);
__game_rodata_114b80_4_base = ADDR(.game_rodata_114b80_4) - 0x4;
__game_rodata_200930_0_base = ADDR(.game_rodata_200930_0);
__game_rodata_200930_28_base = ADDR(.game_rodata_200930_28) - 0x28;
__game_rodata_dc6b0_0_base = ADDR(.game_rodata_dc6b0_0);
__game_rodata_dc6b0_18_base = ADDR(.game_rodata_dc6b0_18) - 0x18;
__game_rodata_1a20a0_0_base = ADDR(.game_rodata_1a20a0_0);
__game_rodata_1a20a0_4_base = ADDR(.game_rodata_1a20a0_4) - 0x4;
__game_rodata_1fa770_0_base = ADDR(.game_rodata_1fa770_0);
__game_rodata_1fa770_8_base = ADDR(.game_rodata_1fa770_8) - 0x8;
__game_rodata_6b320_0_base = ADDR(.game_rodata_6b320_0);
__game_rodata_holtenrope_0_base = ADDR(.game_rodata_holtenrope_0);
__game_rodata_holtenrope_c_base = ADDR(.game_rodata_holtenrope_c) - 0xC;
__game_rodata_holtenrope_18_base = ADDR(.game_rodata_holtenrope_18) - 0x18;
__game_rodata_2062d0_0_base = ADDR(.game_rodata_2062d0_0);
__game_rodata_2062d0_10_base = ADDR(.game_rodata_2062d0_10) - 0x10;
__game_rodata_2062d0_28_base = ADDR(.game_rodata_2062d0_28) - 0x28;
__game_rodata_1d6e80_0_base = ADDR(.game_rodata_1d6e80_0);
__game_rodata_1d6e80_c_base = ADDR(.game_rodata_1d6e80_c) - 0xC;
__game_rodata_f3ba0_0_base = ADDR(.game_rodata_f3ba0_0);
__game_rodata_f3ba0_4_base = ADDR(.game_rodata_f3ba0_4) - 0x4;
__game_rodata_f3270_0_base = ADDR(.game_rodata_f3270_0);
__game_rodata_f3270_4_base = ADDR(.game_rodata_f3270_4) - 0x4;
__game_rodata_6b320_8_base = ADDR(.game_rodata_6b320_8) - 0x8;
__game_rodata_179f30_0_base = ADDR(.game_rodata_179f30_0);
__game_rodata_179f30_2ec_base = ADDR(.game_rodata_179f30_2ec) - 0x2EC;
__game_rodata_179f30_3c4_base = ADDR(.game_rodata_179f30_3c4) - 0x3C4;
__game_rodata_179f30_410_base = ADDR(.game_rodata_179f30_410) - 0x410;
__game_rodata_179f30_438_base = ADDR(.game_rodata_179f30_438) - 0x438;
__game_rodata_179f30_448_base = ADDR(.game_rodata_179f30_448) - 0x448;
__game_rodata_981e0_0_base = ADDR(.game_rodata_981e0_0);
__game_rodata_981e0_38_base = ADDR(.game_rodata_981e0_38) - 0x38;
__game_rodata_981e0_144_base = ADDR(.game_rodata_981e0_144) - 0x144;
__game_rodata_131f30_0_base = ADDR(.game_rodata_131f30_0);
__game_rodata_131f30_c_base = ADDR(.game_rodata_131f30_c) - 0xC;
__game_rodata_173d40_0_base = ADDR(.game_rodata_173d40_0);
__game_rodata_173d40_14_base = ADDR(.game_rodata_173d40_14) - 0x14;
__game_rodata_173d40_38_base = ADDR(.game_rodata_173d40_38) - 0x38;
__game_rodata_173d40_50_base = ADDR(.game_rodata_173d40_50) - 0x50;
__game_rodata_173d40_58_base = ADDR(.game_rodata_173d40_58) - 0x58;
__game_rodata_blood_0_base = ADDR(.game_rodata_blood_0);
__game_rodata_blood_204_base = ADDR(.game_rodata_blood_204) - 0x204;
__game_rodata_blood_260_base = ADDR(.game_rodata_blood_260) - 0x260;
__game_rodata_blood_2b4_base = ADDR(.game_rodata_blood_2b4) - 0x2B4;
__game_rodata_blood_480_base = ADDR(.game_rodata_blood_480) - 0x480;
__game_rodata_blood_4d0_base = ADDR(.game_rodata_blood_4d0) - 0x4D0;
__game_rodata_blood_504_base = ADDR(.game_rodata_blood_504) - 0x504;
__game_rodata_blood_53c_base = ADDR(.game_rodata_blood_53c) - 0x53C;
__game_rodata_effects_sight_0_base = ADDR(.game_rodata_effects_sight_0);
__game_rodata_effects_sight_18_base = ADDR(.game_rodata_effects_sight_18) - 0x18;
__game_rodata_effects_sight_e4_base = ADDR(.game_rodata_effects_sight_e4) - 0xE4;
__game_rodata_177b50_0_base = ADDR(.game_rodata_177b50_0);
__game_rodata_177b50_1c_base = ADDR(.game_rodata_177b50_1c) - 0x1C;
ASSERT(SIZEOF(.game_rodata_433f0) == 0xA0, "game_433F0 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_58f80_0) == 0x100, "game_58F80 table at 80096DF8 extent changed")
ASSERT(SIZEOF(.game_rodata_58f80_100) == 0x18, "game_58F80 table at 80096F04 extent changed")
ASSERT(SIZEOF(.game_rodata_aeb40) == 0x190, "game_AEB40 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_0) == 0x8, "game_B4080 literal pool at 8009DA18 extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_8) == 0x20, "game_B4080 table at 8009DA24 extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_28) == 0x8, "game_B4080 func_1508B9BC literal extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_30) == 0xFC, "game_B4080 table at 8009DA94 extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_12c) == 0xE4, "game_B4080 table at 8009DB90 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_0) == 0xB4, "game_16EE20 table at 800A5218 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_b4) == 0x164, "game_16EE20 table at 800A52CC extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_218) == 0x40, "game_16EE20 table at 800A5430 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_258) == 0x14, "game_16EE20 table at 800A5648 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_26c) == 0x38, "game_16EE20 table at 800A565C extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_2a4) == 0x4, "game_16EE20 func_1514470C literal extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_0) == 0x14, "game_1C1150 first table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_14) == 0x14, "game_1C1150 second table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_28) == 0x14, "game_1C1150 func_15194408 table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_3c) == 0xC, "game_1C1150 func_15194408 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_48) == 0x14, "game_1C1150 func_15194794 table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_5c) == 0x14, "game_1C1150 func_15194810 table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_70) == 0x174, "game_1C1150 func_15194BF0 first table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_1e4) == 0x5C, "game_1C1150 func_15194BF0 second table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_240) == 0x1E8, "game_1C1150 func_15194FF4 first table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_428) == 0x5C, "game_1C1150 func_15194FF4 second table extent changed")
ASSERT(SIZEOF(.game_rodata_49be0) == 0x20, "game_49BE0 table extent changed")
ASSERT(SIZEOF(.game_rodata_cd860) == 0x20, "game_CD860 table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_0) == 0x2EC, "game_179F30 func_1514CA80 first table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_2ec) == 0xD8, "game_179F30 func_1514CA80 second table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_3c4) == 0x4C, "game_179F30 func_1514CA80 third table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_410) == 0x28, "game_179F30 func_1514CA80 fourth table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_438) == 0x10, "game_179F30 func_1514D64C literal extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_448) == 0x28, "game_179F30 table extent changed")
__game_rodata_49be0_payload_size = 0x1C;
__game_rodata_cd860_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_5d2c0) == 0x1A0, "game_5D2C0 table extent changed")
ASSERT(SIZEOF(.game_rodata_1bf090) == 0x70, "game_1BF090 literal and table extent changed")
__game_rodata_5d2c0_payload_size = 0x19C;
__game_rodata_1bf090_payload_size = 0x64;
__game_rodata_aeb40_payload_size = 0x18C;
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
ASSERT(SIZEOF(.game_rodata_11ff10) == 0x10, "game_11FF10 func_150F2D14 literal extent changed")
__game_rodata_11ff10_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_15d730) == 0x50, "game_15D730 table extent changed")
__game_rodata_15d730_payload_size = 0x44;
ASSERT(SIZEOF(.game_rodata_15bd90) == 0x80, "game_15BD90 table extent changed")
__game_rodata_15bd90_payload_size = 0x78;
ASSERT(SIZEOF(.game_rodata_e4070) == 0x30, "game_E4070 table extent changed")
__game_rodata_e4070_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_1bfcb0) == 0x20, "game_1BFCB0 table extent changed")
__game_rodata_1bfcb0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_1bfdd0) == 0x20, "game_1BFDD0 emitter literal extent changed")
__game_rodata_1bfdd0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_12f400) == 0xB0, "game_12F400 table extent changed")
__game_rodata_12f400_payload_size = 0xA4;
ASSERT(SIZEOF(.game_rodata_ca630) == 0x150, "game_CA630 table extent changed")
__game_rodata_ca630_payload_size = 0x148;

ASSERT(SIZEOF(.game_rodata_a9d90) == 0x1C0, "game_A9D90 table extent changed")
__game_rodata_a9d90_payload_size = 0x1C0;

ASSERT(SIZEOF(.game_rodata_10bc70) == 0x10,
       "game_10BC70 constant pool extent changed")
__game_rodata_10bc70_payload_size = 0x4;

ASSERT(SIZEOF(.game_rodata_122b60) == 0x10,
       "game_122B60 constant pool extent changed")
__game_rodata_122b60_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_209b50_0) == 0x18,
       "game_209B50 func_151DC97C table extent changed")
ASSERT(SIZEOF(.game_rodata_209b50_18) == 0xC,
       "game_209B50 func_151DC97C literal extent changed")
ASSERT(SIZEOF(.game_rodata_1e73b0_0) == 0x48,
       "game_1E73B0 func_151BB61C template extent changed")
ASSERT(SIZEOF(.game_rodata_1e73b0_48) == 0x4,
       "game_1E73B0 func_151BB61C literal extent changed")
ASSERT(SIZEOF(.game_rodata_11d830_0) == 0x4,
       "game_11D830 func_150F0A24 literal extent changed")
ASSERT(SIZEOF(.game_rodata_11d830_4) == 0x20,
       "game_11D830 func_150F1170 literal extent changed")

ASSERT(SIZEOF(.game_rodata_1bc650) == 0x490,
       "game_1BC650 table extent changed")
__game_rodata_1bc650_payload_size = 0x488;

ASSERT(SIZEOF(.game_rodata_1483e0) == 0xE0, "game_1483E0 table extent changed")
__game_rodata_1483e0_payload_size = 0xD8;

ASSERT(SIZEOF(.game_rodata_61490) == 0xA0, "game_61490 table extent changed")
__game_rodata_61490_payload_size = 0x94;
ASSERT(SIZEOF(.game_rodata_b21b0) == 0x20, "game_B21B0 table extent changed")
__game_rodata_b21b0_payload_size = 0x1C;
ASSERT(SIZEOF(.game_rodata_b3020) == 0x10, "game_B3020 range literal extent changed")
__game_rodata_b3020_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_10c170) == 0x30, "game_10C170 particle literal extent changed")
__game_rodata_10c170_payload_size = 0x2C;
ASSERT(SIZEOF(.game_rodata_cbbe0) == 0x20, "game_CBBE0 table extent changed")
__game_rodata_cbbe0_payload_size = 0x1C;
ASSERT(SIZEOF(.game_rodata_cbdb0) == 0x50, "game_CBDB0 table extent changed")
__game_rodata_cbdb0_payload_size = 0x44;

ASSERT(SIZEOF(.game_rodata_981e0_0) == 0x38, "game_981E0 func_1506DE84 table extent changed")
ASSERT(SIZEOF(.game_rodata_981e0_38) == 0x10C, "game_981E0 leading and constructor literal extent changed")
ASSERT(SIZEOF(.game_rodata_981e0_144) == 0x80, "game_981E0 func_15070898 literal extent changed")

ASSERT(SIZEOF(.game_rodata_entrypoint) == 0x20, "entrypoint table extent changed")
__game_rodata_entrypoint_payload_size = 0x14;

ASSERT(SIZEOF(.game_rodata_c98f0) == 0x20, "game_C98F0 table extent changed")
__game_rodata_c98f0_payload_size = 0x18;

ASSERT(SIZEOF(.game_rodata_3ba70) == 0x40, "game_3BA70 table extent changed")
__game_rodata_3ba70_payload_size = 0x40;
ASSERT(SIZEOF(.game_rodata_39750_0) == 0x1C, "game_39750 func_1500D8C8 resource table extent changed")
ASSERT(SIZEOF(.game_rodata_39750_1c) == 0x50, "game_39750 func_1500CE4C/func_1500D3AC/func_1500D8C8 literal extent changed")

ASSERT(SIZEOF(.game_rodata_20bda0) == 0x30, "game_20BDA0 table extent changed")
__game_rodata_20bda0_payload_size = 0x28;

ASSERT(SIZEOF(.game_rodata_138b40) == 0x90, "game_138B40 table extent changed")
__game_rodata_138b40_payload_size = 0x8C;

ASSERT(SIZEOF(.game_rodata_10e510) == 0x20, "game_10E510 emitter literal extent changed")
__game_rodata_10e510_payload_size = 0x14;

ASSERT(SIZEOF(.game_rodata_109220) == 0xB0, "game_109220 table and literal extent changed")
__game_rodata_109220_payload_size = 0xB0;

ASSERT(SIZEOF(.game_rodata_ec420) == 0x20, "game_EC420 func_150BF21C literal extent changed")
__game_rodata_ec420_payload_size = 0x14;

ASSERT(SIZEOF(.game_rodata_90840_0) == 0xB8, "game_90840 table extent changed")
ASSERT(SIZEOF(.game_rodata_90840_b8) == 0x98,
       "game_90840 func_15064B94 literal extent changed")
ASSERT(SIZEOF(.game_rodata_173d40_0) == 0x14,
       "game_173D40 func_15146970 id extent changed")
ASSERT(SIZEOF(.game_rodata_173d40_14) == 0x24,
       "game_173D40 func_15146970 table extent changed")
ASSERT(SIZEOF(.game_rodata_173d40_38) == 0x18,
       "game_173D40 func_15146A98 literal extent changed")
ASSERT(SIZEOF(.game_rodata_173d40_50) == 0x8,
       "game_173D40 func_15146D60 literal extent changed")
ASSERT(SIZEOF(.game_rodata_173d40_58) == 0x18,
       "game_173D40 emitter literal extent changed")

/* Burst velocity literals own one word; remaining input bytes are zero alignment. */
ASSERT(SIZEOF(.game_rodata_f3270_0) == 0x4,
       "game_F3270 velocity literal extent changed")
ASSERT(SIZEOF(.game_rodata_f3270_4) == 0x8,
       "game_F3270 state literal extent changed")
ASSERT(SIZEOF(.game_rodata_f3ba0_0) == 0x4,
       "game_F3BA0 velocity literal extent changed")
ASSERT(SIZEOF(.game_rodata_f3ba0_4) == 0x8,
       "game_F3BA0 state literal extent changed")
ASSERT(SIZEOF(.game_rodata_1d6e80_0) == 0xC,
       "game_1D6E80 func_151AADF8 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1d6e80_c) == 0x4,
       "game_1D6E80 velocity literal extent changed")
ASSERT(SIZEOF(.game_rodata_1d8de0) == 0x10, "game_1D8DE0 particle speed literal extent changed")
__game_rodata_1d8de0_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_1fbb80) == 0x20, "game_1FBB80 rain emitter literal extent changed")
__game_rodata_1fbb80_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_1fc5d0) == 0x10, "game_1FC5D0 func_151CF120 literal extent changed")
__game_rodata_1fc5d0_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_188440) == 0x40, "game_188440 literal extent changed")
__game_rodata_188440_payload_size = 0x34;
ASSERT(SIZEOF(.game_rodata_1b8b60) == 0x10, "game_1B8B60 literal extent changed")
__game_rodata_1b8b60_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_e4ff0) == 0x20, "game_E4FF0 literal extent changed")
__game_rodata_e4ff0_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_1cbe20) == 0x10,
       "game_1CBE20 scale literal extent changed")
__game_rodata_1cbe20_payload_size = 0x8;

ASSERT(SIZEOF(.game_rodata_f21d0) == 0x10, "game_F21D0 wave literal extent changed")
__game_rodata_f21d0_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_12c1e0) == 0x10, "game_12C1E0 ray literal extent changed")
__game_rodata_12c1e0_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_1dd500) == 0x10, "game_1DD500 quad literal extent changed")
__game_rodata_1dd500_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_71820) == 0x10, "game_71820 look-at literal extent changed")
__game_rodata_71820_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_2062d0_0) == 0x10, "game_2062D0 func_151DA08C literal extent changed")
ASSERT(SIZEOF(.game_rodata_2062d0_10) == 0x18, "game_2062D0 func_151DA368 literal extent changed")
ASSERT(SIZEOF(.game_rodata_2062d0_28) == 0x4, "game_2062D0 effect literal extent changed")
ASSERT(SIZEOF(.game_rodata_360a0) == 0x20, "game_360A0 descriptor literal extent changed")
__game_rodata_360a0_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_113d60) == 0x10, "game_113D60 emitter literal extent changed")
__game_rodata_113d60_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_fd1d0) == 0x10, "game_FD1D0 prompt literal extent changed")
__game_rodata_fd1d0_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_1a20a0_0) == 0x4, "game_1A20A0 func_15174BF0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1a20a0_4) == 0x10, "game_1A20A0 radian literal extent changed")
ASSERT(SIZEOF(.game_rodata_1199d0) == 0x20, "game_1199D0 smoke literal extent changed")
__game_rodata_1199d0_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_156160) == 0x10, "game_156160 camera literal extent changed")
__game_rodata_156160_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_1ed0f0) == 0x10, "game_1ED0F0 trace epsilon literal extent changed")
__game_rodata_1ed0f0_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_135d00) == 0x10, "game_135D00 billboard literal extent changed")
__game_rodata_135d00_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_1368c0) == 0x10, "game_1368C0 func_1510A40C literal extent changed")
__game_rodata_1368c0_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_eeb70) == 0x20, "game_EEB70 motion literal extent changed")
__game_rodata_eeb70_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_476d0) == 0x10, "game_476D0 view literal extent changed")
__game_rodata_476d0_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_ddf10) == 0x30, "game_DDF10 spawn literal extent changed")
__game_rodata_ddf10_payload_size = 0x24;
ASSERT(SIZEOF(.game_rodata_e35c0) == 0x10, "game_E35C0 effect literal extent changed")
__game_rodata_e35c0_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_fc5f0) == 0x20, "game_FC5F0 particle literal extent changed")
__game_rodata_fc5f0_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_1a7260) == 0x10, "game_1A7260 index table extent changed")
__game_rodata_1a7260_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_ffba0) == 0x20, "game_FFBA0 colour table and literal extent changed")
__game_rodata_ffba0_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_holtenrope_0) == 0xC, "holtenrope func_151B3CF0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_holtenrope_c) == 0xC, "holtenrope func_151B42A4 literal extent changed")
ASSERT(SIZEOF(.game_rodata_holtenrope_18) == 0x8, "holtenrope point literal extent changed")
ASSERT(SIZEOF(.game_rodata_characterflamethrower) == 0x10,
       "characterflamethrower preset literal extent changed")
__game_rodata_characterflamethrower_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_effects_sight_0) == 0x18, "effects_sight func_151C899C literal extent changed")
ASSERT(SIZEOF(.game_rodata_effects_sight_18) == 0xCC, "effects_sight func_151C9BA0 table extent changed")
ASSERT(SIZEOF(.game_rodata_effects_sight_e4) == 0x4, "effects_sight interpolation constant extent changed")
ASSERT(SIZEOF(.game_rodata_e7970) == 0x30, "game_E7970 particle literal extent changed")
__game_rodata_e7970_payload_size = 0x2C;
ASSERT(SIZEOF(.game_rodata_1cc440) == 0x10, "game_1CC440 constant pool extent changed")
__game_rodata_1cc440_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_177b50_0) == 0x1C,
       "game_177B50 func_1514AB5C literal extent changed")
ASSERT(SIZEOF(.game_rodata_177b50_1c) == 0x80,
       "game_177B50 func_1514B034/func_1514B364/func_1514B8E4 literal extent changed")
ASSERT(SIZEOF(.game_rodata_17caf0) == 0x10,
       "game_17CAF0 particle literal extent changed")
__game_rodata_17caf0_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_1865d0_0) == 0x20, "game_1865D0 func_15159C08 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1865d0_20) == 0xC, "game_1865D0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1ef500) == 0x10,
       "game_1EF500 literal extent changed")
__game_rodata_1ef500_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_e8c10) == 0x40,
       "game_E8C10 particle literal extent changed")
__game_rodata_e8c10_payload_size = 0x3C;
ASSERT(SIZEOF(.game_rodata_19e040) == 0x40,
       "game_19E040 particle literal extent changed")
__game_rodata_19e040_payload_size = 0x40;
ASSERT(SIZEOF(.game_rodata_eee70) == 0x20, "game_EEE70 constant pool extent changed")
__game_rodata_eee70_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_1ac2f0) == 0x10, "game_1AC2F0 constant pool extent changed")
__game_rodata_1ac2f0_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_1b5370) == 0x10, "game_1B5370 constant pool extent changed")
__game_rodata_1b5370_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_1b81d0) == 0x20,
       "game_1B81D0 particle literal extent changed")
__game_rodata_1b81d0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_fa360) == 0x10,
       "game_FA360 drift literal extent changed")
__game_rodata_fa360_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_123d40) == 0x10,
       "game_123D40 spawn literal extent changed")
__game_rodata_123d40_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_1dbd40) == 0x10,
       "game_1DBD40 emission literal extent changed")
__game_rodata_1dbd40_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_200930_0) == 0x28,
       "game_200930 func_151D4408 literal extent changed")
ASSERT(SIZEOF(.game_rodata_200930_28) == 0x24,
       "game_200930 effect literal extent changed")
ASSERT(SIZEOF(.game_rodata_12ccf0) == 0x30,
       "game_12CCF0 sparkle literal extent changed")
__game_rodata_12ccf0_payload_size = 0x2C;
ASSERT(SIZEOF(.game_rodata_11d030) == 0x10,
       "game_11D030 motion literal extent changed")
__game_rodata_11d030_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_131f30_0) == 0xC,
       "game_131F30 func_151050B0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_131f30_c) == 0x18,
       "game_131F30 func_151058B4 literal extent changed")
ASSERT(SIZEOF(.game_rodata_6b320_0) == 0x8,
       "game_6B320 func_1503E5F8 literal extent changed")
ASSERT(SIZEOF(.game_rodata_6b320_8) == 0x8,
       "game_6B320 func_1503ECA0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_124920) == 0x10,
       "game_124920 literal extent changed")
__game_rodata_124920_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_127060) == 0x10,
       "game_127060 literal extent changed")
__game_rodata_127060_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_f44d0) == 0x20,
       "game_F44D0 literal extent changed")
__game_rodata_f44d0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_1f2730_0) == 0xC,
       "game_1F2730 func_151C577C first literal range changed")
ASSERT(SIZEOF(.game_rodata_1f2730_c) == 0x14,
       "game_1F2730 func_151C577C second literal range changed")
ASSERT(SIZEOF(.game_rodata_49d30_0) == 0x4,
       "game_49D30 func_1501D044 literal extent changed")
ASSERT(SIZEOF(.game_rodata_49d30_4) == 0x4,
       "game_49D30 func_1501F72C literal extent changed")
ASSERT(SIZEOF(.game_rodata_197f20_0) == 0x8, "game_197F20 func_1516CC58 float literal extent changed")
ASSERT(SIZEOF(.game_rodata_197f20_8) == 0x1C, "game_197F20 func_1516CC58 double literal extent changed")
ASSERT(SIZEOF(.game_rodata_40490) == 0x10,
       "game_40490 literal extent changed")
__game_rodata_40490_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_a28b0) == 0x10,
       "game_A28B0 literal extent changed")
__game_rodata_a28b0_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_dc6b0_0) == 0x18,
       "game_DC6B0 func_150AF328 literal extent changed")
ASSERT(SIZEOF(.game_rodata_dc6b0_18) == 0x4,
       "game_DC6B0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_c2350) == 0x10,
       "game_C2350 literal extent changed")
__game_rodata_c2350_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_12b7d0) == 0x10,
       "game_12B7D0 particle literal extent changed")
__game_rodata_12b7d0_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_83300_0) == 0xC,
       "game_83300 velocity literal extent changed")
ASSERT(SIZEOF(.game_rodata_83300_c) == 0x8,
       "game_83300 func_1505F188 literal extent changed")
ASSERT(SIZEOF(.game_rodata_83300_14) == 0x4,
       "game_83300 func_150623F4 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1d3ab0) == 0x10,
       "game_1D3AB0 constant pool extent changed")
__game_rodata_1d3ab0_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_1ce2f0) == 0x10,
       "game_1CE2F0 scale literal extent changed")
__game_rodata_1ce2f0_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_f9430) == 0x10,
       "game_F9430 particle literal extent changed")
__game_rodata_f9430_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_64120_0) == 0x4,
       "game_64120 degree literal extent changed")
ASSERT(SIZEOF(.game_rodata_64120_4) == 0x4,
       "game_64120 func_1503B708 literal extent changed")
ASSERT(SIZEOF(.game_rodata_20a290) == 0x10,
       "game_20A290 spawn literal pool extent changed")
__game_rodata_20a290_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_1fa770_0) == 0x8,
       "game_1FA770 particle gravity literal extent changed")
ASSERT(SIZEOF(.game_rodata_1fa770_8) == 0xC,
       "game_1FA770 func_151CDB94 literal extent changed")
ASSERT(SIZEOF(.game_rodata_111670_0) == 0x4,
       "game_111670 func_150E42F8 literal extent changed")
ASSERT(SIZEOF(.game_rodata_111670_4) == 0x34,
       "game_111670 effect literal pool extent changed")

ASSERT(SIZEOF(.game_rodata_1179b0) == 0x10,
       "game_1179B0 velocity literal extent changed")
__game_rodata_1179b0_payload_size = 0x4;

ASSERT(SIZEOF(.game_rodata_169510) == 0x40, "game_169510 table extent changed")
__game_rodata_169510_payload_size = 0x34;
ASSERT(SIZEOF(.game_rodata_1b0740) == 0x60, "game_1B0740 table and literal extent changed")
__game_rodata_1b0740_payload_size = 0x54;

ASSERT(SIZEOF(.game_rodata_blood_0) == 0x204, "effects/blood first table extent changed")
ASSERT(SIZEOF(.game_rodata_blood_204) == 0x5C, "effects/blood second table extent changed")
ASSERT(SIZEOF(.game_rodata_blood_260) == 0x54, "effects/blood func_151356D4/func_15135DD0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_blood_2b4) == 0x1CC, "effects/blood func_15137610 table extent changed")
ASSERT(SIZEOF(.game_rodata_blood_480) == 0x50, "effects/blood func_15138C80 table extent changed")
ASSERT(SIZEOF(.game_rodata_blood_4d0) == 0x34, "effects/blood func_15138E98 literal extent changed")
ASSERT(SIZEOF(.game_rodata_blood_504) == 0x38, "effects/blood func_15139768/func_15139D74 literal extent changed")
ASSERT(SIZEOF(.game_rodata_blood_53c) == 0x68, "effects/blood spray and burst literal extent changed")

ASSERT(SIZEOF(.game_rodata_camera_camera) == 0x10,
       "camera_camera angle literal extent changed")
__game_rodata_camera_camera_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_18a8f0) == 0x10,
       "game_18A8F0 clamp literal extent changed")
__game_rodata_18a8f0_payload_size = 0x8;

ASSERT(SIZEOF(.game_rodata_1b8f40) == 0x30, "game_1B8F40 table extent changed")
__game_rodata_1b8f40_payload_size = 0x24;

ASSERT(SIZEOF(.game_rodata_114b80_0) == 0x4, "game_114B80 func_150E7C9C literal extent changed")
ASSERT(SIZEOF(.game_rodata_114b80_4) == 0x4, "game_114B80 func_150E8470 literal extent changed")
ASSERT(SIZEOF(.game_rodata_115f30) == 0x10, "game_115F30 constant pool extent changed")
__game_rodata_115f30_payload_size = 0xC;

ASSERT(SIZEOF(.game_rodata_116d40) == 0x20, "game_116D40 constant pool extent changed")
__game_rodata_116d40_payload_size = 0x20;

ASSERT(SIZEOF(.game_rodata_10d7b0) == 0x20, "game_10D7B0 constant pool extent changed")
__game_rodata_10d7b0_payload_size = 0x18;

ASSERT(SIZEOF(.game_rodata_1188e0) == 0x10, "game_1188E0 constant pool extent changed")
__game_rodata_1188e0_payload_size = 0x4;

ASSERT(SIZEOF(.game_rodata_97aa0) == 0x20, "game_97AA0 constant pool extent changed")
__game_rodata_97aa0_payload_size = 0x18;

ASSERT(SIZEOF(.game_rodata_de5a0) == 0x20, "game_DE5A0 constant pool extent changed")
__game_rodata_de5a0_payload_size = 0x1C;

ASSERT(SIZEOF(.game_rodata_133190) == 0x10, "game_133190 constant pool extent changed")
__game_rodata_133190_payload_size = 0x8;

ASSERT(SIZEOF(.game_rodata_191c30) == 0x20, "game_191C30 constant pool extent changed")
__game_rodata_191c30_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_197120) == 0x20, "game_197120 constant pool extent changed")
__game_rodata_197120_payload_size = 0x1C;

ASSERT(SIZEOF(.game_rodata_1d4ac0) == 0x10, "game_1D4AC0 constant pool extent changed")
__game_rodata_1d4ac0_payload_size = 0xC;

ASSERT(SIZEOF(.game_rodata_1e58b0) == 0x10, "game_1E58B0 constant pool extent changed")
__game_rodata_1e58b0_payload_size = 0x10;

ASSERT(SIZEOF(.game_rodata_1e37d0) == 0x10, "game_1E37D0 constant pool extent changed")
__game_rodata_1e37d0_payload_size = 0x4;

ASSERT(SIZEOF(.game_rodata_1e6260) == 0x10, "game_1E6260 constant pool extent changed")
__game_rodata_1e6260_payload_size = 0x4;

ASSERT(SIZEOF(.game_rodata_1e9820) == 0x20, "game_1E9820 constant pool extent changed")
__game_rodata_1e9820_payload_size = 0x14;

ASSERT(SIZEOF(.game_rodata_light) == 0xC0, "light switch table extent changed")
__game_rodata_light_payload_size = 0xBC;
