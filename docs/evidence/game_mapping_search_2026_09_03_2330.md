# Game mapping search ending 2026-09-03 at 23:30 Brisbane

Scope: continue reviewed raw-assembly game source-family mapping on `feature/mappings`. The deadline is 13:30 UTC. Generic names identify ROM offsets, not recovered historical filenames. No new matching C implementations are claimed.

At the start, reviewed source intervals and exact library text covered 1,343,024 of 2,237,392 tracked US code bytes (60.0263%); the game overlay covered 1,244,512 of 2,072,880 (60.0378%).

## Results and evidence

| Evidence | Accepted groups | Raw entries | Bytes |
| --- | ---: | ---: | ---: |
| [Child chains and render lists](game_raw_child_chain_render_lists.md) | 3 | 26 | 8,768 |
| [Type-4B/framebuffer](game_raw_type4b_framebuffer_groups.md) and [narrow cores](game_raw_narrow_effect_record_cores.md) | 5 | 19 | 9,152 |
| [Scene setup/emission/controller](game_raw_scene_setup_emission_controller.md) | 5 | 16 | 8,624 |
| [Loader/transfer/emission](game_raw_loader_transfer_emission_groups.md) | 5 | 13 | 8,800 |
| [Parser/actor state](game_raw_parser_actor_state_groups.md) | 9 | 23 | 18,224 |
| [Radial/queue/render](game_raw_radial_queue_render_groups.md) | 5 | 18 | 9,248 |
| [Compact display/resources](game_raw_compact_display_resource_pairs.md) | 7 | 16 | 10,304 |
| [Selected particles/resources](game_raw_selected_particle_resource_groups.md) | 5 | 12 | 3,280 |
| [Descriptor callbacks](game_raw_descriptor_callback_families.md) | 10 | 27 | 27,856 |
| [Record/state/render cores](game_raw_record_transform_state_groups.md) | 3 | 9 | 2,208 |
| [Timed actor emitter](game_raw_timed_actor_emitter.md) | 1 | 2 | 1,296 |
| Total | 58 | 181 | 107,760 |

One extra candidate boundary at `0x1B5BF0:0x1B6010` was withdrawn when independent indexing revealed an unaccounted eight-byte entry. Its three raw function work items remain available without boundary credit. The guarded `withdraw-source-unit` CLI preserves work and restores raw map ownership; its tests cover inventory preservation, mixed-map restoration, modified-source rejection and rollback.

## Remaining leads

The deadline ends this pass, not candidate exhaustion. These ranges remain unregistered and receive no coverage credit:

- `0xAC9C0:0xAD770`: connected transform processing, but the independent function CSV omits the raw entry `150AC9C0`. Reconcile that disagreement first.
- `0x1DD140:0x1DD3A0`: apparent EEPROM-read library lineage. No complete masked object match was found among I/J/K/L normal, debug and ROM variants. Keep this as a possible Rare library override, rather than assigning it to game code.
- `0x1082D0:0x108850`: update, child and event pointers exist at `8008A580`, `800897C0` and `8008A968`. Establish the factory selectors and complete membership before grouping them.
- `0xEAF50:0xEB1C0`: action callbacks at `8008A0A0` and `8008A11C`; the relationship still needs dispatcher evidence.
- `0x193660:0x193CA0`: two factories and two emitter callbacks; determine whether they form one connected family or two independent pairs.
- `0x104170:0x104520`: a type-64 constructor/update/draw core is followed by an unrelated getter at `0x1044F4`. The internal split is not 16-byte aligned, so the current source-unit registration contract does not accept it.

Larger mixed ranges also remain. Shared generic factories or similar neighboring routines alone do not establish a source family.

## Final coverage and overlay validation

All 58 accepted units are integrated as mixed C/ASM wrappers. Reviewed source boundaries plus exact library text now cover 1,450,784 / 2,237,392 US code bytes (64.8426%). Game-overlay coverage is 1,352,272 / 2,072,880 (65.2364%). Overall, 786,608 bytes remain without reviewed ownership. The instruction-matched byte count remains 150,564; this pass adds mapping evidence rather than C implementations.

All eleven complete-overlay integration gates pass. After withdrawing the ambiguous boundary, the following batch verifies the corrected map. The final overlay is 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 176 repository tests pass, including the withdrawal cases and reviewed-boundary map coverage. Shell syntax and generated progress checks pass.

The final `./conker build --profile us` also passes the complete US ROM byte comparison. `git diff --check` passes. Existing branch work was preserved; nothing was staged or committed.
