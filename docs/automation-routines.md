# Unattended matching rounds

Scheduled Claude Code routines keep function matching moving without a
maintainer in the loop. Each round runs on the maintainer's machine through the
desktop app's bridge environment, because matching needs the private US ROM,
Docker and the pinned IDO image; public CI never sees a ROM. The driver is
[`scripts/auto_round.sh`](../scripts/auto_round.sh); the merge policy is
[`scripts/auto_policy.py`](../scripts/auto_policy.py). Ordinary matching rules
are unchanged: [AGENTS.md](../AGENTS.md), [CONTRIBUTING.md](../CONTRIBUTING.md)
and the [workflow reference](decompilation-workflow.md) still govern every edit.

## Shape of a round

1. **Lock.** `auto_round.sh start` refuses to run when another round holds the
   lock or any `conker-toolchain-*` container is using CPU, so rounds never
   compete with a maintainer's or Codex's session. A lock older than its
   deadline plus 90 minutes is reclaimed and its worktree removed. The lock
   lives in `~/.conker-auto/lock`; `caffeinate -i` keeps the Mac awake for the
   budget.
2. **Worktree.** A fresh `../conker-auto/<stamp>` worktree on branch
   `auto/match-<stamp>` from `origin/main`, with submodules, a real ROM copy,
   a link to the main checkout's `build/host-python` (from `./conker host-setup`)
   and the US reference split prepared. Matching history saved by earlier
   rounds in `~/.conker-auto/history/` (one `matching-history export` bundle per
   function) is imported, so `next` prints what was already tried.
3. **Review pending PRs.** `auto_round.sh review-pending` re-verifies every open
   `auto-match` PR that has no verdict yet (see below) and merges the ones that
   pass. The reviewing session is never the session that produced the PR.
4. **Match** under the normal rules for the remaining budget
   (`auto_round.sh remaining` prints the minutes left). Exact matches only: the
   round does not `defer`, promote types, edit headers or touch build inputs
   other than added `config/game/us-rodata.ld` literal and jump-table mappings
   with their `config/data/us.json` owner records and `docs/evidence/data-layout/`
   notes (the merge policy accepts those). It may run one `permute --budget 32` per
   distinct candidate when the latest diagnosis is register-only. Near misses
   and dead ends go to matching history, not the PR. A function blocked by
   something the round may not change (a shared header or prototype, a rodata
   mapping, a function boundary, tooling or reference symbolisation) gets one
   line under "Needs a maintainer" in the PR body, and the function is restored.
5. **Batch, commit, PR.** `./conker verify-batch <ids>` must print
   `AGENT_ACTION: BATCH_COMPLETE`; `auto_round.sh commit` uses the agent
   identity; `auto_round.sh open-pr --ids "<ids>"` pushes and labels the PR
   `auto-match`. The driver appends the machine-readable line
   `Auto-match IDs: <ids>` that the reviewer reads, replacing any copy already
   in the body file. A round with no match opens
   no PR. The driver finds the ROM in the main checkout's `roms/` directory
   (`CONKER_AUTO_ROM` overrides it), so it may run from any linked worktree.
6. **Cleanup.** `auto_round.sh cleanup` saves the worktree's matching history
   to `~/.conker-auto/history/`, stops the container, removes the
   worktree and its local branch, deletes any other local `auto/match-*`
   branch that is merged into main or gone upstream, and releases the lock.
   It runs even after a failed round. The merge step deletes the remote
   branch; a PR merged by hand should use `--delete-branch` too.

## Review and merge

`auto_round.sh review <pr>` is an independent re-verification in its own
worktree of the PR head (after `gh pr update-branch` when the branch is behind
main):

| Gate | Requirement |
| --- | --- |
| Policy | `auto_policy.py` passes (below) |
| Per function | `./conker finish <id>` prints `AGENT_ACTION: STOP_MATCHED` for every claimed ID |
| Batch | `./conker verify-batch <ids>` prints `AGENT_ACTION: BATCH_COMPLETE` |
| Public checks | GitHub reports the PR mergeable (`CLEAN`): every public check green; up to 60 minutes wait, a failed or cancelled check stops |
| Base | the branch is up to date with main at merge time (`BEHIND` updates the branch and requeues it for the next round) |

`CONKER_AUTO_NO_MERGE=1` makes `review` and `review-pending` verify and label
without merging, for dry runs.

A pass posts the report, adds `auto-verified` and merges with a merge commit
(`gh pr merge --merge --delete-branch`), matching the repository's history. Any
failure posts the report, adds `needs-human` and stops; automation never
touches a `needs-human` PR again. If main moves while checks run, the branch is
updated, `auto-verified` is removed and the next round re-verifies it.

The reviewer's local evidence is the pre-merge US verification that
[CI and review policy](ci.md) asks a maintainer for; the post-merge ROM
workflow still needs its environment approval.

### Merge policy

`auto_policy.py --repo <worktree> --base origin/main --head HEAD --ids <ids>`
reads only Git and fails on any of these:

- A changed path outside `src/**/*.c`, `progress/functions.json`,
  `progress/source_units.json`, `docs/evidence/`, `config/game/us.yaml`,
  `config/game/us-rodata.ld` or `config/data/us.json`. Headers, `include/`, `Makefile`, `scripts/`,
  `tests/`, `toolchain/`, `.github/` and `config/` otherwise all stop automation.
- `config/game/us.yaml` with any change other than a completed unit's segment
  row moving from `game/<unit>` to `done/game/<unit>` (what
  `progress integrate` writes).
