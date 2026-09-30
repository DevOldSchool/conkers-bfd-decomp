# Cloud matching and reset recovery

A reproducible handoff for ChatGPT dot and other contributors working on
`DevOldSchool/conkers-bfd-decomp` in a cloud Linux executor. This is a setup and
coordination guide, not a replacement for [AGENTS.md](../AGENTS.md),
[CONTRIBUTING.md](../CONTRIBUTING.md), or the
[command reference](decompilation-workflow.md). Read those instructions and any
relevant checkout-local `.agents/skills/*/SKILL.md` before starting. Some
checkouts have no `.agents/skills` directory.

## 1. Establish the checkout and ownership

- Honor the requested cloud environment. Do not silently move work to a user's
  desktop. A fresh executor has no previous executor's filesystem or logins.
- Verify the repository URL, requested branch, full commit, clean/dirty status,
  and current work owner before editing. Preserve unrelated changes.
- Use isolated implementation checkouts. Worktrees isolate source but share Git
  metadata; an independent clone also isolates branch/ref operations. Never
  check out, reset, clean, or rewrite another worker's branch or worktree.
- Assign one integrator ownership of canonical inventory, source-unit records,
  linker configuration, generated progress, acceptance commands, and pushes.
  Review shared changes explicitly rather than letting multiple workers edit
  them concurrently.

```sh
git clone https://github.com/DevOldSchool/conkers-bfd-decomp.git conkers
cd conkers
git remote get-url origin
git fetch origin
git switch --track origin/<requested-branch>
git rev-parse HEAD
git status --short
git submodule update --init --recursive
git submodule status --recursive
```

Use an explicit recorded commit when resuming a checkpoint; do not assume a
branch name still identifies that checkpoint. At the September 30, 2026
recovery point, the published checkpoints were:

- `feature/asm-to-c`: `9189c0498065748a2c8560751958f6d0bae51f4a`
- `feature/main-boundaries`: `e31152eee24e3a1856d75828979f9df497326467`

These are historical anchors, not instructions to reset newer work. Verify the
current remote and resume its newer accepted work when appropriate. The
`lib/ultralib` submodule at this checkpoint is pinned to
`87af1e4d8ed666f2ad407dc11c6e47736094f2f8`. Initialize submodules in every
checkout that builds: `doctor` can pass while a missing submodule breaks the
first real game/full build. Never substitute the submodule's latest branch.

## 2. Restore the exact compiler environment

Use ordinary Docker with the repository's pinned image when available. On a
restricted Linux x86-64 executor where Docker/rootless Docker cannot operate,
use the reviewed namespace adapter in
[`toolchain/cloud-bootstrap`](../toolchain/cloud-bootstrap/README.md). It keeps
normal `./conker` commands and the exact CPU compiler environment. It is a
narrow compatibility adapter, not Docker Engine.

Current immutable pins, also checked against `toolchain/tools.lock.json`:

- CPU image: `ghcr.io/devoldschool/conkers-bfd-decomp-toolchain@sha256:b3e29a92f2c26f11a58fbafde2d5d3b1184416e21b635e07b2a6303591ed5c8b`
- Linux AMD64 manifest: `sha256:3da4b9927f4cc0db09155734cf7572dbb379020ac93cad6c3e796b4ceef40d2b`
- Image configuration: `sha256:10a77ef378fd060dfec5756b8b195197fbf5c399c4f35798eb1ca9344c934fc8`
- IDO static recomp: `v1.2`; archive SHA-256
  `ab5c741561f80913d58c8b074771f23941a3edd312505a8ebed6d1dfeb65e506`
- RSP armips: `156f78f6bccfc07498578ac491ce7fe2a1e807a6`
- RSP recipe SHA-256: `b161bd2fdb84561aa0480fe553e1806420ba7f3caf648dffa0331b42b426713c`

The image alone does not supply the project's RSP extension. Bootstrap rebuilds
armips from the pinned upstream source using the verified image's compiler and
the repository's recipe. Its CMake wheel is pinned by version and SHA-256.
A reviewed private recovery kit can instead supply the verified armips binary;
keep its license and receipt with it. Do not put compiler binaries, image
layers, tool caches, or local recovery artifacts in Git.

