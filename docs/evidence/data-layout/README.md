# Data and section layout

[Evidence index](../README.md) · [Documentation](../../README.md)

Jump tables, literal pools and private storage have their own proof requirements. These records support placement and extent claims; they do not by themselves prove a C match or an original source boundary. See [reviewed initialized data](../../main-private-data.md) for the manifest contract.

## Records

- [Independent bounded DEFLATE replacement](us_independent_deflate.md)
- [US complete bounded asset storage accounting](us_asset_storage_accounting.md)

- [US bank-03 and bank-09 model reconstruction](us_model_reconstruction.md)

- [US texture 1063 PNG-to-RZIP build and data credit](us_texture_1063_build.md)
- [US 26-texture CI4 reconstruction batch](us_ci4_texture_batch.md)
- [US CI4 reconstruction: 50 additional textures, 76 total](us_ci4_texture_batch_50.md)
- [US jump tables exposed by the September 18 automation batch](automation_jump_tables.md)
- [Recovered US switch table placement](blocked_switch_jump_tables.md)
- [Entrypoint switch table](entrypoint_jump_table.md)
- [US game_10BC70 float constant](game_10bc70_float_constant.md)
- [US game_10D7B0 float constants](game_10d7b0_float_constants.md)
- [US game_111670 effect literal pool](game_111670_float_constants.md)
- [US game_116D40 emitter scale](game_116d40_float_constant.md)
- [US game_1188E0 burst spread scale](game_1188e0_float_constant.md)
- [US game_11D830 float constant](game_11d830_float_constant.md)
- [US game_123D40 spawn float constants](game_123d40_float_constants.md)
- [US game_133190 float constants](game_133190_float_constants.md)
- [US game_177B50 particle float constants](game_177b50_float_constants.md)
- [US game_197120 float constant](game_197120_float_constant.md)
- [US game_1B81D0 particle float constants](game_1b81d0_float_constants.md)
- [US game_1DBD40 emission float constants](game_1dbd40_float_constants.md)
- [US game_200930 effect float constants](game_200930_float_constants.md)
- [US game_1CBE20 float constants](game_1cbe20_float_constant.md)
- [US game_1CE2F0 float constants](game_1ce2f0_float_constants.md)
- [US game_1D4AC0 float constants](game_1d4ac0_float_constants.md)
- [US game_1E58B0 float constants](game_1e58b0_float_constants.md)
- [US game_1E9820 float constants](game_1e9820_float_constants.md)
- [US game_1EF500 easing float constant](game_1ef500_float_constants.md)
- [US game_E8C10 particle float constants](game_e8c10_float_constants.md)
- [US game_19E040 particle float constants](game_19e040_float_constants.md)
- [US game_64120 float constant](game_64120_float_constant.md)
- [US game_83300 velocity float constants](game_83300_float_constants.md)
- [US game rodata literal sub-pools](game_rodata_literal_sub_pools.md)
- [US game_97AA0 float constants](game_97aa0_float_constants.md)
- [US game_DE5A0 float constants](game_de5a0_float_constants.md)
- [US game_F9430 particle constants](game_f9430_float_constants.md)
- [US game_FA360 drift float constants](game_fa360_float_constants.md)
- [US game_1FA770 particle gravity constants](game_1fa770_float_constants.md)
- [US game_20A290 spawn literal pool](game_20a290_float_constant.md)
- [US switch table for game_11F780](game_11f780_jump_table.md)
- [US sound-event selector table](game_1483e0_jump_table.md)
- [US switch table for game_12F400](game_12f400_jump_table.md)
- [US switch table for game_15BD90](game_15bd90_jump_table.md)
- [US switch table for game_1BFCB0](game_1bfcb0_jump_table.md)
- [US switch table for game_CA630](game_ca630_jump_table.md)
- [US switch table for game_E4070](game_e4070_jump_table.md)
- [US switch tables for game_15D730](game_15d730_jump_tables.md)
- [US switch table for game_1B8F40](game_1b8f40_jump_table.md)
- [US game_1BC650 jump tables](game_1bc650_jump_tables.md)
- [US game_1BF090 literal pool before its switch table](game_1bf090_literal_pool.md)
- [US state-scale switch table](game_3ba70_jump_table.md) · [JSON](game_3ba70_jump_table.json) · [PATCH](game_3ba70_jump_table.patch)
- [US actor command dispatcher table](game_61490_jump_table.md)
- [External jump table for func_1503453C (US)](game_61950_jump_table.md)
- [Glyph helper switch and floating constants (US)](game_6ea90_glyph_rodata.md)
- [Pending actor action table](game_90840_jump_table.md)
- [Constructor literal pool in game_981E0](game_981e0_constructor_literal_pool.md)
- [Burst velocity literals](game_burst_velocity_literals.md)
- [US switch table for game_A9D90](game_a9d90_jump_table.md)
- [US callback switch table](game_c98f0_jump_table.md)
- [Effect helper floating constants (US)](game_effect_constant_pools.md)
- [AI buffer submission private data](main_ai_private_data.md)
- [B1B0 literal-pool integration](main_b1b0_literal_pool.md)
- [VI manager source and private storage](main_init_vi_layout.md)
- [Main text zero-tail classification at `0x226B0`](main_text_zero_tail_226b0.md)
- [US jump tables for the manual matching batch](manual_batch_jump_tables.md)

## Supporting data

- [main_init_2e50_integration_proposal.json](main_init_2e50_integration_proposal.json)

These are scoped research records, not a fresh verification of the checkout.
Keep new evidence with its topic and link it from this index; amend an existing
record when extending the same claim.

- [Continuing US texture reconstruction](us_texture_reconstruction.md)

- [US native character reconstruction](us_character_reconstruction.md) · [JSON](us_character_reconstruction.json)

- [US native character animation reconstruction](us_animation_reconstruction.md)

- [Extended US scene-model reconstruction](us_model_extended_reconstruction.md)

- [US MP3 decoder table reconstruction](us_mp3_table_reconstruction.md)

- [Complete US character morph bank reconstruction](us_morph_reconstruction.md)

- [US MPEG-2 spectral reconstruction](us_mp3_spectral_reconstruction.md): semantic coefficient sources, exact physical frame spans and exclusion of opaque cues and tails.

- [US event-program reconstruction](us_event_reconstruction.md): complete bank-14 instructions, labels, constant strings, fresh compression and generated index.

- [US sprite PNG reconstruction](us_sprite_reconstruction.md): RGBA5551 and I4 planes, exact compression and native credit for 51 entries.

- [Bank 0A native-format animations](us_animation_bank_0a.md): 29 typed bundles; runtime owner unconfirmed.
- [Script bank reconstruction](us_script_reconstruction.md): tracks, bindings, commands, text and fresh nested archive storage.

- [US animation-control records](us_animation_control_reconstruction.md): 82 bank-0F entries with typed routes, events, action phases and behavior instructions.

- [Light nested switch tables](effects_light_jump_tables.md): both ROM-backed dispatch tables for `func_151604A0`.