- Any deleted file. Moving a completed unit into `src/done/` is a rename and is
  allowed.
- `config/game/us-rodata.ld` with removed lines; literal and jump-table
  mappings may only be added.
- `config/data/us.json` with anything but new `.rodata` owner records whose
  `owner.sources` are units the PR changes (in either their `src/game/` or
  `src/done/game/` form). Existing records must be unchanged.
- Added C lines containing a forced-match construct (`if (1) {}`, `^ 0`,
  `do {} while (0)`), a new `volatile`, inline assembly, a new `#include`, a new
  `#if`/`#ifdef`/`#ifndef`, or an added `GLOBAL_ASM` pragma.
- Inventory changes that are not the claimed matches: an added or removed
  function, a changed entry whose ID is not claimed (other than its `source`
  moving under `src/done/` with a completed unit), a claimed ID with no
  inventory change, or a claimed ID whose US state is not `matched` with zero
  differences. A `defer` therefore fails the policy, which is why rounds never
  defer.

The policy is a scope limit, not match evidence; `finish` and `verify-batch`
establish the match.

## Schedule

One routine, hourly, model `claude-opus-5-5`, environment
`MacBookPro.lan:conkers-bfd-decomp` (bridge). A fire that finds the machine
busy exits in seconds, so rounds run back to back whenever the machine is free:
with a 180-minute budget that is five to seven rounds a day. Requirements on the
Mac: the desktop app open, Docker running, the US ROM at
`roms/baserom.us.z64` in the main checkout.

Routine prompt (self-contained; the session starts in the main checkout and
runs the driver from a detached `../conker-auto-driver` worktree at
`origin/main`, so the main checkout is never modified):

```text
You are an unattended matching round for conkers-bfd-decomp. Work only through
the round driver and the normal ./conker commands. Never edit, commit or
switch branches in the checkout you start in.

0. Refresh the driver checkout from your starting directory:
   git fetch -q origin
   [ -d ../conker-auto-driver ] || git worktree add -q --detach ../conker-auto-driver origin/main
   git -C ../conker-auto-driver checkout -q --detach origin/main
   D="$(cd ../conker-auto-driver && pwd)/scripts/auto_round.sh"
   If "$D" does not exist, stop and report that the driver is not on main.
1. Run "$D" start --budget-minutes 180. If it prints AUTO_ROUND: BUSY, stop
   immediately with a one-line report.
2. cd into the printed WORKTREE. Run "$D" review-pending and note each PR
   verdict it prints (VERIFIED, MERGED, REQUEUED, NEEDS_HUMAN).
3. Read AGENTS.md and CONTRIBUTING.md there, then match functions following
   them exactly (finish must print AGENT_ACTION: STOP_MATCHED) until
   "$D" remaining is below 25. Lead order: `./conker sweep unchanged
   --max-score 300` zeros (resume, then finish), `./conker siblings
   --all-deferred`, then `./conker next --ready`. Read the history summary
   `next` prints: skip a function whose recorded attempts already exhausted
   your hypotheses unless you have a concrete new one, and record each new
   dead end with `./conker matching-history note <id> <attempt> --exhausted`.
   You have task permission for one `./conker permute <id> --budget 32` per
   distinct candidate when the latest finish diagnosis is register-only, as
   CONTRIBUTING allows. A function whose literals or jump tables live in its
   unit's own rodata may land with a new mapping, following the most recent
   commit that added one (git log -S'payload_size' -- config/game/us-rodata.ld):
   add the section and its extent ASSERT to config/game/us-rodata.ld, a .rodata
   owner record for the unit to config/data/us.json, and a note under
   docs/evidence/data-layout/ with its README entry. Never remove or change
   existing lines or records in either file. Never run defer, never edit include/, Makefile,
   scripts/, tests/ or any other config/ file, never add volatile, #if 0 or
   fake constructs; restore any function you do not match exactly with git
   checkout of its files.
4. With at least one STOP_MATCHED: run `./conker verify-batch <ids>` and
   require AGENT_ACTION: BATCH_COMPLETE; drop a function if it fails. Then
   "$D" commit -m "<summary>" and
   "$D" open-pr --ids "<ids>" --title "<title>" --body-file <file>
   with a body of exactly these sections, whatever earlier auto-match PRs
   contain: a one-line summary; a table of matched functions with source,
   start score and key change; shared dependency changed: no; the
   verify-batch result; and, only for functions blocked by something this
   round may not change (a shared header or prototype, a rodata mapping, a
   function boundary, tooling or reference symbolisation), a "Needs a
   maintainer" section with one line each, omitted when there are none. Do
   not write a leads section: near misses, scores and tried variants belong
   in matching history notes, not the PR body. Do not write an Auto-match
   IDs line; the driver adds it. Titles and bodies describe the work only: no model, agent
   or tool names.
5. Always finish with "$D" cleanup, then report in a few lines: PRs reviewed
   and their verdicts, functions matched, PR URL or "no PR", and anything
   labelled needs-human.
```

## Maintainer duties

- Handle `needs-human` PRs: fix and remove the label (the next round
  re-verifies), or close them.
- Approve the post-merge ROM verification environment when prompted, or relax
  that approval for main.
- Watch cost: a full day is up to ~20 model-hours of Opus 5.5. Lower the budget
  or the cron frequency in the routine when the match rate drops.
- Inspect a misbehaving run from `https://claude.ai/code/routines`.

## Local checks

```sh
bash -n scripts/auto_round.sh
python3 -m unittest discover -s tests -p 'test_auto_policy.py'
```