### Source-only bootstrap

Prerequisites: Linux x86-64, Python 3 with pip, Git, `/usr/bin/bwrap`,
`/usr/bin/unshare`, permitted unprivileged namespaces, and permitted access to
public GHCR, GitHub, and the Python package registry. Install missing host tools
only through the executor's approved software/setup path. Namespace/network
policy failures are blockers, not permission to weaken isolation.

Choose a writable runtime directory outside every repository. The following
copies only reviewed scripts and a public provenance receipt:

```sh
repo="$PWD"
runtime=/absolute/writable/path/conker-cloud-toolchain
# Use a new, nonexistent destination; do not overwrite a running adapter.
test ! -e "$runtime" || exit 1
mkdir -m 700 "$runtime"
cp -R toolchain/cloud-bootstrap/. "$runtime/"
python3 "$runtime/bootstrap.py" --rebuild-armips "$repo"
export PATH="$runtime/bin:$PATH"
./conker doctor
```

On subsequent shells, restore this PATH explicitly. Keep the same runtime warm
across targets; do not rebuild it per function. Pass all explicit build checkout
roots in one bootstrap invocation when adding a worker; the allowlist is
replaced, not appended. Coordinate that operation with the integrator. Do not
pass a parent workspace or credential directory as an allowed checkout.

The adapter verifies OCI manifest/config/layer digests, the CPU/RSP pins, and
armips provenance. It uses an unprivileged user/network namespace, read-only
root and source mounts, no external network routes, zero capabilities,
NoNewPrivs, and fresh PID/IPC/UTS/cgroup namespaces. Only explicitly requested
repository output mounts are writable. RLIMIT_NPROC enforces up to 512
processes per real host UID, not an independent Docker cgroup quota. A warm
container is a saved mount recipe; each execution creates fresh isolation and
`/tmp` is not persistent. See the adapter README for limits and verification.

Never enable privileged execution, host networking, arbitrary host mounts,
`--not-a-security-boundary`, or mutable substitute images to get past a failed
bootstrap. Never mount credentials into the toolchain. Do not change CPU
compiler flags or assembly to make a candidate match.

## 3. Restore the private owned-ROM input and prove setup

The user supplies an owned North American ROM privately. Do not obtain a ROM
from public downloads or another decompilation repository. Restore it through
the current executor's supported private file-input mechanism, verify the file
exists locally, then copy it into this checkout's ignored `roms/` directory.
Private file service IDs and signed URLs do not belong in repository docs.

```sh
mkdir -p roms
cp /private/input/owned-us-rom.z64 roms/baserom.us.z64
sha1sum roms/baserom.us.z64
./conker setup --us roms/baserom.us.z64
```

Required SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`, also pinned in
`config/roms.json`. Stop on a mismatch. US is active; EU/PAL does not gate this
work. No ROM, extracted/generated ROM-derived payload, credentials, or private
input identifiers may be committed, attached to a public issue, or included in
a public artifact.

Before matching new work, prove a known match and the full environment:

```sh
# Known accepted actor playback-rate match at the checkpoint above.
./conker diff func_1505841C
./conker rsp
./conker build --all
./conker game-build --refresh
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

First verify that `func_1505841C` is still an accepted C function on the selected
branch; if absent, select an existing accepted ID from that branch's inventory.
The quick check must report `CURRENT (0)` against independent raw assembly. It
is a smoke check, not permission to skip full baseline gates or record new
matches. `rsp` verifies the configured ROM-backed RSP payloads; the main ROM and
game-image builds cover different outputs. Preserve logs with the tested
commit and tool pins. A doctor-only success is not a ROM baseline success.

## 4. Match efficiently without repeating exhausted work

Read relevant `docs/evidence/` records and prior task-owned ledgers under
`build/us/manual-attempts/` before selecting hypotheses. After a reset, restore
private attempt records separately from Git when available. Check source,
reference, relevant declaration/header/toolchain, and search-setting
fingerprints before reusing a result. If old artifacts are unavailable, report
that limit; do not claim an untried search.

