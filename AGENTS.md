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

1. Read `CONTRIBUTING.md`, then use `./conker next --one --details` to select
   one item and obtain its inventory, source, generated assembly, issue metadata,
   and nearby declarations in one bounded local call. Read and claim a related
   issue only when that output records one; `issue: none recorded` means do not
   query GitHub. Read any additional applicable source/header declarations.
2. Work in an isolated Git worktree. Do not share a checkout with another
   implementation agent unless the user explicitly directs you to work on their
   current local branch; in that case preserve all unrelated staged and unstaged
   changes.
3. Use `./conker m2c <work-item-id>` only as a C starting point; add `--profile
   <region>` only when intentionally overriding the default US profile. Replace
   guessed types and offsets with project declarations.
4. Make small changes, run `./conker diff --record <work-item-id>`, and preserve
   the exact target instruction/register output. In a reviewed mixed unit,
   replace only the target function's generated `GLOBAL_ASM` pragma with C at
   the same position. Do not edit target assembly, hand-write assembly bodies,
   or add inline asm.
   On a mismatch, `diff --record` prints the normal focused diff and leaves the
   inventory unchanged. On `CURRENT (0)`, the same compilation records the match
   and regenerates progress; do not repeat it with `progress match`.
   Use `./conker diff --watch <work-item-id>` for the persistent edit loop when
   interactive terminal access is available, then exit the watcher and run
   `diff --record` once for authoritative evidence.
5. After `diff --record` reports and records `CURRENT (0)`, do not edit the
   inventory JSON manually. A reviewed boundary may integrate immediately as
   mixed C/ASM; run integration again to move it to `src/game/done/` only after
   every function matches. Then run the progress and whitespace checks.

## Fast tool usage

- Batch independent read-only discovery commands into one tool call. Do not
  print the full work queue when selecting one item, scan broad generated trees,
  or repeat local context already emitted by `next --one --details`.
- Docker-backed commands are `doctor`, `build`, `m2c` on a cold host cache,
  `diff`, `progress match`, `progress integrate`, and game build/reference
  commands. In a managed sandbox that cannot access the Docker socket, request
  the required Docker permission on the first such command instead of first
  running a known-to-fail sandboxed attempt.
- Keep the repository-scoped warm container alive during a function or
  same-source work session. Use `./conker stop` only when the session is finished
  or the user requests cleanup.
- `./conker progress match <work-item-id>` remains a compatibility alias for
  automated callers. New agent work should use `diff --record` so a successful
  focused diff is not compiled a second time.
- Follow the per-function gate in `CONTRIBUTING.md`; do not run full builds or
  the full test suite after a small source-local match unless shared tooling,
  headers, configuration, or source-unit integration changed.

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
