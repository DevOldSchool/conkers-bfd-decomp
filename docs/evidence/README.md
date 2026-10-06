# Research evidence

These records preserve scoped claims, inputs, rejected hypotheses and validation
results. Dates, counts, branches and tool versions describe the recorded pass.
Read later corrections before treating an old result as current.

Use the [documentation index](../README.md) for operating instructions.
[Function inventory](../../progress/functions.json) owns match state;
[source-unit inventory](../../progress/source_units.json) owns boundaries and
integration. [Generated progress](../progress.md) reports those inventories.
Evidence alone does not mark work complete.

## Browse by topic

Each topic index lists every record and its supporting data. Filenames retain
their existing identity so symbols, old notes and Git history remain searchable.

| Topic | Start here |
| --- | --- |
| [Source boundaries](boundaries/README.md) | [Game mapping](boundaries/game/mapping/game_mapping_residual_frontier.md), [main frontier](boundaries/main/main_boundary_residual_frontier.md), named effects |
| [Libraries](libraries/README.md) | [2.0G reclassification](libraries/libultra_2_0G_rare_reclassification.md), SDK objects and Rare reconstruction |
| [Function matching](matching/README.md) | [Conversion audit](matching/matching_conversion_audit.md), ABI/storage contracts and candidate investigations |
| [Data and section layout](data-layout/README.md) | Jump tables, literal pools, private data and integration proposals |
| [Models and scenes](assets/models/README.md) | [Reference corrections](assets/models/us_model_reference_corrections.md), geometry, pose, placement and validation |
| [Materials and render state](assets/materials/README.md) | [Material frontier](assets/materials/us_model_material_frontier.md), texture formats and consumer state |
| [Semantic naming](assets/naming/README.md) | [Confidence contract](assets/naming/model_name_confidence_review.md), character, prop and resource descriptions |
| [Audio](assets/audio/README.md) | Audio formats, soundtrack fidelity and album correspondence |
| [Interface and fonts](assets/interface/README.md) | Glyph/HUD resources and reference coverage |
| [Debugger](debugger/README.md) | Retail overlay, debug metadata and storage/section evidence |
| [Cross-version research](beta/README.md) | ECTS layout and pointers to regional comparisons |

The [asset roadmap](../asset-roadmap.md) owns the dated asset-status summary.
Local coverage, batch and validation reports reflect their supplied inputs.
Historical reports are not fresh verification of the checkout.

## Find a specific claim

For a source unit, follow its evidence comment or inventory reference first.
Search recursively by symbol, source filename, ROM address, model identity or
format term:

```sh
rg -n 'func_1504BC38' docs/evidence
rg -n 'game_200930|09:0110:00' docs/evidence
rg --files docs/evidence | rg 'game_raw_resource|texture'
```

The original range-specific proofs remain authoritative for their individual
claims; topic indexes do not replace them. A filename containing `raw`,
`candidate` or `final` describes its research context, not current project state.

## Maintaining the collection

- File a new claim in the narrowest existing topic and link it from that topic's
  README. Keep companion JSON and patches beside the record they support.
- Extend an existing record for the same claim. Prefer a stable subject name over
  new `continued`, `final` or session-date documents. Preserve rejected hypotheses
  and explain which later evidence supersedes an earlier conclusion.
- Keep reproducible inputs, results and limitations in evidence. Put reusable
  commands in the owning guide and task progress/retry logs in local
  [attempt ledgers](../decompilation-workflow.md#durable-manual-attempt-ledger).
- Treat source comments, manifests and canonical inventories as incoming
  references. Move referenced evidence through the relocation command below;
  do not hand-edit inventory state or leave placeholder copies at old paths.

### Moving referenced evidence

Prepare a JSON object mapping old repository-relative paths to new paths within
`docs/evidence/`. Preview the affected-file count, then apply the reviewed map:

```sh
./conker relocate-evidence --map /tmp/evidence-moves.json
./conker relocate-evidence --map /tmp/evidence-moves.json --apply
./conker progress check
build/host-python/bin/python3 -m unittest discover -s tests
git -c core.whitespace=cr-at-eol diff --check
```

The command moves tracked UTF-8 evidence, rebases relative Markdown links and
updates exact repository paths in tracked source, configuration and inventories.
It rejects collisions and unsafe paths, and restores the original files on a
handled failure. It changes references only, not match states, scores or
integration decisions. Review the diff and local links afterward; Git history,
external bookmarks and ignored local reports are outside the migration.

Path changes can also invalidate pinned metadata. If the model-name registry
changes, verify that only evidence paths moved, then refresh its byte pin, the
confidence sidecar's record bindings and the sidecar byte pin as required by the
[naming evidence contract](assets/naming/model_name_confidence_review.md).
The relocation command does not refresh those pins automatically. Run the full
Python suite above (after `./conker host-setup`) before publishing the migration.
