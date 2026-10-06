# Data and section layout

[Evidence index](../README.md) · [Documentation](../../README.md)

Jump tables, literal pools and private storage have their own proof requirements. These records support placement and extent claims; they do not by themselves prove a C match or an original source boundary. See [reviewed initialized data](../../main-private-data.md) for the manifest contract.

## Records

- [US jump tables exposed by the September 18 automation batch](automation_jump_tables.md)
- [Recovered US switch table placement](blocked_switch_jump_tables.md)
- [Entrypoint switch table](entrypoint_jump_table.md)
- [US game_11D830 float constant](game_11d830_float_constant.md)
- [US switch table for game_11F780](game_11f780_jump_table.md)
- [US sound-event selector table](game_1483e0_jump_table.md)
- [US switch tables for game_15D730](game_15d730_jump_tables.md)
- [US game_1BC650 jump tables](game_1bc650_jump_tables.md)
- [US state-scale switch table](game_3ba70_jump_table.md) · [JSON](game_3ba70_jump_table.json) · [PATCH](game_3ba70_jump_table.patch)
- [US actor command dispatcher table](game_61490_jump_table.md)
- [External jump table for func_1503453C (US)](game_61950_jump_table.md)
- [Glyph helper switch and floating constants (US)](game_6ea90_glyph_rodata.md)
- [Pending actor action table](game_90840_jump_table.md)
- [Constructor literal pool in game_981E0](game_981e0_constructor_literal_pool.md)
- [US switch table for game_A9D90](game_a9d90_jump_table.md)
- [US callback switch table](game_c98f0_jump_table.md)
- [Effect helper floating constants (US)](game_effect_constant_pools.md)
- [AI buffer submission private data](main_ai_private_data.md)
- [VI manager source and private storage](main_init_vi_layout.md)
- [Main text zero-tail classification at `0x226B0`](main_text_zero_tail_226b0.md)
- [US jump tables for the manual matching batch](manual_batch_jump_tables.md)

## Supporting data

- [main_init_2e50_integration_proposal.json](main_init_2e50_integration_proposal.json)

These are scoped research records, not a fresh verification of the checkout.
Keep new evidence with its topic and link it from this index; amend an existing
record when extending the same claim.
