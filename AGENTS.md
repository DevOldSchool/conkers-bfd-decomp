# Conker decompilation workflow

Use `./conker` from the repository root. It is the supported interface for
Docker, ROM setup, progress, m2c, and asm diffs.

## Small-agent fast path

For ordinary source-local function work, follow this exact loop:

1. Read `CONTRIBUTING.md` once at the start of the task, then run
   `git status --short` once and record all pre-existing changes. Do not reread
   the guide for consecutive functions in the same task unless it changed.
2. `next --ready` is Docker-backed. In a managed sandbox, request Docker
   permission on the first `./conker next --ready` call. Run it once; do not
   separately run `next`, `m2c`, `doctor`, or print the work queue.
3. Treat the emitted `allowed-edit`, `target-file-dirty`,
   `source-unit-state`, and `post-match-action` fields as authoritative. If the
   allowed source has unrelated or overlapping edits whose ownership is
   unclear, stop and report `blocked` without changing it.
4. If the output says `issue: none recorded`, do not access GitHub.
5. Inspect only the declarations printed by `next --ready`, the allowed source,
   existing declarations in `src/` and `include/`, and the emitted bounded raw
   US call sites. Perform at most one additional batched lookup before the
   first candidate unless a compiler error names a missing declaration.
6. Never paste `M2C_FIELD` or `M2C_UNK` into project source. Use the canonical
   scalar aliases from `types.h`, then prefer an existing project structure. If
   none exists, use a typed pointer for one naturally aligned field or a
   source-local partial structure with explicit padding for several fields.
   Values stored with `sb` or `sh` remain `s32` parameters unless an existing declaration proves
   otherwise. Do not change a shared header merely to type one function.
   Copy every concrete C declaration under `required-declarations` that is not
   already available in the allowed source or its headers before the first
   `finish` attempt. Resolve `M2C_UNK` declaration hints from existing project
   declarations instead of copying that placeholder type.
7. Replace only the target `GLOBAL_ASM` pragma, at the same position, then run
   `./conker finish <work-item-id>` immediately after the first reasonable C
   candidate.
8. On `AGENT_ACTION: STOP_MATCHED`, follow the previously emitted
   `post-match-action`: stop when it is `stop`, or run integration when it is
   `integrate`. Do not repeat `progress match` or progress rendering.
9. On `AGENT_ACTION: FIX_COMPILE`, correct only the reported C/declaration
   problem and rerun `finish`; do not start a diff watcher until the candidate
   compiles.
10. On `AGENT_ACTION: CONTINUE_MISMATCH`, try at most three source-only
    expression or declaration variants. Use `diff --watch` only when both stdin
    and stdout are attached to an interactive terminal; otherwise edit and
    rerun `finish`. Never alter assembly, inventory JSON, compiler flags, or
    shared tooling. If still unmatched, report `candidate`. When the user
    explicitly authorizes moving past it, run
    `./conker defer <work-item-id> --reason <text>`; this preserves the current C
    under a disabled source block, restores the exact `GLOBAL_ASM` pragma, and
    removes the item from automatic selection. Use
    `./conker resume <work-item-id>` to restore that candidate before trying it
    again.
11. On `AGENT_ACTION: FIX_INTEGRATION`, correct the source/layout problem before
    running any batch command again. On `AGENT_ACTION: BLOCKED_TOOLING`, or when
    required declarations are unavailable or a match would require unapproved
    shared changes, stop and report `blocked`. Terminal actions are
    authoritative even when a surrounding tool or terminal session also ends.
12. Do not run the batch gate for one source-local match. After the final
    function in a requested group, run `./conker verify-batch <id> [<id>...]`
    exactly once. Never rerun an unchanged failed batch; the command records a
    clean integration failure and rejects an identical retry.
    `AGENT_ACTION: BATCH_COMPLETE` is the successful terminal state.

Feedback budget: send one brief start update, then speak only for a failure,
blocker, or command that runs longer than 60 seconds before the final report.
Do not narrate successful selection, edits, or per-function matches. This keeps
user feedback useful without adding avoidable agent/tool round trips.

Use this exact report shape:

```text
Function/source:
Changed files:
Shared dependency required: yes/no
US focused diff:
Whitespace:
Status: matched/candidate/blocked
Attempts:
```

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

1. Read `CONTRIBUTING.md`, then use `./conker next --ready` to select one item,
   prewarm the repository toolchain, and obtain its inventory, source, generated
   assembly, issue metadata, nearby declarations, and m2c C starter in one
   bounded call. Read and claim a related issue only when that output records
   one; `issue: none recorded` means do not query GitHub. Read any additional
   applicable source/header declarations.
2. Work in an isolated Git worktree. Do not share a checkout with another
   implementation agent unless the user explicitly directs you to work on their
   current local branch; in that case preserve all unrelated staged and unstaged
   changes.
3. Use the m2c output from `next --ready` only as a C starting point. The
   standalone `./conker m2c <work-item-id>` command remains available when a
   specific item is already selected; add `--profile <region>` only when
   intentionally overriding the default US profile. Replace guessed types and
   offsets with project declarations.
4. Make small changes, then run `./conker finish <work-item-id>` to record an
   exact match and perform the progress and whitespace gates in one call. In a
   reviewed mixed unit,
   replace only the target function's generated `GLOBAL_ASM` pragma with C at
   the same position. Do not edit target assembly, hand-write assembly bodies,
   or add inline asm.
   On a mismatch, `finish` prints the normal focused diff and leaves the
   inventory unchanged. On `CURRENT (0)`, the same compilation records the match
   and regenerates progress before checking generated output and whitespace; do
   not repeat it with `progress match`.
   Use `./conker diff --watch <work-item-id>` for the persistent edit loop when
   interactive terminal access is available, then exit the watcher and run
   `finish` once for authoritative evidence and the per-function gate.
5. After `finish` reports and records `CURRENT (0)`, do not edit the
   inventory JSON manually. A reviewed boundary may integrate immediately as
   mixed C/ASM; run integration again to move it to `src/game/done/` only after
   every function matches. If integration runs after `finish`, rerun the progress
   and whitespace checks because integration changes repository state.

## Fast tool usage

- Batch independent read-only discovery commands into one tool call. Use
  `next --ready` and `finish` instead of separate selection/m2c and
  diff/progress/whitespace calls. Do not
  print the full work queue when selecting one item, scan broad generated trees,
  or repeat local context already emitted by `next --ready`.
- Docker-backed commands are `doctor`, `build`, `m2c` on a cold host cache,
  `diff`, `progress match`, `progress integrate`, and game build/reference
  commands. In a managed sandbox that cannot access the Docker socket, request
  the required Docker permission on the first such command instead of first
  running a known-to-fail sandboxed attempt.
- Keep the repository-scoped warm container alive across consecutive functions
  and follow-up agent turns. Do not run `./conker stop` merely because one
  function finished; use it only when the user requests cleanup or the broader
  contribution is finished with no likely follow-up work.
- `./conker progress match <work-item-id>` and `diff --record` remain
  compatibility paths for automated or focused callers. New agent work should
  use `finish` so a successful focused diff is compiled once and the remaining
  per-function gates share the same tool call.
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
