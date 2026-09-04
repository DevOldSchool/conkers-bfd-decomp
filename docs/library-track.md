# Library track

The project builds Nintendo 64 library code from `lib/` separately from
Conker-specific `src/` code. Stock SDK objects come from the pinned ultralib
submodule, while verified Rare variants live in a bounded Rare source snapshot.

## Reviewed code-boundary coverage

As of the 2026-09-03 search, reviewed source-unit intervals plus exact archive
text cover 1,589,056 of 2,237,392 tracked US code bytes (71.0227%). Another
648,336 bytes (28.9773%) still lack that reviewed ownership coverage.

| Area | Reviewed source-unit bytes | Exact archive text | Combined coverage | Tracked code bytes |
| --- | ---: | ---: | ---: | ---: |
| Main | 0 | 98,512 | 98,512 (59.8813%) | 164,512 |
| Game | 1,442,752 | 47,792 | 1,490,544 (71.9069%) | 2,072,880 |

This is boundary coverage, not implementation completion. It merges the US
intervals of the 491 source units with reviewed boundary evidence and the
canonical maps' archive `.text` intervals, separately per overlay, so overlaps
are counted once. The two unreviewed bootstrap units are excluded. Generic
raw split points alone receive no reviewed-ownership credit. Initialized data,
rodata, BSS, and assets are outside this code-byte denominator. The separate
matched-code figure is 150,564 bytes (6.7294%); see generated
[`progress.md`](progress.md).

The resumed game-overlay mapping adds camera, Holten rope, bee-cavern and sight
effects: four structural source-family hypotheses covering 116 functions and
58,368 bytes. All members remain raw assembly, and the complete integrated
overlay remains byte-identical. See the [camera, rope and bee-cavern evidence](evidence/game_beta_camera_rope_bee.md)
and [sight evidence](evidence/game_beta_sight.md) for the boundary limits.
Five further state, callback and shared-helper groups add 249 functions and
92,528 bytes, using offset-derived names while their original filenames remain
unknown. See the [structural group evidence](evidence/game_state_callback_helper_groups.md).
Thirteen early callback, state and resource groups add another 197 functions
and 58,512 bytes; see the [early-group evidence](evidence/game_early_callback_state_groups.md).
Four dispatcher, command-handler and descriptor groups add 662 recovered
entries and 90,672 bytes. Sixteen table-proven return callbacks now have explicit
symbols; their code is still raw assembly. See the [dispatcher evidence](evidence/game_dispatcher_callback_groups.md)
and [callback symbol evidence](evidence/game_return_callback_symbols.md).
Nineteen further helper/callback groups add 263 recovered entries and 95,136
bytes; see the [remaining upstream C-group evidence](evidence/game_remaining_upstream_c_groups.md).
Across these four later batches, 41 new groups cover 1,371 recovered entries
and 336,848 bytes. All four complete-overlay integration attempts pass.
Two more batches add nine reviewed raw source groups, 272 recovered entries
and 73,152 bytes. Both full-overlay checks pass; see the
[callback/state groups](evidence/game_raw_callback_state_groups.md) and
[resource/helper groups](evidence/game_raw_resource_helper_groups.md).
Five further batches add 27 reviewed groups, 485 raw entries and 267,952
bytes. Four internal boundaries separate connected cores from unrelated
neighbors. All complete-overlay gates pass after correcting an integration
parser bug at an existing library boundary; the first six-group attempt had
rolled back safely. See the [core groups](evidence/game_raw_core_state_groups.md),
[preserved helpers](evidence/game_raw_preserved_helper_groups.md),
[connected controllers](evidence/game_raw_connected_controller_groups.md),
[text/view/descriptor groups](evidence/game_raw_text_view_descriptor_groups.md),
and [state/lifecycle groups](evidence/game_raw_state_lifecycle_groups.md).
Seven dispatch, position and effect-helper groups add another 94 raw entries
and 29,520 bytes, with three further internal raw boundaries. Their first
complete-overlay check passes; see the [dispatch/position evidence](evidence/game_raw_dispatch_position_groups.md).
Two descriptor/attachment cores add 26 raw entries and 9,632 bytes; four
rendering/effect lifecycles add 64 entries and 19,088 bytes. Both complete
overlay gates pass. See the [descriptor/attachment cores](evidence/game_raw_descriptor_attachment_cores.md)
and [rendering/effect lifecycles](evidence/game_raw_render_effect_lifecycles.md).
Three clipping, resource and effect groups add 63 raw entries and 23,568
bytes, passing their first full-overlay gate. See the
[clipping/resource evidence](evidence/game_raw_clipping_resource_families.md).
Two particle/emitter groups add 20 raw entries and 10,992 bytes, passing
their first full-overlay gate. See the
[particle/emitter evidence](evidence/game_raw_particle_emitter_groups.md).
Two emission/descriptor groups add 41 raw entries and 24,896 bytes, passing
the first complete-overlay gate. The larger utility group has weaker historical
file-boundary certainty; see the [emission/descriptor evidence](evidence/game_raw_emission_descriptor_groups.md).
An owner/point-array lifecycle and a three-entry emission helper family add
17 raw entries and 8,288 bytes; both pass their first complete-overlay gate.
See the [owner lifecycle](evidence/game_raw_owner_point_lifecycle.md) and
[emission trio](evidence/game_raw_emission_trio.md).
Three state, resource and emission helper groups add 23 raw entries and
17,472 bytes, passing their first full-overlay gate. See the
[state/resource evidence](evidence/game_raw_state_resource_helpers.md).
Two narrowed view/resource cores add ten raw entries and 4,560 bytes,
passing their first full-overlay gate. See the
[view/resource evidence](evidence/game_raw_view_command_cores.md).
Two emission/owner-following particle cores add twelve raw entries and
4,528 bytes, passing their first full-overlay gate. See the
[owner/particle evidence](evidence/game_raw_owner_particle_cores.md).
The [ECTS layout correction](evidence/ects_game_layout.md) restores omitted
beta code and fixes research addresses using the beta ROM's own loader.
The trail source-family lead still lacks a sufficiently established retail
counterpart and receives no mapping credit.