For each selected item:

1. Run `./conker next --ready` once. Use its declarations, raw call sites,
   starter, `allowed-edit`, dirty-file status, source-unit state, and required
   post-match action. Do not separately repeat queue/prewarm/context commands.
2. Prioritize short spans, concrete type/declaration fixes, and proven sibling
   source shapes. A low score alone does not establish an easy match.
3. Make one narrow C hypothesis at the existing pragma position. Preserve ABI,
   source order, actual field widths, and known types. Before the first
   candidate, allow at most one additional batched context lookup, except for
   compiler-reported missing declarations.
4. Immediately run `./conker finish <id>`. Follow its terminal action. Focused
   zero followed by layout failure is an integration problem, not an accepted
   match. Never rerun an unchanged failed gate.
5. Make at most two targeted manual revisions per distinct candidate/settings
   by default. Stop after two non-improving revisions unless concrete new
   evidence and the authorized budget justify more. Record the hypothesis,
   fingerprint, score/class, exact changes, best artifact, and exhausted ideas.
6. Use permutation only if the task permits it and a specific untried supported
   transformation fits the diagnosis; the default ceiling is one 32-variant
   search per distinct candidate/settings. Manual-only work stays manual.
   Register-only classification alone does not justify search.
7. If authorized to move on, retain the best candidate through supported
   `defer`; use `resume` and `reopen-match` for recovery. Do not edit inventory
   state by hand. Candidate improvements are not new matches.

A successful sibling suggests one bounded follow-up lookup, not broad search.
Verify every sibling independently. Preserve attempts and pending batch IDs
before compaction, executor reset, or worker handoff. Keep model settings as
requested; assess changes using newly batch-verified matches per wall-clock
hour and measured tokens when available, not command-output bytes.

## 5. Parallel source work, serialized acceptance

The integrator assigns disjoint source families, target IDs, a base commit,
allowed files, and hypothesis budgets. A worker gets a separate checkout and
returns a source-only patch plus its evidence and attempts. It must not edit
shared headers, linker scripts, canonical JSON, or generated progress, and must
not run state-mutating commands in the integration checkout. Never work on
multiple targets in the same C file concurrently under different ownership.

Workers may inspect/reason independently or test in fully isolated, initialized
checkouts. A worker using `finish` in its own checkout must follow all local
acceptance rules there; return only the allowed source patch and report the
local state/evidence separately. Local worker acceptance never updates the
canonical branch. Do not run independent builds against shared generated output
or writable submodule build directories. Isolate those as well, or serialize
builds through the integrator.

The sole integrator checks patches against current source, applies them one at
a time, and immediately runs authoritative `finish` on each target. It alone
handles reviewed shared changes, source-unit integration and clean batches.
Discard/rebase a stale patch rather than overwriting a newer candidate. Stop and
resolve overlapping ownership before either worker edits more.

## 6. Acceptance and checkpoint checklist

A function is accepted only with independent raw-assembly US `CURRENT (0)` over
the entire registered span, plus source-unit layout, canonical progress, and
whitespace gates. Instruction matching, external data/rodata ownership, and
original source boundaries are separate claims. Switch tables must be checked
against the checksum-validated ROM; unsupported table/relocation forms fail
closed. Never declare a match from same-source output, partial spans,
register-insensitive comparison, compilation alone, disabled table checks,
artificial padding, handwritten/inline assembly, or altered reference code.

- Follow `post-match-action` immediately. After integration rerun
  `./conker progress check` and whitespace checks. A matched member does not
  complete its source unit.
- Keep a durable pending-ID list. Aim for 5–10 focused matches per clean batch;
  flush smaller groups about 45 minutes after the first match and always before
  stopping, handing off, committing, or opening a PR. Do not delay an immediate
  integration boundary to fill a batch.
