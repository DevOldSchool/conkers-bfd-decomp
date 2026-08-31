# Conker decompilation workflow

Use `./conker` from the repository root. It is the supported interface for
Docker, ROM setup, progress, m2c, and asm diffs.

## Source of truth

- `progress/functions.json` is the canonical instruction-match inventory.
- `progress/source_units.json` tracks C-file boundaries and whether a unit is
  safely integrated into the full-ROM link. A matched function alone does not
  make its source unit complete.
- `docs/progress.md` and `progress/summary.json` are generated; update them
  with `./conker progress render`.
- Generated `asm/` is ignored reference output, not a completion marker.
- The generated game comparison map must remain raw assembly even when the
  canonical game build maps that range to mixed or completed C. Never diff a C
  candidate against an object built from the same C source.
- The active target is US. A function is matched when its US entry has
  zero-difference evidence. EU/PAL is a preserved future goal and does not gate
  progress or completion.
- Each present regional record holds its exact symbol and VRAM; the outer symbol
  is the shared work-item ID used by the public m2c and diff commands.
- A function record's optional `overlay` is `main` by default. `./conker m2c`
  and `./conker diff` resolve main versus game-overlay work automatically.
- `./conker game-index` proposes US game-overlay functions. It is a review aid
  only. Use `./conker register-game` with an explicitly reviewed US function to
  create a `raw_asm` work item without claiming a source-unit boundary. Use
  `./conker register-source-unit` separately only after recording reviewed
  boundary evidence and registering every function in that range.

## Agent procedure

1. Read `CONTRIBUTING.md`, the function's issue, its inventory record, and the
   applicable source/header declarations.
2. Work in an isolated Git worktree. Do not share a checkout with another
   implementation agent.
3. Use `./conker m2c <work-item-id>` only as a C starting point; add `--profile
   <region>` only when intentionally overriding the default US profile. Replace
   guessed types and offsets with project declarations.
4. Make small changes, run the US focused diff, and preserve the exact target
   instruction/register output. In a reviewed mixed unit, replace only the
   target function's generated `GLOBAL_ASM` pragma with C at the same position.
   Do not edit target assembly, hand-write assembly bodies, or add inline asm.
   Use `./conker diff --watch <work-item-id>` for the persistent
   edit loop when interactive terminal access is available.
5. After the US result is `CURRENT (0)`, run `./conker progress match
   <work-item-id>` to verify and update the function record plus any separately
   assigned source unit. Do not edit the inventory JSON manually. A reviewed
   boundary may integrate immediately as mixed C/ASM; run integration again to
   move it to `src/game/done/` only after every function matches. Then run the
   progress and whitespace checks.

Every agent report must state the function/source, changed files, shared
dependency requirement, US build/diff result, whitespace result, and status
(`matched`, `candidate`, or `blocked`).

`m2c` and `diff` resolve the registered overlay automatically. For game work,
`m2c` first reuses existing ROM-derived assembly under
`reference/game/<profile>/asm/`, then a validated raw per-function block under
`asm/nonmatchings/`; it prepares the full game reference only when neither is
available. They do not run `clean` or refresh `asm/<profile>/`.
Run `./conker build --all` separately when checking the complete raw baselines.

The legacy game-overlay aliases remain available for compatibility:

```sh
./conker game-m2c <work-item-id> > /tmp/<work-item-id>.c
./conker game-diff <work-item-id>
```