## Current US integration

`lib/ultralib` is pinned to commit
`e24c836796df4bf520ff8b11a5c9d2cea3a66cbd` of decompals/ultralib. The US
profile links three trimmed archives built from that checkout:

- `libultra_2_0L`: 40 unique objects and 48 mapped sections.
- `libultra_2_0I`: 32 unique objects and 35 mapped sections.
- `libultra_2_0L_d`: three unique audio objects and four mapped sections.

The 2.0L survey covers 6,592 text bytes; see
[`evidence/libultra_us_2_0L_object_bounds.md`](evidence/libultra_us_2_0L_object_bounds.md).
The 2.0I survey covers `0x2DF0` (11,760) text bytes and 49 functions; see
[`evidence/libultra_us_2_0I_additional_object_bounds.md`](evidence/libultra_us_2_0I_additional_object_bounds.md).
The exhaustive I-L ROM/debug survey adds 272 standard audio text bytes; see
[`evidence/libultra_us_audio_object_bounds.md`](evidence/libultra_us_audio_object_bounds.md).
Those ranges are archive-owned and therefore no longer appear as generic
`src/libultra` source units or function work items.

`lib/libultrare` started with a bounded snapshot of eleven Rare-modified objects
from n64decomp/007 revision `c4356466796c697dfd298010b9bed261f9ed8c6a`
plus two Conker-specific VI objects and five initialized-data reconstruction
objects. Every complete object MD5 is checked before the archive is staged.
That initial snapshot contributes 26 mapped sections, covers `0x2230` (8,752) text
bytes, and owns 23 member functions. See
[`evidence/libultrare_us_additional_object_bounds.md`](evidence/libultrare_us_additional_object_bounds.md).
The VI-family and complete RSP blob/overlay boundaries are detailed in
[`evidence/libultra_us_vi_rsp_boundaries.md`](evidence/libultra_us_vi_rsp_boundaries.md).
The five standard initialized-data ranges are detailed in
[`evidence/libultra_us_data_object_bounds.md`](evidence/libultra_us_data_object_bounds.md).
These eighteen build objects likewise no longer have generic
`src/libultrare` work items.