- Run `./conker verify-batch <ids...>` without `--incremental`. Success means
  `BATCH_COMPLETE`, including required main/game builds, tests, metadata,
  progress and whitespace. Clear pending IDs only after clean success.
- Never retry an unchanged failed clean batch. Fix the actual source/layout
  problem; otherwise preserve and report the pending group and blocker.
- Regenerate progress through `./conker progress render` when required; never
  hand-edit generated reports. Keep candidates, verified original assembly,
  existing-match rechecks, and newly batch-verified C matches separate.
- Commit reviewable verified checkpoints regularly, using explicit file paths
  rather than blind `git add -A`. Inspect staged content for private inputs and
  unrelated changes. Document tested commit, focused results, batch result,
  attempts, changed files, and any remaining limitation. Do not merge unless
  separately authorized.

## 7. Push safely, verify remotely, retain recovery fallback

Prefer ordinary Git push over large connector uploads. Verify the authenticated
account and exact HTTPS remote first. If a valid authorized login already
exists, reuse it; do not create another credential. Do not print, read, copy, or
package the credential store.

If fresh authentication is necessary, stop for explicit user approval of the
persistent grant. Explain the scopes actually requested: GitHub CLI 2.46's
default login requested account-wide `repo`, `read:org`, and `gist` scopes, not
single-repository access. If no secure credential store is available, disclose
the plaintext fallback before proceeding. The user completes the secure/device
flow; never ask for a token or password in chat.

For a read-only home directory, use a writable private configuration directory
outside all repositories and create it mode 700 before login. Answer **No** to
global Git-auth configuration, and use the helper only on the needed command.
The placeholders below are local values, never repository content:

```sh
export GH_CONFIG_DIR=/absolute/private/outside-repos/github-cli
# For a new directory only, before the user-approved login:
mkdir -m 700 "$GH_CONFIG_DIR"
gh auth login --hostname github.com --git-protocol https --web
# Do not dump gh config, tokens, environment, or credential files.
gh api user --jq .login
git remote get-url origin

branch=feature/asm-to-c  # Use only the explicitly assigned branch.
sha=$(git rev-parse HEAD)
GIT_TERMINAL_PROMPT=0 git -c credential.helper= \
  -c 'credential.helper=!gh auth git-credential' \
  push https://github.com/DevOldSchool/conkers-bfd-decomp.git \
  "$sha:refs/heads/$branch"

gh api "repos/DevOldSchool/conkers-bfd-decomp/git/ref/heads/$branch" --jq .object.sha
git rev-parse "$sha^{tree}"
gh api "repos/DevOldSchool/conkers-bfd-decomp/git/commits/$sha" --jq .tree.sha
```

Require exact remote SHA and tree agreement before reporting a successful push.
If the remote moved, fetch and reconcile with the owner; never force-push or
reset another worker's work. On an ambiguous timeout, read back the remote
before retrying. Check CI for the exact published commit where available;
public CI is not a replacement for local ROM-backed acceptance.

If pushing is blocked, preserve a private cumulative Git bundle and a manifest
with repository, branch, full head SHA, tree SHA, parent/base, checks, and pending
IDs. Include all history necessary to restore the branch rather than a fragile
sequence of deltas:

```sh
git bundle create /private/output/matching-checkpoint.bundle "$branch"
git bundle verify /private/output/matching-checkpoint.bundle
sha256sum /private/output/matching-checkpoint.bundle
# Test restoration in a separate empty destination, never over active work.
git clone --branch "$branch" /private/output/matching-checkpoint.bundle \
  /private/output/restore-check
git -C /private/output/restore-check rev-parse HEAD HEAD^{tree}
```

Save the bundle and nonsecret manifest through the authorized private artifact
channel. Keep owned ROM input, attempt-ledger archive, and toolchain recovery
kit separate; never include authentication material. A bundle preserves Git
objects, not ignored ROMs, generated outputs, submodule working trees, login
state, or pending uncommitted work. Record those gaps explicitly. After a reset,
verify artifact hashes, restore/verify the branch, initialize pinned submodules,
restore toolchain and owned ROM privately, then rerun setup and baseline checks.
