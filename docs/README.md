# Documentation

This index separates newcomer setup, contribution rules, operational workflows,
asset research, and historical evidence. Start with the shortest guide that
matches the work you intend to do.

## Getting started

- [Project overview and quick start](../README.md) introduces the active target
  and the minimum local setup.
- [Contributing](../CONTRIBUTING.md) defines the clean-room, review, and
  verification requirements for accepted changes.
- [Clean-room bootstrap](bootstrap.md) documents ROM validation, the raw
  byte-identical baseline, and the active and future regional profiles.
- [Cloud matching and reset recovery](cloud-matching.md) gives dot and other
  contributors a reproducible cloud setup, isolated parallel workflow, and
  verified checkpoint/push procedure.
- [Continuous integration](ci.md) explains public checks and protected
  full-ROM verification.

## Code decompilation

- [Decompilation workflow](decompilation-workflow.md) is the command guide for
  selecting functions, producing C candidates, running focused diffs,
  registering source units, integrating them, and verifying a batch.
- [Runtime tracing](runtime-tracing.md) covers the pinned Mupen64Plus debugger
  used when static code or display-list evidence cannot identify a consumer.
- [Library track](library-track.md) records Nintendo 64 library boundary work,
  archive integration, and the associated commands.
- [Decompilation progress](progress.md) is generated from the canonical
  inventories and contains the current regional, executable-area, and
  source-unit totals.

## Assets and research

- [RZIP and asset extraction](rzip-assets.md) documents the ROM asset layout,
  extraction commands, proven audio, texture, interface, and model formats, and
  their evidence boundaries.
- [Model appearance extraction](model-appearance.md) covers guarded ROM materials,
  explicit capture-scoped presets, diagnostics, coverage and their proof limits.
- [Resumable model batches](model-batches.md) coordinates corpus refresh, review
  and current blocker reporting.
- [Future asset editing and recomp integration](asset-editing.md) describes the
  reversible editing commands and what can or cannot yet be inserted safely.
- [Asset extraction roadmap](asset-roadmap.md) tracks completed format work and
  the unresolved research frontier.
- [Retail debugger overlay](evidence/us_debugger_overlay.md) records the
  loader-proven US image, provisional C bases, and unresolved runtime storage.
- [Beta evidence](beta-evidence.md) explains how debug and ECTS material may be
  used without treating it as US match or source-boundary proof.

## Sources of truth

- `progress/functions.json` is the canonical function-match inventory.
- `progress/source_units.json` records reviewed source boundaries and
  integration state.
- `docs/progress.md` and the progress badges are generated; do not edit them
  manually.
- `docs/evidence/` contains scoped research records. Evidence documents support
  a claim but do not themselves mark a function or source unit complete.
- Generated assembly, extracted assets, and build products are ignored local
  output and are not completion markers.

Use the supported `./conker` commands for inventory and generated-document
changes instead of editing generated files or canonical JSON by hand.