The main profile additionally links 24 reconstructed Conker N-audio objects:
6,736 text bytes and 34 functions, plus two complete initialized/constant
sections. See
[`evidence/libultrare_us_naudio_variants.md`](evidence/libultrare_us_naudio_variants.md).
The source uses reviewed Conker layouts and behavior rather than presenting
near-matching Rare or Nintendo objects as exact stock output. Reconstructed
objects compiled with debug scheduling flags strip only non-runtime `.mdebug`
host/time metadata to make their full object checksums reproducible.

The active US main profile now links 144 unique library objects through
185 mapped sections: 140 CPU objects and four RSP payload members. The independently
generated US comparison map in `config/reference/us.yaml` remains raw assembly.
The complete rebuilt US ROM is byte-identical. EU/PAL mapping remains future
work.

The continued library-only pass adds eleven complete reconstructed objects:
11,552 text bytes, 34 functions, and five complete rodata sections. This
promotes the formerly raw `syncprintf`, synthesizer, and driver units, and
also reconstructs the main mixer, channel/effect controls, auxiliary mixer,
resampler, and per-voice filter. The shared audio views reproduce Conker's
expanded physical voices and linked auxiliary lists. See
[`evidence/libultrare_us_continued_reconstruction.md`](evidence/libultrare_us_continued_reconstruction.md)
for all object hashes, exact intervals, section ownership, and remaining leads.

A further five audio objects add 16,656 text bytes and 24 functions: decoder,
reverb, envelope, surround configuration, and compact-sequence parsing. Their
complete data, rodata, and BSS ownership is recorded in
[`evidence/libultrare_us_audio_engine_reconstruction.md`](evidence/libultrare_us_audio_engine_reconstruction.md).
The reverb and envelope jump tables use checked runtime-address relocation
preparation before the whole objects enter the main archive.

The following pass adds the seventeen sequence-player helpers and the
heap, bank-relocation, and oscillator families: four complete objects,
31 functions and 8,320 text bytes. The oscillator constants and 16-byte BSS
allocation are also mapped. See
[`evidence/libultrare_us_sequence_helper_reconstruction.md`](evidence/libultrare_us_sequence_helper_reconstruction.md).

The complete floating-point formatting unit `xldtob` now links from
`lib/libultrare`: three functions, 2,848 text bytes and 96 rodata bytes.
All three functions have zero-difference evidence, and the complete US ROM
remains byte-identical. The supported retirement command preserves the complete
C source in the archive tree and removes its duplicate source work items. See
[formatting evidence](evidence/libultrare_us_formatting_boundaries.md).
The MP3 bit/Huffman utilities are also reconstructed and linked. The preserved
power candidate and external workspace ownership remain unresolved library
work; the current follow-up maps game-overlay source families separately.

The residual I-L archive scan finds no distinctive complete loadable libultra
section in a raw US main range. The only residual exact-boundary result is an
indistinguishable 16-byte no-op/padding sequence at `0x39B0`, which has neither
a call site nor a ROM pointer reference. The audit method, source surveys, and
scope conclusion are recorded in
[`evidence/libultra_us_residual_boundary_audit.md`](evidence/libultra_us_residual_boundary_audit.md).

## US game-overlay libraries

The game map links 15 complete stock 2.0I objects (9,024 text bytes) and 20
Rare/Conker objects (38,768 text bytes). All 35 text mappings retain their raw
comparison counterparts. Complete game data/rodata/BSS bindings are recorded
in `config/game/us-sdk.ld`, including separate engine and tail helper targets.
The complete code payload remains byte-identical, and existing compressed
game-data allocations are preserved.

The boundary evidence is collected in:

