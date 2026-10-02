# Research evidence

These records preserve scoped claims, inputs, rejected hypotheses and validation
results. Dates, counts, branches and tool versions describe each recorded pass;
read later corrections before treating an old result as current. This is a
curated starting point, not a catalogue of every function or format.

For operating instructions, start at the [documentation index](../README.md).
[Function inventory](../../progress/functions.json) owns match state;
[source-unit inventory](../../progress/source_units.json) owns reviewed boundaries
and integration. [Generated progress](../progress.md) reports those inventories.
The [asset roadmap](../asset-roadmap.md) owns the dated asset-status summary;
local coverage, batch and validation reports reflect their supplied inputs.
Evidence alone does not mark work complete, and a historical report is not a
fresh verification of the current checkout.

## Function matching and source boundaries

- [Main boundary frontier](main_boundary_residual_frontier.md) identifies reviewed
  ownership, unresolved spans and the evidence needed to reopen them.
- [Game mapping completion](game_mapping_residual_frontier.md) records source and
  section ownership, separately from conversion to matching C.
- [Main beta comparison](main_boundary_beta_comparison.md) and
  [ECTS layout](ects_game_layout.md) explain bounded cross-version evidence;
  [beta research rules](../beta-evidence.md) keep correlations separate from US proof.
- [Blocked-function recovery](blocked_function_recovery.md) records declaration
  corrections; [switch recovery](blocked_switch_jump_tables.md) and
  [manual-batch jump tables](manual_batch_jump_tables.md) preserve layout/data proofs.
- [Conversion audit](matching_conversion_audit.md) separates measured matching
  outcomes from candidate attempts, rechecks and unmeasured efficiency claims.
- [Effect record extents](effect_record_extents.md) preserves consumer-proven
  copy sizes, enclosing layouts and caller copy order.

For a particular source unit, follow its evidence comment or inventory reference
first. The many `game_raw_*`, `game_*` and `main_*` records retain the original
range-specific reasoning; no umbrella summary replaces those boundary proofs.

## Libraries and original assembly

- [2.0G reclassification](libultra_2_0G_rare_reclassification.md) distinguishes stock
  SDK objects from the earlier Rare mappings using complete-section evidence.
- [Residual library audit](libultra_us_residual_boundary_audit.md) records bounded
  template scans and links to subsequent reconstruction work.
- [Continued Rare reconstruction](libultrare_us_continued_reconstruction.md) is an
  entry point for the audio/library object proofs and their remaining limits.
- [Workspace bounds](libultrare_us_workspace_bounds.md) separates used runtime
  storage from unproven original BSS ownership.
- [Original-assembly verification](main_original_assembly_verification.md) and
  [RSP boundaries](libultra_us_vi_rsp_boundaries.md) preserve toolchain and image
  proof; verified assembly does not earn C matching credit.

Use [the library guide](../library-track.md) for integration commands and current
boundary context; historical object counts are not interchangeable with progress.

## Models, materials and runtime state

- [Asset inventory survey](us_asset_inventory.md) preserves storage, model-format,
  animation, collision and captured-corpus discovery evidence.
- [Reference corrections](us_model_reference_corrections.md) explains texture-ID,
  composition and runtime-replay corrections that supersede earlier assumptions.
- [Batch validation](us_model_batch_validation.md), [coverage](us_model_coverage.md)
  and [evidence audits](us_model_evidence_audits.md) define what each check proves.
- [ROM character defaults](us_rom_character_defaults.md),
  [draw tables](us_character_draw_tables.md) and
  [vertex-load matrices](us_character_vertex_load_matrices.md) establish character
  selection, material and transform contracts.
- [Scene consumers](us_model_scene_consumers.md) and
  [static assemblies](us_static_scene_assemblies.md) connect source records to
  placement and selection evidence; [review selections](us_model_review_selections.md)
  record inspection choices without asserting native appearance.
- [Material frontier](us_model_material_frontier.md),
  [constructor tables](us_model_constructor_tables.md) and
  [character alpha frontier](us_character_alpha_frontier.md) identify missing
  consumer/state proof and already-bounded searches.
- [Submitted poses](us_submitted_model_poses.md) joins geometry, pose and materials
  to one captured graphics task. [Event activation](us_model_event_activation.md)
  records bounded static creation/script requests without proving execution.
  [Runtime tracing](../runtime-tracing.md) supplies the capture workflow.

A decoded image, successful import, active actor or bounded negative trace proves
only its stated scope. See [model appearance extraction](../model-appearance.md)
for supported presets and the separation between ROM facts and captured state.

## Other assets and debugger research

- [Non-MP3 audio](us_non_mp3_audio_assets.md) and [MP3 cues](us_mp3_cue_assets.md)
  preserve loader, encoding and preview contracts without inventing names or speech semantics.
- [Font atlas](us_font_atlas.md), [HUD/menu assets](us_hud_menu_assets.md) and
  [interface reference review](us_interface_reference_review.md) separate exact
  resources from visual labels and reference coverage.
- [Retail debugger overlay](us_debugger_overlay.md) and
  [debug metadata](us_retail_debug_metadata.md) distinguish verified image/string
  evidence from provisional source ownership and unresolved runtime storage.

## Find a specific claim

Search from the repository root by exact symbol, source filename, ROM address,
model identity or format term; follow the cited inputs and later corrections:

```sh
rg -n 'func_1504BC38' docs/evidence
rg -n 'game_200930|09:0110:00' docs/evidence
```

Keep evidence filenames and paths referenced by source or metadata stable.
Document technical claims, their reproducible evidence and limitations. Keep
per-task progress, retry logs and candidate snapshots in local
[attempt ledgers](../decompilation-workflow.md#durable-manual-attempt-ledger),
not continuation documents. Add scoped corrections to the relevant topic and keep
reusable command procedures in the owning guide.