- [`game_sdk_tail_text_bounds.md`](evidence/game_sdk_tail_text_bounds.md)
- [`game_sdk_additional_objects.md`](evidence/game_sdk_additional_objects.md)
- [`game_sdk_controller_objects.md`](evidence/game_sdk_controller_objects.md)
- [`game_sdk_mtxutil_variant.md`](evidence/game_sdk_mtxutil_variant.md)
- [`game_sdk_rotation_variant.md`](evidence/game_sdk_rotation_variant.md)
- [`game_sdk_trig_perspective_variants.md`](evidence/game_sdk_trig_perspective_variants.md)
- [`game_sdk_si_access_variant.md`](evidence/game_sdk_si_access_variant.md)

The main and game maps together account for 146,304 exact CPU library text bytes.
This counts each placement once; it is separate from registered handwritten C
function progress and from unverified source-boundary hypotheses.

The continued library-only search adds the audio engine and players, MP3 stream
and decoder, playback wrapper, exponential/logarithm helpers, and independently sourced MP3
assembly transforms and bit/Huffman utilities, plus both complete formatters.
Its 34 reviewed reconstruction objects contain 175 functions and 95,680 text bytes. This is a subset of the totals above, not an additional
amount. Detailed evidence is in the corresponding `libultrare_us_*` notes,
including [MP3 decoder](evidence/libultrare_us_mp3_decoder_reconstruction.md),
[math helpers](evidence/libultrare_us_math_helpers.md), and
[MP3 transforms](evidence/libultrare_us_mp3_transforms.md), and
[MP3 playback](evidence/libultrare_us_mp3_playback_reconstruction.md), and
[main formatter](evidence/libultrare_us_xprintf_reconstruction.md).

The separately assembled RSP boot and audio library adds 6,656 RSP code bytes
and 2,896 initialized data bytes. These stay outside CPU matching and the
historical code-coverage figures above. All four payloads and the complete US
ROM compare exactly; see [RSP evidence](evidence/libultra_us_vi_rsp_boundaries.md).

The MP3 utility now links as a complete Rare assembly member, adding five
functions and 1,152 text bytes after the approved table-access changes; see
[its object comparison](evidence/libultrare_us_mp3_util_boundaries.md).
Remaining library work includes the preserved non-exact power candidate under
`src/libultrare/gu/powf.c` and unresolved external workspace ownership.
The unchanged-template follow-up before MP3 utility integration scanned 6,018 stock/Rare object instances
against both CPU images and the separately compressed game-data image. It finds
no new distinctive text match. Further review rejects one of the three unique
scalar hits as a game callback-table tail; the other two still lack ownership
evidence. The [workspace review](evidence/libultrare_us_workspace_bounds.md)
bounds the MP3 stream and table views but leaves original BSS ownership open.
Four more compiler-mode trials did not improve the power candidate. See the
[residual audit](evidence/libultra_us_residual_boundary_audit.md) for corpus limits
and the subsequently approved MP3 integration. The current game-overlay work
registers reviewed raw-ASM source groups; it does not claim new C matches.

## Contributor commands

Build complete pinned stock archives for SDK-version research with:

```sh
./conker libultra
./conker libultra --version I
./conker libultra --version J
./conker libultra --version K
```

Build the bounded Rare snapshot and verify every object checksum with:

```sh
./conker libultrare
```

Assemble and verify every RSP library payload with:

```sh
./conker rsp
```

After building the I-L `libultra`, `libultra_d`, and `libultra_rom` research
targets, repeat the residual US main scan with:

```sh
./conker library-audit
```

Regenerate the raw target and validate the actual library integration with:

```sh
./conker _prepare-reference --profile us
./conker build --profile us
```

A candidate should move into a library archive only after its complete object
boundary, section ownership, symbols, and relocations are reviewed. Keep the
same range as raw assembly in `config/reference/us.yaml`; a relocation-masked
object resemblance is not a substitute for a byte-identical US rebuild.

Three slot, viewport and timed-controller groups add 21 raw entries and
4,144 bytes; see the [slot and controller evidence](evidence/game_raw_slot_view_controller_groups.md).
The full US overlay remains byte-identical.

Two animated-render and emission-controller groups add 16 raw entries and
7,856 bytes with a byte-identical US overlay; see the [lifecycle evidence](evidence/game_raw_animated_emission_controllers.md).

Two model-anchor and owner-callback cores add eight raw entries and 3,792
bytes with a byte-identical US overlay; see the [model and owner evidence](evidence/game_raw_model_anchor_owner_cores.md).

Sorted-record rendering and paired-object lifecycle groups add 25 raw entries
and 14,144 bytes with a byte-identical US overlay; see the [record and object evidence](evidence/game_raw_sorted_record_object_groups.md).

Composite emitters and a timed renderer add 31 raw entries and 11,952 bytes
with a byte-identical US overlay; see the [emitter and timer evidence](evidence/game_raw_composite_emitter_timed_groups.md).

Model lifecycle, owner effects and mode-dispatch cores add 16 raw entries
and 6,752 bytes with a byte-identical US overlay; see the [model and mode evidence](evidence/game_raw_model_owner_mode_cores.md).

An indexed controller and linked view worklist add 17 raw entries and 6,096
bytes with a byte-identical US overlay; see the [controller and worklist evidence](evidence/game_raw_indexed_controller_view_worklist.md).

Quad rendering and actor-state effects add 22 raw entries and 5,920 bytes
with a byte-identical US overlay; see the [quad and effect evidence](evidence/game_raw_quad_actor_effect_groups.md).

An owner-linked particle lifecycle and common effect dispatch engine add
24 raw entries and 6,864 bytes with a byte-identical US overlay; see the
[owner lifecycle](evidence/game_raw_owner_particle_lifecycle.md) and
[effect engine](evidence/game_raw_effect_dispatch_engine.md) evidence.

A slot controller and two attachment families add twenty raw entries and
6,832 bytes with a byte-identical US overlay; see the
[slot and attachment evidence](evidence/game_raw_slot_motion_attachment_groups.md).

Periodic-effect and actor-resource controllers add eighteen raw entries and
2,912 bytes with a byte-identical US overlay; see the
[periodic and resource evidence](evidence/game_raw_periodic_actor_resource_groups.md).

A record-backed command controller and resource-dependency core add twenty-two
raw entries and 5,904 bytes with a byte-identical US overlay; see the
[record controller](evidence/game_raw_record_command_controller.md) and
[dependency core](evidence/game_raw_resource_dependency_core.md) evidence.

Controller I/O and two renderer lifecycles add thirty-one raw entries and
11,216 bytes with a byte-identical US overlay; see the
[controller I/O](evidence/game_raw_controller_io_group.md) and
[path and owner lifecycles](evidence/game_raw_path_owner_lifecycles.md) evidence.

Two paired owner-effect families add twenty raw entries and 4,704 bytes
with a byte-identical US overlay; see the
[owner stream evidence](evidence/game_raw_paired_owner_streams.md).

- [Owner/audio effect family](evidence/game_raw_owner_audio_effect.md): 12 raw entries, 8,416 bytes.
- [Radial composite effect family](evidence/game_raw_radial_composite_effect.md): 14 raw entries, 10,256 bytes.

- [Rendering records, glyph pipeline and emitter pair](evidence/game_raw_record_glyph_emitter_groups.md): 14 raw entries, 11,728 bytes in three groups.
- [Model-backed debris family](evidence/game_raw_model_debris_family.md): nine raw entries, 10,272 bytes.

- [Actor-state and descriptor-emitter groups](evidence/game_raw_actor_classification_emitter.md): 14 raw entries, 8,512 bytes in two groups.

- [Audio-linked and owner emitter families](evidence/game_raw_audio_owner_emitters.md): 21 raw entries, 8,624 bytes in three groups.

- [Owner child-chain and resource emitters](evidence/game_raw_owner_chain_resource_emitters.md): 13 raw entries, 4,992 bytes in two groups.
- [Parametric element system](evidence/game_raw_parametric_elements.md): 11 raw entries, 5,008 bytes.

- [Secondary particle and stream families](evidence/game_raw_secondary_stream_families.md): 19 raw entries, 6,240 bytes in four groups.

- [Display-object and transition groups](evidence/game_raw_display_transition_groups.md): 16 raw entries, 6,624 bytes in three groups.
- [Buffered effect and stream groups](evidence/game_raw_buffer_stream_families.md): seven raw entries, 2,128 bytes in two groups.

- [Radial and particle composite family](evidence/game_raw_radial_particle_composite.md): six raw entries, 3,600 bytes.

- [Child-chain, emission-chain and render lists](evidence/game_raw_child_chain_render_lists.md): 26 raw entries, 8,768 bytes in three groups.

- [Type-4B display and framebuffer groups](evidence/game_raw_type4b_framebuffer_groups.md): 10 raw entries, 6,112 bytes in two groups.
- [Narrow effect and record cores](evidence/game_raw_narrow_effect_record_cores.md): nine raw entries, 3,040 bytes in three groups.

- [Scene setup, emission and controller groups](evidence/game_raw_scene_setup_emission_controller.md): 16 raw entries, 8,624 bytes in five groups.

- [Loader, transfer and emission groups](evidence/game_raw_loader_transfer_emission_groups.md): 13 raw entries, 8,800 bytes in five groups.

- [Resource parser, actor state and dispatch groups](evidence/game_raw_parser_actor_state_groups.md): 23 raw entries, 18,224 bytes in nine groups.

- [Radial effects, timed queue and render objects](evidence/game_raw_radial_queue_render_groups.md): 18 raw entries, 9,248 bytes in five groups.

- [Compact display objects and resource pairs](evidence/game_raw_compact_display_resource_pairs.md): 16 raw entries, 10,304 bytes in seven groups.

- [Selected particle and resource families](evidence/game_raw_selected_particle_resource_groups.md): 12 raw entries, 3,280 bytes in five groups; one ambiguous boundary was withdrawn.
- [Descriptor callback families](evidence/game_raw_descriptor_callback_families.md): 27 raw entries, 27,856 bytes in ten groups.
- [Descriptor records, actor state and rendering pair](evidence/game_raw_record_transform_state_groups.md): nine raw entries, 2,208 bytes in three groups.
- [Timed actor-emitter family](evidence/game_raw_timed_actor_emitter.md): two raw entries, 1,296 bytes.

The usage-bounded continuation adds 140 reviewed raw working units, 394 entries
and 138,272 bytes. Every accepted batch passed the complete US game-overlay comparison:

- [Internal-call and callback clusters](evidence/game_raw_internal_call_callback_clusters.md) and [direct helper pairs](evidence/game_raw_direct_helper_pairs.md): 26 groups, 66 entries and 22,800 bytes.
- [Callback-table runs](evidence/game_raw_callback_table_runs.md), [complete callback clusters](evidence/game_raw_complete_callback_clusters.md) and [table-selected collections](evidence/game_raw_table_selected_collections.md): 24 groups, 135 entries and 42,400 bytes.
- [Pointer-selected subranges](evidence/game_raw_pointer_selected_subranges.md) and [pointer-table runs](evidence/game_raw_pointer_table_runs.md): 34 groups, 137 entries and 46,752 bytes.
- [Pointer-selected singletons](evidence/game_raw_pointer_singletons.md), [continued singletons](evidence/game_raw_pointer_singletons_continued.md) and [final singletons](evidence/game_raw_pointer_singletons_final.md): 56 minimal working units and 26,320 bytes; the existing named `game_3BFD0` raw split was reviewed and withdrawn.

The [search report ending at 23:30 Brisbane](evidence/game_mapping_search_2026_09_03_2330.md) records this pass and remaining leads.
The [usage-bounded continuation report](evidence/game_mapping_search_until_3_percent.md) records the later pointer and call evidence, exclusions and final coverage.
The [mapping completion record](evidence/game_mapping_residual_frontier.md)
documents the final text-resident data classification and exact Rare EEPROM
objects. The canonical US game-overlay map now has 100% byte ownership and no
raw `asm`/`hasm` subsegment entries.
